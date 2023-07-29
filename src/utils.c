/*
 * utils.c
 *
 *  Created on: 2023年7月22日
 *      Author: jecelyin
 */

#include <stdio.h>
#include "utils.h"
#include "hal_data.h"
#include "i2c.h"

/**
 * This function provides minimum delay_ms (in milliseconds) based on variable incremented.
 * @param ms
 */
void delay_ms(uint32_t ms) {
    R_BSP_SoftwareDelay(ms, BSP_DELAY_UNITS_MILLISECONDS);
}
