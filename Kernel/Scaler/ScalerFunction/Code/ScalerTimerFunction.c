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
// ID Code      : ScalerTimerFunction.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TIMERFUNCTION__

#include "ScalerFunctionInclude.h"
#include "TimerFunction/ScalerTimerFunction.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_RECORD_TIMER_SUPPORT == _ON)
WORD g_usTimerRecordStartTime;
#endif

volatile bit g_bTimer2NotifyInt = _FALSE;

#if(_SCPU_SUPPORT == _ON)
volatile bit g_bTimer2ScpuNotifyInt = _FALSE;
#endif

StructTimerEventTableType g_pstTimerEvent[_TIMER_EVENT_COUNT];

volatile WORD data g_usTimerCounter;
volatile WORD data g_usTimerCounterDoubleBuffer = 1;

#if(_TIME_CURSOR_SUPPORT == _ON)
volatile WORD data g_usTimerMeasureCounter;
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
volatile BYTE data g_ucTimerQuarterCount;
#endif

DWORD g_ulTimerPrevWdtEventProcessTime;
volatile DWORD g_ulTimerChangeClkCurrentTime;
volatile DWORD g_ulTimerWdtRefClk = _HW_CPU32_CLK_SRC_EXTAL / _FLASH_CLK_IN_DIV;
volatile DWORD g_ulTimerPrevWdtRefClk = _HW_CPU32_CLK_SRC_EXTAL / _FLASH_CLK_IN_DIV;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Scaler Timer Event Process
// Input Value  : enumEventID --> Event to be processed
// Output Value : None
//--------------------------------------------------
void ScalerTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if(_HDMI20_SUPPORT == _ON)

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_HDMI2_FORMAT_RESET_WAIT:
            CLR_TMDS_MAC_RX3_HDMI20_FORMAT_RESET_WAITING();
            break;

        case _SCALER_TIMER_EVENT_RX3_HDMI2_SCRAMBLE_DETECT_TIMEOUT:
            ScalerTmdsMacRx3ScrambleDetectTimeoutTimerEvent();
            break;
#endif

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX4_HDMI2_FORMAT_RESET_WAIT:
            CLR_TMDS_MAC_RX4_HDMI20_FORMAT_RESET_WAITING();
            break;

        case _SCALER_TIMER_EVENT_RX4_HDMI2_SCRAMBLE_DETECT_TIMEOUT:
            ScalerTmdsMacRx4ScrambleDetectTimeoutTimerEvent();
            break;
#endif

#endif

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_TMDS_VIDEO_DETECT:
            ScalerTmdsMacRx3TMDSVideoDetectEvent();
            break;

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_TMDS_HPD_LOW_FINISH:
            ScalerTmdsMacRx3HotPlugHighProc(0);

            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
            {
                // Restore Slave Address & Z0 Status
                ScalerTmdsMacRx3AfterHotPlugEventProc(_TRUE);
            }
            else
            {
                // Restore Slave Address
                ScalerTmdsMacRx3AfterHotPlugEventProc(_FALSE);
            }

            // Need to do Zo toggle
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
            {
                ScalerTimerActiveTimerEvent(GET_HDMI_Z0_HPD_INTERVAL(), _SCALER_TIMER_EVENT_RX3_TMDS_HPD_Z0_INTERVAL_FINISH);
            }
            // HPD event is finished
            else
            {
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
                if(GET_TMDS_MAC_RX3_TOGGLE_Z0_EVENT() == _TRUE)
                {
                    CLR_TMDS_MAC_RX3_TOGGLE_Z0();
                    CLR_TMDS_MAC_RX3_TOGGLE_Z0_EVENT();
                }
#endif

                CLR_TMDS_MAC_RX3_HPD_TRIGGER_EVENT();
                CLR_HDMI_MAC_RX3_INTERFACE_SWITCHING();
                CLR_TMDS_MAC_RX3_HPD_TIMER_EVENT_TOGGLING_CABLE_ON();

                if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
                {
                    ScalerTmdsMacRxPowerProc(ScalerTmdsMacRxRxDxMapping(_RX3), _POWER_ACTION_OFF_TO_NORMAL);

                    ScalerGDIPhyRxPowerProc(ScalerTmdsMacRxRxDxMapping(_RX3), _POWER_ACTION_OFF_TO_NORMAL);
                }

                ScalerTmdsMacRx3InterruptInitial();
            }
            break;

        case _SCALER_TIMER_EVENT_RX3_TMDS_HPD_Z0_INTERVAL_FINISH:

            // To do HPD Toggle
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE)
            {
                // HPD Low
                ScalerTmdsMacRx3HotPlugLowProc();

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
                // HPD Low then Reset Scramble Status
                ScalerTmdsMacRx3ScrambleStatusReset();
#endif

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                // HPD Low then Reset Hdmi2.1
                ScalerHdmiFrlMacRx3ResetProc();
#endif

                if(GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_NORMAL)
                {
                    ScalerTimerActiveTimerEvent(GET_HDMI_HOTPLUG_TIME(), _SCALER_TIMER_EVENT_RX3_TMDS_HPD_LOW_FINISH);
                }
                else if(GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22)
                {
                    ScalerTimerActiveTimerEvent(_TMDS_HDCP_2_2_HPD_TIME, _SCALER_TIMER_EVENT_RX3_TMDS_HPD_LOW_FINISH);
                }
                else if(GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_ACER)
                {
                    ScalerTimerActiveTimerEvent(_TMDS_ACER_HPD_TIME, _SCALER_TIMER_EVENT_RX3_TMDS_HPD_LOW_FINISH);
                }
                else if((GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_KEEP_ACTIVE) || (GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
                {
                    ScalerTimerActiveTimerEvent(_TMDS_EDID_SWITCH_HPD_TIME, _SCALER_TIMER_EVENT_RX3_TMDS_HPD_LOW_FINISH);
                }
                else
                {
                    ScalerTimerActiveTimerEvent(GET_HDMI_HOTPLUG_TIME(), _SCALER_TIMER_EVENT_RX3_TMDS_HPD_LOW_FINISH);
                }
            }

            // To do Z0 Toggle
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
            {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                // Backup and Disable Main link related IRQ before Z0 off to prevetn FRL 8/10/12G signal unstable
                ScalerHdmiFrlMacRx3IrqBackupBeforeZ0Off();
#endif

                // Disable Z0
                ScalerTmdsPhyRxSetZ0Status(ScalerTmdsMacRxRxDxMapping(_RX3), _DISABLE);

                ScalerTimerActiveTimerEvent(GET_HDMI_Z0_LOW_PERIOD(), _SCALER_TIMER_EVENT_RX3_TMDS_Z0_LOW_FINISH);
            }

            break;

        case _SCALER_TIMER_EVENT_RX3_TMDS_Z0_LOW_FINISH:
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
            {
                DebugMessageRx3("Rx3 HPD Toggle!!", 0);

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
                if(GET_TMDS_MAC_RX3_TOGGLE_Z0_EVENT() == _TRUE)
                {
                    CLR_TMDS_MAC_RX3_TOGGLE_Z0();
                    CLR_TMDS_MAC_RX3_TOGGLE_Z0_EVENT();
                }
#endif
                CLR_TMDS_MAC_RX3_HPD_TRIGGER_EVENT();
                CLR_HDMI_MAC_RX3_INTERFACE_SWITCHING();
                CLR_TMDS_MAC_RX3_HPD_TIMER_EVENT_TOGGLING_CABLE_ON();

                ScalerGDIPhyRxPowerProc(ScalerTmdsMacRxRxDxMapping(_RX3), _POWER_ACTION_OFF_TO_NORMAL);

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                // Restore Main link related IRQ After Z0 on
                ScalerHdmiFrlMacRx3IrqRestoreAfterZ0On();
#endif

                ScalerTmdsMacRx3InterruptInitial();
            }
            break;
#endif // End of #if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)

#if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX3_TMDS_HPD_LOW_FINISH:
            ScalerTmdsMacRx3HotPlugHighProc(0);

            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
            {
                // Restore Slave Address & Z0 Status
                ScalerTmdsMacRx3AfterHotPlugEventProc(_TRUE);
            }
            else
            {
                // Restore Slave Address
                ScalerTmdsMacRx3AfterHotPlugEventProc(_FALSE);
            }

            // Need to do Z0 toggle
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
            {
                ScalerTimerActiveTimerEvent(GET_HDMI_Z0_HPD_INTERVAL(), _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX3_TMDS_HPD_Z0_INTERVAL_FINISH);
            }
            else
            {
                // Case of "HPD/Z0 At same time" or "Z0 toggle before HPD"
                // Final stage!
                DebugMessageRx3("Rx3 HPD Toggle!! (timer event mode)", 0);

                CLR_TMDS_MAC_RX3_HPD_TRIGGER_EVENT();
                CLR_TMDS_MAC_RX3_ACTIVE_TYPE_HPD_TOGGLING();
                CLR_TMDS_MAC_RX3_HPD_TIMER_EVENT_TOGGLING_CABLE_ON();

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                ScalerHdmiFrlMacRx3RestoreScdcStatus();
#endif

                ScalerTmdsMacRx3InterruptInitial();
            }
            break;

        case _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX3_TMDS_HPD_Z0_INTERVAL_FINISH:

            // To do HPD Toggle
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE)
            {
                // HPD Low
                ScalerTmdsMacRx3HotPlugLowProc();

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
                // HPD Low then Reset Scramble Status
                ScalerTmdsMacRx3ScrambleStatusReset();
#endif

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                // HPD Low then Reset Hdmi2.1
                ScalerHdmiFrlMacRx3ResetProc();
#endif

                if(GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_NORMAL)
                {
                    ScalerTimerActiveTimerEvent(GET_HDMI_HOTPLUG_TIME(), _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX3_TMDS_HPD_LOW_FINISH);
                }
                else if(GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22)
                {
                    ScalerTimerActiveTimerEvent(_TMDS_HDCP_2_2_HPD_TIME, _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX3_TMDS_HPD_LOW_FINISH);
                }
                else if(GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_ACER)
                {
                    ScalerTimerActiveTimerEvent(_TMDS_ACER_HPD_TIME, _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX3_TMDS_HPD_LOW_FINISH);
                }
                else if((GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_KEEP_ACTIVE) || (GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
                {
                    ScalerTimerActiveTimerEvent(_TMDS_EDID_SWITCH_HPD_TIME, _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX3_TMDS_HPD_LOW_FINISH);
                }
                else
                {
                    ScalerTimerActiveTimerEvent(GET_HDMI_HOTPLUG_TIME(), _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX3_TMDS_HPD_LOW_FINISH);
                }
            }

            // To do Z0 Toggle
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
            {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                // Backup and Disable Main link related IRQ before Z0 off to prevetn FRL 8/10/12G signal unstable
                ScalerHdmiFrlMacRx3IrqBackupBeforeZ0Off();
#endif
                // Disable Z0
                ScalerTmdsPhyRxSetZ0Status(ScalerTmdsMacRxRxDxMapping(_RX3), _DISABLE);

                ScalerTimerActiveTimerEvent(GET_HDMI_Z0_LOW_PERIOD(), _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX3_TMDS_Z0_LOW_FINISH);
            }

            break;

        case _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX3_TMDS_Z0_LOW_FINISH:

            // Restore Z0 Status
            ScalerTmdsPhyRxRestoreZ0Status(ScalerTmdsMacRxRxDxMapping(_RX3), g_ucTmdsMacRx3Z0Status);

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            // Restore Main link related IRQ After Z0 on
            ScalerHdmiFrlMacRx3IrqRestoreAfterZ0On();
#endif

            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
            {
                // Final stage!
                DebugMessageRx3("Rx3 HPD Toggle!! (timer event mode)", 0);

                CLR_TMDS_MAC_RX3_HPD_TRIGGER_EVENT();
                CLR_TMDS_MAC_RX3_ACTIVE_TYPE_HPD_TOGGLING();
                CLR_TMDS_MAC_RX3_HPD_TIMER_EVENT_TOGGLING_CABLE_ON();

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                ScalerHdmiFrlMacRx3RestoreScdcStatus();
#endif

                ScalerTmdsMacRx3InterruptInitial();
            }
            else
            {
                // Case of "Z0 toggle before HPD"
                ScalerTimerActiveTimerEvent(GET_HDMI_Z0_HPD_INTERVAL(), _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX3_TMDS_HPD_Z0_INTERVAL_FINISH);
            }
            break;
#endif// End of #if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON)

#endif // End of #if(_D3_HDMI_SUPPORT == _ON)

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX4_TMDS_VIDEO_DETECT:
            ScalerTmdsMacRx4TMDSVideoDetectEvent();
            break;

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX4_TMDS_HPD_LOW_FINISH:
            ScalerTmdsMacRx4HotPlugHighProc(0);

            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
            {
                // Restore Slave Address
                ScalerTmdsMacRx4AfterHotPlugEventProc(_TRUE);
            }
            else
            {
                // Restore Slave Address and Z0 Status
                ScalerTmdsMacRx4AfterHotPlugEventProc(_FALSE);
            }

            // Need to do Zo toggle
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
            {
                ScalerTimerActiveTimerEvent(GET_HDMI_Z0_HPD_INTERVAL(), _SCALER_TIMER_EVENT_RX4_TMDS_HPD_Z0_INTERVAL_FINISH);
            }
            // HPD event is finished
            else
            {
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
                if(GET_TMDS_MAC_RX4_TOGGLE_Z0_EVENT() == _TRUE)
                {
                    CLR_TMDS_MAC_RX4_TOGGLE_Z0();
                    CLR_TMDS_MAC_RX4_TOGGLE_Z0_EVENT();
                }
#endif

                CLR_TMDS_MAC_RX4_HPD_TRIGGER_EVENT();
                CLR_HDMI_MAC_RX4_INTERFACE_SWITCHING();
                CLR_TMDS_MAC_RX4_HPD_TIMER_EVENT_TOGGLING_CABLE_ON();

                if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
                {
                    ScalerTmdsMacRxPowerProc(ScalerTmdsMacRxRxDxMapping(_RX4), _POWER_ACTION_OFF_TO_NORMAL);

                    ScalerGDIPhyRxPowerProc(ScalerTmdsMacRxRxDxMapping(_RX4), _POWER_ACTION_OFF_TO_NORMAL);
                }

                ScalerTmdsMacRx4InterruptInitial();
            }
            break;

        case _SCALER_TIMER_EVENT_RX4_TMDS_HPD_Z0_INTERVAL_FINISH:

            // To do HPD Toggle
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE)
            {
                // HPD Low
                ScalerTmdsMacRx4HotPlugLowProc();

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
                // HPD Low then Reset Scramble Status
                ScalerTmdsMacRx4ScrambleStatusReset();
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                // HPD Low then Reset Hdmi2.1
                ScalerHdmiFrlMacRx4ResetProc();
#endif

                if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_NORMAL)
                {
                    ScalerTimerActiveTimerEvent(GET_HDMI_HOTPLUG_TIME(), _SCALER_TIMER_EVENT_RX4_TMDS_HPD_LOW_FINISH);
                }
                else if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22)
                {
                    ScalerTimerActiveTimerEvent(_TMDS_HDCP_2_2_HPD_TIME, _SCALER_TIMER_EVENT_RX4_TMDS_HPD_LOW_FINISH);
                }
                else if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_ACER)
                {
                    ScalerTimerActiveTimerEvent(_TMDS_ACER_HPD_TIME, _SCALER_TIMER_EVENT_RX4_TMDS_HPD_LOW_FINISH);
                }
                else if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_KEEP_ACTIVE) || (GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
                {
                    ScalerTimerActiveTimerEvent(_TMDS_EDID_SWITCH_HPD_TIME, _SCALER_TIMER_EVENT_RX4_TMDS_HPD_LOW_FINISH);
                }
                else
                {
                    ScalerTimerActiveTimerEvent(GET_HDMI_HOTPLUG_TIME(), _SCALER_TIMER_EVENT_RX4_TMDS_HPD_LOW_FINISH);
                }
            }

            // To do Z0 Toggle
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
            {
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                // Backup and Disable Main link related IRQ before Z0 off to prevetn FRL 8/10/12G signal unstable
                ScalerHdmiFrlMacRx4IrqBackupBeforeZ0Off();
#endif

                // Disable Z0
                ScalerTmdsPhyRxSetZ0Status(ScalerTmdsMacRxRxDxMapping(_RX4), _DISABLE);

                ScalerTimerActiveTimerEvent(GET_HDMI_Z0_LOW_PERIOD(), _SCALER_TIMER_EVENT_RX4_TMDS_Z0_LOW_FINISH);
            }

            break;

        case _SCALER_TIMER_EVENT_RX4_TMDS_Z0_LOW_FINISH:
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
            {
                DebugMessageRx4("Rx4 HPD Toggle!!", 0);

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
                if(GET_TMDS_MAC_RX4_TOGGLE_Z0_EVENT() == _TRUE)
                {
                    CLR_TMDS_MAC_RX4_TOGGLE_Z0();
                    CLR_TMDS_MAC_RX4_TOGGLE_Z0_EVENT();
                }
#endif
                CLR_TMDS_MAC_RX4_HPD_TRIGGER_EVENT();
                CLR_HDMI_MAC_RX4_INTERFACE_SWITCHING();
                CLR_TMDS_MAC_RX4_HPD_TIMER_EVENT_TOGGLING_CABLE_ON();

                ScalerGDIPhyRxPowerProc(ScalerTmdsMacRxRxDxMapping(_RX4), _POWER_ACTION_OFF_TO_NORMAL);

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                // Restore Main link related IRQ After Z0 on
                ScalerHdmiFrlMacRx4IrqRestoreAfterZ0On();
#endif

                ScalerTmdsMacRx4InterruptInitial();
            }
            break;
