/**************************
Title: MultivariatePolynomial.h
Author: Andrew Lounsbury
Date: 6/2/2020
Purpose: for holding EU's
**************************/

/***************************************
1) create nT zero MultivariateTerms in nV variables
2) read in coeff and expo for each MultivariateTerm
3) remove zero MultivariateTerms
4) add like MultivariateTerms
***************************************/

#ifndef MultivariatePolynomial_H
#define MultivariatePolynomial_H
#include "inputValidation.cpp"
#include "MultivariateTerm.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// MultivariatePolynomials of the form [coefficient, exponents] -> ... -> [coefficient, exponents]
class MultivariatePolynomial
{
	private:
		MultivariateTerm* leading;
		MultivariateTerm* trailing;
		int numTerms;
		int numVariables;
		int totalDegree;
		vector<vector<MultivariatePolynomial*> > derivatives;
		bool linear;
	public:		
		double getCoefficient(int i) const 							{ return getMultivariateTerm(i)->coefficient; }
		vector<vector<MultivariatePolynomial*> > getDerivatives() 	{ return derivatives; }
		int getExponent(int t, int var) const 						{ return getExponents(t).at(var); }
		vector<int> getExponents(int i) const 						{ return this->getTerm(i)->exponents; }
		int getNumTerms() const 									{ return numTerms; }
		int getNumVariables() const 								{ return numVariables; }
		int getSizeDerivatives() 									{ return derivatives.size(); }
		// with respect to v
		int getSizeDerivativesWRT(int v) 							{ return derivatives.at(v).size(); }

		MultivariateTerm* getTerm(int n) const						
		{
			MultivariateTerm* curTerm = this->leading;
			for (int i = 0; i < n; i++)
				curTerm = curTerm->next;
			return curTerm;
		}

		MultivariateTerm* getTrailing() const 						{ return trailing; }

		void setCoefficient(int i, int c)
		{
			this->getTerm(i)->coefficient = c;
		}

		void setCoefficient(int t, double num) 			{ getTerm(t)->setCoefficient(num); }
		void setExponent(int t, int v, int num) 		{ getTerm(t)->exponents.at(v) = num; }
		void setExponents(int t, vector<int> expo) 		{ getTerm(t)->setExponents(expo); }

		void setNumTerms(int num) 									{ numTerms = num; }
		void setTotalDegree(int num) 								{ totalDegree = num; }
		
		MultivariatePolynomial();
		MultivariatePolynomial(int, int, int);
		MultivariatePolynomial(int, int, vector<int>, int);
		~MultivariatePolynomial();
		
		// MultivariatePolynomial operator+(const MultivariatePolynomial &p);
		// MultivariatePolynomial operator+(MultivariatePolynomial &l, MultivariatePolynomial &r);
		MultivariatePolynomial operator*(const MultivariatePolynomial &p);
		MultivariatePolynomial* operator-(const MultivariatePolynomial &p);
		bool operator==(const MultivariatePolynomial &p);
		bool operator!=(const MultivariatePolynomial &p);
		bool operator<(const MultivariatePolynomial &p);
		bool operator>(const MultivariatePolynomial &p);
		
