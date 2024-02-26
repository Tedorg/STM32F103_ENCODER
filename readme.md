# STM32F103C8T6 Encoder (aka Bluepill) CMSIS no HAL


## Description
This module provides an interface for reading rotary encoders using the STM32F103C8T6 microcontroller (aka BLuepill). It allows you to easily integrate rotary encoders into your STM32F103C8T6-based projects.

## Features
- Support for both incremental and absolute rotary encoders on PA0 PA1 and PA6 PA7
- Hardware timers 
- Serial Interface for debugging

## Installation
1. Clone or download the repository.
2. Copy the necessary files into your STM32F103C8T6 project.
3. The following tools are used for these projects:
	ARM-GCC compiler toolchain.
	stm32flash flash tool using the on-board STM32 serial bootloader over UART.
	st-link flash tool using an ST-LINK V2 USB programmer.
	Official STM32 CMSIS files as part of their STM32Cube MCU packages.
4. set the path in the makefile

## Usage
1. Initialize the encoder module by calling the initialization function.
2. Configure the encoder settings using the provided configuration functions.
3. Start reading the encoder values by enabling the interrupts.
4. Handle the encoder events in the interrupt service routine (ISR).
5. Use the provided functions to retrieve the encoder values in your main code.

## Examples
```in main.c
encoder_t left, right;
init_encoder(&left, &right);
while(1) {
    update_speed(&left, &right);
    print_debug_info(&left, &right);
}
```

## Resources
- RM0008 Reference manual page 329
- https://github.com/getoffmyhack/STM32F103-Bare-Metal
- https://www.edwinfairchild.com/2019/04/interface-rotary-encoder-right-way.html

## Credits
https://www.edwinfairchild.com/2019/04/interface-rotary-encoder-right-way.html
https://github.com/getoffmyhack/STM32F103-Bare-Metal

