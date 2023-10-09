/*
 * led.h
 *
 *  Created on: Sep 28, 2023
 *      Author: HP
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "stm32f1xx_hal.h"
#include<stdint.h>
#include"software_timer.h"
#include<string.h>

extern const uint8_t chu_cai[208];

struct led8x8 {
	GPIO_TypeDef *gpio_col;
	uint16_t pin_c0;
	uint16_t pin_c1;
	uint16_t pin_c2;
	uint16_t pin_c3;
	uint16_t pin_c4;
	uint16_t pin_c5;
	uint16_t pin_c6;
	uint16_t pin_c7;
	GPIO_TypeDef *gpio_row;
	uint16_t pin_r0;
	uint16_t pin_r1;
	uint16_t pin_r2;
	uint16_t pin_r3;
	uint16_t pin_r4;
	uint16_t pin_r5;
	uint16_t pin_r6;
	uint16_t pin_r7;
	uint8_t cur_buffer[8];
	uint8_t nex_buffer[8];
	int index;
	unsigned short flat_update_nex_buf;
	unsigned short is_reset;

	unsigned short shift_for_space;
};
void scrollLED8x8(struct led8x8 *led, char *str);
void updateLED8x8(struct led8x8 *led, uint8_t index);
void initLED8x8(struct led8x8 *led, GPIO_TypeDef *gpio_col, uint16_t pin_c0,
		uint16_t pin_c1, uint16_t pin_c2, uint16_t pin_c3, uint16_t pin_c4,
		uint16_t pin_c5, uint16_t pin_c6, uint16_t pin_c7,
		GPIO_TypeDef *gpio_row, uint16_t pin_r0, uint16_t pin_r1,
		uint16_t pin_r2, uint16_t pin_r3, uint16_t pin_r4, uint16_t pin_r5,
		uint16_t pin_r6, uint16_t pin_r7, char *str);
struct seven_led {
	GPIO_TypeDef *gpio;
	uint16_t pin_a;
	uint16_t pin_b;
	uint16_t pin_c;
	uint16_t pin_d;
	uint16_t pin_e;
	uint16_t pin_f;
	uint16_t pin_g;
};
void init7SEG(struct seven_led *led, GPIO_TypeDef *gpio, uint16_t pin_a,
		uint16_t pin_b, uint16_t pin_c, uint16_t pin_d, uint16_t pin_e,
		uint16_t pin_f, uint16_t pin_g);
void display7SEG(const struct seven_led *led, unsigned short i);

#endif /* INC_LED_H_ */
