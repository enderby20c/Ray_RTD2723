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
// ID Code      : ScalerTimerFunction_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TIMERFUNCTION_WDINT__

#include "ScalerFunctionInclude.h"
#include "TimerFunction/ScalerTimerFunction.h"




//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructWDTimerEventType g_pstTimerWDEvent[_WD_TIMER_EVENT_COUNT];

volatile BYTE g_pucTimerDeferActiveWDID[_WD_TIMER_EVENT_COUNT];
volatile BYTE g_pucTimerDeferActiveWDTime[_WD_TIMER_EVENT_COUNT];
volatile BYTE g_ucTimerKcpuDeferActiveWDIndex;
volatile bit g_bTimerWDEventProcessNowFlag;

#if(_SCPU_SUPPORT == _ON)
volatile BYTE g_ucTimerScpuDeferActiveWDIndex = _WD_TIMER_EVENT_COUNT;
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_RECORD_TIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Record Timer Start Time
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTimerResetRecordTimer_WDINT(void)
{
    LOAD_TIMER_COUNTER(&g_usTimerRecordStartTime);
}
#endif

//--------------------------------------------------
// Description  : Watch Dog Timer Event Processor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDEventProc_WDINT(void)
{
    BYTE pucActiveWDID[_WD_TIMER_EVENT_COUNT] = {0};
    BYTE pucActiveWDTime[_WD_TIMER_EVENT_COUNT] = {0};

    g_bTimerWDEventProcessNowFlag = _TRUE;
    ScalerTimerWDEventProcess_WDINT(pucActiveWDID, pucActiveWDTime);
    g_bTimerWDEventProcessNowFlag = _FALSE;

    for(BYTE ucWDIndex = 0; ucWDIndex < _WD_TIMER_EVENT_COUNT; ucWDIndex++)
    {
        if((pucActiveWDTime[ucWDIndex] != 0x00) && (pucActiveWDID[ucWDIndex] != _SCALER_WD_TIMER_EVENT_INVALID))
        {
            ScalerTimerWDUpdateTimerEventTable(pucActiveWDTime[ucWDIndex], pucActiveWDID[ucWDIndex]);
        }
    }

    for(BYTE ucWDIndex = 0; ucWDIndex < _WD_TIMER_EVENT_COUNT; ucWDIndex++)
    {
        if(g_pucTimerDeferActiveWDID[ucWDIndex] != _SCALER_WD_TIMER_EVENT_INVALID)
        {
            ScalerTimerWDUpdateTimerEventTable(g_pucTimerDeferActiveWDTime[ucWDIndex], g_pucTimerDeferActiveWDID[ucWDIndex]);
            g_pucTimerDeferActiveWDID[ucWDIndex] = _SCALER_WD_TIMER_EVENT_INVALID;
        }
    }
    g_ucTimerKcpuDeferActiveWDIndex = 0;
#if(_SCPU_SUPPORT == _ON)
    g_ucTimerScpuDeferActiveWDIndex = _WD_TIMER_EVENT_COUNT;
#endif
}


