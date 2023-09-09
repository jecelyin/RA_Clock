//
// Created by Jecelyin Peng on 2023/9/8.
//

#include "key_event.h"
#include "hal_data.h"
#include "timer.h"
#include "stdio.h"
#include "qe_touch_config.h"

#define KEY_SIZE    4
#define LONG_PRESS_TIME  500

struct key_pin_s {
    key_code_t code;
    enum e_bsp_io_port_pin_t port;
};
static struct key_pin_s key_pins[KEY_SIZE] = {
        {.code=KEY_MENU, .port=BSP_IO_PORT_02_PIN_07},
        {.code=KEY_PREV, .port=BSP_IO_PORT_04_PIN_07},
        {.code=KEY_NEXT, .port=BSP_IO_PORT_04_PIN_08},
        {.code=KEY_BACK, .port=BSP_IO_PORT_00_PIN_00},
};
static key_event_t key_events[KEY_SIZE + 1] = {NULL};
static fsp_err_t err;
void key_event_init() {
    err = RM_TOUCH_Open (g_qe_touch_instance_config01.p_ctrl, g_qe_touch_instance_config01.p_cfg);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0);
    }
}

key_event_t* detect_key_event() {
    bsp_io_level_t sw;
    key_event_t *event;
    uint32_t now = millis();

    for (int i = 0; i < KEY_SIZE; ++i) {
        R_IOPORT_PinRead(&g_ioport_ctrl, key_pins[i].port, &sw);
        event = &key_events[i];

        if (sw == BSP_IO_LEVEL_LOW) {
            // 按下
            if (event->press_time <= 0) {
                event->trigger_time = 0;
                event->trigger_type = TAP_EVENT;
                event->event_type = KEY_DOWN_EVENT;
                event->key_code = key_pins[i].code;
                event->press_time = now;
                printf("Key down: %d, time=%u\n", event->key_code, event->press_time);
                return event;
            }
        } else {
            if (event->press_time > 0 && event->trigger_time < 1) {
                // 松开
                event->trigger_time = now;
                if (now - event->press_time >= LONG_PRESS_TIME) {
                    event->trigger_type = LONG_TAP_EVENT;
                }
                event->event_type = KEY_UP_EVENT;
                printf("Key up: %d, total_time=%u\n", event->key_code, now - event->press_time);
                return event;
            }
            event->trigger_type = NONE_EVENT;
            event->press_time = 0;
            event->trigger_time = 0;
            event->event_type = KEY_NONE_EVENT;
        }
    }
    return NULL;
}

key_event_t* detect_touch_event() {
    err = RM_TOUCH_ScanStart (g_qe_touch_instance_config01.p_ctrl);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0);
        return NULL;
    }
    while (0 == g_qe_touch_flag)
    {
    }
    g_qe_touch_flag = 0;
    uint64_t button_status;
    key_event_t *event;
    event = &key_events[KEY_SIZE];
    uint32_t now = millis();

    err = RM_TOUCH_DataGet (g_qe_touch_instance_config01.p_ctrl, &button_status, NULL, NULL);
    if (FSP_SUCCESS == err && (button_status & (0b1)))
    {

        if (event->press_time <= 0) {
            event->trigger_time = 0;
            event->trigger_type = TAP_EVENT;
            event->event_type = TOUCH_EVENT;
            event->key_code = KEY_TOUCH;
            event->press_time = now;
            printf("Touch down: %d, time=%u\n", event->key_code, event->press_time);
            return event;
        }
    }
    if (event->press_time > 0 && event->trigger_time < 1 && (now - event->press_time >= LONG_PRESS_TIME)) {
        // 松开
        event->trigger_time = now;
        event->trigger_type = LONG_TAP_EVENT;
        event->event_type = KEY_UP_EVENT;
        printf("Touch up: %d, total_time=%u\n", event->key_code, now - event->press_time);
        return event;
    }
    event->trigger_type = NONE_EVENT;
    event->press_time = 0;
    event->trigger_time = 0;
    event->event_type = KEY_NONE_EVENT;

    return NULL;
}