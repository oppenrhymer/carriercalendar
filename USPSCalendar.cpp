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
	std::ifstream file("C:/Users/Ryan/Documents/Visual Studio 2015/Projects/USPSCalendar/USPSCalendar/SCHEDULE.INF");
	std::string dayOffColor;
	while (file >> dayOffColor)
	{
	std::cout << "Your day off schedule is: " << dayOffColor << std::endl;
	}
	*/




	return 0;
}
