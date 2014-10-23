// definitions of our scheduler API functions.

#include "scheduler.h"
#include "queue.h"

struct thread_t current_thread;
struct thread_t stored_thread;

void yield() {
 struct thread_t temp = current_thread;
 current_thread = stored_thread;
 stored_thread = temp;
 thread_switch(&stored_thread, &current_thread);
}

