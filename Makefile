# seqspec - analyze and continue arbitrary sequences of any order
# copyright (C) Ethan Marshall - 2022
.POSIX:

SRC = libsspec.c
OBJ = ${SRC:.c=.o}
HDR = libsspec.h sspec_internal.h

LIB = libsspec.a
SLIB = libsspec.so

PREFIX = /usr/local

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
	valgrind ./test
	rm test

install: all
	mkdir -p ${DESTDIR}${PREFIX}/lib ${DESTDIR}${PREFIX}/include
	cp -f ${LIB} ${SLIB} ${DESTDIR}${PREFIX}/lib
	cp -f ${HDR} ${DESTDIR}${PREFIX}/include
	chmod 755 ${DESTDIR}${PREFIX}/lib/${LIB}

uninstall:
	rm -f ${DESTDIR}${PREFIX}/lib/${LIB} ${DESTDIR}${PREFIX}/lib/${SLIB}
	rm -f ${DESTDIR}${PREFIX}/include/*sspec*.h

.PHONY: all clean test install uninstall
