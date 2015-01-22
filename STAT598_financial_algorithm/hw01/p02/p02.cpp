#include <iostream>

# define SUCCESS 0;

using namespace std;

int combine(int n, int k) {
  if(n==k || k==0) {
      cout << " C(" << n << ", " << k << ")" << endl ;
      return 1;
  
  }
  return combine(n-1,k-1)+combine(n-1, k);
}

int main() {
  cout << combine(5, 3) << endl;
  return SUCCESS;
}



