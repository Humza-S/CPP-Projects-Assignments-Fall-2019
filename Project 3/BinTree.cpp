/*
	Name: Humza Salman
	NET ID: MHS180007
*/

#include "BinTree.h"

// destructor
template <typename T>
BinTree<T>::~BinTree() {
	clear();
}

// wrapper function to insert the payload
template<typename T>
void BinTree<T>::insert(T* value) {
	Node<T>* node = new Node<T>(value);
	if (!root) { // inserts a new node into an empty tree
		root = node;
		size++;
	}
	else
		insert(root, node); // inserts a new node into the tree
}

// recursively inserts the new node in sorted order
template <typename T>
void BinTree<T>::insert(Node<T>* parent, Node<T>* node) {
	if (*parent < *node) { // checks to see if node should be inserted in right subtree
		if (!parent->right) { // if parent's right child is null, then inserts the node there
			parent->right = node;
			size++;
		}
		else
			insert(parent->right, node); // since the right child is not null, calls insert again with the parent as the current parent's right child
	}
	else if (*parent->data == *node->data) { // if the payload already exists, then it adds both payloads together
		*(parent->data) + *(node->data);
	}
	else { // inserting into left subtree
		if (!parent->left) { // if parent's left child is null, then inserts the node there
			parent->left = node;
			size++;
		}
		else
			insert(parent->left, node); // since the left child is not null, calls insert again with the parent as the current parent's left child
	}
}

// wrapper function to search for the payload
template<typename T>
Node<T>* BinTree<T>::search(T* key)
{
	return search(root, new Node<T>(key));
}

// recursively searches to see if the node exists which contains the key
template<typename T>
Node<T>* BinTree<T>::search(Node<T>* node, Node<T>* key)
{
	if (node) { // checks to see if the node exists
		if (*node == *key) 
			return node; // returns node if it is found
		else if (*key < *node)
			return search(node->left, key); // calls search again, but goes down the left subtree since the value of the key is less than the node
		else
			return search(node->right, key); // calls search again, but goes down the right subtree
	}
	return nullptr;
}

// wrapper function to remove a payload from the tree
template<typename T>
Node<T>* BinTree<T>::remove(T* key)
{
	if (search(key)) {
		size--;
		return remove(getParent(new Node<T>(key)), key);
	}
	return nullptr;
}

// recursively removes the node from the binary search tree
template<typename T>
Node<T>* BinTree<T>::remove(Node<T>* parent, T* value)
{
	if (!parent) { // checks to see if the parent is null
		if (*value == *root->data) { // if the value is the root, then removes root and returns it
			Node<T>* temp = root; // stores root before removing it

			if (root->right) { // stores data of smallest value in right subtree and removes that node
				root->data = findMinRightSubtree(root->right); 
				root->right = remove(root->right, root->data);
			}
			else if (root->left && !(root->left->data == root->data)) { // stores data of largest value in left subtree and removes that node
				root->data = findMaxLeftSubtree(root->left);
				root->left = remove(root->left, root->data);
			}
			else
				root = nullptr;
			return temp;
		}
		else
			return parent; // returns parent since it's null
	}

	else if (*parent->data > *value) // value is in left subtree
		parent->left = remove(parent->left, value); // calls the remove function on the left subtree
	else if (*parent->data < *value) { // value is in right subtree
		parent->right = remove(parent->right, value); // calls the remove function on the right subtree
	}
	else { // value is found
		if (!parent->left) // no left child (right child exists)
			return parent->right;

		else if (!parent->right) // no right child (left child exists)
			return parent->left;

		else { // both childs
			if (parent->right) { // stores data of smallest value in right subtree and removes that node
				parent->data = findMinRightSubtree(parent->right); 
				parent->right = remove(parent->right, parent->data);
			}
			else { // stores data of largest value in left subtree and removes that node
				parent->data = findMaxLeftSubtree(parent->left);
				parent->left = remove(parent->left, parent->data);
			}
		}
	}
	return parent;
}

// wrapper function to clear the tree
template<typename T>
void BinTree<T>::clear()
{
	if (root) {
		clear(root);
	}
}

// recursively frees the memory of the node in the tree
template<typename T>
void BinTree<T>::clear(Node<T>* node)
{
	if (!node)
		return;
	clear(node->right);
	clear(node->left);
	std::free(node);
	size--;
}

// recursively finds the smallest payload in the right subtree
template <typename T>
T* BinTree<T>::findMinRightSubtree(Node<T>* node) {
	if (node)
		if (node->left)
			return findMinRightSubtree(node->left);
	return node->data;
}

// recursively finds the largest payload in the left subtree;
template <typename T>
T* BinTree<T>::findMaxLeftSubtree(Node<T>* node) {
	if (node)
		if (node->right)
			return findMaxLeftSubtree(node->right);
	return node->data;
}

// wrapper function to find the parent of a node
template<typename T>
Node<T>* BinTree<T>::getParent(Node<T>* node)
{
	if (*root == *node) // root node has no parent
		return nullptr; 
	else
		return getParent(root, node);
}

// recursively finds the parent of the given node
template<typename T>
Node<T>* BinTree<T>::getParent(Node<T>* parent, Node<T>* childNode)
{
	if (!parent)
		return nullptr;
	if (*parent->left == *childNode || *parent->right == *childNode) // returns the value if the parent finds the child node
		return parent;

	// checks to see if the child node is less than or greater than the parent data
	if (*childNode->data < *parent->data) 
		return getParent(parent->left, childNode);
	else
		return getParent(parent->right, childNode);
}