## Makefile for CS533 assignment 2

CC=gcc
DEBUG=-g
WARN=-Wall

main: main.c
	$(CC) $(WARN) -o main main.c queue.c scheduler.c switch.s

debug: main.c
	$(CC) $(DEBUG) $(WARN) -o mainDebug main.c queue.c scheduler.c switch.s

clean:
	rm -f main mainDebug

