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
// ID Code      : ScalerUsb3RetimerUfpPhy1.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_USB3_RETIMER_UFP_PHY_1_H__
#define __SCALER_USB3_RETIMER_UFP_PHY_1_H__

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
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
extern void ScalerUsb3RetimerUfpPhy1Gen1Setting(void);
extern void ScalerUsb3RetimerUfpPhy1Gen2Setting(void);
extern void ScalerUsb3RetimerUfpPhy1DFESetting(void);
extern void ScalerUsb3RetimerUfpPhy1OutputSwingSetting(void);
extern void ScalerUsb3RetimerUfpPhy1TxSscSetting(void);
extern void ScalerUsb3RetimerUfpPhy1UfpRxKLeqOffset(EnumUsbLinkRateKMode enumUsbLinkRateKMode);
extern void ScalerUsb3RetimerUfpPhy1UfpUnflipConfigInitial(void);
extern void ScalerUsb3RetimerUfpPhy1UfpUnflipInitial(void);
extern void ScalerUsb3RetimerUfpPhy1UfpFlipConfigInitial(void);
extern void ScalerUsb3RetimerUfpPhy1UfpFlipInitial(void);
extern void ScalerUsb3RetimerUfpPhy1PhyDisable(bit bAttach, EnumTypeCOrientation enumTypeCOrientation, EnumTypeCPinCfgType enumTypeCPinCfgType);
extern void ScalerUsb3RetimerUfpPhy1IrqDisable(void);
#endif // End of #if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_USB3_RETIMER_UFP_PHY_1_H__
