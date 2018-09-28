#include "stdafx.h"
#include "Date.h"
#include <iostream>
#include <string>
bool Date::isLeapYear() {
	if ((year % 4) == 0)
	{
		if ((year % 100) == 0)
		{
			if ((year % 400) == 0)
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
int Date::getDayOfTheWeek()
{
	int monthtable[] = { 1,4,4,0,2,5,0,3,6,1,4,6 };
	int centurytable[] = { 4,2,0,6 };
	int lasttwodigits = (year % 100);
	int firsttwodigits = (year / 100);	
	int workingnumber = (lasttwodigits / 4);	
	workingnumber += day;	
	if (month >= 1)
	{
		workingnumber += monthtable[month - 1];		
	}
	else {
		std::cout << "ERROR. MONTH LESS THAN 1" << std::endl;
		return -1;
	}
	if (((month == 1) || (month == 2)) && (isLeapYear() == 1))
	{
		workingnumber -= 1;		
	}
	//Code to grab century value.
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
void Date::displayDayOfTheWeek()
{
	switch (getDayOfTheWeek()) {
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

std::string Date::getMonthName() {
	switch (month) {
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

//holidays

int Date::checkIfHoliday() {
	int dayofweek = this->getDayOfTheWeek();
	if ((month == 1) && (day == 1))
	{
		return 1;
	}

	//Have to figure out how many occurrences of a given day there have been
	Date firstday(this->month, 1, this->year);
	int tempday = firstday.getDayOfTheWeek();
	int count = 0;
	int maxcount = count;
	
	if (month != 5)
	{
		for (int i = 1; i <= day; i++)
		{
			if (dayofweek == tempday)
			{
				count++;
				
			}
			if (tempday == 6)
			{
				tempday = 0;
			}
			else {
				tempday++;
			}

		}
	}
	else if ((month == 5) && (dayofweek == 2)) {
		for (int i = 1; i <= 31; i++)
		{
			if (dayofweek == tempday)
			{
				maxcount++;
			}
			if (tempday == 6)
			{
				tempday = 0;
			}
			else {
				tempday++;
			}
			if (i == day)
			{
				count = maxcount;
				
			}
		}
	}
	
	if ((month == 1) && (dayofweek == 2) && (count == 3))
	{
		return 2;
	}
	if ((month == 2) && (dayofweek == 2) && (count == 3))
	{
		return 3;
	}
	if ((month == 5) && (dayofweek == 2) && (maxcount == count))
	{
		return 4;
	}
	if ((month == 7) && (day == 4))
	{
		return 5;
	}
	if ((month == 9) && (dayofweek == 2) && (count == 1))
	{
		return 6;
	}
	if ((month == 10) && (dayofweek == 2) && (count == 2))
	{
		return 7;
	}
	if ((month == 11) && (day == 11))
	{
		return 8;
	}
	if ((month == 11) && (dayofweek == 5) && (count == 4))
	{
		return 9;
	}
	if ((month == 12) && (day == 25))
	{
		return 10;
	}
	return 0;
}
void displayHoliday(int hol)
{
	switch (hol) {
	case 1:
		std::cout << "New Year's Day";
		break;
	case 2:
		std::cout << "Martin Luther King, Jr. Day";
		break;
	case 3:
		std::cout << "President's Day";
		break;
	case 4:
		std::cout << "Memorial Day";
		break;
	case 5:
		std::cout << "Independence Day";
		break;
	case 6:
		std::cout << "Labor Day";
		break;
	case 7:
		std::cout << "Columbus Day";
		break;
	case 8:
		std::cout << "Veteran's Day";
		break;
	case 9:
		std::cout << "Thanksgiving";
		break;
	case 10:
		std::cout << "Christmas Day";
		break;
	default:
		std::cout << "ERROR";
		break;
	}
	return;
}
void Date::displayDate()
{
	std::cout << month << "/" << day << "/" << year << " ";
	displayDayOfTheWeek();
	std::cout << "\t";
	int hol = checkIfHoliday();	
	if (hol)
	{
		displayHoliday(hol);
	}	
	std::cout << std::endl;
	return;
}
int Date::getMonthLength()
{

	if (month == 2)
	{
		if (isLeapYear())
		{
			return 29;
		}
		else {
			return 28;
		}
	}
	if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
	{
		return 30;
	}
	else {
		return 31;
	}
	return 0;
}
Date& Date::operator++(int)
{
	day++;
	if (day > this->getMonthLength())
	{
		day = 1;
		month++;
		if (month > 12)
		{
			month = 1;
			year++;
		}
	}
	return *this;
}
bool operator==(const Date& lhs, const Date& rhs)
{
	if (lhs.year == rhs.year)
	{
		if (lhs.month == rhs.month)
		{
			if (lhs.day == rhs.day)
			{
				return true;
			}
		}
	}
	return false;
}
void Period::setPeriod(Date& beg, Date& end)
{
	beginning = beg;
	ending = end;
	return;
}
void Period::printPeriod()
{
	Date tempdate;
	tempdate = beginning;
	while (!(tempdate == ending))
	{
		if (tempdate.checkIfHoliday())
		{
			tempdate.displayDate();
		}
		tempdate++;

	}
	return;
}
