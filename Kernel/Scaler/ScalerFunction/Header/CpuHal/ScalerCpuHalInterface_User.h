/********************************************************************************/
/*   Copyright (c) 2021 Realtek Semiconductor Corp. All rights reserved.        */
/*                                                                              */
/*   SPDX-License-Identifier: LicenseRef-Realtek-Proprietary                    */
/*                                                                              */
/*   This software component is confidential and proprietary to Realtek         */
/*   Semiconductor Corp. Disclosure, reproduction, redistribution, in whole     */
/*   or in part, of this work and its derivatives without express permission    */
/*   is prohibited.                                                             */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCpuHalInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_RESOURCE_LOCK_ID(enumResourceID)    ((EnumCpu32ResourceLockID)(LOBYTE(enumResourceID)))
#define GET_RESOURCE_SEMAPHORE(enumResourceID)  ((EnumCpuBusSB2SemaphoreIdx)(HIBYTE(enumResourceID)))
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
// Share Resource ID List (Protected By Sync Flag Macro)
typedef enum
{
    _RESOURCE_LOCK_ID_BW8 = 0,
#if(_HW_CPU32_BW32_SUPPORT == _ON)
    _RESOURCE_LOCK_ID_BW32,
#endif
#if(_HW_CPU32_RBUS2DDR_SUPPORT == _ON)
    _RESOURCE_LOCK_ID_RBUS2DDR,
#endif
#if(_ADVANCED_HDR10_SUPPORT == _ON)
    _RESOURCE_LOCK_ID_COLOR_ADVANCED_HDR10_METADATA,
#endif
#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
    _RESOURCE_LOCK_ID_TO_SCPU_NOTIFY,
    _RESOURCE_LOCK_ID_TO_KCPU_NOTIFY,
#endif
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    _RESOURCE_LOCK_ID_DBG_MSG,
#endif
    _RESOURCE_LOCK_ID_MAX,
} EnumCpu32ResourceLockID;

typedef enum
{
    _RESOURCE_ID_BW8 = ((_SEMAPHORE_0 << 8) + _RESOURCE_LOCK_ID_BW8),
#if(_HW_CPU32_BW32_SUPPORT == _ON)
    _RESOURCE_ID_BW32 = ((_SEMAPHORE_1 << 8) + _RESOURCE_LOCK_ID_BW32),
#endif
#if(_HW_CPU32_RBUS2DDR_SUPPORT == _ON)
    _RESOURCE_ID_RBUS2DDR = ((_SEMAPHORE_2 << 8) + _RESOURCE_LOCK_ID_RBUS2DDR),
#endif
#if(_ADVANCED_HDR10_SUPPORT == _ON)
    _RESOURCE_ID_COLOR_ADVANCED_HDR10_METADATA = ((_SEMAPHORE_3 << 8) + _RESOURCE_LOCK_ID_COLOR_ADVANCED_HDR10_METADATA),
#endif
#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
    _RESOURCE_ID_TO_SCPU_NOTIFY = ((_SEMAPHORE_7 << 8) + _RESOURCE_LOCK_ID_TO_SCPU_NOTIFY),
    _RESOURCE_ID_TO_KCPU_NOTIFY = ((_SEMAPHORE_7 << 8) + _RESOURCE_LOCK_ID_TO_KCPU_NOTIFY),
#endif
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    _RESOURCE_ID_DBG_MSG = ((_SEMAPHORE_8 << 8) + _RESOURCE_LOCK_ID_DBG_MSG),
#endif
} EnumCpu32ResourceID;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************



