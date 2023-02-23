PROJECT_NAME := iron_rabbit_gc
CC := gcc
CFLAGS := -Wall
BIN := bin
LIB := lib
SRC := src
INC := include

DEMO := ${PROJECT_NAME}_demo

all:	lib demo
	echo "Building all.."

lib:	lib.o
	ar rcs ${LIB}/${PROJECT_NAME}.a ${PROJECT_NAME}.o

lib.o:	${SRC}/${PROJECT_NAME}.c ${INC}/${PROJECT_NAME}.h
	${CC} ${CFLAGS} -O -c ${SRC}/${PROJECT_NAME}.c

demo:	${SRC}/${DEMO}.c lib
	$(CC) ${CFLAGS} -o ${BIN}/${DEMO} ${SRC}/${DEMO}.c ${LIB}/${PROJECT_NAME}.a

run_demo:	demo
	./${BIN}/${DEMO}

clean:
	rm *.o
	rm -r ${BIN}/*
	rm -r ${LIB}/*
