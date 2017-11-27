#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <stdio.h>

using namespace std;

enum Colour { RED, GREEN, BLUE, CYAN, WHITE };

struct Cursor
{
	int m_X;
	int m_Y;
	int m_PrevX;
	int m_PrevY;
	int m_AsciiChar;
	Cursor() {};
	Cursor(int x, int y, int ascii) : m_X(x), m_Y(y), m_PrevX(x), m_PrevY(y), m_AsciiChar(ascii) {};
};

//this function draws 
void gotoXY(int x, int y);
void drawBoard(int startPosX, int startPosY);
void changeCursorColour(Colour colour);