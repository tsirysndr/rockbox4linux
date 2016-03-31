#             __________               __   ___.
#   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
#   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
#   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
#   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
#                     \/            \/     \/    \/            \/
# $Id: fractals.make 24310 2010-01-21 13:18:27Z teru $
#

FRACTALSSRCDIR := $(APPSDIR)/plugins/fractals
FRACTALSBUILDDIR := $(BUILDDIR)/apps/plugins/fractals

ROCKS += $(FRACTALSBUILDDIR)/fractals.rock

FRACTALS_SRC := $(call preprocess, $(FRACTALSSRCDIR)/SOURCES)
FRACTALS_OBJ := $(call c2obj, $(FRACTALS_SRC))

# add source files to OTHER_SRC to get automatic dependencies
OTHER_SRC += $(FRACTALS_SRC)

$(FRACTALSBUILDDIR)/fractals.rock: $(FRACTALS_OBJ)
