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
// ID Code      : SysSourceInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Source Search Delay Mode
//--------------------------------------------------
#define SET_SOURCE_MEASURE_TARGET_INDEX(x)      (g_ucSourceMeasureTargetIndex = (x))
#define GET_SOURCE_MEASURE_TARGET_INDEX()       (g_ucSourceMeasureTargetIndex % _MULTI_DISPLAY_MAX)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucSourceMeasureTargetIndex;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysSourceSetScanType(BYTE ucScanType);
extern void SysSourceInfoReset(void);

#if(_FREESYNC_SUPPORT == _ON)
extern EnumInputPort SysSourceGetFreesyncInputPort(void);
#endif

extern bit SysSourceCheckAnySourceJudged(void);
