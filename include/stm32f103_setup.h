#ifndef STM32F103_SETUP_H
#define STM32F103_SETUP_H
#include <stdint.h>

// Function to set the clock speed
void busy_tick(void);
uint32_t measure_cpu_usage(void);

void setup_clock_speed();

// Function to initialize the Real-Time Clock (RTC)
void init_rtc();


// Other setup function declarations can be added here

void enableDWT(void);
uint32_t micros(void);
uint32_t millis(void);
#endif /* STM32F103_SETUP_H */
