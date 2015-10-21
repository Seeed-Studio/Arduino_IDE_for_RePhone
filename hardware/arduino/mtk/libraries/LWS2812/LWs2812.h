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


#ifndef _LWS2812_H
#define _LWS2812_H

#include "LTask.h"

#define RGB_WS2812_Address	35

#define RGB_SET_WORK 0x80
#define RGB_SET_MODE 0x81

#define RGB_POWER_OFF           0
#define RGB_POWER_ON            1
#define RGB_MONOCHROME          2
#define RGB_MARQUEE             3
#define RGB_RAINBOW             4


class LWs2812Class : public _LTaskClass
{
public:
	LWs2812Class() { };
	
public:
	/**
	 *  \brief Power off ws2812.
	 *  
	 *  \return Return Null.
	 */
	void power_off();
	
	/**
	 *  \brief Power on ws2812.
	 *  
	 *  \return Return Null.
	 */
	 
	void power_on();
	/**
	 *  \brief Get the status of the ws2812 device.
	 *
	 *  \return Return TRUE or FALSE. TRUE is on line, FALSE is off line.
	 */
	unsigned char check_on_line();
	
	/**
	 *  \brief Display one pixel.  
	 *  
	 *  \param [in] ulRGB the colour of pixel, format is R:G:B -> 255:255:255
	 *  \param [in] ucNum the number of pixel
	 *  
	 *  \return Return Null.
	 */
	void set_pixel_color(unsigned long ulRGB, unsigned char ucNum);
	
	/**
	 *  \brief Display pixels by monochrome mode.  
	 *  
	 *  \param [in] ucNum the number of pixel
	 *  \param [in] ulRGBData the colour of pixel, format is R:G:B -> 255:255:255
	 *  \param [in] uiTime the time of char want to display.
	 *  
	 *  \return Return Null.
	 */
	void monochrome(unsigned char ucNum, unsigned long ulRGBData, unsigned int uiTime);
	
	/**
	 *  \brief Display pixels by marquee mode.  
	 *  
	 *  \param [in] ucNum the number of pixel
	 *  \param [in] ulRGBData the colour of pixel, format is R:G:B -> 255:255:255
	 *  \param [in] uiTime the time of char want to display.
	 *  
	 *  \return Return Null.
	 */
	void marquee(unsigned char ucNum, unsigned long ulRGBData, unsigned int uiTime);
	
	/**
	 *  \brief Display pixels by rainbow mode.  
	 *  
	 *  \param [in] ucNum the number of pixel
	 *  \param [in] uiTime the time of char want to display.
	 *  
	 *  \return Return Null.
	 */
	void rainbow(unsigned char ucNum, unsigned int uiTime);
	
private:

};

extern LWs2812Class LWs2812;

#endif
