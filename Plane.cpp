/*
* Class: Plane 
*
* Implementation of the Plane.h
*
* Designed by:	team 4
*
* List of methods:
*		printSeats: display the seat arrangement in the plane
*		isAvailable: check to see if the seat is available
*		getFlightCode: get the flight code of the plane
*		getDepartingLocation: get the departure location
*		getArrivingLocation: get the arrival location
*		getAvailability: get the total available seats in the plane
*		getCapacity: get the plane's capacity (maximum seats)
*		getTotalBusinessClassSeats: get the plane's total business class seat
*		isAvailableInWaitlist: check the availability of the waitlist
*		reserve: reserve a (sequence of) seat
*		putOnWaitlist: save to waitlist
*		cancelOrderInWaitlist: cancel the order if it is in the waitlist
*		load: load the seating chart from a file
*		printPlaneInfo: display plane's info
*		save: save the seating chart back to the file in the same format
*		isFlyable: check to see if the plane needs to depart
*		loadFromWaitList: load order from the waitlist into the plane
*		makeEmpty: make the plane empty (fly it)
*		getBestLoadableWaitlistTicket: check the seats in the waitlist to see which one can be put into the airplane
*		getMinimumTicketSize: get the minimum ticket group size in the wait list
*
*/

#include "Plane.h"
#include <fstream>
#include <iostream>


/***********************
* DEFAULT CONSTRUCTOR
***********************/
Plane::Plane()
{
	flightCode = "";
	capacity = 0;
	seatingChart = nullptr;
	businessClassSeats = 0;
	totalSeat = 0;
	departLocation = "";
	arriveLocation = "";
	fileName = "";
	waitList = nullptr;
}


/***************************
* OVERLOADED CONSTRUCTOR
***************************/
Plane::Plane(int cap, string fc, string depart, string arrive, string file)
{
	flightCode = fc;
	capacity = cap;
	seatingChart = new string[capacity];
	businessClassSeats = 0;
	departLocation = depart;
	arriveLocation = arrive;
	totalSeat = 0;
	fileName = file;
	waitList = new WaitList(file);

	// load the seating chart from the file
	load();

	// load from the waitlist
	loadFromWaitList();
}


/***************************
* DESTRUCTOR
***************************/
Plane::~Plane()
{
	delete waitList;
	delete [] seatingChart;	
}


/****************************************************
* function: load
* parameter: inputFile: string
* return: void
* read from the file and save the seat into an array
*****************************************************/
void Plane::load()
{
	ifstream inputFile(fileName + ".txt");

	if (!inputFile)
	{
		cout << "Cannot open the file \"" + fileName + ".txt\".\n";
		return;
	}

	for (int i = 0; i < capacity; i++)
	{
		inputFile >> seatingChart[i];

		// increment totalSeat whenever find a reserved seat
		if (seatingChart[i] == "XXX" || seatingChart[i] == "XX")
			totalSeat++;
	}

	inputFile.close();
}


/*************************************************************
* function: getAvailability
* parameter:
* return: int
* return the number of seats that are available to reserve
**************************************************************/
int Plane::getAvailability()
{
	return capacity - totalSeat;
}


/*************************************************************
* function: getCapacity
* parameter:
* return: int
* return the total number of seats on the airplane
**************************************************************/
int Plane::getCapacity()
{
	return capacity;
}


/***********************************************
* function: getTotalBusinessClassSeats
* parameter:
* return: int
* return the number of business class seats
************************************************/
int Plane::getTotalBusinessClassSeats()
{
	return businessClassSeats;
}


/*************************************************************
* function: isAvailable
* parameter: seatNumber: int
* return: bool
* check the given seat to see if it is available to reserve
**************************************************************/
bool Plane::isAvailable(int seatNumber)
{
	return (seatingChart[seatNumber] != "XX" && seatingChart[seatNumber] != "XXX");
}


