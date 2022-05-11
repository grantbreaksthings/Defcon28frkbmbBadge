#ifndef MATRIX_H
#define MATRIX_H

#include "stm32f0xx_hal.h"

#define MTX_ADDR_WR 0x74 << 1 | 0
#define MTX_ADDR_RD 0x74 << 1 | 1
#define MTX_FBUF_ADDR 0x24
#define MTX_ERROR 1
#define MTX_OK 0
#define MTX_WIDTH 8
#define MTX_HEIGHT 18

uint8_t send_fbuf[145];
uint8_t fbuf0[144];
uint8_t fbuf1[144];

extern uint8_t* active_fbuf;
extern uint8_t* next_fbuf;

int init_matrix(I2C_HandleTypeDef* i2c);
int update_fbuf(I2C_HandleTypeDef* i2c);
int clear_fbuf();
#endif
