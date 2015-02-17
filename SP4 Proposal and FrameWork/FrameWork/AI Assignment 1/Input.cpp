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
		CApplication::getInstance()->theCamera->Walk(calculateDistanceMoved(0.01f, 50.0f, timeDiff));
	else //Backward Movement
		CApplication::getInstance()->theCamera->Walk(calculateDistanceMoved(-0.01f, 50.0f, timeDiff));
}

void CInputSystem::moveMeSideway(bool mode, float timeDiff)
{
	if (mode) //Left Movement
		CApplication::getInstance()->theCamera->Strafe(calculateDistanceMoved(-0.01f, 50.0f, timeDiff));
	else //Right Movement
		CApplication::getInstance()->theCamera->Strafe(calculateDistanceMoved(0.01f, 50.0f, timeDiff));
}

void CInputSystem::orientMe(float ang) 
{
	//Camera Orientation
	CApplication::getInstance()->theCamera->Yaw(ang);
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

	//Variables to store currentPos-lastPos
	/*int diffX = x - mouseInfo.lastX;
	int diffY = y - mouseInfo.lastY;

	//Update on y axis
	if (OrientCam)
		CApplication::getInstance()->theCamera->Pitch(diffY * 3.142f / 180.0f);

	//Update on x and z axis
	angle += (float) diffX * 3.142f / 180.0f;
	if (angle > 6.284f)
		angle -= 6.284f;
	else if (angle < -6.284f)
		angle += 6.284f;
	if (OrientCam)
		CApplication::getInstance()->theCamera->Yaw(-angle);*/

	mouseInfo.lastX = x;
	mouseInfo.lastY = y;

	//Checking mouse boundary. (Width)
	/*if  (mouseInfo.lastX > SCREEN_WIDTH-20 || mouseInfo.lastX < 20)
	{
		mouseInfo.lastX = (SCREEN_WIDTH >> 1);
		glutWarpPointer(mouseInfo.lastX, mouseInfo.lastY);
	}

	//Checking mouse boundary. (Height)
	if (mouseInfo.lastY > SCREEN_HEIGHT-20 || mouseInfo.lastY < 20)
	{
		mouseInfo.lastY = (SCREEN_HEIGHT >> 1);
		glutWarpPointer(mouseInfo.lastX, mouseInfo.lastY);
	}*/
}

void CInputSystem::MouseWheel(int button, int dir, int x, int y) {
	
	if(typeid(CApplication::getInstance()->GSM->GetCurrentState()).name() == typeid(CGameState*).name())
		cout << typeid(CApplication::getInstance()->GSM->GetCurrentState()).name() << endl;

	if (dir > 0) {//Zoom In
		/*if(camDist-zoomSpeed*15 > 0)
			camDist -= zoomSpeed;*/
		Vector3 temp = CApplication::getInstance()->theCamera->GetPosition() + CApplication::getInstance()->theCamera->GetDirection();
		CApplication::getInstance()->theCamera->SetPosition(temp.x,temp.y,temp.z);
	}
    else {//Zoom Out
		//camDist += zoomSpeed;
		Vector3 temp = CApplication::getInstance()->theCamera->GetPosition() - CApplication::getInstance()->theCamera->GetDirection();
		CApplication::getInstance()->theCamera->SetPosition(temp.x,temp.y,temp.z);
	}
}

void CInputSystem::MouseClick(int button, int state, int x, int y) {
	switch (button) {

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
	}
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