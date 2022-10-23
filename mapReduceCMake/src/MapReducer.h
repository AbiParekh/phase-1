// mapReduceCMake.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <vector>
#include <string>
#include "Sorter/MapReduceSorter.h"
#include "FileIO/fileIO.h"
#include "Map/Map.h"

class MapReducer
{

public:

// Constructor with inputs
MapReducer(std::string inputDir, std::string outputDir, std::string middleDir);

bool reduce(std::string& outputFileName);

std::string getInputDir();

std::string getOutputDir();

std::string getIntermediateDir();

void setInputDir(std::string);

void setOutputDir(std::string);

void setIntermediateDir(std::string);

private:

/// <summary>
/// Validate the Directories required for Reduction 
/// </summary>
/// S-OConnor TODO Fill Out Comment
/// <returns></returns>
bool validateDirectories();

bool doReduce(std::string& outputFileName);

// Variables with Map Reducer
const std::string LEADING_STRING_MAPPED_FILES = "postMap_";

const std::string LEADING_STRING_SORTED_FILES = "postSorting_";

std::string inputDirectory_;

std::string outputDirectory_;

std::string intermediateDirectory_;

std::size_t bufferSize{ 3000 };

FileIOManagement fileManager;

MapSorter mapSorter;

//creates a new map vector pointing to input directory and sets max buffer size
Map mapBook{ inputDirectory_, bufferSize };

//instantiate Reduce object
//Reduce reduceBook{intermediateDirectory_, bufferSize //with buffer memory



};
// TODO: Reference additional headers your program requires here.
