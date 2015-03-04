#pragma once

#include <iostream>
#include <stdio.h>
#include "freeglut.h"
#include "GameStateManager.h"
#include "Camera.h"
#include "Timer.h"
#include "MenuState.h"
#include "TextureImage.h"

class CApplication
{
protected:
	CApplication(void):clickCheck(false),isPause(false)  {};
	~CApplication(void) {};

public:
	static CApplication* getInstance();

	//Glut Functions
	bool Init();
	void changeSize(int w, int h);
	void drop();

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	//Game State Manager
	CGameStateManager *GSM;

	//Camera
	Camera *theCamera;

	//Render the Environment
	void renderScene();
	
	bool LoadTGA(TextureImage *texture, char *filename);

	bool getClickCheck();
	void setClickCheck(bool clickChecking);

	void setPause(bool isPause);

private:
	static CApplication *instance;

	//Update Function
	void Update();

	//Real-Time Loop Control
	long timelastcall;
	float frequency;

	bool clickCheck;
	bool isPause;
};

