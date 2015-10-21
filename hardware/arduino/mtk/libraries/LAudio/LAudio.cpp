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


#include <string.h>
#include <wchar.h>
#include "vmsystem.h"
#include "vmaudio.h"
#include "vmchset.h"
#include "vmstdlib.h"
#include "LAudio.h"
#include "audio.h"

static int status_result = 0 ;

void LAudioClass::playFile(StorageEnum drv, char *songName)
{
	strcpy((char*)m_path, songName);
	m_drv = drv;
	m_type = true;
	remoteCall(audioPlay, (void*)&status_result);
}

void LAudioClass::playFile(StorageEnum drv, wchar_t* songName)
{
	wcscpy((wchar_t*)m_path, songName);
	m_drv = drv;
	m_type = false;
	remoteCall(audioPlay, (void*)&status_result);
}

void LAudioClass::setVolume(unsigned char volume){
	m_volume = volume;
       remoteCall(audioSetVolume, NULL);
}

void LAudioClass::pause(){
       remoteCall(audioPause, NULL);
}

void LAudioClass::resume(){
       remoteCall(audioResume, NULL);
}

void LAudioClass::stop(){
       remoteCall(audioStop, NULL);
}

AudioStatus LAudioClass::getStatus(){
      AudioStatus status = (AudioStatus)status_result;
      status_result = 0;
      return status;
}
	
VMSTR LAudioClass::getFile(){
	return (signed char *)m_path;
}

unsigned char LAudioClass::getVolume(){
	return m_volume;
}

char LAudioClass::getDriver()
{
	return m_drv;
}

boolean LAudioClass::getType()
{
	return m_type;
}

LAudioClass LAudio;

