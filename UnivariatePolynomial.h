/**************************
Title: UnivariatePolynomial.h
Author: Andrew Lounsbury
Date: 6/2/2020
Purpose: for holding EU's
**************************/

/***************************************
1) create nT zero terms in nV variables
2) read in coeff and expo for each term
3) remove zero terms
4) add like terms
***************************************/

#ifndef UnivariatePolynomial_H
#define UnivariatePolynomial_H
#include "inputValidation.cpp"
#include "UnivariateTerm.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// UnivariatePolynomials of the form [coefficient, exponents] -> ... -> [coefficient, exponents]
class UnivariatePolynomial
{
	private:
		UnivariateTerm* leading;
		UnivariateTerm* trailing;
		int numTerms;
		int numVariables;
		int totalDegree;
		vector<vector<UnivariatePolynomial*> > derivatives;
		bool linear;
	public:		
		double getCoefficient(int i) const 				            { return getUnivariateTerm(i)->coefficient; }
		vector<vector<UnivariatePolynomial*> > getDerivatives() 	{ return derivatives; }
		int getExponent(int t, int var) const 			            { return getExponents(t).at(var); }
		vector<int> getExponents(int i) const 			            { return this->getUnivariateTerm(i)->exponent; }
		int getNumUnivariateTerms() const 				       		{ return numTerms; }
		int getNumVariables() const 				            	{ return numVariables; }
		int getSizeDerivatives() 					            	{ return derivatives.size(); }
		// with respect to v
		int getSizeDerivativesWRT(int v) 			               	{ return derivatives.at(v).size(); }
		UnivariateTerm* getTrailing() const 						{ return trailing; }
		void setNumUnivariateTerms(int num) 						{ numTerms = num; }
		void setTotalDegree(int num) 					        	{ totalDegree = num; }
		
		UnivariatePolynomial();
		UnivariatePolynomial(int, int, int);
		UnivariatePolynomial(int, int, vector<int>, int);
		~UnivariatePolynomial();
		
		// UnivariatePolynomial operator+(const UnivariatePolynomial &p);
		// UnivariatePolynomial operator+(UnivariatePolynomial &l, UnivariatePolynomial &r);
		UnivariatePolynomial operator*(const UnivariatePolynomial &p);
		UnivariatePolynomial* operator-(const UnivariatePolynomial &p);
		bool operator==(const UnivariatePolynomial &p);
		bool operator!=(const UnivariatePolynomial &p);
		bool operator<(const UnivariatePolynomial &p);
		bool operator>(const UnivariatePolynomial &p);
		
