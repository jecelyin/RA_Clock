/*
 * timer_smg.c
 *
 *  Created on: 2023年7月3日
 *      Author: a8456
 */
#include "timer_smg.h"
#include "smg.h"
#include "stdio.h"
#include "buzzer.h"

//数码管变量
extern uint8_t num1, num2, num3, num4;//4个数码管显示的数值
extern uint8_t num_flag;//4个数码管和冒号轮流显示，一轮刷新五次


int sw1_num1 = 0;//按键SW1计数值，去抖和长按短按判断
int sw2_num1 = 0;//按键SW2计数值，去抖和长按短按判断
int sw3_num1 = 0;//按键SW3计数值，去抖和长按短按判断
int sw4_num1 = 0;//按键SW4计数值，去抖和长按短按判断
int qe_sw_num1 = 0;//触摸按键计数值，去抖和长按短按判断

//按键变量
//extern bsp_io_level_t sw1;//按键SW1状态
//extern bsp_io_level_t sw2;//按键SW2状态
//extern bsp_io_level_t sw3;//按键SW3状态
//extern bsp_io_level_t sw4;//按键SW4状态
bsp_io_level_t sw1;//按键SW1状态
bsp_io_level_t sw2;//按键SW2状态
bsp_io_level_t sw3;//按键SW3状态
bsp_io_level_t sw4;//按键SW4状态
extern bsp_io_level_t qe_sw;//触摸电容状态

//extern int sw1_num1;//按键SW1计数值，去抖和长按短按判断
//extern int sw2_num1;//按键SW2计数值，去抖和长按短按判断
//extern int sw3_num1;//按键SW3计数值，去抖和长按短按判断
//extern int sw4_num1;//按键SW4计数值，去抖和长按短按判断
//extern int qe_sw_num1;//触摸按键计数值，去抖和长按短按判断

//数码管显示状态，0正常显示，1修改小时，2修改分钟，3保存修改数据，4温度，5湿度
extern int smg_mode;
extern int sec, min, hour;//保存时间数据
extern uint16_t time_mode_num;//定时器刷新时间，实现闪烁效果


extern rtc_time_t set_time;//RTC时间定义

extern uint8_t flash_flag;//保存时间数据，一半在每过一分钟或者按键修改时间

//温湿度变量定义
extern uint8_t humdity_integer;//湿度整数
extern uint8_t humdity_decimal;//湿度小数
extern uint8_t temp_integer;//温度整数
extern uint8_t temp_decimal;//温度小数
extern uint8_t dht11_check;//校验值

uint32_t time_mode_max = 400;
void timer0_callback(timer_callback_args_t *p_args) {
    if (TIMER_EVENT_CYCLE_END == p_args->event) {
        time_mode_num++;
        if (time_mode_num > time_mode_max * 2)
            time_mode_num = 0;

        if (smg_mode == 0) {
            if (num_flag == 0)
                smg_1(num1);
            else if (num_flag == 1)
                smg_2(num2);
            else if (num_flag == 2)
                smg_3(num3);
            else if (num_flag == 3)
                smg_4(num4);
            else if (num_flag == 4) {
                if (time_mode_num < time_mode_max)
                    smg_maohao_open(1);   //冒号
                else
                    smg_maohao_open(0);   //冒号
            }
        } else if (smg_mode == 1)//修改时间小时
        {
            if (time_mode_num < time_mode_max) {
                if (num_flag == 0)
                    smg_1(hour / 10);
                else if (num_flag == 1)
                    smg_2(hour % 10);
                else if (num_flag == 2)
                    smg_3(min / 10);
                else if (num_flag == 3)
                    smg_4(min % 10);
                else if (num_flag == 4)
                    smg_maohao_open(1);   //冒号
            } else {
                if (num_flag == 0)
                    smg_1_close();
                else if (num_flag == 1)
                    smg_2_close();
                else if (num_flag == 2)
                    smg_3(min / 10);
                else if (num_flag == 3)
                    smg_4(min % 10);
                else if (num_flag == 4)
                    smg_maohao_open(1);   //冒号
            }
        } else if (smg_mode == 2)//修改时间分钟
        {
            if (time_mode_num < time_mode_max) {
                if (num_flag == 0)
                    smg_1(hour / 10);
                else if (num_flag == 1)
                    smg_2(hour % 10);
                else if (num_flag == 2)
                    smg_3(min / 10);
                else if (num_flag == 3)
                    smg_4(min % 10);
                else if (num_flag == 4)
                    smg_maohao_open(1);   //冒号
            } else {
                if (num_flag == 0)
                    smg_1(hour / 10);
                else if (num_flag == 1)
                    smg_2(hour % 10);
                else if (num_flag == 2)
                    smg_3_close();
                else if (num_flag == 3)
                    smg_4_close();
                else if (num_flag == 4)
                    smg_maohao_open(1);   //冒号
            }
        } else if (smg_mode == 3)//保存数据
        {
            set_time.tm_sec = sec;
            set_time.tm_min = min;
            set_time.tm_hour = hour;
            R_RTC_CalendarTimeSet(&g_rtc0_ctrl, &set_time);
            smg_mode = 0;
            flash_flag = 1;//保存数据
        } else if (smg_mode == 4)//显示温度
        {

            if (num_flag == 0)
                smg_1_p();
            else if (num_flag == 1)
                smg_2(1);
            else if (num_flag == 2)
                smg_3(temp_integer / 10);
            else if (num_flag == 3)
                smg_4(temp_integer % 10);
            else if (num_flag == 4)
                smg_maohao_open(1);   //冒号
        } else if (smg_mode == 5)//显示湿度
        {

            if (num_flag == 0)
                smg_1_p();
            else if (num_flag == 1)
                smg_2(2);
            else if (num_flag == 2)
                smg_3(humdity_integer / 10);
            else if (num_flag == 3)
                smg_4(humdity_integer % 10);
            else if (num_flag == 4)
                smg_maohao_open(1);   //冒号
        }


        num_flag++;
        if (num_flag == 5)
            num_flag = 0;

    }
}

