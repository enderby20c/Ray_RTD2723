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
// ID Code      : ScalerUsb3RetimerUfpPhy0.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_USB3_RETIMER_UFP_PHY_0_H__
#define __SCALER_USB3_RETIMER_UFP_PHY_0_H__

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
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
extern void ScalerUsb3RetimerUfpPhy0Gen1Setting(void);
extern void ScalerUsb3RetimerUfpPhy0Gen2Setting(void);
extern void ScalerUsb3RetimerUfpPhy0DFESetting(void);
extern void ScalerUsb3RetimerUfpPhy0OutputSwingSetting(void);
extern void ScalerUsb3RetimerUfpPhy0TxSscSetting(void);

extern void ScalerUsb3RetimerUfpPhy0UfpRxKLeqOffset(EnumUsbLinkRateKMode enumUsbLinkRateKMode);
extern void ScalerUsb3RetimerUfpPhy0UfpUnflipConfigInitial(void);
extern void ScalerUsb3RetimerUfpPhy0UfpUnflipInitial(void);
extern void ScalerUsb3RetimerUfpPhy0UfpFlipConfigInitial(void);
extern void ScalerUsb3RetimerUfpPhy0UfpFlipInitial(void);
extern void ScalerUsb3RetimerUfpPhy0PhyDisable(bit bAttach, EnumTypeCOrientation enumTypeCOrientation, EnumTypeCPinCfgType enumTypeCPinCfgType);
extern void ScalerUsb3RetimerUfpPhy0IrqDisable(void);
#endif // End of #if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_USB3_RETIMER_UFP_PHY_0_H__
