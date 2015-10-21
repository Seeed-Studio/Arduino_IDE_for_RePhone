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


#ifndef _LSENSORHUB_H
#define _LSENSORHUB_H

#include "LTask.h"

#define SensorHubAddress	3

class LSensorHubClass : public _LTaskClass
{
public:
	LSensorHubClass() { };
	
public:
	/**
	 *  \brief Get the status of the sensor hub device.
	 *
	 *  \return Return TRUE or FALSE. TRUE is on line, FALSE is off line.
	 */
	unsigned char check_on_line();
	
	/**
	 *  \brief Get the data of acceleration.  
	 *  
	 *  \param [in] x the pointer of acc_x
	 *  \param [in] y the pointer of acc_y
	 *  \param [in] z the pointer of acc_z
	 *  
	 *  \return Return Null.
	 */
	void GetAccData(long* x, long* y, long* z);
	
	/**
	 *  \brief Get the data of light.  
	 *  
	 *  \param [in] lux the pointer of light
	 *  
	 *  \return Return Null.
	 */
	void GetLighData(unsigned long* lux);
	
	/**
	 *  \brief Get the data of temperature.  
	 *  
	 *  \param [in] temp the pointer of temperature
	 *  
	 *  \return Return Null.
	 */
	void GetTempData(long* temp);
	
private:

};

extern LSensorHubClass LSensorHub;

#endif
