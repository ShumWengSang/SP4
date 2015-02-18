#include "WeatherGenerator.h"


WeatherGenerator::WeatherGenerator()
{
	for (float i = 0; i < 42; i++)
	{
		HazeGraph.push_back(i /2 + i/4 * sin((float)i));
	}
}


WeatherGenerator::~WeatherGenerator()
{
}

void WeatherGenerator::PrintOutHourly()
{
	for (int i = 0; i < HourlyHaze.size(); i++)
	{
		std::cout << HourlyHaze[i] << std::endl;
	}
}

void WeatherGenerator::PrintOutGraph()
{
	for (int j = 0; j < noiseWidth; j++)
	{
		std::cout << "values " << turbulence(j, 4) << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < HazeGraph.size(); i++)
	{
		for (int j = 0; j < HazeGraph[i]; j++)
		{
			std::cout << " ";
		}
		//std::cout << HazeGraph[i] << std::endl;
		std::cout << "0" << std::endl;
	}
}

double WeatherGenerator::turbulence(double x, double size)
{

	double value = 0.0, initialSize = size;

	while (size >= 1)		//ADD TOGETHER ALL THE ZOOMS TO MAKE TURBULANCE
	{
		value += /*interpolation(x / size) **/ size;
		size /= 2.0;
	}

	return((128.0 * value / initialSize));

}

double WeatherGenerator::interpolation(double x)
{
	//get fractional part of x and y
	double fractX = x - int(x);


	//wrap around
	int x1 = (int(x) + noiseWidth) % noiseWidth;


	//neighbor values
	int x2 = (x1 + noiseWidth - 1) % noiseWidth;


	//smooth the noise with bilinear interpolation
	double value = 0.0;
	value += fractX * HazeGraph[x1];
	value += fractX * HazeGraph[x1];
	value += (1 - fractX) * HazeGraph[x2];
	value += (1 - fractX) * HazeGraph[x2];

	value += fractX * HazeGraph[x1];
	value += fractX * HazeGraph[x1];
	value += (1 - fractX) * HazeGraph[x2];
	value += (1 - fractX) * HazeGraph[x2];

	return value;
}