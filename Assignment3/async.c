// Stacy Watts
// CS 533 - Fall 2014
// Assignment 3

#include "scheduler.h"
#include <aio.h>       // For struct aiocb, aio_read, aio_error, aio_return
#include <errno.h>     // For EINPROGRESS
#include <unistd.h>    // For lseek, SEEK_CUR, SEEK_END, SEEK_SET
#include <string.h>    // For memset

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
  struct aiocb *aiocbp;
//  aiocbp->aio_fildes = open(fd, O_RDONLY);
  if (aiocbp->aio_fildes == -1)
//    errExit("open");
//  printf("opened on descriptor %d\n", aiocbp->aio_fildes);
  aio_read(aiocbp);
  return 0;
}

/* from read()
       read() attempts to read up to count bytes from file descriptor fd
       into the buffer starting at buf.

       On files that support seeking, the read operation commences at the
       current file offset, and the file offset is incremented by the number
       of bytes read.  If the current file offset is at or past the end of
       file, no bytes are read, and read() returns zero.                    */

