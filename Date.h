#pragma once
#ifndef DATE_H
#define DATE_H
#include <string>
#include <vector>
#include <list>

class Date {
public:
	friend class Period;
	Date() : day(1), month(1), year(2000) { }
	Date(int m, int d, int y) : day(d), month(m), year(y) { }
	Date& operator++(int);
	Date& operator--(int);
	Date& operator=(const Date& rhs)
	{
		this->day = rhs.day;
		this->month = rhs.month;
		this->year = rhs.year;
		return *this;
	}
	friend bool operator<(Date&, Date&);
	friend int operator-(Date&, Date&);
	
	friend bool operator==(const Date&, const Date&);
	bool isLeapYear();
	int getDayOfTheWeek();
	void displayDayOfTheWeek();
	std::string getMonthName();
	int checkIfHoliday();
	bool isDayOff(std::string);
	void displayDate();
	int getMonthLength();
	int getMonth()
	{
		return month;
	}
	int getDay()
	{
		return day;
	}
	int getYear()
	{
		return year;
	}
	void setDate(int m, int d, int y)
	{
		month = m;
		day = d;
		year = y;
	}
private:
	int month;
	int day;
	int year;

};


class Period {
public:
	Period() : beginning({ 0,0,0 }), ending({ 0,0,0 }) {}
	Period(const Date& d,const Date& d2) : beginning(d), ending(d2) {}
	void setPeriod(const Date&, const Date&);
	int checkFlags(unsigned int, int dayofweek);
	//void printPeriod(unsigned char, std::string);
	std::list<Date> printPeriod(unsigned int, std::string);
	int numberOfSearchResults(unsigned int, std::string);
	Date getBeginning()
	{
		return beginning;
	}
	Date getEnding()
	{
		return ending;
	}
private:
	Date beginning;
	Date ending;
};


#endif
