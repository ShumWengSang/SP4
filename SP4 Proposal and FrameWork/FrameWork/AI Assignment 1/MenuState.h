#pragma once
#include <iostream>
#include <vector>
#include "GameState.h"
#include "GameStateManager.h"
#include "Input.h"
#include "Global.h"
#include "TextureImage.h"

using namespace std;

class CInputSystem;

class CMenuState : public CGameState
{
protected:
	CMenuState(void) {};

public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameStateManager* GSM);
	void Update(CGameStateManager* GSM);
	void Draw(CGameStateManager* GSM);
	void keyboardUpdate(void);

	static CMenuState* Instance() {
		return &theMenuState;
	}
	
	TextureImage bg[2];

private:
	static CMenuState theMenuState;

	//Input System
	CInputSystem* InputSystem;

};

