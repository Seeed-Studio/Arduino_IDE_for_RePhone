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


#include "vmsystem.h"
#include "vmaudio.h"
#include "vmchset.h"
#include "LAudio.h"
#include "Audio.h"
#include "vmaudio.h"
#include "vmaudio_play.h"
#include "vmlog.h"
#include "vmfs.h"
#include "vmstdlib.h"


static VMINT g_handle = -1;  // The handle of play
static VMINT g_interrupt_handle = 0; // The handle of interrupt

void audio_play_callback(VM_AUDIO_HANDLE handle, VM_AUDIO_RESULT result, void* userdata)
{
  int* res = (int*)userdata;
  //Serial1.println("audio_play_callback");
  * res = result;
  //Serial1.print("Audio result is ");
  //Serial1.println(result);
  switch (result) 
  {
	case VM_AUDIO_RESULT_END_OF_FILE:
	// When the end of file is reached, it needs to stop and close the handle
	vm_audio_play_stop(g_handle);
	vm_audio_play_close(g_handle);
	g_handle = -1;
	break;
	
	case VM_AUDIO_RESULT_INTERRUPT:
	// The playback is terminated by another application, for example an incoming call
	vm_audio_play_stop(g_handle);
	vm_audio_play_close(g_handle);
	//vm_audio_play_pause(g_handle);
	g_handle = -1;
	break;
	/*
	case VM_AUDIO_FAILED:
	break;
	
	case VM_AUDIO_SUCCEED:
	break;
	
	case VM_AUDIO_RESULT_STOP:
	break;
	
	case VM_AUDIO_RESULT_INTERRUPT_RESUME:
	break;
	*/
	default:
	break;
  }
}

boolean audioPlay(void* user_data)
{
  int* res = (int*)user_data;
  
  VMWCHAR path[256];
  VMCHAR path_a[256];

  VMINT drv ;
  
  vm_audio_play_parameters_t play_parameters;
  VM_AUDIO_VOLUME volume;

  if(LAudio.getDriver() ==0)
  {
  	drv = vm_fs_get_internal_drive_letter();
  }
  else
  {
  	drv = vm_fs_get_removable_drive_letter();
  }
  
  if(drv >=0)
  {
	
	if( LAudio.getType())
	{
  	    sprintf(path_a,(const signed char*)"%c:\\%s", drv, LAudio.getFile());
	    vm_chset_ascii_to_ucs2(path, 256, path_a);
	}
	else
	{
		sprintf(path_a,(const signed char*)"%c:\\", drv);
		vm_chset_ascii_to_ucs2(path, 256, path_a);
		vm_wstr_concatenate(path, (VMWSTR)LAudio.getFile());
	}
  }
  else
  {
  	//Serial1.println("AudioPlay get driver error");
	return false;
  }
  
  //Serial1.print("filename path is ");
  //Serial1.println((char*)path);

  // set play parameters
  memset(&play_parameters, 0, sizeof(vm_audio_play_parameters_t));
  play_parameters.filename = path;
  play_parameters.reserved = 0;  //
  play_parameters.format = VM_AUDIO_FORMAT_MP3; //
  //play_parameters.output_path = VM_AUDIO_DEVICE_SPEAKER2; 
  //play_parameters.output_path = VM_AUDIO_DEVICE_LOUDSPEAKER; 
  play_parameters.output_path = VM_AUDIO_DEVICE_SPEAKER_BOTH;
  play_parameters.async_mode = 0;
  play_parameters.callback = audio_play_callback;
  play_parameters.user_data = res;
   
  g_handle = vm_audio_play_open(&play_parameters);
  
  if(g_handle >= VM_OK)
  {
    //Serial1.println("open success");
	//*res = 0;
  }
  else
  {
    //Serial1.println("open failed");
	//*res = -1;
	return false;
  }
  // start to play
  vm_audio_play_start(g_handle);
  // set volume
  vm_audio_set_volume(VM_AUDIO_VOLUME_4);
  // register interrupt callback
  g_interrupt_handle = vm_audio_register_interrupt_callback(audio_play_callback,res);
}

boolean audioPause(void* user_data)
{
  if(g_handle >= 0)
  {
	  vm_audio_play_pause(g_handle);
	  return true;
  }
  return false;
}

boolean audioResume(void* user_data)
{
  if(g_handle >= 0)
  {
	  vm_audio_play_resume(g_handle);
	  return true;
  }
  return false;
}

boolean audioStop(void* user_data)
{
  if(g_handle >= 0)
  {
	  vm_audio_play_stop(g_handle);
      vm_audio_play_close(g_handle);
      if(g_interrupt_handle!=0)
      {
        vm_audio_clear_interrupt_callback(g_interrupt_handle);
      }
	  return true;
  }
  return false;
}

boolean audioSetVolume(void* user_data)
{
  switch(LAudio.getVolume())
  {
	  case 0:
	    vm_audio_set_volume(VM_AUDIO_VOLUME_0);
	  break;;
	  case 1:
	    vm_audio_set_volume(VM_AUDIO_VOLUME_1);
	  break;
	  case 2:
	    vm_audio_set_volume(VM_AUDIO_VOLUME_2);
	  break;
	  case 3:
	    vm_audio_set_volume(VM_AUDIO_VOLUME_3);
	  break;
	  case 4:
	    vm_audio_set_volume(VM_AUDIO_VOLUME_4);
	  break;
	  case 5:
	    vm_audio_set_volume(VM_AUDIO_VOLUME_5);
	  break;
	  case 6:
	    vm_audio_set_volume(VM_AUDIO_VOLUME_6);
	  break;
	  default:
	  break; 
  }
  return true;
}