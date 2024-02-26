/****************************************************************************\
 File:          main.h
 
 Description:   main.c header file
 
 Known bugs/missing features:
 
 Modifications:
 Date                Comment
 ----    ------------------------------------------------
\****************************************************************************/

#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdint.h>


// defines to read speed 
#define ENCODER_LEFT 0
#define ENCODER_RIGHT 1



/*********************** function prototypes        *************************/
/*********************** function prototypes        *************************/
void init_setup(void);
void busy_delay(uint32_t milliseconds);

#endif	/* _MAIN_H_ */
