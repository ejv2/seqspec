# seqspec - analyze and continue arbitrary sequences of any order
# copyright (C) Ethan Marshall - 2022

SRC = libsspec.c
OBJ = ${SRC:.c=.o}
HDR = libsspec.h sspec_internal.h

LIB = libsspec.a
SLIB = libsspec.so

all: ${LIB} ${SLIB}

${LIB}: ${OBJ}
	${AR} -rc ${LIB} ${OBJ}
	ranlib ${LIB}

${SLIB}: ${OBJ}
	${CC} -o ${SLIB} -shared ${OBJ}

${OBJ}: ${HDR}

.c.o:
	${CC} -c ${CFLAGS} $<

clean:
	rm -f *.o ${LIB} ${SLIB}

test: ${SLIB}
	${CC} ${CFLAGS} -o test sspec_test.c libsspec.a
	./test
	rm test

.PHONY: all clean test
