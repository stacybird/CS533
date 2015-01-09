// Stacy Watts
// CS 533 - Fall 2014
// Assignment 3

#include "scheduler.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// all tests we create go in this file.  

ssize_t read_wrap(int fd, void * buf, size_t count);


void test_read(void * arg) {
  char * str = (char*) arg;
  int filedesc = open(str, O_RDONLY);
  char buffer[20];
  ssize_t buf_size = 0;
  ssize_t my_count = 0;
  buf_size = sizeof(buffer);
  my_count = read(filedesc, buffer, buf_size);
  do {
    printf("%s", buffer);
    printf("*");
    my_count = read(filedesc, buffer, buf_size);
  } while (my_count != 0);
  printf("\n****    end read of %s\n", str);
  thread_finish();
}

void test_read_wrap(void * arg) {
  char * str = (char*) arg;
  int filedesc = open(str, O_RDONLY);
  char buffer[20];
  ssize_t buf_size = 0;
  ssize_t my_count = 0;
  buf_size = sizeof(buffer);
  my_count = read_wrap(filedesc, buffer, buf_size);
  do {
    my_count = read_wrap(filedesc, buffer, buf_size);
    printf("%s", buffer);
    printf("*");
  } while (my_count != 0);
  printf("\n****    end read_wrap of %s\n", str);
  thread_finish();
}

int main(void) {
  scheduler_begin();
  thread_fork(test_read, (void*)"test.txt");
  thread_fork(test_read_wrap, (void*)"test.txt");
  thread_fork(test_read_wrap, (void*)"test.txt");
  thread_fork(test_read_wrap, (void*)"test.txt");
  scheduler_end();
  return 0;
}