		void addMultivariateTerm(int, vector<int>);
		void addMultivariateTerm(MultivariateTerm*);
		void computeTotalDegree();
		MultivariatePolynomial* derivative(int);
		void enterInfo();
		double eval(double);
		MultivariatePolynomial* getDerivative(int, int);
		int getNonZeroExpo(int) const;
		MultivariateTerm* getMultivariateTerm(int) const;
		void insertMultivariateTerm(int, vector<int>, int);
		void insertMultivariateTerm(int, MultivariateTerm*);
		MultivariatePolynomial* integrate(int);
		double integrateOverInterval(double, double, int);
		bool isConstant();
		bool isConstantMultivariateTerm(int);
		bool isLinear();
		void lexOrder();
		void printMultivariatePolynomial();
		void printMultivariatePolynomial(int, int);
		void removeMultivariateTerm(int &);
		void setEUCoefficients(vector<int>, int);
		void setEUExponents(vector<vector<int> >);
		void setMultivariateTerm(int, MultivariateTerm*);
		void simplify();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// constructor
MultivariatePolynomial::MultivariatePolynomial() // FINISH
{
	leading = NULL;
	trailing = NULL;
	
	numTerms = -1;
	numVariables = -1;
	totalDegree = -1;
	
	linear = true;
}

// these MultivariatePolynomials are in R[var]
// a_{nT}x^{nT} + a_{nT-1}x^{nT-1} + ... + a_1x^{nT-(nT-1)} + a_0
MultivariatePolynomial::MultivariatePolynomial(int nT, int nV, int var) // FINISH
{
	numVariables = nV;
	
	if (nT == -1 || var == -1) // default is 1x_{var}
	{		
		numTerms = 1;
		
		leading = new MultivariateTerm;
		leading->coefficient = 1;
		
		leading->exponents = vector<int>(numVariables); // numVariables is numPlayers
		for (int i = 0; i < numVariables; i++)
		{
			if (i == var)
				leading->exponents.at(i) = 1;
		}
		leading->next = NULL;
		
		trailing = new MultivariateTerm;
		trailing = leading;
		
		totalDegree = 1;
	}
	else
	{
		numTerms = nT;
		
		leading = new MultivariateTerm;
		leading->coefficient = 0;
		leading->exponents.resize(numVariables);
		for (int v = 0; v < numVariables; v++)
		{
			if (v == var)
				leading->exponents.at(v) = numTerms - 1;
			else
				leading->exponents.at(v) = 0;
		}
		leading->next = NULL;
		
		if (numTerms == 1)
			trailing = leading;
		else if (numTerms == 2)
		{			
			trailing = new MultivariateTerm;
			trailing->coefficient = 0;
			trailing->exponents.resize(numVariables);
			for (int v = 0; v < numVariables; v++)
				trailing->exponents.at(v) = 0;
			trailing->next = NULL;
			leading->next = trailing;		
		}
		else // numTerms >= 3
		{
			MultivariateTerm* temp = new MultivariateTerm;
			MultivariateTerm* MultivariateTerm2 = new MultivariateTerm;
			MultivariateTerm2->coefficient = 0;
			MultivariateTerm2->exponents.resize(numVariables);
			for (int v = 0; v < numVariables; v++)
			{
				if (v == var)
					MultivariateTerm2->exponents.at(v) = numTerms - 2;
				else
					MultivariateTerm2->exponents.at(v) = 0;
			}
			leading->next = MultivariateTerm2;
			
			temp = MultivariateTerm2;
			for (int t = 2; t < numTerms - 1; t++) // MultivariateTerms 2,..., numTerms - 1
			{
				MultivariateTerm* newMultivariateTerm = new MultivariateTerm;
				newMultivariateTerm->coefficient = 0;
				newMultivariateTerm->exponents.resize(numVariables);
				for (int v = 0; v < numVariables; v++)
				{
					if (v == var)
						newMultivariateTerm->exponents.at(v) = numTerms - (t + 1);
					else
						newMultivariateTerm->exponents.at(v) = 0;
				}
				temp->next = newMultivariateTerm; // MultivariateTerm t - 1 next points to MultivariateTerm t
				temp = newMultivariateTerm; // temp moves up one MultivariateTerm
			}
			
			trailing = new MultivariateTerm;
			temp->next = trailing;
			trailing->coefficient = 0;
			trailing->exponents.resize(numVariables);
			for (int v = 0; v < numVariables; v++)
				trailing->exponents.at(v) = 0;
			trailing->next = NULL;
		}
		totalDegree = -1;
	}
	linear = true;
}

// destructor
MultivariatePolynomial::~MultivariatePolynomial()
{
	MultivariateTerm* curMultivariateTerm;
	
	curMultivariateTerm = leading;
	while (curMultivariateTerm)
	{
		delete curMultivariateTerm;
		curMultivariateTerm = curMultivariateTerm->next;
	}
	delete this;
}

/*MultivariatePolynomial MultivariatePolynomial::operator+(const MultivariatePolynomial &p)
{		
	MultivariatePolynomial poly;
	// int pMultivariateTermIndex = -1, thisMultivariateTermIndex = -1;
	// bool inP = false, inThis = false;
	
	// constructor creates a single NULL node; if so, do nothing
	if (this == NULL)
		return p;
	else if (&p == NULL || (this == NULL && &p == NULL))
		return *this;
	
	/*if (this->getNumTerms() >= p.getNumTerms())
	{		
		// start with highest degree/first MultivariateTerm in this
		for (int t1 = 0; t1 < this->getNumTerms(); t1++)
		{					
			inP = false;
			// check if p has a MultivariateTerm of the same degree
			for (int t2 = 0; t2 < p.getNumTerms(); t2++)
			{						
				if (this->getExponents(t1) == p.getExponents(t2))
				{							
					inP = true;
					pMultivariateTermIndex = t2;
				}
			}
			
			if (inP) // add coefficients
			{
				poly.setCoefficient(t1, this->getCoefficient(t1) + p.getCoefficient(pMultivariateTermIndex));
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
		// start with highest degree/first MultivariateTerm in p
		for (int t1 = 0; t1 < p.getNumTerms(); t1++)
		{
			inThis = false;
			// check if this has a MultivariateTerm of the same degree
			for (int t2 = 0; t2 < this->getNumTerms(); t2++)
			{
				if (this->getExponents(t2) == p.getExponents(t1))
				{
					inThis = true;
					thisMultivariateTermIndex = t2;
				}
			}
			
			if (inThis) // add coefficients
			{
				poly.setCoefficient(t1, this->getCoefficient(thisMultivariateTermIndex) + p.getCoefficient(t1));
				poly.setExponents(t1, p.getExponents(t1));
			}
			else
			{
				poly.setCoefficient(t1, p.getCoefficient(t1));
				poly.setExponents(t1, p.getExponents(t1));
			}
		}				
	}*/
	
