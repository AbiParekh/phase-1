#include "FileIO.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>


void ReportResults(std::map<std::string, bool> outputMap);
bool Test_readFileIntoVector();
bool Test_canAccessFile();
bool Test_validDirectory();
bool Test_getListOfTextFiles();
bool Test_createDirectory();
bool Test_writeVectorToFile();


int main(int argc, char* argv[])
{
	std::map<std::string, bool>  testResults;
	
	// readFileIntoVector Test
	std::pair<std::string, bool> ReadFileIntoVector("Test_readFileIntoVector", Test_readFileIntoVector());
	testResults.insert(ReadFileIntoVector);


	// canAccess Test
	std::pair<std::string, bool> canAccessFile("Test_canAccessFile", Test_canAccessFile());
	testResults.insert(canAccessFile);

	
	// validDirectory Test   
	std::pair<std::string, bool> validDirectory("Test_validDirectory", Test_validDirectory());
	testResults.insert(validDirectory);

	
	// getListOfTextFiles Test  
	std::pair<std::string, bool> getListOfTextFiles("Test_getListOfTextFiles", Test_getListOfTextFiles());
	testResults.insert(getListOfTextFiles);


	// createDirectory Test
	std::pair<std::string, bool> createDirectory("Test_createDirectory", Test_createDirectory());
	testResults.insert(createDirectory);

	
	//writeVectorToFile Test
	std::pair<std::string, bool> writeVectorToFile("Test_writeVectorToFiley", Test_writeVectorToFile());
	testResults.insert(writeVectorToFile);

	ReportResults(testResults);

	return 0;
}

void ReportResults(std::map<std::string, bool> outputMap)
{
	std::cout << "\n\n\n\n\n" << std::endl;
	std::cout << "========================================== Test Results ==========================================" << std::endl;
	bool results = true;
	for (std::map<std::string, bool>::iterator outputMapIt = outputMap.begin();	outputMapIt != outputMap.end();	outputMapIt++)
	{
		std::string resultsformatted = "";
		if (outputMapIt->second == 0) resultsformatted = "FAIL";
		else  resultsformatted = "PASS";
		std::cout << "Test: " << outputMapIt->first << "; Result: " << resultsformatted << std::endl;
	}
	std::cout << "==================================================================================================" << std::endl;
}

bool Test_readFileIntoVector()
{
	// readFileIntoVector Test Parameters  
	FileIOManagement fileIO;
	bool results_readFileIntoVector = true;
	std::string inputFolderFor_readFileIntoVectorTest = "..\\..\\src\\FileIO\\ConfigFiles";
	std::string inputFileFor_readFileIntoVectorTest = "boat.txt";
	std::vector<std::string> readingInputFile;
	std::vector<std::string> compareVectorFor_readFileIntoVectorTest;
	compareVectorFor_readFileIntoVectorTest.push_back("Row, row, row your boat");
	compareVectorFor_readFileIntoVectorTest.push_back("Gently down the stream");
	compareVectorFor_readFileIntoVectorTest.push_back("Merrily, merrily, merrily, merrily");
	compareVectorFor_readFileIntoVectorTest.push_back("Life is but a dream");
	compareVectorFor_readFileIntoVectorTest.push_back("");
	compareVectorFor_readFileIntoVectorTest.push_back("Row, row, row your boat");
	compareVectorFor_readFileIntoVectorTest.push_back("Gently down the stream");
	compareVectorFor_readFileIntoVectorTest.push_back("");
	compareVectorFor_readFileIntoVectorTest.push_back("If you see a crocodile");
	compareVectorFor_readFileIntoVectorTest.push_back("Don’t forget to scream!");


	fileIO.readFileIntoVector(inputFolderFor_readFileIntoVectorTest, inputFileFor_readFileIntoVectorTest, readingInputFile);
	if (readingInputFile.size() != compareVectorFor_readFileIntoVectorTest.size())
	{
		std::cout <<"readFileIntoVector Failure: Expected Vectors' Sizes do not match " << std::endl;
		results_readFileIntoVector = false;
	}
	else
	{
		for (size_t line = 0; line < readingInputFile.size(); line++)
		{
			if (readingInputFile.at(line).compare(compareVectorFor_readFileIntoVectorTest.at(line)) != 0)
			{
				std::cout << "readFileIntoVector Failure: Fail Reading Input File: " << readingInputFile.at(line) << ", Expected Output: " << compareVectorFor_readFileIntoVectorTest.at(line) << std::endl;
				results_readFileIntoVector = false;
			}
		}
	}
	return results_readFileIntoVector;
}

