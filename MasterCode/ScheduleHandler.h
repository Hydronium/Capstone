#ifndef ALARMHANDLER_H
#define ALARMHANDLER_H

#include "Types.h"
#include "MemoryHandler.h"
//Removed feb25
//int CheckAlarm(int currDay, int currHour, int currMinute, int alarmDay, int alarmHour, int alarmMinute, int alarmSecond);

void SaveSchedule(void);

void ReadStoredScheduleIntoMemory(int cycle);

void LookAtSpecificCycle(structSchedule * schedule, int cycle);

void ScheduleInit(void);

int CheckAlarm(structTime time);

void SetScheduledAlarms(int day, int hour, int minute, int dispenseCycle);

#endif
