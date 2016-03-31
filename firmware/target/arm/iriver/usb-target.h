/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id: usb-target.h 29067 2011-01-17 06:50:27Z jethead71 $
 *
 * Copyright (C) 2006 by Barry Wardelll
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

/* Based off x5 version */

#ifndef USB_TARGET_H
#define USB_TARGET_H

#ifdef HAVE_BOOTLOADER_USB_MODE
#define USB_DRIVER_CLOSE
#endif

bool usb_init_device(void);
void usb_pin_init(void); /* Init the GPIO input only */
bool usb_plugged(void); /* Returns instantaneous state - always */

#endif
