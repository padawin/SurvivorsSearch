SRC_GAME_DIR := src-game
SRC_TOOLS_DIR := src-tools
SRC_COMMON_DIR := src-common
BUILDDIR := build
BINDIR := bin

PROG   := rrpg
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
LDFLAGS:=-Isrc-common -Isrc-game
CCDYNAMICFLAGS := ${CFLAGS} ${LDFLAGS} -I/home/ghislain/home_conf/.self/include -L/home/ghislain/home_conf/.self/lib  -lSDL2 -lSDL2_image -llua -ldl

SRC := $(shell find $(SRC_COMMON_DIR)/ $(SRC_GAME_DIR)/ -type f -name '*.cpp')
OBJ := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRC))
DEP := $(patsubst %.o,%.deps,$(OBJ))

all: game

build-resources:
	./bin/tools/data-compiler tiles resources/src/floor-tiles.dat resources/floor-tiles.dat
	./bin/tools/data-compiler tilesets resources/src/tilesets.dat resources/tilesets.dat
	./bin/tools/data-compiler races resources/src/taxonomy.dat resources/taxonomy.dat
	./bin/tools/data-compiler objects resources/src/objects.dat resources/objects.dat

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

tools:
	@mkdir -p $(BINDIR)/tools
	$(CC) ${CFLAGS} ${CFLAGS} ${LDFLAGS} $(shell find $(SRC_TOOLS_DIR)/dataCompiler/ $(SRC_COMMON_DIR) -name "*.cpp") \
		-o $(BINDIR)/tools/data-compiler
	$(CC) ${CFLAGS} ${CFLAGS} ${LDFLAGS} $(shell find $(SRC_TOOLS_DIR)/dataDecompiler/ $(SRC_COMMON_DIR)/ -name "*.cpp") \
		-o $(BINDIR)/tools/data-decompiler
