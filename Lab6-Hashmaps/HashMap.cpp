/*
 * HashMap.cpp
 *
 *  Created on: Nov 9, 2019
 *      Author: wfcan
 */

#include "HashMap.hpp"
#include <math.h>

/*
 * hashMap, this is the constructor
 *
 * Consumes: two booleans
 * Produces: a hashmap
 */
hashMap::hashMap(bool hash1, bool coll1) {
	first = "the";
	numKeys = 0;
	mapSize = 10;
	getClosestPrime(); // Sets the mapSize attribute to the prime closest to double the current mapSize
	h1 = hash1;
	c1 = coll1;
	collisionct1 = 0;
	collisionct2 = 0;

	// Make the map, initialize all nodes to NULL
	map = new hashNode*[mapSize];
	for (int i = 0; i < mapSize; i++) {
		map[i] = NULL;
	}
}

/*
 * addKeyValue, adds a node to the map at the correct index based on the key string, and then inserts the value into the
 * values field of the hashNode
 * Must check to see whether there's a node at that location. If there's nothing there (it's NULL), add the
 * hashNode with the keyword and value.
 * If the node has the same keyword, just add the value to the list of values.
 * If the node has a different keyword, keep calculating a new hash index until either the keyword matches
 * the node at that index's keyword, or until the
 * map at that index is NULL, in which case you'll add the node there.
 * This method also checks for load, and if the load is over 70%, it calls the reHash method to create a new
 * longer map array and rehash the values
 * if h1 is true, the first hash function is used, and if it’s false, the second is used.
 * if c1 is true, the first collision method is used, and if it’s false, the second is used
 *
 * Consumes: Two strings
 * Produces: Nothing
 */
void hashMap::addKeyValue(string k, string v) {
	int index = getIndex(k);
	hashNode *newNode = new hashNode(k);
	// Check to see if there's another node at the index
	if (map[index] == NULL) {
		map[index] = newNode;
		map[index]->addValue(v);
	} else if (map[index]->keyword == k) {
		map[index]->addValue(v);
	} else { // If the index in the map is not empty and has a different keyword
		int newIndex;
		if (c1) { // If the constructor says to use the first collision function
			newIndex = collHash1(index, k);
		} else { // Else use the second
			newIndex = collHash2(index, k);
		}
		// Insert at new index
		if (map[newIndex] == NULL) {
			map[newIndex] = newNode;
			map[newIndex]->addValue(v);
		} else { // If the new index has the same key value
			map[newIndex]->addValue(v);
		}
	}

	numKeys++;
	// Double the size and reHash if over 70% full
	reHash();
}

/*
 * getIndex, uses calcHash and reHash to calculate and return the index of where the keyword
 *			 k should be inserted into the map array
 *
 * Consumes: A string
 * Produces: An interger
 */
int hashMap::getIndex(string k) {
	int index;

	if (h1) { // If the constructor says to use the first hash function
		index = calcHash(k);
	} else { // Else use the second hash function
		index = calcHash2(k);
	}

	return index;
}

/*
 * calcHash, hash function 1. I made this function sum the ascii values of each character in the string
 * 			 then mod by the mapSize.
 *
 * Consumes: A string
 * Produces: An integer
 */
int hashMap::calcHash(string k) {
	int sum = 0;
	int hashValue;

	for (char letter : k) {
		sum = sum + letter;
	}
	hashValue = sum % mapSize;
	return hashValue;
}

/*
 * calcHash2, hash function 2, This one multiplies the ascii values of the first and last characters of the string, then the 2nd and len-1
 * 							   and so on. Once these are summed up it mods by the map size.
 *
 * Consumes: A string
 * Produces: An integer
 */
int hashMap::calcHash2(string k) {
	int kSize = k.size();
	int hashValue = 0;

	for (int i = 0; i < kSize; i++) {
		// Cast the character at i to int (its ascii value)
		hashValue = hashValue + (int(k[i]) * int(k[kSize-i-1]));
	}
	hashValue = hashValue % mapSize;
	return hashValue;
}

/*
 * isPrime, dertermines whether or not a number is prime or not
 *
 * Consumes: An integer
 * Produces: A boolean
 */
