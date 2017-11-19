/*
* File: Person.cpp
*
* This file contains the implementation of the methods of the Person class
*
* Designed by:	Team 4
*
* List of methods:
*		constructors and destructor
*		getName: return a person's name
*		getAge: return a person's age
*		getDiscountRatio: return a person's discount rate according to one's age
*		operator=: overloaded assignment operator
*/

#include "Person.h"


/***********************
* CONSTRUCTOR
***********************/
Person::Person(string n, int a)
{
	name = n;
	age = a;
}


/*************************
* COPY CONSTRUCTOR
**************************/
Person::Person(const Person &person1)
{
	name = person1.name;
	age = person1.age;
}


/****************************
* function: getName
* parameter: 
* return: void
* return the person's name
*****************************/
string Person::getName()
{
	return name;
}


/****************************
* function: getAge
* parameter:
* return: void
* return the person's age
*****************************/
int Person::getAge()
{
	return age;
}



/*************************************
* function: getDiscountRatio
* parameter:
* return: void
* return the person's discount rate
*************************************/
double Person::getDiscountRatio()
{
	/*
	 * children (12 and under) pay 75% of the ticket price
	 * adults (from 12 to 65 exclusively) pay full price
	 * seniors (65 and above) pay half price
	 */
	if (age <= 12)
		return 0.75;
	else if (age < 65)
		return 1;
	else
		return 0.5;
}



/*******************************
* overload assignment operator 
* parameter:
* return: void
* return the person's name
*******************************/
void Person::operator=(const Person &person)
{
	name = person.name;
	age = person.age;
}