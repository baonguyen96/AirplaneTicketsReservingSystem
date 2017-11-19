/*
* File: Ticket.cpp
*
* This class contains the implementation of all the methods of the Ticket class
*
* Designed by:	Team 4
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

#include "Ticket.h"
#include <iostream>
using namespace std;


// static member to keep track of the total number of ticket
int Ticket::totalTicket = 0;


/****************************************
* CONSTRUCTOR
*****************************************/
Ticket::Ticket(Seat seats[], int size, string flight, int ticketNum)
{
	seatInfo = seats;
	flightInfo = flight;
	groupSize = size;

	if (ticketNum <= 0)
	{
		totalTicket++;					// increment total number of tickets
		ticketNumber = totalTicket;		// set the current ticket's number to the current total ticket
	}
	else
	{
		ticketNumber = ticketNum;
	}

	countPrice();
	setConfirmationCode();
}


/****************************************
* COPY CONSTRUCTOR
*****************************************/
Ticket::Ticket(Ticket* right)
{
	// copy values from the right object to this object
	flightInfo = right->flightInfo;
	groupSize = right->groupSize;
	ticketNumber = right->ticketNumber;
	totalTicket = right->totalTicket;
	totalPrice = right->totalPrice;
	confirmationCode = right->confirmationCode;
	seatInfo = new Seat[groupSize];

	// copy the VALUES of each seat in the array
	for (int i = 0; i < groupSize; i++)
	{
		seatInfo[i] = right->getSeats()[i];
	}
}


/****************************************
* DESTRUCTOR
* deallocate memory of the seatInfo array
*****************************************/
Ticket::~Ticket()
{
	delete [] seatInfo;
}


/****************************************
* function: countPrice
* parameter:
* return: void
* count the sum of all seat's price
*****************************************/
void Ticket::countPrice()
{
	// sum of all seats' prices in the ticket
	for (int i = 0; i < groupSize; i++)
	{
		totalPrice += seatInfo[i].getPrice();
	}
}


/****************************************
* function: print
* parameter:
* return: void
* display the ticket's info to the screen
*****************************************/
void Ticket::print()
{
	cout << toString();
}


/****************************************
* function: getGroupSize
* parameter:
* return: int
* return the total seats of the ticket
*****************************************/
int Ticket::getGroupSize()
{
	return groupSize;
}


/****************************************
* function: toStrig
* parameter:
* return: void
* convert the ticket's info to a string
*****************************************/
string Ticket::toString()
{
	string ticketSummary = "Ticket: " + to_string(ticketNumber) +
				"\nSize: " + to_string(groupSize) +
				"\nFlight: " + flightInfo + 
				"\nConfirmation: " + confirmationCode + "\n";

	for (int i = 0; i < groupSize; i++)
	{
		ticketSummary += seatInfo[i].toString();
	}

	return ticketSummary;
}


/****************************************
* function: getPrice
* parameter:
* return: void
* return the total price of the ticket
*****************************************/
double Ticket::getPrice()
{
	return totalPrice;
}


/****************************************
* function: getTicketCount
* parameter:
* return: void
* return the total number of ticket
*****************************************/
int Ticket::getTicketCount()
{
	return totalTicket;
}


/****************************************
* function: getTicketNumber
* parameter:
* return: void
* return the ticket number
*****************************************/
int Ticket::getTicketNumber()
{
	return ticketNumber;
}


/****************************************
* function: getSeats
* parameter:
* return: Seat pointer
* return the seat array or pointer
*****************************************/
Seat* Ticket::getSeats()
{
	return seatInfo;
}


/****************************************
* function: getConfirmationCode
* parameter:
* return the string of confirmation code
*****************************************/
string Ticket::getConfirmationCode()
{
	return confirmationCode;
}


/****************************************
* function: setConfirmationCode
* parameter:
* setup the confirmation code
*****************************************/
void Ticket::setConfirmationCode()
{
	/*
	 * setup the confirmation code in the format:
	 *		flightInfo_ticketNumber_groupSize_firstSeatNumber
	 */
	confirmationCode = flightInfo;
	confirmationCode += ("_" + to_string(ticketNumber));
	confirmationCode += ("_" + to_string(groupSize));
	confirmationCode += ("_" + to_string(seatInfo[0].getSeatNumber()));
}



/****************************************
* function: cancel
* parameter:
* cancel the ticket
*****************************************/
void Ticket::cancel()
{
	// negate the price
	totalPrice *= -1;

	// cancel every seat in the order
	for (int i = 0; i < groupSize; i++)
	{
		seatInfo[i].cancel();
	}
}

