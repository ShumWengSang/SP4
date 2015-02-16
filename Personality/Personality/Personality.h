#pragma once

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */



class Vector3
{
public:
	int x, y;
	Vector3(){}; 
	Vector3(int x, int y)
	{
		this->x = x;
		this->y = y;
	}; 
};

class Personality
{
public:
	Personality();
	~Personality();

	int HazePreference;
	int DistancePreference;
	int MoneyPreference;
	
};

//Haze factors
//Distance Factors
//Money factors

