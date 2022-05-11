#ifndef ROTATE_H
#define ROTATE_H
#include "stm32f0xx_hal.h"
#include "matrix.h"
#include "img.h"

uint8_t* next_fbuf;
uint8_t stop_rotate;
void rotate_demo(I2C_HandleTypeDef* hi2c);


#endif
