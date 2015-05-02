#---- makefile ----
CC=gcc -std=c99
CFLAGS=-U__STRICT_ANSI__ -fno-common\
       -Wall -Wextra -Wc++-compat -Werror -pedantic
LDFLAGS=

all : labGen

labGen: labGen.o
	${CC} -o labGen labGen.o ${LDFLAGS}

labGen.o: labGen.c labGen.h
	${CC} ${CFLAGS} -o labGen.o -c labGen.c

clean:
	rm -f labGen *.o
