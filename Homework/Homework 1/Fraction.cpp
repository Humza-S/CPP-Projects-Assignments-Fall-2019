/*
   Name: Humza Salman
   NET ID: MHS180007
*/

#include "Fraction.h"
#include <string>

Fraction temp;

Fraction::Fraction() {
	numerator = 5;
	denominator = 7;
}

Fraction::Fraction(int numerator, int denominator) {
	this->numerator = numerator;
	this->denominator = denominator;
}
Fraction::Fraction(int numerator) {
	this->numerator = numerator;
	denominator = 10;
}

Fraction& Fraction::simplify(Fraction& fraction) {
	for (int product = abs(fraction.getNumerator() * fraction.getDenominator()); product > 1; product--) {
		if ((fraction.getNumerator() % product == 0) && (fraction.getDenominator() % product == 0)){
			fraction.setNumerator(fraction.getNumerator() / product);
			fraction.setDenominator(fraction.getDenominator() / product);
		}
	}
	return fraction;
}

Fraction& Fraction::operator+(Fraction fraction) {
	temp.setNumerator(numerator * fraction.getDenominator() + fraction.getNumerator() * denominator);
	temp.setDenominator(denominator * fraction.getDenominator());

	simplify(temp);

	return temp;
}

Fraction& Fraction::operator-(Fraction fraction) {
	//cout << "numerator: " << getNumerator() << endl;
	temp.setNumerator(numerator * fraction.getDenominator() - fraction.getNumerator() * denominator);
	//cout << "numerator: " << getNumerator() << endl;
	temp.setDenominator(denominator * fraction.getDenominator());

	simplify(temp);

	return temp;
}

Fraction& Fraction::operator*(Fraction fraction) {
	temp.setNumerator(numerator * fraction.getNumerator());
	temp.setDenominator(denominator * fraction.getDenominator());

	simplify(temp);

	return temp;
}

Fraction& Fraction::operator/(Fraction fraction) {
	temp.setNumerator(numerator * fraction.getDenominator());
	temp.setDenominator(denominator * fraction.getNumerator());

	simplify(temp);

	return temp;
}

bool Fraction::operator<(Fraction& fraction) {
	if (numerator * fraction.getDenominator() < fraction.getNumerator() * denominator)
		return true;

	return false;
}

bool Fraction::operator>(Fraction& fraction) {
	if (numerator * fraction.getDenominator() > fraction.getNumerator() * denominator)
		return true;

	return false;
}

bool Fraction::operator==(Fraction& fraction) {
	if (numerator * fraction.getDenominator() == fraction.getNumerator()* denominator)
		return true;

	return false;
}

ostream& operator<<(ostream& out, const Fraction& fraction) {
	//out << (fraction.numerator < 0) ? "-" : "";
	out << fraction.numerator << "/" << fraction.denominator;
	return out;
}

istream& operator>>(istream& in, Fraction& fraction) {
	cout << "Enter numerator: ";
	in >> fraction.numerator;
	cout << "Enter denominator: ";
	in >> fraction.denominator;
	cout << endl;
	return in;
}
