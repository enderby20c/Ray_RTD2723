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
// ID Code      : UserCommonColorHDR.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_COLOR_HDR_H__
#define __USER_COMMON_COLOR_HDR_H__

#if(_ULTRA_HDR_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_ADVANCED_HDR10_SUPPORT == _ON)
#if(_DEBUG_MESSAGE_HDR == _ON)
#define CLR_ADVANCED_HDR10_SETTING_DATA()                   (memset(&g_stColorAdvancedHDR10Setting, 0, sizeof(StructAdvancedHDR10MetaData)))
#endif
#endif

#if((_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON) || (_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON))
#define SET_HDR10_PANEL_MAX_LV(region, x)                   (g_pusColorHDRPanelMaxLv[ScalerRegionGetIndex(region)] = (x))
#define GET_HDR10_PANEL_MAX_LV(region)                      (g_pusColorHDRPanelMaxLv[ScalerRegionGetIndex(region)])
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _HDR10_MAX_MASTERING_LV_NONE_TYPE,
    _HDR10_MAX_MASTERING_LV_RECIEVED_TYPE,
} EnumHDR10MasteringLvRecievedType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonColorHDRAdjustHDRMode(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonColorHDRAdjustHDRProc(EnumDisplayRegion enumDisplayRegion);

#if(_HDR10_SUPPORT == _ON)
extern EnumHDR10ChangeStatus UserCommonColorHDRGetHDR10ChangeStatus(EnumDisplayRegion enumDisplayRegion);
extern EnumHDR10MaxMasteringLvType UserCommonColorHDRGetHDR10ModifyLvType(WORD usMaxPanelLv, StructHDR10UserData stHDR10UserData, EnumHDR10MasteringLvRecievedType enumHDR10MasteringLvRecievedType);
extern EnumHDR10MaxMasteringLvType UserCommonColorHDRGetHDR10NOTMLvType(EnumHDR10UserDefineMaxPanelLvType enumHDR10UserDefineMaxPanelLvType);
extern WORD UserCommonColorHDRGetHDR10NOTMBoundAddr(EnumHDR10UserDefineMaxPanelLvType enumHDR10UserDefineMaxPanelLvType);
extern WORD UserCommonColorHDRGetPanelMaxLv(EnumHDR10UserDefineMaxPanelLvType enumHDR10UserDefineMaxPanelLvType);
#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
extern BYTE UserCommonColorHDRFreeSyncIIChangeStatus(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
#if(_DEBUG_MESSAGE_HDR == _ON)
extern EnumAdvancedHDR10ChangeStatus UserCommonColorHDRGetAdvancedHDR10ChangeStatus(void);
#endif
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
extern EnumHDR10SBTMChangeStatus UserCommonColorHDRGetSBTMChangeStatus(EnumDisplayRegion enumDisplayRegion);
#endif
#endif // End of #if(_ULTRA_HDR_SUPPORT == _ON)

#endif // End of #ifndef __USER_COMMON_COLOR_HDR_H__