//--------------------------------------------------
// Description  : Watch Dog Timer Event Handle
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDEventHandler_WDINT(BYTE ucIndex, BYTE *pucActiveWDID, BYTE *pucActiveWDTime)
{
    pucActiveWDID = pucActiveWDID;
    pucActiveWDTime = pucActiveWDTime;

    switch(GET_WD_EVENT_ID(ucIndex))
    {
#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
        case _SCALER_WD_TIMER_EVENT_AUDIO_TTS_PLAYBACK_PROC:

            ScalerAudioTtsDataPlay_WDINT();

            break;
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_D0_DP_SUPPORT == _ON)

        case _SCALER_WD_TIMER_EVENT_RX0_DP_HPD_IRQ_ASSERT:

            ScalerDpMacDphyRxWDTimerEventHpdIrqAssertProc_WDINT(_D0_INPUT_PORT);

            break;

        case _SCALER_WD_TIMER_EVENT_RX0_DP_LINK_TRAINING_REBUILD_PHY:

            ScalerDpMacDphyRxWDTimerEventRebuildPhyProc_WDINT(_D0_INPUT_PORT);

            break;

        case _SCALER_WD_TIMER_EVENT_RX0_DP2_LINK_TRAINING_TIMEOUT:

#if(_D0_DP_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerDpAuxRxWDTimerEventLinkTrainingTimeoutProc_WDINT(_D0_INPUT_PORT);
#endif

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)

        case _SCALER_WD_TIMER_EVENT_RX1_DP_HPD_IRQ_ASSERT:

            ScalerDpMacDphyRxWDTimerEventHpdIrqAssertProc_WDINT(_D1_INPUT_PORT);

            break;

        case _SCALER_WD_TIMER_EVENT_RX1_DP_LINK_TRAINING_REBUILD_PHY:

            ScalerDpMacDphyRxWDTimerEventRebuildPhyProc_WDINT(_D1_INPUT_PORT);

            break;

        case _SCALER_WD_TIMER_EVENT_RX1_DP2_LINK_TRAINING_TIMEOUT:

#if(_D1_DP_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerDpAuxRxWDTimerEventLinkTrainingTimeoutProc_WDINT(_D1_INPUT_PORT);
#endif

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)

        case _SCALER_WD_TIMER_EVENT_RX2_DP_HPD_IRQ_ASSERT:

            ScalerDpMacDphyRxWDTimerEventHpdIrqAssertProc_WDINT(_D2_INPUT_PORT);

            break;

        case _SCALER_WD_TIMER_EVENT_RX2_DP_LINK_TRAINING_REBUILD_PHY:

            ScalerDpMacDphyRxWDTimerEventRebuildPhyProc_WDINT(_D2_INPUT_PORT);

            break;

        case _SCALER_WD_TIMER_EVENT_RX2_DP2_LINK_TRAINING_TIMEOUT:

#if(_D2_DP_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerDpAuxRxWDTimerEventLinkTrainingTimeoutProc_WDINT(_D2_INPUT_PORT);
#endif

            break;
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _SCALER_WD_TIMER_EVENT_CC_0_DETECT_VBUS:
#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
        case _SCALER_WD_TIMER_EVENT_CC_0_CHECK_VBUS_0V:
#endif
            ScalerTypeC0CcWDTimerEventProc_WDINT(GET_WD_EVENT_ID(ucIndex), pucActiveWDID, pucActiveWDTime);

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_CBL_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_PD_0_SEND_SRC_CAP:
        case _SCALER_WD_TIMER_EVENT_PD_0_SEND_HARD_RST:
        case _SCALER_WD_TIMER_EVENT_PD_0_SENDER_RESP_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_PD_0_PS_TRANSITION_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_PD_0_VDM_RESP_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_PD_0_SRC_TURN_ON_POWER:
        case _SCALER_WD_TIMER_EVENT_PD_0_SRC_TURN_OFF_POWER:
        case _SCALER_WD_TIMER_EVENT_PD_0_CHECK_VBUS:
        case _SCALER_WD_TIMER_EVENT_PD_0_SEND_VCONN_ON_PSRDY:
        case _SCALER_WD_TIMER_EVENT_PD_0_BACK_TO_READY_STATE:
        // case _SCALER_WD_TIMER_EVENT_PD_0_TURN_OFF_VCONN_BACK_TO_HW_MODE:
        case _SCALER_WD_TIMER_EVENT_PD_0_SNK_SWITCH_TO_SRC:
        case _SCALER_WD_TIMER_EVENT_PD_0_SEND_EPR_ENTER_FAILED:
        case _SCALER_WD_TIMER_EVENT_PD_0_SEND_VCONN_SWAP:
        case _SCALER_WD_TIMER_EVENT_PD_0_CHUNK_SENDER_REQ_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_PD_0_SEND_EPR_SRC_CAP:
        case _SCALER_WD_TIMER_EVENT_PD_0_TX_AVALIABLE:
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
        case _SCALER_WD_TIMER_EVENT_PD_0_DELL_AM_ENTER_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_PD_0_DELL_ATTEN_RETRY:
