/*
	Name: Humza Salman
	NET ID: MHS180007
*/

// IGNORE FILE AS IT IS NOT FINISHED!


#ifndef HASHMAP_H
#define HASHMAP_H
#include <string>

template <typename K, typename V>

struct HashMapNode {
	K key;
	V value;
};

template <typename K, typename V>
class HashMap
{
	private:
		int buckets;
		V* map = new V[9];
		int entries;
		const float LOAD_FACTOR = 0.7;

		int hashCode(std::string key);
		int hashCode(char key);
		int hashCode(int key);
	public:
		HashMap<K, V>() {
			buckets = 9;
			entries = 0;
			/*for (int i = 0; i < size; i++)
				map[i] = 0;*/
		};
		~HashMap() {};

		int size() { return entries; };
		bool isEmpty() { return entries == 0; };
		int hashFunction(int key, int size) { return key % size; };
		int hashPrimeFunction(int index) { 
			const int HASH_PRIME_NUMBER = 7;
			return HASH_PRIME_NUMBER - (index % HASH_PRIME_NUMBER); 
		};
		void insert(K key, V value);
		V find(K key, V value);
		void remove(K key);
		void clear() {};
		V &operator[](K key);

};

#endif // !HASHMAP_H

template<typename K, typename V>
inline int HashMap<K, V>::hashCode(int key)
{
	return key;
}

template<typename K, typename V>
inline int HashMap<K, V>::hashCode(char key)
{
	return (int)key;
}

template<typename K, typename V>
inline int HashMap<K, V>::hashCode(std::string key)
{
	const int INITIAL_VALUE = 1;
	const int HASH_MULTIPLIER = 7;
	int stringHash = INITIAL_VALUE;
	for (char ch : key)
		stringHash = (stringHash * HASH_MULTIPLIER) + int(ch);
	return stringHash;
}

template<typename K, typename V>
inline void HashMap<K, V>::insert(K key, V value)
{
	int h1 = hashFunction(key, size);
	int h2 = hashPrimeFunction(key, size);
}

template<typename K, typename V>
inline V HashMap<K, V>::find(K key, V value)
{

	return V();
}

template<typename K, typename V>
inline void HashMap<K, V>::remove(K key)
{
	int index = hashFunction(hashCode(key), size);
	
}

template<typename K, typename V>
inline V& HashMap<K, V>::operator[](K key)
{
	// TODO: insert return statement here
}
