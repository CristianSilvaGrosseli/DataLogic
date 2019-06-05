#
# Makefile ESQUELETO
#
# DEVE ter uma regra "all" para geração da biblioteca
# regra "clean" para remover todos os objetos gerados.
#
# NECESSARIO adaptar este esqueleto de makefile para suas necessidades.
#
# 

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

all: t2fs.a

t2fs.a: $(LIB_DIR)/apidisk.o $(BIN_DIR)/t2fs.o
	ar crs $(LIB_DIR)/libt2fs.a $^

$(BIN_DIR)/t2fs.o: $(SRC_DIR)/t2fs.c $(INC_DIR)/t2fs.h
	$(CC) -c -o $@ $< -Wall

clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/*.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~


