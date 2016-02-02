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
#include "Accu2.h"
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


//Simple UART2

//	 // Init hardware
//	uart_state_t uartState; // user provides memory for the driver state structure
//	uart_user_config_t uartConfig;
//
//	hardware_init();
//	configure_uart_pins(1);
//
//
//	 OSA_Init();
//
//
//	uartConfig.baudRate = 9600;
//	uartConfig.bitCountPerChar = kUart8BitsPerChar;
//	uartConfig.parityMode = kUartParityDisabled;
//	uartConfig.stopBitCount = kUartOneStopBit;
//
//PRINTF("Just to init Uart\r");
//	UART_DRV_Init(2,  &uartState, &uartConfig);
//	PRINTF("Uart initilized\n\r");
//
//	while(1){
//		PRINTF("About to send data\n\r");
//UART_DRV_SendDataBlocking(2, AT, sizeof(AT),16000u); // function
////	UART_DRV_ReceiveDataBlocking(2, &TXBUFF, 2,16000); // function
////	 PRINTF("\n\rWho am i register value is: %01X", TXBUFF[0]);
//
//	//PRINTF()
//	PRINTF("Tried to sent some\n");
//
//	}


//	//Accu redings
//	int x,y,z,count, magnet;
//
//    // i2c master state
//    i2c_master_state_t master;
//    // i2c device configuration
//    i2c_device_t device =
//    {
//      .address = 0x1DU,
//      .baudRate_kbps = 400   // 400 Kbps
//    };
//
//    // Init hardware
//    hardware_init();
//
//    //Init ports for I2C 0
//    i2cinitreg();
//
//    // Initialize OSA
//    OSA_Init();
//
//    PRINTF("\r\n==================== I2C MASTER BLOCKING ===================\r\n");
//    PRINTF("\r\n1. Master checks who am i register\
//    \r\n2. Master configures accelerometer and magnetometer\
//    \r\n3. Takes 200 samples, average them and displays results\r\n");
//    PRINTF("\r\n============================================================\r\n\n");
//
//
//    // Initialize i2c master
//    I2C_DRV_MasterInit(I2C_INSTANCE_0, &master);
//    PRINTF("Press any key to start transfer:\r\n\n");
//    GETCHAR();
//
//
//    // Master Sends command of register it wasn't to read and return is saved inside rxBuff
//     I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,WHO_AM_I, 1, rxBuff, 1, 1000);
//     //Prints out values in recived register
//     PRINTF("\n\rWho am i register value is: %01X", rxBuff[0]);
//
//
//     configureAccuAndMag(device);
//
//     while(1){
//
//    	 x = 0;
//    	 y = 0;
//    	 z = 0;
//    	 for(count = 0; count < 200; count++){
//    		 I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,READ_DATA, 1, rxBuff, 13, 1000);
//
//    		     	 x += (int16_t)(((rxBuff[1] << 8) | rxBuff[2]))>> 2;
//    		     	 y += (int16_t)(((rxBuff[3] << 8) | rxBuff[4]))>> 2;
//    		     	 z += (int16_t)(((rxBuff[5] << 8) | rxBuff[6]))>> 2;
//    	 }
//    	 x = x/200;
//    	 y = y/200;
//    	 getWhere(x,y);
//     }
//
//    PRINTF("\r\n==================== I2C MASTER FINISH =================== \r\n");
//
//    // Deinit i2c
//    I2C_DRV_MasterDeinit(0);
//
//    return 0;
}

void i2cinitreg(){
    PORTE_PCR24 |= (0x05u)<<8 | 0x03u;
    PORTE_PCR25 |= (0x05u)<<8 | 0x03u;
}


void getWhere(int x, int y){

	PRINTF("\rAccu is: x=%06i y=%06i  ",x,y);

	if(x<0-TRESHOLD || y<0-TRESHOLD || x>0+TRESHOLD || y>0+TRESHOLD){

	if(y>0+TRESHOLD){
		PRINTF("RIGHT ");
	}else if(y<0-TRESHOLD){
		PRINTF("LEFT ");
	}

	if(x>0+TRESHOLD){
		PRINTF(" BACK ");
	}else if(x<0-TRESHOLD){
		PRINTF(" FRONT ");
	}

	}
	PRINTF("                 ");

}


void configureAccuAndMag(struct i2c_device_t *device){


	PRINTF("\rConfiguring Accu\n");
	//Stendby On
	I2C_DRV_MasterSendDataBlocking(I2C_INSTANCE_0, &device,ACCU_CTR_1, 1, STN_ON, 1, 1000);
	//Setting Mag reg
	I2C_DRV_MasterSendDataBlocking(I2C_INSTANCE_0, &device,MAG_CTR_1, 1, MAG_REG_1, 1, 1000);
	I2C_DRV_MasterSendDataBlocking(I2C_INSTANCE_0, &device,MAG_CTR_2, 1, MAG_REG_2, 1, 1000);
	//Setting Data
	I2C_DRV_MasterSendDataBlocking(I2C_INSTANCE_0, &device,XYZ_DATA_REG, 1, XYZ_DATA, 1, 1000);
	//Standby off
	I2C_DRV_MasterSendDataBlocking(I2C_INSTANCE_0, &device,ACCU_CTR_1, 1, STN_OFF, 1, 1000);



}


/*******************************************************************************
 * EOF
 ******************************************************************************/
