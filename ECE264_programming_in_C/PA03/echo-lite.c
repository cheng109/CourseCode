#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv) {
  int i; 
  if(argc==1){
    printf("\n"); 
    return EXIT_SUCCESS;
  }
  else {
    for(i=1; i<argc; i++) {
      printf("%s ", argv[i]); 
    }
    printf("\n");
    return EXIT_SUCCESS; 
  }
}
