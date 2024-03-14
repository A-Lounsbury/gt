/************************************************
Title: simGame_obsoletions_removed.h
Author: Andrew Lounsbury
Date: 3/13/2024
Purpose: class for simultaneous aspects of games
*************************************************/

#ifndef SIMGAME_H
#define SIMGAME_H
#include "Player.h"
#include "LinkedList.h"

// "Simultaneous Game" a vector of matrices (vectors of vectors) of linked lists and relevant data
template <typename T>
class simGame
{
	private:
		int numPlayers;
		vector<Player*> players;
		int numOutcomes;
		vector<vector<vector<LinkedList<T>*> > > payoffMatrix;
		
		// k-rationalizability 
		vector<vector<vector<vector<int> > > > kMatrix;
		vector<double> rationalityProbabilities = vector<double>(4); // probability a player is L_i, i = 0,...3
		vector<double> outcomeProbabilities; // probability of each outcome in kMatrix stored in kOutcomes; P(s_i, s_j)
		vector<vector<int> > kOutcomes; // n-tuples that appear in kMatrix; won't be all of them
		vector<vector<int> > kStrategies = vector<vector<int> >(4); // 2D matrix containing the strategies each player would play for k-levels 0,...,3
		
		vector<vector<int> > mixedEquilibria; // probabilities each player will play each strategy
		vector<vector<int> > paretoPureEquilibria;
		vector<vector<int> > pureEquilibria; // contains strategy profiles of numPlayers length
		int maxR;
		bool impartial;
		bool mixed;
		
		vector<vector<int> > maxBestResponseLengths();
		vector<vector<int> > maxPayoffLengths();
		// vector<vector<int> > maxEntryLengths(vector<vector<vector<bool> > >);
		int entryBestResponseLengths(int, int, int);
		int entryPayoffLengths(int, int, int);
		int entryLength(vector<vector<vector<bool> > >, int, int, int);
		void clearPureEquilibria() { pureEquilibria.clear(); }
		void clearParetoPureEquilibria() { paretoPureEquilibria.clear(); }
		void pushKOutcomeProbabilities() { outcomeProbabilities.push_back(0.0); }
		
		bool getImpartial() 										{ return impartial; }
		vector<int> getKOutcome(int i) 								{ return kOutcomes.at(i); }
		vector<int> getKStrategy(int i) 							{ return kStrategies.at(i); }
		int getMaxRationality() 									{ return maxR; }
		int getNumOutcomes() const 									{ return numOutcomes; }
		int getNumPlayers() const 									{ return numPlayers; }
		double getOutcomeProbability(int i) 						{ return outcomeProbabilities.at(i); }
		vector<int> getParetoEquilibrium(int i) 					{ return paretoPureEquilibria.at(i); }
		vector<vector<int> > getParetoPureEquilibria() 				{ return paretoPureEquilibria; }
		vector<vector<vector<LinkedList<T>*> > > getPayoffMatrix()	{ return payoffMatrix; }
		vector<vector<int> > getPureEquilibria() 					{ return pureEquilibria; }
		vector<int> getPureEquilibrium(int i)						{ return pureEquilibria.at(i); }
		double getRationalityProbability(double i)					{ return rationalityProbabilities.at(i); }
		
		int getSizeKOutcomes() 										{ return kOutcomes.size(); }
		int getSizeKOutcomeProbabilities() 							{ return outcomeProbabilities.size(); }
		int getSizeParetoPureEquilibria() 							{ return paretoPureEquilibria.size(); }
		int getSizePureEquilibria() 								{ return pureEquilibria.size(); }
		void pushKOutcome(vector<int> temp) 						{ kOutcomes.push_back(temp); }
		void pushEquilibrium(vector<int> temp) 						{ pureEquilibria.push_back(temp); }
		void pushParetoEquilibrium(vector<int> temp) 				{ paretoPureEquilibria.push_back(temp); }
		void setImpatial(bool val) 									{ impartial = val; }
		void setMaxRationality(int m) 								{ maxR = m; }
		void setNumOutcomes(int num) 								{ numOutcomes = num; }
		void setNumPlayers(int n) 									{ numPlayers = n; }
		void setOutcomeProbability(int i, double num) 				{ outcomeProbabilities.at(i) = num; }
		void setRationalityProbability(int i, double num) 			{ rationalityProbabilities.at(i) = num; }
		
		void addStrategy(int);
		bool allEqualEquilibria();
		bool bosCondition(vector<int>, vector<int>);
		void changeAPayoff(int);
		void changePayoffs(int);
		bool checkBOSConditions();		
		bool checkChickenConditions();
		bool checkIHConditions();	
		bool checkNullCondition();
		bool checkPDConditions();
		bool checkSHConditions();
		bool checkZSConditions();
		bool chickenCondition(vector<int>, vector<int>);
		void computeBestResponses();
		void computeChoices();
		vector<vector<Polynomial*> > computeExpectedUtilities();
		void computeImpartiality();
		void computeKStrategies();
		void computeNumOutcomes();
		void computePureEquilibria();
		bool coordination();
		void determineType();
		vector<int> enterStratProfile();
		bool equalEquilibria(int, int);
		vector<vector<vector<bool> > > extraSpacesInColumns();
		int hash(vector<int>);
		bool isInferior();
		void isMixed();
		bool isPureEquilibrium(vector<int>);
		bool isStrictlyDominant(int, int);
		bool isStrictlyDominated(int, int);
		bool isWeaklyDominant(int, int);
		bool isWeaklyDominated(int, int);
		int maxPayoffInRowColOrMatrices(int, vector<int>);
		int maxStratInRowColOrMatrices(int, vector<int>);
		int maxStrat(int);
		void printKOutcomes();
		void printKOutcomeProbabilities();
		void printKProbabilities();
		void printKStrategies();
		void printPayoffMatrixSansInfo();
		void properDominantStrategies();
		bool PO(vector<int>);
		void randType();
		// void removePlayer();
		void removeStrategy(int, int);
		void removeStrategyPrompt(int);
		int rHash(vector<int>);
		vector<int> rUnhash(int matrixIndex);
		void saveKMatrixAsLatex(vector<int>, vector<double>);
		bool shCondition(vector<int>, vector<int>);
		double solve(Polynomial*, Polynomial*);
		vector<int> unhash(int);
	public:
		Player* getPlayer(int i) const { return players.at(i); }
	
