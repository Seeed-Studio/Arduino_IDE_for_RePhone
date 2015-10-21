/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 *
 * Modified 20 Aug 2014 by MediaTek Inc.
 */

#include "SPI.h"
#include "vmdcl_spi.h"
#include "vmlog.h"
#include <math.h>

static char buff[128];

extern char* spi_w_data ;
extern char* spi_r_data;
extern unsigned char* spi_data_memory;

SPIClass::SPIClass()
{
    spi_handle = VM_DCL_HANDLE_INVALID;
}

void SPIClass::begin() 
{
    if(!changePinType(2, PIO_SPI, &spi_handle))		
		return;
	
    if(spi_handle == VM_DCL_HANDLE_INVALID)
    {			
       spi_handle = vm_dcl_open(VM_DCL_SPI_PORT1,0);		
	setPinHandle(2, spi_handle);	
    }
    
    // default control data
    conf_data.clock_high_time = 3;
  	conf_data.clock_low_time = 3;
  	conf_data.cs_hold_time = 15;
  	conf_data.cs_idle_time = 15;
  	conf_data.cs_setup_time= 15;
  	conf_data.clock_polarity = VM_DCL_SPI_CLOCK_POLARITY_0;
  	conf_data.clock_phase = VM_DCL_SPI_CLOCK_PHASE_0;
    conf_data.rx_endian = VM_DCL_SPI_ENDIAN_LITTLE;
  	conf_data.tx_endian = VM_DCL_SPI_ENDIAN_LITTLE;
  	conf_data.rx_msbf = VM_DCL_SPI_MSB_FIRST;
  	conf_data.tx_msbf = VM_DCL_SPI_MSB_FIRST;
  	
  	vm_dcl_control(spi_handle,VM_DCL_SPI_CONTROL_SET_CONFIG_PARAMETER,(void *)&conf_data);

    spi_data.mode = VM_DCL_SPI_MODE_DEASSERT;
    spi_data.is_enabled = VM_FALSE;
    vm_dcl_control(spi_handle,VM_DCL_SPI_CONTROL_SET_MODE,(void *)&spi_data);


    // Default speed set to 4Mhz
    setClockDivider(SPI_CLOCK_DIV4);
    setDataMode(SPI_MODE0);
    setBitOrder(MSBFIRST);
}

void SPIClass::end()
{
	vm_dcl_close(spi_handle);
	spiPinsRest();
	spi_handle = VM_DCL_HANDLE_INVALID;
}

void SPIClass::setBitOrder(BitOrder _bitOrder) 
{
    if(VM_DCL_HANDLE_INVALID==spi_handle)
    {
        return;
    }
    
    if (MSBFIRST == _bitOrder)
    {
        conf_data.rx_endian = VM_DCL_SPI_ENDIAN_BIG;
        conf_data.tx_endian = VM_DCL_SPI_ENDIAN_BIG;
        
    }
    else if (LSBFIRST  == _bitOrder)
    {
        conf_data.rx_endian = VM_DCL_SPI_ENDIAN_LITTLE;
        conf_data.tx_endian = VM_DCL_SPI_ENDIAN_LITTLE;
    }
    else
    {
        return;
    }

  	vm_dcl_control(spi_handle,VM_DCL_SPI_CONTROL_SET_CONFIG_PARAMETER,(void *)&conf_data);
  	
}

void SPIClass::setDataMode(uint8_t _mode) 
{
    if(VM_DCL_HANDLE_INVALID==spi_handle)
    {
        return;
    }
    
    if (_mode == SPI_MODE0)
    {
        conf_data.clock_polarity = VM_DCL_SPI_CLOCK_POLARITY_0;
  	    conf_data.clock_phase = VM_DCL_SPI_CLOCK_PHASE_0;
    }
    else if (_mode == SPI_MODE1)
    {
        conf_data.clock_polarity = VM_DCL_SPI_CLOCK_POLARITY_0;
  	    conf_data.clock_phase = VM_DCL_SPI_CLOCK_PHASE_1;
    }
    else if (_mode == SPI_MODE2)
    {
        conf_data.clock_polarity = VM_DCL_SPI_CLOCK_POLARITY_1;
  	    conf_data.clock_phase = VM_DCL_SPI_CLOCK_PHASE_0;
    }  
    else if (_mode == SPI_MODE3)
    {
        conf_data.clock_polarity = VM_DCL_SPI_CLOCK_POLARITY_1;
  	    conf_data.clock_phase = VM_DCL_SPI_CLOCK_PHASE_1;
    }
    else
    {
        return;
    }
    
    vm_dcl_control(spi_handle,VM_DCL_SPI_CONTROL_SET_CONFIG_PARAMETER,(void *)&conf_data);
}

