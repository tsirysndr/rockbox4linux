/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id: font-player.c 28725 2010-12-02 21:31:38Z kugel $
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

#include "font-player.h"
#include "hwcompat.h"

static unsigned char font_player_newlcd[256][7] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 00 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 01 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 02 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 03 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 04 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 05 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 06 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 07 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 08 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 09 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 0a */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 0b */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 0c */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 0d */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 0e */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 0f */
    { 0x00, 0x10, 0x1c, 0x1f, 0x1c, 0x10, 0x00 }, /* 10 */
    { 0x00, 0x01, 0x07, 0x1f, 0x07, 0x01, 0x00 }, /* 11 */
    { 0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00 }, /* 12 */
    { 0x0a, 0x0a, 0x0a, 0x0a, 0x00, 0x00, 0x0a }, /* 13 */
    { 0x0f, 0x1d, 0x1d, 0x0d, 0x05, 0x05, 0x05 }, /* 14 */
    { 0x07, 0x08, 0x0e, 0x11, 0x0e, 0x02, 0x1c }, /* 15 */
    { 0x00, 0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00 }, /* 16 */
    { 0x01, 0x01, 0x05, 0x09, 0x1f, 0x08, 0x04 }, /* 17 */
    { 0x04, 0x0e, 0x15, 0x04, 0x04, 0x04, 0x04 }, /* 18 */
    { 0x04, 0x04, 0x04, 0x04, 0x15, 0x0e, 0x04 }, /* 19 */
    { 0x11, 0x19, 0x1d, 0x1f, 0x1d, 0x19, 0x11 }, /* 1a */
    { 0x11, 0x13, 0x17, 0x1f, 0x17, 0x13, 0x11 }, /* 1b */
    { 0x10, 0x14, 0x12, 0x1f, 0x12, 0x14, 0x10 }, /* 1c */
    { 0x01, 0x05, 0x09, 0x1f, 0x09, 0x05, 0x01 }, /* 1d */
    { 0x00, 0x1f, 0x0e, 0x0e, 0x04, 0x04, 0x00 }, /* 1e */
    { 0x00, 0x04, 0x04, 0x0e, 0x0e, 0x1f, 0x00 }, /* 1f */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 20 */
    { 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x04 }, /* 21 */
    { 0x0a, 0x0a, 0x0a, 0x00, 0x00, 0x00, 0x00 }, /* 22 */
    { 0x0a, 0x0a, 0x1f, 0x0a, 0x1f, 0x0a, 0x0a }, /* 23 */
    { 0x04, 0x0f, 0x14, 0x0e, 0x05, 0x1e, 0x04 }, /* 24 */
    { 0x18, 0x19, 0x02, 0x04, 0x08, 0x13, 0x03 }, /* 25 */
    { 0x0c, 0x12, 0x14, 0x08, 0x15, 0x12, 0x0d }, /* 26 */
    { 0x0c, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00 }, /* 27 */
    { 0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02 }, /* 28 */
    { 0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08 }, /* 29 */
    { 0x00, 0x04, 0x15, 0x0e, 0x15, 0x04, 0x00 }, /* 2a */
    { 0x00, 0x04, 0x04, 0x1f, 0x04, 0x04, 0x00 }, /* 2b */
    { 0x00, 0x00, 0x00, 0x00, 0x0c, 0x04, 0x08 }, /* 2c */
    { 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00 }, /* 2d */
    { 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00 }, /* 2e */
    { 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00 }, /* 2f */
    { 0x0e, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0e }, /* 30 */
    { 0x04, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x0e }, /* 31 */
    { 0x0e, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1f }, /* 32 */
    { 0x1f, 0x02, 0x04, 0x02, 0x01, 0x11, 0x0e }, /* 33 */
    { 0x02, 0x06, 0x0a, 0x12, 0x1f, 0x02, 0x02 }, /* 34 */
    { 0x1f, 0x10, 0x1e, 0x01, 0x01, 0x11, 0x0e }, /* 35 */
    { 0x06, 0x08, 0x10, 0x1e, 0x11, 0x11, 0x0e }, /* 36 */
    { 0x1f, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04 }, /* 37 */
    { 0x0e, 0x11, 0x11, 0x0e, 0x11, 0x11, 0x0e }, /* 38 */
    { 0x0e, 0x11, 0x11, 0x0f, 0x01, 0x02, 0x0c }, /* 39 */
    { 0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00 }, /* 3a */
    { 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x04, 0x08 }, /* 3b */
    { 0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02 }, /* 3c */
    { 0x00, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x00 }, /* 3d */
    { 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08 }, /* 3e */
    { 0x0e, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04 }, /* 3f */
    { 0x0e, 0x11, 0x01, 0x0d, 0x15, 0x15, 0x0e }, /* 40 */
    { 0x0e, 0x11, 0x11, 0x11, 0x1f, 0x11, 0x11 }, /* 41 */
    { 0x1e, 0x11, 0x11, 0x1e, 0x11, 0x11, 0x1e }, /* 42 */
    { 0x0e, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0e }, /* 43 */
    { 0x1c, 0x12, 0x11, 0x11, 0x11, 0x12, 0x1c }, /* 44 */
    { 0x1f, 0x10, 0x10, 0x1e, 0x10, 0x10, 0x1f }, /* 45 */
    { 0x1f, 0x10, 0x10, 0x1e, 0x10, 0x10, 0x10 }, /* 46 */
    { 0x0e, 0x11, 0x10, 0x17, 0x11, 0x11, 0x0f }, /* 47 */
    { 0x11, 0x11, 0x11, 0x1f, 0x11, 0x11, 0x11 }, /* 48 */
    { 0x0e, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e }, /* 49 */
    { 0x0f, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0c }, /* 4a */
    { 0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11 }, /* 4b */
    { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1f }, /* 4c */
    { 0x11, 0x1b, 0x15, 0x15, 0x11, 0x11, 0x11 }, /* 4d */
    { 0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11 }, /* 4e */
    { 0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e }, /* 4f */
    { 0x1e, 0x11, 0x11, 0x1e, 0x10, 0x10, 0x10 }, /* 50 */
    { 0x0e, 0x11, 0x11, 0x11, 0x11, 0x12, 0x0d }, /* 51 */
    { 0x1e, 0x11, 0x11, 0x1e, 0x14, 0x12, 0x11 }, /* 52 */
    { 0x0e, 0x11, 0x10, 0x0e, 0x01, 0x11, 0x0e }, /* 53 */
    { 0x1f, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 }, /* 54 */
    { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e }, /* 55 */
    { 0x11, 0x11, 0x11, 0x11, 0x11, 0x0a, 0x04 }, /* 56 */
    { 0x11, 0x11, 0x11, 0x15, 0x15, 0x15, 0x0a }, /* 57 */
    { 0x11, 0x11, 0x0a, 0x04, 0x0a, 0x11, 0x11 }, /* 58 */
    { 0x11, 0x11, 0x0a, 0x04, 0x04, 0x04, 0x04 }, /* 59 */
    { 0x1f, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1f }, /* 5a */
    { 0x0e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0e }, /* 5b */
    { 0x11, 0x0a, 0x1f, 0x04, 0x1f, 0x04, 0x04 }, /* 5c */
    { 0x0e, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0e }, /* 5d */
    { 0x04, 0x0a, 0x11, 0x00, 0x00, 0x00, 0x00 }, /* 5e */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f }, /* 5f */
    { 0x08, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00 }, /* 60 */
    { 0x00, 0x00, 0x0e, 0x01, 0x0f, 0x11, 0x0f }, /* 61 */
    { 0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x1e }, /* 62 */
    { 0x00, 0x00, 0x0e, 0x10, 0x10, 0x11, 0x0e }, /* 63 */
    { 0x01, 0x01, 0x0d, 0x13, 0x11, 0x11, 0x0f }, /* 64 */
    { 0x00, 0x00, 0x0e, 0x11, 0x1f, 0x10, 0x0e }, /* 65 */
    { 0x06, 0x09, 0x08, 0x1c, 0x08, 0x08, 0x08 }, /* 66 */
    { 0x00, 0x0f, 0x11, 0x11, 0x0f, 0x01, 0x0e }, /* 67 */
    { 0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x11 }, /* 68 */
    { 0x04, 0x00, 0x0c, 0x04, 0x04, 0x04, 0x0e }, /* 69 */
    { 0x02, 0x00, 0x06, 0x02, 0x02, 0x12, 0x0c }, /* 6a */
    { 0x10, 0x10, 0x12, 0x14, 0x18, 0x14, 0x12 }, /* 6b */
    { 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e }, /* 6c */
    { 0x00, 0x00, 0x1a, 0x15, 0x15, 0x11, 0x11 }, /* 6d */
    { 0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11 }, /* 6e */
    { 0x00, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x0e }, /* 6f */
    { 0x00, 0x00, 0x1e, 0x11, 0x1e, 0x10, 0x10 }, /* 70 */
    { 0x00, 0x00, 0x0d, 0x13, 0x0f, 0x01, 0x01 }, /* 71 */
    { 0x00, 0x00, 0x16, 0x19, 0x10, 0x10, 0x10 }, /* 72 */
    { 0x00, 0x00, 0x0e, 0x10, 0x0e, 0x01, 0x1e }, /* 73 */
    { 0x08, 0x08, 0x1c, 0x08, 0x08, 0x09, 0x06 }, /* 74 */
    { 0x00, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0d }, /* 75 */
    { 0x00, 0x00, 0x11, 0x11, 0x11, 0x0a, 0x04 }, /* 76 */
    { 0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0a }, /* 77 */
    { 0x00, 0x00, 0x11, 0x0a, 0x04, 0x0a, 0x11 }, /* 78 */
    { 0x00, 0x00, 0x11, 0x11, 0x0f, 0x01, 0x1e }, /* 79 */
    { 0x00, 0x00, 0x1f, 0x02, 0x04, 0x08, 0x1f }, /* 7a */
    { 0x02, 0x04, 0x04, 0x08, 0x04, 0x04, 0x02 }, /* 7b */
    { 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 }, /* 7c */
    { 0x08, 0x04, 0x04, 0x02, 0x04, 0x04, 0x08 }, /* 7d */
    { 0x00, 0x04, 0x02, 0x1f, 0x02, 0x04, 0x00 }, /* 7e */
    { 0x00, 0x04, 0x08, 0x1f, 0x08, 0x04, 0x00 }, /* 7f */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f }, /* 80 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f }, /* 81 */
    { 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f }, /* 82 */
    { 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f }, /* 83 */
    { 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f }, /* 84 */
    { 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f }, /* 85 */
    { 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f }, /* 86 */
    { 0x00, 0x0a, 0x04, 0x1f, 0x04, 0x0a, 0x00 }, /* 87 */
    { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 }, /* 88 */
    { 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19 }, /* 89 */
    { 0x1d, 0x1d, 0x1d, 0x1d, 0x1d, 0x1d, 0x1d }, /* 8a */
    { 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08 }, /* 8b */
    { 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c }, /* 8c */
    { 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e }, /* 8d */
    { 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f }, /* 8e */
    { 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00 }, /* 8f */
    { 0x00, 0x0e, 0x1f, 0x1f, 0x1f, 0x0e, 0x00 }, /* 90 */
    { 0x1f, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f }, /* 91 */
    { 0x1f, 0x1b, 0x13, 0x1b, 0x1b, 0x11, 0x1f }, /* 92 */
    { 0x1f, 0x11, 0x1d, 0x1b, 0x17, 0x11, 0x1f }, /* 93 */
    { 0x00, 0x00, 0x07, 0x04, 0x04, 0x14, 0x08 }, /* 94 */
    { 0x04, 0x04, 0x1f, 0x04, 0x04, 0x00, 0x1f }, /* 95 */
    { 0x00, 0x11, 0x0a, 0x04, 0x0a, 0x11, 0x00 }, /* 96 */
    { 0x00, 0x04, 0x00, 0x1f, 0x00, 0x04, 0x00 }, /* 97 */
    { 0x1f, 0x00, 0x11, 0x0a, 0x04, 0x0a, 0x11 }, /* 98 */
    { 0x1c, 0x04, 0x1c, 0x10, 0x1c, 0x00, 0x00 }, /* 99 */
    { 0x1c, 0x04, 0x1c, 0x04, 0x1c, 0x00, 0x00 }, /* 9a */
    { 0x11, 0x12, 0x17, 0x09, 0x17, 0x04, 0x07 }, /* 9b */
    { 0x11, 0x12, 0x14, 0x09, 0x13, 0x07, 0x01 }, /* 9c */
    { 0x18, 0x09, 0x1a, 0x0d, 0x1b, 0x17, 0x01 }, /* 9d */
    { 0x00, 0x05, 0x0a, 0x14, 0x0a, 0x05, 0x00 }, /* 9e */
    { 0x00, 0x14, 0x0a, 0x05, 0x0a, 0x14, 0x00 }, /* 9f */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* a0 */
    { 0x00, 0x00, 0x00, 0x00, 0x1c, 0x14, 0x1c }, /* a1 */
    { 0x07, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00 }, /* a2 */
    { 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x1c }, /* a3 */
    { 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x04 }, /* a4 */
    { 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00 }, /* a5 */
    { 0x00, 0x1f, 0x01, 0x1f, 0x01, 0x02, 0x04 }, /* a6 */
    { 0x00, 0x00, 0x1f, 0x01, 0x06, 0x04, 0x08 }, /* a7 */
    { 0x00, 0x00, 0x02, 0x04, 0x0c, 0x14, 0x04 }, /* a8 */
    { 0x00, 0x00, 0x04, 0x1f, 0x11, 0x01, 0x06 }, /* a9 */
    { 0x00, 0x00, 0x00, 0x1f, 0x04, 0x04, 0x1f }, /* aa */
    { 0x00, 0x00, 0x02, 0x1f, 0x06, 0x0a, 0x12 }, /* ab */
    { 0x00, 0x00, 0x08, 0x1f, 0x09, 0x0a, 0x08 }, /* ac */
    { 0x00, 0x00, 0x00, 0x0e, 0x02, 0x02, 0x1f }, /* ad */
    { 0x00, 0x00, 0x1e, 0x02, 0x1e, 0x02, 0x1e }, /* ae */
    { 0x00, 0x00, 0x00, 0x15, 0x15, 0x01, 0x06 }, /* af */
    { 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00 }, /* b0 */
    { 0x1f, 0x01, 0x05, 0x06, 0x04, 0x04, 0x08 }, /* b1 */
    { 0x01, 0x02, 0x04, 0x0c, 0x14, 0x04, 0x04 }, /* b2 */
    { 0x04, 0x1f, 0x11, 0x11, 0x01, 0x02, 0x04 }, /* b3 */
    { 0x00, 0x1f, 0x04, 0x04, 0x04, 0x04, 0x1f }, /* b4 */
    { 0x02, 0x1f, 0x02, 0x06, 0x0a, 0x12, 0x02 }, /* b5 */
    { 0x08, 0x1f, 0x09, 0x09, 0x09, 0x09, 0x12 }, /* b6 */
    { 0x04, 0x1f, 0x04, 0x1f, 0x04, 0x04, 0x04 }, /* b7 */
    { 0x00, 0x0f, 0x09, 0x11, 0x01, 0x02, 0x0c }, /* b8 */
    { 0x08, 0x0f, 0x12, 0x02, 0x02, 0x02, 0x04 }, /* b9 */
    { 0x00, 0x1f, 0x01, 0x01, 0x01, 0x01, 0x1f }, /* ba */
    { 0x0a, 0x1f, 0x0a, 0x02, 0x02, 0x02, 0x04 }, /* bb */
    { 0x00, 0x18, 0x00, 0x18, 0x01, 0x02, 0x1c }, /* bc */
    { 0x00, 0x1f, 0x01, 0x02, 0x04, 0x0a, 0x11 }, /* bd */
    { 0x08, 0x1f, 0x09, 0x0a, 0x08, 0x08, 0x07 }, /* be */
    { 0x00, 0x11, 0x11, 0x09, 0x01, 0x02, 0x0c }, /* bf */
    { 0x00, 0x0f, 0x09, 0x15, 0x03, 0x02, 0x0c }, /* c0 */
    { 0x02, 0x1c, 0x04, 0x1f, 0x04, 0x04, 0x08 }, /* c1 */
    { 0x00, 0x15, 0x15, 0x15, 0x01, 0x02, 0x04 }, /* c2 */
    { 0x0e, 0x00, 0x1f, 0x04, 0x04, 0x04, 0x08 }, /* c3 */
    { 0x08, 0x08, 0x08, 0x0c, 0x0a, 0x08, 0x08 }, /* c4 */
    { 0x04, 0x04, 0x1f, 0x04, 0x04, 0x08, 0x10 }, /* c5 */
    { 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x1f }, /* c6 */
    { 0x00, 0x1f, 0x01, 0x0a, 0x04, 0x0a, 0x10 }, /* c7 */
    { 0x04, 0x1f, 0x02, 0x04, 0x0e, 0x15, 0x04 }, /* c8 */
    { 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x08 }, /* c9 */
    { 0x00, 0x04, 0x02, 0x11, 0x11, 0x11, 0x11 }, /* ca */
    { 0x10, 0x10, 0x1f, 0x10, 0x10, 0x10, 0x0f }, /* cb */
    { 0x00, 0x1f, 0x01, 0x01, 0x01, 0x02, 0x0c }, /* cc */
    { 0x00, 0x08, 0x14, 0x02, 0x01, 0x01, 0x00 }, /* cd */
    { 0x04, 0x1f, 0x04, 0x04, 0x15, 0x15, 0x04 }, /* ce */
    { 0x00, 0x1f, 0x01, 0x01, 0x0a, 0x04, 0x02 }, /* cf */
    { 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x01 }, /* d0 */
    { 0x00, 0x04, 0x08, 0x10, 0x11, 0x1f, 0x01 }, /* d1 */
    { 0x00, 0x01, 0x01, 0x0a, 0x04, 0x0a, 0x10 }, /* d2 */
    { 0x00, 0x1f, 0x08, 0x1f, 0x08, 0x08, 0x07 }, /* d3 */
    { 0x08, 0x08, 0x1f, 0x09, 0x0a, 0x08, 0x08 }, /* d4 */
    { 0x00, 0x0e, 0x02, 0x02, 0x02, 0x02, 0x1f }, /* d5 */
    { 0x00, 0x1f, 0x01, 0x1f, 0x01, 0x01, 0x1f }, /* d6 */
    { 0x0e, 0x00, 0x1f, 0x01, 0x01, 0x02, 0x04 }, /* d7 */
    { 0x12, 0x12, 0x12, 0x12, 0x12, 0x04, 0x08 }, /* d8 */
    { 0x00, 0x04, 0x14, 0x14, 0x15, 0x15, 0x16 }, /* d9 */
    { 0x00, 0x10, 0x10, 0x11, 0x12, 0x14, 0x18 }, /* da */
    { 0x1f, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f }, /* db */
    { 0x00, 0x1f, 0x11, 0x11, 0x01, 0x02, 0x04 }, /* dc */
    { 0x00, 0x18, 0x00, 0x01, 0x01, 0x02, 0x1c }, /* dd */
    { 0x04, 0x12, 0x08, 0x00, 0x00, 0x00, 0x00 }, /* de */
    { 0x1c, 0x14, 0x1c, 0x00, 0x00, 0x00, 0x00 }, /* df */
    { 0x00, 0x00, 0x09, 0x15, 0x12, 0x12, 0x0d }, /* e0 */
    { 0x00, 0x0e, 0x11, 0x1e, 0x11, 0x1e, 0x10 }, /* e1 */
    { 0x00, 0x11, 0x0a, 0x0a, 0x04, 0x04, 0x08 }, /* e2 */
    { 0x00, 0x00, 0x1f, 0x0a, 0x0a, 0x0a, 0x13 }, /* e3 */
    { 0x1f, 0x10, 0x08, 0x04, 0x08, 0x10, 0x1f }, /* e4 */
    { 0x00, 0x00, 0x0f, 0x14, 0x12, 0x11, 0x0e }, /* e5 */
    { 0x00, 0x09, 0x09, 0x09, 0x0f, 0x08, 0x10 }, /* e6 */
    { 0x00, 0x00, 0x1f, 0x04, 0x04, 0x04, 0x03 }, /* e7 */
    { 0x1f, 0x04, 0x0e, 0x15, 0x0e, 0x04, 0x1f }, /* e8 */
    { 0x00, 0x0e, 0x11, 0x1f, 0x11, 0x11, 0x0e }, /* e9 */
    { 0x00, 0x00, 0x0e, 0x11, 0x11, 0x0a, 0x1b }, /* ea */
    { 0x0f, 0x10, 0x0e, 0x11, 0x11, 0x11, 0x0e }, /* eb */
    { 0x00, 0x00, 0x00, 0x00, 0x0b, 0x15, 0x1a }, /* ec */
    { 0x02, 0x04, 0x0e, 0x15, 0x0e, 0x04, 0x08 }, /* ed */
    { 0x00, 0x0e, 0x10, 0x0e, 0x10, 0x0e, 0x00 }, /* ee */
    { 0x06, 0x09, 0x11, 0x1e, 0x10, 0x10, 0x10 }, /* ef */
    { 0x00, 0x00, 0x08, 0x15, 0x02, 0x00, 0x00 }, /* f0 */
    { 0x00, 0x08, 0x15, 0x0a, 0x15, 0x02, 0x00 }, /* f1 */
    { 0x08, 0x0f, 0x12, 0x0f, 0x0a, 0x1f, 0x02 }, /* f2 */
    { 0x0f, 0x09, 0x0f, 0x09, 0x0f, 0x09, 0x11 }, /* f3 */
    { 0x04, 0x15, 0x15, 0x04, 0x04, 0x0a, 0x11 }, /* f4 */
    { 0x04, 0x04, 0x1d, 0x06, 0x0e, 0x15, 0x04 }, /* f5 */
    { 0x04, 0x04, 0x1f, 0x04, 0x0e, 0x15, 0x04 }, /* f6 */
    { 0x04, 0x0a, 0x11, 0x0e, 0x04, 0x0e, 0x1f }, /* f7 */
    { 0x04, 0x04, 0x0e, 0x04, 0x04, 0x04, 0x1f }, /* f8 */
    { 0x1f, 0x11, 0x11, 0x1f, 0x11, 0x11, 0x1f }, /* f9 */
    { 0x00, 0x01, 0x1e, 0x04, 0x1f, 0x04, 0x04 }, /* fa */
    { 0x00, 0x00, 0x1f, 0x08, 0x0f, 0x09, 0x11 }, /* fb */
    { 0x00, 0x00, 0x1f, 0x15, 0x1f, 0x11, 0x11 }, /* fc */
    { 0x0a, 0x15, 0x0a, 0x15, 0x0a, 0x15, 0x0a }, /* fd */
    { 0x15, 0x0a, 0x15, 0x0a, 0x15, 0x0a, 0x15 }, /* fe */
    { 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f }, /* ff */
};
static unsigned char font_player_oldlcd[256][7] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 00 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 01 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 02 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 03 */
    { 0x0e, 0x11, 0x17, 0x15, 0x17, 0x10, 0x0e }, /* 04 */
    { 0x06, 0x09, 0x08, 0x1e, 0x08, 0x08, 0x1f }, /* 05 */
    { 0x04, 0x0f, 0x14, 0x0e, 0x05, 0x1e, 0x04 }, /* 06 */
    { 0x11, 0x0a, 0x1f, 0x04, 0x1f, 0x04, 0x04 }, /* 07 */
    { 0x08, 0x04, 0x0e, 0x11, 0x1f, 0x10, 0x0e }, /* 08 */
    { 0x02, 0x04, 0x0e, 0x11, 0x1f, 0x10, 0x0e }, /* 09 */
    { 0x08, 0x04, 0x00, 0x11, 0x11, 0x13, 0x0d }, /* 0a */
    { 0x08, 0x04, 0x00, 0x0c, 0x04, 0x04, 0x0e }, /* 0b */
    { 0x08, 0x04, 0x00, 0x0e, 0x11, 0x11, 0x0e }, /* 0c */
    { 0x0f, 0x10, 0x10, 0x10, 0x0f, 0x02, 0x0e }, /* 0d */
    { 0x10, 0x10, 0x17, 0x14, 0x1e, 0x04, 0x04 }, /* 0e */
    { 0x01, 0x0e, 0x13, 0x15, 0x19, 0x0e, 0x10 }, /* 0f */
    { 0x00, 0x02, 0x0e, 0x15, 0x15, 0x0e, 0x08 }, /* 10 */
    { 0x1c, 0x10, 0x17, 0x1d, 0x07, 0x06, 0x05 }, /* 11 */
    { 0x04, 0x0a, 0x04, 0x0e, 0x11, 0x1f, 0x11 }, /* 12 */
    { 0x04, 0x0a, 0x04, 0x01, 0x0f, 0x11, 0x0f }, /* 13 */
    { 0x00, 0x04, 0x04, 0x0a, 0x0a, 0x11, 0x1f }, /* 14 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f }, /* 15 */
    { 0x0e, 0x04, 0x1f, 0x15, 0x1f, 0x04, 0x0e }, /* 16 */
    { 0x1f, 0x11, 0x11, 0x10, 0x10, 0x10, 0x10 }, /* 17 */
    { 0x04, 0x04, 0x0a, 0x0a, 0x11, 0x11, 0x11 }, /* 18 */
    { 0x0e, 0x11, 0x11, 0x11, 0x0a, 0x0a, 0x1b }, /* 19 */
    { 0x1f, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a }, /* 1a */
    { 0x15, 0x15, 0x15, 0x15, 0x0e, 0x04, 0x04 }, /* 1b */
    { 0x1f, 0x08, 0x04, 0x02, 0x04, 0x08, 0x1f }, /* 1c */
    { 0x0e, 0x11, 0x11, 0x1f, 0x11, 0x11, 0x0e }, /* 1d */
    { 0x1f, 0x11, 0x00, 0x0e, 0x00, 0x11, 0x1f }, /* 1e */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 1f */
    { 0x0f, 0x14, 0x14, 0x1f, 0x14, 0x14, 0x17 }, /* 20 */
    { 0x00, 0x00, 0x1a, 0x05, 0x0f, 0x14, 0x0f }, /* 21 */
    { 0x0c, 0x12, 0x16, 0x11, 0x11, 0x16, 0x10 }, /* 22 */
    { 0x02, 0x04, 0x1f, 0x10, 0x1c, 0x10, 0x1f }, /* 23 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* 24 */
    { 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x04 }, /* 25 */
    { 0x1b, 0x09, 0x12, 0x00, 0x00, 0x00, 0x00 }, /* 26 */
    { 0x0a, 0x0a, 0x1f, 0x0a, 0x1f, 0x0a, 0x0a }, /* 27 */
    { 0x00, 0x11, 0x0e, 0x0a, 0x0e, 0x11, 0x00 }, /* 28 */
    { 0x18, 0x19, 0x02, 0x04, 0x08, 0x13, 0x03 }, /* 29 */
    { 0x08, 0x14, 0x14, 0x09, 0x15, 0x12, 0x0d }, /* 2a */
    { 0x0c, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00 }, /* 2b */
    { 0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02 }, /* 2c */
    { 0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08 }, /* 2d */
    { 0x04, 0x15, 0x0e, 0x04, 0x0e, 0x15, 0x04 }, /* 2e */
    { 0x00, 0x04, 0x04, 0x1f, 0x04, 0x04, 0x00 }, /* 2f */
    { 0x00, 0x00, 0x00, 0x00, 0x0c, 0x04, 0x08 }, /* 30 */
    { 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00 }, /* 31 */
    { 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00 }, /* 32 */
    { 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00 }, /* 33 */
    { 0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e }, /* 34 */
    { 0x04, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x0e }, /* 35 */
    { 0x0e, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1f }, /* 36 */
    { 0x1f, 0x02, 0x04, 0x02, 0x01, 0x11, 0x0e }, /* 37 */
    { 0x02, 0x06, 0x0a, 0x12, 0x1f, 0x02, 0x02 }, /* 38 */
    { 0x1f, 0x10, 0x1e, 0x01, 0x01, 0x11, 0x0e }, /* 39 */
    { 0x06, 0x08, 0x10, 0x1e, 0x11, 0x11, 0x0e }, /* 3a */
    { 0x1f, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04 }, /* 3b */
    { 0x0e, 0x11, 0x11, 0x0e, 0x11, 0x11, 0x0e }, /* 3c */
    { 0x0e, 0x11, 0x11, 0x0f, 0x01, 0x02, 0x0c }, /* 3d */
    { 0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00 }, /* 3e */
    { 0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x04, 0x08 }, /* 3f */
    { 0x03, 0x06, 0x0c, 0x18, 0x0c, 0x06, 0x03 }, /* 40 */
    { 0x00, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x00 }, /* 41 */
    { 0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18 }, /* 42 */
    { 0x0e, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04 }, /* 43 */
    { 0x04, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04 }, /* 44 */
    { 0x04, 0x0a, 0x11, 0x11, 0x1f, 0x11, 0x11 }, /* 45 */
    { 0x1e, 0x11, 0x11, 0x1e, 0x11, 0x11, 0x1e }, /* 46 */
    { 0x0e, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0e }, /* 47 */
    { 0x1c, 0x12, 0x11, 0x11, 0x11, 0x12, 0x1c }, /* 48 */
    { 0x1f, 0x10, 0x10, 0x1e, 0x10, 0x10, 0x1f }, /* 49 */
    { 0x1f, 0x10, 0x10, 0x1e, 0x10, 0x10, 0x10 }, /* 4a */
    { 0x0e, 0x10, 0x10, 0x17, 0x11, 0x11, 0x0e }, /* 4b */
    { 0x11, 0x11, 0x11, 0x1f, 0x11, 0x11, 0x11 }, /* 4c */
    { 0x0e, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e }, /* 4d */
    { 0x0f, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0c }, /* 4e */
    { 0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11 }, /* 4f */
    { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1f }, /* 50 */
    { 0x11, 0x1b, 0x15, 0x11, 0x11, 0x11, 0x11 }, /* 51 */
    { 0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11 }, /* 52 */
    { 0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e }, /* 53 */
    { 0x1e, 0x11, 0x11, 0x1e, 0x10, 0x10, 0x10 }, /* 54 */
    { 0x0e, 0x11, 0x11, 0x11, 0x11, 0x12, 0x0d }, /* 55 */
    { 0x1e, 0x11, 0x11, 0x1e, 0x14, 0x12, 0x11 }, /* 56 */
    { 0x0e, 0x11, 0x10, 0x0e, 0x01, 0x11, 0x0e }, /* 57 */
    { 0x1f, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 }, /* 58 */
    { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e }, /* 59 */
    { 0x11, 0x11, 0x11, 0x11, 0x11, 0x0a, 0x04 }, /* 5a */
    { 0x11, 0x11, 0x11, 0x11, 0x11, 0x15, 0x0a }, /* 5b */
    { 0x11, 0x11, 0x0a, 0x04, 0x0a, 0x11, 0x11 }, /* 5c */
    { 0x11, 0x11, 0x0a, 0x04, 0x04, 0x04, 0x04 }, /* 5d */
    { 0x1f, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1f }, /* 5e */
    { 0x0a, 0x00, 0x04, 0x0a, 0x11, 0x1f, 0x11 }, /* 5f */
    { 0x0a, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x0e }, /* 60 */
    { 0x0d, 0x12, 0x00, 0x19, 0x15, 0x13, 0x11 }, /* 61 */
    { 0x0a, 0x00, 0x11, 0x11, 0x11, 0x11, 0x0e }, /* 62 */
    { 0x0e, 0x10, 0x0e, 0x11, 0x0e, 0x01, 0x0e }, /* 63 */
    { 0x04, 0x00, 0x04, 0x08, 0x10, 0x11, 0x0e }, /* 64 */
    { 0x00, 0x00, 0x0e, 0x01, 0x0f, 0x11, 0x0f }, /* 65 */
    { 0x10, 0x10, 0x1e, 0x11, 0x11, 0x11, 0x1e }, /* 66 */
    { 0x00, 0x00, 0x0f, 0x10, 0x10, 0x10, 0x0f }, /* 67 */
    { 0x01, 0x01, 0x0f, 0x11, 0x11, 0x11, 0x0f }, /* 68 */
    { 0x00, 0x00, 0x0e, 0x11, 0x1f, 0x10, 0x0f }, /* 69 */
    { 0x03, 0x04, 0x0f, 0x04, 0x04, 0x04, 0x04 }, /* 6a */
    { 0x00, 0x00, 0x0f, 0x11, 0x0f, 0x01, 0x0e }, /* 6b */
    { 0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x11 }, /* 6c */
    { 0x04, 0x00, 0x0c, 0x04, 0x04, 0x04, 0x0e }, /* 6d */
    { 0x02, 0x00, 0x06, 0x02, 0x02, 0x12, 0x0c }, /* 6e */
    { 0x08, 0x08, 0x09, 0x0a, 0x0c, 0x0a, 0x09 }, /* 6f */
    { 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e }, /* 70 */
    { 0x00, 0x00, 0x1a, 0x15, 0x15, 0x15, 0x15 }, /* 71 */
    { 0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11 }, /* 72 */
    { 0x00, 0x00, 0x0e, 0x11, 0x11, 0x11, 0x0e }, /* 73 */
    { 0x00, 0x00, 0x1e, 0x11, 0x1e, 0x10, 0x10 }, /* 74 */
    { 0x00, 0x00, 0x0f, 0x11, 0x0f, 0x01, 0x01 }, /* 75 */
    { 0x00, 0x00, 0x0b, 0x0c, 0x08, 0x08, 0x08 }, /* 76 */
    { 0x00, 0x00, 0x0e, 0x10, 0x0e, 0x01, 0x1e }, /* 77 */
    { 0x04, 0x04, 0x0f, 0x04, 0x04, 0x04, 0x03 }, /* 78 */
    { 0x00, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0d }, /* 79 */
    { 0x00, 0x00, 0x11, 0x11, 0x11, 0x0a, 0x04 }, /* 7a */
    { 0x00, 0x00, 0x11, 0x11, 0x11, 0x15, 0x0a }, /* 7b */
    { 0x00, 0x00, 0x11, 0x0a, 0x04, 0x0a, 0x11 }, /* 7c */
    { 0x00, 0x00, 0x11, 0x11, 0x0f, 0x01, 0x1e }, /* 7d */
    { 0x00, 0x00, 0x1f, 0x02, 0x04, 0x08, 0x1f }, /* 7e */
    { 0x0a, 0x00, 0x0e, 0x01, 0x0f, 0x11, 0x0f }, /* 7f */
    { 0x00, 0x0a, 0x00, 0x0e, 0x11, 0x11, 0x0e }, /* 80 */
    { 0x0d, 0x12, 0x00, 0x16, 0x19, 0x11, 0x11 }, /* 81 */
    { 0x00, 0x0a, 0x00, 0x11, 0x11, 0x13, 0x0d }, /* 82 */
    { 0x08, 0x04, 0x0e, 0x01, 0x0f, 0x11, 0x0f }, /* 83 */
    { 0x00, 0x0f, 0x10, 0x10, 0x0f, 0x02, 0x04 }, /* 84 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x00 }, /* 85 */
    { 0x00, 0x00, 0x04, 0x0e, 0x1f, 0x00, 0x00 }, /* 86 */
    { 0x00, 0x00, 0x1f, 0x0e, 0x04, 0x00, 0x00 }, /* 87 */
    { 0x02, 0x06, 0x0e, 0x1e, 0x0e, 0x06, 0x02 }, /* 88 */
    { 0x08, 0x0c, 0x0e, 0x0f, 0x0e, 0x0c, 0x08 }, /* 89 */
    { 0x1c, 0x1f, 0x13, 0x10, 0x10, 0x10, 0x10 }, /* 8a */
    { 0x15, 0x0a, 0x15, 0x0a, 0x15, 0x0a, 0x15 }, /* 8b */
    { 0x08, 0x04, 0x0e, 0x11, 0x1f, 0x11, 0x11 }, /* 8c */
    { 0x02, 0x04, 0x0e, 0x11, 0x1f, 0x11, 0x11 }, /* 8d */
    { 0x04, 0x0a, 0x0e, 0x11, 0x1f, 0x11, 0x11 }, /* 8e */
    { 0x0d, 0x12, 0x0e, 0x11, 0x1f, 0x11, 0x11 }, /* 8f */
    { 0x08, 0x04, 0x1f, 0x10, 0x1e, 0x10, 0x1f }, /* 90 */
    { 0x04, 0x0a, 0x1f, 0x10, 0x1c, 0x10, 0x1f }, /* 91 */
    { 0x0a, 0x00, 0x1f, 0x10, 0x1c, 0x10, 0x1f }, /* 92 */
    { 0x08, 0x04, 0x0e, 0x04, 0x04, 0x04, 0x0e }, /* 93 */
    { 0x02, 0x04, 0x0e, 0x04, 0x04, 0x04, 0x0e }, /* 94 */
    { 0x0c, 0x0a, 0x09, 0x1d, 0x09, 0x0a, 0x0c }, /* 95 */
    { 0x08, 0x04, 0x0e, 0x11, 0x11, 0x11, 0x0e }, /* 96 */
    { 0x02, 0x04, 0x0e, 0x11, 0x11, 0x11, 0x0e }, /* 97 */
    { 0x04, 0x0a, 0x0e, 0x11, 0x11, 0x11, 0x0e }, /* 98 */
    { 0x0d, 0x12, 0x0e, 0x11, 0x11, 0x11, 0x0e }, /* 99 */
    { 0x08, 0x04, 0x11, 0x11, 0x11, 0x11, 0x0e }, /* 9a */
    { 0x02, 0x04, 0x11, 0x11, 0x11, 0x11, 0x0e }, /* 9b */
    { 0x02, 0x04, 0x0e, 0x01, 0x0f, 0x11, 0x0f }, /* 9c */
    { 0x04, 0x0a, 0x0e, 0x01, 0x0f, 0x11, 0x0f }, /* 9d */
    { 0x0d, 0x12, 0x0e, 0x01, 0x0f, 0x11, 0x0f }, /* 9e */
    { 0x04, 0x0a, 0x0e, 0x11, 0x1f, 0x10, 0x0e }, /* 9f */
    { 0x0a, 0x00, 0x0e, 0x11, 0x1f, 0x10, 0x0e }, /* a0 */
    { 0x02, 0x04, 0x00, 0x0c, 0x04, 0x04, 0x0e }, /* a1 */
    { 0x04, 0x0a, 0x00, 0x0c, 0x04, 0x04, 0x0e }, /* a2 */
    { 0x0a, 0x00, 0x00, 0x0c, 0x04, 0x04, 0x0e }, /* a3 */
    { 0x02, 0x04, 0x00, 0x0e, 0x11, 0x11, 0x0e }, /* a4 */
    { 0x04, 0x0a, 0x00, 0x0e, 0x11, 0x11, 0x0e }, /* a5 */
    { 0x0d, 0x12, 0x00, 0x0e, 0x11, 0x11, 0x0e }, /* a6 */
    { 0x02, 0x04, 0x00, 0x11, 0x11, 0x13, 0x0d }, /* a7 */
    { 0x04, 0x04, 0x0f, 0x10, 0x10, 0x0f, 0x04 }, /* a8 */
    { 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03 }, /* a9 */
    { 0x0a, 0x04, 0x0b, 0x0c, 0x08, 0x08, 0x08 }, /* aa */
    { 0x0a, 0x04, 0x0f, 0x10, 0x10, 0x10, 0x0f }, /* ab */
    { 0x0a, 0x04, 0x0e, 0x10, 0x0e, 0x01, 0x1e }, /* ac */
    { 0x0a, 0x04, 0x0e, 0x11, 0x1f, 0x10, 0x0e }, /* ad */
    { 0x04, 0x0a, 0x04, 0x11, 0x11, 0x13, 0x0d }, /* ae */
    { 0x02, 0x04, 0x11, 0x11, 0x0f, 0x01, 0x0e }, /* af */
    { 0x02, 0x0f, 0x02, 0x0e, 0x12, 0x12, 0x0e }, /* b0 */
    { 0x02, 0x04, 0x0f, 0x10, 0x10, 0x10, 0x0f }, /* b1 */
    { 0x0e, 0x11, 0x1f, 0x10, 0x0e, 0x04, 0x06 }, /* b2 */
    { 0x0e, 0x01, 0x0f, 0x11, 0x0f, 0x02, 0x03 }, /* b3 */
    { 0x04, 0x00, 0x1f, 0x02, 0x04, 0x08, 0x1f }, /* b4 */
    { 0x02, 0x04, 0x1f, 0x02, 0x04, 0x08, 0x1f }, /* b5 */
    { 0x02, 0x04, 0x0e, 0x10, 0x0e, 0x01, 0x1e }, /* b6 */
    { 0x02, 0x04, 0x16, 0x19, 0x11, 0x11, 0x11 }, /* b7 */
    { 0x0c, 0x04, 0x06, 0x0c, 0x04, 0x04, 0x0e }, /* b8 */
    { 0x04, 0x0e, 0x1f, 0x1f, 0x1b, 0x04, 0x0e }, /* b9 */
    { 0x0a, 0x04, 0x16, 0x19, 0x11, 0x11, 0x11 }, /* ba */
    { 0x09, 0x09, 0x08, 0x1e, 0x08, 0x08, 0x06 }, /* bb */
    { 0x05, 0x05, 0x0c, 0x14, 0x14, 0x14, 0x0c }, /* bc */
    { 0x0a, 0x04, 0x1f, 0x02, 0x04, 0x08, 0x1f }, /* bd */
    { 0x0f, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* be */
    { 0x0f, 0x10, 0x01, 0x01, 0x01, 0x01, 0x01 }, /* bf */
    { 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x1f }, /* c0 */
    { 0x1f, 0x00, 0x0e, 0x10, 0x17, 0x11, 0x0e }, /* c1 */
    { 0x1f, 0x00, 0x0f, 0x11, 0x0f, 0x01, 0x0e }, /* c2 */
    { 0x0e, 0x10, 0x0e, 0x01, 0x0e, 0x04, 0x0c }, /* c3 */
    { 0x00, 0x0e, 0x10, 0x0e, 0x01, 0x0e, 0x04 }, /* c4 */
    { 0x04, 0x00, 0x0e, 0x04, 0x04, 0x04, 0x0e }, /* c5 */
    { 0x00, 0x00, 0x0c, 0x04, 0x04, 0x04, 0x0e }, /* c6 */
    { 0x05, 0x0a, 0x11, 0x11, 0x11, 0x11, 0x0e }, /* c7 */
    { 0x09, 0x12, 0x0e, 0x11, 0x11, 0x11, 0x0e }, /* c8 */
    { 0x09, 0x12, 0x00, 0x11, 0x11, 0x13, 0x0d }, /* c9 */
    { 0x09, 0x12, 0x00, 0x0e, 0x11, 0x11, 0x0e }, /* ca */
    { 0x01, 0x01, 0x01, 0x01, 0x01, 0x10, 0x0f }, /* cb */
    { 0x10, 0x10, 0x10, 0x10, 0x10, 0x01, 0x1e }, /* cc */
    { 0x00, 0x1b, 0x1f, 0x1f, 0x0e, 0x04, 0x00 }, /* cd */
    { 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x18 }, /* ce */
    { 0x0e, 0x11, 0x04, 0x0a, 0x1b, 0x1f, 0x00 }, /* cf */
    { 0x0a, 0x15, 0x04, 0x07, 0x00, 0x11, 0x0a }, /* d0 */
    { 0x0f, 0x10, 0x00, 0x00, 0x00, 0x00, 0x1f }, /* d1 */
    { 0x01, 0x03, 0x1d, 0x11, 0x1d, 0x03, 0x01 }, /* d2 */
    { 0x0e, 0x11, 0x11, 0x1f, 0x1b, 0x1b, 0x1f }, /* d3 */
    { 0x00, 0x01, 0x02, 0x0a, 0x04, 0x04, 0x00 }, /* d4 */
    { 0x04, 0x0e, 0x1f, 0x00, 0x1f, 0x0e, 0x04 }, /* d5 */
    { 0x02, 0x02, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e }, /* d6 */
    { 0x1b, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1b }, /* d7 */
    { 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b }, /* d8 */
    { 0x04, 0x0f, 0x04, 0x04, 0x04, 0x03, 0x06 }, /* d9 */
    { 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b, 0x1b }, /* da */
    { 0x00, 0x04, 0x0e, 0x1f, 0x0e, 0x04, 0x00 }, /* db */
    { 0x00, 0x00, 0x1f, 0x1b, 0x15, 0x11, 0x1f }, /* dc */
    { 0x0e, 0x0e, 0x04, 0x1f, 0x0e, 0x0e, 0x0a }, /* dd */
    { 0x00, 0x00, 0x00, 0x00, 0x0a, 0x04, 0x0a }, /* de */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f }, /* df */
    { 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f }, /* e0 */
    { 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f }, /* e1 */
    { 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f }, /* e2 */
    { 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f }, /* e3 */
    { 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x04 }, /* e4 */
    { 0x04, 0x09, 0x0a, 0x0a, 0x0a, 0x09, 0x04 }, /* e5 */
    { 0x00, 0x1f, 0x11, 0x11, 0x1f, 0x04, 0x1f }, /* e6 */
    { 0x00, 0x07, 0x03, 0x05, 0x08, 0x10, 0x00 }, /* e7 */
    { 0x00, 0x10, 0x08, 0x05, 0x03, 0x07, 0x00 }, /* e8 */
    { 0x09, 0x06, 0x0e, 0x01, 0x0f, 0x11, 0x0f }, /* e9 */
    { 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* ea */
    { 0x00, 0x00, 0x10, 0x08, 0x04, 0x04, 0x04 }, /* eb */
    { 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f }, /* ec */
    { 0x1f, 0x18, 0x14, 0x12, 0x15, 0x18, 0x1f }, /* ed */
    { 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* ee */
    { 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10 }, /* ef */
    { 0x00, 0x03, 0x07, 0x0c, 0x18, 0x1c, 0x1c }, /* f0 */
    { 0x1c, 0x10, 0x1c, 0x07, 0x1c, 0x04, 0x07 }, /* f1 */
    { 0x00, 0x1e, 0x03, 0x09, 0x19, 0x09, 0x1d }, /* f2 */
    { 0x1e, 0x01, 0x19, 0x05, 0x09, 0x1d, 0x01 }, /* f3 */
    { 0x04, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00 }, /* f4 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0f }, /* f5 */
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1e }, /* f6 */
    { 0x04, 0x04, 0x04, 0x08, 0x10, 0x00, 0x00 }, /* f7 */
    { 0x07, 0x03, 0x05, 0x08, 0x10, 0x10, 0x0f }, /* f8 */
    { 0x04, 0x0e, 0x1f, 0x11, 0x11, 0x15, 0x1f }, /* f9 */
    { 0x1f, 0x03, 0x1a, 0x02, 0x1a, 0x02, 0x1e }, /* fa */
    { 0x00, 0x0e, 0x1f, 0x11, 0x1f, 0x0e, 0x00 }, /* fb */
    { 0x03, 0x05, 0x09, 0x09, 0x0b, 0x1b, 0x18 }, /* fc */
    { 0x1f, 0x03, 0x05, 0x09, 0x15, 0x03, 0x1f }, /* fd */
    { 0x10, 0x10, 0x10, 0x10, 0x10, 0x1c, 0x1c }, /* fe */
    { 0x1c, 0x1c, 0x10, 0x10, 0x10, 0x10, 0x10 }, /* ff */
};

unsigned char (*font_player)[256][7] = &font_player_newlcd;

void font_init(void)
{
    if (is_new_player())
        font_player = &font_player_newlcd;
    else
        font_player = &font_player_oldlcd;
}
