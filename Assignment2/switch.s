# Stacy Watts
# CS 533 - Fall 2014
# Assignment 2

.globl thread_start

# 4. First, we'll need to make some slight modifications to our 
#    thread_start assembly routine. Above, in the overview section, we 
#    discussed how we might solve the problem of allowing a thread to 
#    terminate gracefully.
#    Implement the thread_finish function accordingly, then modify your 
#    thread_start routine to push the address of thread_finish on the 
#    bottom of the new thread's stack. This can be accomplished with 
#    the instruction:    
#               pushq $thread_finish
#    We'll also want to pass our initial argument to the target function. #    Once you're done with %rdi, you can overwrite it with the value of 
#    the initial argument.
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

