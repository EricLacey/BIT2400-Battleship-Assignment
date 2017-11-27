#include "stdafx.h"
#include "Positions.h"

Position::Position(int x, int y) 
{
	m_hit = false;
	m_x = x;
	m_y = y;
}

bool Position::operator==(Position rhs)
{
	if (( m_x == rhs.m_x ) && ( m_y == rhs.m_y))
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool Position::operator==(Cursor rhs)
{
	if ((m_x == rhs.m_X) && (m_y == rhs.m_Y))
	{
		return true;
	}
	else
	{
		return false;
	}

}

void Position::m_drawPosition()
{
	if (m_hit == true)
	{
		changeCursorColour(WHITE);
		gotoXY(m_x, m_y);
		cout << 'X';
	}
}
void Position::m_drawPosition(int xOffset, int yOffset)
{
	if (m_hit == true)
	{
		changeCursorColour(WHITE);
		gotoXY(m_x + xOffset, m_y + yOffset);
		cout << 'X';
	}
}



void Position::m_setPositionHit()
{
	m_hit = true;
}

bool Position::m_isHit()
{
	if (m_hit == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Position::m_getX()
{
	return m_x;
}
int Position::m_getY()
{
	return m_y;
}