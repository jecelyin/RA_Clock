//
// Created by Jecelyin Peng on 2023/9/7.
//

#ifndef RA_CLOCK_DISPLAY_H
#define RA_CLOCK_DISPLAY_H

#include "GUI_Paint.h"
#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
//#include "imagedata.h"
#include <stdlib.h>
#define Imagesize ((EPD_2IN9_WIDTH % 8 == 0)? (EPD_2IN9_WIDTH / 8 ): (EPD_2IN9_WIDTH / 8 + 1)) * EPD_2IN9_HEIGHT

extern UBYTE g_display[Imagesize];

void display_init();


#endif //RA_CLOCK_DISPLAY_H
