/*********************************************
Title: bayesianGame.h
Author: Andrew Lounsbury
Date: 5/9/2020
Purpose: class for bayesian analysis of games
*********************************************/

#ifndef BAYESIANGAME_H
#define BAYESIANGAME_H
#include "simGame.h"
#include "listNode.h"

class bayesianGame
{
	private:
		simGame<int>* game1;
		simGame<int>* game2;
		double prob1 = -1.0, prob2 = -1.0;
		simGame<Polynomial*>* expectedGame;
	public:
		simGame<int>* getGame1()
		{ return game1; }
		
		simGame<int>* getGame2()
		{ return game2; }
		
		simGame<Polynomial*>* getExpectedGame()
		{ return expectedGame; }
		
		void setGame1(simGame<int>* g)
		{ game1 = g; }
		
		void setGame2(simGame<int>* g)
		{ game2 = g; }
		
		void setExpectedGame(simGame<Polynomial*>* m)
		{ expectedGame = m; }
		
		bayesianGame(simGame<int>* &);
		void computeBestResponses();
};

bayesianGame::bayesianGame(simGame<int>* &game)
{
	char choice = '\n', impartial = '\n', load = '\n', p1Knows = '\n', p2Knows = '\n', save = '\n';
	simGame<int>* g1;
	
	// USE CURRENT GAME?	
	cout << "Game 1:\n";
	cout << "------------------------------------------------------------\n";
	cout << "Would you like the current game to be one of the possible games in the Bayesian game?  ";
	cin >> choice;
	validateChar(choice);
	
	if (choice == 'n')
	{
		cout << "test1\n";
		
		g1 = new simGame<int>(game->getNumPlayers());
		
		cout << "Would you like to load a game from a file? Enter y or n.  ";
		cin >> load;
		validateChar(load);
		if (load == 'y')
			g1->readFromFile();
		else
		{
			cout << "Is the game impartial? Enter y or n.  ";
			cin >> impartial;
			validateChar(impartial);
			g1->setAllNumStrats(impartial);
			
			for (int x = 0; x < g1->getNumPlayers(); x++)
				g1->changePayoffs(x);
		}
		g1->computeNumPayoffs();
	}
	else
	{
		cout << "Would you like to save your game beforehand? Enter y or n.  ";
		cin >> save;
		validateChar(save);
		
		if (save == 'y')
			game->saveToFile();
		
		g1 = game;
	}
	
	// GAME 2
	simGame<int>* g2 = new simGame<int>(game1->getNumPlayers());	
	cout << "\nGame 2:\n";
	cout << "------------------------------------------------------------\n";
	cout << "Would you like to load a game from a file? Enter y or n.  ";
	cin >> load;
	validateChar(load);
	if (load == 'y')
		g2->readFromFile();
	else
	{
		cout << "Is the game impartial? Enter y or n.  ";
		cin >> impartial;
		validateChar(impartial);
		g2->setAllNumStrats(impartial);
		
		for (int x = 0; x < g1->getNumPlayers(); x++)
			g2->changePayoffs(x);
	}
	g2->computeNumPayoffs();
	
	while (p1Knows != 'y' && p2Knows != 'y')
	{
		cout << "Does player 1 know which game is real? Enter y or n.  ";
		cin >> p1Knows;
		validateChar(p1Knows);
		cout << "Does player 2 know which game is real? Enter y or n.  ";
		cin >> p2Knows;
		validateChar(p2Knows);
	}
	
	if (p1Knows == 'y' && p2Knows == 'n')
	{
		expectedGame = new simGame<Polynomial*>(game1->getNumPlayers());
		expectedGame->getPayoffMatrix().resize(2 * game->getPlayer(0)->getNumStrats());
		for(int i = 0; i < 2; i++) // each row
		{
			expectedGame->getPayoffMatrix().at(i).resize(game->getPlayer(1)->getNumStrats());
			for(int j = 0; j < game->getPlayer(1)->getNumStrats(); j++) // each column in row i
			{
				ListNode<Polynomial*>* head = new ListNode<Polynomial*>; // create first node
				ListNode<Polynomial*>* tail = new ListNode<Polynomial*>; // create second node
				head->value = 0;
				head->bestResponse = false;
				head->next = tail; // first node initialized
				tail->value = 0;
				tail->bestResponse = false;
				tail->next = NULL; // second node initialized
				expectedGame->getPayoffMatrix()[i][j] = head; // head is he first node of the list in payoffMatrix[i][j]
			}
		}
		computeBestResponses();
	}
	else if (p1Knows == 'n' && p2Knows == 'y')
	{
		
	}
	if (p1Knows == 'y' && p2Knows == 'y')
	{
		
	}
}

void bayesianGame::computeBestResponses()
{
	Polynomial* maxValue = new Polynomial;
	
	for (int j = 0; j < players.at(1)->getNumStrats(); j++) // j-th column
	{
		maxValue = 0;
		// find maxValue for each row in j-th column
		for (int i = 0; i < players.at(0)->getNumStrats(); i++)
		{
			if (expectedGame.at(0).at(i).at(j)->value > maxValue)
				maxValue = expectedGame.at(0).at(i).at(j)->value;
		}
		// check each row in j-th column
		for (int i = 0; i < players.at(0)->getNumStrats(); i++)
		{
			if (expectedGame.at(0).at(i).at(j)->value == maxValue) // don't need >= bc it's the max
				expectedGame.at(0).at(i).at(j)->bestResponse = true;
			else
				expectedGame.at(0).at(i).at(j)->bestResponse = false;
		}
	}
	for (int i = 0; i < players.at(0)->getNumStrats(); i++) // i-th row
	{
		maxValue = 0;
		// find maxValue for each column in i-th row
		for (int j = 0; j < players.at(1)->getNumStrats(); j++)
		{
			if (expectedGame.at(0).at(i).at(j)->next->value > maxValue)
				maxValue = expectedGame.at(0).at(i).at(j)->next->value;
		}
		// check each column in i-th row
		for (int j = 0; j < players.at(1)->getNumStrats(); j++)
		{
			if (expectedGame.at(0).at(i).at(j)->next->value == maxValue) // don't need >= bc it's the max
				expectedGame.at(0).at(i).at(j)->next->bestResponse = true;
			else
				expectedGame.at(0).at(i).at(j)->next->bestResponse = false;
		}
	}
}

#endif