/*
 * flash_smg.c
 *
 *  Created on: 2023年7月5日
 *      Author: a8456
 */
#include "flash_smg.h"

volatile bool interrupt_called;
volatile flash_event_t flash_event;


void flash_callback(flash_callback_args_t *p_args) {
    interrupt_called = true;
    flash_event = p_args->event;
}


static fsp_err_t err;
static void WriteFlash(uint8_t Data[], uint32_t data_length);

// DS3231 --------------------------------
// seconds (time_set[0]), minutes, hours, day of the week, date, month and year (time_set[6])
uint8_t time_set[7] = {0, 10, 13, 5, 25, 1, 21};
//array of 7 bytes to refresh time values from ds3231
uint8_t time_current[7] = {0};

/*FLASH写入程序*/
void SaveTimeFlash() {
    WriteFlash(time_set, 7);
}

static void WriteFlash(uint8_t Data[], uint32_t data_length) {
    uint32_t addr = FLASH_DF_BLOCK_0;

    interrupt_called = false;
    /* Erase 1 block of data flash starting at block 0. */
    err = R_FLASH_LP_Erase(&g_flash0_ctrl, FLASH_DF_BLOCK_0, 1);
    assert(FSP_SUCCESS == err);
    while (!interrupt_called) { ;
    }
    assert(FLASH_EVENT_ERASE_COMPLETE == flash_event);
    interrupt_called = false;
    flash_status_t status;
    /* Write 32 bytes to the first block of data flash. */
    err = R_FLASH_LP_Write(&g_flash0_ctrl, (uint32_t) Data, addr, data_length);
    assert(FSP_SUCCESS == err);

    /* Wait until the current flash operation completes. */
    do {
        err = R_FLASH_LP_StatusGet(&g_flash0_ctrl, &status);
    } while ((FSP_SUCCESS == err) && (FLASH_STATUS_BUSY == status));


    /* If the interrupt wasn't called process the error. */
    assert(interrupt_called);
    /* If the event wasn't a write complete process the error. */
    assert(FLASH_EVENT_WRITE_COMPLETE == flash_event);
    /* Verify the data was written correctly. */
    assert(0 == memcmp(Data, (uint8_t *) FLASH_DF_BLOCK_0, data_length));


}

/*FLASH读取打印程序*/
void ReadTimeFlash() {
    uint32_t addr = FLASH_DF_BLOCK_0;
// seconds (time_set[0]), minutes, hours, day of the week, date, month and year (time_set[6])
    time_set[TIME_SEC] = *(__IO uint8_t *) (addr);
    time_set[TIME_MIN] = *(__IO uint8_t *) (addr + 1);
    time_set[TIME_HOUR] = *(__IO uint8_t *) (addr + 2);
    time_set[TIME_DAY] = *(__IO uint8_t *) (addr + 3);
    time_set[TIME_DATE] = *(__IO uint8_t *) (addr + 4);
    time_set[TIME_MONTH] = *(__IO uint8_t *) (addr + 5);
    time_set[TIME_YEAR] = *(__IO uint8_t *) (addr + 6);

    if (time_set[TIME_HOUR] >= 24)
        time_set[TIME_HOUR] = 0;
    if (time_set[TIME_MIN] >= 60)
        time_set[TIME_MIN] = 0;
    if (time_set[TIME_SEC] >= 60)
        time_set[TIME_SEC] = 0;
}



