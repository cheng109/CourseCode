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

	string output1 = removeCharacters1("counterrevolutionaries","aeiou");
	cout << output1 << endl;

	string test01 = string("counterrevolutionaries");
	removeCharacters(test01,"aeiou");
	cout << test01 << endl;

	cout << "over!" ;
	return 0;
}
