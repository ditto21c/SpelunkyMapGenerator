#pragma once
#include <map>
#include <vector>

using namespace std;

class CGenerateRoom
{
public:
	CGenerateRoom();
	virtual ~CGenerateRoom();
	void SetRandomSeed(unsigned int seed);
	void Generate(int roomSize);
	void SetTilesContainer(const std::map<int, std::vector<string>>& tiles_container);
	void Show(bool bAllTiles);


private:
	void GenerateStartTilesPath();
	void GenerateStartTilesShape();

	void GenerateFirstTilesPath();
	void GenerateFirstTilesShape();

	void GenerateTilesPath();
	void GenerateTilesShape();

	void FindXYPath(int idx, int& column, int& row);

private:
	bool bFindExit = false;
	int roomSize = 0;
	int* room = nullptr;
	int curIdx = -1;
	int preIdx = -1;
	unsigned int seed;

	std::map<int, std::vector<string>> tiles_container;
};
