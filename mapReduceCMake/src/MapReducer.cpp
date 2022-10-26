// mapReduceCMake.cpp : Defines the entry point for the application.


#include "MapReducer.h"
#include "FileIO.h"
#include <iostream>
// PUBLIC METHODS

MapReducer::MapReducer(std::string inputDir, std::string outputDir, std::string middleDir) :
	inputDirectory_(inputDir),
	outputDirectory_(outputDir),
	intermediateDirectory_(middleDir),
	mapSorter(folderNameForMapOutput, folderNameForSorterOutput),
	mapBook(intermediateDirectory_ + "\\" + folderNameForMapOutput, bufferSize),
	reduceOb(outputDir)
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
	if (results == true)
	{
		results = results && fileManager.createDirectory(intermediateDirectory_, folderNameForMapOutput);
		results = results && fileManager.createDirectory(intermediateDirectory_, folderNameForSorterOutput);
	}

	if (results == true)
	{
		std::vector<std::string> fileList;
		fileManager.getListOfTextFiles(outputDirectory_, fileList);
		for (size_t count = 0; count < fileList.size() ; count++)
		{
			// Stuff exist in output directory...... kill it
			std::string totalFilePath = outputDirectory_ + "\\" + fileList.at(count);
			if (!fileManager.deleteFile(totalFilePath))
			{
				std::cout << "Unable to Delete (" << totalFilePath << ") in the OUtput Directory" << std::endl;
				results = false;
			}
		}

	}
	return results;
}

bool MapReducer::doReduce(std::string& outputFileName)
{
	if (validateDirectories())
	{
		// For the input Directory read the list of files 
		std::vector<std::string> fileList;
		fileManager.getListOfTextFiles(inputDirectory_, fileList);

		// Input Processing and Map Call for Each file 
		for (size_t fileCount = 0; fileCount < fileList.size(); fileCount++)
		{
			std::vector<std::string> lines;
			// Read Each File Into a Vector of Strings 
			if (fileManager.readFileIntoVector(inputDirectory_, fileList.at(fileCount), lines))
			{
				// Call the Map Function for each Line
				for (size_t fileLine = 0; fileLine < lines.size(); fileLine++)
				{
					//Map Function --> Map
					 mapBook.createMap(fileList.at(fileCount), lines.at(fileLine));
				}

				//Map Function --> Export
				mapBook.flushMap(fileList.at(fileCount));
				lines.resize(0);
			}
		}

		fileList.clear();
		std::string sortedFileName;
		std::string outputMapDirectory = intermediateDirectory_ + "\\" + folderNameForMapOutput;
		std::string outputSortDirectory = intermediateDirectory_ + "\\" + folderNameForSorterOutput;
		if (!mapSorter.sortMappedFiles(outputMapDirectory, outputSortDirectory, sortedFileName))
		{
			std::cout << "ERROR: Unable to Sort Mapped Files Output" << std::endl;
			return false;
		}
		
		if(!reduceOb.reduceFile(outputSortDirectory, sortedFileName, outputFileName)) // Pulls File and puts entire line into Vect
		{
			std::cout << "ERROR: Unable to import Sorted Data into Reducer" << std::endl;
			return false;
		}
	}	
	else
	{
		return false;
	}
	return true;
}
