#include "WeatherGenerator.h"

int persistence = 2;
int Number_Of_Octaves = 4;

double Noise1(int x)
{
	x = (x << 13) ^ x;
	return (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}


double SmoothedNoise_1(float x)
{
	return Noise1(x) / 2 + Noise1(x - 1) / 4 + Noise1(x + 1) / 4;
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
	int fractional_X = x - integer_X;

	double v1 = SmoothedNoise_1(integer_X);
	double v2 = SmoothedNoise_1(integer_X + 1);

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


void main()
{
	WeatherGenerator theWeather;
	for (int i = 0; i < theWeather.HazeGraph.size(); i++)
	{
		double Result = PerlinNoise_1D(theWeather.HazeGraph[i]);

		std::cout << "Result: " << Result  + theWeather.HazeGraph[i]<< std::endl;

		theWeather.HazeGraph[i] += Result;
	}
	theWeather.PrintOutGraph();
	//theWeather.PrintOutGraph();
}