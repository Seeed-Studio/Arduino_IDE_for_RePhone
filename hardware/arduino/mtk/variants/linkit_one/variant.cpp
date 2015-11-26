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


#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Pins descriptions
 */
PinDescription g_APinDescription[]=
{
  { VM_DCL_HANDLE_INVALID, 13, PIO_END, 1  },      // D0 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_EINT / VM_DCL_PIN_MODE_PWM */
  { VM_DCL_HANDLE_INVALID,  3, PIO_END, 1  },      // D1 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_PWM */
  { VM_DCL_HANDLE_INVALID, 27, PIO_END, 1  },      // D2 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_SPI / VM_DCL_PIN_MODE_SDIO */
  { VM_DCL_HANDLE_INVALID, 29, PIO_END, 1  },      // D3 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_SPI / VM_DCL_PIN_MODE_SDIO */
  { VM_DCL_HANDLE_INVALID, 28, PIO_END, 1  },      // D4 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_SPI / VM_DCL_PIN_MODE_SDIO */
  { VM_DCL_HANDLE_INVALID, 19, PIO_END, 1  },      // D5 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_PWM */
  { VM_DCL_HANDLE_INVALID, 43, PIO_END, 0  },      // D6 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_I2C */
  { VM_DCL_HANDLE_INVALID, 44, PIO_END, 0  },      // D7 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_I2C */
  { VM_DCL_HANDLE_INVALID, 11, PIO_END, 0  },      // D8 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_UART */
  { VM_DCL_HANDLE_INVALID, 10, PIO_END, 0  },      // D9 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_UART */
  { VM_DCL_HANDLE_INVALID, 38, PIO_END, 1  },      // D10 /* Pin mux, VM_DCL_PIN_MODE_GPIO */ // gpio can not use it ??
  { VM_DCL_HANDLE_INVALID, 39, PIO_END, 1  },      // D11 /* Pin mux, VM_DCL_PIN_MODE_GPIO */ // gpio can not use it ??
  { VM_DCL_HANDLE_INVALID, 47, PIO_END, 1  },      // D12 /* Pin mux, VM_DCL_PIN_MODE_GPIO */
  { VM_DCL_HANDLE_INVALID, 48, PIO_END, 1  },      // D13 /* Pin mux, VM_DCL_PIN_MODE_GPIO */
  { VM_DCL_HANDLE_INVALID, 49, PIO_END, 1  },      // D14 /* Pin mux, VM_DCL_PIN_MODE_GPIO */
  { VM_DCL_HANDLE_INVALID, 50, PIO_END, 1  },      // D15 /* Pin mux, VM_DCL_PIN_MODE_GPIO */
  
  { VM_DCL_HANDLE_INVALID, 12, PIO_END, 1  },      // D16
  { VM_DCL_HANDLE_INVALID, 15, PIO_END, 1  },      // D17
  { VM_DCL_HANDLE_INVALID, 17, PIO_END, 1  },      // D18
  
  { VM_DCL_HANDLE_INVALID, 57, PIO_END, 0  },      // A0 // gpio can not use it ??
  
  { VM_DCL_HANDLE_INVALID, 0,  PIO_END, 0  },      // A1 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_ADC / VM_DCL_PIN_MODE_EINT */
  { VM_DCL_HANDLE_INVALID, 1,  PIO_END, 0  },      // A2 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_ADC / VM_DCL_PIN_MODE_EINT */
  { VM_DCL_HANDLE_INVALID, 2,  PIO_END, 0  },      // A3 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_ADC / VM_DCL_PIN_MODE_EINT */
  
  { VM_DCL_HANDLE_INVALID, 52, PIO_END, 0  },      // E0 // gpio input only, eint23 can not use it ??
  
  { VM_DCL_HANDLE_INVALID, 13, PIO_END, 1  },      // E1 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_EINT */
  { VM_DCL_HANDLE_INVALID, 18, PIO_END, 1  },      // E2 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_EINT */
  { VM_DCL_HANDLE_INVALID, 25, PIO_END, 1  },      // E3 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_EINT */
  { VM_DCL_HANDLE_INVALID, 46, PIO_END, 1  },      // E4 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_EINT */
  { VM_DCL_HANDLE_INVALID, 30, PIO_END, 1  },      // E5 /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_EINT */
  
  { VM_DCL_HANDLE_INVALID, 14, PIO_END, 1  },      // GPIO14 // wait for test ??
  { VM_DCL_HANDLE_INVALID, 18, PIO_END, 1  },      // GPIO18 // wait for test ??
  { VM_DCL_HANDLE_INVALID, 20, PIO_END, 1  },      // GPIO20 // wait for test ??
  { VM_DCL_HANDLE_INVALID, 30, PIO_END, 1  },      // GPIO30 // wait for test ??
  { VM_DCL_HANDLE_INVALID, 31, PIO_END, 1  },      // GPIO31 // wait for test ??
  { VM_DCL_HANDLE_INVALID, 32, PIO_END, 1  },      // GPIO32 // wait for test ??
  { VM_DCL_HANDLE_INVALID, 33, PIO_END, 1  },      // GPIO33 // wait for test ??
  { VM_DCL_HANDLE_INVALID, 34, PIO_END, 1  },      // GPIO34 // wait for test ??
  { VM_DCL_HANDLE_INVALID, 35, PIO_END, 1  },      // GPIO35 // wait for test ??
  { VM_DCL_HANDLE_INVALID, 36, PIO_END, 1  },      // GPIO36 // wait for test ??
  { VM_DCL_HANDLE_INVALID, 37, PIO_END, 1  },      // GPIO37 // wait for test ??
} ;


