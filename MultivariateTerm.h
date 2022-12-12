/*******************************
Title: UnivariateTerm.h
Author: Andrew Lounsbury
Date: 7/5/2020
Purpose: UnivariateTerms in Polynomial.h
********************************/

#ifndef UnivariateTerm_H
#define UnivariateTerm_H

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// list nodes (UnivariateTerms) of the form [coefficient, exponents]
struct MultivariateTerm
{
	double coefficient;
	vector<int> exponents;
	MultivariateTerm* next;
	
	int getCoefficient()                { return coefficient; }
	vector<int> getExponent()           { return exponents; }
	void setCoefficient(int c)          { coefficient = c; }
	void setExponents(vector<int> e)	{ exponents = e; }
	void setNext(MultivariateTerm* u)   { this->next = u; }
    void printTerm()
	{
		cout << "\nPRINTTERM\n";
		cout << "coeff: " << coefficient << endl;
		cout << "exponents: ";
		for (int v = 0; (unsigned)v < exponents.size(); v++)
			cout << exponents.at(v) << " ";
		cout << endl;
		
		if (coefficient != 1)
			cout << "one\n";
		if (exponents.size() > 1)
			cout << "two\n";
		
		if (coefficient != 1 || exponents.size() > 1)
			cout << coefficient;
		
		for (int v = 0; (unsigned)v < exponents.size(); v++)
		{
			cout << "x";
			if (exponents.size() > 1)
				cout << "_" << v;
			if (exponents.size() > 1)
			{
				if (exponents.at(v) != 0)
					cout << "^" << exponents.at(v);
			}
		}
	}
};

#endif