#endif // End of #if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)

#if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX4_TMDS_HPD_LOW_FINISH:
            ScalerTmdsMacRx4HotPlugHighProc(0);

            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME)
            {
                // Restore Slave Address
                ScalerTmdsMacRx4AfterHotPlugEventProc(_TRUE);
            }
            else
            {
                // Restore Slave Address and Z0 Status
                ScalerTmdsMacRx4AfterHotPlugEventProc(_FALSE);
            }

            // Need to do Z0 toggle
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
            {
                ScalerTimerActiveTimerEvent(GET_HDMI_Z0_HPD_INTERVAL(), _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX4_TMDS_HPD_Z0_INTERVAL_FINISH);
            }
            else
            {
                // Case of "HPD/Z0 At same time" or "Z0 toggle before HPD"
                // Final stage!
                DebugMessageRx4("Rx4 HPD Toggle!! (timer event mode)", 0);

                CLR_TMDS_MAC_RX4_HPD_TRIGGER_EVENT();
                CLR_TMDS_MAC_RX4_ACTIVE_TYPE_HPD_TOGGLING();
                CLR_TMDS_MAC_RX4_HPD_TIMER_EVENT_TOGGLING_CABLE_ON();

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                ScalerHdmiFrlMacRx4RestoreScdcStatus();
#endif
                ScalerTmdsMacRx4InterruptInitial();
            }

            break;

        case _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX4_TMDS_HPD_Z0_INTERVAL_FINISH:

            // To do HPD Toggle
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_Z0_TOGGLE_BEFORE_HPD_TOGGLE)
            {
                // HPD Low
                ScalerTmdsMacRx4HotPlugLowProc();

#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
                // HPD Low then Reset Scramble Status
                ScalerTmdsMacRx4ScrambleStatusReset();
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                // HPD Low then Reset Hdmi2.1
                ScalerHdmiFrlMacRx4ResetProc();
#endif

                if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_NORMAL)
                {
                    ScalerTimerActiveTimerEvent(GET_HDMI_HOTPLUG_TIME(), _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX4_TMDS_HPD_LOW_FINISH);
                }
                else if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_HDCP22)
                {
                    ScalerTimerActiveTimerEvent(_TMDS_HDCP_2_2_HPD_TIME, _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX4_TMDS_HPD_LOW_FINISH);
                }
                else if(GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_ACER)
                {
                    ScalerTimerActiveTimerEvent(_TMDS_ACER_HPD_TIME, _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX4_TMDS_HPD_LOW_FINISH);
                }
                else if((GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_KEEP_ACTIVE) || (GET_TMDS_MAC_RX4_HPD_TRIGGER_EVENT() == _TMDS_MAC_RX_HPD_EDID_SWITCH_RST_TO_SEARCH))
                {
                    ScalerTimerActiveTimerEvent(_TMDS_EDID_SWITCH_HPD_TIME, _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX4_TMDS_HPD_LOW_FINISH);
                }
                else
                {
                    ScalerTimerActiveTimerEvent(GET_HDMI_HOTPLUG_TIME(), _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX4_TMDS_HPD_LOW_FINISH);
                }
            }

            // To do Z0 Toggle
            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
            {
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                // Backup and Disable Main link related IRQ before Z0 off to prevetn FRL 8/10/12G signal unstable
                ScalerHdmiFrlMacRx4IrqBackupBeforeZ0Off();
#endif
                // Disable Z0
                ScalerTmdsPhyRxSetZ0Status(ScalerTmdsMacRxRxDxMapping(_RX4), _DISABLE);

                ScalerTimerActiveTimerEvent(GET_HDMI_Z0_LOW_PERIOD(), _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX4_TMDS_Z0_LOW_FINISH);
            }

            break;

        case _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX4_TMDS_Z0_LOW_FINISH:

            // Restore Z0 Status
            ScalerTmdsPhyRxRestoreZ0Status(ScalerTmdsMacRxRxDxMapping(_RX4), g_ucTmdsMacRx4Z0Status);

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            // Restore Main link related IRQ After Z0 on
            ScalerHdmiFrlMacRx4IrqRestoreAfterZ0On();
#endif

            if(GET_HDMI_Z0_HPD_TYPE() == _HDMI_HPD_TOGGLE_BEFORE_Z0_TOGGLE)
            {
                // Final stage!
                DebugMessageRx4("Rx4 HPD Toggle!! (timer event mode)", 0);

                CLR_TMDS_MAC_RX4_HPD_TRIGGER_EVENT();
                CLR_TMDS_MAC_RX4_ACTIVE_TYPE_HPD_TOGGLING();
                CLR_TMDS_MAC_RX4_HPD_TIMER_EVENT_TOGGLING_CABLE_ON();

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                ScalerHdmiFrlMacRx4RestoreScdcStatus();
#endif

                ScalerTmdsMacRx4InterruptInitial();
            }
            else
            {
                // Case of "Z0 toggle before HPD"
                ScalerTimerActiveTimerEvent(GET_HDMI_Z0_HPD_INTERVAL(), _SCALER_TIMER_EVENT_ACTIVE_TYPE_RX4_TMDS_HPD_Z0_INTERVAL_FINISH);
            }
            break;
#endif // End of #if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON)

#endif // End of #if(_D3_HDMI_SUPPORT == _ON)

#if(_D1_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_D1_TMDS_HPD_ASSERTED:
            PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_D2_TMDS_HPD_ASSERTED:
            PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_D3_TMDS_HPD_ASSERTED:
            PCB_D3_HOTPLUG(_D3_HOT_PLUG_HIGH);
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_D4_TMDS_HPD_ASSERTED:
            PCB_D4_HOTPLUG(_D4_HOT_PLUG_HIGH);
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_D5_TMDS_HPD_ASSERTED:
            PCB_D5_HOTPLUG(_D5_HOT_PLUG_HIGH);
            break;
#endif

#if(_D1_HDMI20_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_HDMI_D1_HPD_5VPIN_CHECK:
            ScalerTmdsMacRxHpd5vPinCheck(_D1_INPUT_PORT);
            break;
#endif

#if(_D2_HDMI20_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_HDMI_D2_HPD_5VPIN_CHECK:
            ScalerTmdsMacRxHpd5vPinCheck(_D2_INPUT_PORT);
            break;
#endif

#if(_D3_HDMI20_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_HDMI_D3_HPD_5VPIN_CHECK:
            ScalerTmdsMacRxHpd5vPinCheck(_D3_INPUT_PORT);
            break;
#endif

#if(_D4_HDMI20_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_HDMI_D4_HPD_5VPIN_CHECK:
            ScalerTmdsMacRxHpd5vPinCheck(_D4_INPUT_PORT);
            break;
#endif

#if(_D5_HDMI20_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_HDMI_D5_HPD_5VPIN_CHECK:
            ScalerTmdsMacRxHpd5vPinCheck(_D5_INPUT_PORT);
            break;
#endif

#if(_HDMI_SUPPORT == _ON)

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_TMDS_HDMI_PACKET_DETECT:
            ScalerTmdsMacRx3HdmiPacketDetectEvent();
            break;

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
        case _SCALER_TIMER_EVENT_RX3_HDMI_ADVANCED_HDR10_DETECT:
            ScalerTmdsMacRx3HdmiAdvancedHdr10DetectEvent();
            break;
#endif

#if(_DM_FUNCTION == _ON)
        case _SCALER_TIMER_EVENT_RX3_HDMI_DM_DETECT:
            ScalerTmdsMacRx3HdmiDmDetectEvent();
            break;
#endif

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_RX3_TMDS_EMP_DETECT:
            ScalerTmdsMacRx3EmpDetectEvent();
            break;
#endif

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_HDMI_FRL_PACKET_DETECT:
            ScalerHdmiFrlMacRx3PacketDetectEvent();
            break;

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
        case _SCALER_TIMER_EVENT_RX3_HDMI_FRL_ADVANCED_HDR10_DETECT:
            ScalerHdmiFrlMacRx3AdvancedHdr10DetectEvent();
            break;
#endif

#if(_DM_FUNCTION == _ON)
        case _SCALER_TIMER_EVENT_RX3_HDMI_FRL_DM_DETECT:
            ScalerHdmiFrlMacRx3HdmiDmDetectEvent();
            break;
#endif

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_RX3_HDMI_FRL_EMP_DETECT:
            ScalerHdmiFrlMacRx3EmpDetectEvent();
            break;
#endif

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_HDMI_FRL_SIGNAL_DETECT:
            ScalerHdmiFrlMacRx3SignalDetectEvent();
            break;
#endif
#endif
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX4_TMDS_HDMI_PACKET_DETECT:
            ScalerTmdsMacRx4HdmiPacketDetectEvent();
            break;

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
        case _SCALER_TIMER_EVENT_RX4_HDMI_ADVANCED_HDR10_DETECT:
            ScalerTmdsMacRx4HdmiAdvancedHdr10DetectEvent();
            break;
#endif

#if(_DM_FUNCTION == _ON)
        case _SCALER_TIMER_EVENT_RX4_HDMI_DM_DETECT:
            ScalerTmdsMacRx4HdmiDmDetectEvent();
            break;
#endif

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_RX4_TMDS_EMP_DETECT:
            ScalerTmdsMacRx4EmpDetectEvent();
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX4_HDMI_FRL_PACKET_DETECT:
            ScalerHdmiFrlMacRx4PacketDetectEvent();
            break;

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
        case _SCALER_TIMER_EVENT_RX4_HDMI_FRL_ADVANCED_HDR10_DETECT:
            ScalerHdmiFrlMacRx4AdvancedHdr10DetectEvent();
            break;
#endif

