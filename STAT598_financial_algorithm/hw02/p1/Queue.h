/*
 * Queue.h
 *
 *  Created on: Feb 13, 2015
 *      Author: cheng109
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "Stack.h"
class Queue {
private:
	int maxStack;
	Stack *inbox;
	Stack *outbox;

public:
	Queue();
	Queue(int maxStack);
	Queue(const Queue &q);
	Queue& operator=(const Queue &q);
	bool enqueue(int value);
	bool dequeue(int &value);
	void reverse();
	int peek();
	friend ostream &operator <<(ostream &out, const Queue &q);
	virtual ~Queue();
};

#endif /* QUEUE_H_ */
