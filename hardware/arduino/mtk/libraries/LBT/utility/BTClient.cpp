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

#include "Arduino.h"
#include "LBT.h"
#include "vmbt_cm.h"
#include "vmbt_spp.h"
#include "vmlog.h"
#include "BTClient.h"
#include "LBTClient.h"
#include "vmtimer.h"
#include "vmstdlib.h"
#include "vmfs.h"
#include "vmmemory.h"
#include "vmchset.h"
#include "vmlog.h"
#include "vmthread.h"

#define BT_NAME "SPP"
#define LOG_BUF_SIZE 96
#define FILE_PATH_SIZE 16
#define SPP_DATA "Hello SPP!"
#ifdef LBT_DEBUG
#define APP_LOG(...) app_log_file(__VA_ARGS__); \
    vm_log_info(__VA_ARGS__)
#else
#define APP_LOG(...)
#endif
static VMINT flag_delete_log;
extern vm_mutex_t client_mutex;

void app_log_file(char *fmt, ...)
{
    va_list args;
    VMINT drv, hdl;
    VMUINT written;
    VMINT ret;
    vm_date_time_t time = {0};
    char buf[LOG_BUF_SIZE] = {0};
    VMWCHAR wpath[FILE_PATH_SIZE] = {0};
    VMCHAR path[FILE_PATH_SIZE] = {0};
  
    buf[LOG_BUF_SIZE - 2] = '\r';
    buf[LOG_BUF_SIZE - 1] = '\n';

    va_start( args, fmt );
    vm_time_get_date_time(&time);
    vm_sprintf((VMSTR)buf+strlen(buf), (VMCSTR)"[%02d:%02d:%02d]", time.hour, time.minute, time.second);
    vm_vsprintf((VMSTR)buf+strlen(buf), (VMCSTR)fmt, args);
        
    drv = vm_fs_get_removable_drive_letter() > 0 ? vm_fs_get_removable_drive_letter() : vm_fs_get_internal_drive_letter();
    vm_sprintf(path, (VMCSTR)"%c:\\%s", drv, BT_NAME".log");

    vm_chset_ascii_to_ucs2(wpath, sizeof(wpath), path); 
    hdl = vm_fs_open(wpath, VM_FS_MODE_APPEND, 0);
    if (hdl < 0)
        hdl = vm_fs_open(wpath, VM_FS_MODE_CREATE_ALWAYS_WRITE, 0);
    else
    {
        if (!flag_delete_log)
        {
            vm_fs_close(hdl);
            vm_fs_delete(wpath);
            flag_delete_log = 1;
            hdl = vm_fs_open(wpath, VM_FS_MODE_CREATE_ALWAYS_WRITE, 0);
        }
    }
    
    vm_fs_write(hdl, buf, LOG_BUF_SIZE, &written);
    vm_fs_close(hdl);

    va_end( args );						
}


#define SPP_UUID 0x1101
#define MAX_DEVICE_SCANNED 10

typedef enum{
	BT_CLIENT_IDLE = 0,
	BT_CLIENT_BEGINING = 1, // not even power on, need to power on first
	BT_CLIENT_POWERING_ON = 2, // waiting for power on to process
    BT_CLIENT_READY = 3, // power on and init done
    BT_CLIENT_ENDING = 4, // not event powr off, need to power off first
    BT_CLIENT_POWERING_OFF = 5 // waiting for power off to process
}bt_client_status;

class btClientContext
{
    public:
    LBTClientClass *ptr;
    VMINT search_tid;
    VMINT btcm_hdl;
    VMINT btspp_hdl;
    VMINT btspp_buf_size;
    void* btspp_buf;

    bt_client_status client_status;
    size_t scan_number;
    VMINT conn_id;
    boolean* waiting_result_p;
    size_t* scan_number_p;
    
    btClientContext(int x, int y);
};

