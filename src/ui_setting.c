//
// Created by Jecelyin Peng on 2023/9/9.
//

#include "ui_setting.h"


static void ui_setting_on_create(char c, ...) {

}

static void ui_setting_on_appear() {

}

static void ui_setting_on_update() {

}

static void ui_setting_on_disappear() {

}

static void ui_setting_on_key_event(key_event_t *event) {
    switch (event->key_code) {
        case KEY_BACK:
            navigate_pop();
            break;
    }
}

static void ui_setting_on_destroy() {

}

void ui_setting_init(ui_page_t *page) {
    page->on_create = ui_setting_on_create;
    page->on_appear = ui_setting_on_appear;
    page->on_update = ui_setting_on_update;
    page->on_disappear = ui_setting_on_disappear;
    page->on_key_event = ui_setting_on_key_event;
    page->on_destroy = ui_setting_on_destroy;
}
