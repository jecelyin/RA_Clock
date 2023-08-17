/*
 * utils.h
 *
 *  Created on: 2023年7月22日
 *      Author: jecelyin
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "stdint.h"
#include "hal_data.h"

void delay_ms(uint32_t ms);
uint8_t pin_read(bsp_io_port_pin_t pin);

#endif /* UTILS_H_ */
