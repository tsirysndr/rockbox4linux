#             __________               __   ___.
#   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
#   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
#   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
#   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
#                     \/            \/     \/    \/            \/
# $Id: reversi.make 20205 2009-03-04 23:41:58Z amiconn $
#

REVERSISRCDIR := $(APPSDIR)/plugins/reversi
REVERSIBUILDDIR := $(BUILDDIR)/apps/plugins/reversi

ROCKS += $(REVERSIBUILDDIR)/reversi.rock

REVERSI_SRC := $(call preprocess, $(REVERSISRCDIR)/SOURCES)
REVERSI_OBJ := $(call c2obj, $(REVERSI_SRC))

# add source files to OTHER_SRC to get automatic dependencies
OTHER_SRC += $(REVERSI_SRC)

$(REVERSIBUILDDIR)/reversi.rock: $(REVERSI_OBJ)
