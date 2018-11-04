#include "stdafx.h"
#include "Search.h"
#include "Input.h"
#include "Globals.h"
#include <iostream>
#include <bitset>

void clrModule()
{
	//This is dumb; should not be duplicating this
	COORD moduleCoords = { 0, 11 };
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD cellCount;
	DWORD count;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;
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
	return;
}
void clrDateEntry()
{
	//This is REALLY dumb
	COORD entryCoords = { 0, 13 };
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD cellCount;
	DWORD count;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		(40),
		entryCoords,
		&count
		))
	{
		std::cout << "Error clearing screen!\n";
		return;
	}
	FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		(40),
		entryCoords,
		&count
		);
	SetConsoleCursorPosition(hStdOut, entryCoords);
	return;
}
int getNumberOfPages(int numberOfResults)
{
	int pages = 0;
	pages = numberOfResults / 25;
	return pages;
}






void drawPage(int page, std::list<Date>::iterator& pageBegin, std::list<Date>::iterator& pageEnd, int xResult, int yResult)
{
	//NOTE: CURRENTLY 5 col by 5 rows. For single days. 
	//WANT TO ADD 3 col (two dates separated by a hyphen) by 6 rows for weeks
	int x, y;
	x = y = 0;
	int NUMBER_OF_ROWS = 5;
	int NUMBER_OF_COLUMNS = 5;
	std::list<Date>::iterator currentItem = pageBegin;
	//console position handling
	COORD itemCoordinates = { 0 , 11 };
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	

	//Ok, so this isn't working. I think if we track both the .begin() & .end() iterators, AS WELL, as the iterator at the beginning of each page, 
	//we can make this happen. Using std::list is still probably the right move, because we need to have fast random access deletion, so users
	//can remove dates from the list, at will.


	for (int i = 0; i < NUMBER_OF_COLUMNS; i++)
	{

		for (int j = 0; j < NUMBER_OF_ROWS; j++)
		{
			SetConsoleCursorPosition(hStdOut, itemCoordinates);
			if ((x == xResult) && (y == yResult))
			{
				SetConsoleTextAttribute(hStdOut, 112);
				currentItem->displayDate();
				SetConsoleTextAttribute(hStdOut, 7);
			}
			else {
				currentItem->displayDate();
			}
			
			itemCoordinates.Y += 2;
			SetConsoleCursorPosition(hStdOut, itemCoordinates);
			y++;
			currentItem++;
			if (currentItem == pageEnd)
			{
				break;
			}
		}
		if (currentItem == pageEnd)
		{
			break;
		}
		x++;
		y = 0;
		itemCoordinates.X += 12;
		itemCoordinates.Y = 11;
		SetConsoleCursorPosition(hStdOut, itemCoordinates);
	}

	return;
}

