// USPSCalendar.cpp : Defines the entry point for the console application.
//Repo MASTER
//


#include "stdafx.h"
#include "Globals.h"
#include "Date.h"
#include "Profile.h"
#include "Menu.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

//AT PRESENT THIS TAKES TWO DATES FROM THE USER AND THEN PRINTS OUT ANY HOLIDAYS FOUND IN THAT PERIOD.
void loadSplash()
{
	std::ifstream splash("C:/Users/Ryan/Documents/Visual Studio 2015/Projects/USPSCalendar/USPSCalendar/logo.asc");
	HANDLE stdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << "\n\n\n\n";
	SetConsoleTextAttribute(stdOutput, FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << splash.rdbuf();
	
	SetConsoleCursorPosition(stdOutput, { 56 , 24 });
	SetConsoleTextAttribute(stdOutput, 7);
	std::cout << "The Amoral Agency, 2018";
	Sleep(4000);
	return;
}
int main(int argc, char* argv[])
{
	loadSplash();
	/*
	Profile newprof;
	std::vector<std::string> tempvec = { "GREEN","SUNDAY" };
	newprof.saveProfile(tempvec, 1);

	Profile newprof2;
	newprof2.loadProfile();
	newprof2.displayProfile();
	std::string dayOffColor = "GREEN";
	*/
	/*
	HWND hwnd = GetConsoleWindow();
	RECT rect = { 100, 100, 700, 1000 };
	MoveWindow(hwnd, rect.top, rect.left, rect.bottom - rect.top, rect.right - rect.left, TRUE);
	*/
	Date testDate(10, 1, 2018);
	Menu newmenu;
	int i = 7;
	int j = 2018;
	int p = 0;
	//Date currDate(10, 1, 2018);
	//Date nextMonth(11, 1, 2018);
	//newmenu.drawCalendar(currDate);
	newmenu.mainLoop(testDate);
	/*
	while (1)
	{
		Date currDate(i, 1, j);
		newmenu.drawCalendar(currDate);
		std::cout << "\n\n1: Search | 2: Add Day | 3: Load Profile | 4: Save Dates | 5: Exit" << std::endl;
		std::cin >> p;
		if (p == 1)
		{
			i++;
			if (i > 12)
			{
				i = 1;
				j++;
			}
		}
		if (p == -1)
		{
			i--;
			if (i < 1)
			{
				i = 12;
				j--;
			}
		}
		std::cin.clear();
		p = 0;

	}
	*/
	
	/*
	std::ifstream file("C:/Users/Ryan/Documents/Visual Studio 2015/Projects/USPSCalendar/USPSCalendar/SCHEDULE.INF");
	std::string dayOffColor;
	while (file >> dayOffColor)
	{
	std::cout << "Your day off schedule is: " << dayOffColor << std::endl;
	}
	*/

	//TO BE USED WHEN HIGHLIGHTING SELECTED OPTIONS. 112 = BACKGROUND GRAY 7 = DEFAULT COLOR

	HANDLE hConsole;

	int k, menuchoice;
	menuchoice = 0;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	/*k = 112;
	SetConsoleTextAttribute(hConsole, k);
	k = 7;
	SetConsoleTextAttribute(hConsole, k);
	*/
	unsigned char searchflags = 0;
	while (menuchoice != 10)
	{
		std::cout << "Search Criteria:\n";
		std::cout << "****************\n";
		if (searchflags & OPTION1_FLAG)
		{
			k = 112;
			SetConsoleTextAttribute(hConsole, k);
			std::cout << "1:";
			k = 7;
			SetConsoleTextAttribute(hConsole, k);
			std::cout << " Holidays" << std::endl;
		}
		else {
			std::cout << "1: Holidays" << std::endl;
		}
		if (searchflags & OPTION2_FLAG)
		{
			k = 112;
			SetConsoleTextAttribute(hConsole, k);
			std::cout << "2:";
			k = 7;
			SetConsoleTextAttribute(hConsole, k);
			std::cout << " Days Off" << std::endl;
		}
		else {
			std::cout << "2: Days Off" << std::endl;
		}
		if (searchflags & OPTION3_FLAG)
		{
			k = 112;
			SetConsoleTextAttribute(hConsole, k);
			std::cout << "3:";
			k = 7;
			SetConsoleTextAttribute(hConsole, k);
			std::cout << " Potential Forces" << std::endl;
		}
		else {
			std::cout << "3: Potential Forces" << std::endl;
		}
		std::cout << "****************\n\n";
		std::cout << "To add or remove, type corresponding number. '10' to quit: ";
		std::cin >> menuchoice;
		if (menuchoice == 1)
		{
			searchflags ^= OPTION1_FLAG;
		}
		if (menuchoice == 2)
		{
			searchflags ^= OPTION2_FLAG;
		}
		if (menuchoice == 3)
		{
			searchflags ^= OPTION3_FLAG;
		}
		std::cout << "\n\n\n";
	}



	return 0;
}
