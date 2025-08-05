CC = gcc
STDC = c90

LIBS = -lm
_APP = app

IDIR = include
BUILD_DIR = build
ODIR = $(BUILD_DIR)/obj
BDIR = $(BUILD_DIR)/bin

WARNINGS = \
	-Wpedantic \
	-Wall \
	-Wextra \
	-Wdouble-promotion \
	-Wformat \
	-Winit-self \
	-Wswitch-default \
	-Wswitch-enum \
	-Wuse-after-free \
	-Wmaybe-uninitialized \
	-Walloc-zero \
	-Warray-parameter \
	-Wduplicated-branches \
	-Wduplicated-cond \
	-Wfloat-equal \
	-Wshadow \
	-Wpointer-arith \
	-Wno-pointer-compare \
	-Wundef \
	-Wc90-c99-compat \
	-Wcast-qual \
	-Wcast-align=strict \
	-Wcast-function-type \
	-Wlogical-op \
	-Wno-long-long

CFLAGS = -std=$(STDC) $(WARNINGS)

SRCS := $(wildcard *.c)
BASES := $(basename $(notdir $(SRCS)))
OBJS = $(patsubst %.c,$(ODIR)/%.o,$(BASES))
APPS = $(patsubst %,$(BDIR)/%,$(BASES))

.PHONY: clean run

.SECONDARY:

all: $(APPS)

$(ODIR)/%.o: %.c | $(ODIR)
	@$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/%: $(ODIR)/%.o | $(BDIR)
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run: $(BDIR)/$(NAME)
	@$(BDIR)/$(NAME) $(ARGS)

$(ODIR):
	@if not exist "$(ODIR)" mkdir "$(ODIR)"

$(BDIR):
	@if not exist "$(BDIR)" mkdir "$(BDIR)"

clean:
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
