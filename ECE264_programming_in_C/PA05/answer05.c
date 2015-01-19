
#ifndef PA05_H
#define PA05_H

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1 
#define FALSE 0

void printArr(int * arr, int len) {
  int ind; 
  printf("= "); 
  for(ind=0; ind < len-1; ind ++) {
    printf("%d + ", arr[ind]); 
  }
  printf("%d\n", arr[len-1]); 
}

void partitionHelper(int value, int * arr, int start) {
  // base case; 
  if(value==0) {
    printArr(arr,start);
  }
  // recursive case; 
  int ind; 
  for (ind=1;  ind <= value; ind++) {
    arr[start] = ind; 
    partitionHelper(value - ind, arr, start+1); 
  }
  
}

void partitionAll(int value) { 
  int * arr = malloc(value * sizeof(int)); 
  partitionHelper(value, arr, 0); 
  free(arr); 
}

void partitionIncreasingHelper(int value, int * arr, int start) {
  // base case; 
  if(value==0) {
    printArr(arr,start);
  }
  // recursive case; 
  int ind; 
  for (ind=1; ind <= value; ind++) {
    arr[start] = ind;
    if(start > 0 && arr[start]<=arr[start-1]) {
      continue; 
    }
    partitionIncreasingHelper(value - ind, arr, start+1); 
   
  }
}

void partitionIncreasing(int value) {
  int * arr = malloc(value * sizeof(int)); 
  partitionIncreasingHelper(value, arr, 0); 
  free(arr); 
}


void partitionDecreasingHelper(int value, int * arr, int start) {
  // base case; 
  if(value==0) {
    printArr(arr,start);
  }
  // recursive case; 
  int ind; 
  for (ind=1; ind <= value; ind++) {
    arr[start] = ind;
    if(start > 0 && arr[start]>=arr[start-1]) {
      continue; 
    }
    partitionDecreasingHelper(value - ind, arr, start+1); 
  }
}

void partitionDecreasing(int value) {
  int * arr = malloc(value * sizeof(int)); 
  partitionDecreasingHelper(value, arr, 0); 
  free(arr); 
}

void partitionOddHelper(int value, int * arr, int start) {
  // base case; 
  if(value==0) {
    printArr(arr,start);
  }
  // recursive case; 
  int ind; 
  for (ind=1; ind <= value; ) {
    arr[start] = ind;
    partitionOddHelper(value - ind, arr, start+1); 
    ind = ind+2; 
  }
}

void partitionOdd(int value) {
  int * arr = malloc(value * sizeof(int)); 
  partitionOddHelper(value, arr, 0); 
  free(arr); 
}

void partitionEvenHelper(int value, int * arr, int start) {
  // base case; 
  if(value==0) {
    printArr(arr,start);
  }
  // recursive case; 
  int ind; 
  for (ind=2; ind <= value; ) {
    arr[start] = ind;
    partitionEvenHelper(value - ind, arr, start+1); 
    ind = ind+2; 
  }
}

void partitionEven(int value) {
  int * arr = malloc(value * sizeof(int)); 
  partitionEvenHelper(value, arr, 0); 
  free(arr); 
}

void partitionOddAndEvenHelper(int value, int * arr, int start) {
  // base case; 
  if(value==0) {
    printArr(arr,start);
  }
  // recursive case; 
  int ind; 
  for (ind=1; ind <= value; ind++ ) {
    arr[start] = ind;
    if (start>0 && (arr[start]+arr[start-1])%2==0) {
      continue; 
    }
    partitionOddAndEvenHelper(value - ind, arr, start+1); 
    
  }
}

void partitionOddAndEven(int value) {
  int * arr = malloc(value * sizeof(int)); 
  partitionOddAndEvenHelper(value, arr, 0); 
  free(arr); 
}


/**
 * Prints all partitions that comprise solely of prime numbers.
 *
 * Example:
 * partitionPrime(5); // prints the following (line order not important)
 * = 2 + 3
 * = 3 + 2
 * = 5
 * 
 * See: note on partitionIncreasing(...)
 * Hint: you will need to write a function that checks if a number is prime.
 * Hint: 1 is not a prime number.
 * Hint: look at file: expected/partitionPrime.output
 */


int isPrime(int value) {
  if(value==1) return FALSE; 
  int i; 
  for(i=2; i<value/2+1; i++) {
    if(value % i == 0) {
      return FALSE; 
    }
  }
  return TRUE; 
}


void partitionPrimeHelper(int value, int * arr, int start) {
  // base case; 
  if(value==0) {
    printArr(arr,start);
  }
  // recursive case; 
  int ind; 
  for (ind=1; ind <= value; ind++ ) {
    arr[start] = ind;
    if (!isPrime(ind)) {
      continue; 
    }
    partitionPrimeHelper(value - ind, arr, start+1); 
    
  }
}

void partitionPrime(int value) {
  int * arr = malloc(value * sizeof(int)); 
  partitionPrimeHelper(value, arr, 0); 
  free(arr); 
}

#endif


