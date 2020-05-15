/*
	Name: Humza Salman
	NET ID: MHS180007
*/

#include "Payload.h"

// default constructor
Payload::Payload()
{
	coefficientNumerator = 0;
	coefficientDenominator = 1;
	exponent = 0;
	calculatedValue = 0;
	trigFunction = "";
	trigCoefficient = 0;
	orderTrigTerms = 0;
}

// overloaded polynomial constructor
Payload::Payload(int c, int e)
{
	coefficientNumerator = c;
	coefficientDenominator = 1;
	exponent = e;
	calculatedValue = 0;
	trigFunction = "";
	trigCoefficient = 0;
	orderTrigTerms = 0;
}

// overloaded trig constructor
Payload::Payload(int c, int e, int tc, std::string tf, int o)
{
	coefficientNumerator = c;
	coefficientDenominator = 1;
	exponent = e;
	calculatedValue = 0;
	trigCoefficient = tc;
	trigFunction = tf;
	orderTrigTerms = o;
}

// simplifies the fraction (numerator and denominator)
void Payload::simplify()
{
	// starts at the absolute value of the product of numerator and denominator
	for (int product = abs(coefficientNumerator * coefficientDenominator); product > 1; product--) {
		if ((coefficientNumerator % product == 0) && (coefficientDenominator % product == 0)) { // only reduces if both numerator and denominator are divisors of product
			coefficientNumerator = coefficientNumerator / product;
			coefficientDenominator = coefficientDenominator / product;
		}
	}
}

// evaluates the integral using the payload
void Payload::evaluateIntegral()
{
	if (trigFunction != "") { // evaluates integral for a trig function payload
		
		if (trigFunction == "sin") { // evaluating a sin trig function; e.g. | sin x dx = -cos x + C
			coefficientNumerator *= -1;
			coefficientDenominator = abs(trigCoefficient); 
			trigFunction = "cos";
		}
		else if (trigFunction == "cos") { // evaluating a cos trig function; e.g. | cos x dx = sin x + C
			coefficientDenominator = abs(trigCoefficient);
			trigFunction = "sin";
		}
		if (trigCoefficient < 0)
			coefficientNumerator *= -1; // if the trig coefficient is negative, then it multiplies the numerator by -1
	}
	else { // evaluates integrals for a polynoimal payload
		coefficientDenominator = abs(exponent + 1);
		if (exponent + 1 < 0)
			coefficientNumerator *= -1; // if the exponent is less than 0, multiplies the numerator by -1
		exponent++;
	}
	simplify(); // simplifying the fraction
}

// calculates the value of the payload based on the value passed in
float Payload::calculateIntegral(int num)
{
	// calculates the integral and makes sure it isn't being divided by zero
	calculatedValue = (this->coefficientDenominator == 0) ? 0 : 
		(float)this->coefficientNumerator * (float)std::pow(num, this->exponent) / (float)this->coefficientDenominator;
	return calculatedValue;
}

// operator overload for '<' so that regular payloads are compared via their exponents and trig payloads are compared via their insertion order
bool Payload::operator<(Payload& p)
{
	if (p.trigFunction != "") {
		if (this->trigFunction == "") // if the payload being compared to is a trig function
			return false;
		else if (this->trigFunction != "") // values that are trig functions are only considered to be less if they were inserted into the tree after another trig function
			return this->orderTrigTerms > p.orderTrigTerms;
	}
	else if (this->trigFunction != "") { // if the object comparing is a trig function, it is greater than what it is being compared to 
		return true;
	}
	return this->exponent < p.exponent; // use exponents to compare normal polynomials
}

// operator overload for '>' so that regular payloads are compared via their exponents and trig payloads are compared via their insertion order
bool Payload::operator>(Payload& p)
{
	if (p.trigFunction != "") { // if the payload being compared to is a trig function
		if (this->trigFunction == "") // values that are NOT trig function are automatically considered to be greater than trig functions
			return true;
		else if (this->trigFunction != "") // values that are trig functions are only considered to be greater if they were inserted into the tree before another trig function
			return this->orderTrigTerms < p.orderTrigTerms;
	}
	else if (this->trigFunction != "") { // if the object comparing is a trig function, it is NOT greater than what it is being compared to 
		return false;
	}
	return this->exponent > p.exponent; // use exponents to compare normal polynomials
}

// outputs the payload
std::ostream& operator<<(std::ostream& out, Payload* p)
{
	if (p->coefficientNumerator < 0) // outputs the negative if a coefficient is less than 0
		out << "-";

	// outputs the coefficient of the term
	if (p->coefficientNumerator == 0 || p->coefficientNumerator == 1)
		out << p->coefficientNumerator;
	else if (p->coefficientDenominator != 0 && p->coefficientDenominator != 1)
		out << "(" << abs(p->coefficientNumerator) << "/" << abs(p->coefficientDenominator) << ")";
	else if (p->coefficientNumerator != 0 || p->coefficientDenominator == 0 || p->coefficientDenominator == 1)
		if (p->coefficientNumerator != 1 && p->coefficientNumerator != -1 && p->coefficientNumerator != 0 && p->exponent != 0)
			out << abs(p->coefficientNumerator);

	// outputting trig terms
	if (p->trigFunction != "") {
		out << p->trigFunction << " ";
		if (p->trigCoefficient != 1 && p->trigCoefficient != 0)
			out << p->trigCoefficient;
	}

	// outputs the variable
	if (p->coefficientNumerator != 0)
		out << "x";

	// outputs the exponent
	if (p->exponent != 1 && p->exponent != 0 && p->trigFunction == "" && p->coefficientNumerator != 0)
		out << "^" << p->exponent;
	return out;
}