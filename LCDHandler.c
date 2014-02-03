#include "LCDHandler.h"
#include "stm32f4_discovery_lcd.h"

void LCDInit(void)
{
	STM32f4_Discovery_LCD_Init();
	LCD_SetBackColor(LCD_COLOR_WHITE);
	LCD_SetTextColor(LCD_COLOR_BLACK);
}

void LCDClear(void)
{
	LCD_Clear(LCD_COLOR_WHITE);
}

//20 columns by 10 lines
void LCDDisplayText(int X, int Y, char * message)
{
	LCD_DisplayStringLineColumn(LINE(X), Y, (uint8_t *)message);
}
