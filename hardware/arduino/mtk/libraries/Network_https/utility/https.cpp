
#include "Arduino.h"
#include "vmlog.h" 
#include "vmhttps.h"
#include "vmgsm_gprs.h"
#include "stdio.h"
#include "string.h"
#include "https.h"


#define CUST_APN    	"cmwap"         	// The APN of your test SIM
#define USING_PROXY 	VM_TRUE         	// Whether your SIM uses proxy
#define PROXY_ADDRESS   "10.0.0.172"    	// The proxy address
#define PROXY_PORT  	80              	// The proxy port


#define MAX_READ_LENGHT	256
#define MAX_LENGHT		(MAX_READ_LENGHT + 16) 


char url[MAX_LENGHT] = {0,};
char content[MAX_LENGHT] = {0, };

VMUINT8 g_channel_id;
VMUINT16 g_request_id;
VMINT g_read_seg_num;
VMINT g_read_ok;


void (*g_http_new_event_cb)(char *, unsigned long) = NULL;

static void https_send_request_set_channel_rsp_cb(VMUINT32 req_id, VMUINT8 channel_id, VM_HTTPS_RESULT result)
{
    VMINT ret = -1;

    ret = vm_https_send_request(
        0,                  				/* Request ID */
        VM_HTTPS_METHOD_GET,                /* HTTP Method Constant */
        VM_HTTPS_OPTION_NO_CACHE,           /* HTTP request options */
        VM_HTTPS_DATA_TYPE_BUFFER,          /* Reply type (wps_data_type_enum) */
        MAX_READ_LENGHT,                    /* bytes of data to be sent in reply at a time. If data is more that this, multiple response would be there */
        (VMSTR)url,        					/* The request URL */
        strlen(url),           				/* The request URL length */
        NULL,                               /* The request header */
        0,                                  /* The request header length */
        NULL,
        0);

    if(ret != 0)
	{
        vm_https_unset_channel(channel_id);
    }
}

static void https_unset_channel_rsp_cb(VMUINT8 channel_id, VM_HTTPS_RESULT result)
{
	Serial.print("\r\nhttps_unset_channel_rsp_cb()\r\n");
	
}

static void https_send_release_all_req_rsp_cb(VM_HTTPS_RESULT result)
{
	Serial.print("\r\nhttps_send_release_all_req_rsp_cb()\r\n");
}

static void https_send_termination_ind_cb(void)
{
	Serial.print("\r\nhttps_send_termination_ind_cb()\r\n");
}

