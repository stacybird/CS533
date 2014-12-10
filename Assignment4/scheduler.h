// Stacy Watts
// CS 533 - Fall 2014
// Assignment 4

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

void scheduler_begin();
void scheduler_end();
void thread_fork(void(*target)(void*), void * arg);
void thread_finish();
void yield();
void mutex_init(struct mutex *);
void mutex_lock(struct mutex *);
void mutex_unlock(struct mutex *);

