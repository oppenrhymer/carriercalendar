#pragma once
#ifndef MONTHS_H
#define MONTHS_H
#include <string>
#include <iostream>


//This class is pretty anemic right now, as I have most of the functions
//prototyped outside of it. I intend to fold them into the class, eventually.

class Month {
public:
	void initializeMonth(int, int);
	std::string getMonthName();
	
private:
	int number_of_days;
	int numerical_representation;
	


};

bool isLeapYear(int);
int getDayOfTheWeek(int,int,int);
void displayDayOfTheWeek(int);


#endif
