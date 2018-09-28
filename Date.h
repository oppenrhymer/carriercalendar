#pragma once
#ifndef DATE_H
#define DATE_H
#include <string>



class Date {
public:
	friend class Period;
	Date() : day(1), month(1), year(2000) { }
	Date(int m, int d, int y) : day(d), month(m), year(y) { }
	Date& operator++(int);
	Date& operator=(const Date& rhs)
	{
		this->day = rhs.day;
		this->month = rhs.month;
		this->year = rhs.year;
		return *this;
	}
	friend bool operator==(const Date&, const Date&);
	bool isLeapYear();
	int getDayOfTheWeek();
	void displayDayOfTheWeek();
	std::string getMonthName();
	int checkIfHoliday();
	void displayDate();
	int getMonthLength();
private:
	int day;
	int month;
	int year;

};


class Period {
public:
	Period(Date d, Date d2) : beginning(d), ending(d2) {}
	void setPeriod(Date&, Date&);
	void printPeriod();
	
private:
	Date beginning;
	Date ending;
};
/*void Month::initializeMonth(int mm, int yy)
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

}*/

#endif