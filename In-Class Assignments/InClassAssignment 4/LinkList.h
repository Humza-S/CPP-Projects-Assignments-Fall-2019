/*
	Name: Humza Salman
	NET ID: MHS180007
*/

#ifndef LinkList_H
#define LinkList_H

#include "Node.h"

class LinkList
{
private:
	Node* head;
	Node* tail;
	int size;
public:
	//constructor
	LinkList() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	};
	//destructor
	~LinkList() {};

	//accessors
	int getSize() { return size; };
	Node* getHead() { return head; };
	Node* getTail() { return tail; };

	//mutators
	void setSize(int s) { size = s; };
	void setHead(Node* n) { head = n; };
	void setTail(Node* n) { tail = n; };

	//functions
	char pop();
	char peek();
	bool isEmpty() { return size == 0; };
	void append(char& newValue);
	void print();
	
};
#endif // !LinkList_H
