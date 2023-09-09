//
// Created by Jecelyin Peng on 2023/9/7.
//

#include "display.h"

UBYTE g_display[Imagesize] = {0};

void display_init() {
    DEV_Module_Init();

    printf("e-Paper Init and Clear...\r\n");
    EPD_2IN9_Init(EPD_2IN9_FULL);
    EPD_2IN9_Clear();
    DEV_Delay_ms(500);
    Paint_NewImage(g_display, EPD_2IN9_WIDTH, EPD_2IN9_HEIGHT, 270, WHITE);
    Paint_Clear(WHITE);

}