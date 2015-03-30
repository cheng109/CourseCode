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

int main() {
  node * root =new node(100); 
  root->left = new node(2); 
  root->right = new node(3); 
  root->left->left = new node(5); 
  root->left->right = new node(6) ; 
  root->right->left = new node(44); 
  root->right->right = new node(2); 

  BFS_print(root); 


}
  
