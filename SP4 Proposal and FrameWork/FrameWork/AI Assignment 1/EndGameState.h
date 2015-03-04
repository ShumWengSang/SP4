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
#include "Highscore.h"
#include "TextureSingleton.h"

class CInputSystem;
class WinLose;

class EndGameState : public CGameState
{
protected:
	TextureImage background[3];
	TextureImage highscore_text;
	TextureImage highscore_box;

private:
	bool result;
	EndGameState(void);
	~EndGameState(void);
	static EndGameState * singleton;

public:
	static EndGameState * Instance()
	{
		if (singleton == NULL)
			singleton = new EndGameState;
		return singleton;
	}

	void Drop();
	
	void Init();
	void Cleanup(){Drop();}

	void Pause();
	void Resume();

	void HandleEvents(CGameStateManager * GSM);
	void Update(CGameStateManager * GSM);
	void Draw(CGameStateManager * GSM);

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);
	void *font_style;
	void printw(float x, float y, float z, char* format, ...);

	void LoadTextures();
	void DrawBackground();
	void DrawHighscore();
	void outcome();
	void InputUsername();
	void SetHighscore(string username);

	void SetMoney(int money);

	WinLose *profitLoss;

private:
	AudioPlayer * sound;
	int money;
	int profit;
	float alpha;
	int Speed, Dir;
	Highscore highscore;
	bool KeyInHighscore;
	bool drawHighscore;
	bool doneInput;
	string input;

};