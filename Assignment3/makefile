## Makefile for CS533 assignment 3

CC=gcc
DEBUG=-g
WARN=-Wall
FLAGS=-lrt

main: main.c
	$(CC) $(WARN) -o main switch.s scheduler.c queue.c async.c main.c $(FLAGS)

snake: snake.c
	$(CC) $(WARN) -o snake switch.s scheduler.c queue.c async.c snake.c $(FLAGS)

debug: main.c
	$(CC) $(DEBUG) $(WARN) -o debugMain switch.s scheduler.c queue.c async.c main.c $(FLAGS)

clean:
	rm -f main debugMain snake

