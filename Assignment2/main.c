#include "scheduler.h"

// all tests we create go in this file.  

/* old data from assignment 1
int ALLOCATE = 1024*1024;  //  1024 felt a little low, doesn't look like this crashes anything.
void test_yield_loop() {
  while (1) {
    printf("testing yield\n");
    yield();
  }
}
  end old data from assignment 1 */



void thread_start(struct thread_t * old, struct thread_t * new);
void thread_switch(struct thread_t * old, struct thread_t * new);


void foo(void * arg) {
  char * str = (char*) arg;
  /* do important stuff */
}


int main(void) {
  scheduler_begin();
  thread_fork(foo, (void*)"bar");
  thread_fork(foo, (void*)"baz");
  scheduler_end(); 

/* begin code from assigment 1 testing in main

  void *stack_bottom = malloc(ALLOCATE);
  void *stack_top = stack_bottom + ALLOCATE;
  current_thread.sp = stack_top; 
  current_thread.initial_function = &test_yield_loop;
  thread_start(&stored_thread, &current_thread); 

  while (1) {
    printf("testing yield other thread\n");
    yield();
  }

  free(stack_bottom);
  return 0;

  end assignment 1 testing from main */
}

