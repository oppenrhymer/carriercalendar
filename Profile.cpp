#include "stdafx.h"
#include "Profile.h"
#include <iostream>
#include <fstream>
void Profile::displayProfile()
{
	std::cout << "Day off schedule: " << std::endl;
	for (auto& i : dayOffColor)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	return;
}
void Profile::saveProfile(const std::vector<std::string>& daysoff, bool rotSched)
{
	//STILL NEED TO DO ERROR CHECKING
	std::ofstream file("C:/Users/Ryan/Documents/Visual Studio 2015/Projects/USPSCalendar/USPSCalendar/PROFILE.RB");

	for (auto& i : daysoff)
	{
		file << i << " ";

	}
	//file << "\n" << rotSched;
	file.close();
	
	return;
}

void Profile::loadProfile()
{
	//STILL NEED TO DO ERROR CHECKING
	std::ifstream file("C:/Users/Ryan/Documents/Visual Studio 2015/Projects/USPSCalendar/USPSCalendar/PROFILE.RB");

	std::vector<std::string> strvec;
	std::string tmpstr;
	while (file >> tmpstr)
	{
		strvec.push_back(tmpstr);
		std::cout << "adding string to strvec..." << std::endl;

	}
	dayOffColor = strvec;
	return;
}
void Profile::deleteProfile()
{
	std::ofstream file;
	file.open("C:/Users/Ryan/Documents/Visual Studio 2015/Projects/USPSCalendar/USPSCalendar/PROFILE.RB", std::ofstream::out | std::ofstream::trunc);
	file.close();
	return;

}