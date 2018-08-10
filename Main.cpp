#include "GenerateRoom.h"
#include <windows.h>
#include "CsvLoader.h"
#include <stdio.h>

void main()
{
	std::map<int, std::vector<string>> tiles_container;

	CCsvLoader loader;
	char buffer[11];
	for (int j = 0; j < 2; ++j)
	{
		for (int i = 0; i < 5; ++i)
		{
			std::snprintf(buffer, 11, "Tile%d%d.csv", i, j);
			std::vector<string> tiles = loader.LoadFile(buffer);
			int key = i * 10 + j;
			tiles_container.insert(std::pair<int, std::vector<string>>(key, tiles));
		}
	}

	CGenerateRoom generateRoom;
	generateRoom.SetTilesContainer(tiles_container);
	generateRoom.SetRandomSeed(GetTickCount());
	generateRoom.Generate(4);
	generateRoom.Show(true);
	
	//for(int i=0; i<1; ++i)
	cout << endl;

	generateRoom.Show(false);
}
