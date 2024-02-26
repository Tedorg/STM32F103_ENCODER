#ifndef ENCODER_H
#define ENCODER_H
#include <stdint.h>

typedef struct encoder encoder_t;
// Function declarations or any other code you want to include in the header file
void init_encoder( encoder_t *left, encoder_t *right);
// float calculate_speed( int encoder_count, int time);

// void init_encoder( encoder_t* left, encoder_t* right) {
void update_speed(encoder_t *left, encoder_t *right);
// float get_speed(struct encoder* enc);
void print_debug_info(encoder_t *left, encoder_t *right);


// void init_hardware_decoder_1(void); 
// void init_hardware_decoder_2(void);

struct encoder {
    int32_t current_count;
    int32_t previous_count;
    float speed; // units per minute
    int32_t position;
};


#endif // ENCODER_H