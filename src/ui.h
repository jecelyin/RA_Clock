//
// Created by Jecelyin Peng on 2023/8/3.
//

#ifndef UI_H
#define UI_H

#include "stdbool.h"
#include "stdint.h"
#include "key_event.h"


typedef enum {
    HOME_PAGE,
    SETTING_PAGE,
} page_name_t;

typedef struct {
    bool created;
    bool is_visible;
    void (*on_create)(char c, ...);
    void (*on_appear)();
    void (*on_update)();
    void (*on_disappear)();
    void (*on_key_event)(key_event_t *event);
    void (*on_destroy)();
} ui_page_t;

#define MAX_PAGE_STACK  3
typedef struct {
    ui_page_t items[MAX_PAGE_STACK];  // 假设消息队列最多容纳10个消息项
    int front;
    int rear;
} page_stack;

typedef struct {
    page_stack page_stacks;
} context_t;

typedef void (*ui_init_ptr)(ui_page_t *page);

void ui_init();
void ui_update();
void navigate_to(page_name_t page_name, ...);
void navigate_pop();

#endif //UI_H