		simGame(int);
		~simGame();
		void addPlayer();
		bool commonKnowledge() const;
		void communication();
		void computeMixedEquilibria();
		void computeMixedStrategies();
		void editPlayer();		
		void printBestResponses();
		void printBothSeparately();
		void printKMatrix();
		void printPayoffMatrix();
		void printPayoffs();
		void printPlayer() const;
		void printPlayers() const;
		void printPureEquilibria();
		void randGame();
		void readFromFile();
		void reduce();
		void savePayoffMatrixAsLatex();
		void saveToFile();
		void setAllNumStrats(char);
		void setAllRationalities();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// constructor
template <typename T>
simGame<T>::simGame(int nP)
{
	numPlayers = nP;
	
	// Initializing players
	for(int x = 0; x < numPlayers; x++)
	{
		// x + 1 is the variable
		Player* p = new Player(numPlayers, x); // with preference of variable p_x
		players.push_back(p);
	}
	
	numOutcomes = 4;
	mixed = true;
	
	// Creating kStrategies' 4 arrays of vectors of size numPlayers and setting rationalityProbabilities
	for (int r = 0; r < 4; r++)
	{
		kStrategies.at(r).resize(numPlayers);
		setRationalityProbability(r, 0.0);
	}
	
	// maximum rationality is 3, meaning there are 4 rationality levels
	int size = 1;
	if (numPlayers > 2)
		size = pow(4, numPlayers);
	
	kMatrix.resize(size);
	
	for (int m = 0; (unsigned)m < kMatrix.size(); m++)
	{
		kMatrix.at(m).resize(4);
		for(int i = 0; i < 4; i++)
		{
			kMatrix.at(m).at(i).resize(4);
			for(int j = 0; j < 4; j++)
			{
				vector<int> vect(numPlayers, -1);
				kMatrix.at(m).at(i).at(j) = vect;
			}
		}
	}
	
	// creating pureEquilibria
	for (int i = 0; (unsigned)i < pureEquilibria.size(); i++)
		pureEquilibria.at(i).resize(numPlayers);

	// creating paretoPureEquilibria
	for (int i = 0; (unsigned)i < paretoPureEquilibria.size(); i++)
		paretoPureEquilibria.at(i).resize(numPlayers);
	
	this->setMaxRationality(0);
	for (int x = 0; x < numPlayers; x++)
	{
		if (players.at(x)->getRationality() > maxR)
			maxR = players.at(x)->getRationality();
	}
	
	// default player has 2 strategies
	size = 1;
	if (numPlayers > 2)
	{
		for (int x = 0; x < numPlayers; x++)
			size *= players.at(x)->getNumStrats();
	}
	payoffMatrix.resize(size);
	
	for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
	{
		payoffMatrix.at(m).resize(players.at(0)->getNumStrats());
		for(int i = 0; i < players.at(0)->getNumStrats(); i++) // each row
		{
			payoffMatrix.at(m).at(i).resize(players.at(1)->getNumStrats());
			for(int j = 0; j < players.at(1)->getNumStrats(); j++) // each column in row i
			{
				LinkedList<T>* newList = new LinkedList<T>; // should already have head and tail
				for (int x = 0; x < numPlayers; x++)
					newList->appendNode(0, false);
				payoffMatrix.at(m).at(i).at(j) = newList; // head is the first node of the list in payoffMatrix.at(0).at(i).at(j)
			}
		}
	}
	zs = false;
	ih = false;
	pd = false;
	pc = false;
	bos = false;
	chicken = false;
	sh = false;
	null = false;
	
	isMixed();
}

// destructor
template <typename T>
simGame<T>::~simGame()
{
	for (int x = 0; x < numPlayers; x++)
		delete players.at(x);
		
	for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
		for(int i = 0; i < players.at(0)->getNumStrats(); i++) // each row
			for(int j = 0; j < players.at(1)->getNumStrats(); j++) // each column in row i
				delete payoffMatrix.at(m).at(i).at(j);
}

// add Player and set attributes
template <typename T>
void simGame<T>::addPlayer()
{
	// char option;
	int c = -1, nS = -1, r = 0;
	// int nT = -1, nV = 1;
	LinkedList<T>* curList; 
	Polynomial* p;
	
	// cout << "\nUtility: ";
	// cin >> u;
	
	cout << "Rationality:  ";
	cin >> r;
	validate(r, 0, 3);
	
	cout << "Number of Strategies:  ";
	cin >> nS;
	validateNumStrats(nS, 10);
	
	if (impartial && nS != players.at(0)->getNumStrats())
		impartial = false;
	
	/*
	cout << "Has the player chosen a strategy? Enter y or n:  ";
	cin >> option;
	if(option == 'y')
	{
		cout << "\nStrategy: ";
		cin >> c;
	}
	else*/
		c = '-';
	
	/*
	cout << "Does the player have a preference? Enter y or n:  ";
	cin >> option;
	if(option == 'y')
	{
		cout << "Enter the number of terms:  ";
		cin >> nT;
		cout << "Enter the number of variables:  ";
		cin >> nV;
		p = new Polynomial(nT, nV, 0);
		p->enterInfo();
	}
	else*/
		p = new Polynomial();
	
	Player* newPlayer = new Player(r, nS, c, p);
	
	players.resize(players.size() + 1);
	players.at(numPlayers) = newPlayer; // player added
	numPlayers++;
	
	// create new matrices in payoffMatrix
	int oldSize = payoffMatrix.size();
	payoffMatrix.resize(oldSize * players.at(numPlayers - 1)->getNumStrats()); // (n3 * n4 * ... * n_{old nP}) * n_{new player}
	for (int m = oldSize; (unsigned)m < payoffMatrix.size(); m++)
	{
		payoffMatrix.at(m).resize(players.at(0)->getNumStrats());
		for(int i = 0; i < players.at(0)->getNumStrats(); i++) // each row
		{
			payoffMatrix.at(m).at(i).resize(players.at(1)->getNumStrats()); // 2D slice is now correct size
			for(int j = 0; j < players.at(1)->getNumStrats(); j++) // each column in row i
			{
				LinkedList<T>* newList = new LinkedList<T>();
				payoffMatrix.at(m).at(i).at(j) = newList; // head is the first node of the list in payoffMatrix.at(0).at(i).at(j)
			}
		}
	}
	
	int val = -1;
	vector<int> profile = vector<int>(numPlayers);
	
	// enter newPlayer's payoffs
	cout << "Enter the new player's payoffs for the existing outcomes:  \n";
	cout << "P_" << numPlayers << ":\n";
	for (int m = 0; m < oldSize; m++)
	{
		profile = unhash(m);
		for(int i = 0; i < players.at(0)->getNumStrats(); i++)
			for(int j = 0; j < players.at(1)->getNumStrats(); j++)
			{
				profile.at(0) = i;
				profile.at(1) = j;
				if (!payoffMatrix.at(m).at(i).at(j))
				{							
					LinkedList<T>* newList = new LinkedList<T>;
					payoffMatrix.at(m).at(i).at(j) = newList;
				}
				curList = payoffMatrix.at(m).at(i).at(j);
				cout << "\t(";
				for (int x = 0; x < numPlayers; x++)
				{
					cout << profile.at(x) + 1;
					if (x < numPlayers - 1)
						cout << ", ";
				}
				cout << "):  ";
				cin >> val;
				curList->appendNode(val, false);
			}
	}
	
	// enter all payoffs in new matrices
	cout << "Enter the payoffs for all players in the new outcomes.\n";
	for (int m = oldSize; (unsigned)m < payoffMatrix.size(); m++)
	{
		profile = unhash(m);
		for (int i = 0; i < players.at(0)->getNumStrats(); i++)
			for (int j = 0; j < players.at(1)->getNumStrats(); j++)
			{
				profile.at(0) = i;
				profile.at(1) = j;
				
				cout << "(";
				for (int y = 0; y < numPlayers; y++)
				{
					cout << profile.at(y) + 1;
					if (y < numPlayers - 1)
						cout << ", ";
				}
				cout << "):\n";
				if (!payoffMatrix.at(m).at(i).at(j))
				{							
					LinkedList<T>* newList = new LinkedList<T>();
					payoffMatrix.at(m).at(i).at(j) = newList;
				}
				curList = payoffMatrix.at(m).at(i).at(j);
				for (int x = 0; x < numPlayers; x++)
				{
					cout << "\tP_" << x + 1 << ":  ";
					cin >> val;
					if (curList->getSize() < numPlayers)
						curList->appendNode(val, false);
					else
						curList->setNodeValue(x, val);
				}
			}
	}
	printPayoffMatrix();
}

// add strategy and payoffs for all players
template <typename T>
void simGame<T>::addStrategy(int x)
{	
	int val = -1;
	LinkedList<T>* curList;
	vector<int> profile = vector<int>(numPlayers);

	players.at(x)->setNumStrats(players.at(x)->getNumStrats() + 1); // increase the player's number of strategies
	cout << "Enter the payoffs for all players in the new outcomes:\n";
	if (x == 0)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
		{
			profile = unhash(m);
			// add a new row to each matrix and set the size of each new row
			payoffMatrix.at(m).resize(payoffMatrix.at(m).size() + 1);
			payoffMatrix.at(m).at(players.at(x)->getNumStrats() - 1).resize(players.at(1)->getNumStrats());
			
			for (int j = 0; j < players.at(1)->getNumStrats(); j++) // add new lists to each new row
			{				
				LinkedList<T>* newList = new LinkedList<T>;
				profile.at(0) = players.at(x)->getNumStrats() - 1;
				profile.at(1) = j;
				
				cout << "(";
				for (int y = 0; y < numPlayers; y++)
				{
					cout << profile.at(y) + 1;
					if (y < numPlayers - 1)
						cout << ", ";
				}
				cout << "):\n";
				payoffMatrix.at(m).at(players.at(x)->getNumStrats() - 1).at(j) = newList;
				curList = payoffMatrix.at(m).at(players.at(x)->getNumStrats() - 1).at(j);
				for (int y = 0; y < numPlayers; y++)
				{
					cout << "\tP_" << y + 1 << ":  ";
					cin >> val;
					curList->appendNode(val, false);
				}
			}
		}
	}
	else if (x == 1)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
		{
			profile = unhash(m);
			// add a new row to each matrix and set the size of each new row
			payoffMatrix.at(m).resize(payoffMatrix.at(m).size() + 1);
			
			for (int i = 0; i < players.at(0)->getNumStrats(); i++) // add new lists to each new column
			{
				payoffMatrix.at(m).at(i).resize(players.at(1)->getNumStrats());
				
				LinkedList<T>* newList = new LinkedList<T>;
				profile.at(0) = i;
				profile.at(1) = players.at(x)->getNumStrats() - 1;
				
				cout << "(";
				for (int y = 0; y < numPlayers; y++)
				{
					cout << profile.at(y) + 1;
					if (y < numPlayers - 1)
						cout << ", ";
				}
				cout << "):\n";
				payoffMatrix.at(m).at(i).at(players.at(x)->getNumStrats() - 1) = newList;
				curList = payoffMatrix.at(m).at(i).at(players.at(x)->getNumStrats() - 1);
				for (int y = 0; y < numPlayers; y++)
				{
					cout << "\tP_" << y + 1 << ":  ";
					cin >> val;
					curList->appendNode(val, false);
				}
			}
		}
	}
	else // x >= 2
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
		{
			profile = unhash(m);
			if (profile.at(x) == players.at(x)->getNumStrats() - 2) // - 2 because we already incremented numStrats at the beginning
			{
				// create and insert new matrix
				vector<vector<LinkedList<T>*> > newMatrix = vector<vector<LinkedList<T>*> >(players.at(0)->getNumStrats());
				for (int i = 0; i < players.at(0)->getNumStrats(); i++)
					newMatrix.at(i).resize(players.at(1)->getNumStrats());
				if ((unsigned)m == payoffMatrix.size() - 1)
					payoffMatrix.push_back(newMatrix);
				else
					payoffMatrix.insert(payoffMatrix.begin() + m + 1, newMatrix);
				
				// enter values into new matrix m + 1
				for (int i = 0; i < players.at(0)->getNumStrats(); i++)
				{
					for (int j = 0; j < players.at(1)->getNumStrats(); j++) // add new lists to each new row
					{				
						profile.at(0) = i;
						profile.at(1) = j;
						
						cout << "\t(";
						for (int y = 0; y < numPlayers; y++)
						{
							if (y == x)
								cout << profile.at(y) + 2;
							else
								cout << profile.at(y) + 1;
							if (y < numPlayers - 1)
								cout << ", ";
						}
						cout << "):\n";
						
						LinkedList<T>* newList = new LinkedList<T>;
						payoffMatrix.at(m + 1).at(i).at(j) = newList;
						curList = payoffMatrix.at(m + 1).at(i).at(j);
						for (int y = 0; y < numPlayers; y++)
						{
							cout << "\t\tP_" << y + 1 << ":  ";
							cin >> val;
							curList->appendNode(val, false);
						}
					}
				}
				m = m + 2; // skip the matrix we just entered
				}
		}
	}
	if (impartial)
		impartial = false;
	
	printPayoffMatrix();
}

// check if all equilibria are equal
template <typename T>
bool simGame<T>::allEqualEquilibria()
{	
	// checking for IH, PD, PC
	for (int a = 0; a < this->getSizePureEquilibria(); a++) // equilibrium being checked
		for (int b = 0; b < numPlayers; b++)
			for (int i = a + 1; i < this->getSizePureEquilibria(); i++) // only need to compare with equilibria past the ones that have been checked
				for (int j = 0; j < numPlayers; j++) // equilibrium being compared
				{
					if (!equalEquilibria(a, i))
						return false;
				}
	return true;
}

// checks if Null game
template <typename T>
bool simGame<T>::checkNullCondition()
{
	int factor = -1;
	LinkedList<T>* curList;

	computeNumOutcomes();
	
	if (getSizePureEquilibria() != numOutcomes)
		return false;
	
	for (int x = 0; x < numPlayers; x++)
	{
		factor = payoffMatrix.at(0).at(0).at(0)->getNodeValue(x);
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
			for (int i = 0; i < players.at(0)->getNumStrats(); i++)
				for (int j = 0; j < players.at(1)->getNumStrats(); j++)
				{					
					curList = payoffMatrix.at(m).at(i).at(j);
					if (curList->getNodeValue(x) != factor)
						return false;
				}
		
	}
	return true;
}

// checks if common knowledge
template <typename T>
bool simGame<T>::commonKnowledge() const
{
	for (int x = 0; x < numPlayers; x++)
	{
		for (int y = 0; y < numPlayers; y++)
		{
			for (int z = 0; z < numPlayers; z++)
			{
				if (!players.at(x)->getKnowledge()->getchoiceKnowledge(y, z))
					return false;
			}
		}
	}
	return true;
}

