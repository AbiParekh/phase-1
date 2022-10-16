
#include "Source.h"
#include "FileIO/fileIO.h"

#define BufferSize 10 //number of elements per row


int main()
{
	string inputDirectory{ "C:\\Users\\esevieux\\source\\repos\\MapReduce_CMake_Project1\\demo\\inputDir" };
	string intermediateDirectory{ "C:\\Users\\esevieux\\source\\repos\\MapReduce_CMake_Project1\\demo\\middleDir" };
	string outputDirectory{ "C:\\Users\\esevieux\\source\\repos\\MapReduce_CMake_Project1\\demo\\outputDir" };


	//each word trimmed and indexed in a vector
	Map myBook{BufferSize};
	
	//FileIO Integration Check
	FileIOManagement fileManager;
	std::vector<std::string> fileList;
	fileManager.getListOfTextFiles(inputDirectory, fileList);

	// Input Processing and initial Map Call
	for (size_t fileCount = 0; fileCount < fileList.size(); fileCount++)
	{
		std::vector<std::string> lines;
		if (fileManager.readFileIntoVector(inputDirectory, fileList.at(fileCount), lines))
		{
			for (size_t fileLine = 0; fileLine < lines.size(); fileLine++)
			{
				//std::cout << "File (" << fileList.at(fileCount) << ") Line (" << fileLine << "): " << lines.at(fileLine) << std::endl;
				//Map Function --> Map
				myBook.map(fileList.at(fileCount), lines.at(fileLine));
			}
			lines.empty();
		}
		//Map Function --> Export
		fileManager.writeVectorToFile(intermediateDirectory, fileList.at(fileCount), myBook.mapExport());
	}

}