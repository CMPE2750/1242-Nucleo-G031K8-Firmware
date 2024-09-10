//******************
//Clock Library
//
// CREATED: 10/27/2023, by Carlos Estay
//
// FILE: clock.c
//


//Max MCU Frequency: 32MHz

#include "gpio.h"
#include "clock.h"

void Clock_InitMsi(MsiRange msiRange)
{
  //Set MSI range
  RCC->ICSCR &= ~RCC_ICSCR_MSIRANGE_Msk;  //Clear MSI range
  RCC->ICSCR |= msiRange;                //Set range
  RCC->CR |=  RCC_CR_MSION;              //Set MSI on

  SystemCoreClockUpdate();  //This is a CMSIS function
  //https://arm-software.github.io/CMSIS_5/latest/Core/html/group__system__init__gr.html
}

void Clock_InitPll(PllRange pllRange)
{
  RCC->CR &= ~RCC_CR_PLLON;             //Disable Pll
  while(RCC->CR  & RCC_CR_PLLRDY);     //Wait until Pll is fully stopped
  /*
  For Pll Configuration check (7.2.4) in the Reference Manual
  Also, the Clock Configuration tab in STMCubeMx 

  - PLLSRC = 0 (HSI16 Clock)  //16MHZ
  - PLLSRC = 1 (HSE Clock)    //Given by external crystal

  PLL_Out = PLL_IN x PLLMUL / PLLDIV


  The PLL VCO clock frequency must not exceed 96 MHz when the product is in
  Range 1, 48 MHz when the product is in Range 2 and 24 MHz when the product is in
  Range 3. (RM 7.3.3)

  */
  RCC->CR |= RCC_CR_HSION_Msk; //Turn ON HSI
  //Clear multiplier and  didisor
  RCC->CFGR &= ~(RCC_CFGR_PLLMUL_Msk | RCC_CFGR_PLLDIV_Msk);
  RCC->CFGR |= pllRange;

  RCC->CR |= RCC_CR_PLLON;              //Enable Pll again
  while(!(RCC->CR & RCC_CR_PLLRDY));    //Wait until PLL is locked
  RCC->CFGR |= RCC_CFGR_SW_PLL;         //Set Pll as System Clock

  SystemCoreClockUpdate();  //This is a CMSIS function
  //https://arm-software.github.io/CMSIS_5/latest/Core/html/group__system__init__gr.html
}

void Clock_EnableOutput(MCO_Select sel, MCO_Div div)
{
  GPIO_InitAlternateF(GPIOA, 8, 0);
  //Clear current DIV and source
  RCC->CFGR &= ~(RCC_CFGR_MCOPRE_Msk| RCC_CFGR_MCOSEL_Msk);
  RCC->CFGR |= div | sel;
  //RCC->CFGR |= sel;
}