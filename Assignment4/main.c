// Stacy Watts
// CS 533 - Fall 2014
// Assignment 4

#include "scheduler.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// all tests we create go in this file.  

struct mutex lock_one;
int shared_counter = 0;


void test_mutex_lock(void * arg) {
   mutex_lock(&lock_one);
   int temp = shared_counter;
   yield();
   shared_counter = temp + 1;
   mutex_unlock(&lock_one);
}




int main(void) {
  scheduler_begin();
  mutex_init(&lock_one);
  //
  mutex_lock(&lock_one);
  mutex_unlock(&lock_one);

//  thread_fork(test_mutex_lock, (void*)"A");
//  thread_fork(test_mutex_lock, (void*)2);
  //
  scheduler_end();
  return 0;
}

