// Title: Assignment-4
//Author: Eric Lacey
//Objective : Construct battleship using both abstract and derived classes to develop our skills with those techniques
//

#include "stdafx.h"
#include "Boat.h"
#include "Positions.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include "functions.h"

using namespace std;


Colour cursorColour = WHITE;

int main()
{
	//create gamestates and substates for game
	enum GameState { Open, Menu, Multiplayer, Exit };
	enum SubState { Setup, Play };
	enum TurnOrder { Player1, Player2 };

	//create gamestate 
	GameState gamestate = Open;


	while (true)
	{
		//game opening
		if (gamestate == Open)
		{
			cout << "Opening screen\n";

			system("pause");
			system("cls");

			gamestate = Menu;
		}

		//menu of game
		if (gamestate == Menu)
		{
			while (gamestate == Menu)
			{
				int userInput;

				gotoXY(0, 0);
				cout << "Battleship \n\n";
				cout << "1- Start New Game\n";
				cout << "2- Exit Game\n";

				cin >> userInput;

				if (userInput == 1)
				{
					gamestate = Multiplayer;
				}
				else if (userInput == 2)
				{
					gamestate = Exit;
				}
				else
				{
					cout << "invalid respose, please try again\n\n";

					cin.clear();
					cin.ignore(100, '\n');
					system("pause");
				}
				system("cls");
			}
		}

		//gameplay
		if (gamestate == Multiplayer)
		{


			//create substate for game in setup mode
			SubState substate = Setup;
			TurnOrder playerTurn = Player1;

			//create two fields as 2d vectors of positions
			vector<vector<Position>> player1Field;
			vector<vector<Position>> player2Field;

			//create a vector for each players' boats
			vector<Boat*> player1Boats;
			vector<Boat*> player2Boats;


			//fill player fields
			for (int i = 0; i < 10; i++)
			{
				//push back a new column of positions to be written onto
				vector<Position> newColumn;
				player1Field.push_back(newColumn);
				player2Field.push_back(newColumn);

				for (int j = 0; j < 10; j++)
				{
					//push back 10 positions into the newly created column
					Position newPos1(((2 * j) + 12), ((2 * i) + 26));
					Position newPos2(((2 * j) + 52), ((2 * i) + 26));
					player1Field.at(i).push_back(newPos1);
					player2Field.at(i).push_back(newPos2);
				}
			}

			//begin setup
			while (substate == Setup && gamestate == Multiplayer)
			{
				//draw player 1 board
				drawBoard(10, 1);
				drawBoard(10, 24);
				gotoXY(15, 48);
				cout << "Player 1 Board";

				//draw player 2 board
				drawBoard(50, 1);
				drawBoard(50, 24);
				gotoXY(55, 48);
				cout << "Player 2 Board\n";

				//Player 1 setup
				if (playerTurn == Player1)
				{
					gotoXY(8, 50);
					cout << "Player 1, begin placing ships";

					//draw player 2 board blue

					changeCursorColour(BLUE);
					drawBoard(50, 1);
					drawBoard(50, 24);

					// Spawning in Carrier
					{

						//taken from notes and modified slightly
						changeCursorColour(RED);


						//define a cursor
						Cursor dude = Cursor(12, 26, 'X');

						//move cursor around to select the anchor point for rotation
						int character;
						while (true)
						{

							HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED);

							if (_kbhit())
							{
								character = _getch();
								switch (character)
								{
								case 80://down
									if (dude.m_Y + 2 <= 44)
									{
										dude.m_Y += 2;
									}
									break;

								case 72://up
									if (dude.m_Y - 2 >= 26)
									{
										dude.m_Y -= 2;
									}
									break;

								case 75://Left
									if (dude.m_X - 2 >= 12)
									{
										dude.m_X -= 2;
									}
									break;

								case 77://Right
									if (dude.m_X + 2 <= 30)
									{
										dude.m_X += 2;
									}
									break;
								case 13: //Enter
									break;
								}

								gotoXY(dude.m_X, dude.m_Y);
								cout << (char)dude.m_AsciiChar;

								//if the character moved, update its new location and clear its old location
								if ((dude.m_X != dude.m_PrevX) || (dude.m_Y != dude.m_PrevY))
								{
									gotoXY(dude.m_PrevX, dude.m_PrevY);
									cout << ' ';
									dude.m_PrevX = dude.m_X;
									dude.m_PrevY = dude.m_Y;
								}

								//if enter was pressed, begin placing boat from that anchor point
								if (character == 13)
								{
									COORD anchorPoint = { dude.m_X, dude.m_Y };
									Direction angle = NORTH;

									while (true)
									{

										gotoXY(8, 50);
										cout << "Use arrows to change direction, ENTER, press enter twice to select     ";

										changeCursorColour(GREEN);
										character = _getch();


										if (character == 80) //down
										{
											gotoXY(8, 50);
											angle = SOUTH;
											Carrier testCarrier(anchorPoint.X, anchorPoint.Y, angle);
											testCarrier.m_drawBoat();
											_getch();
										}
										else if (character == 72) //up
										{
											gotoXY(8, 50);
											angle = NORTH;
											Carrier testCarrier(anchorPoint.X, anchorPoint.Y, angle);
											testCarrier.m_drawBoat();
											_getch();
										}
										else if (character == 75) //left
										{
											gotoXY(8, 50);
											angle = WEST;
											Carrier testCarrier(anchorPoint.X, anchorPoint.Y, angle);
											testCarrier.m_drawBoat();
											_getch();
										}
										else if (character == 77) //right
										{
											gotoXY(8, 50);
											angle = EAST;
											Carrier testCarrier(anchorPoint.X, anchorPoint.Y, angle);
											testCarrier.m_drawBoat();
											_getch();

										}
										else if (character == 8) //backspace
										{
											break;
										}
										else if (character == 13) //enter
										{

											gotoXY(8, 50);

											Carrier testCarrier(anchorPoint.X, anchorPoint.Y, angle);

											//set up flag for confiming if test is good
											bool isGoodFlag = true;

											for (int i = 0; i < testCarrier.m_getSize(); i++)
											{
												if (testCarrier.m_getPosition(i).m_getX() > 30 || testCarrier.m_getPosition(i).m_getX() < 12 || testCarrier.m_getPosition(i).m_getY() > 44 || testCarrier.m_getPosition(i).m_getY() < 26)
												{
													gotoXY(8, 50);
													cout << "Invalid location                                    ";
													isGoodFlag = false;
												}
											}

											if (isGoodFlag == true)
											{
												Boat* carrier = new Carrier(anchorPoint.X, anchorPoint.Y, angle);
												player1Boats.push_back(carrier);
												goto P1Battleship;
											}
										}

										//redraw board in case of broken tiles
										changeCursorColour(WHITE);
										drawBoard(10, 1);
										drawBoard(10, 24);


									}

								}


							}

						}

					}

				P1Battleship:

					// Spawning in Battleship
					{
						//taken from notes and modified slightly
						changeCursorColour(RED);

						//define a cursor
						Cursor dude = Cursor(12, 26, 'X');

						//move cursor around to select the anchor point for rotation
						int character;
						while (true)
						{

							for (int i = 0; i < player1Boats.size(); i++)
							{
								player1Boats[i]->m_drawBoat();
							}

							HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED);

							if (_kbhit())
							{
								character = _getch();
								switch (character)
								{
								case 80://down
									if (dude.m_Y + 2 <= 44)
									{
										dude.m_Y += 2;
									}
									break;

								case 72://up
									if (dude.m_Y - 2 >= 26)
									{
										dude.m_Y -= 2;
									}
									break;

								case 75://Left
									if (dude.m_X - 2 >= 12)
									{
										dude.m_X -= 2;
									}
									break;

								case 77://Right
									if (dude.m_X + 2 <= 30)
									{
										dude.m_X += 2;
									}
									break;
								case 13: //Enter
									break;
								}

								gotoXY(dude.m_X, dude.m_Y);
								cout << (char)dude.m_AsciiChar;

								//if the character moved, update its new location and clear its old location
								if ((dude.m_X != dude.m_PrevX) || (dude.m_Y != dude.m_PrevY))
								{
									gotoXY(dude.m_PrevX, dude.m_PrevY);
									cout << ' ';
									dude.m_PrevX = dude.m_X;
									dude.m_PrevY = dude.m_Y;
								}

								//if enter was pressed, begin placing boat from that anchor point
								if (character == 13)
								{
									COORD anchorPoint = { dude.m_X, dude.m_Y };
									Direction angle = NORTH;

									while (true)
									{

										gotoXY(8, 50);
										cout << "Use arrows to change direction, ENTER, press enter twice to select     ";

										changeCursorColour(GREEN);
										character = _getch();


										if (character == 80) //down
										{
											gotoXY(8, 50);
											angle = SOUTH;
											Battleship testBattleship(anchorPoint.X, anchorPoint.Y, angle);
											testBattleship.m_drawBoat();
											_getch();
										}
										else if (character == 72) //up
										{
											gotoXY(8, 50);
											angle = NORTH;
											Battleship testBattleship(anchorPoint.X, anchorPoint.Y, angle);
											testBattleship.m_drawBoat();
											_getch();
										}
										else if (character == 75) //left
										{
											gotoXY(8, 50);
											angle = WEST;
											Battleship testBattleship(anchorPoint.X, anchorPoint.Y, angle);
											testBattleship.m_drawBoat();
											_getch();
										}
										else if (character == 77) //right
										{
											gotoXY(8, 50);
											angle = EAST;
											Battleship testBattleship(anchorPoint.X, anchorPoint.Y, angle);
											testBattleship.m_drawBoat();
											_getch();

										}
										else if (character == 8) //backspace
										{
											break;
										}
										else if (character == 13) //enter
										{

											gotoXY(8, 50);

											Battleship testBattleship(anchorPoint.X, anchorPoint.Y, angle);
											testBattleship.m_drawBoat();

											//set up flag for confiming if test is good
											bool isGoodFlag = true;

											for (int i = 0; i < testBattleship.m_getSize(); i++)
											{
												for (int j = 0; j < player1Boats.size(); j++)
												{
													if (testBattleship.m_isCollided(player1Boats[j]))
													{
														isGoodFlag = false;
													}
												}
												if (testBattleship.m_getPosition(i).m_getX() > 30 || testBattleship.m_getPosition(i).m_getX() < 12 || testBattleship.m_getPosition(i).m_getY() > 44 || testBattleship.m_getPosition(i).m_getY() < 26)
												{
													gotoXY(8, 50);
													cout << "Invalid location                                    ";
													isGoodFlag = false;
												}
											}

											if (isGoodFlag == true)
											{
												Boat* battleship = new Battleship(anchorPoint.X, anchorPoint.Y, angle);
												player1Boats.push_back(battleship);
												goto P1Cruiser;
												;
											}
										}

										//redraw board in case of broken tiles
										changeCursorColour(WHITE);
										drawBoard(10, 1);
										drawBoard(10, 24);
									}
								}
							}
						}
					}


				P1Cruiser:
					// Spawning in Cruiser
					{
						//taken from notes and modified slightly
						changeCursorColour(RED);


						//define a cursor
						Cursor dude = Cursor(12, 26, 'X');

						//move cursor around to select the anchor point for rotation
						int character;
						while (true)
						{
							for (int i = 0; i < player1Boats.size(); i++)
							{
								player1Boats[i]->m_drawBoat();
							}

							HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED);

							if (_kbhit())
							{
								character = _getch();
								switch (character)
								{
								case 80://down
									if (dude.m_Y + 2 <= 44)
									{
										dude.m_Y += 2;
									}
									break;

								case 72://up
									if (dude.m_Y - 2 >= 26)
									{
										dude.m_Y -= 2;
									}
									break;

								case 75://Left
									if (dude.m_X - 2 >= 12)
									{
										dude.m_X -= 2;
									}
									break;

								case 77://Right
									if (dude.m_X + 2 <= 30)
									{
										dude.m_X += 2;
									}
									break;
								case 13: //Enter
									break;
								}

								gotoXY(dude.m_X, dude.m_Y);
								cout << (char)dude.m_AsciiChar;

								//if the character moved, update its new location and clear its old location
								if ((dude.m_X != dude.m_PrevX) || (dude.m_Y != dude.m_PrevY))
								{
									gotoXY(dude.m_PrevX, dude.m_PrevY);
									cout << ' ';
									dude.m_PrevX = dude.m_X;
									dude.m_PrevY = dude.m_Y;
								}

								//if enter was pressed, begin placing boat from that anchor point
								if (character == 13)
								{
									COORD anchorPoint = { dude.m_X, dude.m_Y };
									Direction angle = NORTH;

									while (true)
									{

										gotoXY(8, 50);
										cout << "Use arrows to change direction, ENTER, press enter twice to select     ";

										changeCursorColour(GREEN);
										character = _getch();


										if (character == 80) //down
										{
											gotoXY(8, 50);
											angle = SOUTH;
											Cruiser testCruiser(anchorPoint.X, anchorPoint.Y, angle);
											testCruiser.m_drawBoat();
											_getch();
										}
										else if (character == 72) //up
										{
											gotoXY(8, 50);
											angle = NORTH;
											Cruiser testCruiser(anchorPoint.X, anchorPoint.Y, angle);
											testCruiser.m_drawBoat();
											_getch();
										}
										else if (character == 75) //left
										{
											gotoXY(8, 50);
											angle = WEST;
											Cruiser testCruiser(anchorPoint.X, anchorPoint.Y, angle);
											testCruiser.m_drawBoat();
											_getch();
										}
										else if (character == 77) //right
										{
											gotoXY(8, 50);
											angle = EAST;
											Cruiser testCruiser(anchorPoint.X, anchorPoint.Y, angle);
											testCruiser.m_drawBoat();
											_getch();

										}
										else if (character == 8) //backspace
										{
											break;
										}
										else if (character == 13) //enter
										{

											gotoXY(8, 50);

											Cruiser testCruiser(anchorPoint.X, anchorPoint.Y, angle);
											testCruiser.m_drawBoat();

											//set up flag for confiming if test is good
											bool isGoodFlag = true;

											for (int i = 0; i < testCruiser.m_getSize(); i++)
											{
												for (int j = 0; j < player1Boats.size(); j++)
												{
													if (testCruiser.m_isCollided(player1Boats[j]))
													{
														isGoodFlag = false;
													}
												}
												if (testCruiser.m_getPosition(i).m_getX() > 30 || testCruiser.m_getPosition(i).m_getX() < 12 || testCruiser.m_getPosition(i).m_getY() > 44 || testCruiser.m_getPosition(i).m_getY() < 26)
												{
													gotoXY(8, 50);
													cout << "Invalid location                                    ";
													isGoodFlag = false;
												}
											}

											if (isGoodFlag == true)
											{
												Boat* cruiser = new Cruiser(anchorPoint.X, anchorPoint.Y, angle);
												player1Boats.push_back(cruiser);
												goto P1Submarine;
											}
										}

										//redraw board in case of broken tiles
										changeCursorColour(WHITE);
										drawBoard(10, 1);
										drawBoard(10, 24);
									}
								}
							}
						}
					}

				P1Submarine:
					// Spawning in Submarine
					{
						//taken from notes and modified slightly
						changeCursorColour(RED);


						//define a cursor
						Cursor dude = Cursor(12, 26, 'X');

						//move cursor around to select the anchor point for rotation
						int character;
						while (true)
						{
							for (int i = 0; i < player1Boats.size(); i++)
							{
								player1Boats[i]->m_drawBoat();
							}

							HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED);

							if (_kbhit())
							{
								character = _getch();
								switch (character)
								{
								case 80://down
									if (dude.m_Y + 2 <= 44)
									{
										dude.m_Y += 2;
									}
									break;

								case 72://up
									if (dude.m_Y - 2 >= 26)
									{
										dude.m_Y -= 2;
									}
									break;

								case 75://Left
									if (dude.m_X - 2 >= 12)
									{
										dude.m_X -= 2;
									}
									break;

								case 77://Right
									if (dude.m_X + 2 <= 30)
									{
										dude.m_X += 2;
									}
									break;
								case 13: //Enter
									break;
								}

								gotoXY(dude.m_X, dude.m_Y);
								cout << (char)dude.m_AsciiChar;

								//if the character moved, update its new location and clear its old location
								if ((dude.m_X != dude.m_PrevX) || (dude.m_Y != dude.m_PrevY))
								{
									gotoXY(dude.m_PrevX, dude.m_PrevY);
									cout << ' ';
									dude.m_PrevX = dude.m_X;
									dude.m_PrevY = dude.m_Y;
								}

								//if enter was pressed, begin placing boat from that anchor point
								if (character == 13)
								{
									COORD anchorPoint = { dude.m_X, dude.m_Y };
									Direction angle = NORTH;

									while (true)
									{

										gotoXY(8, 50);
										cout << "Use arrows to change direction, ENTER, press enter twice to select     ";

										changeCursorColour(GREEN);
										character = _getch();


										if (character == 80) //down
										{
											gotoXY(8, 50);
											angle = SOUTH;
											Submarine testSubmarine(anchorPoint.X, anchorPoint.Y, angle);
											testSubmarine.m_drawBoat();
											_getch();
										}
										else if (character == 72) //up
										{
											gotoXY(8, 50);
											angle = NORTH;
											Submarine testSubmarine(anchorPoint.X, anchorPoint.Y, angle);
											testSubmarine.m_drawBoat();
											_getch();
										}
										else if (character == 75) //left
										{
											gotoXY(8, 50);
											angle = WEST;
											Submarine testSubmarine(anchorPoint.X, anchorPoint.Y, angle);
											testSubmarine.m_drawBoat();
											_getch();
										}
										else if (character == 77) //right
										{
											gotoXY(8, 50);
											angle = EAST;
											Submarine testSubmarine(anchorPoint.X, anchorPoint.Y, angle);
											testSubmarine.m_drawBoat();
											_getch();

										}
										else if (character == 8) //backspace
										{
											break;
										}
										else if (character == 13) //enter
										{

											gotoXY(8, 50);

											Submarine testSubmarine(anchorPoint.X, anchorPoint.Y, angle);
											testSubmarine.m_drawBoat();

											//set up flag for confiming if test is good
											bool isGoodFlag = true;

											for (int i = 0; i < testSubmarine.m_getSize(); i++)
											{
												for (int j = 0; j < player1Boats.size(); j++)
												{
													if (testSubmarine.m_isCollided(player1Boats[j]))
													{
														isGoodFlag = false;
													}
												}
												if (testSubmarine.m_getPosition(i).m_getX() > 30 || testSubmarine.m_getPosition(i).m_getX() < 12 || testSubmarine.m_getPosition(i).m_getY() > 44 || testSubmarine.m_getPosition(i).m_getY() < 26)
												{
													gotoXY(8, 50);
													cout << "Invalid location                                    ";
													isGoodFlag = false;
												}
											}

											if (isGoodFlag == true)
											{
												Boat* sub = new Submarine(anchorPoint.X, anchorPoint.Y, angle);
												player1Boats.push_back(sub);
												goto P1Destroyer;
											}
										}

										//redraw board in case of broken tiles
										changeCursorColour(WHITE);
										drawBoard(10, 1);
										drawBoard(10, 24);
									}
								}
							}
						}
					}

				P1Destroyer:
					// Spawning in Destroyer
					{

						//taken from notes and modified slightly
						changeCursorColour(RED);


						//define a cursor
						Cursor dude = Cursor(12, 26, 'X');

						//move cursor around to select the anchor point for rotation
						int character;
						while (true)
						{
							for (int i = 0; i < player1Boats.size(); i++)
							{
								player1Boats[i]->m_drawBoat();
							}

							HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED);

							if (_kbhit())
							{
								character = _getch();
								switch (character)
								{
								case 80://down
									if (dude.m_Y + 2 <= 44)
									{
										dude.m_Y += 2;
									}
									break;

								case 72://up
									if (dude.m_Y - 2 >= 26)
									{
										dude.m_Y -= 2;
									}
									break;

								case 75://Left
									if (dude.m_X - 2 >= 12)
									{
										dude.m_X -= 2;
									}
									break;

								case 77://Right
									if (dude.m_X + 2 <= 30)
									{
										dude.m_X += 2;
									}
									break;
								case 13: //Enter
									break;
								}

								gotoXY(dude.m_X, dude.m_Y);
								cout << (char)dude.m_AsciiChar;

								//if the character moved, update its new location and clear its old location
								if ((dude.m_X != dude.m_PrevX) || (dude.m_Y != dude.m_PrevY))
								{
									gotoXY(dude.m_PrevX, dude.m_PrevY);
									cout << ' ';
									dude.m_PrevX = dude.m_X;
									dude.m_PrevY = dude.m_Y;
								}

								//if enter was pressed, begin placing boat from that anchor point
								if (character == 13)
								{
									COORD anchorPoint = { dude.m_X, dude.m_Y };
									Direction angle = NORTH;

									while (true)
									{

										gotoXY(8, 50);
										cout << "Use arrows to change direction, ENTER, press enter twice to select     ";

										changeCursorColour(GREEN);
										character = _getch();


										if (character == 80) //down
										{
											gotoXY(8, 50);
											angle = SOUTH;
											Destroyer testDestroyer(anchorPoint.X, anchorPoint.Y, angle);
											testDestroyer.m_drawBoat();
											_getch();
										}
										else if (character == 72) //up
										{
											gotoXY(8, 50);
											angle = NORTH;
											Destroyer testDestroyer(anchorPoint.X, anchorPoint.Y, angle);
											testDestroyer.m_drawBoat();
											_getch();
										}
										else if (character == 75) //left
										{
											gotoXY(8, 50);
											angle = WEST;
											Destroyer testDestroyer(anchorPoint.X, anchorPoint.Y, angle);
											testDestroyer.m_drawBoat();
											_getch();
										}
										else if (character == 77) //right
										{
											gotoXY(8, 50);
											angle = EAST;
											Destroyer testDestroyer(anchorPoint.X, anchorPoint.Y, angle);
											testDestroyer.m_drawBoat();
											_getch();

										}
										else if (character == 8) //backspace
										{
											break;
										}
										else if (character == 13) //enter
										{

											gotoXY(8, 50);

											Destroyer testDestroyer(anchorPoint.X, anchorPoint.Y, angle);
											testDestroyer.m_drawBoat();

											//set up flag for confiming if test is good
											bool isGoodFlag = true;

											for (int i = 0; i < testDestroyer.m_getSize(); i++)
											{
												for (int j = 0; j < player1Boats.size(); j++)
												{
													if (testDestroyer.m_isCollided(player1Boats[j]))
													{
														isGoodFlag = false;
													}
												}
												if (testDestroyer.m_getPosition(i).m_getX() > 30 || testDestroyer.m_getPosition(i).m_getX() < 12 || testDestroyer.m_getPosition(i).m_getY() > 44 || testDestroyer.m_getPosition(i).m_getY() < 26)
												{
													gotoXY(8, 50);
													cout << "Invalid location                                    ";
													isGoodFlag = false;
												}
											}

											if (isGoodFlag == true)
											{
												Boat* destroyer = new Destroyer(anchorPoint.X, anchorPoint.Y, angle);
												player1Boats.push_back(destroyer);
												goto EndPlayer1Spawn;
											}
										}

										//redraw board in case of broken tiles
										changeCursorColour(WHITE);
										drawBoard(10, 1);
										drawBoard(10, 24);
									}
								}
							}
						}
					}
				}

			EndPlayer1Spawn:
				system("cls");

				//Player 2 setup
				if (playerTurn == Player1)
				{
					gotoXY(50, 50);
					cout << "Player 2, begin placing ships";

					//draw player 2 board white

					changeCursorColour(WHITE);
					drawBoard(50, 1);
					drawBoard(50, 24);

					//draw player 1 board blue

					changeCursorColour(BLUE);
					drawBoard(10, 1);
					drawBoard(10, 24);

					// Spawning in Carrier
					{
						//taken from notes and modified slightly
						changeCursorColour(RED);


						//define a cursor
						Cursor dude = Cursor(52, 26, 'X');

						//move cursor around to select the anchor point for rotation
						int character;
						while (true)
						{

							HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED);

							if (_kbhit())
							{
								character = _getch();
								switch (character)
								{
								case 80://down
									if (dude.m_Y + 2 <= 44)
									{
										dude.m_Y += 2;
									}
									break;

								case 72://up
									if (dude.m_Y - 2 >= 26)
									{
										dude.m_Y -= 2;
									}
									break;

								case 75://Left
									if (dude.m_X - 2 >= 52)
									{
										dude.m_X -= 2;
									}
									break;

								case 77://Right
									if (dude.m_X + 2 <= 70)
									{
										dude.m_X += 2;
									}
									break;
								case 13: //Enter
									break;
								}

								gotoXY(dude.m_X, dude.m_Y);
								cout << (char)dude.m_AsciiChar;

								//if the character moved, update its new location and clear its old location
								if ((dude.m_X != dude.m_PrevX) || (dude.m_Y != dude.m_PrevY))
								{
									gotoXY(dude.m_PrevX, dude.m_PrevY);
									cout << ' ';
									dude.m_PrevX = dude.m_X;
									dude.m_PrevY = dude.m_Y;
								}

								//if enter was pressed, begin placing boat from that anchor point
								if (character == 13)
								{
									COORD anchorPoint = { dude.m_X, dude.m_Y };
									Direction angle = NORTH;

									while (true)
									{

										gotoXY(50, 50);
										cout << "Use arrows to change direction, ENTER, press enter twice to select     ";

										changeCursorColour(GREEN);
										character = _getch();


										if (character == 80) //down
										{
											angle = SOUTH;
											Carrier testCarrier(anchorPoint.X, anchorPoint.Y, angle);
											testCarrier.m_drawBoat();
											_getch();
										}
										else if (character == 72) //up
										{
											angle = NORTH;
											Carrier testCarrier(anchorPoint.X, anchorPoint.Y, angle);
											testCarrier.m_drawBoat();
											_getch();
										}
										else if (character == 75) //left
										{
											angle = WEST;
											Carrier testCarrier(anchorPoint.X, anchorPoint.Y, angle);
											testCarrier.m_drawBoat();
											_getch();
										}
										else if (character == 77) //right
										{
											angle = EAST;
											Carrier testCarrier(anchorPoint.X, anchorPoint.Y, angle);
											testCarrier.m_drawBoat();
											_getch();

										}
										else if (character == 8) //backspace
										{
											break;
										}
										else if (character == 13) //enter
										{

											Carrier testCarrier(anchorPoint.X, anchorPoint.Y, angle);

											//set up flag for confiming if test is good
											bool isGoodFlag = true;

											for (int i = 0; i < testCarrier.m_getSize(); i++)
											{
												if (testCarrier.m_getPosition(i).m_getX() > 70 || testCarrier.m_getPosition(i).m_getX() < 52 || testCarrier.m_getPosition(i).m_getY() > 44 || testCarrier.m_getPosition(i).m_getY() < 26)
												{
													gotoXY(50, 50);
													cout << "Invalid location                                    ";
													isGoodFlag = false;
												}
											}

											if (isGoodFlag == true)
											{
												Boat* carrier = new Carrier(anchorPoint.X, anchorPoint.Y, angle);
												player2Boats.push_back(carrier);
												goto P2Battleship;
											}
										}

										//redraw board in case of broken tiles
										changeCursorColour(WHITE);
										drawBoard(50, 1);
										drawBoard(50, 24);

									}
								}
							}
						}
					}

				P2Battleship:

					// Spawning in Battleship
					{

						//taken from notes and modified slightly
						changeCursorColour(RED);


						//define a cursor
						Cursor dude = Cursor(52, 26, 'X');

						//move cursor around to select the anchor point for rotation
						int character;
						while (true)
						{

							for (int i = 0; i < player2Boats.size(); i++)
							{
								player2Boats[i]->m_drawBoat();
							}

							HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED);

							if (_kbhit())
							{
								character = _getch();
								switch (character)
								{
								case 80://down
									if (dude.m_Y + 2 <= 44)
									{
										dude.m_Y += 2;
									}
									break;

								case 72://up
									if (dude.m_Y - 2 >= 26)
									{
										dude.m_Y -= 2;
									}
									break;

								case 75://Left
									if (dude.m_X - 2 >= 52)
									{
										dude.m_X -= 2;
									}
									break;

								case 77://Right
									if (dude.m_X + 2 <= 70)
									{
										dude.m_X += 2;
									}
									break;
								case 13: //Enter
									break;
								}

								gotoXY(dude.m_X, dude.m_Y);
								cout << (char)dude.m_AsciiChar;

								//if the character moved, update its new location and clear its old location
								if ((dude.m_X != dude.m_PrevX) || (dude.m_Y != dude.m_PrevY))
								{
									gotoXY(dude.m_PrevX, dude.m_PrevY);
									cout << ' ';
									dude.m_PrevX = dude.m_X;
									dude.m_PrevY = dude.m_Y;
								}

								//if enter was pressed, begin placing boat from that anchor point
								if (character == 13)
								{
									COORD anchorPoint = { dude.m_X, dude.m_Y };
									Direction angle = NORTH;

									while (true)
									{

										gotoXY(50, 50);
										cout << "Use arrows to change direction, ENTER, press enter twice to select     ";

										changeCursorColour(GREEN);
										character = _getch();


										if (character == 80) //down
										{
											angle = SOUTH;
											Battleship testBattleship(anchorPoint.X, anchorPoint.Y, angle);
											testBattleship.m_drawBoat();
											_getch();
										}
										else if (character == 72) //up
										{
											angle = NORTH;
											Battleship testBattleship(anchorPoint.X, anchorPoint.Y, angle);
											testBattleship.m_drawBoat();
											_getch();
										}
										else if (character == 75) //left
										{
											angle = WEST;
											Battleship testBattleship(anchorPoint.X, anchorPoint.Y, angle);
											testBattleship.m_drawBoat();
											_getch();
										}
										else if (character == 77) //right
										{
											angle = EAST;
											Battleship testBattleship(anchorPoint.X, anchorPoint.Y, angle);
											testBattleship.m_drawBoat();
											_getch();

										}
										else if (character == 8) //backspace
										{
											break;
										}
										else if (character == 13) //enter
										{

											Battleship testBattleship(anchorPoint.X, anchorPoint.Y, angle);
											testBattleship.m_drawBoat();

											//set up flag for confiming if test is good
											bool isGoodFlag = true;

											for (int i = 0; i < testBattleship.m_getSize(); i++)
											{
												for (int j = 0; j < player2Boats.size(); j++)
												{
													if (testBattleship.m_isCollided(player2Boats[j]))
													{
														isGoodFlag = false;
													}
												}
												if (testBattleship.m_getPosition(i).m_getX() > 70 || testBattleship.m_getPosition(i).m_getX() < 52 || testBattleship.m_getPosition(i).m_getY() > 44 || testBattleship.m_getPosition(i).m_getY() < 26)
												{
													gotoXY(50, 50);
													cout << "Invalid location                                    ";
													isGoodFlag = false;
												}
											}

											if (isGoodFlag == true)
											{
												Boat* battleship = new Battleship(anchorPoint.X, anchorPoint.Y, angle);
												player2Boats.push_back(battleship);
												goto P2Cruiser;
												;
											}
										}

										//redraw board in case of broken tiles
										changeCursorColour(WHITE);
										drawBoard(50, 1);
										drawBoard(50, 24);


									}
								}
							}
						}
					}


				P2Cruiser:
					// Spawning in Cruiser
					{
						//taken from notes and modified slightly
						changeCursorColour(RED);


						//define a cursor
						Cursor dude = Cursor(52, 26, 'X');

						//move cursor around to select the anchor point for rotation
						int character;
						while (true)
						{
							for (int i = 0; i < player2Boats.size(); i++)
							{
								player2Boats[i]->m_drawBoat();
							}

							HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED);

							if (_kbhit())
							{
								character = _getch();
								switch (character)
								{
								case 80://down
									if (dude.m_Y + 2 <= 44)
									{
										dude.m_Y += 2;
									}
									break;

								case 72://up
									if (dude.m_Y - 2 >= 26)
									{
										dude.m_Y -= 2;
									}
									break;

								case 75://Left
									if (dude.m_X - 2 >= 52)
									{
										dude.m_X -= 2;
									}
									break;

								case 77://Right
									if (dude.m_X + 2 <= 70)
									{
										dude.m_X += 2;
									}
									break;
								case 13: //Enter
									break;
								}

								gotoXY(dude.m_X, dude.m_Y);
								cout << (char)dude.m_AsciiChar;

								//if the character moved, update its new location and clear its old location
								if ((dude.m_X != dude.m_PrevX) || (dude.m_Y != dude.m_PrevY))
								{
									gotoXY(dude.m_PrevX, dude.m_PrevY);
									cout << ' ';
									dude.m_PrevX = dude.m_X;
									dude.m_PrevY = dude.m_Y;
								}

								//if enter was pressed, begin placing boat from that anchor point
								if (character == 13)
								{
									COORD anchorPoint = { dude.m_X, dude.m_Y };
									Direction angle = NORTH;

									while (true)
									{

										gotoXY(50, 50);
										cout << "Use arrows to change direction, ENTER, press enter twice to select     ";

										changeCursorColour(GREEN);
										character = _getch();


										if (character == 80) //down
										{
											angle = SOUTH;
											Cruiser testCruiser(anchorPoint.X, anchorPoint.Y, angle);
											testCruiser.m_drawBoat();
											_getch();
										}
										else if (character == 72) //up
										{
											angle = NORTH;
											Cruiser testCruiser(anchorPoint.X, anchorPoint.Y, angle);
											testCruiser.m_drawBoat();
											_getch();
										}
										else if (character == 75) //left
										{
											angle = WEST;
											Cruiser testCruiser(anchorPoint.X, anchorPoint.Y, angle);
											testCruiser.m_drawBoat();
											_getch();
										}
										else if (character == 77) //right
										{
											angle = EAST;
											Cruiser testCruiser(anchorPoint.X, anchorPoint.Y, angle);
											testCruiser.m_drawBoat();
											_getch();

										}
										else if (character == 8) //backspace
										{
											break;
										}
										else if (character == 13) //enter
										{

											Cruiser testCruiser(anchorPoint.X, anchorPoint.Y, angle);
											testCruiser.m_drawBoat();

											//set up flag for confiming if test is good
											bool isGoodFlag = true;

											for (int i = 0; i < testCruiser.m_getSize(); i++)
											{
												for (int j = 0; j < player2Boats.size(); j++)
												{
													if (testCruiser.m_isCollided(player2Boats[j]))
													{
														isGoodFlag = false;
													}
												}
												if (testCruiser.m_getPosition(i).m_getX() > 70 || testCruiser.m_getPosition(i).m_getX() < 52 || testCruiser.m_getPosition(i).m_getY() > 44 || testCruiser.m_getPosition(i).m_getY() < 26)
												{
													gotoXY(50, 50);
													cout << "Invalid location                                    ";
													isGoodFlag = false;
												}
											}

											if (isGoodFlag == true)
											{
												Boat* cruiser = new Cruiser(anchorPoint.X, anchorPoint.Y, angle);
												player2Boats.push_back(cruiser);
												goto P2Submarine;
											}
										}

										//redraw board in case of broken tiles
										changeCursorColour(WHITE);
										drawBoard(50, 1);
										drawBoard(50, 24);
									}
								}
							}
						}
					}

				P2Submarine:
					// Spawning in Submarine
					{
						//taken from notes and modified slightly
						changeCursorColour(RED);


						//define a cursor
						Cursor dude = Cursor(52, 26, 'X');

						//move cursor around to select the anchor point for rotation
						int character;
						while (true)
						{
							for (int i = 0; i < player2Boats.size(); i++)
							{
								player2Boats[i]->m_drawBoat();
							}

							HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED);

							if (_kbhit())
							{
								character = _getch();
								switch (character)
								{
								case 80://down
									if (dude.m_Y + 2 <= 44)
									{
										dude.m_Y += 2;
									}
									break;

								case 72://up
									if (dude.m_Y - 2 >= 26)
									{
										dude.m_Y -= 2;
									}
									break;

								case 75://Left
									if (dude.m_X - 2 >= 52)
									{
										dude.m_X -= 2;
									}
									break;

								case 77://Right
									if (dude.m_X + 2 <= 70)
									{
										dude.m_X += 2;
									}
									break;
								case 13: //Enter
									break;
								}

								gotoXY(dude.m_X, dude.m_Y);
								cout << (char)dude.m_AsciiChar;

								//if the character moved, update its new location and clear its old location
								if ((dude.m_X != dude.m_PrevX) || (dude.m_Y != dude.m_PrevY))
								{
									gotoXY(dude.m_PrevX, dude.m_PrevY);
									cout << ' ';
									dude.m_PrevX = dude.m_X;
									dude.m_PrevY = dude.m_Y;
								}

								//if enter was pressed, begin placing boat from that anchor point
								if (character == 13)
								{
									COORD anchorPoint = { dude.m_X, dude.m_Y };
									Direction angle = NORTH;

									while (true)
									{

										gotoXY(50, 50);
										cout << "Use arrows to change direction, ENTER, press enter twice to select     ";

										changeCursorColour(GREEN);
										character = _getch();


										if (character == 80) //down
										{
											angle = SOUTH;
											Submarine testSubmarine(anchorPoint.X, anchorPoint.Y, angle);
											testSubmarine.m_drawBoat();
											_getch();
										}
										else if (character == 72) //up
										{
											angle = NORTH;
											Submarine testSubmarine(anchorPoint.X, anchorPoint.Y, angle);
											testSubmarine.m_drawBoat();
											_getch();
										}
										else if (character == 75) //left
										{
											angle = WEST;
											Submarine testSubmarine(anchorPoint.X, anchorPoint.Y, angle);
											testSubmarine.m_drawBoat();
											_getch();
										}
										else if (character == 77) //right
										{
											angle = EAST;
											Submarine testSubmarine(anchorPoint.X, anchorPoint.Y, angle);
											testSubmarine.m_drawBoat();
											_getch();

										}
										else if (character == 8) //backspace
										{
											break;
										}
										else if (character == 13) //enter
										{

											Submarine testSubmarine(anchorPoint.X, anchorPoint.Y, angle);
											testSubmarine.m_drawBoat();

											//set up flag for confiming if test is good
											bool isGoodFlag = true;

											for (int i = 0; i < testSubmarine.m_getSize(); i++)
											{
												for (int j = 0; j < player2Boats.size(); j++)
												{
													if (testSubmarine.m_isCollided(player2Boats[j]))
													{
														isGoodFlag = false;
													}
												}
												if (testSubmarine.m_getPosition(i).m_getX() > 70 || testSubmarine.m_getPosition(i).m_getX() < 52 || testSubmarine.m_getPosition(i).m_getY() > 44 || testSubmarine.m_getPosition(i).m_getY() < 26)
												{
													gotoXY(50, 50);
													cout << "Invalid location                                    ";
													isGoodFlag = false;
												}
											}

											if (isGoodFlag == true)
											{
												Boat* sub = new Submarine(anchorPoint.X, anchorPoint.Y, angle);
												player2Boats.push_back(sub);
												goto P2Destroyer;
											}
										}

										//redraw board in case of broken tiles
										changeCursorColour(WHITE);
										drawBoard(50, 1);
										drawBoard(50, 24);
									}
								}
							}
						}
					}

				P2Destroyer:
					// Spawning in Destroyer
					{
						//taken from notes and modified slightly
						changeCursorColour(RED);


						//define a cursor
						Cursor dude = Cursor(52, 26, 'X');

						//move cursor around to select the anchor point for rotation
						int character;
						while (true)
						{
							for (int i = 0; i < player2Boats.size(); i++)
							{
								player2Boats[i]->m_drawBoat();
							}

							HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED);

							if (_kbhit())
							{
								character = _getch();
								switch (character)
								{
								case 80://down
									if (dude.m_Y + 2 <= 44)
									{
										dude.m_Y += 2;
									}
									break;

								case 72://up
									if (dude.m_Y - 2 >= 26)
									{
										dude.m_Y -= 2;
									}
									break;

								case 75://Left
									if (dude.m_X - 2 >= 52)
									{
										dude.m_X -= 2;
									}
									break;

								case 77://Right
									if (dude.m_X + 2 <= 70)
									{
										dude.m_X += 2;
									}
									break;
								case 13: //Enter
									break;
								}

								gotoXY(dude.m_X, dude.m_Y);
								cout << (char)dude.m_AsciiChar;

								//if the character moved, update its new location and clear its old location
								if ((dude.m_X != dude.m_PrevX) || (dude.m_Y != dude.m_PrevY))
								{
									gotoXY(dude.m_PrevX, dude.m_PrevY);
									cout << ' ';
									dude.m_PrevX = dude.m_X;
									dude.m_PrevY = dude.m_Y;
								}

								//if enter was pressed, begin placing boat from that anchor point
								if (character == 13)
								{
									COORD anchorPoint = { dude.m_X, dude.m_Y };
									Direction angle = NORTH;

									while (true)
									{

										gotoXY(50, 50);
										cout << "Use arrows to change direction, ENTER, press enter twice to select     ";

										changeCursorColour(GREEN);
										character = _getch();


										if (character == 80) //down
										{
											angle = SOUTH;
											Destroyer testDestroyer(anchorPoint.X, anchorPoint.Y, angle);
											testDestroyer.m_drawBoat();
											_getch();
										}
										else if (character == 72) //up
										{
											angle = NORTH;
											Destroyer testDestroyer(anchorPoint.X, anchorPoint.Y, angle);
											testDestroyer.m_drawBoat();
											_getch();
										}
										else if (character == 75) //left
										{
											angle = WEST;
											Destroyer testDestroyer(anchorPoint.X, anchorPoint.Y, angle);
											testDestroyer.m_drawBoat();
											_getch();
										}
										else if (character == 77) //right
										{
											angle = EAST;
											Destroyer testDestroyer(anchorPoint.X, anchorPoint.Y, angle);
											testDestroyer.m_drawBoat();
											_getch();

										}
										else if (character == 8) //backspace
										{
											break;
										}
										else if (character == 13) //enter
										{

											Destroyer testDestroyer(anchorPoint.X, anchorPoint.Y, angle);
											testDestroyer.m_drawBoat();

											//set up flag for confiming if test is good
											bool isGoodFlag = true;

											for (int i = 0; i < testDestroyer.m_getSize(); i++)
											{
												for (int j = 0; j < player2Boats.size(); j++)
												{
													if (testDestroyer.m_isCollided(player2Boats[j]))
													{
														isGoodFlag = false;
													}
												}
												if (testDestroyer.m_getPosition(i).m_getX() > 70 || testDestroyer.m_getPosition(i).m_getX() < 52 || testDestroyer.m_getPosition(i).m_getY() > 44 || testDestroyer.m_getPosition(i).m_getY() < 26)
												{
													gotoXY(50, 50);
													cout << "Invalid location                                    ";
													isGoodFlag = false;
												}
											}

											if (isGoodFlag == true)
											{
												Boat* destroyer = new Destroyer(anchorPoint.X, anchorPoint.Y, angle);
												player2Boats.push_back(destroyer);
												goto EndPlayer2Spawn;
											}
										}

										//redraw board in case of broken tiles
										changeCursorColour(WHITE);
										drawBoard(50, 1);
										drawBoard(50, 24);
									}
								}
							}
						}
					}
				}

			EndPlayer2Spawn:

				system("cls");
				substate = Play;

			}

			//begin play
			while (substate == Play && gamestate == Multiplayer)
			{
				//setup two wincon flags, one for each player
				bool wincon1 = false;
				bool wincon2 = false;

				while (true)
				{
					//check if either player has won game, if so, run winning dialogue, and delete all 
					if (wincon1 || wincon2)
					{
						system("cls");
						gotoXY(5, 15);


						if (wincon1)
						{
							cout << "Player 1 wins!";
						}
						else if (wincon2)
						{
							cout << "Player 2 wins!";
						}

						//delete pointers to prevent memory leak
						for (int i = 0; i < player1Boats.size(); i++)
						{
							delete player1Boats[i];
						}
						for (int i = 0; i < player2Boats.size(); i++)
						{
							delete player2Boats[i];
						}

						gamestate = Menu;
						break;

					}
					else if (playerTurn == Player1)
					{

						//offset between player2board and player 1's screen
						int xOffset = -40;
						int yOffset = -23;

						//draw player 1 board
						changeCursorColour(WHITE);
						drawBoard(10, 1);
						drawBoard(10, 24);
						gotoXY(15, 48);
						cout << "Player 1 Board";

						//draw player 2 board
						changeCursorColour(BLUE);
						drawBoard(50, 1);
						drawBoard(50, 24);
						gotoXY(55, 48);
						cout << "Player 2 Board\n";

						

						//draw the player's field as of current hits
						for (int i = 0; i < player1Field.size(); i++)
						{
							for (int j = 0; j < player1Field[i].size(); j++)
								player1Field[i][j].m_drawPosition();
						}

						

						//draw the boats on top of that field
						for (int i = 0; i < player1Boats.size(); i++)
						{
							player1Boats[i]->m_drawBoat();
						}

						//draw the player's screen from the enemy's field
						for (int i = 0; i < player2Field.size(); i++)
						{
							for (int j = 0; j < player2Field[i].size(); j++)
								player2Field[i][j].m_drawPosition(xOffset, yOffset);
						}

						//draw the already hit positions on top of that screen
						for (int i = 0; i < player2Boats.size(); i++)
						{
							player2Boats[i]->m_drawEnemyBoatsHit(xOffset, yOffset);
						}
						

						//Here we do a trick, putting the cursor on the enemy player's field to simplify it for us,
						//but we are drawing it on the current player's screen using our offsets

						//define a cursor on the enemy player's field
						Cursor dude = Cursor(52, 26, 'O');

						//move cursor around to select target
						int character;
						while (true)
						{
							
							HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
							changeCursorColour(CYAN);
							
							if (_kbhit())
							{
								character = _getch();
								switch (character)
								{
								case 80://down
									if (dude.m_Y + 2 <= 44)
									{
										dude.m_Y += 2;
									}
									break;

								case 72://up
									if (dude.m_Y - 2 >= 26)
									{
										dude.m_Y -= 2;
									}
									break;

								case 75://Left
									if (dude.m_X - 2 >= 52)
									{
										dude.m_X -= 2;
									}
									break;

								case 77://Right
									if (dude.m_X + 2 <= 70)
									{
										dude.m_X += 2;
									}
									break;
								case 13: //Enter
									break;
								}

								

								//if the character moved, update its new location and clear its old location + clean up the screen
								if ((dude.m_X != dude.m_PrevX) || (dude.m_Y != dude.m_PrevY))
								{
									gotoXY(dude.m_PrevX + xOffset, dude.m_PrevY + yOffset);
									cout << ' ';
									dude.m_PrevX = dude.m_X;
									dude.m_PrevY = dude.m_Y;

									//draw the player's screen from the enemy's field
									for (int i = 0; i < player2Field.size(); i++)
									{
										for (int j = 0; j < player2Field[i].size(); j++)
											player2Field[i][j].m_drawPosition(xOffset, yOffset);
									}

									//draw the already hit positions on top of that screen
									for (int i = 0; i < player2Boats.size(); i++)
									{
										player2Boats[i]->m_drawEnemyBoatsHit(xOffset, yOffset);
									}

									changeCursorColour(CYAN);
									gotoXY(dude.m_X + xOffset, dude.m_Y + yOffset);
									cout << (char)dude.m_AsciiChar;
								}

								//if enter was pressed, check if point has already been hit
								if (character == 13)
								{
									bool breakFlag = false;
									Position* location = nullptr;

									for (int i = 0; i < player2Field.size(); i++)
									{
										//get out of loop if match already found/flag triggered
										if (breakFlag)
										{
											break;
										}
										//loop through field to find match to location
										for (int j = 0; j < player2Field[i].size(); j++)
										{
											if (player2Field[i][j] == dude)
											{
												if (!player2Field[i][j].m_isHit())
												{
													location = &player2Field[i][j];
												}
												breakFlag = true;
												break;
											}
										}
									}

									//if location already hit, go back into loop
									if (location == nullptr)
									{
										gotoXY(8, 50);
										cout << "location already hit";
										_getch();
										gotoXY(8, 50);
										cout << "                    ";
									}
									//else that position is selected and mark as hit on field
									else
									{
										location->m_setPositionHit();
										

										//begin checking to see if any boats hit
										breakFlag = false;
										for (int i = 0; i < player2Boats.size(); i++)
										{
											//get out of loop if match already found/flag triggered
											if (breakFlag)
											{
												break;
											}
											//loop through boats to find match to location
											for (int j = 0; j < player2Boats[i]->m_getSize(); j++)
											{
												//get out of loop if match already found/flag triggered
												if (breakFlag)
												{
													break;
												}

												//if a boat is hit, mark that spot on boat as hit
												if (*location == player2Boats[i]->m_getPosition(j))
												{
													player2Boats[i]->m_setSpotHit(j);
													breakFlag = true;

													//if boat was hit, check if boat is dead, if so, 
													//if so, make death call and check if wincon is set
													if (player2Boats[i]->m_isDead())
													{
														gotoXY(48, 50);
														player2Boats[i]->m_deathCall();
														_getch();
														gotoXY(48, 50);
														cout << "                                        ";

														int deathcount = 0;
														for (int k = 0; k < player2Boats.size(); k++)
														{
															if (player2Boats[k]->m_isDead())
															{
																deathcount++;
															}
														}
														if (deathcount == player2Boats.size())
														{
															wincon1 = true;
														}
													}
												}
											}
										}

										//clear screen and pass off to change turns
										_getch();
										playerTurn = Player2;
										system("cls");
										gotoXY(0, 0);
										changeCursorColour(WHITE);
										cout << "switch players then press any key";
										_getch();
										system("cls");
										break;
									}
								}
							}
						}
					}
					else if (playerTurn == Player2)
					{
						//offset between player2board and player 1's screen
						int xOffset = 40;
						int yOffset = -23;

						//draw player 1 board
						changeCursorColour(BLUE);
						drawBoard(10, 1);
						drawBoard(10, 24);
						gotoXY(15, 48);
						cout << "Player 1 Board";

						//draw player 2 board
						changeCursorColour(WHITE);
						drawBoard(50, 1);
						drawBoard(50, 24);
						gotoXY(55, 48);
						cout << "Player 2 Board\n";



						//draw the player's field as of current hits
						for (int i = 0; i < player2Field.size(); i++)
						{
							for (int j = 0; j < player2Field[i].size(); j++)
								player2Field[i][j].m_drawPosition();
						}



						//draw the boats on top of that field
						for (int i = 0; i < player2Boats.size(); i++)
						{
							player2Boats[i]->m_drawBoat();
						}

						//draw the player's screen from the enemy's field
						for (int i = 0; i < player1Field.size(); i++)
						{
							for (int j = 0; j < player1Field[i].size(); j++)
								player1Field[i][j].m_drawPosition(xOffset, yOffset);
						}

						//draw the already hit positions on top of that screen
						for (int i = 0; i < player1Boats.size(); i++)
						{
							player1Boats[i]->m_drawEnemyBoatsHit(xOffset, yOffset);
						}


						//Here we do a trick, putting the cursor on the enemy player's field to simplify it for us,
						//but we are drawing it on the current player's screen using our offsets

						//define a cursor on the enemy player's field
						Cursor dude = Cursor(12, 26, 'O');

						//move cursor around to select the target
						int character;
						while (true)
						{

							HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
							changeCursorColour(CYAN);

							if (_kbhit())
							{
								character = _getch();
								switch (character)
								{
								case 80://down
									if (dude.m_Y + 2 <= 44)
									{
										dude.m_Y += 2;
									}
									break;

								case 72://up
									if (dude.m_Y - 2 >= 26)
									{
										dude.m_Y -= 2;
									}
									break;

								case 75://Left
									if (dude.m_X - 2 >= 12)
									{
										dude.m_X -= 2;
									}
									break;

								case 77://Right
									if (dude.m_X + 2 <= 30)
									{
										dude.m_X += 2;
									}
									break;
								case 13: //Enter
									break;
								}



								//if the character moved, update its new location and clear its old location + clean up the screen
								if ((dude.m_X != dude.m_PrevX) || (dude.m_Y != dude.m_PrevY))
								{
									gotoXY(dude.m_PrevX + xOffset, dude.m_PrevY + yOffset);
									cout << ' ';
									dude.m_PrevX = dude.m_X;
									dude.m_PrevY = dude.m_Y;

									//draw the player's screen from the enemy's field
									for (int i = 0; i < player1Field.size(); i++)
									{
										for (int j = 0; j < player1Field[i].size(); j++)
											player1Field[i][j].m_drawPosition(xOffset, yOffset);
									}

									//draw the already hit positions on top of that screen
									for (int i = 0; i < player1Boats.size(); i++)
									{
										player1Boats[i]->m_drawEnemyBoatsHit(xOffset, yOffset);
									}

									changeCursorColour(CYAN);
									gotoXY(dude.m_X + xOffset, dude.m_Y + yOffset);
									cout << (char)dude.m_AsciiChar;
								}

								//if enter was pressed, check if point has already been hit
								if (character == 13)
								{
									bool breakFlag = false;
									Position* location = nullptr;

									for (int i = 0; i < player1Field.size(); i++)
									{
										//get out of loop if match already found/flag triggered
										if (breakFlag)
										{
											break;
										}
										//loop through field to find match to location
										for (int j = 0; j < player1Field[i].size(); j++)
										{
											if (player1Field[i][j] == dude)
											{
												if (!player1Field[i][j].m_isHit())
												{
													location = &player1Field[i][j];
												}
												breakFlag = true;
												break;

											}
										}
									}

									//if location already hit, go back into loop
									if (location == nullptr)
									{
										gotoXY(48, 50);
										cout << "location already hit";
										_getch();
										gotoXY(48, 50);
										cout << "                    ";
									}
									//else that position is selected and mark as hit on field
									else
									{
										location->m_setPositionHit();


										//begin checking to see if any boats hit
										breakFlag = false;
										for (int i = 0; i < player1Boats.size(); i++)
										{
											//get out of loop if match already found/flag triggered
											if (breakFlag)
											{
												break;
											}
											//loop through boats to find match to location
											for (int j = 0; j < player1Boats[i]->m_getSize(); j++)
											{
												//get out of loop if match already found/flag triggered
												if (breakFlag)
												{
													break;
												}

												//if a boat is hit, mark that spot on boat as hit
												if (*location == player1Boats[i]->m_getPosition(j))
												{
													player1Boats[i]->m_setSpotHit(j);
													breakFlag = true;

													//if boat was hit, check if boat is dead, if so, 
													//if so, make death call and check if wincon is set
													if (player1Boats[i]->m_isDead())
													{
														gotoXY(18, 50);
														player1Boats[i]->m_deathCall();
														_getch();
														gotoXY(18, 50);
														cout << "                                        ";

														int deathcount = 0;
														for (int k = 0; k < player1Boats.size(); k++)
														{
															if (player1Boats[k]->m_isDead())
															{
																deathcount++;
															}
														}
														if (deathcount == player1Boats.size())
														{
															wincon2 = true;
														}
													}
												}
											}
										}

										_getch();
										playerTurn = Player1;
										system("cls");
										gotoXY(0, 0);
										changeCursorColour(WHITE);
										cout << "switch players then press any key";
										_getch();
										system("cls");
										break;
									}
								}
							}
						}
					}
				}
			}
		}

		if (gamestate == Exit)
		{
			return 0;
		}

	}
}