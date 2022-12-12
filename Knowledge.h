/*******************************
Title: Player.h
Author: Andrew Lounsbury
Date: 5/9/2020
Purpose: Game theory program
********************************/

#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H
#include "MultivariatePolynomial.h"
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
		vector<vector<bool> > choiceKnowledge;
		vector<vector<bool> > numPlayersKnowledge;
		vector<vector<bool> > numStratsKnowledge;
		vector<vector<bool> > payoffKnowledge;
		vector<vector<bool> > preferenceKnowledge;
		vector<vector<bool> > rationalityKnowledge;
		
	public:
		Knowledge(int numPlayers)
		{
			choiceKnowledge = vector<vector<bool> >(numPlayers);
			numPlayersKnowledge = vector<vector<bool> >(numPlayers);
			numStratsKnowledge = vector<vector<bool> >(numPlayers);
			payoffKnowledge = vector<vector<bool> >(numPlayers);
			preferenceKnowledge = vector<vector<bool> >(numPlayers);
			rationalityKnowledge = vector<vector<bool> >(numPlayers);
			
			for (int x = 0; x < numPlayers; x++)
			{
				choiceKnowledge.at(x).resize(numPlayers);
				numPlayersKnowledge.at(x).resize(numPlayers);
				numStratsKnowledge.at(x).resize(numPlayers);
				payoffKnowledge.at(x).resize(numPlayers);
				preferenceKnowledge.at(x).resize(numPlayers);
				rationalityKnowledge.at(x).resize(numPlayers);
				for (int y = 0; y < numPlayers; y++)
				{
					numPlayersKnowledge.at(x).at(y) = true;
					numStratsKnowledge.at(x).at(y) = true;
					payoffKnowledge.at(x).at(y) = true;
					if (x == y) // player knows that P_x knows P_x's information
					{
						choiceKnowledge.at(x).at(y) = true;
						preferenceKnowledge.at(x).at(y) = true;
						rationalityKnowledge.at(x).at(y) = true;
					}
					else
					{
						choiceKnowledge.at(x).at(y) = false;
						preferenceKnowledge.at(x).at(y) = false;
						rationalityKnowledge.at(x).at(y) = false;
					}
				}
			}
		}
		
		~Knowledge(){}
		
		bool getchoiceKnowledge(int x, int y) 					{ return choiceKnowledge.at(x).at(y); }
		bool getpayoffKnowledge(int x, int y) 					{ return payoffKnowledge.at(x).at(y); }
		bool getnumPlayersKnowledge(int x, int y) 				{ return numPlayersKnowledge.at(x).at(y); }
		bool getnumStratsKnowledge(int x, int y) 				{ return numStratsKnowledge.at(x).at(y); }
		bool getrationalityKnowledge(int x, int y) 				{ return rationalityKnowledge.at(x).at(y); }
		bool getpreferenceKnowledge(int x, int y) 				{ return preferenceKnowledge.at(x).at(y); }
		void setchoiceKnowledge(int x, int y, bool val) 		{ choiceKnowledge.at(x).at(y) = val; }
		void setpayoffKnowledge(int x, int y, bool val) 		{ payoffKnowledge.at(x).at(y) = val; }
		void setnumPlayersKnowledge(int x, int y, bool val) 	{ numPlayersKnowledge.at(x).at(y) = val; }
		void setnumStratsKnowledge(int x, int y, bool val) 		{ numStratsKnowledge.at(x).at(y) = val; }
		void setrationalityKnowledge(int x, int y, bool val) 	{ rationalityKnowledge.at(x).at(y) = val; }
		void setpreferenceKnowledge(int x, int y, bool val) 	{ preferenceKnowledge.at(x).at(y) = val; }
};

#endif