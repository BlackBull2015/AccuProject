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
#include "fsl_clock_manager.h"
//#include "fsl_uart.h"

void enable_UART2_receive_interrupt();
void UART2_config(unsigned int BAUD_RATE);
void put_char(char c);


/*
 * UART2 Interrupt Handler
 * Echos received character
 */
void UART2_IRQHandler(void)
{
    if(UART2_S1 & UART_S1_RDRF_MASK)
    	PUTCHAR(UART2_D);
}

char AT[]="AT";
uint8_t TXBUFF[2];
///////////////////////////////////////////////////////////////////////////////
// Code
///////////////////////////////////////////////////////////////////////////////



int main(void)
{
	 // Init hardware
	uart_state_t uartState; // user provides memory for the driver state structure
	uart_user_config_t uartConfig;

	hardware_init();
	UART2_config(9600);
	enable_UART2_receive_interrupt();

	PRINTF("About to send data\n\r");
	while(1){

		put_char('A');
		for(int x=0;x<1000;x++);

	}


return 0;
}

//Function to configure UART2
void UART2_config(unsigned int BAUD_RATE)
{
	long int uart_clock, BR;
	unsigned int SBR, OSR;
	unsigned char temp;
	//enable Port A and UART 0 clocks
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
	//configure UART 0 pins
	configure_uart_pins(1);
	//configure baud rate
	uart_clock = CLOCK_SYS_GetBusClockFreq();
	SBR = uart_clock/(16 * BAUD_RATE);
	UART2_BDL = SBR & 0xFF;
	UART2_BDH |= ((SBR & 0xFF00)>>8);
	UART2_C1 = 0;
	UART2_C2 |= 0x0C; //enable transmitter and receiver
	UART2_C3 = 0;
	//Function to configure UART2
}

void enable_UART2_receive_interrupt()
{
	//Configure NVIC
	NVIC_ClearPendingIRQ(14);
	NVIC_EnableIRQ(14);
	UART2_C2 |= UART_C2_RIE_MASK;	//set RIE to enable receive interrupt
}

/*********************************************************************
* Function to transmit a single character to the UART2 TXD pin
* The function waits until the transmit buffer is empty before writing
* to the date register.
*/
void put_char(char c)
{
	while((UART2_S1 & UART_S1_TDRE_MASK) == 0) //wait until tx buffer is empty
	{}
	UART2_D = c;
}
//********************************************************************


/*******************************************************************************
 * EOF
 ******************************************************************************/
