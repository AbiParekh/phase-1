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
using namespace std;

using std::string;
using std::vector;
using std::ostream;
using std::iterator;
using std::fstream;
using std::ifstream;
using std::ostream_iterator;



/*Takes an input with a key and its respective values ("for, [1,1,1,]")
    Sums up all values for each key, and returns a vector with all reduced values
    export function writes out to a file with the reduced values
    output a file written with success at the end.*/



Reduce::Reduce()
    :bufferLimit{2048} //setting a limit to buffer memory
{};


Reduce::Reduce(const string tMemory)
    :intermediateDirectory{tMemory}, bufferLimit{10}
{};


Reduce::Reduce(const string tMemory, size_t bufferSize)
    :intermediateDirectory{tMemory}, bufferLimit{bufferSize}
{};

Reduce::Reduce(const string key)


Reduce::~Reduce()
    //destructor
{};


bool Reduce::importData(const string& folderPath, const string& fileName)
    //from sorter grab the sorted data 
    //then insert the data into an input vector, then send it to the reduce method
    
{   
    //declare an empty vector
    std::vector<std::string> vec;

    if(IO_management.readFileIntoVector(folderPath, fileName, vec)) {

        for (size_t iterator_index = 0; iterator_index < vec.size(); iterator_index++) {

            reduce(vec.at(iterator_index));
        }
    }

    return true;
};


void Reduce::reduce(const string key, int Iter start_val, int Iter end_val, reduced_val) {
    std::vector<std::pair<string, int>> vec; //input data ("hello", [1,1,1], "hi", [1,1],...)
    std::vector<std::pair<string, int>> reduced_vector; //currently empty, output vector

    //int val = 0;
    int total_sum = 0; //total at each keyword
    for (Iter* p_iterate = start_val; (p_iterate) != (*end_val); ++(*p_iterate)) {
        total_sum += *(*p_iterate);
    }
    reduced_val = std::pair<string, int>(key, total_sum);

    reduced_vector.push_back(reduced_val);

}


bool Reduce::emptyBuffer(){
    //clear the cache 
};


bool Reduce::exportReduce(const string key, int val) 
    
{
    //writes out all data to an export file

    reduced_vector; //output vector

    ofstream out_file("final_output.txt"); //create an output file named final_output.txt
    ostream_iterator<string, int> out_iterator(out_file, "\n");
    copy(key, val, out_iterator);

    //copy(reduced_vector.begin(), reduced_vector.end(), out_iterator);
    //cout << reduced_vector[0] << endl;
}



bool Reduce::exportSuccess(const string) {
    //write success and export it to an output file
    //after the entire input vector has been reduced and outputed.

    if () { //fix this
        ofstream success_file;
        success_file.open ("successs.txt");
        success_file <<"SUCCESS!\n";
        success_file.close();
    }
    
    
}        

ostream& operator<<(ostream& output, const vec& v)
{
    output << "(" << v.first << ":" << v.second << ")"; //formatting the output results
    return output;
};
