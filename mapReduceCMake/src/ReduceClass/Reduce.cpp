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
using std::make_pair;



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

//Reduce::Reduce(const string key)


Reduce::~Reduce()
    //destructor
{};



/*TO DO: WRITE COMMENTS ON IMPORTDATA*/
bool Reduce::importData(const string& folderPath, const string& fileName)
    //from sorter grab the sorted data 
    //then insert the data into an input vector, then send it to the reduce method
    
{   
    //declare an empty vector
    std::vector<std::string> vec;

    if(IO_management.readFileIntoVector(folderPath, fileName, vec)) {

        for (size_t iterator_index = 0; iterator_index < vec.size(); iterator_index++) {

            reduce(vec.at(iterator_index )); //TO DO: FIX THIS
        }
    }

    return true;
};


/*TO DO: WRITE COMMENTS reduce function
take input vector from importData
*/
bool Reduce::reduce(const std::string& key, int& val, int& reduced_val) {
    //int& Iter start_val, int& Iter end_val
   
    bool executionComplete {false};
    bool vectorSent {false};
    std::vector<std::pair<string, int>> vec; //input data ("hello", [1,1,1], "hi", [1,1],...)
    std::vector<std::pair<string, int>> reduced_vector; //currently empty, output vector

    //int val = 0;
    int total_sum = 0; //total at each keyword
    int sVal = vec[0].[0]; //TO DO: FIX THIS
    int eVal;
    int Iter& = sVal;
    // int& Iter eVal;
    for (Iter* sVal; (Iter) != (eVal); ++(Iter)) {
        total_sum += (Iter);
    reduced_vector.push_back(std::pair<string, int>(key, total_sum));
    }

    bool executionComplete {true};
    return executionComplete; //return executionComplete; //false defines that task has failed
}

/*empty buffer */
bool Reduce::emptyBuffer(){
    //clear the cache 
};


/*TO DO: WRITE COMMENTS
export the reduced values and its key from a vector to a file,
send it to FileIOManagement*/

bool Reduce::exportReduce(const string filename, const string key, const int val) 
    
{
    bool executionComplete;
    if (executionComplete = true) {
        
        bool vectorSent {false};
        //writes out all data to an export file
        string buffFile;
        //reduced_vector; //output vector
        std::vector<std::pair<string, int>> reduced_vector; //output vector

        IO_management.writeVectorToFile(this->intermediateDirectory, buffFile, reduced_vector);
        bool vectorSent {true};
        return vectorSent; //false define vector was not exported

    }
    
}


/*TO DO: WRITE COMMENTS ON exportSuccess
export a success file once the reduce operation has successfully completed 
*/
bool Reduce::exportSuccess(const string filename) {
    //write success and export it to an output file
    //after the entire input vector has been reduced and outputed.

    bool vectorSent;

    if (vectorSent = true) { //reduce function finishes its execuation loop, then go ahead with this statement
        ofstream success_file;
        success_file.open ("successs.txt");
        success_file <<"SUCCESS!\n";
        success_file.close();
    }
    return 0;
    
}        

ostream& operator<<(ostream& output, const vec& v)
{
    output << "(" << v.first << ":" << v.second << ")"; //formatting the output results
    return output;
};
