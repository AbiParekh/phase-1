
#include "TestMap.h"
#include <filesystem>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

#define BufferSize 3000 //number tokenPairs per partitioned file (tempDirectory)
namespace fs = std::filesystem;

string path = fs::current_path().parent_path().parent_path().parent_path().generic_string();
string inputDirectory{ path + "/Test/inputDir" };
string middleDirectory{ path + "/Test/middleDir" };
//string outputDirectory{ path +  "/demo/outputDir" };
FileIOManagement fileManager;
std::vector<std::string> fileList;

//Test Cases
bool Test_createMap();
bool Test_exportMap();
bool Test_flushMap();

class testMap 
	: public Map
{
	testMap(string, size_t);
};

int main()
{
	fileManager.getListOfTextFiles(inputDirectory, fileList);
	Map globalBook{ middleDirectory, BufferSize };

	std::map<std::string, bool>  testResults;

	// readFileIntoVector Test
	std::pair<std::string, bool> createMap("Test_createMap", Test_createMap());
	testResults.insert(createMap);
	//std::pair<std::string, bool> exportMap("Test_exportMap", Test_exportMap());
	//testResults.insert(exportMap);
	std::pair<std::string, bool> flushMap("Test_flushMap", Test_flushMap());
	testResults.insert(flushMap);
	
	
	return 0;
}

bool Test_createMap()
{
	Map myBook{ middleDirectory, 9 }; //bufferSize is exact to token size
	return myBook.createMap("Test_createMap.txt", "This is a test file genereated from Test_createMap");
	//if( sizeof(myBook)
}

bool Test_flushMap()
{
	Map myBook{ middleDirectory, 8 }; //buffersize is 1 token smaller, creates buffer to be flushed
	myBook.createMap("Test_flushMap.txt", "This is a test file genereated from Test_flushMap");
	return myBook.flushMap("Test_createMap.txt");
	//if( sizeof(myBook)
}

bool Test_fullMap()
{
	Map myBook{ middleDirectory, BufferSize };
	bool success;


	// Input Processing and initial Map Call
	for (size_t fileCount = 0; fileCount < fileList.size(); fileCount++)
	{
		std::vector<std::string> lines;
		if (fileManager.readFileIntoVector(inputDirectory, fileList.at(fileCount), lines))
		{
			for (size_t fileLine = 0; fileLine < lines.size(); fileLine++)
			{
				//Map Function --> Map and Export
				myBook.createMap(fileList.at(fileCount), lines.at(fileLine));
			}
			//globalBook(myBook);

			//Map Function --> Flush and Export
			myBook.flushMap(fileList.at(fileCount));

			success = lines.empty();
		}
	}
	return success;
}