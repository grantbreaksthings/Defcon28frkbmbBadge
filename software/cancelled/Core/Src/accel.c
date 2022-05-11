#include "accel.h"

int init_accel(I2C_HandleTypeDef* i2c){
	// Set output data rate to 50hz by writing to CTRL1 register
	// and turn on BDU
	uint8_t dat[2] = {0x20, 0x2F};
	uint8_t buf = 0;
	HAL_I2C_Master_Transmit(i2c, ACC_ADDR_WR, &dat, 2, HAL_MAX_DELAY);
	// Set the full scale selection to +-4G, turn on auto increment reads
	dat[0] = 0x23;
	dat[1] = 0x24;
	HAL_I2C_Master_Transmit(i2c, ACC_ADDR_WR, &dat, 2, HAL_MAX_DELAY);

	// Read back the whoami register
	dat[0] = 0xF;
	HAL_I2C_Master_Transmit(i2c, ACC_ADDR_WR, &dat, 1, HAL_MAX_DELAY);
	// Read the data back
	HAL_I2C_Master_Receive(i2c, ACC_ADDR_RD, &buf, 1, HAL_MAX_DELAY);
	return buf;
}

int16_t _get_16bit_reg(uint8_t start_addr, I2C_HandleTypeDef* i2c){
	uint8_t buf_l;
	uint8_t buf_h;
	// Get the lower bits from the register pair, write the address to the bus
	HAL_I2C_Master_Transmit(i2c, ACC_ADDR_WR, &start_addr, 1, HAL_MAX_DELAY);
	// Read the data back
	HAL_I2C_Master_Receive(i2c, ACC_ADDR_RD, &buf_l, 1, HAL_MAX_DELAY);
	// Get the higher bits from the register pair, write the address to the bus
	start_addr = start_addr + 1;
	HAL_I2C_Master_Transmit(i2c, ACC_ADDR_WR, &start_addr, 1, HAL_MAX_DELAY);
	// Read the data back
	HAL_I2C_Master_Receive(i2c, ACC_ADDR_RD, &buf_h, 1, HAL_MAX_DELAY);
	// Return the formatted data
	return (buf_h << 8) | buf_l;
}

int16_t get_x(I2C_HandleTypeDef* i2c){
	return _get_16bit_reg(X_DATA_REG, i2c);
}

int16_t get_y(I2C_HandleTypeDef* i2c){
	return _get_16bit_reg(Y_DATA_REG, i2c);
}
int16_t get_z(I2C_HandleTypeDef* i2c){
	return _get_16bit_reg(Z_DATA_REG, i2c);
}
int16_t get_temp(I2C_HandleTypeDef* i2c){
	return _get_16bit_reg(TMPTR_DATA_REG, i2c);
}

int16_t get_x_avg(I2C_HandleTypeDef* i2c, uint16_t samples){
	int32_t avg = 0;
	for(uint16_t i = 0; i < samples; i++){
		avg = avg + get_x(i2c);
	}
	return avg / samples;
}

int16_t get_y_avg(I2C_HandleTypeDef* i2c, uint16_t samples){
	int32_t avg = 0;
	for(uint16_t i = 0; i < samples; i++){
		avg = avg + get_y(i2c);
	}
	return avg / samples;
}

int16_t get_z_avg(I2C_HandleTypeDef* i2c, uint16_t samples){
	int32_t avg = 0;
	for(uint16_t i = 0; i < samples; i++){
		avg = avg + get_z(i2c);
	}
	return avg / samples;
}
