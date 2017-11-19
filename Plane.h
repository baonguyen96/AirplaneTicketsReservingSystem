/*
* Class: Plane
*
* This abstract class represent a typical airplane.
*
* Designed by:	Team 4
*
* Features:
*		Hold seating chart 
*		Keep track of reserved/available seats and other related fields
*		Keep track of wait list
*		Automatically "fly" and update wait list/seating chart
*		File input/output
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

#ifndef PLANE_H
#define PLANE_H
#include <string>
#include "Seat.h"
#include "Waitlist.h"
using namespace std;

class Plane
{
protected:
	string *seatingChart;		// seating chart of the airplane
	int capacity;				// total number of seat of the airplane
	int totalSeat;				// total reserved seat
	int businessClassSeats;		// total number of business class seats
	string flightCode;			// code represent the flight
	string type;				// airplane type (Boeing or Airbus)
	string departLocation;		// leaving place
	string arriveLocation;		// destination
	string fileName;			// file containing the seating chart of the particular plane
	WaitList *waitList;			// hold the waitlist for this plane

public:
	/*********************
	* CONSTRUCTOR
	********************/

	// default constructor
	Plane();

	// overloaded constructor
	Plane(int, string, string, string, string);


	/*********************
	* DESTRUCTOR
	********************/
	virtual ~Plane();


	/*********************
	* ACCESSORS
	*********************/

	// display the seat arrangement in the plane
	virtual void printSeats() = 0;

	// check to see if the seat is available
	bool isAvailable(int);

	// get the flight code of the plane
	string getFlightCode();
	
	// get the departure location
	string getDepartingLocation();

	// get the arrival location
	string getArrivingLocation();

	// get the total available seats in the plane
	int getAvailability();

	// get the plane's capacity (maximum seats)
	int getCapacity();

	// get the plane's total business class seat
	int getTotalBusinessClassSeats();

	// check the availability of the waitlist
	bool isAvailableInWaitlist(int);


	/*********************
	* MUTATORS
	*********************/

	// reserve a (sequence of) seat
	void reserve(Seat [], int, int);

	// save to waitlist
	void putOnWaitlist(Ticket*);

	// cancel the order if it is in the waitlist
	Ticket* cancelOrderInWaitlist(string);

protected:
	// load the seating chart from a file
	void load();

	// display plane's info
	void printPlaneInfo();

	// save the seating chart back to the file in the same format
	virtual void save() = 0;

private:
	// check to see if the plane needs to depart
	bool isFlyable();

	// load order from the waitlist into the plane
	void loadFromWaitList();

	// make the plane empty (fly it)
	void makeEmpty();

	// check the seats in the waitlist to see which one can be put into the airplane
	int getBestLoadableWaitlistTicket();

	// get the minimum ticket group size in the wait list
	int getMinimumTicketSize();

};

#endif