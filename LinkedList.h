/**************************************************
Title: LinkedList.h
Author: Andrew Lounsbury
Date: 5/11/2020
Purpose: Linked list class for game theory program
***************************************************/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

// linked list (payoff matrix entry) of the form [payoff, BR] -> ... -> [payoff, BR]
template<typename T>
class LinkedList
{
	private:
		struct ListNode
		{
			T value;
			bool bestResponse;
			ListNode* next;
		};
		ListNode* head;
		ListNode* tail;
		int numNodes;
		
	public:
		LinkedList()
		{
			head = NULL;
			tail = NULL;
			
			numNodes = 0;
		}
		
		bool getHead() { return head; }
		int getSize() { return numNodes; }
		
		~LinkedList();
		void appendNode(T, bool);
		void deleteNode(int);
		void displayList(vector<vector<vector<bool> > >, int, int) const;
		void displayPayoffs() const;
		void displayBRs() const;
		T getNodeValue(int);
		void setNodeValue(int, int);
		bool getNodeBestResponse(int);
		void setNodeBestResponse(int, bool);
		void insertNode(T, int);
		int getPos(string) const;
};

template<typename T>
LinkedList<T>::~LinkedList()
{
	ListNode* curNode;
	ListNode* nextNode; // move to succeeding node after delete each curNode
	
	curNode = head;
	
	while(curNode) // while not at end
	{
		nextNode = curNode->next; // keep track of node after curNode being deleted
		delete curNode;
		curNode = nextNode; // move to the next node
	}
}

// append node to tail of list
template<typename T>
void LinkedList<T>::appendNode(T nodeValue, bool br)
{
	// cout << "APPENDNODE\n";
	
	ListNode* newNode = new ListNode;
	newNode->value = nodeValue;
	newNode->bestResponse = br;
	newNode->next = NULL;
	
	if (!head) // list empty
	{		
		head = newNode; // newNode becomes head
		tail = newNode; // and tail
	}
	else // list not empty
	{		
		tail->next = newNode; // tail's next points to newNode; i.e., newNode succeeds tail
		tail = newNode; // newNode is now the tail
	}
	numNodes++;
}

// delete specific node from list
template<typename T>
void LinkedList<T>::deleteNode(int position)
{	
	if (!head)
		return;
	
	ListNode* curNode;
	ListNode* previousNode;
	int counter = 0;
	
	if (position == 0)
	{
		curNode = head->next;
		delete head;
		head = curNode;
	}
	else
	{
		curNode = head;
		while (counter < position)
		{
			previousNode = curNode;
			curNode = curNode->next;
			counter++;
		} // now curNode is the node to be deleted
		
		if (curNode)
		{
			if(curNode == tail)
				tail = previousNode;
			
			previousNode->next = curNode->next;
			delete curNode;
		}
	}
	numNodes--;
}

// print BR's as n-tuple
template<typename T>
void LinkedList<T>::displayBRs() const
{
	ListNode* curNode;
	
	if (!head)
		cout << "The list is empty.\n\n";
	else
	{
		curNode = head;
		
		cout << "(";
		while (curNode)
		{
			if (curNode->bestResponse)
			{
				cout << "1";
				if (curNode->next)
					cout << ", ";
			}
			else if (!curNode->bestResponse)
			{
				cout << "0";
				if (curNode->next)
					cout << ", ";
			}
			curNode = curNode->next;
		}
		cout << ")";
	}
}

// print payoffs and BR's as n-tuple
template<typename T>
void LinkedList<T>::displayList(vector<vector<vector<bool> > > extraSpaces, int m, int j) const // FINISH: spacing for bracketed br notation
{
	int x = 0;
	ListNode* curNode;
	
	if (!head)
		cout << "The list is empty.\n\n";
	else
	{
		curNode = head;
		
		cout << "(";
		while (curNode)
		{
			if (curNode->bestResponse)
			{
				cout << "[" << curNode->value << ", 1]";
				// cout << "[" << curNode->value << "]";
			}
			else if (!curNode->bestResponse)
			{
				// adding extra spacing	
				// if (extraSpaces.at(m).at(j).at(x))
					// cout << " ";
				
				cout << "[" << curNode->value << ", 0]";
				// cout << curNode->value;
			}
			if (curNode->next)
					cout << "-";
			// if (curNode->next)
			// {
				// if (!curNode->bestResponse && extraSpaces.at(m).at(j).at(x))
					// cout << " ";
				
				// cout << ", ";
			// }
			// else
			// {
				// if (!curNode->bestResponse)
					// cout << " ";
			// }
			curNode = curNode->next;
			x++;
		}
		cout << ")";
	}
}

