/*
	Name: Humza Salman
	Net ID: MHS180007
*/

#pragma once
class HashMap
{
	private:
		int size;
		int entries;
		int* arr = new int[9];
		const float LOAD_FACTOR = 0.5;
	public:
		HashMap() {
			size = 9;
			entries = 0;
			for (int i = 0; i < size; i++) {
				arr[i] = 0;
			}
		}
		int hashFunction(int key, int size) {
			return key % size;
		}
		void insert(int value);
		void rehash();
		void printHash();
		void printEntriesAndSize();
};

