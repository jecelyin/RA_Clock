//
// Created by Jecelyin Peng on 2023/8/25.
//

#include "timer.h"
#include "hal_data.h"

static volatile uint32_t agt_time_ms = 0;

void agt_timer1_callback(timer_callback_args_t * p_args) {
    agt_time_ms += 1;
    if (agt_time_ms >= UINT32_MAX) {
        agt_time_ms = 0;
    }
}

void agt_timer_init() {
    fsp_err_t err;
    err = R_AGT_Open(&g_timer1_ctrl, &g_timer1_cfg);
    assert(FSP_SUCCESS == err);

    R_AGT_Start(&g_timer1_ctrl);
    assert(FSP_SUCCESS == err);
}

uint32_t millis() {
    return agt_time_ms;
}