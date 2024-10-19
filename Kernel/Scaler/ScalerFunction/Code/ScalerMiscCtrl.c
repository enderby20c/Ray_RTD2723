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
// ID Code      : ScalerMiscCtrl.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "MiscCtrl/ScalerMiscCtrl.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Setup CPU1 Clock Divider
// Input Value  : enumTargetDiv --> enum of CPU1 Clock Divider
// Output Value : None
//--------------------------------------------------
void ScalerMiscCtrlCpuSetClkDivider(EnumCpuMiscCtrlCpuClkDivider enumTargetDiv)
{
    enumTargetDiv = enumTargetDiv;

#if(_CPU32_IP == _CPU32_IP_TR9)
    Scaler32SetBit(PA30000_00_CPU1_CLK_DIV, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumTargetDiv);
#endif

#if(_CPU32_IP == _CPU32_IP_KR4)
    Scaler32SetBit(PA40010_00_KCPU_CLK_DIV, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumTargetDiv);
#endif

#if(_CPU32_IP == _CPU32_IP_RX3081)
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    ScalerSetBit(PFF_ED_MCU_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), (enumTargetDiv << 2));
#endif
#endif
}

//--------------------------------------------------
// Description  : Get Current CPU1 Clock Divider Setting
// Input Value  : None
// Output Value : enum of Current CPU1 Clock Divider
//--------------------------------------------------
EnumCpuMiscCtrlCpuClkDivider ScalerMiscCtrlCpuGetClkDivider(void)
{
#if(_CPU32_IP == _CPU32_IP_TR9)
    return (EnumCpuMiscCtrlCpuClkDivider)(Scaler32GetDWord(PA30000_00_CPU1_CLK_DIV) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif

#if(_CPU32_IP == _CPU32_IP_KR4)
    return (EnumCpuMiscCtrlCpuClkDivider)(Scaler32GetDWord(PA40010_00_KCPU_CLK_DIV) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif

#if(_CPU32_IP == _CPU32_IP_RX3081)
    return (ScalerGetBit(PFF_ED_MCU_CONTROL, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) >> 2);
#endif
}

#if(_HW_CPU32_NOTIFY_INT_SUPPORT == _ON)
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
//--------------------------------------------------
// Description  : Send CPU Notify INT to KCPU
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMiscCtrlSetNotifyKCPU(void)
{
    Scaler32SetDWord(PA30000_10_NOTIFY_OTHER_CPU_INT_CONTROL, _BIT0);
    DELAY_5US();
    Scaler32SetDWord(PA30000_10_NOTIFY_OTHER_CPU_INT_CONTROL, 0);
}

//--------------------------------------------------
// Description  : Check if has CPU Notify INT sent from KCPU
// Input Value  : None
// Output Value : 1:Yes ; 0:No
//--------------------------------------------------
DWORD ScalerMiscCtrlChkNotifyFromKCPU(void)
{
    return Scaler32GetBit(PA30000_14_CPU1_NOTIFY_INT_STATUS, _BIT0);
}

//--------------------------------------------------
// Description  : Ack CPU Notify INT Flag from KCPU
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMiscCtrlAckNotifyFromKCPU(void)
{
    Scaler32SetDWord(PA30000_14_CPU1_NOTIFY_INT_STATUS, _BIT0);

    // avoiding RBUS delay cause repeat entering INT
    ASM_DSB();
}
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
//--------------------------------------------------
// Description  : Send CPU Notify INT to SCPU
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMiscCtrlSetNotifySCPU(void)
{
    MCU_FD51_NOTIFY_CPU32_INT_CTRL = 0x00;
    MCU_FD51_NOTIFY_CPU32_INT_CTRL = _BIT0;
    DELAY_5US();
    MCU_FD51_NOTIFY_CPU32_INT_CTRL = 0x00;
}

//--------------------------------------------------
// Description  : Check if has CPU Notify INT sent from SCPU
// Input Value  : None
// Output Value : 1:Yes ; 0:No
//--------------------------------------------------
DWORD ScalerMiscCtrlChkNotifyFromSCPU(void)
{
    return (MCU_FD52_NOTIFY_8051_INT_CTRL & _BIT0);
}

//--------------------------------------------------
// Description  : Ack CPU Notify INT Flag from SCPU
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMiscCtrlAckNotifyFromSCPU(void)
{
    MCU_FD52_NOTIFY_8051_INT_CTRL &= ~_BIT0;

    // avoiding RBUS delay cause repeat entering INT
    ASM_DSB();
}
#endif

#endif

//--------------------------------------------------
// Description  : set INT TESTx Enable
// Input Value  : enumIntTestX_idx --> enum Index of IntTestX
// Output Value : None
//--------------------------------------------------
void ScalerMiscCtrlIntTestxSetEnable(EnumCpuMiscCtrlIntTestIdx enumIntTestX_idx)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    Scaler32SetBit(PA30000_20_CPU1_INT_TEST_CONTROL, ~((DWORD)enumIntTestX_idx), enumIntTestX_idx);
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    Scaler32SetBit(PA40010_20_CPU1_INT_TEST_CONTROL, ~((DWORD)enumIntTestX_idx), enumIntTestX_idx);
#endif
}

//--------------------------------------------------
// Description  : set INT TESTx Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMiscCtrlIntTestxSetDisable(EnumCpuMiscCtrlIntTestIdx enumIntTestX_idx)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    Scaler32SetBit(PA30000_20_CPU1_INT_TEST_CONTROL, ~((DWORD)enumIntTestX_idx), 0);
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    Scaler32SetBit(PA40010_20_CPU1_INT_TEST_CONTROL, ~((DWORD)enumIntTestX_idx), 0);
#endif
}

//--------------------------------------------------
// Description  : set INT TESTx triggered
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMiscCtrlIntTestxSetTriggered(EnumCpuMiscCtrlIntTestIdx enumIntTestX_idx)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    Scaler32SetDWord(PA30000_24_CPU1_INT_TEST_TRIGGER, enumIntTestX_idx);
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    Scaler32SetDWord(PA40010_24_CPU1_INT_TEST_TRIGGER, enumIntTestX_idx);
#endif
}

//--------------------------------------------------
// Description  : clear INT TESTx trigger
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMiscCtrlIntTestxClearTrigger(EnumCpuMiscCtrlIntTestIdx enumIntTestX_idx)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    Scaler32SetBit(PA30000_24_CPU1_INT_TEST_TRIGGER, ~(enumIntTestX_idx), 0);
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    Scaler32SetBit(PA40010_24_CPU1_INT_TEST_TRIGGER, ~(enumIntTestX_idx), 0);
#endif
}

//--------------------------------------------------
// Description  : Get INT TESTx INT status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
DWORD ScalerMiscCtrlIntTestxGetStatus(EnumCpuMiscCtrlIntTestIdx enumIntTestX_idx)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    return (Scaler32GetDWord(PA30000_28_CPU1_INT_TEST_STATUS) & enumIntTestX_idx);
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    return (Scaler32GetDWord(PA40010_28_CPU1_INT_TEST_STATUS) & enumIntTestX_idx);
#endif
}

//--------------------------------------------------
// Description  : Ack INT TESTx INT status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMiscCtrlIntTestxAckStatus(EnumCpuMiscCtrlIntTestIdx enumIntTestX_idx)
{
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    Scaler32SetDWord(PA30000_28_CPU1_INT_TEST_STATUS, enumIntTestX_idx);
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    Scaler32SetDWord(PA40010_28_CPU1_INT_TEST_STATUS, enumIntTestX_idx);
#endif
}