// add communication
template <typename T>
void simGame<T>::communication()
{
	LinkedList<T>* curList;
	vector<int> choices = vector<int>(numPlayers); // contains all knowledgable choices at end
	vector<int> originalChoices = vector<int>(numPlayers); // contains no knowledgable choices
	vector<int> tempChoices = vector<int>(numPlayers); // contains only one knowledgable choice
	
	computePureEquilibria(); // calls computeBestResponses()
	determineType();
	isMixed(); // needs pureEquilibria() and determineType()
	computeChoices();
	
	// setting choices, originalChoices and tempChoices
	for (int x = 0; x < numPlayers; x++)
	{
		choices.at(x) = players.at(x)->getChoice();
		originalChoices.at(x) = players.at(x)->getChoice();
		tempChoices.at(x) = players.at(x)->getChoice();
	}
	
	/////////////////////////////////////////////////////////////////////////////
	printPayoffMatrixSansInfo();
	
	cout << "Original Outcome: ";
	if (zs)
		cout << "undecided for zero-sum games\n";
	else
	{
		cout << "(";
		for (int x = 0; x < numPlayers; x++)
		{
			cout << "s_" << originalChoices.at(x) + 1;
			if (x < numPlayers - 1)
				cout << ", ";
		}
		cout << ") -> ";
		
		if (numPlayers < 3)
			curList = payoffMatrix.at(0).at(originalChoices.at(0)).at(originalChoices.at(1));
		else
			curList = payoffMatrix.at(hash(originalChoices)).at(originalChoices.at(0)).at(originalChoices.at(1));
		
		curList->displayPayoffs();
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	cout << "\nPareto-optimal:  ";
	if (PO(tempChoices))
		cout << "yes\n\n";
	else
		cout << "no\n\n";
	
	for (int x = 0; x < numPlayers; x++)
	{
		if (numPlayers == 2)
			cout << "If P_" << x + 1 << " knows the other player's choice:\n";
		else
			cout << "If P_" << x + 1 << " knows the other players' choices:\n";
		cout << "----------------------------------------\n";
		players.at(x)->setChoice(maxStratInRowColOrMatrices(x, originalChoices)); // chooses P_x's choice based on other choices
		choices.at(x) = players.at(x)->getChoice(); // choices should contain all players' choices at the end of this loop
		tempChoices.at(x) = players.at(x)->getChoice();
		
		cout << "Current Outcome:  (";
		for (int y = 0; y < numPlayers; y++)
		{
			cout << "s_" << tempChoices.at(y) + 1;
			if (y < numPlayers - 1)
				cout << ", ";
		}
		cout << ") -> ";
		if (x == 0)
			curList = payoffMatrix.at(hash(originalChoices)).at(tempChoices.at(0)).at(originalChoices.at(1));
		else if (x == 1)
			curList = payoffMatrix.at(hash(originalChoices)).at(originalChoices.at(0)).at(tempChoices.at(1));
		else
			curList = payoffMatrix.at(hash(tempChoices)).at(tempChoices.at(0)).at(tempChoices.at(1));
		
		curList->displayPayoffs();
		
		cout << "\nPareto-optimal:  ";
		if (PO(tempChoices))
			cout << "yes\n\n";
		else
			cout << "no\n\n";
		
		tempChoices = originalChoices; // resetting tempChoices
	}
	
	// all knowledgable choices
	if (numPlayers == 2)
		cout << "If both players know each other's choice:\n";
	else
		cout << "If all players know the others' choices:\n";
	cout << "------------------------------------------\n";
	cout << "Current Outcome:  (";
	for (int x = 0; x < numPlayers; x++)
	{
		cout << "s_" << choices.at(x) + 1;
		if (x < numPlayers - 1)
			cout << ", ";
	}
	cout << ") -> ";
	
	curList = payoffMatrix.at(hash(choices)).at(choices.at(0)).at(choices.at(1));
	curList->displayPayoffs();
	
	cout << "\nPareto-optimal:  ";
	if (PO(choices))
		cout << "yes\n\n";
	else
		cout << "no\n\n";
	
	tempChoices = choices; // tempChoices not needed anymore, can repurpose it
	for (int x = 0; x < numPlayers; x++)
		choices.at(x) = maxStratInRowColOrMatrices(x, tempChoices);
	
	cout << "Common Knowledge:\n";
	cout << "---------------------------------------\n";
	cout << "Current Outcome:  (";
	for (int x = 0; x < numPlayers; x++)
	{
		cout << "s_" << players.at(x)->getChoice() + 1;
		if (x < numPlayers - 1)
			cout << ", ";
	}
	cout << ") -> ";
	
	curList = payoffMatrix.at(hash(choices)).at(choices.at(0)).at(choices.at(1));
	curList->displayPayoffs();
	
	cout << "\nPareto-optimal:  ";
	if (PO(choices))
		cout << "yes\n";
	else
		cout << "no\n";
}

// compute BR's
template <typename T>
void simGame<T>::computeBestResponses()
{
	int maxValue = -std::numeric_limits<int>::max();
	LinkedList<T>* curList;
	
	for (int x = 0; x < numPlayers; x++)
	{
		if (x == 0)
		{
			for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
				for (int j = 0; j < players.at(1)->getNumStrats(); j++) // j-th column
				{
					// find maxValue for each row in j-th column
					maxValue = -std::numeric_limits<int>::max();
					for (int i = 0; i < players.at(0)->getNumStrats(); i++)
					{
						curList = payoffMatrix.at(m).at(i).at(j);
						if (curList->getNodeValue(0) > maxValue)
							maxValue = curList->getNodeValue(0);
					}
					// check each row in j-th column
					for (int i = 0; i < players.at(0)->getNumStrats(); i++)
					{
						curList = payoffMatrix.at(m).at(i).at(j);
						if (curList->getNodeValue(0) == maxValue) // don't need >= bc it's the max
							curList->setNodeBestResponse(0, true);
						else
							curList->setNodeBestResponse(0, false);
					}
				}
				
		}
		else if (x == 1)
		{
			for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
				for (int i = 0; i < players.at(0)->getNumStrats(); i++) // i-th row
				{
					// find maxValue for each column in i-th row
					maxValue = -std::numeric_limits<int>::max();
					for (int j = 0; j < players.at(1)->getNumStrats(); j++)
					{
						curList = payoffMatrix.at(m).at(i).at(j);
						if (curList->getNodeValue(1) > maxValue)
							maxValue = curList->getNodeValue(1);
					}
					// check each column in i-th row
					for (int j = 0; j < players.at(1)->getNumStrats(); j++)
					{
						curList = payoffMatrix.at(m).at(i).at(j);
						if (curList->getNodeValue(1) == maxValue) // don't need >= bc it's the max
							curList->setNodeBestResponse(1, true);
						else
							curList->setNodeBestResponse(1, false);
					}
				}
			
		}
		else // x > 1
		{
			int m = 0;
			int product = 1;
			vector<int> profile = vector<int>(numPlayers);
			while ((unsigned)m < payoffMatrix.size())
			{
				profile = unhash(m);
				for (int i = 0; i < players.at(0)->getNumStrats(); i++)
					for (int j = 0; j < players.at(1)->getNumStrats(); j++)
					{						
						maxValue = -std::numeric_limits<int>::max();
						
						/* Comparing P_x's strategies with each other, keeping P_x's strategy
						the same, so we vary over P_x's strategies */
						profile.at(x) = 0; // at start of section
						while (profile.at(x) < players.at(x)->getNumStrats()) // finding maxValue
						{
							curList = payoffMatrix.at(hash(profile)).at(i).at(j);
							if (curList->getNodeValue(x) > maxValue) // checking for maxValue
								maxValue = curList->getNodeValue(x);
							
							profile.at(x)++; // move to next matrix in section
						}
						
						// CHECK through ij-entries in each section
						profile.at(x) = 0; // at start of section
						while (profile.at(x) < players.at(x)->getNumStrats())
						{
							curList = payoffMatrix.at(hash(profile)).at(i).at(j);
							if (curList->getNodeValue(x) == maxValue) // checking for maxValue
								curList->setNodeBestResponse(x, true);
							else // <
								curList->setNodeBestResponse(x, false);
							
							profile.at(x)++; // move to next matrix in section
						}
					}
				
				// m = hash(profile);
				// profile.at(x)--; // will be exactly numStrats at end, so decrement
				// m = hash(profile); // at last matrix in section
				
				if (x > 2 && x < numPlayers - 1 && product == 1)
				{
					for (int y = 2; y <= x - 1; y++)
						product *= players.at(y)->getNumStrats();
				}
				m += product;
			}
		}
	}
}

// compute choices
template <typename T>
void simGame<T>::computeChoices()
{	
	bool visitedTwice = false;
	vector<vector<int> > alreadyVisited; // contains profiles
	vector<int> choices = vector<int>(numPlayers);
	vector<int> previousChoices = vector<int>(numPlayers);
	vector<int> profile = vector<int>(numPlayers);
	
	if (!zs && !null && pureEquilibria.size() != 0)
	{
		if (mixed)
		{
			// randomly choose one equilibrium or another
			srand(time(NULL));
			// int eq = rand() % pureEquilibria.size();
			// profile = getPureEquilibrium(eq);
			// for (int x = 0; x < numPlayers; x++)
			// 	players.at(x)->setChoice(profile.at(x));

			// randomly choose each strategy
			for (int x = 0; x < numPlayers; x++)
				players.at(x)->setChoice(rand() % players.at(x)->getNumStrats());
		}
		else if (!mixed)
		{
			// start with each player choosing the strategy corresponding to their max payoff
			for (int x = 0; x < numPlayers; x++)
			{		
				players.at(x)->setChoice(maxStrat(x));
				choices.at(x) = players.at(x)->getChoice();
				previousChoices.at(x) = players.at(x)->getChoice();
			}
			
			alreadyVisited.push_back(previousChoices);
			while (!isPureEquilibrium(choices) && !visitedTwice)
			{			
				// change each player's choice to the max in the row/col/section if not already max
				for (int x = 0; x < numPlayers; x++)
					choices.at(x) = maxStratInRowColOrMatrices(x, previousChoices);
				
				// check if new choices have already been visited
				for (int n = 0; (unsigned)n < alreadyVisited.size(); n++)
				{
					if (choices == alreadyVisited.at(n))
						visitedTwice = true;
				}
				
				// add choices to the list of outcomes already visited
				alreadyVisited.push_back(choices);
				// save choices for computing the next step in the process
				previousChoices = choices;
			}
			for (int x = 0; x < numPlayers; x++)
				players.at(x)->setChoice(choices.at(x));
		}
	}
	else
	{
		if (zs)
			cout << "ERROR: computing pure choice for a ZS game\n";
		if (null)
			cout << "ERROR: computing pure choice for a NULL game\n";
		if (pureEquilibria.size() == 0)
			cout << "ERROR: computing pure choice for a game with no pure equilibria\n";
	}
}

// compute expected utilities
template <typename T>
vector<vector<Polynomial*> > simGame<T>::computeExpectedUtilities()
{
	// choose player, then choose strategy
	Polynomial* poly;
	vector<vector<Polynomial*> > EU = vector<vector<Polynomial*> >(numPlayers);
	for (int x = 0; x < numPlayers; x++)
		EU.at(x).resize(players.at(x)->getNumStrats());
	
	if (numPlayers < 3)
	{
		vector<int> coeffs1 = vector<int>(players.at(0)->getNumStrats()); // coefficients for P_1's expected utilities
		vector<int> coeffs2 = vector<int>(players.at(1)->getNumStrats()); // coefficients for P_2's expected utilities
		for (int i = 0; i < players.at(0)->getNumStrats(); i++) // EU_1(s_i)
		{
			for (int j = 0; j < players.at(1)->getNumStrats(); j++) // terms
				coeffs1.at(j) = payoffMatrix.at(0).at(i).at(j)->getNodeValue(1);
			
			poly = new Polynomial(players.at(1)->getNumStrats(), players.at(1)->getNumStrats() - 1, 0);
			poly->setEUCoefficients(coeffs1, numPlayers);
			EU.at(0).at(i) = poly;
		}
		
		for (int j = 0; j < players.at(1)->getNumStrats(); j++) // EU_2(s_j)
		{
			for (int i = 0; i < players.at(0)->getNumStrats(); i++) // terms
				coeffs2.at(i) = payoffMatrix.at(0).at(i).at(j)->getNodeValue(0);
			
			poly = new Polynomial(players.at(0)->getNumStrats(), players.at(0)->getNumStrats() - 1, 0);
			poly->setEUCoefficients(coeffs2, numPlayers);
			EU.at(1).at(j) = poly;
		}
		return EU;
	}
	else // numPlayers >= 3
	{
		int num = -std::numeric_limits<T>::max();
		vector<int> coeffs;
		vector<vector<int>> exponents;
		vector<int> profile;
		
		for (int x = 0; x < numPlayers; x++) // EU_x
		{
			cout << "x: " << x << endl;			
			if (x == 0)
			{
				for (int i = 0; i < players.at(0)->getNumStrats(); i++) // EU_x(i)
				{
					coeffs = vector<int>(players.at(1)->getNumStrats() * payoffMatrix.size()); // coefficients for P_x's expected utilities
					for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
					{
						// Get Coefficients
						profile = unhash(m);
						profile.at(x) = std::numeric_limits<T>::quiet_NaN();
						for (int j = 0; j < players.at(1)->getNumStrats(); j++)
						{
							profile.at(0) = j;
							exponents.push_back(profile); // save exponents along the way
							
							num = 1;
							for (int y = 1; y < numPlayers; y++)
							{
								num *= payoffMatrix.at(m).at(i).at(j)->getNodeValue(y);
								if (num == 0)
									break;
							}
							coeffs.at(players.at(1)->getNumStrats() * m + j) += num;
						}
					}
					poly = new Polynomial(players.at(x)->getNumStrats(), numPlayers, 0);
					poly->setEUCoefficients(coeffs, numPlayers);
					EU.at(x).at(i) = poly;
				}
			}
			else if (x == 1)
			{				
				for (int j = 0; j < players.at(1)->getNumStrats(); j++) // EU_x(j)
				{
					coeffs.clear();
					coeffs.resize(players.at(0)->getNumStrats() * payoffMatrix.size()); // coefficients for P_x's expected utilities
					for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
					{
						profile = unhash(m);
						profile.at(x) = std::numeric_limits<T>::quiet_NaN();
						for (int i = 0; i < players.at(0)->getNumStrats(); i++)
						{
							profile.at(0) = i;
							exponents.push_back(profile);
							
							num = 1;
							for (int y = 0; y < numPlayers; y++)
							{
								if (y != x)
								{
									num *= payoffMatrix.at(m).at(i).at(j)->getNodeValue(y);
									if (num == 0)
										break;
								}
							}
							coeffs.at(players.at(0)->getNumStrats() * m + i) += num;
						}
					}					
					poly = new Polynomial(players.at(x)->getNumStrats(), numPlayers, 0);
					poly->setEUCoefficients(coeffs, numPlayers);
					EU.at(x).at(j) = poly;
				}
			}
			else // x >= 2
			{
				int num = 1, numMatricesInSection = 1, product = 1, size = -1, strat = -1;
				vector<int> alpha; // holds each terms exponents
				
				if (numPlayers != 3)
				{
					for (int y = 2; y < numPlayers; y++)
					{
						if (y != x)
							numMatricesInSection *= players.at(y)->getNumStrats();
					}
				}
				size = players.at(0)->getNumStrats() * players.at(1)->getNumStrats() * numMatricesInSection;
				
				/* Comparing others' strategies based on what P_x's strategy is, keeping 
				P_x's strategies the same, so we vary over the others' strategies */
				strat = 0;
				int count = 0, m = 0;
				while (strat < players.at(x)->getNumStrats())
				{
					coeffs.clear();
					coeffs.resize(size); // coefficients for P_x's expected utilities
					m = 0;
					count = 0;
					while (count < numMatricesInSection)
					{
						profile = unhash(m);
						profile.at(x) = strat;
						for (int i = 0; i < players.at(0)->getNumStrats(); i++)
							for (int j = 0; j < players.at(1)->getNumStrats(); j++) // terms
							{
								// saving exponents
								profile.at(0) = i;
								profile.at(1) = j;
								
								num = 1;
								for (int y = 0; y < numPlayers; y++)
								{
									if (y != x)
									{										
										num *= payoffMatrix.at(hash(profile)).at(i).at(j)->getNodeValue(y);
										if (num == 0)
											break;
									}
								}
								coeffs.at(players.at(0)->getNumStrats() * players.at(1)->getNumStrats() * count + players.at(1)->getNumStrats() * i + j) += num;
							}
						
						// done with profile, use it to save this terms set of exponents
						profile.at(x) = std::numeric_limits<T>::quiet_NaN();
						exponents.push_back(profile);
						
						if (product == 1 && x != numPlayers - 1)
						{
							if (x == 2)
							{
								for (int y = 2; y <= x; y++)
									product *= players.at(y)->getNumStrats();
							}
							else if (x > 2)
							{
								for (int y = 2; y < x; y++)
									product *= players.at(y)->getNumStrats();
							}
						}
						m += product;
						count++;
					}
					for (int n = 0; (unsigned)n < coeffs.size(); n++)
						cout << "coeffs.at(" << n << "): " << coeffs.at(n) << endl;
					
					poly = new Polynomial(players.at(x)->getNumStrats(), numPlayers, 0);
					poly->setEUCoefficients(coeffs, numPlayers);
					poly->setEUExponents(exponents);
					EU.at(x).at(strat) = poly;
					
					strat++;
					if (strat < players.at(x)->getNumStrats())
						cout << endl;
				}
			}
			cout << endl;
		}
		return EU;
	}
}

// compute impartiality
template <typename T>
void simGame<T>::computeImpartiality()
{
	int num = players.at(0)->getNumStrats();
	for (int x = 1; x < numPlayers; x++)
	{
		if (players.at(x)->getNumStrats() != num)
		{
			impartial = false;
			return;
		}
	}
	impartial = true;
}

// compute k-strategies
template <typename T>
void simGame<T>::computeKStrategies()
{	
	int maxStrat = -std::numeric_limits<int>::max();
	int num = -1;
	vector<int> others;
	
	for (int r = 0; r < 4; r++)
		for (int x = 0; x < numPlayers; x++)
		{
			maxStrat = -std::numeric_limits<int>::max();
			
			if (r == 0)
			{
				num = this->maxStrat(x); // num is what player x will do at L_0
				kStrategies.at(0).at(x) = num;
			}
			else
			{
				others = vector<int>(numPlayers);
				for (int y = 0; y < numPlayers; y++)
				{
					if (y == x)
						others.at(y) = -1;
					else
						others.at(y) = kStrategies.at(r - 1).at(y);
				}
				
				// finding the maximum in each row/column/matrix that has already been chosen
				if (x == 0)
				{
					for (int i = 0; i < players.at(0)->getNumStrats(); i++)
					{
						if (payoffMatrix.at(hash(others)).at(i).at(others.at(1))->getNodeBestResponse(0))
							maxStrat = i; // maxStrat for player x
					}
				}
				else if (x == 1)
				{
					for (int j = 0; j < players.at(1)->getNumStrats(); j++)
					{
						if (payoffMatrix.at(hash(others)).at(others.at(0)).at(j)->getNodeBestResponse(1))
							maxStrat = j;
					}
				}
				else // x >= 2
				{					
					for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
						for (int i = 0; i < players.at(0)->getNumStrats(); i++)
						{
							for (int j = 0; j < players.at(1)->getNumStrats(); j++)
							{
								if (payoffMatrix.at(m).at(others.at(0)).at(others.at(1))->getNodeBestResponse(1))
									maxStrat = unhash(m).at(x);
							}
						}
					
				}
				kStrategies.at(r).at(x) = maxStrat;
			}
			if (r == players.at(x)->getRationality())
				players.at(x)->setKChoice(kStrategies.at(r).at(x));
		}
	
	return;
}

// compute mixed equilibria
template <typename T>
void simGame<T>::computeMixedEquilibria()
{
	computePureEquilibria();
	cout << endl;
	
	// Generate combinations
	int n = pureEquilibria.size();
	for (int k = 2; k <= n; k++)
	{
		vector<int> combo = vector<int>(k);
		for (int x = 0; x < k; x++)
			combo.at(x) = x;
		int maxUnsaturated = k - 1;
		while (combo.at(0) < n - k + 1)
		{
			while (maxUnsaturated > 0 && combo.at(maxUnsaturated) == n - k + maxUnsaturated)
				maxUnsaturated--;
			
			cout << "randomizing over (";
			for (int a = 0; (unsigned)a < combo.size(); a++)
			{
				cout << "e_" << combo.at(a);
				if ((unsigned)a < combo.size() - 1)
					cout << ", ";
			}
			cout << ")\n";
			
			combo.at(maxUnsaturated)++;
			while (maxUnsaturated < k - 1)
			{
				combo.at(maxUnsaturated + 1) = combo.at(maxUnsaturated) + 1;
				maxUnsaturated++;
			}
		}
	}
}

// compute mixed strategies
template <typename T>
void simGame<T>::computeMixedStrategies()
{
	vector<int> coeffs1 = vector<int>(players.at(0)->getNumStrats()); // coefficients for P_1's expected utilities
	vector<int> coeffs2 = vector<int>(players.at(1)->getNumStrats()); // coefficients for P_2's expected utilities
	vector<vector<Polynomial*> > EU;
	// double p = -1.0, q = -1.0;
	
	EU = computeExpectedUtilities();
	cout << endl;
	for (int x = 0; x < numPlayers; x++)
	{
		for (int n = 0; (unsigned)n < EU.at(x).size(); n++)
		{
			cout << "EU_" << x + 1 << "(s_" << n + 1 << ") = ";
			EU.at(x).at(n)->printPolynomial();
		}
		if (x < numPlayers - 1)
			cout << "--------------------------\n";
	}
	/*cout << endl;
	
	if (EU.at(0).size() == 2)
		p = solve(EU.at(0).at(0), EU.at(0).at(1));
	if (EU.at(1).size() == 2)
		q = solve(EU.at(1).at(0), EU.at(1).at(1));
	
	if (p == -2.0 || q == -2.0)
		cout << "\nNO MSE\n";
	else
	{
		cout << "MSE:\n";
		cout << "--------------------------\n";
		cout << "P(P_1 chooses s_1) = " << p << endl;
		cout << "P(P_1 chooses s_2) = " << 1 - p << endl;
		cout << "P(P_2 chooses s_1) = " << q << endl;
		cout << "P(P_2 chooses s_1) = " << 1 - q << endl;
	}
	*/
}

// compute total number of outcomes
template <typename T>
void simGame<T>::computeNumOutcomes()
{
	int num = 1;			
	for (int i = 0; i < numPlayers; i++)
		num *= players.at(i)->getNumStrats();
	setNumOutcomes(num);
}

// compute pure equilibria
template <typename T>
void simGame<T>::computePureEquilibria()
{
	// cout << "computePureEquilibria\n";
	bool isEquilibrium = false;
	LinkedList<T>* curList;
	vector<int> strategyProfile = vector<int>(numPlayers);
	
	clearPureEquilibria();
	clearParetoPureEquilibria();
	computeBestResponses();
	
	for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
		for (int i = 0; i < players.at(0)->getNumStrats(); i++)
		{
			for (int j = 0; j < players.at(1)->getNumStrats(); j++)
			{
				
				isEquilibrium = true;
				curList = payoffMatrix.at(m).at(i).at(j);
				int x = 0;
				while (isEquilibrium && x < numPlayers)
				{
					// cout << "\t\t\tx: " << x << endl;
					if (!curList->getNodeBestResponse(x))
						isEquilibrium = false;
					x++;
				}
				if (isEquilibrium) // at the end of payoffMatrix.at(m).at(i).at(j)
				{					
					strategyProfile = unhash(m);
					strategyProfile.at(0) = i; // indices of the equilibrium going into the vector
					strategyProfile.at(1) = j;
					pushEquilibrium(strategyProfile);
					if (PO(strategyProfile))
						pushParetoEquilibrium(strategyProfile);
				}
			}
		}
}

// check if all strats in equilibrium are equal
template <typename T>
bool simGame<T>::coordination()
{
	for (int n = 0; n < getSizePureEquilibria(); n++)
	{
		for (int x = 1; x < numPlayers; x++)
		{
			if (getPureEquilibrium(n).at(0) != getPureEquilibrium(n).at(x))
				return false;
		}
	}
	return true;
}

// edit a single player's info
template <typename T>
void simGame<T>::editPlayer()
{
	int index = -1, menu = -1, r = -1;
	
	printPlayers();
	
	cout << "Enter the index of the player you wish to edit:  ";
	cin >> index;
	validate(index, 1, numPlayers);
	
	cout << "\nPLAYER " << index << ":\n";
	cout << "-----------";
	cout << *players.at(index - 1);
	
	cout << "Which aspect of P_" << index << " would you like to change?\n";
	cout << "1. Rationality\n";
	cout << "2. Add a strategy\n";
	cout << "3. Remove a strategy\n";
	cout << "4. A single payoff\n";
	cout << "5. All payoffs\n";
	cout << "6. Cancel\n";
	cout << "Enter an integer from 1 to 6.  ";
	cin >> menu;
	validate(menu, 1, 6);
	
	switch(menu)
	{
		case 1:	cout << "Enter P_" << index << "'s rationality:  ";
				cin >> r;
				validate(r, 0, 3);
				cout << endl;
				players.at(index - 1)->setRationality(r);
				break;
		case 2:	addStrategy(index - 1);
				break;
		case 3:	removeStrategyPrompt(index - 1);
				break;
		case 4: changeAPayoff(index - 1);
				break;
		case 5: changePayoffs(index - 1);
				break;
		default:	break;
	}
}

// prompt for a strategy profile
// TEST
template <typename T>
vector<int> simGame<T>::enterStratProfile()
{
	vector <int> stratProfile = vector<int>(numPlayers);
	
	cout << "Enter each strategy in the strategy profile:  ";
	cout << "(";
	int count = 0;
	while (count < numPlayers - 1)
	{
		cin >> stratProfile.at(count);
		cout << ", ";
		count++;
	}
	cout << ")\n";
	return stratProfile;
}

// checks if a and b are equal
template <typename T>
bool simGame<T>::equalEquilibria(int a, int b)
{
	LinkedList<T>* aList = payoffMatrix.at(hash(getPureEquilibrium(a))).at(getPureEquilibrium(a).at(0)).at(getPureEquilibrium(a).at(1));
	LinkedList<T>* bList = payoffMatrix.at(hash(getPureEquilibrium(b))).at(getPureEquilibrium(b).at(0)).at(getPureEquilibrium(b).at(1));
	
	for (int x = 0; x < numPlayers; x++)
	{
		if (aList->getNodeValue(x) != bList->getNodeValue(x))
			return false;
	}
	return true;
}

// converts a sequence of strategies into the index in a stack of payoff arrays that correspond to that sequence
template <typename T>
int simGame<T>::hash(vector<int> profile)
{
	computeImpartiality();
	
	// c_2 + sum_{x = 3}^{nP - 1} (nS)^x * c_x
	int num = 0; // return 0 if numPlayers < 2
	if (numPlayers > 2)
		num = profile.at(2);
	if (impartial)
	{
		for (int x = 3; x < numPlayers; x++)
		{
			if (profile.at(x) > 0)
				num += pow(players.at(0)->getNumStrats(), x - 2) * profile.at(x);
		}
	}
	else // c_2 + sum_{x=3}^{nP} nS_2 *...* nS_{x-1} * c_x
	{
		if (numPlayers > 3)
		{
			int product = 0;
			for (int x = 3; x < numPlayers; x++)
			{
				product = 1;
				if (profile.at(x) > 0)
				{
					for (int y = 2; y <= x - 1; y++)
						product *= players.at(y)->getNumStrats();
					
					num += product * profile.at(x);
				}
			}
		}
	}
	return num;
}

// checks if the game is mixed
template <typename T>
void simGame<T>::isMixed()
{
	if (pureEquilibria.size() % 2 == 0)
	{
		mixed = true;
		return;
	}
	else
	{
		if (paretoPureEquilibria.size() > 1)
		{
			mixed = true;
			return;
		}
	}
	mixed = false;
}

// checks if a strategy is inferior (dominated)
template <typename T>
bool simGame<T>::isInferior()
{
	
	
	return false;
}

// checks if profile is a pure equilibrium
template <typename T>
bool simGame<T>::isPureEquilibrium(vector<int> profile)
{
	for (int n = 0; n < getSizePureEquilibria(); n++)
	{
		for (int x = 0; x < numPlayers; x++)
		{
			if (getPureEquilibrium(n).at(x) != profile.at(x))
				return false;
		}
	}
	return true;
}

template <typename T>
bool simGame<T>::isStrictlyDominant(int x, int s)
{	
	// determine if s is a dominant strategy for P_x
	LinkedList<T>* curList;
	
	if (x == 0)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
			for (int i = 0; i < players.at(x)->getNumStrats(); i++)
			{
				if (i != s)
				{
					for (int j = 0; j < players.at(1)->getNumStrats(); j++)
					{						
						curList = payoffMatrix.at(m).at(i).at(j);
						if (curList->getNodeBestResponse(x)) // checks if any others are >=
							return false;
					}
				}
			}
		
	}
	else if (x == 1)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
			for (int i = 0; i < players.at(0)->getNumStrats(); i++)
			{
				// check BR's and compare strat s in that row with all other values in that row
				for (int j = 0; j < players.at(x)->getNumStrats(); j++)
				{
					if (j != s)
					{					
						curList = payoffMatrix.at(m).at(i).at(j);
						if (!curList->getNodeBestResponse(x))
							return false;
					}
				}
			}
		
	}
	else
	{		
		int m = 0, product = 1;
		vector<int> profile = vector<int>(numPlayers);
		vector<int> sProfile = vector<int>(numPlayers);
		while ((unsigned)m < payoffMatrix.size()) // selects s in each section
		{
			for (int i = 0; i < players.at(0)->getNumStrats(); i++) // row in s
				for (int j = 0; j < players.at(1)->getNumStrats(); j++) // column in s
				{
					profile = unhash(m);
					if (profile.at(x) != s)
					{
						curList = payoffMatrix.at(hash(profile)).at(i).at(s);
						if (curList->getNodeBestResponse(x))
							return false;
					}
				}
			
			profile.at(x)--; // will be exactly numStrats at end, so decrement
			m = hash(profile); // at last matrix in section
			if (x > 2 && product == 1)
			{
				for (int y = 2; y <= x - 1; y++)
					product *= players.at(y)->getNumStrats();
			}
			m += product; // move to the next one, which is the first in the next section
		}
	}
	return true;
}

