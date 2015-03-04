#pragma once
#include <iostream>
#include <vector>
#include "GameState.h"
#include "InGameState.h"
#include "GameStateManager.h"
#include "InGameStateManager.h"
#include "BuyMaskState.h"
#include "Global.h"
#include "Input.h"
#include "Stalls.h"
#include "WeatherGenerator.h"
#include "Money.h"
#include "Forecast.h"

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

	static bool skipTutorial;
	int day;

	int maskInStock;
	int maskLeft;
	int oldMaskValue;
	int totalMaskForSell;
	int earned;  //money earned by shop 1
	int earned2; //money earned by shop 2
	int earned3; //money earned by shop 3
	int newMoneyValue;
	int moneyAfterBuy;

	bool firstDay;

	bool shop1selected;
	bool shop2selected;
	bool shop3selected;

	void resetValues();

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	//Game State Manager
	static CInGameStateManager *IGSM;

	//Variables that persists throughout the days.
	CStalls *theStall[3];
	CMoney theMoney;
	WeatherGenerator theHaze;
	CForecast *forecasting;

	static CPlayState* Instance(); 
	static CPlayState* Instance(bool load)
	{
		skipTutorial = true;
		//IGSM->ChangeState(CBuyMaskState::Instance());	
		return &thePlayState;
	}

private:
	static CPlayState thePlayState;
};

