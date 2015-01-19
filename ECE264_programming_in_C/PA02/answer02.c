#include "answer02.h"
#include <string.h>

char *strdup (const char *s) {
  char *d = malloc (strlen (s) + 1);   // Space for length plus nul
  if (d == NULL) return NULL;          // No memory
  strcpy (d,s);                        // Copy the characters
  return d;                            // Return the new string
}

char * strcat_ex(char * * dest, int * n, const char * src) {
  int new_n; 
  char * tmp; 
  if(*dest!=NULL) {
    new_n = 1+2*(strlen(*dest) + strlen(src));
    if(new_n < *n) {
      return strcat(*dest, src); 
    }
    else{
      tmp  = (char*) calloc(new_n,sizeof(char)); //1+2*new_n * sizeof(char)); 
      *n = new_n;
      strcpy(tmp,*dest); 
      free(*dest); 
      *dest=tmp;     
    return strcat(*dest, src);  
    }
  }

  else {
    *n = 1+2*strlen(src);
    tmp  = (char*) calloc(*n,sizeof(char)); //1+2*new_n * sizeof(char)); 
    strcpy(tmp, src);
    *dest = tmp;
    return *dest; 
  }

}

int num_found(const char * str, const char * delims) {
  int counter =0; 
  while(*str) {
    if(strchr(delims, *str)) {
      counter ++; 
    }
    str++; 
  }
  return counter; 
}

char * * explode(const char * str, const char * delims, int * arrLen){
  int N = num_found(str, delims); 
  char ** strList =(char**) calloc((N+1),sizeof(char *)); 
  int arrInd=0; 
  int last=-1;
  *arrLen = N+1; 
  int length = 0; 
  int Ind;

  for(Ind=0; Ind < strlen(str); Ind++){
    if(strchr(delims,str[Ind])!=NULL) {
      length = Ind-last-1; 
      strList[arrInd] =(char*) calloc(1+length,sizeof(char)); 
      memcpy(strList[arrInd], str+last+1, length*sizeof(char));
      last=Ind; 
      arrInd++; 
    }
  }
  int final = strlen(str)-last-1;
  strList[arrInd] =(char*) calloc(1+final,sizeof(char)); 
  strcpy(strList[arrInd], str+last+1);
  
  return strList;
}

char * implode(char * * strArr, int len, const char * glue) {
  char *str=calloc(1,sizeof(char)); 
  int n=0; 
  int i; 
  for(i=0; i<len-1; i++) {
    strcat_ex(&str,&n, strArr[i]);
    strcat_ex(&str,&n, glue); 
  }  
  strcat_ex(&str, &n, strArr[len-1]);
  return str; 

}

int compare(const void *a, const void *b) {
  char* ap = (char*)a; 
  char* bp = (char*)b; 
  return *ap-*bp; 
}

int compare2(const void *a, const void *b) {
  char** ap = (char**) a; 
  char** bp = (char**) b; 
  return strcmp(*ap,  *bp); 
}

void sortStringArray(char * * arrString, int len) {
  qsort(arrString,len, sizeof(char*), compare2); 
}

void sortStringCharacters(char * str) {
  qsort(str, strlen(str), sizeof(char), compare); 
}

void destroyStringArray(char * * strArr, int len) {
  int i; 
  for(i=0; i<len; i++) {
    free(strArr[i]); 
  }
  free(strArr); 
}
