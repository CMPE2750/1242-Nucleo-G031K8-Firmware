//******************
//lcd Library
//
// CREATED: 11/10/2023, by Carlos Estay
//
// FILE: lcd.c
//
/*

LCD   STM32
D0 -> PC0
D1 -> PC1
D2 -> PC2
D3 -> PC3
D4 -> PC4
D4 -> PC5
D6 -> PC6
D7 -> PC7

RS -> PC8
RW -> PC9
E - > PC10

*/


#include "lcd.h"
#include "gpio.h"
#include "simpleTimer.h"



void PortInput(void);
void PortOutput(void);


void lcd_Init (void)
{
    uint8_t data = 0;
    /*
    Use TIM7 for delays
    Remember to enable clock for TIM6 in HAL init
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM7EN; //Enable timer 7 

    */
    TIM_Init(TIM7, 80, 500, 0);

    //SET PC0 - PC7 as GPIO ouputs
    PortOutput();
    //SET PC8-PC10 as GPIO ouputs
    GPIO_InitOutput(GPIOC, 8);
    GPIO_InitOutput(GPIOC, 9);
    GPIO_InitOutput(GPIOC, 10);

    //1st delay - Delay 40+ [ms]
    TIM_Delay_us(TIM7, 45000);

    
    
    //Present Data on PC0-PC7
    GPIOC->ODR &= ~0xFF;    //Clear 8 lsb
    data  = 0b00111000;  //Function Set
/*             ||||||_____(don't care)
               |||||______(don't care)
               ||||_______font:  5x8 matrix (LOW)
               |||________lines: 2 (HIGH)
               ||_________data:  8-bit (HIGH)
               |__________function set of commands
*/ 
    GPIOC->ODR |= data;

    //Write Operation - Instruction Register
    //PC9->R/W->0  PC8->RS->0  
    GPIO_Clear(GPIOC, 9);
    GPIO_Clear(GPIOC, 8);
    //Latch Instruction
    GPIO_Set(GPIOC, 10);
    TIM_Delay_us(TIM7, 5);
    GPIO_Clear(GPIOC, 10);

    //2nd Delay, 4.1ms+   
    TIM_Delay_us(TIM7, 5000);
    //Latch same Instruction again
    GPIO_Set(GPIOC, 10);
    TIM_Delay_us(TIM7, 5);
    GPIO_Clear(GPIOC, 10);

    //third Delay  100+[us]
    TIM_Delay_us(TIM7, 150);
    //Latch same Instruction again
    GPIO_Set(GPIOC, 10);
    TIM_Delay_us(TIM7, 5);
    GPIO_Clear(GPIOC, 10);


    //Busy flag is active now**********************

    //We can check for busy flag now**********************
    //5x8 dots, 2 lines
    lcd_Ins(0b00111000); 
    lcd_Ins(0b00001110);   //display controls
/*                 ||||_____Blink:   LOW for off
                   |||______Cursor:  HIGH for on
                   ||_______Display: HIGH for on
                   |________Display Control commands    
*/
    lcd_Ins(0b00000001);   //clear display, home position
    lcd_Ins(0b00000110);   //mode controls
/*                  |||_____Shift:   LOW for no display shift
                    ||______Inc/Dec: HIGH for increment (to the left)
                    |_______Entry Mode commands
*/         
    
}
//------------------------------------------------------------------------------
uint8_t lcd_Busy (void)
{
    uint8_t busyState;

    /*data bus as inputs for read*/
    PortInput();

    //PC9->R/W->1  PC8->RS->0  
    GPIO_Set(GPIOC, 9);     //Read Operation
    GPIO_Clear(GPIOC, 8);   //Instruction Register

    //Latch Instruction
    GPIO_Set(GPIOC, 10);
    TIM_Delay_us(TIM7, 5);
    GPIO_Clear(GPIOC, 10);

    //Busy Flag is the MSB and AC PC0 - PC7 of the Status Register
    busyState = GPIOC->IDR & GPIO_IDR_ID7_Msk;	
    //data bus returned to outputs for next write
    PortOutput();

    return busyState;  
}

//------------------------------------------------------------------------------
void lcd_Ins(uint8_t command)
{
    while (lcd_Busy());//wait for the Busy Flag to be CLEARED
    //Present Data on PC0-PC7
    GPIOC->ODR &= ~0xFF;    //Clear 8 lsb
    GPIOC->ODR |= command;
    GPIO_Clear(GPIOC, 9);     //Write Operation
    GPIO_Clear(GPIOC, 8);   //Instruction Register 
    //Latch Instruction
    GPIO_Set(GPIOC, 10);
    TIM_Delay_us(TIM7, 5);
    GPIO_Clear(GPIOC, 10);   
}
//------------------------------------------------------------------------------
void lcd_Data (uint8_t data)
{
    while (lcd_Busy());//wait for the Busy Flag to be CLEARED
    //Present Data on PC0-PC7
    GPIOC->ODR &= ~0xFF;    //Clear 8 lsb
    GPIOC->ODR |= data; 
    GPIO_Clear(GPIOC, 9);    //Write Operation
    GPIO_Set(GPIOC, 8);     //Data Register    

    //Latch data
    GPIO_Set(GPIOC, 10);
    TIM_Delay_us(TIM7, 5);
    GPIO_Clear(GPIOC, 10);  
}


//------------------------------------------------------------------------------
void PortInput(void)
{
    for (int i = 0; i < 8; i++)
    {
        GPIO_InitInput(GPIOC, i);
    }   
}
//------------------------------------------------------------------------------
void PortOutput(void)
{
    for (int i = 0; i < 8; i++)
    {
        GPIO_InitOutput(GPIOC, i);
    }   
}
