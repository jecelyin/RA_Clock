/*
 * my_entry.c
 *
 *  Created on: 2023年7月22日
 *      Author: jecelyin
 */

#include "my_entry.h"
#include "smg.h"
#include "timer_smg.h"
#include "flash_smg.h"
#include "aht20.h"
#include "utils.h"
#include "qe_touch_config.h"
#include "buzzer.h"
#include "rtc.h"
#include "driver_ds3231.h"


//温湿度变量定义
uint8_t humdity_integer;//湿度整数
uint8_t humdity_decimal;//湿度小数
uint8_t temp_integer;//温度整数
uint8_t temp_decimal;//温度小数
uint8_t dht11_check;//校验值

//数码管变量
extern uint8_t num1, num2, num3, num4;//4个数码管显示的数值
extern uint8_t num_flag;//4个数码管和冒号轮流显示，一轮刷新五次

//RTC变量
ds3231_time_t current_time;
/* rtc_time_t is an alias for the C Standard time.h struct 'tm' */
rtc_time_t set_time =
        {
                .tm_sec  = 50,      /* 秒，范围从 0 到 59 */
                .tm_min  = 59,      /* 分，范围从 0 到 59 */
                .tm_hour = 23,      /* 小时，范围从 0 到 23*/
                .tm_mday = 29,       /* 一月中的第几天，范围从 0 到 30*/
                .tm_mon  = 11,      /* 月份，范围从 0 到 11*/
                .tm_year = 123,     /* 自 1900 起的年数，2023为123*/
                .tm_wday = 6,       /* 一周中的第几天，范围从 0 到 6*/
//    .tm_yday=0,         /* 一年中的第几天，范围从 0 到 365*/
//    .tm_isdst=0;        /* 夏令时*/
        };


//RTC闹钟变量
rtc_alarm_time_t set_alarm_time =
        {
                .time.tm_sec  = 58,      /* 秒，范围从 0 到 59 */
                .time.tm_min  = 59,      /* 分，范围从 0 到 59 */
                .time.tm_hour = 23,      /* 小时，范围从 0 到 23*/
                .time.tm_mday = 29,       /* 一月中的第几天，范围从 1 到 31*/
                .time.tm_mon  = 11,      /* 月份，范围从 0 到 11*/
                .time.tm_year = 123,     /* 自 1900 起的年数，2023为123*/
                .time.tm_wday = 6,       /* 一周中的第几天，范围从 0 到 6*/

                .sec_match        =  1,//每次秒到达设置的进行报警
                .min_match        =  0,
                .hour_match       =  0,
                .mday_match       =  0,
                .mon_match        =  0,
                .year_match       =  0,
                .dayofweek_match  =  0,
        };

//RTC回调函数
volatile bool rtc_flag = 0; //RTC延时1s标志位
volatile bool rtc_alarm_flag = 0; //RTC闹钟
/* Callback function */
void rtc_callback(rtc_callback_args_t *p_args) {
    /* TODO: add your own code here */
    if (p_args->event == RTC_EVENT_PERIODIC_IRQ)
        rtc_flag = 1;
    else if (p_args->event == RTC_EVENT_ALARM_IRQ)
        rtc_alarm_flag = 1;
}


//bsp_io_level_t sw1;//按键SW1状态
//bsp_io_level_t sw2;//按键SW2状态
//bsp_io_level_t sw3;//按键SW3状态
//bsp_io_level_t sw4;//按键SW4状态
bsp_io_level_t qe_sw = BSP_IO_LEVEL_LOW;//触摸电容状态

void qe_touch_sw(void);

//数码管显示状态，0正常显示，1修改小时，2修改分钟，3保存修改数据，4温度，5湿度
int smg_mode = 0;
//int sec = 0, min = 0, hour = 0;//保存时间数据
uint16_t time_mode_num = 0;//定时器刷新时间，实现闪烁效果
uint8_t sec, min, hour;

uint8_t flash_flag = 0;//保存时间数据，一半在每过一分钟或者按键修改时间
static fsp_err_t err = FSP_SUCCESS;

void parse_aht20( int8_t temperature, uint8_t humidity, enum AHT20_STATUS status ) {
    if( status != AHT20_SUCCESS ) {
        // ...process error
        printf("aht20 error: %d\n", status);
        return;
    }

    humdity_integer = humidity;
    temp_integer = temperature;
}


