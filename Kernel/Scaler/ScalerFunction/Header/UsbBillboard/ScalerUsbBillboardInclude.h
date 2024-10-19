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
// ID Code      : ScalerUsbBillboardInclude.h
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_USB2_SHARED_PHY_SUPPORT == _ON)
#define GET_U2_PHY_SWITCH_PORT()                          (g_enumUsbBillboardMacMuxSwitch)
#define SET_U2_PHY_SWITCH_PORT(x)                         (g_enumUsbBillboardMacMuxSwitch = (x))
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of USB BillBoard U2 Phy Port Mux Switch
//--------------------------------------------------
#if(_HW_USB2_SHARED_PHY_SUPPORT == _ON)
typedef enum
{
    _U2_PHY_PORT_TO_HOST = 0x00,
    _U2_PHY_PORT_TO_BB = 0x01,
}EnumUsbBillboardMacMuxSwitch;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HW_USB2_SHARED_PHY_SUPPORT == _ON)
extern void ScalerUsbBillboardMacMuxSwitch(void);
#endif
#endif
