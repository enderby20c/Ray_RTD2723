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
// ID Code      : SysTimer.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_TIMER__

#include "SysInclude.h"
#include "Timer/SysTimer.h"

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
// Description  : Timer Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTimerHandler(void)
{
    BYTE ucTimerEventIndex = 0;
    BYTE ucTimerEventID = 0;

    for(ucTimerEventIndex = 0; ucTimerEventIndex < _TIMER_EVENT_COUNT; ucTimerEventIndex++)
    {
        if((ScalerTimerCheckEventValid(ucTimerEventIndex) == _TRUE) &&
           (ScalerTimerGetTimerCounter() > ScalerTimerGetEventTime(ucTimerEventIndex)))
        {
            ucTimerEventID = ScalerTimerGetEventID(ucTimerEventIndex);
            ScalerTimerClrEventValid(ucTimerEventIndex);

            if(ucTimerEventID < _USER_TIMER_EVENT_END)
            {
                UserInterfaceTimerEventProc(ucTimerEventID);
            }
            else if(ucTimerEventID < _SYSTEM_TIMER_EVENT_END)
            {
                SysTimerEventProc(ucTimerEventID);
            }
            else
            {
                ScalerTimerEventProc(ucTimerEventID);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Timer Event Process
// Input Value  : enumEventID --> Event to be processed
// Output Value : None
//--------------------------------------------------
void SysTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
        case _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING:

            if(SysSourceEnterPowerSavingCheck() == _TRUE)
            {
                SysSourceClearDetectingEvent();
            }

            break;

        case _SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE:
            SET_MODE_ACTIVE_READY();
            break;

        case _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE:

            // Set no support flag for current display setting target
            SET_RGN_DISPLAY_ACTION(GET_MODE_DISPLAY_TARGET_INDEX(), _DISPLAY_ACTION_OOR);

            DebugMessageSystem("Display OOR", GET_MODE_DISPLAY_TARGET_INDEX());

            break;

        case _SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE:

            // Set no support flag for current display setting target
            SET_RGN_DISPLAY_ACTION(GET_SOURCE_MEASURE_TARGET_INDEX(), _DISPLAY_ACTION_OOR);

            // Clear display stop flag
            CLR_RGN_MEASURE_CHECKING(GET_SOURCE_MEASURE_TARGET_INDEX());

            DebugMessageSystem("Source OOR", GET_SOURCE_MEASURE_TARGET_INDEX());

            break;

        case _SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE:

            DebugMessageSystem("Measure Timeout", GET_SOURCE_MEASURE_TARGET_INDEX());

            // Reset region interface
            SysSourceResetRegion(GET_SOURCE_MEASURE_TARGET_INDEX());

            // Switch to NSG, if not already there
            if((GET_RGN_DISPLAY_STATE(GET_SOURCE_MEASURE_TARGET_INDEX()) != _DISPLAY_STATE_NO_SIGNAL) &&
               (GET_RGN_DISPLAY_ACTION(GET_SOURCE_MEASURE_TARGET_INDEX()) != _DISPLAY_ACTION_NO_SIGNAL))
            {
                SysRegionSetDisplayStateBySearchIndex(GET_RGN_SOURCE_INDEX(GET_SOURCE_MEASURE_TARGET_INDEX()), _DISPLAY_STATE_NO_SIGNAL);
            }

            break;

        case _SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF:

#if(_DP_SUPPORT == _ON)
            SysDpPowerFakeOffToOffProc();
#endif

            SET_TARGET_POWER_STATUS(_POWER_STATUS_OFF);

            break;

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_POWER_FAKE_SAVING_TO_SAVING:

#if(_DP_SUPPORT == _ON)
            SysDpPowerFakeSavingToSavingProc();
#endif

            break;
#endif

        case _SYSTEM_TIMER_EVENT_PANEL_BACKLIGHT_ON:
            UserInterfacePowerPanelTimerEventHandler(_READY_FOR_BACKLIGHT);
            break;

        case _SYSTEM_TIMER_EVENT_PANEL_POWER_OFF:
            UserInterfacePowerPanelTimerEventHandler(_PANEL_POWER_OFF_STATE);

#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _ON)
            if((GET_PANELPOWERACTION() == _PANEL_ON) ||
               (GET_PANELPOWERACTION() == _BACKLIGHT_ON))
            {
                UserCommonPowerPanelAction(GET_PANELPOWERACTION());
            }
#endif
            break;

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT:
            SET_SOURCE_HDMI_SWITCH_TIMEOUT();
            break;
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)
        case _SYSTEM_TIMER_EVENT_SOURCE_ASUS_START_AUTO:
            SET_SOURCE_ASUS_START_AUTO();
            SET_SOURCE_ASUS_FIRST_START_AUTO();
            break;
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
        case _SYSTEM_TIMER_EVENT_SOURCE_EIZO_SEARCH_FINISH:
            if(UserInterfaceSourceAdjustOsdCheckTotalSearchFinish() == _AUTO_SEARCH_TRUE)
            {
                SET_SOURCE_SWITCH_FINISH();
                CLR_SOURCE_DETECTING();
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

                if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
                {
                    BYTE ucRegionIndex = 0;
                    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

                    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ucRegionIndex++)
                    {
                        if((GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _FALSE) &&
                           (GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_NONE) &&
                           (GET_RGN_DISPLAY_ACTION(ucRegionIndex) == _DISPLAY_ACTION_NO_ACTION))
                        {
                            SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_NO_SIGNAL);
                        }
                    }
                }
            }
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_SOURCE_DP_DUAL_SWITCH_TIMEOUT:
            SET_SOURCE_DP_DUAL_SWITCH_TIMEOUT();
            break;
#endif

#if(_AUDIO_SUPPORT == _ON)
#if(_EMBEDDED_DAC_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_INITIAL:
            ScalerAudioDACSetState(_AUDIO_DAC_CHARGE);
            break;

        case _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_CHARGE:
            ScalerAudioDACSetState(_AUDIO_DAC_DEPOP);
            break;

        case _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL:
            ScalerAudioDACDepopToNormal();
            break;
#endif // End of #if(_EMBEDDED_DAC_SUPPORT == _ON)
#endif

#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
        case _SYSTEM_TIMER_EVENT_USB_U2HOST_DETECT:

            SET_U2HOST_CONNECT_DET_READY_FLAG();

            break;
#endif
#endif

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_LOCAL_POWER_DETECT:

            SysUsbTypeCSetLocalPowerDetection();

            break;
#endif

#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D0_TYPE_C_CONNECTION_DET:

            SysUsbTypeCConnectionDetCtrl(_D0_TYPE_C_PORT, _ENABLE);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_D0_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT:

            SysUsbTypeCSetLenovoRcvDeviceTypeTimeout(_D0_TYPE_C_PORT);

            break;
#endif

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _SYSTEM_TIMER_EVENT_D0_TYPE_C_STATUS_DETECT:

            UserCommonUsbTypeCRtsSetStatusDetection(_D0_TYPE_C_PORT);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_D0_TYPE_C_LENOVO_ALT_MODE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoAltModeDetection(_D0_TYPE_C_PORT);

            break;

        case _SYSTEM_TIMER_EVENT_D0_TYPE_C_LENOVO_DEVICE_TYPE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoDeviceTypeDetection(_D0_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _SYSTEM_TIMER_EVENT_D0_TYPE_C_RTD_STATUS_DETECT:

            UserCommonUsbTypeCRtdStatusDetCtrl(_D0_TYPE_C_PORT, _ENABLE);

            break;
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_D0_USB_HUB_COMMUNICATION_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D0_USBHUB_DETECT:

            SysUsbHubSetDspDeviceDetectFlag(_D0_TYPE_C_PORT);

            break;
#endif

#if(_D0_TYPE_C_BILLBOARD_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D0_ENABLE_BILLBOARD:

            SysUsbBillBoardSetTimerEventFlag(_D0_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D1_TYPE_C_CONNECTION_DET:

            SysUsbTypeCConnectionDetCtrl(_D1_TYPE_C_PORT, _ENABLE);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_D1_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT:

            SysUsbTypeCSetLenovoRcvDeviceTypeTimeout(_D1_TYPE_C_PORT);

            break;
#endif

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _SYSTEM_TIMER_EVENT_D1_TYPE_C_STATUS_DETECT:

            UserCommonUsbTypeCRtsSetStatusDetection(_D1_TYPE_C_PORT);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_D1_TYPE_C_LENOVO_ALT_MODE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoAltModeDetection(_D1_TYPE_C_PORT);

            break;

        case _SYSTEM_TIMER_EVENT_D1_TYPE_C_LENOVO_DEVICE_TYPE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoDeviceTypeDetection(_D1_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _SYSTEM_TIMER_EVENT_D1_TYPE_C_RTD_STATUS_DETECT:

            UserCommonUsbTypeCRtdStatusDetCtrl(_D1_TYPE_C_PORT, _ENABLE);

            break;
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_D1_USB_HUB_COMMUNICATION_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D1_USBHUB_DETECT:

            SysUsbHubSetDspDeviceDetectFlag(_D1_TYPE_C_PORT);

            break;
#endif

#if(_D1_TYPE_C_BILLBOARD_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D1_ENABLE_BILLBOARD:

            SysUsbBillBoardSetTimerEventFlag(_D1_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D2_TYPE_C_CONNECTION_DET:

            SysUsbTypeCConnectionDetCtrl(_D2_TYPE_C_PORT, _ENABLE);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_D2_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT:

            SysUsbTypeCSetLenovoRcvDeviceTypeTimeout(_D2_TYPE_C_PORT);

            break;
#endif

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _SYSTEM_TIMER_EVENT_D2_TYPE_C_STATUS_DETECT:

            UserCommonUsbTypeCRtsSetStatusDetection(_D2_TYPE_C_PORT);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_D2_TYPE_C_LENOVO_ALT_MODE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoAltModeDetection(_D2_TYPE_C_PORT);

            break;

        case _SYSTEM_TIMER_EVENT_D2_TYPE_C_LENOVO_DEVICE_TYPE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoDeviceTypeDetection(_D2_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _SYSTEM_TIMER_EVENT_D2_TYPE_C_RTD_STATUS_DETECT:

            UserCommonUsbTypeCRtdStatusDetCtrl(_D2_TYPE_C_PORT, _ENABLE);

            break;
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_D2_USB_HUB_COMMUNICATION_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D2_USBHUB_DETECT:

            SysUsbHubSetDspDeviceDetectFlag(_D2_TYPE_C_PORT);

            break;
#endif

#if(_D2_TYPE_C_BILLBOARD_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D2_ENABLE_BILLBOARD:

            SysUsbBillBoardSetTimerEventFlag(_D2_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_USB_HUB_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_USB_HUB_DISABLE_DURATION_TIMEOUT:

            SET_USB_HUB_DISABLE_DURATION_TIMEOUT_FLAG();

            break;

#if(_D0_USB_HUB_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D0_USB_FROCE_ENABLE:

            SysUsbHubSetForceEnableTimerEventFlag(_D0_TYPE_C_PORT);

            break;
#endif  // End of #if(_D0_USB_HUB_SUPPORT == _ON)

#if(_D1_USB_HUB_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D1_USB_FROCE_ENABLE:

            SysUsbHubSetForceEnableTimerEventFlag(_D1_TYPE_C_PORT);

            break;
#endif  // End of #if(_D1_USB_HUB_SUPPORT == _ON)

#if(_D2_USB_HUB_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D2_USB_FROCE_ENABLE:

            SysUsbHubSetForceEnableTimerEventFlag(_D2_TYPE_C_PORT);

            break;
#endif  // End of #if(_D2_USB_HUB_SUPPORT == _ON)
#endif

#if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_P0_TYPE_C_CONNECTION_DET:

            SysUsbTypeCConnectionDetCtrl(_P0_TYPE_C_PORT, _ENABLE);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_P0_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT:

            SysUsbTypeCSetLenovoRcvDeviceTypeTimeout(_P0_TYPE_C_PORT);

            break;
#endif

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _SYSTEM_TIMER_EVENT_P0_TYPE_C_STATUS_DETECT:

            UserCommonUsbTypeCRtsSetStatusDetection(_P0_TYPE_C_PORT);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_P0_TYPE_C_LENOVO_ALT_MODE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoAltModeDetection(_P0_TYPE_C_PORT);

            break;

        case _SYSTEM_TIMER_EVENT_P0_TYPE_C_LENOVO_DEVICE_TYPE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoDeviceTypeDetection(_P0_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _SYSTEM_TIMER_EVENT_P0_TYPE_C_RTD_STATUS_DETECT:

            UserCommonUsbTypeCRtdStatusDetCtrl(_P0_TYPE_C_PORT, _ENABLE);

            break;
#endif  // End of #if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_P0_TYPE_C_BILLBOARD_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_P0_ENABLE_BILLBOARD:

            SysUsbBillBoardSetTimerEventFlag(_P0_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_P1_TYPE_C_CONNECTION_DET:

            SysUsbTypeCConnectionDetCtrl(_P1_TYPE_C_PORT, _ENABLE);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_P1_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT:

            SysUsbTypeCSetLenovoRcvDeviceTypeTimeout(_P1_TYPE_C_PORT);

            break;
#endif

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _SYSTEM_TIMER_EVENT_P1_TYPE_C_STATUS_DETECT:

            UserCommonUsbTypeCRtsSetStatusDetection(_P1_TYPE_C_PORT);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_P1_TYPE_C_LENOVO_ALT_MODE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoAltModeDetection(_P1_TYPE_C_PORT);

            break;

        case _SYSTEM_TIMER_EVENT_P1_TYPE_C_LENOVO_DEVICE_TYPE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoDeviceTypeDetection(_P1_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _SYSTEM_TIMER_EVENT_P1_TYPE_C_RTD_STATUS_DETECT:

            UserCommonUsbTypeCRtdStatusDetCtrl(_P1_TYPE_C_PORT, _ENABLE);

            break;
#endif  // End of #if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_P1_TYPE_C_BILLBOARD_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_P1_ENABLE_BILLBOARD:

            SysUsbBillBoardSetTimerEventFlag(_P1_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_P2_TYPE_C_CONNECTION_DET:

            SysUsbTypeCConnectionDetCtrl(_P2_TYPE_C_PORT, _ENABLE);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_P2_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT:

            SysUsbTypeCSetLenovoRcvDeviceTypeTimeout(_P2_TYPE_C_PORT);

            break;
#endif

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _SYSTEM_TIMER_EVENT_P2_TYPE_C_STATUS_DETECT:

            UserCommonUsbTypeCRtsSetStatusDetection(_P2_TYPE_C_PORT);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_P2_TYPE_C_LENOVO_ALT_MODE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoAltModeDetection(_P2_TYPE_C_PORT);

            break;

        case _SYSTEM_TIMER_EVENT_P2_TYPE_C_LENOVO_DEVICE_TYPE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoDeviceTypeDetection(_P2_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _SYSTEM_TIMER_EVENT_P2_TYPE_C_RTD_STATUS_DETECT:

            UserCommonUsbTypeCRtdStatusDetCtrl(_P2_TYPE_C_PORT, _ENABLE);

            break;
#endif  // End of #if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_P2_TYPE_C_BILLBOARD_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_P2_ENABLE_BILLBOARD:

            SysUsbBillBoardSetTimerEventFlag(_P2_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_P3_TYPE_C_CONNECTION_DET:

            SysUsbTypeCConnectionDetCtrl(_P3_TYPE_C_PORT, _ENABLE);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_P3_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT:

            SysUsbTypeCSetLenovoRcvDeviceTypeTimeout(_P3_TYPE_C_PORT);

            break;
#endif

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _SYSTEM_TIMER_EVENT_P3_TYPE_C_STATUS_DETECT:

            UserCommonUsbTypeCRtsSetStatusDetection(_P3_TYPE_C_PORT);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_P3_TYPE_C_LENOVO_ALT_MODE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoAltModeDetection(_P3_TYPE_C_PORT);

            break;

        case _SYSTEM_TIMER_EVENT_P3_TYPE_C_LENOVO_DEVICE_TYPE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoDeviceTypeDetection(_P3_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _SYSTEM_TIMER_EVENT_P3_TYPE_C_RTD_STATUS_DETECT:

            UserCommonUsbTypeCRtdStatusDetCtrl(_P3_TYPE_C_PORT, _ENABLE);

            break;
#endif  // End of #if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_P3_TYPE_C_BILLBOARD_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_P3_ENABLE_BILLBOARD:

            SysUsbBillBoardSetTimerEventFlag(_P3_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_P4_TYPE_C_CONNECTION_DET:

            SysUsbTypeCConnectionDetCtrl(_P4_TYPE_C_PORT, _ENABLE);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_P4_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT:

            SysUsbTypeCSetLenovoRcvDeviceTypeTimeout(_P4_TYPE_C_PORT);

            break;
#endif

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _SYSTEM_TIMER_EVENT_P4_TYPE_C_STATUS_DETECT:

            UserCommonUsbTypeCRtsSetStatusDetection(_P4_TYPE_C_PORT);

            break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_P4_TYPE_C_LENOVO_ALT_MODE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoAltModeDetection(_P4_TYPE_C_PORT);

            break;

        case _SYSTEM_TIMER_EVENT_P4_TYPE_C_LENOVO_DEVICE_TYPE_DETECT:

            UserCommonUsbTypeCRtsSetLenovoDeviceTypeDetection(_P4_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _SYSTEM_TIMER_EVENT_P4_TYPE_C_RTD_STATUS_DETECT:

            UserCommonUsbTypeCRtdStatusDetCtrl(_P4_TYPE_C_PORT, _ENABLE);

            break;
#endif  // End of #if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_P4_TYPE_C_BILLBOARD_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_P4_ENABLE_BILLBOARD:

            SysUsbBillBoardSetTimerEventFlag(_P4_TYPE_C_PORT);

            break;
#endif
#endif  // End of #if(_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_ADAPTOR_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_ADAPTOR_TYPE_C_CONNECTION_DET:

            SysUsbTypeCConnectionDetCtrl(_ADAPTOR_TYPE_C_PORT, _ENABLE);

            break;

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
        case _SYSTEM_TIMER_EVENT_ADAPTOR_TYPE_C_STATUS_DETECT:

            UserCommonUsbTypeCRtsSetStatusDetection(_ADAPTOR_TYPE_C_PORT);

            break;
#endif  // End of #if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _SYSTEM_TIMER_EVENT_ADAPTOR_TYPE_C_RTD_STATUS_DETECT:

            UserCommonUsbTypeCRtdStatusDetCtrl(_ADAPTOR_TYPE_C_PORT, _ENABLE);

            break;
#endif  // End of #if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
#endif  // End of #if(_ADAPTOR_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CTRL_RTS_SUPPORT == _ON)
#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _SYSTEM_TIMER_EVENT_TYPE_C_LENOVO_ALT_MODE_URGENT_EVENT_TIMEOUT:

            CLR_TYPE_C_RTS_LENOVO_ALT_MODE_URGENT_EVENT();

            break;
#endif
#endif
#endif

#if(_AUTO_TEST_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_AUTO_TEST_OSD_KEY_MSG:

            SysATOsdMenuKeyMsgClrFlg();
            break;
#endif

#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_CLR_DDCCI0_RECEIVE_COMMAND_NOT_FINISH:
            CLR_RECEIVE_DDCCI0_CMD_NOT_FINISH();
            break;
#endif

#if((_2P_FRAME_SYNC_SUPPORT == _ON) && (_2P_FRAME_SYNC_DEBOUNCE_TIME != 0))
        case _SYSTEM_TIMER_EVENT_2P_FRAME_SYNC_DEBOUNCE:
            SysJudge2pFrameSyncDebounceStop();
            break;
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT:
            SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));
            break;
#endif

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_FW_UPDATE_FOREGROUND_EXIT:
            UserCommonFwUpdateForegroundTimeoutExit();
            break;
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
#if(_DM_DEMO_FUNCTION == _ON)
        case _SYSTEM_TIMER_EVENT_DM_DEMO_FUNCTION:
            UserCommonColorDMDemoFuncProc();
            break;
#endif
#endif
#endif

#if(_HDMI_CEC_SUPPORT == _ON)
#if(_AUDIO_ARC_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_CEC_RETRY_REQUEST_ARC_INITIATE:

            SysAudioArcTxCecSetRequestArcInitiateRetryTimeout();
            break;

        case _SYSTEM_TIMER_EVENT_CEC_RETRY_REQUEST_ARC_TERMINATE:

            SysAudioArcTxCecSetRequestArcTerminateRetryTimeout();
            break;
#endif

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_CEC_RETRY_PHYSICAL_ADDRESS:

            UserCommonCecHalSetPhysicalAddressRetryTimeout();
            break;

        case _SYSTEM_TIMER_EVENT_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY:

            UserCommonCecHalSetWaitForAudioDescriptorReplyTimeout();
            break;
#endif
#endif

        default:
            break;
    }
}

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Fw Update Foreground Timer Event Process
// Input Value  : enumEventID --> Event to be processed
// Output Value : None
//--------------------------------------------------
void SysTimerFwUpdateForegroundHandler(void)
{
    BYTE ucTimerEventIndex = 0;
    BYTE ucTimerEventID = 0;

    for(ucTimerEventIndex = 0; ucTimerEventIndex < _TIMER_EVENT_COUNT; ucTimerEventIndex++)
    {
        ucTimerEventID = ScalerTimerGetEventID(ucTimerEventIndex);
        if(ucTimerEventID == _SYSTEM_TIMER_EVENT_FW_UPDATE_FOREGROUND_EXIT)
        {
            if((ScalerTimerCheckEventValid(ucTimerEventIndex) == _TRUE) &&
               (ScalerTimerGetTimerCounter() > ScalerTimerGetEventTime(ucTimerEventIndex)))
            {
                ScalerTimerClrEventValid(ucTimerEventIndex);

                SysTimerEventProc(ucTimerEventID);
            }
            break;
        }
    }
}
#endif

