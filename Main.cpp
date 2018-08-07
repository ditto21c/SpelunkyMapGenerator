#include "GenerateRoom.h"
#include <windows.h>
#include "CsvLoader.h"
#include <stdio.h>

void main()
{
	std::map<int, std::vector<string>> tiles_container;

	CCsvLoader loader;
	char buffer[11];
	for (int i=0; i<5; ++i)
	{
		std::snprintf(buffer, 11, "Tile%d0.csv", i);
		std::vector<string> tiles = loader.LoadFile(buffer);
		tiles_container.insert(std::pair<int, std::vector<string>>(i, tiles));
	}

	CGenerateRoom generateRoom;
	generateRoom.SetTilesContainer(tiles_container);
	//generateRoom.SetRandomSeed(GetTickCount());
	generateRoom.Generate(5);
	generateRoom.Show(true);
	
	for(int i=0; i<4; ++i)
		cout << endl;

	generateRoom.Show(false);
}
