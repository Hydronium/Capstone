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

void RTC_Alarm_IRQHandler(void)
{
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET)
  {
		RTCInterrupt++;
    RTC_ClearITPendingBit(RTC_IT_ALRA);
    EXTI_ClearITPendingBit(EXTI_Line17);
  } 
}

void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

		TimerInterrupt = 1;
  }
}

/**
 * External interrupt channel 0 Interrupt Handler. This handles
 * the user button.
 */
/*
void EXTI0_IRQHandler(void){
	
	EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
	//state = 1;
	if((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) == 1){
	//pb0_pressed = 1;
		//wait = 1;
	}
 else if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) == 0){
		//pb0_pressed = 0;
	}
}
*/

// Button 1, PB1
void EXTI1_IRQHandler(void)
{
	if ((GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1)) == 0)
	{
		if (ProgramMode == 0)
		{
			//LCDDisplayText(5, 0, "Button PB1");
			ProgramMode++;
		}
		else if (ProgramMode == 1)
		{
			//LCDDisplayText(5, 0, "LALALA PB1");
			ProgramMode--;
		}
	}
 
	EXTI_ClearITPendingBit(EXTI_Line1);
}

// Button 2, PD2
void EXTI2_IRQHandler(void)
{
	if ((GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)) == 0)
	{
		if (ProgramMode == 1)
		{
			b2++;
			
			if (b2 > 2)
			{
				b2 = 0; //0 - Day, 1 - Hour, 2 - Minute
			}
		}
	}
 
	EXTI_ClearITPendingBit(EXTI_Line2);
}

// Button 3, PA3
void EXTI3_IRQHandler(void)
{
	if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)) == 0)
	{
		if (ProgramMode == 1)
		{
			b3++;
		}
	}
 
	EXTI_ClearITPendingBit(EXTI_Line3);
}

// Button 4, PB4
void EXTI4_IRQHandler(void)
{
	if ((GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)) == 0)
	{
		if (ProgramMode == 1)
		{
			b4++;
		}
	}
 
	EXTI_ClearITPendingBit(EXTI_Line4);
}


/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
