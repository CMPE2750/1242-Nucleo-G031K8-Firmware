//******************
//PWM Library
//
// CREATED: 10/04/2024, by Carlos Estay
//
// FILE: pwm.h
//

#ifndef PWM_H
#define PWM_H

#include "stm32g031xx.h"

typedef enum CCR_Typedef__
{//Offset from CCR1
    TimCCR1 = 0x00,   //0x34 -  Offset from Base Timer Addr
    TimCCR2 = 0x04,   //0x38 -  Offset from Base Timer Addr
    TimCCR3 = 0x08,   //0x3C -  Offset from Base Timer Addr
    TimCCR4 = 0x0C,   //0x40 -  Offset from Base Timer Addr
    TimCCR5 = 0x24,   //0x58 -  Offset from Base Timer Addr
    TimCCR6 = 0x28,   //0x5C -  Offset from Base Timer Addr
}CCR_Typedef;

typedef enum ChannelMode_Typedef__
{
    OutputCompareToggle,
    InputCapture,
    Pwm1,       //Positive polarity
    Pwm2,       //NegativePolarity
}ChannelMode_Typedef;

/// @brief This funtion enables a timer, using a prescaler(psc) from
///        the BUS speed, a period for reload(ARR) in ticks.
/// @param timer        //Timer object
/// @param psc          //Prescaler
/// @param period       //Auto reload register
void Timer_Setup(TIM_TypeDef * timer, uint16_t psc, uint16_t period);
void Timer_SetupChannel(TIM_TypeDef * timer, CCR_Typedef ccr, ChannelMode_Typedef chMode);
void Timer_WriteCCR(TIM_TypeDef * timer, CCR_Typedef ccr, uint32_t ccrTicks);
void Timer_SetEnable(TIM_TypeDef * timer, uint16_t en);


#endif /* UART_H */