// checks if s is strictly dominated
template <typename T>
bool simGame<T>::isStrictlyDominated(int x, int s)
{
	// cout << "ISTRICTLYDOMINATED: (" << x << ", " << s << ")\n";
	
	bool domStrat = true;
	LinkedList<T>* curList;
	LinkedList<T>* sList;
	
	if (x == 0)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
			for (int i = 0; i < players.at(x)->getNumStrats(); i++)
			{
				if (i != s)
				{
					domStrat = true;
					for (int j = 0; j < players.at(1)->getNumStrats(); j++)
					{
						curList = payoffMatrix.at(m).at(i).at(j);
						sList = payoffMatrix.at(m).at(s).at(j);
						if (curList->getNodeValue(x) <= sList->getNodeValue(x)) // checks if > than s
							domStrat = false;
					}
					if (domStrat)
						return true;
				}
			}
		
		return false;
	}
	else if (x == 1)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++) // fix a matrix
		{
			// compare strat s in that row with all other values in that row
			for (int i = 0; i < players.at(0)->getNumStrats(); i++) // fix a row
			{
				for (int j = 0; j < players.at(x)->getNumStrats(); j++)
				{
					if (j != s)
					{
						domStrat = true;
						curList = payoffMatrix.at(m).at(i).at(j);
						sList = payoffMatrix.at(m).at(i).at(s);
						if (curList->getNodeValue(x) <= sList->getNodeValue(x)) // checks if > than s
							domStrat = false;
					}
				}
				if (domStrat)
					return true;
			}
		}
		return false;
	}
	else // x >= 2
	{
		int curM = 0, m = 0, product = 1;
		vector<int> curProfile = vector<int>(numPlayers);
		vector<int> sProfile = vector<int>(numPlayers);
		sProfile = unhash(0);
		sProfile.at(x) = s;
		m = hash(sProfile);
		// cout << "start: " << m << endl;
		while ((unsigned)m < payoffMatrix.size() - players.at(x)->getNumStrats() + s + 1) // selects s in each section
		{
			// cout << "m: " << m << endl;
			sProfile = unhash(m);
			sProfile.at(x) = s;
			while ((unsigned)curM < payoffMatrix.size()) // checks other sections for dominant strategies
			{
				// cout << "\tcurM: " << curM << endl;
				curProfile = unhash(curM);
				if (curProfile != sProfile)
				{
					for (int i = 0; i < players.at(0)->getNumStrats(); i++) // row in s
					{
						int j = 0;
						while (j < players.at(1)->getNumStrats() && domStrat) // column in s
						{		
							// cout << "\t\ti: " << i << endl;
							// cout << "\t\tj: " << j << endl;
							
							curList = payoffMatrix.at(curM).at(i).at(j);
							sList = payoffMatrix.at(hash(sProfile)).at(i).at(j);
							
							// cout << "\t\t\t" << curList->getNodeValue(x) << ", " << sList->getNodeValue(x) << endl;
							
							if (curList->getNodeValue(x) <= sList->getNodeValue(x)) // checks if > than s
							// {
								// cout << "\t\t\tWEEWOO\n";
								domStrat = false;
							// }
							j++;
						}
					}
					if (domStrat)
					// {
						// cout << "\tleaving\n";
						return true;
					// }
				}
				
				if (x > 2 && x < numPlayers - 1 && product == 1)
				{
					for (int y = 2; y <= x - 1; y++)
						product *= players.at(y)->getNumStrats();
				}
				curM += product; // move to the next one, which is the first in the next section
				// cout << "\tnext1: " << curM << endl;
			}
			if (x > 2 && x < numPlayers - 1 && product == 1)
			{
				for (int y = 2; y <= x - 1; y++)
					product *= players.at(y)->getNumStrats();
			}
			m += product; // move to next matrix in section of the s strategy, which is the first in the next section
			// cout << "next2\n";
		}
		return false;
	}
}

