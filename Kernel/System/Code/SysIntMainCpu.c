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
// ID Code      : SysIntMainCpu.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SYSTEM_INT__

#include "SysInclude.h"
#include "Interrupt/SysInt.h"


#if(_IS_MAIN_PROCESS_CPU == _TRUE)
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
// Description  : SW INT0 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntMainCpuSw0IRQHandler(void)
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
void SysIntMainCpuSw1IRQHandler(void)
{
    CLEAR_SW_INT1();
}

//--------------------------------------------------
// Description  : HW INT0 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntMainCpuHw0IRQHandler(void)
{
    DWORD ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();

    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_TIMER2) == _TRUE)
    {
#if((_SCPU_SUPPORT == _ON) && (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
        if(ScalerCpuCtrlCheckScpuActive() == _FALSE)
#endif
        {
            // 05:Timer2 Interrupt(WDT Event)
            SysIntTimer2_IRQHandler();
        }
    }

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_CPU_NOTIFY) == _TRUE)
    {
        // Check CPU Communication INT
        if(CHK_SCPU_NOTIFY_INT_HAPPEN() == _TRUE)
        {
            // Clear IRQ Flag
            ACK_SCPU_NOTIFY_INT_FLAG();

            // 00:CPU Notify Interrupt
            if((SysIntMainCpuNotifyIRQHandler(GET_SCPU_NOTIFY_INT_CMD_TYPE()) == _TRUE) ||
               (ScalerCpuSyncNotifyIntHandler(GET_SCPU_NOTIFY_INT_CMD_TYPE()) == _TRUE))
            {
                // Reply Ack
                ACK_SCPU_NOTIFY_INT_CMD();
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : HW INT1 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntMainCpuHw1IRQHandler(void)
{
    // Other HW INT
    DWORD ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();

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
#if((_COLOR_IP_LOCAL_DIMMING == _ON) && (_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE))
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_SCALER_OTHER) == _TRUE)
    {
        // Other HW INT
// #if((_COLOR_IP_LOCAL_DIMMING == _ON) && (_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE))
        // LocalDimming Pwm2Spi SRAM Mode TX done
        ScalerColorLDPwmToSpiSramModeTxDone_Handler();
// #endif
    }
#endif
}

//--------------------------------------------------
// Description  : HW INT2 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntMainCpuHw2IRQHandler(void)
{
    // DP_HIGH/PDCC_HIGH/HDMI_HIGH Handler
    DWORD ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();

#if((_SCPU_SUPPORT == _ON) && (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
    if(ScalerCpuCtrlCheckScpuActive() == _FALSE)
#endif
    {
#if(_ENABLE_KCPU_SCALER_OTHER_INT == _ON)
        if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_SCALER_OTHER) == _TRUE)
        {
            // Other HW INT
#if((_AUDIO_SUPPORT == _ON) && (_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE))
            // Audio TTS Handler
            ScalerAudioTtsIntHandler_EXINT0();
#endif // End of #if((_AUDIO_SUPPORT == _ON) && (_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE))

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
            ScalerIRHWModeIntHandler_EXINT0();
#endif

#if((_COLOR_IP_LOCAL_DIMMING == _ON) && (_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE))
            // LocalDimming Pwm2Spi SRAM Mode TX done
            ScalerColorLDPwmToSpiSramModeTxDone_Handler();
#endif

#if((_GOSD_SUPPORT == _ON) && (_GOSD_FW_MODE == _GOSD_FW_ONE_CPU_MODE))
            ScalerGosdSeDone_Handler();
#endif

            ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
        }
#endif

        if((ulPendingFlags & (_IRQ_MASK_ADC | _IRQ_MASK_PDCC_UNION | _IRQ_MASK_TCPM | _IRQ_MASK_ECDSA_PMCI2C_BB | _IRQ_MASK_SCALER_ALL_UNION)) != 0)
        {
            SysInt0Proc_EXINT0();

            ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
        }
    }

    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_SCALER_ERROR) == _TRUE)
    {
        // Scaler Error INT
        SysIntMainCpuScalerErrorIRQHandler();
    }
}

//--------------------------------------------------
// Description  : HW INT3 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntMainCpuHw3IRQHandler(void)
{
    DWORD ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();

    ulPendingFlags = ulPendingFlags;

#if(_USB3_REPEATER_SUPPORT == _ON)
    // ReDriver Handler
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_REDRIVER) == _TRUE)
    {
        SysInt3Proc_EXINT3();
    }
#endif
}

//--------------------------------------------------
// Description  : HW INT4 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntMainCpuHw4IRQHandler(void)
{
    // Reserved
    DWORD ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();

#if(_PROMOTE_DDC_INT_TO_HW4_INT_LVL == _ON)
    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_DDC) == _TRUE)
    {
        // 11:DW8051 DDC Interrupt
        SysIntDdc_IRQHandler();
    }
#endif

    if(CHECK_INT_PENDING_FLAG(ulPendingFlags, _IRQN_SCALER_ERROR) == _TRUE)
    {
        // Scaler Error INT
        SysIntMainCpuScalerErrorIRQHandler();
    }
}

//--------------------------------------------------
// Description  : HW INT5 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntMainCpuHw5IRQHandler(void)
{
    // 1ms constant int handler
    SysTick_Handler();
}

//--------------------------------------------------
// Description  : Scaler Error Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntMainCpuScalerErrorIRQHandler(void)
{
#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
#if((_SCPU_SUPPORT == _ON) && (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
    if(ScalerCpuCtrlCheckScpuActive() == _FALSE)
#endif
    {
        ScalerGlobalPreventGarbageByBacklight_EXINT0();
    }
#endif

    ScalerCpuCtrlBusError_Handler();
}

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
//--------------------------------------------------
// Description  : CPU Communication interrupt Handler
// Input Value  : enumCpuSyncCommand
// Output Value : _TRUE=need execute ACK_SCPU_NOTIFY_INT_CMD()
//--------------------------------------------------
bit SysIntMainCpuNotifyIRQHandler(EnumCpuSyncCommand enumCpuSyncCommand)
{
    switch(enumCpuSyncCommand)
    {
        default:
            // Command need to be advance processed
            return _FALSE;
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : PendSV callback
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntMainCpuPendSVCallback(void)
{
#if((_SCPU_SUPPORT == _ON) && (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
    if(ScalerCpuCtrlCheckScpuActive() == _FALSE)
#endif
    {
        // Process Timer Event
        while(ScalerCpuHalCheckMainCpuPendSVEventCnt() == _TRUE)
        {
#if(_ADVANCED_HDR10_SUPPORT == _ON)
            ScalerColorAdvancedHDR10MainCpuPendSVCallback();
#endif

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE) && (_LOCAL_DIMMING_FUNCTION == _ON) && (_SCPU_SUPPORT == _ON))
            UserCommonColorLocalDimmingMainCpuPendSVCallback();
#endif
        }
    }
}
#endif // End of #if(_IS_MAIN_PROCESS_CPU == _TRUE)

