#include "Money.h"
#include "Global.h"
using namespace std;

#pragma once

class Money;

class WinLose
{
private:
	bool win;

public:
	WinLose(void);
	~WinLose(void);

	void calcOutcome(int);
	void SetResult(bool);
	bool GetResult();

	CMoney *theMoney;
};
