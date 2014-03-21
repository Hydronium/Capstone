#ifndef MEMORY_HANDLER_H
#define MEMORY_HANDLER_H

#include "Types.h"
#include "stm32f4xx.h"

void MemoryInit(void);
int FlashReadSchedule(structSchedule savedSchedule[], int cycle);
int FlashWriteSchedule(structSchedule savedSchedule[]);

#endif
