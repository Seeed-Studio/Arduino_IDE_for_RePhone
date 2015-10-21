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

#include "LGSM.h"

#include <vmgsm_sim.h>
#include <vmchset.h>
#include <vmstdlib.h>
#include "VoiceCall.h"

LVoiceCallClass::LVoiceCallClass()
{
	registerCallback();
}

LVoiceCallClass::~LVoiceCallClass()
{

}

int LVoiceCallClass::ready()
{
	int result = 0;
	remoteCall(callready, (void*)&result);
	return result;
}

int LVoiceCallClass::voiceCall(const char* to,  unsigned long timeout)
{
	call_info_struct callInfo;
	strcpy(callInfo.num, to);
	remoteCall(callvoiceCall, (void*)&callInfo);
	return callInfo.result;
}

char LVoiceCallClass::getVoiceCallStatus(void)
{
    char status;
    remoteCall(callgetVoiceCallStatus, (void*)&status);
    return status;
}

int LVoiceCallClass::answerCall(void)
{
	int ret;
	remoteCall(callanswerCall, &ret);
	return ret;
}

int LVoiceCallClass::retrieveCallingNumber(char* number, int nlength )
{
	call_info_struct callInfo;
	
	memset(number, 0, nlength);

	remoteCall(callretrieveCallingNumber, (void*)&callInfo);
	
	if(callInfo.result == 1)
	{
		strcpy(number, callInfo.num);
		return 1;
	}
	else
	{
		return 0;
	}
}

int LVoiceCallClass::hangCall(void)
{
	int ret;
	remoteCall(callhangCall, (void*)&ret);
	//Serial1.print("LVoiceCallClass::hangCall ret is ");
	//Serial1.println(ret);
	return ret;
}

LVoiceCallClass LVoiceCall;

