#include "WinLose.h"


WinLose::WinLose(void)
{
	win = false;
	
}


WinLose::~WinLose(void)
{
}

void WinLose::calcOutcome(int money)
{
	if (money > WinMoneyCondition)
	{
		win = true;
	}
	else 
	{
		win = false;
	}

}


bool WinLose::GetResult ()
{
	return win;
}