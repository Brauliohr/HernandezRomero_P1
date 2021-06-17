/* Proyecto 1
 * Diseño con microcontroladores
 * Autor: Braulio Hernández Romero
 * Fecha de entrega: 17 de junio de 2021
 * "DAC - Digital to analog converter changing
 * the output signal through the serial port (UART)
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_uart.h"
#include "fsl_dac.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "dac.h"
#include "pit.h"
#include "uart.h"


typedef enum
{
    inicial,
    ch_freq,
    confirm_freq,
    ch_volt,
    confirm_volt,
} State_name_t;


uint8_t g_tipString[] =
    "Proyecto 1 - Diseno con Microcontroladores\r\nDAC Output inicial:\r\nVolt: 3.3 V\r\nFreq: 1Hz\r\nChoose an option:\r\n 'q' - Change Freq\r\n 'w' - Change Voltage\r\n";

uint8_t select;

/*******************************************************************************
 * Code
 ******************************************************************************/

void UART0_RX_TX_IRQHandler(void)
{
    if (kUART_RxDataRegFullFlag & UART_GetStatusFlags(UART0))

    {
        select = UART_ReadByte(UART0);
    }
    SDK_ISR_EXIT_BARRIER;
}

int main(void)
{
    uint32_t dacValue;

    //Configuración de inicio - UART
    uart_config();

    //Configuración de inicio - DAC
    dac_config();

    /* Send g_tipString out. */
    UART_WriteBlocking(UART0, g_tipString, sizeof(g_tipString) / sizeof(g_tipString[0]));

    State_name_t current_state = inicial;

    while (1)
    {
        dacValue = 0;

        //States machine
        switch (current_state)
        {
        case inicial:
            //Voltaje: 3.3 V y Freq: 1Hz
            dacValue = 4095;
            DAC_SetBufferValue(DAC0, 0U, dacValue);

            /* Send data only when UART TX register is empty and ring buffer has data to send out. */
            if ((kUART_TxDataRegEmptyFlag & UART_GetStatusFlags(UART0)))
            {

               	UART_WriteByte(UART0, select);
            }

            if (select == 'q'){
            	//cambiar frecuencia
            	current_state = ch_freq;
            }
            else if(select == 'w'){
            	//cambiar voltaje
            	current_state = ch_volt;
            }
            else{
            	current_state = inicial;
            }

            break;

        case ch_freq:
        	//cambiar frecuencia

        	if(select == 'q')
        	{
        		//confirmar frecuencia
        	}

        	if(select == 'w')
        	{
        		//cambiar voltaje
        	}

            break;
        case confirm_freq:
        	//confirmar frecuencia

        	if(select == 'w'){
        		//cambiar voltaje
        	}

            break;
        case ch_volt:
        	//cambiar voltaje

        	if(select == 'q')
        	{
        	    //cambiar frecuencia
        	}

        	if(select == 'w')
        	{
        	    //confirmar voltaje
        	}


            break;
        case confirm_volt:
        	//confirmar voltaje

        	if(select == 'q'){
        		//cambiar frecuencia
        	}

            break;
        default:
            inicial;

            break;
        }
    }
}
