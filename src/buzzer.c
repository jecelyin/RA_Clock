//
// Created by Jecelyin Peng on 2023/7/29.
//

#include <stdio.h>
#include "buzzer.h"
#include "hal_data.h"
#include "pitches.h"
#include "timer.h"

#define BUZZER_LOW        R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_03_PIN_02, BSP_IO_LEVEL_LOW);
#define BUZZER_HIGH       R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_03_PIN_02, BSP_IO_LEVEL_HIGH);

static volatile uint32_t limit = 0;

void tone_timer_callback(timer_callback_args_t *p_args) {
    if (limit > 0 && millis() > limit) {
        noTone();
    }
}

//编写两只老虎歌曲文件
//定义音符
#define C_0  -1
#define C_1  262
#define C_2  294
#define C_3  330
#define C_4  350
#define C_5  393
#define C_6  441
#define C_7  495

//音符数组
int yinfu[] =
        {
                C_1, C_2, C_3, C_1,
                C_1, C_2, C_3, C_1,
                C_3, C_4, C_5,
                C_3, C_4, C_5,
                C_5, C_6, C_5, C_4, C_3, C_1,
                C_5, C_6, C_5, C_4, C_3, C_1,
                C_1, C_5, C_1,
                C_1, C_5, C_1,
        };
//音拍数组，每一行代表4拍
float yinpai[] =
        {
                1, 1, 1, 1,
                1, 1, 1, 1,
                1, 1, 2,
                1, 1, 2,
                0.75, 0.25, 0.75, 0.25, 1, 1,
                0.75, 0.25, 0.75, 0.25, 1, 1,
                1, 1, 2,
                1, 1, 2
        };
int length;//音符数量
int tonepin = 3;//3号PWM输出口

int t;

void test_buzzer() {
    length = sizeof(yinfu) / sizeof(yinfu[0]);

    // put your main code here, to run repeatedly:
    for (t = 0; t < length; t++) {
        tone(yinfu[t], 0);  //发出声音
//        delay(400*yinpai[t]);   //发音时间，用户可自调
        R_BSP_SoftwareDelay(400 * yinpai[t], BSP_DELAY_UNITS_MILLISECONDS);
        noTone();    //停止发声
    }
//    delay(3000);
    R_BSP_SoftwareDelay(3000, BSP_DELAY_UNITS_MILLISECONDS);
}

/** 自定义函数：设置PWM占空比
    @param duty 占空比范围：0~100 %
*/
void GPT_PWM_SetDuty(uint8_t duty) {
    timer_info_t info;
    uint32_t current_period_counts;
    uint32_t duty_cycle_counts;

    if (duty > 100)
        duty = 100; //限制占空比范围：0~100

    /* 获得GPT的信息 */
    R_GPT_InfoGet(&g_timer7_ctrl, &info);

    /* 获得计时器一个周期需要的计数次数 */
    current_period_counts = info.period_counts;

    /* 根据占空比和一个周期的计数次数计算GTCCR寄存器的值 */
    duty_cycle_counts = (uint32_t) (((uint64_t) current_period_counts * duty) / 100);

    /* 最后调用FSP库函数设置占空比 */
    R_GPT_DutyCycleSet(&g_timer7_ctrl, duty_cycle_counts, GPT_IO_PIN_GTIOCA);
}

void noTone() {
    R_GPT_Stop(&g_timer7_ctrl);
    limit = 0;
}

/**
 *
 * @param frequency Hertz
 * @param duration millisecond
 */
void tone(uint16_t frequency, uint32_t duration) {
    fsp_err_t err;
    uint32_t now = millis();
    if (now < limit) {
        printf("tone exists, now=%d, limit=%d\n", now, limit);
        return;
    } else {
        printf("tone start now=%d ..............\n", now);
    }
    if (!g_timer7_ctrl.open) {
        err = R_GPT_Open(&g_timer7_ctrl, &g_timer7_cfg);
        assert(FSP_SUCCESS == err);
        R_GPT_Enable(&g_timer7_ctrl);
        err = R_GPT_Stop(&g_timer7_ctrl);
        assert(FSP_SUCCESS == err);
    } else {
        /* 复位定时器. */
        err = R_GPT_Reset(&g_timer7_ctrl);
        assert(FSP_SUCCESS == err);
        R_BSP_SoftwareDelay(20, BSP_DELAY_UNITS_MILLISECONDS);
    }

    uint32_t period_counts = 0;
    uint32_t pclkd_freq_hz = 0;

    pclkd_freq_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKD);
    pclkd_freq_hz >>= (uint32_t) (g_timer7_cfg.source_div);
//    period_counts = (uint64_t)((1 * (pclkd_freq_hz * CLOCK_TYPE_SPECIFIER))  / TIMER_UNITS_MILLISECONDS);
// 频率=时钟源/period，若设置频率为10K，则period=48M/10K=4800
    period_counts = pclkd_freq_hz / frequency;
    err = R_GPT_PeriodSet(&g_timer7_ctrl, period_counts);
    assert(FSP_SUCCESS == err);
    R_BSP_SoftwareDelay(20, BSP_DELAY_UNITS_MILLISECONDS);
//    +占空比=cycle/period，若设置通道A的+占空比为25%，则cycle= +占空比* period=25%5000=1250
//    若设置通道B的+占空比为45%，则cycle= +占空比 period=45%*5000=2250

    /* 设置占空比为50%. */
//    GPT_PWM_SetDuty(80);
    uint32_t duty_cycle = 50 * period_counts / 100;
    err = R_GPT_DutyCycleSet(&g_timer7_ctrl, duty_cycle, GPT_IO_PIN_GTIOCA);
    assert(FSP_SUCCESS == err);
    R_BSP_SoftwareDelay(20, BSP_DELAY_UNITS_MILLISECONDS);

    /* 开启定时器. */
    R_GPT_Start(&g_timer7_ctrl);
    if (duration) {
        limit = now + duration;
    } else {
        limit = 0;
    }
}

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
    tone(C_6, 400);
}