#include "MapReduceSorter.h"
#include "fileIO.h"
#include <iostream>

std::string MapSorter::formatOutput(const std::string& word, const uint32_t& usageCount)
{
	// Setup the Initial Word and Quotations 
	std::string formatedOutput = "(\"" + word + "\"";
	for (size_t counter = 0; counter < usageCount; counter++)
	{
		// Add a 1 for each usage
		formatedOutput.append(", 1");
	}
	///End the with the final parenthesis 
	formatedOutput.append(")");

	return formatedOutput;
}

MapSorter::MapSorter(std::string postMapKey, std::string postSortKey):
	MapOuputDirectoryName(postMapKey),
	SortOuputDirectoryName(postSortKey)
{
}

bool MapSorter::writeSortedMaptoFile(std::string filePath, std::string fileName)
{
	std::vector<std::string> outputVector;
	for (std::map<std::string, uint32_t>::iterator mapIterator = sortedMap.begin(); mapIterator != sortedMap.end();	++mapIterator)
	{
		outputVector.push_back(formatOutput(mapIterator->first, mapIterator->second));
	}

	if (!fileManager.writeVectorToFile(filePath, fileName, outputVector))
	{
		std::cout << "Error: Unable to Write Sorted Map File " << std::endl;
		return false;
	}

	return true;
	
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

	if (phrase.find(subString) == std::string::npos)return false;
	else return true;
}

bool MapSorter::ParseLineIntoSortedMap(const std::string& line)
{
	// Copy off the Line so it can be sliced a part
	std::string phrase = line;
	std::string DELIMITATOR_SUBSTRING = "),";
	std::string FINAL_DELIMITATOR_SUBSTRING = ")";
	std::string WORD_WRAP = "\"";

	AddPhraseToMap(phrase, WORD_WRAP, WORD_WRAP);

	return true;
}


bool MapSorter::IsolateWord(const std::string& formattedWord, const std::string& startString, const std::string& endString, std::string& isloatedWord)
{
	size_t firstPosition = formattedWord.find(startString);
	size_t secondPosition = formattedWord.find(endString, firstPosition+1);
	if ((firstPosition == std::string::npos) || (secondPosition == std::string::npos)) return false;
	isloatedWord = formattedWord.substr(firstPosition+1, secondPosition-(firstPosition + 1));

	return true;
}

bool MapSorter::AddPhraseToMap(const std::string& phrase, const std::string& startString, const std::string& endString)
{
	std::string isolateWord;
	if (IsolateWord(phrase, startString, endString, isolateWord))
	{
		std::map<std::string, uint32_t>::iterator mapIterator = sortedMap.find(isolateWord);
		if (mapIterator == sortedMap.end())
		{
			// The word was not found in the Map therefore add it 
			sortedMap.insert(std::pair<std::string, uint32_t>(isolateWord, 1));
		}
		else
		{
			// The Word was found in the map increment it
			mapIterator->second = mapIterator->second + 1;
		}
	}
	else
	{
		return false;
	}
	return true;
}


bool MapSorter::sortMappedFiles(std::string outputMapDirectory, std::string outpuSortDirectory)
{
	return doSortMappedFiles(outputMapDirectory, outpuSortDirectory);
}

bool MapSorter::doSortMappedFiles(std::string outputMapDirectory, std::string outpuSortDirectory)
{
	bool results = true;
	std::vector<std::string> fileList;
	if (!fileManager.getListOfTextFiles(outputMapDirectory, fileList))
	{
		std::cout << "Error: Unable to get List of Files created by the Map Function" << std::endl;
		results =  false;
	}
	else
	{
		// Call Sort Function
		for (size_t fileCount = 0; fileCount < fileList.size(); fileCount++)
		{
			if (!addFileContentsToSorter(outputMapDirectory, fileList.at(fileCount)))
			{
				std::cout << "Error: Unable to add File: " << outputMapDirectory << "\\" << fileList.at(fileCount) << "To Sorted List" << std::endl;
			}
		}

		std::string sortedFileName = "SortedFile.txt";
		if (!writeSortedMaptoFile(outpuSortDirectory, sortedFileName))
		{
			std::cout << "Error: Unable to Create Sorted Map File " << std::endl;
			results = false;
		}

	}
	
	return results;

}

void MapSorter::getSortedMap(std::map<std::string, uint32_t>& returnMap)
{
	returnMap = sortedMap;
}