/****************************************
* function: getFlightCode
* parameter: 
* return: void
* returnt the plane's flight code
*****************************************/
string Plane::getFlightCode()
{
	return flightCode;
}


/****************************************
* function: getDepartingLocation
* parameter:
* return: void
* returnt the plane's departure location
*****************************************/
string Plane::getDepartingLocation()
{
	return departLocation;
}


/****************************************
* function: getArrivingLocation
* parameter:
* return: void
* returnt the plane's destination
*****************************************/
string Plane::getArrivingLocation()
{
	return arriveLocation;
}


/****************************************
* function: reserve
* parameter:	seats: Seat[]
*				startingSeat: int
*				size: int
* return: void
* reserve the given set of seat(s)
*****************************************/
void Plane::reserve(Seat seats[], int startingSeat, int size)
{
	// reserve each seat in the array
	for (int i = startingSeat; i < size; i++)
	{
		int number = seats[i].getSeatNumber() - 1;

		// mark the reserved seats as XX or XXX
		seatingChart[number] = (seatingChart[number].size() == 2) ? "XX" : "XXX";
	}

	// increase the total reserved seats
	totalSeat += size;

	/*
	 * after each reservating process, check to see if the plane 
	 * is able to fly or not. If it is, "fly" it off by making
	 * it empty. Then reserve the seats in the wait list to the plane.
	 */
	if (isFlyable())
	{
		makeEmpty();
		loadFromWaitList();
	}
}


/***************************************************************
* function: makeEmpty
* parameter:
* return: void
* when the plane is full (or almost full but cannot fit any 
* group from the waitlist), "fly" it off by making empty so 
* it can start taking reservations again
***************************************************************/
void Plane::makeEmpty()
{
	for (int i = 0; i < capacity; i++)
	{
		// reset the data of the array to the value of its index + 1
		if (i < 9)
		{
			seatingChart[i] = ((seatingChart[i].size() == 3) ? "00" : "0") + to_string((i + 1));
		}
		else if (9 <= i && i < 99)
		{
			seatingChart[i] = ((seatingChart[i].size() == 3) ? "0" : "") + to_string((i + 1));
		}
		else
		{
			seatingChart[i] = to_string((i + 1));
		}

	}
	totalSeat = 0;
}


/************************************************
* function: isFlyable
* parameter:
* return: boolean
* check to see if the plane needs to depart
**************************************************/
bool Plane::isFlyable()
{
	/*
	 * conditions for the plane to fly (return true):
	 *		1. the plane is full
	 *		2. the total available seat is less than 
	 *			the minimum ticket size in the wait list
	 *			AND is also less than 10% of the plane's capacity
	 */
	if (totalSeat == capacity)
	{
		return true;
	}
	else if (getAvailability() < (capacity / 10) && 
			getAvailability() < getMinimumTicketSize())
	{
		return true;
	}
	else
	{
		return false;
	}
}


/************************************************
* function: printPlaneInfo
* parameter:
* return: void
* display the basic airplane's info
**************************************************/
void Plane::printPlaneInfo()
{
	cout << "Plane type: " << type
		<< "\nFlight code: " << flightCode
		<< "\nDepart: " << departLocation
		<< "\nArrive: " << arriveLocation
		<< "\nAvailable seats: " << getAvailability() << "\n";
}


/************************************************
* function: isAvailableInWaitlist
* parameter:	seatNumber: int
* return: bool
* check to see if the seat is not in the waitlist
**************************************************/
bool Plane::isAvailableInWaitlist(int seatNumber)
{
	Ticket* ticket = nullptr;

	// loop each ticket
	for (int currentTicket = 0; currentTicket < waitList->getSize(); currentTicket++)
	{
		ticket = waitList->get(currentTicket);

		// loop each seat in the current ticket
		for (int currentSeat = 0; currentSeat < ticket->getGroupSize(); currentSeat++)
		{
			// if found the seat in the waitlist, return false
			if (ticket->getSeats()[currentSeat].getSeatNumber() == seatNumber)
				return false;
		}
	}
	// the seat is not in the current waitlist, return true
	return true;
}



