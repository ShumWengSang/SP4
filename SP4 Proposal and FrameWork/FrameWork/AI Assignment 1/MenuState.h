#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "GameState.h"
#include "GameStateManager.h"
#include "Input.h"
#include "Global.h"
#include "TextureImage.h"
#include "Buttons.h"
#include "AudioPlayer.h"
#include <mmsystem.h>

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

	TextureImage map[1];
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
	void LoadTextures();
	void LoadButtons();
	void DrawButtons();
	void keyboardUpdate(void);
	void playSound();
	void drawMap();
	void checkCameraPos();
	void gameTitle();

	void DrawBackground();
	double interpolation(double x, double y,double z);
	double turbulence(double x, double y, double z, double size);
	void HSLtoRGB(float &Rh, float &Bs, float &Gl);

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	void generatenoise();

	static CMenuState* Instance() {
		return &theMenuState;
	}

	

private:
	static CMenuState theMenuState;

	//Input System
	CInputSystem* InputSystem;
	CButtons* theButton[4];
	AudioPlayer * sound;
	ISoundEngine *se;

	bool isPassed;
	bool skip;
	double exponent;

	float Rh, Gs, Bl;
	float blue;
	int turbulencenum;
	double noise[mWidth][mHeight][mDepth];
};

