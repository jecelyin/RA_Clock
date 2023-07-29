#include "i2c.h"
#include <stdio.h>

uint32_t timeout_ms = 1000;

i2c_master_event_t i2c_event = I2C_MASTER_EVENT_ABORTED;

uint8_t buf10[10] = {0};

void i2c_master_callback(i2c_master_callback_args_t *p_args) {
//    printf("i2c_master_callback, start\n");
    i2c_event = I2C_MASTER_EVENT_ABORTED;
    if (NULL != p_args) {
        /* capture callback event for validating the i2c transfer event*/
        i2c_event = p_args->event;
//        printf("i2c_master_callback, args=\n");
//    } else {
//        printf("i2c_master_callback,no args\n");
    }
}


bool I2C_WaitResult() {

    while ((I2C_MASTER_EVENT_TX_COMPLETE != i2c_event) && timeout_ms > 0) {
        R_BSP_SoftwareDelay(10U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout_ms--;
    }
    timeout_ms = 1000;

    if (I2C_MASTER_EVENT_ABORTED == i2c_event) {
        __BKPT(0);
        return false;
    }
    bool ret = I2C_MASTER_EVENT_TX_COMPLETE == i2c_event || I2C_MASTER_EVENT_RX_COMPLETE == i2c_event;
    if (!ret) {
        __BKPT(0);
    }
    /* Read data back from the I2C slave */
    i2c_event = I2C_MASTER_EVENT_ABORTED;

    return ret;
}

void i2c_detect() {
    uint8_t buf[] = {0x00, 0x00};
    printf("i2c_detect start0...\n");
    fsp_err_t err = FSP_SUCCESS;
    int count = 0;
    for (uint8_t address = 0x28; address < 0x80; address++) {
        R_IIC_MASTER_SlaveAddressSet(&g_i2c_master0_ctrl, address, I2C_MASTER_ADDR_MODE_7BIT);
        err = R_IIC_MASTER_Write(&g_i2c_master0_ctrl, &buf[0], 1, false);
        if (err != FSP_SUCCESS) {
            continue;
        }
        //printf("I2C Write, addr=%d, err=%d\n", address, err);
        while ((I2C_MASTER_EVENT_TX_COMPLETE != i2c_event) && timeout_ms > 0) {
            R_BSP_SoftwareDelay(10U, BSP_DELAY_UNITS_MICROSECONDS);
            timeout_ms--;
        }
        timeout_ms = 1000;
        if (I2C_MASTER_EVENT_ABORTED == i2c_event) {
            continue;
        }
        if (I2C_MASTER_EVENT_TX_COMPLETE == i2c_event) {
            printf("addr=%d (0x%x), ok\n", address, address);
            count++;
        }
        i2c_event = I2C_MASTER_EVENT_ABORTED;
    }
    printf("I2C count: %d\n", count);

/* Send an I2C stop condition */
//    R_IIC_Stop(&g_iic_ctrl);


}


void I2C_Init() {
    R_IIC_MASTER_Open(&g_i2c_master0_ctrl, &g_i2c_master0_cfg);
}

bool I2C_Write(uint8_t const addr, uint8_t *const data, uint16_t const length) {
    R_IIC_MASTER_SlaveAddressSet(&g_i2c_master0_ctrl, addr, I2C_MASTER_ADDR_MODE_7BIT);
    fsp_err_t err = R_IIC_MASTER_Write(&g_i2c_master0_ctrl, data, length, false);
    assert(FSP_SUCCESS == err);

    return I2C_WaitResult();
}

bool I2C_Write_Register(uint8_t const addr, uint8_t reg_address, uint8_t *const data, uint16_t const length) {
    R_IIC_MASTER_SlaveAddressSet(&g_i2c_master0_ctrl, addr, I2C_MASTER_ADDR_MODE_7BIT);

//    fsp_err_t err = R_IIC_MASTER_Write(&g_i2c_master0_ctrl, &reg_address, 0x1, false);
//    assert(FSP_SUCCESS == err);
//
//    I2C_WaitResult();
//    err = R_IIC_MASTER_Write(&g_i2c_master0_ctrl, data, length, false);
//    assert(FSP_SUCCESS == err);
    buf10[0] = reg_address;
    for (int i = 0; i < length; ++i) {
        buf10[1 + i] = data[i];
    }
    fsp_err_t err = R_IIC_MASTER_Write(&g_i2c_master0_ctrl, buf10, length + 1, false);
    assert(FSP_SUCCESS == err);

    return I2C_WaitResult();
}


bool I2C_Read(uint8_t const addr, uint8_t *const p_dest, uint16_t const length) {
    R_IIC_MASTER_SlaveAddressSet(&g_i2c_master0_ctrl, addr, I2C_MASTER_ADDR_MODE_7BIT);
    fsp_err_t err = R_IIC_MASTER_Read(&g_i2c_master0_ctrl, p_dest, length, true);
    assert(FSP_SUCCESS == err);

    return I2C_WaitResult();
}

bool I2C_Read_Register(uint8_t const addr, uint8_t reg_address, uint8_t *const p_dest, uint16_t const length) {
    R_IIC_MASTER_SlaveAddressSet(&g_i2c_master0_ctrl, addr, I2C_MASTER_ADDR_MODE_7BIT);
    fsp_err_t err = R_IIC_MASTER_Write(&g_i2c_master0_ctrl, &reg_address, 0x1, false);
    assert(FSP_SUCCESS == err);

    I2C_WaitResult();
    err = R_IIC_MASTER_Read(&g_i2c_master0_ctrl, p_dest, length, true);
    assert(FSP_SUCCESS == err);

    return I2C_WaitResult();
}

