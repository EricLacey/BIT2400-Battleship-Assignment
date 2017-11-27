#pragma once

#include <iostream>
#include <vector>
#include "functions.h"

using namespace std;

enum FieldOrScreen { Field, screen };

class Position 
{
public:
	Position(int x, int y);

	bool operator==(Position rhs);
	bool operator==(Cursor rhs);

	
	bool m_isHit();
	void m_drawPosition();
	void m_drawPosition(int xOffset, int yOffset);


	void m_setPositionHit();

	int m_getX();
	int m_getY();

private:
	int m_x;
	int m_y;
	bool m_hit;
};