/*
	Name: Humza Salman
	NET ID: MHS180007
*/

#include "SortSearch.h"
#include <iostream>
#include <vector> 


template<typename T>
void sortVector(std::vector<T> &vect) {
	for (int i = 0; i < vect.size() - 1; i++) {
		for (int j = 0; j < vect.size() - i - 1; j++) {
			if (vect[j] > vect[j + 1]) {
				T temp = vect[j];
				vect[j] = vect[j + 1];
				vect[j + 1] = temp;
			}
		}
	}
}

template<typename T>
int searchVector(std::vector<T> &vect, int left, int right, T key) {
	while (left <= right) {
		int mid = (left + right - 1) / 2;
		if (vect[mid] == key)
			return mid;
		if (vect[left < key])
			left = mid + 1;
		else
			right = mid - 1;
	}
	return -1;
}

template<typename T>
void printVector(std::vector<T> &vect) {
	std::string delim = "";
	for (int i = 0; i < (int)vect.size(); i++) {
		std::cout << delim << vect[i];
		delim = ", ";
	}
	std::cout << std::endl;
}

