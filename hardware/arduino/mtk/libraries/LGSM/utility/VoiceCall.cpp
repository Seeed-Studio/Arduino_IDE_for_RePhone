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
#include "VoiceCall.h"
#include "vmgsm_tel.h"
#include "vmlog.h"
#include "string.h"
#include "vmchset.h"
#include "vmgsm_sim.h"


extern vm_gsm_tel_call_listener_callback g_call_status_callback;

static vm_gsm_tel_id_info_t g_uid_info;
static int g_call_status = IDLE_CALL;
static char g_number[42];

static void __call_listener_func(vm_gsm_tel_call_listener_data_t* data)
{
    if(data->call_type == VM_GSM_TEL_INDICATION_INCOMING_CALL)
    {
    	vm_gsm_tel_call_info_t* ind = (vm_gsm_tel_call_info_t*)data->data;
		g_uid_info.call_id = ind->uid_info.call_id;
		g_uid_info.group_id = ind->uid_info.group_id;
		g_uid_info.sim = ind->uid_info.sim;
		strcpy(g_number, (char*)ind->num_uri);
		g_call_status = RECEIVINGCALL;
    }

    else if(data->call_type == VM_GSM_TEL_INDICATION_OUTGOING_CALL)
    {
    	vm_gsm_tel_call_info_t* ind = (vm_gsm_tel_call_info_t*)data->data;
		g_uid_info.call_id = ind->uid_info.call_id;
		g_uid_info.group_id = ind->uid_info.group_id;
		g_uid_info.sim = ind->uid_info.sim;
		strcpy(g_number, (char*)ind->num_uri);
		g_call_status = CALLING;
    }

    else if(data->call_type == VM_GSM_TEL_INDICATION_CONNECTED)
    {
    	vm_gsm_tel_connect_indication_t* ind = (vm_gsm_tel_connect_indication_t*)data->data;
		g_uid_info.call_id = ind->uid_info.call_id;
		g_uid_info.group_id = ind->uid_info.group_id;
		g_uid_info.sim = ind->uid_info.sim;
		g_call_status = TALKING;
    }

    else if(data->call_type == VM_GSM_TEL_INDICATION_CALL_ENDED)
    {
        g_call_status = IDLE_CALL;
    }

    else
    {
    	//vm_log_info("bad operation type");
    }
}

void registerCallback(void)
{
    g_call_status_callback = __call_listener_func;
}

static void _call_voiceCall_callback(vm_gsm_tel_call_actions_callback_data_t* data)
{
   //VMINT* result = (VMINT*)data->user_data;
   
   if(data->type_action == VM_GSM_TEL_CALL_ACTION_DIAL)
    {
	
    	if(data->data_act_rsp.result_info.result == VM_GSM_TEL_OK)
	    {
			//*result = 1;
			g_call_status = CALLING;
			LVoiceCall.post_signal();
    	}
		else
		{
			//*result = 0;
			g_call_status = IDLE_CALL;
		}
    }
    else if(data->type_action == VM_GSM_TEL_CALL_ACTION_ACCEPT)
    {
    	if(data->data_act_rsp.result_info.result == VM_GSM_TEL_OK)
	    {
			//*result = 1;
			g_call_status = TALKING;
			LVoiceCall.post_signal();
    	}
		else
		{
			//*result = 0;
			g_call_status = IDLE_CALL;
		}
    }
    else if(data->type_action == VM_GSM_TEL_CALL_ACTION_HOLD)
    {
    	// not use
    }
    else if(data->type_action == VM_GSM_TEL_CALL_ACTION_END_SINGLE)
    {
        //*result = 1;
		g_call_status = IDLE_CALL;
		LVoiceCall.post_signal();
    }
    else
    {
    	// not use
    }
}

