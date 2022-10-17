
#include "Source.h"
#include <filesystem>

#define BufferSize 10 //number of elements per row
namespace fs = std::filesystem;

int main()
{
	string path = fs::current_path().parent_path().parent_path().generic_string();

	string inputDirectory{ path + "/demo/inputDir" };
	string intermediateDirectory { path + "/demo/middleDir" };
	string outputDirectory{ path +  "/demo/outputDir" };


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