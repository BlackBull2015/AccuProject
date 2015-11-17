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

#define DATA_LENGTH 1
#define I2C_INSTANCE_0 0

// Buffer store data to send to slave
uint8_t txBuff[DATA_LENGTH] = {0};
// Buffer store data to receive from slave
uint8_t rxBuff[1] = {0};

//Test Register for who am i
uint8_t WHO_AM_I[1] = {0x0D};


///////////////////////////////////////////////////////////////////////////////
// Code
///////////////////////////////////////////////////////////////////////////////
int main(void)
{
    // Number byte data will be transfer
    uint32_t count = 0;
    uint32_t i = 0;
    // i2c master state
    i2c_master_state_t master;
    // i2c device configuration
    i2c_device_t device =
    {
      .address = 0x1DU,
      .baudRate_kbps = 400   // 400 Kbps
    };

    // Init hardware
    hardware_init();

    //Init ports for I2C 0
    i2cinitreg();


    // Initialize OSA
    OSA_Init();

    PRINTF("\r\n==================== I2C MASTER BLOCKING ===================\r\n");
    PRINTF("\r\n1. Master sends a frame includes CMD(size of data) and data\
    \r\n2. Master receives data from slave.\
    \r\n3. Compare rxBuff and txBuff to see result.\r\n");
    PRINTF("\r\n============================================================\r\n\n");

    // Initialize i2c master
    I2C_DRV_MasterInit(I2C_INSTANCE_0, &master);
    PRINTF("Press any key to start transfer:\r\n\n");
     // Loop for transfer
    GETCHAR();
    // Master Sends command of register it wasnt to read and return is saved inside rxBuff
     I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,WHO_AM_I, 1, rxBuff, 1, 1000);
     //Prints out values in recived register
     PRINTF("\n\rWho am i register value is: %01X", rxBuff[0]);


////    while(1)
////    {
//        // Wait user press any key
//        //GETCHAR();
//
//        //Maunal
//    	//To set given register to certin value you send register value as command and value to put as data
//        I2C_DRV_MasterSendDataBlocking(I2C_INSTANCE_0, &device,
//        		NULL, 0, (const uint8_t*)WHO_AM_I, 1, 1000);
//        //Delay
//        OSA_TimeDelay(25);
//
//
//        //Maunal
//    	//To Read from given register you send register to read from as command and data bufer to send it to
//        I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,
//        		WHO_AM_I, 1, rxBuff, 1, 1000);
//
////		}//while end

    PRINTF("\r\n==================== I2C MASTER FINISH =================== \r\n");

    // Deinit i2c
    I2C_DRV_MasterDeinit(0);

    return 0;
}

void i2cinitreg(){
    PORTE_PCR24 |= (0x05u)<<8 | 0x03u;
    PORTE_PCR25 |= (0x05u)<<8 | 0x03u;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
