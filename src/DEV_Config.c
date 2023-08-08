/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
*----------------
* |	This version:   V2.0
* | Date        :   2018-10-30
* | Info        :
# ******************************************************************************
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

//extern SPI_HandleTypeDef hspi1;
void DEV_SPI_WriteByte(UBYTE value) {
//    HAL_SPI_Transmit(&hspi1, &value, 1, 1000);
    g_transfer_complete = false;
    err = R_SPI_Write(&g_spi0_ctrl, &value, 1, SPI_BIT_WIDTH_8_BITS);
    assert(FSP_SUCCESS == err);
    /* Wait for SPI_EVENT_TRANSFER_COMPLETE callback event. */
    while (g_transfer_complete == false) {
    }
}

int DEV_Module_Init(void) {
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
//	DEV_Digital_Write(EPD_PWR_PIN, 1);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    err = R_SPI_Open(&g_spi0_ctrl, &g_spi0_cfg);
    assert(FSP_SUCCESS == err);

    return 0;
}

void DEV_Module_Exit(void) {
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);

    //close 5V
//	DEV_Digital_Write(EPD_PWR_PIN, 0);
    DEV_Digital_Write(EPD_RST_PIN, 0);
}

bool DEV_Digital_Read(bsp_io_port_pin_t *pin) {
    bsp_io_level_t ret;
    R_IOPORT_PinRead(&g_ioport_ctrl, *pin, &ret);
    return ret == BSP_IO_LEVEL_HIGH;
}