		void addUnivariateTerm(int, vector<int>);
		void addUnivariateTerm(UnivariateTerm*);
		void computeTotalDegree();
		UnivariatePolynomial* derivative(int);
		void enterInfo();
		double eval(double);
		UnivariatePolynomial* getDerivative(int, int);
		int getNonZeroExpo(int) const;
		UnivariateTerm* getUnivariateTerm(int) const;
		void insertUnivariateTerm(int, vector<int>, int);
		void insertUnivariateTerm(int, UnivariateTerm*);
		UnivariatePolynomial* integrate(int);
		double integrateOverInterval(double, double, int);
		bool isConstant();
		bool isConstantUnivariateTerm(int);
		bool isLinear();
		void lexOrder();
		void printUnivariatePolynomial();
		void printUnivariatePolynomial(int, int);
		void removeUnivariateTerm(int &);
		void setEUCoefficients(vector<int>, int);
		void setEUExponents(vector<vector<int> >);
		void setUnivariateTerm(int, UnivariateTerm*);
		void simplify();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// constructor
UnivariatePolynomial::UnivariatePolynomial() // FINISH
{
	leading = NULL;
	trailing = NULL;
	
	numTerms = -1;
	numVariables = -1;
	totalDegree = -1;
	
	linear = true;
}

// these UnivariatePolynomials are in R[var]
// a_{nT}x^{nT} + a_{nT-1}x^{nT-1} + ... + a_1x^{nT-(nT-1)} + a_0
UnivariatePolynomial::UnivariatePolynomial(int nT, int nV, int var) // FINISH
{
	numVariables = nV;
	
	if (nT == -1 || var == -1) // default is 1x_{var}
	{		
		numTerms = 1;
		
		leading = new UnivariateTerm;
		leading->coefficient = 1;
		
		leading->exponent = vector<int>(numVariables); // numVariables is numPlayers
		for (int i = 0; i < numVariables; i++)
		{
			if (i == var)
				leading->exponent.at(i) = 1;
		}
		leading->next = NULL;
		
		trailing = new UnivariateTerm;
		trailing = leading;
		
		totalDegree = 1;
	}
	else
	{
		numTerms = nT;
		
		leading = new UnivariateTerm;
		leading->coefficient = 0;
		leading->exponent.resize(numVariables);
		for (int v = 0; v < numVariables; v++)
		{
			if (v == var)
				leading->exponent.at(v) = numTerms - 1;
			else
				leading->exponent.at(v) = 0;
		}
		leading->next = NULL;
		
		if (numTerms == 1)
			trailing = leading;
		else if (numTerms == 2)
		{			
			trailing = new UnivariateTerm;
			trailing->coefficient = 0;
			trailing->exponent.resize(numVariables);
			for (int v = 0; v < numVariables; v++)
				trailing->exponent.at(v) = 0;
			trailing->next = NULL;
			leading->next = trailing;		
		}
		else // numTerms >= 3
		{
			UnivariateTerm* temp = new UnivariateTerm;
			UnivariateTerm* term2 = new UnivariateTerm;
			term2->coefficient = 0;
			term2->exponent.resize(numVariables);
			for (int v = 0; v < numVariables; v++)
			{
				if (v == var)
					term2->exponent.at(v) = numTerms - 2;
				else
					term2->exponent.at(v) = 0;
			}
			leading->next = term2;
			
			temp = term2;
			for (int t = 2; t < numTerms - 1; t++) // terms 2,..., numTerms - 1
			{
				UnivariateTerm* newUnivariateTerm = new UnivariateTerm;
				newUnivariateTerm->coefficient = 0;
				newUnivariateTerm->exponent.resize(numVariables);
				for (int v = 0; v < numVariables; v++)
				{
					if (v == var)
						newUnivariateTerm->exponent.at(v) = numTerms - (t + 1);
					else
						newUnivariateTerm->exponent.at(v) = 0;
				}
				temp->next = newUnivariateTerm; // term t - 1 next points to term t
				temp = newUnivariateTerm; // temp moves up one term
			}
			
			trailing = new UnivariateTerm;
			temp->next = trailing;
			trailing->coefficient = 0;
			trailing->exponent.resize(numVariables);
			for (int v = 0; v < numVariables; v++)
				trailing->exponent.at(v) = 0;
			trailing->next = NULL;
		}
		totalDegree = -1;
	}
	linear = true;
}

// destructor
UnivariatePolynomial::~UnivariatePolynomial()
{
	UnivariateTerm* curUnivariateTerm;
	
	curUnivariateTerm = leading;
	while (curUnivariateTerm)
	{
		delete curUnivariateTerm;
		curUnivariateTerm = curUnivariateTerm->next;
	}
	delete this;
}

/*UnivariatePolynomial UnivariatePolynomial::operator+(const UnivariatePolynomial &p)
{		
	UnivariatePolynomial poly;
	// int pUnivariateTermIndex = -1, thisUnivariateTermIndex = -1;
	// bool inP = false, inThis = false;
	
	// constructor creates a single NULL node; if so, do nothing
	if (this == NULL)
		return p;
	else if (&p == NULL || (this == NULL && &p == NULL))
		return *this;
	
	/*if (this->getNumUnivariateTerms() >= p.getNumUnivariateTerms())
	{		
		// start with highest degree/first term in this
		for (int t1 = 0; t1 < this->getNumUnivariateTerms(); t1++)
		{					
			inP = false;
			// check if p has a term of the same degree
			for (int t2 = 0; t2 < p.getNumUnivariateTerms(); t2++)
			{						
				if (this->getExponents(t1) == p.getExponents(t2))
				{							
					inP = true;
					pUnivariateTermIndex = t2;
				}
			}
			
			if (inP) // add coefficients
			{
				poly.setCoefficient(t1, this->getCoefficient(t1) + p.getCoefficient(pUnivariateTermIndex));
				poly.setExponents(t1, this->getExponents(t1));
			}
			else
			{
				poly.setCoefficient(t1, this->getCoefficient(t1));
				poly.setExponents(t1, this->getExponents(t1));
			}
		}
	}
	else
	{		
		// start with highest degree/first term in p
		for (int t1 = 0; t1 < p.getNumUnivariateTerms(); t1++)
		{
			inThis = false;
			// check if this has a term of the same degree
			for (int t2 = 0; t2 < this->getNumUnivariateTerms(); t2++)
			{
				if (this->getExponents(t2) == p.getExponents(t1))
				{
					inThis = true;
					thisUnivariateTermIndex = t2;
				}
			}
			
			if (inThis) // add coefficients
			{
				poly.setCoefficient(t1, this->getCoefficient(thisUnivariateTermIndex) + p.getCoefficient(t1));
				poly.setExponents(t1, p.getExponents(t1));
			}
			else
			{
				poly.setCoefficient(t1, p.getCoefficient(t1));
				poly.setExponents(t1, p.getExponents(t1));
			}
		}				
	}*/
	
