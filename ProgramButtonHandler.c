#include "ProgramButtonHandler.h"

uint8_t ProgramMode = 0, LineSelection = 0, IncrementValue = 0, SaveSettings = 0;
int thing2 = 0;
void PBHandlerInit(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;

  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;

  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	// ----------------------------- "Button 1", Pin A15 ---------------------------------------------------- //
	
  // Configure PA1 pin as input floating
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // Connect EXTI Line1 to PA15 pin
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource15);

  // Configure EXTI Line3
  EXTI_InitStructure.EXTI_Line = EXTI_Line15;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  // Enable and set EXTI Line1 Interrupt to the lowest priority
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	// ----------------------------- "Button 2", Pin A5 ---------------------------------------------------- //
  // Configure PA1 pin as input floating 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // Connect EXTI Line1 to PA3 pin 
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource5);

  // Configure EXTI Line3
  EXTI_InitStructure.EXTI_Line = EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  // Enable and set EXTI Line1 Interrupt to the lowest priority 
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
  // ----------------------------- "Button 3", Pin A8 ---------------------------------------------------- //
	// Configure PC2 pin as input 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // Connect EXTI Line2 to PC2 pin 
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource8);

  // Configure EXTI Line2 
  EXTI_InitStructure.EXTI_Line = EXTI_Line8;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  // Enable and set EXTI Line2 Interrupt to the lowest priority 
  /*NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);*/
	
	// ----------------------------- "Button 4", Pin A10 ---------------------------------------------------- //
	
  // Configure PA1 pin as input with internal pullup resistor
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

    //Connect EXTI Line1 to PA3 pin
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource10);

    //Configure EXTI Line3
  EXTI_InitStructure.EXTI_Line = EXTI_Line10;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  //Enable and set EXTI Line1 Interrupt to the lowest priority 
  /*NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);*/
}

void PBHandlerPB1Pressed(void)
{
	thing2++;
	if (ProgramMode == 0)
	{
		ProgramMode = 1;
	}
	else if (ProgramMode == 1)
	{
		ProgramMode = 0;
	}
}

void PBHandlerPB2Pressed(void)
{
	if (ProgramMode == 1)
	{
		LineSelection++;
			
		if (LineSelection > 3)
		{
			LineSelection = 0; //0 -> Day, 1 -> Hour, 2 -> Minute, 3 -> Dispense
		}
	}
}
		
void PBHandlerPB3Pressed(void)
{
	if (ProgramMode == 1 && IncrementValue == 0)
	{
		IncrementValue = 1;
	}
}

void PBHandlerPB4Pressed(void)
{
	if (ProgramMode == 1 && SaveSettings == 0)
	{
		SaveSettings = 1;
	}
}

int PBHandlerInProgramMode(void)
{
	return ProgramMode;
}

int PBHandlerCurrentlySelectedLine(void)
{
	return LineSelection;
}

int PBHandlerIncrementSelection(void)
{
	if (IncrementValue > 0)
	{
		IncrementValue = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

int PBHandlerUserWantsToSave(void)
{
	if (SaveSettings > 0)
	{
		SaveSettings = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

void PBHandlerResetSelections(void)
{
	LineSelection = 0;
	IncrementValue = 0;
	ProgramMode = 0;
}