#endif

            ScalerTypeC0PdWDTimerEventProc_WDINT(GET_WD_EVENT_ID(ucIndex), pucActiveWDID, pucActiveWDTime);

            break;
#endif

#if((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) &&\
    ((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)))
        case _SCALER_WD_TIMER_EVENT_TYPE_C_0_PMIC_FW_OCP_DELAY:

            ScalerTypeC0PmicWDTimerEventProc_WDINT(GET_WD_EVENT_ID(ucIndex), pucActiveWDID, pucActiveWDTime);

            break;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _SCALER_WD_TIMER_EVENT_CC_1_DETECT_VBUS:
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
        case _SCALER_WD_TIMER_EVENT_CC_1_CHECK_VBUS_0V:
#endif
            ScalerTypeC1CcWDTimerEventProc_WDINT(GET_WD_EVENT_ID(ucIndex), pucActiveWDID, pucActiveWDTime);

            break;

        case _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_PD_1_SEND_SRC_CAP:
        case _SCALER_WD_TIMER_EVENT_PD_1_SEND_HARD_RST:
        case _SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_PD_1_PS_TRANSITION_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_PD_1_VDM_RESP_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_PD_1_SRC_TURN_ON_POWER:
        case _SCALER_WD_TIMER_EVENT_PD_1_SRC_TURN_OFF_POWER:
        case _SCALER_WD_TIMER_EVENT_PD_1_CHECK_VBUS:
        case _SCALER_WD_TIMER_EVENT_PD_1_SEND_VCONN_ON_PSRDY:
        case _SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE:
        // case _SCALER_WD_TIMER_EVENT_PD_1_TURN_OFF_VCONN_BACK_TO_HW_MODE:
        case _SCALER_WD_TIMER_EVENT_PD_1_SNK_SWITCH_TO_SRC:
        case _SCALER_WD_TIMER_EVENT_PD_1_SEND_EPR_ENTER_FAILED:
        case _SCALER_WD_TIMER_EVENT_PD_1_SEND_VCONN_SWAP:
        case _SCALER_WD_TIMER_EVENT_PD_1_CHUNK_SENDER_REQ_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_PD_1_SEND_EPR_SRC_CAP:
        case _SCALER_WD_TIMER_EVENT_PD_1_TX_AVALIABLE:
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
        case _SCALER_WD_TIMER_EVENT_PD_1_DELL_AM_ENTER_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_PD_1_DELL_ATTEN_RETRY:
#endif

            ScalerTypeC1PdWDTimerEventProc_WDINT(GET_WD_EVENT_ID(ucIndex), pucActiveWDID, pucActiveWDTime);

            break;
#endif

#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) &&\
    ((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)))
        case _SCALER_WD_TIMER_EVENT_TYPE_C_1_PMIC_FW_OCP_DELAY:

            ScalerTypeC1PmicWDTimerEventProc_WDINT(GET_WD_EVENT_ID(ucIndex), pucActiveWDID, pucActiveWDTime);

            break;
#endif
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_TCPM_SUPPORT == _ON))
#if(_HW_TCPM_SUPPORT == _ON)
#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_CC_DEBOUNCE:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_PD_DEBOUNCE:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_CBL_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_SEND_SRC_CAP:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_SENDER_RESP_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_PS_TRANSITION_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_SRC_TURN_ON_POWER:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_SRC_TURN_OFF_POWER:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_CHECK_VBUS:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_BACK_TO_READY_STATE:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_SEND_HARD_RST:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_CC_CHECK_VBUS_0V:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_SEND_REQUEST:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_VDM_RESP_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_SNK_SWITCH_TO_SRC:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_0_SEND_VCONN_ON_PSRDY:

            ScalerTypeCTcpmWDTimerEventProc_WDINT(_HW_TCPM_0_0_MAPPING, (EnumTypeCTcpmWDEventID)(GET_WD_EVENT_ID(ucIndex) - _SCALER_WD_TIMER_EVENT_TCPM_0_0_CC_DEBOUNCE), pucActiveWDID, pucActiveWDTime);

            break;
