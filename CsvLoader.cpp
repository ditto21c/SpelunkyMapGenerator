#include "CsvLoader.h"
#include <fstream>

CCsvLoader::CCsvLoader()
{

}

CCsvLoader::~CCsvLoader()
{

}

std::vector<string> CCsvLoader::LoadFile(string fileName)
{
	Items.clear();

	std::ifstream loadFile(fileName);
	string lineStr;
	
	while (getline(loadFile, lineStr))
	{
		size_t idx = 0;

		while (1)
		{
			idx = lineStr.find(",");
			if (string::npos == idx)
			{
				Items.push_back(lineStr);
				break;
			}
			string item = lineStr.substr(0, idx);
			lineStr.erase(0, item.length() + 1);
			Items.push_back(item);
		}
	}

	loadFile.close();

	return Items;
}

std::string CCsvLoader::Find(unsigned int idx)
{
	if (idx < Items.size())
		return Items[idx];
	return "";
}