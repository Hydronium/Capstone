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

char RTCInterrupt = 0;
char TimerInterrupt = 0; 

int init1 = 0;

int day = 0;
int hour = 0;
int minute = 0;

int SaveDay = 0;
int SaveHour = 0;
int SaveMinute = 0;

int main(void)
{
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	
	int seconds = 0;

	char test[10];
	
	char time[20];
	char date[20];
	char DayInfo[20];
	char HourInfo[20];
	char MinuteInfo[20];
	
  Initialization();
	
	//MEAT
	LCDDisplayText(5, 0, "Running Mode");
	sprintf(test, "%d", seconds);
	LCDDisplayText(3, 0, test);
	
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
			
			LCDDisplayText(5, 0, "Running Mode");
			sprintf(DayInfo, "Day---: %d", SaveDay);
			LCDDisplayText(6, 0, DayInfo);
			sprintf(HourInfo, "Hour--: %0.2d", SaveHour);
			LCDDisplayText(7, 0, HourInfo);
			sprintf(MinuteInfo, "Minute: %0.2d", SaveMinute);
			LCDDisplayText(8, 0, MinuteInfo);
		}
		else if (PBHandlerInProgramMode() == 1)
		{
			if (init1 == 0)
			{
				LCDDisplayText(5, 0, "Program Mode");
				LCD_SetTextColor(LCD_COLOR_RED);
				LCDDisplayText(6, 0, "Day---:");
				LCD_SetTextColor(LCD_COLOR_BLACK);
				LCDDisplayText(7, 0, "Hour--:");
				LCDDisplayText(8, 0, "Minute:");
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
					//LCDDisplayText(5, 0, "Program Mode");
					//sprintf(DayInfo, "Day---: %d", day);
					//LCD_SetTextColor(LCD_COLOR_RED);
					//LCDDisplayText(6, 0, DayInfo);
					//LCD_SetTextColor(LCD_COLOR_BLACK);
					//sprintf(HourInfo, "Hour--: %0.2d", hour);
					//LCDDisplayText(7, 0, HourInfo);
					//sprintf(MinuteInfo, "Minute: %0.2d", minute);
					//LCDDisplayText(8, 0, MinuteInfo);
				}
				else if (PBHandlerCurrentlySelectedLine() == 1)
				{
					hour++;
					
					if (hour == 24)
					{
						hour = 0;
					}
					/*LCDDisplayText(5, 0, "Program Mode");
					sprintf(DayInfo, "Day---: %d", day);
					LCDDisplayText(6, 0, DayInfo);
					sprintf(HourInfo, "Hour--: %0.2d", hour);
					LCD_SetTextColor(LCD_COLOR_RED);
					LCDDisplayText(7, 0, HourInfo);
					LCD_SetTextColor(LCD_COLOR_BLACK);
					sprintf(MinuteInfo, "Minute: %0.2d", minute);
					LCDDisplayText(8, 0, MinuteInfo);*/
				}
				else if (PBHandlerCurrentlySelectedLine() == 2)
				{
					minute = minute + 30;
					
					if (minute >= 40)
					{
						minute = 0;
					}
					
					/*LCDDisplayText(5, 0, "Program Mode");
					sprintf(DayInfo, "Day---: %d", day);
					LCDDisplayText(6, 0, DayInfo);
					sprintf(HourInfo, "Hour--: %0.2d", hour);
					LCDDisplayText(7, 0, HourInfo);
					sprintf(MinuteInfo, "Minute: %0.2d", minute);
					LCD_SetTextColor(LCD_COLOR_RED);
					LCDDisplayText(8, 0, MinuteInfo);
					LCD_SetTextColor(LCD_COLOR_BLACK);*/
				}

			}
			
			LCDDisplayText(5, 0, "Program Mode");
			sprintf(DayInfo, "Day---: %d", day);
			sprintf(HourInfo, "Hour--: %0.2d", hour);
			sprintf(MinuteInfo, "Minute: %0.2d", minute);
			
			if (PBHandlerCurrentlySelectedLine() == 0)
			{
					LCD_SetTextColor(LCD_COLOR_RED);
					LCDDisplayText(6, 0, DayInfo);
					LCD_SetTextColor(LCD_COLOR_BLACK);
					
					LCDDisplayText(7, 0, HourInfo);
					
					LCDDisplayText(8, 0, MinuteInfo);
			}
			else if (PBHandlerCurrentlySelectedLine() == 1)
			{
					LCDDisplayText(6, 0, DayInfo);

					LCD_SetTextColor(LCD_COLOR_RED);
					LCDDisplayText(7, 0, HourInfo);
					LCD_SetTextColor(LCD_COLOR_BLACK);

					LCDDisplayText(8, 0, MinuteInfo);
			}
			else if (PBHandlerCurrentlySelectedLine() == 2)
			{
					LCDDisplayText(6, 0, DayInfo);

					LCDDisplayText(7, 0, HourInfo);

					LCD_SetTextColor(LCD_COLOR_RED);
					LCDDisplayText(8, 0, MinuteInfo);
					LCD_SetTextColor(LCD_COLOR_BLACK);
			}
			
			
			
			if (PBHandlerUserWantsToSave() == 1)
			{
				SaveDay = day;
				SaveHour = hour;
				SaveMinute = minute;
			}
		}
		
		RTCGetTime(&RTC_TimeStructure);
		RTCGetDate(&RTC_DateStructure);
		sprintf(date, "D:%d %0.2d M:%0.2d Y:20%0.2d", (int)RTC_DateStructure.RTC_WeekDay, (int)RTC_DateStructure.RTC_Date, (int)RTC_DateStructure.RTC_Month, (int)RTC_DateStructure.RTC_Year);
		sprintf(time, "%0.2d:%0.2d:%0.2d", (int)RTC_TimeStructure.RTC_Hours, (int)RTC_TimeStructure.RTC_Minutes, (int)RTC_TimeStructure.RTC_Seconds);
		LCDDisplayText(0, 0, date);
		LCDDisplayText(1, 0, time);
		
		if (RTCInterrupt != 0)
		{
			//RTCInterrupt = 0;
			
			//Activate alarms	
			if (RTCInterrupt == 1)
			{
				LCDDisplayText(2, 0, "Alarm 1");
				RTCSetAlarm(0, 0, 0, 10);
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
		
		if (TimerInterrupt != 0)
		{
			TimerInterrupt = 0;
			seconds++;
			sprintf(test, "%d", seconds);
			LCDDisplayText(3, 0, test);
			
		}
	}
}

