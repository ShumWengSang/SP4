#pragma once
#include "Vector3.h"
#include "freeglut.h"
#include "Global.h"
#include "Timer.h"

class Bar
{
	private:
		Vector3 Position;
		float Percentage;
		float Height;
		Vector3 Color;
		bool Active;
		bool done;
		int Dir;
		int Speed;
	public:
		Bar(void);
		~Bar(void);
		void init(float r,float g,float b,Vector3 pos);
		void draw();
		void update(float r);
		//get
		bool getdone();
		Vector3 getPos();
		Vector3 getColor();
		float getPercentage();
		bool getActive();
		//set
		void setDone(bool d);
		void setActive(bool at);
		void setPos(Vector3 newpos);
		void setColor(Vector3 Color);
		void setPercentage(float Percentage);
};

