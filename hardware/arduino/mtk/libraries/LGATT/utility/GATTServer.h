#ifndef __GATT_SERVER_H__
#define __GATT_SERVER_H__
//#ifdef __cplusplus
//extern "C" 
//{
//#endif


#include "LGATT.h"
#include "LGATTServer.h"
#include "vmbt_gatt.h"
#include "vmbt_cm.h"


#define MAX_ATTRS 8


typedef enum
{
    VM_OS_STATUS_SUCCESS	= 0,
    VM_OS_STATUS_FAILED	    = 1,
}VM_OS_STATUS;

typedef struct 
{
   VMUINT8 uu[16];
}vm_bt_uuid_struct;


boolean gattServiceRemoteCallHandler(void *userdata);

class GATTService
{
public:
    boolean init(LGATTService &s);
    void deinit(LGATTService &s);

    
    static boolean rBegin(void *userdata);
    static boolean rSend(void *userdata);
    static boolean rEnd(void *userdata);
    
private:

    static void initCB(LGATTService *service);
    static void *alloc(); /* gatts_srv_ctx_t */
    static void dealloc(void *ptr); /* gatts_srv_ctx_t */
    static VMINT toRegist(LGATTService *service);
    static VMINT addDeclaration(LGATTService *service, VM_BT_GATT_ATTRIBUTE_HANDLE srvc_handle, ard_decl_type_enum type);


	static void register_server_callback(VM_BT_GATT_CONTEXT_HANDLE reg_ctx, VMBOOL status, VMUINT8 *app_uuid);
	
	static void service_added_callback(VMBOOL status, VM_BT_GATT_CONTEXT_HANDLE reg_ctx, vm_bt_gatt_service_info_t *srvc_id, VM_BT_GATT_SERVICE_HANDLE srvc_handle);
	
	static void characteristic_added_callback(VMBOOL status, VM_BT_GATT_CONTEXT_HANDLE reg_ctx, vm_bt_gatt_attribute_uuid_t *uuid, VM_BT_GATT_SERVICE_HANDLE srvc_handle, VM_BT_GATT_CHARACTERISTIC_HANDLE char_handle);
	
	static void descriptor_added_callback(VMBOOL status, VM_BT_GATT_CONTEXT_HANDLE reg_ctx, vm_bt_gatt_attribute_uuid_t *uuid, VM_BT_GATT_SERVICE_HANDLE srvc_handle, VM_BT_GATT_DESCRIPTOR_HANDLE descr_handle);
	
	static void service_started_callback(VMBOOL status, VM_BT_GATT_CONTEXT_HANDLE reg_ctx, VM_BT_GATT_SERVICE_HANDLE srvc_handle);
	
	static void listen_callback(VM_BT_GATT_CONTEXT_HANDLE reg_ctx, VMBOOL status);

	static void connection_callback(const vm_bt_gatt_connection_t *conn, VMBOOL connected, const vm_bt_gatt_address_t *bd_addr);
	
    static void request_read_callback(vm_bt_gatt_connection_t *conn, VMUINT16 trans_id, vm_bt_gatt_address_t *bd_addr, VM_BT_GATT_ATTRIBUTE_HANDLE attr_handle, VMUINT16 offset, VMBOOL is_long);
	
    static void request_write_callback(vm_bt_gatt_connection_t *conn, VMUINT16 trans_id, vm_bt_gatt_address_t *bd_addr, VM_BT_GATT_ATTRIBUTE_HANDLE attr_handle, vm_bt_gatt_attribute_value_t *value, VMUINT16 offset, VMBOOL need_rsp, VMBOOL is_prep);

    static vm_bt_gatt_server_callback_t _gatts_service_cb;

};

boolean gattServerRemoteCallHandler(void *userdata);
class GATTServer
{
public:


    static boolean rBegin(LGATTServerClass *server);
    static boolean rEnd(LGATTServerClass *server);

    static boolean rEnQ(const gatts_q_node &node);

    static LGATTService *getCtxByUUID(vm_bt_uuid_struct *app_uuid);
    static LGATTService *getCtxByCTX(void *reg_ctx);
    static LGATTService *getCtxByHandle(void *reg_ctx, VM_BT_GATT_ATTRIBUTE_HANDLE srvc_handle);
    
private:
    static void btcm_cb(VM_BT_CM_EVENT evt, void* param, void* user_data);
    static boolean init(LGATTServerClass *server);
    static boolean deinit(LGATTServerClass *server);

    static LGATTServerClass *_server;
    static VMINT _hdl_btcm;
};


//#ifdef __cplusplus
//}
//#endif

#endif
