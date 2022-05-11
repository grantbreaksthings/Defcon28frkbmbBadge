#ifndef MATRIX_H
#define MATRIX_H
#include "stm32f0xx_hal.h"

#define M 2147483647
#define A 16807

uint32_t seed;

uint8_t u8gen_rand();
void seed_rng(uint32_t new_seed);

#endif
