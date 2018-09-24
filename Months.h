#pragma once
#ifndef MONTHS_H
#define MONTHS_H
#include <string>
#include <iostream>


//bool isLeapYear(int);

class Month {
public:
	void initializeMonth(int, int);
	std::string getMonthName();
	//friend bool isLeapYear(int);
private:
	int number_of_days;
	int numerical_representation;
	


};

bool isLeapYear(int);
int getDayOfTheWeek(int,int,int);
void displayDayOfTheWeek(int);


#endif