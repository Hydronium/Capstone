#include "VisualAlertsHandler.h"
#include "stm32f4xx.h"

void VisualAlertsInit(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	// Configure PA1 pin as input floating
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void ActivateAlarm(void)
{
	GPIOC->BSRRL = GPIO_Pin_2;
}

void DeactivateAlarm(void)
{
	GPIOC->BSRRH = GPIO_Pin_2;
}
