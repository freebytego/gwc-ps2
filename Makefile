TARGET      := gwc.elf
ENGINEDIR	:= ../engine

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
INCDIR      := inc
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := res
SRCEXT      := cpp
VSMEXT		:= vsm
VCLEXT		:= vcl
VCLPPEXT	:= vclpp
DEPEXT      := d
OBJEXT      := o

#Flags, Libraries and Includes
CFLAGS      :=
LIB         := -ltyra -ldebug
LIBDIRS     := -L$(ENGINEDIR)/bin
INC         := -I$(INCDIR) -I$(ENGINEDIR)/inc
INCDEP      := -I$(INCDIR) -I$(ENGINEDIR)/inc

include ../Makefile.base
include $(PS2SDK)/Defs.make

clean-engine:
	cd $(ENGINEDIR) && $(MAKE) cleaner

build-engine:
	cd $(ENGINEDIR) && $(MAKE)

build-release-engine:
	cd $(ENGINEDIR) && $(MAKE) release
