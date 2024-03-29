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
struct condition chopstick_held[5];

void test_mutex_lock(void * arg);
void test_threaded_mutex();
void test_dining_mutex(void * arg);
void test_dining();


void wait_both_free(int i) {
  condition_wait(&chopstick_held[(i+1) % NUM_PHIL]);
  condition_wait(&chopstick_held[i]);
}


void signal_both_free(int i) {
  condition_signal(&chopstick_held[(i+1) % NUM_PHIL]);
  condition_signal(&chopstick_held[i]);
}


void test_cv(void * arg) {
  int left = *(int *)arg;
  printf("\n");
  int right = (left+1) % NUM_PHIL;
  printf("Yield! (Philosopher %d)\n", left);
  yield();
  wait_both_free(left);
  printf("Philosopher %d  will now get the %d chopstick.\n", left, left);
  mutex_lock(&chopstick[left]);
  printf("Philosopher %d  will now get the %d chopstick.\n", left, right);
  mutex_lock(&chopstick[right]);
  printf("Yield! (Philosopher %d)\n", left);
  yield();
  printf("***** Philosopher %d using both chopsticks: %d %d *****\n", left, left, right);
  signal_both_free(left);
  printf("signal  %d  %d\n", left, right);
  mutex_unlock(&chopstick[left]);
  mutex_unlock(&chopstick[right]);
  printf("Yield! (Philosopher %d)\n", left);
  yield();
}


void test_dining_cv() {
  int i = 0;
  for (i = 0; i<NUM_PHIL; ++i) {
    mutex_init(&chopstick[i]);
    condition_init(&chopstick_held[i]);
    chopstick_held[i].lock = &chopstick[i];
  }
  for (i = 0; i<NUM_PHIL; ++i) {
    thread_fork(test_cv, (void*)&i);
  }
}


int main(void) {
  scheduler_begin();
  mutex_init(&lock_test);
  //
  test_threaded_mutex();  // this is the test for part 1.
  // test_dining();  // This is the naive test for philosophers (mutexes)
  test_dining_cv(); // This is the cv test for philosophers
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


// to start, we have a simple, naieve implementation with yields 
// interspersed.  unfortunately the way our scheduler works, this 
// implementation only allows one philosopher at a time, since they are 
// sequentially started, we only have one kernel thread, and they try to 
// aquire the locks in the same order every time.  number of chopsticks 
// to deal with this is philosophers + 1.
void test_dining_mutex(void * arg) {
  int left = *(int *)arg;
  printf("\n");
  int right = left+1;
  printf("Philosopher %d  will now get the %d chopstick.\n", left, left);
  mutex_lock(&chopstick[left]);
  yield();
  printf("Philosopher %d  will now get the %d chopstick.\n", left, right);
  mutex_lock(&chopstick[right]);
  printf("***** Philosopher %d using both chopsticks: %d %d *****\n", left, left, right);
  yield();
  printf("Philosopher %d  will now yield the %d chopstick.\n", left, right);
  mutex_unlock(&chopstick[right]);
  yield();
  printf("Philosopher %d  will now yield the %d chopstick.\n", left, left);
  mutex_unlock(&chopstick[left]);
  yield();
}


void test_dining() {
  int i = 0;
  mutex_init(&chopstick[NUM_PHIL]);
  for (i = 0; i<NUM_PHIL; ++i) {
    mutex_init(&chopstick[i]);
    thread_fork(test_dining_mutex, (void*)&i);
  }
}

