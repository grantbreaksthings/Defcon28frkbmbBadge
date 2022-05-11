#ifndef CONWAY_H
#define CONWAY_H
#include "stm32f0xx_hal.h"
#include "matrix.h"

#define X_BND 7
#define Y_BND 17

uint8_t* active_fbuf;
volatile uint8_t stop_conway;
int life(uint8_t x, uint8_t y);
void conway_demo(I2C_HandleTypeDef* hi2c);
#endif
