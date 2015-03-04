#include "Timer.h"

CTimer* CTimer::instance = NULL;

//Constructor
CTimer::CTimer()
	: fps(0.0f), dt(0.0f)
	, previousTime(timeGetTime())
{
	frameCount = currentTime = previousTime = timeInterval = dtPTime = NULL;
}

//Destructor
CTimer::~CTimer() 
{
	while(timer.size() > 0)
	{
		delete timer.back();
		timer.pop_back();
	}
}

//Returns the current instance
CTimer* CTimer::getInstance()
{
	//Only one instance of Timer Class
	if (instance == NULL)
		instance = new CTimer;
	return instance;
}

//Update
void CTimer::updateTime()
{
	//Increase Frame Count
	++frameCount;

	//Set Time
	currentTime = timeGetTime();

	//Calculate Time Passed
	timeInterval = currentTime - previousTime;
	dt = (float)((currentTime-dtPTime)*0.001);
	dtPTime = currentTime;
	
	//Set Previous Time
	std::vector<STime*>::iterator end = timer.end();
	for (std::vector<STime*>::iterator it=timer.begin(); it!=end; ++it)
	{
		STime* time = *it;
		if(time->active)
			time->timeInterval = currentTime - time->previousTime;
	}

	//Calculate Time Passed
	timeInterval = currentTime - previousTime;

	//Updates FPS every 1 second
	if (timeInterval > 1000)
	{
		//Calculate FPS
		fps = frameCount/(timeInterval*0.001f);

		//Set Time
		previousTime = currentTime;

		//Reset Frame Count
		frameCount = NULL;
	}
}

//Init this Timer instance
void CTimer::init()
{
	previousTime = timeGetTime();
	frameCount = currentTime = NULL;
	fps = 0.0f;
	font_style = GLUT_BITMAP_TIMES_ROMAN_24;
}

//Return Delta Time
float CTimer::getDelta()
{
	return dt;
}

//Return FPS
float CTimer::getFPS()
{
	return fps;
}

int CTimer::insertNewTime(int limit)
{
	STime *newTime = new STime;
	newTime->limiter = limit;
	newTime->active = true;
	newTime->previousTime = timeGetTime();
	newTime->timeInterval = 0;
	timer.push_back(newTime);
	return timer.size()-1;
}

bool CTimer::executeTime(int num)
{
	if (timer[num]->active)
	{
		if (timer[num]->timeInterval > timer[num]->limiter)
		{
			resetTime(num);
			return true;
		}
		return false;
	}
	else return false;
}

void CTimer::resetTime(int num)
{
	timer[num]->previousTime = currentTime;
	timer[num]->timeInterval = NULL;
}

void CTimer::changeLimit(int num, int nlimit)
{
	timer[num]->limiter = nlimit;
}

void CTimer::setTimeInterval(int num, int newTI)
{
	timer[num]->timeInterval = newTI;
}

int CTimer::getTimeInterval(int num)
{
	return timer[num]->timeInterval;
}

int CTimer::getLimit(int num)
{
	return timer[num]->limiter;
}

void CTimer::setActive(bool mode, int num)
{
	timer[num]->active = mode;
}

bool CTimer::getActive(int num)
{
	return timer[num]->active;
}

void CTimer::drop()
{
	delete instance;
}

void CTimer::drawFPS()
{
	glPushMatrix();
		//  Load the identity matrix so that FPS string being drawn
		//  won't get animates
		glLoadIdentity ();
		glPushAttrib(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);

			//  Print the FPS to the window
			if (fps > 28.30f)
				glColor3f( 0.0f, 1.0f, 1.0f);
			else if (fps > 28.0f)
				glColor3f( 0.0f, 1.0f, 0.0f);
			else 
				glColor3f( 1.0f, 0.0f, 0.0f);
			printw (25.0, 25.0, 0, "FPS: %4.2f", fps);

		glPopAttrib();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void CTimer::printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	int i;			//  Iterator
	char * text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1; 

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list 
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos3f (x, y, z);


	//  Draw the characters one by one
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);

	//  Free the allocated memory for the string
	free(text);
}