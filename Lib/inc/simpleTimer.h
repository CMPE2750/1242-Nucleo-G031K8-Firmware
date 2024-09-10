//******************
//Simple Timer Library
//
// CREATED: 11/22/2023, by Carlos Estay
//
// FILE: simpleTimer.h
//
#include "stm32l031xx.h"

/// @brief Init Timer
/// @param Timer
/// @param prescale  
/// @param arr 
/// @param int-noint  
void TIM_Init(TIM_TypeDef*, uint16_t, uint16_t, uint16_t);
void TIM_Start(TIM_TypeDef*);
void TIM_Delay_us(TIM_TypeDef*, uint16_t);