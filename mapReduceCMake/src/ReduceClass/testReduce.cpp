#include "testReduce.h"
#include <iostream>
using namespace std;


//testing importData function
bool importData(const string& filepath, const string& filename) {
    return true;
    //this must the results the function wants
    // If parameter is not true, test fails
}


void test_importData() {
    //cases
    //importData(test filepath, test filename);
    Reduce reduce;
    reduce.importData("filePath", "fileName");
    
}



//testing reduce function
void reduce(const std::string& key, int& val, int& reduced_val) {
    //expected results
}

void testReduce(){
    //cases
}

//testing exportReduce
bool exportReduce(const string filename, int val) {
    //expected results
}

void testExportReduce() {
    //cases
}

//testing exportSucess
bool exportSuccess(const string filename) {
    //expected results
}

void testExportSuccess(){
    //cases
}


//testing emptyBuffer
bool emptyBuffer() {
    //expected results
}

void testEmptyBuffer() {
    //cases
}

int main(void) {
    //call all tests
    test_importData();
    testReduce();
    testExportReduce();
    testExportSuccess();
    testEmptyBuffer();

}



