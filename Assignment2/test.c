#include "scheduler.h"

// all tests we create go in this file.  


void foo(void * arg) {
  char * str = (char*) arg;
  /* do important stuff */
}


int main(void) {
  scheduler_begin();
  thread_fork(foo, (void*)"bar");
  thread_fork(foo, (void*)"baz");
  scheduler_end(); 
}
