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


#endif
