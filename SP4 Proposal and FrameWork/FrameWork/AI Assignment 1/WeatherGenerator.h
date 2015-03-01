#pragma once
#include <vector>
#include <iostream>
#define DayTime 9
#define noiseWidth DayTime * 7

//There are 9 hours of work time, meaning 4.5 minutes total game.
//Every hour, the haze forecast would update. Meaning every 30 seconds.
//It will update a total of 9 times.
//Generate 9 * 7 for entire week, thus 63.

class PerlineNoise
{
public:
	int persistence;
	int Number_Of_Octaves;
	PerlineNoise()
	{
		persistence = 2;
		Number_Of_Octaves = 4;
	}

	double Noise1(int x)
	{
		x = (x << 13) ^ x;
		return (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
	}


	double SmoothedNoise_1(float x)
	{
		return Noise1(static_cast<int>(x / 2)) + Noise1(static_cast<int>(x - 1)) / 4 + Noise1(static_cast<int>(x + 1)) / 4;
	}

	double Cosine_Interpolate(double a, double b, double x)
	{
		double ft = x * 3.1415927;
		double f = (1 - cos(ft)) * .5;

		return  a*(1 - f) + b*f;
	}

	double InterpolatedNoise_1(float x)
	{
		int integer_X = int(x);
		int fractional_X = static_cast<int>(x - integer_X);

		double v1 = SmoothedNoise_1((static_cast<float>(integer_X)));
		double v2 = SmoothedNoise_1((static_cast<float>(integer_X+1)));

		return Cosine_Interpolate(v1, v2, fractional_X);

	}

	double PerlinNoise_1D(float x)
	{

		double total = 0;
		double p = persistence;
		double n = Number_Of_Octaves - 1;

		for (int i = 0; i < n; i++)
		{

			double frequency = 2 * i;
			double  amplitude = p * i;

			total = total + InterpolatedNoise_1(x * frequency) * amplitude;

		}

		return total;

	}
};

class WeatherGenerator
{
public:
	WeatherGenerator();
	~WeatherGenerator();
	

	std::vector<float> HazeAveragePerDay;
	std::vector<float> HazeGraph;

	std::vector<float> DailyStartHaze;

	void PrintOutHourly();
	void PrintOutGraph();

	//double noise[noiseWidth];
	double turbulence(double x, double size);

	double interpolation(double x);
	std::vector<float> GetHazeAvg();
};

