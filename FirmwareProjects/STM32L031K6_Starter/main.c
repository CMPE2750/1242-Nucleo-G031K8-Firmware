/*********************************************************************

File    : main.c
Program : Template Project
Author  : Carlos Estay
Purpose : 
Date    : 

Revision History:

*/

/********************************************************************
  Defines
********************************************************************/

/********************************************************************
  Default includes
********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "stm32l031xx.h"
#include "clock.h"
#include "gpio.h"
/*********************************************************************
  Local Prototypes
*********************************************************************/
void HAL_Init(void);

/*********************************************************************
  Global variables 
*********************************************************************/


/*********************************************************************
  Main entry
*********************************************************************/
int main(void) 
{
  /********************************************************************
    One-time Initializations
  ********************************************************************/  
  
  HAL_Init(); //this is needed when working at higher clock speeds (> 24MHz)
  Clock_InitPll(PLL_32MHZ); //Enable Pll to 16MHz
  //printf("System Clock: %u Hz\n\r", SystemCoreClock); //print system clock result
  Clock_EnableOutput(MCO_Sel_SYSCLK, MCO_Div4); //Enables clock output on PA8 and divides it by 1
  GPIO_InitOutput(GPIOA, 5);

  //TIM_Init(TIM6, 80, 500, 1);
  ////TIM_Init(TIM7, 80, 500, 0);
  //NVIC_EnableIRQ(TIM6_IRQn);
  //__enable_irq();
  //TIM_Start(TIM6);


  /********************************************************************
    Infinite Loop
  ********************************************************************/
  while(1)
  {
 
  }
}

/********************************************************************
  Functions
********************************************************************/
void HAL_Init(void)
{
  //Enable power interface clock (RM 7.3.1)
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  
  //Enable instruction prefetch
  FLASH->ACR |= FLASH_ACR_PRFTEN;
  
  FLASH->ACR |= FLASH_ACR_LATENCY;    //One wait state is used to read a word in the NVM.

  /*Peripherals clock enable*/
  RCC->IOPENR |= RCC_IOPENR_GPIOAEN;  //Enable Port A
  RCC->IOPENR |= RCC_IOPENR_GPIOBEN;  //Enable Port B
  RCC->IOPENR |= RCC_IOPENR_GPIOCEN;  //Enable Port C

  RCC->APB1ENR |= RCC_APB1ENR_USART2EN; //Enable USART2
  RCC->APB2ENR |= RCC_APB2ENR_TIM21EN; //Enable TIM22
}
