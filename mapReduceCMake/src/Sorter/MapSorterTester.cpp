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