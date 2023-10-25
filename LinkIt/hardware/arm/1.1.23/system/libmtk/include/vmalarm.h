/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
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

#ifndef VMALARM_SDK_H_
#define VMALARM_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

typedef struct
{
    VMUINT16 nYear;
    VMUINT8 nMonth;
    VMUINT8 nDay;
    VMUINT8 nHour;
    VMUINT8 nMin;
    VMUINT8 nSec;
    VMUINT8 DayIndex; /* reserved*/
} vm_alarm_time_struct;


typedef enum
{
	VM_ALARM_ERROR_INVALID_ID = -6,	// Invalid alarm ID.
	VM_ALARM_ERROR_INVALID_TIME,		// Invalid alarm time. For example: the set time is earlier than current phone time.
	VM_ALARM_ERROR_OF_PROCESS,			// The alarm in operation does not belong to current application.
	VM_ALARM_ERROR_OF_RES ,					// Exceeds alarm resource limitation, the maximum value is 10.
	VM_ALARM_ERROR_OF_MEM ,					// Insufficient memory for alarm operation.
	VM_ALARM_ERROR ,								// Native alarm error.
	VM_ALARM_OK											// Alarm is set successfully.
} vm_alarm_error_t;


/* alarm expire callback function prototype */
typedef void (*VM_ALARMPROC_T)(VMINT alarm_id);


/******************************************************************************
 * FUNCTION
 *  vm_alarm_set
 * DESCRIPTION
 *  Sets alarm with a dedicated time and expiration callback function, the set time must be later than the current phone time. 
 *  When the set time expires, the expiration callback function will be executed.
 * PARAMETERS
 *  expire_time : [IN] The set time	.
 *  alarm_proc : [IN] The expiration callback function.		
 * RETURNS
 *  If successful, return VM_ALARM_OK; otherwise, return error code.
 *****************************************************************************/
VMINT vm_alarm_set(vm_alarm_time_struct* expire_time, VM_ALARMPROC_T alarm_proc);


/******************************************************************************
 * FUNCTION
 *  vm_alarm_cancel
 * DESCRIPTION
 *  Cancels alarm. If the alarm has expired, this cancel function will do nothing.
 * PARAMETERS
 *  alarm_id : [IN] The alarm ID.	
 * RETURNS
 *  If successful, return VM_ALARM_OK; otherwise, return error code.
 *****************************************************************************/
VMINT vm_alarm_cancel(VMINT alarm_id);

#ifdef __cplusplus
}
#endif

#endif /* VMALARM_SDK_H_ */
