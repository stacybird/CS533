// Stacy Watts
// CS 533 - Fall 2014
// Assignment 2

#include "scheduler.h"
#include <stdio.h>
#include <string.h>

// all tests we create go in this file.  

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

void call_sieve(void * n) {
  int a = (int)n;
  printf("\nFollowing are the prime numbers below %d\n", a);
  SieveOfEratosthenes(a);
  printf("\nnumbers finished below %d\n", a);
}

void test_sieve() {
  scheduler_begin();
  thread_fork(call_sieve, (void*)50000); // this makes scroll back harder for you  :-)
  thread_fork(call_sieve, (void*)10000);
  thread_fork(call_sieve, (void*)1000);
  thread_fork(call_sieve, (void*)15);
  thread_fork(call_sieve, (void*)5);
  scheduler_end();
}


int main(void) {
  test_foo();
  test_sieve();
  return 0;
}

