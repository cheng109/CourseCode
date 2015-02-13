/*
 * Stack.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: cheng109
 */

#include "Stack.h"
#include "Queue.h"
#include <iostream>
#include <string>
#include <vector>
#define SUCCESS 0;

using namespace std;

Stack::Stack(int max) {
	maxStack=max;
	stack = new int[maxStack];
	top=0;

}

// copy constructor;
Stack::Stack(Stack &s){
	maxStack= s.maxStack;
	top = s.top;
	this->stack = new int[maxStack];
	for(int i=0; i<top; i++) {
		this->stack[i]= s.stack[i];
	}
}

Stack & Stack::operator=(const Stack& s) {
	if(this==&s) {
		return *this;
	}
	delete [] this->stack;
	maxStack= s.maxStack;
	top = s.top;
	this->stack = new int[maxStack];
	for(int i=0; i<top; i++) {
		this->stack[i]= s.stack[i];
	}
	return *this;
}

Stack::~Stack() {
	delete [] stack;
}

bool Stack::push(int value) {
	if(top==maxStack) {
		this->expand(maxStack);
	}
	stack[top]=value;
	top++;
	return true;
}

bool Stack::pop(int & value) {
	if(top==0)
		return false;
	value = stack[top-1];
	top--;
	return true;
}

int Stack::getTop() const {
	return top;
}

int Stack::getMaxStack() const {
	return maxStack;

}

bool Stack::peek(int &value) const {
	if(top==0)
		return false;
	value = stack[0];
	return true;
}

void Stack::print() const {
	cout << "stack: (" << this->top << ")"<<endl;
	for(int i=0; i<top; i++){
		cout << stack[i] <<endl;
	}
	cout << endl;
}

void Stack::reverse() {
	int temp;
	if (top==0) return;
	for(int i=0; i<top/2; i++){
		temp = stack[i];
		stack[i] = stack[top-1-i];
		stack[top-1-i] = temp;
	}
}

void Stack::expand(int n) {
	int * temp = new int[maxStack+n];
	copy(stack, stack+top, temp);
	maxStack = maxStack + n;
	delete stack;
	stack = temp;

}

bool isOperator(string c) {
	if(c=="+" || c=="-" || c=="*" || c=="/" || c=="%")
		return true;
	return false;
}

ostream &operator <<(ostream &out, const Stack &s){
	out << "stack: (" << s.getTop() << ")"<<endl;
	for(int i=0; i<s.getTop(); i++){
		cout << s.stack[i] <<endl;
	}
	out << endl;
	return out;

}

int rpn(vector<string> input, int len) {
	Stack stack(len);
	int temp;
	int o1;
	int o2;
	vector<string>::iterator iter=input.begin();
	while(*iter!="$") {
		if(!isOperator(*iter)) {
			stack.push(stoi(*iter));
		}
		else {
			stack.pop(o2);
			stack.pop(o1);
			if(*iter=="+")
				temp=o1+o2;
			else if(*iter=="-")
				temp=o1-o2;
			else if(*iter=="*")
				temp=o1*o2;
			else if(*iter=="/")
				temp=o1/o2;
			else if(*iter=="%")
				temp=o1%o2;
			stack.push(temp);
			cout << "push: " << temp << endl;
			cout << stack << endl;
		}

		iter++;
	}
	stack.pop(temp);
	return temp;

}

int main() {
	vector<string> input;
	input.push_back("6");
	input.push_back("4");
	input.push_back("5");
	input.push_back("+");
	input.push_back("*");
	input.push_back("25");
	input.push_back("2");
	input.push_back("3");
	input.push_back("+");
	input.push_back("/");
	input.push_back("-");
	input.push_back("$");

	cout << rpn(input, 20) << endl ;

	Queue queue(100);
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);
	queue.enqueue(4);
	queue.enqueue(5);

	int val;
	queue.dequeue(val);
	//queue.dequeue(val);
	cout << queue.peek()<< endl;
	cout << queue << endl;

	queue.reverse();
	cout << queue << endl;
	Queue q2(queue);

	cout << "q2 " << endl;
	cout << q2;



	return SUCCESS;
}


