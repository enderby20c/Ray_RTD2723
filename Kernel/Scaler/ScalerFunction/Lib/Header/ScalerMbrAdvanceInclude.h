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
// ID Code      : ScalerMbrAdvanceInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    WORD usVTotal;
    WORD usHTotal;
    WORD usDclk;
    WORD usVFreq;
} StructRtkAdvMbrTimingInfo;

typedef struct
{
    BYTE ucFrameSyncMargin;
    WORD usMaxFreq;
    WORD usMinFreq;
    DWORD ulPixelClock;
    DWORD ulPixelClockMax;
    DWORD ulPixelClockMin;
} StructRtkAdvMbrPanelInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerMbrAdvanceGetRtkAdvMbrStatus(void);
extern bit ScalerMbrAdvanceCheckRtkAdvMbrSequenceCtrl(void);
extern bit ScalerMbrAdvanceRtkAdvMbrSequenceCtrlEnable(bit bEnable);
extern void ScalerMbrAdvanceClearUnusedSetting(BYTE ucTcon);
extern void ScalerMbrAdvanceClearRtkAdvMbrMode(void);
extern void ScalerMbrAdvanceSetRtkAdvMbrUserStatus(EnumRtkAdvMbrUserStatus enumRtkAdvMbrUserStatus);
extern void ScalerMbrAdvanceUpdateRtkAdvMbrStatus(WORD usInputVFreq);
extern void ScalerMbrAdvanceUpdateRtkAdvMbrMemConfig(BYTE *pucMemConfig);
extern void ScalerMbrAdvanceUpdateRtkAdvMbrMDomainInfo(void);
extern void ScalerMbrAdvanceUpdateRtkAdvMbrDisplayInfo(DWORD *pulDclk);
extern void ScalerMbrAdvanceRtkAdvMbrAdjust(StructRtkAdvMbrTimingInfo *pstTimingInfo, BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bEnable);

