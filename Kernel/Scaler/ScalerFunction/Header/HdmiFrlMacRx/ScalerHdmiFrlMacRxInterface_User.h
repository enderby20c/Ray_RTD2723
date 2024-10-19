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
// ID Code      : ScalerHdmiFrlMacRxInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of HDMI FRL MAC Selection
//--------------------------------------------------
typedef enum
{
    _HDMI_FRL_MAC_SELECT_AUTO = 0,
    _HDMI_FRL_MAC_SELECT_D3,
    _HDMI_FRL_MAC_SELECT_D4,
} EnumHdmiFrlMacSelection;

//--------------------------------------------------
// Enumerations of HDMI FRL Rate
//--------------------------------------------------
typedef enum
{
    _HDMI_FRLRATE_NONE = 0,
    _HDMI_FRLRATE_3G = 1,
    _HDMI_FRLRATE_6G_3LANES = 2,
    _HDMI_FRLRATE_6G_4LANES = 3,
    _HDMI_FRLRATE_8G = 4,
    _HDMI_FRLRATE_10G = 5,
    _HDMI_FRLRATE_12G = 6,
} EnumHdmiFrlRate;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
