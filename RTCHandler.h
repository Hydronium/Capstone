#include "stm32f4_discovery.h"

void RTCInit(void);
void RTCGetTime(RTC_TimeTypeDef * TimeStruct);
void RTCGetDate(RTC_DateTypeDef * DateStruct);

void RTCSetAlarm(uint8_t date, uint8_t hours, uint8_t minutes, uint8_t seconds);
