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
// ID Code      : ScalerUsb3RepeaterPhyInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_USB3_REPEATER_PHY_SUPPORT == _ON)
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
#if(_RDC_TEST_TYPE == _USB3_REDRIVER_RDC_TEST_TYPE)
extern bit ScalerUsb3RepeaterPhyCtsModeCheck(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RepeaterPhyCtsFlow(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
extern void ScalerUsb3RepeaterPhyPowerSwitchInitial(EnumPowerAction enumSwitch, EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RepeaterPhyInitial(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumOrientation, EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RepeaterPhyDisable(EnumTypeCPcbPort enumTypeCPcbPort, bit bAttach, EnumTypeCOrientation enumTypeCOrientation, EnumTypeCPinCfgType enumTypeCPinCfgType);
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
extern void ScalerUsb3RepeaterPhyMuxSwitchControl(EnumInputPort enumInputPort, EnumUSBHubPathEnable enumUSBHubPathEnable);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#endif