#if(_DM_FUNCTION == _ON)
        case _SCALER_TIMER_EVENT_RX4_HDMI_FRL_DM_DETECT:
            ScalerHdmiFrlMacRx4HdmiDmDetectEvent();
            break;
#endif

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_RX4_HDMI_FRL_EMP_DETECT:
            ScalerHdmiFrlMacRx4EmpDetectEvent();
            break;
#endif

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX4_HDMI_FRL_SIGNAL_DETECT:
            ScalerHdmiFrlMacRx4SignalDetectEvent();
            break;
#endif
#endif
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TMDS_Z0_POWER_SAVING_TOGGLE_LOW_DUTY:
#if(_D1_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
            {
                ScalerTmdsPhyRxClkLaneZ0HighProc(_D1_INPUT_PORT);
            }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
            {
                ScalerTmdsPhyRxClkLaneZ0HighProc(_D2_INPUT_PORT);
            }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
            {
                ScalerTmdsPhyRxClkLaneZ0HighProc(_D3_INPUT_PORT);
            }
#endif

#if(_D4_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
            {
                ScalerTmdsPhyRxClkLaneZ0HighProc(_D4_INPUT_PORT);
            }
#endif
            break;

        case _SCALER_TIMER_EVENT_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY:

#if(_D1_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
            {
                ScalerTmdsPhyRxClkLaneZ0LowProc(_D1_INPUT_PORT);
            }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
            {
                ScalerTmdsPhyRxClkLaneZ0LowProc(_D2_INPUT_PORT);
            }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
            {
                ScalerTmdsPhyRxClkLaneZ0LowProc(_D3_INPUT_PORT);
            }
#endif

#if(_D4_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
            {
                ScalerTmdsPhyRxClkLaneZ0LowProc(_D4_INPUT_PORT);
            }
#endif
            break;
#endif
#endif // End of #if(_HDMI_SUPPORT == _ON)

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_HDCP2_REAUTH:
#endif
#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX4_HDCP2_REAUTH:
#endif
        ScalerHdcp2ReAuthEvent(enumEventID);
        break;
#endif // End of #if(_TMDS_HDCP_2_2_SUPPORT == _ON)

#if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON))

#if(_DP_AUDIO_RX0_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_AUDIO_RX0_LOAD_STABLE_I_CODE:
            ScalerAudioLoadStableICodeEvent(enumEventID);
            break;
#endif
#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_AUDIO_RX1_LOAD_STABLE_I_CODE:
            ScalerAudioLoadStableICodeEvent(enumEventID);
            break;
#endif
#if(_DP_AUDIO_RX2_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_AUDIO_RX2_LOAD_STABLE_I_CODE:
            ScalerAudioLoadStableICodeEvent(enumEventID);
            break;
#endif
#if(_DP_AUDIO_RX3_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_AUDIO_RX3_LOAD_STABLE_I_CODE:
            ScalerAudioLoadStableICodeEvent(enumEventID);
            break;
#endif
#if(_DP_AUDIO_RX4_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_AUDIO_RX4_LOAD_STABLE_I_CODE:
            ScalerAudioLoadStableICodeEvent(enumEventID);
            break;
#endif

#endif // End of #if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON))

#if(_AUDIO_SUPPORT == _ON)
#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_ENABLE_SPREAD_P_CODE:
            ScalerAudioSpreadPcodeEnable(_AUDIO_FROM_RX3_PORT);
            break;
#endif

        case _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_LOAD_STABLE_I_CODE:
            ScalerAudioLoadStableICodeEvent(enumEventID);
            break;

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_FW_TRACKING_PREPARING:
            ScalerHdmiAudioRx3FwTrackingEventSet();
            break;

        case _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_FW_TRACKING_TIMEOUT:
            ScalerHdmiAudioRx3TimeoutEventSet();
            break;
#endif // End of #if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
#endif // End of #if(_HDMI_AUDIO_RX3_SUPPORT == _ON)

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_HDMI_AUDIO_RX4_ENABLE_SPREAD_P_CODE:
            ScalerAudioSpreadPcodeEnable(_AUDIO_FROM_RX4_PORT);
            break;
#endif

        case _SCALER_TIMER_EVENT_HDMI_AUDIO_RX4_LOAD_STABLE_I_CODE:
            ScalerAudioLoadStableICodeEvent(enumEventID);
            break;

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_HDMI_AUDIO_RX4_FW_TRACKING_PREPARING:
            ScalerHdmiAudioRx4FwTrackingEventSet();
            break;

        case _SCALER_TIMER_EVENT_HDMI_AUDIO_RX4_FW_TRACKING_TIMEOUT:
            ScalerHdmiAudioRx4TimeoutEventSet();
            break;
#endif // End of #if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
#endif // End of #if(_HDMI_AUDIO_RX4_SUPPORT == _ON)

#if(_AUDIO_ARC_SUPPORT == _ON)
#if(_AUDIO_EARC_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_ARC_TX_FORCE_EARC_DISC_INIT_BY_HPD_TOGGLE_TIMEOUT:
            SET_AUDIO_ARC_TX_FORCE_EARC_DISC_INIT_BY_HPD_TOGGLE_TIMEOUT();
            break;
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMEOUT:
            SET_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMEOUT();
            break;
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DP_SUPPORT == _ON)
#if(_D0_DP_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK:

            SET_DP_AUX_RX0_VALID_VIDEO_CHECK();

            break;

        case _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED:

            ScalerDpRxSetHotPlugEvent(_D0_INPUT_PORT, _DP_HPD_ASSERTED);

            break;

        case _SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT:

            if(ScalerDpMacDphyRxHdcpReAuthStatusCheck(_D0_INPUT_PORT) == _FALSE)
            {
                DebugMessageRx0("7. DP HDCP Long HPD", 0);
                ScalerDpRxSetHotPlugEvent(_D0_INPUT_PORT, _DP_HDCP_LONG_HPD_EVENT);
            }

            ScalerDpHdcpRxClrHdcpCpirqFlag(_D0_INPUT_PORT);

            break;

        case _SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ:

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
            if(ScalerDpRxCableStatus(_D0_INPUT_PORT) == _TRUE)
            {
                if((ScalerDpAuxRxGetDpcdInfo(_D0_INPUT_PORT, 0x00, 0x01, 0x00) >= _DP_LINK_HBR2) &&
                   ((GET_DP_RX_D0_MARGIN_LINK() == _TRUE) || (GET_DP_RX_D6_MARGIN_LINK() == _TRUE)))
                {
                    DebugMessageRx0("7. DP Margin Link Long HPD", ScalerDpAuxRxGetDpcdInfo(_D0_INPUT_PORT, 0x00, 0x01, 0x00));

                    switch(ScalerDpAuxRxGetDpcdInfo(_D0_INPUT_PORT, 0x00, 0x01, 0x00))
                    {
                        case _DP_LINK_HBR3:

                            ScalerDpAuxRxSetDpcdValue(_D0_INPUT_PORT, 0x00, 0x00, 0x01, _DP_LINK_HBR2);

                            // When Define Extended Rx Cap Should Set DPCD 0x02201
                            ScalerDpAuxRxSetDpcdValue(_D0_INPUT_PORT, 0x00, 0x22, 0x01, _DP_LINK_HBR2);

                            break;

                        case _DP_LINK_HBR2:

                            ScalerDpAuxRxSetDpcdValue(_D0_INPUT_PORT, 0x00, 0x00, 0x01, _DP_LINK_HBR);

                            // When Define Extended Rx Cap Should Set DPCD 0x02201
                            ScalerDpAuxRxSetDpcdValue(_D0_INPUT_PORT, 0x00, 0x22, 0x01, _DP_LINK_HBR);

                            break;

                        default:
                            break;
                    }

                    ScalerDpRxSetHotPlugEvent(_D0_INPUT_PORT, _DP_MARGIN_LINK_HPD_EVENT);
                }
                else
                {
                    ScalerDpAuxRxLinkStatusIRQ(_D0_INPUT_PORT);
                }
            }
#else
            ScalerDpAuxRxLinkStatusIRQ(_D0_INPUT_PORT);
#endif
            break;

#if((_DP_TX_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_DP_RX0_HDCP2_CPIRQ_EVENT:

            CLR_DP_HDCP2_RX0_AUTH_CPIRQ_TIMRE();

            break;

        case _SCALER_TIMER_EVENT_DP_RX0_HDCP2_REPEATER_PROC_TIMEOUT:

            ScalerDpHdcp2Rx0SetRepeaterProcTimeout();

            break;

        case _SCALER_TIMER_EVENT_DP_RX0_HDCP2_LONG_HOTPLUG_EVENT:

            if(ScalerDpHdcp2RxReAuthStatusCheck(_D0_INPUT_PORT) == _TRUE)
            {
                DebugMessageHDCP2("7. DPRX0 HDCP2 Long HPD", 0);

                ScalerDpRxSetHotPlugEvent(_D0_INPUT_PORT, _DP_HDCP_LONG_HPD_EVENT);
            }

            break;

#endif // End of #if((_DP_TX_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))

        case _SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE:

            CLR_DP_AUX_RX0_CHECK_CH_NO_POWER_DEBOUNCE();

            if(ScalerDpAuxRx0ChSourcePowerCheck() == _OFF)
            {
                BYTE ucDebounceCnt = 0;

                // Debounce for 20ms
                for(ucDebounceCnt = 0; ucDebounceCnt < 10; ucDebounceCnt++)
                {
                    ScalerTimerDelayXms(2);

                    if(ScalerDpAuxRx0ChSourcePowerCheck() == _ON)
                    {
                        break;
                    }
                }

                if(ucDebounceCnt == 10)
                {
                    SET_DP_AUX_RX0_CHECK_CH_POWER_STATUS(_DP_RX_AUX_POWER_STATUS_OFF);

                    ScalerDpAuxRx0DisconnectReset();
                }
            }

            break;

#if(_DP_MST_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX0_SOURCE_WRITE_POWER_UP_TIMEOUT:

            if(GET_DP_AUX_RX0_SOURCE_WRITE_POWER_UP() == _DP_SOURCE_WRITE_POWER_UP_TIMER_ACTIVE)
            {
                CLR_DP_AUX_RX0_SOURCE_WRITE_POWER_UP();
            }

            break;

        case _SCALER_TIMER_EVENT_DP_RX0_MSG_TIMEOUT_EVENT:

            ScalerDpMstRxMsgTimeoutEvent(_D0_INPUT_PORT);

            break;

        case _SCALER_TIMER_EVENT_DP_RX0_UP_REQUEST_PROCESSING:

            ScalerDpRxSetBaseInputPort(_D0_INPUT_PORT);

            CLR_DP_MST_RX_UP_REQUEST_PROCESSING();

            break;
#endif // End of #if(_DP_MST_SUPPORT == _ON)
#endif // End of #if(_D0_DP_SUPPORT == _ON)

#if(_D1_DP_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK:

            SET_DP_AUX_RX1_VALID_VIDEO_CHECK();

            break;

        case _SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED:

            ScalerDpRxSetHotPlugEvent(_D1_INPUT_PORT, _DP_HPD_ASSERTED);

            break;

        case _SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT:

            if(ScalerDpMacDphyRxHdcpReAuthStatusCheck(_D1_INPUT_PORT) == _FALSE)
            {
                DebugMessageRx1("7. DP HDCP Long HPD", 0);
                ScalerDpRxSetHotPlugEvent(_D1_INPUT_PORT, _DP_HDCP_LONG_HPD_EVENT);
            }

            ScalerDpHdcpRxClrHdcpCpirqFlag(_D1_INPUT_PORT);

            break;

        case _SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ:

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
            if(ScalerDpRxCableStatus(_D1_INPUT_PORT) == _TRUE)
            {
                if((ScalerDpAuxRxGetDpcdInfo(_D1_INPUT_PORT, 0x00, 0x01, 0x00) >= _DP_LINK_HBR2) &&
                   (GET_DP_RX_D1_MARGIN_LINK() == _TRUE))
                {
                    DebugMessageRx1("7. DP Margin Link Long HPD", ScalerDpAuxRxGetDpcdInfo(_D1_INPUT_PORT, 0x00, 0x01, 0x00));

                    switch(ScalerDpAuxRxGetDpcdInfo(_D1_INPUT_PORT, 0x00, 0x01, 0x00))
                    {
                        case _DP_LINK_HBR3:

                            ScalerDpAuxRxSetDpcdValue(_D1_INPUT_PORT, 0x00, 0x00, 0x01, _DP_LINK_HBR2);

                            // When Define Extended Rx Cap Should Set DPCD 0x02201
                            ScalerDpAuxRxSetDpcdValue(_D1_INPUT_PORT, 0x00, 0x22, 0x01, _DP_LINK_HBR2);

                            break;

                        case _DP_LINK_HBR2:

                            ScalerDpAuxRxSetDpcdValue(_D1_INPUT_PORT, 0x00, 0x00, 0x01, _DP_LINK_HBR);

                            // When Define Extended Rx Cap Should Set DPCD 0x02201
                            ScalerDpAuxRxSetDpcdValue(_D1_INPUT_PORT, 0x00, 0x22, 0x01, _DP_LINK_HBR);

                            break;

                        default:
                            break;
                    }

                    ScalerDpRxSetHotPlugEvent(_D1_INPUT_PORT, _DP_MARGIN_LINK_HPD_EVENT);
                }
                else
                {
                    ScalerDpAuxRxLinkStatusIRQ(_D1_INPUT_PORT);
                }
            }
#else
            ScalerDpAuxRxLinkStatusIRQ(_D1_INPUT_PORT);
#endif
            break;