btClientContext::btClientContext(int x, int y)
{
    btcm_hdl = x; // -1
    btspp_hdl = -1;
    btspp_buf_size = -0;
    btspp_buf = NULL;
    scan_number = 0;
    conn_id = -1;
    waiting_result_p = NULL;
    scan_number_p = NULL;
    client_status = (bt_client_status)y; // BT_CLIENT_IDLE;
    APP_LOG("btClientContext::btClientContext, [%d,%d] [%d,%d]", x, y, btcm_hdl, client_status);
}


btClientContext g_clientContext(-1, 0);

static VMINT bt_client_init_spp();
static boolean bt_client_end_spp();


static void bt_client_btcm_cb(VM_BT_CM_EVENT evt, void * param, void * user_data)
{

    APP_LOG("[BTC]bt_client_btcm_cb, evt = %d, client_status = %d", evt, g_clientContext.client_status);

    switch (evt)
    {
        case VM_BT_CM_EVENT_ACTIVATE:
        {
            // waiting for power on to process
            if (g_clientContext.client_status == BT_CLIENT_POWERING_ON)
            {
                VMINT ret = bt_client_init_spp();

                if(ret<0)
                {
                    *(g_clientContext.waiting_result_p) = false;
                    g_clientContext.waiting_result_p = NULL;

                    if(bt_client_end_spp())
                    {
                        
                        g_clientContext.ptr->post_signal();
                        
                    }
                }
                else
                {
                    *(g_clientContext.waiting_result_p) = true;
                    g_clientContext.waiting_result_p = NULL;
                    
                    g_clientContext.ptr->post_signal();
                    
                }

            }
            else if (g_clientContext.client_status == BT_CLIENT_ENDING)
            {
                VMINT ret = vm_bt_cm_switch_off();

                if(VM_BT_CM_RESULT_SUCCESS == ret)
                {
                    g_clientContext.client_status = BT_CLIENT_POWERING_OFF;
                }
                else
                {
                    if(g_clientContext.btcm_hdl >= 0)
                    {
                        vm_bt_cm_exit(g_clientContext.btcm_hdl);
                        g_clientContext.btcm_hdl = -1;
                    }
                    
                    g_clientContext.client_status = BT_CLIENT_IDLE;
                    
                    //LTask.post_signal();
                    g_clientContext.ptr->post_signal();
                    
                }
            }
                
            break;
        }

        case VM_BT_CM_EVENT_DEACTIVATE:
        {
            if (g_clientContext.client_status == BT_CLIENT_BEGINING)
            {
                VMINT ret = vm_bt_cm_switch_on();
                
                if(VM_BT_CM_RESULT_SUCCESS == ret)
                {
                    //wait for callback to process
                    g_clientContext.client_status = BT_CLIENT_POWERING_ON;
                }
                else
                {
                    *(g_clientContext.waiting_result_p) = false;
                    g_clientContext.waiting_result_p = NULL;

                    if(bt_client_end_spp())
                    {
                        
                        //LTask.post_signal();
                        g_clientContext.ptr->post_signal();
                        
                    }
                }
            }
            else if(g_clientContext.client_status == BT_CLIENT_POWERING_OFF)
            {
                if(g_clientContext.btcm_hdl >= 0)
                {
                    vm_bt_cm_exit(g_clientContext.btcm_hdl);
                    g_clientContext.btcm_hdl = -1;
                }
                
                g_clientContext.client_status = BT_CLIENT_IDLE;
                
                //LTask.post_signal();
                g_clientContext.ptr->post_signal();
                
            }
                
            break;
        }

        case VM_BT_CM_EVENT_INQUIRY_IND:
        {
            vm_bt_cm_inquiry_indication_t *ind = (vm_bt_cm_inquiry_indication_t *)param;

            if (ind->discovered_device_number > 0)
            {
                g_clientContext.scan_number = ind->discovered_device_number;
            }


            APP_LOG("[BTC]bt_client_btcm_cb, scan_number = %d, discovered_device_number = %d", g_clientContext.scan_number, ind->discovered_dev_num);
            vm_bt_cm_device_info_t dev_info ;
            *(g_clientContext.scan_number_p) = g_clientContext.scan_number;
            for (int i = 0; i < ind->discovered_device_number; i++)
            {
                if( VM_BT_CM_ERROR_SUCCESS == vm_bt_cm_get_device_info_by_index(i, VM_BT_CM_DEVICE_DISCOVERED, &dev_info) )
                {
                    LBTAddress addr;
                    addr.nap[0] = (dev_info.device_address.nap & 0x00ff);
                    addr.nap[1] = (dev_info.device_address.nap & 0xff00) >> 8;
                    addr.uap = dev_info.device_address.uap;
                    addr.lap[0] = (dev_info.device_address.lap & 0x0000ff);
                    addr.lap[1] = (dev_info.device_address.lap & 0x00ff00) >> 8;
                    addr.lap[2] = (dev_info.device_address.lap & 0xff0000) >> 16;
                                
                    APP_LOG("[BTC]VM_BT_CM_EVENT_INQUIRY_IND, name: %s", dev_info.name);
                
                
                    APP_LOG("[BTC]VM_BT_CM_EVENT_INQUIRY_IND, address: %02x:%02x:%02x:%02x:%02x:%02x:", 
                                addr.nap[1],
                                addr.nap[0],
                                addr.uap,
                                addr.lap[2],
                                addr.lap[1],
                                addr.lap[0]);
                
                }
            }
            break;
        }

        case VM_BT_CM_EVENT_INQUIRY_COMPLETE:
        {
            vm_bt_cm_inquiry_complete_t *cmpl = (vm_bt_cm_inquiry_complete_t *)param;

            *(g_clientContext.scan_number_p) = g_clientContext.scan_number;
            
            g_clientContext.ptr->post_signal();
            
            break;
        }

        case VM_BT_CM_EVENT_PAIR_INDICATION:
        {
        	  vm_bt_cm_pair_indication_t *event = (vm_bt_cm_pair_indication_t *)param;
        	  vm_bt_cm_send_passkey(&event->device_address, (VMUINT8*)LBTClient._pincode_buffer, VM_TRUE);
            break;
        }

        default:
        {
            break;
        }
    }


}

