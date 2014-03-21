#ifndef TYPES_H
#define TYPES_H

#include "stm32f4xx.h"

#define DISPENSE_CYCLES 		28

#define ALARM_NOT_EXISTS 		0
#define ALARM_EXISTS				1

#define FLASH_SECTOR_TOTAL	12 //STM32F407VG has 12 memory sectors

typedef struct structTime_s
{
	int day;
	int hour;
	int minute;
	int second;
}structTime;

typedef struct structSchedule_s
{
	int savedScheduleDay;
	int savedScheduleHour;
	int savedScheduleMinute;	
}structSchedule;

typedef struct flashSectorProperties_s
{
	int sectorIndex;
	int sectorSize;
	uintptr_t sectorStartAddr; //uintptr_t is safely convertible to void and back
	uintptr_t sectorEndAddr;
}flashSectorProperties;

#endif
