// Stacy Watts
// CS 533 - Fall 2014
// Assignment 3

#include "scheduler.h"
#include <aio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

// Use the AIO interface to create an AIO control block and initiate an 
// appropriate asynchronous read. Yield until the request is complete.
//
// read_wrap should have as close to the semantics of read as possible. That 
// is, it should return the same value that read would have, and put the same 
// result into buf that read would have.
//
// Furthermore, if the file is seekable, read_wrap should start reading from 
// the current position in the file, and then seek to the appropriate position 
// in the file, just as read would have. This is arguably the most difficult 
// part of this assignment, since aio_read does not seek automatically.

ssize_t read_wrap(int fd, void * buf, size_t count) {
      // your code here!
}
