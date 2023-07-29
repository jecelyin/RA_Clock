//
// Created by Jecelyin Peng on 2023/7/29.
//

#include "buzzer.h"
#include "hal_data.h"

#define BUZZER_LOW        R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_03_PIN_02, BSP_IO_LEVEL_LOW);
#define BUZZER_HIGH       R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_03_PIN_02, BSP_IO_LEVEL_HIGH);

void alarm_sound() {
    uint32_t duration = 200;
    uint32_t i = 0, count = 0;
    while (count < 10) {
        while (i < duration) {
            BUZZER_HIGH
            R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MICROSECONDS);
            BUZZER_LOW
            R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MICROSECONDS);
            i++;
        }
        R_BSP_SoftwareDelay(800, BSP_DELAY_UNITS_MILLISECONDS);
        count++;
    }
}
void press_sound() {
    uint32_t duration = 2;
    uint32_t i = 0;
    while (i < duration) {
        BUZZER_HIGH
        R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MICROSECONDS);
        BUZZER_LOW
        R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MICROSECONDS);
        i++;
    }
}