#endif // End of #if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_CC_DEBOUNCE:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_PD_DEBOUNCE:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_CBL_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_SEND_SRC_CAP:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_SENDER_RESP_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_PS_TRANSITION_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_SRC_TURN_ON_POWER:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_SRC_TURN_OFF_POWER:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_CHECK_VBUS:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_BACK_TO_READY_STATE:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_SEND_HARD_RST:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_CC_CHECK_VBUS_0V:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_SEND_REQUEST:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_VDM_RESP_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_SNK_SWITCH_TO_SRC:
        case _SCALER_WD_TIMER_EVENT_TCPM_0_1_SEND_VCONN_ON_PSRDY:

            ScalerTypeCTcpmWDTimerEventProc_WDINT(_HW_TCPM_0_1_MAPPING, (EnumTypeCTcpmWDEventID)(GET_WD_EVENT_ID(ucIndex) - _SCALER_WD_TIMER_EVENT_TCPM_0_1_CC_DEBOUNCE), pucActiveWDID, pucActiveWDTime);

            break;
#endif // End of #if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_CC_DEBOUNCE:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_PD_DEBOUNCE:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_CBL_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_SEND_SRC_CAP:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_SENDER_RESP_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_PS_TRANSITION_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_SRC_TURN_ON_POWER:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_SRC_TURN_OFF_POWER:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_CHECK_VBUS:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_BACK_TO_READY_STATE:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_SEND_HARD_RST:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_CC_CHECK_VBUS_0V:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_SEND_REQUEST:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_VDM_RESP_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_SNK_SWITCH_TO_SRC:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_0_SEND_VCONN_ON_PSRDY:

            ScalerTypeCTcpmWDTimerEventProc_WDINT(_HW_TCPM_1_0_MAPPING, (EnumTypeCTcpmWDEventID)(GET_WD_EVENT_ID(ucIndex) - _SCALER_WD_TIMER_EVENT_TCPM_1_0_CC_DEBOUNCE), pucActiveWDID, pucActiveWDTime);

            break;
#endif // End of #if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_CC_DEBOUNCE:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_PD_DEBOUNCE:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_CBL_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_SEND_SRC_CAP:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_SENDER_RESP_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_PS_TRANSITION_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_SRC_TURN_ON_POWER:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_SRC_TURN_OFF_POWER:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_CHECK_VBUS:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_BACK_TO_READY_STATE:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_SEND_HARD_RST:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_CC_CHECK_VBUS_0V:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_SEND_REQUEST:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_VDM_RESP_TIMEOUT:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_SNK_SWITCH_TO_SRC:
        case _SCALER_WD_TIMER_EVENT_TCPM_1_1_SEND_VCONN_ON_PSRDY:

            ScalerTypeCTcpmWDTimerEventProc_WDINT(_HW_TCPM_1_1_MAPPING, (EnumTypeCTcpmWDEventID)(GET_WD_EVENT_ID(ucIndex) - _SCALER_WD_TIMER_EVENT_TCPM_1_1_CC_DEBOUNCE), pucActiveWDID, pucActiveWDTime);

            break;
#endif // End of #if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_TCPM_SUPPORT == _ON))

#if(_USB_HUB_SUPPORT == _ON)
#if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_USB_U3_DFP_RXDETECT:

            ScalerUsb3RetimerMac0U3DFPRxDetectTimeOut_WDINT();

            break;
