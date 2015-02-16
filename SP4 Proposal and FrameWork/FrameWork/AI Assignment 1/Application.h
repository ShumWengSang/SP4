#pragma once

#include <iostream>
#include <stdio.h>
#include "freeglut.h"
#include "GameStateManager.h"
#include "Camera.h"
#include "Timer.h"
#include "MenuState.h"

class CApplication
{
protected:
	CApplication(void)  {};
	~CApplication(void) {};

public:
	static CApplication* getInstance();

	//Glut Functions
	bool Init();
	void changeSize(int w, int h);
	void drop();

	//Game State Manager
	CGameStateManager *GSM;

	//Camera
	Camera *theCamera;

	//Render the Environment
	void renderScene();

private:
	static CApplication *instance;

	//Update Function
	void Update();

	//Real-Time Loop Control
	long timelastcall;
	float frequency;

};

