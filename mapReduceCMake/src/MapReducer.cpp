// mapReduceCMake.cpp : Defines the entry point for the application.


#include "MapReducer.h"
#include "FileIO.h"
#include <iostream>

// PUBLIC METHODS

MapReducer::MapReducer(std::string inputDir, std::string outputDir, std::string middleDir):
	inputDirectory_(inputDir), 
	outputDirectory_(outputDir),
	intermediateDirectory_(middleDir),
	mapSorter(LEADING_STRING_MAPPED_FILES, LEADING_STRING_SORTED_FILES)
{}


bool MapReducer::reduce(std::string& outputFileName)
{
	return doReduce(outputFileName);
}

std::string MapReducer::getInputDir()
{
	return inputDirectory_;
}

std::string MapReducer::getOutputDir()
{
	return outputDirectory_;
}

std::string MapReducer::getIntermediateDir()
{
	return intermediateDirectory_;
}

void MapReducer::setInputDir(std::string in)
{
	inputDirectory_ = in;
}

void MapReducer::setOutputDir(std::string out)
{
	outputDirectory_ = out;
}

void MapReducer::setIntermediateDir(std::string middle)
{
	intermediateDirectory_ = middle;
}


// PRIVATE METHODS 
bool MapReducer::validateDirectories()
{
	bool results = fileManager.validDirectory(inputDirectory_);
	results = results && fileManager.validDirectory(outputDirectory_);
	results = results && fileManager.validDirectory(intermediateDirectory_);
	return results;
}

bool MapReducer::doReduce(std::string& outputFileName)
{
	if (validateDirectories())
	{
		FileIOManagement fileManager;
		std::vector<std::string> fileList;
		fileManager.getListOfTextFiles(inputDirectory_, fileList);

		// Input Processing and initial Map Call
		for (size_t fileCount = 0; fileCount < fileList.size(); fileCount++)
		{
			std::vector<std::string> lines;
			if (fileManager.readFileIntoVector(inputDirectory_, fileList.at(fileCount), lines))
			{
				for (size_t fileLine = 0; fileLine < lines.size(); fileLine++)
				{
					//Map Function --> Map
					//Map Function --> Export
				}
			}
		}

		fileList.clear();


		// SORT WRITES OUTPUT FILE 
		if (!fileManager.getListOfTextFilesBasedOnStart(intermediateDirectory_, LEADING_STRING_MAPPED_FILES, fileList))
		{
			std::cout << "Unable to get List of Files created by the MAPPED Directory" << std::endl;
		}

		// Call Sort Function
		for (size_t fileCount = 0; fileCount < fileList.size(); fileCount++)
		{
			if (!mapSorter.addFileContentsToSorter(intermediateDirectory_, fileList.at(fileCount)))
			{
				std::cout << "Unable to add File: " << intermediateDirectory_ << "\\" << fileList.at(fileCount) << "To Sorted List" << std::endl;
			}
		}
	
		std::string sortedFileName = ""; //TODO
		if (!mapSorter.writeSortedMaptoFile(intermediateDirectory_, sortedFileName))
		{
			std::cout << "Unable to Create Sorted Map File " << std::endl;
			return false;
		}

		// SORT WRITES OUTPUT FILE 


		// Call Reduce Function
			// Read from Sorted File
			// Reduce Sorted File Contents 
			// Write Output of Sorted File
			// Write Successful File

	}	
	else
	{

	}
}
