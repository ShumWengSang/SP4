#pragma once
#include <vector>
#include <iostream>
#define noiseWidth 42
//There are 9 hours of work time, meaning 4.5 minutes total game.
//Every hour, the haze forecast would update. Meaning every 30 seconds.
//It will update a total of 9 times.
//Generate 9 * 7 for entire week, thus 63.
class WeatherGenerator
{
public:
	WeatherGenerator();
	~WeatherGenerator();
	std::vector<float> HourlyHaze;
	std::vector<float> HazeGraph;
	void PrintOutHourly();
	void PrintOutGraph();

	//double noise[noiseWidth];
	double turbulence(double x, double size);

	double interpolation(double x);
};

