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
// ID Code      : ScalerUsb3RetimerDfpPhy0.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_USB3_RETIMER_DFP_PHY_0_H__
#define __SCALER_USB3_RETIMER_DFP_PHY_0_H__

#if(_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON)
//****************************************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************************************

//****************************************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************************************


//****************************************************************************************************
// VARIABLE EXTERN
//****************************************************************************************************


//****************************************************************************************************
// FUNCTION EXTERN
//****************************************************************************************************
#if(_HW_USB3_REPEATER_DFP_PHY_LANE_NUM_SUPPORT == _DFP_FOUR_LANE)
extern void ScalerUsb3RetimerDfpPhy0By2KModeInitialSetting(void);
extern void ScalerUsb3RetimerDfpPhy0By2DfpRxKOobs(EnumUsbLinkRateKMode enumUsbLinkRateKMode);
extern void ScalerUsb3RetimerDfpPhy0By2DfpRxKOffset(EnumUsbLinkRateKMode enumUsbLinkRateKMode);
extern void ScalerUsb3RetimerDfpPhy0By2Initial(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_HW_USB3_REPEATER_DFP_PHY_LANE_NUM_SUPPORT == _DFP_TWO_LANE)
extern void ScalerUsb3RetimerDfpPhy0By1KModeInitialSetting(void);
extern void ScalerUsb3RetimerDfpPhy0By1DfpRxKOobs(EnumUsbLinkRateKMode enumUsbLinkRateKMode);
extern void ScalerUsb3RetimerDfpPhy0By1DfpRxKOffset(EnumUsbLinkRateKMode enumUsbLinkRateKMode);
extern void ScalerUsb3RetimerDfpPhy0By1Initial(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
extern void ScalerUsb3RetimerDfpPhy0PhyDisable(void);
extern void ScalerUsb3RetimerDfpPhy0IrqDisable(void);
#endif // End of #if(_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_USB3_RETIMER_DFP_PHY_0_H__
