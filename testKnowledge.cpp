/*******************************
Title: test2.cpp
Author: Andrew Lounsbury
Date: 12/19/2020
Purpose: test knowledge class
********************************/

#include "simGame.h"
using namespace std;

int main()
{
	int menu = -1, numPlayers = 2, oList = 1;
	char impartial = '\n', load = '\n', startRand = '\n';
	
	simGame<int>* game = new simGame<int>(numPlayers);

	cout << "Load game from file? Enter y or n:  ";
	cin >> load;
	validateChar(load);
	if (load == 'y')
		game->readFromFile();
	else
	{
		cout << "Start with a random game? Enter y or n:  ";
		cin >> startRand;
		validateChar(startRand);
		if (startRand == 'y')
			game->randGame();
		else
		{
			cout << "Is the game impartial? Enter y or n:  ";
			cin >> impartial;
			validateChar(impartial);
			game->setAllNumStrats(impartial);
			game->printPayoffMatrix();
		}
	}
	
	while (menu != 3)
	{
		oList = 1;
		cout << "\n------------------------------------\n";
		cout << "What would you like to do?\n";
		cout << "PRINT:\n";
		cout << " 1. print knowledge\n";
		oList++;
		cout << " 2. Load\n";
		oList++;
		cout << " 3. End\n";
		oList++;
		cout << "\nEnter an integer from 1 to 3:  ";
		cin >> menu;
		validate(menu, 1, 3);
		
		switch(menu)
		{	
			case 1:	
					for (int x = 0; x < numPlayers; x++)
					{
						for (int y = 0; y < numPlayers; y++)
						{
							for (int z = 0; z < numPlayers; z++)
							{
								if (y != z)
								{
									cout << "(" << x << ", " << y << ", " << z << ")\n";
									
									// removes the need for a vector holding each x value, the vector players will do this
									// makes more sense for knowledge to be an aspect of each player, rather than the game itself
									// players.at(x)->getKnowledge()->getKnowsChoices(y, z)
									
									if (game->getPlayer(x)->getKnowledge()->getKnowsChoices(y, z))
										cout << "    1\n";
									else
										cout << "not 1\n";
									if (game->getPlayer(x)->getKnowledge()->getKnowsNumPlayers(y, z))
										cout << "    2\n";
									else
										cout << "not 2\n";
									if (game->getPlayer(x)->getKnowledge()->getKnowsNumStrats(y, z))
										cout << "    3\n";
									else
										cout << "not 3\n";
									if (game->getPlayer(x)->getKnowledge()->getKnowsPayoffs(y, z))
										cout << "    4\n";
									else
										cout << "not 4\n";
									if (game->getPlayer(x)->getKnowledge()->getKnowsPreferences(y, z))
										cout << "    5\n";
									else
										cout << "not 5\n";
									if (game->getPlayer(x)->getKnowledge()->getKnowsRationalities(y, z))
										cout << "    6\n";
									else
										cout << "not 6\n";
								}
							}
						}
					}
					if (game->commonKnowledge())
						cout << "yep\n";
					else
						cout << "nope\n";
					
					break;
			case 2: game->readFromFile();

			default: break;
		}
	}

	return 0;
}