#include "answer01.h"

// NOTE: You are NOT to use the strings library on this assignment,
// as stated in the README.

// DO NOT BEGIN WORKING ON THIS FILE UNTIL YOU HAVE COMPLETELY AND
// THOROUGHLY READ THE README FILE!!!

int arraySum(int * array, int len)
{
  int sum=0;
  int i; 
  for(i=0; i<len; i++) {
    sum+=array[i];
  }
  return sum;
}

int arrayCountNegative(int * array, int len)
{
  int count=0;
  int i; 
  for(i=0; i<len; i++) {
    if(array[i]<0) {
      count++;
    }
  }
  return count;
}

int arrayIsIncreasing(int * array, int len)
{    
  int smallest = array[0];
  int i; 
  for(i=0; i<len; i++) {
    if(array[i]>smallest) {
      smallest = array[i];
    }
    if(array[i]<= smallest) {
      return 0;
    }
  }
  return 1;
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
  int index=0;
  int found=0;
  int i; 
  for(i=0; i<len; i++) {
    if(needle==haystack[i]) {
      index = i ;
      found = 1 ; 
    }
  }
  if(found==1) {
    return index;
  }
  else
    return -1;
}

int arrayFindSmallest(int * array, int len)
{
  if(len==0) return 0;
  int smallest = array[0]; 
  int index =0;
  int i; 
  for (i=0; i<len; i++) {
    if(array[i]<smallest) {
      smallest = array[i] ;
      index = i; 
    }
  }
 return index;
}

size_t my_strlen(const char * str)
{
  size_t len=0; 
  while(*(str++)) len++;  
  return len;
}

char * my_strchr(const char * str, int ch)
{
  do { 
    if(*str==ch) return (char *)str;
  }
  while(*(str++)); 
  return NULL; 
}

char * my_strstr(const char * haystack, const char * needle)
{
  int found=0;
  //printf("s=%s \n", needle);
  /* if((*needle)==0) return (char*) haystack; */
  char * temp = needle; 
  while (*haystack) {
    temp = needle; 
    if (*haystack==*temp) {
      while(*temp) {
	temp++; 
	haystack++;
	if(*temp==*haystack) continue;
	else break;
      }
      if(*temp=NULL) return needle;
      
    }
    haystack++;
  }   
  return NULL;
}

char * my_strcpy(char * dest, const char * src)
{
  int i = 0; 
  while(*src) {
    dest[i] = *src; 
    i++; 
    src++; 
  }
  dest[i]='\0';
  return dest;
}

char * my_strcat(char * dest, const char * src)
{
  int len=0; 
  int i=0;
  while(1) {
    if(*dest==NULL) {
      while(*src) {
	dest[len+i]=*src;
	src++; 
	i++;
      }
      break;
    }
    len++; 
    dest++; 
    
  }
  dest[i]='\0'; 
  return dest;
}
 
int my_isspace(int ch)
{
  if(ch==' ' || ch=='\t' || ch=='\n' || ch=='\f' || ch =='\r' || ch=='v')
    return 1;
  else
    return 0;
}

int my_atoi(const char * str)
{
    return -1;
}