//User input for search parameters
void drawSearchParametersDates(Date& beginning,Date& ending, bool uninitialized = false)
{
	COORD itemCoordinates = { 68, 13 };
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdOut, itemCoordinates);

	std::cout << "************";
	itemCoordinates = { 68, 14 };
	SetConsoleCursorPosition(hStdOut, itemCoordinates);
	std::cout << "*";
	if (uninitialized)
	{
		std::cout << "DATES NOT";
		itemCoordinates = { 68, 15 };
		SetConsoleCursorPosition(hStdOut, itemCoordinates);
		std::cout << "*YET SET.";
		itemCoordinates = { 68, 16 };
		SetConsoleCursorPosition(hStdOut, itemCoordinates);
		std::cout << "*";
	}
	else {
		beginning.displayDate();
		itemCoordinates = { 68, 15 };
		SetConsoleCursorPosition(hStdOut, itemCoordinates);
		std::cout << "*    to";
		itemCoordinates = { 68, 16 };
		SetConsoleCursorPosition(hStdOut, itemCoordinates);
		std::cout << "*";
		ending.displayDate();
	}
	itemCoordinates = { 68, 17 };
	SetConsoleCursorPosition(hStdOut, itemCoordinates);
	std::cout << "************";
	return;
	
}
//
//   03/23/1985
//
//   Sat Sun Mon Tue Wed Thu Fri
//   [X] [ ] [ ] [ ] [ ] [ ] [ ]
//
void drawSearchParameters(Date& beginning, Date& ending, unsigned char flags = 0b0000'0000, unsigned int pFlags = 0b0000'0000'0000'0000'0000'0000'0000'0000, int x = -1, int y = 0)
{
	clrModule();
	COORD itemCoordinates = { 0 , 11 };
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdOut, itemCoordinates);

	//for flag operations
	int dayOffset = (-(x)+7);
	int paramOffset = ((dayOffset - 1) * 3);


	beginning.displayDate();
	std::cout << " to ";
	ending.displayDate();
	std::cout << "    " << std::bitset<32>(pFlags);
	itemCoordinates.Y += 4;
	SetConsoleCursorPosition(hStdOut, itemCoordinates);
	std::cout << "Sat Sun Mon Tue Wed Thu Fri";
	itemCoordinates.Y++;
	SetConsoleCursorPosition(hStdOut, itemCoordinates);
	if (x == 0)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "[";
		if (flags & OPTION7_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]";
		SetConsoleTextAttribute(hStdOut, 7);
		std::cout << " ";
	}
	else {
		std::cout << "[";
		if (flags & OPTION7_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "] ";
	}
	if (x == 1)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "[";
		if (flags & OPTION6_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]";
		SetConsoleTextAttribute(hStdOut, 7);
		std::cout << " ";
	}
	else {
		std::cout << "[";
		if (flags & OPTION6_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "] ";
	}
	if (x == 2)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "[";
		if (flags & OPTION5_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]";
		SetConsoleTextAttribute(hStdOut, 7);
		std::cout << " ";
	}
	else {
		std::cout << "[";
		if (flags & OPTION5_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "] ";
	}
	if (x == 3)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "[";
		if (flags & OPTION4_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]";
		SetConsoleTextAttribute(hStdOut, 7);
		std::cout << " ";
	}
	else {
		std::cout << "[";
		if (flags & OPTION4_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "] ";
	}
	if (x == 4)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "[";
		if (flags & OPTION3_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]";
		SetConsoleTextAttribute(hStdOut, 7);
		std::cout << " ";
	}
	else {
		std::cout << "[";
		if (flags & OPTION3_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "] ";
	}
	if (x == 5)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "[";
		if (flags & OPTION2_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]";
		SetConsoleTextAttribute(hStdOut, 7);
		std::cout << " ";
	}
	else {
		std::cout << "[";
		if (flags & OPTION2_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "] ";
	}
	if (x == 6)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "[";
		if (flags & OPTION1_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]";
		SetConsoleTextAttribute(hStdOut, 7);
		std::cout << " ";
	}
	else {
		std::cout << "[";
		if (flags & OPTION1_FLAG)
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]";
	}
	itemCoordinates.Y += 2;
	SetConsoleCursorPosition(hStdOut, itemCoordinates);
	std::cout << "Hol  SDO  BTH";
	itemCoordinates.Y++;
	SetConsoleCursorPosition(hStdOut, itemCoordinates);
	if (y == 1)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "[";
		if (pFlags & (1 << paramOffset))
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]";
		SetConsoleTextAttribute(hStdOut, 7);
		std::cout << "  ";
	}
	else {
		std::cout << "[";
		if (pFlags & (1 << paramOffset))
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]  ";
	}
	if (y == 2)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "[";
		if (pFlags & (1 << (paramOffset + 1)))
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]";
		SetConsoleTextAttribute(hStdOut, 7);
		std::cout << "  ";
	}
	else {
		std::cout << "[";
		if (pFlags & (1 << (paramOffset + 1)))
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]  ";
	}
	if (y == 3)
	{
		SetConsoleTextAttribute(hStdOut, 112);
		std::cout << "[";
		if (pFlags & (1 << (paramOffset + 2)))
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]";
		SetConsoleTextAttribute(hStdOut, 7);
		std::cout << "  ";
	}
	else {
		std::cout << "[";
		if (pFlags & (1 << (paramOffset + 2)))
		{
			std::cout << "X";
		}
		else {
			std::cout << " ";
		}
		std::cout << "]";
	}
	return;
}
std::pair<Period,unsigned int> getSearchParameters()
{
	//found function
	ClearConsoleInputBuffer();

	////


	COORD itemCoordinates = { 0 , 13 };
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdOut, itemCoordinates);
	char unsigned dayFlags = 0b0000'0000;
	unsigned int paramFlags = 0b0000'0000'0000'0000'0000'0000'0000'0000;
	int m, d, y;
	Date beginning(0, 0, 0);
	Date ending(0, 0, 0);
	drawSearchParameters(beginning, ending, dayFlags, paramFlags);
	Sleep(4000);
	SetConsoleCursorPosition(hStdOut, itemCoordinates);
	//while (1)
	//{
		std::cout.flush();
		std::cin.clear();
		std::cout << "Month? ";
		std::cin >> m;
		clrDateEntry();
		std::cout << "Day? ";
		std::cin >> d;
		clrDateEntry();
		std::cout << "Year? ";
		std::cin >> y;
		clrDateEntry();
		beginning = Date(m, d, y);
		std::cout << "Month? ";
		std::cin >> m;
		clrDateEntry();
		std::cout << "Day? ";
		std::cin >> d;
		clrDateEntry();
		std::cout << "Year? ";
		std::cin >> y;
		clrDateEntry();
		ending = Date(m, d, y);

	//}
	
	
	//Search Options Loop
	int dayOfWeekCoord = 0;
	int searchCriterionCoord = 1;
	drawSearchParameters(beginning, ending, dayFlags, paramFlags,dayOfWeekCoord);
	ClearConsoleInputBuffer();
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
		int keypress = getKeypress();
		Sleep(240);
		if (keypress == 6)
		{
			if (dayOfWeekCoord == 6)
			{
				dayOfWeekCoord = 0;
			}
			else {
				dayOfWeekCoord++;
			}
			drawSearchParameters(beginning, ending, dayFlags, paramFlags, dayOfWeekCoord);
		}
		if (keypress == 7)
		{
			if (dayOfWeekCoord == 0)
			{
				dayOfWeekCoord = 6;
			}
			else {
				dayOfWeekCoord--;
			}
			drawSearchParameters(beginning, ending, dayFlags, paramFlags, dayOfWeekCoord);
		}
		if (keypress == 10)
		{
			//compute bit position from dayOfWeekCoord (0 = Sat through 6 = Fri)
			
			int dayOffset = (-(dayOfWeekCoord)+7);
			if (dayFlags & (1 << (dayOffset - 1)))
			{
				dayFlags &= ~(1 << (dayOffset - 1));
				//ADD CODE TO CHANGE PARAMETER FLAGS!!!!
				


			}
			else {
				dayFlags |= 1 << (dayOffset - 1);
				drawSearchParameters(beginning, ending, dayFlags, paramFlags, dayOfWeekCoord, searchCriterionCoord);
				ClearConsoleInputBuffer();
				while (1)
				{
					keypress = getKeypress();
					Sleep(240);
					if (keypress == 6)
					{
						if (searchCriterionCoord == 3)
						{
							searchCriterionCoord = 1;
						}
						else {
							searchCriterionCoord++;
						}
						drawSearchParameters(beginning, ending, dayFlags, paramFlags, dayOfWeekCoord, searchCriterionCoord);
					}
					if (keypress == 7)
					{
						if (searchCriterionCoord == 1)
						{
							searchCriterionCoord = 3;
						}
						else {
							searchCriterionCoord--;
						}
						drawSearchParameters(beginning, ending, dayFlags, paramFlags, dayOfWeekCoord, searchCriterionCoord);
					}
					if (keypress == 10)
					{
						//compute bit position from searchCriterionCoord
						int paramOffset = ((dayOffset - 1) * 3) + (searchCriterionCoord - 1);
						if (paramFlags & (1 << paramOffset))
						{
							paramFlags &= ~(1 << paramOffset);
						}
						else {
							paramFlags |= (1 << paramOffset);
						}
						drawSearchParameters(beginning, ending, dayFlags, paramFlags, dayOfWeekCoord, searchCriterionCoord);
					}
					if (keypress == 11)
					{
						keypress = 0;
						ClearConsoleInputBuffer();
						break;
					}
				}
			}
			drawSearchParameters(beginning, ending, dayFlags, paramFlags, dayOfWeekCoord);
		}
		if (keypress == 11)
		{
			break;
		}
	}
	Sleep(4000);
	
	//std::pair<Period, unsigned int> returnValue = { Period(beginning,ending), paramFlags };

	return std::pair<Period,unsigned int>(Period(beginning,ending), paramFlags);
}




