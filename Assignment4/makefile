## Makefile for CS533 assignment 4

CC=gcc
DEBUG=-g
WARN=-Wall
FLAGS=-lrt

main: main.c
	$(CC) $(WARN) -o main switch.s scheduler.c queue.c async.c main.c $(FLAGS)

demo2: demo2.c
	$(CC) $(WARN) -o demo2 switch.s scheduler.c queue.c async.c demo2.c $(FLAGS)

demo1: demo1.c
	$(CC) $(WARN) -o demo1 switch.s scheduler.c queue.c async.c demo1.c $(FLAGS)

debug: main.c
	$(CC) $(DEBUG) $(WARN) -o debugMain switch.s scheduler.c queue.c async.c main.c $(FLAGS)

clean:
	rm -f demo1 demo2 main debugMain 