#if((_DP_TX_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_DP_RX1_HDCP2_CPIRQ_EVENT:

            CLR_DP_HDCP2_RX1_AUTH_CPIRQ_TIMRE();

            break;

        case _SCALER_TIMER_EVENT_DP_RX1_HDCP2_REPEATER_PROC_TIMEOUT:

            ScalerDpHdcp2Rx1SetRepeaterProcTimeout();

            break;

        case _SCALER_TIMER_EVENT_DP_RX1_HDCP2_LONG_HOTPLUG_EVENT:

            if(ScalerDpHdcp2RxReAuthStatusCheck(_D1_INPUT_PORT) == _TRUE)
            {
                DebugMessageHDCP2("7. DPRX1 HDCP2 Long HPD", 0);

                ScalerDpRxSetHotPlugEvent(_D1_INPUT_PORT, _DP_HDCP_LONG_HPD_EVENT);
            }

            break;

#endif // End of #if((_DP_TX_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))

        case _SCALER_TIMER_EVENT_DP_RX1_AUX_CH_NO_POWER_CHECK_DEBOUNCE:

            CLR_DP_AUX_RX1_CHECK_CH_NO_POWER_DEBOUNCE();

            if(ScalerDpAuxRx1ChSourcePowerCheck() == _OFF)
            {
                BYTE ucDebounceCnt = 0;

                // Debounce for 20ms
                for(ucDebounceCnt = 0; ucDebounceCnt < 10; ucDebounceCnt++)
                {
                    ScalerTimerDelayXms(2);

                    if(ScalerDpAuxRx1ChSourcePowerCheck() == _ON)
                    {
                        break;
                    }
                }

                if(ucDebounceCnt == 10)
                {
                    SET_DP_AUX_RX1_CHECK_CH_POWER_STATUS(_DP_RX_AUX_POWER_STATUS_OFF);

                    ScalerDpAuxRx1DisconnectReset();
                }
            }

            break;

#if(_DP_MST_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX1_SOURCE_WRITE_POWER_UP_TIMEOUT:

            if(GET_DP_AUX_RX1_SOURCE_WRITE_POWER_UP() == _DP_SOURCE_WRITE_POWER_UP_TIMER_ACTIVE)
            {
                CLR_DP_AUX_RX1_SOURCE_WRITE_POWER_UP();
            }

            break;

        case _SCALER_TIMER_EVENT_DP_RX1_MSG_TIMEOUT_EVENT:

            ScalerDpMstRxMsgTimeoutEvent(_D1_INPUT_PORT);

            break;

        case _SCALER_TIMER_EVENT_DP_RX1_UP_REQUEST_PROCESSING:

            ScalerDpRxSetBaseInputPort(_D1_INPUT_PORT);

            CLR_DP_MST_RX_UP_REQUEST_PROCESSING();

            break;
#endif // End of #if(_DP_MST_SUPPORT == _ON)
#endif // End of #if(_D1_DP_SUPPORT == _ON)

#if(_D2_DP_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX2_VALID_SIGNAL_DETECT_CHECK:

            SET_DP_AUX_RX2_VALID_VIDEO_CHECK();

            break;

        case _SCALER_TIMER_EVENT_DP_RX2_HOTPLUG_ASSERTED:

            ScalerDpRxSetHotPlugEvent(_D2_INPUT_PORT, _DP_HPD_ASSERTED);

            break;

        case _SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT:

            if(ScalerDpMacDphyRxHdcpReAuthStatusCheck(_D2_INPUT_PORT) == _FALSE)
            {
                DebugMessageRx2("7. DP HDCP Long HPD", 0);
                ScalerDpRxSetHotPlugEvent(_D2_INPUT_PORT, _DP_HDCP_LONG_HPD_EVENT);
            }

            ScalerDpHdcpRxClrHdcpCpirqFlag(_D2_INPUT_PORT);

            break;

        case _SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ:

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
            if(ScalerDpRxCableStatus(_D2_INPUT_PORT) == _TRUE)
            {
                if((ScalerDpAuxRxGetDpcdInfo(_D2_INPUT_PORT, 0x00, 0x01, 0x00) >= _DP_LINK_HBR2) &&
                   (GET_DP_RX_D2_MARGIN_LINK() == _TRUE))
                {
                    DebugMessageRx2("7. DP Margin Link Long HPD", 0);

                    switch(ScalerDpAuxRxGetDpcdInfo(_D2_INPUT_PORT, 0x00, 0x01, 0x00))
                    {
                        case _DP_LINK_HBR3:

                            ScalerDpAuxRxSetDpcdValue(_D2_INPUT_PORT, 0x00, 0x00, 0x01, _DP_LINK_HBR2);

                            // When Define Extended Rx Cap Should Set DPCD 0x02201
                            ScalerDpAuxRxSetDpcdValue(_D2_INPUT_PORT, 0x00, 0x22, 0x01, _DP_LINK_HBR2);

                            break;

                        case _DP_LINK_HBR2:

                            ScalerDpAuxRxSetDpcdValue(_D2_INPUT_PORT, 0x00, 0x00, 0x01, _DP_LINK_HBR);

                            // When Define Extended Rx Cap Should Set DPCD 0x02201
                            ScalerDpAuxRxSetDpcdValue(_D2_INPUT_PORT, 0x00, 0x22, 0x01, _DP_LINK_HBR);

                            break;

                        default:
                            break;
                    }

                    ScalerDpRxSetHotPlugEvent(_D2_INPUT_PORT, _DP_MARGIN_LINK_HPD_EVENT);
                }
                else
                {
                    ScalerDpAuxRxLinkStatusIRQ(_D2_INPUT_PORT);
                }
            }
#else
            ScalerDpAuxRxLinkStatusIRQ(_D2_INPUT_PORT);
#endif
            break;

#if((_DP_TX_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_DP_RX2_HDCP2_CPIRQ_EVENT:

            CLR_DP_HDCP2_RX2_AUTH_CPIRQ_TIMRE();

            break;

        case _SCALER_TIMER_EVENT_DP_RX2_HDCP2_REPEATER_PROC_TIMEOUT:

            ScalerDpHdcp2Rx2SetRepeaterProcTimeout();

            break;

        case _SCALER_TIMER_EVENT_DP_RX2_HDCP2_LONG_HOTPLUG_EVENT:

            if(ScalerDpHdcp2RxReAuthStatusCheck(_D2_INPUT_PORT) == _TRUE)
            {
                DebugMessageHDCP2("7. DPRX2 HDCP2 Long HPD", 0);

                ScalerDpRxSetHotPlugEvent(_D2_INPUT_PORT, _DP_HDCP_LONG_HPD_EVENT);
            }

            break;

#endif // End of #if((_DP_TX_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))

        case _SCALER_TIMER_EVENT_DP_RX2_AUX_CH_NO_POWER_CHECK_DEBOUNCE:

            CLR_DP_AUX_RX2_CHECK_CH_NO_POWER_DEBOUNCE();

            if(ScalerDpAuxRx2ChSourcePowerCheck() == _OFF)
            {
                BYTE ucDebounceCnt = 0;

                // Debounce for 20ms
                for(ucDebounceCnt = 0; ucDebounceCnt < 10; ucDebounceCnt++)
                {
                    ScalerTimerDelayXms(2);

                    if(ScalerDpAuxRx2ChSourcePowerCheck() == _ON)
                    {
                        break;
                    }
                }

                if(ucDebounceCnt == 10)
                {
                    SET_DP_AUX_RX2_CHECK_CH_POWER_STATUS(_DP_RX_AUX_POWER_STATUS_OFF);

                    ScalerDpAuxRx2DisconnectReset();
                }
            }

            break;

#if(_DP_MST_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX2_SOURCE_WRITE_POWER_UP_TIMEOUT:

            if(GET_DP_AUX_RX2_SOURCE_WRITE_POWER_UP() == _DP_SOURCE_WRITE_POWER_UP_TIMER_ACTIVE)
            {
                CLR_DP_AUX_RX2_SOURCE_WRITE_POWER_UP();
            }

            break;

        case _SCALER_TIMER_EVENT_DP_RX2_MSG_TIMEOUT_EVENT:

            ScalerDpMstRxMsgTimeoutEvent(_D2_INPUT_PORT);

            break;

        case _SCALER_TIMER_EVENT_DP_RX2_UP_REQUEST_PROCESSING:

            ScalerDpRxSetBaseInputPort(_D2_INPUT_PORT);

            CLR_DP_MST_RX_UP_REQUEST_PROCESSING();

            break;
#endif // End of #if(_DP_MST_SUPPORT == _ON)
#endif // End of #if(_D2_DP_SUPPORT == _ON)

#if(_DP_MAC_RX0_SUPPORT == _ON)

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_DP_RX0_SPD_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx0SetSpdInfoDetectingDone();
            break;
#endif
#if(_DP_HDR10_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX0_HDR_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx0SetHdrInfoDetectingDone();
            break;
#endif
#if(_AUDIO_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX0_AUDIO_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx0SetAudioInfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX0_ADVANCED_HDR10_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX0_ADVANCED_HDR10_DETECTING_DONE:
            ScalerDpMacStreamRx0SetAdvancedHdr10InfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX0_DM_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX0_DM_VSIF_DETECTING_DONE:
            ScalerDpMacStreamRx0SetDMVsifInfoDetectingDone();
            break;
#endif
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX0_PPS_SDP_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx0SetPpsSdpInfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_MAC_STREAM_RX0_PPS_RECEIVE_TIMEOUT:
            ScalerDpMacDscPpsTimeOutEventProc(_DP_MAC_0);
            break;
#endif
#endif // End of #if(_DP_MAC_RX0_SUPPORT == _ON)

#if(_DP_MAC_RX1_SUPPORT == _ON)

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_DP_RX1_SPD_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx1SetSpdInfoDetectingDone();
            break;
#endif
#if(_DP_HDR10_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX1_HDR_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx1SetHdrInfoDetectingDone();
            break;
#endif
#if(_AUDIO_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX1_AUDIO_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx1SetAudioInfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX1_ADVANCED_HDR10_DETECTING_DONE:
            ScalerDpMacStreamRx1SetAdvancedHdr10InfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX1_DM_VSIF_DETECTING_DONE:
            ScalerDpMacStreamRx1SetDMVsifInfoDetectingDone();
            break;
#endif
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX1_PPS_SDP_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx1SetPpsSdpInfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_MAC_STREAM_RX1_PPS_RECEIVE_TIMEOUT:
            ScalerDpMacDscPpsTimeOutEventProc(_DP_MAC_1);
            break;
#endif
#endif // End of #if(_DP_MAC_RX1_SUPPORT == _ON)

#if(_DP_MAC_RX2_SUPPORT == _ON)

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_DP_RX2_SPD_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx2SetSpdInfoDetectingDone();
            break;
#endif
#if(_DP_HDR10_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX2_HDR_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx2SetHdrInfoDetectingDone();
            break;
#endif
#if(_AUDIO_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX2_AUDIO_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx2SetAudioInfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX2_ADVANCED_HDR10_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX2_ADVANCED_HDR10_DETECTING_DONE:
            ScalerDpMacStreamRx2SetAdvancedHdr10InfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX2_DM_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX2_DM_VSIF_DETECTING_DONE:
            ScalerDpMacStreamRx2SetDMVsifInfoDetectingDone();
            break;
#endif
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX2_PPS_SDP_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx2SetPpsSdpInfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_MAC_STREAM_RX2_PPS_RECEIVE_TIMEOUT:
            ScalerDpMacDscPpsTimeOutEventProc(_DP_MAC_2);
            break;
#endif
#endif // End of #if(_DP_MAC_RX2_SUPPORT == _ON)

#if(_DP_MAC_RX3_SUPPORT == _ON)

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_DP_RX3_SPD_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx3SetSpdInfoDetectingDone();
            break;
#endif
#if(_DP_HDR10_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX3_HDR_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx3SetHdrInfoDetectingDone();
            break;
#endif
#if(_AUDIO_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX3_AUDIO_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx3SetAudioInfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX3_ADVANCED_HDR10_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX3_ADVANCED_HDR10_DETECTING_DONE:
            ScalerDpMacStreamRx3SetAdvancedHdr10InfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX3_DM_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX3_DM_VSIF_DETECTING_DONE:
            ScalerDpMacStreamRx3SetDMVsifInfoDetectingDone();
            break;
#endif
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX3_PPS_SDP_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx3SetPpsSdpInfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_MAC_STREAM_RX3_PPS_RECEIVE_TIMEOUT:
            ScalerDpMacDscPpsTimeOutEventProc(_DP_MAC_3);
            break;
#endif
#endif // End of #if(_DP_MAC_RX3_SUPPORT == _ON)

#if(_DP_MAC_RX4_SUPPORT == _ON)

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_DP_RX4_SPD_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx4SetSpdInfoDetectingDone();
            break;
#endif
#if(_DP_HDR10_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX4_HDR_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx4SetHdrInfoDetectingDone();
            break;
#endif
#if(_AUDIO_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX4_AUDIO_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx4SetAudioInfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX4_ADVANCED_HDR10_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX4_ADVANCED_HDR10_DETECTING_DONE:
            ScalerDpMacStreamRx4SetAdvancedHdr10InfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX4_DM_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX4_DM_VSIF_DETECTING_DONE:
            ScalerDpMacStreamRx4SetDMVsifInfoDetectingDone();
            break;
#endif
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX4_PPS_SDP_INFOFRAME_DETECTING_DONE:
            ScalerDpMacStreamRx4SetPpsSdpInfoDetectingDone();
            break;
#endif
#if(_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_MAC_STREAM_RX4_PPS_RECEIVE_TIMEOUT:
            ScalerDpMacDscPpsTimeOutEventProc(_DP_MAC_4);
            break;
