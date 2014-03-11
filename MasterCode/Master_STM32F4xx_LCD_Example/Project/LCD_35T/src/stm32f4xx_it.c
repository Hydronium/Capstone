/**
  ******************************************************************************
  * @file    LCD_35T/src/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; Portions COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "LCDHandler.h"
#include "TimerHandler.h"
#include "ProgramButtonHandler.h"
#include "StepperMotorHandler.h"
  
	int thing = 0;
/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */
  
/** @addtogroup USART_Printf
  * @{
  */ 
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
  
/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/
  
/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}
  
/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
  
/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}
  
/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
  
/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
  
/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}
  
/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}
  
/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}
  
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}
  
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/
  
/*void RTC_Alarm_IRQHandler(void)
{
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET)
  {
        RTCInterrupt++;
    RTC_ClearITPendingBit(RTC_IT_ALRA);
    EXTI_ClearITPendingBit(EXTI_Line17);
  } 
}*/
  
void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
  
    timerInterrupt = 1;
  }
}
  
void TIM6_DAC_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
		
	//EXTI_ClearITPendingBit(EXTI_Line0);
	//EXTI_ClearITPendingBit(EXTI_Line1);
	//EXTI_ClearITPendingBit(EXTI_Line2);
	//EXTI_ClearITPendingBit(EXTI_Line3);
	//EXTI_ClearITPendingBit(EXTI_Line4);
	
	//EXTI_ClearITPendingBit(EXTI_Line3);
	EXTI_ClearITPendingBit(EXTI_Line5);
	EXTI_ClearITPendingBit(EXTI_Line8);
	EXTI_ClearITPendingBit(EXTI_Line10);
	EXTI_ClearITPendingBit(EXTI_Line14);
	EXTI_ClearITPendingBit(EXTI_Line15);
	
	//NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void TIM7_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
  
    MoveOneStep();
  }
}  
//PA5 and PA8
void EXTI9_5_IRQHandler(void)
{
	NVIC_DisableIRQ(EXTI9_5_IRQn); // Disable interrupt
	__DSB();
	__ISB(); 
	StartDebounceTimer();
	if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)) == 0)
	{
		
		//StartDebounceTimer();
		PBHandlerPB2Pressed();
		//EXTI_ClearITPendingBit(EXTI_Line5);
	}
		
	if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)) == 0)
	{
    
		//StartDebounceTimer();
		PBHandlerPB3Pressed();
		//EXTI_ClearITPendingBit(EXTI_Line8);
	}
	NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
	//NVIC_EnableIRQ(EXTI9_5_IRQn);
}
  
//PA10
void EXTI15_10_IRQHandler(void)
{
thing++;
	NVIC_DisableIRQ(EXTI15_10_IRQn); // Disable interrupt
	__DSB();
	__ISB();
	StartDebounceTimer();
	if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10)) == 0)
	{
    
		//StartDebounceTimer();
		PBHandlerPB4Pressed();
		//EXTI_ClearITPendingBit(EXTI_Line10);
	}
	
	if ((GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)) == 0)
	{
		PBHandlerPB5Pressed();
	}
		
	if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)) == 0)
	{
    
		//StartDebounceTimer();
		PBHandlerPB1Pressed();
		//EXTI_ClearITPendingBit(EXTI_Line15);
	}
  NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	//NVIC_EnableIRQ(EXTI15_10_IRQn); // Disable interrupt
}

/*
void EXTI3_IRQnHandler(void)
{
	NVIC_DisableIRQ(EXTI3_IRQn); // Disable interrupt
	__DSB();
	__ISB();
	StartDebounceTimer();
	
	if ((GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3)) == 0)
	{
		PBHandlerPB5Pressed();
	}

  NVIC_ClearPendingIRQ(EXTI3_IRQn);
} */ 
  
/**
  * @}
  */ 
  
/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
