/*
 * MakeSeuss.hpp
 *
 *  Created on: Nov 9, 2019
 *      Author: wfcan
 */

#ifndef MAKESEUSS_HPP_
#define MAKESEUSS_HPP_

#include "HashMap.hpp"

class makeSeuss {

	friend class hashMap;
public:
	hashMap *ht;
	string fn; // file name for input (“DrSeuss.txt”)
	string newfile; // name of output file

	makeSeuss(string file, string newf, bool h1, bool c1);
	void readFile();
	void writeFile();
};

#endif /* MAKESEUSS_HPP_ */
