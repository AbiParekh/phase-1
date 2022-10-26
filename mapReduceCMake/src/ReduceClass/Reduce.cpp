#include "Reduce.h"
#include "MapReduceSorter.h"
#include "fileIO.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <iterator>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <utility>
#include <fstream>
#include <map>
using namespace std;

using std::string;
using std::vector;
using std::ostream;
using std::fstream;
using std::ifstream;
using std::ostream_iterator;
using std::make_pair;
using std::map;



/*Takes an input with a key and its respective values ("for, [1,1,1,]")
    Sums up all values for each key, and returns a vector with all reduced values
    export function writes out to a file with the reduced values
    output a file written with success at the end.*/



Reduce::Reduce(std::string OutputDir)
    : bufferLimit(2048),
        outputDirectory(OutputDir)
{}


Reduce::Reduce(const string tMemory, size_t bufferSize)
    : intermediateDirectory{tMemory}, bufferLimit{bufferSize}
{}

//Reduce::Reduce(const string key)


Reduce::~Reduce()
    //destructor
{};

//from sorter grab the sorted data 
//then insert the data into an input vector, then send it to the reduce method
bool Reduce::reduceFile(const string& folderPath, const string& fileName, std::string& outputFile)
{
    outputFile = outputFileName;

    //declare an empty vector
    std::vector<std::string> vec;
    bool dataAttained = true;
 
    if (IO_management.readFileIntoVector(folderPath, fileName, vec)) 
    {

        for (size_t currentLine = 0; currentLine < vec.size(); ++currentLine)
        {

            if (!reduce(vec.at(currentLine)))
            {
                std::cout << "ERROR: Failure attempting to reduce line \"" << vec.at(currentLine) << "\"" << std::endl;
            }
        }
        exportSuccess();
    }
    else
    {
        cout<<"ERROR: Sorted data was not imported to reducer" <<endl;
        dataAttained = false;
    }

    return dataAttained;
}

bool Reduce::reduce(const std::string line)
{
    std::pair<std::string, uint32_t> outputPair;
    if (parseLine(line, outputPair))
    {
        
        Export(outputFileName, outputPair);
    }
    else
    {
        std::cout << std::endl;
    }
    
    return true;

}

bool Reduce::Export(const std::string& fileName, std::pair<std::string, uint32_t>& outputPair)
{
    std::string formattedOutput = "\"" + outputPair.first + "\", " + std::to_string(outputPair.second);
    std::vector<std::string> tempVector;
    tempVector.push_back(formattedOutput);
    IO_management.writeVectorToFile(outputDirectory, fileName, tempVector, true);
    return true;
}

bool Reduce::parseLine(const std::string line, std::pair<std::string, uint32_t>& outputPair)
{
    bool result = true;
    std::string temp = line;
    std::string isoWord;
    uint32_t instances;
    const std::string finalLine;
    
    if (!IsolateWord(line, "\"", "\"", isoWord))
    {
        std::cout << "ERROR: Unable to get key word from Line " << std::endl;
    }
    else if (!getNumberOfInstances(temp, ",", instances))
    {
        std::cout << "Error: Unable to get Instances for key " << isoWord << std::endl;
        result = false;
    }
    else
    {
        outputPair = std::make_pair(isoWord, instances);
    }

    return result;
}


bool Reduce::getNumberOfInstances(std::string format, std::string delim, uint32_t& instance)
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

bool Reduce::IsolateWord(const std::string& formattedWord, const std::string& startString, const std::string& endString, std::string& isloatedWord)
{
    size_t firstPosition = formattedWord.find(startString);
    size_t secondPosition = formattedWord.find(endString, firstPosition + 1);
    if ((firstPosition == std::string::npos) || (secondPosition == std::string::npos)) return false;
    isloatedWord = formattedWord.substr(firstPosition + 1, secondPosition - (firstPosition + 1));

    return true;
}


void Reduce::exportSuccess() 
{
    //write success and export it to an output file
    //after the entire input vector has been reduced and outputed.

        std::string fileName = "success.txt";
        std::vector<std::string> tempVector;
        tempVector.push_back("");
        IO_management.writeVectorToFile(outputDirectory, fileName, tempVector);
        return;
}