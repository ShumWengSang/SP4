#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <typeinfo>
#include "Application.h"
#include "Global.h"
#include "Math.h"

using namespace std;

//Mouse Info
typedef struct {
	bool mLButtonUp;
	bool mLClicked;
	bool mLReclicked;
	bool mRButtonUp;
	bool middleButtonUp;
	int  lastX, lastY;
	int clickedX, clickedY;
} theMouseInfo;

class CInputSystem
{
private:
	static CInputSystem *instance;
	CInputSystem();
	~CInputSystem();

public:
	static CInputSystem* getInstance();

	//Mouse Input
	theMouseInfo mouseInfo;
	bool isClick;
	//Camera Variables
	float angle;
	bool OrientCam;

	//Keyboard Input
	bool myKeys[255];

	//Input Functions
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);

	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	//Movement Functions
	void moveMeForward(bool mode, float timeDiff);
	void moveMeSideway(bool mode, float timeDiff);
	void orientMe(float ang);

	//Calculate the Distance moved with reference to its previous Velocity
	float previousVelocity;
	float calculateDistanceMoved(float acceleration, float maxVelocity, float timeDiff);
};

#endif