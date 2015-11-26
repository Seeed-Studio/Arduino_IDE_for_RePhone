/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 20 Aug 2014 by MediaTek Inc.
  
*/

#ifndef _VARIANT_ARDUINO_DUE_X_
#define _VARIANT_ARDUINO_DUE_X_

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		12000000

/** Master clock frequency */
#define VARIANT_MCK			84000000

//#define __LINKIT_V1__
//

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "Arduino.h"
#ifdef __cplusplus
#include "UARTClass.h"
#endif


static const uint8_t A0  = 19;/*analog input pin A0*/
static const uint8_t A1  = 20;/*analog input pin A1*/
static const uint8_t A2  = 21;/*analog input pin A2*/
static const uint8_t A3  = 22;/*analog input pin A3*/

static const uint8_t E0  = 23;/*interrup input pin E0*/
static const uint8_t E1  = 24;/*interrup input pin E1*/
static const uint8_t E2  = 25;/*interrup input pin E2*/
static const uint8_t E3  = 26;/*interrup input pin E3*/
static const uint8_t E4  = 27;/*interrup input pin E4*/
static const uint8_t E5  = 28;/*interrup input pin E5*/

static const uint8_t GPIO14  = 29;/*digetal pin GPIO14*/
static const uint8_t GPIO18  = 30;/*digetal pin GPIO18*/
static const uint8_t GPIO20  = 31;/*digetal pin GPIO20*/
static const uint8_t GPIO30  = 32;/*digetal pin GPIO30*/
static const uint8_t GPIO31  = 33;/*digetal pin GPIO31*/
static const uint8_t GPIO32  = 34;/*digetal pin GPIO32*/
static const uint8_t GPIO33  = 35;/*digetal pin GPIO33*/
static const uint8_t GPIO34  = 36;/*digetal pin GPIO34*/
static const uint8_t GPIO35  = 37;/*digetal pin GPIO35*/
static const uint8_t GPIO36  = 38;/*digetal pin GPIO36*/
static const uint8_t GPIO37  = 39;/*digetal pin GPIO37*/

#define GPIO_MAX	40


#ifdef __LINKIT_V1__
static const uint8_t A3  = 17;/*analog input pin A3*/
#endif

#ifdef __cplusplus
extern UARTClass Serial;
extern UARTClass Serial1;
#endif

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 1

#define SPI_INTERFACE        SPI0
#define SPI_INTERFACE_ID     ID_SPI0
#define SPI_CHANNELS_NUM 4
#define PIN_SPI_SS0          (5)
#define PIN_SPI_SS1          (5)
#define PIN_SPI_SS2          (5)
#define PIN_SPI_SS3          (5)
#define PIN_SPI_MOSI         (4)
#define PIN_SPI_MISO         (3)
#define PIN_SPI_SCK          (2)
#define BOARD_SPI_SS0        (5)
#define BOARD_SPI_SS1        (5)
#define BOARD_SPI_SS2        (5)
#define BOARD_SPI_SS3        PIN_SPI_SS3
#define BOARD_SPI_DEFAULT_SS BOARD_SPI_SS3

#define BOARD_PIN_TO_SPI_PIN(x) \
	(x==BOARD_SPI_SS0 ? PIN_SPI_SS0 : \
	(x==BOARD_SPI_SS1 ? PIN_SPI_SS1 : \
	(x==BOARD_SPI_SS2 ? PIN_SPI_SS2 : PIN_SPI_SS3 )))
#define BOARD_PIN_TO_SPI_CHANNEL(x) \
	(x==BOARD_SPI_SS0 ? 0 : \
	(x==BOARD_SPI_SS1 ? 1 : \
	(x==BOARD_SPI_SS2 ? 2 : 3)))

static const uint8_t SS   = BOARD_SPI_SS0;
static const uint8_t SS1  = BOARD_SPI_SS1;
static const uint8_t SS2  = BOARD_SPI_SS2;
static const uint8_t SS3  = BOARD_SPI_SS3;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/
 
 
#endif /* _VARIANT_ARDUINO_DUE_X_ */

