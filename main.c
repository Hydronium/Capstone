//#include <LED.h>
#include <stdio.h>
#include <stm32f4xx.h>
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"

#define MESSAGE1   "     STM32F4xx      " 
#define MESSAGE2   " Device running on  " 
#define MESSAGE3   " stm32f4_discovery  " 

int main(void)
{
	volatile uint32_t dlycnt;
	
	for (dlycnt = 0; dlycnt < 10000000; dlycnt++);
  //for (dlycnt = 0; dlycnt < 1; dlycnt++);

  STM32f4_Discovery_LCD_Init();

  /* Display message on stm32f4_discovery LCD **********************************/
  /* Clear the LCD */ 
  LCD_Clear(LCD_COLOR_WHITE);

  /* Set the LCD Back Color */
  //LCD_SetBackColor(LCD_COLOR_BLUE);
	LCD_SetBackColor(LCD_COLOR_RED);
  /* Set the LCD Text Color */
  LCD_SetTextColor(LCD_COLOR_WHITE);
  LCD_DisplayStringLine(LINE(3), (uint8_t *)MESSAGE1);
  LCD_DisplayStringLine(LINE(4), (uint8_t *)MESSAGE2);
  LCD_DisplayStringLine(LINE(5), (uint8_t *)MESSAGE3);
  /* wait for a moment */
  for (dlycnt = 0; dlycnt < 50000000; dlycnt++);
	//for (dlycnt = 0; dlycnt < 5; dlycnt++);

  /* LCD RGB Test */
  LCD_RGB_Test();
  while (1);
	
	//LED_Initialize();

	//LED_On(0);
}
