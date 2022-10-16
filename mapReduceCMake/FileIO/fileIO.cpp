#include "fileIO.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>

namespace fs = std::filesystem;
bool FileIOManagement::writeVectorToFile(const std::string filePath, const std::string fileName, const std::vector<std::string>& items)
{
	if (validDirectory(filePath))
	{
		std::string fileNameAndPath = filePath + "\\" + fileName;
		std::ofstream  outFile;
		outFile.open(fileNameAndPath);
		if (!outFile || !outFile.good())
		{
			std::cout << "Unable to create file (" << fileNameAndPath << ") in Write Vector to File Request" << std::endl;
		}
		for (size_t itemNumber = 0; itemNumber < items.size(); itemNumber++)
		{
			std::string tempHoldingVarForItem = items.at(itemNumber);
			outFile << tempHoldingVarForItem << ", ";
		}

		outFile.close();
	}
	else
	{
		std::cout << "Invalid Folder Path ("<< filePath << ") within the Write Vector To File Request" << std::endl;
		return false;
	}
		return true;
}


bool FileIOManagement::readFileIntoVector(const std::string filePath, const std::string fileName, std::vector<std::string>& items)
{
	if (!canAccessFile(filePath, fileName))
	{
		std::cout << "Invalid File (" << fileName << ") within the read File Into Vector Request" << std::endl;
		return false;
	}

	std::string current_path = (std::filesystem::current_path()).string();
	std::string fileNameAndPath = filePath + "\\" + fileName;
	std::ifstream infile(fileNameAndPath);

	std::string line;
	while (std::getline(infile, line))
	{
		items.push_back(line);
	}

#ifdef PRINT_DEBUG
	std::cout << " THE FILE " << filePath << "\\" << fileName << " IS AS FOLLOWS:" << std::endl;
	for (size_t line = 0; line < items.size(); line++)
	{
		std::cout << "Line " << line << ": " << items.at(line) << std::endl;
	}
#endif
	return true;
}

bool FileIOManagement::canAccessFile(const std::string& filePath, const std::string& fileName)
{
	std::string current_path = (std::filesystem::current_path()).string();
	std::string fileNameAndPath = filePath + "\\" + fileName;
	std::ifstream infile(fileNameAndPath);
	return infile.good();
}

/// <summary>
/// Validates the Directory Exist and is a Directory
/// </summary>
bool FileIOManagement::validDirectory(const std::string& folderPath)
{
	std::string current_path = (std::filesystem::current_path()).string();


	const std::filesystem::path sandbox{ folderPath };
	if (!std::filesystem::exists(sandbox))
	{
		std::cout << "ERROR: The Folder Path: " << folderPath << " does not exist!" << std::endl;
		std::cout << "Current Working Directory is " << current_path << std::endl;
		return false;
	}
	else if (!std::filesystem::is_directory(sandbox))
	{
		std::cout << folderPath << " is not a directory!" << std::endl;
		return false;
	}

	return true;
}


bool FileIOManagement::getListOfTextFiles(std::string inputFolder, std::vector<std::string>& fileList)
{
	if (validDirectory(inputFolder))
	{
		for (const auto& entry : fs::directory_iterator(inputFolder))
		{
#ifdef PRINT_DEBUG
			std::cout << "entry.path() = " << entry.path() << ", entry.path().filename(): " << entry.path().filename() << ", extension: " << entry.path().extension() << std::endl;
#endif
			if ((entry.path().has_extension()) && (entry.path().extension().string().compare(".txt") == 0))
			{				
				fileList.push_back(entry.path().filename().string());
			}
			else
			{
				std::cout << "Ignoring the file " << entry.path().filename() << " as it is not a text file " << std::endl;
			}	
		}
			
	}
	return true;
}
