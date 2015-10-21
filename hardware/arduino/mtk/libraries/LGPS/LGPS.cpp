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
#include "LGPS.h"
#include "wire.h"


unsigned char gps_utc_date_time[GPS_UTC_DATE_TIME_SIZE] = {0};
	
	
unsigned char LGPSClass::check_online()
{
	unsigned char data[GPS_SCAN_SIZE+2] = {0};
	unsigned char i = 0;
	
	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_SCAN_ID);
	Wire.endTransmission();
	
	for(i=0;i<(GPS_SCAN_SIZE+2);i++)
	{
			Wire.requestFrom(GPS_DEVICE_ADDR, 1);
			while(Wire.available())
			{
				data[i] = Wire.read();
			}
	}
	
	//for(i=0;i<(GPS_SCAN_SIZE+2);i++)Serial1.println(data[i]);
	
	if(data[5] == GPS_DEVICE_ADDR)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

unsigned char* LGPSClass::get_utc_date_time(void)
{
	unsigned char data[GPS_UTC_DATE_TIME_SIZE+2];
	unsigned char i;
	
	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_UTC_DATE_TIME_ID);
	Wire.endTransmission();

	for(i=0;i<(GPS_UTC_DATE_TIME_SIZE+2);i++)
	{
		Wire.requestFrom(GPS_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

	for(i=0;i<GPS_UTC_DATE_TIME_SIZE;i++)
	gps_utc_date_time[i] = data[i+2];

	return gps_utc_date_time;
}

unsigned char LGPSClass::get_status(void)
{
	unsigned char data[GPS_STATUS_SIZE+2];
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_STATUS_ID);
	Wire.endTransmission();
	
	for(i=0;i<(GPS_STATUS_SIZE+2);i++)
	{
		Wire.requestFrom(GPS_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

	return data[2];
}

float LGPSClass::get_latitude(void)
{
	unsigned char data[GPS_LATITUDE_SIZE+2];
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_LATITUDE_ID);
	Wire.endTransmission();
	
	for(i=0;i<(GPS_LATITUDE_SIZE+2);i++)
	{
		Wire.requestFrom(GPS_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

	return atof((const char*)&data[2]);
}

unsigned char LGPSClass::get_ns(void)
{
	unsigned char data[GPS_NS_SIZE+2];
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_NS_ID);
	Wire.endTransmission();
	
	for(i=0;i<(GPS_NS_SIZE+2);i++)
	{
		Wire.requestFrom(GPS_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

    if(data[2] == 'N' || data[2] == 'S')return data[2];
    else return data[2] = '-';
}

float LGPSClass::get_longitude(void)
{
	unsigned char data[GPS_LONGITUDE_SIZE+2];
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_LONGITUDE_ID);
	Wire.endTransmission();
	
	for(i=0;i<(GPS_LONGITUDE_SIZE+2);i++)
	{
		Wire.requestFrom(GPS_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

	return atof((const char*)&data[2]);
}

unsigned char LGPSClass::get_ew(void)
{
	unsigned char data[GPS_EW_SIZE+2];
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_EW_ID);
	Wire.endTransmission();
	
	for(i=0;i<(GPS_EW_SIZE+2);i++)
	{
		Wire.requestFrom(GPS_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

	if(data[2] == 'E' || data[2] == 'W')return data[2];
	else return data[2] = '-';
}

float LGPSClass::get_speed(void)
{
	unsigned char data[GPS_SPEED_SIZE+2];
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_SPEED_ID);
	Wire.endTransmission();
	
	for(i=0;i<(GPS_SPEED_SIZE+2);i++)
	{
		Wire.requestFrom(GPS_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

	return atof((const char*)&data[2]);
}

float LGPSClass::get_course(void)
{
	unsigned char data[GPS_COURSE_SIZE+2];
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_COURSE_ID);
	Wire.endTransmission();
	
	for(i=0;i<(GPS_COURSE_SIZE+2);i++)
	{
		Wire.requestFrom(GPS_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

	return atof((const char*)&data[2]);
}

unsigned char LGPSClass::get_position_fix(void)
{
	unsigned char data[GPS_POSITION_FIX_SIZE+2];
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_POSITION_FIX_ID);
	Wire.endTransmission();
	
	for(i=0;i<(GPS_POSITION_FIX_SIZE+2);i++)
	{
		Wire.requestFrom(GPS_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

	return data[2];
}

unsigned char LGPSClass::get_sate_used(void)
{
	unsigned char data[GPS_SATE_USED_SIZE+2];
	unsigned char i;
	unsigned char value;

	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_SATE_USED_ID);
	Wire.endTransmission();	
	
	for(i=0;i<(GPS_SATE_USED_SIZE+2);i++)
	{
		Wire.requestFrom(GPS_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

	if(data[3] >= '0' && data[3] <= '9')value = (data[3] - '0') * 10;
	else value = 0;
	if(data[2] >= '0' && data[2] <= '9')value += (data[2] - '0');
	else value += 0;

	return value;
}

float LGPSClass::get_altitude(void)
{
	unsigned char data[GPS_ALTITUDE_SIZE+2];
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_ALTITUDE_ID);
	Wire.endTransmission();		
	
	for(i=0;i<(GPS_ALTITUDE_SIZE+2);i++)
	{
		Wire.requestFrom(GPS_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

	return atof((const char*)&data[2]);	
}

unsigned char LGPSClass::get_mode(void)
{
	unsigned char data[GPS_MODE_SIZE+2];
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_MODE_ID);
	Wire.endTransmission();		
	
	for(i=0;i<(GPS_MODE_SIZE+2);i++)
	{
		Wire.requestFrom(GPS_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

	return data[2];	
}

unsigned char LGPSClass::get_mode2(void)
{
	unsigned char data[GPS_MODE2_SIZE+2];
	unsigned char i;

	Wire.begin();
	Wire.beginTransmission(GPS_DEVICE_ADDR);
	Wire.write(GPS_MODE2_ID);
	Wire.endTransmission();	
	
	for(i=0;i<(GPS_MODE2_SIZE+2);i++)
	{
		Wire.requestFrom(GPS_DEVICE_ADDR, 1);
		while(Wire.available())
		{
			data[i] = Wire.read();
		}
	}

	return data[2];	
}


LGPSClass LGPS;

