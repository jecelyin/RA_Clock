/*DS3231 high level driver - Reza Ebrahimi v1.0*/
/**
 * https://github.com/hepingood/ds3231/blob/master/example/
 */
#include "rtc.h"
#include "driver_ds3231_interface.h"
#include "hal_data.h"

#define DS3231_BASIC_DEFAULT_AGING_OFFSET        0        /**< 0 offset */

static ds3231_handle_t gs_handle;        /**< ds3231 handle */
static int8_t gs_time_zone = 0;          /**< local zone */

uint8_t rtc_init(void)
{
    uint8_t res;
    int8_t reg;

    /* link functions */
    DRIVER_DS3231_LINK_INIT(&gs_handle, ds3231_handle_t);
    DRIVER_DS3231_LINK_IIC_INIT(&gs_handle, ds3231_interface_iic_init);
    DRIVER_DS3231_LINK_IIC_DEINIT(&gs_handle, ds3231_interface_iic_deinit);
    DRIVER_DS3231_LINK_IIC_READ(&gs_handle, ds3231_interface_iic_read);
    DRIVER_DS3231_LINK_IIC_WRITE(&gs_handle, ds3231_interface_iic_write);
    DRIVER_DS3231_LINK_DELAY_MS(&gs_handle, ds3231_interface_delay_ms);
    DRIVER_DS3231_LINK_DEBUG_PRINT(&gs_handle, ds3231_interface_debug_print);
    DRIVER_DS3231_LINK_RECEIVE_CALLBACK(&gs_handle, ds3231_interface_receive_callback);

    /* init ds3231 */
    res = ds3231_init(&gs_handle);
    if (res != 0)
    {
        ds3231_interface_debug_print("ds3231: init failed.\n");
        __BKPT(0);
        return 1;
    }

    /* set oscillator */
    res = ds3231_set_oscillator(&gs_handle, DS3231_BOOL_TRUE);
    if (res != 0)
    {
        ds3231_interface_debug_print("ds3231: set oscillator failed.\n");
        (void)ds3231_deinit(&gs_handle);
        __BKPT(0);
        return 1;
    }

    /* disable alarm1 */
    res = ds3231_set_alarm_interrupt(&gs_handle, DS3231_ALARM_1, DS3231_BOOL_FALSE);
    if (res != 0)
    {
        ds3231_interface_debug_print("ds3231: set alarm1 interrupt failed.\n");
        (void)ds3231_deinit(&gs_handle);
        __BKPT(0);
        return 1;
    }

    /* disable alarm2 */
    res = ds3231_set_alarm_interrupt(&gs_handle, DS3231_ALARM_2, DS3231_BOOL_FALSE);
    if (res != 0)
    {
        ds3231_interface_debug_print("ds3231: set alarm2 interrupt failed.\n");
        (void)ds3231_deinit(&gs_handle);
        __BKPT(0);
        return 1;
    }

    /* set square wave */
    res = ds3231_set_pin(&gs_handle, DS3231_PIN_SQUARE_WAVE);
    if (res != 0)
    {
        ds3231_interface_debug_print("ds3231: set pin failed.\n");
        (void)ds3231_deinit(&gs_handle);
        __BKPT(0);
        return 1;
    }

    /* disable square wave */
    res = ds3231_set_square_wave(&gs_handle, DS3231_BOOL_FALSE);
    if (res != 0)
    {
        ds3231_interface_debug_print("ds3231: set square wave failed.\n");
        (void)ds3231_deinit(&gs_handle);
        __BKPT(0);
        return 1;
    }

    /* disable 32khz output */
    res = ds3231_set_32khz_output(&gs_handle, DS3231_BOOL_FALSE);
    if (res != 0)
    {
        ds3231_interface_debug_print("ds3231: set 32khz output failed.\n");
        (void)ds3231_deinit(&gs_handle);
        __BKPT(0);
        return 1;
    }

    /* convert to register */
    res = ds3231_aging_offset_convert_to_register(&gs_handle, DS3231_BASIC_DEFAULT_AGING_OFFSET, (int8_t *)&reg);
    if (res != 0)
    {
        ds3231_interface_debug_print("ds3231: convert to register failed.\n");
        (void)ds3231_deinit(&gs_handle);
        __BKPT(0);
        return 1;
    }

    /* set aging offset */
    res = ds3231_set_aging_offset(&gs_handle, reg);
    if (res != 0)
    {
        ds3231_interface_debug_print("ds3231: set aging offset failed.\n");
        (void)ds3231_deinit(&gs_handle);
        __BKPT(0);
        return 1;
    }

    return 0;
}

uint8_t rtc_get_time(ds3231_time_t *t)
{
    /* get time */
    if (ds3231_get_time(&gs_handle, t) != 0)
    {
        __BKPT(0);
        return 1;
    }
    else
    {
        return 0;
    }
}


/**
 * @brief      basic example get the local time zone
 * @param[out] *zone points to a local time zone buffer
 * @return     status code
 *             - 0 success
 * @note       none
 */
