// Stacy Watts
// CS 533 - Fall 2014
// Assignment 2

// definitions of our scheduler API functions.

#include "scheduler.h"
#include "queue.h"

// 5.  scheduler_begin should initialize and/or allocate any data 
//     structures our scheduler will need.
void scheduler_begin() {
  
  
}

// 8. Finally, recall that we need a way to prevent the main thread from 
//    terminating prematurely if there are other threads still running. A 
//    potential solution is given in the overview above. Implement this 
//    solution how you see fit in scheduler_end. You might find the 
//    is_empty queue predicate useful.
void scheduler_end() {
}


// 6. Next, let's implement thread_fork. This function encapsulates 
//    everything necessary to allocate a new thread and then jump to it. 
//    thread_fork should:
// a. Allocate a new thread table entry, and allocate its control stack.
// b. Set the new thread's initial argument and initial function.
// c. Set the current thread's state to READY and enqueue it on the ready 
//    list.
// d. Set the new thread's state to RUNNING.
// e. Save a pointer to the current thread in a temporary variable, then 
//    set the current thread to the new thread.
// f. Call thread_start with the old current thread as old and the new 
//    current thread as new.
void thread_fork(void(*target)(void*), void * arg) {

}

// finish handler at the bottom of the stack which sets the current 
// thread's state to DONE, then calls yield(); 
void thread_finish() {
  // set state to done
  yield();// call yield();
}


// 7. yield is very similar to thread_fork, with the main difference being 
//    that it is pulling the next thread to run off of the ready list 
//    instead of creating it. yield should:
// a. If the current thread is not DONE, set its state to READY and 
//    enqueue it on the ready list.
// b. Dequeue the next thread from the ready list and set its state to 
//    RUNNING.
// c. Save a pointer to the current thread in a temporary variable, then 
//    set the current thread to the next thread.
// d. Call thread_switch with the old current thread as old and the new 
//    current thread as new.
void yield() {

}

