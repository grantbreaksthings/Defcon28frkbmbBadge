#include "doggo.h"

const uint8_t eye_bmp[42] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
		0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
		0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
		0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
		0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

const uint8_t pupil_bmp[1] = {0xFF};


const uint8_t mouth_bmp[28] = {
		0x00, 0x00, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x00, 0xFF,
		0x00, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0xFF,
};
int doggo_demo(I2C_HandleTypeDef* hi2c){
	struct img left_dog_eye;
	left_dog_eye.bitmap = eye_bmp;
	left_dog_eye.width = 6;
	left_dog_eye.height = 7;
	left_dog_eye.x = 0;
	left_dog_eye.y = 0;

	struct img right_dog_eye;
	right_dog_eye.bitmap = eye_bmp;
	right_dog_eye.width = 6;
	right_dog_eye.height = 7;
	right_dog_eye.x = 0;
	right_dog_eye.y = 9;

	struct img left_dog_pupil;
	left_dog_pupil.bitmap = pupil_bmp;
	left_dog_pupil.width = 1;
	left_dog_pupil.height = 1;
	left_dog_pupil.x = 2;
	left_dog_pupil.y = 3;

	struct img right_dog_pupil;
	right_dog_pupil.bitmap = pupil_bmp;
	right_dog_pupil.width = 1;
	right_dog_pupil.height = 1;
	right_dog_pupil.x = 2;
	right_dog_pupil.y = 12;

	struct img dog_mouth;
	dog_mouth.bitmap = mouth_bmp;
	dog_mouth.width = 4;
	dog_mouth.height = 7;
	dog_mouth.x = 4;
	dog_mouth.y = 5;

	// Goes to +-8000 on its side
	int16_t x = 0;
	int16_t y = 0;
	int16_t z = 0;

	while(1){
		x = get_x(hi2c);
		y = get_y(hi2c);
		z = get_z(hi2c);
		if(y > 4000){
			right_dog_pupil.y = 14;
			left_dog_pupil.y = 5;
		}
		if(y < 4000 && y > 2000){
			right_dog_pupil.y = 13;
			left_dog_pupil.y = 4;
		}
		if(y < 2000 && y < -2000){
			right_dog_pupil.y = 12;
			left_dog_pupil.y = 3;
		}
		if(y < -2000 && y > -4000){
			right_dog_pupil.y = 11;
			left_dog_pupil.y = 2;
		}
		if(-4000 > y){
			right_dog_pupil.y = 10;
			left_dog_pupil.y = 21;
		}
		draw_image(&left_dog_eye);
		draw_image(&right_dog_eye);
		draw_image(&left_dog_pupil);
		draw_image(&right_dog_pupil);
		draw_image(&dog_mouth);
		update_fbuf(hi2c);
	}
}
