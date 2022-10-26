#pragma once
#ifndef REDUCE_H
#define REDUCE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <iterator>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <utility>
#include <fstream>
#include "FileIO.h"

using std::vector;
using std::string;
using std::ostream;


typedef std::pair<string, int> vec;
ostream& operator<<(ostream& output, const vec& v);

class Reduce{
    public:

            //variables, method titles, constructors and destructor

            Reduce(std::string OutputDirectory); 
            //constructor

            Reduce(const string tMemory, size_t bufferSize); 
            //with buffer memory

            ~Reduce(); 
            //destructor

            bool reduceFile(const std::string & folderPath, const std::string& fileName, std::string& outFile);
            //import data from sorter class
            //pass 


protected:
    
    bool IsolateWord(const std::string& formattedWord, const std::string& startString, const std::string& endString, std::string& isloatedWord);
 
    bool reduce(const std::string inputString);

    bool parseLine(const std::string line, std::pair<std::string, uint32_t>& outputPair);

    bool getNumberOfInstances(std::string format, std::string delim, uint32_t& instance);

    bool Export(const std::string& fileName, std::pair<std::string, uint32_t>& outputPair);

    void exportSuccess();


  
private:

            std::vector<std::pair<string, uint32_t>> reduced_vector;
            std::string outputDirectory;
            size_t bufferLimit; //memory limits
            string intermediateDirectory; //saved to buffer
            string initialDirectory; //FileIO
            FileIOManagement IO_management; //using fileio class
            const std::string outputFileName = "ReducerOutput.txt";;
           
};

#endif  //REDUCE_H, header file for Reduce class
