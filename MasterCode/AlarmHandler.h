#ifndef ALARMHANDLER_H
#define ALARMHANDLER_H

#include "Types.h"
//Removed feb25
//int CheckAlarm(int currDay, int currHour, int currMinute, int alarmDay, int alarmHour, int alarmMinute, int alarmSecond);

void AlarmsInit(void);

int CheckAlarm(structTime time);

void SetScheduledAlarms(int day, int hour, int minute, int dispenseCycle);

#endif
