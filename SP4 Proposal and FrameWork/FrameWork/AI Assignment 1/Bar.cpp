#include "Bar.h"


Bar::Bar(void)
{
	Speed = 100;
	Dir = 1;
}


Bar::~Bar(void)
{
}

void Bar::init(float r,float g,float b ,Vector3 pos)
{
	this->Position = pos;
	Percentage = 0;
	Height = 16;
	Color.Set(r,g,b);
	done = false;
}

void Bar::draw()
{
	glPushMatrix();
		glTranslatef(Position.x, Position.y, Position.z+1);
		glColor4f(Color.x, Color.y, Color.z, 0.7f);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);	glVertex2f(0,Height);
			glTexCoord2f(1,0);	glVertex2f(Percentage, Height);
			glTexCoord2f(1,1);	glVertex2f(Percentage ,0);
			glTexCoord2f(0,1);	glVertex2f(0,0);				
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glLineWidth(4);
		glTranslatef(Position.x, Position.y, Position.z);
		glColor4f(0, 0, 0, 1.0f);
		glBegin(GL_LINE_LOOP);
			glTexCoord2f(0,0);	glVertex2f(0,Height);
			glTexCoord2f(1,0);	glVertex2f(BARLONG, Height);
			glTexCoord2f(1,1);	glVertex2f(BARLONG, 0);
			glTexCoord2f(0,1);	glVertex2f(0,0);				
		glEnd();
	glPopMatrix();
	glColor3f(1,1,1);
}

void Bar::update(float r)
{
	Percentage += r* CTimer::getInstance()->getDelta();

	//std::cout << Percentage << std::endl;
	//Percentage = r *BARLONG/DayTime;
	if (r >= TIMEBLINK)
	{
		Color.x += Speed * Dir * CTimer::getInstance()->getDelta();
		if (Color.x <= 0)
		{
			Color.x = 0; 
			Dir *= Dir;
		}
		else if (Color.x >= 1)
		{
			Color.x = 1;
			Dir *= -Dir;
		}
	}
	if(Percentage>=BARLONG)
	{
		Percentage=BARLONG;
		done = true;
	}
}
//get
bool Bar::getdone()
{
	return this->done;
}
bool Bar::getActive()
{
	return this->Active;
}

Vector3 Bar::getPos()
{
	return Position;
}

Vector3 Bar::getColor()
{
	return Color;
}
float Bar::getPercentage()
{
	return Percentage;
}
//set
void Bar::setDone(bool d)
{
	this->done = d;
}
void Bar::setActive(bool at)
{
	this->Active = at;
}
void Bar::setPos(Vector3 newpos)
{
	Position = newpos;
}
void Bar::setColor(Vector3 newColor)
{
	Color = newColor;
}
void Bar::setPercentage(float P)
{
	Percentage = P;
}