/************************************************
* function: putOnWaitlist
* parameter:	ticket: Ticket pointer
* return: void
* put the new ticket into the wait list
**************************************************/
void Plane::putOnWaitlist(Ticket* ticket)
{
	waitList->add(ticket);
}



/************************************************
* function: getBestLoadableWaitlistTicket
* parameter:
* return: int
* return the index of the best ticket in the 
* waitlist that can be put onto the airplane
**************************************************/
int Plane::getBestLoadableWaitlistTicket()
{
	int bestWaitlistTicket = -1;

	/*
	 * check every ticket in the waitlist (until find the first available ticket)
	 * if the size of the current ticket is less than or equal to 
	 *	the available seats on the plane, continue checking the seats of that ticket
	 * otherwises, check next ticket
	 * for each ticket, check all of its seats
	 *		if there is at least 1 seat that is not available, skip to the next ticket
	 *		if all seats in a particular ticket is available, return the index of that ticket
	 */

	// loop the entire waitlist
	for (int i = 0; i < waitList->getSize(); i++)
	{
		Ticket* ticket = waitList->get(i);
		int ticketSize = ticket->getGroupSize();

		if (getAvailability() >= ticketSize)
		{
			// loop each seat in the current ticket
			for (int s = 0; s < ticketSize; s++)
			{
				/*
				 * if the current seat in the current ticket is not available in the plane,
				 *		break out of the loop and check the next ticket
				 * else, set the index of best ticket to the current ticket's index
				 */
				int seatNumber = ticket->getSeats()[s].getSeatNumber() - 1;

				if (seatingChart[seatNumber] == "XX" || seatingChart[seatNumber] == "XXX")
				{
					bestWaitlistTicket = -1;
					break;
				}
				else
				{
					bestWaitlistTicket = i;
				}
			}

			/*
			 * if the best ticket index is not 0, return it
			 * otherwise, check the next ticket
			 */
			if (bestWaitlistTicket != -1)
			{
				ticket = nullptr;
				return bestWaitlistTicket;
			}
		}

		ticket = nullptr;
	}

	/*
	 * have not returned anything 
	 * -> there is no ticket on the waitlist that can be put into the plane,
	 * return -1
	 */
	return -1;
}


/*******************************************************
* function: loadFromWaitList
* parameter:
* return: void
* load the best ticket from the waitlist into the plane
*********************************************************/
void Plane::loadFromWaitList()
{
	int bestIndex = getBestLoadableWaitlistTicket();

	// there is available ticket to be loaded, reserve it in the plane
	if (bestIndex != -1)
	{
		Ticket* ticket = waitList->remove(bestIndex);

		reserve(ticket->getSeats(), 0, ticket->getGroupSize());
	}
}


/*******************************************************
* function: getMinimumTicketSize
* parameter:
* return: int
* return the minimum ticket group size in the wait list
*********************************************************/
int Plane::getMinimumTicketSize()
{
	// initialize minSize with the 300 (this is much larger than the largest capacity of any airplane)
	int minSize = 300;

	// loop each ticket to check for the minimum group size
	for (int index = 0; index < waitList->getSize(); index++)
	{
		int currentSize = waitList->get(index)->getGroupSize();

		// update minimum size
		if (currentSize < minSize)
		{
			minSize = currentSize;
		}
	}

	return minSize;
}


/*******************************************************
* function: cancelOrderInWaitlist
* parameter: confirmationCode: string
* return: Ticket pointer
* return the cancelled ticket or null if not found
*********************************************************/
Ticket* Plane::cancelOrderInWaitlist(string confirmationCode)
{
	for (int i = 0; i < waitList->getSize(); i++) 
	{
		if (waitList->get(i)->getConfirmationCode() == confirmationCode)
			return waitList->remove(i);
	}
	return nullptr;
}