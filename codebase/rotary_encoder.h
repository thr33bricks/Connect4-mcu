#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

// Initialisation
void init_encoders(void *base);

// For buttons
int is_red_clicked(void *base);
int is_green_clicked(void *base);
int is_blue_clicked(void *base);

// For rotations
int get_rotation_red(void *base);
int get_rotation_green(void *base);
int get_rotation_blue(void *base);

#endif