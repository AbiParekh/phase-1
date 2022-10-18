#include "MapReduceSorter.h"
#include "fileIO.h"
#include <iostream>

std::string MapSorter::formatOutput(const std::string& word, const uint32_t& usageCount)
{
	return std::string();
}

MapSorter::MapSorter(std::string postMapKey, std::string postSortKey):
	LEADING_STRING_MAPPED_FILES(postMapKey),
	LEADING_STRING_SORTED_FILES(postSortKey)
{
}

bool MapSorter::writeSortedMaptoFile(std::string filePath, std::string fileName)
{
	return false;
}

bool MapSorter::addFileContentsToSorter(const std::string& folderPath, const std::string& fileName)
{
	std::vector<std::string> lines;

	if (fileManager.readFileIntoVector(folderPath, fileName, lines))
	{
		for (size_t fileLine = 0; fileLine < lines.size(); fileLine++)
		{
			ParseLineIntoSortedMap(lines.at(fileLine));
		}
	}
	return true;
}

bool MapSorter::AnotherWordRemaining(const std::string& phrase, const std::string& subString)
{
	std::cout << "Phrase: " << phrase << ", and substring: " << subString << std::endl;
	if (phrase.find(subString) == std::string::npos)return false;
	else return true;
}

bool MapSorter::ParseLineIntoSortedMap(const std::string& line)
{
	// Copy off the Line so it can be sliced a part
	std::string phrase = line;
	std::string DELIMITATOR_SUBSTRING = "), ";
	std::string FINAL_DELIMITATOR_SUBSTRING = ")";
	std::string WORD_WRAP = "\"";
	std::cout << "ParseLineIntoSortedMap!" << std::endl;
	// While there are still more words pull them Apart 
	while (AnotherWordRemaining(phrase, DELIMITATOR_SUBSTRING))
	{
		static int count = 0;

		size_t length = phrase.find(DELIMITATOR_SUBSTRING);
		std::string subString = phrase.substr(0, length +3);
		phrase = phrase.substr(length + 3);
		AddPhraseToMap(phrase, WORD_WRAP, WORD_WRAP);
	}

	if (AnotherWordRemaining(phrase, FINAL_DELIMITATOR_SUBSTRING))
	{
		size_t length = phrase.find(DELIMITATOR_SUBSTRING);
		std::string subString = phrase.substr(0, length + 3);
		phrase = phrase.substr(0, length);
		AddPhraseToMap(phrase, WORD_WRAP, WORD_WRAP);
	}
	return true;
}


bool MapSorter::IsolateWord(const std::string& formattedWord, const std::string& startString, const std::string& endString, std::string& isloatedWord)
{
	size_t firstPosition = formattedWord.find(startString);
	size_t secondPosition = formattedWord.find(endString, firstPosition+1);
	if ((firstPosition == std::string::npos) || (secondPosition == std::string::npos)) return false;
	isloatedWord = formattedWord.substr(firstPosition+1, secondPosition-(firstPosition + 1));
	std::cout << "1st " << startString << "is at " << firstPosition << " and 2nd " << endString << " is at " << secondPosition << ", ISOLATED WORD = " << isloatedWord << std::endl;
	return true;
}

void MapSorter::AddPhraseToMap(const std::string& phrase, const std::string& startString, const std::string& endString)
{
	std::string isolateWord;
	if (IsolateWord(phrase, startString, endString, isolateWord))
	{
		std::cout << "isolateWord: " << isolateWord << std::endl; //ADD TO MAP
	}
}
