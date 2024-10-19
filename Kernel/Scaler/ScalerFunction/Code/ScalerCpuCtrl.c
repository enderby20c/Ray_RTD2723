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
// ID Code      : ScalerCpuCtrl.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_CPU32_CTRL__

#include "ScalerFunctionInclude.h"
#include "CpuCtrl/ScalerCpuCtrl.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_SCPU_SUPPORT == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
//--------------------------------------------------
// Description  : CPU32 Control Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuCtrlHandler(void)
{
#if(_HW_CPU32_NOTIFY_INT_SUPPORT == _ON)
    // Received CPU32 Request Command
    if(GET_SCPU_NOTIFY_INT_MORE_PROCESS_FLAG() == _TRUE)
    {
        // Clear SCPU Notify INT More Process Flag
        CLR_SCPU_NOTIFY_INT_MORE_PROCESS_FLAG();

        ScalerCpuSyncHandler();
    }
#endif
}

//--------------------------------------------------
// Description  : Control Scpu Platform Bus Mode/Sclk Enable/Scpu Enable
// Input Value  :
//                bRBusMode : 0:BypassMode ; 1:RBusMode
//                bEnableScpuPlatformClk : 0:Disable  Scpu Paltform Sclk ; 1:Enable Scpu Paltform Sclk
//                bEnableScpu : 0:Disable Scpu ; 1:Enable Scpu
// Output Value : None
//--------------------------------------------------
void ScalerCpuCtrlSetScpuGlobalControl(bit bRBusMode, bit bEnableScpuPlatformClk, bit bEnableScpu)
{
    if(bRBusMode == _TRUE)
    {
        if(bEnableScpu == _TRUE)
        {
            // Enable SCPU
            MCU_FD50_CPU32_GLOBAL_CTRL = (_BIT2 | (bEnableScpuPlatformClk << 0));
            MCU_FD50_CPU32_GLOBAL_CTRL = (_BIT2 | _BIT1 | (bEnableScpuPlatformClk << 0));
            ScalerMcuDelay5us();
            MCU_FD50_CPU32_GLOBAL_CTRL = (_BIT2 | (bEnableScpuPlatformClk << 0));
        }
        else
        {
            // Disable SCPU
            MCU_FD50_CPU32_GLOBAL_CTRL = (_BIT2 | _BIT1 | (bEnableScpuPlatformClk << 0));
            ScalerMcuDelay5us();
        }
    }
    else
    {
        MCU_FD50_CPU32_GLOBAL_CTRL = ((((bit)!bEnableScpu) << 1) | (bEnableScpuPlatformClk << 0));
    }
}

//--------------------------------------------------
// Description  : Check if SCPU is Active
// Input Value  : None
// Output Value : _TRUE:SCPU is Active ; _FALSE:SCPU is Disabled
//--------------------------------------------------
bit ScalerCpuCtrlCheckScpuActive(void)
{
    return ((MCU_FD50_CPU32_GLOBAL_CTRL == (_BIT2 | _BIT0)) ? _TRUE : _FALSE);
}