// checks if s is weakly dominant
template <typename T>
bool simGame<T>::isWeaklyDominant(int x, int s)
{	
	LinkedList<T>* curList;
	LinkedList<T>* sList;
	bool oneIsLess = false;
	
	if (x == 0)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
			for (int i = 0; i < players.at(x)->getNumStrats(); i++)
			{
				if (i != s)
				{
					for (int j = 0; j < players.at(1)->getNumStrats(); j++)
					{						
						curList = payoffMatrix.at(m).at(i).at(j);
						sList = payoffMatrix.at(m).at(s).at(j);
						if (!sList->getNodeBestResponse(x)) // checks if at least >=
							return false;
						if (!oneIsLess && curList->getNodeValue(x) < sList->getNodeValue(x)) // checks if one is < than s
							oneIsLess = true;
					}
				}
			}
		
	}
	else if (x == 1)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
			for (int i = 0; i < players.at(0)->getNumStrats(); i++)
			{
				// check BR's and compare strat s in that row with all other values in that row
				for (int j = 0; j < players.at(x)->getNumStrats(); j++)
				{
					if (j != s)
					{						
						curList = payoffMatrix.at(m).at(i).at(j);
						sList = payoffMatrix.at(m).at(i).at(s);
						if (!sList->getNodeBestResponse(x)) // checks if at least >=
							return false;
						if (!oneIsLess && curList->getNodeValue(x) < sList->getNodeValue(x)) // checks if one is < than s
							oneIsLess = true;
					}
				}
			}
	}
	else // x > 1
	{
		int em = 0, m = 0, product = 1;
		vector<int> profile = vector<int>(numPlayers);
		vector<int> sProfile = vector<int>(numPlayers);
		while ((unsigned)m < payoffMatrix.size()) // selects s in each section
		{
			for (int i = 0; i < players.at(0)->getNumStrats(); i++) // row in s
				for (int j = 0; j < players.at(1)->getNumStrats(); j++) // column in s
				{
					sProfile = unhash(m);
					sProfile.at(x) = s;
					
					sList = payoffMatrix.at(hash(sProfile)).at(i).at(s);
					if (!sList->getNodeBestResponse(x))
						return false;
					
					em = 0;
					while ((unsigned) em < payoffMatrix.size()) // 2nd section counter
					{
						for (int i2 = 0; i2 < players.at(0)->getNumStrats(); i2++) // 2nd row counter
						{
							for (int j2 = 0; j2 < players.at(1)->getNumStrats(); j2++) // 2nd column counter
							{
								profile = unhash(m);
							
								/* Comparing P_x's strategies with each other, keeping P_x's strategy
								the same, so we vary over P_x's strategies */
								profile.at(x) = 0; // at start of section
								while (profile.at(x) < players.at(x)->getNumStrats()) // going through each matrix in section
								{
									if (profile.at(x) != s) // skipping s
									{
										curList = payoffMatrix.at(hash(profile)).at(i2).at(j2);
										if (!oneIsLess && curList->getNodeValue(x) < sList->getNodeValue(x)) // checks if one is < than s
											oneIsLess = true;
									}
									profile.at(x)++; // move to next matrix in section
								}
							}
						}
						profile.at(x)--; // will be exactly numStrats at end, so decrement
						em = hash(profile); // at last matrix in section
						if (x > 2 && product == 1)
						{
							for (int y = 2; y <= x - 1; y++)
								product *= players.at(y)->getNumStrats();
						}
						em += product; // move to the next one, which is the first in the next section
					}
				}
			
			sProfile.at(x)--; // will be exactly numStrats at end, so decrement
			m = hash(sProfile); // at last matrix in section
			if (x > 2 && product == 1)
			{
				for (int y = 2; y <= x - 1; y++)
					product *= players.at(y)->getNumStrats();
			}
			m += product; // move to the next one, which is the first in the next section
		}
	}
	if (!oneIsLess)
	{
		cout << "\nNOTE: this game contains 2 equivalent strategies.\n";
		return false;
	}
	return true;
}

// checks if s is weakly dominated
/* B is weakly dominated by A for P_1
          A      |       B      |       C  
A | [2,1], [0,1] | [1,1], [0,1] | [1,1], [0,1] <--
B | [1,0], [0,1] | [1,1], [0,1] | [1,1], [0,1] <--
C | [1,0], [0,1] | [1,1], [0,1] | [1,1], [0,1]
*/
/*****************************************************************************
everything is a best response
at least one payoff is better
the rest are at greater than or equal to the highest payoff for that strategy
*****************************************************************************/
template <typename T>
bool simGame<T>::isWeaklyDominated(int x, int s)
{
	LinkedList<T>* curList;
	LinkedList<T>* sList;
	bool oneIsGreater = false;
	
	if (x == 0)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
			for (int i = 0; i < players.at(x)->getNumStrats(); i++)
			{
				if (i != s)
				{
					for (int j = 0; j < players.at(1)->getNumStrats(); j++)
					{
						curList = payoffMatrix.at(m).at(i).at(j);
						sList = payoffMatrix.at(m).at(s).at(j);
						if (!sList->getNodeBestResponse(x))
							return false;
						if (curList->getNodeValue(x) > sList->getNodeValue(x))
							oneIsGreater = true;
					}
				}
			}
		
	}
	else if (x == 1)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
			for (int i = 0; i < players.at(0)->getNumStrats(); i++)
			{
				// check BR's and compare strat s in that row with all other values in that row
				for (int j = 0; j < players.at(x)->getNumStrats(); j++)
				{
					if (j != s)
					{
						curList = payoffMatrix.at(m).at(i).at(j);
						sList = payoffMatrix.at(m).at(i).at(s);
						if (!sList->getNodeBestResponse(x))
							return false;
						if (curList->getNodeValue(x) > sList->getNodeValue(x))
							oneIsGreater = true;
					}
				}
			}
		
	}
	else // x > 1
	{
		// NEED A SECTION, ROW, AND COLUMN COUNTER FOR s AND A SECTION, ROW, AND COLUMN COUNTER TO RUN THROUGH OUTCOMES NOT IN S
		int em = 0, m = 0, product = 1;
		vector<int> profile = vector<int>(numPlayers);
		vector<int> sProfile = vector<int>(numPlayers);
		while ((unsigned)m < payoffMatrix.size()) // selects s in each section
		{
			for (int i = 0; i < players.at(0)->getNumStrats(); i++) // row in s
				for (int j = 0; j < players.at(1)->getNumStrats(); j++) // column in s
				{
					sProfile = unhash(m);
					sProfile.at(x) = s;
					
					em = 0;
					while ((unsigned) em < payoffMatrix.size()) // 2nd section counter
					{
						for (int i2 = 0; i2 < players.at(0)->getNumStrats(); i2++) // 2nd row counter
						{
							for (int j2 = 0; j2 < players.at(1)->getNumStrats(); j2++) // 2nd column counter
							{
								profile = unhash(m);
							
								/* Comparing P_x's strategies with each other, keeping P_x's strategy
								the same, so we vary over P_x's strategies */
								profile.at(x) = 0; // at start of section
								while (profile.at(x) < players.at(x)->getNumStrats()) // going through each matrix in section
								{
									if (profile.at(x) != s) // skipping s
									{
										curList = payoffMatrix.at(hash(profile)).at(i2).at(j2);
										if (!curList->getNodeBestResponse(x))
											return false;
									}
									profile.at(x)++; // move to next matrix in section
								}
							}
						}
						profile.at(x)--; // will be exactly numStrats at end, so decrement
						em = hash(profile); // at last matrix in section
						if (x > 2 && product == 1)
						{
							for (int y = 2; y <= x - 1; y++)
								product *= players.at(y)->getNumStrats();
						}
						em += product; // move to the next one, which is the first in the next section
					}
				}
			
			sProfile.at(x)--; // will be exactly numStrats at end, so decrement
			m = hash(sProfile); // at last matrix in section
			if (x > 2 && product == 1)
			{
				for (int y = 2; y <= x - 1; y++)
					product *= players.at(y)->getNumStrats();
			}
			m += product; // move to the next one, which is the first in the next section
		}
	}
	if (!oneIsGreater)
	{
		cout << "\nNOTE: this game contains 2 equivalent strategies.\n";
		return false;
	}
	return true;
}

