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
#include "LMotor.h"
#include "wire.h"


unsigned char LMotorClass::check_on_line()
{
	unsigned char DataBuf[4] = {0};
	unsigned char i = 0;
	Wire.begin();
	Wire.beginTransmission(MOTOR_Address);
	Wire.endTransmission();
	Wire.requestFrom(MOTOR_Address, 4);
	while(Wire.available())
    {
		DataBuf[i++] = Wire.read();
    }
	if(DataBuf[3] == MOTOR_Address)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void LMotorClass::set_work(unsigned int uiTime)
{
	unsigned char DataBuf[3] = {0};

	DataBuf[0] = MOTOR_SET_WORK;
	DataBuf[1] = ((uiTime >> 8) & 0xff);
	DataBuf[2] = (uiTime & 0xff);

	Wire.begin();
	Wire.beginTransmission(MOTOR_Address);
	Wire.write(DataBuf,3);
	Wire.endTransmission();
}

void LMotorClass::set_mode(unsigned char ucMode)
{
	unsigned char DataBuf[2] = {0};
	
	DataBuf[0] = MOTOR_SET_MODE;
	DataBuf[1] = ucMode;
	
	Wire.begin();
	Wire.beginTransmission(MOTOR_Address);
	Wire.write(DataBuf,2);
	Wire.endTransmission();
}

LMotorClass LMotor;

