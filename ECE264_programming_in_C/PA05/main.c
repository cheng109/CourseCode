#include "answer05.h"
#include <stdio.h>

int isPrime(int value); 
int main(int argc, char ** argv) {
  //partitionAll(5);  
  //partitionIncreasing(5);  
  // partitionDecreasing(5);  
  //partitionOdd(5);  
  //partitionEven(6);  
  //partitionOddAndEven(5);  
  partitionPrime(5);  
  // printOut all the prime numbers; 
  int ind=2; 
  for (ind=2; ind<500; ind++) {
    if(isPrime(ind)) {
      printf("%d, ", ind); 
    }
  }
  printf("\n"); 
  return 0; 

}

