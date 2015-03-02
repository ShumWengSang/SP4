#pragma once
#include <iostream>
#include "GameState.h"
#include "GameStateManager.h"
#include "Input.h"
#include "Global.h"
#include "TextureImage.h"
#include "Buttons.h"
#include "AudioPlayer.h"
#include "WinLose.h"

class CInputSystem;
class WinLose;

class EndGameState : public CGameState
{
protected:
	TextureImage background[2];

private:
	bool result;

public:
	EndGameState(void);
	~EndGameState(void);

	void LoadTextures();
	void DrawBackground();
	void outcome();

	WinLose *profitLoss;

private:
	CInputSystem* InputSystem;
	AudioPlayer * sound;
	ISoundEngine *se;

};