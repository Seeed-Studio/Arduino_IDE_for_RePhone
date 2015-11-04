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
#include "vmlog.h"
#include "vmfs.h"
#include "vmchset.h"
#include <stdio.h>
#include <string.h>
#include "CFile.h"


boolean file_create(void* user_data)
{
	char* data_name = (char*)user_data;
	
	VMCHAR filename[VM_FS_MAX_PATH_LENGTH] = {0};
	VMWCHAR wfilename[VM_FS_MAX_PATH_LENGTH] = {0};
	VM_FS_HANDLE filehandle = -1;

	sprintf((char*)filename, "%c:\\%s", vm_fs_get_internal_drive_letter(), data_name);
	vm_chset_ascii_to_ucs2(wfilename, sizeof(wfilename), filename);

    if((filehandle = vm_fs_open(wfilename, VM_FS_MODE_CREATE_ALWAYS_WRITE, TRUE)) < 0)
    {
        vm_log_info("Failed to create file: %s",filename);
		//Serial1.print("Failed to create file.\r\n");
        return true;
    }
    vm_log_info("Success to create file: %s", filename);
	//Serial1.print("Success to create file.\r\n");
    vm_fs_close(filehandle);
	return true;
}

boolean file_write(void* user_data)
{
	file_info_struct* data_file = (file_info_struct*)user_data;
	
	VMCHAR filename[VM_FS_MAX_PATH_LENGTH] = {0};
	VMWCHAR wfilename[VM_FS_MAX_PATH_LENGTH] = {0};
	VM_FS_HANDLE filehandle = -1;
	VMUINT writelen = 0;
	VMINT ret = 0;

	sprintf((char*)filename, "%c:\\%s", vm_fs_get_internal_drive_letter(), data_file->filename);
	vm_chset_ascii_to_ucs2(wfilename, sizeof(wfilename), filename);

    // write file
    if((filehandle = vm_fs_open(wfilename, VM_FS_MODE_WRITE, TRUE)) < 0)
    {
        vm_log_info("Write failed to open file: %s",filename);
        return true;
    }
    vm_log_info("Write success to open file: %s", filename);

    vm_fs_seek(filehandle, 0, VM_FS_BASE_END);

	ret = vm_fs_write(filehandle, (void*)data_file->buffer, strlen(data_file->buffer), &writelen);
    if(ret < 0)
    {
        vm_log_info("Failed to write file");
        return true;
    }
    vm_log_info("Success to write file: %s", filename);
	vm_fs_close(filehandle);
	return true;
}

boolean file_delete(void* user_data)
{
	char* data_name = (char*)user_data;
	
	VMCHAR filename[VM_FS_MAX_PATH_LENGTH] = {0};
	VMWCHAR wfilename[VM_FS_MAX_PATH_LENGTH] = {0};
    VMINT ret = 0;

	sprintf((char*)filename, "%c:\\%s", vm_fs_get_internal_drive_letter(), data_name);
	vm_chset_ascii_to_ucs2(wfilename, sizeof(wfilename), filename);

	ret = vm_fs_delete(wfilename);
	if(ret == 0)
	{
		vm_log_info("Success to delete file: %s",filename);
		//Serial1.print("Success to delete file.\r\n");
	}
	else
	{
		vm_log_info("Failed to delete file: %s",filename);
		//Serial1.print("Failed to delete file.\r\n");
	}
	return true;
}

boolean file_read(void* user_data)
{
	read_info_struct* data_inf = (read_info_struct*)user_data;
	
	VMCHAR filename[VM_FS_MAX_PATH_LENGTH] = {0};
	VMWCHAR wfilename[VM_FS_MAX_PATH_LENGTH] = {0};
    VM_FS_HANDLE filehandle = -1;
	VMUINT readlen = 0;
	VMINT ret = 0;

	sprintf((char*)filename, "%c:\\%s", vm_fs_get_internal_drive_letter(), data_inf->filename);
	vm_chset_ascii_to_ucs2(wfilename, sizeof(wfilename), filename);
	
	if((filehandle = vm_fs_open(wfilename, VM_FS_MODE_READ, TRUE)) < 0)
    {
		vm_log_info("Failed to open file: %s",filename);
		//Serial1.print("Failed to open file.\r\n");
		return true;
	}
	vm_log_info("Success to open file: %s", filename);
	//Serial1.print("Success to open file.\r\n");
	
	ret = vm_fs_seek(filehandle, data_inf->pos, VM_FS_BASE_BEGINNING);
	if (ret < 0)
    {
        vm_log_info("Failed to seek the file.");
		//Serial1.print("Failed to seek the file.\r\n");
		vm_fs_close(filehandle);
        return true;
    }
	
	vm_log_info("Success to seek the file.");
	//Serial1.print("Success to seek the file.\r\n");

    ret = vm_fs_read(filehandle, (void*)data_inf->buffer, data_inf->nbyte, &readlen);
    if (ret < 0)
    {
        vm_log_info("Failed to read the file.");
		//Serial1.print("Failed to read the file.\r\n");
		vm_fs_close(filehandle);
        return true;
    }

	vm_log_info("Success to read the file.");
    //Serial1.print("Success to read the file.\r\n");
	vm_fs_close(filehandle);
	return true;
}

boolean file_size(void* user_data)
{
	size_info_struct* data_inf = (size_info_struct*)user_data;
	
	VMCHAR filename[VM_FS_MAX_PATH_LENGTH] = {0};
	VMWCHAR wfilename[VM_FS_MAX_PATH_LENGTH] = {0};
    VM_FS_HANDLE filehandle = -1;
	
	sprintf((char*)filename, "%c:\\%s", vm_fs_get_internal_drive_letter(), data_inf->filename);
	vm_chset_ascii_to_ucs2(wfilename, sizeof(wfilename), filename);
	
	if((filehandle = vm_fs_open(wfilename, VM_FS_MODE_READ, TRUE)) < 0)
    {
		vm_log_info("Failed to open file: %s",filename);
		//Serial1.print("Failed to open file.\r\n");
		return true;
	}
	
	vm_log_info("Success to open file: %s", filename);
	//Serial1.print("Success to open file.\r\n");
	vm_fs_get_size(filehandle, (VMUINT*)data_inf->size);
	vm_fs_close(filehandle);
	return true;
}
