#pragma once
#include <iostream>
#include <vector>
#include "GameState.h"
#include "GameStateManager.h"
#include "Input.h"
#include "GameObject.h"
#include "Global.h"

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

	static CPlayState* Instance() {
		return &thePlayState;
	}

private:
	static CPlayState thePlayState;

	//Input System
	CInputSystem* InputSystem;

	void RenderCharacter(GameObject* go);
	GameObject* player;
	GameObject* police;

	std::vector<GameObject*> v_Total;
};

