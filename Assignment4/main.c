// Stacy Watts
// CS 533 - Fall 2014
// Assignment 4

#include "scheduler.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// all tests we create go in this file.  

// vars for first test
struct mutex lock_test;
int shared_counter = 0;

// vars for second test
int NUM_PHIL = 5;
struct mutex chopstick[5];

void test_mutex_lock(void * arg);
void test_threaded_mutex();



void test_cv(void * arg) {
  int left = *(int *)arg;
  printf("%d\n", left);
  int right = (left+1) % NUM_PHIL;
  printf("Philosopher %d  will now get the %d chopstick.\n", left, left);
  mutex_lock(&chopstick[left]);
  yield();
  printf("Philosopher %d  will now get the %d chopstick.\n", right, right);
  mutex_lock(&chopstick[right]);
  printf("using both chopsticks: %d %d\n", left, right); 
  yield();
  printf("Philosopher %d  will now yield the  chopstick.\n", right);
  mutex_unlock(&chopstick[right]);
  yield();
  printf("Philosopher %d  will now yield the %d chopstick.\n", left, left);
  mutex_unlock(&chopstick[left]);
  yield();
}




void test_dining() {
  int i = 0;
  for (i = 0; i<NUM_PHIL; ++i) {
    thread_fork(test_cv, (void*)&i);
  }
}


int main(void) {
  scheduler_begin();
  mutex_init(&lock_test);
  //
  // test_threaded_mutex();  // this is the test for part 1.
  test_dining();  // This is the test for part 2.
  //
  scheduler_end();
  return 0;
}



// this is essentialy the argument for using a lock, shared data accessed!
// I left this in to prove to myself that the schedule still worked, the 
// mutex had worked so well.  
void test_unprotected_update(void * arg) {
   int temp = shared_counter;
   printf("%s  starts shared counter = %d\n", (char *)arg, shared_counter);
   yield();
   printf("%s  after yield in critical section shared counter = %d\n", 
         (char *)arg, shared_counter);
   shared_counter = temp + 1;
}

void test_unprotected_threaded() {
  thread_fork(test_unprotected_update, (void*)"Thread 1");
  thread_fork(test_unprotected_update, (void*)"Thread 2");
  thread_fork(test_unprotected_update, (void*)"Thread 3");
  thread_fork(test_unprotected_update, (void*)"Thread 4");
  thread_fork(test_unprotected_update, (void*)"Thread 5");
  thread_fork(test_unprotected_update, (void*)"Thread 6");
  thread_fork(test_unprotected_update, (void*)"Thread 7");
  thread_fork(test_unprotected_update, (void*)"Thread 8");
}


// I initialy wrote this out and had to debug why the value never got to 16
// at some point I noticed I'd failed to re-check the value of shared 
// counter. case in point why cached values and multithreading is hard.  
void test_mutex_lock(void * arg) {
   printf("%s  attempts locking, shared counter = %d\n", 
         (char *)arg, shared_counter);
   mutex_lock(&lock_test);
   int temp = shared_counter;
   printf("%s  in critical section, shared counter = %d\n", 
         (char *)arg, shared_counter);
   yield();
   printf("%s  after yield in critical section shared counter = %d\n", 
         (char *)arg, shared_counter);
   shared_counter = temp + 1;
   printf("%s  after update in critical section shared counter = %d\n", 
         (char *)arg, shared_counter);
   yield();
   mutex_unlock(&lock_test);
   printf("%s  after lock release, shared counter = %d\n", 
         (char *)arg, shared_counter);
   yield();
   // second time for locking
   printf("%s  attempts 2nd locking, shared counter = %d\n", 
         (char *)arg, shared_counter);
   mutex_lock(&lock_test);
   temp = shared_counter;
   printf("%s  in 2nd critical section, shared counter = %d\n", 
         (char *)arg, shared_counter);
   yield();
   printf("%s  after yield in 2nd critical section shared counter = %d\n", 
         (char *)arg, shared_counter);
   shared_counter = temp + 1;
   printf("%s  after update in 2nd critical section shared counter = %d\n",
         (char *)arg, shared_counter);
   yield();
   mutex_unlock(&lock_test);
   printf("%s  after lock release, shared counter = %d\n", 
         (char *)arg, shared_counter);
}



void test_threaded_mutex() {
  thread_fork(test_mutex_lock, (void*)"Thread 1");
  thread_fork(test_mutex_lock, (void*)"Thread 2");
  thread_fork(test_mutex_lock, (void*)"Thread 3");
  thread_fork(test_mutex_lock, (void*)"Thread 4");
  thread_fork(test_mutex_lock, (void*)"Thread 5");
  thread_fork(test_mutex_lock, (void*)"Thread 6");
  thread_fork(test_mutex_lock, (void*)"Thread 7");
  thread_fork(test_mutex_lock, (void*)"Thread 8");
}