static int bt_client_spp_read(void* data)
{
	  VMINT ret = 0;
	  VMINT i = 0;
    if(g_clientContext.conn_id < 0)
    {

        APP_LOG((char*)"[BTC]bt_client_spp_read : not connected yet");

        return true;
    }
    char *readdata = new char[LBT_SERIAL_BUFFER_SIZE];
    if(readdata == NULL)
  	{
  		APP_LOG((char*)"[BTC]bt_client_spp_read : allocate memory fail");
  		return false;
  	}
    ret = vm_bt_spp_read(g_clientContext.conn_id, (void*)readdata, LBT_SERIAL_BUFFER_SIZE);

    APP_LOG("[BTC]bt_client_spp_read, ret: %d", ret);

    if (ret < 0)
    {
       APP_LOG((char*)"[BTC]bt_client_spp_read : read data fail");

    }
    else 
    {
    	  if(client_mutex.guard == 0)
    	  {
    	      vm_mutex_init(&client_mutex);
    	  }
    	  vm_mutex_lock(&client_mutex);
        for(i=0;i<ret;i++)
        {
        	LBTClient._rx_buffer->store_char(readdata[i]);
        }
        vm_mutex_unlock(&client_mutex);
        APP_LOG((char*)"[BTC]bt_client_spp_read : read data success");
    }
    delete[] readdata;
	return ret;
}

