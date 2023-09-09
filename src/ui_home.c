//
// Created by Jecelyin Peng on 2023/9/8.
//

#include "ui_home.h"
#include "rtc.h"
#include "display.h"

static ds3231_time_t current_time;
static PAINT_TIME paint_time;

static void ui_home_on_create(char c, ...) {

}

static void ui_home_on_appear() {
    EPD_2IN9_Init(EPD_2IN9_FULL);
    Paint_SelectImage(g_display);
    EPD_2IN9_Clear();
    Paint_Clear(WHITE);
    EPD_2IN9_Display(g_display);
}

static void ui_home_on_update() {
    rtc_get_time(&current_time);

    paint_time.Year = current_time.year;
    paint_time.Month = current_time.month;
    paint_time.Day = current_time.date;
    paint_time.Hour = current_time.hour;
    paint_time.Min = current_time.minute;
    paint_time.Sec = current_time.second;

    EPD_2IN9_Init(EPD_2IN9_PART);
    Paint_ClearWindows(150, 80, 150 + Font20.Width * 7, 80 + Font20.Height, WHITE);
    Paint_DrawTime(150, 80, &paint_time, &Font20, WHITE, BLACK);

    EPD_2IN9_Display(g_display);
}

static void ui_home_on_disappear() {

}

static void ui_home_on_key_event(key_event_t *event) {
    switch (event->key_code) {
        case KEY_MENU:
            printf("go to setting page..\n");
            navigate_to(SETTING_PAGE);
            break;
        case KEY_TOUCH:
            printf("home touch\n");
            break;
        default:
            printf("key: %d\n", event->key_code);
    }
}

static void ui_home_on_destroy() {

}

void ui_home_init(ui_page_t *page) {
    page->on_create = ui_home_on_create;
    page->on_appear = ui_home_on_appear;
    page->on_update = ui_home_on_update;
    page->on_disappear = ui_home_on_disappear;
    page->on_key_event = ui_home_on_key_event;
    page->on_destroy = ui_home_on_destroy;
}
