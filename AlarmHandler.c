#include "AlarmHandler.h"

int CheckAlarm(int currDay, int currHour, int currMinute, int alarmDay, int alarmHour, int alarmMinute, int alarmSecond)
{
	if (alarmDay == currDay && alarmHour == currHour && alarmMinute == currMinute && alarmSecond == 0)
	{
		return 1;
	}
	
	return 0;
}
