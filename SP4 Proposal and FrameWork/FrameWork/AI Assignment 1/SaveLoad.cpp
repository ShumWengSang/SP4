#include "SaveLoad.h"


CSaveLoad::CSaveLoad(void)
{
}
CSaveLoad::~CSaveLoad(void)
{
}

void CSaveLoad::init()
{
	day = 0;
	money = 0;
	mask = 0;
	here = false;
}

void CSaveLoad::Load(string fileName)
{
	ifstream inData;
	inData.open (fileName);

	string data[4];

	if (inData.is_open())
	{
		while (!inData.eof())
		{
			//the first is a dummy
			getline (inData, data[0]);
			getline (inData, data[1]);
			day = atoi(data[1].c_str());

			getline (inData, data[2]);
			money = atoi(data[2].c_str());

			getline (inData, data[3]);
			mask = stoi(data[3].c_str());

			here = true;
		}	

		inData.close ();
	}
	else
		here = false;
		//cout << "Failed opening" << endl;
}

void CSaveLoad::Save(string fileName)
{
	ofstream outData;
	outData.open(fileName);
	
	string data[3];

	data[0] = to_string((_ULonglong)day);
	data[1] = to_string((_ULonglong)money);
	data[2] = to_string((_ULonglong)mask);

	if (outData.is_open())
	{
		outData << 0 << endl;
		for (int i = 0; i < 3; i++)
			outData << data[i] << endl;
	
		outData.close ();
	}
}

void CSaveLoad::overwriteData(string fileName, int day, int money, int mask)
{
	this->day = day;
	this->money = money;
	this->mask = mask;

	Save(fileName);
}

int CSaveLoad::getDay()
{
	return day;
}
int CSaveLoad::getMoney()
{
	return money;
}
int CSaveLoad::getMask()
{
	return mask;
}

bool CSaveLoad::getHere()
{
	return here;
}
void CSaveLoad::off()
{
	here = false;
}