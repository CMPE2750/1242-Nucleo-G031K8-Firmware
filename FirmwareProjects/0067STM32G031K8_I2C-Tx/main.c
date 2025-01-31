/*********************************************************************

File    : main.c
Program : I2C Transmit
Author  : Carlos Estay
Purpose : 
Date    : Jan-29-2025

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
#include "stm32g031xx.h"
#include "clock.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "i2c.h"


/*********************************************************************
  Local Prototypes
*********************************************************************/
void HAL_Init(void);
void Delay_ms(uint16_t ms);

/*********************************************************************
  Global variables 
*********************************************************************/

volatile uint16_t msCounter = 0, delayCounter = 0;
volatile uint8_t beacon = 0;


/*********************************************************************
  Main entry
*********************************************************************/
int main(void) 
{
  uint8_t data[] = {0x3F, 0xFF};
  /********************************************************************
    One-time Initializations
  ********************************************************************/  
  
  HAL_Init(); //this is needed when working at higher clock speeds (> 24MHz)
  Clock_InitPll(PLL_40MHZ); //Enable Pll to 40MHz
  printf("System Clock: %u Hz\n\r", SystemCoreClock); //print system clock result
  Clock_EnableOutput(MCO_Sel_SYSCLK, MCO_Div1); //Enables clock output on PA8 and divides it factor

  GPIO_InitOutput(GPIOC, 6);  //built in led
  SysTick_Config(SystemCoreClock / 1000); //Make SysTick to Tick at 1[ms] and call SysTick_Handler()
  
  /*****I2C INitialization*****/

  /*I2C low level configuration*/
  GPIO_InitAlternateF(GPIOA, 9, 6); //SCL
  GPIO_I2C_Config(GPIOA, 9);
  GPIO_InitAlternateF(GPIOA, 10, 6); //SDA
  GPIO_I2C_Config(GPIOA, 10);
  
  /*Init I2C Module*/
  I2C_Init(I2C1, I2C_Standard);

  /*****USART2 INitialization*****/
  GPIO_InitAlternateF(GPIOA, 2, 1);
  GPIO_InitAlternateF(GPIOA, 3, 1);
  UART_Init(USART2, 115200, 0);

  /********************************************************************
    Infinite Loop
  ********************************************************************/
  while(1)
  {
    if(beacon)
    {
      beacon = 0;
      GPIO_Toggle(GPIOC, 6);
      I2C_ScanFirstAddr(I2C1);
      //I2C_Transmit(I2C1, 0xE1,data, 2);
    }
  }
}

/********************************************************************
  Functions
********************************************************************/
void HAL_Init(void)
{
  //Enable power interface clock (RM 5.4.15)
  RCC->APBENR1 |= RCC_APBENR1_PWREN_Msk;
  

  /*Define HCLK clock ratio to the FLASH,
    slow down system to access flash (RM 3.7.1)*/

  FLASH->ACR |= FLASH_ACR_PRFTEN_Msk;     //Enable instruction prefetch  
  FLASH->ACR |= FLASH_ACR_LATENCY_Msk;    //One wait state is used to read a word in the NVM.

  /*Peripherals clock enable (RM 5.4.13)*/
  
  RCC->IOPENR |= RCC_IOPENR_GPIOAEN_Msk;  //Enable Port A
  RCC->IOPENR |= RCC_IOPENR_GPIOBEN_Msk;  //Enable Port B
  RCC->IOPENR |= RCC_IOPENR_GPIOCEN_Msk;  //Enable Port C

  RCC->APBENR1 |= RCC_APBENR1_USART2EN_Msk;     //Enable USART2
  RCC->APBENR1 |= RCC_APBENR1_I2C1EN;           //Enable I2C1
  /*We need this following setting to the I2C1 module is bus speed independent*/
  RCC->CCIPR &= ~RCC_CCIPR_I2C1SEL_Msk; //Clear Independe clock setting
  RCC->CCIPR |= RCC_CCIPR_I2C1SEL_1;    //Set independent clock to HSI16

}
void Delay_ms(uint16_t ms)
{
  delayCounter = ms;
  while(delayCounter);
}


/*  This event Handler gets called every 1[ms] according to Systick Configuration
    This is technically not an ISR (it's an exception), therefore 
    it requires no flag clearing.
*/
void SysTick_Handler(void)
{
  if(delayCounter)
  {
    --delayCounter;
  }
  if(++msCounter > 99)
  {
    //GPIO_Toggle(GPIOC, 6);
    msCounter = 0;
    beacon = 1;   
  }
}
 
/****************Interrupt Service Routines (ISR's)***********************/

