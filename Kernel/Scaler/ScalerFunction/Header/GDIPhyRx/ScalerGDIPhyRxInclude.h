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
// ID Code      : ScalerGDIPhyRxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of GDI Clk Freq. (in kHz)
//--------------------------------------------------
//#define _GDIPHY_RX_GDI_CLK_KHZ                      (DWORD)(_M2PLL_CLK_KHZ / _SYS_CLK_DIV)    // in kHz
#define _GDIPHY_RX_GDI_CLK_KHZ                      (DWORD)((bit)ScalerGetBit(P80_06_GDI_CLK_DIVIDER, _BIT4) ? (((DWORD)1000 * _M2PLL_CLK_MHZ) / _GDI_CLK_DIV) : (_SYS_USE_ISO_CLK ? _HW_INTERNAL_OSC_XTAL : _EXT_XTAL))

//--------------------------------------------------
// DP Scaler Side Lane List
//--------------------------------------------------
#define _GDI_PHY_LANE0                              0
#define _GDI_PHY_LANE1                              1
#define _GDI_PHY_LANE2                              2
#define _GDI_PHY_LANE3                              3

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _LANE_DP_MODE = 0x00,
    _LANE_USB3_MODE,
} EnumLaneConfig;

typedef enum
{
    _COMBO_PHY_PORT_NONE = 0x00,
    _COMBO_PHY_PORT_0,
    _COMBO_PHY_PORT_1,
    _COMBO_PHY_PORT_2,
} EnumComboPhySwich;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumInputPort ScalerGDIPhyRxRxDxMapping(EnumRx enumRx);
extern void ScalerGDIPhyRxBandgap(bit bSelect);
extern void ScalerGDIPhyRxPowerProc(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction);
extern void ScalerGDIPhyRxLanePower(EnumInputPort enumInputPort, bit bEnable, BYTE ucLane);
extern void ScalerGDIPhyRxDisableOtherPort(EnumInputPort enumInputPort);
extern void ScalerGDIPhyRxSetComboPhySwitch(EnumInputPort enumInputPort);
extern EnumComboPhySwich ScalerGDIPhyRxGetComboPhySwitch(void);

extern EnumRx ScalerGDIPhyRxDxRxMapping_EXINT0(EnumInputPort enumInputPort);
extern EnumComboPhySwich ScalerGDIPhyRxGetComboPhySwitch_EXINT0(void);
extern void ScalerGDIPhyRxLaneMode_EXINT0(EnumInputPort enumInputPort, EnumLaneConfig enumLaneMode, BYTE ucLane);
extern void ScalerGDIPhyRxLanePower_EXINT0(EnumInputPort enumInputPort, bit bEnable, BYTE ucLane);

extern EnumComboPhySwich ScalerGDIPhyRxGetComboPhySwitch_WDINT(void);

