// Stacy Watts
// CS 533 - Fall 2014
// Assignment 2

#include "scheduler.h"
#include <stdio.h>

// all tests we create go in this file.  

void foo(void * arg) {
  char * str = (char*) arg;
  /* do important stuff */
  printf("\nfoo threading works! args: %s\n", str);
}


int main(void) {
  scheduler_begin();
  thread_fork(foo, (void*)"bar");
  thread_fork(foo, (void*)"baz");
  scheduler_end(); 

  return 0;
}

