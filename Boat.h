#pragma once

#include <iostream>
#include <vector>
#include "Positions.h"
#include "functions.h"
#include <Windows.h>

using namespace std;

enum Direction{NORTH, EAST, SOUTH, WEST};

class Boat 
{
public:
	Boat();

	Position m_getPosition(int i);
	int m_getSize();
	void m_setSpotHit(int i);
	bool m_isDead();
	bool m_isCollided(Boat* boat2);
	void m_drawBoat();
	void m_drawEnemyBoatsHit(int xOffset, int yOffset);
	void m_hideBoat();
	virtual void m_deathCall() = 0;
		

protected:
	int m_size;
	vector<Position> m_positions;
};

//////////////////////////////////////////////////

class Destroyer:public Boat 
{
public:
	Destroyer(int x_start, int y_start, Direction angle);
	~Destroyer();
	void m_deathCall();
private:

};

//////////////////////////////////////////////////

class Submarine:public Boat
{
public:
	Submarine(int x_start, int y_start, Direction angle);
	~Submarine();
	void m_deathCall();
private:

};

//////////////////////////////////////////////////

class Cruiser:public Boat
{
public:
	Cruiser(int x_start, int y_start, Direction angle);
	~Cruiser();
	void m_deathCall();
private:

};

//////////////////////////////////////////////////

class Battleship:public Boat
{
public:
	Battleship(int x_start, int y_start, Direction angle);
	~Battleship();
	void m_deathCall();
private:

};

//////////////////////////////////////////////////

class Carrier:public Boat
{
public:
	Carrier(int x_start, int y_start, Direction angle);
	~Carrier();
	void m_deathCall();
private:

};

