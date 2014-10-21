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

void scheduler_begin();
void scheduler_end();
void thread_fork(void(*target)(void*), void * arg);
void thread_finish();
void yield();

