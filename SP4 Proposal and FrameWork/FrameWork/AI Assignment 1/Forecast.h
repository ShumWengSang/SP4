#pragma once
#include <iostream>
#include <vector>
using namespace std;


class CForecast
{
	int forecastNum[7]; //value of forecasts
	int forecastNumRange[7]; //value of forecasts in a range of numbers
	int actualNum[7]; //value of actual PSI
	int actualNumRange[7]; //value of actual PSI in a range of numbers
	
	int currentDay;
	int maxRange;

public:
	CForecast(void);
	~CForecast(void);
	
	void init();
	void forecasting();

	void checkDay(int curDay);
	void setForecastNumRange(int lowRange, int highRange, int higherChance, int day);
	int prediction(int lowRange, int highRange, int highestChance);


	void setCurrentDay(int day);
	void setActualArray(std::vector<float> actual); //set range on range X

	int getCurrentDay();
	int getCurrentForecast();

	
	float getActual();
};

