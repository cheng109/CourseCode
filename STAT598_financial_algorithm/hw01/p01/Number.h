/*
 * Number.h
 *
 *  Created on: Jan 16, 2015
 *      Author: cheng109
 */

#ifndef NUMBER_H_
#define NUMBER_H_

class Number {

public:
	int n;
	int primeFactors[50];   // An array storing all the prime factors.
							// Assume the number of factors no more than 50;
	int size = 0 ;		// total number of factors.
	int sum = 0;		// sum of all the factors.

public:
	Number(const int n);
	void factorization();
	void printOut();

	virtual ~Number();
};

bool isPrime(int n);
#endif /* NUMBER_H_ */
