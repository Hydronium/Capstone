#ifndef TYPES_H
#define TYPES_H

#define DISPENSE_CYCLES 	28

#define ALARM_NOT_EXISTS 	0
#define ALARM_EXISTS			1

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



#endif
