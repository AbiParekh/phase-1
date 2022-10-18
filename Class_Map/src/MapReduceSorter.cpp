#include "MapReduceSorter.h"
#include "fileIO.h"

std::string MapSorter::formatOutput(const std::string& word, const uint32_t& usageCount)
{
	return std::string();
}

MapSorter::MapSorter(std::string postMapKey, std::string postSortKey):
	LEADING_STRING_MAPPED_FILES(postMapKey),
	LEADING_STRING_SORTED_FILES(postSortKey)
{
}

bool MapSorter::writeSortedMaptoFile(std::string filePath, std::string fileName)
{
	return false;
}

bool MapSorter::addFileContentsToSorter(const std::string& folderPath, const std::string& fileName)
{
	std::vector<std::string> lines;

	if (fileManager.readFileIntoVector(folderPath, fileName, lines))
	{
		for (size_t fileLine = 0; fileLine < lines.size(); fileLine++)
		{
			// DO PARSING FUNCTIN
		}
	}
	return true;
}
