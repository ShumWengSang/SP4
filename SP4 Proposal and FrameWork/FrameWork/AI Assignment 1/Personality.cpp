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
	/* initialize random seed: */
	int total = 300;
	while (true)
	{
		HazePreference = rand() % 298;
		DistancePreference = rand() % 299;
		//the below would put money in inverse to haze and distance preference
		MoneyPreference = total - (HazePreference + DistancePreference);
		if (MoneyPreference > 0 && InBetween(HazePreference, 50, 150) && InBetween(DistancePreference, 50, 150) && InBetween(MoneyPreference,50,150))
			break;
	}
	std::cout << "HAZEP: " << HazePreference << std::endl;
	std::cout << "DISTP: " << DistancePreference << std::endl;
	std::cout << "MONEYP: " << MoneyPreference << std::endl;
	std::cout << "TOTAL: " << MoneyPreference + HazePreference + DistancePreference << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	HazePreference /= 100;
	DistancePreference /= 100;
	MoneyPreference /= 100;
}


Personality::~Personality()
{
}

