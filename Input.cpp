#include "stdafx.h"
#include <Windows.h>

void ClearConsoleInputBuffer()
{
	PINPUT_RECORD ClearingVar1 = new INPUT_RECORD[256];
	DWORD ClearingVar2;
	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), ClearingVar1, 256, &ClearingVar2);
	delete[] ClearingVar1;
}

int getKeypress()
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
	int keypress;

	while (1)
	{
		//1 key
		if (GetKeyState(0x31) & 0x8000)
		{
			keypress = 1;
			break;
		}
		else
			//2 key
			if (GetKeyState(0x32) & 0x8000)
			{
				keypress = 2;
				break;
			}
			else
				//3 key
				if (GetKeyState(0x33) & 0x8000)
				{
					keypress = 3;
					break;
				}
				else
					//4 key
					if (GetKeyState(0x34) & 0x8000)
					{
						keypress = 4;
						break;
					}
					else
						//5 key
						if (GetKeyState(0x35) & 0x8000)
						{
							keypress = 5;
							break;
						}
						else
							if (GetKeyState(0x27) & 0x8000) //right arrow
							{

								keypress = 6;
								break;
							}
							else
								if (GetKeyState(0x25) & 0x8000) //left arrow
								{
									keypress = 7;
									break;
								}
								else
									if (GetKeyState(0x26) & 0x8000) // up arrow
									{
										keypress = 8;
										break;
									}
									else
										if (GetKeyState(0x28) & 0x800) // down arrow
										{
											keypress = 9;
											break;
										}
										else 
											if (GetKeyState(0x0D) & 0x8000) // enter key
											{
												keypress = 10;
												break;
											}
											else
												if (GetKeyState(0x1B) & 0x800) // esc key
												{
													keypress = 11;
													break;
												}
												else
													{
														continue;
													}
		Sleep(240);
	}
	return keypress;
}