#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define LINE_MAX 10000 

int main(int argc, char ** argv) {
  int i;
  
  FILE *outFile; 
  char line[LINE_MAX]; 
  if(argc==1) {
    while(fgets(line, LINE_MAX, stdin)!=NULL) 
      printf("%s", line); 
  }

  for(i=1; i<argc; i++) {
    if(strcmp(argv[i],"--help")==0) {
      printf("Usage: cat-lite [--help] [FILE]...\n"
	     "With no FILE, or when FILE is -, read standard input.\n\n"
	     "Examples:\n"
	     "  cat-lite README   Print the file README to standard output.\n"
	     "  cat-lite f - g    Print f's contents, then standard input, \n"
	     "                    then g's contents.\n"
	     "  cat-lite          Copy standard input to standard input.\n");
      return EXIT_SUCCESS; 
    }

    if(strcmp(argv[i],"-")==0) {
      while(fgets(line, LINE_MAX, stdin)!=NULL) 
	printf("%s", line); 

    }
    else {
      outFile = fopen(argv[i], "r"); 
      if(outFile==NULL) 
	fprintf(stderr, "cat cannot open %s\n", argv[i]); 
      else {
	while(fgets(line, LINE_MAX, outFile)!=NULL) 
	  printf("%s",line);
	fclose(outFile); 
      }
      
    }
        
  }
  return EXIT_SUCCESS;

}
