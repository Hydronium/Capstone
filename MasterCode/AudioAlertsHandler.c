#include "AudioAlertsHandler.h"
#include "stm32f4xx.h"

void AudioAlertsInit(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOB clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	// Configure PB1 pin as input floating
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void ActivateAudioAlert(void)
{
	GPIOB->BSRRL = GPIO_Pin_1;
}

void DeactivateAudioAlert(void)
{
	GPIOB->BSRRH = GPIO_Pin_1;
}
