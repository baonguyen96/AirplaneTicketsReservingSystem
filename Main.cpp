/*
 * CS/SE 3376.001
 * Professor Goodrum
 * Spring 2016
 * 
 * Project: Airplane Ticket Reservation System
 * Designed by: Team 4:	
 *					Bao Nguyen
 *					Baoan Nguyen
 *					Eric Nguyen
 *					Amit Patel
 * Last modified date: 04/03/2016
 *
 * Program overview:
 *		We will design an airline ticket reservation system. Through 
 *		this program, the user will reserve seat(s) on an airplane 
 *		designating which of the available planes they wish to reserve 
 *		seats on. The program will display a seat map that will outline 
 *		which seats are occupied and which seats are available. From 
 *		the available seats, the user may designate how many additional 
 *		passengers will be flying for that particular flight stating how 
 *		many children, adults, and seniors. From the number of people 
 *		listed, the user will assign each passenger a seat on the plane
 *		based on the availability. A party must fly together and cannot 
 *		be separated. If any seat in the current order is not available
 *		in the airplane, notify the user and check to see if that seat is
 *		currently on the wait list. If it is, the program will prompt the
 *		user to choose another seat. If the seat is not on the wait list 
 *		yet, ask if the user wants to be held in the wait list. If the 
 *		user choose to do so, keep getting seat(s) info like normal, but
 *		when finish, the program will place the current user's ticket onto
 *		the wait list of the selected plane. If the seats are reserved 
 *		successfully (not involving wait list), a confirmation (the receipt
 *		of the ticket) will be generated which will compose of a party name, 
 *		party size, and the plane. Then the current ticket will be append 
 *		to the report list, which contains all ticket receipts of the 
 *		current run. When closing the program, the report list will be 
 *		saved back into the report file (appending to the end, not 
 *		overriding the old file). The program also allows the users to cancel
 *		their reservations (but only those tickets in the wait list). 
 *		All airplane's seating charts and wait lists will also be saved back 
 *		into the appropriate file of each plane and override the old files.
 *
 * List of methods:
 *		getMenu: display the menu and get user's input
 *		isInt: check to see if the string can be casted to an integer
 *		isInRange: check to see if am integer is within the range from lower bound to upper bound
 *		initializePlanes: create new plane objects 
 *		viewPlanes: prompt the user for the plane and display its information to the screen
 *		reserve: let the user reserve seat(s) in a particular airplane
 *		isSelected: check to see if the seat is already selected by the user
 *		quit: deallocate any dynamic memories and close the program
 *		cancelWaitList: let the users cancel their order if they are placed in the wait lists
 *		getYesNo: get the result of the yes no questions from the user
 *		printBigDivider: display the big divider between groups of texts
 *		printSmallDivider: dispalay the small divider between groups of texts
 *		extractFlightInfoFromConfirmCode: extract the flight code from the confirmation code
 */


#include <iostream>
#include "LinkedList.h"
#include "Seat.h"
#include "Person.h"
#include "Ticket.h"
#include "Report.h"
#include "Boeing.h"
#include "Plane.h"
#include "Airbus.h"
#include <string>
#include <iomanip>
using namespace std;


/********************
* GLOBAL VARIABLES
*********************/
const int TOTAL_PLANES = 5;		// total number of planes
Plane* planes[TOTAL_PLANES];	// array of 5 airplanes
Report *report;					// report of the current run


/*********************
* FUNCTION PROTOTYPES
**********************/
int getMenu(string, int, int, bool, bool);
bool isInt(string s);
bool isInRange(int, int, int);
void initializePlanes();
int viewPlanes();
void reserve();
bool isSelected(Seat *, int, int, int);	
void quit();
void cancelWaitList();
bool getYesNo(string);
void printBigDivider();
void printSmallDivider();
string extractFlightInfoFromConfirmCode(string);


