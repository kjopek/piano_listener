PROG=pianola
SRCS=main.c music.c

CC=clang

NO_MAN = "no"

CFLAGS += -I/usr/local/include -g
LDFLAGS += -L/usr/local/lib -lfftw3_threads

.include<bsd.prog.mk>