#endif
#endif // End of #if(_DP_MAC_RX4_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
#if(_DP_MST_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_TX_FORCE_REBUILD_TOPOLOGY_EVENT:

            if(ScalerDpRxGetSrcMstEnable(GET_DP_RX_MAIN_PORT()) == _TRUE)
            {
                SET_DP_MST_TX_WAIT_TOPOLOGY_REBUILD_MSG();

                ScalerDpRxSetHotPlugEvent(GET_DP_RX_MAIN_PORT(), _DP_MST_LONG_HPD_EVENT);
            }

            break;

        case _SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT:

            ScalerDpMstRxMsgCountResetEvent();

            ScalerDpMstTxMsgCountResetEvent();

            break;

        case _SCALER_TIMER_EVENT_DP_TX_MSG_COUNT_RESET_EVENT:

            ScalerDpMstTxMsgCountResetEvent();

            break;

#if(_DP_MST_TX_PLUG_CSN_DEBOUNCE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_TX_PLUG_CSN_DEBOUNCING:

            CLR_DP_MST_TX_PLUG_CSN_DEBOUNCING();

            break;
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_TX_ENUM_MSG_REPLY_PBN_WAIT_TIMEOUT:
            SET_DP_MST_TX_ENUM_MSG_REPLY_TIMEOUT();
            break;
#endif
#endif

#if(_DP_TX_FEC_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_TX_FEC_DECODE_DIS_FAIL_RETRAIN:

            ScalerDpMacTxFecDisableFailReLinkTraining();

            break;
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_TX_LT_TIMEOUT:

            SET_DP_TX_LT_TIMEOUT();

            break;

        case _SCALER_TIMER_EVENT_DP_TX_AUX_RD_INTERVAL:

            SET_DP_TX_LT_WAIT_AUX_RD_INTERVAL_DONE();

            break;
#endif

        case _SCALER_TIMER_EVENT_DP_TX_HPD_DEBOUNCE:

            SET_DP_TX_HPD_DEBOUNCE();

            DebugMessageScaler("7. Dp Tx Excute HPD Debounce", 1);

            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_TO_READ_R0:

            ScalerDpHdcp14TxTimeoutToReadR0Event();

            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_FOR_V_READY:

            ScalerDpHdcp14TxTimeoutForVReadyEvent();

            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY:

            ScalerDpHdcp14TxPollingVReadyEvent();

            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_CERTIFICATE:

            ScalerDpHdcp2TxTimeoutToReadCertificateEvent();

            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_H_PRIME:

            ScalerDpHdcp2TxTimeoutToReadHPrimeEvent();

            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_PAIRING_INFO:

            ScalerDpHdcp2TxTimeoutToReadPairingInfoEvent();

            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_ENCRYPT_DATA:

            ScalerDpHdcp2TxTimeoutToEncyptDataEvent();

            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_FOR_V_READY:

            ScalerDpHdcp2TxTimeoutForVReadyEvent();

            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_POLLING_V_READY:

            ScalerDpHdcp2TxPollingVReadyEvent();

            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_M_PRIME:

            ScalerDpHdcp2TxTimeoutToReadMPrimeEvent();

            break;
#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)

#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX0_HDCP_CPIRQ_EVENT:

            CLR_DP_HDCP14_RX0_AUTH_CPIRQ_TIMRE();

            break;

        case _SCALER_TIMER_EVENT_DP_RX0_HDCP_REPEATER_PROC_TIMEOUT:

            ScalerDpHdcp14RxSetRepeaterProcTimeout(ScalerDpHdcpRxRxDxMapping(_RX0));

            break;

        case _SCALER_TIMER_EVENT_DP_RX0_HDCP_READ_IRQ_TIMEOUT:

            ScalerDpHdcp14RxSetReadIrqTimeout(ScalerDpHdcpRxRxDxMapping(_RX0));

            break;
#endif // End of #if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)

#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_DP_RX1_HDCP_CPIRQ_EVENT:

            CLR_DP_HDCP14_RX1_AUTH_CPIRQ_TIMRE();

            break;

        case _SCALER_TIMER_EVENT_DP_RX1_HDCP_REPEATER_PROC_TIMEOUT:

            ScalerDpHdcp14RxSetRepeaterProcTimeout(ScalerDpHdcpRxRxDxMapping(_RX1));

            break;

        case _SCALER_TIMER_EVENT_DP_RX1_HDCP_READ_IRQ_TIMEOUT:

            ScalerDpHdcp14RxSetReadIrqTimeout(ScalerDpHdcpRxRxDxMapping(_RX1));

            break;
#endif // End of #if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)

#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_DP_RX2_HDCP_CPIRQ_EVENT:

            CLR_DP_HDCP14_RX2_AUTH_CPIRQ_TIMRE();

            break;

        case _SCALER_TIMER_EVENT_DP_RX2_HDCP_REPEATER_PROC_TIMEOUT:

            ScalerDpHdcp14RxSetRepeaterProcTimeout(ScalerDpHdcpRxRxDxMapping(_RX2));

            break;

        case _SCALER_TIMER_EVENT_DP_RX2_HDCP_READ_IRQ_TIMEOUT:

            ScalerDpHdcp14RxSetReadIrqTimeout(ScalerDpHdcpRxRxDxMapping(_RX2));

            break;
#endif // End of #if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
#endif // End if #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _SCALER_TIMER_EVENT_CC_0_STATE_TO_UNATTACH:

            ScalerTypeC0CcTimerEventProc(enumEventID);

            break;
        case _SCALER_TIMER_EVENT_PD_0_PPS_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_0_SRC_EPR_KEEP_ALIVE_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_0_SEND_HARD_RST:
        case _SCALER_TIMER_EVENT_PD_0_SNK_HARD_RST_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_0_S8_HRST:
        case _SCALER_TIMER_EVENT_PD_0_CLR_REQ_WAIT:
        case _SCALER_TIMER_EVENT_PD_0_CLR_PARTNER_ALT_SUPPORT:
        case _SCALER_TIMER_EVENT_PD_0_TPC_ERROR_RECOVERY:
        case _SCALER_TIMER_EVENT_PD_0_T480_ERROR_RECOVERY:
        case _SCALER_TIMER_EVENT_PD_0_SRC_TURN_OFF_POWER:
        case _SCALER_TIMER_EVENT_PD_0_SRC_TURN_ON_POWER:
        case _SCALER_TIMER_EVENT_PD_0_CLR_PRS_WAIT:
        case _SCALER_TIMER_EVENT_PD_0_CLR_DRS_WAIT:
        case _SCALER_TIMER_EVENT_PD_0_CLR_VCS_WAIT:
        case _SCALER_TIMER_EVENT_PD_0_DFP_START_ALT_MODE:
        case _SCALER_TIMER_EVENT_PD_0_LENOVO_RESP_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_0_VDM_RESP_CONFLICT_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_0_CLR_ATTENTION_WAIT:
        case _SCALER_TIMER_EVENT_PD_0_CLR_GET_SNK_CAP_WAIT:
        case _SCALER_TIMER_EVENT_PD_0_CLR_VDMMSG_WAIT:
        case _SCALER_TIMER_EVENT_PD_0_CLR_VDM_BUSY_FLAG:

            ScalerTypeC0PdTimerEventProc(enumEventID);

            break;

#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
        case _SCALER_TIMER_EVENT_TYPE_C_0_PMIC_TRACKING:
        case _SCALER_TIMER_EVENT_TYPE_C_0_PMIC_SAFETY_PROTECT:
        case _SCALER_TIMER_EVENT_TYPE_C_0_PMIC_POLLING_OCP:

            ScalerTypeC0PmicTimerEventProc(enumEventID);

            break;
#endif // End of #if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
#endif // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _SCALER_TIMER_EVENT_CC_1_STATE_TO_UNATTACH:

            ScalerTypeC1CcTimerEventProc(enumEventID);

            break;

        case _SCALER_TIMER_EVENT_PD_1_PPS_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_1_SRC_EPR_KEEP_ALIVE_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_1_SEND_HARD_RST:
        case _SCALER_TIMER_EVENT_PD_1_SNK_HARD_RST_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_1_S8_HRST:
        case _SCALER_TIMER_EVENT_PD_1_CLR_REQ_WAIT:
        case _SCALER_TIMER_EVENT_PD_1_CLR_PARTNER_ALT_SUPPORT:
        case _SCALER_TIMER_EVENT_PD_1_TPC_ERROR_RECOVERY:
        case _SCALER_TIMER_EVENT_PD_1_T480_ERROR_RECOVERY:
        case _SCALER_TIMER_EVENT_PD_1_SRC_TURN_OFF_POWER:
        case _SCALER_TIMER_EVENT_PD_1_SRC_TURN_ON_POWER:
        case _SCALER_TIMER_EVENT_PD_1_CLR_PRS_WAIT:
        case _SCALER_TIMER_EVENT_PD_1_CLR_DRS_WAIT:
        case _SCALER_TIMER_EVENT_PD_1_CLR_VCS_WAIT:
        case _SCALER_TIMER_EVENT_PD_1_DFP_START_ALT_MODE:
        case _SCALER_TIMER_EVENT_PD_1_LENOVO_RESP_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_1_VDM_RESP_CONFLICT_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_1_CLR_ATTENTION_WAIT:
        case _SCALER_TIMER_EVENT_PD_1_CLR_GET_SNK_CAP_WAIT:
        case _SCALER_TIMER_EVENT_PD_1_CLR_VDMMSG_WAIT:
        case _SCALER_TIMER_EVENT_PD_1_CLR_VDM_BUSY_FLAG:

            ScalerTypeC1PdTimerEventProc(enumEventID);

            break;

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
        case _SCALER_TIMER_EVENT_TYPE_C_1_PMIC_TRACKING:
        case _SCALER_TIMER_EVENT_TYPE_C_1_PMIC_SAFETY_PROTECT:
        case _SCALER_TIMER_EVENT_TYPE_C_1_PMIC_POLLING_OCP:

            ScalerTypeC1PmicTimerEventProc(enumEventID);

            break;
#endif // End of #if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
#endif // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_TCPM_SUPPORT == _ON))
#if(_HW_TCPM_SUPPORT == _ON)
#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _SCALER_TIMER_EVENT_TCPM_0_0_SNK_HARD_RST_TIMEOUT:
        case _SCALER_TIMER_EVENT_TCPM_0_0_CLR_REQ_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_0_CLR_PARTNER_ALT_SUPPORT:
        case _SCALER_TIMER_EVENT_TCPM_0_0_T480_ERROR_RECOVERY:
        case _SCALER_TIMER_EVENT_TCPM_0_0_SRC_TURN_OFF_POWER:
        case _SCALER_TIMER_EVENT_TCPM_0_0_SRC_TURN_ON_POWER:
        case _SCALER_TIMER_EVENT_TCPM_0_0_VDM_RESP_CONFLICT_TIMEOUT:
        case _SCALER_TIMER_EVENT_TCPM_0_0_CLR_ATTENTION_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_0_CLR_GET_SNK_CAP_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_0_S8_HRST:
        case _SCALER_TIMER_EVENT_TCPM_0_0_SEND_HARD_RST:
        case _SCALER_TIMER_EVENT_TCPM_0_0_TPC_ERROR_RECOVERY:
        case _SCALER_TIMER_EVENT_TCPM_0_0_CLR_PRS_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_0_CLR_DRS_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_0_CLR_VCS_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_0_CLR_VDMMSG_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_0_CLR_VDM_BUSY_FLAG:
        case _SCALER_TIMER_EVENT_TCPM_0_0_DFP_START_ALT_MODE:
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TCPM_0_0_PPS_TIMEOUT:
#endif
#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TCPM_0_0_OVP_UVP_CHECK:
#endif
#if((_TYPE_C_PMIC_SUPPORT == _ON) && (_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_TCPM_0_0_PMIC_TRACKING:
        case _SCALER_TIMER_EVENT_TCPM_0_0_PMIC_POLLING_OCP:
#endif

            ScalerTypeCTcpmTimerEventProc(_HW_TCPM_0_0_MAPPING, (EnumTypeCTcpmEventID)(enumEventID - _SCALER_TIMER_EVENT_TCPM_0_0_SNK_HARD_RST_TIMEOUT));

            break;
#endif // End of #if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _SCALER_TIMER_EVENT_TCPM_0_1_SNK_HARD_RST_TIMEOUT:
        case _SCALER_TIMER_EVENT_TCPM_0_1_CLR_REQ_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_1_CLR_PARTNER_ALT_SUPPORT:
        case _SCALER_TIMER_EVENT_TCPM_0_1_T480_ERROR_RECOVERY:
        case _SCALER_TIMER_EVENT_TCPM_0_1_SRC_TURN_OFF_POWER:
        case _SCALER_TIMER_EVENT_TCPM_0_1_SRC_TURN_ON_POWER:
        case _SCALER_TIMER_EVENT_TCPM_0_1_VDM_RESP_CONFLICT_TIMEOUT:
        case _SCALER_TIMER_EVENT_TCPM_0_1_CLR_ATTENTION_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_1_CLR_GET_SNK_CAP_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_1_S8_HRST:
        case _SCALER_TIMER_EVENT_TCPM_0_1_SEND_HARD_RST:
        case _SCALER_TIMER_EVENT_TCPM_0_1_TPC_ERROR_RECOVERY:
        case _SCALER_TIMER_EVENT_TCPM_0_1_CLR_PRS_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_1_CLR_DRS_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_1_CLR_VCS_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_1_CLR_VDMMSG_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_0_1_CLR_VDM_BUSY_FLAG:
        case _SCALER_TIMER_EVENT_TCPM_0_1_DFP_START_ALT_MODE:
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TCPM_0_1_PPS_TIMEOUT:
#endif
#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TCPM_0_1_OVP_UVP_CHECK:
#endif
#if((_TYPE_C_PMIC_SUPPORT == _ON) && (_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_TCPM_0_1_PMIC_TRACKING:
        case _SCALER_TIMER_EVENT_TCPM_0_1_PMIC_POLLING_OCP:
