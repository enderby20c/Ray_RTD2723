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
// ID Code      : SysIntSecondCpu.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SYSTEM_INT__

#include "SysInclude.h"
#include "Interrupt/SysInt.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_IS_MAIN_PROCESS_CPU == _FALSE)
//--------------------------------------------------
// Description  : SW INT0 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntSecondCpuSw0IRQHandler(void)
{
    CLEAR_SW_INT0();

    // Pending System Service Handler
    PendSV_Handler();
}

//--------------------------------------------------
// Description  : SW INT1 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntSecondCpuSw1IRQHandler(void)
{
    CLEAR_SW_INT1();
}

//--------------------------------------------------
// Description  : HW INT0 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntSecondCpuHw0IRQHandler(void)
{
    DWORD ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();

#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_TIMER2) == _TRUE)
    {
        // 05:Timer2 Interrupt(WDT Event)
        SysIntTimer2_IRQHandler();
    }
#endif

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_CPU_NOTIFY) == _TRUE)
    {
        // CPU Notify INT
        SysIntSecondCpuNotifyIRQHandler();
    }
#endif
}

//--------------------------------------------------
// Description  : HW INT1 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntSecondCpuHw1IRQHandler(void)
{
    DWORD ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();

#if((_HW_CPU32_BW32_SUPPORT == _ON) || (_HW_CPU32_RBUS2DDR_SUPPORT == _ON))
    // 02:BW32/RBUS2DDR Interrupt
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_BW32) == _TRUE)
    {
#if(_HW_CPU32_BW32_SUPPORT == _ON)
        ScalerBW32_IRQHandler();
#endif

#if(_HW_CPU32_RBUS2DDR_SUPPORT == _ON)
        ScalerRBusToDdr_IRQHandler();
#endif
    }
#endif

#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_COPROCESSOR)
#if(((_COLOR_IP_LOCAL_DIMMING == _ON) && (_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)) || (_GOSD_SUPPORT == _ON))
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_SCALER_OTHER) == _TRUE)
    {
        // Other HW INT
#if((_COLOR_IP_LOCAL_DIMMING == _ON) && (_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE))
        // LocalDimming Pwm2Spi SRAM Mode TX done
        ScalerColorLDPwmToSpiSramModeTxDone_Handler();
#endif

#if(_GOSD_SUPPORT == _ON)
        ScalerGosdSeDone_Handler();
#endif
    }
#endif
#endif

#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
#if(_PROMOTE_DDC_INT_TO_HW4_INT_LVL == _OFF)
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_DDC) == _TRUE)
    {
        // 11:DW8051 DDC Interrupt
        SysIntDdc_IRQHandler();
    }
#endif

#if(_HW_IIC_1_SUPPORT == _ON)
#if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_I2CM) == _TRUE)
    {
        // 09:I2CM Interrupt
        SysIntI2CM_IRQHandler();
    }
#endif
#endif

    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_TIMER0) == _TRUE)
    {
        // 03:Timer0 Interrupt
        SysIntTimer0_IRQHandler();
    }

    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_TIMER1) == _TRUE)
    {
        // 04:Timer1 Interrupt
        SysIntTimer1_IRQHandler();
    }

#if(_UART_SUPPORT == _ON)
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_DW_UART) == _TRUE)
    {
        // 06:DW_UART Interrupt
        SysIntExtUart_IRQHandler();
    }
#endif
#endif
}

//--------------------------------------------------
// Description  : HW INT2 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntSecondCpuHw2IRQHandler(void)
{
#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
    DWORD ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();

#if(_ENABLE_KCPU_SCALER_OTHER_INT == _ON)
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_SCALER_OTHER) == _TRUE)
    {
        // Other HW INT
#if((_COLOR_IP_LOCAL_DIMMING == _ON) && (_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE))
        // LocalDimming Pwm2Spi SRAM Mode TX done
        ScalerColorLDPwmToSpiSramModeTxDone_Handler();
#endif

#if(_GOSD_SUPPORT == _ON)
        ScalerGosdSeDone_Handler();
#endif

#if((_AUDIO_SUPPORT == _ON) && (_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE))
        // Audio TTS Handler
        ScalerAudioTtsIntHandler_EXINT0();
#endif // End of #if((_AUDIO_SUPPORT == _ON) && (_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE))

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
        ScalerIRHWModeIntHandler_EXINT0();
#endif

        ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
    }
#endif

    if((ulPendingFlags & (_IRQ_MASK_ADC | _IRQ_MASK_PDCC_UNION | _IRQ_MASK_ECDSA_PMCI2C_BB | _IRQ_MASK_SCALER_ALL_UNION)) != 0)
    {
        SysInt0Proc_EXINT0();

        ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
    }
#endif
}

//--------------------------------------------------
// Description  : HW INT3 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntSecondCpuHw3IRQHandler(void)
{
#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
    DWORD ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();

    ulPendingFlags = ulPendingFlags;

#if(_USB3_REPEATER_SUPPORT == _ON)
    // ReDriver Handler
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_REDRIVER) == _TRUE)
    {
        SysInt3Proc_EXINT3();
    }
#endif
#endif
}

