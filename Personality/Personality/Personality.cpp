#include "Personality.h"


Personality::Personality()
{
	/* initialize random seed: */
	srand(time(NULL));
	int total = 300;
	HazePreference = rand() % 298;
	DistancePreference = rand() % (299 - HazePreference);
	MoneyPreference = rand() % (300 - DistancePreference);
}


Personality::~Personality()
{
}

