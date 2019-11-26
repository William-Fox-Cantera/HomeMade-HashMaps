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

	// UNCOMMENT TO SEE TESTS FOR findKey AND printMap
//	string keys[20] = {"planet", "no", "screen", "yes", "hello", "robot", "pencil", "worm", "computer",
//			"metal", "keyboard", "army", "hairstle", "egg", "ocean", "apple", "jet", "running", "leaping", "baseball"};
//	hashMap mapOne(true, false);
//
//	cout << "Printing Map:\n " << endl;
//	for (int i = 0; i < 20; i++) {
//		mapOne.addKeyValue(keys[i], "DummyValue");
//	}
//	mapOne.printMap();
//
//	cout << "\nTests for the findKey() method, remember, if a -1 is returned, that means the key is not in the map." << endl;
//	cout << "\nFind Test One: " << endl;
//	cout << "Finding: planet-> " << mapOne.findKey("planet") << endl;
//	cout << "\nFind test Two: " << endl;
//	cout << "Finding: hedgehog-> " << mapOne.findKey("hedgehog") << endl;
//	cout << "\nFind Test Three: " << endl;
//	cout << "Finding: egg-> " << mapOne.findKey("egg") << endl;
//	cout << "\nFind Test Four: " << endl;
//	cout << "Finding: running-> " << mapOne.findKey("running") << endl;
//	cout << "\nFind Test Five: " << endl;
//	cout << "Finding: desk-> " << mapOne.findKey("desk") << endl;

	return 0;
}


