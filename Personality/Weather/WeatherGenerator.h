#pragma once
#include <vector>
#include <iostream>
#define noiseWidth 42
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