#endif

            ScalerTypeCTcpmTimerEventProc(_HW_TCPM_0_1_MAPPING, (EnumTypeCTcpmEventID)(enumEventID - _SCALER_TIMER_EVENT_TCPM_0_1_SNK_HARD_RST_TIMEOUT));

            break;
#endif // End of #if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _SCALER_TIMER_EVENT_TCPM_1_0_SNK_HARD_RST_TIMEOUT:
        case _SCALER_TIMER_EVENT_TCPM_1_0_CLR_REQ_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_0_CLR_PARTNER_ALT_SUPPORT:
        case _SCALER_TIMER_EVENT_TCPM_1_0_T480_ERROR_RECOVERY:
        case _SCALER_TIMER_EVENT_TCPM_1_0_SRC_TURN_OFF_POWER:
        case _SCALER_TIMER_EVENT_TCPM_1_0_SRC_TURN_ON_POWER:
        case _SCALER_TIMER_EVENT_TCPM_1_0_VDM_RESP_CONFLICT_TIMEOUT:
        case _SCALER_TIMER_EVENT_TCPM_1_0_CLR_ATTENTION_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_0_CLR_GET_SNK_CAP_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_0_S8_HRST:
        case _SCALER_TIMER_EVENT_TCPM_1_0_SEND_HARD_RST:
        case _SCALER_TIMER_EVENT_TCPM_1_0_TPC_ERROR_RECOVERY:
        case _SCALER_TIMER_EVENT_TCPM_1_0_CLR_PRS_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_0_CLR_DRS_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_0_CLR_VCS_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_0_CLR_VDMMSG_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_0_CLR_VDM_BUSY_FLAG:
        case _SCALER_TIMER_EVENT_TCPM_1_0_DFP_START_ALT_MODE:
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TCPM_1_0_PPS_TIMEOUT:
#endif
#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TCPM_1_0_OVP_UVP_CHECK:
#endif
#if((_TYPE_C_PMIC_SUPPORT == _ON) && (_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_TCPM_1_0_PMIC_TRACKING:
        case _SCALER_TIMER_EVENT_TCPM_1_0_PMIC_POLLING_OCP:
#endif

            ScalerTypeCTcpmTimerEventProc(_HW_TCPM_1_0_MAPPING, (EnumTypeCTcpmEventID)(enumEventID - _SCALER_TIMER_EVENT_TCPM_1_0_SNK_HARD_RST_TIMEOUT));

            break;
#endif // End of #if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _SCALER_TIMER_EVENT_TCPM_1_1_SNK_HARD_RST_TIMEOUT:
        case _SCALER_TIMER_EVENT_TCPM_1_1_CLR_REQ_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_1_CLR_PARTNER_ALT_SUPPORT:
        case _SCALER_TIMER_EVENT_TCPM_1_1_T480_ERROR_RECOVERY:
        case _SCALER_TIMER_EVENT_TCPM_1_1_SRC_TURN_OFF_POWER:
        case _SCALER_TIMER_EVENT_TCPM_1_1_SRC_TURN_ON_POWER:
        case _SCALER_TIMER_EVENT_TCPM_1_1_VDM_RESP_CONFLICT_TIMEOUT:
        case _SCALER_TIMER_EVENT_TCPM_1_1_CLR_ATTENTION_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_1_CLR_GET_SNK_CAP_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_1_S8_HRST:
        case _SCALER_TIMER_EVENT_TCPM_1_1_SEND_HARD_RST:
        case _SCALER_TIMER_EVENT_TCPM_1_1_TPC_ERROR_RECOVERY:
        case _SCALER_TIMER_EVENT_TCPM_1_1_CLR_PRS_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_1_CLR_DRS_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_1_CLR_VCS_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_1_CLR_VDMMSG_WAIT:
        case _SCALER_TIMER_EVENT_TCPM_1_1_CLR_VDM_BUSY_FLAG:
        case _SCALER_TIMER_EVENT_TCPM_1_1_DFP_START_ALT_MODE:
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TCPM_1_1_PPS_TIMEOUT:
#endif
#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TCPM_1_1_OVP_UVP_CHECK:
#endif
#if((_TYPE_C_PMIC_SUPPORT == _ON) && (_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_TCPM_1_1_PMIC_TRACKING:
        case _SCALER_TIMER_EVENT_TCPM_1_1_PMIC_POLLING_OCP:
#endif

            ScalerTypeCTcpmTimerEventProc(_HW_TCPM_1_1_MAPPING, (EnumTypeCTcpmEventID)(enumEventID - _SCALER_TIMER_EVENT_TCPM_1_1_SNK_HARD_RST_TIMEOUT));

            break;
#endif // End of #if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_TCPM_SUPPORT == _ON))

#if(_ADVANCED_HDR10_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_ADVANCED_HDR10_ERROR_STATE_DETECT:
            ScalerColorAdvancedHDR10PCMHLWDBErrorStateProc();
            break;
#endif


#if(_FW_UPDATE_BACKGROUND_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_DPTX_BUSY:
            ScalerFwUpdateBackgroundSetBusyStatus(_AFFECTED_IP_DPTX, _STATUS_IDLE, 0);
            break;
#endif
#if(_DP_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_DPRX_BUSY:
            ScalerFwUpdateBackgroundSetBusyStatus(_AFFECTED_IP_DPRX, _STATUS_IDLE, 0);
            break;
#endif
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_TYPEC_BUSY:
            ScalerFwUpdateBackgroundSetBusyStatus(_AFFECTED_IP_TYPEC, _STATUS_IDLE, 0);
            break;
#endif
#if(_DIGITAL_PORT_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_MCCS_BUSY:
            ScalerFwUpdateBackgroundSetBusyStatus(_AFFECTED_IP_MCCS, _STATUS_IDLE, 0);
            break;
#endif
        case _SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_HDCP_BUSY:
            ScalerFwUpdateBackgroundSetBusyStatus(_AFFECTED_IP_HDCP, _STATUS_IDLE, 0);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Event Time
// Input Value  : ucEventIndex --> Event which time is needed
// Output Value : Event Time
//--------------------------------------------------
WORD ScalerTimerGetEventTime(BYTE ucEventIndex)
{
    return GET_EVENT_TIME(ucEventIndex);
}

//--------------------------------------------------
// Description  : Clear Event Time
// Input Value  : ucEventIndex --> Event which time is needed to be cleared
// Output Value : None
//--------------------------------------------------
void ScalerTimerClrEventValid(BYTE ucEventIndex)
{
    CLR_EVENT_VALID(ucEventIndex);
}

//--------------------------------------------------
// Description  : Check if Event is Valid
// Input Value  : ucEventIndex --> Event to be checked
// Output Value : Validity(_TRUE/_FALSE)
//--------------------------------------------------
bit ScalerTimerCheckEventValid(BYTE ucEventIndex)
{
    return (GET_EVENT_VALID(ucEventIndex) == _TRUE);
}

//--------------------------------------------------
// Description  : Active Timer Event
// Input Value  : usTime --> Time to active Timer Event
//                ucEventID --> Event to be actived
// Output Value : _TRUE if actived successfully
//--------------------------------------------------
bit ScalerTimerActiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID)
{
    BYTE ucEventIndex = 0;

    // Search for Existing Event with the same Event ID
    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_EVENT_VALID(ucEventIndex) == _TRUE)
        {
            if(GET_EVENT_ID(ucEventIndex) == enumEventID)
            {
                return _TRUE;
            }
        }
    }

    // Choose any Vacant Storage for Event
    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_EVENT_VALID(ucEventIndex) == _FALSE)
        {
            SET_EVENT_ID(ucEventIndex, enumEventID);
            SET_EVENT_TIME(ucEventIndex, (WORD)((DWORD)(ScalerTimerCheckTimerEvent(usTime)) + usTime));
            return _TRUE;
        }
    }

    DebugMessageCritical("No More Available Storage for Simultaneous Event!!!!!!", 0x00);
    ASSERT(_FALSE);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Reactive a timer for an event. If the event is exist,
//                this function will reset the executing time and restart.
// Input Value  : usTime    --> Unit in 1ms, range in 0.01 ~ 61 sec
//                Event     --> Execute Event while timeup
// Output Value : _TRUE if actived successfully
//--------------------------------------------------
bit ScalerTimerReactiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID)
{
    BYTE ucEventIndex = 0;

    // Search for Existing Event with the same Event ID
    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_EVENT_VALID(ucEventIndex) == _TRUE)
        {
            if(GET_EVENT_ID(ucEventIndex) == enumEventID)
            {
                SET_EVENT_TIME(ucEventIndex, (WORD)((DWORD)(ScalerTimerCheckTimerEvent(usTime)) + usTime));

                return _TRUE;
            }
        }
    }

    // Choose any Vacant Storage for Event
    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_EVENT_VALID(ucEventIndex) == _FALSE)
        {
            SET_EVENT_ID(ucEventIndex, enumEventID);
            SET_EVENT_TIME(ucEventIndex, (WORD)((DWORD)(ScalerTimerCheckTimerEvent(usTime)) + usTime));
            return _TRUE;
        }
    }

    DebugMessageCritical("No More Available Storage for Simultaneous Event!!!!!!", 0x00);
    ASSERT(_FALSE);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Cancel an event
// Input Value  : Event     --> Event which we want to cancel
// Output Value : None
//--------------------------------------------------
void ScalerTimerCancelTimerEvent(EnumScalerTimerEventID enumEventID)
{
    BYTE ucEventIndex = 0;

#if(_DP_MST_SUPPORT == _ON)
    ScalerDpMstRxCancelTimerEvent(enumEventID);
#endif

    // Search for Existing Event with the same Event ID
    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_EVENT_VALID(ucEventIndex) == _TRUE)
        {
            if(GET_EVENT_ID(ucEventIndex) == enumEventID)
            {
                CLR_EVENT_VALID(ucEventIndex);

                return;
            }
        }
    }
}

__attribute__((alias("ScalerTimerCancelTimerEvent")))
void ScalerTimerCancelTimerEvent_EXINT0(EnumScalerTimerEventID enumEventID);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_TCPM_SUPPORT == _ON))
__attribute__((alias("ScalerTimerCancelTimerEvent")))
void ScalerTimerCancelTimerEvent_WDINT(EnumScalerTimerEventID enumEventID);
#endif


//--------------------------------------------------
// Description  : Get Event Remain Time
// Input Value  : ucEventID --> Event which has been activated
// Output Value : Event ID Time
//--------------------------------------------------
WORD ScalerTimerGetEventRemainTime(EnumScalerTimerEventID enumEventID)
{
    BYTE ucEventIndex = 0;
    WORD usTime = 0;

    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(ScalerTimerGetEventID(ucEventIndex) == enumEventID)
        {
            if(GET_EVENT_VALID(ucEventIndex) == _TRUE)
            {
                if(ScalerTimerGetEventTime(ucEventIndex) > ScalerTimerGetTimerCounter())
                {
                    usTime = (ScalerTimerGetEventTime(ucEventIndex) - ScalerTimerGetTimerCounter());
                }

                break;
            }
        }
    }

    return usTime;
}

