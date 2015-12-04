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
uint8_t rxBuff[13] = {0};
uint8_t mockData[1] = {0x00};
uint8_t mockData2[1] = {0x00};

//Test Register for who am i
uint8_t WHO_AM_I[1] = {0x0D};

//Read Register Data status
uint8_t READ_DATA[1] = {0x00};


//Register Addresses
uint8_t ACCU_CTR_1[1] = {0x2A};
uint8_t MAG_CTR_1[1] = {0x5B};
uint8_t MAG_CTR_2[1] = {0x5C};
uint8_t XYZ_DATA_REG[1] = {0x0F};



//Config Register Values
//Standby Mode
uint8_t STN_ON[1] = {0x00};
uint8_t STN_OFF[1] = {0x0D};
//Mag
uint8_t MAG_REG_1[1] = {0x1F};
uint8_t MAG_REG_2[1] = {0x20};
//XYZ data set
uint8_t XYZ_DATA[1] = {0x01};



uint8_t mock1 = {0x6D};
uint8_t mock2 = {0x6E};
uint8_t mock3 = {0x6F};
uint8_t mock4 = {0x70};
uint8_t mock5 = {0x71};
uint8_t mock6 = {0x72};



///////////////////////////////////////////////////////////////////////////////
// Code
///////////////////////////////////////////////////////////////////////////////
int main(void)
{
	//Accu redings
	int x;
	int y;
	int z;
	//Mag redings
	int mx;
	int my;
	int mz;
//	int16_t refx;
//	int16_t refy;
//	int16_t refz;

int magnet;



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


//Configuring accu and magnetomer
     PRINTF("\rConfiguring Accu\n");
 	//Stendby On
 	I2C_DRV_MasterSendDataBlocking(I2C_INSTANCE_0, &device,ACCU_CTR_1, 1, STN_ON, 1, 1000);
 	PRINTF("\rStendby\n");
 	//Setting Mag reg
 	I2C_DRV_MasterSendDataBlocking(I2C_INSTANCE_0, &device,MAG_CTR_1, 1, MAG_REG_1, 1, 1000);
 	I2C_DRV_MasterSendDataBlocking(I2C_INSTANCE_0, &device,MAG_CTR_2, 1, MAG_REG_2, 1, 1000);
 	PRINTF("\rMag done\n");
 	//Setting Data
 	I2C_DRV_MasterSendDataBlocking(I2C_INSTANCE_0, &device,XYZ_DATA_REG, 1, XYZ_DATA, 1, 1000);
 	PRINTF("\rxyz done\n");


// 	I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,mock1, 1, mockData, 1, 1000);
// 	I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,mock2, 1, mockData, 1, 1000);
// 	I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,mock3, 1, mockData, 1, 1000);
// 	I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,mock4, 1, mockData, 1, 1000);
// 	I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,mock5, 1, mockData, 1, 1000);
// 	I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,mock6, 1, mockData, 1, 1000);



 	//Standby off
 	I2C_DRV_MasterSendDataBlocking(I2C_INSTANCE_0, &device,ACCU_CTR_1, 1, STN_OFF, 1, 1000);
 	PRINTF("\rstandby off\n");

 	//Reding Mock registers






//
// 	PRINTF("\r\ngetting ref values");
// 	I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,mock1, 1, mockData, 1, 1000);
// 	PRINTF("\n\rRef is: %01X", mockData[0]);
// 	I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,mock2, 1, mockData2, 1, 1000);
// 	PRINTF("\n\rRef is: %01X", mockData2[0]);
// 	refx = (int16_t)(mockData[0]<<8 | mockData2[0]);
// 	I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,mock3, 1, mockData, 1, 1000);
// 	PRINTF("\n\rRef is: %01X", mockData[0]);
// 	I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,mock4, 1, mockData2, 1, 1000);
// 	PRINTF("\n\rRef is: %01X", mockData2[0]);
// 	refy = (int16_t)(mockData[0]<<8 | mockData2[0]);
// 	I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,mock5, 1, mockData, 1, 1000);
// 	PRINTF("\n\rRef is: %01X", mockData[0]);
// 	I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,mock6, 1, mockData2, 1, 1000);
// 	PRINTF("\n\rRef is: %01X\n", mockData2[0]);
// 	refz = (int16_t)(mockData[0]<<8 | mockData2[0]);

 	//PRINTF("\n\rRef is: %i %i %i\n", (int)refx, (int)refy, (int)refz);



  //   configureAccuAndMag();

     while(1){

    	 I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,READ_DATA, 1, rxBuff, 13, 1000);

    	 x = (int16_t)(((rxBuff[1] << 8) | rxBuff[2]))>> 2;
    	 y = (int16_t)(((rxBuff[3] << 8) | rxBuff[4]))>> 2;
    	 z = (int16_t)(((rxBuff[5] << 8) | rxBuff[6]))>> 2;
    	 // copy the magnetometer byte data into 16 bit words
    	 mx = (int16_t)((rxBuff[7] << 8) | rxBuff[8]);
    	 my = (int16_t)((rxBuff[9] << 8) | rxBuff[10]);
    	 mz = (int16_t)((rxBuff[11] << 8) | rxBuff[12]);
    	// magnet = (int)(sqrt(pow((mx- (int)refx),2)+pow((my- (int)refy),2)+pow((mz- (int)refz),2)))/10;
    	 magnet = (int)(sqrt(pow(mx,2)+pow(my,2)+pow(mz,2)))/10;

    	// PRINTF("\rAccu is: x=%i y=%i z=%i  Max is: x=%i y= =%i z=%i ",x,y,z,mx,my,mz);
    	 PRINTF("\rAccu is: x=%06i y=%06i z=%06i  Max is: %06i",x,y,z,magnet);



     }


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

void configureAccuAndMag(device){

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
