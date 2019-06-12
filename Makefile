SRCDIR := src
BUILDDIR := build
BINDIR := bin

PROG   := survivors
TARGET := $(PROG)
CC     := $(CROSS_COMPILE)g++ -std=c++11
INCL   :=
CFLAGS := -g -O2 -Wall -Wmissing-declarations -Weffc++ \
		-pedantic -pedantic-errors -Wextra -Wcast-align \
		-Wcast-qual -Wconversion -Wsign-conversion \
		-Wdisabled-optimization \
		-Werror -Wfloat-equal -Wformat=2 \
		-Wformat-nonliteral -Wformat-security \
		-Wformat-y2k \
		-Wimport -Winit-self -Winline \
		-Winvalid-pch \
		-Wlong-long \
		-Wmissing-field-initializers -Wmissing-format-attribute \
		-Wmissing-include-dirs -Wmissing-noreturn \
		-Wpacked -Wpointer-arith \
		-Wredundant-decls \
		-Wshadow -Wstack-protector \
		-Wstrict-aliasing=2 -Wswitch-default \
		-Wswitch-enum \
		-Wunreachable-code -Wunused \
		-Wunused-parameter \
		-Wvariadic-macros \
		-Wwrite-strings -Wno-long-long
LDFLAGS:=-I$(SRCDIR)/game -I$(SRCDIR)/survivor-search -I$(SRCDIR)/ncurses -I$(SRCDIR)/survivor-search -I/home/ghislain/home_conf/.self/include/ -L/home/ghislain/home_conf/.self/lib/
CCDYNAMICFLAGS := ${CFLAGS} ${LDFLAGS} -lncursesw -llua -ldl

SRC := $(shell find $(SRCDIR)/game $(SRCDIR)/survivor-search $(SRCDIR)/ncurses -type f -name '*.cpp')
OBJ := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRC))
DEP := $(patsubst %.o,%.deps,$(OBJ))

all: game

game: $(PROG)

-include $(DEP)

%.deps: %.cpp
	$(CC) -MM $< >$@

$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) -c -MMD $(patsubst $(BUILDDIR)/%.o,%.cpp,$@) $(CCDYNAMICFLAGS) -o $@

clean:
	rm -rf $(BUILDDIR) $(LIBDIR)

$(PROG): $(OBJ)
	mkdir -p $(BINDIR)
	$(CC) -o $(BINDIR)/$@ $^ $(CCDYNAMICFLAGS)
	cp -r config/ data/ scripts/ $(BINDIR)
