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
// ID Code      : UserCommonColorDMInterface_User.h No.0000
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
    _DM_OSD_ENTRY,
    _DM_OSD_EXIT,
} EnumDMOsdEvent;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
extern EnumDMSupport UserCommonColorDMGetEnableStatus(EnumDisplayRegion enumDisplayRegion);
extern bit UserCommonColorDMGetMuteStatus(EnumDisplayRegion enumDisplayRegion);
extern bit UserCommonColorDMGetDMStatus(EnumDisplayRegion enumDisplayRegion);
extern bit UserCommonColorDMGetDMGameMode(EnumDisplayRegion enumDisplayRegion);
extern bit UserCommonColorDMOSDAdjust(EnumSelRegion enumSelRegion, EnumDMAdjustType enumAdjustType);
extern bit UserCommonColorDMStatusChange(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonColorDMOSDSupportSwitch(EnumInputPort enumInputPort);
extern void UserCommonColorDMIRQSupportSwitch(EnumDisplayRegion enumDisplayRegion, bit bEn);
extern EnumDisplayRegion UserCommonColorDMGetDisplayRegion(EnumSelRegion enumSelRegion);
#if(_DM_CONFIG_GAME_MODE_INDEX != _DM_PICTURE_MODE_NONE)
extern void UserCommonColorDMSetBackupMode(EnumDisplayRegion enumDisplayRegion, BYTE ucPictureModeIndex);
#endif
#endif
#endif