#endif // End of #if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_USB_HUB_U1U2U3_DFP_JFM_ENABLE_TIMEOUT:

            ScalerUsb3RetimerMac0DfpU1U2U3JfmEnableTimeOut_WDINT();

            break;
#endif // End of #if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
#endif // End of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
#endif // End of #if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
#endif // End of #if(_USB_HUB_SUPPORT == _ON)


#if(_HDMI20_SUPPORT == _ON)

        case _SCALER_WD_TIMER_EVENT_RX0_HDMI_RR_RETRY:
        case _SCALER_WD_TIMER_EVENT_RX1_HDMI_RR_RETRY:
        case _SCALER_WD_TIMER_EVENT_RX2_HDMI_RR_RETRY:
        case _SCALER_WD_TIMER_EVENT_RX3_HDMI_RR_RETRY:
        case _SCALER_WD_TIMER_EVENT_RX4_HDMI_RR_RETRY:
        case _SCALER_WD_TIMER_EVENT_RX5_HDMI_RR_RETRY:

            ScalerTmdsMacRxHdmiReadRequestTimerEnable_WDINT();

            break;
#endif

#if(_HDMI_SUPPORT == _ON)
#if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_RX3_TMDS_RETRY_SET_PHY:

            // HDCP14 and HDCP2 Auth Not Done
            if(((ScalerGetBit_EXINT(P72_C0_HDCP_CR, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P72_A9_TMDS_ABC0, _BIT6) != _BIT6)) ||
               ((ScalerGetBit_EXINT(P2E_26_HDCP_I2C_CTRL_0, _BIT7) == _BIT7) && (ScalerGetByte_EXINT(P2E_2C_HDCP_I2C_CTRL_6) != 0x10)))
            {
                // Retry to Set Phy
                CLR_TMDS_MAC_RX3_PHY_SET();

                // Disable Freq. Unstable IRQ
                ScalerSetBit_EXINT(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), 0x00);

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                if(ScalerGetBit_EXINT(P67_00_HDMI_TOP_0, _BIT6) == 0x00)
#endif
                {
                    // Reset Freq. Detect Counter
                    ScalerSetBit_EXINT(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), 0x00);
                    ScalerSetBit_EXINT(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);

                    // Enable Freq. Stable IRQ
                    ScalerSetBit_EXINT(P72_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                }
            }

            // Retry Once Only
            SET_TMDS_MAC_RX3_RETRY_SET_PHY();

            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_RX4_TMDS_RETRY_SET_PHY:

            // HDCP14 and HDCP2 Auth Not Done
            if(((ScalerGetBit_EXINT(P73_C0_HDCP_CR, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P73_A9_TMDS_ABC0, _BIT6) != _BIT6)) ||
               ((ScalerGetBit_EXINT(P6D_26_HDCP_I2C_CTRL_0, _BIT7) == _BIT7) && (ScalerGetByte_EXINT(P6D_2C_HDCP_I2C_CTRL_6) != 0x10)))
            {
                // Retry to Set Phy
                CLR_TMDS_MAC_RX4_PHY_SET();

                // Disable Freq. Unstable IRQ
                ScalerSetBit_EXINT(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), 0x00);

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                if(ScalerGetBit_EXINT(P1E_00_HDMI_TOP_0, _BIT6) == 0x00)
#endif
                {
                    // Reset Freq. Detect Counter
                    ScalerSetBit_EXINT(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), 0x00);
                    ScalerSetBit_EXINT(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);

                    // Enable Freq. Stable IRQ
                    ScalerSetBit_EXINT(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                }
            }

            // Retry Once Only
            SET_TMDS_MAC_RX4_RETRY_SET_PHY();

            break;
#endif

#endif // End of #if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
#endif // End of #if(_HDMI_SUPPORT==_ON)

