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
// ID Code      : Irq_List.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_SCALER_TYPE == _RL6829_SERIES)
#include <RL6829_Series_IrqList.h>
#elif(_SCALER_TYPE == _RL6952_SERIES)
#include <RL6952_Series_IrqList.h>
#elif(_SCALER_TYPE == _RL6978_SERIES)
#include <RL6978_Series_IrqList.h>
#endif

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _CPU_IRQ_DISABLE = 0,
    _CPU_IRQ_SW_LEVEL_0,
    _CPU_IRQ_SW_LEVEL_1,

    _CPU_IRQ_HW_LEVEL_0,
    _CPU_IRQ_HW_LEVEL_1,
    _CPU_IRQ_HW_LEVEL_2,
    _CPU_IRQ_HW_LEVEL_3,
    _CPU_IRQ_HW_LEVEL_4,
    _CPU_IRQ_HW_LEVEL_5,

    _CPU_IRQ_HW_LOWEST_LEVEL = _CPU_IRQ_HW_LEVEL_0,     // HW INT Lowest Priority
    _CPU_IRQ_HW_HIGHEST_LEVEL = _CPU_IRQ_HW_LEVEL_5,    // HW INT Highest Priority
} EnumCpuIrqPriority;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
