#include "TimerHandler.h"

void TimerInit(void)
{
	//uint16_t PrescalerValue;
	//TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	NVIC_InitTypeDef NVIC_InitStructure;

  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* Enable the TIM3 global Interrupt
   */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Enable TIM3 clock 
	
	/* 1s timer */
	TIM3->PSC = 35999; // Set prescaler to 35999 
	TIM3->ARR = 1999; // Set auto-reload to 1999 
	
	TIM3->CR1 &= ~TIM_CR1_OPM; // NOT One pulse mode 
	
	TIM3->EGR |= TIM_EGR_UG; // Force update 
	TIM3->SR &= ~TIM_SR_UIF; // Clear the update flag 
	TIM3->DIER |= TIM_DIER_UIE; // Enable interrupt on update event 
	NVIC_EnableIRQ(TIM3_IRQn); // Enable TIM3 IRQ 
	TIM3->CR1 |= TIM_CR1_CEN; // Enable TIM3 counter
	
	
	
	/* Debounce Timer */
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; // Enable TIM6 clock 
	
	/* 400 ms timer */
	TIM6->PSC = 35999; // Set prescaler value
	TIM6->ARR = 799; // Set auto-reload value 
	
	TIM6->CR1 |= TIM_CR1_OPM; // One pulse mode 
	
	TIM6->EGR |= TIM_EGR_UG; // Force update 
	TIM6->SR &= ~TIM_SR_UIF; // Clear the update flag 
	TIM6->DIER |= TIM_DIER_UIE; // Enable interrupt on update event 
	NVIC_EnableIRQ(TIM6_DAC_IRQn); // Enable TIM6 IRQ 
	
	//TIM6->CR1 |= TIM_CR1_CEN; // Enable TIM6 counter
	
	/* Stepper Motor Timer */
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN; //Enable TIM7 clock
	
	/* 1s timer */
	TIM7->PSC = 35999; // Set prescaler value
	TIM7->ARR = 1999; // Set auto-reload value
	
	TIM7->CR1 &= ~TIM_CR1_OPM; // NOT One pulse mode 

	TIM7->EGR |= TIM_EGR_UG; // Force update 
	TIM7->SR &= ~TIM_SR_UIF; // Clear the update flag 
	TIM7->DIER |= TIM_DIER_UIE; // Enable interrupt on update event 
	NVIC_EnableIRQ(TIM7_IRQn); // Enable TIM7 IRQ 
	
	//Timer will be enabled when the stepper motor needs to move.
}

void StartDebounceTimer(void)
{
	TIM6->CR1 |= TIM_CR1_CEN; // Enable TIM6 counter
}

void StartCartridgeTimer(void)
{
	TIM7->CR1 |= TIM_CR1_CEN;
}

void StopCartridgeTimer(void)
{
	TIM7->CR1 &= ~TIM_CR1_CEN;
}

void ResetCartridgeTimer(void)
{
	TIM7->CNT = 0;
}
