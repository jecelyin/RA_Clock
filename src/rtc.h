/*ds3231 driver header file - Reza Ebrahimi v1.0*/
#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include "driver_ds3231.h"

uint8_t rtc_init(void);
uint8_t rtc_get_time(ds3231_time_t *t);
uint8_t rtc_get_timestamp_time_zone(int8_t *zone);
uint8_t rtc_get_temperature(int16_t *raw, float *s);
uint8_t rtc_get_ascii_time(char *buf, uint8_t len);
uint8_t rtc_set_time(ds3231_time_t *t);
uint8_t rtc_get_alarm1(ds3231_time_t *t, ds3231_alarm1_mode_t *mode);
uint8_t rtc_set_alarm2(ds3231_time_t *t, ds3231_alarm2_mode_t mode);
uint8_t rtc_get_alarm2(ds3231_time_t *t, ds3231_alarm2_mode_t *mode);
uint8_t rtc_clear_alarm_flag(ds3231_alarm_t alarm);
uint8_t rtc_enable_alarm(ds3231_alarm_t alarm);
uint8_t rtc_disable_alarm(ds3231_alarm_t alarm);


uint8_t rtc_deinit(void);
#endif
