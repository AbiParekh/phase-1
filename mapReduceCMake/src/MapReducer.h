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
	const std::string folderNameForMapOutput = "MapOutput";

	const std::string folderNameForSorterOutput = "SorterOutput";

	const std::size_t bufferSize{ 3000 };

	// Input Argument provide at time of construction with the location of the input files
	std::string inputDirectory_;

	// Input Argument provide at time of construction with the location of an existing temporary directory for storing the final output
	std::string outputDirectory_;

	// Input Argument provide at time of construction with the location of an existing temporary directory for storing working files
	std::string intermediateDirectory_;

	// Map Object 
	FileIOManagement fileManager;

	// 
	MapSorter mapSorter;

	// A new map vector pointing to input directory and sets max buffer size
	Map mapBook; 

	//Reduce reduceOb;
};

//instantiate Reduce object
//Reduce reduceBook{intermediateDirectory_, bufferSize //with buffer memory


// TODO: Reference additional headers your program requires here.
