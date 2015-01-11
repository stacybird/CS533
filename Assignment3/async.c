// Stacy Watts
// CS 533 - Fall 2014
// Assignment 3

#include "scheduler.h"
#include <stdlib.h>
#include <stdio.h>
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
  off_t offset;
  int status = 0;
  int bytes_read = 0;

  struct aiocb *aiocbp = malloc(sizeof(struct aiocb)); // allocate structure
  if (aiocbp == NULL) {
    return -1; // malloc issue
  }
  memset(aiocbp, 0, sizeof(struct aiocb)); // zero out control block
  memset(buf, 0, count); // zero out buffer before using
  aiocbp->aio_fildes = fd;  // set the file
  if (aiocbp->aio_fildes == -1){
    errno = EBADF;
    return -1;
  }
  aiocbp->aio_buf = buf;
  aiocbp->aio_nbytes = count; // number of bytes to read
  aiocbp->aio_reqprio = 0; // no additional priority set 
  if ((0 == fd) || (1 == fd) || (2 == fd)) { 
    aiocbp->aio_offset = 0; // seek would be invalid for stdin, stdout, stderr.
  }
  else {
    aiocbp->aio_offset = lseek(fd, 0, SEEK_CUR);  // offset for the file
  }
  aiocbp->aio_sigevent.sigev_notify = SIGEV_NONE; // correct for polling
  status = aio_read(aiocbp);  // start the read
  if (status == -1) {
    return -1;
  }
  while (aio_error(aiocbp) == EINPROGRESS) {
    yield();
    status = aio_error(aiocbp);
  }
  switch (status) {
    case 0:
      bytes_read = aio_return(aiocbp);
      if (!(0 == fd) || (1 == fd) || (2 == fd)) { // do seek only if not stdin 
        offset = lseek(fd, bytes_read, SEEK_CUR); // set the new offset
        if (-1 == offset) {
          offset = lseek(fd, bytes_read, SEEK_CUR); // on fail, try again.
        }
      }
      break;
    case ECANCELED:
      errno = EINTR;
      break;
    default:
      errno = EIO;
      break;
  }

  return bytes_read;
}

