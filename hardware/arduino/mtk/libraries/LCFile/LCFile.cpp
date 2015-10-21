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

#include "arduino.h"
#include "CFile.h"
#include "LCFile.h"


void LCFileClass::FileCreate(const char* filename)
{
	strcpy(FileName, filename);
	remoteCall(file_create, &FileName);
}

void LCFileClass::FileOpen(const char* filename)
{
	strcpy(FileName, filename);
	remoteCall(file_open, &FileName);
}

void LCFileClass::FileWrite(const char* strbuf)
{
	file_info_struct dataInf;
	strcpy(dataInf.filename, FileName);
	strcpy(dataInf.buffer, strbuf);
	remoteCall(file_write, &dataInf);
}

void LCFileClass::FileDelete(void)
{
	remoteCall(file_delete, &FileName);
}

void LCFileClass::FileRead(char* strbuf,unsigned int nbyte, unsigned long pos)
{
	read_info_struct dataInf;
	strcpy(dataInf.filename, FileName);
	dataInf.nbyte = nbyte;
	dataInf.pos = pos;
	dataInf.buffer = strbuf;
	remoteCall(file_read, &dataInf);
}

void LCFileClass::FileSize(unsigned long* size)
{
	size_info_struct dataInf;
	strcpy(dataInf.filename, FileName);
	dataInf.size = size;
	remoteCall(file_size, &dataInf);
}