// returns the maximum payoff in a specific row, column, or section of matrices. In the third case, it is comparing the values for the same ij-entry of each matrix in the section
template <typename T>
int simGame<T>::maxPayoffInRowColOrMatrices(int x, vector<int> choices)
{	
	int maxVal = -std::numeric_limits<int>::max();
	LinkedList<T>* curList;
	
	if (x == 0) // row
	{
		for (int i = 0; i < players.at(0)->getNumStrats(); i++)
		{
			curList = payoffMatrix.at(hash(choices)).at(i).at(choices.at(1));
			if (curList->getNodeValue(0) > maxVal) // curList->getNodeBestResponse(0) && 
				maxVal = curList->getNodeValue(0);
		}
	}
	else if (x == 1) // col
	{
		for (int j = 0; j < players.at(1)->getNumStrats(); j++)
		{
			curList = payoffMatrix.at(hash(choices)).at(choices.at(0)).at(j);
			if (curList->getNodeValue(1) > maxVal) // curList->getNodeBestResponse(1) && 
				maxVal = curList->getNodeValue(1);
		}
	}
	else // set of matrices
	{
		vector<int> profile = vector<int>(numPlayers); // for hashing/unhashing m
		
		profile = choices;
		profile.at(x) = 0;
		while (profile.at(x) < players.at(x)->getNumStrats())
		{
			curList = payoffMatrix.at(hash(choices)).at(choices.at(0)).at(choices.at(1));
			if (curList->getNodeValue(x) > maxVal) // maxVal is in the same section as curList->getNodeValue(x), so if true ---> curList->getNodeValue(x) is a best response anyways
				maxVal = curList->getNodeValue(x);
			
			profile.at(x)++;
		}
	}
	return maxVal;
}

// finds the max strat in a row, col, or matrix based on a set of other predetermined choices
template <typename T>
int simGame<T>::maxStratInRowColOrMatrices(int x, vector<int> choices)
{	
	bool firstMaxFound = false;
	int maxStrat = -std::numeric_limits<int>::max();
	LinkedList<T>* curList;
	if (x == 0) // row
	{
		for (int i = 0; i < players.at(0)->getNumStrats(); i++)
		{
			curList = payoffMatrix.at(hash(choices)).at(i).at(choices.at(1));
			choices.at(x) = i;
			if (!firstMaxFound && curList->getNodeValue(x) == maxPayoffInRowColOrMatrices(x, choices))
			{
				maxStrat = i;
				firstMaxFound = true;
			}
		}
	}
	else if (x == 1) // col
	{		
		for (int j = 0; j < players.at(1)->getNumStrats(); j++)
		{
			curList = payoffMatrix.at(hash(choices)).at(choices.at(0)).at(j);
			choices.at(x) = j;			
			if (!firstMaxFound && curList->getNodeValue(x) == maxPayoffInRowColOrMatrices(x, choices))
			{
				maxStrat = j;
				firstMaxFound = true;
			}
		}
	}
	else // section of matrices
	{		
		vector<int> profile = vector<int>(numPlayers);

		profile = choices;
		profile.at(x) = 0;		
		while (profile.at(x) < players.at(x)->getNumStrats())
		{
			curList = payoffMatrix.at(hash(profile)).at(profile.at(0)).at(profile.at(1));
			if (!firstMaxFound && curList->getNodeValue(x) == maxPayoffInRowColOrMatrices(x, choices))
			{
				maxStrat = profile.at(x);
				firstMaxFound = true;
			}
			profile.at(x)++;
		}
	}
	return maxStrat;
}

// returns the strategy that gives P_x's maximum payoff over all outcomes
template <typename T>
int simGame<T>::maxStrat(int x)
{
	
	int maxStrat = 0, maxVal = -std::numeric_limits<int>::max();
	LinkedList<T>* curList;
	
	if (x == 0)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
			for (int i = 0; i < players.at(0)->getNumStrats(); i++)
				for (int j = 0; j < players.at(1)->getNumStrats(); j++)
				{
					curList = payoffMatrix.at(m).at(i).at(j);
					if (curList->getNodeValue(0) > maxVal)
					{
						maxVal = curList->getNodeValue(0);
						maxStrat = i;
					}
				}
	}
	else if (x == 1)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
			for (int i = 0; i < players.at(0)->getNumStrats(); i++)
				for (int j = 0; j < players.at(1)->getNumStrats(); j++)
				{
					curList = payoffMatrix.at(m).at(i).at(j);
					if (curList->getNodeValue(1) > maxVal)
					{
						maxVal = curList->getNodeValue(1);
						maxStrat = j;
					}
				}
	}
	else
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
			for (int i = 0; i < players.at(0)->getNumStrats(); i++)
				for (int j = 0; j < players.at(1)->getNumStrats(); j++)
				{					
					if (!payoffMatrix.at(m).at(i).at(j))
						cout << "\t\tNOT\n";
					
					curList = payoffMatrix.at(m).at(i).at(j);
					if (curList->getNodeValue(x) > maxVal)
					{
						maxVal = curList->getNodeValue(x);
						maxStrat = unhash(m).at(x);
					}
				}
	}
	return maxStrat;
}

// checks if strategy is Pareto-optimal
template <typename T>
bool simGame<T>::PO(vector<int> stratProfile)
{
	LinkedList<T>* curList;
	LinkedList<T>* profile = payoffMatrix.at(hash(stratProfile)).at(stratProfile.at(0)).at(stratProfile.at(1));
	// (-->)
	bool onePlayerWorseOff = true;
	// (<--)
	// bool onePlayerBetterOff = true;
	// int count = 0;
	// (-->)
	vector<vector<int> > betterOutcomes;
	vector<int> betterOffPlayers;
	vector<bool> worseOff;
	// (<--)
	vector<vector<int> > worseOutcomes;
	vector<int> worseOffPlayers;
	vector<bool> betterOff;
	
	// PO := (fa o \ prof)[(ex x)Better(x, o) <--> (ex y)Worse(y, o)]
	
	/********************************************************************
	PO := (fa o \ prof)[(ex x)Better(x, o) --> (ex y)Worse(y, o)]
	   := (fa o \ prof)[(ex x)WorseOrSame(x, o) || (ex y)Worse(y, o)]
	
	!PO := (ex o \ prof)[(ex x)Better(x, o) && (ex y)BetterOrSame(y, o)]
	*********************************************************************/
	
	/*
	determine if B) any players are better off && W) if any are worse off at outcomes other than stratProfile
		*** could do each b/off w/off case individually ***
		
		1) if B && W: 
		
			determine if at least one other player is worse off at each outcome found
				if: true for one outcome in each better payoff initially found   -if they're worse off for one player, they're worse off for all
					return true;
				else: there exists an outcome for which at least one player is not worse off
					return false;
					
			determine if at least one other player is better off at each outcome found
				if: true for at least one outcome in each worse payoff initially found   -if they're better off for one player, they're better off for all
					return true;
				else: there exists an outcome for which a player is not better off
					return false;
					
		2) if !B && (W || !W): no player is better off, stratProfile is best option, which is Pareto-optimal
			return true;
			
		3) if B && !W: no player is worse off, stratProfile is worst option
			return false;
	
		// OLD
		if: determine if at least one other player is worse off at each outcome found
				if: true for all outcomes found initially, return true;
				else: there exists an outcome for which a player is not worse off, return false;
				
		else: no player is better off, stratProfile is best option
			return true;
	*/
	
	// cout << "PROFILE: (" << profile->value << ", " << profile->next->value << ")\n";
	
	// (-->)
	// determine if a player is better or worse off at outcomes other than stratProfile	
	vector<int> comparing = vector<int>(numPlayers);
	for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
	{
		comparing = unhash(m);
		for (int i = 0; i < players.at(0)->getNumStrats(); i++)
		{
			comparing.at(0) = i;
			for (int j = 0; j < players.at(1)->getNumStrats(); j++)
			{				
				comparing.at(1) = j;
				if (comparing != stratProfile) // move to next payoff in matrix m if same as stratProfile
				{
					// cout << "\n\t\ti: " << i << endl;
					// cout << "\t\tj: " << j << endl;
					
					bool foundOneBetter = false;
					bool foundOneWorse = false;
					int x = 0;
					while ((!foundOneBetter || !foundOneWorse) && x < numPlayers)
					{
						// cout << "\t\t\tx: " << x << endl;
						curList = payoffMatrix.at(m).at(i).at(j);
						profile = payoffMatrix.at(hash(stratProfile)).at(stratProfile.at(0)).at(stratProfile.at(1));
						/*
						count = 0;
						while (count < x)
						{
							curNode = curNode->next;
							profile = profile->next;
							count++;
						}
						*/
						
						// cout << "\t\t\tprofile: " << profile->value << endl;						
						// cout << "\t\t\tcurNode: " << curNode->value << endl;						
						if (profile->getNodeValue(x) < curList->getNodeValue(x)) // P_x is better off at curNode
						{
							// cout << "\t\t\t\tbetter at curNode";
							
							foundOneBetter = true;
							betterOffPlayers.push_back(x);
							betterOutcomes.push_back(unhash(m)); // first two are -1
								betterOutcomes.at(betterOutcomes.size() - 1).at(0) = i;
								betterOutcomes.at(betterOutcomes.size() - 1).at(1) = j;
							worseOff.push_back(false); // for checking later
						}
						else if (profile->getNodeValue(x) > curList->getNodeValue(x)) // P_x is worse off at curNode
						{
							// cout << "\t\t\t\tworse at curNode";
							
							foundOneWorse = true;
							worseOffPlayers.push_back(x);
							worseOutcomes.push_back(unhash(m)); // first two are -1
								worseOutcomes.at(worseOutcomes.size() - 1).at(0) = i;
								worseOutcomes.at(worseOutcomes.size() - 1).at(1) = j;
							betterOff.push_back(false); // for checking later
						}
						x++;
					}
				}
			}
		}
	}
	
	
	
	if (betterOutcomes.size() > 0) // determine if at least one other player is worse off at each outcome found
	{
		// cout << "\t\t\t\tB: " << betterOutcomes.size() << endl;
		// 1) B && !W
		if (worseOutcomes.size() <= 0)
		{
			// cout << "\t\t\t\tfalse 1\n";
			return false;
		}
		
		int n = 0;
		while ((unsigned)n < worseOff.size() && !worseOff.at(n)) // for comparing the other players, not
		{			
			for (int x = 0; x < numPlayers; x++)
			{
				if (betterOffPlayers.at(n) != x) // possibly incorrect, but doesn't matter if it checks the same player bc that player is already better off
				{
					curList = payoffMatrix.at(hash(betterOutcomes.at(n))).at(betterOutcomes.at(n).at(0)).at(betterOutcomes.at(n).at(1));
					profile = payoffMatrix.at(hash(stratProfile)).at(stratProfile.at(0)).at(stratProfile.at(1));
					/*
					count = 0;
					while (count < x)
					{
						curNode = curNode->next;
						profile = profile->next;
						count++;
					}
					*/
					if (curList->getNodeValue(x) < profile->getNodeValue(x))
						worseOff.at(n) = true;
				}
			}
			n++;
		}
		n = 0;
		while ((unsigned)n < worseOff.size() && onePlayerWorseOff)
		{
			if (!worseOff.at(n))
			{
				// cout << "false 2\n";
				onePlayerWorseOff = false;
			}
			n++;
		}
		
		if (onePlayerWorseOff) // true for all outcomes initially placed in betterOutcomes
			return true;
		else // there exists an outcome for which no player is worse off
			return false;
	}
	else // betterOutcomes.size() <= 0	!B && (W || !W)
	{
		// cout << "BEST OUTCOME\n";
		return true;
	}
}

