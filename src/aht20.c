#include "aht20.h"
#include "i2c.h"
#include "utils.h"
#include "stdio.h"

/**
 * https://github.com/kpierzynski/AVR_aht20/blob/master/src/aht20.c
 */

aht20_t aht20;
uint8_t triggered = 0;

#if CRC_TYPE == CRC_SAVE_CPU
static const uint8_t crc_lookup[] PROGMEM = {
0x00, 0x31, 0x62, 0x53, 0xC4, 0xF5, 0xA6, 0x97, 0xB9, 0x88, 0xDB, 0xEA, 0x7D, 0x4C, 0x1F, 0x2E,
0x43, 0x72, 0x21, 0x10, 0x87, 0xB6, 0xE5, 0xD4, 0xFA, 0xCB, 0x98, 0xA9, 0x3E, 0x0F, 0x5C, 0x6D,
0x86, 0xB7, 0xE4, 0xD5, 0x42, 0x73, 0x20, 0x11, 0x3F, 0x0E, 0x5D, 0x6C, 0xFB, 0xCA, 0x99, 0xA8,
0xC5, 0xF4, 0xA7, 0x96, 0x01, 0x30, 0x63, 0x52, 0x7C, 0x4D, 0x1E, 0x2F, 0xB8, 0x89, 0xDA, 0xEB,
0x3D, 0x0C, 0x5F, 0x6E, 0xF9, 0xC8, 0x9B, 0xAA, 0x84, 0xB5, 0xE6, 0xD7, 0x40, 0x71, 0x22, 0x13,
0x7E, 0x4F, 0x1C, 0x2D, 0xBA, 0x8B, 0xD8, 0xE9, 0xC7, 0xF6, 0xA5, 0x94, 0x03, 0x32, 0x61, 0x50,
0xBB, 0x8A, 0xD9, 0xE8, 0x7F, 0x4E, 0x1D, 0x2C, 0x02, 0x33, 0x60, 0x51, 0xC6, 0xF7, 0xA4, 0x95,
0xF8, 0xC9, 0x9A, 0xAB, 0x3C, 0x0D, 0x5E, 0x6F, 0x41, 0x70, 0x23, 0x12, 0x85, 0xB4, 0xE7, 0xD6,
0x7A, 0x4B, 0x18, 0x29, 0xBE, 0x8F, 0xDC, 0xED, 0xC3, 0xF2, 0xA1, 0x90, 0x07, 0x36, 0x65, 0x54,
0x39, 0x08, 0x5B, 0x6A, 0xFD, 0xCC, 0x9F, 0xAE, 0x80, 0xB1, 0xE2, 0xD3, 0x44, 0x75, 0x26, 0x17,
0xFC, 0xCD, 0x9E, 0xAF, 0x38, 0x09, 0x5A, 0x6B, 0x45, 0x74, 0x27, 0x16, 0x81, 0xB0, 0xE3, 0xD2,
0xBF, 0x8E, 0xDD, 0xEC, 0x7B, 0x4A, 0x19, 0x28, 0x06, 0x37, 0x64, 0x55, 0xC2, 0xF3, 0xA0, 0x91,
0x47, 0x76, 0x25, 0x14, 0x83, 0xB2, 0xE1, 0xD0, 0xFE, 0xCF, 0x9C, 0xAD, 0x3A, 0x0B, 0x58, 0x69,
0x04, 0x35, 0x66, 0x57, 0xC0, 0xF1, 0xA2, 0x93, 0xBD, 0x8C, 0xDF, 0xEE, 0x79, 0x48, 0x1B, 0x2A,
0xC1, 0xF0, 0xA3, 0x92, 0x05, 0x34, 0x67, 0x56, 0x78, 0x49, 0x1A, 0x2B, 0xBC, 0x8D, 0xDE, 0xEF,
0x82, 0xB3, 0xE0, 0xD1, 0x46, 0x77, 0x24, 0x15, 0x3B, 0x0A, 0x59, 0x68, 0xFF, 0xCE, 0x9D, 0xAC
};
#endif

uint8_t buf1[1] = {0};
uint8_t send_buf[3] = {0};
uint8_t buf7[7] = {0};

static void aht20_send_full_command( uint8_t cmd, uint8_t param1, uint8_t param2 ) {
//	i2c_start();
//	i2c_write(AHT20_ADDRESS << 1 | I2C_WRITE);
//	i2c_write(cmd);
//	i2c_write(param1);
//	i2c_write(param2);
//	i2c_stop();
    send_buf[0] = cmd;
    send_buf[1] = param1;
    send_buf[2] = param2;
    I2C_Write(AHT20_ADDRESS, send_buf, 3);
}

