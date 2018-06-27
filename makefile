CC = gcc

VFLAGS  = --quiet
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full

all: Build

Build: src/City.c src/Route.c src/Salesman.c headers/City.h headers/Route.h headers/Salesman.h
	@$(CC) src/City.c src/Route.c src/Salesman.c -o Salesman -lm -Wall -O3
	@echo Sucessfully Compiled Salesman
	
clean: Salesman
	rm Salesman.out
	
memcheck: Build
	@valgrind $(VFLAGS) ./Salesman 8