static void https_send_read_request_rsp_cb(VMUINT16 request_id, VM_HTTPS_RESULT result, 
                                           VMUINT16 status, VMINT32 cause, VM_HTTPS_PROTOCOL protocol, 
                                           VMUINT32 content_length,VMBOOL more,
                                           VMSTR content_type, VMUINT8 content_type_len,  
                                           VMSTR new_url, VMUINT32 new_url_len,
                                           VMSTR reply_header, VMUINT32 reply_header_len,  
                                           VMSTR reply_segment, VMUINT32 reply_segment_len)
{
    VMINT ret = -1;
	
	Serial.print("\r\nhttps_send_request_rsp_cb()\r\n");
	
	g_request_id = request_id;
	
    if(result != 0)
	{
        vm_https_cancel(request_id);
        vm_https_unset_channel(g_channel_id);
		
		g_read_ok = false;
    }
    else
	{
		//Serial.print((char *)reply_segment);
		//memset(content, MAX_LENGHT, 0);
		//memcpy(content, reply_segment, reply_segment_len);
		g_http_new_event_cb((char *)reply_segment, reply_segment_len);
		
        ret = vm_https_read_content(request_id, ++g_read_seg_num, MAX_READ_LENGHT);
        if(ret != 0)
		{
            vm_https_cancel(request_id);
            vm_https_unset_channel(g_channel_id);
			
			g_read_ok = false;
        }
		else g_read_ok = true;
    }
}
static void https_send_read_read_content_rsp_cb(VMUINT16 request_id, VMUINT8 seq_num, 
                                                VM_HTTPS_RESULT result, VMBOOL more, 
                                                VMWSTR reply_segment, VMUINT32 reply_segment_len)
{
    VMINT ret = -1;
	
	g_request_id = request_id;		
	
	//Serial.print((char *)reply_segment);
	//memset(content, MAX_LENGHT, 0);
	//memcpy(content, reply_segment, reply_segment_len);
	g_http_new_event_cb((char *)reply_segment, reply_segment_len);
		
    if(more > 0)
	{
        ret = vm_https_read_content(
            request_id,                       /* Request ID */
            ++g_read_seg_num,                 /* Sequence number (for debug purpose) */
            MAX_READ_LENGHT);                 /* The suggested segment data length of replied data in the peer buffer of 
                                                 response. 0 means use reply_segment_len in MSG_ID_WPS_HTTP_REQ or 
                                                 read_segment_length in previous request. */
        if(ret != 0)
		{
            vm_https_cancel(request_id);
            vm_https_unset_channel(g_channel_id);
			
			g_read_ok = false;
        }
		else g_read_ok = true;
    }
    else
	{
        /* don't want to send more requests, so unset channel */
        vm_https_cancel(request_id);
        vm_https_unset_channel(g_channel_id);
        g_channel_id = 0;
        g_read_seg_num = 0;
		
		g_read_ok = false;
    }
}

static void https_send_cancel_rsp_cb(VMUINT16 request_id, VM_HTTPS_RESULT result)
{
	Serial.print("\r\nhttps_send_cancel_rsp_cb()");
}

static void https_send_status_query_rsp_cb(VMUINT8 status)
{
	Serial.print("\r\nhttps_send_status_query_rsp_cb()");
}

static void set_custom_apn(void)
{
    vm_gsm_gprs_apn_info_t apn_info;
    
    memset(&apn_info, 0, sizeof(apn_info));
    strcpy((char *)apn_info.apn, CUST_APN);
    strcpy((char *)apn_info.proxy_address, PROXY_ADDRESS);
    apn_info.proxy_port = PROXY_PORT;
    apn_info.using_proxy = USING_PROXY;
    vm_gsm_gprs_set_customized_apn_info(&apn_info);
}

static void https_send_request(void)
{
	VMINT ret = -1;
	VM_BEARER_DATA_ACCOUNT_TYPE apn = VM_BEARER_DATA_ACCOUNT_TYPE_GPRS_CUSTOMIZED_APN;
	
	vm_https_callbacks_t callbacks = {
		https_send_request_set_channel_rsp_cb,
		https_unset_channel_rsp_cb,
		https_send_release_all_req_rsp_cb,
		https_send_termination_ind_cb,
		https_send_read_request_rsp_cb,
		https_send_read_read_content_rsp_cb,
		https_send_cancel_rsp_cb,
		https_send_status_query_rsp_cb
	};

	set_custom_apn();
	ret = vm_https_register_context_and_callback(apn, &callbacks);

	if(ret != 0)
	{
		return;
	}

	/* set network profile information */
	ret = vm_https_set_channel(
	0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0,
	0, 0
	);
}

boolean https_set_new_event_callback(void(*cb)(char *, unsigned long))
{
    g_http_new_event_cb = cb;
	return true;
}

boolean https_connect(void* user_data)
{
	char *buf = (char *)user_data;
	
	if(strlen(buf) > MAX_LENGHT)return true;
	
	memset(url, 0, strlen(url));
	memcpy(url, buf, strlen(buf));
	Serial.println(url);
	
	https_send_request();
	
	return true;
}

boolean https_stop(void* user_data)
{
	vm_https_cancel(g_request_id);
	vm_https_unset_channel(g_channel_id);
	g_channel_id = 0;
	g_read_seg_num = 0;
	g_read_ok = false;
	
	return true;
}
