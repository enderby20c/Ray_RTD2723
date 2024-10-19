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
// ID Code      : SysInt.c No.0000
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
//--------------------------------------------------
// Description  : Separated interrupt 0 Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
static inline void SysInt0SeparatedProc_EXINT0(void)
{
    DWORD ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();

#if(_HDCP_2_2_SUPPORT == _ON)
    bit bHdcpHandlerFinished = _FALSE;
#endif

#if(_DP_SUPPORT == _ON)
    if((ulPendingFlags & _IRQ_MASK_DP_RX_UNION) != 0)
    {
        ScalerDpRxIntHandler_EXINT0();

#if(_HDCP_2_2_SUPPORT == _ON)
        if(bHdcpHandlerFinished == _FALSE)
        {
            ScalerHdcp2IntHandler_EXINT0();
            bHdcpHandlerFinished = _TRUE;
        }
#endif

#if(_DP_USER_INT0_SUPPORT == _ON)
        UserCommonDpIntHandler_EXINT0();
#endif

        ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
    }
#endif

#if(_DSC_DECODER_SUPPORT == _ON)
    if((ulPendingFlags & (_IRQ_MASK_SCALER_OTHER | _IRQ_MASK_TX | _IRQ_MASK_DP_HIGH | _IRQ_MASK_DP_LOW)) != 0)
    {
        ScalerDscDecoderIntHandler_EXINT0();
        ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
    }
#endif

    if((ulPendingFlags & (_IRQ_MASK_TX)) != 0)
    {
#if(_PANEL_STYLE == _PANEL_VBO)
        ScalerDisplayVboTxIntHandler_EXINT0();
#endif

#if(_PANEL_STYLE == _PANEL_DPTX)
#if((_PANEL_DPTX_HPD_DETECT == _ON) && (_PANEL_DPTX_IRQ_HPD_DETECT == _ON))
        ScalerDisplayDpTxIrqIntHandler_EXINT0();
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
        ScalerDpMacTxIntHandle_EXINT0();
#endif
        ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
    }

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
    if((ulPendingFlags & (_IRQ_MASK_IMD_EVENT)) != 0)
    {
        ScalerGlobalDDomainIntHandler_EXINT0();
        ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
    }
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
    if((ulPendingFlags & (_IRQ_MASK_IMD_EVENT)) != 0)
    {
        ScalerColorAdvancedHDR10PCMHLWDBIntHandler_EXINT0();
        ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
    }
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
#if(_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_NONE)
    if((ulPendingFlags & (_IRQ_MASK_ADC)) != 0)
    {
        ScalerMcuAdcLsAdcDetectIntHandler_EXINT0();
        ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
    }
#endif
#endif

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
    if((ulPendingFlags & (_IRQ_MASK_ADC | _IRQ_MASK_PDCC_UNION | _IRQ_MASK_ECDSA_PMCI2C_BB)) != 0)
    {
        ScalerTypeCIntHandler_EXINT0();
        ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
    }
#endif

#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
    if((ulPendingFlags & _IRQ_MASK_TCPM) != 0)
    {
        ScalerTypeCTcpmIntHandler_EXINT0();
        ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
    }
#endif
#endif

#if(_HDMI_SUPPORT == _ON)
#if(_HDMI_CEC_SUPPORT == _ON)
#if(_HW_CEC_IRQ_GROUP == _HW_CEC_IRQ_SCALER_OTHER)
    if((ulPendingFlags & (_IRQ_MASK_SCALER_OTHER)) != 0)
#else // (_HW_CEC_IRQ_GROUP == _HW_CEC_IRQ_HDMI)
    if((ulPendingFlags & (_IRQ_MASK_HDMI_LOW)) != 0)
#endif
    {
        ScalerCecIntHandler_EXINT0();
        ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
    }
#endif

    if((ulPendingFlags & (_IRQ_MASK_HDMI_HIGH | _IRQ_MASK_HDMI_LOW)) != 0)
    {
#if(_HDCP_2_2_SUPPORT == _ON)
        if(bHdcpHandlerFinished == _FALSE)
        {
            ScalerHdcp2IntHandler_EXINT0();
            bHdcpHandlerFinished = _TRUE;
            ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
        }
#endif

#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
        ScalerHdmiArcTxHighIntHandler_EXINT0(GET_POWER_STATUS());
        ScalerHdmiArcTxLowIntHandler_EXINT0(GET_POWER_STATUS());
#endif

        if((ulPendingFlags & _IRQ_MASK_HDMI_HIGH) != 0)
        {
            ScalerTmdsMacRxHighIntHandler_EXINT0(GET_POWER_STATUS());
        }

        if((ulPendingFlags & _IRQ_MASK_HDMI_LOW) != 0)
        {
            ScalerTmdsMacRxLowIntHandler_EXINT0(GET_POWER_STATUS());
        }

        ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
    }
#endif

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
    if((ulPendingFlags & (_IRQ_MASK_IMD_EVENT | _IRQ_MASK_SCALER_ERROR)) != 0)
    {
        ScalerGlobalIDomainIntHandler_EXINT0();
        ulPendingFlags = CPU32_GET_INT_PENDING_STATUS();
    }
#endif
}

