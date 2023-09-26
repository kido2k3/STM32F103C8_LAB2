/*
 * segment_led.h
 *
 *  Created on: Sep 15, 2023
 *      Author: HP
 */

#ifndef SEGMENT_LED_H_
#define SEGMENT_LED_H_

#include <stdint.h>
#include "main.h"
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
#endif /* SEGMENT_LED_H_ */
