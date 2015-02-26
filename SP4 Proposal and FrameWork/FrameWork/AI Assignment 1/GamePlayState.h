#pragma once
#include <iostream>
#include <vector>
#include "InGameState.h"
#include "InGameStateManager.h"
#include "Global.h"
#include "Input.h"
#include "InGameState.h"
#include "Money.h"
#include "TextureImage.h"
#include "Buttons.h"
#include "Grid.h"
#include "Stalls.h"
#include "Buyer.h"
#include "Bar.h"

using namespace std;

#define SEEDCOUNT 1

enum PLAYSTATE_BUTTON
{
	pause,
	shop,
	shop2,
	shop3
};

enum BUYING_BUTTON
{
	close,
	bpFifty,
	bpHundred,
	bpTwohundred,
	bpMenu
};

struct cameraValues_
{
	Vector3 camPos;		//position of cam
	Vector3 camPoint;	//position cam is pointing at
	Vector3 camDir;		//direction cam is pointing to
	float camDist;		//zoom dist of cam
	float camDist_max;	//Max zoom dist of cam
	float angle;		//angle of cam along y-axis
	float VEL_X;		//speed of camera rotation along y-axis
	float VEL_Y;		//speed of camera rotation upwards/downwards
	float MAX_Y;		//maximum speed of VEL_Y

};

class CInputSystem;

class CGamePlayState : public CInGameState
{
private:
	CGamePlayState(void) { DayNumber = 0; };

	TextureImage button[7];
	TextureImage map[1];
	TextureImage skyBox[6];
	
	TextureImage buyingButton[4];
	TextureImage buyingBackground[1];
	
	bool isBuying;

	bool isPause;
	bool shop1Selected;
	bool shop2Selected;
	bool shop3Selected;

	Vector3 barPos;

public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CInGameStateManager* GSM);
	void Update(CInGameStateManager* GSM);
	void Draw(CInGameStateManager* GSM);
	void keyboardUpdate(void);
	void LoadTextures();
	void LoadButtons();
	void DrawButtons();
	void drawInfo();
	void DrawSkyBox();

	void DrawBuying();

	void DrawTimeBar();


	void buyMask(int stall, int maskNo);

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	static CGamePlayState* Instance() {
		return &theGamePlayState;
	}

	int DayNumber;
	int HourNumber;

	void *font_style;
	void printw(float x, float y, float z, char* format, ...);

private:
	static CGamePlayState theGamePlayState;

	std::vector<Entity*> theListofEntities;
	std::vector<Tiles *> theSeededTiles;

	CTimer * theTimerInstance;
	int TimerKeySeed;

	int TimerKeyDay;

	void ClickCollision();

	CMoney theMoney;
	CButtons* theButton[4];
	CStalls* theStall[3];
	Grid* theGrid;

	CButtons* theBuyingButton[4];

	Bar theTimeBar;

	//Camera
	cameraValues_ camValues;

	void OnRotate(int x, int y);
};

