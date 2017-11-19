/*
* File: Seat.cpp
*
* This file contains the implementation of all the methods of Seat class
*
* Designed by:	Team 4
*
* List of methods:
*		constructors and destructor
*		getSeatNumber: return the seat's number
*		getPrice: return the price of the seat
*		getReserver: return the seat's reserver
*		toString: convert the seat's info into a string
*		setSeatNumber: set the seat's number
*		setSeatNumber: set the seat's number (overloaded)
*		setReserver: set the seat's reserver
*		cancel: cancel the seat reservation
*		operator=: overloaded the assignment oeprator
*
*/

#include "Seat.h"
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;


/****************************************
* CONSTRUCTOR
*****************************************/
Seat::Seat()
{
	seatNumber = 0;
	reserver = nullptr;	
	price = 0;
}


/****************************************
* OVERLOADED CONSTRUCTOR
*****************************************/
Seat::Seat(int number, double p, Person *person)
{
	seatNumber = number;
	reserver = person;
	price = p;
}



/****************************************
* COPY CONSTRUCTOR
*****************************************/
Seat::Seat(const Seat* right)
{
	seatNumber = right->seatNumber;
	reserver = right->reserver;
	price = right->price;
}



/****************************************
* DESTRUCTOR
*****************************************/
Seat::~Seat()
{
	delete reserver;
}


/****************************************
* function: getPrice
* parameter:
* return: double
* return the price of the seat
*****************************************/
double Seat::getPrice()
{
	return price;
}


/****************************************
* function: getSeatNumber
* parameter:
* return: int
* return the seat's number
*****************************************/
int Seat::getSeatNumber()
{
	return seatNumber;
}


/****************************************
* function: toString
* parameter:
* return: string
* convert the seat's info into a string
*****************************************/
string Seat::toString()
{
	ostringstream priceStream;
	priceStream << fixed << setprecision(2) << price;

	return "\nName: " + reserver->getName() +
		"\nAge: " + to_string(reserver->getAge()) +
		"\nSeat: " + to_string(seatNumber) +
		"\nPrice: " + priceStream.str() + "\n";
}


/****************************************
* function: getReserver
* parameter:
* return: Person pointer
* return the reference of the reserver
*****************************************/
Person* Seat::getReserver()
{
	return reserver;
}


/************************************************
* function: isBusinessClass
* parameter: totalBusinessSeats: int
* return: bool
* check if the current seat is a bussiness class
*************************************************/
bool Seat::isBusinessClass(int totalBusinessSeats)
{
	return seatNumber <= totalBusinessSeats;
}


/****************************************
* function: setSeatNumber
* parameter:	number: int
*				totalBusinessSeat: int
* return: void
* set the seat's number and its price
*****************************************/
void Seat::setSeatNumber(int number, int totalBusinessSeats)
{
	seatNumber = number;

	// set the price
	price = isBusinessClass(totalBusinessSeats) ? BUSINESS_PRICE : ECONOMIC_PRICE;

	// adjust the price according to the reserver's age (child vs adult vs senior)
	if (reserver != nullptr)
	{
		price *= reserver->getDiscountRatio();
	}

}


/****************************************
* function: setSeatNumber (overloaded)
* parameter:	number: int
*				price: double
* return: void
* set the seat's number and its price
*****************************************/
void Seat::setSeatNumber(int number, double pr)
{
	seatNumber = number;
	price = pr;
}

/****************************************
* function: serReserver
* parameter: person: Person pointer
* return: void
* set the reserver of the seat
*****************************************/
void Seat::setReserver(Person *person)
{
	reserver = person;
}


/***********************************************
* function: overload assignment operator
* parameter: right: constant reference of Seat
* return: void
* make a copy of the Seat object
************************************************/
void Seat::operator=(const Seat &right)
{
	reserver = new Person(right.reserver->getName(), right.reserver->getAge());
	seatNumber = right.seatNumber;
	price = right.price;
}


/***********************************************
* function: cancel
* parameter: 
* return: void
* cancel the seat by negating its price
************************************************/
void Seat::cancel()
{
	price *= -1;
}