//--------------------------------------------------
// Description  : Bootup CPU32 CPU
// Input Value  : None
// Output Value : None
// Attention : DDR Initialized Must be Done Before Call ScalerCpuCtrlBootInit()
//--------------------------------------------------
void ScalerCpuCtrlBootInit(void)
{
    // Set SCPU(TR9) Boot FW Default Reset && Exception Vector Entry Address according FlashBankOffset
    DWORD ulDefaultResetAddress = (((DWORD)(ScalerCpuCtrlFlashBankOffsetGetValue() + 1)) << 16);

    // Enable Invalid Addr Access on RBus IRQ
    SET_ACCESS_INVALID_ADDR_ON_RBUS_IRQ();

    // Gating SCPU's Clock as CPU32 WD Timeout
    CLR_SCPU_GATING_CLOCK_OPTION();

#if(_HW_CPU32_NOTIFY_INT_SUPPORT == _ON)
    // Enable Received CPU32 IRQ for Communication
    SET_SCPU_RECEIVE_REQUEST_IRQ();

    // Clear CPU32 Boot flags
    // 0xA3000004[0]:Bootloader Extract Kernel Success
    // 0xA3000004[1]:Bootloader Extract Kernel Done(maybe success or failed)
    // 0xA3000004[2]:Kernel FW executed
    Scaler32SetDWord(PA30000_04_GLOBAL_CTRL_DUMMY0, 0);
#endif

    // Enable RBUS mode, Enable SCPU Sclk and Disable SCPU for setting MTVEC vector value
    ScalerCpuCtrlSetScpuGlobalControl(_TRUE, _TRUE, _FALSE);
    Scaler32SetDWord(PA30004_00_RISCV_CPU1_DEFAULT_RESET_VECTOR, ulDefaultResetAddress);
    Scaler32SetDWord(PA30004_04_RISCV_CPU1_DEFAULT_MTVEC, (ulDefaultResetAddress + _SCPU_BOOT_DEFAULT_EXCEPTION_OFFSET));

#if(_FW_CPU32_MAIN_PROCESS_CPU == _CPU_ID_KCPU)

    // Enable RBUS mode, Enable SCPU Sclk and Enable SCPU
    ScalerCpuCtrlSetScpuGlobalControl(_TRUE, _TRUE, _TRUE);


#if(_HW_CPU32_NOTIFY_INT_SUPPORT == _ON)
    // CPU32 Bootloader may consume 42ms
    if(ScalerTimerPollingFlagProc32Bit(_SCPU_IMAGE_LOAD_TIMEOUT, PA30000_04_GLOBAL_CTRL_DUMMY0, _BIT1, _TRUE) == _FALSE)
    {
        // Bootloader Extract Kernel Timeout...
        DebugMessageCpu32("CPU32 Extract Kernel Timeout", 0);
        Scaler32SetDWord(PA30000_04_GLOBAL_CTRL_DUMMY0, 0);
    }
    else
    {
        // Check Bootloadrt Kernel Extract Status
        if((Scaler32GetDWord(PA30000_04_GLOBAL_CTRL_DUMMY0) & _BIT0) != _BIT0)
        {
            // Bootloader Extract Kernel Failed...
            DebugMessageCpu32("CPU32 Extract Kernel Failed", 0);
            Scaler32SetDWord(PA30000_04_GLOBAL_CTRL_DUMMY0, 0);
        }
        else
        {
            // Bootloader Extract Kernel Success
            if(ScalerTimerPollingFlagProc32Bit(5, PA30000_04_GLOBAL_CTRL_DUMMY0, _BIT2, _TRUE) == _FALSE)
            {
                // Bootloader Execute Kernel FW Failed...
                DebugMessageCpu32("CPU32 Execute Kernel FW Failed", 0);
                Scaler32SetDWord(PA30000_04_GLOBAL_CTRL_DUMMY0, 0);
            }
            else
            {
#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
                ScalerCpuCtrlActorInit();
#endif
                DebugMessageCpu32("CPU32 pass", 1);
            }
        }
    }
    if(Scaler32GetDWord(PA30000_04_GLOBAL_CTRL_DUMMY0) == 0)
    {
        // Keep RBUS Mode && TR9 Platform Clk Enable, just Disable TR9 CPU
        ScalerCpuCtrlSetScpuGlobalControl(_TRUE, _TRUE, _FALSE);
    }
#endif

#else
    // _FW_CPU32_MAIN_PROCESS_CPU is _CPU_ID_SCPU

    // Clear WDT
    CLR_MCU_WATCH_DOG();

#if(_HW_CPU32_NOTIFY_INT_SUPPORT == _ON)
    // Enable RBUS mode, Enable SCPU Sclk and Enable SCPU
    ScalerCpuCtrlSetScpuGlobalControl(_TRUE, _TRUE, _TRUE);
#endif
#endif
}

