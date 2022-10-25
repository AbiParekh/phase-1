
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

string path = fs::current_path().parent_path().parent_path().generic_string();
//C:\Users\esevieux\source\repos\phase - 1\mapReduceCMake
string inputDirectory{ path + "/src/Map/Test/inputDir" };
string middleDirectory{ path + "/src/Map/Test/middleDir" };
//string outputDirectory{ path +  "/demo/outputDir" };
FileIOManagement fileManager;
std::vector<std::string> fileList;

//Test Cases
void ReportResults(std::map<std::string, bool> outputMap);
bool Test_createMap();
bool Test_exportMap();
bool Test_flushMap();
bool Test_emptyCache();
bool Test_emptyCache_2();

class testMap : public Map
{
public:
	testMap(std::string filename, std::size_t bufferSize) : Map(filename, bufferSize)
	{
		 
	}
	bool testExportMap(const std::string filename,  const std::string testString)
	{
		bool result = exportMap(filename, testString);
		return result;
	}
	bool testEmptyCache(const std::string filename, const std::string testString)
	{
		bool result = emptyCache();
		return result;
	}
};

int main()
{
	fileManager.getListOfTextFiles(inputDirectory, fileList);
	Map globalBook{ middleDirectory, BufferSize };

	std::map<std::string, bool>  testResults;

	// readFileIntoVector Test
	std::pair<std::string, bool> createMap("Test_createMap", Test_createMap());
	testResults.insert(createMap);
	std::pair<std::string, bool> exportMap("Test_exportMap", Test_exportMap());
	testResults.insert(exportMap);
	std::pair<std::string, bool> flushMap("Test_flushMap", Test_flushMap());
	testResults.insert(flushMap);
	std::pair<std::string, bool> emptyCache("Test_emptyCache", Test_emptyCache());
	testResults.insert(emptyCache);
	std::pair<std::string, bool> emptyCacheFail("Test_emptyCacheFail", Test_emptyCache_2());
	testResults.insert(emptyCacheFail);
	
	ReportResults(testResults);
	return 0;
}

void ReportResults(std::map<std::string, bool> outputMap)
{
	std::cout << "\n\n\n\n\n" << std::endl;
	std::cout << "========================================== Test Results ==========================================" << std::endl;
	bool results = true;
	for (std::map<std::string, bool>::iterator outputMapIt = outputMap.begin(); outputMapIt != outputMap.end(); outputMapIt++)
	{
		std::string resultsformatted = "";
		if (outputMapIt->second == 0) resultsformatted = "FAIL";
		else  resultsformatted = "PASS";
		std::cout << "Test: " << outputMapIt->first << "; Result: " << resultsformatted << std::endl;
	}
	std::cout << "==================================================================================================" << std::endl;
}


bool Test_createMap()
{
	Map myBook{ middleDirectory, 9 }; //bufferSize is exact to token size
	return myBook.createMap("Test_createMap.txt", "This is a test file genereated from Test_createMap");
}

bool Test_exportMap()
{
	//uses class testMap which has protected access to Map, buffersize 1 will export on single word
	testMap myBook{ middleDirectory, 1 };
	return myBook.testExportMap("Test_exportMap.txt", "Export_Succeeded"); 
}

bool Test_emptyCache() 
{
	//uses class testMap which has protected access to Map, buffersize 1 will export on single word
	bool expected;
	testMap myBook{ middleDirectory, 4 };
	myBook.createMap("Test_emptyCache.txt", "emptyCache expected fail outcome");
	expected =  myBook.testEmptyCache("Test_emptyCache", "Empty Cache Failed (Successfully)");
	return (expected == false ? true : false);
	//return expected == false; //should fail if buffersize = 4
	//return myBook.testEmptyCache();
}

bool Test_emptyCache_2()
{
	//uses class testMap which has protected access to Map, buffersize 1 will export on single word
	bool expected;
	testMap myBook{ middleDirectory, 5 };
	myBook.createMap("Test_emptyCache.txt", "emptyCache expected pass outcome");
	expected = myBook.testEmptyCache("Test_emptyCache", "Empty Cache Succeeded");
	
	return expected ; //should pass if buffersize != 4
	//return myBook.testEmptyCache();
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