#include "answer02.h"

int main(int argc, char ** argv) {
  int n ; 
  char * dest = NULL; 
  char * src = "My name is Jun Cheng, and Hello World!";
  strcat_ex(&dest, &n,  src); 
  printf("The src string is:\t \'%s\', \nThe final string is: \t\'%s\' \n ", src, dest); 
  
  const char * z2 = "How did it get so late so soon?";
  char * s1 = NULL;
  strcat_ex(&s1, &n, z2);
  printf("\n n= %d \n", n);
  free(s1); 

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
