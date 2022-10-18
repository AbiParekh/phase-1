
#include "Source.h"
#include <filesystem>

#define BufferSize 3000 //number tokenPairs per partitioned file (tempDirectory)
namespace fs = std::filesystem;

int main()
{
	string path = fs::current_path().parent_path().parent_path().generic_string();

	string inputDirectory{ path + "/inputDir" };
	string middleDirectory { path + "/middleDir" };
	//string outputDirectory{ path +  "/demo/outputDir" };


	//each word trimmed and indexed in a vector
	Map myBook{middleDirectory, BufferSize};
	
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
				//Map Function --> Map and Export
				myBook.map(fileList.at(fileCount), lines.at(fileLine));
			}
	
			//Map Function --> Flush and Export
			myBook.flush(fileList.at(fileCount));

			lines.empty();
		}
	}
	return 0;
}