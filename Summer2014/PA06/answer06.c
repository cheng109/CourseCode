#include <stdlib.h>
#include <stdio.h>
#include "answer06.h"




void print_tree(SparseNode * root) ; 

SparseNode * SparseNode_create(int index, int value) {
  SparseNode * node = (SparseNode*) malloc(1*sizeof(SparseNode));    
  node->index = index; 
  node->value = value; 
  node->left = NULL; 
  node->right = NULL; 
  return node; 
}

SparseNode * SparseArray_insert(SparseNode * array, int index, int value) {
  // Base case;
  if(value==0) 
    return array; 
  if( array==NULL) {
    return SparseNode_create(index, value);
  }
  // recursive case;
  if(index == array->index) {
    array->value = value; 
    return array; 
  }

  if(index < array->index)
    array->left = SparseArray_insert(array->left, index, value);
  if(index > array->index)
    array->right = SparseArray_insert(array->right, index, value);

  return array;
}


SparseNode * SparseArray_add_node(SparseNode * array, int index, int value) {
  // Base case;
  if(value==0) 
    return array; 
  if( array==NULL) {
    return SparseNode_create(index, value);
  }
  // recursive case;
  if(index == array->index) {
    array->value = value + array->value;
    if(array->value==0) 
      return SparseArray_remove(array, index); 
    else 
      return array; 
  }

  if(index < array->index)
    array->left = SparseArray_add_node(array->left, index, value);
  if(index > array->index)
    array->right = SparseArray_add_node(array->right, index, value);

  return array;
}


SparseNode * SparseArray_build(int * indices, int * values, int length) {
  SparseNode * root = NULL; 
  int ind; 
  for(ind=0; ind<length; ind++) {
    if(values[ind]==0) 
      continue; 
    else
      root = SparseArray_insert(root, indices[ind], values[ind]); 
  }
  return root; 
}

void SparseArray_destroy(SparseNode * array) {
  // Base case; 
  if (array == NULL)  
    return; 

  // Recursive case; 
  SparseArray_destroy(array->left); 
  SparseArray_destroy(array->right);
  free(array); 
  return;
}

int SparseArray_getMin(SparseNode * array) { 
  // Always go left; 
  if(array->left==NULL) 
    return array->index; 
  return SparseArray_getMin(array->left); 
}

int SparseArray_getMax(SparseNode * array) { 
  // Always go right; 
  if(array->right==NULL) 
    return array->index; 
  return SparseArray_getMax(array->right); 
}

SparseNode * SparseArray_getNode(SparseNode * array, int index) {
  // Error Case; 
  if(array == NULL) {
    printf("The index is not found. \n"); 
    return NULL; 
  }
  // Base case; 
  else if(index == array->index) 
    return array; 

  // Recursive case; 
  else if(index < array->index) 
    return SparseArray_getNode(array->left, index); 
  //else if(index > array->index) 
  else 
    return SparseArray_getNode(array->right, index); 
  
}

void index_swap(SparseNode * A, SparseNode * B) {
  //SparseNode * temp = SparseArray_create((*A)->index,(*A)->value); 
  int temp_index = A->index; 
  int temp_value = A->value; 
  
  A->index = B->index; 
  A->value = B->value; 
  
  B->index = temp_index; 
  B->value = temp_value; 
}



