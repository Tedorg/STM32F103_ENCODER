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

float get_speed(encoder_t *enc);

int32_t get_position(encoder_t *enc);

void reset_position(encoder_t *enc);

struct encoder {
    uint16_t current_count;
    int32_t position;
    float speed; // units per minute
};


#endif // ENCODER_H