static void aht20_send_cmd( uint8_t cmd ) {
//	i2c_start();
//	i2c_write(AHT20_ADDRESS << 1 | I2C_WRITE);
//	i2c_write(cmd);
//	i2c_stop();
    buf1[0] = cmd;
	if (!I2C_Write(AHT20_ADDRESS, buf1, 1)) {
		printf("AHT20 send command failure!\n");
	}
}

static uint8_t aht20_read_cmd() {
//	i2c_start();
//	i2c_write(AHT20_ADDRESS << 1 | I2C_READ);
//	register uint8_t read = i2c_read(I2C_NACK);
//	i2c_stop();
    buf1[0] = 0;
    I2C_Read(AHT20_ADDRESS, buf1, 1);

    return buf1[0];
}

void aht20_init() {
	delay_ms(AHT20_AFTER_POWER_ON_DELAY);
	aht20_send_cmd(AHT20_SOFT_RESET_CMD);
	delay_ms(AHT20_DELAY);

	aht20_send_cmd(AHT20_STATUS_WORD);
	uint8_t status_word = aht20_read_cmd();

	if( !(status_word & AHT20_CAL) ) {
		aht20_send_full_command(AHT20_INIT_CMD, AHT20_INIT_PARAM_1, AHT20_INIT_PARAM_2);
		delay_ms(AHT20_AFTER_POWER_ON_DELAY);
	}
}

static void (*aht20_read_event_callback)(int8_t temperature, uint8_t humidity, enum AHT20_STATUS status);

void register_aht20_event_callback(void (*callback)(int8_t temperature, uint8_t humidity, enum AHT20_STATUS status)) {
        aht20_read_event_callback = callback;
}

#if CRC_TYPE == CRC_SAVE_SPACE

static uint8_t crc(uint8_t *data, uint8_t len)
{
    uint8_t crc = 0xff;
    uint8_t i, j;
    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (j = 0; j < 8; j++) {
            if ((crc & 0x80) != 0)
                crc = (uint8_t)((crc << 1) ^ 0x31);
            else
                crc <<= 1;
        }
    }
    return crc;
}

#else

static uint8_t crc(uint8_t *data, uint8_t len) {
	register uint8_t crc = 0xFF;
	while(len--) {
			crc = pgm_read_byte(crc_lookup + (crc ^ *data++));
	}
	return crc;
}

#endif

static uint8_t aht20_read() {
//	i2c_start();
//	i2c_write(AHT20_ADDRESS << 1 | I2C_READ);
//	for( uint8_t i = 0; i < 7; i++ ) {
//		*( (uint8_t*)&aht20 + i ) = i2c_read( i == 6 ? I2C_NACK : I2C_ACK );
//	}
//	i2c_stop();
    memset(buf7, 0, 6);
    I2C_Read(AHT20_ADDRESS, buf7, 6);

	for( uint8_t i = 0; i < 7; i++ ) {
		*( (uint8_t*)&aht20 + i ) = buf7[i];
	}

//	if( crc( (uint8_t*)&aht20, 6 ) != aht20.crc ) {
//		return AHT20_CRC_FAIL;
//	}
	
	return AHT20_SUCCESS;
}

static int8_t aht20_get_temperature() {
	int32_t temp;
	temp = ( ((int32_t)aht20.data[2] & 0b00001111) << 16 ) | ((int32_t)aht20.data[3] << 8) | (aht20.data[4]);
	temp = ( (temp*25)>>17 ) - 50;
	return (int8_t)temp;
}

static uint8_t aht20_get_humidity() {
	int32_t hum;
	hum = ( (int32_t)aht20.data[0] << 12 ) | ((int32_t)aht20.data[1] << 4) | ( (aht20.data[2] & 0b11110000) >> 4 );
	hum = ((hum*25)>>18);
	return (uint8_t)hum;
}

void aht20_trigger_measurement() {
	aht20_send_full_command(AHT20_MEASURE_CMD, AHT20_MEASURE_PARAM_1, AHT20_MEASURE_PARAM_2);
	triggered = 1;
	delay_ms(AHT20_MEASURE_DELAY);
}

void aht20_event() {
	if( !triggered ) return;
    uint8_t ret = aht20_read_cmd();
    printf("aht20_read_cmd, ret=%d\n", ret);
	if( !(ret & 0x80) ) {
		enum AHT20_STATUS status = aht20_read();

		if( aht20_read_event_callback ) aht20_read_event_callback( aht20_get_temperature(), aht20_get_humidity(), status );
		triggered = 0;
	}
}

