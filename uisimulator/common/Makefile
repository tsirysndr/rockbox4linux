############################################################################
#             __________               __   ___.                  
#   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___  
#   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /  
#   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <   
#   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
#                     \/            \/     \/    \/            \/ 
# $Id: Makefile 27372 2010-07-10 13:49:49Z kugel $
#
# Copyright (C) 2002 by Daniel Stenberg <daniel@haxx.se>
#
# All files in this archive are subject to the GNU General Public License.
# See the file COPYING in the source tree root for full license agreement.
#
# This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
# KIND, either express or implied.
#
############################################################################

DEPFILE = $(OBJDIR)/dep-commonsim

RM = rm -f
DEBUG = -g

# Use this for simulator-only files
INCLUDES = -I. -I$(OBJDIR) $(TARGET_INC) -I$(FIRMDIR)/export -I$(APPSDIR)	\
-I$(ROOTDIR)/uisimulator/sdl -I$(BUILDDIR)

# This sets up 'SRC' based on the files mentioned in SOURCES
include $(TOOLSDIR)/makesrc.inc

OBJS := $(SRC:%.c=$(OBJDIR)/%.o)

DEFINES := -DHAVE_CONFIG_H -DGETTIMEOFDAY_TWO_ARGS -DSIMULATOR \
$(TARGET) -DMEM=${MEMORYSIZE} $(EXTRA_DEFINES)

SOURCES = $(SRC)

DIRS = .

CFLAGS = $(DEBUG) $(DEFINES) $(INCLUDES) $(GCCOPTS)

OUTFILE = $(BUILDDIR)/libcomsim.a

all: $(OUTFILE)

include $(TOOLSDIR)/make.inc

clean:
	$(call PRINTS,cleaning commonsim)$(RM) $(OBJS) *~ core $(DEPFILE) $(OUTFILE)

$(OUTFILE): $(OBJS)
	$(call PRINTS,AR+RANLIB $(@F))$(AR) ruv $@ $(OBJS) >/dev/null 2>&1
	$(SILENT)$(RANLIB) $@

-include $(DEPFILE)
