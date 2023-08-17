/*****************************************************************************
* | File      	:   DEV_Config.c
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
#include "DEV_Config.h"

static volatile bool g_transfer_complete = false;
static fsp_err_t err = FSP_SUCCESS;

void spi_callback(spi_callback_args_t * p_args) {
    if (p_args->event == SPI_EVENT_TRANSFER_COMPLETE) {
        g_transfer_complete = true;
    } else {
        __BKPT(0);
    }
}

void GPIO_Config(void)
{
//    pinMode(EPD_BUSY_PIN,  INPUT);
//    pinMode(EPD_RST_PIN , OUTPUT);
//    pinMode(EPD_DC_PIN  , OUTPUT);
//    pinMode(EPD_CS_PIN , OUTPUT);

//    digitalWrite(EPD_CS_PIN , HIGH);
    DEV_Digital_Write(EPD_CS_PIN , HIGH);
}
/******************************************************************************
function:	Module Initialize, the BCM2835 library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_Module_Init(void)
{
	//gpio
	GPIO_Config();

	//serial printf
//	Serial.begin(115200);
	
	// spi
//	SPI.begin();
    err = R_SPI_Open(&g_spi0_ctrl, &g_spi0_cfg);
    assert(FSP_SUCCESS == err);
	return 0;
}

/******************************************************************************
function:
			SPI read and write
******************************************************************************/
void DEV_SPI_WriteByte(UBYTE data)
{
//    SPI.transfer(data);
    g_transfer_complete = false;
    err = R_SPI_Write(&g_spi0_ctrl, &data, 1, SPI_BIT_WIDTH_8_BITS);
    assert(FSP_SUCCESS == err);
    /* Wait for SPI_EVENT_TRANSFER_COMPLETE callback event. */
    while (g_transfer_complete == false) {
    }
}
