PROG=test_fft
SRCS=test_fft.c music.c

NO_MAN = "no"

CFLAGS += -I/usr/local/include -g
LDFLAGS += -L/usr/local/lib -lfftw3_threads

.include<bsd.prog.mk>