#if((_HDMI_SUPPORT == _ON) && (_HDMI_UNSTABLE_BED_CHECK_SUPPORT == _ON))
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_RX3_HDMI_UNSTABLE_BED_CHECK:

            if(GET_TMDS_MAC_RX3_PHY_SET() == _TRUE)
            {
                ScalerTmdsMacRxHdmiUnstableBedCheck_WDINT(_RX3);
            }

            break;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_RX4_HDMI_UNSTABLE_BED_CHECK:

            if(GET_TMDS_MAC_RX4_PHY_SET() == _TRUE)
            {
                ScalerTmdsMacRxHdmiUnstableBedCheck_WDINT(_RX4);
            }

            break;
#endif
#endif

#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX0_AKE_INIT:

            ScalerDpHdcp2RxAkeInitProc_WDINT(_D0_INPUT_PORT);

            break;
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX1_AKE_INIT:

            ScalerDpHdcp2RxAkeInitProc_WDINT(_D1_INPUT_PORT);

            break;
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_AKE_INIT:

            ScalerDpHdcp2RxAkeInitProc_WDINT(_D2_INPUT_PORT);

            break;
#endif

#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX0_H_PRIME:

            ScalerDpHdcp2RxHPrimeProc_WDINT(_D0_INPUT_PORT);

            break;
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX1_H_PRIME:

            ScalerDpHdcp2RxHPrimeProc_WDINT(_D1_INPUT_PORT);

            break;
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_H_PRIME:

            ScalerDpHdcp2RxHPrimeProc_WDINT(_D2_INPUT_PORT);

            break;
#endif

#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX0_SKE:

            ScalerDpHdcp2RxSkeProc_WDINT(_D0_INPUT_PORT);

            break;
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX1_SKE:

            ScalerDpHdcp2RxSkeProc_WDINT(_D1_INPUT_PORT);

            break;
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_SKE:

            ScalerDpHdcp2RxSkeProc_WDINT(_D2_INPUT_PORT);

            break;
#endif

#if(_DP_HDCP2_RX0_REPEATER_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX0_M_PRIME:

            ScalerDpHdcp2RxMPrimeProc_WDINT(_D0_INPUT_PORT);

            break;
#endif

#if(_DP_HDCP2_RX1_REPEATER_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX1_M_PRIME:

            ScalerDpHdcp2RxMPrimeProc_WDINT(_D1_INPUT_PORT);

            break;

#endif

