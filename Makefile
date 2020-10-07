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

testscanner: install lexer.o err.o token.o
	$(COMPILE) -o $(BIN)$@ src/$@.c $(BIN)lexer.o $(BIN)err.o $(BIN)token.o

lexer.o: src/lexer.c src/lexer.h
	$(COMPILE) -c $< -o $(BIN)$@

token.o: src/token.c src/token.h
	$(COMPILE) -c $< -o $(BIN)$@

err.o: src/err.c src/err.h
	$(COMPILE) -c $< -o $(BIN)$@

clean:
	rm -rf $(BIN)
