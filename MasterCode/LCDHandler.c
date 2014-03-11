#include "LCDHandler.h"
#include "stm32f4_discovery_lcd.h"
#include "stdio.h"

void LCDInit(void)
{
	STM32f4_Discovery_LCD_Init();
	LCD_SetBackColor(BACKGROUND_COLOUR);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCDClear();
}

void LCDClear(void)
{
	LCD_Clear(BACKGROUND_COLOUR);
}

//20 columns by 10 lines
void LCDDisplayText(int X, int Y, char * message)
{
	LCD_DisplayStringLineColumn(LINE(X), Y, (uint8_t *)message);
}

void LCDDisplayCurrentAlarmTime(int day, int hour, int minute, int dispenseCycle, int selectedLine)
{
	char DayInfo[20];
	char HourInfo[20];
	char MinuteInfo[20];
	char DispenseInfo[20];
	
	LCD_SetTextColor(LCD_COLOR_BLACK);
	
	switch(day)
	{
		case 0: sprintf(DayInfo, "     Day: Mon"); break;
		case 1: sprintf(DayInfo, "     Day: Tue"); break;
		case 2: sprintf(DayInfo, "     Day: Wed"); break;
		case 3: sprintf(DayInfo, "     Day: Thu"); break;
		case 4: sprintf(DayInfo, "     Day: Fri"); break;
		case 5: sprintf(DayInfo, "     Day: Sat"); break;
		case 6: sprintf(DayInfo, "     Day: Sun"); break;
		default: sprintf(DayInfo, "     Day: Sun"); break;
	}
	sprintf(HourInfo, "    Hour: %0.2d", hour);
	sprintf(MinuteInfo, "  Minute: %0.2d", minute);
	sprintf(DispenseInfo, "Dispense: %0.2d", dispenseCycle);
	
	if (selectedLine == 0)
	{
		LCD_SetTextColor(LCD_COLOR_RED);
	}
	LCDDisplayText(6, 0, DayInfo);
	if (selectedLine == 0)
	{
		LCD_SetTextColor(LCD_COLOR_BLACK);
	}
	
	if (selectedLine == 1)
	{
		LCD_SetTextColor(LCD_COLOR_RED);
	}
	LCDDisplayText(7, 0, HourInfo);
	if (selectedLine == 1)
	{
		LCD_SetTextColor(LCD_COLOR_BLACK);
	}
	
	if (selectedLine == 2)
	{
		LCD_SetTextColor(LCD_COLOR_RED);
	}
	LCDDisplayText(8, 0, MinuteInfo);
	if (selectedLine == 2)
	{
		LCD_SetTextColor(LCD_COLOR_BLACK);
	}
	
	if (selectedLine == 3)
	{
		LCD_SetTextColor(LCD_COLOR_RED);
	}
	LCDDisplayText(9, 0, DispenseInfo);
	if (selectedLine == 3)
	{
		LCD_SetTextColor(LCD_COLOR_BLACK);
	}
}
