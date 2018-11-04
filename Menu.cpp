#include "stdafx.h"
#include "Menu.h"
#include "Date.h"
#include "Search.h"
#include "Input.h"
#include <Windows.h>
#include <iostream>
#include <chrono>

Menu::Menu() {
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;
	calendarCoords = { ((csbi.dwSize.X / 2) - 10), 0 };
	menuCoords = { 0, 23 };
	moduleCoords = { 0, 11 }; //TEMPORARY. NEEDS TESTING 12
}
void Menu::clearScreen()
{
	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		))
	{
		std::cout << "Error clearing screen!\n";
		return;
	}
	FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		);
	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}


void Menu::clearCalendar()
{
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		(csbi.dwSize.X * 8),
		homeCoords,
		&count
		))
	{
		std::cout << "Error clearing screen!\n";
		return;
	}

	/* Fill the entire buffer with the current colors and attributes*/
	FillConsoleOutputAttribute(
	hStdOut,
	csbi.wAttributes,
	(csbi.dwSize.X * 8),
	homeCoords,
	&count
	);

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}



void Menu::clearMenu()
{
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		(csbi.dwSize.X),
		menuCoords,
		&count
		))
	{
		std::cout << "Error clearing screen!\n";
		return;
	}
	SetConsoleCursorPosition(hStdOut, menuCoords);
}


void Menu::clearModule()
{
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		(csbi.dwSize.X * 12),
		moduleCoords,
		&count
		))
	{
		std::cout << "Error clearing screen!\n";
		return;
	}
	FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		(csbi.dwSize.X * 12),
		moduleCoords,
		&count
		);
	SetConsoleCursorPosition(hStdOut, moduleCoords);
}


int Menu::drawCalendar()
{
	//currentDate = dte;
	COORD currentLine = calendarCoords;
	COORD debugCoords = { 0,20 };
	clearCalendar();

	//Display month and year
	SetConsoleCursorPosition(hStdOut, currentLine);
	std::cout << currentDate.getMonthName() << " " << currentDate.getYear() << std::endl;
	currentLine.Y++;
	SetConsoleCursorPosition(hStdOut, currentLine); 
	std::cout << "--------------------" << std::endl;
	currentLine.Y++;
	SetConsoleCursorPosition(hStdOut, currentLine);

	int dayOfWeekCounter = 1;

	//necessary to prevent overlap
	int monthLength = currentDate.getMonthLength();
	
	//this alters monthlength to account for redundant day checks, which occur when the first day of the month isn't sunday
	if (currentDate.getDayOfTheWeek() == 0)
	{
		monthLength += 7;
	}
	else {
		monthLength += currentDate.getDayOfTheWeek();
	}
	
	for (int i = 1; i < monthLength; i++)
	{
		if (dayOfWeekCounter == currentDate.getDayOfTheWeek())
		{
			if (currentDate.checkIfHoliday())
			{
				SetConsoleTextAttribute(hStdOut, 13);
			}
			//NEED TO ADD ALL DAY OFF SCHEDULES
			//**********
			//**********
			if (currentDate.isDayOff("BLUE"))
			{
				SetConsoleTextAttribute(hStdOut, 27);
			}
			
			if (currentDate.getDay() < 10)
			{
				std::cout << " " << currentDate.getDay() << " ";

			}
			else {
				std::cout << currentDate.getDay() << " ";
			}
			
			currentDate++;
			//End the current line if it reaches a Sunday (i.e. DOTW '1')
			if (currentDate.getDayOfTheWeek() == 1)
			{
				std::cout << std::endl;
				currentLine.Y++;
				SetConsoleCursorPosition(hStdOut, currentLine);
			}
			SetConsoleTextAttribute(hStdOut, 7);
		}
		else {
			std::cout << "   ";
		}
		dayOfWeekCounter++;
		//Saturday is considered '0' by getDayOfTheWeek(). Must account for that
		if (dayOfWeekCounter > 6)
		{
			dayOfWeekCounter = 0;
		}
		/*DEBUGGING INFO
		
		FillConsoleOutputCharacter(
			hStdOut,
			(TCHAR) ' ',
			(csbi.dwSize.X * 2),
			debugCoords,
			&count
			);
		SetConsoleCursorPosition(hStdOut, debugCoords);
		std::cout << "i: " << i << "   dayofweekcounter: " << dayOfWeekCounter << "  monthLength: " << monthLength << "  getDay: " << dte.getDay() 
			<< "   getMonthLength: " << dte.getMonthLength();
		Sleep(2000);
		SetConsoleCursorPosition(hStdOut, currentLine);
		*/
	}
	/*ORIGINAL*/
	//currentLine.Y += 2;
	//currentLine.X = 0;
	currentLine.Y = 9;
	currentLine.X = 0;
	SetConsoleCursorPosition(hStdOut, currentLine);
	for (int q = 0; q < 80; q++)
	{
		std::cout << "*";
	}
	currentLine.Y++;
	currentLine.X = 0;
	SetConsoleCursorPosition(hStdOut, currentLine);
	return 0;

}
int Menu::drawModule(int mod)
{
	clearModule();
	switch (mod)
	{
		case 1:
			//std::cout << "Search 10/1/2018 to 12/28/2018 BLUE\n";
			searchModuleMainLoop();
			break;
		case 2:
			std::cout << "You are utilizing the add day function.";
			break;
		case 3:
			std::cout << "You are utilizing the load profile function.";
			break;
		case 4:
			std::cout << "You are utilizing the save profile function.";
			break;
		default:
			std::cout << "There was an error with drawing the module.";
			break;
	}
	//Sleep(4000);
	clearModule();
	SetConsoleCursorPosition(hStdOut, menuCoords);
	return 0;
}
int Menu::drawMenu(int selection)
{
	//
	clearMenu();
	for (int q = 0; q < 80; q++)
	{
		std::cout << "*";
	}
	//std::cout << std::endl;
	if (selection == 1)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "1:";
		SetConsoleTextAttribute(hStdOut, 7);
	}
	else {
		std::cout << "1:";
	}
	std::cout << " Search | ";
	if (selection == 2)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "2:";
		SetConsoleTextAttribute(hStdOut, 7);
	}
	else {
		std::cout << "2:";
	}
	std::cout << " Add Day | ";
	if (selection == 3)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "3:";
		SetConsoleTextAttribute(hStdOut, 7);
	}
	else {
		std::cout << "3:";
	}
	std::cout << " Load Profile | ";
	if (selection == 4)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "4:";
		SetConsoleTextAttribute(hStdOut, 7);
	}
	else {
		std::cout << "4:";
	}
	std::cout << " Save Profile | ";
	if (selection == 5)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "5:";
		SetConsoleTextAttribute(hStdOut, 7);
	}
	else {
		std::cout << "5:";
	}
	std::cout << " Exit";
	
	SetConsoleCursorPosition(hStdOut, { 79,24 });

	return 0;
}

