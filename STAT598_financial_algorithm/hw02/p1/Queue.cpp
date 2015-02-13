/*
 * Queue.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: cheng109
 */

#include "Queue.h"
#include <iostream>
using namespace std;

Queue::Queue() {
}

Queue::Queue(int maxStack) {
	this->maxStack = maxStack;
	inbox =new Stack(maxStack);
	outbox=new Stack(maxStack);
}

Queue::Queue(const Queue &q){
	this->maxStack = q.maxStack;
	inbox =new Stack(this->maxStack);
	outbox=new Stack(this->maxStack);
	inbox->top = q.inbox->top;
	outbox->top = q.outbox->top;
	for(int i=0; i<q.inbox->getTop(); i++) {

		inbox->stack[i]= q.inbox->stack[i];
	}
}

Queue & Queue::operator=(const Queue& q) {
	if(this==&q) {
		return *this;
	}
	delete [] this->inbox->stack;
	delete [] this->outbox->stack;
	maxStack= q.maxStack;
	inbox =new Stack(this->maxStack);
	outbox=new Stack(this->maxStack);
	inbox->top = q.inbox->top;
	outbox->top = q.outbox->top;

	for(int i=0; i<q.inbox->getTop(); i++) {
		inbox->stack[i]= q.inbox->stack[i];
	}
	return *this;
}


Queue::~Queue() {
	delete inbox;
	delete outbox;

}

bool Queue::enqueue(int value){
	inbox->push(value);
	return true;
}


bool Queue::dequeue(int &value) {
	int temp;
	if(inbox->getTop()==0) {
		return false;
	}
	if(outbox->getTop()==0) {
		while(inbox->getTop()!=0){
			inbox->pop(temp);
			outbox->push(temp);
		}
	}
	outbox->pop(value);
	while(outbox->getTop()!=0){
		outbox->pop(temp);
		inbox->push(temp);

	}
	return true;
}

ostream &operator <<(ostream &out, const Queue &q){
	out << *(q.inbox);
	return out;
}

void Queue::reverse(){
	this->inbox->reverse();

}

int Queue::peek(){
	int val;
	this->inbox->peek(val);
	return val;

}
