#include <iostream> 
#include <cmath>
using namespace std; 

bool triplet(int N) {
  int mod, mod1; 
  int result, result1;  
  int a, b; 
  for(int i=2; i<sqrt(N)+1; i++){
    mod = N%i; 
    result = N/i; 
    if(mod==0) {
      a = i ; 
      for(int j=2; j<sqrt(result)+1; ++j) {
	mod1 = result%j;
	result1 = result/j; 
	if(mod1==0) {
	  b = j; 
	  if(result1>2) {
	    cout << a << "*" << b << "*" <<  result1 << endl;
	    return true; 
	  }
 	  else 
	    return false; 
	}
      }
    }
  }

  return false; 

}

int main() {
  if(!triplet(144))
    cout << "No triplet found!" << endl;  

  return 0; 
}
