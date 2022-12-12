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
	int exponents;
	MultivariateTerm* next;
	
	int getCoefficient()                { return coefficient; }
	int getExponent()                   { return exponents; }
	void setCoefficient(int c)          { coefficient = c; }
	void setExponents(int e)            { exponents = e; }
	void setNext(MultivariateTerm* u)   { this->next = u; }
    void printTerm()
	{
		cout << coefficient << "^" << exponents;
	}
};

#endif