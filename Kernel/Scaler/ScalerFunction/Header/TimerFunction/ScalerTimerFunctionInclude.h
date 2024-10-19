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
// ID Code      : ScalerTimerFunctionInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definitions of D0 WD Timer count
//--------------------------------------------------
#if(_D0_DP_SUPPORT == _ON)

#if(((_DP_HDCP2_RX0_REPEATER_SUPPORT == _ON) && (_HW_D0_DP_HDCP_RX_MAPPING == _MAPPING_RX0)) ||\
    ((_DP_HDCP2_RX1_REPEATER_SUPPORT == _ON) && (_HW_D0_DP_HDCP_RX_MAPPING == _MAPPING_RX1)) ||\
    ((_DP_HDCP2_RX2_REPEATER_SUPPORT == _ON) && (_HW_D0_DP_HDCP_RX_MAPPING == _MAPPING_RX2)))
#define _D0_WD_TIMER_DP_EVENT_COUNT             (2)
#else
#define _D0_WD_TIMER_DP_EVENT_COUNT             (1)
#endif

#else
#define _D0_WD_TIMER_DP_EVENT_COUNT             (0)
#endif

//--------------------------------------------------
// Definitions of D1 WD Timer count
//--------------------------------------------------
#if(_D1_DP_SUPPORT == _ON)

#if(((_DP_HDCP2_RX0_REPEATER_SUPPORT == _ON) && (_HW_D1_DP_HDCP_RX_MAPPING == _MAPPING_RX0)) ||\
    ((_DP_HDCP2_RX1_REPEATER_SUPPORT == _ON) && (_HW_D1_DP_HDCP_RX_MAPPING == _MAPPING_RX1)) ||\
    ((_DP_HDCP2_RX2_REPEATER_SUPPORT == _ON) && (_HW_D1_DP_HDCP_RX_MAPPING == _MAPPING_RX2)))
#define _D1_WD_TIMER_DP_EVENT_COUNT             (2)
#else
#define _D1_WD_TIMER_DP_EVENT_COUNT             (1)
#endif

#else
#define _D1_WD_TIMER_DP_EVENT_COUNT             (0)
#endif

//--------------------------------------------------
// Definitions of D2 WD Timer count
//--------------------------------------------------
#if(_D2_DP_SUPPORT == _ON)

#if(((_DP_HDCP2_RX0_REPEATER_SUPPORT == _ON) && (_HW_D2_DP_HDCP_RX_MAPPING == _MAPPING_RX0)) ||\
    ((_DP_HDCP2_RX1_REPEATER_SUPPORT == _ON) && (_HW_D2_DP_HDCP_RX_MAPPING == _MAPPING_RX1)) ||\
    ((_DP_HDCP2_RX2_REPEATER_SUPPORT == _ON) && (_HW_D2_DP_HDCP_RX_MAPPING == _MAPPING_RX2)))
#define _D2_WD_TIMER_DP_EVENT_COUNT             (2)
#else
#define _D2_WD_TIMER_DP_EVENT_COUNT             (1)
#endif

#else
#define _D2_WD_TIMER_DP_EVENT_COUNT             (0)
#endif

//--------------------------------------------------
// Definitions of total WD Timer count
//--------------------------------------------------
#define _WD_TIMER_EVENT_COUNT                   (6 +\
                                                 _D0_WD_TIMER_DP_EVENT_COUNT +\
                                                 _D1_WD_TIMER_DP_EVENT_COUNT +\
                                                 _D2_WD_TIMER_DP_EVENT_COUNT)

//--------------------------------------------------
// Definitions of Timer counter setting
//--------------------------------------------------
#define LOAD_TIMER_COUNTER(pusCounter)          {\
                                                    SET_TIMER2_INT_STATUS(_FALSE);\
                                                    *(pusCounter) = g_usTimerCounter;\
                                                    if(GET_TIMER2_INT_STATUS() == _TRUE)\
                                                    {\
                                                        *(pusCounter) = g_usTimerCounter;\
                                                    }\
                                                }
#define STORE_TIMER_COUNTER(x)                  (g_usTimerCounterDoubleBuffer = ((x) + 1))

//--------------------------------------------------
// Definitions of Timer2
//--------------------------------------------------
#define _EVENT_TIME_MAX                         61000

//--------------------------------------------------
// IDLE Mode
//--------------------------------------------------
#define _IDLE_TIME_MAX                          100 // unit: ms

