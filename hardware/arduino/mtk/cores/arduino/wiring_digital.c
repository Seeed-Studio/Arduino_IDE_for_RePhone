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
*/

#include "Arduino.h"
#include "vmdcl.h"
#include "vmdcl_gpio.h"
#include "vmlog.h"

#ifdef __cplusplus
 extern "C" {
#endif

extern void pinMode( uint32_t ulPin, uint32_t ulMode )
{  
	VM_DCL_HANDLE gpio_handle; 
    vm_dcl_gpio_control_set_register_status_r0_r1_t pupd;
    //vm_log_info("pinMode(): pin = %d , pin_internal = %d, mode = %d", ulPin, g_APinDescription[ulPin].ulGpioId, ulMode);
    
    if(!changePinType(ulPin, PIO_DIGITAL, &gpio_handle))
		return;

	if(gpio_handle == VM_DCL_HANDLE_INVALID)
		gpio_handle = vm_dcl_open(VM_DCL_GPIO, g_APinDescription[ulPin].ulGpioId);
    
    // set PIN direction
    switch ( ulMode )
    {
		case INPUT:
			vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_DIRECTION_IN, NULL);
			if( g_APinDescription[ulPin].ulPupd)
			{
			pupd.register_status = 0;
			pupd.r0 = 1;
			pupd.r1 = 0;
			vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_REGISTER_STATUS_R0_R1, &pupd);
			}
			else
			{
				vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_ENABLE_PULL, NULL);
				vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_PULL_LOW, NULL);
			}
		break ;
        
		case INPUT_PULLUP:
			vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_DIRECTION_IN, NULL);   
			if( g_APinDescription[ulPin].ulPupd)
			{
			pupd.register_status = 1;
			pupd.r0 = 1;
			pupd.r1 = 0;
			vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_REGISTER_STATUS_R0_R1, &pupd);
			}
			else
			{
				vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_ENABLE_PULL, NULL);
				vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_PULL_HIGH, NULL);      
			}
		break ;
        
		case OUTPUT:
			vm_dcl_control(gpio_handle,VM_DCL_GPIO_COMMAND_SET_DIRECTION_OUT, NULL);
		break ;
        
        default:
        break ;
    }
    
    g_APinDescription[ulPin].ulHandle = gpio_handle;
    
}

extern void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{   
    //vm_log_info("digitalWrite(): pin = %d , value = %d", ulPin, ulVal);
    
    if (ulPin > PIO_MAX_NUM )
    {
        return;
    }
    
    // write PIN
    switch (ulVal)
    {
        case HIGH:
            vm_dcl_control(g_APinDescription[ulPin].ulHandle,VM_DCL_GPIO_COMMAND_WRITE_HIGH, NULL);   
            break;
            
        case LOW:
            vm_dcl_control(g_APinDescription[ulPin].ulHandle,VM_DCL_GPIO_COMMAND_WRITE_LOW, NULL);  
            break;
            
        default:
            break;
    }
    
}

extern int digitalRead( uint32_t ulPin )
{
    vm_dcl_gpio_control_level_status_t  data;

	//vm_log_info("digitalRead(): pin = %d", ulPin);

	if (ulPin > PIO_MAX_NUM )
    {
        //vm_log_info("digitalRead(): pin mapping failed, return LOW as default.");
        return LOW;
    }
	 
    vm_dcl_control(g_APinDescription[ulPin].ulHandle, VM_DCL_GPIO_COMMAND_READ,(void *)&data);
   
    if ( data.level_status == VM_DCL_GPIO_IO_LOW )
    {
        //vm_log_info("digitalRead(): result = LOW");
        return LOW ;
    }
    else if ( data.level_status == VM_DCL_GPIO_IO_HIGH )
    {
        //vm_log_info("digitalRead(): result = HIGH");
        return HIGH ;
    }
    else
    {
        //vm_log_info("digitalRead(): read failed, return LOW as default.");
        return LOW ;
    }
}

/*
extern void pinMode(uint32_t ulPin, uint32_t ulMode)
{
	VM_DCL_HANDLE gpio_handle;
	gpio_handle = vm_dcl_open(VM_DCL_GPIO, ulPin);

	if(gpio_handle != VM_DCL_HANDLE_INVALID)
	{
		switch(ulMode)
		{
			case INPUT:
				vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_MODE_0, NULL);
				vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_DIRECTION_IN, NULL);
			break;

			case OUTPUT:
				vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_MODE_0, NULL);
				vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_DIRECTION_OUT, NULL);
			break;

			case INPUT_PULLUP:
				vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_MODE_0, NULL);
				vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_DIRECTION_IN, NULL);
				vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_ENABLE_PULL, NULL);
				vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_PULL_HIGH, NULL);
			break;

			case INPUT_PULLDN:
				vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_MODE_0, NULL);
				vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_DIRECTION_IN, NULL);
				vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_ENABLE_PULL, NULL);
				vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_PULL_LOW, NULL);
			break;

			default:
			break;
		}
	}
	else
	{
		vm_log_info("gpio set pin mode fail");
		return -1;
	}

	vm_dcl_close(gpio_handle);
	return TRUE;
}

extern void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
	VM_DCL_HANDLE gpio_handle;
	gpio_handle = vm_dcl_open(VM_DCL_GPIO, ulPin);

	if(gpio_handle != VM_DCL_HANDLE_INVALID)
	{
		if(ulVal == LOW)
			vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_WRITE_LOW, NULL);
		else if(ulVal == HIGH)
			vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_WRITE_HIGH, NULL);
	}
	else
	{
		vm_log_info("gpio write pin fail");
		return -1;
	}

	vm_dcl_close(gpio_handle);
	return TRUE;
}

extern int digitalRead( uint32_t ulPin )
{
	VM_DCL_HANDLE gpio_handle;
	vm_dcl_gpio_control_level_status_t data;
	int ret;

	gpio_handle = vm_dcl_open(VM_DCL_GPIO, ulPin);

	if(gpio_handle != VM_DCL_HANDLE_INVALID)
	{
		vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_READ, (void*)&data);

		if (data.level_status == 1)ret = HIGH;
		else ret = LOW;
	}
	else
	{
		vm_log_info("gpio read pin fail");
		return -1;
	}

	vm_dcl_close(gpio_handle);
	return ret;
}
*/
#ifdef __cplusplus
}
#endif

