/*
 * segment_led.c
 *
 *  Created on: Sep 15, 2023
 *      Author: HP
 */

#include"segment_led.h"
void display(const struct seven_led *led, GPIO_PinState a, GPIO_PinState b,
		GPIO_PinState c, GPIO_PinState d, GPIO_PinState e, GPIO_PinState f,
		GPIO_PinState g) {
	HAL_GPIO_WritePin(led->gpio, led->pin_a, a);
	HAL_GPIO_WritePin(led->gpio, led->pin_b, b);
	HAL_GPIO_WritePin(led->gpio, led->pin_c, c);
	HAL_GPIO_WritePin(led->gpio, led->pin_d, d);
	HAL_GPIO_WritePin(led->gpio, led->pin_e, e);
	HAL_GPIO_WritePin(led->gpio, led->pin_f, f);
	HAL_GPIO_WritePin(led->gpio, led->pin_g, g);
}
void display7SEG(const struct seven_led *led, unsigned short i) {
	switch (i) {
	case 0:
		display(led, 0, 0, 0, 0, 0, 0, 1);
		break;
	case 1:
		display(led, 1, 0, 0, 1, 1, 1, 1);
		break;
	case 2:
		display(led, 0, 0, 1, 0, 0, 1, 0);
		break;
	case 3:
		display(led, 0, 0, 0, 0, 1, 1, 0);
		break;
	case 4:
		display(led, 1, 0, 0, 1, 1, 0, 0);
		break;
	case 5:
		display(led, 0, 1, 0, 0, 1, 0, 0);
		break;
	case 6:
		display(led, 0, 1, 0, 0, 0, 0, 0);
		break;
	case 7:
		display(led, 0, 0, 0, 1, 1, 1, 1);
		break;
	case 8:
		display(led, 0, 0, 0, 0, 0, 0, 0);
		break;
	case 9:
		display(led, 0, 0, 0, 0, 1, 0, 0);
		break;
	default:
		display(led, 1, 1, 1, 1, 1, 1, 1);
	}
}
void init7SEG(struct seven_led *led, GPIO_TypeDef *gpio, uint16_t pin_a,
		uint16_t pin_b, uint16_t pin_c, uint16_t pin_d, uint16_t pin_e,
		uint16_t pin_f, uint16_t pin_g) {
	led->gpio = gpio;
	led->pin_a = pin_a;
	led->pin_b = pin_b;
	led->pin_c = pin_c;
	led->pin_d = pin_d;
	led->pin_e = pin_e;
	led->pin_f = pin_f;
	led->pin_g = pin_g;
}
