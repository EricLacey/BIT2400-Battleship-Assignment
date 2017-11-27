#include "stdafx.h"
#include "functions.h"





void drawBoard(int startPosX, int startPosY)
{
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			gotoXY(i + startPosX, j + startPosY);

			// OUTER WALLS
			//four corners
			if (i == 0 && j == 0)
			{
				cout << (char)201;
			}
			else if (i == 0 && j == 22)
			{
				cout << (char)200;
			}
			else if (i == 22 && j == 0)
			{
				cout << (char)187;
			}
			else if (i == 22 && j == 22)
			{
				cout << (char)188;
			}
			//side walls
			else if (i == 0 || i == 22)
			{

				if (i == 0)
				{
					cout << (char)204;
				}
				else
				{
					cout << (char)185;
				}

			}
			//top + bottom walls
			else if (j == 0 || j == 22)
			{
				if (j == 0)
				{
					cout << (char)203;
				}
				else
				{
					cout << (char)202;
				}
			}

			//INNER WALLS
			//four corners
			else if (i == 1 && j == 1)
			{
				cout << (char)218;
			}
			else if (i == 1 && j == 21)
			{
				cout << (char)192;
			}
			else if (i == 21 && j == 1)
			{
				cout << (char)191;
			}
			else if (i == 21 && j == 21)
			{
				cout << (char)217;
			}
			//side walls
			else if (i == 1 || i == 21)
			{
				if (j % 2 == 0)
				{
					cout << (char)179;
				}
				else
				{
					if (i == 1)
					{
						cout << (char)195;
					}
					else
					{
						cout << (char)180;
					}
				}
			}
			//top + bottom walls
			else if (j == 1 || j == 21)
			{
				if (i % 2 == 0)
				{
					cout << (char)196;
				}
				else
				{
					if (j == 1)
					{
						cout << (char)194;
					}
					else
					{
						cout << (char)193;
					}
				}
			}

			//CENTER AREA
			else if ((i % 2 != 0) && (j % 2 != 0))
			{
				cout << (char)197;
			}
			else if ((i % 2 != 0) && !(j % 2 != 0))
			{
				cout << (char)179;
			}
			else if (!(i % 2 != 0) && (j % 2 != 0))
			{
				cout << (char)196;
			}
		}
	}
}

void gotoXY(int x, int y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	SetConsoleCursorPosition(hStdout, position);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.dwSize = 10;
	SetConsoleCursorInfo(hStdout, &cursorInfo);

}

void makeCursorVisible()
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = true;
	cursorInfo.dwSize = 10;
	SetConsoleCursorInfo(hStdout, &cursorInfo);
}

void changeCursorColour(Colour colour)
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (colour)
	{
	case RED:
		SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED);
		break;
	case GREEN:
		SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_GREEN);
		break;
	case BLUE:
		SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_BLUE);
		break;
	case WHITE:
		SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case CYAN:
		SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	default:
		break;
	}

}
