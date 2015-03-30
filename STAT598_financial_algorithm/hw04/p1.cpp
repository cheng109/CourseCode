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

  for(iter=map.begin(); iter!=map.end(); ++iter) {
    cout << iter->first << ":"<< iter->second <<endl; 
  }
  unordered_map<int, int>::iterator result; 
  for(int i=0; i<v->size(); i++) {
    for(int j=i+1; j<v->size(); j++) {

      int target=-(v->at(i)+v->at(j)); 
      result = map.find(target); 
      if(result!=map.end()) {
	cout << v->at(i) << "," << v->at(j) << "," << result->first << endl; 
      }
    }
  }
}

int main() {
  int vv[6] = {1, 2, 3, -1, -3,-5};   
  vector<int> v(&vv[0], &vv[0]+6); 
  
  threeSum(&v); 



  return 0; 

}
