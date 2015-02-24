#pragma once
#include <iostream>
#include <vector>
using namespace std;


class CForecast
{
	int forecastNum[7]; //value of forecasts
	int forecastNumRange[7]; //value of forecasts in a range of numbers
	int actualNumRange[7]; //value of actual PSI in a range of numbers
	
	int currentDay;
	int maxRange;

public:
	CForecast(void);
	~CForecast(void);
	
	void init();
	int forecasting(int day);

	int checkDay(int curDay);
	int setForecastNumRange(int lowRange, int highRange, int higherChance);
	int prediction(int lowRange, int highRange, int highestChance);

	void setCurrentDay(int day);
	void setActualRange(std::vector<float> actual); //set range on range X

	int getCurrentDay();
	float getCurrentForecast();
};

