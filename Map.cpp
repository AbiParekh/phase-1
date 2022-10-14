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

//initializes a Map type with default values
//Map::map()
//{}

//Default Constructor, no args provided
Map::Map()
	:maxBufferSize{ 10 }
{};

Map::Map(int n)
	:maxBufferSize{ n }
{};

Map::~Map()
{};

void Map::map(const string filename, const string strCAPS)
{
	string parsedWord, str{ lowerCase(strCAPS) };
	
	for (int tokenStart = 0, tokenEnd = 0; tokenEnd <= str.length(); tokenEnd++) //iterate through each char, check if end of work
	{
		if (ispunct(str[tokenEnd]) || str[tokenEnd] == ' ' || tokenEnd == str.length() 
			|| str[tokenEnd] == '\t' || str[tokenEnd] == '\n')//if char is punct 
		{
			if (tokenStart != tokenEnd) //not first char in word
			{
				parsedWord = str.substr(tokenStart, tokenEnd - tokenStart);
				exportTokens(filename, parsedWord);
				tokenStart = tokenEnd + 1;	// moves word start to next char
			}
			else if (tokenStart == tokenEnd) //first char in word is a punct
			{
				tokenStart = tokenEnd + 1; // moves word start to next char
			}
		}
	}
	
	/*if (tokenWords.size() > 0) //End of line check for cached tokens not exported to FileIO
	{
		emptyCache();
	}*/
};

string Map::lowerCase(const string& input)
{
	string output;
	for (char c : input)
	{
		output += tolower(c);
	}
	return output;
}
bool Map::emptyCache()
{
	bool isEmpty = true;
	if (tokenWords.size() > 0)
	{
		isEmpty = false;
		for (int i = 0; i < tokenWords.size(); i++)
		{
			cout << tokenWords[i] << '\n';
		}
		tokenWords.clear();
	}
	return isEmpty;
}

void Map::exportTokens(string filename, string token)
{
	tokenWords.push_back(std::make_pair(token, 1));
	if (tokenWords.size() == maxBufferSize) // Buffer reached dump to FileIO
	{
		emptyCache();
	}
};

tokenPair Map::getToken(int index)
{
	return tokenWords[index];
}

ostream& operator<<(ostream& os, const tokenPair& tp)
{
	os << "(\"" << tp.first << "\"" << ", " << tp.second << ")";
	return os;
}