//--------------------------------------------------
// Definitions of TimeOut
//--------------------------------------------------
#define _TIMER_WAIT_EVENT_TIMEOUT               90 // unit: ms

//--------------------------------------------------
// Macro of Timer Event Structure
//--------------------------------------------------
#define GET_EVENT_VALID(x)                      (g_pstTimerEvent[x].enumEventID != _SCALER_TIMER_EVENT_INVALID)
#define CLR_EVENT_VALID(x)                      (g_pstTimerEvent[x].enumEventID = _SCALER_TIMER_EVENT_INVALID)

#define GET_EVENT_ID(x)                         (g_pstTimerEvent[x].enumEventID)
#define SET_EVENT_ID(x, y)                      (g_pstTimerEvent[x].enumEventID = (y))

#define GET_EVENT_TIME(x)                       (g_pstTimerEvent[x].usTime)
#define SET_EVENT_TIME(x, y)                    (g_pstTimerEvent[x].usTime = (y))

//--------------------------------------------------
// Macro of WD Timer Event Structure
//--------------------------------------------------
#define GET_WD_EVENT_VALID(x)                   (g_pstTimerWDEvent[x].enumEventID != _SCALER_WD_TIMER_EVENT_INVALID)
#define CLR_WD_EVENT_VALID(x)                   (g_pstTimerWDEvent[x].enumEventID = _SCALER_WD_TIMER_EVENT_INVALID)

#define GET_WD_EVENT_ID(x)                      (g_pstTimerWDEvent[x].enumEventID)
#define SET_WD_EVENT_ID(x, y)                   (g_pstTimerWDEvent[x].enumEventID = (y))