#if(_DP_HDCP2_RX2_REPEATER_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_M_PRIME:

            ScalerDpHdcp2RxMPrimeProc_WDINT(_D2_INPUT_PORT);

            break;
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_TMDS_RX3_HDCP2_RSA_CAL_START:

            if(ScalerHdcp2RsaAvailable_WDINT() == _TRUE)
            {
                if(ScalerGetBit_EXINT(P63_10_HDCP_RSA_CTRL0, _BIT7) == 0x00) // RSA = Idle
                {
                    ScalerTmdsHdcp2Rx3RxRsaCalculate_WDINT();

                    // Active Timer Event to Check RSA Done
                    *pucActiveWDID = _SCALER_WD_TIMER_EVENT_TMDS_RX3_HDCP2_CHECK_RSA_CAL_DONE;
                    *pucActiveWDTime = 10;
                }
                else
                {
                    // Reactive WD Timer to Start RSA Cal
                    *pucActiveWDID = _SCALER_WD_TIMER_EVENT_TMDS_RX3_HDCP2_RSA_CAL_START;
                    *pucActiveWDTime = 10;
                }
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TMDS_RX3_HDCP2_CHECK_RSA_CAL_DONE:

            if(ScalerHdcp2RsaAvailable_WDINT() == _TRUE)
            {
                if(ScalerGetBit_EXINT(P63_10_HDCP_RSA_CTRL0, _BIT2) == _BIT2) // RSA done
                {
                    BYTE pucTemp[16] = {0};

                    // Disable RSA Module
                    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT0), 0x00);

                    if(ScalerHdcp2RxRsaOaepCalculate_WDINT(pucTemp) == _TRUE)
                    {
                        ScalerTmdsHdcp2Rx3HPrime_WDINT(pucTemp);
                    }
                }
                else
                {
                    // Reactive WD Timer to Check RSA Done
                    *pucActiveWDID = _SCALER_WD_TIMER_EVENT_TMDS_RX3_HDCP2_CHECK_RSA_CAL_DONE;
                    *pucActiveWDTime = 10;
                }
            }
            else
            {
                // Disable RSA Module
                ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT0), 0x00);
            }
            break;


        case _SCALER_WD_TIMER_EVENT_RX3_HDCP2_SET_REAUTH:

            if(GET_TMDS_HDCP2_RX3_AUTHENTICATION_DONE() == _TRUE)
            {
                BYTE pucBackUp[2] = {0};
                pucBackUp[0] = ScalerGetByte_EXINT(P72_C3_HDCP_AP);
                pucBackUp[1] = (ScalerGetByte_EXINT(P72_C2_HDCP_PCR) & 0x01);

                // Set C4 Port non-auto increase
                ScalerSetBit_EXINT(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT0), _BIT0);

                ScalerSetByte_EXINT(P72_C3_HDCP_AP, _P72_C4_PT_71_PORT_PAGE72_HDCP2_STATUS2);
                ScalerSetBit_EXINT(P72_C4_HDCP_DP, ~_BIT3, _BIT3);

                ScalerSetBit_EXINT(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT0), pucBackUp[1]);
                ScalerSetByte_EXINT(P72_C3_HDCP_AP, pucBackUp[0]);
            }

            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_TMDS_RX4_HDCP2_RSA_CAL_START:

            if(ScalerHdcp2RsaAvailable_WDINT() == _TRUE)
            {
                if(ScalerGetBit_EXINT(P63_10_HDCP_RSA_CTRL0, _BIT7) == 0x00) // RSA = Idle
                {
                    ScalerTmdsHdcp2Rx4RxRsaCalculate_WDINT();

                    // Active Timer Event to Check RSA Done
                    *pucActiveWDID = _SCALER_WD_TIMER_EVENT_TMDS_RX4_HDCP2_CHECK_RSA_CAL_DONE;
                    *pucActiveWDTime = 10;
                }
                else
                {
                    // Reactive WD Timer to Start RSA Cal
                    *pucActiveWDID = _SCALER_WD_TIMER_EVENT_TMDS_RX4_HDCP2_RSA_CAL_START;
                    *pucActiveWDTime = 10;
                }
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TMDS_RX4_HDCP2_CHECK_RSA_CAL_DONE:

            if(ScalerHdcp2RsaAvailable_WDINT() == _TRUE)
            {
                if(ScalerGetBit_EXINT(P63_10_HDCP_RSA_CTRL0, _BIT2) == _BIT2) // RSA done
                {
                    BYTE pucTemp[16] = {0};

                    // Disable RSA Module
                    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT0), 0x00);

                    if(ScalerHdcp2RxRsaOaepCalculate_WDINT(pucTemp) == _TRUE)
                    {
                        ScalerTmdsHdcp2Rx4HPrime_WDINT(pucTemp);
                    }
                }
                else
                {
                    // Reactive WD Timer to Check RSA Done
                    *pucActiveWDID = _SCALER_WD_TIMER_EVENT_TMDS_RX4_HDCP2_CHECK_RSA_CAL_DONE;
                    *pucActiveWDTime = 10;
                }
            }
            else
            {
                // Disable RSA Module
                ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT0), 0x00);
            }
            break;


        case _SCALER_WD_TIMER_EVENT_RX4_HDCP2_SET_REAUTH:

            if(GET_TMDS_HDCP2_RX4_AUTHENTICATION_DONE() == _TRUE)
            {
                BYTE pucBackUp[2] = {0};
                pucBackUp[0] = ScalerGetByte_EXINT(P73_C3_HDCP_AP);
                pucBackUp[1] = (ScalerGetByte_EXINT(P73_C2_HDCP_PCR) & 0x01);

                // Set C4 Port non-auto increase
                ScalerSetBit_EXINT(P73_C2_HDCP_PCR, ~(_BIT4 | _BIT0), _BIT0);

                ScalerSetByte_EXINT(P73_C3_HDCP_AP, _P73_C4_PT_71_PORT_PAGE73_HDCP2_STATUS2);
                ScalerSetBit_EXINT(P73_C4_HDCP_DP, ~_BIT3, _BIT3);

                ScalerSetBit_EXINT(P73_C2_HDCP_PCR, ~(_BIT4 | _BIT0), pucBackUp[1]);
                ScalerSetByte_EXINT(P73_C3_HDCP_AP, pucBackUp[0]);
            }

            break;
