#include "AlarmHandler.h"

int savedScheduleDay[30] = {0};
int savedScheduleHour[30] = {0};
int savedScheduleMinute[30] = {0};	
//int savedScheduleDispenseCycle[30] = {0};

typedef struct structSchedule
{
	int savedScheduleDay;
	int savedScheduleHour;
	int savedScheduleMinute;	
} structSchedule;

structSchedule savedSchedule[30] = {0};



void SetScheduledAlarms(int day, int hour, int minute, int dispenseCycle)
{
	savedScheduleDay[dispenseCycle] = day;
	savedScheduleHour[dispenseCycle] = hour;
	savedScheduleMinute[dispenseCycle] = minute;
}

int CheckAlarm(structCurrentTime time, int size)
{
	int returnValue = 0; //ALARM_NOT_EXISTS
	for (int xx = 0; xx < size; xx++)
	{
		if (savedSchedule[xx].savedScheduleDay == time
	}
	return 0;
}
/*Commented Feb25
int CheckAlarm(int currDay, int currHour, int currMinute, int alarmDay, int alarmHour, int alarmMinute, int alarmSecond)
{
	
	if (alarmDay == currDay && alarmHour == currHour && alarmMinute == currMinute && alarmSecond == 0)
	{
		return 1;
	}
	
	return 0;
}
*/