#define SET_CURRENT_WD_REF_CLK_KHZ(ulKHz)       (g_ulTimerWdtRefClk = (ulKHz))
#define GET_CURRENT_WD_REF_CLK_KHZ()            (g_ulTimerWdtRefClk)
#define SET_PREVIOUS_WD_REF_CLK_KHZ(ulKHz)      (g_ulTimerPrevWdtRefClk = (ulKHz))
#define GET_PREVIOUS_WD_REF_CLK_KHZ()           (g_ulTimerPrevWdtRefClk)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions for WD Timer Event
//--------------------------------------------------
typedef enum
{
    _SCALER_WD_TIMER_EVENT_INVALID = 0,

#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
    _SCALER_WD_TIMER_EVENT_AUDIO_TTS_PLAYBACK_PROC,
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

    _SCALER_WD_TIMER_EVENT_DP_LINK_TRAINING_REBUILD_PHY,
#if(_D0_DP_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_RX0_DP_LINK_TRAINING_REBUILD_PHY,
    _SCALER_WD_TIMER_EVENT_RX0_DP2_LINK_TRAINING_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_RX0_DP_HPD_IRQ_ASSERT,
#endif

#if(_D1_DP_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_RX1_DP_LINK_TRAINING_REBUILD_PHY,
    _SCALER_WD_TIMER_EVENT_RX1_DP2_LINK_TRAINING_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_RX1_DP_HPD_IRQ_ASSERT,
#endif

#if(_D2_DP_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_RX2_DP_LINK_TRAINING_REBUILD_PHY,
    _SCALER_WD_TIMER_EVENT_RX2_DP2_LINK_TRAINING_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_RX2_DP_HPD_IRQ_ASSERT,
#endif

#if(_HDMI20_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_RX0_HDMI_RR_RETRY,
    _SCALER_WD_TIMER_EVENT_RX0_HDMI_HPD,
    _SCALER_WD_TIMER_EVENT_RX1_HDMI_RR_RETRY,
    _SCALER_WD_TIMER_EVENT_RX1_HDMI_HPD,
    _SCALER_WD_TIMER_EVENT_RX2_HDMI_RR_RETRY,
    _SCALER_WD_TIMER_EVENT_RX2_HDMI_HPD,
    _SCALER_WD_TIMER_EVENT_RX3_HDMI_RR_RETRY,
    _SCALER_WD_TIMER_EVENT_RX3_HDMI_HPD,
    _SCALER_WD_TIMER_EVENT_RX4_HDMI_RR_RETRY,
    _SCALER_WD_TIMER_EVENT_RX4_HDMI_HPD,
    _SCALER_WD_TIMER_EVENT_RX5_HDMI_RR_RETRY,
    _SCALER_WD_TIMER_EVENT_RX5_HDMI_HPD,
#endif

#if(_HDMI_SUPPORT == _ON)
#if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_RX3_TMDS_RETRY_SET_PHY,
#endif
#if(_TMDS_MAC_RX4_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_RX4_TMDS_RETRY_SET_PHY,
#endif
#endif // End of #if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
    _SCALER_WD_TIMER_EVENT_CC_0_DETECT_VBUS,
#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
    _SCALER_WD_TIMER_EVENT_CC_0_CHECK_VBUS_0V,
#endif
    _SCALER_WD_TIMER_EVENT_PD_0_CBL_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_PD_0_SEND_SRC_CAP,
    _SCALER_WD_TIMER_EVENT_PD_0_SEND_HARD_RST,
    _SCALER_WD_TIMER_EVENT_PD_0_SENDER_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_PD_0_PS_TRANSITION_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_PD_0_VDM_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_PD_0_SRC_TURN_ON_POWER,
    _SCALER_WD_TIMER_EVENT_PD_0_SRC_TURN_OFF_POWER,
    _SCALER_WD_TIMER_EVENT_PD_0_CHECK_VBUS,
    _SCALER_WD_TIMER_EVENT_PD_0_SEND_VCONN_ON_PSRDY,
    _SCALER_WD_TIMER_EVENT_PD_0_BACK_TO_READY_STATE,
    // _SCALER_WD_TIMER_EVENT_PD_0_TURN_OFF_VCONN_BACK_TO_HW_MODE,
    _SCALER_WD_TIMER_EVENT_PD_0_SNK_SWITCH_TO_SRC,
    _SCALER_WD_TIMER_EVENT_PD_0_SEND_EPR_ENTER_FAILED,
    _SCALER_WD_TIMER_EVENT_PD_0_SEND_VCONN_SWAP,
    _SCALER_WD_TIMER_EVENT_PD_0_CHUNK_SENDER_REQ_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_PD_0_SEND_EPR_SRC_CAP,
    _SCALER_WD_TIMER_EVENT_PD_0_TX_AVALIABLE,
#if((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) && ((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)))
    _SCALER_WD_TIMER_EVENT_TYPE_C_0_PMIC_FW_OCP_DELAY,
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    _SCALER_WD_TIMER_EVENT_PD_0_DELL_AM_ENTER_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_PD_0_DELL_ATTEN_RETRY,
#endif
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
    _SCALER_WD_TIMER_EVENT_CC_1_DETECT_VBUS,
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
    _SCALER_WD_TIMER_EVENT_CC_1_CHECK_VBUS_0V,
#endif
    _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_PD_1_SEND_SRC_CAP,
    _SCALER_WD_TIMER_EVENT_PD_1_SEND_HARD_RST,
    _SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_PD_1_PS_TRANSITION_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_PD_1_VDM_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_PD_1_SRC_TURN_ON_POWER,
    _SCALER_WD_TIMER_EVENT_PD_1_SRC_TURN_OFF_POWER,
    _SCALER_WD_TIMER_EVENT_PD_1_CHECK_VBUS,
    _SCALER_WD_TIMER_EVENT_PD_1_SEND_VCONN_ON_PSRDY,
    _SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE,
    // _SCALER_WD_TIMER_EVENT_PD_1_TURN_OFF_VCONN_BACK_TO_HW_MODE,
    _SCALER_WD_TIMER_EVENT_PD_1_SNK_SWITCH_TO_SRC,
    _SCALER_WD_TIMER_EVENT_PD_1_SEND_EPR_ENTER_FAILED,
    _SCALER_WD_TIMER_EVENT_PD_1_SEND_VCONN_SWAP,
    _SCALER_WD_TIMER_EVENT_PD_1_CHUNK_SENDER_REQ_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_PD_1_SEND_EPR_SRC_CAP,
    _SCALER_WD_TIMER_EVENT_PD_1_TX_AVALIABLE,
#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && ((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)))
    _SCALER_WD_TIMER_EVENT_TYPE_C_1_PMIC_FW_OCP_DELAY,
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    _SCALER_WD_TIMER_EVENT_PD_1_DELL_AM_ENTER_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_PD_1_DELL_ATTEN_RETRY,
#endif
#endif
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_TCPM_SUPPORT == _ON))
#if(_HW_TCPM_SUPPORT == _ON)
#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_CC_DEBOUNCE,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_PD_DEBOUNCE,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_CBL_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_SEND_SRC_CAP,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_SENDER_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_PS_TRANSITION_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_SRC_TURN_ON_POWER,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_SRC_TURN_OFF_POWER,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_CHECK_VBUS,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_BACK_TO_READY_STATE,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_SEND_HARD_RST,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_CC_CHECK_VBUS_0V,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_SEND_REQUEST,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_VDM_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_SNK_SWITCH_TO_SRC,
    _SCALER_WD_TIMER_EVENT_TCPM_0_0_SEND_VCONN_ON_PSRDY,
