#include "fileIO.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <cstdio>

namespace fs = std::filesystem;
bool FileIOManagement::writeVectorToFile(const std::string filePath, const std::string fileName, const std::vector<std::string>& items)
{
	bool result = true;
	if (validDirectory(filePath))
	{
		std::string fileNameAndPath = filePath + "\\" + fileName;
		std::ofstream  outFile;
		outFile.open(fileNameAndPath);
		if (!outFile || !outFile.good())
		{
			std::cout << "Error: Unable to create file (" << fileNameAndPath << ") in Write Vector to File Request" << std::endl;
			result = false;
			
		}
		else
		{
			for (size_t itemNumber = 0; itemNumber < items.size(); itemNumber++)
			{
				std::string tempHoldingVarForItem = items.at(itemNumber);
//				outFile << tempHoldingVarForItem << "\n";
				outFile << tempHoldingVarForItem << std::endl;

			}

			outFile.close();
		}
		
	}
	else
	{
		std::cout << "Error:  Invalid Folder Path ("<< filePath << ") within the Write Vector To File Request" << std::endl;
		result = false;
	}
		
	return result;
}



bool FileIOManagement::readFileIntoVector(const std::string filePath, const std::string fileName, std::vector<std::string>& items)
{
	if (!canAccessFile(filePath, fileName))
	{
		std::cout << "Error: Invalid File (" << fileName << ") within the read File Into Vector Request" << std::endl;
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

	return true;
}



bool FileIOManagement::canAccessFile(const std::string& filePath, const std::string& fileName)
{
	std::string current_path = (std::filesystem::current_path()).string();
	std::string fileNameAndPath = filePath + "\\" + fileName;
	std::ifstream infile(fileNameAndPath);
	return infile.good();
}



bool FileIOManagement::validDirectory(const std::string& folderPath)
{
	std::string current_path = (std::filesystem::current_path()).string();


	const std::filesystem::path sandbox{ folderPath };
	if (!std::filesystem::exists(sandbox))
	{
		std::cout << "ERROR: The Folder Path: " << folderPath << " does not exist!" << std::endl;
		std::cout << "INFO: Current Working Directory is " << current_path << std::endl;
		return false;
	}
	else if (!std::filesystem::is_directory(sandbox))
	{
		std::cout << "Error: Provided Path (" << folderPath << ") is not a directory!" << std::endl;
		return false;
	}

	return true;
}



bool FileIOManagement::createDirectory(const std::string& folderPath, const std::string& newFolderName)
{
	bool result = true;
	if (validDirectory(folderPath))
	{
		std::string newFolderPathFull = folderPath + "\\" + newFolderName;

		// If the folder exist delete the contents 
		if (validDirectory(newFolderPathFull))
		{
			std::cout << "Warning: Already Exist, deleting directory and contents " << std::endl;
			fs::remove_all("newFolderPathFull"); // Deletes one or more files recursively.
		}
		
		// If the Folder Does not exist create it 
		fs::create_directories(newFolderPathFull);

		if (!validDirectory(newFolderPathFull))
		{
			std::cout << "Error: Unable to Create the Directory (" << newFolderPathFull << ")" << std::endl;
		}
	}
	else
	{
		result = false;
	}
	return result;
}

bool FileIOManagement::getListOfTextFiles(const std::string& inputFolder, std::vector<std::string>& fileList)
{
	bool result = true;
	if (validDirectory(inputFolder))
	{
		for (const auto& entry : fs::directory_iterator(inputFolder))
		{
			if ((entry.path().has_extension()) && (entry.path().extension().string().compare(".txt") == 0))
			{				
				fileList.push_back(entry.path().filename().string());
			}
			else
			{
				std::cout << "Warning: Ignoring the file " << entry.path().filename() << " as it is not a text file " << std::endl;
			}	
		}
			
	}
	else
	{
		result = false;
	}
	return result;
}


// OBE DO NOT UNIT TEST 

bool FileIOManagement::getListOfTextFilesBasedOnStart(const std::string& inputFolder, const std::string& startingSubString, std::vector<std::string>& fileList)
{
	if (validDirectory(inputFolder))
	{
		for (const auto& entry : fs::directory_iterator(inputFolder))
		{
			if ((entry.path().has_extension()) && (entry.path().extension().string().compare(".txt") == 0))
			{
				std::string tempFileName = entry.path().filename().string();
				
				// Ensure the File Name is not smaller then the substring before attempting check
				if (tempFileName.size() > startingSubString.size())
				{
					//Find the Starting String and Verify it starts at Position 0
					size_t pos = tempFileName.find(startingSubString);
					if (pos != std::string::npos && pos == 0)
					{
						fileList.push_back(entry.path().filename().string());
					}
				}
			}
			else
			{
				std::cout << "Warning: Ignoring the file " << entry.path().filename() << " as it is not a text file " << std::endl;
			}
		}

	}
	return true;
}
