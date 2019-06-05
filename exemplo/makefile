CC=gcc
LIB_DIR=./../lib
INC_DIR=./../include
BIN_DIR=./../bin
SRC_DIR=./../src

all: main

main: ./main.c $(LIB_DIR)/libt2fs.a
	$(CC) -o $@ $^ -Wall

clean:
	rm -rf ./*~
