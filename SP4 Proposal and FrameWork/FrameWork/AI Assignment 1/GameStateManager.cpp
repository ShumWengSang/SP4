#include "GameStateManager.h"
#include "GameState.h"

CGameStateManager* CGameStateManager::instance = NULL;

//Only returns one Instance of CGameStateManager
CGameStateManager* CGameStateManager::getInstance()
{
	//Singleton Structure
	if (instance == NULL)
		instance = new CGameStateManager;
	return instance;
}

void CGameStateManager::Init(const char* title, int width, int height, int bpp, bool fullscreen)
{
	m_fullscreen = fullscreen;
	m_running = true;
}

void CGameStateManager::Cleanup()
{
	// cleanup the all states
	while ( !StackOfStates.empty() ) {
		StackOfStates.back()->Cleanup();
		StackOfStates.pop_back();
	}

	// switch back to windowed mode so other 
	// programs won't get accidentally resized
	if ( m_fullscreen ) {
	}
}

void CGameStateManager::ChangeState(CGameState* state) 
{
	// cleanup the current state (Calls Destructor, destroys InputSystem, causes crash)

	// store and init the new state
	StackOfStates.push_back(state);
	StackOfStates.back()->Init();
}

void CGameStateManager::PushState(CGameState* state)
{
	// pause current state
	if ( !StackOfStates.empty() ) {
		StackOfStates.back()->Pause();
	}

	// store and init the new state
	StackOfStates.push_back(state);
	StackOfStates.back()->Init();
}

void CGameStateManager::PopState()
{
	// cleanup the current state
	if ( !StackOfStates.empty() ) {
		StackOfStates.back()->Cleanup();
		StackOfStates.pop_back();
	}

	// resume previous state
	if ( !StackOfStates.empty() ) {
		StackOfStates.back()->Resume();
	}
}

void CGameStateManager::HandleEvents() 
{
	// let the state handle events
	StackOfStates.back()->HandleEvents(this);
}

void CGameStateManager::Update() 
{
	// let the state update the theGSM
	StackOfStates.back()->Update(this);
}

void CGameStateManager::Draw() 
{
	// let the state draw the screen
	StackOfStates.back()->Draw(this);
}

CGameState* CGameStateManager::GetCurrentState()
{
	return StackOfStates.back();
}

