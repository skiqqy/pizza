# @Auther Stephen Cochrane
# @Licence GPL
# Makefile for the pizza project

CC      = gcc
FLAGS   = -Wall
COMPILE = $(CC) $(FLAGS)
BIN     = bin/

install:
	mkdir -p bin

all: install pizza

pizza:

testscanner: install scanner.o err.o
	$(COMPILE) -o $(BIN)$@ src/$@.c $(BIN)scanner.o $(BIN)err.o

scanner.o: src/scanner.c src/scanner.h
	$(COMPILE) -c $< -o bin/$@

err.o: src/err.c src/err.h
	$(COMPILE) -c $< -o bin/$@

clean:
	rm -rf $(BIN)
