/*
 * Commands_dec.h
 *
 *  Created on: Feb 9, 2016
 *      Author: Eric
 */

#ifndef COMMANDS_SET
#define COMMANDS_SET

///////////////////////////////////////////////////////////////////////////////
//  Commands that are recievied from bluetooth
///////////////////////////////////////////////////////////////////////////////
#define LFT 50	//Bluetooth Left Command
#define RGH 51	//Bluetooth Right Command
#define	FRW 52	//Bluetooth Forward Command
#define	BCK 53	//Bluetooth Backwords Command
#define	LVL 54	//Bluetooth Level Platform Command
#define	TST 55	//Bluetooth Test Command
#define	LCK 56	//Bluetooth Lock Device Command
#define	UCK 57	//Bluetooth Unlock Device Command
#define LVP 58	//Bluetooth Platform Up Command
#define LDO 59	//Bluetooth Platform Down Command


///////////////////////////////////////////////////////////////////////////////
// Commands to send to ATMEGA168
///////////////////////////////////////////////////////////////////////////////
#define LEFT 01		//Turn left to atmega
#define RIGHT 02	//Turn right for atmega
#define FORWARD 03	//Go Forward
#define BACK 04		//Move bakwards
#define TEST 05		//Send a test command to micro
#define ACCULEFT 06	//Reading from accelerometer that left side is lifted
#define ACCURIGHT 07//Reading from accelerometer that right side is lifted
#define ACCUBACK 08	//Reading from accelerometer that back is lifted
#define ACCUFRONT 09//Reading from accelerometer that front is lifted
#define LEVELUP 10	//Move platform up
#define LEVELDOWN 11//Move platform down
#define LEVELIT 12	//Level testing command
#define LOCK 30		//lock the device
#define UNLOCK 31	//Unlock the device


char left[] = "LEFT";
char right[] = "RIGHT";
char front[] = "FRONT";
char back[] = "BACK";

#endif
