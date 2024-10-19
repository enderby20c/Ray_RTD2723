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
// ID Code      : ScalerUsb3RepeaterMacInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_USB3_REPEATER_MAC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
//  Retimer DFP Port Orientation
//--------------------------------------------------

#define GET_USB_HUB_U3_SPEED_SUPPORT()                  (g_ucUsb3RepeaterMacU3SupportSpeed)
#define SET_USB_HUB_U3_SPEED_SUPPORT(x)                 (g_ucUsb3RepeaterMacU3SupportSpeed = (x))
#define CLR_USB_HUB_U3_SPEED_SUPPORT(x)                 (g_ucUsb3RepeaterMacU3SupportSpeed = _USB_3_GEN1)

#define GET_USB_HUB_U3_LANE_SUPPORT()                   (g_ucUsb3RepeaterMacU3SupportLane)
#define SET_USB_HUB_U3_LANE_SUPPORT(x)                  (g_ucUsb3RepeaterMacU3SupportLane = (x))
#define CLR_USB_HUB_U3_LANE_SUPPORT(x)                  (g_ucUsb3RepeaterMacU3SupportLane = _USB_3_LANE_X1)

#define GET_TYPE_C_ORIENTATION_EXINT3(x)                (g_pstTypeCInfo[ScalerUsb3RepeaterMacGetTypeCIndex_EXINT3(x)].enumOrientation)
#define GET_TYPE_C_PIN_ASSIGNMENT_EXINT3(x)             (g_pstTypeCInfo[ScalerUsb3RepeaterMacGetTypeCIndex_EXINT3(x)].enumPinAssignment)

#define GET_USB_HUB_SWITCH_PORT_RESULT()                (g_enumUsb3RepeaterMacHubOSDResult)
#define SET_USB_HUB_SWITCH_PORT_RESULT(x)               (g_enumUsb3RepeaterMacHubOSDResult = (x))

#define GET_USB_REPEATER_POWER_CUT_MODE()               (g_ucUsb3RepeaterMacPowerCutMode)
#define SET_USB_REPEATER_POWER_CUT_MODE(x)              (g_ucUsb3RepeaterMacPowerCutMode = (x))

#define GET_USB_REPEATER_PIND_FAKE_SAVING_U3_LATE()     (g_bUsb3RepeaterMacU3PinDEnterFakeSavingU3Late)
#define SET_USB_REPEATER_PIND_FAKE_SAVING_U3_LATE()     (g_bUsb3RepeaterMacU3PinDEnterFakeSavingU3Late = _TRUE)
#define CLR_USB_REPEATER_PIND_FAKE_SAVING_U3_LATE()     (g_bUsb3RepeaterMacU3PinDEnterFakeSavingU3Late = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
#if(_USB32_P3_POWER_INTERFERE_SOLUTION_SUPPORT == _ON)
//--------------------------------------------------
// Enum of  P3 Power Interfere Solution Step
//--------------------------------------------------
typedef enum
{
    _P3_POWER_SOLUTION_HIGH_PIRORITY = 0x00,
    _P3_POWER_SOLUTION_MEDIUM_PIRORITY,
    _P3_POWER_SOLUTION_LOW_PIRORITY,
} EnumP3PowerSolutionStep;
#endif // End of #if(_USB32_P3_POWER_INTERFERE_SOLUTION_SUPPORT == _ON)
#endif // End of #if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bUsb3RepeaterMacU3PinDEnterFakeSavingU3Late;
extern BYTE g_ucUsb3RepeaterMacU3SupportSpeed;
extern BYTE g_ucUsb3RepeaterMacU3SupportLane;
extern BYTE g_ucUsb3RepeaterMacPowerCutMode;
extern EnumUsbHubOSDResult g_enumUsb3RepeaterMacHubOSDResult;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumRx ScalerUsb3RepeaterMacDx2MacxMapping(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumRx ScalerUsb3RepeaterMacDx2MacxMapping_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumRx ScalerUsb3RepeaterMacUfpPhyx2MacxMapping(EnumRx enumUfpPhyxIndex);
extern EnumRx ScalerUsb3RepeaterMacUfpPhyx2MacxMapping_EXINT3(EnumRx enumUfpPhyxIndex);
extern EnumTypeCPcbPort ScalerUsb3RepeaterMacMacx2DxMapping_EXINT3(EnumRx enumMacxIndex);
extern BYTE ScalerUsb3RepeaterMacGetTypeCIndex_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
extern void ScalerUsb3RepeaterMacPowerCutOnProcess_EXINT3(void);
extern void ScalerUsb3RepeaterMacPowerCutOffProcess_EXINT3(void);
extern bit ScalerUsb3RepeaterMacCheckP3PowerCutOFF_EXINT3(void);
#if(_USB32_P3_POWER_INTERFERE_SOLUTION_SUPPORT == _ON)
extern void ScalerUsb3RepeaterMacP3PowerInterfereSolution_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort, EnumP3PowerSolutionStep enumP3PowerSolutionStep);
#endif // End of #if(_USB32_P3_POWER_INTERFERE_SOLUTION_SUPPORT == _ON)
#endif // End of #if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
#endif