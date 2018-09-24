// USPSCalendar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Months.h"
#include "Holidays.h"
#include "test.h"
#include <iostream>

int main()
{
	
	int y = 1;
	int d, m;
	while (y != 0)
	{
		Month month1;
		std::cout << "Enter a year: ";
		std::cin >> y;
		std::cout << "Enter a month: ";
		std::cin >> m;
		std::cout << "Enter a day: ";
		std::cin >> d;
		std::cout << "Initializing month class..." << std::endl;
		month1.initializeMonth(m, y);

		std::cout << "The day of the week for " << month1.getMonthName() << " " << d << ", " << y << " is ";
		int dotw = getDayOfTheWeek(m, d, y);
		displayDayOfTheWeek(dotw);
		std::cout << "." << std::endl;
		int holiday = checkIfHoliday(m, d, y);
		if (holiday)
		{
			displayHoliday(holiday);
			std::cout << " is on this date";
			if (dotw == 1)
			{
				std::cout << ", but it will be observed on Monday, " << month1.getMonthName() << " " << d << "." << std::endl;
			}
			else {
				std::cout << "." << std::endl;
			}
		}
		
		
	}

	return 0;
}

