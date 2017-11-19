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
*
*/

#include "Airbus.h"
#include <iostream>		// to use cin/cout
#include <fstream>		// to work with files
using namespace std;


/******************************************
* CONSTRUCTOR
* load the file to store the seating chart
*****************************************/

Airbus::Airbus(string flightCode, string depart, string arrive, string fileName) :
Plane(136, flightCode, depart, arrive, fileName)
{
	type = "Airbus";
	businessClassSeats = 24;
	seatingFile = fileName;
}

/********************************************
* DESTRUCTOR
* save the seating chart back into the file
*********************************************/
Airbus::~Airbus()
{
	save();	
}



/****************************************
* function: printSeats (override)
* parameter:
* return: void
* display the seating arrangement
*****************************************/
void Airbus::printSeats()
{
	printPlaneInfo();

	cout << "Seating chart:\n\n            BUSINESS CLASS\n";
	// display bussiness seats layout
	for (int i = 0; i < businessClassSeats; i++)
	{
		// display the first 6 whitespaces at the beginning of each row
		if (i % 4 == 0)
			cout << "     " << seatingChart[i] << "     ";
		// display the seat then go to new row
		else if ((i + 1) % 4 == 0)
			cout << seatingChart[i] << "\n";
		else
			cout << seatingChart[i] << "     ";
	}

	cout << "            ECONOMIC CLASS\n";

	// display economic seats layout
	for (int i = businessClassSeats; i < capacity; i++)
	{
		if ((i + 4) % 7 == 0)
			cout << seatingChart[i] << "    ";
		else if ((i + 5) % 7 == 0)
			cout << "  " << seatingChart[i] << endl;
		else
			cout << seatingChart[i] << "  ";
	}
}



/*******************************************
* function: save (override)
* parameter: 
* return: void
* save the seating chart back into the file
********************************************/
void Airbus::save()
{
	ofstream outputFile(fileName + ".txt");

	if (!outputFile)
	{
		cout << "Cannot open output file.\n";
		return;
	}

	// display bussiness seats layout
	for (int i = 0; i < businessClassSeats; i++)
	{
		// display the first 6 whitespaces at the beginning of each row
		if (i % 4 == 0)
			outputFile << "     " << seatingChart[i] << "     ";
		// display the seat then go to new row
		else if ((i + 1) % 4 == 0)
			outputFile << seatingChart[i] << "\n";
		else
			outputFile << seatingChart[i] << "     ";
	}

	outputFile << endl;

	// display economic seats layout
	for (int i = businessClassSeats; i < capacity; i++)
	{
		if ((i + 4) % 7 == 0)
			outputFile << seatingChart[i] << "    ";
		else if ((i + 5) % 7 == 0)
			outputFile << "  " << seatingChart[i] << endl;
		else
			outputFile << seatingChart[i] << "  ";
	}
}