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

//	makeSeuss seussOne("DrSeuss.txt", "story", false, true);

	string keys[20] = {"planet", "no", "screen", "yes", "hello", "robot", "pencil", "worm", "computer",
			"metal", "keyboard", "army", "hairstyle", "egg", "ocean", "apple", "jet", "running", "leaping", "baseball"};
	hashMap mapOne(false, true);

	for (int i = 0; i < 20; i++) {
		mapOne.addKeyValue(keys[i], "DummyValue");
	}
	mapOne.printMap();

	return 0;
}


