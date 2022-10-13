#pragma once

#include <string>
#include <vector>
/// <summary>
/// fileIOSupport class abstracts  File Input IO functionality 
/// </summary>
class FileIOManagement
{
public:
	/// <summary>
	/// Method writes the provided Vector into an output files where each String in Vector is written to an individual Line
	/// </summary>
	bool writeVectorToFile(const std::string filePath, const std::string fileName, const std::vector<std::string>& items);


	/// <summary>
	/// Loads each line from file into a Vector where each line is written a string
	/// </summary>
	bool readFileIntoVector(const std::string filePath, const std::string fileName, std::vector<std::string>& items);

	/// <summary>
	/// Loads each line from file into a Vector where each line is written a string
	/// </summary>
	bool readNextLineFromFile(const std::string filePath, const std::string fileName, std::string& inputfile);

};