	/*cout << "\nNT: " << this->getNumUnivariateTerms() << endl;
	cout << "NT: " << p.getNumUnivariateTerms() << endl;
	
	for (int t = 0; t < this->getNumUnivariateTerms(); t++)
		poly.addUnivariateTerm(this->getUnivariateTerm(t));
	for (int t = 0; t < p.getNumUnivariateTerms(); t++)
		poly.addUnivariateTerm(p.getUnivariateTerm(t));
	
	poly.simplify();
	return poly;
}*/

// UnivariatePolynomial multiplication
UnivariatePolynomial UnivariatePolynomial::operator*(const UnivariatePolynomial &p)
{
	int nV = this->getNumVariables();
	if (nV < p.getNumVariables())
		nV = p.getNumVariables();
				
	UnivariatePolynomial* poly = new UnivariatePolynomial(this->getNumUnivariateTerms() * p.getNumVariables(), nV, -1);
	
	for (int t1 = 0; t1 < this->getNumUnivariateTerms(); t1++)
	{
		for (int t2 = 0; t2 < p.getNumUnivariateTerms(); t2++)
		{
			poly->setCoefficient(t1 + t2, this->getCoefficient(t1) + p.getCoefficient(t2));
			for (int v = 0; v < poly->getNumVariables(); v++)
				poly->setExponent(t1 + t2, v, this->getExponent(t1, v) + p.getExponent(t2, v));
		}
	}
	return *poly;
}

// UnivariatePolynomial subtraction
UnivariatePolynomial* UnivariatePolynomial::operator-(const UnivariatePolynomial &p)
{
	// cout << "SUBTRACTION\n";
	
	UnivariatePolynomial* poly;
	int pUnivariateTermIndex = -1, thisUnivariateTermIndex = -1;
	bool inP = false, inThis = false;
	
	if (this->getNumUnivariateTerms() >= p.getNumUnivariateTerms())
	{
		poly = new UnivariatePolynomial(this->getNumUnivariateTerms(), this->getNumVariables(), -1); // -1 bc the var parameter isn't needed and is irrelevant
		
		// start with highest degree/first term in this
		for (int i = 0; i < this->getNumUnivariateTerms(); i++)
		{
			inP = false;
			// check if p has a term of the same degree
			for (int j = 0; j < p.getNumUnivariateTerms(); j++)
			{
				if (p.getExponents(j) == this->getExponents(i))
				{
					inP = true;
					pUnivariateTermIndex = j;
				}
			}
			
			if (inP) // subtract coefficients
			{
				poly->setCoefficient(i, this->getCoefficient(i) - p.getCoefficient(pUnivariateTermIndex));
				poly->setExponents(i, this->getExponents(i));
			}
			else
			{
				poly->setCoefficient(i, this->getCoefficient(i));
				poly->setExponents(i, this->getExponents(i));
			}
		}
	}
	else
	{
		poly = new UnivariatePolynomial(p.getNumUnivariateTerms(), p.getNumVariables(), -1); // -1 bc the var parameter isn't needed and is irrelevant
		
		// start with highest degree/first term in p
		for (int i = 0; i < p.getNumUnivariateTerms(); i++)
		{
			inThis = false;
			// check if this has a term of the same degree
			for (int j = 0; j < this->getNumUnivariateTerms(); j++)
			{
				if (this->getExponents(j) == p.getExponents(i))
				{
					inThis = true;
					thisUnivariateTermIndex = j;
				}
			}
			
			if (inThis) // subtract coefficients
			{
				poly->setCoefficient(i, this->getCoefficient(thisUnivariateTermIndex) - p.getCoefficient(i));
				poly->setExponents(i, p.getExponents(i));
			}
			else
			{
				poly->setCoefficient(i, -p.getCoefficient(i));
				poly->setExponents(i, p.getExponents(i));
			}
		}				
	}
	poly->simplify();			
	return poly;
}

// UnivariatePolynomial equality
bool UnivariatePolynomial::operator==(const UnivariatePolynomial &p)
{
	if (this->getDegree() != p.getDegree() || this->getNumUnivariateTerms() != p.getNumUnivariateTerms())
		return false;
	
	for (int i = 0; i < p.getNumUnivariateTerms(); i++)
	{
		if (this->getCoefficient(i) != p.getCoefficient(i))// || this->getExponents(i) != p.getExponents(i))
			return false;
		
		if (this->getExponents(i) != p.getExponents(i))
			return false;
	}
	return true;
}

// UnivariatePolynomial inequality
bool UnivariatePolynomial::operator!=(const UnivariatePolynomial &p)
{
	if (*this == p)
		return false;
	else
		return true;
}

// UnivariatePolynomial order, less than
bool UnivariatePolynomial::operator<(const UnivariatePolynomial &p) // FINISH
{
	// x^alpha = a_0x^alpha_0 + a_1x^alpha_1 + ... + a_{nT-2}x^alpha_{nT-2} + a_{nT-1}x^alpha_{nT-1}
	// x^beta = b_0x^beta_0 + b_1x^beta_1 + ... + b_{nT-2}x^beta_{nT-2} + b_{nT-1}x^beta_{nT-1}
	
	// constructor creates a single NULL node; if so, do nothing
	if (this == NULL && &p != NULL && p.getCoefficient(0) != 0)
		return true;
	else if (this != NULL && &p == NULL)
		return false;
	else if (this == NULL && &p == NULL)
		return false;
	
	// check to see if equal terms exist
	
	if (*this == p)
		return false;
	
	// eliminating equal terms
	// if p = f + h and q = g + h ==> only need to check f < g

	// checking integral
	if ((*this - p)->integrateOverInterval(0, 1, 0) <= 0)
		return false;
	
	// check derivatives
	
	return true;
}

// UnivariatePolynomial order, greater than
bool UnivariatePolynomial::operator>(const UnivariatePolynomial &p)
{
	if (*this == p || *this < p)
		return false;
	else
		return true;
}

// add a term
void UnivariatePolynomial::addUnivariateTerm(int coeff, vector<int> expo) // TEST
{
	cout << "ADDTERM other\n";
	
	int n = 0, numExponents = 0;
	while ((unsigned)n < expo.size() && numExponents < 2)
	{
		if (expo.at(n) != 0)
			numExponents++;
		n++;
	}
	if (linear && numExponents > 1)
		linear = false;
	
	UnivariateTerm* newUnivariateTerm = new UnivariateTerm;
	newUnivariateTerm->coefficient = coeff;
	newUnivariateTerm->exponent = expo;
	
	if (!leading)
	{
		cout << "leading == NULL\n";
		leading = newUnivariateTerm;
		trailing = newUnivariateTerm;
	}
	else
	{
		cout << "ELSE\n";
		trailing->next = newUnivariateTerm;
		cout << "test1\n";
		trailing = newUnivariateTerm;
		cout << "test2\n";
	}
	numTerms++;
}

// add a term
void UnivariatePolynomial::addUnivariateTerm(UnivariateTerm* term) // TEST
{
	cout << "ADDTERM\n";
	
	// Check if new term is nonlinear
	if (linear)
	{
		int n = 0, numExponents = 0;
		while ((unsigned)n < term->exponent.size() && numExponents < 2)
		{
			if (term->exponent.at(n) != 0)
				numExponents++;
			n++;
		}
		if (linear && numExponents > 1)
			linear = false;
	}
	
	if (!leading)
	{
		leading = term;
		trailing = term;
	}
	else
	{
		trailing->next = term;
		trailing = term;
	}
	numTerms++;
	
	cout << "END ADDTERM: ";
	this->printUnivariatePolynomial();
	cout << endl;
}

// get derivative
// FINISH: linear derivatives from nonlinear UnivariatePolynomials
UnivariatePolynomial* UnivariatePolynomial::derivative(int var)
{
	// computes the derivative of this wrt to the var-th variable
	
	UnivariatePolynomial* poly = new UnivariatePolynomial(this->getNumUnivariateTerms(), this->getNumVariables(), 0);
	for (int t = 0; t < poly->getNumUnivariateTerms(); t++)
	{
		poly->setCoefficient(t, this->getCoefficient(t));
		for (int v = 0; v < poly->getNumVariables(); v++)
			poly->setExponent(t, v, this->getExponent(t, v));
	}
	
	for (int t = 0; t < poly->getNumUnivariateTerms(); t++)
	{
		if (poly->getExponent(t, var) != 0) // var-th variable occurs
		{			
			poly->setCoefficient(t, poly->getCoefficient(t) * poly->getExponent(t, var));
			
			for (int v = 0; v < poly->getNumVariables(); v++)
			{
				if (v != var) // if nonlinear, this is taking the partial
					poly->setExponent(t, v, 0);
				else
					poly->setExponent(t, v, poly->getExponent(t, v) - 1);
			}
		}
		else // var-th variable does not occur
		{
			if (numTerms > 1)
				poly->removeUnivariateTerm(t);
			else
				poly->setCoefficient(t, 0); // is now the zero UnivariatePolynomial
		}
	}
	// poly->printUnivariatePolynomial();
	return poly;
}

// enter info
/* separate bc mixed strategies doesn't 
require the user to enter info */
void UnivariatePolynomial::enterInfo()
{
	double c = 0.0;
	int e = -1;
	
	for (int t = 0; t < numTerms; t++)
	{
		cout << "-------------------------------------------" << endl;
		if(t == 0)
			cout << "Enter the 1st coefficient:  ";
		else if (t == 1)
			cout << "Enter the 2nd coefficient:  ";
		else if (t == 2)
			cout << "Enter the 3rd coefficient:  ";
		else
			cout << "Enter the " << t + 1 << "-th coefficient:  ";
		cin >> c;
		validateTypeDouble(c);
		this->setCoefficient(t, c);
		
		for (int v = 0; v < numVariables; v++)
		{
			if (t == 0)
			{
				cout << "Enter the ";
				if (v == 0)
					cout << "1st ";
				else if (v == 1)
					cout << "2nd ";
				else if (v == 2)
					cout << "3rd ";
				else
					cout << v + 1 << "-th ";
				cout << "exponent in the 1st term:  ";
			}
			else if (t == 1)
			{
				cout << "Enter the ";
				if (v == 0)
					cout << "1st ";
				else if (v == 1)
					cout << "2nd ";
				else if (v == 2)
					cout << "3rd ";
				else
					cout << v + 1 << "-th ";
				cout << "exponent in the 2nd term:  ";
			}
			else if (t == 2)
			{
				cout << "Enter the ";
				if (v == 0)
					cout << "1st ";
				else if (v == 1)
					cout << "2nd ";
				else if (v == 2)
					cout << "3rd ";
				else
					cout << v + 1 << "-th ";
				cout << "exponent in the 3rd term:  ";
			}
			else
			{
				cout << "Enter the ";
				if (v == 0)
					cout << "1st ";
				else if (v == 1)
					cout << "2nd ";
				else if (v == 2)
					cout << "3rd ";
				else
					cout << v + 1 << "-th ";
				cout << "exponent in the " << t + 1 << " term:  ";
			}
			cin >> e;
			validateTypeInt(e);
			this->setExponent(t, v, e);			
		}
	}
	computeTotalDegree();
}

// evaluate UnivariatePolynomial function at val
double UnivariatePolynomial::eval(double val)
{
	double num = 1.0, sum = 0.0;
	
	if (isConstant())
		return getCoefficient(0);
	else
	{
		for(int t = 0; t < numTerms; t++)
		{ 
			num = getCoefficient(t);
			for (int v = 0; v < numVariables; v++)
				num *= pow(val, getExponent(t, v));
			
			sum += num;
		}
		return sum;
	}
}

// computes derivatives up to the (n + 1)-th derivative wrt the v-th variable
UnivariatePolynomial* UnivariatePolynomial::getDerivative(int n, int v)
{
	bool loop = false;
	
	// Resizing derivatives
	if (getSizeDerivatives() < v + 1)
		derivatives.resize(v + 1);
	
	if (derivatives.at(v).size() == 0)
	{
		derivatives.at(v).resize(1);
		derivatives.at(v).at(0) = this;
		loop = true;
	}
	else if (derivatives.at(v).at(0) != this)
	{
		derivatives.at(v).at(0) = this;
		loop = true;
	}
	
	// Pushing into derivatives.at(v) until it has spots 0,...,n
	cout << "size: " << getSizeDerivativesWRT(v) << endl;
	cout << "n + 1: " << n + 1 << endl;
	while (getSizeDerivativesWRT(v) < n + 1 && loop)
	{
		cout << "size: " << getSizeDerivativesWRT(v) << endl;
		
		if (getSizeDerivativesWRT(v) == 0)
			derivatives.at(v).push_back(derivative(v));
		else
			derivatives.at(v).push_back(getDerivative(derivatives.at(v).size() - 1, v)->derivative(v));
	}
	cout << "size1: " << derivatives.size() << endl;
	cout << "size2: " << derivatives.at(v).size() << endl;
	return derivatives.at(v).at(n);
}

// get nonzero exponent
// for linear UnivariatePolynomials
int UnivariatePolynomial::getNonZeroExpo(int t) const
{ 
	for (int v = 0; v < numVariables; v++)
	{
		if (this->getExponent(t, v) != 0)
			return v;
	}
	return (numTerms - 1);
}

// get term
UnivariateTerm* UnivariatePolynomial::getUnivariateTerm(int t) const
{
	int count = 0;
	UnivariateTerm* curUnivariateTerm;
	curUnivariateTerm = leading;
	
	while (count < t)
	{
		curUnivariateTerm = curUnivariateTerm->next;
		count++;
	}
	return curUnivariateTerm;
}

// insert term
void UnivariatePolynomial::insertUnivariateTerm(int t, vector<int> expo, int coeff)
{
	UnivariateTerm* newUnivariateTerm = new UnivariateTerm;
	
	// putting info into newUnivariateTerm
	newUnivariateTerm->coefficient = coeff;
	for (int n = 0; (unsigned)n < expo.size(); n++)
		newUnivariateTerm->exponent.push_back(expo.at(n));
	
	if (t == 0)
	{
		newUnivariateTerm->next = leading->next;
		leading = newUnivariateTerm;
	}
	else
	{
		newUnivariateTerm->next = getUnivariateTerm(t - 1)->next; // t - 1 --> new --> t
		getUnivariateTerm(t - 1)->next = newUnivariateTerm; // insert at position i
	}
	numTerms++;
}

// insert term
void UnivariatePolynomial::insertUnivariateTerm(int t, UnivariateTerm* term)
{	
	if (t == 0)
	{
		term->next = leading->next;
		leading = term;
	}
	else
	{
		term->next = getUnivariateTerm(t - 1)->next; // i - 1 --> new --> i
		getUnivariateTerm(t - 1)->next = term; // insert at position i
	}
	numTerms++;
}

// integrate
UnivariatePolynomial* UnivariatePolynomial::integrate(int var) // FINISH (... + c)
{
	UnivariatePolynomial* poly = new UnivariatePolynomial(getNumUnivariateTerms(), getNumVariables(), 0);
	
	// copying this pointer
	for (int t = 0; t < numTerms; t++)
	{
		for (int v = 0; v < poly->getNumVariables(); v++)
		{
			poly->setCoefficient(t, getCoefficient(t));
			poly->setExponent(t, v, getExponent(t, v));
		}
	}
	// computing
	for (int t = 0; t < numTerms; t++)
	{
		poly->setExponent(t, var, poly->getExponent(t, var) + 1);
		poly->setCoefficient(t, poly->getCoefficient(t) / static_cast<double>(poly->getExponent(t, var)));
	}
	return poly;
}

// integrate over [a, b]
double UnivariatePolynomial::integrateOverInterval(double a, double b, int var)
{
	// cout << "INTEGRATEOVER\n";
	
	double num = -1;
	UnivariatePolynomial* poly = new UnivariatePolynomial(getNumUnivariateTerms(), getNumVariables(), 0);
	
	for (int t = 0; t < poly->getNumUnivariateTerms(); t++)
	{
		for (int v = 0; v < poly->getNumVariables(); v++)
		{
			poly->setCoefficient(t, getCoefficient(t));
			poly->setExponent(t, v, getExponent(t, v));
		}
	}
	poly = poly->integrate(var);
	num = poly->eval(b) - poly->eval(a);
	
	cout << endl;
	
	// cout << "num:  " << num << endl;
	// cout << "end INTEGRATEOVER\n";
	return num;
}

// checks if constant
bool UnivariatePolynomial::isConstant()
{
	bool allExpoZero = true;
	for (int t = 0; t < numTerms; t++)
	{
		if (!isConstantUnivariateTerm(t))
		{
			allExpoZero = false;
			return allExpoZero;
		}
	}
	return allExpoZero;
}

// checks if constant term
bool UnivariatePolynomial::isConstantUnivariateTerm(int t)
{
	bool allExpoZero = true;
	for (int v = 0; v < numVariables; v++)
	{
		if(getExponent(t, v) != 0)
			allExpoZero = false;
	}
	return allExpoZero;
}

// checks if linear
bool UnivariatePolynomial::isLinear() // TEST
{
	int numExponents = 0;
	for (int t = 0; t < numTerms; t++)
	{
		numExponents = 0;
		for (int v = 0; v < numVariables; v++)
		{
			if (getExponent(t, v) != 0)
				numExponents++;
			if (numExponents > 1)
				return false;
		}
	}
	return true;
}

// print UnivariatePolynomial
void UnivariatePolynomial::printUnivariatePolynomial()
{
	bool nonConstant = false, oneMoreNonZero = false;
	int count = 0;
	
	// simplify();
	for (int t = 0; t < numTerms; t++) // terms
	{
		nonConstant = false;
		for (int v = 0; v < numVariables; v++) // variables
		{
			if (getExponent(t, v) != 0)
				nonConstant = true; // at least one is nonzero
		}
		
		oneMoreNonZero = false;
		count = t + 1;
		if (t < numTerms - 1) // checks if there's one more nonzero term
		{
			while (!oneMoreNonZero && count != numTerms)
			{
				if (getCoefficient(count) != 0)
					oneMoreNonZero = true;
				
				count++;
			}
		}
		
		if (!leading) // empty
			cout << "EMPTY UnivariatePolynomial: enter values for coefficients and exponents";
		else // not empty
		{
			if (getCoefficient(t) != 0) // nonzero coefficient
			{
				if (t == 0 && getCoefficient(t) < 0) // first term negative
				{
					if ((getCoefficient(t) != -1 && nonConstant) || !nonConstant)
						cout << getCoefficient(t);
					else
						cout << "-";
				}
				else // not first term OR nonnegative coefficient
				{
					if ((abs(getCoefficient(t)) != 1 && nonConstant) || !nonConstant)
						cout << abs(getCoefficient(t));
				}
				
				for (int v = 0; v < numVariables; v++)
				{
					if (getExponent(t, v) != 0)
					{
							cout << "x";
							if (numVariables > 1)
								cout << "_" << v + 1;
							if (getExponent(t, v) != 1)
								cout << "^" << getExponent(t, v);
					}
				}
				
				if (t < numTerms - 1 && oneMoreNonZero && getCoefficient(t + 1) >= 0) // && exists(a_k)[i < k <= n && a_k != 0]
					cout << " + ";
				else if (t < numTerms - 1 && oneMoreNonZero && getCoefficient(t + 1) < 0)
					cout << " - ";
			}
			else if (getCoefficient(t) == 0) // zero coefficient
			{
				if (numTerms == 1) // in a monomial
					cout << "0";
			}
		}
	}
	cout << endl;
}

// print UnivariatePolynomial
// For EU's
void UnivariatePolynomial::printUnivariatePolynomial(int player, int strat)
{
	bool nonConstant = false, oneMoreNonZero = false;
	int count = 0;
	
	simplify();
	for (int t = 0; t < numTerms; t++) // terms
	{
		nonConstant = false;
		for (int v = 0; v < numVariables; v++) // variables
		{
			if (getExponent(t, v) != 0)
				nonConstant = true; // at least one is nonzero
		}
		
		oneMoreNonZero = false;
		count = t + 1;
		if (t < numTerms - 1) // checks if there's one more nonzero term
		{
			while (!oneMoreNonZero && count != numTerms)
			{
				if (getCoefficient(count) != 0)
					oneMoreNonZero = true;
				
				count++;
			}
		}
		
		if (!leading) // empty
			cout << "EMPTY UnivariatePolynomial: enter values for coefficients and exponents";
		else // not empty
		{
			if (getCoefficient(t) != 0) // nonzero coefficient
			{
				if (t == 0 && getCoefficient(t) < 0) // first term negative
				{
					if ((getCoefficient(t) != -1 && nonConstant) || !nonConstant)
						cout << getCoefficient(t);
					else
						cout << "-";
				}
				else // not first term OR nonnegative coefficient
				{
					if ((abs(getCoefficient(t)) != 1 && nonConstant) || !nonConstant)
						cout << abs(getCoefficient(t));
				}
				
				for (int v = 0; v < numVariables; v++)
				{
					if (getExponent(t, v) != 0)
					{
							cout << "p_" << player << ", " << strat;
							if (getExponent(t, v) != 1)
								cout << "^" << getExponent(t, v);
					}
				}
				
				if (t < numTerms - 1 && oneMoreNonZero && getCoefficient(t + 1) >= 0) // && exists(a_k)[i < k <= n && a_k != 0]
					cout << " + ";
				else if (t < numTerms - 1 && oneMoreNonZero && getCoefficient(t + 1) < 0)
					cout << " - ";
			}
			else if (getCoefficient(t) == 0) // zero coefficient
			{
				if (numTerms == 1) // in a monomial
					cout << "0";
			}
		}
	}
	cout << endl;
}

// remove term
void UnivariatePolynomial::removeUnivariateTerm(int &t)
{	
	int count = 0;
	UnivariateTerm* curUnivariateTerm;
	UnivariateTerm* previousUnivariateTerm;
	
	if (t == 0)
	{
		delete leading;
		leading = leading->next;
	}
	else
	{
		curUnivariateTerm = leading;
		while (count < t)
		{
			previousUnivariateTerm = curUnivariateTerm;
			curUnivariateTerm = curUnivariateTerm->next;
			count++;
		}
		previousUnivariateTerm->next = curUnivariateTerm->next;
		delete curUnivariateTerm;
		curUnivariateTerm = curUnivariateTerm->next;
	}
	numTerms--;
	t--;
}

// set EU coeffs
void UnivariatePolynomial::setEUCoefficients(vector<int> coeffs, int numPlayers) // TEST
{
	// enters coeffs into the expected utility, leaving the last term as a_{n-1}
	
	// if (numPlayers < 3)
	// {
		/*
		nP == 2:
		--------
		n = numTerms
		a_0p_0 + ... + a_{n-2}p_{n-2} + a_{n-1}(1 - p_0 - ... - p_{n-2})
		a_0p_0 + ... + a_{n-2}p_{n-2} + a_{n-1} - a_{n-1}p_0 - ... - a_{n-1}p_{n-2}
		(a_0p_0 - a_{n-1}p_0) + ... + (a_{n-2}p_{n-2} - a_{n-1}p_{n-2}) + a_{n-1}
		(a_0 - a_{n-1})p_0 + ... + (a_{n-2} - a_{n-1})p_{n-2} + a_{n-1}

		0p + 3(1-p)
		0p + 3 - 3p
		0p - 3p + 3
		(0 - 3)p + 3
		-3p + 3
		*/
			
		// (a_i - a_{n-1})p_i
		for (int t = 0; t < numTerms - 1; t++)
		{
			this->setCoefficient(t, coeffs.at(t) - coeffs.at(numTerms - 1));
			for (int v = 0; v < numVariables; v++)
			{
				if (t == v)
					this->setExponent(t, v, 1);
				else
					this->setExponent(t, v, 0);
			}
		}
		// a_{n-1}
		this->setCoefficient(numTerms - 1, coeffs.at(numTerms - 1));
		for (int v = 0; v < numVariables; v++)
			this->setExponent(numTerms - 1, v, 0);
	// }
	// else
		// cout << "ERROR: numPLayers > 2\n";
}

// set EU exponents
void UnivariatePolynomial::setEUExponents(vector<vector<int> > exponents) // FINISH: need number of terms per UnivariatePolynomial
{
	// enters exponents into the expected utility
	
	// for (int t = 0; t < numTerms; t++)
		// this->setUnivariateTerm(t, exponents.at(t));
}

// set term
void UnivariatePolynomial::setUnivariateTerm(int t, UnivariateTerm* temp)
{
	this->setCoefficient(t, temp->coefficient);
	this->setExponents(t, temp->exponent);
}

// simplify
void UnivariatePolynomial::simplify()
{
	cout << "SIMPLIFY\n";
	
	bool sameAlpha = true;
	
	// getting rid of zero terms
	for (int t = 0; t < numTerms; t++)
	{
		cout << "t: " << t << endl;
		if (getCoefficient(t) == 0 && numTerms > 1)
		{
			// cout << "IF\n";
			removeUnivariateTerm(t);
		}
	}
	
	// combining nonzero terms
	for (int t1 = 0; t1 < numTerms; t1++)
	{
		cout << "t1: " << t1 << endl;
		for (int t2 = t1 + 1; t2 < numTerms; t2++)
		{
			cout << "t2: " << t2 << endl;
			sameAlpha = true;
			for (int v = 0; v < numVariables; v++)
			{
				if (getUnivariateTerm(t1)->exponent.at(v) != getUnivariateTerm(t2)->exponent.at(v))
					sameAlpha = false;
			}
			if (sameAlpha)
			{
				cout << "\tsame\n";
				setCoefficient(t1, getCoefficient(t1) + getCoefficient(t2));
				if (numTerms > 1)
					removeUnivariateTerm(t2);
			}
		}
	}
	
	cout << "DONE SIMPLIFY\n";
}

#endif