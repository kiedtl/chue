#
# chue: a cat(1) for colors
#
# (c) Kiëd Llaentenn
# See the COPYING file for more information
#

include config.mk

VERSION = \"0.1.0\"

BIN     = chue
SRC     = main.c list.c read.c lex.c parse.c display.c result.c \
	  color.c ccommon/src/die.c
OBJ     = $(SRC:.c=.o)

WARNING = -Wall -Wextra -Wold-style-definition \
	  -Wmissing-prototypes -Wfloat-equal -Wstrict-prototypes \
	  -Wredundant-decls -Wendif-labels -Wstrict-aliasing=2 -Woverflow \
	  -Wformat=2 -Wmissing-include-dirs -Wno-trigraphs -Winit-self
INC     = -I. -Iccommon/include/
DEF     =

CFLAGS  = -std=c99 -DVERSION=$(VERSION) -D_DEFAULT_SOURCE \
	  $(WARNING) $(INC)
LDFLAGS = -lm -fuse-ld=$(LD)

all: debug docs

.c.o:
	@printf "    %-8s%s\n" "CC" $@
	$(CMD)$(CC) $(CFLAGS) $(CFLAGS_OPT) -c $< -o $(<:.c=.o)

debug: CFLAGS_OPT  := $(DEBUG_CFLAGS)
debug: LDFLAGS_OPT := $(DEBUG_LDFLAGS)
debug: $(BIN)

release: CFLAGS_OPT  := $(RELEASE_CFLAGS)
release: LDFLAGS_OPT := $(RELEASE_LDFLAGS)
release: $(BIN)

$(BIN): $(OBJ)
	@printf "    %-8s%s\n" "CCLD" $@
	$(CMD)$(CC) -o $@ $^ $(CFLAGS) $(CFLAGS_OPT) $(LDFLAGS) $(LDFLAGS_OPT)

docs: man/$(BIN).1
man/$(BIN).1: man/$(BIN).1.scd
	@printf "    %-8s%s\n" "SCDOC" $@
	$(CMD)scdoc < $^ > $@

clean:
	$(CMD)rm -f $(BIN) $(OBJ) man/$(BIN).1

install: docs $(BIN)
	@printf "    %-8s%s\n" "INSTALL" $@
	$(CMD)install -Dm755 $(BIN) $(DESTDIR)/$(PREFIX)/bin/$(BIN)
	@printf "    %-8s%s\n" "INSTALL" $@
	$(CMD)install -Dm644 man/$(BIN).1 $(DESTDIR)/$(PREFIX)/share/man/man1/$(BIN).1

uninstall:
	$(CMD)rm -f $(DESTDIR)/$(PREFIX)/bin/$(BIN)
	$(CMD)rm -f $(DESTDIR)/$(PREFIX)/share/man/man1/$(BIN).1

.PHONY: all debug docs release clean install uninstall
