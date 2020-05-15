/*
	Name: Humza Salman
	NET ID: MHS180007
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>

#include "BinTree.h"
#include "BinTree.cpp"
#include "Node.h"
#include "Node.cpp"
#include "Payload.h"

using namespace std;

//prototypes
void evaluateAllIntegrals(BinTree<Payload>* tree);
void evaluateAllIntegrals(Node<Payload>* node);
float sumIntegralCalculations(BinTree<Payload>* tree, const int &var);
float sumIntegralCalculations(Node<Payload>* node, const int &var);
void printReverseInOrder(BinTree<Payload>* tree, bool &firstTerm);
void printReverseInOrder(Node<Payload>* node, bool& firstTerm);
void clear(BinTree<Payload>* tree);


int main()
{
	ifstream inputFile; // used to read in file
	string filename; // file name used to open the file

	BinTree<Payload>* tree = new BinTree<Payload>(); // intializing new tree

	cin >> filename;
	inputFile.open(filename);
	
	if (inputFile) { // checks to see if the input file is open
		while (!inputFile.eof()) { // iterates through until reaching the end of file

			// getting integral and storing into line
			string line;
			getline(inputFile, line);
			if (line.empty())  // breaks while loop if an empty line is encountered
				break;
			
			// removes ' dx' from the line since it is redundant
			line.erase(line.find(" dx"));

			// removes any spaces in the expression, except for the one before the expression begins
			line.erase(std::remove(line.begin()+line.find(' ') + 1, line.end(), ' '), line.end());
			
			
			/*
			Regex pattern to evaluate the integral range.

			Part 1: Checks to see if the first integer is present and if it is negative or not. 
			Part 2: There will always be a '|' (since we are evaluating integrals) so it expects that that. 
			Part 3: Checks to see if there the upper value of the integral range and if it is negative or not.
			*/
			regex pipePattern(R"((-?\d*)?(\|)(-?\d*)?)"); 		

			smatch pipeMatch; // string match to be used with regex for the integral range

			int from = 0, to = 0; // values to store the range of the integral
			bool definite = false; // determines if the integral is definite or indefinite

			// if there is a pipe pattern present, then it stores the values for the integral range
			if (regex_search(line, pipeMatch, pipePattern)) {
				for (int i = 0; i < (int) pipeMatch.size(); i++) {
					if (i == 1 && pipeMatch.str(i).size() > 0) {
						from = stoi(pipeMatch.str(i)); // stores the beginning of the integral range
						definite = true; // if it finds the beginning endpoint, the integral is definite
					}
					else if (i == 3 && pipeMatch.str(i).size() > 0) {
						to = stoi(pipeMatch.str(i)); // stores the ending of the integral range
					}
				}
			}

			// parses the line such that the integral range and the space after is gone, leaving only the  expression
			line = line.substr(line.find(' ')+1);


			/*
			Regex pattern to evaluate the payload.

			Part 1: checks to see if there is a coefficient present and if that coefficient is a negative.
			Part 2: encompasses the trig term
			Part 3: checks to see the trig term itself: sin, cos
			Part 4: checks to see if there is a coefficient inside of trig term
			Part 5: checks to see if there is a variable
			Part 6: encompasses the exponent term
			Part 7: checks to see if there is an exponent
			*/
			regex payloadPattern(R"((-?\d*)?((sin|cos)(-?\d*)?)?(x)?(\^(-?\d*))?)");

			smatch payloadMatch; // string match to be used for the payload

			int orderTrigTerms = 1; // first trig term has the highest priority to be outputted first

			// while there is still a payload present in the expression which matches the payload pattern
			while (regex_search(line, payloadMatch, payloadPattern)) {

				int coeff = 1; // coefficient will be 1 by default
				int exp = 0; // exponent will be 0 by default
				int trigCoeff = 1; // coefficient inside of trig function will be 1 by default | e.g. sin x, coefficient of x is 1

				string var = ""; // assume there is no variable initially
				string trigFunction = ""; // assume there is no trig function initially


				// goes through the payload match and stores values for the payload
				for (int i = 0; i < (int) payloadMatch.size(); ++i) {
					if (i == 1 && payloadMatch.str(i).size() > 0) {
						if(payloadMatch.str(i) == "-") // if there is only a negative sign and no digit
							coeff *= -1; // since there is a negative sign, multiplies the coefficient by -1 to make it negative;
						else
							coeff = stoi(payloadMatch.str(i)); // stores the coefficient
					}
					else if (i == 3 && payloadMatch.str(i).size() > 0) {
						trigFunction = payloadMatch.str(i); // stores the trig function
					}
					else if (i == 4 && payloadMatch.str(i).size() > 0) {
						if (payloadMatch.str(i) == "-") // checks to see if the coefficient inside the trig function is only a negative sign
							trigCoeff *= -1; // if it is, then it makes the trig coefficient -1
						else
							trigCoeff = stoi(payloadMatch.str(i)); // stores the trig coefficient
					}
					else if (i == 5 && payloadMatch.str(i).size() > 0) {
						var = payloadMatch.str(i); // stores the variable if it exists so that we know whether a term has an exponent of 1 or 0 later on
					}
					else if (i == 7 && payloadMatch.str(i).size() > 0) {
						exp = stoi(payloadMatch.str(i)); // stores the exponent
					}
				}

				// assining the exponent if the exponent is still 0, and the variable if it is empty
				if (var != "" && exp == 0)
					exp = 1; // makes exponent 1 since there was no exponent after the variable

				Payload* p; // used to create new payloads

				// inserting the payload into the tree depending on if it is a trig function or a normal polynomial
				if (trigFunction != "") {
					orderTrigTerms++; // increment the priority of the order trig terms are inserted
					p = new Payload(coeff, exp, trigCoeff, trigFunction, orderTrigTerms); // creates a new trig payload
				}
				else 
					p = new Payload(coeff, exp); // creates a new poly payload

				tree->insert(p); // inserts payload into the tree
				

				// parsing the line so that the payload just inserted is no longer a part of the line
				if ((int)line.length() > (int) payloadMatch.length()) { // line length has to be greater than the current payload length
					if (line.substr(payloadMatch.length()).at(0) == '+') { // checks to see if the expression starts with a plus
						line = line.substr(payloadMatch.length() + 1); // removes the current payload and the plus from the expression
					}
					else if (line.substr(payloadMatch.length()).at(0) == '-') { // checks to see if the expression starts with a negative
						line = line.substr(payloadMatch.length()); // removes the current payload from the expression
					}
				}
				else  // breaks the while loop if the line is no longer greater than the payload length, i.e: end of expression
					break;				
			}

			evaluateAllIntegrals(tree); // evaluates all the integrals in the tree

			bool firstTerm = true; // used to track if the first term has been printed

			cout << setprecision(3) << fixed; // used to format to 3 decimal places

			printReverseInOrder(tree, firstTerm); // outputs all the terms in the tree in descending order

			//outputs the integral format based on if it is definite or not
			if (definite)
				cout << ", " << from << "|" << to << " = " << 
				sumIntegralCalculations(tree, to) - sumIntegralCalculations(tree, from) << "\n"; // outputs the definite integral format and the value for that integral
			else 
				cout << " + C\n"; //outputs the indefinite integral format

			clear(tree); // clearing the tree to be used again for another payload
		}
	}
	delete tree;

	inputFile.close();
}

