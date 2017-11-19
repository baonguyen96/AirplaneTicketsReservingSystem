/*
* 
* CS/SE 3376.001
* Team 4
*
* Class: LinkedList (template)
*
* This class is an implementation of LinkedList data structure.
*
* List of methods:
*	getFirst: get the first node in the list
*	getLast: get the last node in the list
*	get: get the ith node in the list
*	getSize: get the size of the list
*	isEmpty: check if the list is empty
*	clear: empty out the linked list
*	addFirst: add new node to the front of the list
*	addLast: add new node to the end of the list
*	add: add new node to the ith position of the list
*	removeFirst: remove first node from the list
*	removeLast: remove last node from the list
*	remove: remove ith node from the list
*
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <class T>
class LinkedList
{
private:
	// structure of each node of the linked list
	struct Node
	{
		T* data;			// the data with generic type of the list
		Node* next;			// pointer to the next node in the list
		Node* previous;		// pointer to the previous node in the list
	};

	Node* first;	// pointer to the front of the list
	Node* last;		// pointer to the end of the list
	int size;		// the length of the list

	// check to see if the location is in the listSize
	bool isValidIndex(int);

	// remove the only node in the list
	T* removeOnly();

public:
	/*********************
	* CONSTRUCTOR
	********************/
	LinkedList();


	/*********************
	* DESTRUCTOR
	********************/
	~LinkedList();


	/*********************
	* ACCESSORS
	********************/

	// get the first node in the list
	T* getFirst();

	// get the last node in the list
	T* getLast();

	// get the ith node in the list
	T* get(int i);

	// get the size of the list
	int getSize();

	// check if the list is empty
	bool isEmpty();

	void clear();


	/*********************
	* MUTATORS
	********************/

	// add new node to the front of the list
	void addFirst(T*);

	// add new node to the end of the list
	void addLast(T*);

	//// add new node to the ith position of the list
	void add(int, T*);

	// remove first node from the list
	T* removeFirst();

	// remove last node from the list
	T* removeLast();

	// remove ith node from the list
	T* remove(int);

};

#endif	// end of class LinkedList