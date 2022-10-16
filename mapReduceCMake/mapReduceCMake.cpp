// mapReduceCMake.cpp : Defines the entry point for the application.
//

#include "mapReduceCMake.h"

#include "fileIO.h"
#include <vector>
#include <string>

// Print Banner at the top of the Program
void printBanner();

// Print Help Message that displays the correct arguments to provide
void printHelp();

/// Convert Char* Arguments to Strings within a Vector 
void convertArgsToStrings(int numberOfArguments, char* argumentArray[], std::vector<std::string>& argumentVector);

// Validate the Correct Command Line Arguments where provided to the function
bool validateCommandLineArguments(int numberOfArguments, char* argumentArray[], std::string& inputDirectory, std::string& outputDirectory, std::string& intermediateDirectory);

int main(int argc, char* argv[])
{
	printBanner(); 
	std::string inputDirectory, outputDirectory, intermediateDirectory;

	if (validateCommandLineArguments(argc, argv, inputDirectory, outputDirectory, intermediateDirectory))
	{
		FileIOManagement fileManager;
		std::vector<std::string> fileList;
		fileManager.getListOfTextFiles(inputDirectory, fileList);
		
		// Input Processing and initial Map Call
		for (size_t fileCount = 0; fileCount < fileList.size(); fileCount++)
		{
			std::vector<std::string> lines; 
			if (fileManager.readFileIntoVector(inputDirectory, fileList.at(fileCount), lines))
			{
				for (size_t fileLine = 0; fileLine < lines.size(); fileLine++)
				{
					std::cout << "File (" << fileList.at(fileCount) << ") Line (" << fileLine << "): " << lines.at(fileLine) << std::endl;
					//Map Function --> Map
					//Map Function --> Export
				}
			}
			fileManager.writeVectorToFile(intermediateDirectory, fileList.at(fileCount), lines);
		}

		// Call Sort Function
		
		// Call Reduce Function
	}
	else
	{
		std::cout << "Invalid validateCommandLineArguments ....... Exiting" << std::endl;
		return -1;
	}

	return 0;
}

//int main(int argc, char* argv[])
//{
//	
//	FileIOManagement fileManger;
//	fileManger.canAccessFile("demo/inputDir/", );
//}


void convertArgsToStrings(int numberOfArguments, char* argumentArray[], std::vector<std::string>& argumentVector)
{
	for (int i = 0; i < numberOfArguments; ++i)
	{
		argumentVector.push_back(std::string(argumentArray[i]));
	}
}

void printBanner()
{
	// Print Banner to Screen
	std::cout << "------------------------- Phase 1 - Map Reducer ------------------------" << std::endl;
#ifdef PRINT_DEBUG	
	std::cout << "C++ Version is " << __cplusplus << std::endl;
#endif
	std::cout << "This program is a standalone command-line program that can run a word count MapReduce Work Flow. \n" <<
		"A set of text files are stored and will ultimately produce a single output file that contains \n" <<
		"a list of words and their associated counts in the originating input files."<< std::endl;
	std::cout << "-----------------------------------------------------------------------" << std::endl;
}

void printHelp()
{
	std::cout << "The Program should be provided 3 Arguments in the following Order: (Paths should be relative) " << std::endl;
	std::cout << "     a) Path to the Directory that holds input files.\n" <<
				 "     b) Path to the Directory to hold output file. \n" <<
				 "     c) Temporary directory to hold intermediate output files. \n " << std::endl;
}

bool validateCommandLineArguments(int numberOfArguments, char* argumentArray[], std::string& inputDirectory, std::string& outputDirectory, std::string& intermediateDirectory)
{
	std::vector<std::string> argumentVector;
	convertArgsToStrings(numberOfArguments, argumentArray, argumentVector);
	std::vector<std::string>::iterator argVecIT = find(argumentVector.begin(), argumentVector.end(), "-help");
	if (argVecIT != argumentVector.end())
	{
		printHelp();
		return false;
	}
	else if (argumentVector.size() != 4)
	{
		std::cout << "Incorrect Number of Arguments Provided! Please See Instructions below" << std::endl;
		printHelp();
		return false;
	}

	inputDirectory = argumentVector.at(1);
	outputDirectory = argumentVector.at(2);
	intermediateDirectory = argumentVector.at(3);
	FileIOManagement fileManger;
	bool results = fileManger.validDirectory(inputDirectory);
	results = results && fileManger.validDirectory(outputDirectory);
	results = results && fileManger.validDirectory(intermediateDirectory);
	return results;
}
