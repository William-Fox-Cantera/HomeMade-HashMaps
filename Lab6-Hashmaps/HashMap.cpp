/*
 * HashMap.cpp
 *
 *  Created on: Nov 9, 2019
 *      Author: wfcan
 */

#include "HashMap.hpp"

/*
 * hashMap, this is the constructor
 * Consumes: two booleans
 * Produces: a hashmap
 */
hashMap::hashMap(bool hash1, bool coll1) {
	first = "test";
	numKeys = 5;
	mapSize = 5;
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



