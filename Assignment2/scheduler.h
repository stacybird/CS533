typedef enum {
  RUNNING,
  READY,
  BLOCKED,
  DONE
} state_t;

struct thread_t {
  void *sp; // stack pointer
  void(*initial_function)(void);
  state_t state;
};

