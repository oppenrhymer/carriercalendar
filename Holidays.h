#pragma once
#ifndef HOLIDAYS_H
#define HOLIDAYS_H
#include "Months.h"

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
//Will check to see if supplied day is a federal holiday, and, if so return an integer corresponding to the following table:
// 0 NO HOLIDAY
// 1 NEW YEAR'S DAY
// 2 Martin Luther King, Jr. Day (Third Monday in January).
// 3 President's Day (Third Monday in February).
// 4 Memorial Day(Last Monday in May).
// 5 Independence Day(July 4).
// 6 Labor Day(First Monday in September).
// 7 Columbus Day(Second Monday in October).
// 8 Veterans Day(November 11).
// 9 Thanksgiving Day(Fourth Thursday in November).
// 10 Christmas Day(December 25).
//
//WORKING AS INTENDED

int checkIfHoliday(int mm, int dd, int yy)
{
	int dayofweek =	getDayOfTheWeek(mm, dd, yy);
	if ((mm == 1) && (dd == 1))
	{
		return 1;
	}
	
	//Have to figure out how many occurrences of a given day there have been
	int firstdayofmonth = getDayOfTheWeek(mm, 1, yy);
	int count = 0;
	int maxcount = count;
	int tempday = firstdayofmonth;
	if (mm != 5)
	{
		for (int i = 1; i <= dd; i++)
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
	else {
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
			if (i == dd)
			{
				count = maxcount;
			}
		}
	}
	if ((mm == 1) && (dayofweek == 2) && (count == 3))
	{
		return 2;
	}
	if ((mm == 2) && (dayofweek == 2) && (count == 3))
	{
		return 3;
	}
	if ((mm == 5) && (dayofweek == 2) && (maxcount == count))
	{
		return 4;
	}
	if ((mm == 7) && (dd == 4))
	{
		return 5;
	}
	if ((mm == 9) && (count == 1))
	{
		return 6;
	}
	if ((mm == 10) && (count == 2))
	{
		return 7;
	}
	if ((mm == 11) && (dd == 11))
	{
		return 8;
	}
	if ((mm == 11) && (count == 4))
	{
		return 9;
	}
	if ((mm = 12) && (dd == 25))
	{
		return 10;
	}
	return 0;
}


#endif