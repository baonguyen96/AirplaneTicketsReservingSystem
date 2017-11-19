/*
* File: Report.cpp
*
* This class contains the implementation of the methods of the Report class.
*
* Designed by:	Team 4
*
*/

// need this to suppress the warning of Visual Studio about the function localtime
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Report.h"
#include <fstream>		// work with files
#include <ctime>		// to use the system current time
#include <iomanip>		// to format the output
using namespace std;

/****************************************
* CONSTRUCTOR
*****************************************/
Report::Report()
{
	ticketsSold = new LinkedList<Ticket>();
}


/****************************************
* DESTRUCTOR
*****************************************/
Report::~Report()
{
	save();
	delete ticketsSold;
}


/***********************************************
* function: add
* parameter:	ticket: Ticket pointer
* return: void
* add new ticket to the end of the report list
************************************************/
void Report::add(Ticket *ticket)
{
	ticketsSold->addLast(ticket);
}


/****************************************
* function: save
* parameter:
* return: void
* save the report back into the file 
*****************************************/
void Report::save()	// problem here
{
	ofstream reportFile("Report.txt", ios::app);	// open the Report.txt file in append mode

	// check to make sure the file is opened correctly
	if (reportFile.fail())
	{
		cout << "Error: cannot open file.\n";
		return;
	}

	countDailyProfit();

	// display the current time & the profit of the report
	// get current time
	time_t t = time(0);  
	struct tm * now = localtime(&t);

	// set up the date-time string with the format: YYYY-MM-DD HH:MM:SS
	string currentDateTime = to_string(now->tm_year + 1900) + '-'
		+ ((now->tm_mon + 1 < 10) ? "0" : "") + to_string(now->tm_mon + 1) + '-'
		+ ((now->tm_mday < 10) ? "0" : "") + to_string(now->tm_mday) + ' '
		+ ((now->tm_hour < 10) ? "0" : "") + to_string(now->tm_hour) + ':'
		+ ((now->tm_min < 10) ? "0" : "") + to_string(now->tm_min) + ':'
		+ ((now->tm_sec < 10) ? "0" : "") + to_string(now->tm_sec);

	reportFile << currentDateTime << "\n\nCurrent report's profit: $"
			<< fixed << setprecision(2) << dailyProfit << "\n";

	// keep writing until the end of the report
	// null?
	while (ticketsSold->getSize() != 0)
	{
		Ticket *ticket = ticketsSold->removeFirst();	// cannot read reserver's info

		reportFile << "\n-------------------------\n\n" << ticket->toString();

		delete ticket;
	}

	reportFile << "\n====================================\n\n";

	reportFile.close();

}


/****************************************
* function: countDailyProfit
* parameter:
* return: void
* count the current report's profit
*****************************************/
void Report::countDailyProfit()
{
	for (int i = 0; i < ticketsSold->getSize(); i++)
	{
		dailyProfit += ticketsSold->get(i)->getPrice();
	}
}