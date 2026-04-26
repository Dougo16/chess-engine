# Makefile for a single C file

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

# Default target (first one in the file)
main: main.c
	$(CC) $(CFLAGS) engine.c -o engine

# Remove build products
clean:
	rm -f main
