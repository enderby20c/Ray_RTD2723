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
// ID Code      : UserCommonTmdsInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of User Force HPD toggle when wakeup from Power Saving
//--------------------------------------------------
typedef enum
{
    _USER_FORCE_PS_TMDS_HPD_NOT_TOGGLE = 0x00,
    _USER_FORCE_PS_TMDS_HPD_TOGGLE,
} EnumUserForcePSTmdsHpdToggle;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)
extern BYTE UserCommonTmdsGetAVIInfo(EnumInputPort enumInputPort, EnumAviInfoContent enumContent);
extern void UserCommonTmdsSetHdmiZ0HpdType(EnumHdmiZ0HpdType enumHdmiZ0HpdType, WORD usZ0LowPeriod, WORD usZ0HpdInterval);
extern EnumHdmiZ0Status UserCommonTmdsGetZ0Status(EnumInputPort enumInputPort);
extern void UserCommonTmdsHotPlugDdcConfig(EnumInputPort enumInputPort, bit bEnable);

#if(_HDMI_IDENTIFY_GAME_SRC_SUPPORT == _ON)
extern StructHdmiSpdInfo UserCommonTmdsGetSpdInfo(EnumInputPort enumInputPort);
extern EnumHdmiSpdProuductlInfo UserCommonTmdsGetSpdPdInfo(EnumInputPort enumInputPort);
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
extern EnumVideoDimensionType UserCommonTmdsGet3dVideoValid(EnumInputPort enumInputPort);
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
extern EnumHdmiFrlRate UserCommonTmdsGetFrlRate(EnumInputPort enumInputPort);
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
extern BYTE UserCommonTmdsHdmi21GetFvaFactor(EnumInputPort enumInputPort);
#endif
#endif
