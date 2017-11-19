/*
* Class: LinkedList (template)
*
* This class represents the report of each time the program runs.

* Features:
*		Keep track of all the tickets generated in the current run
*		Calculate total profit of the current run
*		Save the current report list to the file in appending mode
*
* Designed by:	Team 4
*
*/

#ifndef REPORT_H
#define REPORT_H

#include "LinkedList.cpp"
#include "Ticket.h"

class Report
{
private:
	LinkedList<Ticket> *ticketsSold;	// the list of all the reserved ticket of the current run
	double dailyProfit;					// total tickets' prices of the current report

	// save the report back into the file
	void save();

	// sum all tickets' prices in the report
	void countDailyProfit();

public:

	/*********************
	* CONSTRUCTOR
	********************/
	Report();


	/*********************
	* DESTRUCTOR
	********************/
	~Report();
	

	/*********************
	* MUTATOR
	********************/

	// add new ticket into the report
	void add(Ticket *);

};

#endif