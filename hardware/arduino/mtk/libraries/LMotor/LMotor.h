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


#ifndef _LMOTOR_H
#define _LMOTOR_H

#include "LTask.h"

#define MOTOR_Address       34

#define MOTOR_SET_WORK   	0x80
#define MOTOR_SET_MODE  	0x81

#define MOTOR_MODE_SHORT        0x00
#define MOTOR_MODE_LONG         0x01
#define MOTOR_MODE_INTERVAL     0x02


class LMotorClass : public _LTaskClass
{
public:
	LMotorClass() { };
	
public:
	/**
	 *  \brief Get the status of the motor device.
	 *
	 *  \return Return TRUE or FALSE. TRUE is on line, FALSE is off line.
	 */
	unsigned char check_on_line();
	
	/**
	 *  \brief Set the motor work with time.
	 *
	 *  \param [in] uiTime the time of working.
	 *  
	 *  \return Return Null.
	 */
	void set_work(unsigned int uiTime);
	
    /**
	 *  \brief Set the motor work with mode.
	 *
	 *  \param [in] ucMode the mode of working.
	 *  
	 *  \return Return Null.
	 */
	void set_mode(unsigned char ucMode);
	
private:

};

extern LMotorClass LMotor;

#endif
