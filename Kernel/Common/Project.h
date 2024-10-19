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
// ID Code      : Project.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PROJECT_H__
#define __PROJECT_H__

//--------------------------------------------------
// List Include
//--------------------------------------------------
#include <Scaler/Scaler_List.h>
#include <Project/Project_List.h>
#include <Panel/Panel_List.h>
#include <Pcb/Pcb_List.h>

#include <User_Project_List.h>
#include <User_Panel_List.h>
#include <User_Pcb_List.h>

//--------------------------------------------------
// RLxxxx Generation Option
//--------------------------------------------------
#include <Scaler/RL6829/RL6829_Gen_Option.h>
#include <Scaler/RL6952/RL6952_Gen_Option.h>
#include <Scaler/RL6978/RL6978_Gen_Option.h>

//--------------------------------------------------
// Project and Project Option Include
//--------------------------------------------------
#include <User_Project_Include.h>
#include <Project/Project_Config_Pre_Check.h>

#if(_SCALER_TYPE == _RL6829_SERIES)
#include <Project/RL6829_Project_Default.h>
#elif(_SCALER_TYPE == _RL6952_SERIES)
#include <Project/RL6952_Project_Default.h>
#elif(_SCALER_TYPE == _RL6978_SERIES)
#include <Project/RL6978_Project_Default.h>
#endif

#include <Project/RL6829_Project_Default.h>
#include <Project/RL6952_Project_Default.h>
#include <Project/RL6978_Project_Default.h>

#include <User_Project_Option.h>
#include <Project/Project_Option.h>

//--------------------------------------------------
// Panel and Panel Option Include
//--------------------------------------------------
#include <User_Panel_Include.h>
#include <Panel/Panel_Config_Pre_Check.h>

#include <Panel/Panel_Default.h>

#include <User_Panel_Option.h>
#include <Panel/Panel_Option.h>

//--------------------------------------------------
// Pcb and Pcb Option Include
//--------------------------------------------------
#include <User_Pcb_Include.h>

#include <Pcb/Pcb_Config_Pre_Check.h>

#if(_SCALER_TYPE == _RL6829_SERIES)
#include <Pcb/RL6829_Pcb_Default.h>
#elif(_SCALER_TYPE == _RL6952_SERIES)
#include <Pcb/RL6952_Pcb_Default.h>
#elif(_SCALER_TYPE == _RL6978_SERIES)
#include <Pcb/RL6978_Pcb_Default.h>
#endif

#include <Pcb/RL6829_Pcb_Default.h>
#include <Pcb/RL6952_Pcb_Default.h>
#include <Pcb/RL6978_Pcb_Default.h>
#include <Pcb/Pcb_Deprecated_Option.h>

#include <User_Pcb_Option.h>
#include <Pcb/Pcb_Option.h>

//--------------------------------------------------
// CPU-related Include
//--------------------------------------------------
#include <Arch/CPU32_IP_List.h>
#include <Arch/Irq_List.h>
#include <cmsis_device.h>

//--------------------------------------------------
// Option Include
//--------------------------------------------------
#include <User_Scaler_Option.h>
#include <Scaler/Scaler_Option.h>

//--------------------------------------------------
// Config Check Include
//--------------------------------------------------
#include <Project/Project_Config_Check.h>
#include <Panel/Panel_Config_Check.h>
#include <Pcb/Pcb_Config_Check.h>

//--------------------------------------------------
// Debug Include
//--------------------------------------------------
#include <Debug.h>

//--------------------------------------------------
// Device Include
//--------------------------------------------------
#include <ExternalDeviceInterface.h>

//--------------------------------------------------
// Test Option Include
//--------------------------------------------------
#include <Scaler_Test_Function.h>

//--------------------------------------------------
// Edid Checker Include
//--------------------------------------------------
#include <Edid_Checker_Option.h>

#endif // End of #ifndef __PROJECT_H__
