// Stacy Watts
// CS 533 - Fall 2014
// Assignment 4

// definitions of our scheduler API functions.

#include "scheduler.h"
#include "queue.h"
#include <stdlib.h>


int ALLOCATE = 1024*1024;  // stack allocation size
struct queue * ready_list;
struct thread_t * current_thread = NULL;

void thread_start(struct thread_t * old, struct thread_t * new);
void thread_switch(struct thread_t * old, struct thread_t * new);

// initialization and allocation of scheduler
void scheduler_begin() {
  ready_list = malloc(sizeof(struct queue));
  ready_list->head = NULL;
  ready_list->tail = NULL;
  current_thread = malloc(sizeof(struct thread_t));
  current_thread->state = RUNNING;
}


// prevent main thread from ending prematurely.
void scheduler_end() {
  while (!is_empty(ready_list)) {
    yield();
  }
}


// + allocates the new thread table entry and stack
// + sets the new thread argument and function
// + sets original to ready and enquques
// + sets new thread to running
// + shuffle pointer to current thread, and call thread start
void thread_fork(void(*target)(void*), void * arg) {
  struct thread_t * new_thread = malloc(sizeof(struct thread_t));
  void *stack_bottom = malloc(ALLOCATE);
  void *stack_top = stack_bottom + ALLOCATE;
  new_thread->sp = stack_top; 
  new_thread->initial_function = target;
  new_thread->initial_arg = arg;
  current_thread->state = READY;
  thread_enqueue(ready_list, current_thread);
  new_thread->state = RUNNING;
  struct thread_t * temp_thread = current_thread;
  current_thread = new_thread;
  thread_start(temp_thread, current_thread);
}


// finish handler at the bottom of the stack which sets the current 
// thread's state to DONE, then calls yield(); 
void thread_finish() {
  current_thread->state = DONE;
  yield();
}


// + if current thread isn't blocked or done, put self on ready list.
// + dequeue next thread, set running.
// + shuffle pointer for current thread
// + switch threads
//
// 4.1 Modify your yield routine to prevent a thread whose status is
//     BLOCKED from enqueuing itself on the ready list.
void yield() {
  if (    (BLOCKED != current_thread->state) 
       && (DONE != current_thread->state)) {
    current_thread->state = READY;
    thread_enqueue(ready_list, current_thread);
  }
  struct thread_t * next_thread = thread_dequeue(ready_list);
  next_thread->state = RUNNING;
  struct thread_t * temp_thread = current_thread;
  current_thread = next_thread;
  thread_switch(temp_thread, current_thread);
}


// 4.3 Code a data structure, struct mutex that represents your lock, 
//     and three functions:
//       void mutex_init(struct mutex *)
//       void mutex_lock(struct mutex *)
//       void mutex_unlock(struct mutex *)
//     mutex_init should initialize all fields of struct mutex. mutex_lock
//     should attempt to acquire the lock, and block the calling thread if
//     the lock is already held. mutex_unlock should at least wake up a 
//     thread waiting for the lock. It may do other things as well 
//     depending on the design you choose.
void mutex_init(struct mutex * lock) {
  lock = malloc(sizeof(struct lock));
  lock.holder == NULL;
  lock->blocked_list = malloc(sizeof(struct queue));
  lock->blocked_list->head = NULL;
  lock->blocked_list->tail = NULL;
}


void mutex_lock(struct mutex * lock) {
  if (lock->holder == NULL) {
    lock->holder = current_thread;
  }
  else {
    current_thread->state = BLOCKED;
    thread_enqueue(lock->blocked_list, current_thread);
    yield();
  }
}


void mutex_unlock(struct mutex * lock) {
  // just lelease lock if noone waiting
  if (is_empty(lock->blocked_list)) {
    lock->holder = NULL;
  } // otherwise release to next waiting for lock
  else {
    lock->holder = thread_dequeue(lock->blocked_list);
    lock->holder->state = READY;
    thread_enqueue(ready_list, lock->holder);
  }
}


// 4.5 Code a data structure struct condition, that represents your 
//     condition variable, and four functions:
//       void condition_init(struct condition *)
//       void condition_wait(struct condition *)
//       void condition_signal(struct condition *)
//       void condition_broadcast(struct condition *)
//     condition_init should initialize all fields of struct condition. 
//     condition_wait should cause a thread to wait on the condition, and 
//     condition_signal should wake up a waiting thread (but not suspend 
//     the current thread, as per MESA semantics). condition_broadcast 
//     should signal all waiting threads.
void condition_init(struct condition * cv) {
  cv = malloc(sizeof(struct cv));
  cv->lock = NULL;
}

void condition_wait(struct condition * cv) {
  if (cv->lock != NULL) {
    current_thread->state = BLOCKED;
    thread_enqueue(cv->lock->blocked_list, current_thread);
    yield();
  }
}


// wake next up on blocked list, add to ready list.  
void condition_signal(struct condition * cv) {
  struct thread_t * temp_thread;
  temp_thread = thread_dequeue(cv->lock->blocked_list);
  temp_thread->state = READY;
  thread_enqueue(ready_list, temp_thread);
}


// wake all threads on blocked queue.
void condition_broadcast(struct condition * cv) {
  struct thread_t * temp_thread;
  while (!is_empty(cv->lock->blocked_list)) {
    temp_thread = thread_dequeue(cv->lock->blocked_list);
    temp_thread->state = READY;
    thread_enqueue(ready_list, temp_thread);
  }
}

