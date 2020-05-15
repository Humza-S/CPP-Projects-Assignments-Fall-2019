/*
	Name: Humza Salman
	NET ID: MHS180007
*/

#ifndef SORTSEARCH_H
#define SORTSEARCH_H
#include <vector>

template<typename T>
class SortSearch {
public:
	SortSearch() {};
	void sortVector(std::vector<T>& vect) {};
	int searchVector(std::vector<T>& vect, int left, int right, T key) {};
	void printVector(std::vector<T>& vect) {};
};

#endif // !SORTSEARCH_H