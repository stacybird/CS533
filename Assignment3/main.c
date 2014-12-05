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

void foo(void * arg) {
  char * str = (char*) arg;
  /* do important stuff */
  printf("\nfoo threading works! args: %s\n", str);
}

void test_foo() {
  scheduler_begin();
  thread_fork(foo, (void*)"bar");
  thread_fork(foo, (void*)"baz");
  thread_fork(foo, (void*)"bifur");
  thread_fork(foo, (void*)"bofur");
  thread_fork(foo, (void*)"bombur");
  thread_fork(foo, (void*)"fili");
  thread_fork(foo, (void*)"kili");
  scheduler_end(); 
}

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

void test_read(void * arg) {
  char * str = (char*) arg;
  int filedesc = open(str, O_RDONLY);
  char buffer[20];
  size_t buf_size = 0;
  size_t my_count = 0;
  buf_size = sizeof(buffer);
  my_count = read(filedesc, buffer, buf_size);
//  do {
    printf("%s", buffer);
    printf("*");
    my_count = read(filedesc, buffer, buf_size);
//  } while (my_count != 0);
  printf("\n****    end read of %s\n", str);
  thread_finish();
}

void test_read_wrap(void * arg) {
  char * str = (char*) arg;
  int filedesc = open(str, O_RDONLY);
  char buffer[20];
  size_t buf_size = 0;
  size_t my_count = 0;
  buf_size = sizeof(buffer);
  my_count = read_wrap(filedesc, buffer, buf_size);
  do {
    my_count = read_wrap(filedesc, buffer, buf_size);
    printf("%s", buffer);
    printf("*");
  } while (my_count != 0);
  printf("\n****    end read_wrap of %s\n", str);
  thread_finish();
}

int main(void) {
  scheduler_begin();
  //thread_fork(test_read, (void*)"test.txt");
  thread_fork(test_read_wrap, (void*)"test.txt");
  thread_fork(test_read_wrap, (void*)"test.txt");
  thread_fork(test_read_wrap, (void*)"test.txt");
  scheduler_end();
  return 0;
}

