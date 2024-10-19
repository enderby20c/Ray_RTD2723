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
// ID Code      : SysRegionInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_RGN_DISPLAY_MODE(x)                 ((x) & _DISPLAY_MODE_NONE)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysRegionResetInfo(void);

#if(_MULTI_DISPLAY_MAX >= 0x02)
extern BYTE SysRegionGetSourceIndex(BYTE ucRgnNum);
#endif
extern bit SysRegionCheckDisplayActiveState(void);
extern void SysRegionClearAllDisplayEvent(BYTE ucDisplayEventSet);

extern void SysRegionSetMeasureResultPointerRegion(EnumDisplayRegion enumDisplayRegion);
extern EnumDisplayRegion SysRegionConvertPortToRegion(EnumInputPort enumInputPort);
extern EnumRegionIndex SysRegionConvertPortToRegionIndex(EnumInputPort enumInputPort);
