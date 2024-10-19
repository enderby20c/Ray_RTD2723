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
// ID Code      : ScalerUsb3RetimerUfpPhy1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_USB3_RETIMER_UFP_PHY1_KMODE_FINISH()                        (g_bUsb3RetimerUfpPhy1KmodeFinish)
#define SET_USB3_RETIMER_UFP_PHY1_KMODE_FINISH()                        (g_bUsb3RetimerUfpPhy1KmodeFinish = _TRUE)
#define CLR_USB3_RETIMER_UFP_PHY1_KMODE_FINISH()                        (g_bUsb3RetimerUfpPhy1KmodeFinish = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bUsb3RetimerUfpPhy1KmodeFinish;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerUsb3RetimerUfpPhy1Initial(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumOrientation);
extern void ScalerUsb3RetimerUfpPhy1Disable(bit bAttach, EnumTypeCOrientation enumTypeCOrientation, EnumTypeCPinCfgType enumTypeCPinCfgType);
extern void ScalerUsb3RetimerUfpPhy1KModeInitialSetting(void);
extern void ScalerUsb3RetimerUfpPhy1KModeEndSetting(void);
extern void ScalerUsb3RetimerUfpPhy1UfpRxKOobs(void);
extern void ScalerUsb3RetimerUfpPhy1UfpRxKOffset(EnumUsbLinkRateKMode enumUsbLinkRateKMode);
extern void ScalerUsb3RetimerUfpPhy1UfpPhyRateChangeSetting_EXINT3(EnumUsbLinkPhyRate enumUsbLinkPhyRate);


#endif  // End of #if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
