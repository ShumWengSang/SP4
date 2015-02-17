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

	//Game State Manager
	CInGameStateManager *IGSM;

	static CPlayState* Instance() {
		return &thePlayState;
	}

private:
	static CPlayState thePlayState;

};

