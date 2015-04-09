#include <iostream>
#include <vector> 
#include <unordered_map>

using namespace std; 

void threeSum(vector<int> * v) {
  unordered_map<int, int>  map; 
  unordered_map<int, int>::iterator iter; 
  for(int i=0 ; i<v->size();++i) {
    map[v->at(i)] = i;  
  }

  unordered_map<int, int>::iterator result; 
  for(int i=0; i<v->size(); i++) {
    for(int j=i+1; j<v->size(); j++) {

      int target=-(v->at(i)+v->at(j)); 
      result = map.find(target); 
      if(result!=map.end() && result->second>j) {
	cout << v->at(i) << "," << v->at(j) << "," << result->first << endl; 
      }
    }
  }
}

int main() {
  int i, n;
  vector<int> v ;
  cout << "Enter the amount of numbers you want to evaluate: " << endl;
  cin >> i;
  cout << "Enter the numbers to be evaluated: " << endl;
  while (v.size()<i && cin>> n) {
    v.push_back(n);
  }
  cout << "The Triplets are: " << endl; 

  threeSum(&v); 
  return 0; 
}
