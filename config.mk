#
# chue: a cat(1) for colors
#
# (c) Kiëd Llaentenn
# See the COPYING file for more information
#

CMD = @

DESTDIR =
PREFIX  = /usr/local

CC = cc
LD = gold

RELEASE_CFLAGS  = -Os
RELEASE_LDFLAGS = -march=native -flto -s
DEBUG_CFLAGS    = -Og -ggdb
DEBUG_LDFLAGS   = -fsanitize=address
