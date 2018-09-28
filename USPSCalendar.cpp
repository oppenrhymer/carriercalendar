// USPSCalendar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Date.h"
#include <iostream>


//AT PRESENT THIS TAKES TWO DATES FROM THE USER AND THEN PRINTS OUT ANY HOLIDAYS FOUND IN THAT PERIOD.
int main()
{
	int m, d, y;
	std::cout << "Enter begin date. Month? ";
	std::cin >> m;
	std::cout << "Day? ";
	std::cin >> d;
	std::cout << "Year? ";
	std::cin >> y;
	int m2, d2, y2;
	std::cout << "Enter end date. Month? ";
	std::cin >> m2;
	std::cout << "Day? ";
	std::cin >> d2;
	std::cout << "Year? ";
	std::cin >> y2;
	Date beg(m, d, y);
	Date end(m2, d2, y2);
	
	Period per(beg,end);
	per.printPeriod();
	

	return 0;
}

