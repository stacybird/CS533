// Stacy Watts
// CS 533 - Fall 2014
// Assignment 3

#include "scheduler.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// all tests we create go in this file.  

ssize_t read_wrap(int fd, void * buf, size_t count);


// http://www.geeksforgeeks.org/sieve-of-eratosthenes/
// marks all mutiples of 'a' ( greater than 'a' but less than equal to 'n') as 1.
void markMultiples(int arr[], int a, int n) {
  int i = 2, num;
  while ( (num = i*a) <= n ) {
    arr[ num-1 ] = 1; // minus 1 because index starts from 0.
    ++i;
  }
}

// http://www.geeksforgeeks.org/sieve-of-eratosthenes/
// A function to print all prime numbers smaller than n
void SieveOfEratosthenes(int n) {
  if (n >= 2) {  // There are no prime numbers smaller than 2
    // Create an array of size n and initialize all elements as 0
    int arr[n];
    memset(arr, 0, sizeof(arr));
    /* Following property is maintained in the below for loop
       arr[i] == 0 means i + 1 is prime
       arr[i] == 1 means i + 1 is not prime */
    int i;
    for (i=1; i<n; ++i) {
      if ( arr[i] == 0 ) {  //(i+1) is prime, print it and mark its multiples
        printf("%d ", i+1);
        markMultiples(arr, i+1, n);
      }
      if (i%100 == 0) {
        printf("     yield! n=%d", n);
        yield();
        printf("\ncontinue! n=%d   ", n);
      }
    }
  }
}

void call_sieve(int n) {
  printf("\nFollowing are the prime numbers below %d\n", n);
  SieveOfEratosthenes(n);
  printf("\nnumbers finished below %d\n", n);
}

void test_sieve() {
  thread_fork(call_sieve, (void*)100000); // this makes scroll back harder for you  :-)
  thread_fork(call_sieve, (void*)10000);
  thread_fork(call_sieve, (void*)1000);
  thread_fork(call_sieve, (void*)15);
  thread_fork(call_sieve, (void*)5);
}



// just for the sake of checking input with a regular file is the same.
void test_read(void * arg) {
  char * str = (char*) arg;
  int filedesc = open(str, O_RDONLY);
  char buffer[20];
  ssize_t buf_size = 0;
  ssize_t my_count = 0;
  buf_size = sizeof(buffer);
  my_count = read(filedesc, buffer, buf_size);
  do {
    printf("%s", buffer);
    my_count = read(filedesc, buffer, buf_size);
  } while (my_count != 0);
  printf("\n****    end read of %s\n", str);
  thread_finish();
}


void test_read_wrap_file(void * arg) {
  char * str = (char*) arg;
  int filedesc = open(str, O_RDONLY);
  char buffer[20];
  ssize_t buf_size = 0;
  ssize_t my_count = 0;
  buf_size = sizeof(buffer);
  my_count = read_wrap(filedesc, buffer, buf_size);
  do {
    printf("%s", buffer);
    my_count = read_wrap(filedesc, buffer, buf_size);
  } while (my_count != 0);
  printf("\n****    end read_wrap of %s\n", str);
  thread_finish();
}


void test_read_wrap_stdin(void * arg) {
  printf("Waiting for stdin:\n");
  char buf[2];
  read_wrap(0, buf, 2);
  printf("Test complete, input: %s\n", buf);
} 

int main(void) {
  scheduler_begin();
//  thread_fork(test_read, (void*)"test.txt");
  thread_fork(test_read_wrap_stdin, (void*)"0");
  thread_fork(test_read_wrap_stdin, (void*)"0");
  test_sieve();
  thread_fork(test_read_wrap_file, (void*)"test.txt");
  scheduler_end();
  return 0;
}

