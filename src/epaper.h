//
// Created by Jecelyin Peng on 2023/8/3.
//

#ifndef EPAPER_H
#define EPAPER_H

#include <stdlib.h>
#include "DEV_Config.h"
#include "EPD_2in9_V2.h"
#include "EPD_2in9.h"
#include "GUI_Paint.h"

inline void epd_init() {
    DEV_Module_Init();
    printf("e-Paper Init and Clear...\r\n");
    EPD_2IN9_V2_Init();
    EPD_2IN9_V2_Clear();
//    EPD_2IN9_Init(EPD_2IN9_FULL);
//    EPD_2IN9_Clear();
}

#endif //EPAPER_H
