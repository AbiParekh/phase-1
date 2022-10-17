#pragma once

#include <string>
#include <vector>

/// Questions for the Professor: 
///		1. Is the program only supposed to accept files with a text file (.txt) extension? 
///		2. Is the program going to have all files are at the top level of the input directory or are we supposed to go lower down?

/// /// <summary>
/// fileIOSupport class abstracts  File Input IO functionality 
/// </summary>
class FileIOManagement
{
public:
	/// <summary>
	/// Method writes the provided Vector into an output files where each String in Vector is written to an individual Line
	/// NOTE: Method will write out a Text File with Extension .txt
	/// </summary>
	bool writeVectorToFile(const std::string filePath, const std::string fileName, const std::vector<std::string>& items);


	/// <summary>
	/// Loads each line from file into a Vector where each line is written a string
	/// </summary>
	bool readFileIntoVector(const std::string filePath, const std::string fileName, std::vector<std::string>& items);

	/// <summary>
	/// Validates the File Exist and can be opened. Assumes the user has already validated the File Path using the Valid Directory Call. 
	/// </summary>
	bool canAccessFile(const std::string& filePath, const std::string& fileName);

	/// <summary>
	/// Validates the Directory Exist
	/// </summary>
	bool validDirectory(const std::string& folderPath);

	/// <summary>
	/// Get the List of Text File from within that Directory. 
	/// FileList contains just the name of the file plus the extension it does not include the route to the file.
	/// </summary>
	bool getListOfTextFiles(std::string inputFolder, std::vector<std::string>& fileList);

};