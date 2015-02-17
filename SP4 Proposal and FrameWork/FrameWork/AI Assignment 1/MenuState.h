#pragma once
#include <iostream>
#include <vector>
#include "GameState.h"
#include "GameStateManager.h"
#include "Input.h"
#include "Global.h"
#include "TextureImage.h"
#include "Buttons.h"

using namespace std;

enum MENU_BUTTON
{
	start,
	loadGame,
	options,
	quit
};

class CInputSystem;

class CMenuState : public CGameState
{
protected:
	CMenuState(void) {};

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
	void DrawButtons();
	void DrawBackground();
	void keyboardUpdate(void);
	void mouseClick(void);

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	static CMenuState* Instance() {
		return &theMenuState;
	}

private:
	static CMenuState theMenuState;

	//Input System
	CInputSystem* InputSystem;
	CButtons* theButton[4];
};

