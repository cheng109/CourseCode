#include <queue>
#include <iostream>
using namespace std; 

struct node {
  int value; 
  node* left; 
  node* right; 
  node(int a): value(a), left(NULL), right(NULL) {
  }
}; 


void BFS_print(node* root) {
  queue<node*> q; 
  q.push(root); 
  cout << root->value << endl; 
  while(!q.empty()) {
    node* l = q.front()->left; 
    node* r = q.front()->right; 
    if(l!=NULL){
      cout << l->value << endl; 
      q.push(l);
    } 
    if(r!=NULL) {
      cout << r->value << endl; 
      q.push(r); 
    }
    q.pop(); 
  }
}

void DFS_print(node* root) {
  // pre-order
  if(root==NULL) 
    return; 
  cout << root->value << endl ; 
  DFS_print(root->left); 
  DFS_print(root->right); 
}

node* mirrorCopy(node* root) {
  if(root==NULL) 
    return NULL; 
  node* n = new node(root->value); 
  n->left = mirrorCopy(root->right); 
  n->right = mirrorCopy(root->left); 
  return n; 
}


int main() {
  node * root =new node(100); 
  root->left = new node(2); 
  root->right = new node(3); 
  root->left->left = new node(5); 
  root->left->right = new node(6) ; 
  root->right->left = new node(44); 
  root->right->right = new node(2); 

  // Part(a)

  BFS_print(root); 
  // Part(b)
  DFS_print(root); 

  // Part(c)
  node* newNode = mirrorCopy(root); 
  cout << "new tree" << endl; 
  DFS_print(newNode); 
}
  