#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
//--------------------------------------------------
// Description  : Init for SCPU actor mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuCtrlActorInit(void)
{
    // Disable KCPU interrupts
    for(EnumIRQnType enumIRQnTypeIdx = _IRQN_CPU_NOTIFY; enumIRQnTypeIdx <= _IRQN_SCALER_ALL; ++enumIRQnTypeIdx)
    {
        switch(enumIRQnTypeIdx)
        {
            case _IRQN_CPU_NOTIFY:
            case _IRQN_SCALER_ERROR:
                break;

            default:
                ScalerCpuHalDisableIRQ(enumIRQnTypeIdx);
                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Shut down 32bits platform(Set CPU32 in idle mode and wait for shut down)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuCtrlSystemOff(void)
{
    WORD usTimeOut = 10;
    // Make Sure already initialized DDR before Boot CPU32 Core
#if(_HW_CPU32_NOTIFY_INT_SUPPORT == _ON)
    ScalerCpuSyncShutDownCmd();
#endif
    // wait 10ms for SCPU fbus/dbus/rbus idle
    while(usTimeOut != 0)
    {
        if((MCU_FDEC_CPU32_WDT_CTRL & (_BIT6 | _BIT4 | _BIT2)) == (_BIT6 | _BIT4 | _BIT2))
        {
            break;
        }
        ScalerTimerDelayXms(1);
        usTimeOut--;
    }
    // switch to bypass bus mode, Set SCPU Sclk and SCPU Disable
    ScalerCpuCtrlSetScpuGlobalControl(_FALSE, _FALSE, _FALSE);

#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
    ScalerMcuIntPriorityInit();
#endif
}

//--------------------------------------------------
// Description  : Get CPU32 Flash Bank Offset Value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerCpuCtrlFlashBankOffsetGetValue(void)
{
    return (((BYTE)(DWORD)(&__flash_bank_count__)) - 1);
}
#endif

//--------------------------------------------------
// Description  : Get Bus Idle Status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerCpuCtrlGetCpu32BusIdleStatus(void)
{
    // Wait DDR bus Max Request Latency for Command Complete
    if(ScalerTimerPollingFlagProc(20, PFD_EC_CPU32_WDT_CTRL, _BIT7, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Wait Flash bus Max Request Latency for Command Complete
    if(ScalerTimerPollingFlagProc(20, PFD_EC_CPU32_WDT_CTRL, _BIT5, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Wait Rbus Max Request Latency for Command Complete
    if(ScalerTimerPollingFlagProc(20, PFD_EC_CPU32_WDT_CTRL, _BIT3, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Check R/F/D Bus Idle
    if((MCU_FDEC_CPU32_WDT_CTRL & (_BIT6 | _BIT4 | _BIT2)) == (_BIT6 | _BIT4 | _BIT2))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif // End of #if(_SCPU_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Access Invalid Addr on Rbus
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuCtrlBusErrorProcess(EnumDebugSysBusErrorType enumDebugSysBusErrorType)
{
#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
    // Log Bus Error Information
    if(Scaler32GetDWord(PA40010_4C_CPU1_TEST_MODE_DUMMY3) == 0x00000000)
    {
        Scaler32SetDWord(PA40010_4C_CPU1_TEST_MODE_DUMMY3, (DWORD)g_pulDebugSysBusErrorInfo);

        g_pulDebugSysBusErrorInfo[0] = enumDebugSysBusErrorType;

        // Record CPU Context Buffer Address
        g_pulDebugSysBusErrorInfo[14] = (DWORD)(&g_pulDebugCpuContext[0]);

        // RX3081: g_pulDebugSysBusErrorInfo[1~7]={CP0_STATUS, CP0_CAUSE, CP0_EPC, CP0_BADVADDR, CP0_CCTL, CP0_CK0, CP0_CK1}
        // TR9   : g_pulDebugSysBusErrorInfo[1~7]={MSTATUS, MCAUSE, MEPC, MTVAL, MIE, MIP, MTVEC}
        TRAP_DUMP((&g_pulDebugSysBusErrorInfo[1]));

        switch(enumDebugSysBusErrorType)
        {
            case _DBG_SYSBUS_ERR_RXI300_RW_FAIL:
                // RXI-300 Bus Memory Hole Error Happened
#if(_HW_CPU32_RXI300_GEN == _RXI300_HW_GEN_0)
                g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA40002_30_ELR_I_CODE);     // ELR_I_CODE    RXI-300 Error log code register
                g_pulDebugSysBusErrorInfo[9] = Scaler32GetDWord(PA40002_00_ELR_I_PLD0);     // ELR_I_PLD0    RXI-300 Error log payload register0
                g_pulDebugSysBusErrorInfo[10] = Scaler32GetDWord(PA40002_0C_ELR_I_ADR0);    // ELR_I_ADR0    RXI-300 Error log address[31:0]
                g_pulDebugSysBusErrorInfo[11] = Scaler32GetDWord(PA40002_10_ELR_I_ADR1);    // ELR_I_ADR0    RXI-300 Error log address[63:32]
                g_pulDebugSysBusErrorInfo[12] = Scaler32GetDWord(PA40002_04_ELR_I_PLD1);    // ELR_I_PLD1    RXI-300 Error log payload register1
                g_pulDebugSysBusErrorInfo[13] = Scaler32GetDWord(PA40002_08_ELR_I_ID);      // ELR_I_ID      RXI-300 Error log ID information register
#endif
#if(_HW_CPU32_RXI300_GEN == _RXI300_HW_GEN_1)
                if(Scaler32GetBit(PA40002_30_ELR_1_CODE, _BIT(7, 0)) != 0)
                {
                    g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA40002_30_ELR_1_CODE);     // ELR_1_CODE    RXI-300 Error log code register
                    g_pulDebugSysBusErrorInfo[9] = Scaler32GetDWord(PA40002_00_ELR_1_PLD0);     // ELR_1_PLD0    RXI-300 Error log payload register0
                    g_pulDebugSysBusErrorInfo[10] = Scaler32GetDWord(PA40002_0C_ELR_1_ADR0);    // ELR_1_ADR0    RXI-300 Error log address[31:0]
                    g_pulDebugSysBusErrorInfo[11] = Scaler32GetDWord(PA40002_10_ELR_1_ADR1);    // ELR_1_ADR1    RXI-300 Error log address[63:32]
                    g_pulDebugSysBusErrorInfo[12] = Scaler32GetDWord(PA40002_04_ELR_1_PLD1);    // ELR_1_PLD1    RXI-300 Error log payload register1
                    g_pulDebugSysBusErrorInfo[13] = Scaler32GetDWord(PA40002_08_ELR_1_ID);      // ELR_1_ID      RXI-300 Error log ID information register
                }
                else if(Scaler32GetBit(PA40002_70_ELR_2_CODE, _BIT(7, 0)) != 0)
                {
                    g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA40002_70_ELR_2_CODE);     // ELR_2_CODE    RXI-300 Error log code register
                    g_pulDebugSysBusErrorInfo[9] = Scaler32GetDWord(PA40002_40_ELR_2_PLD0);     // ELR_2_PLD0    RXI-300 Error log payload register0
                    g_pulDebugSysBusErrorInfo[10] = Scaler32GetDWord(PA40002_4C_ELR_2_ADR0);    // ELR_2_ADR0    RXI-300 Error log address[31:0]
                    g_pulDebugSysBusErrorInfo[11] = Scaler32GetDWord(PA40002_50_ELR_2_ADR1);    // ELR_2_ADR1    RXI-300 Error log address[63:32]
                    g_pulDebugSysBusErrorInfo[12] = Scaler32GetDWord(PA40002_44_ELR_2_PLD1);    // ELR_2_PLD1    RXI-300 Error log payload register1
                    g_pulDebugSysBusErrorInfo[13] = Scaler32GetDWord(PA40002_48_ELR_2_ID);      // ELR_2_ID      RXI-300 Error log ID information register
                }
                else if(Scaler32GetBit(PA40002_B0_ELR_3_CODE, _BIT(7, 0)) != 0)
                {
                    g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA40002_B0_ELR_3_CODE);     // ELR_3_CODE    RXI-300 Error log code register
                    g_pulDebugSysBusErrorInfo[9] = Scaler32GetDWord(PA40002_80_ELR_3_PLD0);     // ELR_3_PLD0    RXI-300 Error log payload register0
                    g_pulDebugSysBusErrorInfo[10] = Scaler32GetDWord(PA40002_8C_ELR_3_ADR0);    // ELR_3_ADR0    RXI-300 Error log address[31:0]
                    g_pulDebugSysBusErrorInfo[11] = Scaler32GetDWord(PA40002_90_ELR_3_ADR1);    // ELR_3_ADR1    RXI-300 Error log address[63:32]
                    g_pulDebugSysBusErrorInfo[12] = Scaler32GetDWord(PA40002_84_ELR_3_PLD1);    // ELR_3_PLD1    RXI-300 Error log payload register1
                    g_pulDebugSysBusErrorInfo[13] = Scaler32GetDWord(PA40002_88_ELR_3_ID);      // ELR_3_ID      RXI-300 Error log ID information register
                }
#endif
                break;
            case _DBG_SYSBUS_ERR_RXI300_TIMEOUT:
                // RXI-300 Bus Timeout Error Happened
                g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA40010_98_CPU1_RXI300_TO_CTRL2);     // Address when RXI-300 Bus Timeout occur
                break;
#if(_SCPU_SUPPORT == _ON)
            case _DBG_SYSBUS_ERR_SCPU_WRAPPER_MEM_TRASH:
                // USE SCPU_Wrapper Memory Trash INT for TR9 PMP enhance
                g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA20020_50_MEM_TRASH_DBG_INT);
                g_pulDebugSysBusErrorInfo[9] = ScalerBusScpuWrapMemTrashDbgGetTrapAddr();
                g_pulDebugSysBusErrorInfo[10] = ScalerBusScpuWrapMemTrashDbgGetTrapRW();
                break;
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
            // KCPU
            case _DBG_SYSBUS_ERR_SB2_KCPU_DEBUG_TRAP:
                // KCPU access Debug Address Range
                g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA20014_CC_DBG_ADDR1);
                g_pulDebugSysBusErrorInfo[9] = ScalerBusSb2ScpuGetTrapAddress();    // TrapAddress
                break;
            case _DBG_SYSBUS_ERR_SB2_SCPU_ACCESS_SECURE_REGION:
                // SCPU access Secure Region
                g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA20019_74_INTSTAT);
                g_pulDebugSysBusErrorInfo[9] = ScalerBusSb2ScpuIllegalAccessSecurRegionIntGetTrapAddress();
                break;
            case _DBG_SYSBUS_ERR_SB2_BUS_TIMEOUT:
                // SB2 BUS Timeout
                g_pulDebugSysBusErrorInfo[8] = MCU_FDED_SB2_TIMEOUT_INTSTAT;    // ucBUS
                g_pulDebugSysBusErrorInfo[9] = MCU_FDEE_SB2_TIMEOUT_RECORD;     // ucMaster
                g_pulDebugSysBusErrorInfo[10] = (((DWORD)MCU_FDEF_SB2_TIMEOUT_INV_ADDR_0) << 24) |
                                                (((DWORD)MCU_FDF0_SB2_TIMEOUT_INV_ADDR_1) << 16) |
                                                (((DWORD)MCU_FDF1_SB2_TIMEOUT_INV_ADDR_2) << 8) |
                                                (((DWORD)MCU_FDF2_SB2_TIMEOUT_INV_ADDR_3) << 0);
                break;
            case _DBG_SYSBUS_ERR_SB2_KCPU_ACCESS_INVALID_ADDR:
                // KCPU access invalid address(KCPU RW RBUS/RBUSD Timeout)
                // include BW8_RBUS_INVALID_ADDR
                g_pulDebugSysBusErrorInfo[8] = ScalerBusSb2GetInvalidAccessAddress();
                break;
            case _DBG_SYSBUS_ERR_SCPU_WDT_TIMEOUT:
                // SCPU WDT Timeout
                g_pulDebugSysBusErrorInfo[8] = MCU_FDEC_CPU32_WDT_CTRL;     // WDT Ctrl
                break;
            case _DBG_SYSBUS_ERR_KCPU_MEI:
                if(g_pulDebugSysBusErrorInfo[2] == _TRAP_UNKNOWN_INST)
                {
                    g_pulDebugSysBusErrorInfo[0] = _DBG_SYSBUS_ERR_SCPU_USAGE_FAULT;
                }
                if((g_pulDebugSysBusErrorInfo[2] == _TRAP_LOAD_ACCESS_FAULT) || (g_pulDebugSysBusErrorInfo[2] == _TRAP_STORE_ACCESS_FAULT))
                {
                    g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA40010_94_CPU1_RXI300_TO_CTRL1);
                    g_pulDebugSysBusErrorInfo[9] = Scaler32GetDWord(PA40010_98_CPU1_RXI300_TO_CTRL2);
                }
                break;
#else
            // SCPU
            case _DBG_SYSBUS_ERR_SCPU_HARD_FAULT:
            case _DBG_SYSBUS_ERR_SCPU_MEI:
                if(g_pulDebugSysBusErrorInfo[2] == _TRAP_UNKNOWN_INST)
                {
                    g_pulDebugSysBusErrorInfo[0] = _DBG_SYSBUS_ERR_SCPU_USAGE_FAULT;
                }
                if((g_pulDebugSysBusErrorInfo[2] == _TRAP_LOAD_ACCESS_FAULT) || (g_pulDebugSysBusErrorInfo[2] == _TRAP_STORE_ACCESS_FAULT))
                {
                    g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA40010_94_CPU1_RXI300_TO_CTRL1);
                    g_pulDebugSysBusErrorInfo[9] = Scaler32GetDWord(PA40010_98_CPU1_RXI300_TO_CTRL2);
                }
                ScalerBusSb2TrapError_AddDebugInfo();
                break;
            case _DBG_SYSBUS_ERR_SB2_SCPU_ACCESS_DBG_TRAP_ADDR:
                // SCPU access Debug Address Range
                g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA20014_CC_DBG_ADDR1);
                g_pulDebugSysBusErrorInfo[9] = ScalerBusSb2ScpuGetTrapAddress();
                break;
#if(_HW_CPU32_BW32_SUPPORT == _ON)
            case _DBG_SYSBUS_ERR_BW32_DEST_ADDR:
                // BW32 Error Dest Address
                g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA20002_50_BW32_ERR_DEST_CTRL);     // Error Flag
                g_pulDebugSysBusErrorInfo[9] = Scaler32GetDWord(PA20002_60_BW32_ERR_DEST_ADDR0);    // CMD0 Error Address
                g_pulDebugSysBusErrorInfo[10] = Scaler32GetDWord(PA20002_64_BW32_ERR_DEST_ADDR1);   // CMD1 Error Address
                g_pulDebugSysBusErrorInfo[11] = Scaler32GetDWord(PA20002_68_BW32_ERR_DEST_ADDR2);   // CMD2 Error Address
                break;
#endif
#if(_HW_CPU32_RBUS2DDR_SUPPORT == _ON)
            case _DBG_SYSBUS_ERR_RBUS2DDR_SRC_ADDR:
                // RBUS2DDR Error Src Address
                g_pulDebugSysBusErrorInfo[8] = Scaler32GetDWord(PA20003_50_RBUS2DDR_ERR_SRC_CTRL);     // Error Flag
                g_pulDebugSysBusErrorInfo[9] = Scaler32GetDWord(PA20003_60_RBUS2DDR_ERR_SRC_ADDR0);    // CMD0 Error Address
                g_pulDebugSysBusErrorInfo[10] = Scaler32GetDWord(PA20003_64_RBUS2DDR_ERR_SRC_ADDR1);   // CMD1 Error Address
                g_pulDebugSysBusErrorInfo[11] = Scaler32GetDWord(PA20003_68_RBUS2DDR_ERR_SRC_ADDR2);   // CMD2 Error Address
                break;
#endif
#endif
#endif
            default:
                break;
        }
    }
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    // Mark CPU Source
    g_pulDebugSysBusErrorInfo[0] |= _BIT31;
