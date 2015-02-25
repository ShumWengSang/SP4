#include "Money.h"
using namespace std;

#pragma once

class Money;

class WinLose
{
private:
	bool profit, loss, win;

public:
	WinLose(void);
	~WinLose(void);

	void calcOutcome(int);
	bool GetResult(bool);

	CMoney *theMoney;
};

