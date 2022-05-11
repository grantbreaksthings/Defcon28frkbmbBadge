#include "img.h"

void draw_image(struct img* image){
	for(uint8_t y = 0; y < image->height; y++){
		for(uint8_t x = 0; x < image->width; x++){
			next_fbuf[((y + image->y) * MTX_WIDTH) + (x + image->x)] =  image->bitmap[(y * image->width) + x];
		}
	}
}
