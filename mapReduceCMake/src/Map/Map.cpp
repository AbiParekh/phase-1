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
	:maxBufferSize{ 1024 } // defaults sizeOfBuffer to 1k tokenPairs
{};

Map::~Map()
{
//To do: deallocate memory in vectors, tokenPairs
};

Map::Map(const string intermediate)
	: tempDirectory { intermediate }, maxBufferSize {10} 
{};

Map::Map(const string intermediate, size_t sizeOfBuffer)
	: tempDirectory{ intermediate }, maxBufferSize{ sizeOfBuffer }
{};

Map::Map(const Map& t)
{
	maxBufferSize = t.maxBufferSize;
	exportBuffer = t.exportBuffer;
	tokenWords = t.tokenWords;
	tempDirectory = t.tempDirectory;
	mapFileManager = t.mapFileManager;
	fileIndex = t.fileIndex;

}

bool Map::removePunctuation(const string str, const int tokenStart, const int tokenEnd)
{
	//not alphanumeric and not apostrophe, must be punctuation
	if (!iswalnum(str[tokenEnd]) && !(str[tokenEnd] == '\'') )
	{
		return true;
	}
	
	else if (tokenEnd == str.length())
	{
		return true;
	}

	//determine if apostrophe should be char or punct
	else if (str[tokenEnd] == '\'') 
	{
		//apostrophe is first char in word, treat as punctuation
		if (tokenStart == tokenEnd)
		{
			return true;
		}

		//apostrophe is last char in word, check if ok to keep
		if (!iswalnum(str[tokenEnd + 1]))
		{
			//apostrophe ok since contracts word, i.e class' or o' clock
			if (str[tokenEnd - 1] == 's' || str[tokenEnd - 1] == 'o')
			{
				return false;
			}
			//apostrophe must be a punctuation
			else
			{
				return true;
			}	
		}
	}
	return false;
}

bool Map::createMap(const string filename, const string strCAPS)
{
	bool isExported{ false };
	string parsedWord, str{ lowerCaseMap(strCAPS) };
	
	for (int tokenStart = 0, tokenEnd = 0; tokenEnd <= str.length(); tokenEnd++) //iterate through each char, check if end of work
	{
		//((!iswalnum(str[tokenEnd]) && !(str[tokenEnd] == '\'')) || tokenEnd == str.length()) //checks if char is not alphanumeric (iswalnum) or apostrophe
		if(removePunctuation(str,tokenStart, tokenEnd))
		{

			if (tokenStart != tokenEnd) //not first char in word
			{
				parsedWord = str.substr(tokenStart, tokenEnd - tokenStart);
				isExported = exportMap(filename, parsedWord);
				tokenStart = tokenEnd + 1;	// moves word start to next char
			}
			else if (tokenStart == tokenEnd) //first char in word is a punct
			{
				tokenStart = tokenEnd + 1; // moves word start to next char
			}
		}
	}
	return isExported;
};

bool Map::flushMap(const string fileName)
{
	bool isFlushed = exportMap(fileName, fileIndex);
	cout << "Mapped " << fileIndex << " Partition(s) of " << fileName << " to tempDirectory: " << this->tempDirectory << endl;
	fileIndex = 0;
	return isFlushed; //nothing to flush
}

bool Map::exportMap(const string filename, string token)
{
	bool isExported{ false };
	tokenWords.push_back(std::make_pair(token, 1));
	if (tokenWords.size() == maxBufferSize) // Buffer reached dump to FileIO
	{
		//cout << "cache is full, exporting to file" << endl;
		isExported = exportMap(filename, fileIndex);
	}
	return isExported; //False if nothing exported
};

bool Map::exportMap(const string fileName, int index)
{
	bool isExported = emptyCache();

	//Prevents duplicate write to file if current buffer was already exported
	if (isExported) {
		string tempFile = addFileSuffix(fileName, index);
		fileIndex = index + 1;

		//writes contents of buffer to file in temp directory
		mapFileManager.writeVectorToFile(this->tempDirectory, tempFile, exportBuffer);
		//cout << "Map has exported file: " << this->tempDirectory << '/' << tempFile << endl;
	}

	return isExported; //False if nothing exported
}

bool Map::emptyCache()
{
	bool isEmptied{ false };

	if (tokenWords.size() > 0)
	{
		exportBuffer.resize(0);
		size_t index = exportBuffer.size(); //implicitly set index back to zero

		exportBuffer.push_back("");
		isEmptied = true;
		int i = 0;
		size_t tk_sz = tokenWords.size(); //token size

		for (int i = 0; i < tk_sz; i++)
		{
			if (i > 0) exportBuffer[index] += "\n";
			exportBuffer[index] += "(\"" + tokenWords[i].first + "\"," + std::to_string(tokenWords[i].second) + ")";
		}

		tokenWords.erase(tokenWords.begin(), tokenWords.begin() + tk_sz);
	}
	return isEmptied; //False if no cache emptied
}

string Map::addFileSuffix(const string filename, int index)
{
	string tempFile = filename;
	size_t lastdot = filename.find_last_of("."); //finds extension if any in file
	if (lastdot == std::string::npos) //filename has no extensions
	{
		return filename + '_' + std::to_string(index);
	}
	else //need to append index before extension from file
	{
		return filename.substr(0, lastdot) + '_' + std::to_string(index) + filename.substr(lastdot);
	}
}

string Map::lowerCaseMap(const string& input)
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

