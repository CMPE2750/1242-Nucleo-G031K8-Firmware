//******************
//lcd Library
//
// CREATED: 11/10/2023, by Carlos Estay
//
// FILE: lcd.h
//

#include "stm32l031xx.h"

#define Latch


void lcd_Init (void);
uint8_t lcd_Busy (void); 
void lcd_Ins (uint8_t);
void lcd_Data (uint8_t);