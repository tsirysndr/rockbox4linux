/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id: backlight-target.h 26917 2010-06-18 13:45:24Z ranma $
 *
 * Copyright © 2008 Rafaël Carré
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
#ifndef BACKLIGHT_TARGET_H
#define BACKLIGHT_TARGET_H

#include "stdbool.h"
#include "lcd.h"
#include "backlight.h"

static inline void _backlight_on(void)
{
    lcd_enable(true);
}

static inline void _backlight_off(void)
{
    lcd_enable(false);
}

#define _backlight_panic_on() _backlight_on()

static inline bool _backlight_init(void)
{
    GPIOD_DIR |= (1<<7); /* for button light */
    return true;
}

static inline void _buttonlight_on(void)
{
    GPIOD_PIN(7) = (1<<7);
}

static inline void _buttonlight_off(void)
{
    GPIOD_PIN(7) = 0;
}

#endif
