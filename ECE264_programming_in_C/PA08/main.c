#include "answer08.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * * argv)
{
  const char * str = "34050958923936410041";
  uint128 w = alphaTou128(str);
  char * w_str = u128ToString(w);
  printf("Biiigggg number: %s\n", w_str);
  if(strcmp(str, w_str) != 0)
    printf("ERROR!, expected %s\n", str);

  //int result;                                                                                                                                                                                              
  primalityTestParallel(w, 4);
  //printf("The number #%s is prime number: %s \n", u129ToString(w), (result==1)?"TRUE":"FALSE");                                                                                                            
  free(w_str);
  return EXIT_SUCCESS;


}