bool Test_canAccessFile()
{
	FileIOManagement fileIO;
	bool results_canAccessFile = true;
	std::string inputFolderFor_canAccessFileTest = "..\\..\\src\\FileIO\\ConfigFiles";
	std::string inputFileFor_canAccessFileTest = "boat.txt";
	std::string IncorrectFileNameFor_canAccessFileTest = "doesNotExist.txt";

	if (!(fileIO.canAccessFile(inputFolderFor_canAccessFileTest, inputFileFor_canAccessFileTest) == true))
	{
		std::string tempOutput = inputFolderFor_canAccessFileTest + "\\" + inputFileFor_canAccessFileTest;
		std::cout << "Test_canAccessFile: canAccessFile (" << tempOutput << ") is invalid" << std::endl;
		results_canAccessFile = false;
	}

	if (!(fileIO.canAccessFile(inputFolderFor_canAccessFileTest, IncorrectFileNameFor_canAccessFileTest) == false))
	{
		std::string tempOutput = inputFolderFor_canAccessFileTest + "\\" + IncorrectFileNameFor_canAccessFileTest;
		std::cout << "Test_canAccessFile: canAccessFile(" << tempOutput << ") is Valid" << std::endl;
		results_canAccessFile = false;
	}

	return results_canAccessFile;
}

bool Test_validDirectory()
{
	FileIOManagement fileIO;
	bool results_validDirector = true;
	std::string inputFolderFor_validDirectory = "..\\..\\src\\FileIO\\ConfigFiles";
	std::string IncorrectFolderNameFor_validDirectory = "..\\..\\src\\FileIO\\DoesNotExist_ConfigFiles";
	std::string File_validDirectory = "..\\..\\src\\FileIO\\ConfigFiles\\boat.txt";


	bool validDir = fileIO.validDirectory(inputFolderFor_validDirectory);
	if (!(validDir == true))
	{
		std::cout << "Test_validDirectory: Directory(" << inputFolderFor_validDirectory << ") is inValid" << std::endl;
		results_validDirector = false;
	}

	bool invalidDir = fileIO.validDirectory(IncorrectFolderNameFor_validDirectory);
	if (!(invalidDir == false))
	{
		std::cout << "Test_validDirectory: Directory(" << IncorrectFolderNameFor_validDirectory << ") is Valid" << std::endl;
		results_validDirector = false;
	}

	bool validFile = fileIO.validDirectory(File_validDirectory);
	if (!(validFile == false))
	{
		std::cout << "Test_validDirectory: File identified  (" << File_validDirectory << ") as a folder! " << std::endl;
		results_validDirector = false;
	}

	return results_validDirector;
}

bool Test_getListOfTextFiles()
{
	FileIOManagement fileIO;
	bool results_getListOfTextFiles = true;
	std::string incorrectInputFolderFor_getListOfTextFiles = "..\\..\\src\\FileIO\\ConfigFiles\\files2";
	std::string inputFolderFor_getListOfTextFiles			= "..\\..\\src\\FileIO\\ConfigFiles\\files";
	std::string inpuFile_getListOfTextFiles					= "..\\..\\src\\FileIO\\ConfigFiles\\boat.txt";
	std::vector<std::string> fileList1, fileList2;
	std::vector<std::string> outputFileList;
	outputFileList.push_back("exhuast 4.txt");
	outputFileList.push_back("Other2.txt");
	outputFileList.push_back("Random.txt");
	outputFileList.push_back("syr.txt");
	outputFileList.push_back("winner.txt");
	

	if (!(fileIO.getListOfTextFiles(incorrectInputFolderFor_getListOfTextFiles, fileList1) == false))
	{
		std::cout << "Test_getListOfTextFiles: getListOfTextFiles(" << incorrectInputFolderFor_getListOfTextFiles << ") indicates it is Valid" << std::endl;
		results_getListOfTextFiles = false;
	}

	if (!(fileIO.getListOfTextFiles(inpuFile_getListOfTextFiles, fileList1) == false))
	{
		std::cout << "Test_getListOfTextFiles: getListOfTextFiles(" << inpuFile_getListOfTextFiles << ") indicates it is Valid" << std::endl;
		results_getListOfTextFiles = false;
	}

	if (!(fileIO.getListOfTextFiles(inputFolderFor_getListOfTextFiles, fileList2) == true))
	{
		std::cout << "Test_getListOfTextFiles: getListOfTextFiles(" << inputFolderFor_getListOfTextFiles << ") indicates it is invalid" << std::endl;
		results_getListOfTextFiles = false;
	}

	for (size_t files = 0; files < fileList2.size(); files++)
	{
		if (fileList2.at(files).compare(outputFileList.at(files)) != 0)
		{
			std::cout << "Reading Input File: " << fileList2.at(files) << "Expected Output: " << outputFileList.at(files) << std::endl;
			results_getListOfTextFiles = false;
		}
	}

	return results_getListOfTextFiles;
}

