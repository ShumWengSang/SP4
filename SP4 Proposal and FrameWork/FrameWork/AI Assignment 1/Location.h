#pragma once
#include <iostream>
class Location
{
private:
	int x, y,z;

public:
	Location(void);
	~Location(void);

	void renderMap(void);
	
	void setX(int x);
	void setY(int y);

	int getX();
	int getY();

};

