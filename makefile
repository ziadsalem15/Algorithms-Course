CC=gcc
CFLAGS=-g -std=c99 -Wall

test : arrays
	./arrays

part2 :
				$(CC) $(CFLAGS) slists.c test.c -o test
