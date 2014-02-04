//#include <LED.h>
#include <stdio.h>
#include <stm32f4xx.h>
#include "stm32f4_discovery.h"


#include "LCDHandler.h"
//#include "stm32f4_discovery_lcd.h"

#include "Initialization.h"
#include "RTCHandler.h"

char RTCInterrupt = 0;

int main(void)
{
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	volatile uint32_t dlycnt;
	//int zz;
	
	char time[20];
	char date[20];
	
	for (dlycnt = 0; dlycnt < 1000000; dlycnt++)
	;
	
  Initialization();

  /* Clear the LCD */ 
	LCDClear();

  /* Set the LCD Text Color */
	//for (zz = 0; zz<9; zz++)
	//	LCDDisplayText(zz, zz+1, "blarg");

  /* wait for a moment */
  for (dlycnt = 0; dlycnt < 5000000; dlycnt++);
	
	//MEAT
  while (1)
	{
		RTCGetTime(&RTC_TimeStructure);
		RTCGetDate(&RTC_DateStructure);
		sprintf(date, "D:%d %0.2d M:%0.2d Y:20%0.2d", (int)RTC_DateStructure.RTC_WeekDay, (int)RTC_DateStructure.RTC_Date, (int)RTC_DateStructure.RTC_Month, (int)RTC_DateStructure.RTC_Year);
		sprintf(time, "%0.2d:%0.2d:%0.2d", (int)RTC_TimeStructure.RTC_Hours, (int)RTC_TimeStructure.RTC_Minutes, (int)RTC_TimeStructure.RTC_Seconds);
		LCDDisplayText(0, 0, date);
		LCDDisplayText(1, 0, time);
		
		if (RTCInterrupt != 0)
		{
			RTCInterrupt = 0;
			//Activate alarms
			LCDDisplayText(2, 0, "Alarm went off");
		}
	}
}
