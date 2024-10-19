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
// ID Code      : UserCommonColorDM.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_COLOR_DM_H__
#define __USER_COMMON_COLOR_DM_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DEBUG_MESSAGE_DM == _ON)
#define _DM_POLLING_BEC_TIMEOUT                     200
#else
#define _DM_POLLING_BEC_TIMEOUT                     20
#endif

#define _DM_DEMO_FUNCTION_TIME_LIMIT                15
#define _DM_DEMO_FUNCTION_TIME_UNIT                 SEC(60)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
extern void UserCommonColorDMGetData(EnumSelRegion enumSelRegion, StructColorDMOsdSetting *pstDMOsdData);
extern bit UserCommonColorDMPollingBECStatus(EnumRegionIndex enumRegionIndex, DWORD ulWaitTimeout, EnumDMBECStatus enumDMBECStatus);
extern void UserCommonColorDMAdjust(EnumDisplayRegion enumDisplayRegion, EnumRegionIndex enumRegionIndex, EnumDMAdjustType enumAdjustType);
extern void UserCommonColorDMAdjustDMProc(EnumDisplayRegion enumDisplayRegion, EnumDMAdjustType enumAdjustType);
#endif
#endif

#endif // End of #ifndef __USER_COMMON_COLOR_DM_H__
