/*
	Names:
		Humza Salman | MHS180007
		Evelyn Smith | TSS180005
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

int sum(int* arr, int& size);
int low(int* arr, int& size);
int high(int* arr, int& size);
double avg(int* arr, int& size);
int* updateArray(int* arr, int& size);

int main()
{
	ifstream input;
	input.open("Random.txt");

	int size = 1;
	int* numArray = new int[size];
	int tab = 1;

	if (input) {
		int* ptr = numArray;
		while (!input.eof()) {
			input >> *ptr;

			ptr = updateArray(numArray, size);

			ptr++;
		}
	}
	input.close();

	cout << "size: " << size << endl;
	cout << *(numArray + 1) << endl;

	cout << "SUM: " << sum(numArray, size) << endl;
	cout << "LOW: " << low(numArray, size) << endl;
	cout << "HIGH: " << high(numArray, size) << endl;
	cout << "AVERAGE: " << avg(numArray, size) << endl;

}

int sum(int* arr, int& size) {
	int* ptr = arr;
	int sum = 0;
	for (int i = 0; i < size - 99; i++) {
		sum += *ptr;
		ptr++;
	}
	return sum;
}
int low(int* arr, int& size) {
	int low = arr[0];
	for (int i = 0; i < size; i++) {
		if (low > * arr)
			low = *arr;
		arr++;
	}
	return low;
}
int high(int* arr, int& size) {
	int high = arr[0];
	for (int i = 0; i < size; i++) {
		if (high < *arr)
			high = *arr;
		arr++;
	}
	return high;
}
double avg(int* arr, int& size) {
	return ((double)sum(arr, size) / (double)size);
}

int* updateArray(int* arr, int& size) {
	int* temp = new int[size + 1];

	for (int i = 0; i < size; i++) {
		*temp = *arr;
		temp++;
		arr++;
	}
	arr = temp - size;
	size++;
	return temp - size;
}
