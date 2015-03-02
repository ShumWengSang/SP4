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

using namespace std;

enum HELP_BUTTON
{
	back,
	volUp,
	volDown,
	help
};

class CInputSystem;

class helpState : public CGameState
{
protected:
	helpState(void){};
	TextureImage button[4];
	TextureImage popUp[4];
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

	//Inputs
	void MouseMove (int x, int y);//
	void MouseClick(int button, int state, int x, int y);//
	void MouseWheel(int button, int dir, int x, int y){}

	static helpState* Instance() 
	{
		return &theHelpState;
	}

private:
	static helpState theHelpState;

	CInputSystem* InputSystem;
	CButtons* theButton[4];
	AudioPlayer * sound;
	ISoundEngine *se;



};

