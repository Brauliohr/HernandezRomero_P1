/*
 * uart.h
 *
 *  Created on: 16 jun. 2021
 *      Author: Braulio
 */

#ifndef UART_H_
#define UART_H_
/*! @brief Ring buffer size (Unit: Byte). */
#define DEMO_RING_BUFFER_SIZE 16

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_uart.h"

void uart_config(void);

#endif /* UART_H_ */
