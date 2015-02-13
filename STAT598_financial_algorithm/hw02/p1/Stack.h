/*
 * Stack.h
 *
 *  Created on: Feb 12, 2015
 *      Author: cheng109
 */

#ifndef STACK_H_
#define STACK_H_
#include <iostream>
using namespace std;
class Stack {
friend class Queue;
private:
	int maxStack;
	int top;
	int * stack;
public:
	Stack(int maxStack);
	Stack(Stack &s);
	bool push(int value);
	bool pop(int &value);
	int getTop() const;
	int getMaxStack() const;
	void print() const;
	bool peek(int &value) const;
	void expand(int n);
	virtual ~Stack();
	void reverse();
	friend ostream &operator <<(ostream &out, const Stack &s);
	Stack &operator=(const Stack& s);

};


#endif /* STACK_H_ */
