
#include "Arduino.h"
#include "stdio.h"
#include "string.h"
#include "vmgsm_gprs.h"
#include "vmsock.h"
#include "vmbearer.h"
#include "BSDTCPClient.h"


#define CONNECT_PORT 80
#define APN "cmwap"
//#define USING_PROXY VM_TRUE
#define USING_PROXY VM_FALSE
#define PROXY_IP    "10.0.0.172"
#define PROXY_PORT  80

#define MAX_ADDR_LEN 64
#define MAX_REQU_LEN 256
#define MAX_BUF_LEN 512


char address[MAX_ADDR_LEN] = {0, };
char request[MAX_REQU_LEN] = {0, }; 
char content[MAX_BUF_LEN] = {0, };

static VM_BEARER_HANDLE g_bearer_hdl;
static VM_THREAD_HANDLE g_thread_handle;
static VMINT g_soc_client;


void (*g_http_new_event_cb)(char *, long) = NULL;


static VMINT32 soc_sub_thread(VM_THREAD_HANDLE thread_handle, void* user_data)
{
    SOCKADDR_IN addr_in = {0};
    int len = 0;
    int ret;
    
    Serial.println("soc sub thread.");

    g_soc_client = socket(PF_INET, SOCK_STREAM, 0);
    addr_in.sin_family = PF_INET;
    addr_in.sin_addr.S_un.s_addr = inet_addr(address);
    addr_in.sin_port = htons(CONNECT_PORT);
    
    ret = connect(g_soc_client, (SOCKADDR*)&addr_in, sizeof(SOCKADDR));
    
    ret = send(g_soc_client, request, strlen(request), 0);
    len = recv(g_soc_client, content, MAX_BUF_LEN, 0);
    
    if(len > 0)
    {
        content[len] = 0;
        g_http_new_event_cb((char *)content, len);
    }
    else
    {        
        Serial.println("Received FIN from server");
    }
    
    closesocket(g_soc_client);
    
    return 0;
}

static void bearer_callback(VM_BEARER_HANDLE handle, VM_BEARER_STATE event, VMUINT data_account_id, void *user_data)
{    
    //Serial.print("bearer call back handle is ");
    //Serial.println(handle);
    ///Serial.print("bearer call back event is ");
    //Serial.println(event);
    
    if(VM_BEARER_WOULDBLOCK == g_bearer_hdl)
    {
        g_bearer_hdl = handle;
    }
    if(handle == g_bearer_hdl)
    {
        switch (event)
        {
            case VM_BEARER_DEACTIVATED:
                break;
            case VM_BEARER_ACTIVATING:
                break;
            case VM_BEARER_ACTIVATED:
                g_thread_handle = vm_thread_create(soc_sub_thread, NULL, 0);
                break;
            case VM_BEARER_DEACTIVATING:
                break;
            default:
                break;
        }
    }
}

static void set_custom_apn(void)
{
    VMINT ret;
    vm_gsm_gprs_apn_info_t apn_info;

    memset(&apn_info, 0, sizeof(apn_info));
    apn_info.using_proxy = USING_PROXY;
    strcpy((char *)apn_info.apn, APN);
    strcpy((char *)apn_info.proxy_address, PROXY_IP);
    apn_info.proxy_port = PROXY_PORT;
    
    ret = vm_gsm_gprs_set_customized_apn_info(&apn_info);
}

static void client_send_request(void)
{
    set_custom_apn();
    //g_bearer_hdl = vm_bearer_open(VM_BEARER_DATA_ACCOUNT_TYPE_GPRS_CUSTOMIZED_APN, NULL, bearer_callback, VM_BEARER_IPV4);
    g_bearer_hdl = vm_bearer_open(VM_BEARER_DATA_ACCOUNT_TYPE_GPRS_NONE_PROXY_APN, NULL, bearer_callback, VM_BEARER_IPV4);
    Serial.print("vm_bearer_open handle is ");
    Serial.println(g_bearer_hdl);
}


boolean BSD_TCP_client_connect(void* user_data)
{
    char *buf = (char *)user_data;
    
    if(strlen(buf) > MAX_ADDR_LEN)return true;
    
    memset(address, 0, MAX_ADDR_LEN);
    memcpy(address, buf, strlen(buf));
    
    return true;
}

boolean BSD_TCP_client_request(void* user_data)
{
    char *buf = (char *)user_data;
    
    if(strlen(buf) > MAX_REQU_LEN)return true;
    
    memset(request, 0, MAX_REQU_LEN);
    memcpy(request, buf, strlen(buf));
    
    client_send_request();
        
    return true;
}

boolean BSD_TCP_client_set_new_event_callback(void(*cb)(char *, long))
{
    g_http_new_event_cb = cb;
    
	return true;
}