// program starts here
int main()
{
	int menu = 0;

	// print the banner
	printBigDivider();
	cout << "\t\tTICKET RESERVATION\n";
	printBigDivider();

	// create the planes and the report
	initializePlanes();		
	report = new Report();

	// keep running the program until the user choose to quit
	do
	{
		// prompt the user for the menu
		menu = getMenu("Menu:\n\n1. View planes\n2. Reserve\n3. Cancel wait list reservation\n4. Quit\n\n", 1, 4, true, true);

		switch (menu)
		{
			case 1: viewPlanes(); break;		// user chose to view planes
			case 2: reserve(); break;			// user chose to reserve seats
			case 3: cancelWaitList(); break;	// user chose to cancel his order in the wait list
			case 4: quit(); break;				// user chose to quit the program
		}

	} while (menu != 4);	// quit when menu is 4

	printBigDivider();

	return 0;
}


/*************************************************************
* function: isInt
* parameter:	input: string
* return: bool
* check to see if the given input is an integer or not
**************************************************************/
bool isInt(string input)
{
	/*
	 * if the string has 0 size, it is invalid
	 * loop through each character in the string
	 * if any character is not a digit, return false
	 * if all characters are digit, return true
	 */
	if (input.size() == 0)
		return false;
	for (unsigned int i = 0; i < input.size(); i++)
	{
		if (!isdigit(input[i]))
			return false;
	}
	return true;
}


/***************************************************************************
* function: isInRange
* parameter:	prompt: string
*				lowerBound: int
*				upperBound: int
* return: bool
* check to see if the number is in the domain of [lowerBound, upperBound]
***************************************************************************/
bool isInRange(int number, int lowerBound, int upperBound)
{
	return ((lowerBound <= number) && (number <= upperBound));
}


/*************************************************************
* function: getMenu
* parameter:	prompt: string
*				lowerBound: int (lower bound of choices)
*				upperBound: int (upper bound of choices)
*				printChoice: print the multiple choice or not
*				printDivider: print the divider or not
* return: int
* prompt the user to choose a menu and return a valid choice
**************************************************************/
int getMenu(string prompt, int lowerBound, int upperBound, bool printChoice, bool printDivider)
{
	string input = "";
	int number = 0;

	if (printChoice)
		cout << prompt;

	do {
		if (printChoice)
			cout << "Your choice: ";
		else
			cout << prompt;

		getline(cin, input);

		// validate input

		// check to see if the input is an integer
		if (!isInt(input))
		{
			cout << "You must enter an integer between " << lowerBound << " and " << upperBound << "\n";
		}
		// now the input is indeed an integer
		else
		{
			// convert from string to integer
			number = stoi(input);

			// check to see if the input is in a specific range
			if (!isInRange(number, lowerBound, upperBound))
			{
				cout << "You must enter an integer between " << lowerBound << " and " << upperBound << "\n";
				number = 0;
			}
		}


	} while (number == 0);	// keep asking while number is 0

	if (printDivider)
		printBigDivider();

	return number;
}


/********************************************************
* function: initializePlanes
* parameter: 
* return: void
* initialize all airplanes 
* there are 2 types of airplanes: Airbus and Boeing
* each airplane has a unique route
*********************************************************/
void initializePlanes()
{
	planes[0] = new Airbus("A_DFW->NYC", "Dallas", "New York City", "Airbus_DFW_NYC");
	planes[1] = new Boeing("B_WA->LA", "Washington D.C.", "Los Angeles", "Boeing_WA_LA");
	planes[2] = new Airbus("A_PN->SD", "Phoenix", "San Diego", "Airbus_PN_SD");
	planes[3] = new Boeing("B_CHI->MIA", "Chicago", "Miami", "Boeing_CHI_MIA");
	planes[4] = new Airbus("A_NYC-DFW", "New York City", "Dallas", "Airbus_NYC_DFW");
}


