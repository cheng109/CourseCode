/*
 * Number.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: cheng109
 */

#include "Number.h"
#include <math.h>
#include <iostream>
# define TRUE 1
# define FALSE 0


bool isPrime(int n) {
	if (n == 2)
		return TRUE;
	int max = sqrt(n) + 1;
	for (int i = 2; i < max; i++) {
		if (n % i == 0) {
			return FALSE;
		}
	}
	return TRUE;
}

Number::Number(const int number) {
	this->n = number;
}

Number::~Number() {

}

void Number::factorization() {
	int n= this->n;
	int max = sqrt(n)+1;
	int i = 2;
	for(; i<max; i++) {
		if(n%i==0 && isPrime(i)) {
			this->sum += i;
			this->primeFactors[this->size]= i;
			this->size += 1;
			n = n/i;
			i--;
		}
	}
	if(n>=max) {
		this->primeFactors[this->size]=n;
		this->size +=1;
		this->sum += n;
	}
}

void Number::printOut() {
	std::cout << this->n << " = ";
	for(int i=0; i<this->size-1; i++) {
		std::cout << this->primeFactors[i] << " * ";
	}
	if (this->size==1) {
		std::cout << this->primeFactors[size-1] << " = " << " PRIME " << std::endl;
	}
		else std::cout << this->primeFactors[size-1] << " = " << this->sum << std::endl;
}
