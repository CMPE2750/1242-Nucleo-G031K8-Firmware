//******************
//Clock Library
//
// CREATED: 10/27/2023, by Carlos Estay
//
// FILE: clock.h
//
//
#include "stm32l031xx.h"

#ifndef CLOCK_H
#define CLOCK_H



typedef enum MsiRangeTyepedef__
{/**/
    Msi65KHZ = 0 << 13,
    Msi131KHZ = 1 << 13,
    Msi262KHZ = 2 << 13,
    Msi524KHZ = 3 << 13,
    Msi1_048MHZ = 4 << 13,
    Msi2_097MHZ = 5 << 13,
    Msi4_194MHZ = 6 << 13
}MsiRange;
  
typedef enum PllRangeTypedef__
{

  /*
  Formula:

  PLL_Out = PLL_IN x PLLMUL / PLLDIV

  PLL_IN must be in the range of 2MHz - 24MHz.

    - PLLMUL is defaulted to 0(x3)
    - PLLDIV can be 2 (01), 3(10), or 4(11). 0 is not allowed

  */

    PLL_16MHZ = 1<<RCC_CFGR_PLLMUL_Pos | RCC_CFGR_PLLDIV4_Msk,    // 16MHz x 4 / 4
    PLL_24MHZ = 0<<RCC_CFGR_PLLMUL_Pos | RCC_CFGR_PLLDIV2_Msk,    // 16MHz x 3 / 2
    PLL_32MHZ = 1<<RCC_CFGR_PLLMUL_Pos | RCC_CFGR_PLLDIV2_Msk,   // 16MHz x 4 / 2

}PllRange;  


typedef enum MCO_DivTpedef__
{
    MCO_Div1 = 0 << 28,
    MCO_Div2 = 1 << 28,
    MCO_Div4 = 2 << 28,
    MCO_Div8 = 3 << 28,
    MCO_Div16 = 4 << 28
}MCO_Div;

typedef enum MCO_SelectTpedef__
{
    MCO_Sel_None= 0 << 24,
    MCO_Sel_SYSCLK = 1 << 24,
    MCO_Sel_HSI16 = 2 << 24,
    MCO_Sel_MSI = 3 << 24,
    MCO_Sel_HSE = 4 << 24,
    MCO_Sel_PLL = 5 << 24,
    MCO_Sel_LSI = 6 << 24,
    MCO_Sel_LSE = 7 << 24
}MCO_Select;


void Clock_InitMsi(MsiRange);
void Clock_InitPll(PllRange);
void Clock_EnableOutput(MCO_Select, MCO_Div);
  
#endif /* CLOCK_H */