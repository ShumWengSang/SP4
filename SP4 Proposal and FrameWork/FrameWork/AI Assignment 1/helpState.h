#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "GameState.h"
#include "GameStateManager.h"
#include "Input.h"
#include "Global.h"
#include "TextureImage.h"
#include "Buttons.h"
#include "AudioPlayer.h"
#include "LoadState.h"
#include "MenuState.h"

using namespace std;

enum HELP_BUTTON
{
	back,
	volUp,
	volDown
};

class CInputSystem;

class helpState : public CGameState
{
protected:
	helpState(void){};
	TextureImage button[3];
	TextureImage slider[2];
	TextureImage background[1];

public:
	
	~helpState(void);

	void Init();
	void Cleanup(){}

	void Pause(){}
	void Resume(){}

	void HandleEvents(CGameStateManager* GSM);//
	void Update(CGameStateManager* GSM);//
	void Draw(CGameStateManager* GSM);//

	void LoadTextures();//
	void keyboardUpdate(void);//
	void LoadButtons();
	void DrawButtons();
	void DrawBackground();
	void DrawInfo();

	//Inputs
	void MouseMove (int x, int y);//
	void MouseClick(int button, int state, int x, int y);//
	void MouseWheel(int button, int dir, int x, int y){}

	static helpState* Instance() 
	{
		return &theHelpState;
	}

	void *font_style;
	void printw(float x, float y, float z, char* format, ...);
	
	
private:
	static helpState theHelpState;
	AudioPlayer * sound;
	CInputSystem* InputSystem;
	CButtons* theButton[3];

	ISoundEngine *se;

	bool volumeUp;
	bool volumeDown;
};

