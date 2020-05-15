/*
	Name: Humza Salman
	NET ID: MHS180007
*/

#include "SortSearch.cpp"
#include <iostream>

using namespace std;

int main()
{
	//int vector
	vector<int> vect1 = { 2, 18, 1, 9, 7, 20, };
	cout << "Int Vector: ";
	printVector(vect1);
	cout << "Sorted: ";
	sortVector(vect1);
	printVector(vect1);
	cout << endl;
	
	//double/float vector
	vector<double> vect2 = { 2.6, 18.7, 1.1, 9.2, 7.6, 20.2, };
	cout << "Double/Float Vector: ";
	printVector(vect2);
	cout << "Sorted: ";
	sortVector(vect2);
	printVector(vect2);
	cout << endl;

	//string vector
	vector<string> vect3 = { "a", "e", "d", "c", "f", "k", "z", "q" };
	cout << "String Vector: ";
	printVector(vect3);
	cout << "Sorted: ";
	sortVector(vect3);
	printVector(vect3);
	cout << endl;
}
