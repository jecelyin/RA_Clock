/*
 * app_entry.c
 *
 *  Created on: 2023年7月22日
 *      Author: jecelyin
 */

#include "app.h"
#include "utils.h"
#include "rtc.h"
#include "display.h"
#include "ui.h"
#include "timer.h"
#include "i2c.h"


//static fsp_err_t err = FSP_SUCCESS;

void app_entry() {
    printf("app entry start...\n");
    agt_timer_init();

    I2C_Init();
    printf("e-Paper Init and Clear...\n");
    display_init();

    /**********************data flash***************************************/
//    flash_result_t blank_check_result;
//    /* Open the flash lp instance. */
//    err = R_FLASH_LP_Open(&g_flash0_ctrl, &g_flash0_cfg);
//    assert(FSP_SUCCESS == err);

//    ReadTimeFlash();

    /*************************** DS3231 START **************************************/
    rtc_init();
    /*************************** DS3231 END **************************************/

    ui_init();
    while (1) {
        ui_update();
        R_BSP_SoftwareDelay(10U, BSP_DELAY_UNITS_MILLISECONDS);
    }

    rtc_deinit();
}
