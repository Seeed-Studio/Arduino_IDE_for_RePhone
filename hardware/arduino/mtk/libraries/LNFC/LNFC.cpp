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

#include "arduino.h"
#include "LNFC.h"
#include "wire.h"


unsigned char uid[10] = {0};
unsigned char ptr[64] = {0};


unsigned char LNFCClass::check_online(void)
{
	unsigned char data[6];
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(NFC_SCAN_ID);
	Wire.endTransmission();
	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(0);
	Wire.endTransmission();

	for(i=0;i<6;i++)
	{
		Wire.requestFrom(NFC_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
			//Serial1.println(data[i]);
		}
	}

	if(data[5] == NFC_DEVICE_ADDR)return 1;
	else return 0;
}

void LNFCClass::adapter_init(void)
{
	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(NFC_ADAPTER_INIT_ID);
	Wire.endTransmission();
	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(0);
	Wire.endTransmission();
}

unsigned char *LNFCClass::adapter_get_uid(void)
{
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(NFC_ADAPTER_GET_UID_ID);
	Wire.endTransmission();
	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(0);
	Wire.endTransmission();

	for(i=0;i<10;i++)uid[i] = 0;
	
	for(i=0;i<2;i++)
	{
		Wire.requestFrom(NFC_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			uid[i] = Wire.read();
		}
	}

	for(i=0;i<uid[1];i++)
	{	
		Wire.requestFrom(NFC_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			uid[i + 2] = Wire.read();
		}
	}
	uid[uid[1] + 2] = '\0';

	return (unsigned char *)uid;
}

unsigned char *LNFCClass::adapter_read(void)
{
	unsigned char data[2];
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(NFC_ADAPTER_READ_ID);
	Wire.endTransmission();
	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(0);
	Wire.endTransmission();

	for(i=0;i<2;i++)
	{
		Wire.requestFrom(NFC_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

	unsigned char length = data[1];

	for(i=0;i<64;i++)ptr[i] = 0;
	
	*ptr = data[0];
	*(ptr + 1) = data[1];
	*(ptr + length + 2) = '\0';

	for(i=0;i<*(ptr + 1);i++)
	{
		Wire.requestFrom(NFC_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			*(ptr + i + 2) = Wire.read();
		}
	}

	return ptr;
}

void LNFCClass::adapter_write(char *string)
{
	unsigned char length;
	unsigned char i;

	length = strlen(string);
	
	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(NFC_ADAPTER_WRITE_ID);
	Wire.endTransmission();
	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(length);
	Wire.endTransmission();
	
	for(i=0;i<length;i++)
	{		
		Wire.begin();
		Wire.beginTransmission(NFC_DEVICE_ADDR);
		Wire.write(*(string + i));
		Wire.endTransmission();
	}
}

void LNFCClass::adapter_erase(void)
{
	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(NFC_ADAPTER_ERASE_ID);
	Wire.endTransmission();
	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(0);
	Wire.endTransmission();
}

void LNFCClass::emulate_init(unsigned char *id)
{
	unsigned char i;
	
	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(NFC_EMULATE_INIT_ID);
	Wire.endTransmission();
	Wire.begin();
	Wire.beginTransmission(NFC_DEVICE_ADDR);
	Wire.write(3);
	Wire.endTransmission();

	for(i=0;i<3;i++)
	{
		Wire.begin();
		Wire.beginTransmission(NFC_DEVICE_ADDR);
		Wire.write(*(id + i));
		Wire.endTransmission();
	}
}

LNFCClass LNFC;

