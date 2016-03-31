#             __________               __   ___.
#   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
#   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
#   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
#   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
#                     \/            \/     \/    \/            \/
# $Id: sudoku.make 19218 2008-11-25 19:54:23Z zagor $
#

SUDOKUSRCDIR := $(APPSDIR)/plugins/sudoku
SUDOKUBUILDDIR := $(BUILDDIR)/apps/plugins/sudoku

ROCKS += $(SUDOKUBUILDDIR)/sudoku.rock

SUDOKU_SRC := $(call preprocess, $(SUDOKUSRCDIR)/SOURCES)
SUDOKU_OBJ := $(call c2obj, $(SUDOKU_SRC))

# add source files to OTHER_SRC to get automatic dependencies
OTHER_SRC += $(SUDOKU_SRC)

$(SUDOKUBUILDDIR)/sudoku.rock: $(SUDOKU_OBJ)
