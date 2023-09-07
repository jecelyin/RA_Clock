//
// Created by Jecelyin Peng on 2023/7/29.
//

#ifndef BUZZER_H
#define BUZZER_H

#include "stdint.h"

void GPT_PWM_Init(void);
void test_buzzer();
void tone(uint16_t frequency, uint32_t duration);
void noTone();
void alarm_sound();
void press_sound();

#endif //BUZZER_H
