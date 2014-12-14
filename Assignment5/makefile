## Makefile for CS533 assignment 5

CC=gcc
DEBUG=-g
WARN=-Wall
FLAGS=-lrt

main: main.c
	$(CC) $(WARN) -o main switch.s scheduler.c queue.c async.c main.c $(FLAGS)

debug: main.c
	$(CC) $(DEBUG) $(WARN) -o debugMain switch.s scheduler.c queue.c async.c main.c $(FLAGS)

clean:
	rm -f demo1 demo2 main debugMain 

