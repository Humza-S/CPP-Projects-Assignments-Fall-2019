// Homework6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <list>

using namespace std;

struct Node {
	int data;
	Node* next;
};

void bubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);

void quickSort(struct Node** headRef);
struct Node* quickSortRecur(struct Node* head, struct Node* end, long long int& comp, long int& itemAssign);
struct Node* partition(struct Node* head, struct Node* end,
	struct Node** newHead, struct Node** newEnd, long long int& comp, long int& itemAssign);
struct Node* getTail(struct Node* cur);
void insertionSort(struct Node** head_ref);
void sortedInsert(struct Node** head_ref, struct Node* new_node, long long int& comp, long int& itemAssign);
int MergeSort(Node** headRef);
Node* SortedMerge(Node* a, Node* b, long long int& comp);
void FrontBackSplit(Node* source, Node** frontRef, Node** backRef, long long int& comp);

void push(Node** head_ref, int new_data);
void swap(int* xp, int* yp);
void printArray(int arr[], int size);
void printList(Node* node);

int main()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 10000);

	int arr1[5000];
	int arr2[5000];
	int arr3[5000];
	Node* list1 = NULL;
	Node* list2 = NULL;
	Node* list3 = NULL;
	for (int i = 0; i < 5000; i++) {
		int val = dis(gen);
		arr1[i] = val;
		arr2[i] = val;
		arr3[i] = val;
	}
	for (int i = 0; i < 4100; i++) {
		int val = dis(gen);
		push(&list1, val);
		push(&list2, val);
		push(&list3, val);
	}
	//printList(list1);
	bubbleSort(arr1, 5000);
	selectionSort(arr2, 5000);
	insertionSort(arr3, 5000);


	quickSort(&list1);
	insertionSort(&list2);
	int c = MergeSort(&list3);
	cout << "\nMerge Sort: " << c << endl;
}


// A function to implement bubble sort  
void bubbleSort(int arr[], int n)
{
	int i, j;
	long long int comp = 0;
	long int itemAssign = 0;
	bool swapped;
	for (i = 0; i < n - 1; i++)
	{
		swapped = false;
		for (j = 0; j < n - i - 1; j++)
		{
			comp++;
			if (arr[j] > arr[j + 1])
			{
				itemAssign++;
				swap(&arr[j], &arr[j + 1]);
				swapped = true;
			}
		}

		// IF no two elements were swapped by inner loop, then break 
		if (swapped == false)
			break;
	}
	cout << "\nBubble Sort: " << comp << " || " << itemAssign << '\n';
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;
	long long int comp = 0;
	long int itemAssign = 0;
	// One by one move boundary of unsorted subarray  
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array  
		min_idx = i;
		for (j = i + 1; j < n; j++) {
			comp++;
			if (arr[j] < arr[min_idx])
				min_idx = j;
		}

		// Swap the found minimum element with the first element  
		itemAssign++;
		swap(&arr[min_idx], &arr[i]);
	}
	cout << "\nSelection Sort: " << comp << " || " << itemAssign << '\n';
}

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
	int i, key, j;
	long long int comp = 0;
	long int itemAssign = 0;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			comp++;
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
		itemAssign++;
	}
	cout << "\nInsertion Sort: " << comp << " || " << itemAssign << '\n';
}

// function to sort a singly linked list using insertion sort 
void insertionSort(struct Node** head_ref)
{
	long long int comp = 0;
	long int itemAssign = 0;
	// Initialize sorted linked list 
	struct Node* sorted = NULL;

	// Traverse the given linked list and insert every 
	// node to sorted 
	struct Node* current = *head_ref;
	comp++;
	while (current != NULL)
	{
		comp++;
		// Store next for next iteration 
		struct Node* next = current->next;

		// insert current in sorted linked list 
		sortedInsert(&sorted, current, comp, itemAssign);

		// Update current 
		current = next;
	}

	// Update head_ref to point to sorted linked list 
	*head_ref = sorted;
	
	cout << "\nInsertion Sort (Linked List): " << comp << " || " << itemAssign << '\n';
}

/* function to insert a new_node in a list. Note that this
  function expects a pointer to head_ref as this can modify the
  head of the input linked list (similar to push())*/
void sortedInsert(struct Node** head_ref, struct Node* new_node, long long int& comp, long int& itemAssign)
{
	struct Node* current;
	/* Special case for the head end */
	comp++;
	if (*head_ref == NULL || (*head_ref)->data >= new_node->data)
	{
		itemAssign++;
		new_node->next = *head_ref;
		*head_ref = new_node;
	}
	else
	{
		/* Locate the node before the point of insertion */
		current = *head_ref;
		while (current->next != NULL &&
			current->next->data < new_node->data)
		{
			++comp;
			current = current->next;
		}
		itemAssign++;
		new_node->next = current->next;
		current->next = new_node;
	}
}

/* sorts the linked list by changing next pointers (not data) */
int MergeSort(Node** headRef)
{
	Node* head = *headRef;
	Node* a;
	Node* b;
	long long int comp = 0;

	/* Base case -- length 0 or 1 */
	comp++;
	if ((head == NULL) || (head->next == NULL)) {
		return 0;
	}

	/* Split head into 'a' and 'b' sublists */
	FrontBackSplit(head, &a, &b, comp);

	/* Recursively sort the sublists */
	MergeSort(&a);
	MergeSort(&b);

	/* answer = merge the two sorted lists together */
	*headRef = SortedMerge(a, b, comp);

	return comp;
}

