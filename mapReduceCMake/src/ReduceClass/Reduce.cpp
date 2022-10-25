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
using std::iterator;
using std::fstream;
using std::ifstream;
using std::ostream_iterator;
using std::make_pair;
using std::map;



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

Reduce::Reduce(const Reduce& mem) {
    bufferLimit = mem.bufferLimit;
    intermediateDirectory = mem.intermediateDirectory;
    initialDirectory = mem.initialDirectory;
    IO_management = mem.IO_management;
    vec = mem.vec;
    reduced_vector = mem.reduced_vector;


}

/*TO DO: WRITE COMMENTS ON IMPORTDATA*/
bool Reduce::importData(const string& folderPath, const string& fileName)
    //from sorter grab the sorted data 
    //then insert the data into an input vector, then send it to the reduce method
    
{   
    //declare an empty vector
    std::vector<std::pair<string, uint32_t>> vec;
    bool dataAttained = true;
    const std::string Encap_1 = "[";
    const std::string Encap_2 = "]";
    if(IO_management.readFileIntoVector(folderPath, fileName, vec)) {

        for (size_t iterator_index = 0; iterator_index < vec.size(); iterator_index++) {

            reduce(vec.at(iterator_index), Encap_1); //TO DO: FIX THIS
            //reduce(vec.at(iterator_index));
        }
    }
    else{
        cout<<"Sorted data was not imported to reducer" <<endl;
        dataAttained = false;
    }

    return dataAttained;
};


std::string Reduce::configOutput(const std::string& key, const uint32_t& val) {
    std::string configuredOutput = "(\"" + key + "\"";
    for (size_t item = 0; item < val; item++) {
        configuredOutput.append(key, val);
    }
    configuredOutput.append("");

    return configuredOutput;
}

/*TO DO: WRITE COMMENTS reduce function
take input vector from importData
//for loop iterate through the input vector
    //while it inserts reduced values into reduced_vector
    //if statement to change boolean for executionComplete
        //if input vector is empty, then executionComplete = true
        //if not executionComplete = false cout <<error occurred << 
        //if executionComplete = true

    //for loop for embedding from vec to reduced vector 
*/
bool Reduce::reduce() {
    //int& Iter start_val, int& Iter end_val
   

    bool executionComplete = false;
    bool vectorSent = false;
    std::vector<std::pair<string, uint32_t>> vec; //input data ("hello", [1,1,1], "hi", [1,1],...)
    std::vector<std::pair<string, uint32_t>> reduced_vector; //currently empty, output vector
    std::vector<std::string,uint32_t>::iterator rVec;

    int total_sum = 0; //total at each keyword
    
    if (executionComplete = false) {
            for (std::vector<std::string,uint32_t>::iterator rVec = vec.begin(); rVec != vec.end(); ++rVec) {
                vec.push_back(configOutput(rVec->first, rVec->second));

             while (auto i : vec; vec[i].second.begin() != vec[i].second.end(); i++) {
                int total_sum = i;
                reduced_vector.push_back(configOutput(vec->first, vec->second));
        };

        executionComplete = true;
        //return executionComplete;
        
        }

    }
    else {
        cout<< "execution was not completed" <<endl;
        executionComplete = false;
        //return executionComplete;
    }
        

    return executionComplete; //return executionComplete; //false defines that task has failed
}


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
    else{
        cout<< "was not able to export the reduced file" <<endl;
        bool vectorSent = false;
        return vectorSent;
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

    else {
        cout << "Reduced file has not been sent, will not allow success to occur" << endl;
        vectorSent = false;
    };
    return vectorSent;
    
}        

/*empty buffer */
bool Reduce::emptyBuffer(){
    //clear the cache 
};

ostream& operator<<(ostream& output, const vec& v)
{
    output << "(" << v.first << ":" << v.second << ")"; //formatting the output results
    return output;
};
