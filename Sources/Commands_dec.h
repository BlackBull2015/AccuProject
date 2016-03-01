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

char* CommandsBlue[10] = {"LFT","RGH","FRW","BCK","LVL"
		,"TST","LVP","LDO","LCK","UCK"};

#define LFT 1	//Bluetooth Left Command 1
#define RGH 2	//Bluetooth Right Command 2
#define	FRW 3	//Bluetooth Forward Command 3
#define	BCK 4	//Bluetooth Backwords Command 4
#define	LVL 5	//Bluetooth Level Platform Command 5
#define	TST 6	//Bluetooth Test Command 6
#define	LCK 7	//Bluetooth Lock Device Command 7
#define	UCK 8	//Bluetooth Unlock Device Command 8
#define LVP 9	//Bluetooth Platform Up Command 9
#define LDO 10	//Bluetooth Platform Down Command 10


///////////////////////////////////////////////////////////////////////////////
// Commands to send to ATMEGA168
///////////////////////////////////////////////////////////////////////////////
char* CommandsMicro[14] = {"LEFT","RIGHT","FORWARD","BACK","LEVELIT"
		,"TEST","LEVELUP","LEVELDOWN","LOCK","UNLOCK","ACCULEFT"
,"ACCURIGHT","ACCUBACK","ACCUFRONT"};

#define LEFT 01		//Turn left to atmega
#define RIGHT 02	//Turn right for atmega
#define FORWARD 03	//Go Forward
#define BACK 04		//Move bakwards
#define LEVELIT 05	//Level testing command
#define TEST 06		//Send a test command to micro
#define LEVELUP 07	//Move platform up
#define LEVELDOWN 08//Move platform down
#define LOCK 09		//lock the device
#define UNLOCK 10	//Unlock the device

#define ACCULEFT 11	//Reading from accelerometer that left side is lifted
#define ACCURIGHT 12//Reading from accelerometer that right side is lifted
#define ACCUBACK 13	//Reading from accelerometer that back is lifted
#define ACCUFRONT 14//Reading from accelerometer that front is lifted







char left[] = "LEFT";
char right[] = "RIGHT";
char front[] = "FRONT";
char back[] = "BACK";

#endif
