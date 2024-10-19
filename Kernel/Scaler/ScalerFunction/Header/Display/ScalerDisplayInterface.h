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
// ID Code      : ScalerDisplayInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
#define SET_FREE_RUN_DDOMAIN_SETTING(x)                             (g_stDisplayCustomizedData.enumFreeRunDdomainSetting = (x))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDisplayCustomizedData g_stDisplayCustomizedData;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumDVFSelect ScalerDisplaySelectDVFMode(void);

#if(_PANEL_EXIST_MULTIPANEL == _ON)
extern void ScalerDisplayInterfacePowerSwitch(void);
#endif

extern void ScalerDisplaySetDspc(void);

#if(_PANEL_STYLE == _PANEL_LVDS)
extern void ScalerDisplayLvdsPLL(bit bOn);
extern void ScalerDisplayLvdsPower(bit bOn);
#endif

extern void ScalerDisplayPadPower(bit bOn);
