//#include <LED.h>
#include "stdio.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
  
//#include "stm32f4_discovery_lcd.h"
#include "Initialization.h"
#include "RTCHandler.h"
#include "stm32f4xx_it.h"
#include "LCDHandler.h"
#include "stm32f4_discovery_lcd.h"
#include "ProgramButtonHandler.h"
#include "AlarmHandler.h"
#include "VisualAlertsHandler.h"
#include "Types.h"
#include "StepperMotorHandler.h"

  
char RTCInterrupt = 0;
char timerInterrupt = 0; 
  



structTime currentTime;
int main(void)
{
	int init1 = 0;
	int init2 = 0;
		
	int day = 0;
	int hour = 0;
	int minute = 0;
	int dispense = 0;

	int recentlySavedDay = 0;
	int recentlySavedHour = 0;
	int recentlySavedMinute = 0;
	int recentlySavedDispenseCycle = 0;
	
	int scheduleState = 0;
	int alarmState = 0;
	int alarmMinute = 0;
	
	char test[10];
		
	Initialization();
		

	LCDDisplayText(5, 0, "Running Mode");

	sprintf(test, "%d", currentTime.day);
	LCDDisplayText(0, 0, test);
	sprintf(test, "%0.2d:%0.2d:%0.2d", currentTime.hour, currentTime.minute, currentTime.second);
	LCDDisplayText(1, 0, test);
  
  while (1)
	{

		if (PBHandlerInProgramMode() == 0)
		{   
			if (init1 != 0) 
			{
				LCDClear();
				PBHandlerResetSelections();
				init1 = 0;

				day = 0;
				hour = 0;
				minute = 0;
				dispense = 0;
			}
			if (init2 == 0)
			{
				LCDDisplayText(5, 0, "Running Mode");
				LCDDisplayCurrentAlarmTime(0, 0, 0, 0, -1);
			}
			else if (init2 == 1)
			{
				LCDDisplayText(5, 0, "Running Mode");
				LCDDisplayCurrentAlarmTime(recentlySavedDay, recentlySavedHour, recentlySavedMinute, recentlySavedDispenseCycle, -1);
			}
		}
		else if (PBHandlerInProgramMode() == 1)
		{
			if (PBHandlerIncrementSelection() == 1)
			{
				if (PBHandlerCurrentlySelectedLine() == 0)
				{
					day++;

					if (day == 7)
					{
						day = 0;
					}
				}
				else if (PBHandlerCurrentlySelectedLine() == 1)
				{
					hour++;

					if (hour == 24)
					{
						hour = 0;
					}
				}
				else if (PBHandlerCurrentlySelectedLine() == 2)
				{
					minute++;

					if (minute >= 60)
					{
						minute = 0;
					}
				}
				else if (PBHandlerCurrentlySelectedLine() == 3)
				{
					dispense++;
					
					if (dispense >= 28)
					{
						dispense = 0;
					}
				}
			}

			LCDDisplayText(5, 0, "Program Mode");

			LCDDisplayCurrentAlarmTime(day, hour, minute, dispense, PBHandlerCurrentlySelectedLine());

			if (PBHandlerUserWantsToSave() == 1)
			{
				SetScheduledAlarms(day, hour, minute, dispense);
				recentlySavedDay = day;
				recentlySavedHour = hour;
				recentlySavedMinute = minute;
				recentlySavedDispenseCycle = dispense;

				init2 = 1;
			}
		}

		if (timerInterrupt != 0)
		{
			timerInterrupt = 0;
			currentTime.second++;

			if (currentTime.second >= 60)
			{
				currentTime.second = 0;
				currentTime.minute++;

				if (currentTime.minute >= 60)
				{
					currentTime.minute = 0;
					currentTime.hour++;

					if (currentTime.hour >= 24)
					{
						currentTime.hour = 0;
						currentTime.day++;

						if (currentTime.day >= 6)
						{
							currentTime.day = 0;
						}
					}
				}
			}
		}

		sprintf(test, "%d", currentTime.day);
		LCDDisplayText(0, 0, test);
		sprintf(test, "%0.2d:%0.2d:%0.2d", currentTime.hour, currentTime.minute, currentTime.second);
		LCDDisplayText(1, 0, test);

		if (PBHandlerUserWantsToReset() == 1)
		{
			scheduleState = 1;

			LCDDisplayText(2, 0, "Schedule Enabled");
		}

		if (CheckAlarm(currentTime) == ALARM_EXISTS && 
				scheduleState == 1)
		{
			if (alarmState == 0)
			{
				LCDDisplayText(3, 0, "ALARM: ACTIVATE!");
				ActivateVisualAlert();
				//ActivateAudioAlert
				MoveOneSection();
				alarmMinute = currentTime.minute;
			}
			alarmState = 1;
		}

		if (alarmState == 1)
		{
			if (currentTime.second == 5)//if (currentTime.minute >= alarmMinute + 20)
			{
				DeactivateVisualAlert();
				LCDDisplayText(3, 0, "                    ");
				alarmState = 0;
			}
			
			//if dispense button pressed
			//turn off alarm/reset things/dispense pill
		}	
	}
}
