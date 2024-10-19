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
// ID Code      : ScalerUsb3RetimerMac0.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_USB3_RETIMER_MAC_0_H__
#define __SCALER_USB3_RETIMER_MAC_0_H__

#if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
//****************************************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************************************
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
#define GET_USB3_RETIMER_P3_STATUS()                            (g_enumUsb3RetimerMac0P3State)
#define SET_USB3_RETIMER_P3_STATUS(x)                           (g_enumUsb3RetimerMac0P3State = (x))
#endif

//****************************************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************************************


//****************************************************************************************************
// VARIABLE EXTERN
//****************************************************************************************************


//****************************************************************************************************
// FUNCTION EXTERN
//****************************************************************************************************
extern void ScalerUsb3RetimerMac0UfpOnRegionInitial(EnumTypeCOrientation enumOrientation);
extern void ScalerUsb3RetimerMac0UfpOffRegionInitial(EnumTypeCOrientation enumOrientation);
extern void ScalerUsb3RetimerMac0UfpOffRegionU3ExitInitial(void);
extern void ScalerUsb3RetimerMac0DfpOnRegionInitial(void);
extern void ScalerUsb3RetimerMac0DfpOffRegionInitial(void);
extern void ScalerUsb3RetimerMac0DfpOffRegionU3ExitInitial(void);
extern void ScalerUsb3RetimerMac0OnRegionEnable(bit bEnable);
extern void ScalerUsb3RetimerMac0OffRegionEnable(bit bEnable);
extern void ScalerUsb3RetimerMac0IrqEnable(bit bEnable);
extern void ScalerUsb3RetimerMac0UfpPortConfigSetting_EXINT3(void);
extern void ScalerUsb3RetimerMac0DfpPortConfigSetting_EXINT3(void);
#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
extern void ScalerUsb3RetimerMac0UfpAsyFifoResetProc(void);
extern void ScalerUsb3RetimerMac0DfpAsyFifoResetProc(void);
extern void ScalerUsb3RetimerMac0UfpAsyFifox2Proc_EXINT3(void);
extern void ScalerUsb3RetimerMac0UfpAsyFifox1Proc_EXINT3(void);
extern void ScalerUsb3RetimerMac0DfpAsyFifox2Proc_EXINT3(void);
extern void ScalerUsb3RetimerMac0DfpAsyFifox1Proc_EXINT3(void);
#endif // End of #if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
extern void ScalerUsb3RetimerMac0UfpExitCPbyPollingSolution_EXINT3(void);
extern void ScalerUsb3RetimerMac0DfpExitCPbyPollingSolution_EXINT3(void);
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
extern void ScalerUsb3RetimerMac0PowerCutOffInitialSetting(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RetimerMac0PowerCutOffLFPSInitialSetting(EnumTypeCPcbPort enumTypeCPcbPort);
#endif // End of #if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
#endif // End of #if(_USB3_RETIMER_MAC0_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_USB3_RETIMER_MAC_0_H__
