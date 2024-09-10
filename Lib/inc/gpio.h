//******************
//GPIO Library
//
// CREATED: 10/27/2023, by Carlos Estay
//
// FILE: gpio.h
//
#include "stm32l031xx.h"

#ifndef GPIO_H
#define GPIO_H

  void GPIO_InitInput(GPIO_TypeDef*, uint16_t);
  void GPIO_InitOutput(GPIO_TypeDef*, uint16_t);
  void GPIO_InitAlternateF(GPIO_TypeDef*, uint16_t, uint16_t);
  void GPIO_Set(GPIO_TypeDef*, uint16_t);
  void GPIO_Clear(GPIO_TypeDef*, uint16_t);
  void GPIO_Toggle(GPIO_TypeDef* , uint16_t);
  int GPIO_Read(GPIO_TypeDef*, uint16_t);

#endif /* GPIO_H */