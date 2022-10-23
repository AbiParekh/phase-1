#pragma once
#include <vector>
#include <string>
#include <map>
#include "FileIO.h"

class MapSorter
{
public:
		//Constructor
		MapSorter(std::string mapName, std::string SortName);


		//Destructor
		
		bool sortMappedFiles(std::string outputMapDirectory, std::string outpuSortDirectory);

protected:

	
	/// <summary>
	/// S-OConnor TODO Fill Out Comments
	/// </summary>
	/// <param name="folderPath"></param>
	/// <param name="fileName"></param>
	/// <returns></returns>
	bool addFileContentsToSorter(const std::string& folderPath, const std::string& fileName);

	/// <summary>
	/// 
	/// </summary>
	bool ParseLineIntoSortedMap(const std::string& line);

	/// <summary>
	/// 
	/// </summary>
	bool AddPhraseToMap(const std::string& formattedWord, const std::string& startString, const std::string& endString);
	
	/// <summary>
	/// Write Sorted Contents to File in the Format: ("<WORD>", 
	/// </summary>
	/// <param name="filePath"> Existing Path to send Output </param>
	/// <param name="fileName"> Non-Existing File Name that will be generated by this Function</param>
	/// <returns>
	/// True if Successfully Created Output File
	/// </returns>
	bool writeSortedMaptoFile(std::string filePath, std::string fileName);

	/// <summary>
	/// S-OConnor TODO Fill Out Comments
	/// </summary>
	/// <param name="word"></param>
	/// <param name="usageCount"></param>
	/// <returns></returns>
	std::string formatOutput(const std::string& word, const uint32_t& usageCount);

	/// <summary>
	/// 
	/// </summary>
	bool AnotherWordRemaining(const std::string& phrase, const std::string& subString);

	/// <summary>
	/// 
	/// </summary>
	bool IsolateWord(const std::string& formattedWord, const std::string& startString, const std::string& endString, std::string& isloatedWord);

	/// <summary>
	/// 
	/// </summary>
	bool doSortMappedFiles(std::string outputMapDirectory, std::string outpuSortDirectory);

	
	void getSortedMap(std::map<std::string, uint32_t>& returnMap);

private:
	/// <summary>
	/// Collection of Data for Usage. The Key is a String while the Value is the usage count 
	/// </summary>
	std::map<std::string, uint32_t> sortedMap;

	/// <summary>
	/// FileIOManagement Class for accessing Methods for writing to Functions 
	/// </summary>
	FileIOManagement fileManager;

	const std::string MapOuputDirectoryName;

	const std::string SortOuputDirectoryName;

};