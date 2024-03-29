/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id: rolo_restart_firmware.S 27788 2010-08-12 13:38:25Z kugel $
 *
 * Copyright (C) 2008 by Michael Sevakis
 *
 * RoLo firmware restart code for IMX31
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
#include "config.h"
#include "cpu.h"

/****************************************************************************
 * void rolo_restart_firmware(const unsigned char* source, unsigned char* dest,
 *                            int length) NORETURN_ATTR;
 */
    .section    .text, "ax", %progbits
    .align      2
    .global     rolo_restart_firmware
rolo_restart_firmware:
    adr     r4, restart_copy_start
    adr     r5, restart_copy_end
    ldr     r6, =IRAM_BASE_ADDR
    mov     r7, r6

    @ Copy stub to IRAM  
1:
    ldr     r8, [r4], #4
    str     r8, [r7], #4
    cmp     r5, r4
    bhi     1b

    @ Branch to stub
    bx      r6

restart_copy_start:
    @ Trivial copy of firmware to final location
    mov     r4, r1
1:
    subs    r2, r2, #1
    ldrb    r7, [r0], #1
    strb    r7, [r4], #1
    bge     1b

    @ Clean and invalidate all caches
    mov     r0, #0
    mcr     p15, 0, r0, c7, c14, 0
    mcr     p15, 0, r0, c7, c5, 0
    mcr     p15, 0, r0, c7, c10, 4
    mcr     p15, 0, r0, c7, c5, 4
    
    @ Branch to destination (should be address 0x00000000)
    bx      r1
restart_copy_end:
    .size   rolo_restart,.-rolo_restart