bool hashMap::isPrime(int x) {
	bool isPrime = true;

	if (x <= 1) {
		isPrime = false;
	}

	for (int i = 2; i < x; i++) {
		if (x % i == 0) {
			isPrime = false;
			break;
		}
	}

	return isPrime;
}

/*
 * getClosestPrime, I used a binary search on an array of prime numbers to find the closest prime
 * to double the map Size, and then set mapSize to that new prime. You can include as one of the fields an array of
 * prime numbers, or you can write a function that calculates the next prime number. Whichever you prefer.
 *
 * Consumes: Nothing
 * Produces: Nothing
 */
void hashMap::getClosestPrime() {
	int closestPrime = mapSize * 2;

	// Uses isPrime and an incrementor to check double the mapSize + 1 until it finds a prime
	while (true) {
		if (isPrime(closestPrime)) {
			mapSize = closestPrime;
			break;
		}
		closestPrime++;
	}
}

/*
 * rehash, when size of array is at 70%, double array size and rehash keys
 *
 * Consumes: Nothing
 * Produces: Nothing
 */
void hashMap::reHash() {
	// If the map is over 70% full double the size
	double percentFull = double(numKeys) / double(mapSize);
	if (percentFull > .7) {
		const int tempSize = mapSize;
		// Remember this method increases the map size
		getClosestPrime();
		//cout << "MAPSIZE " << mapSize << endl;
		hashNode **tempMap = new hashNode*[mapSize];
		for (int i = 0; i < mapSize; i++) {
			tempMap[i] = NULL;
		}

		for (int i = 0; i < tempSize; i++) {
			if (map[i] != NULL) {
				int rehash = getIndex(map[i]->keyword);
				if (tempMap[rehash] == NULL) {
					tempMap[rehash] = map[i];
				} else {
					if (c1) { // Uses linear probing
						while (tempMap[rehash] != NULL) {
							if (rehash == mapSize) {
								rehash = 0;
							}
							rehash++;
						}
						tempMap[rehash] = map[i];
					} else { // Uses quadratic probing
						while (tempMap[rehash] != NULL) {
							if (rehash == mapSize) {
								rehash = 0;
							}
							rehash++;
						}
						tempMap[rehash] = map[i];
					}
					tempMap[rehash] = map[i];
				}
			}
		}
		delete [] map;
		map = tempMap;
	}
}

/*
 * collHash1, getting index with collision method 1 (note – you may modify the
 * 			  parameters if you don’t need some/need more). This method uses linear probing.
 *
 * Consumes: An integer and a string
 * Produces: An integer
 */
int hashMap::collHash1(int i, string k) {
	while (map[i] != NULL) {
		if (map[i]->keyword == k) {
			break;
		}
		if (i == mapSize) {
			i = 0;
		}
		i++;
	}
	return i;
}

/*
 * collHash2, getting index with collision method 2 (note – you may modify the
 *			  parameters if you don’t need some/need more). This method uses quadratic probing.
 *
 * Consumes: An integer and a string
 * Produces: An integer
 */
int hashMap::collHash2(int i, string k) {
	while (map[i] != NULL) {
		if (map[i]->keyword == k) {
			break;
		}

		if (i == mapSize) {
			i = 0;
		}
		i++;

	}
	return i;
}

/*
 * findKey, finds the key in the array and returns its index. If it's not in the array,
 *			returns -1
 *
 *	Consumes: A string
 *	Produces: an integer
 */
int hashMap::findKey(string k) {
	int indexToReturn = -1;
	int startingIndex = getIndex(k);

	if (map[startingIndex] != NULL) {
		if (map[startingIndex]->keyword == k) {
			// If the index returned from the get index funtion is the correct one on the first try
			indexToReturn = startingIndex;
		} else {
			while (map[startingIndex] != NULL) {
				if (map[startingIndex]->keyword == k) {
					break;
				}
				startingIndex++;
			}
		}
	}

	return indexToReturn-1;
}

/*
 * printMap, prints the map
 *
 * Consumes: Nothing
 * Produces: Nothing
 */
void hashMap::printMap() {
	int count = 0;
	for (int i = 0; i < mapSize; i++) {
		if (map[i] != NULL) {
			cout << "Key: " << map[i]->keyword << endl;
			count++;
		} else {
			cout << "NULL" << endl;
		}
	}
	cout << "COUNT: " << count << endl;
}


