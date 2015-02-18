#include "fc.h"


fc::fc(void)
{
}

fc::~fc(void)
{
}

void fc::init()
{
	//forecastNum[7] = 0,0,0,0,0,0,0;
	//forecastNumRange[7] = 0,0,0,0,0,0,0;
	//actualNum[7] = 0,0,0,0,0,0,0;
	//actualNumRange[7] = 0,0,0,0,0,0,0;
	
	setCurrentDay(1);

	for(int i=0; i<7; i++){
		forecastNum[i] = 0;
		forecastNumRange[i] = 0;
		actualNum[i] = 0;
		actualNumRange[i] = 0;
	}


}


int fc::forecasting(int day)
{
	//if (currentDay == day)
		return checkDay(day);
}

int fc::checkDay(int curDay)
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

int fc::setForecastNumRange(int lowRange, int highRange, int higherChance)
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
		if (highRange >= 10)
		{
			hR = 10;
		}
	}
	else if (higherChance > 0)
	{
		lR = lowRange;
		hR = highRange+1;
		hC = highRange+1;

		if (highRange+1 > 10)
		{
			hR = 10;
			hC = 10;
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

int fc::prediction(int lowRange, int highRange, int highestChance)
{
	int temp[11] = {0,0,0,0,0,0,0,0,0,0,0};
	int max = 10;

	for(int start = 0; start < max; start++)
	{
			temp[start] += 1;

		if(start >= lowRange && start <= highRange)
			temp[start] += 2;
		if(start == highestChance-1)
			temp[start] += 3;

		temp[10] += temp[start];
	}

	int x = rand() % temp[10] + 1;
	int sum = temp[0];

 	if( 0 < x && x <= sum)
		return 1;
	for (int i = 1; i < max; i++)
	{
		if( sum < x && x <= sum+temp[i])
			return i+1;
		else
			sum += temp[i];
	}
	
		/*if( 0 < x && x <= temp[0])
			return 1;
		if( temp[0] < x && x <= (temp[0] + temp[1]) )
			return 2;
		if( (temp[0] + temp[1]) < x && x <= (temp[0] + temp[1] + temp[2]) )
			return 3;
		if( (temp[0] + temp[1] + temp[2]) < x && x <= (temp[0] + temp[1] + temp[2] + temp[3]) )
			return 4;
		if( (temp[0] + temp[1] + temp[2] + temp[3]) < x && x <= temp[5] )
			return 5;*/
}



void fc::setCurrentDay(int day)
{
	currentDay = day;
}
void fc::setActual(float value, int day)
{
	actualNum[day-1] = value;
}
void fc::setActualRange(float value, int range)
{
	actualNumRange[range-1] = value;
}

int fc::getCurrentDay()
{
	return currentDay;
}
float fc::getCurrentForecast()
{
	return forecastNum[currentDay-1];
}