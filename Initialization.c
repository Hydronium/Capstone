#include "Initialization.h"
#include "stm32f4_discovery_lcd.h"

#include "LCDHandler.h"
#include "RTCHandler.h"
#include "TimerHandler.h"

void Initialization()
{
	LCDInit();
	RTCInit();
	//TimerInit();
}
