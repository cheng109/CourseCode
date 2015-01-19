
#include "answer07.h"
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define BUFFLEN 8000

// -------------------------------------------------------------------- HuffNode

HuffNode * HuffNode_create(int value) {

  HuffNode * node = malloc(sizeof(HuffNode)); 
  node->value = value; 
  node->left = NULL; 
  node->right = NULL; 
  return node; 
}

void HuffNode_destroy(HuffNode * tree) {
  if(tree==NULL) 
    return; 
  else {
    HuffNode_destroy(tree->left); 
    HuffNode_destroy(tree->right); 
    free(tree); 
  }
}

Stack * Stack_create() {
  Stack * stack = (Stack *) malloc(1*sizeof(Stack *)); 
  stack->head = NULL; 
  return stack; 
}

void Stack_destroy(Stack * stack) {
  if(Stack_isEmpty(stack)) {
    printf("The stack is NULL, no need to destroy!\n"); 
  }
  StackNode * iter = stack->head;
  while(iter!=NULL) {
    StackNode * next = iter->next;
    HuffNode_destroy(iter->tree);
    free(iter); 
    iter = next;
  }
  free(stack);
}

int Stack_isEmpty(Stack * stack) {
  if(stack->head==NULL) 
    return TRUE; 
  else 
    return FALSE; 
}

HuffNode * Stack_popFront(Stack * stack) {
  if(Stack_isEmpty(stack)) {
    printf("Error: the stack is empty, can't popFront. \n"); 
  }
  StackNode * tempStack = stack->head; 
  HuffNode * tempHuff = tempStack->tree; 
  stack->head = stack->head->next; 
  free(tempStack);  
  return tempHuff; 
}

void Stack_pushFront(Stack * stack, HuffNode * tree) {
  StackNode * newNode = malloc(1*sizeof(StackNode)); 
  if(Stack_isEmpty(stack)){
    newNode->next = NULL; 
  }
  else {
    newNode->next = stack->head; 
  }
  newNode->tree = tree; 
  stack->head = newNode; 
}

void print_HuffNode(HuffNode * tree) {
  // Post-order
  if (tree==NULL) 
    return; 
  print_HuffNode(tree->left); 
  print_HuffNode(tree->right); 
  printf(" '%c' ",tree->value); 
}

void print_Stack(Stack * stack) {
  StackNode * iter = stack->head; 
  while(iter) {
    print_HuffNode(iter->tree); 
    iter = iter->next; 
  }
  printf("\n"); 
}

int stackNode_number (Stack * stack) {
  int num=0; 
  StackNode* iter = stack->head; 
  while(iter!=NULL) {
    num++; 
    iter = iter->next; 
  }
  return num; 
}

void Stack_popPopCombinePush(Stack * stack) {
  HuffNode * right = Stack_popFront(stack); 
  HuffNode * left = Stack_popFront(stack); 
  HuffNode * newTree = HuffNode_create((int)'^'); 
  newTree->right = right; 
  newTree->left = left; 
  Stack_pushFront(stack,newTree); 
}

HuffNode * HuffTree_readTextHeader(FILE * fp){
  if(fp==NULL) {
    printf("Error opening file\n");
    return NULL; 
  }
  Stack * stack= Stack_create(); 
  int C, nextC; 
  HuffNode * tree = NULL; 
  do { 
    C = fgetc(fp); 
    if(C=='1') {
      nextC = fgetc(fp); 
      tree = HuffNode_create(nextC); 
      Stack_pushFront(stack, tree); 
    }
    else if (C=='0') {
      if(stackNode_number(stack)==1)
	break; 
      Stack_popPopCombinePush(stack); 
    }
  } while(fp!=NULL); 
  HuffNode * node = stack->head->tree; 
  stack->head->tree = NULL; 
  Stack_destroy(stack); 
  return node; 
}


void print_array(int * array, int len) {
  int ind; 
  printf("\n"); 
  for(ind=0; ind < len; ind++) {
    printf("%d", array[ind]); 
    if(ind%4==3) printf(" "); 
    if(ind%128==127) printf("\n"); 
  }
  printf("\n"); 

}

unsigned char readoutByte(int * pos, int * array) {
  char val = '\0'; 
  int ind;
  for(ind= *pos; ind< (*pos+8); ind++) {
    val = val | (array[ind] <<(7+*pos-ind)); 
  }
  *pos = *pos +8; 
  return val; 
}

void readinBit(FILE * fp, int * buffer) {  
  if(fp==NULL) {
    printf("Error opening file\n");
    return ; 
  }
  int bit_offset = -1;
  unsigned char byte; 
  int write_pos=0; 
  while(!feof(fp)) {
    if(bit_offset < 0) {
      byte = fgetc(fp); 
      if(feof(fp)) {
	break;
      }
      bit_offset = 7;
    }    
    int bit = (byte >> bit_offset) & 0x01;
    bit_offset--; 
    buffer[write_pos] = bit; 
    write_pos ++; 
  }
  print_array(buffer, write_pos); 
  if(buffer[0]!=1) 
    printf("Error: file does not start with '1' \n"); 
}

HuffNode * HuffTree_readBinaryHeader(FILE * fp) {
  int buffer[BUFFLEN]; 
  readinBit(fp, buffer); 
  
  Stack * stack= Stack_create();
  int C, nextC;
  HuffNode * tree = NULL;
  int pos = 0;
  while(TRUE) {
    C = buffer[pos];
    pos = pos+1; 
    if(C==1) {
      nextC =(int) readoutByte(&pos, buffer) ;
      tree = HuffNode_create(nextC);
      Stack_pushFront(stack, tree);
    }
    else if (C==0) {
      if(stackNode_number(stack)==1)
  	break;
      Stack_popPopCombinePush(stack);
    }
  } 

  HuffNode * node = stack->head->tree;
  stack->head->tree = NULL;
  Stack_destroy(stack);
  return node;

}

int main (int argc, char ** argv) {

  FILE * fp2 = fopen("inputs/12-stone.bit-huff", "r"); 
  HuffNode * tree2 =HuffTree_readBinaryHeader(fp2);

  print_HuffNode(tree2);
  printf("\n");
  //  Stack_destroy(stack);
  HuffNode_destroy(tree2);
  fclose(fp2); 
  return EXIT_SUCCESS;
}
