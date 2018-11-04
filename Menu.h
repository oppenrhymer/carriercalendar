#pragma once
#ifndef MENU_H
#define MENU_H
#include <vector>
#include <string>
#include <Windows.h>

#include "Date.h"

class Menu {
public:
	Menu();
	void clearScreen();
	void clearCalendar();
	void clearMenu();
	void clearModule();
	int drawCalendar();
	int drawMenu(int);
	int drawModule(int);
	void mainLoop(const Date&);
private:
	HANDLE                     hStdOut;					//Standard output
	CONSOLE_SCREEN_BUFFER_INFO csbi;					//contains console buffer information
	DWORD                      count;					//number of characters written
	DWORD                      cellCount;				//number of characters to write
	COORD                      homeCoords = { 0, 0 };	//origin
	COORD					   calendarCoords;			//coordinates for drawing the calendar
	COORD					   menuCoords;
	COORD					   moduleCoords;
	Date					   currentDate;				//working Date for displaying calendar

};

#endif