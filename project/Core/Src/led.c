/*
 * led.c
 *
 *  Created on: Sep 28, 2023
 *      Author: HP
 */

#include "led.h"
uint8_t cur_buffer[8] = { };
uint8_t nex_buffer[8] = { };
const uint8_t chu_cai[208] = { 0x18, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, //A
		0x7c, 0x42, 0x42, 0x7c, 0x42, 0x42, 0x42, 0x7c, //B
		0x3c, 0x42, 0x40, 0x40, 0x40, 0x40, 0x42, 0x3c, //C
		0x78, 0x44, 0x42, 0x42, 0x42, 0x42, 0x44, 0x78, //D
		0x7e, 0x40, 0x40, 0x7e, 0x40, 0x40, 0x40, 0x7e, //E
		0x7e, 0x40, 0x40, 0x7e, 0x40, 0x40, 0x40, 0x40, //F
		0x38, 0x44, 0x40, 0x40, 0x4e, 0x44, 0x44, 0x38, //G
		0x42, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 0x42, //H
		0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, //I
		0x7e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x48, 0x30, //J
		0x42, 0x44, 0x48, 0x70, 0x70, 0x48, 0x44, 0x42, //K
		0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7e, //L
		0x42, 0x66, 0x5a, 0x5a, 0x42, 0x42, 0x42, 0x42, //M
		0x42, 0x62, 0x72, 0x7a, 0x5e, 0x4e, 0x46, 0x42, //N
		0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c, //O
		0x7c, 0x42, 0x42, 0x42, 0x7c, 0x40, 0x40, 0x40, //P
		0x18, 0x24, 0x42, 0x42, 0x42, 0x4a, 0x24, 0x1a, //Q
		0x78, 0x44, 0x44, 0x78, 0x70, 0x48, 0x44, 0x42, //R
		0x3c, 0x42, 0x40, 0x30, 0x18, 0x06, 0x42, 0x3c, //S
		0x7e, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, //T
		0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c, //U
		0x42, 0x42, 0x42, 0x42, 0x42, 0x66, 0x3c, 0x18, //V
		0x42, 0x42, 0x42, 0x42, 0x5a, 0x5a, 0x66, 0x42, //W
		0x42, 0x66, 0x24, 0x18, 0x18, 0x24, 0x66, 0x42, //X
		0x42, 0x42, 0x42, 0x24, 0x18, 0x18, 0x18, 0x18, //Y
		0x7e, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x7e //Z
		};