// removes every node in the tree
void clear(BinTree<Payload>* tree) {
	if (tree->getRoot()) { 
		tree->remove(tree->getRoot()->getData()); // removes the root to clear the tree
		clear(tree);
	}
}

// wrapper function to evaluate all integrals
void evaluateAllIntegrals(BinTree<Payload>* tree)
{
	if (tree->getRoot())
		evaluateAllIntegrals(tree->getRoot());
}

// recursively evaluates all integrals in an in order traversal
void evaluateAllIntegrals(Node<Payload>* node) {
	if (!node)
		return;
	evaluateAllIntegrals(node->getLeft());
	node->getData()->evaluateIntegral();
	evaluateAllIntegrals(node->getRight());
}

// wrapper function to sum up all the integral calculations
float sumIntegralCalculations(BinTree<Payload>* tree, const int &var)
{
	float sum = 0; // initially the sum is 0
	if (tree->getRoot())
		sum = sumIntegralCalculations(tree->getRoot(), var);
	return sum;
}

// recursively sums up all the calculated values for all the evaluated integrals in the tree
float sumIntegralCalculations(Node<Payload>* node, const int &var)
{
	if (!node) // if the node is null then there is no value, so returns 0
		return 0;
	return (node->getData()->calculateIntegral(var) + 
		sumIntegralCalculations(node->getLeft(), var) + 
		sumIntegralCalculations(node->getRight(), var)); // finds value in the left and right subtree and adds them
}