#ifdef __cplusplus
}
#endif

boolean changePinType(uint32_t ulPin, uint32_t ulPinType, VM_DCL_HANDLE* handle)
{
	VM_DCL_HANDLE gpio_handle; 

    if (ulPin > PIO_MAX_NUM)
    {
        return false;
    }
	

	if(g_APinDescription[ulPin].ulPinType == ulPinType && g_APinDescription[ulPin].ulHandle != VM_DCL_HANDLE_INVALID)
	{
		*handle = g_APinDescription[ulPin].ulHandle;
		return true;
	}

	*handle = VM_DCL_HANDLE_INVALID;

	if(ulPinType == PIO_DIGITAL)
	{
	    if(ulPin == A0 || ulPin == E0)return false; // gpio57 & gpio52
		
		if(g_APinDescription[ulPin].ulHandle != VM_DCL_HANDLE_INVALID)
		{
			vm_dcl_close(g_APinDescription[ulPin].ulHandle);
		}
		gpio_handle = vm_dcl_open(VM_DCL_GPIO,g_APinDescription[ulPin].ulGpioId);
		vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_0,NULL);
		vm_dcl_close(gpio_handle); 
	}
	else if(ulPinType == PIO_ANALOG)
	{
		if(g_APinDescription[ulPin].ulHandle != VM_DCL_HANDLE_INVALID)
		{
			vm_dcl_close(g_APinDescription[ulPin].ulHandle);
		}
		gpio_handle = vm_dcl_open(VM_DCL_GPIO,g_APinDescription[ulPin].ulGpioId);
		vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_2,NULL);
		vm_dcl_close(gpio_handle); 
	}
	else if(ulPinType == PIO_EINT)
	{
		if(g_APinDescription[ulPin].ulHandle != VM_DCL_HANDLE_INVALID)
		{
			vm_dcl_close(g_APinDescription[ulPin].ulHandle);
		}
		gpio_handle = vm_dcl_open(VM_DCL_GPIO,g_APinDescription[ulPin].ulGpioId);
		
		switch(ulPin)
		{
			case A1:case A2:case A3://gpio0,gpio1,gpio2
				vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_1,NULL);
				vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_DIRECTION_IN, NULL);
			break;
			//case E0://gpio52
			case E1:case E2:case E4://gpio13,gpio18,gpio46
				vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_2,NULL);
				vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_DIRECTION_IN, NULL);
			break;
			case E3:case E5://gpio25
				vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_4,NULL);
				vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_DIRECTION_IN, NULL);
			break;
			default:
			break;
		}
		
		vm_dcl_close(gpio_handle); 
	}
	else if(ulPinType == PIO_PWM)
	{
		if(g_APinDescription[ulPin].ulHandle != VM_DCL_HANDLE_INVALID)
		{
			vm_dcl_close(g_APinDescription[ulPin].ulHandle);
		}
		gpio_handle = vm_dcl_open(VM_DCL_GPIO,g_APinDescription[ulPin].ulGpioId);

		if(ulPin == 0)
			vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_3,NULL);
		else if(ulPin == 1)
			vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_4,NULL);
		else if(ulPin == 5)
			vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_2,NULL);

		vm_dcl_close(gpio_handle); 
	}
	else if(ulPinType == PIO_SPI)
	{
		for(int i = 2; i<5; i++)
		{
			if(g_APinDescription[i].ulHandle != VM_DCL_HANDLE_INVALID)
			{
				vm_dcl_close(g_APinDescription[i].ulHandle);
			}
			gpio_handle = vm_dcl_open(VM_DCL_GPIO,g_APinDescription[i].ulGpioId);
			vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_4,NULL);
			vm_dcl_close(gpio_handle); 
			g_APinDescription[i].ulHandle = VM_DCL_HANDLE_INVALID;

		}
	}
	else if(ulPinType == PIO_UART)
	{
		for(int i = 8; i<10; i++)
		{
			if(g_APinDescription[i].ulHandle != VM_DCL_HANDLE_INVALID)
			{
				vm_dcl_close(g_APinDescription[i].ulHandle);
			}
			gpio_handle = vm_dcl_open(VM_DCL_GPIO,g_APinDescription[i].ulGpioId);
			vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_1,NULL);
			vm_dcl_close(gpio_handle); 
			g_APinDescription[i].ulHandle = VM_DCL_HANDLE_INVALID;

		}	
	}
	else if(ulPinType == PIO_I2C)
	{
		for(int i = 6; i<8; i++)
		{
			if(g_APinDescription[i].ulHandle != VM_DCL_HANDLE_INVALID)
			{
				vm_dcl_close(g_APinDescription[i].ulHandle);
			}
			gpio_handle = vm_dcl_open(VM_DCL_GPIO,g_APinDescription[i].ulGpioId);
			vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_1,NULL);
			vm_dcl_close(gpio_handle); 
			g_APinDescription[i].ulHandle = VM_DCL_HANDLE_INVALID;

		}	
	}
	else if(ulPinType == PIO_SD)
	{
		for(int i = 2; i<5; i++)
		{
			if(g_APinDescription[i].ulHandle != VM_DCL_HANDLE_INVALID)
			{
				vm_dcl_close(g_APinDescription[i].ulHandle);
			}
			gpio_handle = vm_dcl_open(VM_DCL_GPIO,g_APinDescription[i].ulGpioId);
			vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_8,NULL);
			vm_dcl_close(gpio_handle); 
			g_APinDescription[i].ulHandle = VM_DCL_HANDLE_INVALID;

		}
	}
	else
	{
		return false;
	}
	
	g_APinDescription[ulPin].ulPinType = (EPioType)ulPinType;

	return true;
}

