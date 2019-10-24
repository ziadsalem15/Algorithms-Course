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
	./part2b && exit 1 || [ $$? -eq 1 ] #no parameters
	./part2b -x 6 && exit 2 || [ $$? -eq 2 ]
	./part2b -c x && exit 3 || [ $$? -eq 3 ]
	./part2b -c 60 && exit 0 || [ $$? -eq 0 ]
	./part2b -c -400 && exit 4 || [ $$? -eq 4 ]
	./part2b -f 10 && exit 0 || [ $$? -eq 0 ]
	./part2b -f 5 h && exit 1 || [ $$? -eq 1 ] 
