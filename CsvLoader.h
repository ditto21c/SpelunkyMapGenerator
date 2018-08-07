#pragma once

#include <iostream>
#include <string>
#include <vector>

using std::string;

class CCsvLoader
{
public:
	CCsvLoader();
	virtual ~CCsvLoader();

	std::vector<string> LoadFile(string fileName);
	string Find(unsigned int idx);
	int Count() { return Items.size();}

private:
	std::vector<string> Items;

};