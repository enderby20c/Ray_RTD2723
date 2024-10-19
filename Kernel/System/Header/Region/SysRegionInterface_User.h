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
// ID Code      : SysRegionInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DISPLAY_STATE_NONE,
    _DISPLAY_STATE_NO_SIGNAL,
    _DISPLAY_STATE_OOR,
    _DISPLAY_STATE_DISPLAY_READY,
    _DISPLAY_STATE_ACTIVE,

    _DISPLAY_STATE_MAX = 0x0F,
} EnumDisplayState;

typedef enum
{
    _DISPLAY_EVENT_TIMING_CONFIRMED = _BIT0,
    _DISPLAY_EVENT_TIMING_DOUBLE_CHECK = _BIT1,
    _DISPLAY_EVENT_MEASURE_CHECKING = _BIT3,
    _DISPLAY_EVENT_FIRST_ACTIVE = _BIT4,
    _DISPLAY_EVENT_STATE_CHANGE_USR = _BIT6,
    _DISPLAY_EVENT_STATE_CHANGE_SYS = _BIT7,
    _DISPLAY_EVENT_ALL = 0xFF,
} EnumDisplayEvent;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysRegionUpdateInterface(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort);
extern EnumDisplayState SysRegionGetDisplayState(EnumDisplayRegion enumDisplayRegion);
extern EnumSourceType SysRegionGetSourceType(EnumDisplayRegion enumDisplayRegion);
extern EnumInputPort SysRegionGetInputPort(EnumDisplayRegion enumDisplayRegion);
extern EnumDisplayRegion SysRegionGetDisplayRegion(EnumRegionIndex enumRegionIndex);
extern EnumRegionIndex SysRegionGetDisplayRegionIndex(EnumDisplayRegion enumDisplayRegion);
extern bit SysRegionCheckAllDisplayState(EnumDisplayState enumDisplayState);
extern bit SysRegionCheckUserDisplayStateChange(void);
extern bit SysRegionCheckDisplayEvent(EnumDisplayRegion enumDisplayRegion, EnumDisplayEvent enumDisplayEvent);
extern EnumDisplayRegion SysRegionGetMeasureResultPointerRegion(void);
extern void SysRegionGetMeasureResultByRegion(EnumDisplayRegion enumDisplayRegion, StructTimingInfo *pstTimingInfo);
extern EnumRegionIndex SysRegionConvertSourceIndexToRegionIndex(BYTE ucSearchIndex);
extern BYTE SysRegionGetDisplayStateCount(EnumDisplayState enumDisplayState);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
extern EnumDisplayMode SysRegionEagleSightTransDisplayMode(EnumDisplayMode enumDisplayMode);
#endif

