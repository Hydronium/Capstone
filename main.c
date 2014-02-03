//#include <LED.h>
#include <stdio.h>
#include <stm32f4xx.h>
#include "stm32f4_discovery.h"
#include "LCDHandler.h"
//#include "stm32f4_discovery_lcd.h"

#include "Initialization.h"

#define MESSAGE0	 "12345678901234567890"
#define MESSAGE1   "     STM32F4xx      " 
#define MESSAGE2   " Device running on  " 
#define MESSAGE3   " stm32f4_discovery  " 

int main(void)
{
	volatile uint32_t dlycnt;
	int zz;
	
	for (dlycnt = 0; dlycnt < 1000000; dlycnt++)
	;
	
  Initialization();

  /* Clear the LCD */ 
	LCDClear();

  /* Set the LCD Text Color */
	for (zz = 0; zz<9; zz++)
		LCDDisplayText(zz, zz+1, "blarg");

  /* wait for a moment */
  for (dlycnt = 0; dlycnt < 50000000; dlycnt++);
	LCDClear();
	
	//MEAT
  while (1)
	{}
}
