/*
 * main.c
 *
 *  Created on: 27 Oct 2019
 *      Author: Richard Carter
 */

#include "ascii_game_template.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTitle("ASCII Console Game");

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // console output handle

	COORD size;
	size.X = 60;
	size.Y = 60;
	SMALL_RECT windowSize;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = size.X-1;
	windowSize.Bottom = size.Y-1;
	int success;
	success = SetConsoleScreenBufferSize(hStdOut, size);
	if (!success)
		printf("Set Buffer Size Error\n");
	success = SetConsoleWindowInfo(hStdOut, TRUE , &windowSize);
	if (!success)
		printf("Set Window Info Error\n");
	// Disables the auto return when out of space
	SetConsoleMode(hStdOut,  ENABLE_PROCESSED_OUTPUT);

	// Create cursorLocation variable
	COORD cursorLocation;

	// Draw border
	cursorLocation.X = 0;
	cursorLocation.Y = 0;
	SetCoord(cursorLocation);
	printf("╔");
	cursorLocation.X = windowSize.Right;
	cursorLocation.Y = 0;
	SetCoord(cursorLocation);
	printf("╗");
	cursorLocation.X = 0;
	cursorLocation.Y = windowSize.Bottom;
	SetCoord(cursorLocation);
	printf("╚");
	cursorLocation.X = windowSize.Right;
	cursorLocation.Y = windowSize.Bottom;
	SetCoord(cursorLocation);
	printf("╝\r");
	for (cursorLocation.Y = 1; cursorLocation.Y < windowSize.Bottom; cursorLocation.Y++)
	{
		cursorLocation.X = 0;
		SetCoord(cursorLocation);
		printf("║");
		cursorLocation.X = windowSize.Right;
		SetCoord(cursorLocation);
		printf("║");
	}
	for (cursorLocation.X = 1; cursorLocation.X < windowSize.Right; cursorLocation.X++)
	{
		cursorLocation.Y = 0;
		SetCoord(cursorLocation);
		printf("═");
		cursorLocation.Y = windowSize.Bottom;
		SetCoord(cursorLocation);
		printf("═");
	}

	cursorLocation.X = (windowSize.Right / 2)-13;
	cursorLocation.Y = windowSize.Bottom / 2;
	SetCoord(cursorLocation);
	printf("Try hitting the arrow keys!");
	cursorLocation = GetCoord();

	// Input loop
	while(1)
	{
		if (_kbhit())
		{
			unsigned char inputChar = _getch();
			if (inputChar == 0xE0)
			{
				switch (_getch())
				{
					case 72:
						if (cursorLocation.Y > 1)
						{
							cursorLocation.Y--;
							SetCoord(cursorLocation);
						}
						break;
					case 80:
						if (cursorLocation.Y < windowSize.Bottom - 1)
						{
							cursorLocation.Y++;
							SetCoord(cursorLocation);
						}
						break;
					case 75:
						if (cursorLocation.X > 1)
						{
							cursorLocation.X--;
							SetCoord(cursorLocation);
						}
						break;
					case 77:
						if (cursorLocation.X < windowSize.Right - 1)
						{
							cursorLocation.X++;
							SetCoord(cursorLocation);
						}
						break;
				}
			}
		}
		Sleep(10);
	}

	return 0;
}

COORD GetCoord()
{
	// Gets various information about the screen buffer and extracts current Cursor Position
	// Hint: the cursor position changes when you print things
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(hStdOut, &csbiInfo);
	COORD dwCursorPosition = csbiInfo.dwCursorPosition;
	return dwCursorPosition;
}

void SetCoord(COORD coords)
{
	// Sets the new Cursor Position
  SetConsoleCursorPosition(hStdOut, coords);
}
