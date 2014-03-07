#include "AlarmHandler.h"


int savedScheduleDay[DISPENSE_CYCLES] = {0};
int savedScheduleHour[DISPENSE_CYCLES] = {0};
int savedScheduleMinute[DISPENSE_CYCLES] = {0};	
//int savedScheduleDispenseCycle[30] = {0};



structSchedule savedSchedule[30] = {0};



void SetScheduledAlarms(int day, int hour, int minute, int dispenseCycle)
{
	savedScheduleDay[dispenseCycle] = day;
	savedScheduleHour[dispenseCycle] = hour;
	savedScheduleMinute[dispenseCycle] = minute;
}

int CheckAlarm(structTime time)
{
	int alarmValue = ALARM_NOT_EXISTS;
	int xx;
	for (xx = 0; xx <= DISPENSE_CYCLES; xx++)
	{
		if ( (savedSchedule[xx].savedScheduleDay == time.day) 		&&
				 (savedSchedule[xx].savedScheduleHour == time.hour) 	&&
				 (savedSchedule[xx].savedScheduleMinute == time.minute) )
			alarmValue = ALARM_EXISTS;
	}
	return alarmValue;
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
