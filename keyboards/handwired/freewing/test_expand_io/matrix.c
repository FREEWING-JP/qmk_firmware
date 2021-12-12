// Copyright 2021 Y.Sakamoto (@FREEWING-JP)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"
#include "gpio.h"

// Col Output selector /Y0-/Y7 8bit
// #define MATRIX_COL_PINS { F5, F6, F7 }
static void select_col(uint8_t col) {
    writePin(F5, (col & 1));
    writePin(F6, (col & 2));
    writePin(F7, (col & 4));
}

// Row Input selector I0-I15 16bit
// #define MATRIX_ROW_PINS { B6, B2, B3, B1 } = { E6 }
static void select_row(uint8_t row) {
    writePin(B6, (row & 1));
    writePin(B2, (row & 2));
    writePin(B3, (row & 4));
    writePin(B1, (row & 8));
}

// Row I0-I15 16bit
// { E6 }
static matrix_row_t read_rows(uint8_t row) {
    int inputPin;

    if (row < 16) {
        // I0-I15
        select_row(row);
        inputPin = E6;
    }

    matrix_row_t rows = 0;
    for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
        // MSB = col 7, LSB = col 0
        select_col(MATRIX_COLS - 1 - col);
        matrix_io_delay();

        rows <<= 1;
        rows |= (readPin(inputPin) ? 0 : 1);
    }

    return rows;
}

void matrix_init_custom(void) {
    /* Col pin configuration
     * 74HC138 3-to-8 line decoder/demultiplexer
     * 74HC4051 3-to-8 analog multiplexer/demultiplexer
     *  pin: xx  F7  F6  F5
     *    Z   1   0   0   0
     *  /Y0   0   0   0   0
     *  /Y1   0   0   0   1
     *  /Y2   0   0   1   0
     *  /Y3   0   0   1   1
     *  /Y4   0   1   0   0
     *  /Y5   0   1   0   1
     *  /Y6   0   1   1   0
     *  /Y7   0   1   1   1
     * 74HC4051 COM = GND = 'L'
     */
    setPinOutput(F5); // Bit0 1
    setPinOutput(F6); // Bit1 2
    setPinOutput(F7); // Bit2 4
    // setPinOutput(xx); // /Enable
    // writePinHigh(xx); // Disable

    /* Row pin configuration
     * 74HC4067 16-channel analog multiplexer/demultiplexer
     *  pin:  B1  B3  B2  B6
     *   I0    0   0   0   0
     *   I1    0   0   0   1
     *   I2    0   0   1   0
     *   I3    0   0   1   1
     *   I4    0   1   0   0
     *   I5    0   1   0   1
     *   I6    0   1   1   0
     *   I7    0   1   1   1
     *   I8    1   0   0   0
     *   I9    1   0   0   1
     *   I10   1   0   1   0
     *   I11   1   0   1   1
     *   I12   1   1   0   0
     *   I13   1   1   0   1
     *   I14   1   1   1   0
     *   I15   1   1   1   1
     */
    setPinOutput(B6); // Bit0 1
    setPinOutput(B2); // Bit1 2
    setPinOutput(B3); // Bit2 4
    setPinOutput(B1); // Bit3 8

    // Row pin Input I0-I15 74HC4067 Common 'L' active
    setPinInputHigh(E6);
}

// MATRIX_ROWS = 16
// MATRIX_COLS = 8
// matrix_row_t = uint8_t
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // writePinLow(xx); // Enable
    matrix_row_t* p = current_matrix;

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        matrix_row_t now_rows = read_rows(row);
        if (*p != now_rows) {
            *p = now_rows;
            matrix_has_changed = true;
        }
        ++p;
    }
    // writePinHigh(xx); // Disable

    return matrix_has_changed;
}

