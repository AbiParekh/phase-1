#pragma once
///////////////////////////////////////////////////////////
// Map.h
// CIS687 Object Oriented Design in C++
// Emmanuell Sevieux - October 13, 2022
// Project 1 - MapReduce Team Project 
///////////////////////////////////////////////////////////

#ifndef _Map_h_
#define _Map_h_
#include <iostream>
#include <string>
#include <vector>
#include "FileIO.h"

using std::string;
using std::vector;
using std::ostream;


//tokenPair Type used to create a key,value pair of words, count
typedef std::pair<string, int> tokenPair;

//Overloads << operator for streaming tokenPair type
ostream& operator<<(ostream& os, const tokenPair& tp);

class Map
{
public:

	//ostream operator for testing ( cout << map::obj )
	friend ostream& operator<<(ostream& os, const tokenPair& tp);

	//default constructor if no Directories nor buffer set
	Map();

	//default constructor if no buffer size set
	Map(const string intermediateDir);

	//constructor with buffersize set
	Map(const string intermediateDir, int sizeOfBuffer);

	//Destructor
	~Map(); 

	//tokenizes words, accepts a key(filename) and value(single line) from fileIO
	void map(string filename, string inputLine);

	//tokenizes words, accepts a key(filepath), key(filename) and value(single line) from fileIO
	void map(string filepath, string filename, string inputLine);

	//clears Maps contents, prepares to read in new file
	bool flush(const string filename);


private: /** PRIVATE MEMBER FUNCTIONS **/

	//empties buffer
	bool emptyCache();

	//accepts key(filename) and value(vector of tokenized strings) sends to output when buffer is full
	bool exportMap(string filename, string token);

	//Write contents of Buffer to file using FileIO. Buffer is emptied on this call.
	bool exportMap(const string filename, int index);

	// converts a string into lowercase
	string lowerCase(const string&); 

	// adds suffix to end of intermediate file
	string appendFileIndex(const string filename, int index);

	

private: /** PRIVATE DATA MEMBERS **/

	//size of buffer, exports to tempDirectory if full
	int maxBufferSize{};

	//formatted as string of tokens ("token1",1),("token2",2),... 
	vector<string> exportBuffer; 
	
	//private data member tokenPair ("",int)
	vector<tokenPair> tokenWords; 

	//FilePaths passed as args from main
	string tempDirectory;

	//handles FileIO implementation
	FileIOManagement exportMap_FileManager;

	//Counter to index large files broken into smaller tempFiles
	int fileIndex{ 0 }; 

};

#endif