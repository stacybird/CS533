// Stacy Watts
// CS 533 - Fall 2014
// Assignment 2

// definitions of our scheduler API functions.

#include "scheduler.h"
#include "queue.h"
#include <stdlib.h>


int ALLOCATE = 1024*1024;  // stack allocation size
struct queue * ready_list;
struct thread_t * current_thread = NULL;

void thread_start(struct thread_t * old, struct thread_t * new);
void thread_switch(struct thread_t * old, struct thread_t * new);

// 5.  scheduler_begin should initialize and/or allocate any data 
//     structures our scheduler will need.
void scheduler_begin() {
  ready_list = malloc(sizeof(struct queue));
  ready_list->head = NULL;
  ready_list->tail = NULL;
  current_thread = malloc(sizeof(struct thread_t));
  current_thread->state = RUNNING;
}

// 8. Finally, recall that we need a way to prevent the main thread from 
//    terminating prematurely if there are other threads still running. A 
//    potential solution is given in the overview above. Implement this 
//    solution how you see fit in scheduler_end. You might find the 
//    is_empty queue predicate useful.
void scheduler_end() {
  while (!is_empty(ready_list)) {
    yield();
  }
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
// a. Allocate a new thread table entry, and allocate its control stack.
  struct thread_t * new_thread = malloc(sizeof(struct thread_t));
  void *stack_bottom = malloc(ALLOCATE);
  void *stack_top = stack_bottom + ALLOCATE;
  new_thread->sp = stack_top; 
// b. Set the new thread's initial argument and initial function.
  new_thread->initial_function = target;
  new_thread->initial_arg = arg;
// c. Set the current thread's state to READY and enqueue it on the ready 
//    list.
  current_thread->state = READY;
  thread_enqueue(ready_list, current_thread);
// d. Set the new thread's state to RUNNING.
  new_thread->state = RUNNING;
// e. Save a pointer to the current thread in a temporary variable, then 
//    set the current thread to the new thread.
  struct thread_t * temp_thread = current_thread;
  current_thread = new_thread;
// f. Call thread_start with the old current thread as old and the new 
//    current thread as new.
  thread_start(temp_thread, current_thread);
}


// finish handler at the bottom of the stack which sets the current 
// thread's state to DONE, then calls yield(); 
void thread_finish() {
  current_thread->state = DONE; // set state to done
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
// 4.1 Modify your yield routine to prevent a thread whose status is BLOCKED
//     from enqueuing itself on the ready list.
void yield() {
// a. If the current thread is not DONE, set its state to READY and 
//    enqueue it on the ready list.
  if ((BLOCKED != current_thread->state) && (DONE != current_thread->state)) {
    current_thread->state = READY;
    thread_enqueue(ready_list, current_thread);
  }
// b. Dequeue the next thread from the ready list and set its state to 
//    RUNNING.
  struct thread_t * next_thread = thread_dequeue(ready_list);
  next_thread->state = RUNNING;
// c. Save a pointer to the current thread in a temporary variable, then 
//    set the current thread to the next thread.
  struct thread_t * temp_thread = current_thread;
  current_thread = next_thread;
// d. Call thread_switch with the old current thread as old and the new 
  thread_switch(temp_thread, current_thread);
}

