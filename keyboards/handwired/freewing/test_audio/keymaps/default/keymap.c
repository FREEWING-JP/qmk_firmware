// Copyright 2021 Y.Sakamoto (@FREEWING-JP)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKSONG1 = SAFE_RANGE,
    QMKSONG2,
    QMKSONG3,
    QMKSONG4,
    QMKSONG5,
    QMKSONG6,
    QMKSONG7,
    QMKSONG8,
    QMKSONG9,
    QMKSONG10,
    QMKSONG11,
    QMKSONG12,
    QMKSONG13,
    QMKSONG14,
    QMKSONG15
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        QMKSONG1,    QMKSONG2,    QMKSONG3,    QMKSONG4,
        QMKSONG5,    QMKSONG6,    QMKSONG7,    QMKSONG8,
        QMKSONG9,    QMKSONG10,   QMKSONG11,   QMKSONG12,
        QMKSONG13,   QMKSONG14,   QMKSONG15,   MO(_FN)
    ),
    [_FN] = LAYOUT(
        QMKSONG1,    QMKSONG2,    QMKSONG3,    QMKSONG4,
        QMKSONG5,    QMKSONG6,    QMKSONG7,    QMKSONG8,
        QMKSONG9,    QMKSONG10,   QMKSONG11,   QMKSONG12,
        QMKSONG13,   QMKSONG14,   QMKSONG15,   _______
    )
};

#ifdef AUDIO_ENABLE
float song1[][2] = SONG(CAMPANELLA);
float song2[][2] = SONG(FANTASIE_IMPROMPTU);
float song3[][2] = SONG(ROCK_A_BYE_BABY);
float song4[][2] = SONG(AG_SWAP_SOUND);
float song5[][2] = SONG(WORKMAN_SOUND);
/*
float song6[][2] = SONG(CHROMATIC_SOUND);
float song7[][2] = SONG(GUITAR_SOUND);
float song8[][2] = SONG(VIOLIN_SOUND);
float song9[][2] = SONG(MAJOR_SOUND);
float song10[][2] = SONG(MINOR_SOUND);
float song11[][2] = SONG(ODE_TO_JOY);
float song12[][2] = SONG(ROCK_A_BYE_BABY);
float song13[][2] = SONG(CAMPANELLA);
float song14[][2] = SONG(FANTASIE_IMPROMPTU);
float song15[][2] = SONG(NOCTURNE_OP_9_NO_1);
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKSONG1:
            if (record->event.pressed) {
                // when keycode QMKSONG1 is pressed
                PLAY_SONG(song1);
            } else {
                // when keycode QMKSONG1 is released
            }
            break;
        case QMKSONG2:
            if (record->event.pressed) {
                // when keycode QMKSONG2 is pressed
                PLAY_SONG(song2);
            } else {
                // when keycode QMKSONG2 is released
            }
            break;
        case QMKSONG3:
            if (record->event.pressed) {
                // when keycode QMKSONG3 is pressed
                PLAY_SONG(song3);
            } else {
                // when keycode QMKSONG3 is released
            }
            break;
        case QMKSONG4:
            if (record->event.pressed) {
                // when keycode QMKSONG4 is pressed
                PLAY_SONG(song4);
            } else {
                // when keycode QMKSONG4 is released
            }
            break;
        case QMKSONG5:
            if (record->event.pressed) {
                // when keycode QMKSONG5 is pressed
                PLAY_SONG(song5);
            } else {
                // when keycode QMKSONG5 is released
            }
            break;
/*
        case QMKSONG6:
            if (record->event.pressed) {
                // when keycode QMKSONG6 is pressed
                PLAY_SONG(song6);
            } else {
                // when keycode QMKSONG6 is released
            }
            break;
        case QMKSONG7:
            if (record->event.pressed) {
                // when keycode QMKSONG7 is pressed
                PLAY_SONG(song7);
            } else {
                // when keycode QMKSONG7 is released
            }
            break;
        case QMKSONG8:
            if (record->event.pressed) {
                // when keycode QMKSONG8 is pressed
                PLAY_SONG(song8);
            } else {
                // when keycode QMKSONG8 is released
            }
            break;
        case QMKSONG9:
            if (record->event.pressed) {
                // when keycode QMKSONG9 is pressed
                PLAY_SONG(song9);
            } else {
                // when keycode QMKSONG9 is released
            }
            break;
        case QMKSONG10:
            if (record->event.pressed) {
                // when keycode QMKSONG10 is pressed
                PLAY_SONG(song10);
            } else {
                // when keycode QMKSONG10 is released
            }
            break;
        case QMKSONG11:
            if (record->event.pressed) {
                // when keycode QMKSONG11 is pressed
                PLAY_SONG(song11);
            } else {
                // when keycode QMKSONG11 is released
            }
            break;
        case QMKSONG12:
            if (record->event.pressed) {
                // when keycode QMKSONG12 is pressed
                PLAY_SONG(song12);
            } else {
                // when keycode QMKSONG12 is released
            }
            break;
        case QMKSONG13:
            if (record->event.pressed) {
                // when keycode QMKSONG13 is pressed
                PLAY_SONG(song13);
            } else {
                // when keycode QMKSONG13 is released
            }
            break;
        case QMKSONG14:
            if (record->event.pressed) {
                // when keycode QMKSONG14 is pressed
                PLAY_SONG(song14);
            } else {
                // when keycode QMKSONG14 is released
            }
            break;
        case QMKSONG15:
            if (record->event.pressed) {
                // when keycode QMKSONG15 is pressed
                PLAY_SONG(song15);
            } else {
                // when keycode QMKSONG15 is released
            }
            break;
*/
    }

    return true;
}
#endif