#endif

    DISABLE_CPU32_WDT();
#endif

    // Ack Bus Error
    switch(enumDebugSysBusErrorType)
    {
        case _DBG_SYSBUS_ERR_RXI300_RW_FAIL:
            // Ack RXI300 Bus Memory Hole Error Flag
#if(_HW_CPU32_RXI300_GEN == _RXI300_HW_GEN_0)
            Scaler32SetDWord(PA40002_3C_ELR_I_INTR_CLR, _BIT0);
#endif
#if(_HW_CPU32_RXI300_GEN == _RXI300_HW_GEN_1)
            if(Scaler32GetBit(PA40002_30_ELR_1_CODE, _BIT(7, 0)) != 0)
            {
                Scaler32SetDWord(PA40002_3C_ELR_1_INTR_CLR, _BIT0);
            }
            else if(Scaler32GetBit(PA40002_70_ELR_2_CODE, _BIT(7, 0)) != 0)
            {
                Scaler32SetDWord(PA40002_7C_ELR_2_INTR_CLR, _BIT0);
            }
            else if(Scaler32GetBit(PA40002_B0_ELR_3_CODE, _BIT(7, 0)) != 0)
            {
                Scaler32SetDWord(PA40002_BC_ELR_3_INTR_CLR, _BIT0);
            }
#endif
            break;
        case _DBG_SYSBUS_ERR_RXI300_TIMEOUT:
            // Ack RXI300 Bus Timeout Flag
            Scaler32SetDWord(PA40010_94_CPU1_RXI300_TO_CTRL1, _BIT0);
            break;
#if(_SCPU_SUPPORT == _ON)
        case _DBG_SYSBUS_ERR_SCPU_WRAPPER_MEM_TRASH:
            // USE SCPU_Wrapper Memory Trash INT for TR9 PMP enhance
            ScalerBusScpuWrapMemTrashDbgIntAckStatus();
            ScalerBusScpuWrapMemTrashDbgNegIntAckStatus();
            break;
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
        // KCPU
        case _DBG_SYSBUS_ERR_SB2_KCPU_DEBUG_TRAP:
            // Ack Flag
            ScalerBusSb2KcpuTrapAddressIntAckStatus();
            break;
        case _DBG_SYSBUS_ERR_SB2_SCPU_ACCESS_SECURE_REGION:
            // SCPU access Secure Region
            ScalerBusSb2ScpuIllegalAccessSecurRegionIntAckStatus();
            break;
        case _DBG_SYSBUS_ERR_SB2_KCPU_ACCESS_INVALID_ADDR:
            // KCPU access invalid address(KCPU RW RBUS/RBUSD Timeout)
            // include BW8_RBUS_INVALID_ADDR
            ScalerBusSb2KcpuInvalidAccessIntAckStatus();
            break;
        case _DBG_SYSBUS_ERR_SB2_BUS_TIMEOUT:
        case _DBG_SYSBUS_ERR_SCPU_WDT_TIMEOUT:
            // SB2 BUS Timeout, Disable SCPU WDT
            Scaler32SetBit(PA30003_04_TCWCR, ~((DWORD)0xFF), _WDT_DISABLE);
            // SCPU WDT Timeout
#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
            while(1)
            {
                // wait for User Debug via ISP Mode
            }
#else
            // Whole chip reset
            SET_WHOLE_CHIP_RESET();
#endif
            break;
#else
        // SCPU
        case _DBG_SYSBUS_ERR_SCPU_HARD_FAULT:
        case _DBG_SYSBUS_ERR_SCPU_USAGE_FAULT:
        case _DBG_SYSBUS_ERR_SCPU_MEI:

            ScalerBusSb2TrapError_IRQHandler();
            break;
        case _DBG_SYSBUS_ERR_SB2_SCPU_ACCESS_DBG_TRAP_ADDR:
            // SCPU access Debug Address Range
            // Ack Flag
            ScalerBusSb2ScpuTrapAddressIntAckStatus();
            break;
#if(_HW_CPU32_BW32_SUPPORT == _ON)
        case _DBG_SYSBUS_ERR_BW32_DEST_ADDR:
            // ack cmd0/cmd1/cmd2 Address Error Flag
            Scaler32SetBit(PA20002_50_BW32_ERR_DEST_CTRL, ~(_BIT16 | _BIT8 | _BIT0), (_BIT16 | _BIT8 | _BIT0));
            break;
#endif
#if(_HW_CPU32_RBUS2DDR_SUPPORT == _ON)
        case _DBG_SYSBUS_ERR_RBUS2DDR_SRC_ADDR:
            // ack cmd0/cmd1/cmd2 Address Error Flag
            Scaler32SetBit(PA20003_50_RBUS2DDR_ERR_SRC_CTRL, ~(_BIT16 | _BIT8 | _BIT0), (_BIT16 | _BIT8 | _BIT0));
            break;
#endif
#endif
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : CPU32 Related Interrupt Process(WDT/SB2 Bus Error/CPU Communication)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuCtrlBusError_Handler(void)
{
    // Check RXI-300 Error Log
#if(_HW_CPU32_RXI300_GEN == _RXI300_HW_GEN_0)
    if(Scaler32GetBit(PA40002_30_ELR_I_CODE, _BIT(7, 0)) != 0)
#endif
#if(_HW_CPU32_RXI300_GEN == _RXI300_HW_GEN_1)
    if((Scaler32GetBit(PA40002_30_ELR_1_CODE, _BIT(7, 0)) != 0) ||
       (Scaler32GetBit(PA40002_70_ELR_2_CODE, _BIT(7, 0)) != 0) ||
       (Scaler32GetBit(PA40002_B0_ELR_3_CODE, _BIT(7, 0)) != 0))
#endif
    {
        // RXI-300 Bus R/W Error Happened
        ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_RXI300_RW_FAIL);
    }

    // Check RXI-300 Bus Timeout
    if(Scaler32GetBit(PA40010_94_CPU1_RXI300_TO_CTRL1, _BIT0) == _BIT0)
    {
        // RXI-300 Bus Timeout Error Happened
        ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_RXI300_TIMEOUT);
    }