//--------------------------------------------------
// Description  : Search a timer event
// Input Value  : ucEventID --> Event which has been activated
// Output Value : None
//--------------------------------------------------
bit ScalerTimerSearchActiveTimerEvent(EnumScalerTimerEventID enumEventID)
{
    BYTE ucEventIndex = 0;

    // Search Correponding EventID and wait until it finished
    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_EVENT_ID(ucEventIndex) == enumEventID)
        {
            if(GET_EVENT_VALID(ucEventIndex) == _TRUE)
            {
                return _TRUE;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check timer and events. We have to run this function when setting up a timer for an event.
// Input Value  : usTime    --> Unit in 1ms, range in 0.001 ~ 61sec
// Output Value : Return usPresentTime
//--------------------------------------------------
WORD ScalerTimerCheckTimerEvent(WORD usTime)
{
    BYTE ucTimerEventCnt = 0;
    WORD usPresentTime = 0;

    usPresentTime = ScalerTimerGetTimerCounter();

    if(usTime > _EVENT_TIME_MAX)
    {
        usTime = _EVENT_TIME_MAX;
    }

    if((usPresentTime > (_EVENT_TIME_MAX - usTime)) || // Size Limit of Timer Counter
       (usPresentTime > (0xFFFF - usTime))) // Timer Counter Overflow
    {
        STORE_TIMER_COUNTER(0);

        // Reset Timer Event Counter
        for(ucTimerEventCnt = 0; ucTimerEventCnt < _TIMER_EVENT_COUNT; ucTimerEventCnt++)
        {
            if(GET_EVENT_VALID(ucTimerEventCnt) == _TRUE)
            {
                if(GET_EVENT_TIME(ucTimerEventCnt) > usPresentTime)
                {
                    SET_EVENT_TIME(ucTimerEventCnt, (GET_EVENT_TIME(ucTimerEventCnt) - usPresentTime));
                }
                else
                {
                    SET_EVENT_TIME(ucTimerEventCnt, 0);
                }
            }
        }

        usPresentTime = 0;
    }

    return usPresentTime;
}


//--------------------------------------------------
// Description  : Get Timer Counter.
// Input Value  : None
// Output Value : Timer Counter
//--------------------------------------------------
WORD ScalerTimerGetTimerCounter(void)
{
    WORD usPresentTime = g_usTimerCounter;

    if(usPresentTime != (g_usTimerCounterDoubleBuffer - 1))
    {
        return g_usTimerCounterDoubleBuffer - 1;
    }

    return usPresentTime;
}

//--------------------------------------------------
// Description  : Get Event ID
// Input Value  : Referenced Event Index
// Output Value : Stored Event ID
//--------------------------------------------------
BYTE ScalerTimerGetEventID(BYTE ucEventIndex)
{
    return GET_EVENT_ID(ucEventIndex);
}

//--------------------------------------------------
// Description  : Initial timer and events. We have to run this function at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTimerInitialTimerEvent(void)
{
    BYTE ucTimerEventCnt = 0;

    for(ucTimerEventCnt = 0; ucTimerEventCnt < _TIMER_EVENT_COUNT; ucTimerEventCnt++)
    {
        CLR_EVENT_VALID(ucTimerEventCnt);
    }

    ScalerTimerSetRunStatus(_TIMER_2, _ON);
}

//--------------------------------------------------
// Description  : Timer Delay
// Input Value  : usNum --> Delay in ms
// Output Value : None
//--------------------------------------------------
void ScalerTimerDelayXms(WORD usNum)
{
    if(usNum != 0)
    {
        WORD usStart1msTimerCnt = g_usTimerCounter;

        SET_TIMER2_INT_STATUS(_FALSE);

        while(_TRUE)
        {
            if(GET_TIMER2_INT_STATUS() == _TRUE)
            {
                SET_TIMER2_INT_STATUS(_FALSE);

                WORD usCurrent1msTimerCnt = g_usTimerCounter;

                if(usCurrent1msTimerCnt != usStart1msTimerCnt)
                {
                    WORD usDiffCnt = 0;

                    if(usCurrent1msTimerCnt > usStart1msTimerCnt)
                    {
                        usDiffCnt = usCurrent1msTimerCnt - usStart1msTimerCnt;
                    }
                    else
                    {
                        usDiffCnt = usCurrent1msTimerCnt + (0xFFFF - usStart1msTimerCnt + 1);
                    }

                    if(usDiffCnt >= usNum)
                    {
                        return;
                    }
                }
            }
        }
    }
}

//----------------------------------------------------------------------
// Description  : Polling XRAM Flag Process
// Input Value  : usTimeout --> Timeout number (Max: 65,535 ms)
//                ulXRAMAddr--> XRAM Addr
//                ucBit     --> Polling Bit
//                bSuccess  --> 1 or 0 when finished for Polling Bit
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------
bit ScalerTimerPollingXRAMFlagProc(WORD usTimeout, DWORD ulXRAMAddr, BYTE ucBit, bit bSuccess)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;

    usPreviousTime = g_usTimerCounter;

    do
    {
        if(((bit)((*((volatile BYTE *)(ulXRAMAddr))) & (ucBit)) ^ bSuccess) == _FALSE)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }while(usTimeElapsed <= usTimeout);

    return _FALSE;
}

__attribute__((alias("ScalerTimerPollingXRAMFlagProc")))
bit ScalerTimerPollingXRAMFlagProc_EXINT0(WORD usTimeout, DWORD ulXRAMAddr, BYTE ucBit, bit bSuccess);

__attribute__((alias("ScalerTimerPollingXRAMFlagProc")))
bit ScalerTimerPollingXRAMFlagProc_WDINT(WORD usTimeout, DWORD ulXRAMAddr, BYTE ucBit, bit bSuccess);

//----------------------------------------------------------------------
// Description  : Polling Scaler Flag Process
// Input Value  : usTimeout --> Timeout number (Max: 65,535 ms)
//                usRegister--> Current Register
//                ucBit     --> Polling Bit
//                bSuccess  --> 1 or 0 when finished for Polling Bit
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------
bit ScalerTimerPollingFlagProc(WORD usTimeout, WORD usRegister, BYTE ucBit, bit bSuccess)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;

    usPreviousTime = g_usTimerCounter;

    do
    {
        if(((bit)ScalerGetBit(usRegister, ucBit) ^ bSuccess) == _FALSE)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }while(usTimeElapsed <= usTimeout);

    return _FALSE;
}

__attribute__((alias("ScalerTimerPollingFlagProc")))
bit ScalerTimerPollingFlagProc_EXINT0(WORD usTimeout, WORD usRegister, BYTE ucBit, bit bSuccess);

__attribute__((alias("ScalerTimerPollingFlagProc")))
bit ScalerTimerPollingFlagProc_WDINT(WORD usTimeout, WORD usRegister, BYTE ucBit, bit bSuccess);


//----------------------------------------------------------------------
// Description  : Polling Scaler Flag Process
// Input Value  : usTimeout --> Timeout number (Max: 65,535 ms)
//                ulRegister--> Current Register
//                ulBit     --> Polling Bit
//                ulSuccess  --> 1 or 0 when finished for Polling Bit
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------
bit ScalerTimerPollingFlagProc32Bit(DWORD ulTimeout, DWORD ulRegister, DWORD ulBit, DWORD ulbSuccess)
{
    DWORD ulTimeElapsed = 0;
    WORD usPreviousTime = g_usTimerCounter;

    do
    {
        BYTE ucTmpFlag = Scaler32GetBit(ulRegister, ulBit) ? 1 : 0;

        if(ucTmpFlag == ulbSuccess)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            ulTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }while(ulTimeElapsed <= ulTimeout);

    return _FALSE;
}


//----------------------------------------------------------------------
// Description  : Polling Scaler Flag Process
// Input Value  : ucTimeout --> Timeout number (Max: 255 ms)
//                ucRegister--> Current Register
//                ucBit     --> Polling Bit
//                bSuccess  --> 1 or 0 when finished for Polling Bit
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------
bit ScalerTimerPollingDataBitFlagProc(WORD usTimeout, WORD usRegister, BYTE ucValue, BYTE ucBit, bit bSuccess)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;

    usPreviousTime = g_usTimerCounter;

    do
    {
        if(((bit)ScalerGetDataPortBit(usRegister, ucValue, ucBit) ^ bSuccess) == _FALSE)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while(usTimeElapsed <= usTimeout);

    return _FALSE;
}

//----------------------------------------------------------------------
// Description  : Polling Scaler Flag Process
// Input Value  : usTimeout --> Timeout number (Max: 65,535 ms)
//                usPortAddress--> Current Port Address
//                ucRegister--> Current Port Register
//                ucBit     --> Polling Bit
//                bSuccess  --> 1 or 0 when finished for Polling Bit
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------
bit ScalerTimerPollingPortFlagProc(WORD usTimeout, WORD usPortAddress, BYTE ucRegister, BYTE ucBit, bit bSuccess)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;

    usPreviousTime = g_usTimerCounter;

    do
    {
        if(((bit)ScalerGetDataPortBit(usPortAddress, ucRegister, ucBit) ^ bSuccess) == _FALSE)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }while(usTimeElapsed <= usTimeout);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if Event is Valid
// Input Value  : ucEventID --> Event which has been activated
// Output Value : None
//--------------------------------------------------
void ScalerTimerWaitForActiveTimerEvent(EnumScalerTimerEventID enumEventID)
{
    ScalerTimerDelayXms(ScalerTimerGetEventRemainTime(enumEventID));
    ScalerTimerCancelTimerEvent(enumEventID);
}

//--------------------------------------------------
// Description  : Clear Event Status
// Input Value  : enumEvent   --> Specified event
// Output Value : None
//--------------------------------------------------
void ScalerTimerClrDDomainEventStatus(EnumWaitDDomainEventType enumEvent)
{
    switch(enumEvent)
    {
        case _EVENT_DEN_START:
            // Total
            ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT2);
            break;

        case _EVENT_DEN_STOP:
            // Total
            ScalerSetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT4);
            break;

        case _EVENT_DVS:
            ScalerSetByte(PC0_02_DDOMAIN_IRQ_WD_CTRL1, _BIT6);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : enumEvent   --> Specified event
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
BYTE ScalerTimerGetDDomainEventStatus(EnumWaitDDomainEventType enumEvent)
{
    switch(enumEvent)
    {
        case _EVENT_DEN_START:
            // Total
            return ((ScalerGetByte(PC0_02_DDOMAIN_IRQ_WD_CTRL1) & _BIT2) << 2);

        case _EVENT_DEN_STOP:
            // Total
            return ((ScalerGetByte(PC0_02_DDOMAIN_IRQ_WD_CTRL1) & _BIT4) << 1);

        case _EVENT_DVS:
            return (ScalerGetByte(PC0_02_DDOMAIN_IRQ_WD_CTRL1) & _BIT6);

        default:
            return 0;
    }
}