void initLED8x8(struct led8x8 *led, GPIO_TypeDef *gpio_col, uint16_t pin_c0,
		uint16_t pin_c1, uint16_t pin_c2, uint16_t pin_c3, uint16_t pin_c4,
		uint16_t pin_c5, uint16_t pin_c6, uint16_t pin_c7,
		GPIO_TypeDef *gpio_row, uint16_t pin_r0, uint16_t pin_r1,
		uint16_t pin_r2, uint16_t pin_r3, uint16_t pin_r4, uint16_t pin_r5,
		uint16_t pin_r6, uint16_t pin_r7, char *str) {
	led->gpio_col = gpio_col;
	led->gpio_row = gpio_row;
	led->pin_c0 = pin_c0;
	led->pin_c1 = pin_c1;
	led->pin_c2 = pin_c2;
	led->pin_c3 = pin_c3;
	led->pin_c4 = pin_c4;
	led->pin_c5 = pin_c5;
	led->pin_c6 = pin_c6;
	led->pin_c7 = pin_c7;
	led->pin_r0 = pin_r0;
	led->pin_r1 = pin_r1;
	led->pin_r2 = pin_r2;
	led->pin_r3 = pin_r3;
	led->pin_r4 = pin_r4;
	led->pin_r5 = pin_r5;
	led->pin_r6 = pin_r6;
	led->pin_r7 = pin_r7;
	led->index = 0;
	led->flat_update_nex_buf = 1;
	led->is_reset = 0;
	unsigned len = strlen(str);
	if (len > 0) {
		memcpy(led->cur_buffer, chu_cai + (str[led->index++] - 65) * 8,
				sizeof(led->cur_buffer));
		if (led->index >= len)
			led->index = 0;
	}
	if (len > 1) {
		memcpy(led->nex_buffer, chu_cai + (str[led->index++] - 65) * 8,
				sizeof(led->nex_buffer));
		if (led->index >= len)
			led->index = 0;
		for (int i = 0; i < 8; i++)
			led->nex_buffer[i] <<= 1;
	}

}
void shift_once(struct led8x8 *led, unsigned int str_len, char c) {
	if (c == ' ' || led->is_reset == 2) {
		led->shift_for_space++;
	}
	for (int i = 0; i < 8; i++) {
		led->cur_buffer[i] = (led->cur_buffer[i] << 1);
		if (0 < led->shift_for_space && led->shift_for_space < 5) {
		} else {
			led->cur_buffer[i] = led->cur_buffer[i] | (led->nex_buffer[i] >> 7);
			led->nex_buffer[i] <<= 1;
		}
		if (led->nex_buffer[i] != 0) {
			led->flat_update_nex_buf = 0;
		}
	}

}
void scrollLED8x8(struct led8x8 *led, char *str) {
	shift_once(led, strlen(str), str[(led->index > 1) ? led->index - 2 : 0]);
	if (led->flat_update_nex_buf) {
		while(str[led->index]<'A'||str[led->index]>'Z')led->index++;
		memcpy(led->nex_buffer, chu_cai + (str[led->index++] - 65) * 8,
				sizeof(led->nex_buffer));
		if (led->index >= strlen(str)){
			led->is_reset = 1;
			led->index = 0;
		}
		if(led->index == 1 && led->is_reset == 1)led->is_reset = 2;
		if(led->index != 1 && led->is_reset == 2)led->is_reset = 0;

		led->shift_for_space = 0;
	}
	led->flat_update_nex_buf = 1;
}
void OffAllLed(struct led8x8 *led) {
	uint16_t pin = led->pin_r0 | led->pin_r1 | led->pin_r2 | led->pin_r3
			| led->pin_r4 | led->pin_r5 | led->pin_r6 | led->pin_r7;
	HAL_GPIO_WritePin(led->gpio_row, pin, 0);
}
void OnColunm(struct led8x8 *led, uint8_t buffer) {
	uint8_t mask = 0x01; // 0000 0001
	for (int i = 7; i >= 0; i--) {
		switch (i) {
		case 0:
			HAL_GPIO_WritePin(led->gpio_col, led->pin_c7,
					!!(mask << i & buffer));
			break;
		case 1:
			HAL_GPIO_WritePin(led->gpio_col, led->pin_c6,
					!!(mask << i & buffer));
			break;
		case 2:
			HAL_GPIO_WritePin(led->gpio_col, led->pin_c5,
					!!(mask << i & buffer));
			break;
		case 3:
			HAL_GPIO_WritePin(led->gpio_col, led->pin_c4,
					!!(mask << i & buffer));
			break;
		case 4:
			HAL_GPIO_WritePin(led->gpio_col, led->pin_c3,
					!!(mask << i & buffer));
			break;
		case 5:
			HAL_GPIO_WritePin(led->gpio_col, led->pin_c2,
					!!(mask << i & buffer));
			break;
		case 6:
			HAL_GPIO_WritePin(led->gpio_col, led->pin_c1,
					!!(mask << i & buffer));
			break;
		default:
			HAL_GPIO_WritePin(led->gpio_col, led->pin_c0,
					!!(mask << i & buffer));
		}
	}
}
void updateLED8x8(struct led8x8 *led, uint8_t index) {
	OffAllLed(led);
	switch (index) {
	case 0:
		HAL_GPIO_WritePin(led->gpio_row, led->pin_r0, 1);
		OnColunm(led, led->cur_buffer[index]);
		break;
	case 1:
		HAL_GPIO_WritePin(led->gpio_row, led->pin_r1, 1);
		OnColunm(led, led->cur_buffer[index]);
		break;
	case 2:
		HAL_GPIO_WritePin(led->gpio_row, led->pin_r2, 1);
		OnColunm(led, led->cur_buffer[index]);
		break;
	case 3:
		HAL_GPIO_WritePin(led->gpio_row, led->pin_r3, 1);
		OnColunm(led, led->cur_buffer[index]);
		break;
	case 4:
		HAL_GPIO_WritePin(led->gpio_row, led->pin_r4, 1);
		OnColunm(led, led->cur_buffer[index]);
		break;
	case 5:
		HAL_GPIO_WritePin(led->gpio_row, led->pin_r5, 1);
		OnColunm(led, led->cur_buffer[index]);
		break;
	case 6:
		HAL_GPIO_WritePin(led->gpio_row, led->pin_r6, 1);
		OnColunm(led, led->cur_buffer[index]);
		break;
	case 7:
		HAL_GPIO_WritePin(led->gpio_row, led->pin_r7, 1);
		OnColunm(led, led->cur_buffer[index]);
		break;
	default:
		break;
	}
}

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
