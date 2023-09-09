//
// Created by Jecelyin Peng on 2023/8/3.
//

#include "ui.h"
#include "display.h"
#include "ui_home.h"
#include "ui_setting.h"
#include "buzzer.h"
#include <stdarg.h>


static context_t ui_context;
// 注意要和page_name_t顺序一致
static ui_init_ptr pages_init[] = {
        ui_home_init,
        ui_setting_init
};


static void destroy_page(ui_page_t *page);
static void page_stack_init(page_stack *page_stack);
static bool page_stack_is_empty(page_stack* page_stack);
static bool page_stack_is_full(page_stack* page_stack);
static void page_stack_push(page_stack* page_stack, ui_page_t* item);
static ui_page_t* page_stack_pop(page_stack* page_stack);
static ui_page_t* page_stack_last(page_stack* page_stack);

void navigate_to(page_name_t page_name, ...) {
    va_list args;
    va_start(args, page_name);

    ui_page_t page;
    ui_init_ptr init_fun = pages_init[page_name];
    init_fun(&page);

    context_t *ctx = &ui_context;
    page_stack *pages = &ctx->page_stacks;
    page_stack_push(pages, &page);

    if (!page.created) {
        page.on_create(0, args);
        page.created = true;
    }

    va_end(args);
}

void navigate_pop() {
    context_t *ctx = &ui_context;
    page_stack *pages = &ctx->page_stacks;
    ui_page_t *page = page_stack_pop(pages);
    destroy_page(page);
}

void ui_init() {
    context_t *ctx = &ui_context;
    page_stack *pages = &ctx->page_stacks;
    page_stack_init(pages);

    key_event_init();

    navigate_to(HOME_PAGE);
}

void ui_update() {
    page_stack *pages = &ui_context.page_stacks;
    ui_page_t *curr_page = page_stack_last(pages);

    if (!curr_page->is_visible) {
        curr_page->is_visible = true;
        curr_page->on_appear();
    }

    key_event_t *event = detect_key_event();
    if (event != NULL) {
        press_sound();
        curr_page->on_key_event(event);
    }
    event = detect_touch_event();
    if (event != NULL) {
        press_sound();
        curr_page->on_key_event(event);
    }

    curr_page->on_update();
}

static void destroy_page(ui_page_t *page) {
    page->on_destroy();
    page->created = false;
}

void ui_destroy() {
    // todo: destroy all page
}


static void page_stack_init(page_stack *page_stack) {
    page_stack->front = -1;
    page_stack->rear = -1;
}

static bool page_stack_is_empty(page_stack* page_stack) {
    return (page_stack->front == -1);
}

static bool page_stack_is_full(page_stack* page_stack) {
    return ((page_stack->rear + 1) % MAX_PAGE_STACK == page_stack->front);
}

static void page_stack_push(page_stack* page_stack, ui_page_t* item) {
    if (page_stack_is_full(page_stack)) {
        printf("Error: page_stack is full.\n");
        return;
    }

    if (page_stack_is_empty(page_stack)) {
        page_stack->front = page_stack->rear = 0;
    } else {
        page_stack->rear = (page_stack->rear + 1) % MAX_PAGE_STACK;
    }

    page_stack->items[page_stack->rear] = *item;
}

static ui_page_t* page_stack_pop(page_stack* page_stack) {
    if (page_stack_is_empty(page_stack)) {
        printf("Error: page_stack is empty.\n");
        return NULL;
    }

    ui_page_t * item = &page_stack->items[page_stack->front];

    if (page_stack->front == page_stack->rear) {
        page_stack->front = page_stack->rear = -1;
    } else {
        page_stack->front = (page_stack->front + 1) % MAX_PAGE_STACK;
    }

    return item;
}

static ui_page_t* page_stack_last(page_stack* page_stack) {
    ui_page_t* item = &page_stack->items[page_stack->front];
    return item;
}
