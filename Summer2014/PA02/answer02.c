#define PA02
#include "answer02.h"


char * strcat_ex(char * * dest, int * n, const char * src) {
  int new_n = strlen(*dest) + strlen(src); 
  if(new_n < *n ) {
    return strcat(*dest, src); 
  }
  else {
    char *tmp  = (char*) calloc(1+new_n,sizeof(char)); //1+2*new_n * sizeof(char)); 
    *n = new_n;
    strcpy(tmp,*dest); 
    free(*dest); 
    *dest=tmp;     
    return strcat(*dest, src); 
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

  for(int Ind=0; Ind < strlen(str); Ind++){
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
  for(int i=0; i<len-1; i++) {
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
  for(int i=0; i<len; i++) {
    free(strArr[i]); 
  }
  free(strArr); 

}


char *strdup (const char *s) {
  char *d = malloc (strlen (s) + 1);   // Space for length plus nul
  if (d == NULL) return NULL;          // No memory
  strcpy (d,s);                        // Copy the characters
  return d;                            // Return the new string
}

#ifndef PA02

int main(int argc, char ** argv) {
  int n=4 ; 
  char * dest = calloc(n,sizeof(char)); 
  strcpy(dest, "Ha "); 

  char * src = "My name is Jun Cheng, and Hello World!";
  strcat_ex(&dest, &n,  src); 
  //printf("The src string is:\t \'%s\', \nThe final string is: \t\'%s\' \n ", src, dest); 
  
  char * delims=" "; 
  //printf("\nTest for explode\n"); 
  int arrLen; 
  char **strList =  explode(src, delims, &arrLen);
  char *str = implode(strList, arrLen, ",");
  //printf("The concated string is: '%s' \n", str);
  //printf("\nTesting string sorting: \n"); 
  int len;
  
  char *s= dest; 
  char * * strArr = explode(dest, " ", &len);

  sortStringArray(strArr, len);
  char * new_str = implode(strArr, len, "_");
  printf("Original string: '%s' \nNew String: '%s'\n", s, new_str); // beatle brew lady
 
  char * s2 = strdup("How did it get so late so soon?");
  sortStringCharacters(s2); 
  printf("\nOriginal string: '%s' \nNew String: '%s'\n", s2, s2); 

  free(s2); 
  free(str); 
  free(dest);
  free(new_str); 
  destroyStringArray(strList,arrLen); 
  destroyStringArray(strArr,len); 

  return EXIT_SUCCESS; 

}


#endif
