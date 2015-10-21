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
#include <vmgsm_sms.h>
#include <vmchset.h>
#include <vmstdlib.h>
#include <vmmemory.h>
#include <vmlog.h>


struct linkit_sms_send_struct
{
    const char *number;
    const char *content;
    int result;
};

struct linkit_sms_unread_msg_struct
{
    int id;
    char *number;
    char *content;
};

boolean linkit_sms_ready_handler(void* userdata);
boolean linkit_sms_send_handler(void* userdata);

boolean linkit_sms_get_unread_handler(void* userdata);
boolean linkit_sms_delete_handler(void* userdata);


linkit_sms_send_struct *g_linkit_sms_send_data;

char *g_linkit_sms_number_buf = 0;
char *g_linkit_sms_content_buf = 0;


/*****************************************************************************
* 
* LSMSClass class
* 
*****************************************************************************/

LSMSClass::LSMSClass():
    _msgId(-1),
    _msgPos(0)
{

}

LSMSClass::~LSMSClass()
{

}

int LSMSClass::ready()
{
    int result;
    LTask.remoteCall(linkit_sms_ready_handler, &result);
    return result;
}

int LSMSClass::beginSMS(const char* to)
{
    _toNumber = to;
    _toContent = "";
    return 1;
}

size_t LSMSClass::write(uint8_t c)
{
    _toContent += (char)c;
}

int LSMSClass::endSMS()
{
    linkit_sms_send_struct data;

    data.content = _toContent.c_str();
    data.number = _toNumber.c_str();

    LTask.remoteCall(linkit_sms_send_handler, &data);

    //LGSMLOG("[LOG]endSMS():");
    //LGSMLOG(data.result);

    if(data.result == 1)
        return 1;
    else
        return 0;
}

int LSMSClass::available()
{
    linkit_sms_unread_msg_struct data;
    
    LTask.remoteCall(linkit_sms_get_unread_handler, &data);
	//data.id = -1;

	//Serial1.print("available data id ");
    //Serial1.println(data.id);
	//Serial1.println(g_linkit_sms_number_buf);
	//Serial1.println(g_linkit_sms_content_buf);
	
    if (data.id < 0)return false;

    _msgId = data.id;
    //_msgNumber = data.number;
    //_msgContent = data.content;
	_msgNumber = g_linkit_sms_number_buf;
    _msgContent = g_linkit_sms_content_buf;
    _msgPos = 0;
	//Serial1.println(_msgNumber);
	//Serial1.println(_msgContent);
    return true;
}

int LSMSClass::remoteNumber(char* number, int nlength)
{
    int len;

    if (_msgId < 0)
        return 0;

    len = strlen(_msgNumber);

    if (len+1 > nlength)
        return len+1;
        
    strcpy(number, _msgNumber);
    return len;
}

int LSMSClass::remoteContent(char* content, int nlength)
{
    int len;

    if (_msgId < 0)
        return 0;

    len = strlen(_msgContent);

    if (len+1 > nlength)
        return len+1;
        
    strcpy(content, _msgContent);
    return len;
}

int LSMSClass::read()
{
    int result;
    
    if(_msgId < 0)
        return -1;

    result = _msgContent[_msgPos];
    if (result)
        _msgPos++;
    else
        result = -1;
        
    return result;
}

int LSMSClass::peek()
{
    if(_msgId < 0)
        return -1;

    return _msgContent[_msgPos];
}

void LSMSClass::flush()
{
    if(_msgId < 0)
        return;

    LTask.remoteCall(linkit_sms_delete_handler, (void*)_msgId);
    _msgId = -1;
}


boolean linkit_sms_ready_handler(void* userdata)
{
    int result;

    //LGSMLOG("[LOG]vm_gsm_sim_get_card_count:");
    //LGSMLOG(vm_gsm_sim_get_card_count());
    //LGSMLOG("[LOG]vm_gsm_sms_is_sms_ready:");
    //LGSMLOG(vm_gsm_sms_is_sms_ready());

    result = false;
    if(vm_gsm_sim_get_card_count() > 0 && vm_gsm_sms_is_sms_ready())
        result = true;

    *((int*)userdata) = result;
    return true;    
}

void linkit_sms_send_callback(vm_gsm_sms_callback_t* callback_data)
{
    //LGSMLOG("[LOG]linkit_sms_send_callback");
    g_linkit_sms_send_data->result = callback_data->result;
    LTask.post_signal();
}

boolean linkit_sms_send_handler(void* userdata)
{
    linkit_sms_send_struct *data = (linkit_sms_send_struct*)userdata;
    VMWCHAR *number;
    VMWCHAR *content;
    VMINT  size;

    //LGSMLOG("[LOG]linkit_sms_send_handler");
    //LGSMLOG("[LOG]Number:");
    //LGSMLOG(data->number);
    //LGSMLOG("[LOG]Content:");
    //LGSMLOG(data->content);

    // ascii to ucs2
    size = (strlen(data->number)+1)*sizeof(VMWCHAR);
    number = (VMWCHAR *)vm_malloc(size);
    vm_chset_ascii_to_ucs2(number, size, (VMCHAR*)data->number);

    size = (strlen(data->content)+1)*sizeof(VMWCHAR);
    content = (VMWCHAR *)vm_malloc(size);
    vm_chset_ascii_to_ucs2(content, size, (VMCHAR*)data->content);

    // send and wait for result
    g_linkit_sms_send_data = data;
    size = vm_gsm_sms_send(number, content, linkit_sms_send_callback, NULL);
    //LGSMLOG("[LOG]vm_gsm_sms_send:");
    //LGSMLOG(size);

    // TODO: can we free them now, or need to wait for callback?
    vm_free(number);
    vm_free(content);
    
    if(size)   // send ok
    {
        data->result = true;
        return true;
    }
	
    data->result = false;
    return false;
}

