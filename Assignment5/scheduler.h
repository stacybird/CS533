// Stacy Watts
// CS 533 - Fall 2014
// Assignment 5

#include "queue.h"

typedef enum {
  RUNNING,
  READY,
  BLOCKED,
  DONE
} state_t;

struct thread_t {
  void *sp; // stack pointer
  void(*initial_function)(void*);
  void * initial_arg;
  state_t state;
};

// Design a mutex lock that provides mutual exclusion between the lock 
// and unlock primitives by blocking any thread that attempts to lock a 
// mutex that is currently held. 
struct mutex {
  struct thread_t * holder;
  struct queue blocked_list;
};

// Design a condition variable that has MESA semantics. You may design it 
// in terms of your mutex lock, or on its own.
struct condition {
  struct mutex * lock;
};

void scheduler_begin();
void scheduler_end();
void thread_fork(void(*target)(void*), void * arg);
void thread_finish();
void yield();
void mutex_init(struct mutex *);
void mutex_lock(struct mutex *);
void mutex_unlock(struct mutex *);
void condition_init(struct condition *);
void condition_wait(struct condition *);
void condition_signal(struct condition *);
void condition_broadcast(struct condition *);

extern struct thread_t * get_current_thread();
extern void set_current_thread(struct thread_t*);
#define current_thread (get_current_thread())

