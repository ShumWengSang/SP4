#pragma once
#include <iostream>
#include <vector>
#include "GameState.h"
#include "GameStateManager.h"
#include "Input.h"
#include "Global.h"
#include "TextureImage.h"
#include "Buttons.h"
#include "SaveLoad.h"
#include "AudioPlayer.h"

using namespace std;

enum SAVE_BUTTON
{
	save1,
	save2,
	save3,
	back
};

class CSaveState : public CGameState
{
private:
	CSaveState(void) {};
	
	TextureImage button[4];
	TextureImage background[1];

public:

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameStateManager* GSM);
	void Update(CGameStateManager* GSM);
	void Draw(CGameStateManager* GSM);
	void LoadTextures();
	void LoadButtons();
	void LoadLoadData();
	void DrawButtons();
	void DrawBackground();
	void DrawLoadInfo();
	void keyboardUpdate(void);
	void UpdateLoadData();

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	static CSaveState* Instance() {
		if (theSaveState == NULL)
			theSaveState = new CSaveState();
		return 	theSaveState;
	}

	void *font_style;
	void printw(float x, float y, float z, char* format, ...);

	void Drop()
	{
		for (int i = 0; i < 4; i++)
		{
			if(theButton[i] != NULL)
			{
				delete theButton[i];
				theButton[i] = NULL;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if(loadedFiles[i] != NULL)
			{
				delete loadedFiles[i];
				loadedFiles[i] = NULL;
			}
		}

		if (se != NULL)
		{
			delete se;
			se = NULL;
		}

		/*if (sound != NULL)
		{
			delete sound;
			sound = NULL;
		}*/

		if (theSaveState != NULL)
		{
			delete theSaveState;
			theSaveState = NULL;
		}

	}

private:
	static CSaveState *theSaveState;

	//Input System
	CInputSystem* InputSystem;
	CButtons* theButton[4];
	AudioPlayer * sound;
	ISoundEngine *se;
	CSaveLoad* loadedFiles[3];
};