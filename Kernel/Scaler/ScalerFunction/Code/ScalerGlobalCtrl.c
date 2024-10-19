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
// ID Code      : ScalerGlobalCtrl.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "GlobalCtrl/ScalerGlobalCtrl.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile DWORD g_ulGlobalCtrlCpuClk_KHz = _HW_CPU32_CLK_SRC_EXTAL;
volatile DWORD g_ulGlobalCtrlPrevCpuClk_KHz = _HW_CPU32_CLK_SRC_INVALID;

#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
volatile DWORD g_ulGlobalCtrlScpuClk_KHz = _HW_CPU32_CLK_SRC_EXTAL;
volatile DWORD g_ulGlobalCtrlPrevScpuClk_KHz = _HW_CPU32_CLK_SRC_INVALID;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Wait command be executed by CPU32 CPU
// Input Value  : enumCpuClkSrc-->CPU Clock Source
// Output Value : None
//--------------------------------------------------
void ScalerGlobalCtrlSetSys32ClkSrc(EnumClkSel enumClkSel)
{
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    ScalerGlobalCtrlSetKcpuClkSrc(enumClkSel);
#else
    ScalerGlobalCtrlSetScpuClkSrc(enumClkSel);
#endif
}

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
//--------------------------------------------------
// Description  : Set KCPU CLK Source
// Input Value  : enumCpuClkSrc-->CPU Clock Source
// Output Value : None
//--------------------------------------------------
void ScalerGlobalCtrlSetKcpuClkSrc(EnumClkSel enumClkSel)
{
    SET_PREVIOUS_CPU_CLK_KHZ(GET_CURRENT_CPU_CLK_KHZ());

    SET_PREVIOUS_WD_REF_CLK_KHZ(GET_CURRENT_WD_REF_CLK_KHZ());

    switch(enumClkSel)
    {
        case _M2PLL_CLK:
            // M2PLL
            // setup CPU CLK Divider=2
            ScalerMiscCtrlCpuSetClkDivider(_CPU_CLK_DIV_2);
            SET_CURRENT_CPU_CLK_KHZ(_HW_CPU32_CLK_SRC_M2PLL);
            SET_CURRENT_WD_REF_CLK_KHZ(_HW_CPU32_CLK_SRC_M2PLL / _FLASH_CLK_DIV);
            break;
        case _IOSC_CLK:
            // IOSC CLK
            // setup CPU CLK Divider=1
            ScalerMiscCtrlCpuSetClkDivider(_CPU_CLK_DIV_1);
            SET_CURRENT_CPU_CLK_KHZ(_HW_CPU32_CLK_SRC_IOSC);
            SET_CURRENT_WD_REF_CLK_KHZ(_HW_CPU32_CLK_SRC_IOSC / _FLASH_CLK_PS_DIV);
            break;
        case _EXT_XTAL_CLK:
            // EXTAL CLK
            // setup CPU CLK Divider=1
            ScalerMiscCtrlCpuSetClkDivider(_CPU_CLK_DIV_1);
            SET_CURRENT_CPU_CLK_KHZ(_HW_CPU32_CLK_SRC_EXTAL);
            SET_CURRENT_WD_REF_CLK_KHZ(_HW_CPU32_CLK_SRC_EXTAL / _FLASH_CLK_IN_DIV);
            break;
        default:
            // setup CPU CLK Divider=1
            ScalerMiscCtrlCpuSetClkDivider(_CPU_CLK_DIV_1);
            SET_CURRENT_CPU_CLK_KHZ(_HW_CPU32_CLK_SRC_EXTAL);
            SET_CURRENT_WD_REF_CLK_KHZ(_HW_CPU32_CLK_SRC_EXTAL / _FLASH_CLK_IN_DIV);
            break;
    }

    __DSB();
}
#endif

#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
//--------------------------------------------------
// Description  : Set SCPU CLK Source
// Input Value  : enumCpuClkSrc-->CPU Clock Source
// Output Value : None
//--------------------------------------------------
void ScalerGlobalCtrlSetScpuClkSrc(EnumClkSel enumClkSel)
{
    SET_PREVIOUS_CPU_CLK_KHZ(GET_CURRENT_CPU_CLK_KHZ());

    switch(enumClkSel)
    {
        case _M2PLL_CLK:
            // EMCU PLL CLK
#if(_HW_CPU32_CLK_SRC_EMCU_PLL == _EMCU_PLL_SPEED_354M)
            // Select EMCU_PLL, Set SB2 CLK = SCPU_CLK / 2 = 177MHz
            Scaler32SetBit(PA30000_00_CPU1_CLK_DIV, ~(_BIT17 | _BIT16 | _BIT(11, 8)), (_BIT16 | (2UL << 8)));
#endif
#if(_HW_CPU32_CLK_SRC_EMCU_PLL == _EMCU_PLL_SPEED_480M)
            // Select EMCU_PLL, Set SB2 CLK = SCPU_CLK / 3 = 160MHz
            Scaler32SetBit(PA30000_00_CPU1_CLK_DIV, ~(_BIT17 | _BIT16 | _BIT(11, 8)), (_BIT16 | (3UL << 8)));
#endif
            // setup SCPU CLK Divider=1
            ScalerMiscCtrlCpuSetClkDivider(_CPU_CLK_DIV_1);
            SET_CURRENT_CPU_CLK_KHZ(_HW_CPU32_CLK_SRC_EMCU_PLL);
            break;
        case _IOSC_CLK:
            // IOSC CLK
            Scaler32SetBit(PA30000_00_CPU1_CLK_DIV, ~(_BIT17 | _BIT16 | _BIT(11, 8)), (1UL << 8));
            // setup CPU CLK Divider=1
            ScalerMiscCtrlCpuSetClkDivider(_CPU_CLK_DIV_1);
            SET_CURRENT_CPU_CLK_KHZ(_HW_CPU32_CLK_SRC_IOSC);
            break;
        case _EXT_XTAL_CLK:
            // EXTAL CLK
            // setup CPU CLK Divider=1
            Scaler32SetBit(PA30000_00_CPU1_CLK_DIV, ~(_BIT17 | _BIT16 | _BIT(11, 8)), (1UL << 8));
            ScalerMiscCtrlCpuSetClkDivider(_CPU_CLK_DIV_1);
            SET_CURRENT_CPU_CLK_KHZ(_HW_CPU32_CLK_SRC_EXTAL);
            break;
        default:
            // setup CPU CLK Divider=1
            ScalerMiscCtrlCpuSetClkDivider(_CPU_CLK_DIV_1);
            SET_CURRENT_CPU_CLK_KHZ(_HW_CPU32_CLK_SRC_EXTAL);
            break;
    }

    __DSB();
}
#endif

//--------------------------------------------------
// Description  : Get KCPU Clock Rate
// Input Value  : None
// Output Value : KCPU Clock Rate(KHz)
//--------------------------------------------------
DWORD ScalerGlobalCtrlGetEclkClockRate(void)
{
    return (g_ulGlobalCtrlCpuClk_KHz / (ScalerGetBit(PFF_ED_MCU_CONTROL, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) >> 2));
}

