/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

 // Standard C Included Files
#include <stdio.h>
// SDK Included Files
#include "board.h"
#include "fsl_os_abstraction.h"
#include "fsl_i2c_master_driver.h"
#include "fsl_debug_console.h"
#include "Accu.h"
#include "fsl_uart_hal.h"
#include "fsl_uart_driver.h"
//#include "fsl_uart.h"

char AT[]="AT";
uint8_t TXBUFF[2];
///////////////////////////////////////////////////////////////////////////////
// Code
///////////////////////////////////////////////////////////////////////////////

void UART2_IRQHandler(void)
{
	UART_DRV_IRQHandler(2);
}
int main(void)
{
	 // Init hardware
	uart_state_t uartState; // user provides memory for the driver state structure
	uart_user_config_t uartConfig;

	hardware_init();
	configure_uart_pins(1);


	 OSA_Init();


	uartConfig.baudRate = 9600;
	uartConfig.bitCountPerChar = kUart8BitsPerChar;
	uartConfig.parityMode = kUartParityDisabled;
	uartConfig.stopBitCount = kUartOneStopBit;

PRINTF("Just to init Uart\r");
	UART_DRV_Init(2,  &uartState, &uartConfig);
	PRINTF("Uart initilized\n\r");

	while(1){
		PRINTF("About to send data\n\r");
UART_DRV_SendDataBlocking(2, AT, sizeof(AT),16000u); // function
	PRINTF("Tried to sent some\n");
	}


return 0;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
