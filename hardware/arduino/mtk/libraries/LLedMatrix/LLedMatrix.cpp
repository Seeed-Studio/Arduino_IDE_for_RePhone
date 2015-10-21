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
#include "LLedMatrix.h"
#include "wire.h"


unsigned char LLedMatrixClass::check_on_line()
{
	unsigned char DataBuf[4] = {0};
	unsigned char i = 0;
	Wire.begin();
	Wire.beginTransmission(LEDAddress);
	Wire.endTransmission();
	Wire.requestFrom(LEDAddress, 4);
	while(Wire.available())
    {
		DataBuf[i++] = Wire.read();
    }
	if(DataBuf[3] == LEDAddress)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void LLedMatrixClass::disp_string(const char uData[],unsigned char uDataLength,unsigned int uTime)
{
	unsigned char buffer[20] = {0};
	unsigned char i;
	
	if(uDataLength > 4)return;
	buffer[0] = DISP_STRING;
	buffer[1] = uDataLength;
	for(i=0;i<uDataLength;i++)buffer[i + 2] = *(uData ++);
	buffer[i+2] = uTime >> 8;
	buffer[i+3] = uTime;
	
	Wire.begin();
	Wire.beginTransmission(LEDAddress);
	Wire.write(buffer,uDataLength + 4);
	Wire.endTransmission();
}

void LLedMatrixClass::disp_char(const char uData,unsigned int uTime)
{
	unsigned char buffer[4] = {0};
	unsigned char  i;
	
	buffer[0] = DISP_CHAR_5X7;
	buffer[1] = uData;
	buffer[2] = uTime >> 8;
	buffer[3] = uTime;

	Wire.begin();
	Wire.beginTransmission(LEDAddress);
	Wire.write(buffer,4);
	Wire.endTransmission();
}

void LLedMatrixClass::set_disp_orientation(unsigned char orientation)
{
	
}

void LLedMatrixClass::disp_pic(unsigned char uPicNum, unsigned int uTime)
{
	unsigned char buffer[4] = {0};
	unsigned char  i;
	
	buffer[0] = DISP_PIC;
	buffer[1] = uPicNum;
	buffer[2] = uTime >> 8;
	buffer[3] = uTime;

	Wire.begin();
	Wire.beginTransmission(LEDAddress);
	Wire.write(buffer,4);
	Wire.endTransmission();
}


LLedMatrixClass LedMatrix;

