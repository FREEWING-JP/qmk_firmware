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
