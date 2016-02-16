/*
 * Accu.h
 *
 *  Created on: Feb 2, 2016
 *      Author: Eric
 */

#ifndef SOURCES_ACCU_H_
#define SOURCES_ACCU_H_

#define DATA_LENGTH 13
#define I2C_INSTANCE_0 0
#define TRESHOLD 200

///////////////////////////////////////////////////////////////////////////////
//Accelerometer configuration files
///////////////////////////////////////////////////////////////////////////////
void i2cinitreg();
void getWhere(int x, int y);

int x,y,z,count, magnet;

// Buffer store data to receive from slave
uint8_t rxBuff[DATA_LENGTH] = {0};

//Test Register for who am i
uint8_t WHO_AM_I[1] = {0x0D};

//Read Register Data status
uint8_t READ_DATA[1] = {0x00};


///////////////////////////////////////////////////////////////////////////////
// Register addresses
///////////////////////////////////////////////////////////////////////////////
uint8_t ACCU_CTR_1[1] = {0x2A};
uint8_t MAG_CTR_1[1] = {0x5B};
uint8_t MAG_CTR_2[1] = {0x5C};
uint8_t XYZ_DATA_REG[1] = {0x0F};


///////////////////////////////////////////////////////////////////////////////
// Config Register Values
///////////////////////////////////////////////////////////////////////////////
//Standby Mode
uint8_t STN_ON[1] = {0x00};
uint8_t STN_OFF[1] = {0x0D};
//Mag
uint8_t MAG_REG_1[1] = {0x1F};
uint8_t MAG_REG_2[1] = {0x20};
//XYZ data set
uint8_t XYZ_DATA[1] = {0x01};




#endif /* SOURCES_ACCU_H_ */