#endif // End of #if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_CC_DEBOUNCE,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_PD_DEBOUNCE,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_CBL_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_SEND_SRC_CAP,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_SENDER_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_PS_TRANSITION_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_SRC_TURN_ON_POWER,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_SRC_TURN_OFF_POWER,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_CHECK_VBUS,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_BACK_TO_READY_STATE,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_SEND_HARD_RST,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_CC_CHECK_VBUS_0V,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_SEND_REQUEST,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_VDM_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_SNK_SWITCH_TO_SRC,
    _SCALER_WD_TIMER_EVENT_TCPM_0_1_SEND_VCONN_ON_PSRDY,
#endif // End of #if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_CC_DEBOUNCE,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_PD_DEBOUNCE,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_CBL_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_SEND_SRC_CAP,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_SENDER_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_PS_TRANSITION_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_SRC_TURN_ON_POWER,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_SRC_TURN_OFF_POWER,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_CHECK_VBUS,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_BACK_TO_READY_STATE,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_SEND_HARD_RST,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_CC_CHECK_VBUS_0V,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_SEND_REQUEST,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_VDM_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_SNK_SWITCH_TO_SRC,
    _SCALER_WD_TIMER_EVENT_TCPM_1_0_SEND_VCONN_ON_PSRDY,
#endif // End of #if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_CC_DEBOUNCE,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_PD_DEBOUNCE,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_CBL_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_SEND_SRC_CAP,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_SENDER_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_PS_TRANSITION_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_SRC_TURN_ON_POWER,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_SRC_TURN_OFF_POWER,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_CHECK_VBUS,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_BACK_TO_READY_STATE,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_SEND_HARD_RST,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_CC_CHECK_VBUS_0V,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_SEND_REQUEST,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_VDM_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_SNK_SWITCH_TO_SRC,
    _SCALER_WD_TIMER_EVENT_TCPM_1_1_SEND_VCONN_ON_PSRDY,
#endif // End of #if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_TCPM_SUPPORT == _ON))

#if(_DP_HDCP2_RX0_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX0_AKE_INIT,
#endif
#if(_DP_HDCP2_RX1_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX1_AKE_INIT,
#endif
#if(_DP_HDCP2_RX2_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_AKE_INIT,
#endif

#if(_DP_HDCP2_RX0_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX0_H_PRIME,
#endif
#if(_DP_HDCP2_RX1_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX1_H_PRIME,
#endif
#if(_DP_HDCP2_RX2_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_H_PRIME,
#endif

#if(_DP_HDCP2_RX0_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX0_SKE,
#endif
#if(_DP_HDCP2_RX1_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX1_SKE,
#endif
#if(_DP_HDCP2_RX2_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_SKE,
#endif

#if(_DP_HDCP2_RX0_REPEATER_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX0_M_PRIME,
#endif
#if(_DP_HDCP2_RX1_REPEATER_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX1_M_PRIME,
#endif
#if(_DP_HDCP2_RX2_REPEATER_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_M_PRIME,
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_TMDS_RX3_HDCP2_RSA_CAL_START,
    _SCALER_WD_TIMER_EVENT_TMDS_RX3_HDCP2_CHECK_RSA_CAL_DONE,
    _SCALER_WD_TIMER_EVENT_RX3_HDCP2_SET_REAUTH,
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_TMDS_RX4_HDCP2_RSA_CAL_START,
    _SCALER_WD_TIMER_EVENT_TMDS_RX4_HDCP2_CHECK_RSA_CAL_DONE,
    _SCALER_WD_TIMER_EVENT_RX4_HDCP2_SET_REAUTH,
#endif
#endif

#if(_HDMI_UNSTABLE_BED_CHECK_SUPPORT == _ON)
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_RX3_HDMI_UNSTABLE_BED_CHECK,
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_RX4_HDMI_UNSTABLE_BED_CHECK,
#endif
#endif

