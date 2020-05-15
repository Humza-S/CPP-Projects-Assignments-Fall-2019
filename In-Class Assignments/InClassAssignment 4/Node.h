/*
	Name: Humza Salman
	NET ID: MHS180007
*/

#ifndef Node_H
#define Node_H

#include <iostream>

class Node
{
private:
	char nodeData;
	Node* next;
	Node* previous;
public:

	//constructors
	Node() {
		next = nullptr;
		previous = nullptr;
	};
	Node(char data) {
		nodeData = data;
		this->next = nullptr;
		this->previous = nullptr;
	};

	//destructor
	~Node() {};

	friend std::ostream& operator<<(std::ostream& out, Node* node) {
		out << node->getData();
		return out;
	}

	//accessors
	char getData() { return this->nodeData; };
	Node* getNext() { return this->next; };
	Node* getPrevious() { return this->previous; };

	//mutators
	void setData(char data) { nodeData = data; };
	void setNext(Node* n) { this->next = n; };
	void setPrevious(Node* p) { this->previous = p; };
};
#endif // !Node_H

