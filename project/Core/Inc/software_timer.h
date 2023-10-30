/*
 * software_timer.h
 *
 *  Created on: Sep 20, 2023
 *      Author: HP
 */

#ifndef MYLIB_SOFTWARE_TIMER_H_
#define MYLIB_SOFTWARE_TIMER_H_
#include<stdint.h>
struct s_timer {
	uint8_t st;
	unsigned long time;
};
void set_timer(struct s_timer* timer, const unsigned long time);
void run_timer(struct s_timer* timer);


#endif /* MYLIB_SOFTWARE_TIMER_H_ */
