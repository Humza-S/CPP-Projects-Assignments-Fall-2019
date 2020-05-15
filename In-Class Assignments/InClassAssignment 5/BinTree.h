/*
	Name: Humza Salman | MHS180007
	Name: Nick Baker | NDB180002
*/

#ifndef BinTree_H
#define BinTree_H

#include "Node.h"
#include <queue>

template<typename T> class Node; // forward declaration to enable use of friend class

template <typename T>
class BinTree
{
	private:
		Node<T>* root;
		int size;

		//helper functions
		T* findMinRightSubtree(Node<T>* node);
		T* findMaxLeftSubtree(Node<T>* node);
		Node<T>* getParent(Node<T>* node);
		Node<T>* getParent(Node<T>* parent, Node<T>* node);
	public:
		//constructors
		BinTree<T>() {
			root = nullptr;
			size = 0;
		}

		//destructor
		~BinTree<T>();

		//wrapper functions
		void insert(T* value);
		Node<T>* search(T* key);
		Node<T>* remove(T* key);
		void clear();
		
		//functions
		void insert(Node<T>* parent, Node<T>* newNode);
		Node<T>* search(Node<T>* node, Node<T>* key);
		Node<T>* remove(Node<T>* parent, T* node);
		void clear(Node<T>* root);
		void printBreadthFirst();
		int getHeight(Node<T>* node);

		//accessors
		Node<T>* getRoot() { return root; };
		int getSize() { return size; };

		//mutators
		void setRoot(Node<T>* r) { root = r; };
};

#endif // !BinTree_H