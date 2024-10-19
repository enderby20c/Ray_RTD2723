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
// ID Code      : ScalerUsb3RepeaterPhyInclude.h No.0000
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
extern bit ScalerUsb3RepeaterPhyGetKModeFinish(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RepeaterPhyJfmInitialSetting(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumRx ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumRx ScalerUsb3RepeaterPhyDx2DfpPhyxMapping(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumRx ScalerUsb3RepeaterPhyDx2UfpPhyxMapping_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumRx ScalerUsb3RepeaterPhyMacx2DfpPhyxMapping(EnumRx enumMacxIndex);
extern EnumRx ScalerUsb3RepeaterPhyMacx2DfpPhyxMapping_EXINT3(EnumRx enumMacxIndex);
extern EnumRx ScalerUsb3RepeaterPhyMacx2UfpPhyxMapping_EXINT3(EnumRx enumMacxIndex);
extern EnumTypeCPcbPort ScalerUsb3RepeaterPhyUfpPhyx2DxMapping_EXINT3(EnumRx enumUfpPhyxIndex);
extern void ScalerUsb3RepeaterPhyFwAdaptionControl_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RepeaterPhyEnterComplianceMode_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RepeaterPhyExitComplianceMode_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumRx ScalerUsb3RepeaterPhyDx2DfpPhyxMapping_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort);

#endif
