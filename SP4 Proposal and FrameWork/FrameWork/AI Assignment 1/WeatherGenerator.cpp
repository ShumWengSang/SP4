#include "WeatherGenerator.h"

//15 - 24
WeatherGenerator::WeatherGenerator()
{
	for (float i = 0; i < noiseWidth; i++)
	{
		HazeGraph.push_back(i /2 + i/4 * sin((float) 0.7 * i));
	}

	for (int i = 0; i <= DayTime; i++)
	{
		HazeGraph[i] = HazeGraph[15 + i];
	}
	for (int i = DayTime; i <= DayTime * 2; i++)
	{
		HazeGraph[i] = HazeGraph[15 + i];
	}
	PerlineNoise thePerlineNoise;

	for (int i = 0; i < HazeGraph.size(); i++)
	{
		double Result = thePerlineNoise.PerlinNoise_1D(HazeGraph[i]);

		std::cout << "Result: " << i << " " << Result + HazeGraph[i] * 13 << std::endl;

		HazeGraph[i] += Result;
		HazeGraph[i] *= 13;

		if ((i+1) % 9 == 0 && i != 0)
		{
			std::cout << "END OF DAY -----------------" << std::endl;
			//DailyStartHaze.push_back
		}
	}


}


WeatherGenerator::~WeatherGenerator()
{
}

void WeatherGenerator::PrintOutHourly()
{

}

double interpolate(double a, double b, double x)
{
	double ft = x * 3.1415927;
	double f = (1.0 - cos(ft))* 0.5;
	return a*(1.0 - f) + b*f;
}

void WeatherGenerator::PrintOutGraph()
{

	std::cout << std::endl;
	for (int i = 0; i < HazeGraph.size(); i++)
	{
		for (int j = 0; j < HazeGraph[i] / 13; j++)
		{
			std::cout << " ";
		}
		//std::cout << HazeGraph[i] << std::endl;
		std::cout << "0" << std::endl;
	}

	std::cout << std::endl;
	for (int i = 0; i < HazeAveragePerDay.size(); i++)
	{
		std::cout << "Haze Average Number: " << i << " " << HazeAveragePerDay[i] << std::endl;
	}

}

std::vector<float> WeatherGenerator::GetHazeAvg()
{
	HazeAveragePerDay.clear();
	for (int i = 0; i < 7; i++)
	{
		float temp = 0;
		for (int j = 0; j < DayTime; j++)
		{
			temp += HazeGraph[j + i * DayTime];
		}
		temp /= DayTime;
		HazeAveragePerDay.push_back(temp);
	}
	return HazeAveragePerDay;
}



double WeatherGenerator::turbulence(double x, double size)
{

	double value = 0.0, initialSize = size;

	while (size >= 1)		//ADD TOGETHER ALL THE ZOOMS TO MAKE TURBULANCE
	{
		//value += interpolation(x / size) * size;
		size /= 2.0;
	}

	return((128.0 * value / initialSize));

}
