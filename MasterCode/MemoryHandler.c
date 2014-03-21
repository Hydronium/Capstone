#include "MemoryHandler.h"

//This is the memory layout for the STM32F407VG.
const flashSectorProperties flashSectorLayout[FLASH_SECTOR_TOTAL] = 
{
	{ 0, 	16 * 1024, 	0x08000000, 0x08003FFF},
	{ 1, 	16 * 1024, 	0x08004000, 0x08007FFF},
	{ 2, 	16 * 1024, 	0x08008000, 0x0800BFFF},
	{ 3, 	16 * 1024, 	0x0800C000, 0x0800FFFF},
	{ 4, 	64 * 1024, 	0x08010000, 0x0801FFFF},
	{ 5, 	128 * 1024, 0x08020000, 0x0803FFFF},
	{ 6, 	128 * 1024, 0x08040000, 0x0805FFFF},
	{ 7, 	128 * 1024, 0x08060000, 0x0807FFFF},
	{ 8, 	128 * 1024, 0x08080000, 0x0809FFFF},
	{ 9, 	128 * 1024, 0x080A0000, 0x080BFFFF},
	{ 10, 128 * 1024, 0x080C0000, 0x080DFFFF},
	{ 11, 128 * 1024, 0x080E0000, 0x080FFFFF}
};

structSchedule (*bufferSchedules)[DISPENSE_CYCLES] = 0;

void MemoryInit(void)
{
	bufferSchedules = (void *)flashSectorLayout[11].sectorStartAddr; //7 -> sector 6 (void *)0x080E0000; //
}

int FlashReadSchedule(structSchedule savedSchedule[], int cycle)
{
	savedSchedule[cycle].savedScheduleDay = (*bufferSchedules)[cycle].savedScheduleDay;
	savedSchedule[cycle].savedScheduleHour = (*bufferSchedules)[cycle].savedScheduleHour;
	savedSchedule[cycle].savedScheduleMinute = (*bufferSchedules)[cycle].savedScheduleMinute;
	return 0;
}

int FlashWriteSchedule(structSchedule savedSchedule[])
{
	int zz = 0;
	
	FLASH_Unlock();
	
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	/* may not need to erase if we're overwriting the exact same size object
	if (FLASH_EraseSector(FLASH_Sector_6, VoltageRange_3) != FLASH_COMPLETE) //Clear it of old schedule
	{
		FLASH_Lock();
		return 0;
	}
	*/
	/*
	for (zz = 0; zz < DISPENSE_CYCLES; zz++)
	{
		FLASH_ProgramWord(flashSectorLayout[7].sectorStartAddr + zz*(4 * sizeof(int)), 											zz);
		FLASH_ProgramWord(flashSectorLayout[7].sectorStartAddr + zz*(4 * sizeof(int)) + sizeof(int), 				savedSchedule[zz].savedScheduleDay);
		FLASH_ProgramWord(flashSectorLayout[7].sectorStartAddr + zz*(4 * sizeof(int)) + (2 * sizeof(int)), 	savedSchedule[zz].savedScheduleMinute);
		FLASH_ProgramWord(flashSectorLayout[7].sectorStartAddr + zz*(4 * sizeof(int)) + (3 * sizeof(int)), 	savedSchedule[zz].savedScheduleHour);
	}*/
	for (zz = 0; zz < DISPENSE_CYCLES; zz++)
	{/*
		FLASH_ProgramWord(flashSectorLayout[11].sectorStartAddr + zz*(4 * sizeof(int)), 											0x11111111);
		FLASH_ProgramWord(flashSectorLayout[11].sectorStartAddr + zz*(4 * sizeof(int)) + sizeof(int), 				0x22222222);
		FLASH_ProgramWord(flashSectorLayout[11].sectorStartAddr + zz*(4 * sizeof(int)) + (2 * sizeof(int)), 	0x33333333);
		FLASH_ProgramWord(flashSectorLayout[11].sectorStartAddr + zz*(4 * sizeof(int)) + (3 * sizeof(int)),   0x44444444);
		*/
		FLASH_ProgramWord(flashSectorLayout[11].sectorStartAddr + zz*(3 * sizeof(int)), 											0x00000001);
		FLASH_ProgramWord(flashSectorLayout[11].sectorStartAddr + zz*(3 * sizeof(int)) + sizeof(int), 				0x00000003);
		FLASH_ProgramWord(flashSectorLayout[11].sectorStartAddr + zz*(3 * sizeof(int)) + (2 * sizeof(int)), 	0x00000007);
		//FLASH_ProgramWord(flashSectorLayout[11].sectorStartAddr + zz*(4 * sizeof(int)) + (3 * sizeof(int)), 	0x00000009);
		
	}
	FLASH_Lock();
	
	return 1;
}