static void bt_client_spp_cb(VM_BT_SPP_EVENT evt, vm_bt_spp_event_cntx_t * param, void * user_data)
{
    vm_bt_spp_event_cntx_t* cntx = (vm_bt_spp_event_cntx_t*)param;

    switch(evt)
    {        
        case VM_BT_SPP_EVENT_CONNECT:
        {
            if (cntx->result)
            {
                if(g_clientContext.waiting_result_p != NULL)
                {
                    *(g_clientContext.waiting_result_p) = true;
                }
                g_clientContext.conn_id = cntx->connection_id;
            }
            else
            {
                if(g_clientContext.waiting_result_p != NULL)
                {
                    *(g_clientContext.waiting_result_p) = false;
                }
            }

            if(g_clientContext.waiting_result_p != NULL)
            {
                g_clientContext.waiting_result_p = NULL;
                g_clientContext.ptr->post_signal();
                
            }
            else
            {
                // reconnection
            }
            break;
        }

        case VM_BT_SPP_EVENT_DISCONNECT:
        {
            g_clientContext.conn_id = -1;
            break;
        }

        case VM_BT_SPP_EVENT_READY_TO_WRITE:
        {
            g_clientContext.ptr->post_signal_write();
            break;
        }
        
        case VM_BT_SPP_EVENT_READY_TO_READ:
        {
        	  bt_client_spp_read(NULL);
        	
#if(0)
            g_clientContext.ptr->post_signal_read();
#endif
            break;
        }

    }

}

static VMINT bt_client_init_spp()
{
    VMUINT evt_mask = VM_BT_SPP_EVENT_CONNECT | 
                      VM_BT_SPP_EVENT_READY_TO_WRITE | 
                      VM_BT_SPP_EVENT_READY_TO_READ | 
                      VM_BT_SPP_EVENT_DISCONNECT;
    
    g_clientContext.btspp_hdl = vm_bt_spp_open(evt_mask,bt_client_spp_cb,NULL);
    
    if(g_clientContext.btspp_hdl < 0)
    {
        APP_LOG((char*)"[BTC]bt_client_init_spp fail : btspp_open");

        return g_clientContext.btspp_hdl;
    }

    vm_bt_spp_set_security_level(g_clientContext.btspp_hdl,VM_BT_SPP_SECURITY_NONE);

    VMINT min_buf_size = vm_bt_spp_get_min_buffer_size();
    g_clientContext.btspp_buf = vm_calloc(min_buf_size);
    g_clientContext.btspp_buf_size = min_buf_size;

    if(g_clientContext.btspp_buf == NULL)
    {
        APP_LOG((char*)"[BTC]bt_client_init_spp fail : alloc buffer");

        return -1;
    }

    APP_LOG("[BTC]bt_client_init_spp done, btspp_hdl=%d", g_clientContext.btspp_hdl);

    return 0;

}

static boolean bt_client_end_spp()
{
    if(g_clientContext.btspp_hdl >= 0)
    {
        vm_bt_spp_close(g_clientContext.btspp_hdl);
        g_clientContext.btspp_hdl = -1;
    }

    if(g_clientContext.btspp_buf != NULL)
    {
        vm_free(g_clientContext.btspp_buf);
        g_clientContext.btspp_buf = NULL;
    }

    if(g_clientContext.conn_id >= 0)
    {
        g_clientContext.conn_id = -1;
    }

    VMINT ret = vm_bt_cm_get_power_status();

    APP_LOG("[BTC]bt_client_end_spp, power status = %d", ret);

    if (VM_BT_CM_POWER_ON == ret)
    {
        VMINT ret = vm_bt_cm_switch_off();

        if(VM_BT_CM_RESULT_SUCCESS == ret)
        {
            g_clientContext.client_status = BT_CLIENT_POWERING_OFF;

            APP_LOG("[BTC]bt_client_end_spp, wait for power off bt 1");

            return false;
        }
    }
    else if (VM_BT_CM_POWER_SWITCHING_ON == ret)
    {
        g_clientContext.client_status = BT_CLIENT_ENDING;

        APP_LOG("[BTC]bt_client_end_spp, wait for power on bt");

        return false;
    }
    else if (VM_BT_CM_POWER_SWITCHING_OFF == ret)
    {
        g_clientContext.client_status = BT_CLIENT_POWERING_OFF;

        APP_LOG("[BTC]bt_client_end_spp, wait for power off bt 2");

        return false;
    }

    // VM_BT_CM_POWER_OFF
    if(g_clientContext.btcm_hdl >= 0)
    {
        vm_bt_cm_exit(g_clientContext.btcm_hdl);
        g_clientContext.btcm_hdl = -1;
    }

    g_clientContext.client_status = BT_CLIENT_IDLE;

    APP_LOG("[BTC]bt_client_end_spp, done");

    return true;

}