// wrapper function to output the tree in descending order
void printReverseInOrder(BinTree<Payload>* tree, bool &firstTerm) 
{
	if (tree->getRoot())
		printReverseInOrder(tree->getRoot(), firstTerm);
}

// recursively outputs the tree in descending order
void printReverseInOrder(Node<Payload>* node, bool &firstTerm) 
{
	if (!node)
		return;

	printReverseInOrder(node->getRight(), firstTerm); // outputs the right subtree first to achieve outputting in descending order

	Payload* p = node->getData();

	// outputting the first term's coefficient may be different due to fractions
	if (firstTerm) {
		if (p->getCoefficientNumerator() == 0)
			cout << p->getCoefficientNumerator();
		else if ( p->getCoefficientDenominator() != 0 && p->getCoefficientDenominator() != 1) {
			cout << "(" << p->getCoefficientNumerator() << "/" << p->getCoefficientDenominator() << ")";
		}
		else if (p->getCoefficientDenominator() == 0 || p->getCoefficientDenominator() == 1) {
			if (p->getCoefficientNumerator() == -1) {
				cout << "-";
			}
			else if (p->getCoefficientNumerator() != 1 && p->getCoefficientNumerator() != 0 && p->getExponent() != 0)
				cout << p->getCoefficientNumerator();
		}
		firstTerm = false;
	}
	else { // outputting coefficients that are not part of the first term 
		if (p->getCoefficientNumerator() < 0)
			cout << " - ";
		else if (p->getCoefficientNumerator() > 0)
			cout << " + ";
		if (p->getCoefficientNumerator() == 0)
			cout << p->getCoefficientNumerator();
		else if (p->getCoefficientNumerator() != 0 && p->getCoefficientDenominator() != 0 && p->getCoefficientDenominator() != 1) {
			cout << "(" << abs(p->getCoefficientNumerator()) << "/" << abs(p->getCoefficientDenominator()) << ")";
		}
		else if (p->getCoefficientDenominator() == 0 || p->getCoefficientDenominator() == 1) {
			if (p->getCoefficientNumerator() != 1 && p->getCoefficientNumerator() != -1 && p->getCoefficientNumerator() != 0 && p->getExponent() != 0)
				cout << abs(p->getCoefficientNumerator());
		}
	}
	
	// outputs the trig function if it exists
	if (p->getTrigFunction() != "") {
		cout << p->getTrigFunction() << " ";
		if (p->getTrigCoefficient() != 1 && p->getTrigCoefficient() != 0)
			cout << p->getTrigCoefficient();
	}

	// outputs the variable
	if(p->getCoefficientNumerator() != 0)
		cout << "x";

	// outputs the exponent
	if (p->getExponent() != 1 && p->getExponent() != 0 && p->getTrigFunction() == "" && p->getCoefficientNumerator() != 0)
		cout << "^" << p->getExponent();

	printReverseInOrder(node->getLeft(), firstTerm); // outputs the left subtree so to achieve outputting in descending order
}