	/*cout << "\nNT: " << this->getNumTerms() << endl;
	cout << "NT: " << p.getNumTerms() << endl;
	
	for (int t = 0; t < this->getNumTerms(); t++)
		poly.addMultivariateTerm(this->getMultivariateTerm(t));
	for (int t = 0; t < p.getNumTerms(); t++)
		poly.addMultivariateTerm(p.getMultivariateTerm(t));
	
	poly.simplify();
	return poly;
}*/

// MultivariatePolynomial multiplication
MultivariatePolynomial MultivariatePolynomial::operator*(const MultivariatePolynomial &p)
{
	int nV = this->getNumVariables();
	if (nV < p.getNumVariables())
		nV = p.getNumVariables();
				
	MultivariatePolynomial* poly = new MultivariatePolynomial(this->getNumTerms() * p.getNumVariables(), nV, -1);
	
	for (int t1 = 0; t1 < this->getNumTerms(); t1++)
	{
		for (int t2 = 0; t2 < p.getNumTerms(); t2++)
		{
			poly->setCoefficient(t1 + t2, this->getCoefficient(t1) + p.getCoefficient(t2));
			for (int v = 0; v < poly->getNumVariables(); v++)
				poly->setExponent(t1 + t2, v, this->getExponent(t1, v) + p.getExponent(t2, v));
		}
	}
	return *poly;
}

// MultivariatePolynomial subtraction
MultivariatePolynomial* MultivariatePolynomial::operator-(const MultivariatePolynomial &p)
{
	// cout << "SUBTRACTION\n";
	
	MultivariatePolynomial* poly;
	int pMultivariateTermIndex = -1, thisMultivariateTermIndex = -1;
	bool inP = false, inThis = false;
	
	if (this->getNumTerms() >= p.getNumTerms())
	{
		poly = new MultivariatePolynomial(this->getNumTerms(), this->getNumVariables(), -1); // -1 bc the var parameter isn't needed and is irrelevant
		
		// start with highest degree/first MultivariateTerm in this
		for (int i = 0; i < this->getNumTerms(); i++)
		{
			inP = false;
			// check if p has a MultivariateTerm of the same degree
			for (int j = 0; j < p.getNumTerms(); j++)
			{
				if (p.getExponents(j) == this->getExponents(i))
				{
					inP = true;
					pMultivariateTermIndex = j;
				}
			}
			
			if (inP) // subtract coefficients
			{
				poly->setCoefficient(i, this->getCoefficient(i) - p.getCoefficient(pMultivariateTermIndex));
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
		poly = new MultivariatePolynomial(p.getNumTerms(), p.getNumVariables(), -1); // -1 bc the var parameter isn't needed and is irrelevant
		
		// start with highest degree/first MultivariateTerm in p
		for (int i = 0; i < p.getNumTerms(); i++)
		{
			inThis = false;
			// check if this has a MultivariateTerm of the same degree
			for (int j = 0; j < this->getNumTerms(); j++)
			{
				if (this->getExponents(j) == p.getExponents(i))
				{
					inThis = true;
					thisMultivariateTermIndex = j;
				}
			}
			
			if (inThis) // subtract coefficients
			{
				poly->setCoefficient(i, this->getCoefficient(thisMultivariateTermIndex) - p.getCoefficient(i));
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

// MultivariatePolynomial equality
bool MultivariatePolynomial::operator==(const MultivariatePolynomial &p)
{
	if (this->getDegree() != p.getDegree() || this->getNumTerms() != p.getNumTerms())
		return false;
	
	for (int i = 0; i < p.getNumTerms(); i++)
	{
		if (this->getCoefficient(i) != p.getCoefficient(i))// || this->getExponents(i) != p.getExponents(i))
			return false;
		
		if (this->getExponents(i) != p.getExponents(i))
			return false;
	}
	return true;
}

// MultivariatePolynomial inequality
bool MultivariatePolynomial::operator!=(const MultivariatePolynomial &p)
{
	if (*this == p)
		return false;
	else
		return true;
}

// MultivariatePolynomial order, less than
bool MultivariatePolynomial::operator<(const MultivariatePolynomial &p) // FINISH
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
	
	// check to see if equal MultivariateTerms exist
	
	if (*this == p)
		return false;
	
	// eliminating equal MultivariateTerms
	// if p = f + h and q = g + h ==> only need to check f < g

	// checking integral
	if ((*this - p)->integrateOverInterval(0, 1, 0) <= 0)
		return false;
	
	// check derivatives
	
	return true;
}

// MultivariatePolynomial order, greater than
bool MultivariatePolynomial::operator>(const MultivariatePolynomial &p)
{
	if (*this == p || *this < p)
		return false;
	else
		return true;
}

// add a MultivariateTerm
void MultivariatePolynomial::addMultivariateTerm(int coeff, vector<int> expo) // TEST
{
	cout << "ADDMultivariateTerm other\n";
	
	int n = 0, numExponents = 0;
	while ((unsigned)n < expo.size() && numExponents < 2)
	{
		if (expo.at(n) != 0)
			numExponents++;
		n++;
	}
	if (linear && numExponents > 1)
		linear = false;
	
	MultivariateTerm* newMultivariateTerm = new MultivariateTerm;
	newMultivariateTerm->coefficient = coeff;
	newMultivariateTerm->exponents = expo;
	
	if (!leading)
	{
		cout << "leading == NULL\n";
		leading = newMultivariateTerm;
		trailing = newMultivariateTerm;
	}
	else
	{
		cout << "ELSE\n";
		trailing->next = newMultivariateTerm;
		cout << "test1\n";
		trailing = newMultivariateTerm;
		cout << "test2\n";
	}
	numTerms++;
}

// add a MultivariateTerm
void MultivariatePolynomial::addMultivariateTerm(MultivariateTerm* MultivariateTerm) // TEST
{
	cout << "ADDMultivariateTerm\n";
	
	// Check if new MultivariateTerm is nonlinear
	if (linear)
	{
		int n = 0, numExponents = 0;
		while ((unsigned)n < MultivariateTerm->exponents.size() && numExponents < 2)
		{
			if (MultivariateTerm->exponents.at(n) != 0)
				numExponents++;
			n++;
		}
		if (linear && numExponents > 1)
			linear = false;
	}
	
	if (!leading)
	{
		leading = MultivariateTerm;
		trailing = MultivariateTerm;
	}
	else
	{
		trailing->next = MultivariateTerm;
		trailing = MultivariateTerm;
	}
	numTerms++;
	
	cout << "END ADDMultivariateTerm: ";
	this->printMultivariatePolynomial();
	cout << endl;
}

// get derivative
// FINISH: linear derivatives from nonlinear MultivariatePolynomials
MultivariatePolynomial* MultivariatePolynomial::derivative(int var)
{
	// computes the derivative of this wrt to the var-th variable
	
	MultivariatePolynomial* poly = new MultivariatePolynomial(this->getNumTerms(), this->getNumVariables(), 0);
	for (int t = 0; t < poly->getNumTerms(); t++)
	{
		poly->setCoefficient(t, this->getCoefficient(t));
		for (int v = 0; v < poly->getNumVariables(); v++)
			poly->setExponent(t, v, this->getExponent(t, v));
	}
	
	for (int t = 0; t < poly->getNumTerms(); t++)
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
				poly->removeMultivariateTerm(t);
			else
				poly->setCoefficient(t, 0); // is now the zero MultivariatePolynomial
		}
	}
	// poly->printMultivariatePolynomial();
	return poly;
}

// enter info
/* separate bc mixed strategies doesn't 
require the user to enter info */
void MultivariatePolynomial::enterInfo()
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
				cout << "exponent in the 1st MultivariateTerm:  ";
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
				cout << "exponent in the 2nd MultivariateTerm:  ";
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
				cout << "exponent in the 3rd MultivariateTerm:  ";
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
				cout << "exponent in the " << t + 1 << " MultivariateTerm:  ";
			}
			cin >> e;
			validateTypeInt(e);
			this->setExponent(t, v, e);			
		}
	}
	computeTotalDegree();
}

