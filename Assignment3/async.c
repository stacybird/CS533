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
//  off_t offset;
  int status;
  int size = sizeof(buf);
  int bytes_read;

  struct aiocb *aiocbp = malloc(sizeof(struct aiocb)); // allocate structure
  if (aiocbp == NULL) {
    do {
      perror("malloc issue");
      exit(EXIT_FAILURE); 
    } while (0);
  }
  aiocbp->aio_fildes = fd;  // set the file
  if (aiocbp->aio_fildes == -1){
    do { 
      perror("opened on file");
      exit(EXIT_FAILURE); 
    } while (0);
  }
  aiocbp->aio_buf = buf;
  //malloc(size); // allocate for the buffer
  if (aiocbp->aio_buf == NULL) {
    do { 
      perror("malloc issue");
      exit(EXIT_FAILURE); 
    } while (0);
  }
  aiocbp->aio_nbytes = size; // number of bytes to read
  aiocbp->aio_reqprio = 0; // no additional priority set 
  aiocbp->aio_offset = SEEK_CUR;  // offset for the file
  aiocbp->aio_sigevent.sigev_notify = SIGEV_NONE; // correct for polling
  
  status = aio_read(aiocbp);  // start the read
  if (status == -1) {
    do { 
      perror("aio_read issue");
      exit(EXIT_FAILURE); 
    } while (0);
  }
  
  while (status == EINPROGRESS) {
    printf("Async request still going.  \n");
    yield();
    status = aio_error(aiocbp);
  }
  switch (status) {
    case 0:
      printf("I/O succeeded\n");
      bytes_read = aio_return(aiocbp);
      //offset = lseek(fd, size, SEEK_CUR); // set the new offset after the read
      //strcpy(buf, aiocbp->aio_buf);
      break;
    case ECANCELED:
      printf("Canceled\n");
      break;
    default:
      do { 
        perror("aio_error");
        exit(EXIT_FAILURE); 
      } while (0);
      break;
  }

  return bytes_read;
}

/* from read()
       read() attempts to read up to count bytes from file descriptor fd
       into the buffer starting at buf.

       On files that support seeking, the read operation commences at the
       current file offset, and the file offset is incremented by the number
       of bytes read.  If the current file offset is at or past the end of
       file, no bytes are read, and read() returns zero.                    

       On success, the number of bytes read is returned (zero indicates end
       of file), and the file position is advanced by this number.  It is
       not an error if this number is smaller than the number of bytes
       requested; this may happen for example because fewer bytes are
       actually available right now (maybe because we were close to end-of-
       file, or because we are reading from a pipe, or from a terminal), or
       because read() was interrupted by a signal.  On error, -1 is
       returned, and errno is set appropriately.  In this case, it is left
       unspecified whether the file position (if any) changes.             */

