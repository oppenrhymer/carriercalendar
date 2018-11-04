#include "stdafx.h"
#include "Globals.h"
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
	//int tempday = firstdayofmonth;
	if (month != 5)
	{
		for (int i = 1; i <= day; i++)
		{
			if (dayofweek == tempday)
			{
				count++;
				//troubleshooting...
				//std::cout << "Day count: " << count << std::endl;
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
	//this entire function will need to be altered to fit Search. *******************************
	std::cout << month << "/" << day << "/" << year;
	/*displayDayOfTheWeek();
	std::cout << "\t";
	int hol = checkIfHoliday();	
	if (hol)
	{
		displayHoliday(hol);
	}	
	std::cout << std::endl;
	*/
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
	if (day > getMonthLength())
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
Date& Date::operator--(int)
{
	day--;
	int previousMonth = (getMonth() - 1);
	if (previousMonth < 1)
	{
		previousMonth = 12;
	}
	if (day < 1)
	{
		month = previousMonth;
		day = getMonthLength();
		if (month == 12)
		{
			year--;
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
bool operator<(Date& lhs, Date& rhs)
{
	if (lhs.getYear() < rhs.getYear())
	{
		
		return true;
	}
	if (lhs.getYear() == rhs.getYear())
	{
		if (lhs.getMonth() < rhs.getMonth())
		{
			return true;
		}
		if (lhs.getMonth() == rhs.getMonth())
		{
			if (lhs.getDay() <= rhs.getDay())
			{
				return true;
			}
		}
	}
	return false;
}
int operator-(Date& lhs,Date& rhs)
{
	
	Date tempdate = rhs;
	int daycounter = 0;
	if (rhs < lhs)
	{
		while (1)
		{
			tempdate++;
			daycounter++;
			if (tempdate == lhs)
			{
				break;
			}
		}
		return daycounter;
	}
	else {
		while (1)
		{
			tempdate--;
			daycounter++;
			if (tempdate == lhs)
			{
				break;
			}
		}
		return daycounter;
	}
	
	return 0;
	
}



//days off
//***NEED TO GET RIDE OF PARAMETERS AND INSTEAD RELY ON PROFILE DATA*** 10/16/18
bool Date::isDayOff(std::string dayOffColor)
{
	//It looks messy, and damn it, there has to be a more elegant way to do this than overloading the '-' operator like this
	//but it works. Still need to add the other day off colors, and a logical statement to handle fixed schedules.10/1/18

	int counter = 0;
	Date searchDate;
	if (dayOffColor == "BROWN")
	{
		//A
		//control date **MUST BE A KNOWN MONDAY OFF**
		//searchDate = Date(12, 4, 2017);
		searchDate = Date(12, 21, 2015);
	}
	if (dayOffColor == "RED")
	{
		//B
		//control date **MUST BE A KNOWN MONDAY OFF**
		//searchDate = Date(11, 27, 2017);
		searchDate = Date(12, 14, 2015);
	}
	if (dayOffColor == "BLACK")
	{
		//C
		//control date **MUST BE A KNOWN MONDAY OFF**
		//searchDate = Date(11, 20, 2017);
		searchDate = Date(12, 7, 2015);
	}
	if (dayOffColor == "YELLOW")
	{
		//D
		//control date **MUST BE A KNOWN MONDAY OFF**
		//searchDate = Date(12, 25, 2017);
		searchDate = Date(11, 30, 2015);
	}
	if (dayOffColor == "BLUE")
	{
		//E
		//control date **MUST BE A KNOWN MONDAY OFF**
		//searchDate = Date(12, 18, 2017);
		searchDate = Date(11, 23, 2015);
	}
	if (dayOffColor == "GREEN")
	{
		//F
		//control date **MUST BE A KNOWN MONDAY OFF**
		//searchDate = Date(12, 11, 2017);
		searchDate = Date(11, 16, 2015);
	}
	if (*this == searchDate)
	{
		return true;
	}

	//'daydifference' is the total number of days between the control date and the date being investigated
	int daydifference = *this - searchDate;
	

	//for when the date is before above searchDates. ugh...
	if (*this < searchDate)
	{
		if (((daydifference % 42) == 0) || ((daydifference % 42) == 34) || ((daydifference % 42) == 26) || ((daydifference % 42) == 18) || ((daydifference % 42) == 10) || ((daydifference % 42) == 9))
		{
			return true;
		}
	}
	//takes the total number of days, mods it into a period of up to 42 days (the total time between mondays off);
	//if the date is a multiple of 8 (with one exception **SEE NEXT 'IF' STATEMENT**...), or day 33 (SATURDAY OFF),
	//or day 42 (FINAL MONDAY OFF), will return true.
	if (searchDate < *this)
	{
		if (((daydifference % 42) % 8 == 0) || ((daydifference % 42) == 33) || ((daydifference % 42) == 0))
		{
			//this last check is necessary because the final saturday before the last monday 
			//will give a false positive (day '40', a multiple of 8, in the period)
			if ((daydifference % 42) != 40)
			{
				return true;
			}
		}
	}
		
	
	if (this->getDayOfTheWeek() == 1)
	{
		return true;
	}
	return false;
}
void Period::setPeriod(const Date& beg, const Date& end)
{
	beginning = beg;
	ending = end;
	return;
}


int Period::checkFlags(unsigned int flags, int dayofweek)
{
	//takes in the day of the week (0 == sat) in order to lookup the three bit flags in the unsigned int bitset
	//then, after checking which are on and off returns a unique code for printPeriod.
	//FORCE|SCHEDULED DAY OFF|HOLIDAY
	//1 == 001
	//2 == 010
	//3 == 011
	//4 == 100
	//5 == 101
	//6 == 110
	//7 == 111
	//0 == no flags set
	int dayoffset = (-(dayofweek) + 6);

	//holiday check
	if (flags & (1 << (dayoffset * 3)))
	{
		//scheduled day off check
		if (flags & (1 << ((dayoffset * 3) + 1)))
		{
			//potential force check
			if (flags & (1 << ((dayoffset * 3) + 2)))
			{

				return 7;
			}
			else {
				return 3;
			}
		}
		else {
			return 1;
		}
	}
	if (flags & (1 << ((dayoffset * 3) + 1)))
	{
		if (flags & (1 << ((dayoffset * 3) + 2)))
		{
			return 6;
		}
		else {
			return 2;
		}
	}
	if (flags & (1 << ((dayoffset * 3) + 1)))
	{
		if (flags & (1 << (dayoffset * 3)))
		{
			return 5;
		}
		else {
			return 4;
		}
	}
	return 0;
}


std::list<Date> Period::printPeriod(unsigned int flags, std::string dayOffColor)
{
	
	//SECOND ITERATION. USES OVERLOADED OPERATORS
	Date tempdate;
	std::list<Date> resultsList;
	tempdate = beginning;
	int counter = 0;
	
	//0 = Sat
	//Hol SDO FORCE

	while (!(tempdate == ending))
	{
		int flagsCode = checkFlags(flags, tempdate.getDayOfTheWeek());
		bool willBeDisplayed = false;
		switch (flagsCode)
		{
			case 0:
				break;
			case 1:
				if (tempdate.checkIfHoliday())
					willBeDisplayed = true;
				break;
			case 2:
				if (tempdate.isDayOff(dayOffColor))
					willBeDisplayed = true;
				break;
			case 3:
				if (tempdate.checkIfHoliday() && tempdate.isDayOff(dayOffColor))
					willBeDisplayed = true;
				break;
			case 4: //Unfinished, for now. Need to figure out an elegant way to check for forced days
				if (tempdate.checkIfHoliday() && tempdate.isDayOff(dayOffColor))
					willBeDisplayed = true;
				break;
			case 5:
				if (tempdate.checkIfHoliday() && tempdate.isDayOff(dayOffColor))
					willBeDisplayed = true;
				break;
			case 6:
				if (tempdate.checkIfHoliday() && tempdate.isDayOff(dayOffColor))
					willBeDisplayed = true;
				break;
			case 7:
				if (tempdate.checkIfHoliday() && tempdate.isDayOff(dayOffColor))
					willBeDisplayed = true;
				break;
			default:
				break;
		}
		if (willBeDisplayed)
		{
			resultsList.push_back(tempdate);
		}
		if (beginning < ending)
		{
			tempdate++;
		}
		else {
			tempdate--;
		}
		counter++;

	}
	
	return resultsList;
}

int Period::numberOfSearchResults(unsigned int flags, std::string dayOffColor)
{
	Date tempdate;
	tempdate = beginning;
	int counter = 0;
	while (!(tempdate == ending))
	{
	

		int flagsCode = checkFlags(flags, tempdate.getDayOfTheWeek());
		bool willBeDisplayed = false;
		switch (flagsCode)
		{
		case 0:
			break;
		case 1:
			if (tempdate.checkIfHoliday())
				willBeDisplayed = true;
			break;
		case 2:
			if (tempdate.isDayOff(dayOffColor))
				willBeDisplayed = true;
			break;
		case 3:
			if (tempdate.checkIfHoliday() && tempdate.isDayOff(dayOffColor))
				willBeDisplayed = true;
			break;
		case 4: //Unfinished, for now. Need to figure out an elegant way to check for forced days
			if (tempdate.checkIfHoliday() && tempdate.isDayOff(dayOffColor))
				willBeDisplayed = true;
			break;
		case 5:
			if (tempdate.checkIfHoliday() && tempdate.isDayOff(dayOffColor))
				willBeDisplayed = true;
			break;
		case 6:
			if (tempdate.checkIfHoliday() && tempdate.isDayOff(dayOffColor))
				willBeDisplayed = true;
			break;
		case 7:
			if (tempdate.checkIfHoliday() && tempdate.isDayOff(dayOffColor))
				willBeDisplayed = true;
			break;
		default:
			break;
		}
		if (willBeDisplayed)
		{
			counter++;
		}
		if (beginning < ending)
		{
			tempdate++;
		}
		else {
			tempdate--;
		}
	}
	return counter;
}
