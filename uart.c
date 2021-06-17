/*
 * uart.c
 *
 *  Created on: 16 jun. 2021
 *      Author: Braulio
 */
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_uart.h"
#include "uart.h"

void uart_config(void)
{
	uart_config_t config;
	    BOARD_InitPins();
	    BOARD_BootClockRUN();

	    /*
	     * config.baudRate_Bps = 115200U;
	     * config.parityMode = kUART_ParityDisabled;
	     * config.stopBitCount = kUART_OneStopBit;
	     * config.txFifoWatermark = 0;
	     * config.rxFifoWatermark = 1;
	     * config.enableTx = false;
	     * config.enableRx = false;
	     */
	    UART_GetDefaultConfig(&config);
	    config.baudRate_Bps = 115200U;
	    config.enableTx     = true;
	    config.enableRx     = true;

	    UART_Init(UART0, &config, CLOCK_GetFreq(kCLOCK_CoreSysClk));

	    /* Enable RX interrupt. */
	    UART_EnableInterrupts(UART0, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
	    EnableIRQ(UART0_RX_TX_IRQn);

}
