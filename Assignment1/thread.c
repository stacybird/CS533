// Stacy Watts
// CS 533 - Fall 2014
// Assignment 1
//
// develop a C data structure representing a thread and to develop and test the 
// x86-64 assembly routines for starting threads and switching between them.

#include <stdio.h>
#include <stdlib.h>

// 1.  Write a C data structure, struct thread_t, to represent a thread table 
//     entry (the data pertaining to a thread). At first, it should have at 
//     least a stack pointer (perhaps of type void*), and a pointer to an initial 
//     function (perhaps of type void(*initial_function)(void)).

struct thread_t {
  void *sp; // stack pointer
  void(*initial_function)(void);
            // CPU Context
            // Program counter
            // Register State
};


int ALLOCATE = 1024;
struct thread_t current_thread;
struct thread_t stored_thread;

void thread_start(struct thread_t * old, struct thread_t * new);
void thread_switch(struct thread_t * old, struct thread_t * new);

void yield() {
 struct thread_t temp = current_thread;
 current_thread = stored_thread;
 stored_thread = temp;
 thread_switch(&stored_thread, &current_thread);
}

void test_yield_loop() {
    printf("testing yield");
    yield();
}

int main()
{
  void *stack_bottom = malloc(ALLOCATE);
  //printf("%p  stack_bottom\n", stack_bottom);
  void *stack_top = stack_bottom + 1024;
  //printf("%p  stack_top\n", stack_top);
  current_thread.sp = stack_top; 
  //printf("%p  current_thread\n", &current_thread);
  //printf("%p  current_thread.sp\n", current_thread.sp);
  
  current_thread.initial_function = &yield;
  //printf("%p  current_thread.initial_function\n", current_thread.initial_function);
  thread_start(&stored_thread, &current_thread); 

  test_yield_loop();

  free(stack_bottom);
  return 0;
}

// Your grade will primarily be determined by how well we think you understand 
// the underlying concepts of each assignment, based not only on your code, but 
// also how you've tested your code, and your write-ups.

