#include "StepperMotorHandler.h"
#include "TimerHandler.h"

int movements = 0;
int timing = 0;
int change = 0;

void StepperMotorInit(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOC clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	
	// Configure PC6 pin as output
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	// Configure PC7 pin as output
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	// Configure PB6 pin as output
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// Configure PB7 pin as output
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void MoveOneSection(void)
{
	StartCartridgeTimer();
}

void MoveOneStep(void)
{
	timing = movements % 4;
	if ( timing == 0 )
	{
		//A + B
		GPIOC->BSRRL = GPIO_Pin_6; //On
		GPIOC->BSRRH = GPIO_Pin_7; //Off
		
		GPIOB->BSRRL = GPIO_Pin_6; //On
		GPIOB->BSRRH = GPIO_Pin_7; //Off
	}
	else if( timing - 1 == 0 )
	{
		//B + A'
		GPIOC->BSRRH = GPIO_Pin_6; //Off
		GPIOC->BSRRL = GPIO_Pin_7; //On
		
		GPIOB->BSRRL = GPIO_Pin_6; //On
		GPIOB->BSRRH = GPIO_Pin_7; //Off
	}
	else if( timing - 2 == 0 )
	{
		//A' + B'
		GPIOC->BSRRH = GPIO_Pin_6; //Off
		GPIOC->BSRRL = GPIO_Pin_7; //On
		
		GPIOB->BSRRH = GPIO_Pin_6; //Off
		GPIOB->BSRRL = GPIO_Pin_7; //On
	}
	else if( timing - 3 == 0 )
	{
		//B' + A
		GPIOC->BSRRL = GPIO_Pin_6; //On
		GPIOC->BSRRH = GPIO_Pin_7; //Off
		
		GPIOB->BSRRH = GPIO_Pin_6; //Off
		GPIOB->BSRRL = GPIO_Pin_7; //On
	}
	movements++;
	
	if (movements >= 7 + change)
	{
		movements = (timing + 1)%4;
		change = movements;
		StopCartridgeTimer();
		ResetCartridgeTimer();
	}
}
