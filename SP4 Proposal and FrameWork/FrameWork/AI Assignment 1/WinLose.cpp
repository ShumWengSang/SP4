#include "WinLose.h"


WinLose::WinLose(void)
{
	profit = loss = win = false;
	
}


WinLose::~WinLose(void)
{
}

void WinLose::calcOutcome(int money)
{
	if (money > theMoney->getCurrentMoney())
	{
		profit = true;
	}
	else 
	{
		loss = true;
	}

}

bool WinLose::GetResult (bool result)
{
	if (result == true)
	{
		win = result;
	}
	else
	{
		win = false;
	}
	return win;
}

