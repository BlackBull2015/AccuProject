/*
 * Arkadiusz Bochen
 * G00291410
 * Main project Year 5
 * SLATAV main code for kl26z
 *
 *During Development
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
#include "Accu_Includes.h"
#include "fsl_uart_hal.h"
#include "fsl_uart_driver.h"
#include "UART2_Interrupt.h"
//#include "fsl_uart.h"

///////////////////////////////////////////////////////////////////////////////
// Code
///////////////////////////////////////////////////////////////////////////////

//void UART1_IRQHandler(void)
//{
//	UART_DRV_IRQHandler(1);
//}
int main(void)
{


//Simple UART1

//	 // Init hardware
//	uart_state_t uartState1; // user provides memory for the driver state structure
//	uart_user_config_t uartConfig1;
//
//	hardware_init();
//	configure_uart_pins(0);
//
//
//	 OSA_Init();
//
//
//	uartConfig1.baudRate = 9600;
//	uartConfig1.bitCountPerChar = kUart8BitsPerChar;
//	uartConfig1.parityMode = kUartParityDisabled;
//	uartConfig1.stopBitCount = kUartOneStopBit;
//
//PRINTF("Just to init Uart\r");
//	UART_DRV_Init(1,  &uartState1, &uartConfig1);
//	PRINTF("Uart initilized\n\r");
//
//	while(1){
//		PRINTF("About to send data\n\r");
//UART_DRV_SendDataBlocking(1, AT, sizeof(AT),16000u); // function
////	UART_DRV_ReceiveDataBlocking(1, &TXBUFF, 2,16000); // function
////	 PRINTF("\n\rWho am i register value is: %01X", TXBUFF[0]);
//
//	//PRINTF()
//	PRINTF("Tried to sent some\n");
//
//	}


	//Accu init
    i2c_master_state_t master;
    i2c_device_t device =
    {
      .address = 0x1DU,
      .baudRate_kbps = 400   // 400 Kbps
    };
    hardware_init();
    UART2_config(9600);
    enable_UART2_receive_interrupt();
    i2cinitreg();

    // Initialize OSA
    OSA_Init();

    // Initialize i2c master
    I2C_DRV_MasterInit(I2C_INSTANCE_0, &master);
    configureAccuAndMag(device);

    PRINTF("\r\n==================== I2C MASTER BLOCKING ===================\r\n");
    PRINTF("\r\n1. Master checks who am i register\
    \r\n2. Master configures accelerometer and magnetometer\
    \r\n3. Takes 200 samples, average them and displays results\r\n");
    PRINTF("\r\n============================================================\r\n\n");

    PRINTF("Press any key to start transfer:\r\n\n");
    GETCHAR();


     while(1){

    	 x = 0;
    	 y = 0;
    	 z = 0;
    	 for(count = 0; count < 200; count++){
    		 I2C_DRV_MasterReceiveDataBlocking(I2C_INSTANCE_0, &device,READ_DATA, 1, rxBuff, 13, 1000);

    		     	 x += (int16_t)(((rxBuff[1] << 8) | rxBuff[2]))>> 2;
    		     	 y += (int16_t)(((rxBuff[3] << 8) | rxBuff[4]))>> 2;
    		     	 z += (int16_t)(((rxBuff[5] << 8) | rxBuff[6]))>> 2;
    	 }
    	 x = x/200;
    	 y = y/200;
    	 getWhere(x,y);
     }

    PRINTF("\r\n==================== I2C MASTER FINISH =================== \r\n");

    // Deinit i2c
    I2C_DRV_MasterDeinit(0);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Pin configure
///////////////////////////////////////////////////////////////////////////////
void i2cinitreg(){
    PORTE_PCR24 |= (0x05u)<<8 | 0x03u;
    PORTE_PCR25 |= (0x05u)<<8 | 0x03u;
}
///////////////////////////////////////////////////////////////////////////////
// Get lift side
///////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
// Accu configuration
///////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////
// UART2 Interrupt Handler Echos received character
/////////////////////////////////////////////////////////////////////////////
void UART2_IRQHandler(void)
{
	int count,size;
    if(UART2_S1 & UART_S1_RDRF_MASK){
    	if(UART2_D != '\r')
    		CommandBuffer[BufferStage++] = UART2_D;
    	else{
    		size = BufferStage;
    		BufferStage = 0;
    		for(count = 0;count < size; count ++){
    			PUTCHAR(CommandBuffer[BufferStage++]);
    		}
    		BufferStage = 0;
    		memset(CommandBuffer,0,sizeof(CommandBuffer));
    	}
    //	PUTCHAR(UART2_D);	//Test for sending all characters
    }

}
///////////////////////////////////////////////////////////////////////////////
//Function to configure UART2
///////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
// Configure NVIC
///////////////////////////////////////////////////////////////////////////////
void enable_UART2_receive_interrupt()
{

	NVIC_ClearPendingIRQ(14);
	NVIC_EnableIRQ(14);
	UART2_C2 |= UART_C2_RIE_MASK;	//set RIE to enable receive interrupt
}
///////////////////////////////////////////////////////////////////////////////
// Function to transmit a single character to the UART2 TXD pin
///////////////////////////////////////////////////////////////////////////////
void put_char(char c)
{
	while((UART2_S1 & UART_S1_TDRE_MASK) == 0) //wait until tx buffer is empty
	{}
	UART2_D = c;
}


/*******************************************************************************
 * EOF
 ******************************************************************************/
