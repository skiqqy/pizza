# @Auther Stephen Cochrane
# @Licence GPL
# Makefile for the pizza project

CC      = gcc
FLAGS   = -Wall -lm
COMPILE = $(CC) $(FLAGS)
BIN     = bin/

all: install pizza
	@echo "Baking the pizza c:"

install:
	mkdir -p bin

pizza: err.o lexer.o

# Run a full scan
test: testlexer

testlexer: install lexer.o err.o token.o
	$(COMPILE) -o $(BIN)$@ src/$@.c $(BIN)lexer.o $(BIN)err.o $(BIN)token.o
	./tests/tscanner.sh

lexer.o: src/lexer.c src/lexer.h
	$(COMPILE) -c $< -o $(BIN)$@

token.o: src/token.c src/token.h
	$(COMPILE) -c $< -o $(BIN)$@

err.o: src/err.c src/err.h
	$(COMPILE) -c $< -o $(BIN)$@

clean:
	rm -rf $(BIN)
