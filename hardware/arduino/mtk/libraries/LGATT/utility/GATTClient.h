#ifndef __GATT_CLIENT_H__
#define __GATT_CLIENT_H__

#include "vmbt_cm.h"
#include "vmbt_gatt.h"
#include "GATTClient.h"
#include "LTask.h"


typedef enum
{
    VM_OS_STATUS_SUCCESS	= 0,
    VM_OS_STATUS_FAILED	    = 1,
}VM_OS_STATUS;

typedef struct 
{
   VMUINT8 uu[16];
}vm_bt_uuid_struct;


extern boolean gattBegin(void *userData);
extern boolean gattScan(void *userData);
extern boolean gattConnect(void *userData);
extern boolean gattDisConnect(void *userData);
extern boolean gattEnableNotification(void *userData);
extern boolean gattQueryNotification(void *userData);
extern boolean gattGetCharacteristic(void *userData);
extern boolean gattGetDescriptor(void *userData);
extern boolean gattReadCharacteristic(void *userData);
extern boolean gattWriteCharacteristic(void *userData);
extern boolean gattReadDescriptor(void *userData);
extern boolean gattWriteDescriptor(void *userData);
extern boolean gattReadRemoteRSSI(void *userData);
extern boolean gattEnd(void *userData);


#endif
