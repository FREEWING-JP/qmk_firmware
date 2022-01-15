// Copyright 2021 Y.Sakamoto (@FREEWING-JP)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"
#include "gpio.h"
#include "i2c_master.h"
#include "quantum.h"

#if (MATRIX_COLS > 8)
#    error "MATRIX_COLS must be 8 or less"
#endif

#if (MATRIX_ROWS <= 8)
#    define ROW_TYPE uint8_t
#    define matrix_bitpop(bits) bitpop(bits)
#elif (MATRIX_ROWS <= 16)
#    define ROW_TYPE uint16_t
#    define matrix_bitpop(bits) bitpop16(bits)
#elif (MATRIX_ROWS <= 32)
#    define ROW_TYPE uint32_t
#    define matrix_bitpop(bits) bitpop32(bits)
#endif

#define ROW_SHIFTER ((ROW_TYPE)1)

#define MAXIMUM_ACCEPT_HIT_KEY 6

#define PCF857x_I2C_TIMEOUT 50

#define I2C_WRITE 0x00
#define I2C_READ 0x01

// Col Output PCF8574 (A2=L, A1=L, A0=L)
#define I2C_ADDR_COL 0x20
#define I2C_ADDR_COL_WRITE ((I2C_ADDR_COL << 1) | I2C_WRITE)
#define I2C_ADDR_COL_READ ((I2C_ADDR_COL << 1) | I2C_READ)

// Row Input PCF8574 (A2=H, A1=L, A0=L)
#define I2C_ADDR_ROW 0x24
#define I2C_ADDR_ROW_WRITE ((I2C_ADDR_ROW << 1) | I2C_WRITE)
#define I2C_ADDR_ROW_READ ((I2C_ADDR_ROW << 1) | I2C_READ)

// Col Output PCF8574 8bit
static void col_init(void) {
    // All Output 'H'
    uint8_t buf[] = { 0b11111111 };
    i2c_transmit(I2C_ADDR_COL_WRITE, buf, sizeof(buf), PCF857x_I2C_TIMEOUT);
}

// Row Input PCF8574 8bit / PCF8575 16bit
static void row_init(void) {
#if (MATRIX_ROWS <= 8)
    // Row Input PCF8574 8bit
    // All Input Pull Up
    // Row 0 - 7 Input 'L' active
    uint8_t buf[] = { 0b11111111 };
    i2c_transmit(I2C_ADDR_ROW_WRITE, buf, sizeof(buf), PCF857x_I2C_TIMEOUT);
#elif (MATRIX_ROWS <= 16)
    // Row Input PCF8575 16bit
    // All Input Pull Up
    // Row 0 - 15 Input 'L' active
    uint8_t buf[] = { 0b11111111, 0b11111111 };
    i2c_transmit(I2C_ADDR_ROW_WRITE, buf, sizeof(buf), PCF857x_I2C_TIMEOUT);
#elif (MATRIX_ROWS <= 32)
    // Row Input PCF8575 16bit
    // All Input Pull Up
    // Row 0 - 15 Input 'L' active
    uint8_t buf[] = { 0b11111111, 0b11111111 };
    i2c_transmit(I2C_ADDR_ROW_WRITE, buf, sizeof(buf), PCF857x_I2C_TIMEOUT);

    // Row 16 Input 'L' active
    setPinInputHigh(B4);

    // Row 17 Input 'L' active
    setPinInputHigh(B5);
#endif
}

// Col Output PCF8574 8bit
static void select_col(uint8_t col) {
    // Col Output 'L'
    uint8_t colByte = ~(1 << col);
    uint8_t buf[] = { colByte };
    i2c_transmit(I2C_ADDR_COL_WRITE, buf, sizeof(buf), PCF857x_I2C_TIMEOUT);
}

// Row Input PCF8574 8bit / PCF8575 16bit
static ROW_TYPE read_rows(void) {
#if (MATRIX_ROWS <= 8)
    // Row Input PCF8574 8bit
    uint8_t buf[1];
    i2c_receive(I2C_ADDR_ROW_READ, buf, sizeof(buf), PCF857x_I2C_TIMEOUT);
    return ~buf[0];
#elif (MATRIX_ROWS <= 16)
    // Row Input PCF8575 16bit
    uint8_t buf[2];
    i2c_receive(I2C_ADDR_ROW_READ, buf, sizeof(buf), PCF857x_I2C_TIMEOUT);
    return ~((buf[1] << 8) | buf[0]);
#elif (MATRIX_ROWS <= 32)
    // Row Input PCF8575 16bit
    uint8_t buf[2];
    i2c_receive(I2C_ADDR_ROW_READ, buf, sizeof(buf), PCF857x_I2C_TIMEOUT);

    // Row 16 'L' active
    uint8_t buf2 = (readPin(B4) ? 0 : 1);
    // Row 17 'L' active
    buf2 |= (readPin(B5) ? 0 : 2);

    return (buf2 << 16) | ~((buf[1] << 8) | buf[0]);
#endif
}

void matrix_init_custom(void) {
    i2c_init();
    col_init();
    row_init();
}

// MATRIX_ROWS = 4
// MATRIX_COLS = 4
// matrix_row_t = uint8_t
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // Scan Keyboard Matrix
    ROW_TYPE tmp_rows[MATRIX_COLS];
    ROW_TYPE* pt = tmp_rows;
    for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
        // MSB = col 7, LSB = col 0
        select_col(col);
        matrix_io_delay();

        *pt++ = read_rows();
    }
    col_init();

#ifdef MAXIMUM_ACCEPT_HIT_KEY
    // Check Maximum Accept Hit Key count
    uint8_t hit_key_count = 0;
    for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
        ROW_TYPE rows = tmp_rows[col];

        // Hit None Key is Continue
        if (rows == 0) continue;

        // Counting Hit Key
        hit_key_count += matrix_bitpop(rows);

        // Not Accept over Maximum Accept Hit Key
        if (hit_key_count > MAXIMUM_ACCEPT_HIT_KEY) return false;
    }
#endif

    // Hunt Keyboard Matrix Ghost for Anti Ghosting by FREE WING
    for (uint8_t col = 0; col < MATRIX_COLS - 1; ++col) {
        ROW_TYPE rows = tmp_rows[col];

        // Hit None Key is Pass without Complaint
        if (rows == 0) continue;

        // Only Hit One Key
        bool hit_one_key = (matrix_bitpop(rows) == 1);

        // Check Ghost
        for (uint8_t col2 = MATRIX_COLS - 1; col2 > col; --col2) {

            // Not detecting bits is Safe
            if (!(rows & tmp_rows[col2])) continue;

            // When Only Hit One Key, Not detecting other bit is Safe
            if (hit_one_key && !(rows ^ tmp_rows[col2])) continue;

            // Catch Ghost !!
            // We are Keyboard Matrix Ghost Busters !!
            return false;
        }
    }

    // Check Keyboard Matrix has Changed
    bool matrix_has_changed = false;
    matrix_row_t* p = current_matrix;
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {

        // Convert Rows data to Column data Matrix
        ROW_TYPE and_row = (ROW_SHIFTER << row);
        matrix_row_t now_rows = 0;
        int8_t col = MATRIX_COLS;
        while (--col >= 0) {
            now_rows <<= 1;
            now_rows |= ((tmp_rows[col] & and_row) ? 1 : 0);
        }

        // Has Changed
        if (*p != now_rows) {
            *p = now_rows;
            matrix_has_changed = true;
        }
        ++p;
    }

    return matrix_has_changed;
}