/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
Node* SortedMerge(Node* a, Node* b, long long int& comp)
{
	Node* result = NULL;

	/* Base cases */
	comp++;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	/* Pick either a or b, and recur */
	comp++;
	if (a->data <= b->data) {
		result = a;
		result->next = SortedMerge(a->next, b, comp);
	}
	else {
		result = b;
		result->next = SortedMerge(a, b->next, comp);
	}
	return (result);
}

// Returns the last node of the list 
struct Node* getTail(struct Node* cur)
{
	while (cur != NULL && cur->next != NULL)
		cur = cur->next;
	return cur;
}

// Partitions the list taking the last element as the pivot 
struct Node* partition(struct Node* head, struct Node* end,
	struct Node** newHead, struct Node** newEnd, long long int& comp, long int& itemAssign)
{
	struct Node* pivot = end;
	struct Node* prev = NULL, * cur = head, * tail = pivot;

	// During partition, both the head and end of the list might change 
	// which is updated in the newHead and newEnd variables 
	comp++;
	while (cur != pivot)
	{
		comp++;
		comp++;
		if (cur->data < pivot->data)
		{
			// First node that has a value less than the pivot - becomes 
			// the new head 
			comp++;
			if ((*newHead) == NULL)
				(*newHead) = cur;
			itemAssign++;
			prev = cur;
			itemAssign++;
			cur = cur->next;
		}
		else // If cur node is greater than pivot 
		{
			// Move cur node to next of tail, and change tail 
			if (prev) {
				itemAssign++;
				prev->next = cur->next;
			}

			itemAssign++;
			struct Node* tmp = cur->next;
			cur->next = NULL;
			tail->next = cur;
			tail = cur;
			cur = tmp;
		}
	}

	// If the pivot data is the smallest element in the current list, 
	// pivot becomes the head 
	comp++;
	if ((*newHead) == NULL) {
		itemAssign++;
		(*newHead) = pivot;
	}

	// Update newEnd to the current last node 
	itemAssign++;
	(*newEnd) = tail;

	// Return the pivot node 
	return pivot;
}


//here the sorting happens exclusive of the end node 
struct Node* quickSortRecur(struct Node* head, struct Node* end, long long int& comp, long int& itemAssign)
{
	// base condition 
	comp++;
	if (!head || head == end)
		return head;

	Node* newHead = NULL, * newEnd = NULL;

	// Partition the list, newHead and newEnd will be updated 
	// by the partition function 
	itemAssign++;
	struct Node* pivot = partition(head, end, &newHead, &newEnd, comp, itemAssign);

	// If pivot is the smallest element - no need to recur for 
	// the left part. 
	comp++;
	if (newHead != pivot)
	{
		// Set the node before the pivot node as NULL 
		struct Node* tmp = newHead;
		while (tmp->next != pivot) {
			comp++;
			tmp = tmp->next;
		}
		tmp->next = NULL;

		// Recur for the list before pivot 
		newHead = quickSortRecur(newHead, tmp, comp, itemAssign);

		// Change next of last node of the left half to pivot 
		itemAssign++;
		tmp = getTail(newHead);
		itemAssign++;
		tmp->next = pivot;
	}

	// Recur for the list after the pivot element 
	itemAssign++;
	pivot->next = quickSortRecur(pivot->next, newEnd, comp, itemAssign);

	return newHead;
}

// The main function for quick sort. This is a wrapper over recursive 
// function quickSortRecur() 
void quickSort(struct Node** headRef)
{
	long long int comp = 0;
	long int itemAssign = 0;
	(*headRef) = quickSortRecur(*headRef, getTail(*headRef), comp, itemAssign);
	cout << "\nQuick Sort: " << comp << " || " << itemAssign << '\n';
	return;
}


/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
	and return the two lists using the reference parameters.
	If the length is odd, the extra node should go in the front list.
	Uses the fast/slow pointer strategy. */
void FrontBackSplit(Node* source, Node** frontRef, Node** backRef, long long int& comp)
{
	Node* fast;
	Node* slow;
	slow = source;
	fast = source->next;

	/* Advance 'fast' two nodes, and advance 'slow' one node */
	while (fast != NULL) {
		comp++;
		fast = fast->next;
		if (fast != NULL) {
			comp++;
			slow = slow->next;
			fast = fast->next;
		}
	}

	/* 'slow' is before the midpoint in the list, so split it in two
	at that point. */
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

/* Function to insert a node at the beginging of the linked list */
void push(Node** head_ref, int new_data)
{
	/* allocate node */
	Node* new_node = new Node();

	/* put in the data */
	new_node->data = new_data;

	/* link the old list off the new node */
	new_node->next = (*head_ref);

	/* move the head to point to the new node */
	(*head_ref) = new_node;
}

void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void printList(Node* node)
{
	while (node != NULL) {
		cout << node->data << " ";
		node = node->next;
	}
	cout << '\n';
}