// print payoffs as n-tuple
template<typename T>
void LinkedList<T>::displayPayoffs() const
{
	ListNode* curNode;
	
	if (!head)
		cout << "The list is empty.\n\n";
	else
	{
		curNode = head;
		
		cout << "(";
		while (curNode)
		{
			cout << curNode->value;
			if (curNode->next)
				cout << ", ";
			curNode = curNode->next;
		}
		cout << ")";
	}
}

// get node value
template<typename T>
T LinkedList<T>::getNodeValue(int position)
{
	ListNode* curNode;
	if (!head)
	{
		cout << "\t\tERROR (getN 1): list empty\n";
		return -std::numeric_limits<int>::max();
	}
	else
	{
		if (position == 0) // value at head
			return head->value;
		
		curNode = head; // start at beginning of list
		int curPosition = 0;
		while (curPosition <= position && curNode) // find position of value, return
		{
			if (position == curPosition) // found
				return curNode->value;
			curPosition++;
			curNode = curNode->next;
		}
	}
	cout << "\t\tERROR (getN 2): node " << position << " not found\n";
	return -std::numeric_limits<int>::max();
}

// get node BR
template<typename T>
bool LinkedList<T>::getNodeBestResponse(int position)
{
	ListNode* curNode;
	if (!head)
	{
		cout << "ERROR (getBR 1): list empty\n";
		return false;
	}
	else
	{
		if (position == 0) // value at head
			return head->bestResponse;
		
		curNode = head; // start at beginning of list
		int curPosition = 0;
		
		while (position >= curPosition && curNode) // find position of value, return
		{
			if (position == curPosition) // found
				return curNode->bestResponse;
			
			curPosition++;
			curNode = curNode->next;
		}
	}
	cout << "ERROR (getBR 2): best response not found\n";
	return false;
}

// returns the position of a payoff in the list
template<typename T>
int LinkedList<T>::getPos(string name) const
{
	ListNode* curNode;
	int pos;
	
	curNode = head; // start at beginning
	pos = 0;
	
	while (curNode)
	{
		if (curNode->value.getName() == name)
			return pos; // found
		
		pos++;
		curNode = curNode->next;
	}
	return -1; // not found
}

// insert a node at position
template<typename T>
void LinkedList<T>::insertNode(T nodeValue, int position)
{
	ListNode* curNode;
	ListNode* newNode = new ListNode;
	ListNode* prev;
	
	newNode->value = nodeValue;
	newNode->next = NULL;
	numNodes++;
	
	if (!head) // list empty
	{
		if (position != 0)
			cout << "\n\nUnable to insert a node at position " << position << " because there are no nodes in the list. Inserting at position 1.\n\n";
		
		head = newNode;
		tail = newNode;
	}
	else // list not empty
	{
		curNode = head;
		int count = 0;
		if (position == 0) // insert at head if needed
		{
			newNode->next = head->next;
			head = newNode;
			return;
		}
		else
		{
			while (curNode != tail && count < position)
			{
				count++;
				if (count == position)
					break;
				curNode = curNode->next;
			}
			
			// curNode is positioned 1 node BEFORE the node we want to insert
			if(curNode->next == NULL) //we are appending this node to the end
				tail = newNode;
				
			newNode->next = curNode->next;
			curNode->next = newNode;
		}
	}
}

// set node BR
template<typename T>
void LinkedList<T>::setNodeBestResponse(int position, bool val)
{
	// cout << "\tSETNODEBESTRESPONSE\n";
	ListNode* curNode;
	if (!head)
	{
		cout << "\t\tERROR (setBR 1): list empty\n";
		return;
	}
	else
	{
		if (position == 0) // BR at head
			head->bestResponse = val;
		
		curNode = head; // start at beginning of list
		int curPosition = 0;
		while (position >= curPosition && curNode) // find position of value, return
		{
			if (position == curPosition) // found
			{
				curNode->bestResponse = val;
				return;
			}
			
			curPosition++;
			curNode = curNode->next;
		}
	}
	cout << "\t\tERROR (setBR 2): node " << position << " not found\n";
	return;
}

// set node value
template<typename T>
void LinkedList<T>::setNodeValue(int position, int val)
{
	// cout << "\t\t\tSETNODEVALUE\n";
	
	ListNode* curNode;
	if (!head)
	{
		cout << "\t\t\t\tERROR (setVal 1): list is empty\n";
		return;
	}
	else
	{
		if (position == 0) // value at head
			head->value = val;
		
		curNode = head; // start at beginning of list
		int curPosition = 0;
		while (position >= curPosition && curNode) // find position of value, return
		{
			if (position == curPosition) // found
			{
				curNode->value = val;
				return;
			}
			
			curPosition++;
			curNode = curNode->next;
			
			// if (!curNode)
				// cout << "EXITING\n";
		}
	}
	cout << "\t\t\t\tERROR (setVal 2): node " << position << " not found\n";
	return;
}

#endif