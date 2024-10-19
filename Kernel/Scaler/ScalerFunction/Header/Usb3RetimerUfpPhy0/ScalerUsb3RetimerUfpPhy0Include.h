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
// ID Code      : ScalerUsb3RetimerUfpPhy0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_USB3_RETIMER_UFP_PHY0_KMODE_FINISH()                        (g_bUsb3RetimerUfpPhy0KmodeFinish)
#define SET_USB3_RETIMER_UFP_PHY0_KMODE_FINISH()                        (g_bUsb3RetimerUfpPhy0KmodeFinish = _TRUE)
#define CLR_USB3_RETIMER_UFP_PHY0_KMODE_FINISH()                        (g_bUsb3RetimerUfpPhy0KmodeFinish = _FALSE)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bUsb3RetimerUfpPhy0KmodeFinish;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerUsb3RetimerUfpPhy0Initial(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumOrientation);
extern void ScalerUsb3RetimerUfpPhy0Disable(bit bAttach, EnumTypeCOrientation enumTypeCOrientation, EnumTypeCPinCfgType enumTypeCPinCfgType);
extern void ScalerUsb3RetimerUfpPhy0KModeInitialSetting(void);
extern void ScalerUsb3RetimerUfpPhy0KModeEndSetting(void);
extern void ScalerUsb3RetimerUfpPhy0UfpRxKOobs(void);
extern void ScalerUsb3RetimerUfpPhy0UfpRxKOffset(EnumUsbLinkRateKMode enumUsbLinkRateKMode);
#if(_HW_USB3_REPEATER_UFP_P3_DPHY_PWRCUT_SUPPORT == _ON)
extern void ScalerUsb3RetimerUfpPhy0DFEInitial_EXINT3(void);
extern void ScalerUsb3RetimerUfpPhy0SaveDFEAdaptationResult_EXINT3(void);
extern void ScalerUsb3RetimerUfpPhy0ReloadDFEAdaptationResult_EXINT3(void);
#endif
extern void ScalerUsb3RetimerUfpPhy0UfpPhyRateChangeSetting_EXINT3(EnumUsbLinkPhyRate enumUsbLinkPhyRate);

#endif  // End of #if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
