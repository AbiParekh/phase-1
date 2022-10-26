#include "FileIO.h"
#include "MapReduceSorter.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>


void ReportResults(std::map<std::string, bool> outputMap);

bool Test_IsolateWord();
bool getNumberOfInstances(std::string format, std::string delim, uint32_t& instance);


/*

bool Test_writeSortedMaptoFile();
bool Test_addFileContentsToSorter();
bool Test_ParseLineIntoSortedMap();
bool Test_AddPhraseToMap();
bool Test_formatOutput();
bool Test_AnotherWordRemaining();
*/
class MapSorterTestFramework : public MapSorter
{
public:
	MapSorterTestFramework(std::string postMapKey, std::string postSortKey) : MapSorter(postMapKey, postSortKey) {}

	bool isolateWordFramework(const std::string& formattedWord, const std::string& startString, const std::string& endString, std::string& isloatedWord)
	{
		bool result = IsolateWord(formattedWord, startString, endString, isloatedWord);
		return result;
	}

	bool copmareMapResults(std::map<std::string, uint32_t> expectedSortedMap)
	{
		bool result = true;
		std::map<std::string, uint32_t> storedMap;
		getSortedMap(storedMap);
		if (expectedSortedMap.size() != storedMap.size())
		{
			std::cout << "Output Map is Not The Expected Size" << std::endl;
			result = false;
		}
		std::map<std::string, uint32_t>::iterator mapit = expectedSortedMap.begin();


	}
};

int main(int argc, char* argv[])
{
	std::map<std::string, bool>  testResults;
	
	std::pair<std::string, bool> IsolateWord("Test_writeVectorToFiley", Test_IsolateWord());
	testResults.insert(IsolateWord);

	
	std::string q1 = "(\"six\", 1, 1, 1, 1, 1, 1)";
	std::string q2 = "(\"one\", 1)";
	std::string q3 = "(\"zero\",  )";
	std::string q4 = "(\"10\", 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)";
	uint32_t in1 = 0;
	uint32_t in2 = 0;
	uint32_t in3 = 0;
	uint32_t in4 = 0;

	if (!getNumberOfInstances(q1, ",", in1))
	{
		std::cout << "ERROR: Q1" << std::endl;
	}
	else
	{
		std::cout << "Q1 has " << in1 << " instances " << std::endl;
	}

	if (!getNumberOfInstances(q2, ",", in2))
	{
		std::cout << "ERROR: Q1" << std::endl;
	}
	else
	{
		std::cout << "Q1 has " << in2 << " instances " << std::endl;
	}

	if (!getNumberOfInstances(q3, ",", in3))
	{
		std::cout << "ERROR: Q1" << std::endl;
	}
	else
	{
		std::cout << "Q3 has " << in3 << " instances " << std::endl;
	}

	if (!getNumberOfInstances(q4, ",", in4))
	{
		std::cout << "ERROR: Q1" <<  std::endl;
	}
	else
	{
		std::cout << "Q4 has " << in4 << " instances " << std::endl;
	}
	
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

bool Test_IsolateWord()
{

	MapSorterTestFramework sorter("MAP_OUTPUT", "SORT_OUTPUT");
	bool results_IsolateWord = true;
	std::string delim = "\"";
	std::string formattedWord = "(\"row\", 1)";
	std::string formattedWord2 = "(\"depth_charge\", 1)";
	std::string formattedWord3 = "NO Deliminator";
	std::string isloatedWord = "";
	std::string isloatedWord2 = "";
	std::string isloatedWord3 = "";

	bool results = sorter.isolateWordFramework(formattedWord, delim, delim, isloatedWord);

	int correctWord = isloatedWord.compare("row");
	if (correctWord != 0 || results == false)
	{
		std::cout << "Test_IsolateWord: Unable to Isolate row" << std::endl;
		results_IsolateWord = false;
	}


	results = sorter.isolateWordFramework(formattedWord2, delim, delim, isloatedWord2);
	correctWord = isloatedWord2.compare("depth_charge");
	if (correctWord != 0 || results == false)
	{
		std::cout << "Test_IsolateWord: Unable to Isolate depth_charge" << std::endl;
		results_IsolateWord = false;
	}

	results = sorter.isolateWordFramework(formattedWord3, delim, delim, isloatedWord3);
	if (results != false)
	{
		std::cout << "Test_IsolateWord: did not fail when deliminator is missing" << std::endl;
		results_IsolateWord = false;
	}

	return results_IsolateWord;
}



bool getNumberOfInstances(std::string format, std::string delim, uint32_t& instance)
{
	size_t firstPosition = format.find(delim);
	if (firstPosition == std::string::npos)
	{
		return false;
	}
	size_t formatSize = format.size();
	std::string subString = format.substr(firstPosition);
	std::string::difference_type n = std::count(subString.begin(), subString.end(), '1');
	instance = static_cast<uint32_t>(n);
	return true;
}