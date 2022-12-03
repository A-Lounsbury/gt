/**********************************************
Title: seqGame.h
Author: Andrew Lounsbury
Date: 6/6/2020
Purpose: class for sequential aspects of games
**********************************************/

#ifndef SEQGAME_H
#define SEQGAME_H
#include "Player.h"
#include "TreeNode.h"

class SeqGame
{
	private:
		TreeNode* root;
		int numNodes;
		int numPlayers;
		vector<Player*> players; // array of pointers to Players
		
		void insert(TreeNode*&, TreeNode* &);
		void destroySubTree(TreeNode*);
		void displayInOrder(TreeNode*) const;
		// void displayPreOrder(TreeNode*) const;
		void displayPostOrder(TreeNode*) const;
	public:
		SeqGame()
		{
			root = new TreeNode;
			root = NULL;
			numNodes = 0;
			numPlayers = 2;
			players = vector<Player*>(numPlayers);
		}
		
		SeqGame(int nP)
		{
			root = new TreeNode;
			root = NULL;
			numNodes = 0;
			numPlayers = nP;
			players = vector<Player*>(numPlayers);
		}
		
		~SeqGame()
		{ destroySubTree(root); }
		
		void displayPreOrder(TreeNode*) const;
		
		Player* getPlayer(int i) const
		{ return players.at(i); }
		
		TreeNode* getRoot()
		{ return root; }
		
		void setRoot(TreeNode* node)
		{ root = node; }
		
		void computePath(TreeNode*);
		int difference(TreeNode*);
		void display(TreeNode* , int);
		int height(TreeNode*);
		void insert(TreeNode*, vector<int>);
		int numNodesPerLevel(int);
		bool search(TreeNode*);
};

void SeqGame::computePath(TreeNode* node) // FINISH
{
	TreeNode* curNode = root;
	vector<TreeNode*> temp = vector<TreeNode*>(node->getLevel() - 1); // tracks nodes on the way to node
	// vector<int> checking;
	
	// curNode at level - 1
	while (curNode->getLevel() < node->getLevel() - 1)
	{
		// keep track of the nodes curNode passes on the way to node
		temp.at(curNode->getLevel()) = curNode;
		
		
		// checking = vector<int>(node->getLevel() - 1);
		// for (int i = 0; i < node->getLevel() - 1; i++)
			// checking.at(i) = node->getLevel();
		
		/*
		will always be the 0-th, 1st, 2nd,... node 
		in the path down to level - i */
		for (int i = 1; i < node->getLevel(); i++) // each level (level - i)
		{
			for (int j = 0; j < players[curNode->getNodePlayer()]->getNumStrats(); j++)
			{
				curNode = curNode->getNext(j);
			}
		}
	}
	
	// players[curNode->getNodePlayer()]->getNumStrats()
	// each strategy in that node in level - i
	for (int j = 0; j < players[curNode->getNodePlayer()]->getNumStrats(); j++)
	{
		if (curNode->getNext(j) == node)
		{
			// if node is found, all nodes recorded in temp are the path for node
			node->setPathVertex(0, 0);
			for (int n = 1; n < curNode->getLevel(); n++)
				node->setPathVertex(n, temp.at(n)->getStrategy());
			
			node->setPathVertex(curNode->getLevel(), j);
			return;
		}
	}
	
	// move up a level to check the next level - 1 node to the right
	curNode = temp.at(curNode->getLevel() - 1);
}

void SeqGame::destroySubTree(TreeNode* curNode)
{
	if (curNode)
	{
		for (int i = 0; i < players[curNode->getNodePlayer()]->getNumStrats(); i++)
		{
			if (curNode->getNext(i) != NULL)
				destroySubTree(curNode = curNode->getNext(i + 1));
		}
		delete curNode;
	}
}

int SeqGame::difference(TreeNode* node)
{
	int size = players[node->getNodePlayer()]->getNumStrats();
	vector<int> heights = vector<int>(size);
	int maxHeight = -1;
	int minHeight = std::numeric_limits<int>::max();
	int diff;
	
	for (int i = 0; i < size; i++)
		heights.at(i) = height(node->getNext(i));
	for (int i = 0; i < size; i++)
	{
		if (heights.at(i) > maxHeight)
			maxHeight = heights.at(i);
		if (heights.at(i) < minHeight)
			minHeight = heights.at(i);
	}
	diff = maxHeight - minHeight;
	return diff;
}

/*
			-1
		0		1
	0	1
	
			1
		2		3
	
d1
	d2

	ed2
	d3
	
	ed3
ed1
*/

