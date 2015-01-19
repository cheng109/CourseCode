/*
 ============================================================================
 Name        : hw01.cpp
 Author      : Jun Cheng
 Version     :
 Copyright   :
 Description : Ruth-Aaron pair
 ============================================================================
*/
# include <iostream>
# include <math.h>
# define SUCCESS 0

# include "Number.h"

using namespace std;

void RA_pairs(int num) {
	// Find the first 'num' Ruth-Aaron pairs.
	int temp_sum = 0 ;
	int n=3;
	int index=0;
	while (index < num) {
		Number Num = Number(n);
		Num.factorization();

		if (temp_sum==Num.sum) {
			index ++;
			Number tempNum=Number(n-1);
			tempNum.factorization();
			tempNum.printOut();
			Num.printOut();
			cout << endl;
		}
		temp_sum=Num.sum;
		n++;
	}
}

int main() {

	RA_pairs(20);
	cout << "over!" << endl;

	return SUCCESS;
};

