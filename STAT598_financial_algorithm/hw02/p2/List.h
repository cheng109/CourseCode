/*
 * List.h
 *
 *  Created on: Feb 12, 2015
 *      Author: juncheng
 */

#ifndef LIST_H_
#define LIST_H_

struct Node{
	int value;
	Node* next;
};

class List {
public:
	Node *head;
	List();
	List(Node* node);
	List(const List* l);
	void tailAppend(int value);
	void print() const;
	void duplicateRemove();

	void reverse();
	virtual ~List();
};


bool palindrome(Node* list);
void braid(Node* list);
#endif /* LIST_H_ */
