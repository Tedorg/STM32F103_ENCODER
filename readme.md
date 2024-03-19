# STM32F103C8T6 (aka Bluepill) Encoder Mode CMSIS no HAL


## Description
This module provides an interface for reading rotary encoders using the STM32F103C8T6 microcontroller (aka Bluepill). It allows you to easily integrate rotary encoders into your STM32F103C8T6-based projects.

## Features
- Support for two quadrature rotary encoders on PA0 PA1 and PA6 PA7.
- Serial interface for debugging.

## Installation
1. Clone or download the repository.
2. Copy the necessary files into your STM32F103C8T6 project.
3. The following tools are used for these projects:
	- ARM-GCC compiler toolchain.
	- st-link flash tool using an ST-LINK V2 USB programmer.
	- Official STM32 CMSIS files as part of their STM32Cube MCU packages.
4. set the path in the makefile

## Usage
 -  Initialize the encoder module by calling the initialization function.
 -  get speed and postition of encoders

 ## FLASHING
 - run make clean
 - run make swd_flash



## Examples
```in main.c

#define NUMBER_OF_ENCODER 2
#define ENCODER_LEFT 0
#define ENCODER_RIGHT 1

encoder_t encoder_data[NUMBER_OF_ENCODER];
    for (int i = 0; i < NUMBER_OF_ENCODER; i++)
    {
        init_encoder(&encoder_data[i], (uint8_t)i);
    }
while(1) {
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
}
```

## Resources
- RM0008 Reference manual page 329
- https://github.com/getoffmyhack/STM32F103-Bare-Metal
- https://www.edwinfairchild.com/2019/04/interface-rotary-encoder-right-way.html

## Credits
https://www.edwinfairchild.com/2019/04/interface-rotary-encoder-right-way.html
https://github.com/getoffmyhack/STM32F103-Bare-Metal

