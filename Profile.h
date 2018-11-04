#pragma once
#ifndef PROFILE_H
#define PROFILE_H
#include <string>
#include <vector>
#include <fstream>
class Profile {
public:

	void saveProfile(const std::vector<std::string>&, bool);
	void loadProfile();
	void deleteProfile();
	void displayProfile();
private:
	//If rotating, will be a single element (a color); if it is not, it will be two days of the week.
	std::vector<std::string> dayOffColor;

	bool rotatingSchedule;
	//list of potential annual candidate weeks

	//list of confirmed annual weeks
};

#endif