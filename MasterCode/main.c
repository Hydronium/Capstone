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

  
char RTCInterrupt = 0;
char timerInterrupt = 0; 
  
int init1 = 0;
int init2 = 0;
  
int day = 0;
int hour = 0;
int minute = 0;
int dispense = 0;
  
int dayDisplay = 0;
int hourDisplay = 0;
int minuteDisplay = 0;
int secondDisplay = 0;
int dispenseDisplay = 0;
  
int saveDay = 999;
int saveHour = 999;
int saveMinute = 999;
int saveDispense = 999;
int saveDay2 = 999;
int saveHour2 = 999;
int saveMinute2 = 999;
int saveDispense2 = 999;
int tempSeconds = 999;

int recentlySavedDay = 0;
int recentlySavedHour = 0;
int recentlySavedMinute = 0;
int recentlySavedDispenseCycle = 0;


structTime currentTime;
int main(void)
{
	char test[10];
		
	char DayInfo[20];
	char HourInfo[20];
	char MinuteInfo[20];
	char DispenseInfo[20];
		
	Initialization();
		

	LCDDisplayText(5, 0, "Running Mode");

	sprintf(test, "%d", dayDisplay);
	LCDDisplayText(0, 0, test);
	sprintf(test, "%0.2d:%0.2d:%0.2d", hourDisplay, minuteDisplay, secondDisplay);
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
            }
            if (init2 == 0)
            {
                LCDDisplayText(5, 0, "Running Mode");
                LCDDisplayText(6, 0, "Day---: 0");
                LCDDisplayText(7, 0, "Hour--: 00");
                LCDDisplayText(8, 0, "Minute: 00");
                LCDDisplayText(9, 0, "Dispense: 0");
            }
            else if (init2 == 1)
            {
							LCDDisplayText(5, 0, "Running Mode");
							LCDDisplayCurrentDayTime(recentlySavedDay, recentlySavedHour, recentlySavedMinute, recentlySavedDispenseCycle);

                /*sprintf(DayInfo, "Day---: %d", recentlySavedDay);
                LCDDisplayText(6, 0, DayInfo);
                sprintf(HourInfo, "Hour--: %0.2d", recentlySavedHour);
                LCDDisplayText(7, 0, HourInfo);
                sprintf(MinuteInfo, "Minute: %0.2d", recentlySavedMinute);
                LCDDisplayText(8, 0, MinuteInfo);
                sprintf(DispenseInfo, "Dispense: %0.2d", recentlySavedDispenseCycle);
                LCDDisplayText(9, 0, DispenseInfo);*/
            }
        }
        else if (PBHandlerInProgramMode() == 1)
        {
            if (init1 == 0) //Test to see if this is even necessary.
            {
                LCDDisplayText(5, 0, "Program Mode");
                LCD_SetTextColor(LCD_COLOR_RED);
                LCDDisplayText(6, 0, "Day---:");
                LCD_SetTextColor(LCD_COLOR_BLACK);
                LCDDisplayText(7, 0, "Hour--:");
                LCDDisplayText(8, 0, "Minute:");
                LCDDisplayText(9, 0, "Dispense:");
                init1++;
            }
        }
          
        if(PBHandlerInProgramMode() == 1)
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
            sprintf(DayInfo, "Day---: %d", day);
            sprintf(HourInfo, "Hour--: %0.2d", hour);
            sprintf(MinuteInfo, "Minute: %0.2d", minute);
            sprintf(DispenseInfo, "Dispense: %0.2d", dispense);
              
            if (PBHandlerCurrentlySelectedLine() == 0)
            {
                LCD_SetTextColor(LCD_COLOR_RED);
                LCDDisplayText(6, 0, DayInfo);
                LCD_SetTextColor(LCD_COLOR_BLACK);
                LCDDisplayText(7, 0, HourInfo); 
                LCDDisplayText(8, 0, MinuteInfo);
                LCDDisplayText(9, 0, DispenseInfo);
            }
            else if (PBHandlerCurrentlySelectedLine() == 1)
            {
                LCDDisplayText(6, 0, DayInfo);
                LCD_SetTextColor(LCD_COLOR_RED);
                LCDDisplayText(7, 0, HourInfo);
                LCD_SetTextColor(LCD_COLOR_BLACK);
                LCDDisplayText(8, 0, MinuteInfo);
                LCDDisplayText(9, 0, DispenseInfo);
            }
            else if (PBHandlerCurrentlySelectedLine() == 2)
            {
                LCDDisplayText(6, 0, DayInfo);
                LCDDisplayText(7, 0, HourInfo);
                LCD_SetTextColor(LCD_COLOR_RED);
                LCDDisplayText(8, 0, MinuteInfo);
                LCD_SetTextColor(LCD_COLOR_BLACK);
                LCDDisplayText(9, 0, DispenseInfo);
            }
            else if (PBHandlerCurrentlySelectedLine() == 3)
            {
                LCDDisplayText(6, 0, DayInfo);
                LCDDisplayText(7, 0, HourInfo);
                LCDDisplayText(8, 0, MinuteInfo);
                LCD_SetTextColor(LCD_COLOR_RED);
                LCDDisplayText(9, 0, DispenseInfo);
                LCD_SetTextColor(LCD_COLOR_BLACK);
            }
              
            if (PBHandlerUserWantsToSave() == 1)
            {
							SetScheduledAlarms(day, hour, minute, dispense);
							recentlySavedDay = day;
							recentlySavedHour = hour;
							recentlySavedMinute = minute;
							recentlySavedDispenseCycle = dispense;
							
							init2 = 1;
							/*
                if (dispense == 0)
                {   
                    saveDay = day;
                    saveHour = hour;
                    saveMinute = minute;
                    saveDispense = dispense;
                    init2 = 1;
                }
                if (dispense == 1)
                {   
                    saveDay2 = day;
                    saveHour2 = hour;
                    saveMinute2 = minute;
                    saveDispense2 = dispense;
                    init2 = 1;
                }*/
            }
        }

        if (RTCInterrupt != 0)
        {
            //RTCInterrupt = 0;
              
            //Activate alarms   
            if (RTCInterrupt == 1)
            {
                //LCDDisplayText(2, 0, "Alarm 1");
                //RTCSetAlarm(0, 0, 0, 10);
            }
            /*if (RTCInterrupt == 2)
            {
                LCDDisplayText(3, 0, "Alarm 2");
                RTCSetAlarm(0, 0, 0, 15);
            }
            if (RTCInterrupt == 3)
            {
                LCDDisplayText(4, 0, "Alarm 3");
            }*/
        }
          
				if (timerInterrupt != 0)
				{
					timerInterrupt = 0;
					secondDisplay++;
					currentTime.second++;

					if (currentTime.second >= 60)
					{
						minuteDisplay++;
						secondDisplay = 0;
						currentTime.second = 0;
						currentTime.minute++;

						if (currentTime.minute >= 60)
						{
							hourDisplay++;
							minuteDisplay = 0;
							currentTime.minute = 0;
							currentTime.hour++;

							if (currentTime.hour >= 24)
							{
								dayDisplay++;
								hourDisplay = 0;
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
				
				sprintf(test, "%d", dayDisplay);
        LCDDisplayText(0, 0, test);
        sprintf(test, "%0.2d:%0.2d:%0.2d", hourDisplay, minuteDisplay, secondDisplay);
        LCDDisplayText(1, 0, test);
				
				if (CheckAlarm(currentTime) == ALARM_EXISTS)
				/*Removed Feb25
        if (CheckAlarm(dayDisplay, hourDisplay, minuteDisplay, saveDay, saveHour, saveMinute, secondDisplay) == 1)
        {
            LCDDisplayText(3, 0, "ALARM: ACTIVATE!");
            ActivateAlarm();
        }
        if (CheckAlarm(dayDisplay, hourDisplay, minuteDisplay, saveDay2, saveHour2, saveMinute2, secondDisplay) == 1)
        {
            LCDDisplayText(3, 0, "ALARM: ACTIVATE!");
            ActivateAlarm();
        }*/
				
        if (secondDisplay == 5)
        {
            DeactivateAlarm();
            //tempSeconds = 999;
            LCDDisplayText(3, 0, "                    ");
        }
    }
}
