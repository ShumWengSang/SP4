#include "Input.h"

CInputSystem* CInputSystem::instance = NULL;

//Constructor
CInputSystem::CInputSystem() 
	: OrientCam(true)
{
	//Initialise Keys
	for(short i = 0; i < 255; ++i)
		myKeys[i] = false;

	//Initialise Mouse Variables
	mouseInfo.lastX = SCREEN_WIDTH >> 1;
	mouseInfo.lastY = SCREEN_HEIGHT >> 1;
	mouseInfo.clickedX = SCREEN_WIDTH >> 1;
	mouseInfo.clickedY = SCREEN_HEIGHT >> 1;
	mouseInfo.mRButtonUp = true;

	//Initialise Camera Variables
	angle = previousVelocity = 0.0f;
}

//Destructor
CInputSystem::~CInputSystem() {}

//Singleton Structure
CInputSystem* CInputSystem::getInstance()
{
	//Only allows one instance of InputSystem
	if (instance == NULL)
		instance = new CInputSystem;
	return instance;
}

void CInputSystem::moveMeForward(bool mode, float timeDiff) 
{
	if (mode) //Forward Movement
		Camera::getInstance()->Walk(calculateDistanceMoved(0.01f, 50.0f, timeDiff));
	else //Backward Movement
		Camera::getInstance()->Walk(calculateDistanceMoved(-0.01f, 50.0f, timeDiff));
}

void CInputSystem::moveMeSideway(bool mode, float timeDiff)
{
	if (mode) //Left Movement
		Camera::getInstance()->Strafe(calculateDistanceMoved(-0.01f, 50.0f, timeDiff));
	else //Right Movement
		Camera::getInstance()->Strafe(calculateDistanceMoved(0.01f, 50.0f, timeDiff));
}

void CInputSystem::orientMe(float ang) 
{
	//Camera Orientation
	Camera::getInstance()->Yaw(ang);
}

void CInputSystem::KeyboardDown(unsigned char key, int x, int y)
{
	//Key is pressed
	myKeys[key]= true;
}

void CInputSystem::KeyboardUp(unsigned char key, int x, int y)
{
	//Key is released
	myKeys[key]= false;
}

void CInputSystem::MouseMove (int x, int y) {

	CApplication::getInstance()->MouseMove(x, y);
}

void CInputSystem::MouseClick(int button, int state, int x, int y) {
	/*switch (button) {

		case GLUT_LEFT_BUTTON:
			if (state == 0) 
				mouseInfo.mLButtonUp = false;
			else
				mouseInfo.mLButtonUp = true;
			mouseInfo.clickedX = x;
			mouseInfo.clickedY = y;

			break;

		case GLUT_RIGHT_BUTTON:
			break;

		case GLUT_MIDDLE_BUTTON:
			break;
	}*/

	CApplication::getInstance()->MouseClick(button, state, x, y);
}

void CInputSystem::MouseWheel(int button, int dir, int x, int y) {
	
	CApplication::getInstance()->MouseWheel(button, dir, x, y);
}

float CInputSystem::calculateDistanceMoved(float acceleration, float maxVelocity, float timeDiff)
{
	//d = (u + (10m/s2) * timeDiff) * timeDiff
	float currentVelocity = previousVelocity + acceleration * timeDiff;
	if (currentVelocity > maxVelocity)
		currentVelocity = maxVelocity;
	float distanceMoved = currentVelocity * timeDiff;
	previousVelocity = currentVelocity;
	return distanceMoved;
}