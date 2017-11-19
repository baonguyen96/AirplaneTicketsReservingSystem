/*
* Class: LinkedList (template)
*
* This class is an implementation of LinkedList data structure.
* Features:
*		Doubly linked list
*		Add/remove new node anywhere in the list
*
* Designed by:	Team 4
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

#include "LinkedList.h"
#include <iostream>
using namespace std;

/***********************
* CONSTRUCTOR
***********************/
template <class T>
LinkedList<T>::LinkedList()
{
	first = nullptr;
	last = nullptr;
	size = 0;
}

/**********************
* DESTRUCTOR
***********************/
template <class T>
LinkedList<T>::~LinkedList()
{
	clear();
	delete first;
	delete last;
}


/********************************************************
* function: isValidIndex
* parameter: index: integer
* return: bool
* check to see if the given index is inside of the list
*********************************************************/
template <class T>
bool LinkedList<T>::isValidIndex(int index)
{
	return (0 <= index && index < size);
}


/*******************************************
* function: isEmpty
* parameter: void
* return: bool
* check to see if the list is empty or not
********************************************/
template <class T>
bool LinkedList<T>::isEmpty()
{
	return size == 0;
}


/*******************************************
* function: getSize
* parameter: void
* return: int
* return the number of nodes in the list
********************************************/
template <class T>
int LinkedList<T>::getSize()
{
	return size;
}


/*******************************************
* function: getFirst
* parameter: void
* return: T*: template pointer
* return the first node of the list
********************************************/
template <class T>
T* LinkedList<T>::getFirst()
{
	return first->data;
}


/*******************************
* function: get
* parameter: i: integer
* return: T*: template pointer
* get the ith node in the list
********************************/
template <class T>
T* LinkedList<T>::get(int index) 
{
	/*
	* check to see if the index is in the domain of [0, size)
	* if not, print out error message and return null
	*/
	if (!isValidIndex(index))
	{
		cout << "Error: position is not in range.\n";
		return nullptr;
	}

	/*
	* if the given index is in the first half of the list,
	* find it from the front of the list.
	* if the given index is in the second half of the list,
	* find it from the back of the list.
	* (ensure better run time)
	*/
	Node* currentPointer;

	if (index < size / 2)
	{
		int currentPosition = 0;
		currentPointer = first;

		// keep moving the currentPointer to the index position
		while (currentPosition != index)
		{
			currentPointer = currentPointer->next;
			currentPosition++;
		};
	}
	else
	{
		int currentPosition = size - 1;
		currentPointer = last;

		// keep moving the currentPointer to the index position
		while (currentPosition != index)
		{
			currentPointer = currentPointer->previous;
			currentPosition--;
		}
	}

	return currentPointer->data;
}


/*******************************************
* function: getLast
* parameter: void
* return: T*: pointer to the template type
* return the last node of the list
********************************************/
template <class T>
T* LinkedList<T>::getLast() 
{
	return last->data;
}


/*******************************************
* function: addFirst
* parameter: T*: template pointer
* return: void
* add new node to the front of the list
********************************************/
template <class T>
void LinkedList<T>::addFirst(T* data)
{
	// setup the node for the LinkedList
	Node* node = new Node();
	node->data = data;
	node->next = node->previous = nullptr;

	/*
	* add the new node to the front of the list
	* if the list is empty, point first & last to the new node
	* if the list is not empty, establish the links between new node and first,
	*		then move the firstPointer to the node
	* finally, increment the size of the list
	*/
	if (isEmpty())
	{
		first = last = node;
	}
	else
	{
		node->next = first;
		first->previous = node;
		first = node;
	}
	size++;
}


/*************************************************
* function: add
* parameter: index: integer
*			 T*: template pointer
* return: void
* add new node to the ith position of the list
**************************************************/
template <class T>
void LinkedList<T>::add(int index, T* data)
{
	// setup the node for the LinkedList
	Node* node = new Node();
	node->data = data;
	node->next = node->previous = nullptr;

	/*
	* check to see if the index is in the domain of [0, size)
	* if not, print out error message and return null
	*/
	if (!isValidIndex(index))
	{
		cout << "Error: position is not in range.\n";
		return;
	}

	/*
	* add the new node to the ith position of the list
	* if the list is empty, point first & last to the new node
	* if the list is not empty,
	*		go to the position of index - 1
	*		then establish the bidirectional links between the currentPointer and the new node
	* finally, increment the size of the list
	*/
	if (isEmpty())
	{
		first = last = node;
	}
	else
	{
		Node* currentPointer;

		/*
		 * if the index is in the first half of the list, go from the front
		 * if the index is in the second half of the list, go from the back
		 */
		if (index < size / 2)
		{
			int currentPosition = 0;
			currentPointer = first;

			// keep moving the currentPointer to the index position
			while (currentPosition != index - 1)
			{
				currentPointer = currentPointer->next;
				currentPosition++;
			}
		}
		else
		{
			int currentPosition = size - 1;
			currentPointer = last;

			// keep moving the currentPointer to the index position
			while (currentPosition != index - 1)
			{
				currentPointer = currentPointer->previous;
				currentPosition--;
			}
		}

		// add node
		node->next = currentPointer->next;
		currentPointer->next->previous = node;
		currentPointer->next = node;
		node->previous = currentPointer;
	}

	size++;
}


