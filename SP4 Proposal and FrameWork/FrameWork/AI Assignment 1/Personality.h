#pragma once

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cmath>

extern bool InBetween(int NumbertoCheck, int Start, int End);


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

