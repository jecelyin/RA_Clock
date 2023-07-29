/*DS3231 low level API - Reza Ebrahimi v1.0*/
#include "ds3231.h"
#include "i2c.h"

uint8_t buf2[2] = {0};
uint8_t buf8[8] = {0};

/*function to transmit one byte of data to register_address on ds3231 (device_address: 0X68)*/
void time_i2c_write_single(uint8_t device_address, uint8_t register_address, uint8_t *data_byte)
{
    buf2[0] = register_address;
    buf2[1] = *data_byte;
    I2C_Write(device_address, buf2, 2);
}

/*function to transmit an array of data to device_address, starting from start_register_address*/
void time_i2c_write_multi(uint8_t device_address, uint8_t start_register_address, uint8_t *data_array, uint8_t data_length)
{
    buf8[0] = start_register_address;
    memcpy(&buf8[1], data_array, data_length);
    I2C_Write(device_address, buf2, data_length + 1);
}

/*function to read one byte of data from register_address on ds3231*/
void time_i2c_read_single(uint8_t device_address, uint8_t register_address, uint8_t *data_byte)
{
    buf2[0] = register_address;
    I2C_Write(device_address, buf2, 1);
    I2C_Read(device_address, data_byte, 1);
}

/*function to read an array of data from device_address*/
void time_i2c_read_multi(uint8_t device_address, uint8_t start_register_address, uint8_t *data_array, uint8_t data_length)
{
    buf2[0] = start_register_address;
    I2C_Write(device_address, buf2, 1);
    I2C_Read(device_address, data_array, data_length);
}

/*function to initialize I2C peripheral in 100khz or 400khz*/
void ds3231_I2C_init()
{
}
