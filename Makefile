CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

# Default target (first one in the file)
main: engine.c
	$(CC) $(CFLAGS) engine.c -o engine -lm

# Remove build products
clean:
	rm -f engine
