#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class CMap
{
public:
	CMap(void);
	~CMap(void);

	void Init(const int theScreen_Height, const int theScreen_Width, const int theNumOfTiles_Height, const int theNumOfTiles_Width,const int theMap_Height, const int theMap_Width, const int theTileSize=25);
	bool LoadMap(const string mapName);
	int GetNumOfTiles_Height(void);	// get the number of tiles for the height of the screen
	int GetNumOfTiles_Width(void);	// get the number of tiles for the width of the screen
	int GetTileSize(void);

	int getNumOfTiles_MapHeight(void);	// get the number of tiles for the height of the map
	int getNumOfTiles_MapWidth(void);	// get the number of tiles for the width of the map

	vector<vector<int> > theScreenMap;

private:
	int theScreen_Height;
	int theScreen_Width;
	int theNumOfTiles_Height;	// number of tiles in the screen's height
	int theNumOfTiles_Width;	// number of tiles in the screen's width
	int theTileSize;

	int theMap_Height;	// map's height
	int theMap_Width;	// map's width
	int theNumOfTiles_MapHeight;	// number of tiles in the map's height
	int theNumOfTiles_MapWidth;	// number of tiles in the map's width

	bool LoadFile(const string mapName);
};
