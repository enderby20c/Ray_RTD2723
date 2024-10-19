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
// ID Code      : SysTmdsInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


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
extern void SysTmdsInterfaceSwitch(EnumInputPort enumInputPort, EnumPortType enumPortType, StructPortSwitchedStatus *pstPortStatus);

#if(_HDMI_SUPPORT == _ON)
extern void SysTmdsRxHandler(void);
extern void SysTmdsRxSetPsWakeupHpdToggle(void);

#if(_HDMI_ON_POWER_CONTROL == _ON)
extern void SysTmdsRxOnPowerControlByCableDetect(void);
#endif
#endif // End of #if(_HDMI_SUPPORT == _ON)

