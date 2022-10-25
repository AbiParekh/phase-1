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

            Reduce(); 
            //constructor

            Reduce(const string tMemory); 
            //with no memory allocation

            Reduce(const string tMemory, size_t bufferSize); 
            //with buffer memory

            ~Reduce(); 
            //destructor


    protected:

            bool importData(const string& folderPath, const string& fileName);
            //import data from sorter class
            //pass 

            std::vector<std::pair<string, uint32_t>> vec;
            //input vector with data inserted from the sorter

            std::vector<std::pair<string, uint32_t>> reduced_vector;
            //vector used for storing reduced values from the reduce function.

            std::string Reduce::configOutput(const std::string& key, const uint32_t& val);
            //configure the output 

            bool reduce(); 
            //Iterator will start from the front and iterate to the end for the values of a key
            //it will add to the counter how many it iterated through
            //key stays constant with no change
            //values will be added and put under the key it belongs to.

            bool emptyBuffer(); 
            //clean up memory

            std::vector<std::pair<string, int>>& exportReduce(); 
            //output vector with reduced values

            bool exportReduce(const string filename, const string key, const int val); 
            //write to file and export

            bool exportSuccess(const string filename); 
            //write success to file and export

        
            std::vector<std::pair<string, int>> vec; //input data
            std::vector<std::pair<string, int>> reduced_vector; //reduced vector for output

            int bufferLimit{}; //memory limits
            string intermediateDirectory; //saved to buffer
            string initialDirectory; //FileIO
            FileIOManagement IO_management; //using fileio class
};

#endif  //REDUCE_H, header file for Reduce class
