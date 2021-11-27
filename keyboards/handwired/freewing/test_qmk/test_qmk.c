// Copyright 2021 Y.Sakamoto (@FREEWING-JP)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "test_qmk.h"

#ifdef JOYSTICK_ENABLE
#include "joystick.h"
#include "analog.h"

void joystick_task(){
    joystick_status.axes[0] = analogReadPin(B4)/4 - 128;
    joystick_status.axes[1] = analogReadPin(B5)/4 - 128;
    joystick_status.status |= JS_UPDATED;
    send_joystick_packet(&joystick_status);
}
#endif
