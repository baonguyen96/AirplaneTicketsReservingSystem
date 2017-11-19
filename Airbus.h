/*
* Class: Airbus
*
* This class is an inheritance of the Plane abstract class.
* It implement the functions printSeats and save of its base class.
*
* Designed by:	Team 4
*
* List of methods:
*	constructor and destructor
*	printSeats: display the seat arrangment in the plane
*	save: save the seating chart back to the file in the same format

*/

#ifndef AIRBUS_H
#define AIRBUS_H
#include "Plane.h"

class Airbus : public Plane
{
private:
	string seatingFile;		// the name of the file containing Boeing type seating chart

public:

	/*********************
	* CONSTRUCTOR
	********************/
	Airbus() : Plane()
	{
		seatingFile = "";
	}

	// overloaded constructor
	Airbus(string, string, string, string);


	/*********************
	* DESTRUCTOR
	********************/
	~Airbus();


	/*********************
	* OVERRIDE FUNCTIONS
	********************/

	// display the seat arrangment in the plane
	virtual void printSeats() override;

	// save the seating chart back to the file in the same format
	virtual void save() override;
};

#endif