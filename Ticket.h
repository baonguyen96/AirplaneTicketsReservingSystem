/*
*
* CS/SE 3376.001
* Team 4
*
* Class: Ticket
*
* This class represents the receipt/confirmation of one order

* Features:
*		Keep track of number of seats and total price of an order
*		Automatically generate different ticket number each time a ticket object is created
*
* List of methods:
*		constructors and destructor
*		countPrice: count the total price of the ticket
*		setConfirmationCode: setup the confirmation code
*		print: display the current ticket to the console
*		getPrice: return the total price of the ticket
*		toString: return the string representation of the ticket
*		getTicketCount: return the total number of tickets created
*		getTicketNumber: return the current ticket's number
*		getGroupSize: return the total number of seats of the current ticket
*		getSeats: return the seat array of the ticket
*		getConfirmationCode: return the confirmation code of the ticket
*		cancel: cancel the ticket reservation
*		overloaded assignment operator
*
*/

#ifndef TICKET_H
#define TICKET_H

#include "Seat.h"
#include <string>

class Ticket
{
private:
	Seat *seatInfo;				// array of seats in the current ticket
	double totalPrice;			// sum of all seats' prices in the ticket
	string flightInfo;			// flight code of the ticket
	static int totalTicket;		// keep track of the total tickets created
	int ticketNumber;			// the number of the current ticket
	int groupSize;				// total number of seats in the current ticket
	string confirmationCode;	// confirmation code of the ticket

	// count the total price of the ticket
	void countPrice();

	// setup the confirmation code
	void setConfirmationCode();

public:
	/******************
	* CONSTRUCTOR
	*******************/
	Ticket(Seat[], int, string, int);


	/******************
	* COPY CONSTRUCTOR
	*******************/
	Ticket(Ticket*);



	/******************
	* DESTRUCTOR
	*******************/
	~Ticket();


	/******************
	* ACCESSORS
	*******************/

	// display the current ticket to the console
	void print();

	// return the total price of the ticket
	double getPrice();

	// return the string representation of the ticket
	string toString();

	// return the total number of tickets created
	static int getTicketCount();

	// return the current ticket's number
	int getTicketNumber();

	// return the total number of seats of the current ticket
	int getGroupSize();

	// return the seat array of the ticket
	Seat* getSeats();

	// return the confirmation code of the ticket
	string getConfirmationCode();

	// cancel the ticket reservation
	void cancel();

};

#endif