//--------------------------------------------------
// Description  : Interrupt 0 Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysInt0Proc_EXINT0(void)
{
#if(_DP_SUPPORT == _ON)
    ScalerDpAuxRxEnterIntSetting_EXINT0();

    if(ScalerDpAuxRxJudgeHandler_EXINT0() == _TRUE)
    {
        ScalerDpAuxRxExitIntSetting_EXINT0();

        return;
    }
#endif

    SysInt0SeparatedProc_EXINT0();

#if(_DP_SUPPORT == _ON)
    ScalerDpAuxRxExitIntSetting_EXINT0();
#endif
}

//--------------------------------------------------
// Description  : Interrupt 1 Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntDdc_IRQHandler(void)
{
#if(_HDMI_SUPPORT == _ON)
    ScalerTmdsMacRxDdcDetect();
#endif

#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
    if(UserCommonFwUpdateGetStatus() == _TRUE)
    {
        UserCommonFwUpdateIntProc();
    }
#endif

#if((_DEBUG_MESSAGE_SUPPORT == _ON) ||\
    (_DDCCI_CODE_REDUCTION == _ON))
    ScalerDebugIntProc();
#else
    if(UserCommonDdcciGetStatus() == _TRUE)
    {
        UserCommonDdcciIntGetData();
    }
    else
    {
        ScalerDebugIntProc();
    }
#endif

#if(_AUTO_TEST_SUPPORT == _ON)
    SysATIntProc();
#endif
}

#if(_HW_IIC_1_SUPPORT == _ON)
#if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
//--------------------------------------------------
// Description  : Interrupt 1 Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntI2CM_IRQHandler(void)
{
    // I2C_1 Slave Int Handler : Get I2C_1 Slave Data
    ScalerMcuHwIIC1SlaveHandler_EXINT1();
}
#endif
#endif

#if(_USB3_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Interrupt 3 Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysInt3Proc_EXINT3(void)
{
    CLEAR_INTERRUPT_FLAG(_INT_EXINT_3);

#if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
    ScalerUsb3RetimerMac0IntHandler_EXINT3(GET_POWER_STATUS());
#elif(_USB3_REDRIVER_MAC0_SUPPORT == _ON)
    ScalerUsb3RedriverMac0IntHandler_EXINT3();
#endif

#if(_USB3_RETIMER_MAC1_SUPPORT == _ON)
    ScalerUsb3RetimerMac1IntHandler_EXINT3();
#elif(_USB3_REDRIVER_MAC1_SUPPORT == _ON)
    ScalerUsb3RedriverMac1IntHandler_EXINT3();
#endif
}
#endif

#if((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
//--------------------------------------------------
// Description  : 32bits Timer0 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntTimer0_IRQHandler(void)
{
    if(ScalerTimerGetINTFlag(_CPU_TIMER_0) != 0)
    {
        // Ack Timer0 INT flag
        ScalerTimerAckINTFlag(_CPU_TIMER_0);

        // TODO:: add timer0 INT process here
#if(_INSTANT_TIMER_EVENT_0 == _ON)
        SysIntTimer0Proc_T0INT();
#endif
    }
}

//--------------------------------------------------
// Description  : 32bits Timer1 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntTimer1_IRQHandler(void)
{
    if(ScalerTimerGetINTFlag(_CPU_TIMER_1) != 0)
    {
        // Ack Timer1 INT flag
        ScalerTimerAckINTFlag(_CPU_TIMER_1);

        // TODO:: add timer1 INT process here
#if(_INSTANT_TIMER_EVENT_1 == _ON)
        SysIntTimer1Proc_T1INT();
#endif
    }
}

//--------------------------------------------------
// Description  : 32bits Timer2 Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntTimer2_IRQHandler(void)
{
    if(ScalerTimerGetINTFlag(_CPU_TIMER_2) != 0)
    {
        // WDT Timer(Timer2) Event
        SysIntTimerWDProc_WDINT();
    }
}
#endif

