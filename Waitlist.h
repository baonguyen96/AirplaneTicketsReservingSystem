/*
*
* CS/SE 3376.001
* Team 4
*
* Class: WaitList
*
* This class is like a queue to hold the waiting tickets.
*
* Features:
*		Add ticket to the end of the list
*		Remove ticket from the front (or anywhere) of the list
*		Access the ticket at a given index of the list
*
* List of methods:
*		constructor and destructor
*		save: save the waitlist into the file
*		load: load the waitlist from the file
*		add: add new ticket to the end of the waitlist
*		remove: remove the first ticket from the waitlist
*		remove: remove the ith ticket from the waitlist
*		getSize: return the size of the waitlist
*		isEmpty: check if the wait list is empty
*		getFirst: return the first ticket of the waitlist
*		get: return the ith ticket of the waitlist
*/

#ifndef WAIT_LIST_H
#define WAIT_LIST_H

#include "LinkedList.h"
#include "Ticket.h"
#include <string>

class WaitList
{
private:
	LinkedList<Ticket> *waitlist;	// the list of tickets to be held
	string flightFileName;			// the flight that the wait list belongs to

	// save the waitlist into the file
	void save();

	// load the waitlist from the file
	void load();

public:

	/*********************
	 * CONSTRUCTORS
	 *********************/
	WaitList(string);


	/*********************
	* DESTRUCTOR
	*********************/
	~WaitList();


	/*********************
	* MUTATORS
	*********************/

	// add new ticket to the end of the waitlist
	void add(Ticket *);

	// remove the first ticket from the waitlist
	Ticket* remove();

	// remove the ith ticket from the waitlist
	Ticket* remove(int);


	/*********************
	* ACCESSORS
	*********************/

	// return the size of the waitlist
	int getSize();

	// check if the wait list is empty
	bool isEmpty();

	// return the first ticket of the waitlist
	Ticket* getFirst();

	// return the ith ticket of the waitlist
	Ticket* get(int);

};

#endif