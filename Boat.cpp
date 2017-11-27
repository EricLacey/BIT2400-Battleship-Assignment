#include "stdafx.h"
#include "Boat.h"
#include "functions.h"

///////////////////////////////////////////////////////////////

Boat::Boat(){}

Position Boat::m_getPosition(int i)
{
	return m_positions[i];
}

int Boat::m_getSize()
{
	return m_size;
}

void Boat::m_setSpotHit(int i)
{
	m_positions[i].m_setPositionHit();
}

bool Boat::m_isDead()
{
	int hitCount = 0;

	for (int i = 0; i < m_positions.size(); i++)
	{
		if (m_positions[i].m_isHit())
		{
			hitCount++;
		}
	}

	if (hitCount == m_size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Boat::m_isCollided(Boat* boat2)
{
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < boat2->m_size; j++)
		{
			if (m_positions[i] == boat2->m_positions[j])
			{
				return true;
			}
		}
	}

	return false;
}

void Boat::m_drawBoat()
{
	for (int i = 0; i < m_size; i++)
	{
		gotoXY(m_positions[i].m_getX(), m_positions[i].m_getY());
		
		if (m_positions[i].m_isHit())
		{
			changeCursorColour(RED);
			cout << (char)178;
		}
		else
		{
			changeCursorColour(GREEN);
			cout << (char)178;
		}
	}
	
}

//this function draws all the enemy's hit boat spaces, to be placed on the player's screen
void Boat::m_drawEnemyBoatsHit(int xOffset, int yOffset)
{
	{
		for (int i = 0; i < m_size; i++)
		{
			if (m_positions[i].m_isHit())
			{
				gotoXY(m_positions[i].m_getX() + xOffset, m_positions[i].m_getY() + yOffset);

				changeCursorColour(RED);
				cout << 'X';
			}
		}
	}
}

//this function hides all boats on the player's fields
void Boat::m_hideBoat()
{
	for (int i = 0; i < m_size; i++)
	{
		gotoXY(m_positions[i].m_getX(), m_positions[i].m_getY());
		cout << ' ';
	}
}


///////////////////////////////////////////////////////////////
Destroyer::Destroyer(int x_start, int y_start, Direction angle) 
{
	m_size = 2;

	if (angle == NORTH)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start, y_start - (2 * i));
			m_positions.push_back(newpos);
		}
	}
	else if (angle == EAST)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start + (2 * i), y_start);
			m_positions.push_back(newpos);
		}
	}
	else if (angle == SOUTH)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start, y_start + (2 * i));
			m_positions.push_back(newpos);
		}
	}
	else if (angle == WEST)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start - (2 * i), y_start);
			m_positions.push_back(newpos);
		}
	}
}

Destroyer::~Destroyer() 
{
	m_hideBoat();
}

void Destroyer::m_deathCall()
{
	cout << "You sank my Destroyer!" << endl;
}


///////////////////////////////////////////////////////////////

Submarine::Submarine(int x_start, int y_start, Direction angle)
{
	m_size = 3;

	if (angle == NORTH)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start, y_start - (2 * i));
			m_positions.push_back(newpos);
		}
	}
	else if (angle == EAST)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start + (2 * i), y_start);
			m_positions.push_back(newpos);
		}
	}
	else if (angle == SOUTH)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start, y_start + (2 * i));
			m_positions.push_back(newpos);
		}
	}
	else if (angle == WEST)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start - (2 * i), y_start);
			m_positions.push_back(newpos);
		}
	}
}

Submarine::~Submarine()
{
	m_hideBoat();
}

void Submarine::m_deathCall()
{
	cout << "You sank my Submarine!" << endl;
}

///////////////////////////////////////////////////////////////

Cruiser::Cruiser(int x_start, int y_start, Direction angle)
{
	m_size = 3;

	if (angle == NORTH)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start, y_start - (2 * i));
			m_positions.push_back(newpos);
		}
	}
	else if (angle == EAST)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start + (2 * i), y_start);
			m_positions.push_back(newpos);
		}
	}
	else if (angle == SOUTH)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start, y_start + (2 * i));
			m_positions.push_back(newpos);
		}
	}
	else if (angle == WEST)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start - (2 * i), y_start);
			m_positions.push_back(newpos);
		}
	}
}

Cruiser::~Cruiser()
{
	m_hideBoat();
}

void Cruiser::m_deathCall()
{
	cout << "You sank my Cruiser!" << endl;
}

///////////////////////////////////////////////////////////////

Battleship::Battleship(int x_start, int y_start, Direction angle)
{
	m_size = 4;

	if (angle == NORTH)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start, y_start - (2 * i));
			m_positions.push_back(newpos);
		}
	}
	else if (angle == EAST)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start + (2 * i), y_start);
			m_positions.push_back(newpos);
		}
	}
	else if (angle == SOUTH)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start, y_start + (2 * i));
			m_positions.push_back(newpos);
		}
	}
	else if (angle == WEST)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start - (2 * i), y_start);
			m_positions.push_back(newpos);
		}
	}
}

Battleship::~Battleship()
{
	m_hideBoat();
}

void Battleship::m_deathCall()
{
	cout << "You sank my Battleship!" << endl;
}

///////////////////////////////////////////////////////////////

Carrier::Carrier(int x_start, int y_start, Direction angle)
{
	m_size = 5;

	if (angle == NORTH)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start, y_start - (2 * i));
			m_positions.push_back(newpos);
		}
	}
	else if (angle == EAST)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start + (2 * i), y_start);
			m_positions.push_back(newpos);
		}
	}
	else if (angle == SOUTH)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start, y_start + (2 * i));
			m_positions.push_back(newpos);
		}
	}
	else if (angle == WEST)
	{
		for (int i = 0; i < m_size; i++)
		{
			Position newpos(x_start - (2 * i), y_start);
			m_positions.push_back(newpos);
		}
	}
}


Carrier::~Carrier()
{
	m_hideBoat();
}


void Carrier::m_deathCall()
{
	cout << "You sank my Carrier!" << endl;
}

