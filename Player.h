/*******************************
Title: Player.h
Author: Andrew Lounsbury
Date: 5/9/2020
Purpose: Game theory program
********************************/

#ifndef PLAYER_H
#define PLAYER_H
#include "MultivariatePolynomial.h"
#include "Knowledge.h"
#include <iostream>
#include <iomanip>
#include <iterator>
#include <fstream>
#include <limits>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// player class for simGame.h
class Player
{
	private:
		int choice;
		int kChoice; // kChoices give the outcome in k-rationalizability model
		int numStrats;
		int rationality;
		Knowledge* knowledge;
		MultivariatePolynomial* preference;
		
		~Player() 							{ delete preference; }
		int getKChoice() const 				{ return kChoice; }
		void printPlayer() const 			{ cout << this; }
		MultivariatePolynomial* getPreference() const 	{ return preference; }
		void setPreference(MultivariatePolynomial* p) 	{ preference = p; }
		
		friend ostream& operator << (ostream& os, const Player& p)
		{
			os << "\n" << "Number of Strategies:  " << right << setw(9) << p.numStrats;
			os << "\n" << "Rationality:  " << right << setw(18) << p.rationality;
			os << "\n" << "Choice:  " << right << setw(22) << "s_" << p.choice + 1;
			os << "\n" << "k-rationalizability Choice:  s_" << p.kChoice + 1;
			os << "\n" << "Preference:  " << right << setw(17);
			p.preference->printMultivariatePolynomial();
			cout << endl;
			return os;
		}
	public:
		Player(int numPlayers, int x)
		{
			rationality = 0;
			numStrats = 2;
			choice = -1;
			kChoice = -1;
			knowledge = new Knowledge(numPlayers);
			// -1, numVariables, var // nT = -1 or var (x) = -1 is default
			preference = new MultivariatePolynomial(-1, numPlayers, x);
		}
		
		Player(int r, int n, char s, MultivariatePolynomial* p)
		{
			rationality = r;
			numStrats = n;
			choice = s;
			preference = p;
		}
		
		int getChoice() const		{ return choice; }
		Knowledge* getKnowledge()	{ return knowledge; }
		int getNumStrats() const	{ return numStrats; }
		int getRationality() const	{ return rationality; }
		void setChoice(int c)		{ choice = c; }
		void setKChoice(int c)		{ kChoice = c; }
		void setNumStrats(int n)	{ numStrats = n; }
		void setRationality(int r)	{ rationality = r; }
};

#endif