void my_entry() {
    printf("my entry start...");
//    fsp_err_t status = R_IIC_MASTER_Open(&g_i2c_master0_ctrl, &g_i2c_master0_cfg);
//    assert(FSP_SUCCESS == status);

    /**********************温湿度测试***************************************/
    //Init aht20
    aht20_init();

    //Register callback for reading temperature and humidity
    register_aht20_event_callback( parse_aht20 );

    //Trigger measurement and wait 80mS
    aht20_trigger_measurement();
    /**********************定时器开启***************************************/
    /* Initializes the module. */
    err = R_GPT_Open(&g_timer0_ctrl, &g_timer0_cfg);
    /* Handle any errors. This function should be defined by the user. */
    assert(FSP_SUCCESS == err);
    /* Start the timer. */
    (void) R_GPT_Start(&g_timer0_ctrl);
    /**********************data flash***************************************/
    flash_result_t blank_check_result;
    /* Open the flash lp instance. */
    err = R_FLASH_LP_Open(&g_flash0_ctrl, &g_flash0_cfg);
    assert(FSP_SUCCESS == err);

    ReadTimeFlash();

    /**********************RTC开启***************************************/
//    rtc_time_t get_time;
    /* Initialize the RTC module*/
    err = R_RTC_Open(&g_rtc0_ctrl, &g_rtc0_cfg);
    /* Handle any errors. This function should be defined by the user. */
    assert(FSP_SUCCESS == err);

    /* Set the RTC clock source. Can be skipped if "Set Source Clock in Open" property is enabled. */
    R_RTC_ClockSourceSet(&g_rtc0_ctrl);

    /* R_RTC_CalendarTimeSet must be called at least once to start the RTC */
    R_RTC_CalendarTimeSet(&g_rtc0_ctrl, &set_time);
    /* Set the periodic interrupt rate to 1 second */
    R_RTC_PeriodicIrqRateSet(&g_rtc0_ctrl, RTC_PERIODIC_IRQ_SELECT_1_SECOND);

    R_RTC_CalendarAlarmSet(&g_rtc0_ctrl, &set_alarm_time);
    uint8_t rtc_second = 0;      //秒
//    uint8_t rtc_minute = 0;      //分
//    uint8_t rtc_hour = 0;         //时
//    uint8_t rtc_day = 0;          //日
//    uint8_t rtc_month = 0;      //月
//    uint16_t rtc_year = 0;        //年
//    uint8_t rtc_week = 0;        //周
//    rtc_time_t get_time;

    /*************************** DS3231 START **************************************/
    rtc_init();
    /*************************** DS3231 END **************************************/
    rtc_get_time(&current_time);

    sec = current_time.second;        //时间数据 秒
    min = current_time.minute;        //时间数据 分钟
    hour = current_time.hour;        //时间数据 小时

    /* Open Touch middleware */
    err = RM_TOUCH_Open (g_qe_touch_instance_config01.p_ctrl, g_qe_touch_instance_config01.p_cfg);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0);
    }

    while (1) {

        if (flash_flag)        //按键修改完毕数据后进行保存
        {
            current_time.format = DS3231_FORMAT_24H;
            current_time.hour = hour;
            current_time.minute = min;
            current_time.second = 0;
            rtc_set_time(&current_time);
            SaveTimeFlash();
            flash_flag = 0;
            delay_ms(100);
        }


        if (rtc_flag) {
            rtc_get_time(&current_time); //获取RTC计数时间
            rtc_flag = 0;

//            hour = current_time.hour;
//            min = current_time.minute;
            //时间显示
            num1 = current_time.hour / 10;
            num2 = current_time.hour % 10;

            num3 = current_time.minute / 10;
            num4 = current_time.minute % 10;

            if (rtc_second % 5 == 0) //5S读一次
            {
//                DHT11_Read ();
                aht20_trigger_measurement();
                aht20_event();
                printf("hum=%d temp=%d\n", humdity_integer, temp_integer);
                if (current_time.format == DS3231_FORMAT_24H)
                {
                    printf("ds3231: %04d-%02d-%02d %02d:%02d:%02d %d.\n",
                           current_time.year, current_time.month, current_time.date,
                           current_time.hour, current_time.minute, current_time.second, current_time.week
                    );
                }
                else
                {
                    printf("ds3231: %04d-%02d-%02d %s %02d:%02d:%02d %d.\n",
                           current_time.year, current_time.month, current_time.date, (current_time.am_pm == DS3231_AM) ? "AM" : "PM",
                           current_time.hour, current_time.minute, current_time.second, current_time.week
                    );
                }
            }

        }
        if (rtc_alarm_flag) {
            rtc_alarm_flag = 0;
            printf("/************************Alarm Clock********************************/\n");
        }
        qe_touch_sw ();
        set_smg_button();
        R_BSP_SoftwareDelay(10U, BSP_DELAY_UNITS_MILLISECONDS);
    }

}

void qe_touch_sw(void)
{
    /* for [CONFIG01] configuration */
    err = RM_TOUCH_ScanStart (g_qe_touch_instance_config01.p_ctrl);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0);
        return;
    }
    while (0 == g_qe_touch_flag)
    {
    }
    g_qe_touch_flag = 0;
    uint64_t button_status;
    err = RM_TOUCH_DataGet (g_qe_touch_instance_config01.p_ctrl, &button_status, NULL, NULL);
    if (FSP_SUCCESS == err)
    {
        /* TODO: Add your own code here. */
        if (button_status & (0b1))
            qe_sw = 1;
        else
            qe_sw = 0;
    }

}
