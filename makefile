CC=gcc
CFLAGS=-g -std=c99 -Wall
#LDFLAGS=-lm

test2a:
	./part2a #no parameters
	./part2a "only one parameter"
	./part2a "biggest parameter" "at" "start"
	./part2a "biggest" "parameter" "at" "end" "very very very big parameter"
	./part2a "answer" "somewhere" "in" "the" "middle"
	./part2a "two" "strings" "the" "same" "length" "haha!"


test2b:
	./part2b #no parameters
	./part2b "-c"
	./part2b "-c" ""