boolean btClientBegin(void *userData)
{

    APP_LOG("[Kinse][BTC]btClientBegin, 1");

    APP_LOG("[Kinse][BTC]btClientBegin = %d, status[%d]" , g_clientContext.btcm_hdl, g_clientContext.client_status);

    LBTClientBeginContext* c = (LBTClientBeginContext*) userData;
    g_clientContext.ptr = (LBTClientClass*)c->ptr;
    if(g_clientContext.btcm_hdl >= 0)
    {
        //already inited
        c->result = false;
        APP_LOG((char*)"[BTC]btClientBegin fail : already inited");
        return true;        
    }

    g_clientContext.btcm_hdl = vm_bt_cm_init(
        bt_client_btcm_cb,     
        VM_BT_CM_EVENT_ACTIVATE |
        VM_BT_CM_EVENT_DEACTIVATE |
        VM_BT_CM_EVENT_INQUIRY_IND |
        VM_BT_CM_EVENT_PAIR_INDICATION |
        VM_BT_CM_EVENT_SECURITY_USER_CONFIRM |
        VM_BT_CM_EVENT_INQUIRY_COMPLETE,
        NULL);

    APP_LOG("[Kinse][BTC]btClientBegin, 2 = %d" ,g_clientContext.btcm_hdl);

    if(g_clientContext.btcm_hdl < 0)
    {
        c->result = false;
        APP_LOG((char*)"[BTC]btClientBegin fail : btcm_init fail");
        return true;
    }


    VMINT ret = vm_bt_cm_get_power_status();

    APP_LOG("[BTC]btClientBegin, power status = %d", ret);

    if (VM_BT_CM_POWER_OFF == ret)
    {
        ret = vm_bt_cm_switch_on();

        if(VM_BT_CM_RESULT_SUCCESS == ret)
        {
            //wait for callback to process
            g_clientContext.client_status = BT_CLIENT_POWERING_ON;
            g_clientContext.waiting_result_p = &(c->result);

            APP_LOG("[BTC]btClientBegin, wait for power on bt 1, btcm_hdl=%d", g_clientContext.btcm_hdl);

            return false;
        }
    }
    else if (VM_BT_CM_POWER_SWITCHING_OFF == ret)
    {
        g_clientContext.client_status = BT_CLIENT_BEGINING;
        g_clientContext.waiting_result_p = &(c->result);

        APP_LOG("[BTC]btClientBegin, wait for power off bt, btcm_hdl=%d", g_clientContext.btcm_hdl);

        return false;
    }
    else if (VM_BT_CM_POWER_SWITCHING_ON == ret)
    {
        g_clientContext.client_status = BT_CLIENT_POWERING_ON;
        g_clientContext.waiting_result_p = &(c->result);

        APP_LOG("[BTC]btClientBegin, wait for power on bt 2, btcm_hdl=%d", g_clientContext.btcm_hdl);

        return false;
    }
    else if (VM_BT_CM_POWER_ON == ret)
    {
        ret = bt_client_init_spp();
    }

    if(ret<0)
    {
        c->result = false;
        APP_LOG((char*)"[BTC]btClientBegin fail : init app fail");        
        return bt_client_end_spp();
    }

    //success
    g_clientContext.client_status = BT_CLIENT_READY;
    c->result = true;

    APP_LOG("[BTC]btClientBegin done, btcm_hdl=%d", g_clientContext.btcm_hdl);

	return true;

}


boolean btClientEnd(void *userData)
{
    APP_LOG("[BTC]btClientEnd");

	return bt_client_end_spp();;
}

