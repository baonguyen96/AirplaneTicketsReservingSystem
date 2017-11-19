/*
*
* CS/SE 3376.001
* Team 4
*
* Class: Person
*
* This class is a structure of a person for the seat's reserver.

* Features:
*		Initialize/access a person's name & age
*		Get discount rate depends on the age
*
* List of methods:
*		constructors and destructor
*		getName: return a person's name
*		getAge: return a person's age
*		getDiscountRatio: return a person's discount rate according to one's age
*		operator=: overloaded assignment operator 
*
*/

#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person
{
private:
	string name;	// person's full name
	int age;		// person's age

public:

	/******************
	 * CONSTRUCTORS
	 *****************/
	
	// default constructor
	Person(){}

	// overloaded constructor
	Person(string, int);

	// copy constructor
	Person(const Person &);


	/******************
	* DESTRUCTORS
	*****************/
	~Person(){}


	/******************
	* ACCESSORS
	*****************/

	// return a person's name
	string getName();

	// return a person's age
	int getAge();

	// return a person's discount rate according to one's age
	double getDiscountRatio();


	/******************************
	* overload assignment operator
	*******************************/
	void operator=(const Person &);
};

#endif