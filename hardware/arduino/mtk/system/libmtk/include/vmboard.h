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

#ifndef _VMBOARD_SDK_H
#define _VMBOARD_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmtype.h"

/* pin mux mode */
typedef enum
{
    VM_DCL_PIN_MODE_GPIO = 1,  /* gpio mode */
    VM_DCL_PIN_MODE_ADC,       /* adc mode */
    VM_DCL_PIN_MODE_PWM,       /* pwm mode */
    VM_DCL_PIN_MODE_UART,      /* uart mode */
    VM_DCL_PIN_MODE_EINT,      /* eint mode */
    VM_DCL_PIN_MODE_SPI,       /* spi mode */
    VM_DCL_PIN_MODE_I2C,       /* i2c mode */
    VM_DCL_PIN_MODE_SDIO,      /* sdio mode */
    VM_DCL_PIN_MODE_DBI_C,     /* dbi mode */
} VM_DCL_PIN_MODE;

#if defined(__HDK_LINKIT_ONE_V1__)
#define D0   10    /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_UART */
#define D1   11    /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_UART */
#define D2   46    /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_EINT */
#define D3   13    /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_EINT / VM_DCL_PIN_MODE_PWM */
#define D4   40    /* Pin mux, VM_DCL_PIN_MODE_GPIO */
#define D5   3     /* Pin mux, VM_DCL_PIN_MODE_GPIO */
#define D6   25    /* Pin mux, VM_DCL_PIN_MODE_GPIO */
#define D7   50    /* Pin mux, VM_DCL_PIN_MODE_GPIO */
#define D8   48    /* Pin mux, VM_DCL_PIN_MODE_GPIO */
#define D9   19    /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_PWM */
#define D10 26     /* Pin mux, VM_DCL_PIN_MODE_GPIO */
#define D11 28     /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_SPI / VM_DCL_PIN_MODE_SDIO */
#define D12 29     /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_SPI / VM_DCL_PIN_MODE_SDIO */
#define D13 27     /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_SPI / VM_DCL_PIN_MODE_SDIO */
#define D14 0      /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_ADC */
#define D15 1      /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_ADC */
#define D16 2      /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_ADC */
#define D18 44     /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_I2C */
#define D19 43     /* Pin mux, VM_DCL_PIN_MODE_GPIO / VM_DCL_PIN_MODE_I2C */
#define A0 0       /* Pin mux, same with D14 */
#define A1 1       /* Pin mux, same with D15 */
#define A2 2       /* Pin mux, same with D16 */
#elif defined(__HDK_LINKIT_ASSIST_2502__)
#define D0 13
#define D1 3
#define D2 27
#define D3 29
#define D4 28
#define D5 19
#define D6 43
#define D7 44
#define D8 11
#define D9 10
#define D10 38
#define D11 39
#define D12 47
#define D13 48
#define D14 49
#define D15 50
#define A0 57
#define A1 0
#define A2 1
#define A3 2
#define E0 52
#elif defined(__HDK_MT2502D_DEV_BOARD__)
#define D0 13
#define D1 3
#define D2 27
#define D3 29
#define D4 28
#define D5 19
#define D6 43
#define D7 44
#define D8 11
#define D9 10
#define D10 38
#define D11 39
#define D12 47
#define D13 48
#define D14 49
#define D15 50
#define D16
#define D17
#define A0 57
#define A1 0
#define A2 1
#define A3 2
#define E0 52
#else
#define D0 0
#endif

#ifdef __cplusplus
}
#endif

#endif /* _VMBOARD_SDK_H */