void searchPeriod(Period& testPeriod, unsigned int searchFlags)
{
	//Period here is temporary, for testing. Need to get that date range from user
	//Date dte1(10, 1, 2018);
	//Date dte2(1, 25, 2020);
	//Date dte2(2, 25, 2019);
	//Period testPeriod(dte1, dte2);
	std::string dayoffcolor = "BLUE";
	const int ITEMS_PER_PAGE = 25;
	const int NUMBER_OF_COLUMNS = 5;
	

	int numberOfSearchResults = testPeriod.numberOfSearchResults(searchFlags, dayoffcolor);
	int numberOfPages = getNumberOfPages(numberOfSearchResults);
	if (numberOfSearchResults == 0)
	{
		std::cout << "There were no matches for that search criteria!";
		Sleep(1440);
		return;
	}
	//console position handling
	COORD itemCoordinates = { 0 , 10 };
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdOut, itemCoordinates );
	


	/*
	//1st iteration
	std::vector<Date> resultsVector = testPeriod.printPeriod(0b0000'0011, dayoffcolor);
	std::vector<Date>::iterator resultsVectorIterator = resultsVector.begin();
	std::deque<Date> resultsPagedDeque;
	
	
	while ((resultsVectorIterator != resultsVector.end()) && (resultsPagedDeque.size() < 25))
	{
		resultsPagedDeque.push_back(*resultsVectorIterator);
		resultsVectorIterator++;
	}

	*/

	std::list<Date> resultsList = testPeriod.printPeriod(searchFlags, dayoffcolor);
	std::list<Date>::iterator resultsListIteratorBegin = resultsList.begin();
	std::list<Date>::iterator resultsListIteratorEnd = resultsList.begin();
	std::list<Date>::iterator cursorIterator = resultsList.begin();
	std::cout << "num of results: " << numberOfSearchResults << "  num pages: " << numberOfPages << "  list size: " << resultsList.size();
	
	itemCoordinates = { 0, 11 };
	SetConsoleCursorPosition(hStdOut, itemCoordinates);
	int x, y, page, itemCounter;
	x = y = page = itemCounter = 0;


	//Set up the page iterators
	for (; resultsListIteratorEnd != resultsList.end(); resultsListIteratorEnd++)
	{
		itemCounter++;
		if (itemCounter == (ITEMS_PER_PAGE + 1))
		{
			break;
		}
	}
	
	drawSearchParametersDates(testPeriod.getBeginning(),testPeriod.getEnding());
	
	drawPage(page, resultsListIteratorBegin, resultsListIteratorEnd, x, y);
	while (1)
	{
		
		SetConsoleCursorPosition(hStdOut, { 55, 21 });
		std::cout << "x:" << x << "y:" << y << "page:" << page << " cursor?: "; 

		//Fixes bound checks for lowest date, but none other
		bool safeToIncrementCursor = true;
		
		cursorIterator++;
		if (cursorIterator == resultsList.end())
		{
			safeToIncrementCursor = false;
		}
		else {
			safeToIncrementCursor = true;
		}
		cursorIterator--;
		

		//Fixes bound checks for all others, in a full column
		bool safeToIncrementColumn = true;
		int cursorCounter = 0;
		for (int j = y; j <= 4; j++)
		{
			cursorCounter++;
			cursorIterator++;
			if (cursorIterator == resultsList.end())
			{
				safeToIncrementColumn = false;
				
				break;
			}
			
		}
		for (int k = 0; k < cursorCounter; k++)
		{
			cursorIterator--;
		}

		


		//for to diagnose cursorIterator math issues. WILL BREAK PROGRAM AT END OF RESULTSLIST
		cursorIterator->displayDate();

		SetConsoleCursorPosition(hStdOut, itemCoordinates);
		
		if ((GetKeyState(0x27) & 0x8000) && (x == (NUMBER_OF_COLUMNS - 1)) && (page < numberOfPages) && (safeToIncrementColumn)) //right arrow; NEXT PAGE
		{
			Sleep(240);
			page++;
			x = 0;
			y = 0;
			clrModule();
			itemCounter = 0;
			resultsListIteratorBegin = resultsListIteratorEnd;
			for (; resultsListIteratorEnd != resultsList.end(); resultsListIteratorEnd++)
			{
				itemCounter++;
				if (itemCounter == (ITEMS_PER_PAGE + 1))
				{
					break;
				}
			}
			cursorIterator = resultsListIteratorBegin;
			drawSearchParametersDates(testPeriod.getBeginning(),testPeriod.getEnding());
			drawPage(page, resultsListIteratorBegin, resultsListIteratorEnd, x, y);
		}
		if ((GetKeyState(0x25) & 0x8000) && (x == 0) && (page > 0)) //left arrow; PREV PAGE
		{
			Sleep(240);
			page--;
			x = 0;
			y = 0;
			clrModule();
			itemCounter = 0;
			//resultsListIteratorBegin--;
			resultsListIteratorEnd = resultsListIteratorBegin;
			for (; resultsListIteratorBegin != resultsList.begin(); resultsListIteratorBegin--)
			{
				itemCounter++;
				if (itemCounter == (ITEMS_PER_PAGE + 1))
				{
					break;
				}
			}
			
			cursorIterator = resultsListIteratorBegin;
			drawSearchParametersDates(testPeriod.getBeginning(),testPeriod.getEnding());
			drawPage(page, resultsListIteratorBegin, resultsListIteratorEnd, x, y);

		}
		if ((GetKeyState(0x27) & 0x8000) && (x < 4) && (safeToIncrementColumn)) //right arrow
		{
			Sleep(240);
			
			x++;	
			int newY = y;	
			for (int j = y; j < 4; j++)
			{

				if (cursorIterator == resultsList.end())
				{
					break;
				}
				cursorIterator++;
			}
			for (int k = 0; k <= y; k++)
			{
				cursorIterator++;

				if (cursorIterator == resultsList.end())
				{
					cursorIterator--;
					break;
				}
				newY = k;

				//SetConsoleCursorPosition(hStdOut, { 50, 22 });
				//std::cout << k << " ";
			}
			y = newY;
			drawPage(page, resultsListIteratorBegin, resultsListIteratorEnd, x, y);	

		}
		
		if ((GetKeyState(0x25) & 0x8000) && (x > 0)) //left arrow
		{
			Sleep(240);
			x--;
			
			int newY = y;
			for (int j = 4; j > y; j--)
			{

				if (cursorIterator == resultsList.begin())
				{
					break;
				}
				cursorIterator--;
			}
			for (int k = 0; k <= y; k++)
			{
				newY = k;
				if (cursorIterator == resultsList.begin())
				{
					break;
				}
				cursorIterator--;
				
			}
			y = newY;
			drawPage(page, resultsListIteratorBegin, resultsListIteratorEnd, x, y);
				
		}
		if ((GetKeyState(0x26) & 0x8000) && (y > 0)) //up arrow
		{
			Sleep(240);
			y--;
			cursorIterator--;
			drawPage(page, resultsListIteratorBegin, resultsListIteratorEnd, x, y);

		}
		if ((GetKeyState(0x28) & 0x8000) && (y < 4) && (safeToIncrementCursor)) //down arrow
		{
			Sleep(240);
			y++;
			cursorIterator++;
			drawPage(page, resultsListIteratorBegin, resultsListIteratorEnd, x, y);

		}
		if (GetKeyState(0x1B) & 0x8000)  //ESC
		{
			//Sleep(240);
			break;
		}

	}
	/*for (int i = 0; i < numberOfPages; i++)
	{

		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				std::cout << "Result: " << j;
				itemCoordinates.Y += 2;
				SetConsoleCursorPosition(hStdOut, itemCoordinates);
			}
			itemCoordinates.Y = 11;
			itemCoordinates.X += 12;
			SetConsoleCursorPosition(hStdOut, itemCoordinates);
		}
	}*/
	itemCoordinates.Y = 11;
	itemCoordinates.X = 0;
	SetConsoleCursorPosition(hStdOut, itemCoordinates);
	

	//int searchResults = testPeriod.numberOfSearchResults(0b0000'0011, dayoffcolor);
	//std::cout << "Number of results: " << searchResults;
	return;
}

void searchModuleMainLoop()
{
	Date beginning, ending;
	Period dateRange(beginning, ending);
	std::pair<Period, unsigned int> rangeAndParameters;
	while (1)
	{
		rangeAndParameters = getSearchParameters();
		clrModule();
		
		drawSearchParametersDates(rangeAndParameters.first.getBeginning(), rangeAndParameters.first.getEnding());
		searchPeriod(rangeAndParameters.first, rangeAndParameters.second);
		Sleep(1000);
		if (GetKeyState(0x1B) & 0x8000)  //ESC
		{
			//Sleep(240);
			break;
		}
	}

	return;
}