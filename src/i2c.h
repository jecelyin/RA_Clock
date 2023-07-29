#ifndef _I2C_H
#define _I2C_H

#include "hal_data.h"
#include <stdbool.h>

void I2C_Init();
bool I2C_Write(uint32_t const addr, uint8_t * const data, uint32_t const length);
bool I2C_Read(uint32_t const addr, uint8_t * const p_dest, uint32_t const length);
void i2c_detect();

#endif /* _I2C_H */
