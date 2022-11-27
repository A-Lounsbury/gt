/*********************************************
Title: seqGame.h
Author: Andrew Lounsbury
Date: 6/7/2020
Purpose: class for sequential game tree nodes
*********************************************/

#ifndef TREENODE_H
#define TREENODE_H
#include "Player.h"

class TreeNode
{
	private:
		template <typename T>
		struct ListNode // hold payoffs
		{
			T value;
			bool bestResponse; // for comparing root nodes
			ListNode* next;
		};
		int strategy; // for ordering the tree
		int level; // for internal nodes
		int player = level % 2; // for internal nodes
		ListNode<int>* payoff;
		vector<TreeNode*> next; // numStrategies branches coming off the internal nodes
		vector<int> path = vector<int>(level);
	public:
		TreeNode()
		{
			this->strategy = 0;
			this->level = 0;
			this->player = level % 2;
			this->payoff = new ListNode<int>;
			this->payoff = NULL;
			
			this->next = vector<TreeNode*>(1);
			
			// next = vector<TreeNode*>(players[player]->getNumStrategies());
			// for (int i = 0; i < players[player]->getNumStrategies(); i++)
				// next.at(i) = NULL;
			
			for (int i = 0; i < level; i++)
				path.at(i) = -1;
		}
		
		TreeNode(int s, ListNode<int>* pO, vector<TreeNode*> n, vector<int> p)
		{
			this->strategy = s;
			this->level = p.size();
			this->player = p.size() % 2;
			this->payoff = pO;
			this->next = n;
			this->path = p;
		}
		
		TreeNode(vector<int> p)
		{
			this->strategy = 0;
			this->level = 0;
			this->player = level % 2;
			this->payoff = new ListNode<int>;
			this->payoff = NULL;
			
			this->next = vector<TreeNode*>(1);
			
			// next = vector<TreeNode*>(players[player]->getNumStrategies());
			// for (int i = 0; i < players[player]->getNumStrategies(); i++)
				// next.at(i) = NULL;
			
			this->path = p;
		}
		
		~TreeNode()
		{ cout << "\nDeleted a node."; }
		
		void addNext()
		{ next.push_back(NULL); }
		
		int getLevel()
		{ return this->level; }
		
		TreeNode* getNext(int i)
		{ return next.at(i); }
		
		vector<int> getPath()
		{ return path; }
		
		int getPathVertex(int i)
		{ return path.at(i); }
		
		ListNode<int>* getPayoff()
		{ return this->payoff; }
		
		int getNodePlayer()
		{ return player; }
		
		int getSizeNext()
		{ return next.size(); }
		
		int getStrategy()
		{ return strategy; }
		
		void setNext(int i, TreeNode* curNode)
		{ next.at(i) = curNode; }
		
		void setNextPlayer(int i, int index)
		{ next.at(i)->setPlayer(index); }
		
		void setPathVertex(int i, int num)
		{ path.at(i) = num; }
		
		void setPayoff(ListNode<int>* node)
		{ payoff = node; }
		
		void setPath(vector<int> p)
		{ this->path = p; }
		
		void setPlayer(int num)
		{ player = num; }
		
		void setStrategy(int num)
		{ strategy = num; }
};

#endif