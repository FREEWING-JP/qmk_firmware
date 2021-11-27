// Copyright 2021 Y.Sakamoto (@FREEWING-JP)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        AU_ON, KC_2,    KC_1,  MO(_FN1)
    ),
    [_FN1] = LAYOUT(
        AU_OFF, RESET,  RESET, _______
    ),
    [_FN2] = LAYOUT(
        AU_OFF, RESET,  RESET, _______
    ),
    [_FN3] = LAYOUT(
        AU_OFF, RESET,  RESET, _______
    )
};

#ifdef OLED_ENABLE
#include <stdio.h>
//#include "oled_display.h"
#include "oled_driver.h"

uint16_t oledState = 0;

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
}

void oled_task_user(void) {
    if (oledState == 0) {
        oled_clear();
        render_logo();
        oledState = 1;
        return;
    } else if (oledState == 1) {
        if (timer_read() < 5000) {
            // Display Logo 5 sec
        } else {
            oled_clear();
            oledState = 2;
        }
        return;
    }

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _FN1:
            oled_write_P(PSTR("FN1\n"), false);
            break;
        case _FN2:
            oled_write_P(PSTR("FN2\n"), false);
            break;
        case _FN3:
            oled_write_P(PSTR("FN3\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("[NUM]") : PSTR("[   ]"), led_state.num_lock);
    oled_write_P(led_state.caps_lock ? PSTR("[CAP]") : PSTR("[   ]"), led_state.caps_lock);
    oled_write_P(led_state.scroll_lock ? PSTR("[SCR]") : PSTR("[   ]"), led_state.scroll_lock);
    oled_write_P(PSTR("\n"), false);

#ifdef DEBUG_MATRIX_SCAN_RATE
    char str[24] = "";
    sprintf(str, "Scan rate:%5ld/sec", get_matrix_scan_rate());
    oled_write(str, false);
#endif
}
#endif
