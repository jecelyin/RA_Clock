/*****************************************************************************
* | File      	:   DEV_Config.h
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-02-19
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include "hal_data.h"
#include <stdint.h>
#include <stdio.h>
#include "utils.h"

/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * GPIO config
**/
#define EPD_RST_PIN     BSP_IO_PORT_00_PIN_14
#define EPD_DC_PIN      BSP_IO_PORT_00_PIN_12
#define EPD_CS_PIN      BSP_IO_PORT_00_PIN_13
#define EPD_BUSY_PIN    SPI_BUSY

/**
 * GPIO read and write
**/
#define HIGH 1
#define LOW  0
//#define DEV_Digital_Write(_pin, _value) digitalWrite(_pin, _value == 0? LOW:HIGH)
#define DEV_Digital_Read(_pin) pin_read(_pin)
#define DEV_Digital_Write(_pin, _value)  \
    R_IOPORT_PinWrite(&g_ioport_ctrl, _pin, _value == 0 ? BSP_IO_LEVEL_LOW : BSP_IO_LEVEL_HIGH)
/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms) R_BSP_SoftwareDelay(__xms, BSP_DELAY_UNITS_MILLISECONDS)

/*------------------------------------------------------------------------------------------------------*/
UBYTE DEV_Module_Init(void);
void DEV_SPI_WriteByte(UBYTE data);

#endif
