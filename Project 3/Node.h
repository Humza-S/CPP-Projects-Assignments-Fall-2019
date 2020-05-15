/*
	Name: Humza Salman
	NET ID: MHS180007
*/

#ifndef Node_H
#define Node_H

#include <iostream>

template <typename T> class BinTree; // forward declaration to enable use of friend class

template <typename T>
class Node
{
	private:
		T* data;
		Node<T>* left;
		Node<T>* right;
	public:

		// constructors
		Node<T>() {
			data = nullptr;
			left = nullptr;
			right = nullptr;
		}
		Node<T>(T* d) {
			data = d;
			left = nullptr;
			right = nullptr;
		}

		// destructor
		~Node<T>() {
			delete data;
			delete left;
			delete right;
		};

		// operators overloads
		bool operator==(const Node<T>& node) {
			return *this->data == *node.data;
		}
		bool operator<(Node<T>& node) {
			return *this->data < *node.data;
		}
		bool operator>(Node<T>& node) {
			return *this->data > *node.data;
		}
		friend std::ostream& operator<<(std::ostream& out, Node<T>* node) {
			out << node->data;
			return out;
		}		

		// accessors
		T* getData() { return data; };
		Node<T>* getLeft() { return left; };
		Node<T>* getRight() { return right; };

		// mutators
		void setData(T* data) { data = data; };
		void setLeft(Node<T>* l) { left = l; };
		void setRight(Node<T>* r) { right = r; };

		// friend classes
		friend class BinTree<T>;
};
#endif // !Node_H

