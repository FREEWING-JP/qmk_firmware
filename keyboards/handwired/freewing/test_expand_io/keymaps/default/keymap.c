// Copyright 2021 Y.Sakamoto (@FREEWING-JP)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,
        KC_5,    KC_6,    KC_7,    KC_8,
        KC_9,    KC_A,    KC_B,    KC_C,
        KC_D,    KC_E,    KC_F,    MO(_FN)
    ),
    [_FN] = LAYOUT(
        KC_G,    KC_H,    KC_I,    KC_J,
        KC_K,    KC_L,    KC_M,    KC_N,
        KC_O,    KC_P ,   KC_Q,    KC_R,
        KC_S,    KC_T,    KC_U,    _______
    )
};

#ifdef AUDIO_ENABLE
  #include "audio.h"

  float song1[][2] = SONG(STARTUP_SOUND);
  float song2[][2] = SONG(GOODBYE_SOUND);
  float song3[][2] = SONG(PLANCK_SOUND);
  float song4[][2] = SONG(PREONIC_SOUND);
  float song5[][2] = SONG(QWERTY_SOUND);
  float song6[][2] = SONG(COLEMAK_SOUND);
  float song7[][2] = SONG(DVORAK_SOUND);
  float song8[][2] = SONG(WORKMAN_SOUND);


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_1:
            if (record->event.pressed) {
                // when keycode KC_1 is pressed
                PLAY_SONG(song1);
            } else {
                // when keycode KC_1 is released
            }
            break;
        case KC_2:
            if (record->event.pressed) {
                // when keycode KC_2 is pressed
                PLAY_SONG(song2);
            } else {
                // when keycode KC_2 is released
            }
            break;
        case KC_3:
            if (record->event.pressed) {
                // when keycode KC_3 is pressed
                PLAY_SONG(song3);
            } else {
                // when keycode KC_3 is released
            }
            break;
        case KC_4:
            if (record->event.pressed) {
                // when keycode KC_4 is pressed
                PLAY_SONG(song4);
            } else {
                // when keycode KC_4 is released
            }
            break;
        case KC_5:
            if (record->event.pressed) {
                // when keycode KC_5 is pressed
                PLAY_SONG(song5);
            } else {
                // when keycode KC_5 is released
            }
            break;
        case KC_6:
            if (record->event.pressed) {
                // when keycode KC_6 is pressed
                PLAY_SONG(song6);
            } else {
                // when keycode KC_6 is released
            }
            break;
        case KC_7:
            if (record->event.pressed) {
                // when keycode KC_7 is pressed
                PLAY_SONG(song7);
            } else {
                // when keycode KC_7 is released
            }
            break;
        case KC_8:
            if (record->event.pressed) {
                // when keycode KC_8 is pressed
                PLAY_SONG(song8);
            } else {
                // when keycode KC_8 is released
            }
            break;
    }

    return true;
}
#endif