#if(_USB_HUB_SUPPORT == _ON)
#if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_USB_U3_DFP_RXDETECT,
#endif // End of #if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_USB_HUB_U1U2U3_DFP_JFM_ENABLE_TIMEOUT,
#endif // End of #if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
#endif // End of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
#endif // End of #if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
#endif // End of #if(_USB_HUB_SUPPORT == _ON)


#if(_GOSD_SUPPORT == _ON)
    _SCALER_WD_TIMER_EVENT_GOSD_OSD1_CONTINUOUS_START,
    _SCALER_WD_TIMER_EVENT_GOSD_OSD2_CONTINUOUS_START,
    _SCALER_WD_TIMER_EVENT_GOSD_OSD3_CONTINUOUS_START,
#endif // #if(_GOSD_SUPPORT == _ON)

    _SCALER_WD_TIMER_EVENT_END,
    _SCALER_WD_TIMER_EVENT_COUNT = _SCALER_WD_TIMER_EVENT_END,
    _SCALER_WD_TIMER_EVENT_NULL = 0xFF,
}EnumScalerWDTimerEventID;

typedef struct
{
    EnumScalerWDTimerEventID enumEventID;
    DWORD ulTime;
} StructWDTimerEventType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile DWORD g_ulTimerChangeClkCurrentTime;
extern volatile DWORD g_ulTimerWdtRefClk;
extern volatile DWORD g_ulTimerPrevWdtRefClk;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTimerCancelTimerEvent_EXINT0(EnumScalerTimerEventID enumEventID);
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_TCPM_SUPPORT == _ON))
extern void ScalerTimerCancelTimerEvent_WDINT(EnumScalerTimerEventID enumEventID);
#endif

extern void ScalerTimerWDEventHandler_WDINT(BYTE ucIndex, BYTE *pucActiveWDID, BYTE *pucActiveWDTime);

extern void ScalerTimerClrDDomainEventStatus(EnumWaitDDomainEventType enumEvent);
extern BYTE ScalerTimerGetDDomainEventStatus(EnumWaitDDomainEventType enumEvent);

extern bit ScalerTimerPollingXRAMFlagProc(WORD usTimeout, DWORD ulXRAMAddr, BYTE ucBit, bit bSuccess);
extern bit ScalerTimerPollingXRAMFlagProc_EXINT0(WORD usTimeout, DWORD ulXRAMAddr, BYTE ucBit, bit bSuccess);
extern bit ScalerTimerPollingXRAMFlagProc_WDINT(WORD usTimeout, DWORD ulXRAMAddr, BYTE ucBit, bit bSuccess);

extern bit ScalerTimerPollingFlagProc(WORD usTimeout, WORD usRegister, BYTE ucBit, bit bSuccess);
extern bit ScalerTimerPollingFlagProc_EXINT0(WORD usTimeout, WORD usRegister, BYTE ucBit, bit bSuccess);
extern bit ScalerTimerPollingFlagProc_WDINT(WORD usTimeout, WORD usRegister, BYTE ucBit, bit bSuccess);

extern bit ScalerTimerPollingFlagProc32Bit(DWORD ulTimeout, DWORD ulRegister, DWORD ulBit, DWORD ulbSuccess);

extern bit ScalerTimerPollingDataBitFlagProc(WORD usTimeout, WORD usRegister, BYTE ucValue, BYTE ucBit, bit bSuccess);
extern bit ScalerTimerPollingPortFlagProc(WORD usTimeout, WORD usPortAddress, BYTE ucRegister, BYTE ucBit, bit bSuccess);

extern void ScalerTimerWDActivateTimerEvent(WORD usTimeMS, EnumScalerWDTimerEventID enumEventID);
extern void ScalerTimerWDUpdateTimerEventTable(WORD usTimeMS, EnumScalerWDTimerEventID enumEventID);
extern void ScalerTimerWDActivateTimerEvent_WDINT(WORD usTimeMS, EnumScalerWDTimerEventID enumEventID);
extern void ScalerTimerWDActivateTimerEvent_EXINT0(WORD usTimeMS, EnumScalerWDTimerEventID enumEventID);
extern void ScalerTimerWDCancelTimerEvent(EnumScalerWDTimerEventID enumEventID);
extern void ScalerTimerWDCancelTimerEvent_EXINT0(EnumScalerWDTimerEventID enumEventID);
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_TCPM_SUPPORT == _ON))
extern void ScalerTimerWDCancelTimerEvent_WDINT(EnumScalerWDTimerEventID enumEventID);
#endif

