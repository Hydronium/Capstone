#include "StepperMotorHandler.h"
#include "TimerHandler.h"

int movements = 0;
int timing = 0;

void MoveOneSection(void)
{
	StartCartridgeTimer();
}

void MoveOneStep(void)
{
	timing = movements % 4;
	if ( timing == 0 )
	{
		//A + B
	}
	else if( timing - 1 == 0 )
	{
		//B + A'
	}
	else if( timing - 2 == 0 )
	{
		//A' + B'
	}
	else if( timing - 3 == 0 )
	{
		//B' + A
	}
	movements++;
	
	if (movements == 1)
	{
		StopCartridgeTimer();
		ResetCartridgeTimer();
	}
}