uint8_t rtc_get_timestamp_time_zone(int8_t *zone)
{
    *zone = gs_time_zone;

    return 0;
}

/**
 * @brief      basic example get the current temperature
 * @param[out] *raw points to a raw temperature buffer
 * @param[out] *s points to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 * @note       none
 */
uint8_t rtc_get_temperature(int16_t *raw, float *s)
{
    /* get temperature */
    if (ds3231_get_temperature(&gs_handle, raw, s) != 0)
    {
        __BKPT(0);
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief      basic example get the ascii time
 * @param[out] *buf points to an ascii buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t rtc_get_ascii_time(char *buf, uint8_t len)
{
    ds3231_time_t t;

    /* get time */
    if (ds3231_get_time(&gs_handle, &t) != 0)
    {
        __BKPT(0);
        return 1;
    }

    if (t.format == DS3231_FORMAT_24H)
    {
        (void)snprintf(buf, len, "%04d-%02d-%02d %02d:%02d:%02d %d.\n", t.year, t.month, t.date, t.hour, t.minute, t.second, t.week);
    }
    else
    {
        (void)snprintf(buf, len, "%04d-%02d-%02d %s %02d:%02d:%02d %d.\n", t.year, t.month, t.date, (t.am_pm == DS3231_AM) ? "AM" : "PM",
                       t.hour, t.minute, t.second, t.week
        );
    }

    return 0;
}

uint8_t rtc_deinit(void)
{
    if (ds3231_deinit(&gs_handle) != 0)
    {
        __BKPT(0);
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     basic example set the time
 * @param[in] *t points to a time structure
 * @return    status code
 *            - 0 success
 *            - 1 set time failed
 * @note      none
 */
uint8_t rtc_set_time(ds3231_time_t *t)
{
    /* set time */
    if (ds3231_set_time(&gs_handle, t) != 0)
    {
        __BKPT(0);
        return 1;
    }
    else
    {
        return 0;
    }
}


/**
 * @brief      alarm example get the alarm 1
 * @param[out] *t points to a time structure
 * @param[out] *mode points to a alarm 1 interrupt mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get alarm1 failed
 * @note       none
 */
uint8_t rtc_get_alarm1(ds3231_time_t *t, ds3231_alarm1_mode_t *mode)
{
    /* get alarm1 */
    if (ds3231_get_alarm1(&gs_handle, t, mode) != 0)
    {
        __BKPT(0);
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     alarm example set the alarm 2
 * @param[in] *t points to a time structure
 * @param[in] mode is the alarm 2 interrupt mode
 * @return    status code
 *            - 0 success
 *            - 1 set alarm2 failed
 * @note      none
 */
uint8_t rtc_set_alarm2(ds3231_time_t *t, ds3231_alarm2_mode_t mode)
{
    /* set alarm2 */
    if (ds3231_set_alarm2(&gs_handle, t, mode) != 0)
    {
        __BKPT(0);
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief      alarm example get the alarm 2
 * @param[out] *t points to a time structure
 * @param[out] *mode points to a alarm 2 interrupt mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get alarm2 failed
 * @note       none
 */
uint8_t rtc_get_alarm2(ds3231_time_t *t, ds3231_alarm2_mode_t *mode)
{
    /* get alarm2 */
    if (ds3231_get_alarm2(&gs_handle, t, mode) != 0)
    {
        __BKPT(0);
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     alarm clear the interrupt flag
 * @param[in] alarm is the alarm number
 * @return    status code
 *            - 0 success
 *            - 1 alarm clear failed
 * @note      none
 */
uint8_t rtc_clear_alarm_flag(ds3231_alarm_t alarm)
{
    /* alarm clear */
    if (ds3231_alarm_clear(&gs_handle, alarm) != 0)
    {
        __BKPT(0);
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     enable the alarm
 * @param[in] alarm is the alarm number
 * @return    status code
 *            - 0 success
 *            - 1 enable alarm failed
 * @note      none
 */
uint8_t rtc_enable_alarm(ds3231_alarm_t alarm)
{
    /* clear alarm flag */
    if (ds3231_alarm_clear(&gs_handle, alarm) != 0)
    {
        __BKPT(0);
        return 1;
    }

    /* enable alarm */
    if (ds3231_set_alarm_interrupt(&gs_handle, alarm, DS3231_BOOL_TRUE) != 0)
    {
        __BKPT(0);
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     disable the alarm
 * @param[in] alarm is the alarm number
 * @return    status code
 *            - 0 success
 *            - 1 disable alarm failed
 * @note      none
 */
uint8_t rtc_disable_alarm(ds3231_alarm_t alarm)
{
    /* disable alarm */
    if (ds3231_set_alarm_interrupt(&gs_handle, alarm, DS3231_BOOL_FALSE) != 0)
    {
        __BKPT(0);
        return 1;
    }
    else
    {
        return 0;
    }
}


