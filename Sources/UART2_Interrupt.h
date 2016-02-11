/*
 * UART2_Interrupt.h
 *
 *  Created on: Feb 9, 2016
 *      Author: Eric
 */

#ifndef SOURCES_UART2_INTERRUPT_H_
#define SOURCES_UART2_INTERRUPT_H_
#include "board.h"

int BufferStage = 0;
char AT[]="AT";
uint8_t TXBUFF[2];
char CommandBuffer[20];

void UART2_config(unsigned int BAUD_RATE);
void enable_UART2_receive_interrupt();
void put_char(char c);
void UART2_IRQHandler(void);





#endif /* SOURCES_UART2_INTERRUPT_H_ */
