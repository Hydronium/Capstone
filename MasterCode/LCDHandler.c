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

void LCDDisplayCurrentAlarmTime(int day, int hour, int minute, int dispenseCycle)
{
	char DayInfo[20];
	char HourInfo[20];
	char MinuteInfo[20];
	char DispenseInfo[20];
	
	switch(day)
	{
		case 0: sprintf(DayInfo, "     Day: Mon");
		case 1: sprintf(DayInfo, "     Day: Tue");
		case 2: sprintf(DayInfo, "     Day: Wed");
		case 3: sprintf(DayInfo, "     Day: Thu");
		case 4: sprintf(DayInfo, "     Day: Fri");
		case 5: sprintf(DayInfo, "     Day: Sat");
		case 6: sprintf(DayInfo, "     Day: Sun");
	}
	
	LCDDisplayText(6, 0, DayInfo);
	
	sprintf(HourInfo, "    Hour: %0.2d", hour);
	LCDDisplayText(7, 0, HourInfo);
	
	sprintf(MinuteInfo, "  Minute: %0.2d", minute);
	LCDDisplayText(8, 0, MinuteInfo);
	
	sprintf(DispenseInfo, "Dispense: %0.2d", dispenseCycle);
	LCDDisplayText(9, 0, DispenseInfo);
}
