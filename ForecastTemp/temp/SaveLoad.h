#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "fc.h"

#pragma once
class CSaveLoad
{
public:
	CSaveLoad(void);
	~CSaveLoad(void);

	void init();

	void Save(string fileName);
	void Load(string fileName);

	void overwriteData(string fileName, int day, int money, int mask);

private:
	int day;
	int money;
	int mask;
	//fc* tempFC;
};