void linkit_sms_read_callback(vm_gsm_sms_callback_t* callback_data)
{
    vm_gsm_sms_read_message_data_callback_t* read_msg;
	//Serial1.print("sms_read_sms_sample_callback \r\n");
    /* Checks if it is an SMS read event */
    if(callback_data->action == VM_GSM_SMS_ACTION_READ)
    {
        if(callback_data->cause == VM_GSM_SMS_CAUSE_NO_ERROR)
        {
            if(callback_data->action_data)
            {
				//Serial1.print("sms_read_sms_sample_callback action_data null\r\n");
				//goto TASKEND;
                //return;	
            
				//Serial1.print("sms_read_sms_sample_callback action_data ok\r\n");
				/* Analyses the data */
				read_msg = (vm_gsm_sms_read_message_data_callback_t*)callback_data->action_data;

				int size = vm_wstr_string_length((VMWCHAR*)read_msg->message_data->number);
				g_linkit_sms_number_buf = (char*)vm_malloc(size+1);
				vm_chset_ucs2_to_ascii((signed char *)g_linkit_sms_number_buf, size+1, (VMWCHAR*)read_msg->message_data->number);

				// assume dcs = UCS2
				g_linkit_sms_content_buf = (char*)vm_malloc(read_msg->message_data->content_buffer_size/2+1);
				vm_chset_ucs2_to_ascii((signed char *)g_linkit_sms_content_buf, read_msg->message_data->content_buffer_size/2+1, (VMWCHAR*)read_msg->message_data->content_buffer);

				/* Frees the memory allocated by the malloc() */
				vm_free(read_msg->message_data->content_buffer);
				vm_free(read_msg->message_data);
			}
        }
        else
        {
            Serial1.print("read msg failed\r\n");
        }
    }
	//Serial1.print("sms_read_sms_sample_callback end\r\n");
	LTask.post_signal();
}

boolean linkit_sms_get_unread_handler(void* userdata)
{
	linkit_sms_unread_msg_struct *dest = (linkit_sms_unread_msg_struct*)userdata;
    VMINT16 message_id;
    vm_gsm_sms_read_message_data_t* message_data = NULL;
    VMWCHAR* content_buff;
    VMINT res;
    VMINT number_count = 0;
    VM_GSM_SIM_ID sim_id;
    VMBOOL result;
	//Serial1.print("sms_read_sms_sample \r\n");
    number_count = vm_gsm_sim_get_card_count();
    //Serial1.print("sms read card count ");
	//Serial1.println(number_count);
    sim_id = vm_gsm_sim_get_active_sim_card();
    //Serial1.print("sms read active sim id ");
	//Serial1.println(sim_id);
    result = vm_gsm_sim_has_card();
    //Serial1.print("sms read sim card result " );
	//Serial1.println(result);
    /* Gets the message ID of the first message in the SMS inbox */
    message_id = vm_gsm_sms_get_message_id(VM_GSM_SMS_BOX_INBOX, 0);
	dest -> id= message_id;
	
    if(message_id >= 0)
    {
		/* Allocates memory for the message data */
		message_data = (vm_gsm_sms_read_message_data_t*)vm_calloc(sizeof(vm_gsm_sms_read_message_data_t));
		if(message_data == NULL)
		{
			//Serial1.print("sms read malloc message data fail\r\n");
			return false;
		}
		
		/* Allocates memory for the content buffer of the message */
		content_buff = (VMWCHAR*)vm_calloc((500+1)*sizeof(VMWCHAR));
		if(content_buff == NULL)
		{
			vm_free(message_data);
			//Serial1.print("sms read malloc content fail\r\n");
			return false;

		}
		message_data->content_buffer = content_buff;
		message_data->content_buffer_size = 500;
		
		/* Reads the message */
		res = vm_gsm_sms_read_message(message_id, VM_TRUE, message_data, linkit_sms_read_callback, NULL);
		
		if(res != VM_GSM_SMS_RESULT_OK)
		{
			vm_free(content_buff);
			vm_free(message_data);
			//Serial1.print("register read callback fail\r\n");
			return false;
		}
		else
		{
			return true;
		}
	}
}


void linkit_sms_delete_callback(vm_gsm_sms_callback_t* callback_data)
{
    LTask.post_signal();
}

boolean linkit_sms_delete_handler(void* userdata)
{
    VMUINT16 msg_id = (VMUINT16)((VMUINT32)userdata);

    vm_gsm_sms_delete_message(msg_id, linkit_sms_delete_callback, userdata);

    return false;
}


LSMSClass LSMS;