//--------------------------------------------------
// Description  : HW INT4 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntSecondCpuHw4IRQHandler(void)
{
    // Reserved
    DWORD ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();

#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
#if(_PROMOTE_DDC_INT_TO_HW4_INT_LVL == _ON)
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_DDC) == _TRUE)
    {
        // 11:DW8051 DDC Interrupt
        SysIntDdc_IRQHandler();
    }
#endif
#endif

    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_SCALER_ERROR) == _TRUE)
    {
#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
        ScalerGlobalPreventGarbageByBacklight_EXINT0();
#endif
#endif

        SysIntSecondCpuScalerErrorIRQHandler();
    }
}

//--------------------------------------------------
// Description  : HW INT5 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntSecondCpuHw5IRQHandler(void)
{
#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
    // 1ms constant int handler
    SysTick_Handler();
#endif
}

//--------------------------------------------------
// Description  : Scaler Error Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntSecondCpuScalerErrorIRQHandler(void)
{
#if(_SCPU_SUPPORT == _ON)
    // SB2 DebugTrap INT
    if(ScalerBusSb2ScpuTrapAddressIntGetStatus() != 0)
    {
        // SCPU access Debug Address Range
        ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_SB2_SCPU_ACCESS_DBG_TRAP_ADDR);
    }
#endif
}

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
//--------------------------------------------------
// Description  : CPU Notify Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntSecondCpuNotifyIRQHandler(void)
{
    if(ScalerMiscCtrlChkNotifyFromKCPU() != 0)
    {
        // Ack NotifyFromKCPU int flag
        ScalerMiscCtrlAckNotifyFromKCPU();

        // Process Fast Response Cmd
        if(g_stCpuSyncToScpuCmd.stCmdHeader.ucCmdSeqNum != g_stCpuSyncToScpuCmdReply.ucAckCmdSeqNum)
        {
            switch(GET_KCPU_NOTIFY_INT_CMD_TYPE())
            {
#if(_LOCAL_DIMMING_FUNCTION == _ON)
                case _SCALER_CPU_SYNC_COLOR_LOCAL_DIMMING:
                    UserCommonColorLocalDimmingSyncToScpuHandler();
                    ACK_KCPU_NOTIFY_INT_CMD();
                    break;
#endif

#if(_GOSD_SUPPORT == _ON)
                case _SCALER_CPU_SYNC_GOSD_CONTINUOUS:
                {
                    ScalerGosdContinuousProc();
                    ACK_KCPU_NOTIFY_INT_CMD();
                    break;
                }
                case _SCALER_CPU_SYNC_GOSD_CONTINUOUS_SET_STEP:
                    ScalerGosdContinuousSetStepProc();
                    ACK_KCPU_NOTIFY_INT_CMD();
                    break;

                case _SCALER_CPU_SYNC_GOSD_CONTINUOUS_STEP_CHANGE_POSITION:
                    ScalerGosdContinuousStepChangePositionProc();
                    ACK_KCPU_NOTIFY_INT_CMD();
                    break;

                case _SCALER_CPU_SYNC_GOSD_SET_STATUS:
                    GOSD_SET_SURFACE_STATUS(g_stCpuSyncToScpuCmd.unCmdBody.stCpuSyncGosdSetSurfaceStatusCmd.ulSurfaceId, g_stCpuSyncToScpuCmd.unCmdBody.stCpuSyncGosdSetSurfaceStatusCmd.ucStatus);
                    ACK_KCPU_NOTIFY_INT_CMD();
                    break;

#endif // #if(_GOSD_SUPPORT == _ON)
                default:
                    if(ScalerScpuSyncIntFastCommHandler() == _FALSE)
                    {
                        // Set CPU Communication Defer Process Flag,will be process in mainloop
                        SET_KCPU_NOTIFY_INT_MORE_PROCESS_FLAG();
                    }
                    break;
            }
        }
    }
}
#endif  // End of #if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))

//--------------------------------------------------
// Description  : PendSV callback
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntSecondCpuPendSVCallback(void)
{
    // Process Timer Event
#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
    while(ScalerCpuHalCheckMainCpuPendSVEventCnt() == _TRUE)
    {
#if(_ADVANCED_HDR10_SUPPORT == _ON)
        ScalerColorAdvancedHDR10MainCpuPendSVCallback();
#endif

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE) && (_LOCAL_DIMMING_FUNCTION == _ON) && (_SCPU_SUPPORT == _ON))
        UserCommonColorLocalDimmingMainCpuPendSVCallback();
#endif
    }
#endif

#if(_SCPU_SUPPORT == _ON)
    // Process Timer Event
    while(ScalerCpuHalCheckSecondCpuPendSVEventCnt() == _TRUE)
    {
#if(_GOSD_SUPPORT == _ON)
        ScalerGosdDecompressPollingDoneProc(_SCPU_SWIRQ_TIMEOUT_GOSD_DECOMPRESS);
#endif
#if(_ADVANCED_HDR10_SUPPORT == _ON)
        UserCommonColorAdvancedHDR10SecondCpuPendSVCallback();
#endif
    }
#endif
}
#endif // End of #if(_IS_MAIN_PROCESS_CPU == _FALSE)
