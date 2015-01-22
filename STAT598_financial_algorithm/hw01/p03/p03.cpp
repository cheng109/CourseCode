//============================================================================
// Name        : string_manipulate.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <string>
#include <iostream>
using namespace std;

string removeCharacters1(string str, string remove) {
	for(int i=0; i<remove.length(); i++) {
		for(int j=0; j<str.length(); j++) {
			if(remove[i]==str[j]) {
				str.erase(j,1);
			}
		}
	}
	return str;
}

void removeCharacters(string &str, string remove) {
	for(int i=0; i<remove.length(); i++) {
		for(int j=0; j<str.length(); j++) {
			if(remove[i]==str[j]) {
				str.erase(j,1);
			}
		}
	}

}


int main() {

  string testString = string("counterrevolutionaries");
  string remove = string("aeiou"); 
  cout << "testString: " << testString << endl;
  cout << "remove: " << remove << endl;
  string output1 = removeCharacters1(testString,remove);
  cout << "output01: "<< output1 << endl;
    
  removeCharacters(testString,remove);
  cout << "testString: " << testString << endl;
  return 0;
}
