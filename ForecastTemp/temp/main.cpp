#include "fc.h"

#include <iostream>
#include "time.h"
using namespace std;

fc *forecasr;

void main (void)
{
	srand(time(NULL));
	int psi[7];
	forecasr = new fc;
	forecasr->init();

	for ( int i = 0; i < 7; i++)
	{
		psi[i] = rand() % 10 + 1;

		cout << forecasr->forecasting(i+1) << ", " << psi[i] << endl;
		cout << forecasr->getCurrentDay() << endl;

		forecasr->setCurrentDay(i+2);
		forecasr->setActualRange(psi[i], i+1);
		
		cout << endl;
	}

	system("pause");
}