// evaluate MultivariatePolynomial function at val
double MultivariatePolynomial::eval(double val)
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
MultivariatePolynomial* MultivariatePolynomial::getDerivative(int n, int v)
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
// for linear MultivariatePolynomials
int MultivariatePolynomial::getNonZeroExpo(int t) const
{ 
	for (int v = 0; v < numVariables; v++)
	{
		if (this->getExponent(t, v) != 0)
			return v;
	}
	return (numTerms - 1);
}

// get MultivariateTerm
MultivariateTerm* MultivariatePolynomial::getMultivariateTerm(int t) const
{
	int count = 0;
	MultivariateTerm* curMultivariateTerm;
	curMultivariateTerm = leading;
	
	while (count < t)
	{
		curMultivariateTerm = curMultivariateTerm->next;
		count++;
	}
	return curMultivariateTerm;
}

// insert MultivariateTerm
void MultivariatePolynomial::insertMultivariateTerm(int t, vector<int> expo, int coeff)
{
	MultivariateTerm* newMultivariateTerm = new MultivariateTerm;
	
	// putting info into newMultivariateTerm
	newMultivariateTerm->coefficient = coeff;
	for (int n = 0; (unsigned)n < expo.size(); n++)
		newMultivariateTerm->exponents.push_back(expo.at(n));
	
	if (t == 0)
	{
		newMultivariateTerm->next = leading->next;
		leading = newMultivariateTerm;
	}
	else
	{
		newMultivariateTerm->next = getMultivariateTerm(t - 1)->next; // t - 1 --> new --> t
		getMultivariateTerm(t - 1)->next = newMultivariateTerm; // insert at position i
	}
	numTerms++;
}

