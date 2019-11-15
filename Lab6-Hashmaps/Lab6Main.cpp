/*
 * Lab6Main.cpp
 *
 *  Created on: Nov 9, 2019
 *      Author: wfcan
 */

#include "MakeSeuss.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>

using namespace std;

int main() {
	// Seed random
	srand(time(NULL));

	// Four Dr. Seuss stories, each made with a different combination of the hash and collision functions.
	makeSeuss seussOne("DrSeuss.txt", "Hash1,Coll1", true, true);
	makeSeuss seussTwo("DrSeuss.txt", "Hash1,Coll2", true, false);
	makeSeuss seussThree("DrSeuss.txt", "Hash2,Coll1", false, true);
	makeSeuss seussFour("DrSeuss.txt", "Hash2,Coll2", false, false);

//	string keys[20] = {"planet", "no", "screen", "yes", "hello", "robot", "pencil", "worm", "computer",
//			"metal", "keyboard", "army", "hairstle", "egg", "ocean", "apple", "jet", "running", "leaping", "baseball"};
//	hashMap mapOne(true, true);
//
//	for (int i = 0; i < 20; i++) {
//		mapOne.addKeyValue(keys[i], "DummyValue");
//	}
//	mapOne.printMap();

	return 0;
}


