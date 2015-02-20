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
		//value += interpolation(x / size) * size;
		size /= 2.0;
	}

	return((128.0 * value / initialSize));

}

/* --- My harmonic summing functions - PDB --------------------------*/

/*
In what follows "alpha" is the weight when the sum is formed.
Typically it is 2, As this approaches 1 the function is noisier.
"beta" is the harmonic scaling/spacing, typically 2.
*/


//double PerlinNoise1D(double x, double alpha, double beta, int n)
//{
//	int i;
//	double val, sum = 0;
//	double p, scale = 1;
//
//	p = x;
//	for (i = 0; i<n; i++) {
//		val = noise1(p);
//		sum += val / scale;
//		scale *= alpha;
//		p *= beta;
//	}
//	return(sum);
//}