// print k-matrix
template <typename T>
void simGame<T>::printKMatrix()
{
	char save = '\n';
	LinkedList<T>* curList;
	vector<int> curEntry;
	vector<int> temp; // used to fill kOutcomes
	bool inOutcomes = false;
	int index = 0;
	double num = -1, probability = -1.0, sum = 0.0;
	vector<double> EU(numPlayers, 0.0);
	
	computePureEquilibria();
	kOutcomes.clear();
	outcomeProbabilities.clear();
	
	computePureEquilibria(); // calls computeBestResponses()
	determineType();
	isMixed(); // needs pureEquilibria() and determineType()
	if (mixed)
	{
		cout << "\nERROR: mixed k-rationalizability has not been implemented\n";
		return;
	}
	computeKStrategies(); // what players do at each rationality level
	
	cout << "Enter the probability that a player will be a given level of rationality.\n";
	for (int r = 0; r < 3; r++)
	{
		cout << "P(L_" << r << "): ";
		cin >> num;
		validateDouble(num, 0, 1);
		sum += num;
		setRationalityProbability(r, num);
	}
	cout << "P(L_3) = 1 - " << sum << " = " << 1 - sum;
	
	setRationalityProbability(3, 1 - sum);
	
	printPayoffMatrixSansInfo();
	
	// printing k-matrix
	vector<int> rationalityProfile = vector<int>(numPlayers); // for labelling each matrix
	for (int m = 0; (unsigned)m < kMatrix.size(); m++)
	{		
		for (int r1 = 0; r1 < 4; r1++) // L_r1 row
			for (int r2 = 0; r2 < 4; r2++) // L_r2 column
			{
				temp.push_back(kStrategies.at(r1).at(0));
				temp.push_back(kStrategies.at(r2).at(1));
				for (int x = 2; x < numPlayers; x++)
					temp.push_back(kStrategies.at(rUnhash(m).at(x)).at(x));
				
				kMatrix.at(m).at(r1).at(r2) = temp;
				
				inOutcomes = false;
				for (int n = 0; n < getSizeKOutcomes(); n++)
				{
					if (getKOutcome(n) == temp)
						inOutcomes = true;
				}
				if (!inOutcomes)
					pushKOutcome(temp);
				temp.clear();
			}
		
		
		if (numPlayers > 2)
		{			
			rationalityProfile = rUnhash(m);
		
			if (numPlayers == 3)
				cout << "(l_3) = (";
			else if (numPlayers == 4)
				cout << "(l_3, l_4) = (";
			else if (numPlayers == 5)
				cout << "(l_3, l_4, l_5) = (";
			else if (numPlayers == 6)
				cout << "(l_3, l_4, l_5, l_6) = (";
			else
				cout << "(l_3, ..., l_" << numPlayers << ") = (";
			for (int x = 2; x < numPlayers; x++)
			{
				cout << rationalityProfile.at(x) + 1;
				if (x < numPlayers - 1)
					cout << ", ";
			}
			cout << ")\n\n";
		}
		
		cout << "     L_0";
		for (int r2 = 1; r2 < 4; r2++)
			cout << setw(5 * numPlayers) << "L_" << r2;
		cout << endl;
		
		for (int r1 = 0; r1 < 4; r1++) // L_r1 row
		{
			cout << "L_" << r1 << " ";
			for (int r2 = 0; r2 < 4; r2++) // L_r2 column
			{
				curEntry = kMatrix.at(m).at(r1).at(r2);
				cout << "(";
				for (int x = 0; x < numPlayers; x++) // gets the whole n-tuple entry
				{
					cout << "s_" << curEntry.at(x) + 1; // getKStrategy(r1).at(x) + 1 || getKStrategy(r2).at(x) + 1???
					if (x < numPlayers - 1)
						cout << ", ";
				}
				cout << ")";
				if (r2 < 3)
					cout << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	// fill with 0.0
	for (int n = 0; n < getSizeKOutcomes(); n++)
		outcomeProbabilities.push_back(0.0);
	
	for (int r1 = 0; r1 < 4; r1++) // L_r1
		for (int r2 = 0; r2 < 4; r2++) // L_r2
		{
			probability = 0.0;
			
			// find to which outcome the kMatrix entry corresponds
			index = 0;
			while (getKOutcome(index).at(0) != getKStrategy(r1).at(0) || getKOutcome(index).at(1) != getKStrategy(r2).at(1))
				index++;
			
			probability += getRationalityProbability(r1) * getRationalityProbability(r2); // adding P(L_r1, L_r2)
			
			setOutcomeProbability(index, getOutcomeProbability(index) + probability);
		}
	
	vector<int> choices = vector<int>(numPlayers);
	for (int x = 0; x < numPlayers; x++)
	{
		choices.at(x) = kStrategies.at(players.at(x)->getRationality()).at(x);
		players.at(x)->setKChoice(choices.at(x));
	}
	
	if (pureEquilibria.size() != 0) // no equilibria ==> can't compute a choice among equilibria
	{
		cout << "Current Outcome: ";
		if (zs)
			cout << "undecided for zero-sum games\n";
		else if (null) // similarly if all outcomes are equilibria
			cout << "undecided for null games\n";
		else
		{
			cout << "(";
			for (int x = 0; x < numPlayers; x++)
			{
				cout << "L_" << players.at(x)->getRationality();
				if (x < numPlayers - 1)
					cout << ", ";
			}
			
			cout << ") -> (";
			for (int x = 0; x < numPlayers; x++)
			{
				cout << "s_" << choices.at(x) + 1;
				if (x < numPlayers - 1)
					cout << ", ";
			}
			
			cout << ") -> ";
			curList = payoffMatrix.at(hash(choices)).at(choices.at(0)).at(choices.at(1));
			curList->displayPayoffs();
			
			cout << "\nPareto-optimal:  ";
			if (PO(choices))
				cout << "yes\n\n";
			else
				cout << "no\n\n";
		}
	}
	else
		cout << "currently undecided for games with no pure equilibria\n";
	
	// printing probabilities
	for (int n = 0; (unsigned)n < kOutcomes.size(); n++)
	{
		cout << "P(";
		for (int x = 0; x < numPlayers; x++)
		{
			cout << "s_" << kOutcomes.at(n).at(x) + 1;
			if (x < numPlayers - 1)
				cout << ", ";
		}
		cout << ") = " << getOutcomeProbability(n) << endl;
	}
	
	// computing expected utilities
	for (int x = 0; x < numPlayers; x++)
	{
		EU.at(x) = 0.0;
		for (int num = 0; (unsigned)num < kOutcomes.size(); num++) // runs through kOutcomes
		{
			if (numPlayers < 3)
				curList = payoffMatrix.at(0).at(getKOutcome(num).at(0)).at(getKOutcome(num).at(1));
			else				
				curList = payoffMatrix.at(hash(getKOutcome(num))).at(getKOutcome(num).at(0)).at(getKOutcome(num).at(1));
			
			EU.at(x) += curList->getNodeValue(x) * getOutcomeProbability(num);
		}
	}
	cout << endl;
	
	for (int x = 0; x < numPlayers; x++)
		cout << "EU_" << x + 1 << " = " << EU.at(x) << endl;
	
	cout << "Save k-rationalizability model as LaTeX? Enter y or n:  ";
	cin >> save;
	validateChar(save);
	if (save == 'y')
		saveKMatrixAsLatex(choices, EU);
}

template <typename T>
void simGame<T>::printKOutcomes()
{
	cout << "PRINTKOUTCOMES\n";
	
	cout << "{";
	for (int a = 0; a < getSizeKOutcomes(); a++)
	{
		cout << "(";
		for (int x = 0; x < 2; x++)
		{
			cout << getKOutcome(a).at(x);
			if (x < 1)
				cout << ", ";
		}
		cout << ")";
		if (a < getSizeKOutcomes() - 1)
			cout << ", ";
	}
	cout << "}\n\n";
}

template <typename T>
void simGame<T>::printKOutcomeProbabilities()
{
	for (int i = 0; i < getSizeKOutcomeProbabilities(); i++)
		cout << getOutcomeProbability(i) << endl;
	cout << endl;
}

template <typename T>
void simGame<T>::printKProbabilities()
{
	cout << endl;
	for (int i = 0; i < 4; i++)
		cout << "L_" << i << ": " << getRationalityProbability(i) << endl;
	cout << endl;
}

template <typename T>
void simGame<T>::printKStrategies()
{
	cout << "    P\n";
	cout << "    ";
	for (int x = 0; x < numPlayers; x++)
		cout << x << " ";
	cout << "\n----------\n";
	for (int r = 0; r < 4; r++)
	{
		cout <<"r " << r << "|";
		for (unsigned int x = 0; x < kStrategies.at(r).size(); x++)
			cout << kStrategies.at(r).at(x) << " ";
		cout << endl;
	}
	cout << endl;
}

// produce a random game with payoffs between 0 and 100
template <typename T>
void simGame<T>::randGame()
{
	bool addMoreOutcomesPast2 = false; // kMatrix
	int nP = -1, nS = -1, oldNumPlayers = -1, oldNumStrats[numPlayers], oldSize = -1;
	LinkedList<T>* curList;
	srand(time(NULL));
	
	oldNumPlayers = numPlayers;
	
	for (int x = 0; x < numPlayers; x++)
		oldNumStrats[x] = players.at(x)->getNumStrats();
	
	oldSize = payoffMatrix.size();
	
	cout << "Enter the number of players from 2 to 4:  ";
	cin >> nP;
	validateNumPlayers(nP);
	numPlayers = nP;
	
	// add new players if there are more and increase the size of kStrategy vectors
	if (oldNumPlayers != numPlayers)
	{
		if (oldNumPlayers < numPlayers)
			addMoreOutcomesPast2 = true;
		
		for (int i = oldNumPlayers; i < numPlayers; i++)
		{
			Player* p = new Player(numPlayers, i);
			players.push_back(p);
		}
	}
	
	for (int x = 0; x < numPlayers; x++)
	{
		if (x < 2)
		{
			cout << "Enter the number of strategies from 2 to 5 for P_" << x + 1  << ":  ";
			cin >> nS;
			validateNumStrats(nS, 5);
			players.at(x)->setNumStrats(nS);
		}
		else
		{	
			cout << "Enter the number of strategies from 2 to 3 for P_" << x + 1  << ":  ";
			cin >> nS;
			validateNumStrats(nS, 3);
			players.at(x)->setNumStrats(nS);
		}		
		players.at(x)->setRationality(rand() % 4);
	}
	cout << endl;
	
	// resizing payoffMatrix and kMatrix
	if (oldNumPlayers != numPlayers)
	{		
		for (int r = 0; r < 4; r++)
			kStrategies.at(r).resize(numPlayers);
		
		// new matrices need to be inserted in the correct positions, not added at the end
		int size = 1;
		if (numPlayers > 2)
		{
			for (int x = 2; x < numPlayers; x++)
				size *= players.at(x)->getNumStrats();
		}
		payoffMatrix.resize(size);
		
		size = 1;
		if (numPlayers > 2)
			size = pow(4, numPlayers - 2);
		
		kMatrix.resize(size);
	}
	
	// creating/deleting entries and entering random values
	for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
	{
		payoffMatrix.at(m).resize(players.at(0)->getNumStrats());
		for (int i = 0; i < players.at(0)->getNumStrats(); i++)
		{
			payoffMatrix.at(m).at(i).resize(players.at(1)->getNumStrats());
			for (int j = 0; j < players.at(1)->getNumStrats(); j++)
			{						
				// create new list if needed
				if (!payoffMatrix.at(m).at(i).at(j))
				{
					LinkedList<T>* newList = new LinkedList<T>;
					payoffMatrix.at(m).at(i).at(j) = newList;
				}
				curList = payoffMatrix.at(m).at(i).at(j);
				while (curList->getSize() > numPlayers)
					curList->deleteNode(curList->getSize() - 1); // DELETING
				
				for (int x = 0; x < numPlayers; x++)
				{
					if (m < oldSize && x < oldNumPlayers && i < oldNumStrats[0] && j < oldNumStrats[1]) // old matrix, old payoff, old outcome
						curList->setNodeValue(x, rand() % 100);
					else // everything else is new
						curList->appendNode(rand() % 100, false); // ADDING
				}
			}
		}
	}
	
	// resizing kMatrix
	if (addMoreOutcomesPast2)
	{
		for (int m = 0; (unsigned)m < kMatrix.size(); m++)
		{
			kMatrix.at(m).resize(4);
			for(int i = 0; i < 4; i++)
			{
				kMatrix.at(m).at(i).resize(4);
				for(int j = 0; j < 4; j++)
				{
					vector<int> vect(numPlayers, -1);
					kMatrix.at(m).at(i).at(j) = vect;
				}
			}
		}
	}
	printPayoffMatrix();
}

// remove strategy s from player P_x
template <typename T>
void simGame<T>::removeStrategy(int x, int s)
{
	if (x == 0)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
			payoffMatrix.at(m).erase(payoffMatrix.at(m).begin() + s);
	}
	else if (x == 1)
	{
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
		{
			for(int i = 0; i < players.at(0)->getNumStrats(); i++)
				payoffMatrix.at(m).at(i).erase(payoffMatrix.at(m).at(i).begin() + s);
		}
	}
	else // x > 1
	{
		int numErased = 0;
		int product = 1;
		int m = 0;
		vector<int> end = vector<int>(numPlayers);
		for (int y = 0; y < numPlayers; y++)
		{
			if (y != x)
				end.at(y) = players.at(y)->getNumStrats();
			else
				end.at(y) = s;
		}
		
		vector<int> profile = vector<int>(numPlayers);
		while (m < hash(end))
		{
			profile = unhash(m);
			profile.at(x) = s; // at start of section
			int num = 1;
			if (x < numPlayers - 1)
			{
				for (int y = 2; y < numPlayers; y++)
				{
					if (y != x)
						num *= players.at(y)->getNumStrats();
				}
			}
			else if (x == numPlayers - 1 && numPlayers > 3)
				num = players.at(x)->getNumStrats();
			while (numErased < num)
			{
				payoffMatrix.erase(payoffMatrix.begin() + hash(profile));
				numErased++;
				
				// last player's matrices are all lined up; others' must be found
				if (x < numPlayers - 1)
				{
					cout << endl;
					if (profile.at(2) > 0) // simply decrement first number
						profile.at(2)--;
					else // go through each succeeding number
					{
						int y = 2;
						bool foundNonzero = false;
						do 
						{							
							profile.at(y) = players.at(y)->getNumStrats() - 1;
							// not last number and next number is nonzero
							if (y != numPlayers - 1 && profile.at(y + 1) != 0)
							{
								profile.at(y + 1)--;
								foundNonzero = true;
							}
							// not last number and next number is 0
							else if (y != numPlayers - 1 && profile.at(y + 1) == 0)
								profile.at(y) = players.at(y)->getNumStrats() - 1;
							else if (y == numPlayers - 1) // at last number
								profile.at(y)--;
							y++; // move to next number
							
							/* stop when arrive at a number > 0 
							or when we get to the last number */
						} while (y < numPlayers && profile.at(y) == 0 && !foundNonzero);
					}
					
					bool incremented = false;
					int y = 2;
					while (!incremented && y < numPlayers)
					{
						if (y != x)
						{
							if (profile.at(y) != players.at(y)->getNumStrats() - 1)
							{
								profile.at(y)++;
								incremented = true;
							}
						}
						y++;
					}
				}
			}
			if (x > 2 && x < numPlayers - 1 && product == 1)
			{
				for (int y = 2; y <= x - 1; y++)
					product *= players.at(y)->getNumStrats();
			}
			m += product; // move to the next one, which is the first in the next section
		}
	}
	players.at(x)->setNumStrats(players.at(x)->getNumStrats() - 1);
	
	if (impartial)
		impartial = false;
}

// converts a sequence of strategies into the index in a stack of payoff arrays that correspond to that sequence
template <typename T>
int simGame<T>::rHash(vector<int> rationalityProfile)
{	
	// sum_{i = 2}^{nP} maxR^{i - 1} * r_i
	int num = 0, product = 0;
	for (int i = 2; (unsigned)i < rationalityProfile.size(); i++)
	{
		product = 1;		
		product = pow(4, i - 1);
		num += product * rationalityProfile.at(i);
	}
	return num;
}

// converts an index in a stack of payoff arrays into the sequence of strategies that produce that index
template <typename T>
vector<int> simGame<T>::rUnhash(int matrixIndex)
{
	int rationality = 0, previousValues = 0, product = 1;
	vector<int> rationalityProfile = vector<int>(numPlayers);
	rationalityProfile.at(0) = -1;
	rationalityProfile.at(1) = -1;
	
	product = pow(4, numPlayers - 3);
	
	for (int x = numPlayers - 1; x > 1; x--)
	{
		rationality = 0;
		while (product * rationality + previousValues < matrixIndex && rationality != 4)
			rationality++;
		
		if (product * rationality + previousValues > matrixIndex)
			rationality--;
		
		previousValues += product * rationality;
		rationalityProfile.at(x) = rationality;
		product = product / 4;
	}	
	return rationalityProfile;
}

// save k-matrix to be displayed in LaTeX
template <typename T>
void simGame<T>::saveKMatrixAsLatex(vector<int> choices, vector<double> EU)
{
	int val = -std::numeric_limits<T>::max();
	LinkedList<T>* curList;
	ofstream outfile;
	string filename;
	vector<int> curEntry, rationalityProfile; // for labelling each matrix
	
	cout << "Enter the name of the file (Example: file.txt):  ";
	cin >> filename;
	
	outfile.open(filename.c_str());
	if (!outfile)
		cout << "There was an error opening the file.\n";
	else
	{
		for (int m = 0; (unsigned)m < kMatrix.size(); m++)
		{		
			if (numPlayers > 2)
			{			
				rationalityProfile = rUnhash(m);
				
				outfile << "$";
				if (numPlayers == 3)
					outfile << "(l_3) = (";
				else if (numPlayers == 4)
					outfile << "(l_3, l_4) = (";
				else if (numPlayers == 5)
					outfile << "(l_3, l_4, l_5) = (";
				else if (numPlayers == 6)
					outfile << "(l_3, l_4, l_5, l_6) = (";
				else
					outfile << "(l_3, \\dots, l_" << numPlayers << ") = (";
				for (int x = 2; x < numPlayers; x++)
				{
					outfile << rationalityProfile.at(x) + 1;
					if (x < numPlayers - 1)
						outfile << ", ";
				}
				outfile << ")$\n";
			}
			
			outfile << "\\[\n";
			outfile << "\\kbordermatrix\n";
			outfile << "\t{\n";
			outfile << "\t\t & ";
			for (int r2 = 0; r2 < 4; r2++)
			{
				outfile << "L_" << r2;
				if (r2 < 3)
					outfile << " & ";
			}
			outfile << " \\\\\n";
			
			for (int r1 = 0; r1 < 4; r1++) // L_r1 row
			{
				outfile << "\t\tL_" << r1 << " & ";
				for (int r2 = 0; r2 < 4; r2++) // L_r2 column
				{
					curEntry = kMatrix.at(m).at(r1).at(r2);
					outfile << "(";
					for (int x = 0; x < numPlayers; x++) // gets the whole n-tuple entry
					{
						outfile << "s_" << curEntry.at(x) + 1; // getKStrategy(r1).at(x) + 1 || getKStrategy(r2).at(x) + 1???
						if (x < numPlayers - 1)
							outfile << ", ";
					}
					outfile << ")";
					if (r2 < 3)
						outfile << " & ";
				}
				outfile << " \\\\\n";
			}
			outfile << "\t}\n";
			outfile << "\\]\n";
		}
		
		outfile << "Current Outcome:  $(";
		for (int x = 0; x < numPlayers; x++)
		{
			outfile << "L_" << players.at(x)->getRationality();
			if (x < numPlayers - 1)
				outfile << ", ";
		}
		outfile << ") \\mapsto (";
		for (int x = 0; x < numPlayers; x++)
		{
			outfile << "s_" << choices.at(x) + 1;
			if (x < numPlayers - 1)
				outfile << ", ";
		}
		outfile << ") \\mapsto ";
		curList = payoffMatrix.at(hash(choices)).at(choices.at(0)).at(choices.at(1));
		outfile << "(";
		for (int x = 0; x < numPlayers; x++)
		{
			val = curList->getNodeValue(x);
			if (curList->getNodeBestResponse(x))
			{
				outfile << "\\mathbf{";
				outfile << val;
				outfile << "}";
			}
			else
				outfile << val;
			if (x < numPlayers - 1)
				outfile << ", ";
		}
		outfile << ")$\n";
		
		outfile << "Pareto-optimal:  ";
		if (PO(choices))
			outfile << "yes\n\n";
		else
			outfile << "no\n\n";
		
		// printing probabilities
		outfile << "$";
		for (int r = 0; r < 3; r++)
			outfile << "P(L_" << r << "): " << rationalityProbabilities.at(r) << " \\\\\n";
		for (int n = 0; (unsigned)n < kOutcomes.size(); n++)
		{
			outfile << "P(";
			for (int x = 0; x < numPlayers; x++)
			{
				outfile << "s_" << kOutcomes.at(n).at(x) + 1;
				if (x < numPlayers - 1)
					outfile << ", ";
			}
			outfile << ") = " << getOutcomeProbability(n) << " \\\\\n";
		}		
		for (int x = 0; x < numPlayers; x++)
		{
			outfile << "EU_" << x + 1 << " = " << EU.at(x);
			if (x < numPlayers - 1)
				outfile << " \\\\\n";
		}
		outfile << "$";
		
		cout << "Saved to " << filename << ".\n";
	}
}

// save payoff matrix to be displayed in LaTeX
template <typename T>
void simGame<T>::savePayoffMatrixAsLatex()
{
	LinkedList<T>* curList;
	ofstream outfile;
	string filename;
	vector<int> profile;
	
	cout << "Enter the name of the file (Example: file.txt):  ";
	cin >> filename;
	
	outfile.open(filename.c_str());
	if (!outfile)
		cout << "There was an error opening the file.\n";
	else
	{
		int val = -std::numeric_limits<T>::max();
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
		{
			if (numPlayers > 2)
			{
				if (m == 0)
					outfile << "\\noindent\n";
				profile = unhash(m);
				outfile << "$";
				if (numPlayers == 3)
					outfile << "(c_3) = (";
				else if (numPlayers == 4)
					outfile << "(c_3, c_4) = (";
				else if (numPlayers == 5)
					outfile << "(c_3, c_4, c_5) = (";
				else if (numPlayers == 6)
					outfile << "(c_3, c_4, c_5, c_6) = (";
				else
					outfile << "(c_3, \\dots, c_" << numPlayers << ") = (";
				for (int x = 2; x < numPlayers; x++)
				{
					outfile << profile.at(x) + 1;
					if (x < numPlayers - 1)
						outfile << ", ";
				}
				outfile << ")$\n";
			}
			
			outfile << "\\[\n";
			outfile << "\t\\kbordermatrix\n";
			outfile << "\t{\n";
			outfile << "\t\t";
			// if (numPlayers > 2)
			// {
				// profile = unhash(m);
				// outfile << "(";
				// for (int x = 2; x < numPlayers; x++)
				// {
					// outfile << profile.at(x) + 1;
					// if (x < numPlayers - 1)
						// outfile << ", ";
				// }
				// outfile << ") ";
			// }
			outfile << "& ";
			for (int j = 0; j < players.at(1)->getNumStrats(); j++)
			{
				outfile << "s_" << j + 1;
				if (j < players.at(1)->getNumStrats() - 1)
					outfile << " & ";
			}
			outfile << " \\\\\n";
			for (int i = 0; i < players.at(0)->getNumStrats(); i++)
			{
				outfile << "\t\ts_" << i + 1 << " & ";
				for (int j = 0; j < players.at(1)->getNumStrats(); j++)
				{
					curList = payoffMatrix.at(m).at(i).at(j);
					outfile << "(";
					for (int x = 0; x < numPlayers; x++)
					{
						val = curList->getNodeValue(x);
						if (curList->getNodeBestResponse(x))
						{
							outfile << "\\mathbf{";
							outfile << val;
							outfile << "}";
						}
						else
							outfile << val;
						if (x < numPlayers - 1)
							outfile << ", ";
					}
					outfile << ") ";
					if (j < players.at(1)->getNumStrats() - 1)
						outfile << "& ";
				}
				if (i < players.at(0)->getNumStrats() - 1)
					outfile << "\\\\";
				outfile << endl;
			}
			outfile << "\t}\n";
			outfile << "\\]";
			if ((unsigned)m < payoffMatrix.size() - 1)
				outfile << endl;
		}
		cout << "Saved to " << filename << ".\n";
	}	
}

// converts an index in a stack of payoff arrays into the sequence of strategies that produce that index
template <typename T>
vector<int> simGame<T>::unhash(int m)
{
	int choice = 0;
	int previousValues = 0; // values from players below P_x
	int productNumStrats = 1;
	vector<int> profile = vector<int>(numPlayers); // a vector of zeros of length numPlayers
	profile.at(0) = -1;
	profile.at(1) = -1;
	
	for (int x = 2; x < numPlayers - 1; x++)
		productNumStrats *= players.at(x)->getNumStrats();
	
	for (int x = numPlayers - 1; x > 1; x--)
	{
		choice = 0;
		while (productNumStrats * choice + previousValues < m 
				&& choice != players.at(x)->getNumStrats() - 1)
			choice++;
		
		if (productNumStrats * choice + previousValues > m)
			choice--;
		
		previousValues += productNumStrats * choice;
		profile.at(x) = choice;
		productNumStrats = productNumStrats / players.at(x)->getNumStrats();
	}	
	return profile;
}

#endif