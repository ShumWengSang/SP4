#pragma once
#include <iostream>
#include <vector>
#include "GameState.h"
#include "InGameState.h"
#include "GameStateManager.h"
#include "InGameStateManager.h"
#include "Global.h"
#include "Input.h"

using namespace std;

class CInputSystem;

class CPlayState : public CGameState
{
protected:
	CPlayState(void) {};

public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameStateManager* GSM);
	void Update(CGameStateManager* GSM);
	void Draw(CGameStateManager* GSM);
	void keyboardUpdate(void);

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	//Game State Manager
	CInGameStateManager *IGSM;

	static CPlayState* Instance() {
		return &thePlayState;
	}

private:
	static CPlayState thePlayState;

};

