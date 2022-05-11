#ifndef ACCEL_H
#define ACCEL_H
#include "stm32f0xx_hal.h"

#define ACC_ADDR_WR 	0x1D << 1 | 0
#define ACC_ADDR_RD 	0x1D << 1 | 1

#define X_DATA_REG		0x28
#define Y_DATA_REG		0x2A
#define Z_DATA_REG		0x2C
#define TMPTR_DATA_REG	0x0B

// Notes to self
// Look into BDU (block data update) on the LIS12. Might be important
// X, Y, Z registers might be twos complement? Temperature is for sure

int init_accel(I2C_HandleTypeDef* i2c);
int16_t get_x(I2C_HandleTypeDef* i2c);
int16_t get_y(I2C_HandleTypeDef* i2c);
int16_t get_z(I2C_HandleTypeDef* i2c);
int16_t get_x_avg(I2C_HandleTypeDef* i2c, uint16_t samples);
int16_t get_y_avg(I2C_HandleTypeDef* i2c, uint16_t samples);
int16_t get_z_avg(I2C_HandleTypeDef* i2c, uint16_t samples);
float get_xy_angle(I2C_HandleTypeDef* i2c);
int16_t get_temp(I2C_HandleTypeDef* i2c);
int16_t _get_16bit_reg(uint8_t start_addr, I2C_HandleTypeDef* i2c);
int reset_accel(I2C_HandleTypeDef* i2c);

#endif
