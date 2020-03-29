# ------------------------------------------------
# Generic Makefile
# Date : 27/02/2020
# Author : Leger Charlie
# ------------------------------------------------

# Project configuration
TARGET   = app_createPicture

SRCDIR   = src
INCDIR	 = include
OBJDIR   = obj
BINDIR   = bin

# Build configuration
ifeq ($(ARCH), arm)
	CCPREFIX = arm-linux-gnueabihf-
	DEFINE_MACRO = -D'TARGET_ARM'
else
	CCPREFIX =
	DEFINE_MACRO =
endif

# Compilation configuration
CC       = $(CCPREFIX)gcc
CFLAGS   = -std=c11 -Wall -I$(INCDIR) $(DEFINE_MACRO)

# linking flags here
LDFLAGS	 = -lm
LFLAGS   = -Wall -I$(INCDIR) $(LDFLAGS)

# Get all files
SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

# Commands
$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully! ($(CC))"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: mrproper
mrproper: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"