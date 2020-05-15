/*
   Name: Humza Salman
   NET ID: MHS180007
*/

#include "Fraction.h"

#include <iostream>

using namespace std;

int main() {
	Fraction fraction1(3, 4);
	Fraction fraction2;

	cout << boolalpha;

	cout << "Original Fraction1: " << fraction1 << endl;
	cout << "Original Fraction2: " << fraction2 << endl << endl;

	cin >> fraction2;
	fraction2.simplify(fraction2);

	cout << "Fraction1: " << fraction1 << endl;
	cout << "Fraction2: " << fraction2 << endl << endl;

	cout << "Addition: ";
	cout << fraction1 + fraction2 << endl << endl;

	cout << "Subtraction: ";
	cout << fraction1 - fraction2 << endl << endl;

	cout << "Multiplication: ";
	cout << fraction1 * fraction2 << endl << endl;

	cout << "Division: ";
	cout << fraction1 / fraction2 << endl << endl;

	cout << "Less Than: ";
	cout << (fraction1 < fraction2) << endl << endl;

	cout << "Greater Than: ";
	cout << (fraction1 > fraction2) << endl << endl;

	cout << "Equal To: ";
	cout << (fraction1 == fraction2);



	return 0;
}
