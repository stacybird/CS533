# Stacy Watts
# CS 533 - Fall 2014
# Assignment 2

# 2. Write an assembly routine to start a new thread, with the prototype:
# void thread_start(struct thread_t * old, struct thread_t * new);
#   a.  Push all callee-save registers (%rbx, %rbp, %r12-15) onto the current stack.
#   b.  Save the current stack pointer (%rsp) in old's thread table entry.
#   c.  Load the stack pointer from new's thread table entry into %rsp.
#   d.  Jump to the initial function of new.

# void thread_start(struct thread_t * old, struct thread_t * new);

.globl thread_start

thread_start:
  pushq $thread_finish
  pushq %rbx           # callee-save
  pushq %rbp           # callee-save
  pushq %r12           # callee-save
  pushq %r13           # callee-save
  pushq %r14           # callee-save
  pushq %r15           # callee-save
  movq  %rsp, (%rdi)  # *old.sp = %rsp
  movq (%rsi), %rsp   # %rsp = *new.sp
  jmp *8(%rsi)        # jump *new.initial_function

# 3. Write an assembly routine to switch between two threads, with the prototype:
# void thread_switch(struct thread_t * old, struct thread_t * new);
#   a.  Push all callee-save registers onto the current stack.
#   b.  Save the current stack pointer in old's thread table entry.
#   c.  Load the stack pointer from new's thread table entry.
#   d.  Pop all callee-save registers from the new stack.
#   e.  Return.

# void thread_switch(struct thread_t * old, struct thread_t * new);

.globl thread_switch

thread_switch:
  pushq %rbx           # callee-save
  pushq %rbp           # callee-save
  pushq %r12           # callee-save
  pushq %r13           # callee-save
  pushq %r14           # callee-save
  pushq %r15           # callee-save
  movq  %rsp, (%rdi)  # *old.sp = %rsp
  movq (%rsi), %rsp   # %rsp = *new.sp
  popq %r15            # callee-restore
  popq %r14            # callee-restore
  popq %r13            # callee-restore
  popq %r12            # callee-restore
  popq %rbp            # callee-restore
  popq %rbx            # callee-restore
  ret                  # return


# finish handler at the bottom of the stack which sets the current thread's state to DONE, then calls yield(); 

.globl thread_finish

thread_finish:
	pushq	%rbp
	movq	%rsp, %rbp
.L2:
	movl	$3, 40(%rbp)
	movl	$0, %eax
	call	yield
	jmp	.L2
  # set state to done
  # call yield();
 
