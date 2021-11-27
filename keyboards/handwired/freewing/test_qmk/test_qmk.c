// Copyright 2021 Y.Sakamoto (@FREEWING-JP)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "test_qmk.h"

#ifdef JOYSTICK_ENABLE
#include "joystick.h"
#include "analog.h"

/* joystick config */
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_IN(B4, 0, 512, 1023),
    [1] = JOYSTICK_AXIS_IN(B5, 0, 512, 1023)
};

/* joystick button code (thumbstick pressed) */
void keyboard_pre_init_kb(void) {
     // setPinInputHigh(F6);
}
#endif
