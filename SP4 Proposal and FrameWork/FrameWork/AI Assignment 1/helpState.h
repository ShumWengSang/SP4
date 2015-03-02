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
	TextureImage button[4];
	TextureImage popUp[4];
	TextureImage background[1];

public:
	helpState(void);
	~helpState(void);

	void Init();

	void HandleEvents(CGameStateManager* GSM);
	void Update(CGameStateManager* GSM);
	void Draw(CGameStateManager* GSM);

	void LoadTextures();
	void keyboardUpdate(void);
	void LoadButtons();
	void DrawButtons();
	void DrawBackground();

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);

private:
	static helpState theHelpState;

	CInputSystem* InputSystem;
	CButtons* theButton[4];
	AudioPlayer * sound;
	ISoundEngine *se;



};

