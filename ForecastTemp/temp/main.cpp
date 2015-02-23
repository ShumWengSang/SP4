#include "fc.h"
#include "SaveLoad.h"

#include <iostream>
#include "time.h"
using namespace std;


void main (void)
{
	srand(time(NULL));
	
	//Forecast
	int psi[7];

	fc *forecasr;
	forecasr = new fc();
	forecasr->init();

	for ( int i = 0; i < 7; i++)
	{
		psi[i] = rand() % 5 + 1;

		cout << forecasr->forecasting(i+1) << ", " << psi[i] << endl;
		cout << forecasr->getCurrentDay() << endl;

		forecasr->setCurrentDay(i+2);
		forecasr->setActualRange(psi[i], i+1);
		
		cout << endl;
	}


	//SaveLoad
	CSaveLoad *sl1;
	sl1 = new CSaveLoad();
	sl1->init();

	sl1->Load("file1.txt");

	sl1->overwriteData("file1.txt", 9001, 000, 3);
	
	//sl1->Save("file1.txt");


	system("pause");
}