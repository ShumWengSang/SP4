#include "Forecast.h"


CForecast::CForecast(void)
{
}

CForecast::~CForecast(void)
{
}

void CForecast::init()
{
	currentDay = 1;

	for(int i=0; i<7; i++)
	{
		forecastNum[i] = 0;
		forecastNumRange[i] = 0;
		actualNumRange[i] = 0;
	}

	maxRange = 10;
}


void CForecast::forecasting()
{
	for (int day = 1; day < 8; day++)
	{
		checkDay(day);
		cout << "Day: " << getCurrentDay() << endl;
		cout << "Forecasting: " << getCurrentForecast() << endl;
		cout << "Actual: " << getActual() << endl;
		setCurrentDay(day+1);
	}
	currentDay = 1;
}

void CForecast::checkDay(int curDay)
{
	if(curDay == 2) //day 2
	{
		setForecastNumRange(actualNumRange[0], actualNumRange[0], 1, curDay);
	}
	else if(curDay == 3) //day 3
	{
		if (actualNumRange[0] < actualNumRange[1]) //going up
			setForecastNumRange(actualNumRange[0], actualNumRange[1], 1, curDay);
		
		else if (actualNumRange[1] < actualNumRange[0]) //going down
			setForecastNumRange(actualNumRange[1], actualNumRange[0],-1, curDay);
		
		else if (actualNumRange[0] == actualNumRange[1])//same
			setForecastNumRange(actualNumRange[0], actualNumRange[1], 0, curDay);
	}
	else if(curDay > 3) //day 4++
	{
		int sum = 0;
	
		sum += actualNum[curDay-2] - actualNum[curDay-4];
		
		if (actualNumRange[curDay-3] < actualNumRange[curDay-2]) //going up
			setForecastNumRange(actualNumRange[curDay-3], actualNumRange[curDay-2], sum, curDay);
		
		else if (actualNumRange[curDay-2] < actualNumRange[curDay-3]) //going down
			setForecastNumRange(actualNumRange[curDay-2], actualNumRange[curDay-3], sum, curDay);
	
		else if (actualNumRange[curDay-2] == actualNumRange[curDay-3]) //same
			setForecastNumRange(actualNumRange[curDay-3], actualNumRange[curDay-2], sum, curDay);
	}
	else //day 1
	{
		setForecastNumRange(2, 2, 1, curDay);
	}
}

void CForecast::setForecastNumRange(int lowRange, int highRange, int higherChance, int day)
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

	forecastNumRange[day-1] = result;

	/*
	1= 1-50
	2= 51-100
	3= 101-150
	4= 151-200
	5= 201-250
	6= 251-300
	7= 301-350
	8= 351-400
	9= 401-450
	10=451-500
	*/

	forecastNum[day-1] = rand() % 50 + ((result-1)*50+1);

	//switch ( result )
	//{
	//case 1:
	//	//forecastNumRange[day-1] = 1;
	//	forecastNum[day-1] = rand() % 50 +1;
	//	break;
	//case 2:
	//	//forecastNumRange[day-1] = 2;
	//	forecastNum[day-1] = rand() % 50 +51;
	//	break;
	//case 3:
	//	//forecastNumRange[day-1] = 3;
	//	forecastNum[day-1] = rand() % 50 +101;
	//	break;
	//case 4:
	//	//forecastNumRange[day-1] = 4;
	//	forecastNum[day-1] = rand() % 50 +151;
	//	break;
	//case 5:
	//	//forecastNumRange[day-1] = 5;
	//	forecastNum[day-1] = rand() % 100 +201;
	//	break;
	//}
}

int CForecast::prediction(int lowRange, int highRange, int highestChance)
{
	int temp[11] = {0,0,0,0,0,0,0,0,0,0,0};

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
void CForecast::setActualArray(std::vector<float> actual)
{
	for (int i = 0; i < 7; i++)
	{
		actualNum[i] = actual.at(i);
		for (int j = 1; j < 11; j++)
		{
			if (actualNum[i] > (j-1)*50 && actualNum[i] < j*50)
				actualNumRange[i] = j;
				continue;
		}
	}
}

int CForecast::getCurrentDay()
{
	return currentDay;
}
int CForecast::getCurrentDayRange()
{
	return forecastNumRange[currentDay-1];
}
int CForecast::getCurrentForecast()
{
	return forecastNum[currentDay-1];
}
float CForecast::getActual()
{
	return actualNum[currentDay-1];
}