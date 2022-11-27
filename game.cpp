/*******************************
Title: game.cpp
Author: Andrew Lounsbury
Date: 5/9/2020
Purpose: Game theory program
********************************/
#include "simGame.h"
#include "seqGame.h"

int main()
{
	int menu = -1, numPlayers = 2, oList = 1;
	int type = -1;
	char impartial = '\n', load = '\n', save = '\n', startRand = '\n';
	
	// cout << "Is the game simultaneous(1) or sequential(2)? Enter 1 or 2:  ";
	// cin >> type;
	// validate(type, 1, 2);
	type = 1;
	
	// cout << "Enter the number of players in the game.  ";
	// cin >> numPlayers;
	// validate(numPlayers, 2, 6);
	
	if (type == 1)
	{
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
		// game->computeNumOutcomes();
		
		while (menu != 20)
		{
			oList = 1;
			cout << "\n------------------------------------\n";
			cout << "What would you like to do?\n";
			cout << "PRINT:\n";
			cout << " " << oList << ". payoffs and best responses";
			cout << setw(10) << oList + 10 << ". remove inferior strategies\n";
			oList++;
			
			cout << " " << oList << ". payoffs";
			cout << setw(29) << oList + 10 << ". Generate random game\n";
			oList++;
			
			cout << " " << oList << ". best responses";
			cout << setw(22) << oList + 10 << ". Add communication\n";
			oList++; // 10 ^
			
			cout << " " << oList << ". both separately";
			cout << setw(21) << oList + 10 << ". Load game from file\n";
			oList++;			
			
			cout << " " << oList << ". pure equilibria";
			cout << setw(21) << oList + 10 << ". Save game to file\n";
			oList++;		
			
			cout << " " << oList << ". expected utilities";
			cout << setw(18) << oList + 10 << ". Save game as LaTeX\n";
			oList++;
			
			cout << " " << oList << ". k-rationalizability model";
			cout << setw(11) << oList + 10 << ". End program\n";
			oList++;
			
			cout << " " << oList << ". A specific player's information\n";
			oList++;
			cout << " " << oList << ". All players' information\n";
			oList++;
			cout << " " << oList << ". Combinations\n";
			oList++;
			oList += 8;
			cout << "- - - - - - - - - - - - - - - - - -\n";
			
			// cout << oList << ". Bayesian model\n";
			// oList++;
			
			cout << "DEPRECIATED:\n";
			cout << oList << ". Set all players' rationalities\n";
			oList++;
			cout << oList << ". Add player\n";
			oList++;
			cout << oList << ". Edit player\n";
			// cout << oList << ". Remove player\n";
			// oList++;
			cout << "- - - - - - - - - - - - - - - - - -\n";
			cout << "Enter an integer from 1 to " << oList << ":  ";
			cin >> menu;
			if (menu == 16)
				menu += 3;
			else if (menu == 19)
				menu -= 3;
			validate(menu, 1, oList);			
			
			switch(menu)
			{	
				case 1: game->printPayoffMatrix();
						break;
				case 2: game->printPayoffs();
						break;
				case 3: game->printBestResponses();
						break;
				case 4: game->printBothSeparately();
						break;
				case 5: game->printPureEquilibria();
						break;
				case 6: game->computeMixedStrategies();
						break;
				case 7: game->printKMatrix();
						break;
				case 8: game->printPlayer();
						break;
				case 9: game->printPlayers();
						break;
				case 10: game->computeMixedEquilibria();
						break;
				case 11: game->reduce();
						break;
				case 12: game->randGame();
						break;
				case 13: game->communication();
						break;
				case 14: game->readFromFile();
						break;
				case 15: game->saveToFile();
						break;				
				case 16: game->savePayoffMatrixAsLatex();
						break;
				case 17: game->editPlayer();
						break;
				case 18: game->setAllRationalities();
						break;
				case 19: game->addPlayer();
						break;
				case 20: cout << "Save game before ending? (Enter y or n):  ";
						cin >> save;
						validateChar(save);
						if (save == 'y')
							game->saveToFile();
						break;
			}
		}
	}
	else
	{
		SeqGame* game = new SeqGame(2);
		/*
					r
				0		1
			0	1
		*/
		
		vector<int> rootPath{-1};
		vector<int> path1{-1, 0};
		vector<int> path2{-1, 1};
		vector<int> path3{-1, 0, 0};
		vector<int> path4{-1, 0, 1};
		
		game->insert(game->getRoot(), rootPath);
		game->insert(game->getRoot(), path1);
		game->insert(game->getRoot(), path2);
		// game->insert(game->getRoot(), path3);
		// game->insert(game->getRoot(), path4);
		
		game->display(game->getRoot(), 0);
		
		// game->displayPreOrder(game->getRoot());
		
	}
	return 0;
}