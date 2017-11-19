/*
*
* CS/SE 3376.001
* Team 4
*
* Class: Person
*
* This class is a structure of a seat.

* Features:
*		Seat's number
*		Seat's reserver
*		Seat's price (according to the reserver)
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

#ifndef SEAT_H
#define SEAT_H
#include "Person.h"

class Seat 
{
private:
	int seatNumber;								// the seat number
	double price;								// the seat price
	Person *reserver;							// the reserver of the seat
	const double BUSINESS_PRICE = 200.00;		// price of business seats
	const double ECONOMIC_PRICE = 100.00;		// price of economic seats

	// check to see if the seat is a business class seat or not
	bool isBusinessClass(int);

public:

	/******************
	* CONSTRUCTORS
	*******************/

	// default constructor
	Seat();

	// overloaded constructor
	Seat(int, double, Person *);

	Seat(const Seat*);


	/******************
	* DESTRUCTORS
	*****************/
	~Seat();

	
	/******************
	* ACCESSORS
	*****************/

	// return the seat's number
	int getSeatNumber();

	// return the price of the seat
	double getPrice();

	// return the seat's reserver
	Person* getReserver();

	// convert the seat's info into a string
	string toString();

	
	/******************
	* MUTATORS
	*****************/

	// set the seat's number
	void setSeatNumber(int, int);

	// set the seat's number (overloaded)
	void setSeatNumber(int, double);

	// set the seat's reserver
	void setReserver(Person *);

	// cancel the seat reservation
	void cancel();


	/********************************
	* overload assignment operator 
	********************************/
	void operator=(const Seat &);
};

#endif
