// Stacy Watts
// CS 533 - Fall 2014
// Assignment 1
//
// develop a C data structure representing a thread
// to develop and test the x86-64 assembly routines for starting threads and switching between them.

// 1.  Write a C data structure, struct thread_t, to represent a thread table entry (the data pertaining to a thread). At first, it should have at least a stack pointer (perhaps of type void*), and a pointer to an initial function (perhaps of type void(*initial_function)(void)).

// 2. Write an assembly routine to start a new thread, with the prototype:
// void thread_start(struct thread_t * old, struct thread_t * new);
//   a.  Push all callee-save registers (%rbx, %rbp, %r12-15) onto the current stack.
//   b.  Save the current stack pointer (%rsp) in old's thread table entry.
//   c.  Load the stack pointer from new's thread table entry into %rsp.
//   d.  Jump to the initial function of new.

// 3. Write an assembly routine to switch between two threads, with the prototype:
// void thread_switch(struct thread_t * old, struct thread_t * new);
//   a.  Push all callee-save registers onto the current stack.
//   b.  Save the current stack pointer in old's thread table entry.
//   c.  Load the stack pointer from new's thread table entry.
//   d.  Pop all callee-save registers from the new stack.
//   e.  Return.

