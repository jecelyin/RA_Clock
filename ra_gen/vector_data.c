/* generated vector source file - do not edit */
        #include "bsp_api.h"
        /* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
        #if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = iic_master_rxi_isr, /* IIC0 RXI (Receive data full) */
            [1] = iic_master_txi_isr, /* IIC0 TXI (Transmit data empty) */
            [2] = fcu_frdyi_isr, /* FCU FRDYI (Flash ready interrupt) */
            [3] = agt_int_isr, /* AGT0 INT (AGT interrupt) */
            [4] = sci_uart_rxi_isr, /* SCI9 RXI (Received data full) */
            [5] = sci_uart_txi_isr, /* SCI9 TXI (Transmit data empty) */
            [6] = sci_uart_tei_isr, /* SCI9 TEI (Transmit end) */
            [7] = sci_uart_eri_isr, /* SCI9 ERI (Receive error) */
            [8] = spi_rxi_isr, /* SPI0 RXI (Receive buffer full) */
            [9] = ctsu_write_isr, /* CTSU WRITE (Write request interrupt) */
            [10] = iic_master_tei_isr, /* IIC0 TEI (Transmit end) */
            [11] = iic_master_eri_isr, /* IIC0 ERI (Transfer error) */
            [12] = gpt_capture_a_isr, /* GPT7 CAPTURE COMPARE A (Compare match A) */
            [13] = spi_txi_isr, /* SPI0 TXI (Transmit buffer empty) */
            [14] = ctsu_read_isr, /* CTSU READ (Measurement data transfer request interrupt) */
            [15] = ctsu_end_isr, /* CTSU END (Measurement end interrupt) */
            [18] = spi_tei_isr, /* SPI0 TEI (Transmission complete event) */
            [19] = spi_eri_isr, /* SPI0 ERI (Error) */
            [23] = rtc_carry_isr, /* RTC CARRY (Carry interrupt) */
        };
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_IELS_ENUM(EVENT_IIC0_RXI), /* IIC0 RXI (Receive data full) */
            [1] = BSP_PRV_IELS_ENUM(EVENT_IIC0_TXI), /* IIC0 TXI (Transmit data empty) */
            [2] = BSP_PRV_IELS_ENUM(EVENT_FCU_FRDYI), /* FCU FRDYI (Flash ready interrupt) */
            [3] = BSP_PRV_IELS_ENUM(EVENT_AGT0_INT), /* AGT0 INT (AGT interrupt) */
            [4] = BSP_PRV_IELS_ENUM(EVENT_SCI9_RXI), /* SCI9 RXI (Received data full) */
            [5] = BSP_PRV_IELS_ENUM(EVENT_SCI9_TXI), /* SCI9 TXI (Transmit data empty) */
            [6] = BSP_PRV_IELS_ENUM(EVENT_SCI9_TEI), /* SCI9 TEI (Transmit end) */
            [7] = BSP_PRV_IELS_ENUM(EVENT_SCI9_ERI), /* SCI9 ERI (Receive error) */
            [8] = BSP_PRV_IELS_ENUM(EVENT_SPI0_RXI), /* SPI0 RXI (Receive buffer full) */
            [9] = BSP_PRV_IELS_ENUM(EVENT_CTSU_WRITE), /* CTSU WRITE (Write request interrupt) */
            [10] = BSP_PRV_IELS_ENUM(EVENT_IIC0_TEI), /* IIC0 TEI (Transmit end) */
            [11] = BSP_PRV_IELS_ENUM(EVENT_IIC0_ERI), /* IIC0 ERI (Transfer error) */
            [12] = BSP_PRV_IELS_ENUM(EVENT_GPT7_CAPTURE_COMPARE_A), /* GPT7 CAPTURE COMPARE A (Compare match A) */
            [13] = BSP_PRV_IELS_ENUM(EVENT_SPI0_TXI), /* SPI0 TXI (Transmit buffer empty) */
            [14] = BSP_PRV_IELS_ENUM(EVENT_CTSU_READ), /* CTSU READ (Measurement data transfer request interrupt) */
            [15] = BSP_PRV_IELS_ENUM(EVENT_CTSU_END), /* CTSU END (Measurement end interrupt) */
            [18] = BSP_PRV_IELS_ENUM(EVENT_SPI0_TEI), /* SPI0 TEI (Transmission complete event) */
            [19] = BSP_PRV_IELS_ENUM(EVENT_SPI0_ERI), /* SPI0 ERI (Error) */
            [23] = BSP_PRV_IELS_ENUM(EVENT_RTC_CARRY), /* RTC CARRY (Carry interrupt) */
        };
        #endif