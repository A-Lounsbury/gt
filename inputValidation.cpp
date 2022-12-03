/*******************************
Title: inputValidation.cpp
Author: Andrew Lounsbury
Date: 5/9/2020
Purpose: function for validating input
********************************/

#include <iostream>
#include <limits>
using namespace std;

// checks a < n < b
void validate(int &n, int a, int b)
{
	while (!cin)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nINVALID INPUT: must be an integer.\n";
		cout << "Enter an integer from " << a << " to " << b << ".  ";
		cin >> n;
		validate(n, a, b);
	}
	while (n < a || n > b)
	{
		cin.clear();
		cout << "\nINVALID INPUT: must be between " << a << " and " << b << ".\n";
		cout << "Enter an integer from " << a << " to " << b << ".  ";
		cin >> n;
		validate(n, a, b);
	}
}

// checks a < n < b
void validateDouble(double &n, int a, int b)
{
	while (!cin)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nINVALID INPUT: must be a rational number.\n";
		cout << "Enter a rational number from " << a << " to " << b << ".  ";
		cin >> n;
	}
	while (n < a || n > b)
	{
		cin.clear();
		cout << "\nINVALID INPUT: must be between " << a << " and " << b << ".\n";
		cout << "Enter a rational number from " << a << " to " << b << ".  ";
		cin >> n;
		validateDouble(n, a, b);
	}
}

void validateChar(char &choice)
{
	while (choice != 'y' && choice != 'n')
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nINVALID INPUT: Enter either y or n.  ";
		cin >> choice;
		validateChar(choice);
	}
}

void validateNumPlayers(int &n)
{
	while (n < 2 || n > 4)
	{
		cin.clear();
		if (n < 2)
			cout << "ERROR: game must have at least two players\n";
		else if (n > 4)
			cout << "ILL-ADVISED INPUT: too many players can lead to a massive amount of matrices\n";
		
		cout << "Enter number of players from 2 to 4:  ";
		cin >> n;
		validateNumPlayers(n);
	}
}

void validateNumStrats(int &n, int b)
{
	while (n < 2 || n > b)
	{
		cin.clear();
		if (n < 2)
			cout << "ERROR: player must have at least 2 strategies\n";
		else if (n > b)
			cout << "ILL-ADVISED INPUT: too many players can lead to a massive amount of matrices\n";
		
		cout << "Enter number of players from 2 to " << b << ":  ";
		cin >> n;
		validateNumPlayers(n);
	}
}

void validateTypeInt(int &n)
{
	while (!cin)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nINVALID INPUT: must be an integer.\n";
		cout << "Enter an integer.  ";
		cin >> n;
		validateTypeInt(n);
	}
}

void validateTypeDouble(double &n)
{
	while (!cin)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nINVALID INPUT: must be an integer.\n";
		cout << "Enter a rational number.  ";
		cin >> n;
		validateTypeDouble(n);
	}
}