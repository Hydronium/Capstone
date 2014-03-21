#include "ScheduleHandler.h"

/*
int savedScheduleDay[DISPENSE_CYCLES] = {999};
int savedScheduleHour[DISPENSE_CYCLES] = {999};
int savedScheduleMinute[DISPENSE_CYCLES] = {999};	*/
//int savedScheduleDispenseCycle[30] = {0};

structSchedule savedSchedule[DISPENSE_CYCLES] = {0};

void SaveSchedule(void)
{
	FlashWriteSchedule(savedSchedule);
}

void ReadStoredScheduleIntoMemory(int cycle)
{
	FlashReadSchedule(savedSchedule, cycle);
}

void LookAtSpecificCycle(structSchedule * schedule, int cycle)
{
	schedule->savedScheduleDay = savedSchedule[cycle].savedScheduleDay;
	schedule->savedScheduleHour = savedSchedule[cycle].savedScheduleHour;
	schedule->savedScheduleMinute = savedSchedule[cycle].savedScheduleMinute;
}

void ScheduleInit(void)
{
	int xx;
	for (xx = 0; xx <= DISPENSE_CYCLES; xx++)
	{
		savedSchedule[xx].savedScheduleDay = 99;
		savedSchedule[xx].savedScheduleHour = 99;
		savedSchedule[xx].savedScheduleMinute = 99;
	}
}

void SetScheduledAlarms(int day, int hour, int minute, int dispenseCycle)
{
	savedSchedule[dispenseCycle].savedScheduleDay = day;
	savedSchedule[dispenseCycle].savedScheduleHour = hour;
	savedSchedule[dispenseCycle].savedScheduleMinute = minute;
}

int CheckAlarm(structTime time)
{
	int xx;
	int alarmValue = ALARM_NOT_EXISTS;
	
	for (xx = 0; xx <= DISPENSE_CYCLES; xx++)
	{
		if ( (savedSchedule[xx].savedScheduleDay == time.day) 			&&
				 (savedSchedule[xx].savedScheduleHour == time.hour) 		&&
				 (savedSchedule[xx].savedScheduleMinute == time.minute)	&&
				 (time.second < 5))
		{
			alarmValue = ALARM_EXISTS;
		}
	}
	return alarmValue;
}