#endif
#endif

#if(_GOSD_SUPPORT == _ON)
        case _SCALER_WD_TIMER_EVENT_GOSD_OSD1_CONTINUOUS_START:
        case _SCALER_WD_TIMER_EVENT_GOSD_OSD2_CONTINUOUS_START:
        case _SCALER_WD_TIMER_EVENT_GOSD_OSD3_CONTINUOUS_START:
        {
            EnumGosdDisplayOSD enumDispPlane = GET_GOSD_DISPLAY_PLANE_BY_WDTEVENT(GET_WD_EVENT_ID(ucIndex));
            // check Parameters Changing or not
            if((g_bGosdContinuousGlobalPause == _TRUE) ||
               (g_pstGosdContinuousParam[enumDispPlane].bGosdContinuousPause == _TRUE))
            {
                // params are changing, re-check in 1ms
                *pucActiveWDTime = 1;
                *pucActiveWDID = GET_WD_EVENT_ID(ucIndex);
                break;
            }

            // execute continuous process
#if((_GOSD_SYNC_BY_INT_NOTIFY == _TRUE) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
            // execute by CpuSyncToScpu
            UnionCpuSyncReplyCmdBody unCpuSyncToScpuCmdReplyBody = {0};
            g_pstCpuSyncToScpuCmd->unCmdBody.stCpuSyncGosdCmd.ucDispPlane = enumDispPlane;
            ScalerCpuSyncSendCmd(_SCALER_CPU_SYNC_GOSD_CONTINUOUS, _SCALER_CPU_SYNC_TIMEOUT_GOSD, &unCpuSyncToScpuCmdReplyBody);
#elif((_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE) && (_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE))
            // execute by Scpu
            g_stGosdContinuousCmd.ucDispPlane = enumDispPlane;
            bit bExecuteNormal = ScalerGosdContinuousProc();
#endif

            if(g_pstGosdContinuousParam[enumDispPlane].enumGosdContinuousType == _GOSD_CONTINUOUS_NONE)
            {
                // stop continuous step
                break;
            }

#if((_GOSD_SYNC_BY_INT_NOTIFY == _TRUE) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
            if(unCpuSyncToScpuCmdReplyBody.stCpuSyncGosdCmdReply.bExecuteStatus == _TRUE)
#elif((_GOSD_SYNC_BY_GLOBAL_VARIABLE == _TRUE) && (_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE))
            if(bExecuteNormal == _TRUE)
#endif
            {
                // Continuous Execute Normal, reactive in specified time to next step
                *pucActiveWDTime = g_pstGosdContinuousParam[enumDispPlane].usGosdContinuousTimer;
            }
            else
            {
                // not ready for current step, re-check in 5ms
                *pucActiveWDTime = 5;
            }
            // Reactive WD Timer to next step
            *pucActiveWDID = GET_WD_EVENT_ID(ucIndex);
            break;
        }
#endif

        default:
            break;
    }

    // Clear Event Valid After Event Processed
    CLR_WD_EVENT_VALID(ucIndex);
}

