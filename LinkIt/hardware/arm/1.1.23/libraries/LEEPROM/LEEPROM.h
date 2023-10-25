/*
  Copyright (c) 2014 MediaTek Inc.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License..

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
   See the GNU Lesser General Public License for more details.
*/


#ifndef _LINKITEEPROM_H
#define _LINKITEEPROM_H

#include "LTask.h"

//#include "vmsys.h"
/*****************************************************************************
 * Class LEEPROMClass
 ****************************************************************************/
 
// LEEPROMClass represents reading from and writing to a long term storage - EEPROM.
//
// EXAMPLE:
// <code>
// #include <LEEPROM.h>
// void setup() {
//   // Insert your setup code here to run it once:
//   
// }
//
// void loop() {
//   // Insert your main code here to run it repeatedly:
//   byte a = 1;
//   EEPROM.write(0, a);
//   byte b = EEPROM.read(0);
//   if (a == b)
//   {
//   	// Do something.
//   	delay(2000);
//   }
// }
// </code>
class LEEPROMClass : public _LTaskClass 
{
private:
    int m_init;

// Method
public:
    LEEPROMClass(int init);
    //~LEEPROMClass();
	// DESCRIPTION
    //Writes a byte to the EEPROM. 
    // RETURNS
    // VMUINT8
	// EXAMPLE
	// <code>
    // #include <EEPROM.h>
    // int a = 0;
    // int value;
    // void setup()
    // {
    //   Serial.begin(9600);
    // }
    // void loop()
    // {
    //   value = EEPROM.read(a);
    // 
    //   Serial.print(a);
    //   Serial.print("\t");
    //   Serial.print(value);
    //   Serial.println();
    //   a = a + 1;
    //   if (a == 512)
    //     a = 0;
    //   delay(500);
    // }
	// </code> 
	VMUINT8 read(
	        int addr // addr: The location to read from, starting from 0 (Integer). 
	        ); 
	
	// DESCRIPTION
    //Writes a byte to the EEPROM. 
    // RETURNS
    // void
	// EXAMPLE
	// <code>
    // #include <EEPROM.h>
    // 
    // void setup()
    // {
    //   for (int i = 0; i < 512; i++)
    //     EEPROM.write(i, i);
    // }
    // 
    // void loop()
    // {
    // }
	// </code> 
	void write(
	    int addr, // addr: The location to write to, starting from 0 (Integer).
	    uint8_t value // value: The value to write, from 0 to 255 (Bytes).
	    );
};

extern LEEPROMClass & getEEPROM(void);
#define EEPROM getEEPROM()

#endif

