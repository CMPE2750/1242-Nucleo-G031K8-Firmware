//******************
//Simple Timer Library
//
// CREATED: 11/22/2023, by Carlos Estay
//
// FILE: simpleTimer.c
//

#include "simpleTimer.h"


void TIM_Init(TIM_TypeDef* timer, uint16_t psc, uint16_t arr, uint16_t iEnable)
{
  timer->CR1 &= ~TIM_CR1_CEN;   //Disable counter

  timer->PSC = psc - 1;          //Set prescaler
  timer->ARR = arr;           //set auto-reload
  if(iEnable)
  {
    timer->DIER |= TIM_DIER_UIE_Msk; //Enable interrupt on update event
  }
  else
  {
    timer->DIER &= ~TIM_DIER_UIE_Msk; //disable interrupt on update event
  }
  timer->CR1 |= TIM_CR1_URS_Msk; //Only counter overflow generates ISR (33.4.1)
}
//--------------------------------------------------------------------------------------
void TIM_Start(TIM_TypeDef* timer)
{
    timer->CR1 |= TIM_CR1_CEN;    //Enable counter
}
//--------------------------------------------------------------------------------------
void TIM_Delay_us(TIM_TypeDef* timer, uint16_t us)
{
    timer->CR1 &= ~TIM_CR1_CEN;             //Disable counter
    timer->ARR = us;                        //set [us] counts
    timer->EGR |= TIM_EGR_UG_Msk;           //Re-initialize counter and registers
    timer->SR &= ~TIM_SR_UIF_Msk;           //Clear flag
    timer->CR1 |= TIM_CR1_CEN;             //Start counter
    while(!(timer->SR & TIM_SR_UIF_Msk));   //Wait till event tOut
    timer->SR &= ~TIM_SR_UIF_Msk;           //Clear flag
    timer->CR1 &= ~TIM_CR1_CEN;             //Disable counter
}

//--------------------------------------------------------------------------------------