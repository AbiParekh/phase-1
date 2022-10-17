#pragma once

#include <string>
#include <vector>

/// Questions for the Professor: 
///		1. Is the program only supposed to accept files with a text file (.txt) extension? 
///		2. Is the program going to have all files are at the top level of the input directory or are we supposed to go lower down?
///		3. Does Punctuation include the following: ('.', '!', '?', ',', ':', ';', '-', '[', ']', '{', '}', '(', ')', ''', ' ` ', '"', '...'
///		4. How should we handle the following? '@', '#', '$', '%', '^', '&', '*', '-_', '+', '=', '\', '<', '>', '/', '~'? Should we Treat them as Chars?

/// <summary>
/// Class provides methods for writing and reading from Files
/// </summary>
class FileIOManagement
{
public:
	/// <summary>
	/// Method writes the provided Vector into an output files where each String in Vector is written with a ', ' split between them
	/// NOTE: Method will write out a Text File with Extension .txt
	/// </summary>
	/// <param name="fileName">Name of a File that DOES NOT EXIST within the directory of File Path</param>
	/// <param name="items">Vector with the Contents that will be written into the file</param>
	/// <returns>True if File Created Successfully</returns>
	bool writeVectorToFile(const std::string filePath, const std::string fileName, const std::vector<std::string>& items);

	/// <summary>
	/// Loads each line from file into a Vector where each line is written as a string
	/// </summary>
	/// <param name="filePath">Existing Location of the Directory that the file should be within</param>
	/// <param name="fileName">Name of a File that EXIST within the directory of File Path</param>
	/// <param name="items">Storage Vector where the Contents of the File will be captured. </param>
	/// <returns></returns>
	bool readFileIntoVector(const std::string filePath, const std::string fileName, std::vector<std::string>& items);

	/// <summary>
	/// Validates the File Exist and can be opened. Assumes the user has already validated the File Path using the Valid Directory Call. 
	/// </summary>
	/// <param name="filePath">Existing Location of the Directory that the file should be within</param>
	/// <param name="fileName">Name of a File that EXIST within the directory of File Path</param>
	/// <returns>Returns True if the file can be accessed </returns>
	bool canAccessFile(const std::string& filePath, const std::string& fileName);


	/// <summary>
	/// Validates the Directory Exist
	/// </summary>
	/// <param name="folderPath">Existing Location of the Directory that the file should be within</param>
	/// <returns>Returns True if the path is to a Directory that is accessible </returns>
	bool validDirectory(const std::string& folderPath);

	/// <summary>
	/// Get the List of Text File from within that Directory. 
	/// FileList contains just the name of the file plus the extension it does not include the route to the file.
	/// </summary>
	/// <param name="folderPath">Existing Location of the Directory that the file should be within</param>
	/// <param name="fileList">Vector where file names will be stored</param>
	/// <returns>True if function was able to return fileList</returns>
	bool getListOfTextFiles(const std::string& inputFolder, std::vector<std::string>& fileList);

	/// <summary>
	/// Get the List of Text File from within that Directory if the file starts with a Parameter provided by the user.
	/// FileList contains just the name of the file plus the extension it does not include the route to the file.
	/// </summary>
	/// <param name="folderPath">Existing Location of the Directory that the file should be within</param>
	/// <param name="fileList">Vector where file names will be stored</param>
	/// <returns>True if function was able to return fileList</returns>
	bool getListOfTextFilesBasedOnStart(const std::string& inputFolder, const std::string& startingSubString, std::vector<std::string>& fileList);
};