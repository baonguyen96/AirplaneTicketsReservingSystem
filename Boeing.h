/*
* Class: Boeing
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
*
*/

#ifndef BOEING_H
#define BOEING_H
#include "Plane.h"

class Boeing : public Plane
{
private:
	string seatingFile;		// the name of the file containing Boeing type seating chart

public:
	/*********************
	* CONSTRUCTOR
	********************/
	Boeing() : Plane()
	{
		seatingFile = "";
	}

	// overloaded constructor
	Boeing(string, string, string, string);


	/*********************
	* DESTRUCTOR
	********************/
	~Boeing();


	/*********************
	* OVERRODE FUNCTIONS
	*********************/

	// display the seat arrangment in the plane
	virtual void printSeats() override;

	// save the seating chart back to the file in the same format
	virtual void save() override;

};

#endif