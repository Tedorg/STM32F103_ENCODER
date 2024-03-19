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
#include "uart.h"
#include "encoder.h"

#define NUMBER_OF_ENCODER 2
/*measure time passed since the last update*/
uint32_t initialTime = 0;

// init stm32 setup functions
void init_setup(void)
{
    setup_clock_speed();
    // Enable DWT
    enableDWT();
    // init_rtc();
    init_uart();
}

int main(void)
{

    init_setup();

    encoder_t encoder_data[NUMBER_OF_ENCODER];
    for (int i = 0; i < NUMBER_OF_ENCODER; i++)
    {

        init_encoder(&encoder_data[i], (uint8_t)i);
    }
    uint32_t clock_speed = SystemCoreClock / 1000000;
    printf("MEMORY %d kb  CLOCKSPEED %ld MHz   TIME %ld \n", *((uint16_t *)0x1FFFF7E0), clock_speed, micros());

    // reset_position_enc(&encoder_data[ENCODER_LEFT]);
    // reset_position_enc(&encoder_data[ENCODER_RIGHT]);

    while (1)
    {

        uint32_t currentMillis = millis();
        if (currentMillis - initialTime >= 100)
        {
            update_encoder(&encoder_data[ENCODER_LEFT]);
            update_encoder(&encoder_data[ENCODER_RIGHT]);

            float speed_left = get_speed_enc(&encoder_data[ENCODER_LEFT]);
            float speed_right = get_speed_enc(&encoder_data[ENCODER_RIGHT]);

            uint32_t position_left = get_position_enc(&encoder_data[ENCODER_LEFT]);
            uint32_t position_right = get_position_enc(&encoder_data[ENCODER_RIGHT]);

            // Print debug information
            printf("\nLEFT: ");
            print_info_enc(&encoder_data[ENCODER_LEFT]);
            printf("RIGHT: ");
            print_info_enc(&encoder_data[ENCODER_RIGHT]);
            initialTime = currentMillis;
        }
    }
    return 0;
}