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

void test_foo() {
  scheduler_begin();
  thread_fork(foo, (void*)"bar");
  thread_fork(foo, (void*)"baz");
  thread_fork(foo, (void*)"bifur");
  thread_fork(foo, (void*)"bofur");
  thread_fork(foo, (void*)"bombur");
  thread_fork(foo, (void*)"fili");
  thread_fork(foo, (void*)"kili");
  scheduler_end(); 
}


int main(void) {
  test_foo();

  return 0;
}

