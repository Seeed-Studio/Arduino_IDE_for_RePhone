/*
 * TwoWire.h - TWI/I2C library for Arduino Due
 * Copyright (c) 2011 Cristian Maglie <c.maglie@bug.st>.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Modified 20 Aug 2014 by MediaTek Inc.
 */

extern "C" {
#include <string.h>
#include <stdlib.h> 
#include <inttypes.h>  
#include "vmsystem.h" 
#include "vmdcl.h" 
#include "vmdcl_i2c.h" 
#include "vmlog.h"
}

#include "Wire.h"

VM_DCL_HANDLE i2c_handle = -1;                 /* Declare a VM_DCL_HANDLE variable. */

TwoWire::TwoWire() :
	 rxBufferIndex(0), rxBufferLength(0), txAddress(0),
			txBufferLength(0), srvBufferIndex(0), srvBufferLength(0), status(
					UNINITIALIZED) {
	// Empty
}


int speed = 100;

void TwoWire::set_speed(int __speed)
{
    speed = __speed;
}
void TwoWire::begin(void) {
	
	if(!changePinType(18, PIO_I2C, &i2c_handle))
		return;

	if(i2c_handle == VM_DCL_HANDLE_INVALID)
	   i2c_handle = vm_dcl_open(VM_DCL_I2C,0); 
	else
	   i2c_handle = g_APinDescription[18].ulHandle;

	if(VM_DCL_HANDLE_INVALID == i2c_handle)	 
	{	  	
		vm_log_info("begin, failed.i2c_handle:%d",i2c_handle);	
	}	

	setPinHandle(18, i2c_handle);

	status = MASTER_IDLE;
}
	
void TwoWire::begin(uint8_t address) {
	status = SLAVE_IDLE;// can not porting use dcl
}

void TwoWire::begin(int address) {
	begin((uint8_t) address);// can not porting use dcl
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop) {

	// perform blocking read into buffer
	int readed = 0;
	VM_DCL_STATUS ret = VM_DCL_STATUS_OK;
	vm_dcl_i2c_control_config_t conf_data;
	vm_dcl_i2c_control_single_read_t  read_data;
	
	if(i2c_handle==-1)
	{
		vm_log_info("requestFrom,i2c handle is invalid.i2c_handle:%d",i2c_handle);
		return 0;
	}
	
	if (quantity > BUFFER_LENGTH)
		quantity = BUFFER_LENGTH;
	conf_data.reserved_0 = (VM_DCL_I2C_OWNER)0;
	conf_data.transaction_mode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
	conf_data.get_handle_wait = 0;
	conf_data.reserved_1 = 0;
	conf_data.delay_length = 0;
	conf_data.slave_address = address<<1;
	conf_data.fast_mode_speed = speed;
	conf_data.high_mode_speed = 0;
	ret = vm_dcl_control(i2c_handle,VM_DCL_I2C_CMD_CONFIG,(void *)&conf_data);
	read_data.data_ptr = &(rxBuffer[0]);
	read_data.data_length = quantity;
	ret = vm_dcl_control(i2c_handle,VM_DCL_I2C_CMD_SINGLE_READ,(void *)&read_data);
	rxBufferIndex = 0;
	rxBufferLength = quantity;

	return quantity;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity) {
	return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) true);
}

uint8_t TwoWire::requestFrom(int address, int quantity) {
	return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop) {
	return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) sendStop);
}

void TwoWire::beginTransmission(uint8_t address) {
	if(i2c_handle==-1)
	{
		vm_log_info("beginTransmission:i2c handle is invalid,return");
		return;
	}
	status = MASTER_SEND;

	// save address of target and empty buffer
	txAddress = address<<1;
	txBufferLength = 0;
}

void TwoWire::beginTransmission(int address) {
	beginTransmission((uint8_t) address);
}

uint8_t TwoWire::endTransmission(uint8_t sendStop) {
	vm_dcl_i2c_control_config_t conf_data;
	vm_dcl_i2c_control_single_write_t write_data;
	VM_DCL_STATUS ret = VM_DCL_STATUS_OK;
	int32_t sent = 0;

	if(i2c_handle==-1)
	{
		vm_log_info("endTransmission,i2c handle is invalid.i2c_handle:%d",i2c_handle);
		return 0;
	}
    
    if(0 < txBufferLength) {
		conf_data.reserved_0 =  (VM_DCL_I2C_OWNER)0;
		conf_data.transaction_mode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
		conf_data.get_handle_wait = 0;
		conf_data.reserved_1 = 0;
		conf_data.delay_length = 0;
		conf_data.slave_address = txAddress;

		conf_data.fast_mode_speed = speed;
		conf_data.high_mode_speed = 0;
		ret = vm_dcl_control(i2c_handle,VM_DCL_I2C_CMD_CONFIG,(void *)&conf_data);
	
		write_data.data_ptr = &(txBuffer[0]);
		write_data.data_length = txBufferLength;
        ret = vm_dcl_control(i2c_handle,VM_DCL_I2C_CMD_SINGLE_WRITE,(void *)&write_data);
		sent = txBufferLength;
	}
  
	txBufferLength = 0;

	status = MASTER_IDLE;
	return sent;
}

//	This provides backwards compatibility with the original
//	definition, and expected behaviour, of endTransmission
//
uint8_t TwoWire::endTransmission(void)
{
	return endTransmission(true);
}

size_t TwoWire::write(uint8_t data) {
	if (status == MASTER_SEND) {
		if (txBufferLength >= BUFFER_LENGTH)
			return 0;
		txBuffer[txBufferLength++] = data;
		return 1;
	} else {
		if (srvBufferLength >= BUFFER_LENGTH)
			return 0;
		srvBuffer[srvBufferLength++] = data;
		return 1;
	}
}

size_t TwoWire::write(const uint8_t *data, size_t quantity) {
	if (status == MASTER_SEND) {
		for (size_t i = 0; i < quantity; ++i) {
			if (txBufferLength >= BUFFER_LENGTH)
				return i;
			txBuffer[txBufferLength++] = data[i];
		}
	} else {
		for (size_t i = 0; i < quantity; ++i) {
			if (srvBufferLength >= BUFFER_LENGTH)
				return i;
			srvBuffer[srvBufferLength++] = data[i];
		}
	}
	return quantity;
}

int TwoWire::available(void) {
	return rxBufferLength - rxBufferIndex;
}

int TwoWire::read(void) {
	if (rxBufferIndex < rxBufferLength)
		return rxBuffer[rxBufferIndex++];
	return -1;
}

int TwoWire::peek(void) {
	if (rxBufferIndex < rxBufferLength)
		return rxBuffer[rxBufferIndex];
	return -1;
}

void TwoWire::flush(void) {
	// Do nothing, use endTransmission(..) to force
	// data transfer.
}

void TwoWire::onReceive(void(*function)(int)) {
	onReceiveCallback = function;
}

void TwoWire::onRequest(void(*function)(void)) {
	onRequestCallback = function;
}

void TwoWire::onService(void) {
	// Retrieve interrupt status
}
// Preinstantiate Objects //////////////////////////////////////////////////////
TwoWire Wire = TwoWire();