void set_smg_button(void) {

    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_02_PIN_07, &sw1);
    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_07, &sw2);
    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_08, &sw3);
    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_00, &sw4);
    if (!sw2)
        printf("sw2=%d\n", sw2);
    if (!sw3)
        printf("sw3=%d\n", sw3);
    if (!sw4)
        printf("sw4=%d\n", sw4);
    if (sw1 + sw2 + sw3 + sw4 == 4 && qe_sw == 0)//按键都没按下,清除按键按下计数值
    {
        sw1_num1 = 0;
        sw2_num1 = 0;
        sw3_num1 = 0;
        sw4_num1 = 0;
        qe_sw_num1 = 0;
    } else if (sw1 == 0 && sw2 && sw3 && sw4 && qe_sw == 0)//只有SW1按下
    {
        if (sw1_num1 < 2001)//按下小于10s,1001是防止变量在1000时候一直切换模式
            sw1_num1++;
        if (sw1_num1 % 10 == 0)//模式切换,按下
        {
            //buzzer_num=20;//蜂鸣器叫200ms
            if (smg_mode > 2)
                smg_mode = 0;
            else
                smg_mode++;
        }
        if (smg_mode == 6)
            smg_mode = 0;

        printf("press key1, sw1_num1=%d, mode=%d\n",sw1_num1, smg_mode);
        press_sound();
    } else if (sw2 == 0 && sw1 && sw3 && sw4 && qe_sw == 0)//只有SW2按下
    {
        press_sound();
        if (sw2_num1 < 10)//300ms 减一次
            sw2_num1++;
        else {
            sw2_num1 = 0;
            if (smg_mode == 1) {
                if (hour > 0)
                    hour--;
                else
                    hour = 23;

            } else if (smg_mode == 2) {
                if (min > 0)
                    min--;
                else
                    min = 59;
            }
        }
        printf("press key2, mode=%d, hour=%d,min=%d\n",smg_mode,hour,min);
    } else if (sw3 == 0 && sw1 && sw2 && sw4 && qe_sw == 0)//只有SW3按下
    {
        press_sound();
        if (sw3_num1 < 10)//300ms 减一次
            sw3_num1++;
        else {
            sw3_num1 = 0;
            if (smg_mode == 1) {
                if (hour < 23)
                    hour++;
                else
                    hour = 0;

            } else if (smg_mode == 2) {
                if (min < 59)
                    min++;
                else
                    min = 0;
            }
        }
        printf("press key3\n");
    } else if (sw4 == 0 && sw1 && sw2 && sw3 && qe_sw == 0)//只有SW3按下
    {
        press_sound();
        printf("press key4\n");
    } else if (sw1 && sw2 && sw3 && sw4 && qe_sw)//只有触摸电容按下
    {
        if (qe_sw_num1 < 30)//2000ms 切换一次
            qe_sw_num1++;
        else {
            qe_sw_num1 = 0;
            if (smg_mode == 0)//切换到显示温度
            {
                smg_mode = 4;

            } else if (smg_mode == 4)//切换到显示湿度
            {
                smg_mode = 5;
            }
                //切换为数据保存
            else if (smg_mode == 1 || smg_mode == 2) {
                smg_mode = 3;
            } else if (smg_mode == 5)//正常显示
            {
                smg_mode = 0;
            }

        }
        printf("press touch\n");
    }


}



















