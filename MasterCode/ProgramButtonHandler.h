#include "stm32f4_discovery.h"

void PBHandlerInit(void);
void PBHandlerPB1Pressed(void);
void PBHandlerPB2Pressed(void);
void PBHandlerPB3Pressed(void);
void PBHandlerPB4Pressed(void);
void PBHandlerPB5Pressed(void);
void PBHandlerPB6Pressed(void);
	
int PBHandlerInProgramMode(void);
int PBHandlerCurrentlySelectedLine(void);
int PBHandlerIncrementSelection(void);
int PBHandlerUserWantsToSave(void);
int PBHandlerUserWantsToReset(void);
int PBHandlerUserPressedDispenseButton(void);

void PBHandlerResetSelections(void);
