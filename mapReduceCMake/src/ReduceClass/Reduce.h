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
ostream& operator<<(ostream& output, const vec& v), int>>;

class Reduce{
    public:

            //variables, method titles, constructors and destructor

            Reduce(); //constructor

            Reduce(const string intermediateDir); //with no memory allocation

            Reduce(const string intermediateDir, size_t buffer); //with buffer memory

            ~Reduce(); //destructor

            bool importData(const string& filepath, const string& filename);

            std::vector<string> vec;
            std::vector<std::pair<string, int>> reduced_vector;

            void reduce(const std::string& key, int& Iter start_val, int& Iter end_val, reduced_val); 
            //four parameters, a string key, a start value, a end value, and a output redued value
            //Iterator will start from the front and iterate to the end for the values of a key
            //it will add to the counter how many it iterated through
            //key stays constant with no change
            //values will be added and put under the key it belongs to.

            bool emptyBuffer(); //clean up memory

            std::vector<std::pair<string, int>>& exportReduce(); 
            //output vector with reduced values

            bool exportReduce(const string filename, int val); //write to file and export

            bool exportSuccess(const string filename); //write success to file and export


    private:
            int bufferLimit{}; 
            std::vector<std::pair<string, int>> vec; //input data
            std::vector<std::pair<string, int>> reduced_vector; //reduced vector for output
            int maxbuffsize{};
            string intermediateDirectory;
            string initialDirectory;
            FileIOManagement IO_management;
};

#endif  //REDUCE_H, header file for Reduce class
