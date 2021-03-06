#pragma once

#include <iostream>
#include <array>
#include <stdio.h>
using namespace std;

class fc
{
private:
	int forecastNum[7]; //value of forecasts
	int forecastNumRange[7]; //value of forecasts
	int actualNum[7]; //value of actual PSI
	int actualNumRange[7]; //value of actual PSI

	int currentDay;

	int maxRange;

public:
	fc();
	~fc();

	void init();
	int forecasting(int day);

	int checkDay(int curDay);
	int setForecastNumRange(int lowRange, int highRange, int higherChance);
	int prediction(int lowRange, int highRange, int highestChance);

	void setCurrentDay(int day);
	void setActual(float value, int day); //set value on day X
	void setActualRange(float value, int range); //set range on range X

	int getCurrentDay();
	float getCurrentForecast();
};

