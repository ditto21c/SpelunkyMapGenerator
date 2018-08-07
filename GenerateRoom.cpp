#include "GenerateRoom.h"
#include <iostream>
#include <math.h>
#include <string>

CGenerateRoom::CGenerateRoom()
{
	
}

CGenerateRoom::~CGenerateRoom()
{
	if (room)
		delete room;
}

void CGenerateRoom::SetRandomSeed(unsigned int seed)
{
	this->seed = seed;
	srand(seed);
}

void CGenerateRoom::Generate(int roomSize)
{
	this->roomSize = roomSize;

	if (room)
		delete room;

	room = new int[roomSize*roomSize];
	memset(room, -1, sizeof(int) * roomSize*roomSize);

	GenerateStartTilesPath();
	GenerateStartTilesShape();

	GenerateFirstTilesPath();
	GenerateFirstTilesShape();

	while (!bFindExit)
	{
		GenerateTilesPath();
		GenerateTilesShape();
	}

	for (int i = 0; i < roomSize*roomSize; ++i)
	{
		if (room[i] == -1)
			room[i] = 0;
	}
}

void CGenerateRoom::SetTilesContainer(const std::map<int, std::vector<string>>& tiles_container)
{
	this->tiles_container = tiles_container;
}

void CGenerateRoom::Show(bool bAllTiles)
{
	if (bAllTiles)
	{
		std::map<int, std::vector<string>>::iterator iter = tiles_container.find(0);
		if (iter == tiles_container.end())
			return;

		int containerSize = iter->second.size();
		int sqrtSize = (int)sqrt(containerSize);

		int idx = 0;
		string* allTiles = new string[roomSize*roomSize*iter->second.size()];
		for (int i = 0; i < roomSize*roomSize; ++i)
		{
			std::map<int, std::vector<string>>::iterator iter = tiles_container.find(room[i]);
			if (iter == tiles_container.end())
				return;

			for (auto& str : iter->second)
			{
				allTiles[idx++] = str;
			}
		}

		int row = 0;
		int remainValue = 0;
		for (int i=0; i<roomSize*sqrtSize; ++i)
		{
			row = i / sqrtSize;
			remainValue = i % sqrtSize;
			for (int j=0; j<roomSize*sqrtSize; ++j)
			{
				int curIdx = row * roomSize + (j / sqrtSize);
				int jIdx = j % sqrtSize;
				string cur = allTiles[curIdx * containerSize + (remainValue * sqrtSize + jIdx)];
				std::cout << cur;
			}
			std::cout << std::endl;
		}
	}
	else
	{
		for (int i = 0; i < roomSize*roomSize; ++i)
		{
			cout << room[i];
			if (i % roomSize == roomSize - 1)
				cout << endl;
		}
	}
}

void CGenerateRoom::GenerateStartTilesPath()
{
	curIdx = rand() % roomSize;
	preIdx = curIdx;
}

void CGenerateRoom::GenerateStartTilesShape()
{
	int shape = rand() % 2;
	shape += 1;
	room[curIdx] = shape;
}

void CGenerateRoom::GenerateFirstTilesPath()
{
	preIdx = curIdx;
	int next_move_idx = rand() % 2;
	if (0 == next_move_idx)
	{
		if (curIdx % roomSize == 0)
			curIdx += roomSize;
		else
			curIdx -= 1;
	}
	else
	{
		if (curIdx % roomSize == roomSize-1)
			curIdx += roomSize;
		else
			curIdx += 1;
	}
}

void CGenerateRoom::GenerateFirstTilesShape()
{
	int column, row;
	FindXYPath(curIdx, column, row);
	room[row*roomSize + column] = 1;
}

void CGenerateRoom::GenerateTilesPath()
{
	preIdx = curIdx;
	int next_move_idx = rand() % 5;
	if (next_move_idx < 2)
	{
		if (curIdx % roomSize == 0)
			curIdx += roomSize;
		else
			curIdx -= 1;
	}
	else if (next_move_idx < roomSize)
	{
		if (curIdx % roomSize == roomSize -1)
			curIdx += roomSize;
		else
			curIdx += 1;
	}
	else
	{
		curIdx += roomSize;
	}
}

void CGenerateRoom::GenerateTilesShape()
{
	if (curIdx - roomSize == preIdx) // down
	{
		// ÀÌÀü ÀÎµ¦½º ·ë ÇüÅÂ º¯È¯
		int column, row;
		FindXYPath(preIdx, column, row);
		int roomIdx = row*roomSize + column;
		if (room[roomIdx] == 1)
			room[roomIdx] = 2;
		else if (room[roomIdx] == 4)
			room[roomIdx] = 3;

		FindXYPath(curIdx, column, row);
		roomIdx = row*roomSize + column;
		int shapeType = rand() % 2;
		int shape = 0 == shapeType ? 3 : 4;
		room[roomIdx] = shape;
		if (shape == 4 && row == 3)
			bFindExit = true;
	}
	else
	{
		int column, row;
		FindXYPath(curIdx, column, row);
		int roomIdx = row*roomSize + column;
		if (room[roomIdx] == -1)
		{
			int shapeType = rand() % 3;
			int shape = 2 == shapeType ? shapeType + 2 : shapeType + 1;
			room[roomIdx] = shape;
			if (shape == 4 && row == 3)
				bFindExit = true;
		}
	}
}

void CGenerateRoom::FindXYPath(int idx, int& column, int& row)
{
	column = idx % roomSize;
	row = idx / roomSize;
}