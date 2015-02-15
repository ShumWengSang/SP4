#ifndef CTIMER_H
#define CTIMER_H

#include <Windows.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "freeglut.h"

class CTimer
{
public:
	typedef struct
	{
		bool active;
		int previousTime, timeInterval, limiter;
	} STime;

private:
	static CTimer* instance;
	CTimer();
	~CTimer();
	
	int frameCount, currentTime, previousTime, timeInterval, dtPTime;
	float fps, dt;
	std::vector<STime*> timer;

public:
	static CTimer* getInstance();

	void updateTime();
	float getDelta();
	float getFPS();
	int insertNewTime(int limit);
	bool executeTime(int num);
	void resetTime(int num);
	void changeLimit(int num,int nlimit);
	void init();
	void setActive(bool mode,int num);
	bool getActive(int num);
	int getTimeInterval(int num);
	int getLimit(int num);
	static void drop();
	void drawFPS();
	void *font_style;
	void printw(float x, float y, float z, char* format, ...);
};

#endif