#if(_UART_SUPPORT == _ON)
//--------------------------------------------------
// Description  : External UART Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntExtUart_IRQHandler(void)
{
#if((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON))
    if(ScalerMcuUartExt0CheckIntID() == _UART_INT_ID_RX_DATA_RDY)
    {
        UserInterfaceUartExt0IntHandler();
    }
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON))
    if(ScalerMcuUartExt1CheckIntID() == _UART_INT_ID_RX_DATA_RDY)
    {
        UserInterfaceUartExt1IntHandler();
    }
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON))
    if(ScalerMcuUartExt2CheckIntID() == _UART_INT_ID_RX_DATA_RDY)
    {
        UserInterfaceUartExt2IntHandler();
    }
#endif
}
#endif

//--------------------------------------------------
// Description  : Timer0 Int Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntTimer0Proc_T0INT(void)
{
#if(_INSTANT_TIMER_EVENT_0 == _ON)
    UserInterfaceTimer0InstantAccess_T0INT();
#endif
}

//--------------------------------------------------
// Description  : Timer1 Int Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntTimer1Proc_T1INT(void)
{
#if(_INSTANT_TIMER_EVENT_1 == _ON)
    UserInterfaceTimer1InstantAccess_T1INT();
#endif
}

//--------------------------------------------------
// Description  : Timer2 Int Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntTimer2Proc_T2INT(void)
{
#if(_DP_SUPPORT == _ON)
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRxDpcdIrqProtect_T2INT();
#endif
#endif

    // Clear watchdog
    CLR_MCU_WATCH_DOG();

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _OFF)

    SET_TIMER2_ALL_INT_STATUS(_TRUE);

    // Timer Counter
    g_usTimerCounter = g_usTimerCounterDoubleBuffer;
    g_usTimerCounterDoubleBuffer += 1;

#if(_TIME_CURSOR_SUPPORT == _ON)
    g_usTimerMeasureCounter += 1;
#endif

#else

    if(g_ucTimerQuarterCount >= 3)
    {
        g_ucTimerQuarterCount = 0;

        SET_TIMER2_ALL_INT_STATUS(_TRUE);

        // Timer Counter
        g_usTimerCounter = g_usTimerCounterDoubleBuffer;
        g_usTimerCounterDoubleBuffer += 1;

#if(_TIME_CURSOR_SUPPORT == _ON)
        g_usTimerMeasureCounter += 1;
#endif
    }
    else
    {
        g_ucTimerQuarterCount++;
    }

    UserInterfaceTimer2InstantAccess_T2INT();

#endif

#if((_DP_SUPPORT == _ON) && (_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE))
    ScalerDpRxHpdIrqAssertTimer2EventProc_T2INT();
#endif

#if(_DP_SUPPORT == _ON)
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRxDpcdIrqProtect_T2INT();
#endif
#endif
}

//--------------------------------------------------
// Description  : WD Timer Int Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntTimerWDProc_WDINT(void)
{
    ScalerTimerWDEventProc_WDINT();
}

//--------------------------------------------------
// Description  : SysTick Handler CallBack
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntSystickCallback(void)
{
    ScalerWdtClearWDT();

#if((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
    SysIntTimer2Proc_T2INT();
    // set 1ms timer handler
#endif
}

//--------------------------------------------------
// Description  : PendSV callback
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntPendSVCallback(void)
{
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    SysIntMainCpuPendSVCallback();
#else
    SysIntSecondCpuPendSVCallback();
#endif
}

//--------------------------------------------------
// Description  : CPU Watch Dog Timer Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntWdt_IRQHandler(void)
{
    if(ScalerWdtGetWdtNmiFlag() != 0)
    {
        // Ack WDT Flag
        ScalerWdtAckWdtNmiFlag();

        // Clear WDT Counter(used for WDT NMI and Reset function )
        ScalerWdtClearWDT();
    }
}

//--------------------------------------------------
// Description  : SCPU MEI Exception Handler.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysIntMEI_IRQHandler(void)
{
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_KCPU_MEI);
#else
#if(_HW_CPU32_BW32_SUPPORT == _ON)
    // BW32_INVALID_ADDR_TO_SB2
    ScalerBW32Error_Handler();
#endif

#if(_HW_CPU32_RBUS2DDR_SUPPORT == _ON)
    // RBUS2DDR_INVALID_ADDR_TO_SB2
    ScalerRBusToDdrError_Handler();
#endif

    ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_SCPU_MEI);
#endif
}

