#pragma once
///////////////////////////////////////////////////////////
// Map.h
// CIS687 Object Oriented Design in C++
// Emmanuell Sevieux - October 13, 2022
// Project 1 - MapReduce Team Project 
// Map Class: The map class will contain a public method map(), that accepts a key and
// value.The key will be the file nameand the value will be a single line of raw data from
// the file.The map() function will tokenize the value into distinct words(remove
//	punctuation, whitespaceand capitalization).The map() function will call a second
//	function export that takes a keyand value as two parameters.The export function will
//	buffer output in memoryand periodically write the data out to disk(periodicity can be
//	based on the size of the buffer).The intermediate data will be written to the temporary
// 	directory(specified via command line).
///////////////////////////////////////////////////////////

#ifndef _Map_h_
#define _Map_h_
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ostream;
//using std::operator<<;

typedef std::pair<string, int> tokenPair;

//ostream& operator<<(ostream& os, const tokenPair tp);

ostream& operator<<(ostream& os, const tokenPair& tp);
class Map
{
public:

	//ostream operator for testing ( cout << map::obj )
	friend ostream& operator<<(ostream& os, const tokenPair& tp);

	//default constructor
	Map();

	//constructor with buffersize set
	Map(int maxBufferSize);

	//Destructor
	~Map(); 

	//tokenizes words, accepts a key(filename) and value(single line) from fileIO
	void map(string filename, string inputLine);

	//accepts key(filename) and value(vector of tokenized strings) sends to output when buffer is full
	void bufferTokens(string filename, string token);

	//empties buffer
	bool emptyCache();

	vector<string>& mapExport(); //copy exportBuffer and clear it's contents

	// converts a string into lowercase
	string lowerCase(const string&); 

private:
	int bufferSize{ 10 }; //size of buffer
	vector<string> exportBuffer; //formatted as string of tokens ("token1",1),("token2",2),... 
	vector<tokenPair> tokenWords; //private data member tokenPair ("",int)
	bool bufferExported{ false }; //clears exportBuffer when true
	int maxBufferSize{};

};

#endif