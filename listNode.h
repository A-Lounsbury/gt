/**********************************************************
Title: listNode.h
Author: Andrew Lounsbury
Date: 5/9/2020
Purpose: struct for linked list entries in payoff matrices
**********************************************************/

#ifndef LISTNODE_H
#define LISTNODE_H

template <typename T>
struct ListNode
{
	T value;
	bool bestResponse;
	ListNode* next;
};

#endif