SparseNode * SparseArray_remove(SparseNode * node, int index) { 
  //  SparseNode * node = SparseArray_getNode(array, index); 
  //SparseNode * temp; 
  SparseNode * temp =NULL; 
  SparseNode * temp2 =NULL; 
  if(node == NULL) {
    printf("The index is not found. \n");
    return NULL;
  }
  if(node->index==index) {
    if(node->left==NULL && node->right==NULL) {
      free(node);
      return NULL; 
    }
    else if(node->left==NULL && node->right!=NULL) {
      temp = node->right; 
      free(node); 
      return temp; 
    }
    else if(node->right==NULL && node->left!=NULL) {
      temp = node->left; 
      free(node); 
      return temp;
    }
  
    else if(node->right!=NULL && node->left!=NULL) {
      temp = node->right; 
      temp2 = node;
      int ind=0; 
      while(temp->left!=NULL) {
	temp2 = temp; 
	temp = temp->left; 
	ind =1; 
      }
      index_swap(node, temp);
      if(ind==0)     temp2->right = temp->right; 
      if(ind==1)     temp2->left = temp->right; 
      
      free(temp); 
      return node; 
    }
  }
  else if(index < node->index) {
    node->left = SparseArray_remove(node->left, index);
  }
  else if(index > node->index) {
    node->right =  SparseArray_remove(node->right, index);
  } 
  return node; 
}


SparseNode * SparseArray_copy(SparseNode * array) {
  
  if(array==NULL) 
    return NULL; 

  // Recursive case; 
  SparseNode * root = SparseNode_create(array->index, array->value); 
  root->left  = array->left;
  root->left  = SparseArray_copy(root->left);
  root->right = array->right; 
  root->right = SparseArray_copy(root->right); 

  return root; 

}

void array_insert(SparseNode * array_1, SparseNode * array_2 ) {
  // Base case;
  if (array_2==NULL)
    return; 

  // Recursive case; 
  array_insert(array_1, array_2->left);
  SparseArray_add_node(array_1, array_2->index, array_2->value); 
  array_insert(array_1, array_2->right);
}

SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2) {
 
  SparseNode *merge = SparseArray_copy(array_1); 
  array_insert(merge, array_2); 
  return merge; 

}

void print_tree(SparseNode * root) {
  
  // base case; 
  if (root == NULL)
    return;

  // recursive case;
  print_tree(root->left); 
  printf("[%d, %d],", root->index, root->value); 
  print_tree(root->right); 
  
}


int SparseNode_check(SparseNode * node)
{
  // Check the above conditions here.
  // return FALSE if the node is invalid, or if there is an
  // invalid child node.
  if (node == NULL)
    return 1;
  

  // recursive case; 

  return SparseNode_check(node->left) 
    && SparseNode_check(node->right) 
    && node->left->index < node->index 
    && node->index < node->right->index; 
}

// store the binary tree in an array in PREORDER. 
void preOrder(SparseNode * node, int * arr, int * index) {
  if(node==NULL)
    return; 

  preOrder(node->left, arr, index); 
  arr[*index] = node->value; 
  (*index) ++; 
  preOrder(node->right, arr, index); 

}




/* int main(int argc, char * * argv) */
/* { */
/*   SparseNode * root = SparseNode_create(10, 100); */
/*   root->left = SparseNode_create(5, 101); */
/*   root->right = SparseNode_create(15, 102); */
/*   root->left->right = SparseNode_create(8, 103); */
/*   root->left->left = SparseNode_create(3, 103); */

  
  
/*   print_tree(root); */
/*   printf("\n"); */
/*   root = SparseArray_remove(root, 5);  */
/*   printf("After removing: \n");  */
/*   print_tree(root); */
/*   printf("\n"); */


/*   int indices[] = { 5, 3, 4, 2, 9, 8, 6};  */
/*   int values[] = { 100, 29, 45, 93, 84, 32, 8};  */
/*   int length = 7;  */
/*   SparseNode * rootBuild = SparseArray_build(indices, values, length);  */

/*   SparseNode * root_copy = SparseArray_copy(rootBuild);  */
/*   print_tree(rootBuild);  */
/*   printf("\n");  */

  
/*   SparseNode * merge = SparseArray_merge(root, root_copy);  */
  
/*   printf("\n\n");  */


/*   SparseArray_destroy(merge); */
/*   SparseArray_destroy(root_copy);  */
/*   SparseArray_destroy(rootBuild);  */
/*   SparseArray_destroy(root);  */
/*   return 0; */
/* } */

