/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id: lcd-target.h 23265 2009-10-19 18:14:27Z Domonoky $
 *
 * Copyright (C) 2007 by Greg White
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

extern void lcd_enable(bool state);

/* Config values for LCDCON1 */
/* ENVID = 0, BPPMODE = 16 bpp, PNRMODE = TFT, MMODE = Each Frame, CLKVAL = 8 */
#define LCD_CLKVAL  8
#define LCD_MMODE   0
#define LCD_PNRMODE 3
#define LCD_BPPMODE 12
#define LCD_ENVID   1

/* Config values for LCDCON2 */
/* VCPW = 1, VFPD = 5, VBPD = 7 */
#define LCD_UPPER_MARGIN 7
#define LCD_LOWER_MARGIN 5
#define LCD_VSYNC_LEN    1

/* Config values for LCDCON3 */
/* HFPD = 9, HBPD = 7 */
#define LCD_LEFT_MARGIN  7
#define LCD_RIGHT_MARGIN 9

/* Config values for LCDCON4 */
/* HSPW = 7 */
#define LCD_HSYNC_LEN 7
