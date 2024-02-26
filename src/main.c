/****************************************************************************\
 File:          main.c
 Date:

 Description:
  Main program file for the STM32F103C8T6 "Blue Pill" development board.
  This file contains the main program loop and initialization functions.



 Known bugs/missing features:

\****************************************************************************/
#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include "stm32f1xx.h"
#include "stm32f103_setup.h"
#include "encoder.h"
/*measure time passed since the last update*/
uint32_t initialTime = 0;
encoder_t left, right;

// init stm32 setup functions
void init_setup(void)
{
    setup_clock_speed();
   //Enable DWT 
    enableDWT();
    //init_rtc();
   
    init_encoder(&left, &right);
}

int main(void)
{
    

    init_setup();
    uint32_t clock_speed = SystemCoreClock / 1000000;
    printf("MEMORY %d kb  CLOCKSPEED %ld MHz   TIME %ld \n", *((uint16_t *)0x1FFFF7E0), clock_speed, micros());

   
    while (1)
    {   

        uint32_t currentMillis = millis();
        if ( currentMillis - initialTime >= 100)
        {
            update_speed(&left, &right);
            // Print debug information
            print_debug_info(&left, &right);
           
        initialTime =  currentMillis;

        }
    }
}