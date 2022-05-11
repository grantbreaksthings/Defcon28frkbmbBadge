#include "matrix.h"
#include <string.h>

uint8_t* active_fbuf;
uint8_t* next_fbuf;

int init_matrix(I2C_HandleTypeDef* i2c){
	// Set up the next and active fbuf pointers
	active_fbuf = fbuf0;
	next_fbuf = fbuf1;
	// Clear the frame buffers
	clear_fbuf();
	// Turn on the GPIO that controls the shutdown register for the matrix
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);

	// Set command register to point to function register
	uint8_t dat[2] = {0xfd, 0x0b};
	HAL_I2C_Master_Transmit(i2c, MTX_ADDR_WR, &dat, 2, HAL_MAX_DELAY);

	// Bring matrix out of shutdown, write a 1 to shutdown register
	dat[0] = 0xa;
	dat[1] = 0x1;
	HAL_I2C_Master_Transmit(i2c, MTX_ADDR_WR, &dat, 2, HAL_MAX_DELAY);

	// Set command register to point to frame 1 register
	dat[0] = 0xfd;
	dat[1] = 0x00;
	HAL_I2C_Master_Transmit(i2c, MTX_ADDR_WR, &dat, 2, HAL_MAX_DELAY);

	// Set all the LEDs to on
	for(uint8_t i = 0; i < 0x12; i++){
	  dat[0] = i;
	  dat[1] = 0xFF;
	  HAL_I2C_Master_Transmit(i2c, MTX_ADDR_WR, &dat, 2, HAL_MAX_DELAY);
	}
	// Initialize the LEDs with the cleared frame buffer
	HAL_I2C_Master_Transmit(i2c, MTX_ADDR_WR, send_fbuf, 145, HAL_MAX_DELAY);
	// Set the I2C as ready
	return MTX_OK;
}

int update_fbuf(I2C_HandleTypeDef* i2c){
	// Transform the fbuf so it gets displayed properly
	transform_fbuf();
	// Send the new fbuf over to the matrix
	HAL_I2C_Master_Transmit(i2c, MTX_ADDR_WR, send_fbuf, 145, HAL_MAX_DELAY);
	// Swap the next and active fbuf pointers
	uint8_t *tmp = next_fbuf;
	next_fbuf = active_fbuf;
	active_fbuf = tmp;
	memset(next_fbuf, 0, 144);
	return MTX_OK;
}

int transform_fbuf(){
	// Move the data in the fbuf around to handle the LED layout
	memcpy(send_fbuf + 1,   next_fbuf + 0 *  MTX_WIDTH, 8);
	memcpy(send_fbuf + 17,  next_fbuf + 1 *  MTX_WIDTH, 8);
	memcpy(send_fbuf + 33,  next_fbuf + 2 *  MTX_WIDTH, 8);
	memcpy(send_fbuf + 49,  next_fbuf + 3 *  MTX_WIDTH, 8);
	memcpy(send_fbuf + 65,  next_fbuf + 4 *  MTX_WIDTH, 8);
	memcpy(send_fbuf + 81,  next_fbuf + 5 *  MTX_WIDTH, 8);
	memcpy(send_fbuf + 97,  next_fbuf + 6 *  MTX_WIDTH, 8);
	memcpy(send_fbuf + 113, next_fbuf + 7 *  MTX_WIDTH, 8);
	memcpy(send_fbuf + 129, next_fbuf + 8 *  MTX_WIDTH, 8);
	memcpy(send_fbuf + 9,   next_fbuf + 9 *  MTX_WIDTH, 8);
	memcpy(send_fbuf + 25,  next_fbuf + 10 * MTX_WIDTH, 8);
	memcpy(send_fbuf + 41,  next_fbuf + 11 * MTX_WIDTH, 8);
	memcpy(send_fbuf + 57,  next_fbuf + 12 * MTX_WIDTH, 8);
	memcpy(send_fbuf + 73,  next_fbuf + 13 * MTX_WIDTH, 8);
	memcpy(send_fbuf + 89,  next_fbuf + 14 * MTX_WIDTH, 8);
	memcpy(send_fbuf + 105, next_fbuf + 15 * MTX_WIDTH, 8);
	memcpy(send_fbuf + 121, next_fbuf + 16 * MTX_WIDTH, 8);
	memcpy(send_fbuf + 137, next_fbuf + 17 * MTX_WIDTH, 8);
}

int clear_fbuf(){
	// Clear the frame buffers that the matrix uses
	memset(fbuf0, 0, 144);
	memset(fbuf1, 0, 144);
	memset(send_fbuf, 0, 145);
	// Set the first address of the frame buffer to the address of the first
	// PWM register. This makes transmitting easier
	send_fbuf[0] = MTX_FBUF_ADDR;
	return MTX_OK;
}

