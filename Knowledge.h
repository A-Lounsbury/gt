/*******************************
Title: Player.h
Author: Andrew Lounsbury
Date: 5/9/2020
Purpose: Game theory program
********************************/

#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H
#include "Polynomial.h"
#include <iostream>
#include <iomanip>
#include <iterator>
#include <fstream>
#include <limits>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Knowledge
{
	private:
		int player;
		vector<vector<bool> > knowsChoices;
		vector<vector<bool> > knowsNumPlayers;
		vector<vector<bool> > knowsNumStrats;
		vector<vector<bool> > knowsPayoffs;
		vector<vector<bool> > knowsPreferences;
		vector<vector<bool> > knowsRationalities;
		
		////////////////////////////////////////////////////////////
		// vector of levels, players
		// i is common knowledge if all know that all others know i
		// (forall x)[P_x |= (forall y)[P_y |= i]]
		// knowsChoices.at(x).at(y)
		//		==> P_x |= P_y |= c_z
	// 	 Similarly, P_x |= P_y |= pa_z
	// 	 			P_x |= P_y |= ns_z
	// 	 			P_x |= P_y |= r_z
	// 	 			P_x |= P_y |= pr_z
	
	// 	P_x |= i implies P_x |= P_x |= i
		////////////////////////////////////////////////////////////
	public:
		Knowledge(int numPlayers)
		{
			knowsChoices = vector<vector<bool> >(numPlayers);
			knowsNumPlayers = vector<vector<bool> >(numPlayers);
			knowsNumStrats = vector<vector<bool> >(numPlayers);
			knowsPayoffs = vector<vector<bool> >(numPlayers);
			knowsPreferences = vector<vector<bool> >(numPlayers);
			knowsRationalities = vector<vector<bool> >(numPlayers);
			
			for (int x = 0; x < numPlayers; x++)
			{
				knowsChoices.at(x).resize(numPlayers);
				knowsNumPlayers.at(x).resize(numPlayers);
				knowsNumStrats.at(x).resize(numPlayers);
				knowsPayoffs.at(x).resize(numPlayers);
				knowsPreferences.at(x).resize(numPlayers);
				knowsRationalities.at(x).resize(numPlayers);
				for (int y = 0; y < numPlayers; y++)
				{
					knowsNumPlayers.at(x).at(y) = true;
					knowsNumStrats.at(x).at(y) = true;
					knowsPayoffs.at(x).at(y) = true;
					if (x == y) // player knows that P_x knows P_x's information
					{
						knowsChoices.at(x).at(y) = true;
						knowsPreferences.at(x).at(y) = true;
						knowsRationalities.at(x).at(y) = true;
					}
					else
					{
						knowsChoices.at(x).at(y) = false;
						knowsPreferences.at(x).at(y) = false;
						knowsRationalities.at(x).at(y) = false;
					}
				}
			}
		}
		
		~Knowledge(){}
		
		bool getKnowsChoices(int x, int y) 					{ return knowsChoices.at(x).at(y); }
		bool getKnowsPayoffs(int x, int y) 					{ return knowsPayoffs.at(x).at(y); }
		bool getKnowsNumPlayers(int x, int y) 				{ return knowsNumPlayers.at(x).at(y); }
		bool getKnowsNumStrats(int x, int y) 				{ return knowsNumStrats.at(x).at(y); }
		bool getKnowsRationalities(int x, int y) 			{ return knowsRationalities.at(x).at(y); }
		bool getKnowsPreferences(int x, int y) 				{ return knowsPreferences.at(x).at(y); }
		void setKnowsChoices(int x, int y, bool val) 		{ knowsChoices.at(x).at(y) = val; }
		void setKnowsPayoffs(int x, int y, bool val) 		{ knowsPayoffs.at(x).at(y) = val; }
		void setKnowsNumPlayers(int x, int y, bool val) 	{ knowsNumPlayers.at(x).at(y) = val; }
		void setKnowsNumStrats(int x, int y, bool val) 		{ knowsNumStrats.at(x).at(y) = val; }
		void setKnowsRationalities(int x, int y, bool val) 	{ knowsRationalities.at(x).at(y) = val; }
		void setKnowsPreferences(int x, int y, bool val) 	{ knowsPreferences.at(x).at(y) = val; }
};

#endif