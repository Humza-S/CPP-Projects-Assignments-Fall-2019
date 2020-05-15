#include "LinkList.h"

char LinkList::pop()
{
	char temp = tail->getData();
	tail = tail->getPrevious();
	tail->setNext(nullptr);
	size--;
	return temp;
}

char LinkList::peek()
{
	return tail->getData();
}

void LinkList::append(char& newValue)
{
	Node* node = new Node(newValue);
	if (head == nullptr) { // checks to see if the list is empty
		head = node;
		tail = node;
	}
	else { // updates the tail pointer's next pointer, new node's previous pointer, and the tail pointer itself
		tail->setNext(node);
		node->setPrevious(this->tail);
		tail = node;
	}
	size++; // increments size since a new node was added
}

void LinkList::print()
{
	Node* current = head;
	while (current) {
		std::cout << current->getData();
		current = current->getNext();
	}
}
