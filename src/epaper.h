//
// Created by Jecelyin Peng on 2023/8/3.
//

#ifndef EPAPER_H
#define EPAPER_H

#include "DEV_Config.h"
#include "EPD_2in9.h"

inline void epd_init() {
    DEV_Module_Init();
    EPD_2IN9_Init(EPD_2IN9_FULL);
}
#define epd_clear      EPD_2IN9_Clear
#define epd_display    EPD_2IN9_Display
#define epd_sleep      EPD_2IN9_Sleep

#endif //EPAPER_H