/***********************************************************
* function: viewPlanes
* parameter:
* return: int
* return the user's choice of selecting plane or going back
************************************************************/
int viewPlanes()
{
	string prompt = "Planes:\n\n1. Airbus (DFW->NYC)\n2. Boeing (WA->LA)\n";
	prompt += "3. Airbus (PN->SD)\n4. Boeing (CHI->MIA)\n5. Airbus (NYC->DFW)\n6. Go back\n\n";

	int choice = getMenu(prompt, 1, 6, true, true);

	/*
	* if the user does not choose 6 (go back),
	* then print out the seating chart of the given airplane
	*/
	if (choice != 6)
	{
		planes[choice - 1]->printSeats();
		printBigDivider();
	}


	return choice;
}


/********************************************************
* function: reserve
* parameter:
* return: void
* let the user reserve seat(s) on a particular airplane
*********************************************************/
void reserve()
{
	cout << "Which plane do you want to reserve?\n\n";
	
	int plane = viewPlanes();			// which plane to reserve

	// if the user did not choose to go back (6), continue reserving
	if (plane != 6)
	{
		bool continueReserving = false;		// whether or not to continue reserving

		// keep looping if the user chooses to continue reserving seats on the same plane
		do
		{
			// get the total number of seats on this airplane to reserve in this order
			int totalSeat;
			int startingSeat = 0;				// first seat to reserve
			string name = "";
			int age = 0, seatNumber = 0;
			bool isValidSeat = false;			// whether or not the seat the user just selected is valid
			bool putOnWaitlist = false;			// whether or not to put the ticket on waitlist
			bool allAvailable = true;			// check to see if all selected seats are available

			// get total seats to reserve
			totalSeat = getMenu("Total seat(s) to reserve: ", 1, planes[plane - 1]->getCapacity(), false, false);

			// create a dynamic array to hold seat objects
			Seat* seat = new Seat[totalSeat];

			printSmallDivider();

		RESERVING: // label

			// loop to get info of each seat
			for (int currentSeat = startingSeat; currentSeat < totalSeat; currentSeat++)
			{
				// reset the isValidSeat flag every time in the loop goes to new iteration
				isValidSeat = false;

				cout << "Seat #" << currentSeat + 1 << " in this order:\n\n";

				// get name
				cout << "Reserver's full name: ";
				getline(cin, name);

				// get age
				age = getMenu("Reserver's age: ", 1, 100, false, false);

				// keep asking for the seat number until getting a valid one or the user put on wait list
				do
				{
					// get seat number
					seatNumber = getMenu("Seat number: ", 1, planes[plane - 1]->getCapacity(), false, false);

					// check to see if the user already chose this seat
					if (isSelected(seat, currentSeat, 0, seatNumber))
					{
						cout << "You already chose this seat.\n";
					}
					// the seat is not selected by the user in this order
					else
					{
						// the seat is already reserved in the plane
						if (!planes[plane - 1]->isAvailable(seatNumber - 1))
						{
							cout << "\nThis seat is already reserved, ";

							/*
							 * if the waitlist is still available, ask to put the entire order onto the waitlist
							 * else, notify the user to choose another seat
							 */
							if (planes[plane - 1]->isAvailableInWaitlist(seatNumber))
							{
								// prompt to put on wait list
								cout << "but you\n(and your entire order) can still be put on the wait list.\n\n";
								putOnWaitlist = getYesNo("Do you want to do so?");
								
								// setup new seat in the array (not in the plane) if the user chose to put on wait list
								if (putOnWaitlist)
								{
									allAvailable = false;

									// setup new seat in the array (not in the plane)
									seat[currentSeat].setReserver(new Person(name, age));
									seat[currentSeat].setSeatNumber(seatNumber, planes[plane - 1]->getTotalBusinessClassSeats());
									
									break;	// break out of the do-while loop
								}
							}
							// the seat is not available in the plane and the wait list
							else
							{
								cout << "\nand is also not available to be held in the wait list.\n\n";
							}

						}
						// the seat is still available in the plane
						else
						{
							// setup new seat in the array (not in the plane)
							seat[currentSeat].setReserver(new Person(name, age));
							seat[currentSeat].setSeatNumber(seatNumber, planes[plane - 1]->getTotalBusinessClassSeats());
							
							isValidSeat = true;
						}
					}

				} while (!isValidSeat);	// keep looping until the user chooses a valid seat number

				printSmallDivider();

			}	// end for(seats)

			// ask the user if he/she wants to continue reserving seats on this plane
			continueReserving = getYesNo("Do you want to reserve more seats on this airplane?");

			/*
			 * if the user wants to continue reserving, 
			 *		ask for the next total seats, create new array with size = oldTotalSeat + newTotalSeat
			 *		then copy the contents of old array to new array and update the address of the old array
			 * if the user does not want to continue reserving, 
			 *		generate ticket and exit out of this function
			 */
			if (continueReserving)
			{
				printSmallDivider();

				// set oldTotalSeat and startingSeat to current totalSeat
				int oldTotalSeat = totalSeat;
				startingSeat = totalSeat;

				// get the total number of seats on this airplane to reserve in this order
				totalSeat = getMenu("Total seat(s) to reserve: ", 1, planes[plane - 1]->getCapacity(), false, false);

				printSmallDivider();

				// dynamically create new Seat array (temporary array) to hold the old and new seats
				Seat* newSeat = new Seat[oldTotalSeat];

				// copy old array to temporary array
				for (int i = 0; i < oldTotalSeat; i++)
				{
					newSeat[i] = seat[i];
				}

				// free the memory of the current seat array, then create a new array with larger size
				delete [] seat;
				seat = new Seat[oldTotalSeat + totalSeat];

				// copy data from the temporary array back into the current array
				for (int i = 0; i < oldTotalSeat; i++)
				{
					seat[i] = newSeat[i];
				}

				// free the memory of the temporary seat array
				delete [] newSeat;

				// update new total seats
				totalSeat += oldTotalSeat;

				// continue reserving process
				goto RESERVING;

			}	// end if(continue reserving)
			// quit reserving
			else	
			{
				printBigDivider();

				// generate new ticket, print it out to the screen and save it to the record
				Ticket *ticket = new Ticket(seat, totalSeat, planes[plane - 1]->getFlightCode(), 0);
				ticket->print();
				cout << "\nTotal price: " << fixed << setprecision(2) << ticket->getPrice() << "\n";

				/*
				* start reserving or put on wait list
				* if all seats are available, reserve them
				* if at least 1 seat is not available and the user chose to put on the wait list, do so
				*/
				if (allAvailable)
				{
					planes[plane - 1]->reserve(seat, startingSeat, totalSeat);
				}
				else
				{
					cout << "\nThis order is added to the wait list.\n";
					planes[plane - 1]->putOnWaitlist(ticket);
				}

				Ticket *reportTicket = new Ticket(ticket);

				// add new ticket into the report list
				report->add(reportTicket);

				printBigDivider();

			}	// end else (quit reserving)

		} while (continueReserving); // keep looping if the user chooses to continue reserving seats on the same plane

	}	// end if(not go back)


	// logout automatically

}