#if((_SCPU_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
    if((MCU_FDED_SB2_TIMEOUT_INTSTAT & _BIT1) == _BIT1)
    {
        // sb2_iva_int_en is 1

        // KCPU SB2 Debug Trap Process
        if(ScalerBusSb2KcpuTrapAddressIntGetStatus() != 0)
        {
            // KCPU access Debug Address Range
            ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_SB2_KCPU_DEBUG_TRAP);
        }

        // Check Non-Secure CPU Access Secure Region
        if(ScalerBusSb2ScpuIllegalAccessSecurRegionIntGetStatus() != 0)
        {
            // SCPU access Secure Region
            ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_SB2_SCPU_ACCESS_SECURE_REGION);
        }

        // Check SB2 Bus Timeout INT
        if(GET_SB2_TIMEOUT_INT_FLAG() != 0)
        {
            ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_SB2_BUS_TIMEOUT);
        }
    }

    if(ScalerBusSb2KcpuInvalidAccessIntGetStatus() != 0)
    {
        // SB2_KCPU_RW_RBUS_TIMEOUT
        // SB2_KCPU_RW_RBUSD_TIMEOUT
        // KCPU access invalid address
        // include BW8_RBUS_INVALID_ADDR
        ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_SB2_KCPU_ACCESS_INVALID_ADDR);
    }

    if((ScalerBusScpuWrapMemTrashDbgIntGetStatus() != 0) || (ScalerBusScpuWrapMemTrashDbgNegIntGetStatus() != 0))
    {
        // USE SCPU_Wrapper Memory Trash INT for TR9 PMP enhance
        ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_SCPU_WRAPPER_MEM_TRASH);
    }

    // Check CPU32 Watchdog Timeout INT
    if(GET_SCPU_WD_IRQ() == _TRUE)
    {
        // Receive CPU32 Watch Dog Timeout Event
        ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_SCPU_WDT_TIMEOUT);
    }
#endif
}
