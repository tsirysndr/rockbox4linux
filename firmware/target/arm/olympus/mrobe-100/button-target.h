/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id: button-target.h 22053 2009-07-26 14:26:14Z roolku $
 *
 * Copyright (C) 2008 by Mark Arigo
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/

#ifndef _BUTTON_TARGET_H_
#define _BUTTON_TARGET_H_

#include <stdbool.h>
#include "config.h"

#define MEP_BUTTON_HEADER   0x1a
#define MEP_BUTTON_ID       0x09
#define MEP_ABSOLUTE_HEADER 0x0b

bool button_hold(void);
void button_init_device(void);
int  button_read_device(void);

#ifndef BOOTLOADER
void button_int(void);
#endif

/* Main unit's buttons */
#define BUTTON_PLAY         0x00000001
#define BUTTON_MENU         0x00000002
#define BUTTON_LEFT         0x00000004
#define BUTTON_DISPLAY      0x00000008
#define BUTTON_RIGHT        0x00000010
#define BUTTON_SELECT       0x00000020
#define BUTTON_UP           0x00000040
#define BUTTON_SLIDE_UP     0x00000080
#define BUTTON_DOWN         0x00000100
#define BUTTON_SLIDE_DOWN   0x00000200
#define BUTTON_POWER        0x00000400
#define BUTTON_MAIN         (BUTTON_PLAY|BUTTON_MENU|BUTTON_LEFT|BUTTON_DISPLAY\
                            |BUTTON_RIGHT|BUTTON_SELECT|BUTTON_UP|BUTTON_SLIDE_UP\
                            |BUTTON_DOWN|BUTTON_SLIDE_DOWN|BUTTON_POWER)

#define HAS_BUTTON_HOLD

#define POWEROFF_BUTTON     BUTTON_POWER
#define POWEROFF_COUNT      10

#ifdef HAVE_REMOTE_LCD
void headphones_int(void);
bool remote_button_hold(void);

/* Remote control's buttons */
#define BUTTON_RC_PLAY      0x00010000
#define BUTTON_RC_REW       0x00020000
#define BUTTON_RC_FF        0x00040000
#define BUTTON_RC_DOWN      0x00080000
#define BUTTON_RC_HEART     0x00100000
#define BUTTON_RC_MODE      0x00200000
#define BUTTON_RC_VOL_UP    0x00400000
#define BUTTON_RC_VOL_DOWN  0x00800000
#define BUTTON_REMOTE       (BUTTON_RC_PLAY|BUTTON_RC_REW|BUTTON_RC_FF\
                            |BUTTON_RC_DOWN|BUTTON_RC_HEART|BUTTON_RC_MODE\
                            |BUTTON_RC_VOL_UP|BUTTON_RC_VOL_DOWN)

#define HAS_REMOTE_BUTTON_HOLD
#define RC_POWEROFF_BUTTON  BUTTON_RC_PLAY
#else
#define BUTTON_REMOTE 0
#endif /* HAVE_REMOTE_LCD */

#endif /* _BUTTON_TARGET_H_ */
