/*Module encoder should return the speed of the robot in rotation per minute
The encoder module should be able to calculate the speed of the robot based on the number of encoder steps and the time passed
this module should be initialized with the init_encoder function and updated with the update_speed function

use it like this:

in main.c
encoder_t left, right;
init_encoder(&left, &right);
while(1) {
    update_speed(&left, &right);
    print_debug_info(&left, &right);
}
*/

#include "encoder.h"
#include <stdint.h>
#include <stdio.h>
#include "stm32f1xx.h"
#include "stm32f103_setup.h"


#define ENCODER_COUNT 1300 // number of encoder steps per wheel revolution
#define USED_ENCODERS 2 // how many encoders are used

/*reset encoder count is halt of max uint16. this helps to prevent faulty vlaue on overflow*/
const int reset_encoder_count =65535/2;

int32_t current_millis = 0, previous_millis = 0;

static float calculate_speed( int count, int interval);
static void init_hardware_decoder_1(void);
static void init_hardware_decoder_2(void);
void init_encoder( encoder_t *left, encoder_t *right) {
    
    init_hardware_decoder_1();
    init_hardware_decoder_2();
    
    left->current_count = 0;
    left->speed = 0.0;
    left->position = 0;

    right->current_count = 0;
    right->speed = 0.0;
    right->position = 0;
}

static float calculate_speed( int count, int interval) {
    // Calculate speed in units per minute
    //
    float speed = (count/(float)ENCODER_COUNT)*(60000.0/interval);
    return speed;
}

// ...

void update_speed(encoder_t *left, encoder_t *right) {
    /*
    Update general values for both encoders
    interval is the time passed since the last update. its measured in milliseconds

    */ 

    int interval, count_difference;
    current_millis = millis();
    interval = current_millis - previous_millis;
    
    // Update speed for left encoder
    left->current_count = TIM2->CNT;
    count_difference = left->current_count - reset_encoder_count;
    /*poston sums driven distance */
    left->position += (count_difference);
    left->speed = calculate_speed(count_difference,  interval);
    /*reset encoder count to prevent overflow*/
    TIM2->CNT = reset_encoder_count;
    
    // Update speed for right encoder
    right->current_count = TIM3->CNT;
    count_difference = right->current_count - reset_encoder_count;
    right->position += (count_difference);
    right->speed = calculate_speed(count_difference,  interval);
    TIM3->CNT = reset_encoder_count;

    previous_millis = current_millis;
}

float get_speed(encoder_t *enc){
    return enc->speed;
}

uint32_t get_position(encoder_t *enc){
    return enc->position;
}

void reset_position(encoder_t *enc){
    enc->position = 0;
}


void print_debug_info(encoder_t *left, encoder_t *right) {
    // Print debug information
    printf("Left: %ld, speed: %0.3f Pos: %ld \t Right: %ld, speed: %0.3f Pos: %ld  \n", left->current_count, left->speed, left->position, right->current_count, right->speed, right->position);
}
// ...

// void setup_timer() {
//     // Configure TIM1 channel 4 for 100ms interval
//     TIM1->CCR4 = 100; // Set compare value for 100ms
//     TIM1->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2; // Set channel 4 to PWM mode 1
//     TIM1->CCER |= TIM_CCER_CC4E; // Enable channel 4 output
//     TIM1->CR1 |= TIM_CR1_CEN; // Enable TIM1

//     // Enable TIM1 channel 4 interrupt
//     NVIC_EnableIRQ(TIM1_CC_IRQn);
//     TIM1->DIER |= TIM_DIER_CC4IE; // Enable capture/compare 4 interrupt
// }

    


// float get_speed(struct encoder* enc) {
//     return enc->speed;
// }


 static void init_hardware_decoder_1(void)
  {

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Configure Pins 0 and 1 of Port A as alternate function inputs
    GPIOA->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_CNF7);
    GPIOA->CRL |= (GPIO_CRL_CNF6_1 | GPIO_CRL_CNF7_1);
    TIM3->ARR = 0xFFFF;
    // Configure encoder interface
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;                // Enable clock for TIM2
   // TIM3->CR1 = 0;                                     // Disable timer
    TIM3->CCMR1 = TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0; // Capture on TI1 and TI2
    TIM3->SMCR = TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0;      // Enable encoder mode
    TIM3->CNT = reset_encoder_count;                                 // Reset counter
    TIM3->CR1 |= TIM_CR1_CEN;                          // Enable timer
  }

 static void init_hardware_decoder_2(void)
  {
    // Enable clock for GPIO Port A
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Configure Pins 0 and 1 of Port A as alternate function inputs
    GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1);
    GPIOA->CRL |= (GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1);
    TIM2->ARR =0xFFFF;
    // Configure encoder interface
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;                // Enable clock for TIM2
   // TIM2->CR1 = 0;                                     // Disable timer
    TIM2->CCMR1 = TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0; // Capture on TI1 and TI2
    TIM2->SMCR = TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0;      // Enable encoder mode
    TIM2->CNT = reset_encoder_count;                                 // Reset counter
    TIM2->CR1 |= TIM_CR1_CEN;                          // Enable timer
  }