/*******************************************
* function: addLast
* parameter: T*: template pointer
* return: void
* add new node to the end of the list
********************************************/
template <class T>
void LinkedList<T>::addLast(T* data)
{
	// setup the node for the LinkedList
	Node* node = new Node();
	node->data = data;
	node->next = node->previous = nullptr;

	/*
	* add the new node to the end of the list
	* if the list is empty, point firstPoiter to the new node
	* if the list is not empty, establish the links between new node and last,
	*		then move the lastPointer to the node
	* finally, increment the size of the list
	*/
	if (isEmpty())
	{
		first = last = node;
	}
	else
	{
		node->previous = last;
		last->next = node;
		last = node;
	}
	size++;
}


/********************************************************
* function: removeFirst
* parameter: void
* return: T*: template pointer
* remove the first node from the list and return it
*********************************************************/
template <class T>
T* LinkedList<T>::removeFirst()
{
	if (isEmpty())
	{
		cout << "The list is empty.\n";
		return nullptr;
	}
	else if (size == 1)
	{
		return removeOnly();
	}
	else
	{
		Node* hold = first;
		first = first->next;
		first->previous = nullptr;
		hold->next = nullptr;
		size--;
		T* data = hold->data;
		delete hold;
		return data;
	}
}


/********************************************************
* function: remove
* parameter: index: int
* return: T*: template pointer
* remove the ith node from the list and return it
*********************************************************/
template <class T>
T* LinkedList<T>::remove(int index)
{
	/*
	* check to see if the index is in the domain of [0, size)
	* if not, print out error message and return null
	*/
	if (!isValidIndex(index))
	{
		cout << "Error: position is not in range.\n";
		return nullptr;
	}
	else if (isEmpty())	// empty list
	{
		cout << "The list is empty.\n";
		return nullptr;
	}
	else if (size == 1)	// only 1 element in the list
	{
		return removeOnly();
	}
	else if (index == 0)	// remove the first node in the list
	{
		return removeFirst();
	}
	else if (index == size - 1)	// remove the last node in the list
	{
		return removeLast();
	}
	else	// remove the in-between nodes in the list
	{
		Node* currentPointer;

		// find the removal node from first half
		if (index < size / 2)
		{
			int currentPosition = 0;
			currentPointer = first;

			// keep moving the currentPointer to the index position
			while (currentPosition != index - 1)
			{
				currentPointer = currentPointer->next;
				currentPosition++;
			}
		}
		// find the removal node from second half
		else
		{
			int currentPosition = size - 1;
			currentPointer = last;

			// keep moving the currentPointer to the index position
			while (currentPosition != index - 1)
			{
				currentPointer = currentPointer->previous;
				currentPosition--;
			}
		}

		// break the links and return the data of the removal node
		Node* removalNode = currentPointer->next;
		currentPointer->next = removalNode->next;
		removalNode->next->previous = currentPointer;
		removalNode->next = removalNode->previous = nullptr;

		size--; 
		
		T* data = removalNode->data;
		delete removalNode;
		return data;
	}
}


/********************************************************
* function: removeLast
* parameter: void
* return: T*: template pointer
* remove the last node from the list and return it
*********************************************************/
template <class T>
T* LinkedList<T>::removeLast()
{
	if (isEmpty())
	{
		cout << "The list is empty.\n";
		return nullptr;
	}
	else if (size == 1)
	{
		return removeOnly();
	}
	else
	{
		Node* hold = last;
		last = last->previous;
		last->next = nullptr;
		hold->previous = nullptr;

		size--; 
		
		T* data = hold->data;
		delete hold;
		return data;
	}
}


/***************************************************************
* function: removeOnly
* parameter: void
* return: T*: template pointer
* remove the only node from the list and return its data
****************************************************************/
template <class T>
T* LinkedList<T>::removeOnly()
{
	T* data = first->data;
	first = last = nullptr;
	size--;
	return data;
}


/***************************************************************
* function: clear
* parameter: void
* return: void
* clear out all nodes in the linked list
****************************************************************/
template <class T>
void LinkedList<T>::clear()
{
	while (size != 0)
	{
		delete removeFirst();
	}

	first = last = nullptr;
}