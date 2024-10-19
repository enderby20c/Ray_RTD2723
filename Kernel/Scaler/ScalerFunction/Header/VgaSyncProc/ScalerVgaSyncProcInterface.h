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
// ID Code      : ScalerVgaSyncProcInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of ADC Clock Limit
//--------------------------------------------------
#define GET_ADC_LIMIT_CLOCK()                          (g_usVgaSyncProcClockLimit)

//--------------------------------------------------
// Definitions of Input Sync Type State
//--------------------------------------------------
#define _NO_SYNC_STATE                                 0
#define _SS_STATE                                      1
#define _CS_STATE                                      2
#define _SOG_STATE                                     3
#define _SOY_STATE                                     4
#define _DSS_STATE                                     5
#define _NOT_SUPPORT_STATE                             0

//--------------------------------------------------
// Definitions of mode search status
//--------------------------------------------------
#define _VGA_MODE_NOSUPPORT                            254

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern WORD g_usVgaSyncProcClockLimit;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerVgaSyncProcScanInitial(EnumInputPort enumInputPort);
extern bit ScalerVgaSyncProcPreDetect(EnumInputPort enumInputPort);
extern bit ScalerVgaSyncProcStableDetect(EnumInputPort enumInputPort, EnumSourceType enumSourceType);
extern bit ScalerVgaSyncProcGetSyncPad(void);
extern BYTE ScalerVgaSyncProcTypeAutoRun(void);
extern bit ScalerVgaSyncProcAdcClkInitial(void);
extern bit ScalerVgaSyncProcAdcClkSetting(void);
extern void ScalerVgaSyncProcClampPosCheck(BYTE ucVideoModeFlg);
extern void ScalerVgaSyncProcClearSyncChangeStatus(void);
extern DWORD ScalerVgaSyncProcGetCurrentClockFreq(void);

#endif // #if(_VGA_SUPPORT == _ON)

