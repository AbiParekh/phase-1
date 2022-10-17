#include "Map.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
	//exportMap(filename); //flushes any remaining data from string and writes to temp file;

};

void Map::bufferTokens(const string filename, string token)
{
	tokenWords.push_back(std::make_pair(token, 1));
	if (tokenWords.size() == maxBufferSize) // Buffer reached dump to FileIO
	{
		cout << "cache is full, exporting to file" << endl;
		exportMap(filename);
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


//uses FileIO to writeVectorToFile, returns true upon success
bool Map::exportMap(const string fileName)
{
	return exportMap(fileName, fileIndex); //if no index provided use curent
}

bool Map::exportMap(const string fileName, int index)
{
	emptyCache();
	//string tempFile = fileName;
	fileIndex = index; 

	string tempFile = appendFileIndex(fileName, fileIndex++);

	//writes contents of buffer to file in temp directory
	exportMap_FileManager.writeVectorToFile(this->tempDirectory, tempFile, exportBuffer); 
	cout << "Map has exported file: " << this->tempDirectory << '/' << tempFile << endl;
	//temp flag indicating buffer to be emptied on next call to emptyCache
	bufferExported = true;

	return true;
}

//creates partitioned file names for temp write to file

string Map::appendFileIndex(const string filename, int index)
{
	string tempFile = filename;
	size_t lastdot = filename.find_last_of("."); //finds extension if any in file
	if (lastdot == std::string::npos) //filename has no extensions
	{
		return filename + '-' + std::to_string(index);
	}
	else //need to append index before extension from file
	{
		return filename.substr(0, lastdot) + '-' + std::to_string(index) + filename.substr(lastdot);
	}
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