void SeqGame::display(TreeNode* node, int level)
{
	int num = rand();
	cout << "\nDISPLAY:  " << num << endl;
	// cout << num << endl;
	
	int i, strat;
	if (node)
	{
		for (strat = 0; strat < node->getSizeNext() - 1; strat++)
		{
			cout << "\nstrat: " << strat << endl;
			
			display(node->getNext(strat), level + 1);
		
			printf("\n");
			
			for (i = 0; i < level && node != root; i++)
				cout << "        ";
			
			if (node == root)
				cout << "P_" << node->getNodePlayer() + 1 << ", s_{" << node->getStrategy() << "}";
			else
				cout << "P_" << node->getNodePlayer() + 1 << ", s_" << node->getStrategy() + 1;
		}
		
		display(node->getNext(node->getSizeNext() - 1), level + 1);
	}
	cout << "   DONE:  " << num << "\n";
}

void SeqGame::displayPreOrder(TreeNode* node) const
{
	cout << "DISPLAYPREORDER\n";
	if (node)
	{
		cout << "P_" << node->getNodePlayer() << ", s_" << node->getStrategy() << "  ";
		cout << node->getPayoff() << endl;
		for (int i = 0; i < players[1 - node->getNodePlayer()]->getNumStrats(); i++)
			displayPreOrder(node->getNext(i));
	}
	
	cout << "END OF DISPLAYPREORDER\n";
}

int SeqGame::height(TreeNode* node) // FINISH
{
	cout << "GETTING HEIGHT\n";
	
	int size = players[node->getNodePlayer()]->getNumStrats();
	vector<int> heights = vector<int>(size);
	int maxHeight = -1;
	int h = 0;
	
	if (node)
	{
		for (int i = 0; i < size; i++)
			heights.at(i) = height(node->getNext(i));
		for (int i = 0; i < size; i++)
		{
			if (heights.at(i) > maxHeight)
				maxHeight = heights.at(i);
		}
		h = maxHeight + 1;
	}
	return h;
}

/*
			-1
		0		1
	0	1
*/

// Copy tree from level l down from previous node in l
// insert new payoffs NLR
void SeqGame::insert(TreeNode* root, vector<int> p) // FINISH
{
	cout << "INSERTING\n";
	
	TreeNode* curNode;
	TreeNode* newNode = new TreeNode;
	newNode->setPath(p);
	
	if (!root)
	{
		setRoot(newNode);
		getRoot()->setStrategy(-1); // all paths start with -1
		cout << "DONE INSERTING\n\n";
		return;
	}
	
	// if (path.size() != (unsigned)height(this->getRoot()))
	// {
		// cout << "This is an invalid node.\n";
		// return;
	// }
	
	curNode = root;
	int lev = 0;
	// follow path to spot before the new spot
	while (curNode && (unsigned)lev < p.size() - 2) // && curNode->getNext(path.at(i))       && curNode->getPath() != path
	{		
		lev++;
		cout << "lev: " << lev << endl;
		cout << "path at " << lev << ": " << p.at(lev) << endl;
		cout << "size: " << curNode->getSizeNext() << endl;
		curNode = curNode->getNext(p.at(lev));
		cout << "test1\n";
	}
	cout << "test2\n";
	curNode->addNext(); // create spot in next, will be the last position
	cout << "test3\n";
	curNode->setNext(curNode->getSizeNext() - 1, newNode);
	curNode->setNextPlayer(curNode->getSizeNext() - 1, 1 - curNode->getNodePlayer());
	cout << "DONE INSERTING\n\n";
}

int SeqGame::numNodesPerLevel(int i)
{
	int num = -1;
	int r = -1;
	
	if (i == 0)
		return 0;
	else if (i % numPlayers == 0)
	{
		for (int x = 0; x < numPlayers; i++)
			num *= pow(players[x]->getNumStrats(), i / numPlayers);
	}
	else if (i % numPlayers > 0)
	{
		r = i % numPlayers;
		for (int x = 0; x < numPlayers; i++)
		{
			if (r > 0)
			{
				num *= pow(players[x]->getNumStrats(), (i / numPlayers) + 1);
				r--;
			}
			else
				num *= pow(players[x]->getNumStrats(), i / numPlayers);
		}
	}
	return num;
}

bool SeqGame::search(TreeNode* item) // FINISH
{
	TreeNode* curNode = root;
	
	while (curNode)
	{
		while (curNode->getLevel() != item->getLevel())
		{
			curNode->getNext(0);
		}
		for (int i = 0; i < players[curNode->getNodePlayer()]->getNumStrats(); i++)
		{
			if (curNode->getStrategy() == item->getStrategy())
				return true;
			else
			{
				cout << "else\n";
				return false;
			}
		}
	}
	return true;
}

#endif