/*
 * List.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: juncheng
 */
#include "List.h"
#define SUCCESS 0;
#include "stddef.h"
#include <iostream>
using namespace std;

List::List() {
	this->head = NULL;
}

List::List(Node* node){
	this->head = node;

}
List::List(const List* l) {
	this->head=NULL;
	Node* cur = l->head;
	while(cur!=NULL) {
		this->tailAppend(cur->value);
		cur = cur->next;
	}
}

void List::tailAppend(int value) {
	Node *n=new Node;
	n->value=value;
	n->next = NULL;
	Node *cur = this->head;
	if(cur==NULL)
		head=n;
	while(cur) {
		if(cur->next == NULL) {
			cur->next = n;
			break;
		}
		cur = cur->next;
	}
}

void List::print() const {
	Node *cur = this->head;
	while(cur!=NULL) {
		cout<< cur->value << " -> ";
		cur = cur->next;
	}
	cout << " Null " << endl;
}


void List::duplicateRemove() {
	int val;
	Node* backupNode;
	Node* cur = this->head;
	while(cur!=NULL) {
		val = cur->value;

		backupNode = cur;
		cur = cur->next;
		Node* cur2 = cur;
		while(cur2!=NULL) {
			if(cur2->value==val) {
				backupNode->next = cur2->next;
				cur2 = backupNode->next;
			}
			else{
				backupNode = cur2;
				cur2= cur2->next;
			}
		}
	}
}


List::~List() {
	Node* cur = this->head;
	Node* backupNode;
	while(cur!=NULL) {
		backupNode = cur->next;
		delete cur;
		cur = backupNode->next;
	}

}


void List::reverse() {
	Node* cur=this->head;
	Node* backupNode = cur;
	Node* backupNext= cur->next;
	while(backupNext!=NULL) {
		cur = backupNext;
		backupNext = cur->next;
		cur->next = backupNode;
		backupNode = cur;
	}
	this->head->next = NULL;
	this->head = cur;
}

bool palindrome(Node* list) {
	List* l = new List(list);
	List* newList = new List(l);

	newList->reverse();
	Node* cur = l->head;
	Node* newCur = newList->head;
	while(cur!=NULL) {
		if(cur->value != newCur->value) {
			cout << "This list is NOT a palindrome. " << endl;
			return false;
		}
		cur = cur->next;
		newCur = newCur->next;

	}
	cout << "This list is a palindrome. " << endl;
	return true;

}

void braid(Node* list) {
	List* oldList = new List(list);
	List* newList = new List(oldList);
	newList->reverse();
	Node* cur = oldList->head;
	while(cur->next!=NULL) {

		cur = cur->next;
	}
	cur->next = newList->head;
	//list = oldList->head;

}

int main() {
	List *list = new List();
	list->tailAppend(1);
	list->tailAppend(5);
	list->tailAppend(7);
	list->tailAppend(4);
	list->tailAppend(4);
	list->tailAppend(4);
	list->tailAppend(7);
	list->tailAppend(5);
	list->tailAppend(1);
	cout << "Original List: " << endl;
	list->print();


	cout << "(a) ";
	palindrome(list->head);
	cout << "(d) After braiding: " << endl;
	braid(list->head);
	list->print();
	cout << "(c) After duplicating remove:" << endl;
	list->duplicateRemove();
	list->print();

	delete list;
	return SUCCESS;
}
