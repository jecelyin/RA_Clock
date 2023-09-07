/* generated vector header file - do not edit */
        #ifndef VECTOR_DATA_H
        #define VECTOR_DATA_H
        #ifdef __cplusplus
        extern "C" {
        #endif
                /* Number of interrupts allocated */
        #ifndef VECTOR_DATA_IRQ_COUNT
        #define VECTOR_DATA_IRQ_COUNT    (22)
        #endif
        /* ISR prototypes */
        void gpt_counter_overflow_isr(void);
        void rtc_alarm_periodic_isr(void);
        void fcu_frdyi_isr(void);
        void agt_int_isr(void);
        void sci_uart_rxi_isr(void);
        void sci_uart_txi_isr(void);
        void sci_uart_tei_isr(void);
        void sci_uart_eri_isr(void);
        void iic_master_rxi_isr(void);
        void iic_master_txi_isr(void);
        void rtc_carry_isr(void);
        void gpt_capture_a_isr(void);
        void ctsu_write_isr(void);
        void iic_master_tei_isr(void);
        void iic_master_eri_isr(void);
        void spi_rxi_isr(void);
        void spi_txi_isr(void);
        void ctsu_read_isr(void);
        void ctsu_end_isr(void);
        void spi_tei_isr(void);
        void spi_eri_isr(void);

        /* Vector table allocations */
        #define VECTOR_NUMBER_GPT0_COUNTER_OVERFLOW ((IRQn_Type) 0) /* GPT0 COUNTER OVERFLOW (Overflow) */
        #define GPT0_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 0) /* GPT0 COUNTER OVERFLOW (Overflow) */
        #define VECTOR_NUMBER_RTC_ALARM ((IRQn_Type) 1) /* RTC ALARM (Alarm interrupt) */
        #define RTC_ALARM_IRQn          ((IRQn_Type) 1) /* RTC ALARM (Alarm interrupt) */
        #define VECTOR_NUMBER_FCU_FRDYI ((IRQn_Type) 2) /* FCU FRDYI (Flash ready interrupt) */
        #define FCU_FRDYI_IRQn          ((IRQn_Type) 2) /* FCU FRDYI (Flash ready interrupt) */
        #define VECTOR_NUMBER_AGT0_INT ((IRQn_Type) 3) /* AGT0 INT (AGT interrupt) */
        #define AGT0_INT_IRQn          ((IRQn_Type) 3) /* AGT0 INT (AGT interrupt) */
        #define VECTOR_NUMBER_SCI9_RXI ((IRQn_Type) 4) /* SCI9 RXI (Received data full) */
        #define SCI9_RXI_IRQn          ((IRQn_Type) 4) /* SCI9 RXI (Received data full) */
        #define VECTOR_NUMBER_SCI9_TXI ((IRQn_Type) 5) /* SCI9 TXI (Transmit data empty) */
        #define SCI9_TXI_IRQn          ((IRQn_Type) 5) /* SCI9 TXI (Transmit data empty) */
        #define VECTOR_NUMBER_SCI9_TEI ((IRQn_Type) 6) /* SCI9 TEI (Transmit end) */
        #define SCI9_TEI_IRQn          ((IRQn_Type) 6) /* SCI9 TEI (Transmit end) */
        #define VECTOR_NUMBER_SCI9_ERI ((IRQn_Type) 7) /* SCI9 ERI (Receive error) */
        #define SCI9_ERI_IRQn          ((IRQn_Type) 7) /* SCI9 ERI (Receive error) */
        #define VECTOR_NUMBER_IIC0_RXI ((IRQn_Type) 8) /* IIC0 RXI (Receive data full) */
        #define IIC0_RXI_IRQn          ((IRQn_Type) 8) /* IIC0 RXI (Receive data full) */
        #define VECTOR_NUMBER_IIC0_TXI ((IRQn_Type) 9) /* IIC0 TXI (Transmit data empty) */
        #define IIC0_TXI_IRQn          ((IRQn_Type) 9) /* IIC0 TXI (Transmit data empty) */
        #define VECTOR_NUMBER_RTC_PERIOD ((IRQn_Type) 10) /* RTC PERIOD (Periodic interrupt) */
        #define RTC_PERIOD_IRQn          ((IRQn_Type) 10) /* RTC PERIOD (Periodic interrupt) */
        #define VECTOR_NUMBER_RTC_CARRY ((IRQn_Type) 11) /* RTC CARRY (Carry interrupt) */
        #define RTC_CARRY_IRQn          ((IRQn_Type) 11) /* RTC CARRY (Carry interrupt) */
        #define VECTOR_NUMBER_GPT7_CAPTURE_COMPARE_A ((IRQn_Type) 12) /* GPT7 CAPTURE COMPARE A (Compare match A) */
        #define GPT7_CAPTURE_COMPARE_A_IRQn          ((IRQn_Type) 12) /* GPT7 CAPTURE COMPARE A (Compare match A) */
        #define VECTOR_NUMBER_CTSU_WRITE ((IRQn_Type) 13) /* CTSU WRITE (Write request interrupt) */
        #define CTSU_WRITE_IRQn          ((IRQn_Type) 13) /* CTSU WRITE (Write request interrupt) */
        #define VECTOR_NUMBER_IIC0_TEI ((IRQn_Type) 14) /* IIC0 TEI (Transmit end) */
        #define IIC0_TEI_IRQn          ((IRQn_Type) 14) /* IIC0 TEI (Transmit end) */
        #define VECTOR_NUMBER_IIC0_ERI ((IRQn_Type) 15) /* IIC0 ERI (Transfer error) */
        #define IIC0_ERI_IRQn          ((IRQn_Type) 15) /* IIC0 ERI (Transfer error) */
        #define VECTOR_NUMBER_SPI0_RXI ((IRQn_Type) 16) /* SPI0 RXI (Receive buffer full) */
        #define SPI0_RXI_IRQn          ((IRQn_Type) 16) /* SPI0 RXI (Receive buffer full) */
        #define VECTOR_NUMBER_SPI0_TXI ((IRQn_Type) 17) /* SPI0 TXI (Transmit buffer empty) */
        #define SPI0_TXI_IRQn          ((IRQn_Type) 17) /* SPI0 TXI (Transmit buffer empty) */
        #define VECTOR_NUMBER_CTSU_READ ((IRQn_Type) 18) /* CTSU READ (Measurement data transfer request interrupt) */
        #define CTSU_READ_IRQn          ((IRQn_Type) 18) /* CTSU READ (Measurement data transfer request interrupt) */
        #define VECTOR_NUMBER_CTSU_END ((IRQn_Type) 19) /* CTSU END (Measurement end interrupt) */
        #define CTSU_END_IRQn          ((IRQn_Type) 19) /* CTSU END (Measurement end interrupt) */
        #define VECTOR_NUMBER_SPI0_TEI ((IRQn_Type) 22) /* SPI0 TEI (Transmission complete event) */
        #define SPI0_TEI_IRQn          ((IRQn_Type) 22) /* SPI0 TEI (Transmission complete event) */
        #define VECTOR_NUMBER_SPI0_ERI ((IRQn_Type) 23) /* SPI0 ERI (Error) */
        #define SPI0_ERI_IRQn          ((IRQn_Type) 23) /* SPI0 ERI (Error) */
        #ifdef __cplusplus
        }
        #endif
        #endif /* VECTOR_DATA_H */