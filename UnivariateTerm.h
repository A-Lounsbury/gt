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

// list nodes (UnivariateTerms) of the form [coefficient, exponent]
struct UnivariateTerm
{
	double coefficient;
	int exponent;
	UnivariateTerm* next;
	
	int getCoefficient()			{ return coefficient; }
	int getExponent() 				{ return exponent; }
	void setCoefficient(int c)		{ coefficient = c; }
	void setExponent(int e)			{ exponent = e; }
	void setNext(UnivariateTerm* u)	{ this->next = u; }

	void printTerm()
	{
		cout << coefficient << "^" << exponent;
	}
};

#endif