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
	first = "";
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
		numKeys++;
	} else if (map[index]->keyword == k) {
		map[index]->addValue(v);
		// Add to the counter that keeps track of collisions caused by the hash function
		collisionct1++;
	} else { // If the index in the map is not empty and has a different keyword
		collisionct1++;
		int newIndex;
		if (c1) { // If the constructor says to use the first collision function
			newIndex = collHash1(index, map, k);
		} else { // Else use the second
			newIndex = collHash2(index, map, k);
		}
		// Insert at new index
		if (map[newIndex] == NULL) {
			map[newIndex] = newNode;
			map[newIndex]->addValue(v);
			numKeys++;
		} else { // If the new index has the same key value
			map[newIndex]->addValue(v);
		}
	}
	// ReHash if over 70% full
	double percentFull = double(numKeys) / double(mapSize);
	if (percentFull > .7) {
		reHash();
	}
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
 * calcHash, hash function 1. I made this function sum the ascii values of each character in the string, multiply it by
 * 			 a prime for better results, then mod by the mapSize.
 *
 * Consumes: A string
 * Produces: An integer
 */
int hashMap::calcHash(string k) {
	int kSize = k.size();
	int hashValue = 0;

	for (int i = 0; i < kSize; i++) {
		// Cast the character at i to int (its ascii value)
		hashValue += 31 * int(k[i]);
	}
	return hashValue % mapSize;
}

/*
 * calcHash2, hash function 2, This hashing function is similar to the first in that it adds the ascii values of each
 * 							   letter in the string, but also multiplys by a prime and divides by 2.
 *
 * Consumes: A string
 * Produces: An integer
 */
int hashMap::calcHash2(string k) {
	int kSize = k.size();
	unsigned int hashValue = 0;
	int prime = 5;

	for (int i = 0; i < kSize; i++) {
		   hashValue ^= (hashValue << prime) + (hashValue >> 2) + int(k[i]);
	}
	return hashValue % mapSize;
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
	int tempSize = mapSize;
	// Increases the map size to double then take the closest prime
	getClosestPrime();

	// Fill in the new map will NULL
	hashNode **tempMap = new hashNode*[mapSize];
	for (int i = 0; i < mapSize; i++) {
		tempMap[i] = NULL;
	}
	// Go through each spot in the old map and rehash its elements to the new map
	for (int i = 0; i < tempSize; i++) {
		if (map[i] != NULL) {
			// Rehashing, remember the hash will be done using the new larger map size.
			int index = getIndex(map[i]->keyword);

			// Handling Collisions
			if (tempMap[index] == NULL) {
				tempMap[index] = map[i];
			} else {
				if (c1) { // Uses linear probing
					index = collHash1(index, tempMap, ""); // Note the "" argument for the collision handling, there would be no
				} else { // Uses quadratic probing		   // duplicate keys as this is just copying the current map values into
					index = collHash2(index, tempMap, ""); // a bigger map. So no need to worry in this case.
				}
				tempMap[index] = map[i];
			}
		}
	}
	// Get rid of the old map and set map equal to the new dynamically allocated double size map.
	delete[] map;
	map = tempMap;
}

/*
 * collHash1, getting index with collision method 1 (note – you may modify the
 * 			  parameters if you don’t need some/need more). This method uses linear probing.
 *
 * Consumes: An integer, an array of hashnodes, and a string
 * Produces: An integer
 */
int hashMap::collHash1(int i, hashNode **aMap, string k) {
	while (aMap[i] != NULL) {
		// Exit the loop and save the index if the keywords match
		if (aMap[i]->keyword == k) {
			break;
		}
		// If the collisions reach the end of the map go back to the beginning and keep trying
		if (i >= mapSize) {
			i = 0;
		}
		i += 1;
		// Keep track of secondary collisions caused by this collision handling function
		collisionct2++;
	}
	return i;
}

/*
 * collHash2, getting index with collision method 2 (note – you may modify the
 *			  parameters if you don’t need some/need more). This method uses quadratic probing.
 *
 * Consumes: An integer, an array of hashnodes, and a string
 * Produces: An integer
 */
int hashMap::collHash2(int i, hashNode **aMap2, string k) {
	int j = 1;
	while (aMap2[i] != NULL) {
		// Exit the loop and save the index if the keywords match
		if (aMap2[i]->keyword == k) {
			break;
		}
		// start back at the ~beginning, that is (index - mapLength) and keep trying for a valid location
		i += j * j;
		if (i >= mapSize) {
			i -= mapSize;
			j = 1;
		}
		j++;
		// Keep track of secondary collisions caused by this collision handling function
		collisionct2++;
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
	int newIndex = -1; // returns -1 if the key is not in the map
	int startingIndex = getIndex(k);
	if (map[startingIndex] != NULL) {
		if (map[startingIndex]->keyword == k) {
			// If the index returned from the get index funtion is the correct one on the first try
			return startingIndex;
		}
		while (map[startingIndex] != NULL) { // Loop until the data is found in the collision cluster
			if (c1) {
				if (map[startingIndex]->keyword == k) {
					newIndex = startingIndex;
					break;
				}
				if (startingIndex >= mapSize) { // if collisions forced the data to loop back to the beginning of the map
					startingIndex = 0; // keep searching from the beginning while there are still collisions
				}
			} else { // If the second collision handling function is to be used, that is quadratic probing
				newIndex += startingIndex * startingIndex;
			}
			startingIndex++;
		}
	}
	return newIndex;
}

/*
 * printMap, prints the map
 *
 * Consumes: Nothing
 * Produces: Nothing
 */
void hashMap::printMap() {
	for (int i = 0; i < mapSize; i++) {
		if (map[i] != NULL) {
			cout << "Key: " << map[i]->keyword << endl;
			for (int j = 0; j < map[i]->currSize; j++) {
				cout << "Value(s): " << map[i]->values[j] << endl;
			}
			cout << endl;
		}
	}
	cout << "Collisions caused by the hash function: " << collisionct1 << endl;
	cout << "Collisions caused by the collision handling function: " << collisionct2 << endl;
}


