#include "answer06.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * * argv)
{
  SparseNode * root = SparseNode_create(10, 100);
  root->left = SparseNode_create(5, 101);
  root->right = SparseNode_create(15, 102);
  root->left->right = SparseNode_create(8, 103);
  root->left->left = SparseNode_create(3, 103);

  
  
  print_tree(root);
  printf("\n");
  //  root = SparseArray_remove(root, 5); 
  root = SparseArray_insert(root, 8,202); 
  printf("After insert: \n"); 
  print_tree(root);
  printf("\n");


  int indices[] = { 5, 3, 4, 2, 9, 8, 6};
  int values[] = { -101, 29, 45, 93, 84, 32, 8};
  int length = 7;
  SparseNode * rootBuild = SparseArray_build(indices, values, length);

  SparseNode * root2 = SparseArray_merge(rootBuild, root); 

  /* SparseNode * root_copy = SparseArray_copy(rootBuild);  */
  print_tree(root2); 
  /* printf("\n");  */

  
  /* SparseNode * merge = SparseArray_merge(root, root_copy);  */
  
  /* printf("\n\n");  */


  /* SparseArray_destroy(merge); */
  /* SparseArray_destroy(root_copy);  */
  SparseArray_destroy(rootBuild);
  SparseArray_destroy(root2);

  SparseArray_destroy(root);
  return 0;
}