boolean btClientConnect(void *userData)
{
    LBTClientConnectContext* pContext = (LBTClientConnectContext*)userData ;

    if(g_clientContext.conn_id != -1)
    {
        //someone connected
        APP_LOG((char*)"[BTC]btClientConnect fail : already connected = %d", g_clientContext.conn_id);

        pContext->result = false;
        return true;        
    }
    if(pContext->is_set_pin == true)
    {
        vm_bt_cm_set_bt_pairing_type(VM_BT_CM_PIN_AND_SSP);
    }
    vm_bt_cm_bt_address_t btspp_addr = {0};
    btspp_addr.lap = ((0x000000ff & (VMUINT)pContext->address->lap[2]) << 16) | 
        ((0x000000ff & (VMUINT)pContext->address->lap[1]) << 8) | 
        (0x000000ff & (VMUINT)pContext->address->lap[0]);
    btspp_addr.uap = pContext->address->uap;
    btspp_addr.nap = ((0x00ff & (VMUINT16)pContext->address->nap[1]) << 8) | (0x00ff & (VMUINT16)pContext->address->nap[0]);
    VMUINT8 *tmp = (VMUINT8*)&btspp_addr.nap;
    APP_LOG("[BTC]btClientConnect nap 0x%x, 0x%x", tmp[1], tmp[0]);
    APP_LOG("[BTC]btClientConnect nap:%x, uap:%x, lap:%x", btspp_addr.nap, btspp_addr.uap, btspp_addr.lap);

    VMINT ret = vm_bt_spp_connect(
        g_clientContext.btspp_hdl,
        &btspp_addr,
        g_clientContext.btspp_buf, 
        g_clientContext.btspp_buf_size/2, 
        g_clientContext.btspp_buf_size/2, 
        SPP_UUID);


    APP_LOG("[BTC]btClientConnect ret[%d], address: %02x:%02x:%02x:%02x:%02x:%02x:", 
                ret,
                pContext->address->nap[1],
                pContext->address->nap[0],
                pContext->address->uap,
                pContext->address->lap[2],
                pContext->address->lap[1],
                pContext->address->lap[0]);


    if( ret < 0)
    {
        //connect fail
        pContext->result = false;
        return true;
    }

    // wait for connect result
    g_clientContext.waiting_result_p = &(pContext->result);
	return false;
}

boolean btClientConnected(void *userData)
{
    boolean* result = (boolean*) userData;

    APP_LOG("[BTC]btClientConnected, conn_id = %d", g_clientContext.conn_id);

    if(g_clientContext.conn_id != -1)
    {
        //connected
        *result = true;
    }
    else
    {
        //not connected yet
        *result = false;
    }

    return true;
}

static void bt_client_timeout_cb(VM_TIMER_ID_PRECISE tid, void* user_data)
{
    APP_LOG("[BTC]bt_client_timeout_cb %d", tid);
    if (tid == g_clientContext.search_tid)
    {
        vm_bt_cm_search_abort();
        vm_timer_delete_precise(g_clientContext.search_tid);
        g_clientContext.search_tid = 0;
    }
}
boolean btClientScan(void *userData)
{
    LBTClientScanContext* pContext = (LBTClientScanContext*)userData ;

    g_clientContext.scan_number = 0;

    APP_LOG("[BTC]btClientScan, time_out = %d", pContext->time_out);

    if(pContext->time_out == 0)
    {
        pContext->number = g_clientContext.scan_number;
        return true ;
    }

    VMINT ret = vm_bt_cm_search(MAX_DEVICE_SCANNED, pContext->time_out, 0xFFFFFFFF, 1);

    if (ret < 0)
    {
        pContext->number = g_clientContext.scan_number;

        APP_LOG((char*)"[BTC]btClientScan fail : btcm_search fail");

        return true;
    }

    g_clientContext.search_tid = vm_timer_create_precise(pContext->time_out*1000, bt_client_timeout_cb, NULL);
    APP_LOG("[BTC]search_tid = %d, timeout = %d", g_clientContext.search_tid, pContext->time_out*1000);
    g_clientContext.scan_number_p = &(pContext->number);
	return false;
}