/****************************************************************
* function: isSelected
* parameter:	seats: Seat*
*				size: int
*				currentSeat: int
*				seatNumber: int
* return: bool
* RECURSIVELY check to see if the user already chose that seat 
*****************************************************************/
bool isSelected(Seat *seats, int size, int currentSeat, int seatNumber)
{
	// finished checking all seats and did not find any repeat, return false
	if (currentSeat > (size - 1))
		return false;
	// found a repeated seat, return true
	else if (seats[currentSeat].getSeatNumber() == seatNumber)
		return true;
	// recursively check the next seat in the array
	else
		return isSelected(seats, size, currentSeat + 1, seatNumber);
}


/********************************************************
* function: quit
* parameter:	
* return: void
* delete all dynamic memories allocated in the program
*********************************************************/
void quit()
{
	cout << "Good bye.\n";

	// free the dynamic memory of the planes array
	for (int i = 0; i < 5; i++)
	{
		delete planes[i];
	}

	// delete the report
	delete report;	
}


/****************************************
* function: getYesNo
* parameter: prompt: string
* return: bool
* ask user to answer a yes/no question
*****************************************/
bool getYesNo(string prompt)
{
	string input = "";

	do
	{
		cout << prompt << "\nEnter 'Y' for \"Yes\" or 'N' for \"No\": ";
		getline(cin, input);
		
		/*
		 * validate input
		 *
		 * if the length of the input string is not 1, then it is invalid (only get 1 character)
		 * if the character of the input is not y or n (after converting to lowercase),
		 * then it is also invalid
		 * 
		 * if the input is y, return true (continue reserving on the same plane)
		 * if the input is n, return false (quit reserving)
		 */
		if ((input.size() != 1) || (tolower(input[0]) != 'y' && tolower(input[0]) != 'n'))
		{
			cout << "Invalid input.\n";
		}
		else
		{
			return (tolower(input[0]) == 'y') ? true : false;
		}

	} while (true);
}


