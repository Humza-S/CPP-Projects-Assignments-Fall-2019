/*
	Name: Humza Salman || Mike Yu
	NETID: MHS180007 || WXY180003
*/

#include "Node.h"
#include "LinkList.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int outPrecedence(char input);
int inPrecedence(char input);

int main()
{
	/*enum Precedence {
		'^', 
	};*/
	ifstream input;
	input.open("sample.txt");

	LinkList* expression = new LinkList();
	LinkList* stack = new LinkList();
	string exp = "";

	if (input) {
		while (!input.eof()) {
			string line;
			getline(input, line);
			for (char c : line) {
				if (c != ' ') {
					if (isalpha(c)) { // operand encountered
						//expression->append(c);
						cout << c;
					}
					else if (c == '(') { // ( encountered
						stack->append(c);
					}
					else if (c == '^' || c == '*' || c == '%' || 
							 c == '/' || c == '+' || c == '-') { // operator encountered
						if (stack->isEmpty()) {
							stack->append(c);
						}
						else {
							while (!stack->isEmpty() && outPrecedence(c) < inPrecedence(c)) {
								/*char temp = stack->pop();
								expression->append(temp);*/
								cout << stack->peek();
								stack->pop();
							}
							stack->append(c);
						}
						
					}
					else if (c == ')') {
						//char temp = stack->pop();
						while (stack->peek() != '(') {
							/*char temp = stack->pop();
							expression->append(temp);*/
							cout << stack->peek();
							stack->pop();
							if (stack->isEmpty())
								break;
						}
						/*char temp = stack->pop();
						expression->append(temp);*/
						stack->pop();
					}
				}
			}
			while (!stack->isEmpty()) {
				if (stack->peek() == '(') {
					break;
				}
				/*char temp = stack->pop();
				expression->append(temp);*/
				cout << stack->peek();
				stack->pop();
			}
		}
	}
	//expression->print();
}

int outPrecedence(char input) {
	switch (input) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 3;
	case '^':
		return 6;
	case '(':
		return 100;
	}
}

int inPrecedence(char input) {
	switch (input) {
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 4;
	case '^':
		return 5;
	case '(':
		return 0;
	}
}