//--------------------------------------------------
// Description  : Hold until the specified event occurs by register
// Input Value  : enumEvent   --> Specified event
//                Input Data Path Page
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit ScalerTimerWaitForIDomainEventByReg(EnumWaitIDomainEventType enumEvent, BYTE ucIRQPageOffset)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;
    BYTE ucEventData = enumEvent;

    // Clear status (status register will be cleared after write)
    ScalerSetByte(P0_A2_M1_EVENT_FLAG + ucIRQPageOffset, ucEventData);

    usPreviousTime = g_usTimerCounter;

    do
    {
        if((ScalerGetByte(P0_A2_M1_EVENT_FLAG + ucIRQPageOffset) & ucEventData) == ucEventData)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while(usTimeElapsed <= _TIMER_WAIT_EVENT_TIMEOUT);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : enumEvent   --> Specified event
//                enumInputDataPath --> I-domain data path
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit ScalerTimerWaitForIDomainEvent(EnumWaitIDomainEventType enumEvent, EnumInputDataPath enumInputDataPath)
{
    BYTE ucIRQPageOffset = 0;

    enumInputDataPath = ScalerGlobalGetIDomainInputDataPath(enumEvent, enumInputDataPath);

    if(enumInputDataPath == _INPUT_PATH_NONE)
    {
        return _FALSE;
    }

    ucIRQPageOffset = ScalerIDomainGetIRQPageOffset(enumInputDataPath);

    return ScalerTimerWaitForIDomainEventByReg(enumEvent, ucIRQPageOffset);
}

//--------------------------------------------------
// Description  : Hold until the specified event occurs by register
// Input Value  : enumEvent   --> Specified event
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit ScalerTimerWaitForDDomainEventByReg(EnumWaitDDomainEventType enumEvent)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;
    WORD usEventFlagAddr = 0xFF;
    BYTE ucEventData = enumEvent;

    switch(enumEvent)
    {
        case _EVENT_DVS:
        case _EVENT_DEN_START:
        case _EVENT_DEN_STOP:
            usEventFlagAddr = PC0_03_EVENT_FLAG; // Total DEN
            if(enumEvent == _EVENT_DEN_STOP)
            {
                ucEventData = _BIT7;
            }
            else if(enumEvent == _EVENT_DEN_START)
            {
                ucEventData = _BIT6;
            }
            else
            {
                ucEventData = _BIT5;
            }
            break;

        default:
            return _FALSE;
    }

    // Clear status (status register will be cleared after write)
    ScalerSetByte(usEventFlagAddr, ucEventData);

    usPreviousTime = g_usTimerCounter;

    do
    {
        if((ScalerGetByte(usEventFlagAddr) & ucEventData) == ucEventData)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while(usTimeElapsed <= _TIMER_WAIT_EVENT_TIMEOUT);

    return _FALSE;
}

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
//--------------------------------------------------
// Description  : Hold until DEN_START event occurs by flag
// Input Value  : None
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit ScalerTimerWaitForDDenStartEventByFlag(void)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;

    SET_EVENT_DEN_START_INT(_FALSE);

    usPreviousTime = g_usTimerCounter;

    do
    {
        if(GET_EVENT_DEN_START_INT() == _TRUE)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while(usTimeElapsed <= _TIMER_WAIT_EVENT_TIMEOUT);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Hold until DEN_STOP event occurs by flag
// Input Value  : None
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit ScalerTimerWaitForDDenStopEventByFlag(void)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;

    SET_EVENT_DEN_STOP_INT(_FALSE);

    usPreviousTime = g_usTimerCounter;

    do
    {
        if(GET_EVENT_DEN_STOP_INT() == _TRUE)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while(usTimeElapsed <= _TIMER_WAIT_EVENT_TIMEOUT);

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : enumEvent   --> Specified event
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit ScalerTimerWaitForDDomainEvent(EnumWaitDDomainEventType enumEvent)
{
    if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
       (GET_DPLL_POWER_STATUS() == _FALSE))
    {
        // Display format gen disabled or DPLL power down
        return _FALSE;
    }

    switch(enumEvent)
    {
        case _EVENT_DVS:
#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
            if(ScalerGetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, _BIT7) == _BIT7)
            {
                return ScalerTimerWaitForDDenStartEventByFlag();
            }
            else
#endif
            {
                return ScalerTimerWaitForDDomainEventByReg(enumEvent);
            }
            break;

        case _EVENT_DEN_START:

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
            if(ScalerGetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, _BIT3) == _BIT3)
            {
                return ScalerTimerWaitForDDenStartEventByFlag();
            }
            else
#endif
            {
                return ScalerTimerWaitForDDomainEventByReg(enumEvent);
            }
            break;

        case _EVENT_DEN_STOP:

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
            if(ScalerGetBit(PC0_02_DDOMAIN_IRQ_WD_CTRL1, _BIT5) == _BIT5)
            {
                return ScalerTimerWaitForDDenStopEventByFlag();
            }
            else
#endif
            {
                return ScalerTimerWaitForDDomainEventByReg(enumEvent);
            }
            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Watch Dog Reference Clk Change
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDRefClkChange(void)
{
    if(ScalerTimerGetEnable(_CPU_TIMER_2) == _TRUE)
    {
        // Manual Trigger WD_Timer INT to Proc WDTimerProc_WDINT
        g_ulTimerChangeClkCurrentTime = ScalerTimerGetCurrentValue(_CPU_TIMER_2);
        ScalerTimerSetTargetValue(_CPU_TIMER_2, 2);
    }
    else
    {
        SET_PREVIOUS_WD_REF_CLK_KHZ(GET_CURRENT_WD_REF_CLK_KHZ());
    }
}

//--------------------------------------------------
// Description  : Activate Watch Dog Timer
//                Acceptable Event Time should be between 10 ~ 500ms (for 14.318M) or 5 ~ 250ms (for 27M)
// Input Value  : usTimeMS --> time(in ms)
//                enumEventID --> WD Event ID
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDUpdateTimerEventTable(WORD usTimeMS, EnumScalerWDTimerEventID enumEventID)
{
    BYTE ucIndex = 0;
    BYTE ucEventIndex = 0;

    BYTE ucIntStatus = GET_INTERRUPT_GLOBAL_ENABLE_STATUS();
    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

    // Calculate Target WD Count
    DWORD ulTargetTimerCnt = ((DWORD)usTimeMS * GET_TIMER32_1MS_TICK_COUNT());

    for(ucIndex = 0; ucIndex < _WD_TIMER_EVENT_COUNT; ucIndex++)
    {
        if(GET_WD_EVENT_VALID(ucIndex) == _FALSE)
        {
            DWORD ulCurrentTimerCnt = ScalerTimerGetCurrentValue(_CPU_TIMER_2);
            DWORD ulTargetCntValue = ScalerTimerGetTargetValue(_CPU_TIMER_2);
            DWORD ulTargetRemainCntValue = ulTargetCntValue - ulCurrentTimerCnt;

            SET_WD_EVENT_ID(ucIndex, enumEventID);

            if(ulTargetTimerCnt < ulTargetRemainCntValue)
            {
                // The New Add Event happen before current event
                if(ulTargetTimerCnt < 2)
                {
                    // Threshold Set < 2 will Induce HW IRQ can't happen
                    ulTargetTimerCnt = 2;
                }
                if(ulTargetCntValue == _TIMER32_MAX_COUNT)
                {
                    // WDT is idle now
                    ScalerTimerSetEnable(_CPU_TIMER_2, _ENABLE);
                }
                // counter will be reset to 0 and begin to count, trigger INT when curr_cnt = target_cnt and continue count to 0xFFFFFFFF after INT triggered
                ScalerTimerSetTargetValue(_CPU_TIMER_2, ulTargetTimerCnt);

                // Clear WD Timer Count
                CLR_MCU_WATCH_DOG();

                SET_WD_EVENT_TIME(ucIndex, ulTargetTimerCnt);

                // Modify the Remain Time of Every Other Valid Event (Use Event ID as Temporariy Variable)
                for(ucEventIndex = 0; ucEventIndex < _WD_TIMER_EVENT_COUNT; ucEventIndex++)
                {
                    if((GET_WD_EVENT_VALID(ucEventIndex) == _FALSE) || (ucEventIndex == ucIndex))
                    {
                        continue;
                    }
                    else
                    {
                        SET_WD_EVENT_TIME(ucEventIndex, ((GET_WD_EVENT_TIME(ucEventIndex) > ulCurrentTimerCnt) ? (GET_WD_EVENT_TIME(ucEventIndex) - ulCurrentTimerCnt) : 0));
                    }
                }
            }
            else
            {
                // The New Add Event happen after current event
                SET_WD_EVENT_TIME(ucIndex, (ulTargetTimerCnt + ulCurrentTimerCnt));
            }
            break;
        }
    }
    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(ucIntStatus);
}

//--------------------------------------------------
// Description  : Activate Watch Dog Timer
//                Acceptable Event Time should be between 10 ~ 500ms (for 14.318M) or 5 ~ 250ms (for 27M)
// Input Value  : usTimeMS --> time(in ms)
//                enumEventID --> WD Event ID
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDActivateTimerEvent(WORD usTimeMS, EnumScalerWDTimerEventID enumEventID)
{
    if(g_bTimerWDEventProcessNowFlag == _FALSE)
    {
#if((_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_COPROCESSOR) && ((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON)))
        g_pstScpuSyncToKcpuCmd->unCmdBody.stCpuSyncWDTimerEventCmd.enumWDTimerEventAction = _WD_TIMER_EVENT_ACTIVATE;
        g_pstScpuSyncToKcpuCmd->unCmdBody.stCpuSyncWDTimerEventCmd.usEventID = (WORD)enumEventID;
        g_pstScpuSyncToKcpuCmd->unCmdBody.stCpuSyncWDTimerEventCmd.usTimeMS = usTimeMS;
        ScalerScpuSyncSendCmd(_SYSTEM_CPU_SYNC_WD_EVENT, _SYSTEM_CPU_SYNC_TIMEOUT_WDT_EVENT, _NULL_POINTER);
#else
        ScalerTimerWDUpdateTimerEventTable(usTimeMS, enumEventID);
#endif
    }
    else
    {
        // defer activate WDT event process
#if((_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_COPROCESSOR) && ((_SCPU_SUPPORT == _ON) && (_IS_MAIN_PROCESS_CPU == _FALSE)))
        if(g_ucTimerScpuDeferActiveWDIndex > g_ucTimerKcpuDeferActiveWDIndex)
        {
            BYTE ucIntStatus = GET_INTERRUPT_GLOBAL_ENABLE_STATUS();
            SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);
            g_ucTimerScpuDeferActiveWDIndex--;
            SET_INTERRUPT_GLOBAL_ENABLE_STATUS(ucIntStatus);
            g_pucTimerDeferActiveWDID[g_ucTimerScpuDeferActiveWDIndex] = enumEventID;
            g_pucTimerDeferActiveWDTime[g_ucTimerScpuDeferActiveWDIndex] = usTimeMS;
        }
#else
#if((_SCPU_SUPPORT == _ON) &&\
    ((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)))
        if(g_ucTimerKcpuDeferActiveWDIndex < g_ucTimerScpuDeferActiveWDIndex)
#else
        if(g_ucTimerKcpuDeferActiveWDIndex < _WD_TIMER_EVENT_COUNT)
#endif
        {
            BYTE ucIntStatus = GET_INTERRUPT_GLOBAL_ENABLE_STATUS();
            SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);
            g_pucTimerDeferActiveWDID[g_ucTimerKcpuDeferActiveWDIndex] = enumEventID;
            g_pucTimerDeferActiveWDTime[g_ucTimerKcpuDeferActiveWDIndex] = usTimeMS;
            g_ucTimerKcpuDeferActiveWDIndex++;
            SET_INTERRUPT_GLOBAL_ENABLE_STATUS(ucIntStatus);
        }
#endif
    }
}

__attribute__((alias("ScalerTimerWDActivateTimerEvent")))
void ScalerTimerWDActivateTimerEvent_WDINT(WORD usTimeMS, EnumScalerWDTimerEventID enumEventID);

__attribute__((alias("ScalerTimerWDActivateTimerEvent")))
void ScalerTimerWDActivateTimerEvent_EXINT0(WORD usTimeMS, EnumScalerWDTimerEventID enumEventID);

//--------------------------------------------------
// Description  : Cancel WD Timer Event (Only for EXINT0)
// Input Value  : ucEventID => Event ID
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDCancelTimerEvent(EnumScalerWDTimerEventID enumEventID)
{
#if((_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_COPROCESSOR) && ((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON)))
    g_pstScpuSyncToKcpuCmd->unCmdBody.stCpuSyncWDTimerEventCmd.enumWDTimerEventAction = _WD_TIMER_EVENT_CANCEL;
    g_pstScpuSyncToKcpuCmd->unCmdBody.stCpuSyncWDTimerEventCmd.usEventID = (WORD)enumEventID;
    ScalerScpuSyncSendCmd(_SYSTEM_CPU_SYNC_WD_EVENT, _SYSTEM_CPU_SYNC_TIMEOUT_WDT_EVENT, _NULL_POINTER);
#else
    BYTE ucIndex = 0;
    BYTE ucIntStatus = GET_INTERRUPT_GLOBAL_ENABLE_STATUS();
    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);
    for(ucIndex = 0; ucIndex < _WD_TIMER_EVENT_COUNT; ucIndex++)
    {
        if(GET_WD_EVENT_ID(ucIndex) == enumEventID)
        {
            CLR_WD_EVENT_VALID(ucIndex);
            break;
        }
    }
    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(ucIntStatus);
#endif
}

__attribute__((alias("ScalerTimerWDCancelTimerEvent")))
void ScalerTimerWDCancelTimerEvent_EXINT0(EnumScalerWDTimerEventID enumEventID);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_TCPM_SUPPORT == _ON))
__attribute__((alias("ScalerTimerWDCancelTimerEvent")))
void ScalerTimerWDCancelTimerEvent_WDINT(EnumScalerWDTimerEventID enumEventID);
#endif

//--------------------------------------------------
// Description  : Watch Dog Timer Event Processor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDEventProcess(BYTE *pucActiveWDID, BYTE *pucActiveWDTime)
{
    if((ScalerTimerGetINTFlag(_CPU_TIMER_2) == _TRUE) || (GET_CURRENT_WD_REF_CLK_KHZ() != GET_PREVIOUS_WD_REF_CLK_KHZ()))
    {
        DWORD ulNextTime = _TIMER32_MAX_COUNT;
        DWORD ulCurrentTimerCnt = g_ulTimerPrevWdtEventProcessTime;

        if((g_ulTimerChangeClkCurrentTime != 0) && (ScalerTimerGetTargetValue(_CPU_TIMER_2) == 2))
        {
            ulCurrentTimerCnt += g_ulTimerChangeClkCurrentTime;
        }
        else
        {
            ulCurrentTimerCnt += ScalerTimerGetCurrentValue(_CPU_TIMER_2);
        }

        // Clear Watch Dog
        CLR_MCU_WATCH_DOG();

        // Clear Overflow Flag
        ScalerTimerAckINTFlag(_CPU_TIMER_2);

#if(_DP_SUPPORT == _ON)
        ScalerDpAuxRxEnterIntSetting_WDINT();
#endif

        for(BYTE ucIndex = 0; ucIndex < _WD_TIMER_EVENT_COUNT; ucIndex++)
        {
            if(GET_WD_EVENT_VALID(ucIndex) == _TRUE)
            {
                if(GET_WD_EVENT_TIME(ucIndex) <= ulCurrentTimerCnt)
                {
                    ScalerTimerWDEventHandler_WDINT(ucIndex, &pucActiveWDID[ucIndex], &pucActiveWDTime[ucIndex]);
                }
                else
                {
                    if(GET_CURRENT_WD_REF_CLK_KHZ() == GET_PREVIOUS_WD_REF_CLK_KHZ())
                    {
                        // Calculate Remain Event Time
                        SET_WD_EVENT_TIME(ucIndex, ((GET_WD_EVENT_TIME(ucIndex) > ulCurrentTimerCnt) ? (GET_WD_EVENT_TIME(ucIndex) - ulCurrentTimerCnt) : 0));
                    }
                    else
                    {
                        // Calculate Remain Event Time; M2PLL -> iosc
                        SET_WD_EVENT_TIME(ucIndex, ((GET_WD_EVENT_TIME(ucIndex) > ulCurrentTimerCnt) ? (GET_DWORD_MUL_DIV((GET_WD_EVENT_TIME(ucIndex) - ulCurrentTimerCnt), GET_CURRENT_WD_REF_CLK_KHZ(), GET_PREVIOUS_WD_REF_CLK_KHZ())) : 0));
                    }

                    // Set Next Execute Time
                    if(GET_WD_EVENT_TIME(ucIndex) < ulNextTime)
                    {
                        ulNextTime = GET_WD_EVENT_TIME(ucIndex);
                    }
                }
            }
        }

#if(_DP_SUPPORT == _ON)
        ScalerDpAuxRxExitIntSetting_WDINT();
#endif

        if(ulNextTime == _TIMER32_MAX_COUNT)
        {
            // No Active WDT Event need to process
            ScalerTimerSetTargetValue(_CPU_TIMER_2, ulNextTime);
            ScalerTimerSetEnable(_CPU_TIMER_2, _DISABLE);
            g_ulTimerPrevWdtEventProcessTime = 0;
        }
        else
        {
            // Calculate WDT Event spend time
            if((g_ulTimerChangeClkCurrentTime != 0) && (ScalerTimerGetTargetValue(_CPU_TIMER_2) == 2))
            {
                g_ulTimerPrevWdtEventProcessTime = ScalerTimerGetCurrentValue(_CPU_TIMER_2);
            }
            else
            {
                g_ulTimerPrevWdtEventProcessTime = ScalerTimerGetCurrentValue(_CPU_TIMER_2) - (ulCurrentTimerCnt - g_ulTimerPrevWdtEventProcessTime);
            }

            if(g_ulTimerPrevWdtEventProcessTime > ulNextTime)
            {
                // Threshold Set < 2 will Induce TIMER32 HW IRQ can't happen
                ScalerTimerSetTargetValue(_CPU_TIMER_2, 2);
            }
            else
            {
                ulNextTime = ulNextTime - g_ulTimerPrevWdtEventProcessTime;
                if(ulNextTime < 2)
                {
                    ulNextTime = 2;
                }
                ScalerTimerSetTargetValue(_CPU_TIMER_2, ulNextTime);
            }
        }

        g_ulTimerChangeClkCurrentTime = 0;

        SET_PREVIOUS_WD_REF_CLK_KHZ(GET_CURRENT_WD_REF_CLK_KHZ());
    }
}

__attribute__((alias("ScalerTimerWDEventProcess")))
void ScalerTimerWDEventProcess_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime);