void Menu::mainLoop(const Date& dte)
{
	currentDate = dte;
	clearScreen();
	int selectCode = 1;
	int m = currentDate.getMonth();
	int y = currentDate.getYear();
	drawCalendar();
	drawMenu(0);
	while (1)
	{
		//1 == 1 key
		//2 == 2 key
		//3 == 3 key
		//4 == 4 key
		//5 == 5 key
		//6 == right arrow
		//7 == left arrow
		//8 == up arrow
		//9 == down arrow
		//10 == enter
		//11 == esc
		/*
		int keypress = getKeypress();
		
		Sleep(240);
		if (keypress == 5)
		{
			break;
		}
		if (keypress == 6)
		{
			//Sleep(240);
			m++;
			if (m > 12)
			{
				y++;
				m = 1;
			}
			currentDate.setDate(m, 1, y);
			drawCalendar();
			drawMenu(0);
			continue;
		}
		if (keypress == 7)
		{
			//Sleep(240);
			m--;
			if (m < 1)
			{
				y--;
				m = 12;
			}
			currentDate.setDate(m, 1, y);
			drawCalendar();
			drawMenu(0);
			continue;
		}
		drawMenu(keypress);
		drawModule(keypress);
		drawMenu(0);
		*/
		
		//1 through 5 keys
		if (GetKeyState(0x31) & 0x8000)
		{
			selectCode = 1;
			drawMenu(selectCode);
			drawModule(selectCode);
			drawMenu(0);
		}
		else
			if (GetKeyState(0x32) & 0x8000)
			{
				selectCode = 2;
				drawMenu(selectCode);
				drawModule(selectCode);
				drawMenu(0);
			}
			else
				if (GetKeyState(0x33) & 0x8000)
				{
					selectCode = 3;
					drawMenu(selectCode);
					drawModule(selectCode);
					drawMenu(0);
				}
				else
					if (GetKeyState(0x34) & 0x8000)
					{
						selectCode = 4;
						drawMenu(selectCode);
						drawModule(selectCode);
						drawMenu(0);
					}
					else
						if (GetKeyState(0x35) & 0x8000)
						{
							selectCode = 5;
							break;
						}
						else
							if (GetKeyState(0x27) & 0x8000) //right arrow
							{

								Sleep(240);
								m++;
								if (m > 12)
								{
									y++;
									m = 1;
								}
								currentDate.setDate(m, 1, y);
								drawCalendar();
								drawMenu(0);
							}
							else
								if (GetKeyState(0x25) & 0x8000) //left arrow
								{
									Sleep(240);
									m--;
									if (m < 1)
									{
										y--;
										m = 12;
									}
									currentDate.setDate(m, 1, y);
									drawCalendar();
									drawMenu(0);
								}
								else
								{
									continue;
								}
		
		
	}
	clearScreen();
	return;
}
