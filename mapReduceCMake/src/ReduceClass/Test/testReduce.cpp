#include "testReduce.h"
#include <iostream>
#include "FileIO.h"
#include "MapReduceSorter.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <Reduce.h>
using namespace std;
#include <algorithm>
namespace fs = std::filesystem;

string path = fs::current_path().parent_path().parent_path().generic_string();

string middleDrectory{ path + "src/Reduce/Test/middleDir"};
string outputDirectory{ path + "src/Reduce/Test/outputDir"};

FileIOManagement IO_management;
std::vector<std::string> vec;
//std::


void sendTestResults(std::map<std::string, bool> outputmap);

bool TestIsolateWord();

bool TestReduce();

bool TestgetNumberOfInstances(std::string format, std::string delim, uint32_t& instance);

bool TestExport();

void TestexportSuccess();

class ReduceTests : public Reduce {
    bool testreduceFile(const std::string & folderPath, const std::string& fileName, std::string& outFile) {

    };

    bool testExport(const std::string& fileName, std::pair<std::string, uint32_t>& outputPair) {
        bool output = Export(fileName, outputPair);
        return output;
    };

    void testexportSuccess() {
        testR ex_success{ outputDirectory ,1};
        return
        return S_output;
    };

    bool isolateWord(const std::string& formattedWord, const std::string& startString, const std::string& endString, std::string& isloatedWord)
	{
		bool result = IsolateWord(formattedWord, startString, endString, isloatedWord);
		return result;
	}
};

void sendTestResults(std::map<std::string, bool> outputmap){
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
};

bool TestIsolateWord(){
    ReduceTests reducer("MAP_OUTPUT", "SORT_OUTPUT");
	bool results_IsolateWord = true;
	std::string delim = "\"";
	std::string formattedWord = "(\"row\", 1)";
	std::string formattedWord2 = "(\"depth_charge\", 1)";
	std::string formattedWord3 = "NO Deliminator";
	std::string isloatedWord = "";
	std::string isloatedWord2 = "";
	std::string isloatedWord3 = "";

	bool results = reducer.isolateWord(formattedWord, delim, delim, isloatedWord);

	int correctWord = isloatedWord.compare("row");
	if (correctWord != 0 || results == false)
	{
		std::cout << "Test_IsolateWord: Unable to Isolate row" << std::endl;
		results_IsolateWord = false;
	}


	results = reducer.isolateWord(formattedWord2, delim, delim, isloatedWord2);
	correctWord = isloatedWord2.compare("depth_charge");
	if (correctWord != 0 || results == false)
	{
		std::cout << "Test_IsolateWord: Unable to Isolate depth_charge" << std::endl;
		results_IsolateWord = false;
	}

	results = reducer.isolateWord(formattedWord3, delim, delim, isloatedWord3);
	if (results != false)
	{
		std::cout << "Test_IsolateWord: did not fail when deliminator is missing" << std::endl;
		results_IsolateWord = false;
	}

	return results_IsolateWord;
};


bool Testreduce() {

}


bool TestgetNumberOfInstances(std::string format, std::string delim, uint32_t& instance)
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


bool TestExport() {
    ReduceTests myFile{ outputDirectory, 1 };
    return myFile.testExport("Test_exportedReduce.txt", "Export complete");
}

void TestexportSuccess() {
    ReduceTests mySuccess{ outputDirectory, 1}; 
    return mySuccess.testexportSuccess("Success.txt". "Success");
}




int main(void) {

    IO_management.getListofTextFiles(outputDirectory, fileList);

    //call all tests
    TestIsolateWord(); 
    Testreduce();
    TestgetNumberOfInstances();
    TestExport();
    TestexportSuccess();
    sendTestResults(std::map<std::string, bool> outputmap);
}



