//#include <LED.h>
#include "stdio.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "LCDHandler.h"
//#include "stm32f4_discovery_lcd.h"
#include "Initialization.h"
#include "RTCHandler.h"
#include "stm32f4xx_it.h"
#include "LCDHandler.h"
#include "stm32f4_discovery_lcd.h"

char RTCInterrupt = 0;
char TimerInterrupt = 0; 
/*
int BI1 = 0;
int BI2 = 0;
int BI3 = 0;
int BI4 = 0;
*/
int ProgramMode = 0;
int b2 = 0;
int b3 = 0;
int b4 = 0;
int init1 = 0;

int day = 0;
int hour = 0;
int minute = 0;

int SaveDay = 0;
int SaveHour = 0;
int SaveMinute = 0;


void PB_Config(void);

EXTI_InitTypeDef   EXTI_InitStructure;

int main(void)
{
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	volatile uint32_t dlycnt;
	//int zz;
	int seconds = 0;
	
	//int datetestincrementer = 0;
	//int datetestincrementer2 = 0;
	char test[10];
	
	char time[20];
	char date[20];
	char DayInfo[20];
	char HourInfo[20];
	char MinuteInfo[20];
	
  Initialization();
	PB_Config();
  /* Clear the LCD */ 
	//LCDClear();

  /* Set the LCD Text Color */
	//for (zz = 0; zz<9; zz++)
	//	LCDDisplayText(zz, zz+1, "blarg");

  /* wait for a moment */
  //for (dlycnt = 0; dlycnt < 5000000; dlycnt++);
	
	//MEAT
	LCDDisplayText(5, 0, "Running Mode");
	
  while (1)
	{
		
		if (ProgramMode == 0)
		{	
			if (init1 != 0) 
			{
				LCDClear();
				b2 = 0;
				b3 = 0;
				b4 = 0;
				init1 = 0;
				LCDDisplayText(5, 0, "Running Mode");
				sprintf(DayInfo, "Day---: %d", SaveDay);
				LCDDisplayText(6, 0, DayInfo);
				sprintf(HourInfo, "Hour--: %d", SaveHour);
				LCDDisplayText(7, 0, HourInfo);
				sprintf(MinuteInfo, "Minute: %d", SaveMinute);
				LCDDisplayText(8, 0, MinuteInfo);
			}
		}
		else if (ProgramMode == 1)
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
		
		if(ProgramMode == 1)
		{
			if (b2 == 0)
			{
					LCDDisplayText(5, 0, "Program Mode");
					sprintf(DayInfo, "Day---: %d", day);
					LCD_SetTextColor(LCD_COLOR_RED);
					LCDDisplayText(6, 0, DayInfo);
					LCD_SetTextColor(LCD_COLOR_BLACK);
					sprintf(HourInfo, "Hour--: %d", hour);
					LCDDisplayText(7, 0, HourInfo);
					sprintf(MinuteInfo, "Minute: %d", minute);
					LCDDisplayText(8, 0, MinuteInfo);
			}
			else if (b2 == 1)
			{
					LCDDisplayText(5, 0, "Program Mode");
					sprintf(DayInfo, "Day---: %d", day);
					LCDDisplayText(6, 0, DayInfo);
					sprintf(HourInfo, "Hour--: %d", hour);
					LCD_SetTextColor(LCD_COLOR_RED);
					LCDDisplayText(7, 0, HourInfo);
					LCD_SetTextColor(LCD_COLOR_BLACK);
					sprintf(MinuteInfo, "Minute: %d", minute);
					LCDDisplayText(8, 0, MinuteInfo);
			}
			else if (b2 == 2)
			{
					LCDDisplayText(5, 0, "Program Mode");
					sprintf(DayInfo, "Day---: %d", day);
					LCDDisplayText(6, 0, DayInfo);
					sprintf(HourInfo, "Hour--: %d", hour);
					LCDDisplayText(7, 0, HourInfo);
					sprintf(MinuteInfo, "Minute: %d", minute);
					LCD_SetTextColor(LCD_COLOR_RED);
					LCDDisplayText(8, 0, MinuteInfo);
					LCD_SetTextColor(LCD_COLOR_BLACK);
			}
			
			if (b3 >= 1)
			{
				if (b2 == 0)
				{
					day++;
					
					if (day == 7)
					{
						day = 0;
					}
					LCDDisplayText(5, 0, "Program Mode");
					sprintf(DayInfo, "Day---: %d", day);
					LCD_SetTextColor(LCD_COLOR_RED);
					LCDDisplayText(6, 0, DayInfo);
					LCD_SetTextColor(LCD_COLOR_BLACK);
					sprintf(HourInfo, "Hour--: %d", hour);
					LCDDisplayText(7, 0, HourInfo);
					sprintf(MinuteInfo, "Minute: %d", minute);
					LCDDisplayText(8, 0, MinuteInfo);
				}
				else if (b2 == 1)
				{
					hour++;
					
					if (hour == 24)
					{
						hour = 0;
					}
					LCDDisplayText(5, 0, "Program Mode");
					sprintf(DayInfo, "Day---: %d", day);
					LCDDisplayText(6, 0, DayInfo);
					sprintf(HourInfo, "Hour--: %d", hour);
					LCD_SetTextColor(LCD_COLOR_RED);
					LCDDisplayText(7, 0, HourInfo);
					LCD_SetTextColor(LCD_COLOR_BLACK);
					sprintf(MinuteInfo, "Minute: %d", minute);
					LCDDisplayText(8, 0, MinuteInfo);
				}
				else if (b2 == 2)
				{
					minute = minute + 30;
					
					if (minute >= 40)
					{
						minute = 0;
					}
					LCDDisplayText(5, 0, "Program Mode");
					sprintf(DayInfo, "Day---: %d", day);
					LCDDisplayText(6, 0, DayInfo);
					sprintf(HourInfo, "Hour--: %d", hour);
					LCDDisplayText(7, 0, HourInfo);
					sprintf(MinuteInfo, "Minute: %d", minute);
					LCD_SetTextColor(LCD_COLOR_RED);
					LCDDisplayText(8, 0, MinuteInfo);
					LCD_SetTextColor(LCD_COLOR_BLACK);
				}
				
				b3 = 0;
			}
			
			if (b4 >= 1)
			{
				SaveDay = day;
				SaveHour = hour;
				SaveMinute = minute;
				b4 = 0;
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
			if (RTCInterrupt == 2)
			{
				LCDDisplayText(3, 0, "Alarm 2");
				RTCSetAlarm(0, 0, 0, 15);
			}
			if (RTCInterrupt == 3)
			{
				LCDDisplayText(4, 0, "Alarm 3");
			}
		}
		
		if (TimerInterrupt != 0)
		{
			TimerInterrupt = 0;
			sprintf(test, "%d", seconds);
			LCDDisplayText(3, 0, test);
			seconds++;
		}
	}
}

void PB_Config(void)
	{
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;

  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	// ----------------------------- "Button 1", Pin B1 ---------------------------------------------------- //
	/*Pushbutton 1*/
  /* Configure PA1 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Connect EXTI Line1 to PA3 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);

  /* Configure EXTI Line3 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI Line1 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
		
  // ----------------------------- "Button 2", Pin D2 ---------------------------------------------------- //
	/* Configure Pd5 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Connect EXTI Line0 to PA0 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2);

  /* Configure EXTI Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI Line5 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	// ----------------------------- "Button 3", Pin A3 ---------------------------------------------------- //
	/*Pushbutton 1*/
  /* Configure PA1 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect EXTI Line1 to PA3 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3);

  /* Configure EXTI Line3 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI Line1 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	// ----------------------------- "Button 4", Pin B4 ---------------------------------------------------- //
	/*Pushbutton 1*/
  /* Configure PA1 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Connect EXTI Line1 to PA3 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource4);

  /* Configure EXTI Line3 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI Line1 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
        
        //Push Button 3
                /* Configure PA2 pin as input floating */
  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  //GPIO_Init( GPIOA, &GPIO_InitStructure );

  /* Connect EXTI Line3 to PA3 pin */
  //SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOA, EXTI_PinSource3 );

  /* Configure EXTI Line3 */
  //EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  //      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  //EXTI_Init( &EXTI_InitStructure );

  /* Enable and set EXTI Line3 Interrupt to the lowest priority */
  //NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  //NVIC_Init( &NVIC_InitStructure );
        
        //Push Button 4
                        /* Configure PA4 pin as input floating */
  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
 // GPIO_Init( GPIOA, &GPIO_InitStructure );

  /* Connect EXTI Line4 to PA4 pin */
 // SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOA, EXTI_PinSource4);

  /* Configure EXTI Line4 */
 // EXTI_InitStructure.EXTI_Line = EXTI_Line4;
 //       EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  //EXTI_Init( &EXTI_InitStructure );

  /* Enable and set EXTI Line4 Interrupt to the lowest priority */
  //NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  //NVIC_Init( &NVIC_InitStructure );
}
