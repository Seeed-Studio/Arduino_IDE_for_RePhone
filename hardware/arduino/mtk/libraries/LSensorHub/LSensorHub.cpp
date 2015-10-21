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
#include "LSensorHub.h"
#include "wire.h"


unsigned char LSensorHubClass::check_on_line()
{
	unsigned char DataBuf[4] = {0};
	unsigned char i = 0;
	Wire.begin();
	Wire.beginTransmission(SensorHubAddress);
	Wire.write(0);
	Wire.endTransmission();
	Wire.requestFrom(SensorHubAddress, 4);
	while(Wire.available())
    {
		DataBuf[i++] = Wire.read();
    }
	if(DataBuf[3] == 5)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void LSensorHubClass::GetAccData(long* x, long* y, long* z)
{
	unsigned char DataBuf[10] = {0};
	unsigned char i;
	long DataX = 0; 
	long DataY = 0; 
	long DataZ = 0;
	
	Wire.begin();
	Wire.beginTransmission(SensorHubAddress);
	Wire.write(4);
	Wire.endTransmission();
	Wire.requestFrom(SensorHubAddress, 8);
	i = 0;
	while(Wire.available())
    {
		DataBuf[i++] = Wire.read();
    }
	DataX |= DataBuf[7] << 24;
	DataX |= DataBuf[6] << 16;
	DataX |= DataBuf[5] << 8;
	DataX |= DataBuf[4];
	
	Wire.beginTransmission(SensorHubAddress);
	Wire.write(12);
	Wire.endTransmission();
	Wire.requestFrom(SensorHubAddress, 8);
	i = 0;
	while(Wire.available())
    {
		DataBuf[i++] = Wire.read();
    }
	DataY |= DataBuf[7] << 24;
	DataY |= DataBuf[6] << 16;
	DataY |= DataBuf[5] << 8;
	DataY |= DataBuf[4];
	
	Wire.beginTransmission(SensorHubAddress);
	Wire.write(20);
	Wire.endTransmission();
	Wire.requestFrom(SensorHubAddress, 8);
	i = 0;
	while(Wire.available())
    {
		DataBuf[i++] = Wire.read();
    }
	DataZ |= DataBuf[7] << 24;
	DataZ |= DataBuf[6] << 16;
	DataZ |= DataBuf[5] << 8;
	DataZ |= DataBuf[4];
	
	*x = DataX;
	*y = DataY;
	*z = DataZ;
}

void LSensorHubClass::GetLighData(unsigned long* lux)
{
	unsigned char DataBuf[10] = {0};
	unsigned char i = 0;
	long Data32;
	
	Wire.begin();
	Wire.beginTransmission(SensorHubAddress);
	Wire.write(28);
	Wire.endTransmission();
	Wire.requestFrom(SensorHubAddress, 8);
	while(Wire.available())
    {
		DataBuf[i++] = Wire.read();
    }
	
	Data32 |= DataBuf[7] << 24;
	Data32 |= DataBuf[6] << 16;
	Data32 |= DataBuf[5] << 8;
	Data32 |= DataBuf[4];
	
	*lux = Data32;
}

void LSensorHubClass::GetTempData(long* temp)
{
	unsigned char DataBuf[10] = {0};
	unsigned char i = 0;
	long Data32;
	
	Wire.begin();
	Wire.beginTransmission(SensorHubAddress);
	Wire.write(36);
	Wire.endTransmission();
	Wire.requestFrom(SensorHubAddress, 8);
	while(Wire.available())
    {
		DataBuf[i++] = Wire.read();
    }
	
	Data32 |= DataBuf[7] << 24;
	Data32 |= DataBuf[6] << 16;
	Data32 |= DataBuf[5] << 8;
	Data32 |= DataBuf[4];
	
	*temp = Data32;
}

LSensorHubClass LSensorHub;

