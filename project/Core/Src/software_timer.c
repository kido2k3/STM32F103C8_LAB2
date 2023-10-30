/*
 * software_timer.c
 *
 *  Created on: Sep 20, 2023
 *      Author: HP
 */

#include"software_timer.h"
void set_timer(struct s_timer *timer, const unsigned long time) {
	timer->time = time;
	timer->st = 1;
}
void run_timer(struct s_timer *timer) {
	if (timer->time > 0) {
		timer->time--;
		if (timer->time < 1) {
			timer->st = 0;
		}
	}
}