void spiPinsRest(void)
{
	int i;
	VM_DCL_HANDLE gpio_handle; 
	
	for(int i = 2; i<5; i++)
	{
		gpio_handle = vm_dcl_open(VM_DCL_GPIO, g_APinDescription[i].ulGpioId);
		vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_0,NULL);
		vm_dcl_close(gpio_handle); 
		g_APinDescription[i].ulHandle = VM_DCL_HANDLE_INVALID;
		g_APinDescription[i].ulPinType = PIO_DIGITAL;
	}
}

void setPinHandle(uint32_t ulPin, VM_DCL_HANDLE handle)
{
	g_APinDescription[ulPin].ulHandle = handle;
}

/*
 * UART objects
 */
RingBuffer rx_buffer1;
RingBuffer rx_buffer2;

UARTClass Serial(1, &rx_buffer1);
UARTClass Serial1(2, &rx_buffer2);

void serialEvent() __attribute__((weak));
void serialEvent1() __attribute__((weak));
void serialEventRun(void)
{
  if (Serial.available())
  {
  	 if(serialEvent)
  	 {
  	     serialEvent();
  	 }
  }
  if (Serial1.available())
  {
  	 if(serialEvent1)
  	 {
  	     serialEvent1();
  	 }
  }
}

#ifdef __cplusplus
extern "C" {
#endif

void init( void )
{
	int i;
	VM_DCL_HANDLE gpio_handle; 
	
	for(i=0;i<8;i++)
	{
		gpio_handle = vm_dcl_open(VM_DCL_GPIO,g_APinDescription[i].ulGpioId);
		vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_0,NULL);
		vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_DIRECTION_OUT, NULL);
       	vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_WRITE_LOW, NULL);   
		vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_DIRECTION_IN, NULL);
		vm_dcl_close(gpio_handle); 
	}
	for(i=10;i<GPIO_MAX;i++)
	{
	    if(i == 20)continue;
		gpio_handle = vm_dcl_open(VM_DCL_GPIO,g_APinDescription[i].ulGpioId);
		vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_MODE_0,NULL);
		vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_DIRECTION_OUT, NULL);
        vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_WRITE_LOW, NULL);   
		vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_DIRECTION_IN, NULL);
		vm_dcl_close(gpio_handle); 
	}
}

#ifdef __cplusplus
}
#endif

