#include "conway.h"

int life(uint8_t x, uint8_t y){
	uint8_t x_end;
	uint8_t y_end;

	uint8_t x_start;
	uint8_t y_start;
	uint8_t neighbors = 0;
	// Set the bounds for looking for neighbors
	if(x == 0){
		x_start = x;
		x_end = x + 1;
	}
	else if(x == X_BND){
		x_start = X_BND - 1;
		x_end = x;
	}
	else{
		x_start = x - 1;
		x_end = x + 1;
	}
	if(y == 0){
		y_start = y;
		y_end = y + 1;
	}
	else if(y == Y_BND){
		y_start = Y_BND - 1;
		y_end = y;
	}
	else{
		y_start = y - 1;
		y_end = y + 1;
	}
	for(uint8_t y_index = y_start; y_index <= y_end; y_index++){
		for(uint8_t x_index = x_start; x_index <= x_end; x_index++){
			if((active_fbuf[y_index * MTX_WIDTH + x_index] != 0) &&
					!((x == x_index) && (y == y_index))){
				neighbors++;
			}
		}
	}
	// Any cell with less than 2 neighbors dies of loneliness
	if(active_fbuf[y * MTX_WIDTH + x] != 0 && neighbors < 2){
		return 0;
	}
	// Any living cell with 2 or 3 neighbors lives on to the next generation
	else if((active_fbuf[y * MTX_WIDTH + x] != 0) && (neighbors == 2 || neighbors == 3)){
		return 1;
	}
	// Any cell with more than 3 neighbors dies of overpopulation
	else if(active_fbuf[y * MTX_WIDTH + x] != 0 && neighbors > 3){
		return 0;
	}
	// Any dead cell with exactly three neighbors is born
	else if(active_fbuf[y * MTX_WIDTH + x] == 0 && neighbors == 3){
		return 1;
	}
	// MISRA
	else{
		return 0;
	}

}

void conway_demo(I2C_HandleTypeDef* hi2c){
	stop_conway = 0;
	// Seed Conway's game of life with a glider
	next_fbuf[0 * MTX_WIDTH + 1] = 0xFF;
	next_fbuf[1 * MTX_WIDTH + 2] = 0xFF;
	next_fbuf[2 * MTX_WIDTH + 0] = 0xFF;
	next_fbuf[2 * MTX_WIDTH + 1] = 0xFF;
	next_fbuf[2 * MTX_WIDTH + 2] = 0xFF;
	update_fbuf(hi2c);
	while (!stop_conway){
		for(uint8_t y = 0; y < 18; y++){
			for(uint8_t x = 0; x < 8; x++){
				if(life(x, y)){
					next_fbuf[y * MTX_WIDTH + x] = 0xFF;
				}
			}
		}
		HAL_Delay(100);
		update_fbuf(hi2c);
	}
}
