#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define LINE_MAX 2000


int main (int argc, char ** argv) {
  int showHelp=FALSE; 
  int lineNumber=FALSE;
  int invertMatch=FALSE;
  int quietSuppress=FALSE; 
  //int badSwitch=FALSE; 
  char pattern[LINE_MAX]; 
  char line[LINE_MAX]; 
  int num=0; 
  int i;

  if(argc>1) {
    if(argv[argc-1][0]=='-')  {
      fprintf(stderr,"Error message: Final argument should be PATTERN\n"); 
      return EXIT_FAILURE; 
    }
    else strcpy(pattern, argv[argc-1]); 
  }

  for(i=1; i<argc; i++) {
    if(argv[i][0]=='-') {
      if(strcmp(argv[i],"--help")==0) 
	showHelp=TRUE;
      else if(strcmp(argv[i],"-v")==0 || strcmp(argv[i],"--invert-match")==0) 
	invertMatch=TRUE; 
      else if(strcmp(argv[i],"-n")==0 || strcmp(argv[i],"--line-number")==0) 
	lineNumber=TRUE; 
      else if(strcmp(argv[i],"-q")==0 || strcmp(argv[i],"--quiet")==0) 
	quietSuppress=TRUE; 
      else {
	//badSwitch=TRUE; 
	fprintf(stderr, "Unknown switch:'%s'\n", argv[i]); 
	return 2;
      }
    }
  }

  if(showHelp==TRUE) {
    printf("Usage: grep-lite [OPTION]... PATTERN\n"
	   "Search for PATTERN in standard input. PATTERN is a string.\n"
	   "grep-lite will search standard inpt line by line, and (by default) print out those lines which contain pattern as a substring.\n"
	   "\n"
	   "-v, --invert-match\t print non-matching lines\n"
	   "-n, --line-numer\t print line numbers with output\n"
	   "-q, --quiet\t\t suppress all output\n"
	   "\n"
	   "Exit status is 0 if any line is selected, 1 otherwise;\n"
	   "if any error occurs, then the exit status is 2.\n"); 
    return EXIT_SUCCESS; 
  }

         // search for patterns. 
  while(fgets(line, LINE_MAX, stdin)!=NULL) {
    num++;
    if(quietSuppress==TRUE) break;
    else if((strstr(line, pattern)!=NULL && invertMatch==FALSE) 	 
       ||(strstr(line, pattern)==NULL && invertMatch==TRUE))  {	  
      if(lineNumber==TRUE) {
	printf("%d:", num);
      }
      printf("%s", line); 
    }
  }
  return EXIT_SUCCESS; 
}
