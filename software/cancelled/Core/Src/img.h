#ifndef ROTATE_H
#define ROTATE_H
#include "stm32f0xx_hal.h"
#include "matrix.h"

struct img{
	uint8_t* bitmap;
	uint8_t width;
	uint8_t height;
	uint8_t x;
	uint8_t y;
};

uint8_t* next_fbuf;

void draw_image(struct img* image);


#endif
