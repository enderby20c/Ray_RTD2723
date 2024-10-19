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
// ID Code      : ScalerUsb3RetimerPhyInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_USB3_RETIMER_PHY_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_USB3_CTS_SET_PHY()                  (g_bUsb3RetimerPhyCtsSetPhy)
#define SET_USB3_CTS_SET_PHY(x)                 (g_bUsb3RetimerPhyCtsSetPhy = (x))

#if(_HW_USB3_REPEATER_UFP_P3_DPHY_PWRCUT_SUPPORT == _ON)
#define GET_USB3_RETIMER_PHY_PINASSIGNMENT_D()  (g_bUsb3RetimerPhyPinAssignmentD)
#define SET_USB3_RETIMER_PHY_PINASSIGNMENT_D()  (g_bUsb3RetimerPhyPinAssignmentD = _TRUE)
#define CLR_USB3_RETIMER_PHY_PINASSIGNMENT_D()  (g_bUsb3RetimerPhyPinAssignmentD = _FALSE)

#define GET_USB3_RETIMER_PHY_UNFLIP()           (g_bUsb3RetimerPhyUnflip)
#define SET_USB3_RETIMER_PHY_UNFLIP()           (g_bUsb3RetimerPhyUnflip = _TRUE)
#define CLR_USB3_RETIMER_PHY_UNFLIP()           (g_bUsb3RetimerPhyUnflip = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of USB Link Rate
//--------------------------------------------------
typedef enum
{
    _USB_LINK_KMODE_5G = 0x00,
    _USB_LINK_KMODE_10G = 0x10,
} EnumUsbLinkRateKMode;

//--------------------------------------------------
// Definitions of USB Link Rate
//--------------------------------------------------
typedef enum
{
    _USB_LINK_PHY_RATE_5G = 0x00,
    _USB_LINK_PHY_RATE_10G = 0x01,
} EnumUsbLinkPhyRate;

//--------------------------------------------------
// Definitions of USB AC Gain
//--------------------------------------------------
typedef enum
{
#if(_HW_USB3_REPEATER_PHY_DFP_MUX_TYPE == _USB3_REPEATER_PHY_DFP_MUX_EMBEDDED)
    _USB_DFP_TX_AC_GAIN_LEVEL0 = 0x00,
    _USB_DFP_TX_AC_GAIN_LEVEL1 = 0x00,
    _USB_DFP_TX_AC_GAIN_LEVEL2 = 0x02,
    _USB_DFP_RX_AC_GAIN_LEVEL0 = 0x00,
    _USB_DFP_RX_AC_GAIN_LEVEL1 = 0x01,
    _USB_DFP_RX_AC_GAIN_LEVEL2 = 0x03,
    _USB_DFP_RX_AC_GAIN_LEVEL3 = 0x05,
    _USB_DFP_RX_AC_GAIN_LEVEL4 = 0x07,
#else
    _USB_DFP_TX_AC_GAIN_LEVEL0 = 0x02,
    _USB_DFP_TX_AC_GAIN_LEVEL1 = 0x04,
    _USB_DFP_TX_AC_GAIN_LEVEL2 = 0x06,
    _USB_DFP_RX_AC_GAIN_LEVEL0 = 0x02,
    _USB_DFP_RX_AC_GAIN_LEVEL1 = 0x04,
    _USB_DFP_RX_AC_GAIN_LEVEL2 = 0x06,
    _USB_DFP_RX_AC_GAIN_LEVEL3 = 0x08,
    _USB_DFP_RX_AC_GAIN_LEVEL4 = 0x0A,
#endif

#if(_HW_USB3_REPEATER_PHY_DFP_MUX_TYPE == _USB3_REPEATER_PHY_DFP_MUX_EMBEDDED)
    _USB_UFP_TX_AC_GAIN_LEVEL0_5G = 0x04,
    _USB_UFP_TX_AC_GAIN_LEVEL1_5G = 0x06,
    _USB_UFP_TX_AC_GAIN_LEVEL2_5G = 0x08,
    _USB_UFP_TX_AC_GAIN_LEVEL0_10G = 0x0A,
    _USB_UFP_TX_AC_GAIN_LEVEL1_10G = 0x0F,
    _USB_UFP_TX_AC_GAIN_LEVEL2_10G = 0x0F,
#else
    _USB_UFP_TX_AC_GAIN_LEVEL0_5G = 0x04,
    _USB_UFP_TX_AC_GAIN_LEVEL1_5G = 0x06,
    _USB_UFP_TX_AC_GAIN_LEVEL2_5G = 0x08,
    _USB_UFP_TX_AC_GAIN_LEVEL0_10G = 0x04,
    _USB_UFP_TX_AC_GAIN_LEVEL1_10G = 0x06,
    _USB_UFP_TX_AC_GAIN_LEVEL2_10G = 0x08,
#endif
} EnumUsbAcGainSet;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HW_USB3_REPEATER_UFP_P3_DPHY_PWRCUT_SUPPORT == _ON)
extern bit g_bUsb3RetimerPhyPinAssignmentD;
extern bit g_bUsb3RetimerPhyUnflip;
#endif
extern bit g_bUsb3RetimerPhyUfp0LeqOffsetHitHighBoundary_L0;
extern bit g_bUsb3RetimerPhyUfp0LeqOffsetHitHighBoundary_L2;
extern bit g_bUsb3RetimerPhyUfp0LeqOffsetHitLowBoundary_L0;
extern bit g_bUsb3RetimerPhyUfp0LeqOffsetHitLowBoundary_L2;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerUsb3RetimerPhyPowerSwitchInitial(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RetimerPhySetKModeFinish(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit ScalerUsb3RetimerPhyGetKModeFinish(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RetimerPhyClearKModeFinish(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RetimerPhyUfpJfmInitialSetting(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RetimerPhyUfpJfmDisable(void);
#endif
