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
#include "LWs2812.h"
#include "wire.h"


void LWs2812Class::power_off()
{
	unsigned char DataBuf[2] = {0};
	DataBuf[0] = RGB_SET_MODE;
	DataBuf[1] = RGB_POWER_OFF;
	Wire.begin();
	Wire.beginTransmission(RGB_WS2812_Address);
	Wire.write(DataBuf,2);
	Wire.endTransmission();
}
	
void LWs2812Class::power_on()
{
	unsigned char DataBuf[2] = {0};
	DataBuf[0] = RGB_SET_MODE;
	DataBuf[1] = RGB_POWER_ON;
	Wire.begin();
	Wire.beginTransmission(RGB_WS2812_Address);
	Wire.write(DataBuf,2);
	Wire.endTransmission();
}

unsigned char LWs2812Class::check_on_line()
{
	unsigned char DataBuf[4] = {0};
	unsigned char i = 0;
	Wire.begin();
	Wire.beginTransmission(RGB_WS2812_Address);
	Wire.endTransmission();
	Wire.requestFrom(RGB_WS2812_Address, 4);
	while(Wire.available())
    {
		DataBuf[i++] = Wire.read();
    }
	if(DataBuf[3] == RGB_WS2812_Address)
	{
		power_on();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void LWs2812Class::set_pixel_color(unsigned long ulRGB, unsigned char ucNum)
{
	unsigned char DataBuf[5] = {0};

	DataBuf[0] = RGB_SET_WORK;
	DataBuf[1] = ucNum;
	DataBuf[2] = ((ulRGB >> 16) & 0xff);
	DataBuf[3] = ((ulRGB >> 8) & 0xff);
	DataBuf[4] = (ulRGB & 0xff);

	Wire.begin();
	Wire.beginTransmission(RGB_WS2812_Address);
	Wire.write(DataBuf,5);
	Wire.endTransmission();
}

void LWs2812Class::monochrome(unsigned char ucNum, unsigned long ulRGBData, unsigned int uiTime)
{
	unsigned char DataBuf[8] = {0};
	
	DataBuf[0] = RGB_SET_MODE;
	DataBuf[1] = RGB_MONOCHROME;
	DataBuf[2] = ucNum;
	DataBuf[3] = (ulRGBData >> 16) & 0xff;
	DataBuf[4] = (ulRGBData >> 8) & 0xff;
	DataBuf[5] = ulRGBData & 0xff;
	DataBuf[6] = (uiTime >> 8) & 0xff;
	DataBuf[7] = uiTime & 0xff;
	
	Wire.begin();
	Wire.beginTransmission(RGB_WS2812_Address);
	Wire.write(DataBuf,8);
	Wire.endTransmission();
}

void LWs2812Class::marquee(unsigned char ucNum, unsigned long ulRGBData, unsigned int uiTime)
{
	unsigned char DataBuf[8] = {0};

	DataBuf[0] = RGB_SET_MODE;
	DataBuf[1] = RGB_MARQUEE;
	DataBuf[2] = ucNum;
	DataBuf[3] = (ulRGBData >> 16) & 0xff;
	DataBuf[4] = (ulRGBData >> 8) & 0xff;
	DataBuf[5] = ulRGBData & 0xff;
	DataBuf[6] = (uiTime >> 8) & 0xff;
	DataBuf[7] = uiTime & 0xff;
	
	Wire.begin();
	Wire.beginTransmission(RGB_WS2812_Address);
	Wire.write(DataBuf,8);
	Wire.endTransmission();
}
	
void LWs2812Class::rainbow(unsigned char ucNum, unsigned int uiTime)
{
	unsigned char DataBuf[5] = {0};

	DataBuf[0] = RGB_SET_MODE;
	DataBuf[1] = RGB_RAINBOW;
	DataBuf[2] = ucNum;
	DataBuf[3] = (uiTime >> 8) & 0xff;
	DataBuf[4] = uiTime & 0xff;

	Wire.begin();
	Wire.beginTransmission(RGB_WS2812_Address);
	Wire.write(DataBuf,5);
	Wire.endTransmission();
}

LWs2812Class LWs2812;

