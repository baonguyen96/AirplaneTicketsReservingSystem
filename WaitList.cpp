/*
* File: WaitList.cpp
*
* This class contains the implementation of all the methods of the WaitList class
*
* Designed by:	Team 4
*
* List of methods:
*		constructor and destructor
*		save: save the waitlist into the file
*		load: load the waitlist from the file
*		add: add new ticket to the end of the waitlist
*		remove: remove the first ticket from the waitlist
*		remove: remove the ith ticket from the waitlist
*		getSize: return the size of the waitlist
*		isEmpty: check if the wait list is empty
*		getFirst: return the first ticket of the waitlist
*		get: return the ith ticket of the waitlist
*
*/

#include "WaitList.h"
#include "LinkedList.cpp"
#include <iostream>
#include <fstream>			// work with files
using namespace std;


/****************************************************
* CONSTRUCTOR
*****************************************************/
WaitList::WaitList(string flight)
{
	waitlist = new LinkedList<Ticket>();
	flightFileName = flight;

	load();
}


/****************************************************
* DESTRUCTOR
*****************************************************/
WaitList::~WaitList()
{
	save();
	delete waitlist;
}

/****************************************************
* function: save
* parameter:
* return: void
* save the current waitlist back into the file 
* and override the old file
*****************************************************/
void WaitList::save()
{
	ofstream outputFile(flightFileName + "_waitlist.txt");

	// loop each ticket in the waitlist to write it to the file
	for (int i = 0; i < waitlist->getSize(); i++)
	{
		//Ticket* ticket = waitlist->get(i);
		outputFile << waitlist->get(i)->toString() << "---------- ----------\n";
		//delete ticket;
	}

	outputFile.close();
}


/****************************************************
* function: load
* parameter:
* return: void
* read data from the file to construct the waitlist
*****************************************************/
void WaitList::load()
{
	// try to open the waitlist.txt file as input mode
	ifstream inputFile(flightFileName + "_waitlist.txt");

	// cannot open the file
	if (inputFile.fail())
		cout << "Cannot open the file.\n";
	// open successfully
	else
	{
		string category = "", data = "", name = "", flightCode = "", confirmationCode = "";
		int age = 0, seatNumber = 0, ticketNumber = 0, size = 0, seatCount = 0;
		double price = 0;
		//bool readStuff = false;
		Seat* seats = nullptr;

		// start reading from the file
		inputFile >> category;
		inputFile >> data;

		// keep reading till the end of the file
		while (!inputFile.eof())
		{
			//readStuff = true;

			if (category == "Ticket:")
			{
				ticketNumber = stoi(data);
				seatCount = 0;
			}
			else if (category == "Size:")
			{
				size = stoi(data);

				// allocate space for the seat array;
				seats = new Seat[size];
			}
			else if (category == "Flight:")
			{
				flightCode = data;
			}
			else if (category == "Name:")
			{
				name = data;

				/*
				* keep reading data for name because it may contain white spaces
				* stop whenever the data is "Age:" (new category)
				*/
				inputFile >> data;
				while (data != "Age:")
				{
					name += " " + data;
					inputFile >> data;
				}

				/*
				* done reading the name
				* set the category to be the current data,
				* then go to the READ_DATA label to read in the new data
				*/
				category = data;
				goto READ_DATA;
			}
			else if (category == "Age:")
			{
				age = stoi(data);
			}
			else if (category == "Seat:")
			{
				seatNumber = stoi(data);
			}
			else if (category == "Price:")
			{
				price = stod(data);

				// fill the seat in the array
				seats[seatCount].setReserver(new Person(name, age));
				seats[seatCount].setSeatNumber(seatNumber, price);

				seatCount++;

				// done getting all seats, add the ticket to the waitlist
				if (seatCount == size)
				{
					Ticket* ticket = new Ticket(seats, size, flightCode, ticketNumber);
					add(ticket);
				}

			}

			inputFile >> category;

			READ_DATA:	// label to jump to

			inputFile >> data;

		}	// end while (not eof)

		// close the file after finish reading
		inputFile.close();

	}	// end else (open successfully)
}


/****************************************************
* function: getSize
* parameter: 
* return: int
* return the length of the waitlist
*****************************************************/
int WaitList::getSize()
{
	return waitlist->getSize();
}


/****************************************************
* function: add
* parameter: ticket: Ticket pointer
* return: void
* add new ticket to the end of the waitlist
*****************************************************/
void WaitList::add(Ticket *ticket)
{
	waitlist->addLast(ticket);
}


/****************************************************
* function: remove
* parameter:
* return: Ticket pointer
* remove and return the first ticket in the waitlist
*****************************************************/
Ticket* WaitList::remove()
{
	return waitlist->removeFirst();
}


/****************************************************************
* function: remove (overloaded)
* parameter: index: int
* return: Ticket pointer
* remove and return the ticket at a given index in the waitlist
*****************************************************************/
Ticket* WaitList::remove(int index)
{
	return waitlist->remove(index);
}


/****************************************************
* function: get
* parameter:
* return: Ticket pointer
* return, but not remove, the ticket at a given index
*****************************************************/
Ticket* WaitList::get(int index)
{
	return waitlist->get(index);
}


/******************************************************
* function: getFirst
* parameter:
* return: Ticket pointer
* return, but not remove, the first ticket in the list
*******************************************************/
Ticket* WaitList::getFirst()
{
	return waitlist->getFirst();
}


/******************************************************
* function: isEmpty
* parameter:
* return: bool
* check if the wait list is empty
*******************************************************/
bool WaitList::isEmpty()
{
	return waitlist->isEmpty();
}

