#pragma once
#include <vector>
#include <iostream>

using namespace std;

class CGameState;

class CGameStateManager
{
public:
	
	static CGameStateManager* getInstance();

	void Init(const char* title, int width=640, int height=480, int bpp=32, bool fullscreen=false);
	void Cleanup();

	void ChangeState(CGameState* state);
	void PushState(CGameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	CGameState* GetCurrentState();

	bool Running() {
		return m_running; 
	}
	void Quit() { 
		m_running = false; 
	}

private:
	static CGameStateManager *instance;

	// the stack of states
	vector<CGameState*> StackOfStates;

	bool m_running;
	bool m_fullscreen;

};

