#include "RTCHandler.h"

void RTCInit(void)
{
	RTC_InitTypeDef  RTC_InitStructure;
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	
	RTC_AlarmTypeDef RTC_AlarmStructure;
	
	EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);
	
	/* Enable the LSI oscillator */ 
  RCC_LSICmd(ENABLE);
	
	/* Wait till LSI is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {}
	
	/* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	
	/* Enable the RTC Clock */
	RCC_RTCCLKCmd(ENABLE);

	/* Wait for RTC APB registers synchronisation */
	RTC_WaitForSynchro();
	
	/* Calendar Configuration with LSI supposed at 32KHz */
	RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
	RTC_InitStructure.RTC_SynchPrediv	=  0xFF; /* (32KHz / 128) - 1 = 0xFF*/
	RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
	RTC_Init(&RTC_InitStructure);
	
	/* Set the Time */
	RTC_TimeStructure.RTC_Hours   = 0x00;
	RTC_TimeStructure.RTC_Minutes = 0x00;
	RTC_TimeStructure.RTC_Seconds = 0x00;
	RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);
	
	//We need to read the date for some reason, so that when we write the year value it actually sticks.
	//Else the year value is garbage. This makes no sense, but that's what it is.
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
	
	/* Set the Date */
	RTC_DateStructure.RTC_WeekDay = 0x00;
	RTC_DateStructure.RTC_Date = 0x00;
	RTC_DateStructure.RTC_Month = 0x00;
	RTC_DateStructure.RTC_Year = 0x14;
	RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
	
	/* Set the alarm 05h:20min:30s */
  //RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_AM;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = 0x00;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0x00;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0x05;
  RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x00;
  RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
  RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
  
  /* Configure the RTC Alarm A register */
  RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);
  
  /* Enable RTC Alarm A Interrupt */
  RTC_ITConfig(RTC_IT_ALRA, ENABLE);
  
  /* Enable the alarm */
  RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
  
  RTC_ClearFlag(RTC_FLAG_ALRAF);
	
	//Configuring the EXTI/NVIC for the RTC alarm
	
	/* RTC Alarm A Interrupt Configuration */
  /* EXTI configuration *******************************************************/
  EXTI_ClearITPendingBit(EXTI_Line17); 
	
  EXTI_InitStructure.EXTI_Line = EXTI_Line17; //Line17 is directly connected to RTC internally
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable the RTC Alarm Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void RTCGetTime(RTC_TimeTypeDef * TimeStruct)
{
	RTC_GetTime(RTC_Format_BIN, TimeStruct);
}

void RTCGetDate(RTC_DateTypeDef * DateStruct)
{
	RTC_GetDate(RTC_Format_BIN, DateStruct);
}