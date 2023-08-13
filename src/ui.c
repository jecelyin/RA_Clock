//
// Created by Jecelyin Peng on 2023/8/3.
//

#include "ui.h"
#include "epaper.h"
#include "GUI_Paint.h"

UBYTE imgMem[4736] = {0};
void ui_main() {
    //Create a new image cache
//    UBYTE *BlackImage;
    // Value = 4736 (0x1280)
//    UWORD Imagesize = ((EPD_2IN9_V2_WIDTH % 8 == 0)? (EPD_2IN9_V2_WIDTH / 8 ): (EPD_2IN9_V2_WIDTH / 8 + 1)) * EPD_2IN9_V2_HEIGHT;
//    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
//        printf("Failed to apply for black memory...\r\n");
//        return;
//    }
    UWORD Imagesize = 4736;
    UBYTE *BlackImage = imgMem;
    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);
    Paint_Clear(BLACK);
    EPD_2IN9_V2_Display(BlackImage, Imagesize);
//    Paint_NewImage(BlackImage, EPD_2IN9_WIDTH, EPD_2IN9_HEIGHT, 90, WHITE);
//    Paint_Clear(BLACK);
//    EPD_2IN9_Display(BlackImage);
}