// insert MultivariateTerm
void MultivariatePolynomial::insertMultivariateTerm(int t, MultivariateTerm* MultivariateTerm)
{	
	if (t == 0)
	{
		MultivariateTerm->next = leading->next;
		leading = MultivariateTerm;
	}
	else
	{
		MultivariateTerm->next = getMultivariateTerm(t - 1)->next; // i - 1 --> new --> i
		getMultivariateTerm(t - 1)->next = MultivariateTerm; // insert at position i
	}
	numTerms++;
}

// integrate
MultivariatePolynomial* MultivariatePolynomial::integrate(int var) // FINISH (... + c)
{
	MultivariatePolynomial* poly = new MultivariatePolynomial(getNumTerms(), getNumVariables(), 0);
	
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
double MultivariatePolynomial::integrateOverInterval(double a, double b, int var)
{
	// cout << "INTEGRATEOVER\n";
	
	double num = -1;
	MultivariatePolynomial* poly = new MultivariatePolynomial(getNumTerms(), getNumVariables(), 0);
	
	for (int t = 0; t < poly->getNumTerms(); t++)
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
bool MultivariatePolynomial::isConstant()
{
	bool allExpoZero = true;
	for (int t = 0; t < numTerms; t++)
	{
		if (!isConstantMultivariateTerm(t))
		{
			allExpoZero = false;
			return allExpoZero;
		}
	}
	return allExpoZero;
}

// checks if constant MultivariateTerm
bool MultivariatePolynomial::isConstantMultivariateTerm(int t)
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
bool MultivariatePolynomial::isLinear() // TEST
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

// print MultivariatePolynomial
void MultivariatePolynomial::printMultivariatePolynomial()
{
	bool nonConstant = false, oneMoreNonZero = false;
	int count = 0;
	
	// simplify();
	for (int t = 0; t < numTerms; t++) // MultivariateTerms
	{
		nonConstant = false;
		for (int v = 0; v < numVariables; v++) // variables
		{
			if (getExponent(t, v) != 0)
				nonConstant = true; // at least one is nonzero
		}
		
		oneMoreNonZero = false;
		count = t + 1;
		if (t < numTerms - 1) // checks if there's one more nonzero MultivariateTerm
		{
			while (!oneMoreNonZero && count != numTerms)
			{
				if (getCoefficient(count) != 0)
					oneMoreNonZero = true;
				
				count++;
			}
		}
		
		if (!leading) // empty
			cout << "EMPTY MultivariatePolynomial: enter values for coefficients and exponents";
		else // not empty
		{
			if (getCoefficient(t) != 0) // nonzero coefficient
			{
				if (t == 0 && getCoefficient(t) < 0) // first MultivariateTerm negative
				{
					if ((getCoefficient(t) != -1 && nonConstant) || !nonConstant)
						cout << getCoefficient(t);
					else
						cout << "-";
				}
				else // not first MultivariateTerm OR nonnegative coefficient
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

// print MultivariatePolynomial
// For EU's
void MultivariatePolynomial::printMultivariatePolynomial(int player, int strat)
{
	bool nonConstant = false, oneMoreNonZero = false;
	int count = 0;
	
	simplify();
	for (int t = 0; t < numTerms; t++) // MultivariateTerms
	{
		nonConstant = false;
		for (int v = 0; v < numVariables; v++) // variables
		{
			if (getExponent(t, v) != 0)
				nonConstant = true; // at least one is nonzero
		}
		
		oneMoreNonZero = false;
		count = t + 1;
		if (t < numTerms - 1) // checks if there's one more nonzero MultivariateTerm
		{
			while (!oneMoreNonZero && count != numTerms)
			{
				if (getCoefficient(count) != 0)
					oneMoreNonZero = true;
				
				count++;
			}
		}
		
		if (!leading) // empty
			cout << "EMPTY MultivariatePolynomial: enter values for coefficients and exponents";
		else // not empty
		{
			if (getCoefficient(t) != 0) // nonzero coefficient
			{
				if (t == 0 && getCoefficient(t) < 0) // first MultivariateTerm negative
				{
					if ((getCoefficient(t) != -1 && nonConstant) || !nonConstant)
						cout << getCoefficient(t);
					else
						cout << "-";
				}
				else // not first MultivariateTerm OR nonnegative coefficient
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

// remove MultivariateTerm
void MultivariatePolynomial::removeMultivariateTerm(int &t)
{	
	int count = 0;
	MultivariateTerm* curMultivariateTerm;
	MultivariateTerm* previousMultivariateTerm;
	
	if (t == 0)
	{
		delete leading;
		leading = leading->next;
	}
	else
	{
		curMultivariateTerm = leading;
		while (count < t)
		{
			previousMultivariateTerm = curMultivariateTerm;
			curMultivariateTerm = curMultivariateTerm->next;
			count++;
		}
		previousMultivariateTerm->next = curMultivariateTerm->next;
		delete curMultivariateTerm;
		curMultivariateTerm = curMultivariateTerm->next;
	}
	numTerms--;
	t--;
}

// set EU coeffs
void MultivariatePolynomial::setEUCoefficients(vector<int> coeffs, int numPlayers) // TEST
{
	// enters coeffs into the expected utility, leaving the last MultivariateTerm as a_{n-1}
	
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
void MultivariatePolynomial::setEUExponents(vector<vector<int> > exponents) // FINISH: need number of MultivariateTerms per MultivariatePolynomial
{
	// enters exponents into the expected utility
	
	// for (int t = 0; t < numTerms; t++)
		// this->setMultivariateTerm(t, exponents.at(t));
}

// set MultivariateTerm
void MultivariatePolynomial::setMultivariateTerm(int t, MultivariateTerm* temp)
{
	this->setCoefficient(t, temp->coefficient);
	this->setExponents(t, temp->exponents);
}

// simplify
void MultivariatePolynomial::simplify()
{
	cout << "SIMPLIFY\n";
	
	bool sameAlpha = true;
	
	// getting rid of zero MultivariateTerms
	for (int t = 0; t < numTerms; t++)
	{
		cout << "t: " << t << endl;
		if (getCoefficient(t) == 0 && numTerms > 1)
		{
			// cout << "IF\n";
			removeMultivariateTerm(t);
		}
	}
	
	// combining nonzero MultivariateTerms
	for (int t1 = 0; t1 < numTerms; t1++)
	{
		cout << "t1: " << t1 << endl;
		for (int t2 = t1 + 1; t2 < numTerms; t2++)
		{
			cout << "t2: " << t2 << endl;
			sameAlpha = true;
			for (int v = 0; v < numVariables; v++)
			{
				if (getMultivariateTerm(t1)->exponents.at(v) != getMultivariateTerm(t2)->exponents.at(v))
					sameAlpha = false;
			}
			if (sameAlpha)
			{
				cout << "\tsame\n";
				setCoefficient(t1, getCoefficient(t1) + getCoefficient(t2));
				if (numTerms > 1)
					removeMultivariateTerm(t2);
			}
		}
	}
	
	cout << "DONE SIMPLIFY\n";
}

#endif