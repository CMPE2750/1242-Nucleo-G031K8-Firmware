//******************
//Clock Library
//
// CREATED: Sept/24/2024, by Carlos Estay
//
// FILE: clock.h
//
//
#include "stm32g031xx.h"

#ifndef CLOCK_H
#define CLOCK_H

#define RCC_CFGR_SW_PLL RCC_CFGR_SW_1

/*
  PLL_CLK = PLL_IN x (N / M) / R 
  Default R = 2

*/
typedef enum PllRangeTypedef__
{
    PLL_16MHZ = 1<<RCC_PLLCFGR_PLLR_Pos | 4<<RCC_PLLCFGR_PLLN_Pos | 2<<RCC_PLLCFGR_PLLM_Pos, // 16MHz x 4 / 2 / 2
    PLL_20MHZ = 1<<RCC_PLLCFGR_PLLR_Pos | 5<<RCC_PLLCFGR_PLLN_Pos | 2<<RCC_PLLCFGR_PLLM_Pos, // 16MHz x 5 / 2 /2
    PLL_24MHZ = 1<<RCC_PLLCFGR_PLLR_Pos | 6<<RCC_PLLCFGR_PLLN_Pos | 2<<RCC_PLLCFGR_PLLM_Pos, // 16MHz x 6 / 2 / 2
    PLL_32MHZ = 1<<RCC_PLLCFGR_PLLR_Pos | 4<<RCC_PLLCFGR_PLLN_Pos | 1<<RCC_PLLCFGR_PLLM_Pos, // 16MHz x 4 / 1 / 2
    PLL_40MHZ = 1<<RCC_PLLCFGR_PLLR_Pos | 5<<RCC_PLLCFGR_PLLN_Pos | 1<<RCC_PLLCFGR_PLLM_Pos, // 16MHz x 5 / 1 / 2
    PLL_48MHZ = 1<<RCC_PLLCFGR_PLLR_Pos | 6<<RCC_PLLCFGR_PLLN_Pos | 1<<RCC_PLLCFGR_PLLM_Pos, // 16MHz x 6 / 1 / 2
    PLL_64MHZ = 1<<RCC_PLLCFGR_PLLR_Pos | 8<<RCC_PLLCFGR_PLLN_Pos | 1<<RCC_PLLCFGR_PLLM_Pos, // 16MHz x 8 / 1 / 2

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


void Clock_InitPll(PllRange);
void Clock_EnableOutput(MCO_Select, MCO_Div);
  
#endif /* CLOCK_H */