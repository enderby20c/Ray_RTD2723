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
// ID Code      : ScalerMDomain.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_MDOMAIN_H__
#define __SCALER_MDOMAIN_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _FRAME_BUFFER_METHOD                    0
#define _LINE_BUFFER_METHOD                     1

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
#define SET_IDEN_DDEN_RELATION(x, y)            (g_pstMDomainBackupInfo[x].enumMDomainIdenDdenRelation = (y))
#define GET_IDEN_DDEN_RELATION(x)               (g_pstMDomainBackupInfo[x].enumMDomainIdenDdenRelation)
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#define GET_MDOMAIN_ES_SUB_VSTART(x)            (g_pstMDomainBackupInfo[x].usbksubvstart)
#define SET_MDOMAIN_ES_SUB_VSTART(x, y)         (g_pstMDomainBackupInfo[x].usbksubvstart = (y))
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _FRAME_SYNC_MAIN,
    _FRAME_SYNC_SUB,
} EnumFrameSyncSource;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMDomainIDDomainDBApply(EnumInputDataPath enumSelectedDataPath, EnumDBApply enumDBApply);
extern bit ScalerMDomainCheckDVtotalFinetune(EnumMemoryConfig enumMemoryConfig);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
extern EnumMDomainIdenDdenRelation ScalerMDomainCheckFrameSyncIdenDdenRelation(void);
#endif

#if((_FRC_SUPPORT == _ON) && (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I))
extern void ScalerMDomainIDDomainDBApplyFRCModeSetDB(EnumInputDataPath enumSelectedDataPath);
#endif

#if((_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON) || (_DRR_SUPPORT == _ON))
#if(_FRC_SUPPORT == _ON)
extern bit ScalerMDomainFSLineBufferDclkDvtotalCheck(void);
#endif
#endif

extern void ScalerMDomainSetDDomain(const StructSDRAMDataInfo *pstFIFOScaling);
extern void ScalerMDomainCalculateDclkDVtotal(EnumMemoryConfig enumMemoryConfig);

extern EnumMemoryWorkMode ScalerMDomainMemoryConfig(void);
extern StructDHVtotal ScalerMDomainDHVtotalFinetune(DWORD ulDclk, BYTE ucMemorySel, bit bDclkCalculateMethod);
extern void ScalerMDomainFSVgipDoubleBufferApply(void);
extern void ScalerMDomainSetDisplayTimingGenHVSyncWidth(WORD usDHSync, WORD usDVSync);
extern void ScalerMDomainSetBackground_R1(void);
extern void ScalerMDomainSetDisplayVerticalActiveEnd(EnumDDomainRegion enumDDomainRegion, WORD usVactiveEnd);

#if(_OD_FUNCTION == _ON)
extern void ScalerMDomainODConfig(void);
#endif // End of #if(_OD_SUPPORT == _ON)

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
extern void ScalerMDomainSetFrameSyncSource(EnumFrameSyncSource enumFrameSyncSource);
#endif

#if(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
#if(_HW_OSD_BLENDING_BG_COLOR_INSERT_GEN == _OSD_BLENDING_BG_COLOR_INSERT_GEN_0)
extern bit ScalerMDomainCheckPreviousBlackFrame(void);
extern void ScalerMDomainBlackFrameInsertSync(BYTE ucMNIdx, bit bPreviosBlackFrame);
#endif
#endif

#endif // End of #ifndef __SCALER_MDOMAIN_H__
