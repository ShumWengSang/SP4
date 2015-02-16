#include "Application.h"
#include <mmsystem.h>

CApplication* CApplication::instance = NULL;

bool CApplication::Init()
{
	//Set camera position
	theCamera = new Camera(Camera::LAND_CAM);
	theCamera->SetPosition(0.0, 2.0, -5.0);
	theCamera->SetDirection(0.0, 0.0, 1.0);

	//Game State Manager
	GSM = CGameStateManager::getInstance();
	GSM->Init("Game State Manager");
	GSM->ChangeState(CMenuState::Instance());

	//Real-Time Loop Control
	timelastcall = timeGetTime();
	frequency = 70.0f;
	CTimer::getInstance()->init();

	return true;
}

void CApplication::Update() 
{
	//Calculate the framerate
	timelastcall = timeGetTime();

	//Update Time
	CTimer::getInstance()->updateTime();

	//Handle the GSM events
	GSM->HandleEvents();

	//Update GSM
	GSM->Update();
}

void CApplication::renderScene() {

	//Clear the Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	//Constrain Update
	if ((timeGetTime()-timelastcall) > 1000.f / frequency) //"timeGetTime()-timelastcall" is DeltaTime
		Update(); //Update Game

	//Render
	GSM->Draw();
	
	//CTimer::getInstance()->drawFPS();

	//Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();

	//Swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}

void CApplication::changeSize(int w, int h) {

	//Prevent a divide by zero, when window is too short
	//(you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = (float) (1.0f* w / h);

	//Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	//Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

//Returns only one Instance of CApplication
CApplication* CApplication::getInstance()
{
	//Singleton Structure
	if (instance == NULL)
		instance = new CApplication();
	return instance;
}

//Exit
void CApplication::drop()
{
	if (theCamera != NULL)
	{
		delete theCamera;
		theCamera = NULL;
	}
	if (GSM != NULL)
	{
		GSM->Cleanup();
		delete GSM;
		GSM = NULL;
	}
	if(CTimer::getInstance() != NULL)
	{
		CTimer::drop();
	}
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

