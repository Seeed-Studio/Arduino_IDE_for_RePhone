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


#ifndef _LCHECKSIM_H
#define _LCHECKSIM_H

#include "LTask.h"


// LBattery class interface, With this library, you can get battery infomation like charging status and battery level
class LCheckSIMClass  : public _LTaskClass {

// Constructor / Destructor
public:
	LCheckSIMClass() { };

// Method
public:
	// DESCRIPTION
	//     SIM is inset or not.
	// RETURNS
	//     true: in inset state, false: not in inset state
	boolean isCheck();

private:
	boolean m_check;
};

extern LCheckSIMClass LCheckSIM;

#endif
