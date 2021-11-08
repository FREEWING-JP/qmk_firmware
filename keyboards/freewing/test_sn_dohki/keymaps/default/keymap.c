// Copyright 2021 Y.Sakamoto (@FREEWING-JP)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_DEL,   KC_PSCR,
        KC_HOME,  KC_UP,   KC_END,  KC_PGUP,
        KC_LEFT,  KC_DOWN, KC_RGHT, KC_PGDN
    )
};
