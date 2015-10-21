/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005-2015
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifndef VMGPS_SDK_H
#define VMGPS_SDK_H


#ifdef __cplusplus
extern "C" {
#endif

#include "vmtype.h"





/*The GPS type. GPS is always used, it can be enhanced with the optional support of Beidou and GLONASS. The actual support of multiple satellite systems is dependent on the underlying hardware platform. */
/*GPS type. The type is dependent on your GPS chipset. Only MediaTek MTK3336 supports VM_GPS_ONLY. */
typedef enum
{
    VM_GPS_ONLY,    /* The GPS ONLY type. */
    VM_GPS_GLONASS, /* The GPS and GLONASS type. */
    VM_GPS_BEIDOU   /* The GPS and BEIDOU type. */
} VM_GPS_TYPE;


#define VM_GPS_MAX_GPGGA_SENTENCE_LENGTH 100
#define VM_GPS_MAX_GPGSA_SENTENCE_LENGTH 80
#define VM_GPS_MAX_GPRMC_SENTENCE_LENGTH 100
#define VM_GPS_MAX_GPVTG_SENTENCE_LENGTH 80
#define VM_GPS_MAX_GPGSV_SENTENCE_LENGTH 400
#define VM_GPS_MAX_GLGSV_SENTENCE_LENGTH 400
#define VM_GPS_MAX_BDGSV_SENTENCE_LENGTH 400
#define VM_GPS_MAX_BDGSA_SENTENCE_LENGTH 80
#define VM_GPS_MAX_GLGSA_SENTENCE_LENGTH 80


/*The GPS data structure */
typedef struct
{
    VMCHAR  GPGGA[VM_GPS_MAX_GPGGA_SENTENCE_LENGTH+1];     /* The GGA data type. */
    VMCHAR  GPGSA[VM_GPS_MAX_GPGSA_SENTENCE_LENGTH+1];     /* The GSA data type. */
    VMCHAR  GPRMC[VM_GPS_MAX_GPRMC_SENTENCE_LENGTH+1];     /* TheRMC data type.*/
    VMCHAR  GPVTG[VM_GPS_MAX_GPVTG_SENTENCE_LENGTH+1];     /* TheVTG data type.*/
    VMCHAR  GPGSV[VM_GPS_MAX_GPGSV_SENTENCE_LENGTH+1];     /* TheGSV data type.*/
    VMCHAR  GLGSV[VM_GPS_MAX_GLGSV_SENTENCE_LENGTH+1];     /* TheGLONASS GSV data type.*/
    VMCHAR  GLGSA[VM_GPS_MAX_GLGSA_SENTENCE_LENGTH+1];     /* TheGLONASS GSA data type.*/
    VMCHAR  BDGSV[VM_GPS_MAX_BDGSV_SENTENCE_LENGTH+1];     /* TheBD GSV data type.*/
    VMCHAR  BDGSA[VM_GPS_MAX_BDGSA_SENTENCE_LENGTH+1];     /* TheBD GSA data type.*/
} vm_gps_sentence_info_t;



/*The GPS start parameters.*/
typedef enum
{
    VM_GPS_SET_LOCATION_REPORT_PERIOD = 1,           /* The Normal mode. The minimum time is 1 second. */
    VM_GPS_SET_LOCATION_REPORT_PREIOD_SLEEP_FIRST,   /* The 'Sleep First' mode is a low power mode. GPS is powered off in the beginning and will be switched on to get the position before the set period times out.*/
    VM_GPS_SET_LOCATION_REPORT_PREIOD_WROK_FIRST,    /* The 'Work First' mode is a low power mode. GPS is powered on in the beginning to get the position and once the position is found, it will switch off to save energy. After the set period it will power itself on.*/
    VM_GPS_SET_ASSIST_DATA_FOR_FAST_FIXED            /*The 'Set GPS assist data for fast fix' type. */
} VM_GPS_PARAMETERS;

/*The GPS assist data.*/
typedef struct
{
    VMUINT16      u2YEAR ;             /* > 2000 */
    VMUINT8       u1MONTH;             /* 1~12 */
    VMUINT8       u1DAY;               /* 1~31*/
    VMUINT8       u1HOUR;              /* 0~23*/
    VMUINT8       u1MIN;               /* 0~59*/
    VMUINT8       u1SEC;               /* 0~59*/
    double	Latitude;				/* reserved */
    double	Longitude;				/* reserved */
    double	Altitude;               /* reserved */
} vm_gps_assist_data_config_t;

/*The GPS callback message.*/
typedef enum
{
    VM_GPS_OPEN_RESULT,         /* The GPS open confirm message, the data is the result (success/failure) of opening GPS.*/
    VM_GPS_SET_MODE_RESULT,     /* Reserved. */
    VM_GPS_CLOSE_RESULT,        /* Reserved, the engine will release all resources when GPS is closed, so it will not send a 'closed' message. */
    VM_GPS_SENTENCE_DATA,       /* GPS data receive message, the data represents the GPS sentence data, please refer to vm_gps_sentence_info_t. */
    VM_GPS_SET_PARAM_RESULT,    /* GPS set parameter confirm message, data shows if it was successful or not*/
    VM_GPS_MESSAGE_TYPE_MAX = 0x7FFFFFFF
} VM_GPS_MESSAGE;

/*****************************************************************************
 * FUNCTION
 *  vm_gps_callback
 * DESCRIPTION
 *  This function represents a GPS callback.
 * PARAMETERS
 *  message:[IN] GPS message  open/set mode/sentence ...
 *  data: [IN] message parameters, please refer to VM_GPS_PARAMETERS.
 *  user_data:[IN] user data
 *****************************************************************************/
typedef void (*vm_gps_callback)(VM_GPS_MESSAGE message, void* data, void* user_data);

/*****************************************************************************
* FUNCTION
 *    vm_gps_open
 * DESCRIPTION
 *  This will initialize GPS and opens the UART port.
 * PARAMETERS
 *  type:[IN] GPS type, refer to vm_gps_type_enum
 *  callback:[IN]The GPS callback function
 *  user_data:[IN]user data
 * RETURNS
 *  VM_SUCCESS : Opened successfully.
 *  VM_FAIL : Failed while opening.
 *****************************************************************************/
VM_RESULT vm_gps_open(VM_GPS_TYPE type, vm_gps_callback callback, void* user_data);


/*****************************************************************************
* FUNCTION
 *    vm_gps_set_parameter
 * DESCRIPTION
 *  This function sets a GPS parameter
 * PARAMETERS
 *  parameter   :[IN]Parameter you want to set, refer to VM_GPS_PARAMETERS
 *  value       :[IN]Parameter value
 *  user_data   :[IN]User data
 * RETURNS
 *  VM_SUCCESS : Successfully set the parameter.
 *  VM_FAIL : Failed
*****************************************************************************/
VM_RESULT vm_gps_set_parameters(VM_GPS_PARAMETERS parameters, VMUINT32 value, void* user_data);


/*****************************************************************************
* FUNCTION
* vm_gps_close
* DESCRIPTION
* This function will close GPS if it is not in use by any other application.
* RETURNS
* VM_OK :Successfully closed GPS.
* VM_FAIL : Closing GPS failed.
*****************************************************************************/
VM_RESULT vm_gps_close(void);


#ifdef __cplusplus
}
#endif

#endif /* VMGPS_SDK_H */

