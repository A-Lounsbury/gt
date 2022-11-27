/************************************************
Title: gtMain.cpp
Author: Andrew Lounsbury
Date: 12/25/20
Purpose: toolbar functions for gtApp
*************************************************/

template <typename T>
void simGame<T>::readFromFile()
{
	bool addMoreOutcomesPast2 = false; // kMatrix
	ifstream infile;
	int nP = -1, nS = -1, r = -1;
	int oldNumPlayers = -1, oldNumStrats[numPlayers], oldSize = -1;
	LinkedList<T>* curList;
	string filename;
	
	cout << "Enter the name of the file (Example: file.txt):  ";
	cin >> filename;
	
	infile.open(filename.c_str());
	if (!infile)
		cout << "\nERROR: could not open file\n";
	else
	{
		while (!infile.eof())
		{
			oldNumPlayers = numPlayers;
			
			for (int x = 0; x < numPlayers; x++)
				oldNumStrats[x] = players.at(x)->getNumStrats();
			
			oldSize = payoffMatrix.size();
			
			// reading numPlayers
			infile >> nP;
			setNumPlayers(nP);
			
			// reading numStrats for old players
			if (oldNumPlayers <= numPlayers)
			{
				for (int x = 0; x < oldNumPlayers; x++)
				{
					infile >> nS;
					players.at(x)->setNumStrats(nS);
				}
			}
			else
			{
				for (int x = 0; x < numPlayers; x++)
				{
					infile >> nS;
					players.at(x)->setNumStrats(nS);
				}
			}
			
			/**************************************
			add new players if there are more
			resizing payoffMatrix and kMatrix
			increase the size of kStrategy vectors 
			***************************************/
			if (oldNumPlayers != numPlayers)
			{
				if (oldNumPlayers < numPlayers)
					addMoreOutcomesPast2 = true;
				
				// create new players and read rest of numStrats
				for (int x = oldNumPlayers; x < numPlayers; x++)
				{
					Player* p = new Player(numPlayers, x);
					players.push_back(p);
					
					infile >> nS;
					players.at(x)->setNumStrats(nS);
				}
				
				for (int rat = 0; rat < 4; rat++)
					kStrategies.at(rat).resize(numPlayers);
			}
			// new matrices added at the end
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
		
			for (int x = 0; x < numPlayers; x++)
			{
				infile >> r;
				players.at(x)->setRationality(r);
			}
			kOutcomes.clear();
			outcomeProbabilities.clear();
			
			// creating/deleting entries and reading values	
			int val;
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
						
						// infile.ignore(1,'(');
						// infile >> val;
						// cout << "first: " << val << endl;
						// curList->setNodeValue(0, val);
						for (int x = 0; x < numPlayers; x++)
						{
							// cout << "x: "<< x << endl;
							// infile.ignore(256, ',');
							infile >> val;
							// cout << "\tval: "<< val << endl;
							if (m < oldSize && x < oldNumPlayers 
								&& i < oldNumStrats[0] && j < oldNumStrats[1]) // old matrix, old payoff, old outcome
								curList->setNodeValue(x, val);
							else // everything else is new
								curList->appendNode(val, false); // ADDING
						}
						// infile.ignore(5,'(');
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
		}
		cout << "Done reading from " << filename << endl;
		infile.close();
	}
	
	printPayoffMatrix();
}

template <typename T>
void simGame<T>::savePayoffMatrixAsLatex() // FIX
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

template <typename T>
void simGame<T>::saveToFile()
{
	LinkedList<T>* curList;
	ofstream outfile;
	string filename;
	
	cout << "Enter the name of the file (Example: file.txt):  ";
	cin >> filename;
	
	outfile.open(filename.c_str());
	if (!outfile)
		cout << "There was an error opening the file.\n";
	else
	{
		outfile << numPlayers << endl;
		
		for (int x = 0; x < numPlayers; x++)
		{
			outfile << players.at(x)->getNumStrats();
			if (x < numPlayers - 1)
				outfile << " ";
		}
		outfile << endl;
		
		for (int x = 0; x < numPlayers; x++)
		{
			outfile << players.at(x)->getRationality();
			if (x < numPlayers - 1)
				outfile << " ";
		}
		outfile << endl;
		
		int val = -std::numeric_limits<T>::max();
		for (int m = 0; (unsigned)m < payoffMatrix.size(); m++)
		{
			for (int i = 0; i < players.at(0)->getNumStrats(); i++)
			{
				for (int j = 0; j < players.at(1)->getNumStrats(); j++)
				{
					curList = payoffMatrix.at(m).at(i).at(j);
					for (int x = 0; x < numPlayers; x++)
					{
						val = curList->getNodeValue(x);
						outfile << val;
						if (x < numPlayers - 1)
							outfile << " ";
					}
					if (j < players.at(1)->getNumStrats() - 1)
						outfile << " ";
				}
				if (i < players.at(0)->getNumStrats() - 1)
					outfile << endl;
			}
			if ((unsigned)m < payoffMatrix.size() - 1)
				outfile << endl << endl;
		}
		cout << "Saved to " << filename << ".\n";
	}
}