boolean callvoiceCall(void* user_data)
{
  VMINT ret;
  call_info_struct* callInfo_p = (call_info_struct*)user_data;
  vm_gsm_tel_dial_action_request_t req;
  vm_gsm_tel_call_actions_data_t data;
  
  req.sim = VM_GSM_TEL_CALL_SIM_1;
  req.is_ip_dial = 0;
  req.module_id = 0;
  vm_chset_ascii_to_ucs2((VMWSTR)req.num_uri, VM_GSM_TEL_MAX_NUMBER_LENGTH, (VMSTR)callInfo_p->num);

  req.phonebook_data = NULL;

  data.action = VM_GSM_TEL_CALL_ACTION_DIAL;
  data.data_action = (void*)&req;
  //data.user_data = (void*)&callInfo_p->result;
  data.user_data = NULL;
  data.callback = _call_voiceCall_callback;  
  
  ret = vm_gsm_tel_call_actions(&data);
  
  vm_gsm_tel_set_output_device(VM_GSM_TEL_DEVICE_LOUDSPK);
  vm_gsm_tel_set_volume(VM_AUDIO_VOLUME_6);
  
  if(ret < 0)
  {
  	return false;
  }
  else
  {
  	callInfo_p->result = 1;
  	return true;
  }
}

boolean callanswerCall(void* user_data)
{
  VMINT ret;
  //VMINT* result = (VMINT*)user_data;
  vm_gsm_tel_single_call_action_request_t req;
  vm_gsm_tel_call_actions_data_t data;
  
  req.action_id.sim   = g_uid_info.sim;
  req.action_id.call_id = g_uid_info.call_id;
  req.action_id.group_id = g_uid_info.group_id;

  data.action = VM_GSM_TEL_CALL_ACTION_ACCEPT;
  data.data_action = (void*)&req;
  //data.user_data = result;
  data.user_data = NULL;
  data.callback = _call_voiceCall_callback;
  
  ret = vm_gsm_tel_call_actions(&data);
  
  vm_gsm_tel_set_output_device(VM_GSM_TEL_DEVICE_LOUDSPK);
  vm_gsm_tel_set_volume(VM_AUDIO_VOLUME_6);
  
  if(ret < 0)
  {
  	//*result = 0;
  	return false;
  }
  else
  {
  	//*result = 1;
  	return true;
  }
}

boolean callretrieveCallingNumber(void* user_data)
{
  call_info_struct* callInfo =  (call_info_struct*)user_data;
  callInfo->result = 0;

  if(g_call_status == RECEIVINGCALL || g_call_status == TALKING)
  {
  	strcpy((char*)callInfo->num, (char*)g_number);
	callInfo->result = 1;
  }
  
  return true;
}

boolean callready(void* user_data)
{
  VMINT* result = (VMINT*)user_data;
  *result = 1;
  return true;
}

boolean callgetVoiceCallStatus(void* user_data)
{
  char* status = (char*)user_data;
  *status = g_call_status;
  return true;
}

void call_hangCall_callback(vm_gsm_tel_call_actions_callback_data_t* data)
{
	//VMINT* result = (VMINT*)data->user_data;

	if(data->type_action == VM_GSM_TEL_CALL_ACTION_END_SINGLE)
	{
		//*result = 1;
		g_call_status = IDLE_CALL;
		LVoiceCall.post_signal();
	}
	else
	{
		// not use
	}
}

boolean callhangCall(void* user_data)
{
  VMINT ret;
  VMINT* result = (VMINT*)user_data;
  vm_gsm_tel_single_call_action_request_t req;
  vm_gsm_tel_call_actions_data_t data;
  
  if(IDLE_CALL == g_call_status)return true;
  
  req.action_id.sim   = g_uid_info.sim;
  req.action_id.call_id = g_uid_info.call_id;
  req.action_id.group_id = g_uid_info.group_id;
  
  data.action = VM_GSM_TEL_CALL_ACTION_END_SINGLE;
  data.data_action = (void*)&req;
  //data.user_data = result;
  data.user_data = NULL;
  data.callback = call_hangCall_callback;
  
  ret = vm_gsm_tel_call_actions(&data);
  
  if(ret < 0)
  {
  	return false;
  }
  else
  {
  	*result = 1;
  	return true;
  }
}