/*****************************************************
* function: cancelWaitList
* parameter: void
* return: void
* let the user cancel the order that is on waitlist 
*****************************************************/
void cancelWaitList()
{
	// display text indicator
	cout << "Choose the plane containing\n"
		<< " the seat(s) that you want to cancel.\n\n"
		<< "** PLease note that cancellation\n"
		<< "   is only available if your seat(s)\n"
		<< "   is(are) being held in the wait list. **\n";
	printSmallDivider();

	// get the confirmation code
	string confirmationCode = "";
	cout << "Enter your confirmation code: ";
	cin >> confirmationCode;

	// get the flightCode from the confirmation
	string flightInfo = extractFlightInfoFromConfirmCode(confirmationCode);
	int plane = 0;

	/*
	 * find the plane 
	 * loop through each plane and check its flightCode
	 * when find the match, break out of the loop
	 * after checking the last plane and still not find the match,
	 * set the current plane to the total planes (sentinel that
	 * signals ArrayIndexOutOfBoundException, overflow by 1)
	 */
	for (; plane < TOTAL_PLANES; plane++)
	{
		if (flightInfo == planes[plane]->getFlightCode())
			break;
		else if (plane == TOTAL_PLANES - 1)
			plane = TOTAL_PLANES;
	}
	
	// invalid code case: wrong flightCode
	if (plane >= TOTAL_PLANES)
	{
		cout << "\nTicket not found.\n";
	}
	// valid flightCode
	else
	{
		// find the returned ticket
		Ticket* returnedTicket = planes[plane]->cancelOrderInWaitlist(confirmationCode);

		// found the ticket that matched the confirmation code
		if (returnedTicket != nullptr)
		{
			cout << "\nTicket removed successfully.\n";

			printSmallDivider();

			// print the returned ticket to the screen
			returnedTicket->cancel();
			returnedTicket->print();

			// add the returned ticket to the report
			report->add(returnedTicket);
		}
		// did not find any ticket that match the confirmation code
		else
		{
			cout << "\nTicket not found.\n";
		}
	}

	printBigDivider();

	char c;
	cin.get(c);
}



/*****************************************************
* function: printBigDivider
* parameter: void
* return: void
* print the big divider between the text
*****************************************************/
void printBigDivider()
{
	cout << "\n======================================================\n\n";
}


/*****************************************************
* function: printSmallDivider
* parameter: void
* return: void
* print the small divider between the text
*****************************************************/
void printSmallDivider()
{
	cout << "\n-------------------------------------\n\n";
}


/*****************************************************
* function: extractFlightInfoFromConfirmCode
* parameter: confirmationCode: string
* return: the string representation of the flightCode
* extract the flight code from the confirmation code
*****************************************************/
string extractFlightInfoFromConfirmCode(string confirmationCode)
{
	string flightInfo = "";

	// confirmation code must be at least 16 characters long
	if (confirmationCode.size() < 16)
		return "Invalid";

	// flight code is the first 10 characters of the confirmation code
	for (int i = 0; i < 10; i++)
	{
		flightInfo += confirmationCode[i];
	}

	return flightInfo;
}