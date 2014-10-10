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


void thread_start(struct thread_t * old, struct thread_t * new);

int main()
{
  struct thread_t myThread; // to test for starters 

  return 0;
}


// 2. Write an assembly routine to start a new thread, with the prototype:
// void thread_start(struct thread_t * old, struct thread_t * new);
//   a.  Push all callee-save registers (%rbx, %rbp, %r12-15) onto the current stack.
//   b.  Save the current stack pointer (%rsp) in old's thread table entry.
//   c.  Load the stack pointer from new's thread table entry into %rsp.
//   d.  Jump to the initial function of new.

void thread_start(struct thread_t * old, struct thread_t * new) {
  return;
}

// 3. Write an assembly routine to switch between two threads, with the prototype:
// void thread_switch(struct thread_t * old, struct thread_t * new);
//   a.  Push all callee-save registers onto the current stack.
//   b.  Save the current stack pointer in old's thread table entry.
//   c.  Load the stack pointer from new's thread table entry.
//   d.  Pop all callee-save registers from the new stack.
//   e.  Return.


// Your grade will primarily be determined by how well we think you understand 
// the underlying concepts of each assignment, based not only on your code, but 
// also how you've tested your code, and your write-ups.

