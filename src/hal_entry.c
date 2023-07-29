#include "hal_data.h"
#include <stdio.h>
#include "my_entry.h"
#include "utils.h"
#include "i2c.h"

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);

FSP_CPP_FOOTER



static fsp_err_t err = FSP_SUCCESS;
volatile bool uart_send_complete_flag = false;

void user_uart_callback(uart_callback_args_t *p_args) {
    if (p_args->event == UART_EVENT_TX_COMPLETE) {
        uart_send_complete_flag = true;
    }
}

//#ifdef __GNUC__                                 //串口重定向
//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//#endif

PUTCHAR_PROTOTYPE {
    err = R_SCI_UART_Write(&g_uart9_ctrl, (uint8_t *) &ch, 1);
    if (FSP_SUCCESS != err)
        __BKPT();
    while (uart_send_complete_flag == false) {
    }
    uart_send_complete_flag = false;
    return ch;
}

//int _write(int fd, char *pBuffer, int size) {
//    for (int i = 0; i < size; i++) {
//        __io_putchar(*pBuffer++);
//    }
//    return size;
//}

/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void) {
    /* Open the transfer instance with initial configuration. */
    err = R_SCI_UART_Open(&g_uart9_ctrl, &g_uart9_cfg);
    assert(FSP_SUCCESS == err);
    I2C_Init();
    printf("Hi, Renesas entry!\n");
//    i2c_detect();
    my_entry();

#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event) {
    if (BSP_WARM_START_RESET == event) {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

    if (BSP_WARM_START_POST_C == event) {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open(&g_ioport_ctrl, g_ioport.p_cfg);
    }
}

#if BSP_TZ_SECURE_BUILD

FSP_CPP_HEADER
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
FSP_CPP_FOOTER

#endif