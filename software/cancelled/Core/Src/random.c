#include "random.h"

uint8_t u8gen_rand(){
	seed = (A * seed) % M;
	return (M/seed) % 255;
}
void seed_rng(uint32_t new_seed){
	seed = new_seed;
}
