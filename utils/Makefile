TOP=$(abspath ..)
include $(TOP)/defs.mak

SUBLIBDIR=$(LIBDIR)

ARCHIVE = libmystutils.a

SOURCES = $(wildcard *.c)

INCLUDES = -I$(INCDIR) -I$(BUILDDIR)/musl/include
INCLUDES += -I$(BUILDDIR)/openenclave/include/openenclave/3rdparty

CFLAGS =
CFLAGS += $(DEFAULT_CFLAGS)
CFLAGS += $(OPTIMIZATION_CFLAGS)
CFLAGS += -nostdinc
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections
CFLAGS += -Wno-conversion
CFLAGS += -Wno-parentheses
CFLAGS += -O3

LDFLAGS = $(DEFAULT_LDFLAGS)

ifdef MYST_ENABLE_GCOV
CFLAGS += $(GCOV_CFLAGS)
endif

include $(TOP)/rules.mak
