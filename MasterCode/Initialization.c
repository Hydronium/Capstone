#include "Initialization.h"
#include "stm32f4_discovery_lcd.h"

#include "LCDHandler.h"
#include "RTCHandler.h"
#include "TimerHandler.h"
#include "ProgramButtonHandler.h"
#include "VisualAlertsHandler.h"
#include "ScheduleHandler.h"
#include "StepperMotorHandler.h"

void Initialization()
{
	LCDInit();
	//RTCInit();
	TimerInit();
	PBHandlerInit();
	VisualAlertsInit();
	ScheduleInit();
	StepperMotorInit();
}
