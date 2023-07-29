#ifndef _I2C_H
#define _I2C_H

#include "hal_data.h"
#include <stdbool.h>

void I2C_Init();
bool I2C_Write(uint8_t const addr, uint8_t * const data, uint16_t const length);
bool I2C_Write_Register(uint8_t const addr, uint8_t reg_address, uint8_t * const data, uint16_t const length);

bool I2C_Read(uint8_t const addr, uint8_t * const p_dest, uint16_t const length);
bool I2C_Read_Register(uint8_t const addr, uint8_t reg_address, uint8_t * const p_dest, uint16_t const length);
void i2c_detect();

#endif /* _I2C_H */
