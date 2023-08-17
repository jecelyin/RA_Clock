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

//R_IOPORT_PortRead
uint8_t pin_read(bsp_io_port_pin_t pin) {
    bsp_io_level_t p_pin_value = BSP_IO_LEVEL_LOW;
    fsp_err_t err = R_IOPORT_PinRead(&g_ioport_ctrl, pin, &p_pin_value);
    assert(FSP_SUCCESS == err);
    return p_pin_value == BSP_IO_LEVEL_HIGH ? 1 : 0;
}