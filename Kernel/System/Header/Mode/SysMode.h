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
// ID Code      : SysMode.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SYS_MODE_H__
#define __SYS_MODE_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysModeFirstDisplayCheckProc(void);
extern void SysModeDisplayStateProc(void);
extern void SysModeDisplayInitialSetting(void);

extern bit SysModeDisplaySetting(void);
extern bit SysModeBypassDisplaySettingStatus(void);
extern BYTE SysModeGetDisplaySettingCount(void);
extern void SysModeSetUpDisplayGlobalInitialization(void);
extern void SysModeSetUpDisplayGlobalFinialSetting(void);
extern void SysModeSetUpDisplayInitialization(BYTE ucIndex);
extern void SysModeSetUpInputCapture(void);
extern void SysModeSetUpDisplayCapture(void);
extern bit SysModeSetUpMDomain(void);

extern WORD SysModeGetDisplayVSHeight(EnumDisplayMode enumDisplayMode);
extern void SysModeDisplayTimingInitial(EnumDisplayMode enumDisplayMode, EnumDisplayRegion enumDisplayRegion);
extern void SysModeSetMtPMemorySelect(void);
extern bit SysModeCheckToDisableGlobalDoubleBuffer(void);

#if(_DRR_SUPPORT == _ON)
extern void SysModeDrrSetMdomainInfo(void);
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
extern void SysModeHDMI21SetMdomainInfo(void);
extern void SysModeHdmi21GetFvaTimingInfo(WORD usVfreqMax, StructEdidInfo *pstCatchTimingInfo, EnumInputPort enumInputPort, StructTimingInfo *pstTimingInfo);
#endif
extern BYTE SysModeSelectMemoryDataBit(EnumMemoryDataBitSelect enumMemoryDataBitSelect);


#endif // End of #ifndef __SYS_MODE_H__
