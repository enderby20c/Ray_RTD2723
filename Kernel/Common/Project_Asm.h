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
// ID Code      : Project_Asm.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PROJECT_ASM_H__
#define __PROJECT_ASM_H__

//--------------------------------------------------
// List Include
//--------------------------------------------------
#include <Global.h>
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
// CPU-related Include
//--------------------------------------------------
#include <Arch/CPU32_IP_List.h>

//--------------------------------------------------
// Register Include
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6829_SERIES)
#include <RL6829_Series_RegList.h>
#elif(_SCALER_TYPE == _RL6952_SERIES)
#include <RL6952_Series_RegList.h>
#elif(_SCALER_TYPE == _RL6978_SERIES)
#include <RL6978_Series_RegList.h>
#endif

//--------------------------------------------------
// Memory layout Include
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6829_SERIES)
#include <RL6829_Series_McuMemLayout.h>
#elif(_SCALER_TYPE == _RL6952_SERIES)
#include <RL6952_Series_McuMemLayout.h>
#elif(_SCALER_TYPE == _RL6978_SERIES)
#include <RL6978_Series_McuMemLayout.h>
#endif

//--------------------------------------------------
// Debug Include
//--------------------------------------------------
#include <Debug.h>

#endif // End of #ifndef __PROJECT_ASM_H__
