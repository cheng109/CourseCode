//typedef __uint128_t uint128;
/* #define MAX(X,Y) ((X) > (Y) ? (X) : (Y)) */

#include <stdio.h>
#include "answer08.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

#define TURE 1
#define FALSE 0
#define BUFFER_MAX 100

typedef struct {
  uint128 start; 
  uint128 end; 
  uint128 value; 
  int * factorFound; 
} block; 

int isSpace(char c) {
  if(c!=' ' && c!=',' && c>='0' && c<='9')
    return FALSE; 
  return TRUE; 
}

uint128 alphaTou128(const char * str) {
  uint128 k = 0;
  int i=0; 
  if (str[0]=='-') return 0; 
  while(str[i]!='\0') {
    if(!isSpace(str[i]))
      k = k*10 + (str[i]-'0');
    i ++; 
  }
  return k; 
}

void swapChar ( char * a, char * b) {
  char temp = *a ; 
  *a = *b; 
  *b = temp; 
}

char * swapStr(char * str, int len) {
  int ind; 
  for(ind=0; ind<len/2; ind++) {
    swapChar(&str[ind], &str[len-ind-1]); 
  }
  return str; 
}

char * u128ToString(uint128 value){
  char * str = malloc(BUFFER_MAX * sizeof(char)); 
  int start_pos=0; 
  str[start_pos] = '\0'; 
  int ind = start_pos+1;  
  int res;
  while(TRUE) {
    res = value%10;
    value = value/10;
    str[ind] = (char) (res + '0');  
    ind ++;
    if(value!=0)
      continue; 
    break; 
  }
  swapStr(str,ind); 
  return str; 
}


block * block_create(uint128 start, uint128 end, uint128 value, int * found) {
  block * b = malloc(sizeof(block)); 
  b->start = start; 
  b->end = end; 
  b->value = value; 
  b->factorFound = found; 
  return b; 
}

void print_block(block * b) {
  printf("'%s', [%s, %s] \n", u128ToString(b->value), u128ToString(b->start), u128ToString(b->end)); 
}              

void * is_Prime(void * testBlock) {
  block * b = (block*) testBlock; 
  uint128 ind; 
  if(b->value==2) {
    *(b->factorFound) = FALSE; 
    pthread_exit(0); 
  }  
  if(b->value%2==0) {
    *(b->factorFound) = TRUE; 
    pthread_exit(0); 
  }
  uint128 start = (b->start%2==0) ? b->start+1 : b->start; 
  uint128 end = (b->end%2==0) ? b->end+1 : b->end; 
  for(ind=start; ind<= end; ) {
    if(b->value != ind && b->value%ind==0)  {
      *(b->factorFound) = TRUE; 
      pthread_exit(0); 
    }
    ind = ind+2; 
  }
  pthread_exit(0); 
}
  
int primalityTestParallel(uint128 value, int n_threads) {
  pthread_t * th = malloc(sizeof(pthread_t)*n_threads); 
  int factorFound = FALSE; 
  int i, created; 
  block ** b = malloc (sizeof(block*) * n_threads); 

  // Create thread; 
  uint128 max= floor(sqrt(value)*1.1); 
  uint128 interval = (max-1)/n_threads; 
  for(i=0; i<n_threads; i++) {
    uint128 start =ceil ( 2+i*interval    ) ; 
    uint128  end =  floor( 2+(i+1)*interval); 
    b[i] = block_create(start, end, value, &factorFound); 
    if((created= pthread_create(&th[i],	NULL,(void * (*) (void*)) is_Prime,(void*) b[i]))) {
      fprintf(stderr, "Failed to create thread %d, ", i); 
      return 1; 
    }
  }

  for(i=0; i<n_threads; i++)
    pthread_join(th[i], NULL);
  free(th);
  for(i=0; i<n_threads; i++) {
    free(b[i]); 
  }
  free(b); 

  if(factorFound==TRUE) {
    /* char * u = u128ToString(value);  */
    /* printf("This number #%s is NOT a prime.  \n", u);  */
    /* free(u);  */
    return FALSE; 
  }
  /* char * u = u128ToString(value);  */

  /* printf("This number #%s is a PRIME. \n", u);  */
  /* free(u);  */
  return TRUE; 
}

