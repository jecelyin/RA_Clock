//
// Created by Jecelyin Peng on 2023/9/8.
//

#ifndef RA_CLOCK_KEY_EVENT_H
#define RA_CLOCK_KEY_EVENT_H
#include "stdint.h"

typedef enum {
    KEY_NONE_EVENT,
    KEY_DOWN_EVENT,
    KEY_UP_EVENT,
    TOUCH_EVENT,
} event_type_t;

typedef enum {
    KEY_NULL,
    KEY_MENU,
    KEY_PREV,
    KEY_NEXT,
    KEY_BACK,
    KEY_TOUCH
} key_code_t;

typedef enum {
    NONE_EVENT,
    TAP_EVENT,
    LONG_TAP_EVENT
} key_trigger_type_t;

typedef struct {
    key_code_t key_code;
    event_type_t event_type;
    key_trigger_type_t trigger_type;
    uint32_t press_time;
    uint32_t trigger_time;
} key_event_t;

void key_event_init();
key_event_t* detect_key_event();
key_event_t* detect_touch_event();

#endif //RA_CLOCK_KEY_EVENT_H
