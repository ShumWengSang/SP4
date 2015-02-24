#include "Forecast.h"


/*
#include "Forecast.h"

#include <iostream>
#include "time.h"
using namespace std;

CForecast *forecasr;

void main (void)
{
	srand(time(NULL));
	int psi[7];
	forecasr = new CForecast;
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
*/


CForecast::CForecast(void)
{
}

CForecast::~CForecast(void)
{
}

void CForecast::init()
{
	setCurrentDay(1);

	for(int i=0; i<7; i++){
		forecastNum[i] = 0;
		forecastNumRange[i] = 0;
		actualNumRange[i] = 0;
	}

	maxRange = 5;
}


int CForecast::forecasting(int day)
{
	//if (currentDay == day)
		return checkDay(day);
}

int CForecast::checkDay(int curDay)
{
	if(curDay == 2)
	{
		return setForecastNumRange(actualNumRange[0], actualNumRange[0], 0);
	}
	else if(curDay == 3)
	{
		if (actualNumRange[0] < actualNumRange[1]) //going up
			return setForecastNumRange(actualNumRange[0], actualNumRange[1], 1);
		
		else if (actualNumRange[1] < actualNumRange[0]) //going down
			return setForecastNumRange(actualNumRange[1], actualNumRange[0],-1);
		
		else if (actualNumRange[0] == actualNumRange[1])//same
			return setForecastNumRange(actualNumRange[0], actualNumRange[1], 0);
	}
	else if(curDay > 3)
	{
		int sum = 0;
	
		sum += actualNumRange[curDay-2] - actualNumRange[curDay-4];
		
		if (actualNumRange[curDay-3] < actualNumRange[curDay-2]) //going up
			return setForecastNumRange(actualNumRange[curDay-3], actualNumRange[curDay-2], sum);
		
		else if (actualNumRange[curDay-2] < actualNumRange[curDay-3]) //going down
			return setForecastNumRange(actualNumRange[curDay-2], actualNumRange[curDay-3], sum);
	
		else if (actualNumRange[curDay-2] == actualNumRange[curDay-3]) //same
			return setForecastNumRange(actualNumRange[curDay-3], actualNumRange[curDay-2], sum);
	}
	else
	{
		return setForecastNumRange(1, 10, 0);
	}
}

int CForecast::setForecastNumRange(int lowRange, int highRange, int higherChance)
{
	int lR, hR, hC;
	int result;

	if (higherChance == 0)
	{		
		lR = lowRange-1;
		hR = highRange+1;
		hC = 0;

		if (lowRange <= 1)
		{
			lR = 1;
		}
		if (highRange >= maxRange)
		{
			hR = maxRange;
		}
	}
	else if (higherChance > 0)
	{
		lR = lowRange;
		hR = highRange+1;
		hC = highRange+1;

		if (highRange+1 > maxRange)
		{
			hR = maxRange;
			hC = maxRange;
		}
	}
	else if (higherChance < 0)
	{
		lR = lowRange-1;
		hR = highRange;
		hC = lowRange-1;

		if (lowRange-1 < 1)
		{
			lR = 1;
			hC = 1;
		}
	}

	result= prediction(lR, hR, hC);

	forecastNumRange[currentDay-1] = result;

	/*
	1= 1-50
	2= 51-100
	3= 101-150
	4= 151-200
	5= 201-300
	*/
	switch ( result )
	{
	case 1:
		//forecastNumRange[day-1] = 1;
		forecastNum[currentDay-1] = rand() % 50 +1;
		break;
	case 2:
		//forecastNumRange[day-1] = 2;
		forecastNum[currentDay-1] = rand() % 50 +51;
		break;
	case 3:
		//forecastNumRange[day-1] = 3;
		forecastNum[currentDay-1] = rand() % 50 +101;
		break;
	case 4:
		//forecastNumRange[day-1] = 4;
		forecastNum[currentDay-1] = rand() % 50 +151;
		break;
	case 5:
		//forecastNumRange[day-1] = 5;
		forecastNum[currentDay-1] = rand() % 100 +201;
		break;
	}

	return forecastNumRange[currentDay-1];
}

int CForecast::prediction(int lowRange, int highRange, int highestChance)
{
	int temp[6] = {0,0,0,0,0,0};

	for(int start = 0; start < maxRange; start++)
	{
			//temp[start] += 1;

		if(start >= lowRange-1 && start <= highRange-1)
			temp[start] += 1;
		if(start == highestChance-1)
			temp[start] += 2;

		temp[maxRange] += temp[start];
	}
	
	int x1 = rand() % temp[maxRange] + 1;
	int x2 = rand() % temp[maxRange] + 1;
	int x3 = rand() % temp[maxRange] + 1;
	int x = (x1 + x2 + x3)/3;

	int sum = temp[0];

 	if( 0 < x && x <= sum)
		return 1;
	for (int i = 1; i < maxRange; i++)
	{
		if( sum < x && x <= sum+temp[i])
			return i+1;
		else
			sum += temp[i];
	}
}



void CForecast::setCurrentDay(int day)
{
	currentDay = day;
}
void CForecast::setActualRange(std::vector<float> actual)
{
	for (int i = 0; i < 7; i++)
	actualNumRange[i] = actual.at(i);
}

int CForecast::getCurrentDay()
{
	return currentDay;
}
float CForecast::getCurrentForecast()
{
	return forecastNum[currentDay-1];
}