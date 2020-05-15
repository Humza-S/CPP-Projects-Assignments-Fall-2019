/*
	Name: Humza Salman
	Net ID: MHS180007
*/

#include <iostream>
#include "HashMap.h"

using namespace std;

int main()
{
	HashMap* hash = new HashMap();
	for (int i = 0; i < 20; i++) {
		hash->insert(rand() % 899 + 100);
		if (i % 4 == 0 && i != 0) {
			hash->printHash();
			hash->printEntriesAndSize();
		}
	}

	return 0;
}