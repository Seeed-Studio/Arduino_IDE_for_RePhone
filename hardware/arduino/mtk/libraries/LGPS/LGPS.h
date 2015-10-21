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


#ifndef _LGPS_H
#define _LGPS_H

#include "LTask.h"


/*!
	\def GPS_DEVICE_ADDR
	The I2C address GPS

	\def GPS_SCAN_ID
	The id of scan data, the format is 0,0,0,Device address
	\def GPS_SCAN_SIZE
	The length of scan data

	\def GPS_UTC_DATE_TIME_ID
	The id of utc date and time, the format is YMDHMS
	\def GPS_UTC_DATE_TIME_SIZE
	The length of utc date and time data

	\def GPS_STATUS_ID
	The id of GPS status, the format is A/V
	\def GPS_STATUS_SIZE
	The length of GPS status data

	\def GPS_LATITUDE_ID
	The id of latitude, the format is dd.dddddd
	\def GPS_LATITUDE_SIZE
	The length of latitude data

	\def GPS_NS_ID
	The id of latitude direction, the format is N/S
	\def GPS_NS_SIZE
	The length of latitude direction data

	\def GPS_LONGITUDE_ID
	The id of longitude, the format is ddd.dddddd
	\def GPS_LONGITUDE_SIZE
	The length of longitude data

	\def GPS_EW_ID
	The id of longitude direction, the format is E/W
	\def GPS_EW_SIZE
	The length of longitude direction data

	\def GPS_SPEED_ID
	The id of speed, the format is 000.0~999.9 Knots
	\def GPS_SPEED_SIZE
	The length of speed data

	\def GPS_COURSE_ID
	The id of course, the format is 000.0~359.9
	\def GPS_COURSE_SIZE
	The length of course data

	\def GPS_POSITION_FIX_ID
	The id of position fix status, the format is 0,1,2,6
	\def GPS_POSITION_FIX_SIZE
	The length of position fix status data

	\def GPS_SATE_USED_ID
	The id of state used, the format is 00~12
	\def GPS_SATE_USED_SIZE
	The length of sate used data

	\def GPS_ALTITUDE_ID
	The id of altitude, the format is -9999.9~99999.9
	\def GPS_ALTITUDE_SIZE
	The length of altitude data

	\def GPS_MODE_ID
	The id of locate mode, the format is A/M
	\def GPS_MODE_SIZE
	The length of locate mode data

	\def GPS_MODE2_ID
	The id of current status, the format is 1,2,3
	\def GPS_MODE2_SIZE
	The length of current status data
*/

/* Data format:
 * ID(1 byte), Data length(1 byte), Data 1, Data 2, ... Data n (n bytes, n = data length)
 * For example, get the scan data.
 * First, Send GPS_SCAN_ID(1 byte) to device.
 * Second, Receive scan data(ID + Data length + GPS_SCAN_SIZE = 6 bytes).
 * Third, The scan data begin from the third data of received.
 * End
 */
#define GPS_DEVICE_ADDR			0x05

#define GPS_SCAN_ID				0 // 4 bytes
#define GPS_SCAN_SIZE			4 // 0,0,0,Device address

#define GPS_UTC_DATE_TIME_ID	1 // YMDHMS
#define GPS_UTC_DATE_TIME_SIZE  6 // 6 bytes

#define GPS_STATUS_ID			2 // A/V
#define GPS_STATUS_SIZE			1 // 1 byte

#define GPS_LATITUDE_ID			3 // dd.dddddd
#define GPS_LATITUDE_SIZE		9 // 9 bytes

#define GPS_NS_ID				4 // N/S
#define GPS_NS_SIZE				1 // 1 byte

#define GPS_LONGITUDE_ID		5 // ddd.dddddd
#define GPS_LONGITUDE_SIZE		10 // 10 bytes

#define GPS_EW_ID				6 // E/W
#define GPS_EW_SIZE				1 // 1 byte

#define GPS_SPEED_ID			7 // 000.0~999.9 Knots
#define GPS_SPEED_SIZE			5 // 5 bytes

#define GPS_COURSE_ID			8 // 000.0~359.9
#define GPS_COURSE_SIZE			5 // 5 bytes

#define GPS_POSITION_FIX_ID		9 // 0,1,2,6
#define GPS_POSITION_FIX_SIZE	1 // 1 byte

#define GPS_SATE_USED_ID		10 // 00~12
#define GPS_SATE_USED_SIZE		2 // 2 bytes

#define GPS_ALTITUDE_ID			11 // -9999.9~99999.9
#define GPS_ALTITUDE_SIZE		7 // 7 bytes

#define GPS_MODE_ID				12 // A/M
#define GPS_MODE_SIZE			1 // 1 byte

#define GPS_MODE2_ID			13 // 1,2,3
#define GPS_MODE2_SIZE			1 // 1 byte


class LGPSClass : public _LTaskClass
{
public:
	LGPSClass() { };
	
public:
	/**
	 *  \brief Get the status of the device.
	 *
	 *  \return Return TRUE or FALSE. TRUE is on line, FALSE is off line.
	 *
	 */
	unsigned char check_online(void);

	/**
	 *  \brief Get the utc date and time.
	 *
	 *  \return Return the pointer of utc date sand time, the format is YMDHMS.
	 *
	 */
	unsigned char* get_utc_date_time(void);

	/**
	 *  \brief Get the status of GPS.
	 *
	 *  \return Return A or V. A is orientation, V is navigation.
	 *
	 */
	unsigned char get_status(void);

	/**
	 *  \brief Get the altitude.
	 *
	 *  \return Return altitude data. The format is dd.dddddd.
	 *
	 */
	float get_latitude(void);

	/**
	 *  \brief Get the altitude direction.
	 *
	 *  \return Return altitude direction data. The format is N/S. N is north, S is south.
	 *
	 */
	unsigned char get_ns(void);

	/**
	 *  \brief Get the longitude.
	 *
	 *  \return Return longitude data. The format is ddd.dddddd.
	 *
	 */
	float get_longitude(void);

	/**
	 *  \brief Get the longitude direction.
	 *
	 *  \return Return longitude direction data. The format is E/W. E is east, W is west.
	 *
	 */
	unsigned char get_ew(void);

	/**
	 *  \brief Get the speed.
	 *
	 *  \return Return speed data. The format is 000.0~999.9 Knots.
	 *
	 */
	float get_speed(void);

	/**
	 *  \brief Get the course.
	 *
	 *  \return Return course data. The format is 000.0~359.9.
	 *
	 */
	float get_course(void);

	/**
	 *  \brief Get the status of position fix.
	 *
	 *  \return Return course data. The format is 0,1,2,6.
	 *
	 */
	unsigned char get_position_fix(void);

	/**
	 *  \brief Get the number of state used。
	 *
	 *  \return Return number of state used. The format is 0-12.
	 *
	 */
	unsigned char get_sate_used(void);

	/**
	 *  \brief Get the altitude。 the format is -9999.9~99999.9
	 *
	 *  \return Return altitude data. The format is -9999.9~99999.9.
	 *
	 */
	float get_altitude(void);

	/**
	 *  \brief Get the mode of location.
	 *
	 *  \return Return mode of location. The format is A/M. A:automatic, M:manual.
	 *
	 */
	unsigned char get_mode(void);

	/**
	 *  \brief Get the current status of GPS.
	 *
	 *  \return Return current status. The format is 1,2,3. 1:null, 2:2D, 3:3D.
	 *
	 */
	unsigned char get_mode2(void);

	
private:

};

extern LGPSClass LGPS;

#endif
