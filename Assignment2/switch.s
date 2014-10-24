# Stacy Watts
# CS 533 - Fall 2014
# Assignment 2

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

