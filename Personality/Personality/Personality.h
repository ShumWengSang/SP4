#pragma once

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cmath>

extern bool InBetween(int NumbertoCheck, int Start, int End);

class Vector3
{
public:
	int x, y;
	Vector3()
	{
		x = 0;
		y = 0;
	}; 
	Vector3(int x, int y)
	{
		this->x = x;
		this->y = y;
	}; 
	Vector3 Vector3::operator-(const Vector3& rhs) const
	{
		return Vector3(x - rhs.x, y - rhs.y);
	}
	float Vector3::Length(void) const
	{
		return sqrt((double)x * x + y * y );
	}
};

class Personality
{
public:
	Personality();
	~Personality();

	float HazePreference;
	float DistancePreference;
	float MoneyPreference;
	
};

//Haze factors
//Distance Factors
//Money factors

