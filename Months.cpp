#include "stdafx.h"
#include "Months.h"
#include <iostream>

//Leap year check works as intended.
bool isLeapYear(int y) {
	if ((y % 4) == 0)
	{
		if ((y % 100) == 0)
		{
			if ((y % 400) == 0)
			{
				return 1;
			}
			else {
				return 0;
			}
		}

		return 1;

	}
	return 0;
}
int getDayOfTheWeek(int mm, int dd, int yy)
{
	int monthtable[] = { 1,4,4,0,2,5,0,3,6,1,4,6 };
	int centurytable[] = { 4,2,0,6 };
	int lasttwodigits = (yy % 100);
	int firsttwodigits = (yy / 100);
	int workingnumber = (lasttwodigits / 4);
	workingnumber += dd;
	if (mm >= 1)
	{
		workingnumber += monthtable[mm - 1];
	}
	else {
		std::cout << "ERROR. MONTH LESS THAN 1" << std::endl;
		return -1;
	}
	if ((mm == 1) || (mm == 2))
	{
		workingnumber -= 1;
	}
	//Code to grab century value. Have to get mathy...
	int firsttwodigits2 = firsttwodigits;
	while (1)
	{
		if ((firsttwodigits2 >= 17) && (firsttwodigits2 <= 20))
		{
			break;
		}
		if (firsttwodigits2 < 17)
		{
			firsttwodigits2 += 4;
		}
		if (firsttwodigits2 > 20)
		{
			firsttwodigits2 -= 4;
		}
		std::cout << "I am stuck in a loop..." << std::endl;
	}
	switch (firsttwodigits2) {
	case 17:
		workingnumber += 4;
		break;
	case 18:
		workingnumber += 2;
		break;
	case 19:
		workingnumber += 0;
		break;
	case 20:
		workingnumber += 6;
		break;
	default:
		std::cout << "ERROR" << std::endl;
		break;
	}
	workingnumber += lasttwodigits;
	workingnumber = workingnumber % 7;
	return workingnumber;
}
void displayDayOfTheWeek(int day)
{
	switch (day) {
	case 0:
		std::cout << "Saturday";
		break;
	case 1:
		std::cout << "Sunday";
		break;
	case 2:
		std::cout << "Monday";
		break;
	case 3:
		std::cout << "Tuesday";
		break;
	case 4:
		std::cout << "Wednesday";
		break;
	case 5:
		std::cout << "Thursday";
		break;
	case 6:
		std::cout << "Friday";
		break;
	default:
		std::cout << "Error";
		break;
	}
}
void Month::initializeMonth(int mm, int yy)
{
	numerical_representation = mm;

	if (mm == 2)
	{
		if (isLeapYear(yy))
		{
			number_of_days = 29;
		}
		else {
			number_of_days = 28;
		}
	}
	if ((mm == 4) || (mm == 6) || (mm == 9) || (mm == 11))
	{
		number_of_days = 30;
	}
	else {
		number_of_days = 31;
	}
	return;

}
std::string Month::getMonthName() {
	switch (numerical_representation) {
	case 1:
		return "January";
	case 2:
		return "February";
	case 3:
		return "March";
	case 4:
		return "April";
	case 5:
		return "May";
	case 6:
		return "June";
	case 7:
		return "July";
	case 8:
		return "August";
	case 9:
		return "September";
	case 10:
		return "October";
	case 11:
		return "November";
	case 12:
		return "December";
	default:
		return "ERROR";
		break;
	}
}