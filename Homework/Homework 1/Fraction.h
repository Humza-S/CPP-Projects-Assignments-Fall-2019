/*
   Name: Humza Salman
   NET ID: MHS180007
*/

#ifndef Fraction_h
#define Fraction_h

#include <iostream>
#include <string>

using namespace std;

class Fraction
{
private:
	int numerator;
	int denominator;

public:
	//constructors
	Fraction(); //default constructor
	Fraction(int numerator, int denominator); //overloaded contructor
	Fraction(int numerator); //overloaded constructor

	//accesors
	int getNumerator() { return numerator; };
	int getDenominator() { return denominator; };

	//mutators
	void setNumerator(int newNumerator) {
		numerator = newNumerator;
	};

	void setDenominator(int newDenominator) {
		denominator = newDenominator;
	};

	//functions
	Fraction& simplify(Fraction&);

	//overloaded operators
	Fraction& operator+(Fraction);
	Fraction& operator-(Fraction);
	Fraction& operator*(Fraction);
	Fraction& operator/(Fraction);
	bool operator<(Fraction&);
	bool operator>(Fraction&);
	bool operator==(Fraction&);

	friend ostream& operator<<(ostream&, const Fraction&);
	friend istream& operator>>(istream&, Fraction&);

};
#endif

