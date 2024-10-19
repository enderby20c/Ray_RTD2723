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
// ID Code      : ScalerUsb3RetimerDfpPhy0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerUsb3RetimerDfpPhy0Initial(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RetimerDfpPhy0KModeInitialSetting(void);
extern void ScalerUsb3RetimerDfpPhy0KModeEndSetting(void);
extern void ScalerUsb3RetimerDfpPhy0DfpRxKOobs(EnumUsbLinkRateKMode enumUsbLinkRateKMode);
extern void ScalerUsb3RetimerDfpPhy0DfpRxKOffset(EnumUsbLinkRateKMode enumUsbLinkRateKMode);
extern void ScalerUsb3RetimerDfpPhy0Disable(void);
#endif  // End of #if(_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON)

