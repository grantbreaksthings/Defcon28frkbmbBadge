#ifndef DOGGO_H
#define DOGGO_H

#include "stm32f0xx_hal.h"
#include "matrix.h"
#include "accel.h"
#include "img.h"

uint8_t* active_fbuf;
uint8_t* next_fbuf;

int doggo_demo(I2C_HandleTypeDef* hi2c);

#endif
