#include "Map.h"
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;
using std::getline;

Map::Map()
	:maxBufferSize{ 10 } // defaults sizeOfBuffer
{};


Map::Map(const string intermediate)
	: tempDirectory { intermediate }, maxBufferSize {10} 
{};

Map::Map(const string intermediate, int sizeOfBuffer)
	: tempDirectory{ intermediate }, maxBufferSize{ sizeOfBuffer }
{};

Map::~Map()
{};

void Map::map(const string filename, const string strCAPS)
{
	string parsedWord, str{ lowerCase(strCAPS) };
	
	for (int tokenStart = 0, tokenEnd = 0; tokenEnd <= str.length(); tokenEnd++) //iterate through each char, check if end of work
	{
		if(!iswalnum(str[tokenEnd]) || tokenEnd == str.length()) //checks if char is not alphanumeric (iswalnum)
		{
			if (tokenStart != tokenEnd) //not first char in word
			{
				parsedWord = str.substr(tokenStart, tokenEnd - tokenStart);
				bufferTokens(filename, parsedWord);
				tokenStart = tokenEnd + 1;	// moves word start to next char
			}
			else if (tokenStart == tokenEnd) //first char in word is a punct
			{
				tokenStart = tokenEnd + 1; // moves word start to next char
			}
		}
	}
};

void Map::bufferTokens(string filename, string token)
{
	tokenWords.push_back(std::make_pair(token, 1));
	if (tokenWords.size() == maxBufferSize) // Buffer reached dump to FileIO
	{
		emptyCache();
		//To-do: alert flag/lock that cache is full
	}
};

bool Map::emptyCache()
{
	bool isEmpty = true;
	size_t index = exportBuffer.size();

	if (tokenWords.size() > 0)
	{
		if (bufferExported) //clears buffer after write to file. Move construct would be better in exportMap
		{
			exportBuffer.resize(0);
			index = exportBuffer.size(); //implicitly set index back to zero
			bufferExported = false;
		}
		exportBuffer.push_back("");
		isEmpty = false;
		int i = 0;
		size_t tk_sz = tokenWords.size() ; //token size

		for (int i = 0; i < tk_sz; i++)
		{
			if (i > 0) exportBuffer[index] += ",";
			exportBuffer[index] += "(\"" + tokenWords[i].first + "\"," + std::to_string(tokenWords[i].second) + ")";
		}
		tokenWords.erase(tokenWords.begin(), tokenWords.begin() + tk_sz);
	}
	return isEmpty;
}

//Returns vector of Strings by reference
//implementation requires user to handle FileIO
vector<string>& Map::exportMap() 
{
	emptyCache();
	bufferExported = true;
	return exportBuffer;
}

//uses FileIO to writeVectorToFile, returns true upon success
bool Map::exportMap(const string filename)
{
	emptyCache();

	//writes contents of buffer to file in temp directory
	exportMap_FileManager.writeVectorToFile(this->tempDirectory, filename, exportBuffer); 

	//temp flag indicating buffer to be emptied on next call to emptyCache
	bufferExported = true;

	return true;
}

string Map::lowerCase(const string& input)
{
	string output;
	for (char c : input)
	{
		output += tolower(c);
	}
	return output;
}

ostream& operator<<(ostream& os, const tokenPair& tp)
{
	os << "(\"" << tp.first << "\"" << ", " << tp.second << ")";
	return os;
}

