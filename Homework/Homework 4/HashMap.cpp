/*
	Name: Humza Salman
	Net ID: MHS180007
*/

#include "HashMap.h"
#include <iostream>
#include <functional>
void HashMap::insert(int key)
{
	//std::cout << "e/s:" << (float)entries / (float)size;
	if (LOAD_FACTOR < (float)entries / (float)size) {
		rehash();
		//printHash();
		//printEntriesAndSize();
	}

	int x = 1;
	int bucketsProbed = 0;
	int index = hashFunction(key, size);
	while (bucketsProbed < size) {
		if (arr[index] == 0) {
			arr[index] = key;
			entries++;
			return;
		}
		index = (index + x * x) % size;
		x++;
		bucketsProbed++;
	}	
}

void HashMap::rehash()
{
	std::cout<<"\nrehashing\n";

	int newSize = size * 2;
	int* newArr = new int[newSize];
	for (int i = 0; i < newSize; i++) {
		newArr[i] = 0;
	}

	int bucket = 0;
	entries = 0;
	while (bucket < size) {
		if (arr[bucket] != 0) { // 0 is used to indicate an empty bucket, so if the bucket is not empty
			int key = arr[bucket];

			int x = 1;
			int bucketsProbed = 0;
			int index = hashFunction(key, newSize);
			while (bucketsProbed < newSize) {
				if (newArr[index] == 0) {
					newArr[index] = key;
					entries++;
					break;
				}
				index = (index + x * x) % newSize;
				x++;
				bucketsProbed++;
			}
		}
		bucket++;
		if (bucket == size)
			break;
	}
	delete[] arr;
	arr = newArr;
	size = newSize;
}

void HashMap::printHash()
{
	std::cout << "\n";
	std::string delimeter = "";
	for (int i = 0; i < size; i++) {
		delimeter = ", ";
		std::cout << arr[i] << delimeter;
	}
	std::cout << "\n";
}

void HashMap::printEntriesAndSize()
{
	std::cout << "\nSize: " << size << "\tEntries: " << entries << "\n";
}
