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


#ifndef _CFILE_H
#define _CFILE_H

#ifdef __cplusplus
extern "C" {
#endif


boolean file_create(void* user_data);
boolean file_open(void* user_data);
boolean file_write(void* user_data);
boolean file_delete(void* user_data);
boolean file_read(void* user_data);
boolean file_size(void* user_data);
boolean file_rename(void* user_data);


typedef struct
{
	char filename[26];
	char buffer[128];
}file_info_struct;

typedef struct
{
	char filename[26];
	unsigned int nbyte;
	unsigned long pos;
	char* buffer;
}read_info_struct;

typedef struct
{
	char filename[26];
	unsigned long* size;
}size_info_struct;


#ifdef __cplusplus
}
#endif

#endif

