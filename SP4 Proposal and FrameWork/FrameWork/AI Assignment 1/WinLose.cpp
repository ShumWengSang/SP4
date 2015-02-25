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
	if (money > 900)
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