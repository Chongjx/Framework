#include <iostream>
#include <fstream>
#include "LoadHmap.h"

bool LoadHeightMap(const char *file_path, std::vector<unsigned char> &heightMap)
{
	std::ifstream fileStream(file_path, std::ios::binary);
	if(!fileStream.is_open())
	{
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
		return false;
	}

    fileStream.seekg(0, std::ios::end);
    std::streampos fsize = (unsigned)fileStream.tellg();
	
	fileStream.seekg(0, std::ios::beg);
	heightMap.resize((unsigned)fsize);
	fileStream.read((char *)&heightMap[0], fsize);
	
	fileStream.close();
	return true;
}

float ReadHeightMap(std::vector<unsigned char> &heightMap, float x, float z)
{
	unsigned terrainSize = (unsigned)sqrt((double)heightMap.size());

	unsigned xCoord = (x + 0.5f) * terrainSize;
	unsigned zCoord = (z + 0.5f) * terrainSize;

	return (float)heightMap[zCoord * terrainSize + xCoord] / 256.f;
}