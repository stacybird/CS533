// definitions of our scheduler API functions.

#include "scheduler.h"
#include "queue.h"

struct thread_t current_thread;
struct thread_t stored_thread;

void scheduler_begin() {
}

void scheduler_end() {
}

void thread_fork(void(*target)(void*), void * arg) {
}

// finish handler at the bottom of the stack which sets the current thread's state to DONE, then calls yield(); 
void thread_finish() {
  // set state to done
  yield();// call yield();
}

void yield() {
 struct thread_t temp = current_thread;
 current_thread = stored_thread;
 stored_thread = temp;
 thread_switch(&stored_thread, &current_thread);
}

