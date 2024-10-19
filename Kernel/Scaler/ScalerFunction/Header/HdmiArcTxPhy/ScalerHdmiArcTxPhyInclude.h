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
// ID Code      : ScalerHdmiArcTxPhyInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
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
extern void ScalerHdmiArcTxPhyInitial(void);
extern void ScalerHdmiArcTxPhyPowerOff(void);
extern void ScalerHdmiArcTxPhySetArcMode(bit bEnable);
extern void ScalerHdmiArcTxPhyPllPowerOff(void);
extern void ScalerHdmiArcTxPhySetPll(void);

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
extern void ScalerHdmiArcTxPhyEarcInitial(void);
extern void ScalerHdmiArcTxPhyEarcSetDuty(void);
extern void ScalerHdmiArcTxPhyEarcDiffDrivingPower(bit bOnOff);
extern void ScalerHdmiArcTxPhyEarcCmDrivingPower(bit bOnOff);
extern void ScalerHdmiArcTxPhyEarcCmDrivingPower_EXINT0(bit bOnOff);
extern void ScalerHdmiArcTxPhyEarcDiffDrivingPower_EXINT0(bit bOnOff);
#endif // End for #if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
#endif // End for #if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)