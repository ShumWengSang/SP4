#pragma once
#include <iostream>
#include <vector>
#include "InGameState.h"
#include "InGameStateManager.h"
#include "Global.h"
#include "Input.h"
#include "InGameState.h"
#include "TextureImage.h"
#include "Buttons.h"

using namespace std;

enum ENDSTATE_BUTTON
{
	save
};

class CInputSystem;

class CEndOfDayState : public CInGameState
{
private:
	CEndOfDayState(void) {};

	TextureImage button[1];
	TextureImage background[1];

public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CInGameStateManager* GSM);
	void Update(CInGameStateManager* GSM);
	void Draw(CInGameStateManager* GSM);
	void LoadTextures();
	void LoadButtons();
	void DrawButtons();
	void DrawBackground();
	void keyboardUpdate(void);

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	static CEndOfDayState* Instance() {
		return &theEndOfDayState;
	}

private:
	static CEndOfDayState theEndOfDayState;
	CButtons* theButton[4];
};

