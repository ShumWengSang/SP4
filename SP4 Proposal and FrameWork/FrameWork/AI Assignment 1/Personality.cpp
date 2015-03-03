#include "Personality.h"


#include <iostream>
static bool InBetween(int NumbertoCheck, int Start, int End)
{
	if (NumbertoCheck < Start)
		return false;
	if (NumbertoCheck > End)
		return false;
	return true;
}

Personality::Personality()
{
	Init();
}


Personality::~Personality()
{
}

void Personality::Init()
{
	/* initialize random seed: */
	int total = 300;
	while (true)
	{
		HazePreference = static_cast<float>(rand() % 298);
		DistancePreference = static_cast<float>(rand() % 299);
		//the below would put money in inverse to haze and distance preference
		MoneyPreference = total - (HazePreference + DistancePreference);
		if (MoneyPreference > 0 && InBetween(static_cast<int>(HazePreference), 50, 150) && InBetween(static_cast<int>(DistancePreference), 50, 150) && InBetween(static_cast<int>(MoneyPreference), 50, 150)
			)
			break;
	}
	HazePreference /= 100;
	DistancePreference /= 100;
	MoneyPreference /= 100;
}