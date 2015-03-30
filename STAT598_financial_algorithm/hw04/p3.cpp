#include <iostream>
#include <string> 
#include <cmath> 
using namespace std; 

int convert(int base, string & s) {
  string::reverse_iterator it; 
  int digit;
  int pos= 0; 
  int value = 0; 
  for(it=s.rbegin(); it!=s.rend(); ++it) {
    if(*it <= '9' && *it >='0') 
      digit = *it -'0'; 
    if(*it <= 'F' && *it >='A') 
      digit = *it -'A'+10; 
    value += digit * pow(base, pos); 
    ++pos; 
  }
  return value; 

}

int main() {
  string s="C3455E"; 
  cout << convert(16, s) << endl; 

  return 0; 
}