void SPIClass::setClockDivider(uint8_t _divider) 
{
    if(VM_DCL_HANDLE_INVALID == spi_handle)
    {
        return;
    }
    
    if (_divider == SPI_CLOCK_DIV2)
    {
        conf_data.clock_high_time = 1;
  	    conf_data.clock_low_time = 1;
    }
    else if (_divider == SPI_CLOCK_DIV4)
    {
        conf_data.clock_high_time = 3;
  	    conf_data.clock_low_time = 3;
    }
    else if (_divider == SPI_CLOCK_DIV8)
    {
        conf_data.clock_high_time = 7;
  	    conf_data.clock_low_time = 7;
    }
    else if (_divider == SPI_CLOCK_DIV16)
    {
        conf_data.clock_high_time = 15;
  	    conf_data.clock_low_time = 15;
    }
    else if (_divider == SPI_CLOCK_DIV32)
    {
        conf_data.clock_high_time = 31;
  	    conf_data.clock_low_time = 31;
    }
    else if (_divider == SPI_CLOCK_DIV64)
    {
        conf_data.clock_high_time = 63;
  	    conf_data.clock_low_time = 63;
    }
    else if (_divider == SPI_CLOCK_DIV128)
    {
        conf_data.clock_high_time = 127;
  	    conf_data.clock_low_time = 127;
    }
    else
    {
        return;
    }
    
    vm_dcl_control(spi_handle,VM_DCL_SPI_CONTROL_SET_CONFIG_PARAMETER,(void *)&conf_data);
}

byte SPIClass::transfer(uint8_t _data) 
{
    vm_dcl_spi_control_read_write_t  write_and_read;
	
    if(VM_DCL_HANDLE_INVALID == spi_handle)
    {
        return 0;
    }
    	    
    if(spi_w_data)
    {
    	*spi_w_data = _data;
        write_and_read.read_data_ptr =  (VMUINT8*)spi_r_data;
        write_and_read.read_data_length = 1;
        write_and_read.write_data_ptr = (VMUINT8*)spi_w_data;
        write_and_read.write_data_length = 1; 
        vm_dcl_control(spi_handle,VM_DCL_SPI_CONTROL_WRITE_AND_READ,(void *)&write_and_read);
    }

    return *spi_r_data;
}

uint32_t SPIClass::write_2x(uint8_t* _data, uint32_t size) 
{
    uint8_t* p = _data;
	
    VM_DCL_BUFFER_LENGTH count, datalen;
    VM_DCL_STATUS status;

    if(size > 65536)
    {
        for(;size>65536;)
	 {
    	  memcpy(spi_data_memory, p, 65536);
         count = 64;
	  datalen = 1024;
    	  status = vm_dcl_write(spi_handle,(VM_DCL_BUFFER*)spi_data_memory,datalen,&count,0);
		  
         if(status < VM_DCL_STATUS_OK)
		return 0;
		 
	  p = &p[65536];
	  size = size -65536;
    	}
    }
	
    if(size > 1024)
    {
    	count = size/1024;
	datalen = 1024;
    }
    else
    {
    	count = 1;
	datalen = size;
    }
	
    memcpy(spi_data_memory, _data, size);
    status = vm_dcl_write(spi_handle,(VM_DCL_BUFFER*)spi_data_memory,datalen,&count,0);
    if(status == VM_DCL_STATUS_OK)
		return size;
    else
		return 0;
    
}

uint32_t SPIClass::write(uint8_t* _data, uint32_t size) 
{
    	int x = 1, y = 1, k;

	while(y <= size)
	{
	  x++;
	  y = (double)pow(2, (double)x);
	}
	
	k = size-y/2;

	write_2x(_data, y/2);
	
	if(k>2)
		return write(&_data[y/2], k);
	
	else if(k==2)
	{
		if(conf_data.rx_endian == VM_DCL_SPI_ENDIAN_BIG)
		{
			transfer(_data[y/2+1]);
			return transfer(_data[y/2]);
		}
		else
		{
			transfer(_data[y/2]);
			return transfer(_data[y/2+1]);
		}
	}
	else
	{
		return transfer(_data[y/2]);
	}
}

SPIClass SPI;

