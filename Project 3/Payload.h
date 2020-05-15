/*
	Name: Humza Salman
	NET ID: MHS180007
*/

#ifndef Payload_H
#define Payload_H

#include <string>
#include <iostream>
#include <cmath>

class Payload
{
	private:
		int	coefficientNumerator;
		int coefficientDenominator;
		int exponent;
		float calculatedValue;
		std::string trigFunction;
		int trigCoefficient;
		int orderTrigTerms;
	public:
		// constructors
		Payload();
		Payload(int c, int e);
		Payload(int c, int e, int tc, std::string tf, int o);

		// accessors
		int getCoefficientNumerator() { return coefficientNumerator; };
		int getCoefficientDenominator() { return coefficientDenominator; };
		int getTrigCoefficient() { return trigCoefficient; };
		std::string getTrigFunction() { return trigFunction; };
		int getExponent() { return exponent; };

		// mutators
		void setCoefficient(int c) { coefficientNumerator = c; };
		void setExponent(int e) { exponent = e; };

		// fraction functions
		void simplify();

		// integrate functions
		void evaluateIntegral();
		float calculateIntegral(int num);

		// adds the coefficient numerators together 
		void operator+(Payload& p) {
			this->coefficientNumerator += p.coefficientNumerator;
		}

		// two paylaods are equal if they have the same exponent, trigCoefficient, and trigFunction
		bool operator==(Payload& p) {
			return ((this->exponent == p.exponent) && (this->trigCoefficient == p.trigCoefficient) && (this->trigFunction == p.trigFunction)); 
		}

		// other overloaded operators
		bool operator<(Payload& p); 
		bool operator>(Payload& p);
		friend std::ostream& operator<<(std::ostream& out, Payload* p);
		
};

#endif // !Payload_H