boolean btClientGetDeviceInfo(void *userData)
{

    LBTClientGetDeviceInfoContext* pContext = (LBTClientGetDeviceInfoContext*)userData;

    if(pContext->index < 0 || pContext->index >= g_clientContext.scan_number)
    {
        //invalid range

        APP_LOG((char*)"[BTC]btClientGetDeviceInfo : invalid range = %d", pContext->index);

        pContext->result = false;
        return true;
    }

    vm_bt_cm_device_info_t dev_info ;

    if( VM_BT_CM_ERROR_SUCCESS == vm_bt_cm_get_device_info_by_index(pContext->index, VM_BT_CM_DEVICE_DISCOVERED, &dev_info) )
    {
        pContext->device_info->address.nap[0] = (dev_info.device_address.nap & 0x00ff);
        pContext->device_info->address.nap[1] = (dev_info.device_address.nap & 0xff00) >> 8;
        pContext->device_info->address.uap = dev_info.device_address.uap;
        pContext->device_info->address.lap[0] = (dev_info.device_address.lap & 0x0000ff);
        pContext->device_info->address.lap[1] = (dev_info.device_address.lap & 0x00ff00) >> 8;
        pContext->device_info->address.lap[2] = (dev_info.device_address.lap & 0xff0000) >> 16;

        strcpy(pContext->device_info->name, (const char*)dev_info.name);

        APP_LOG("[BTC]btClientGetDeviceInfo, name: %s", dev_info.name);

        APP_LOG("[BTC]btClientGetDeviceInfo, device_address: nap:%x, uap:%x, lap:%x",
                    dev_info.device_address.nap,
                    dev_info.device_address.uap,
                    dev_info.device_address.lap);


        APP_LOG("[BTC]btClientGetDeviceInfo, address: %02x:%02x:%02x:%02x:%02x:%02x:", 
                    pContext->device_info->address.nap[1],
                    pContext->device_info->address.nap[0],
                    pContext->device_info->address.uap,
                    pContext->device_info->address.lap[2],
                    pContext->device_info->address.lap[1],
                    pContext->device_info->address.lap[0]);

        pContext->result = true;
    }
    else
    {
        // fail to get the device info
        APP_LOG((char*)"[BTC]btClientGetDeviceInfo : get_dev_info_by_index fail");
        pContext->result = false;
    }

    return true;

}

boolean btClientRead(void *userData)
{

    LBTClientReadWriteContext* pContext = (LBTClientReadWriteContext*)userData;

    if(g_clientContext.conn_id < 0)
    {
        //not connected yet

        APP_LOG((char*)"[BTC]btClientRead : not connected yet");

        pContext->lenProcessed = 0;
        return true;
    }

    VMINT ret = vm_bt_spp_read(g_clientContext.conn_id, pContext->buf, pContext->len);

    APP_LOG("[BTC]btClientRead, ret: %d", ret);

    if (ret < 0)
    {
        //read fail
        pContext->lenProcessed = 0;
    }
    else 
    {
        pContext->lenProcessed = ret;
    }

	return true;
}

boolean btClientWrite(void *userData)
{
    LBTClientReadWriteContext* pContext = (LBTClientReadWriteContext*)userData;

    if(g_clientContext.conn_id < 0)
    {
        //not connected yet

        APP_LOG((char*)"[BTC]btClientWrite : not connected yet");

        pContext->lenProcessed = 0;
        return true;
    }

    VMINT ret = vm_bt_spp_write(g_clientContext.conn_id, pContext->buf, pContext->len);

    APP_LOG("[BTC]btClientWrite, ret: %d", ret);

    if (ret < 0)
    {
        //read fail
        pContext->lenProcessed = 0;
    }
    else 
    {
        pContext->lenProcessed = ret;
    }

	return true;
}

