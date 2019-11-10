/*
 * HashNode.cpp
 *
 *  Created on: Nov 9, 2019
 *      Author: wfcan
 */

#include "HashNode.hpp"

/*
 * hashNode, this is the constructor for teh hashNode class, initializes keyword to "",
 * 			 valuesSize to 0, and currSize to 0 and values to NULL.
 *
 * Consumes: Nothing
 * Produces: A hashNode
 */
hashNode::hashNode() {
	keyword = "";
	valuesSize = 0;
	currSize = 0;
	values = NULL;
}

/*
 * hashNode, another constructor (overloaded), initializes keyword to s, the valuesSize to 100
 * (or whatever you like for starting), the currSize to 0, and the values to be a dynamically allocated array of valuesSize
 *
 * Consumes: A string
 * Produces: A hashNode
 */
hashNode::hashNode(string s) {
	keyword = s;
	valuesSize = 100;
	currSize = 0;
	values = new string[valuesSize];
}

/*
 * hashNode, yet another constructor (overloaded), in addition, puts a value in the values array and initializes currSize to 1
 *
 * Consumes: Two strings
 * Produces: A hashNode
 */
hashNode::hashNode(string s, string v) {
	keyword = s;
	valuesSize = 100;
	currSize = 1;
	values = new string[valuesSize];
	values[0] = v;
}

/*
 * addValue, adds a new value to the end of the values array, increases currSize, checks to make sure
 *           there’s more space, and, if not, calls dblArray()
 *
 * Consumes: A string
 * Produces: Nothing
 */
void hashNode::addValue(string v) {
	// Handles the case where values is initially empty
	values[currSize] = v;
	currSize++;

	// Double the size of the values array if it is full
	if (currSize == valuesSize) {
		dblArray();
	}
}

/*
 * dblArray, creates a new array, double the length, and copies over the values. Sets the values array to
 *           be the newly allocated array.
 *
 * Consumes: Nothing
 * Produces: Nothing
 */
void hashNode::dblArray() {
	int previousSize = valuesSize;
	valuesSize *= 2;
	string *newArr = new string[valuesSize];

	// Copy values over
	for (int i = 0; i < previousSize; i++) {
		newArr[i] = values[i];
	}

	// Set values array to new array
	values = newArr;
}


/*
 * getRandValue, returns a random string from the values array. If there’s no values in the value array, then it
 *			     returns an empty string.
 *
 * Consumes: Nothing
 * Produces: A string
 */
string hashNode::getRandValue() {
	string stringToReturn;
	if (currSize == 0) {
		stringToReturn = "";
	} else {
		int randomIndex = rand() % currSize;
		stringToReturn = values[randomIndex];
	}


	return stringToReturn;
}