bool Test_createDirectory()
{
	FileIOManagement fileIO;
	bool results_createDirectory = true;
	std::string existingDirectoryName_createDirectoryTest = "createDirectoryTester";
	std::string newDirectoryName_createDirectoryTest = "createDirectoryTesterDOESNOTEXIST";
	std::string inputFolderFor_createDirectoryTest = "..\\..\\src\\FileIO\\ConfigFiles";

	bool createDir = fileIO.createDirectory(inputFolderFor_createDirectoryTest, existingDirectoryName_createDirectoryTest);
	if (createDir == false)
	{
		std::cout << "Test_createDirectory: Directory(" << existingDirectoryName_createDirectoryTest << ") could not be created" << std::endl;
		results_createDirectory = false;
	}


	createDir = fileIO.createDirectory(inputFolderFor_createDirectoryTest, newDirectoryName_createDirectoryTest);
	if (createDir == false)
	{
		std::cout << "Test_createDirectory: Directory(" << newDirectoryName_createDirectoryTest << ") could not be created" << std::endl;
		results_createDirectory = false;
	}

	return results_createDirectory;

}

bool Test_writeVectorToFile()
{
	// Test Parameters	
	FileIOManagement fileIO;
	bool results_writeVectorToFile = true;
	std::string inputFolderFor_readFileIntoVectorTest = "..\\..\\src\\FileIO\\ConfigFiles";
	std::string compareableFile = "boatOutput.txt";
	std::string outputFile = "createdboatOutput.txt";
	std::vector<std::string> VectorToBePushedIntoFileTest;
	VectorToBePushedIntoFileTest.push_back("(\"row\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"row\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"row\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"your\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"boat\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"gently\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"down\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"the\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"stream\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"merrily\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"merrily\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"merrily\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"merrily\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"life\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"is\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"but\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"a\", 1)");
	VectorToBePushedIntoFileTest.push_back("(\"dream\", 1)");

	fileIO.writeVectorToFile(inputFolderFor_readFileIntoVectorTest, outputFile, VectorToBePushedIntoFileTest);

	std::string p1 = inputFolderFor_readFileIntoVectorTest + "\\" + compareableFile;
	std::string p2 = inputFolderFor_readFileIntoVectorTest + "\\" + outputFile;
	std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
	std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);

	if (f1.fail() || f2.fail()) {
		results_writeVectorToFile = false; //file problem
		std::cout << "Test_writeVectorToFile: Unable to open one of the files" << std::endl;
	}

	else if (f1.tellg() != f2.tellg()) {
		results_writeVectorToFile = false; //size mismatch
		std::cout << "Test_writeVectorToFile: Output File is not the expected Size " << std::endl;

	}
	else
	{
		//seek back to beginning and use std::equal to compare contents
		f1.seekg(0, std::ifstream::beg);
		f2.seekg(0, std::ifstream::beg);
		bool eq = std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
			std::istreambuf_iterator<char>(),
			std::istreambuf_iterator<char>(f2.rdbuf()));
		if (eq == false)
		{
			std::cout << "Test_writeVectorToFile: The Files are not equal" << std::endl;
			results_writeVectorToFile = false;
		}
	}
	return results_writeVectorToFile;
}