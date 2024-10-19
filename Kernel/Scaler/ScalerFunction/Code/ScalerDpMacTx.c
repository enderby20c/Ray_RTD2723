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
// ID Code      : ScalerDpMacTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_TX__

#include "ScalerFunctionInclude.h"
#include "DpMacTx/ScalerDpMacTx.h"

#if(_DP_MAC_TX_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructDigitalColorInfoChanged g_stDpMacTxInputDigitalColorInfoChanged;
StructDPTxModeInfoType g_stDpMacTxModeInfo;
StructDPTxInputInfo g_stDpMacTxInputInfo;
EnumDPTxHPDEventType g_enumDpMacTxHPDType = _DP_TX_HPD_NONE;
EnumDPTxIRQEventType g_enumDpMacTxIRQType = _DP_TX_IRQ_HPD_NONE;
volatile EnumDPTxIRQEventType g_enumDpMacTxIRQTypeInt = _DP_TX_IRQ_HPD_NONE;
EnumDPTxTRQEventHDCPType g_enumDpMacTxIRQHdcpType = _DP_TX_IRQ_HDCP_NONE;

#if((_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON) && (_PX_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
EnumDpTxHpdQueueType g_enumDpMacTxHpdQueueType = _DP_TX_HPD_QUEUE_NONE;
EnumDpTxHpdQueueType g_enumDpMacTxHpdQueueTypeBackup = _DP_TX_HPD_QUEUE_NONE;
bit g_bDpMacTxIRQHpdQueue = _FALSE;
BYTE g_ucDpMacTxHpdLevel = _LOW;
#endif

#if(_DP_TX_FEC_SUPPORT == _ON)
bit g_bDpMacTxCloneFecEnable = _FALSE;
#endif
StructTimingInfo g_stDpMacTxInputTimingInfo;
StructCloneModeSwitchInfo g_stDpMacTxCloneModeSwitch;
BYTE g_pucDpMacTxHdcpKsvFifo[_DP_TX_HDCP14_DEVICE_COUNT_MAX * 5];
BYTE g_pucDpMacTxHdcpDownStreamV[20];
BYTE g_ucDpMacTxStreamType = _DATA_PATH_NONE;
volatile bit g_bDpMacTxExceedBW = _FALSE;
volatile bit g_bDpMacTxIRQHPDDetected = _FALSE;
volatile bit g_bDpMacTxSourceChanged = _FALSE;
volatile BYTE g_ucDpMacTxStreamSource = _DP_TX_SOURCE_NONE;

volatile bit g_bDpMacTxSecDataFirstApplyed = _FALSE;
volatile bit g_bDpMacTxSecColorFirstApplyed = _FALSE;

bit g_bDpMacTxDownStreamVscSdpSupport;
bit g_bDpMacTxDownStreamFecSupport;

BYTE g_pucDpMacTxVscSdpDB16to18[3];
WORD g_usDpMacTxInputHStartMeasure;
WORD g_usDpMacTxInputHWidthMeasure;
BYTE g_pucDpMacTxPreviousDfpDeviceCap[16]; // Record DPCD 0x00000 ~ 0x0000F Capability
BYTE g_pucDpMacTxPreviousDfpDeviceExtendCap[16]; // Record DPCD 0x02200 ~ 0x0220F Capability

#if(_DFP_SINK_EDID_CHANGE_CHECK_METHOD == _EDID_SHA_CODE)
bit g_bDpMacTxSha1ImportFirstBlockFlag = _TRUE;
WORD g_usDpMacTxSha1ImportDataTotalCount;
BYTE g_pucDpMacTxPreviousDfpDeviceEdidSha1[_DP_TX_EDID_SHA1_VALUE_SIZE_MAX]; // Record Down Stream Edid Sha Code
#else
BYTE g_pucDpMacTxPreviousDfpDeviceEdidBackup[_DP_TX_EDID_SIZE_MAX]; // Record Down Stream Edid Info
#endif

BYTE g_ucDpMacTxPreviousMstCapStatus; // Record DPCD 0x00021 Capability
BYTE g_ucDpMacTxPreviousFecCapStatus; // Record DPCD 0x00090 Capability
BYTE g_ucDpMacTxPreviousDscCapStatus; // Record DPCD 0x00060 Capability
BYTE g_ucDpMacTxPreviousVscSdpCapStatus; // Record DPCD 0x002210 Capability
BYTE *g_pucDpMacTxDownStreamCapTable; // Record Basic or Extend DPCD Cap Table
BYTE g_pucDpMacTxDfpLTTPRCap[8]; // Record LTTPR 0xF00000 ~ 0xF007 Capability
StructDpTxSdpCtrl g_stDpMacTxSdpInfoCtrl;
EnumDpTxSdpDecodeType g_enumDpMacTxSdpDecodeType = _DP_TX_SDP_DECODE_OFF;
EnumPowerStatus g_enumDpMacTxPowerStatus;

StructDownStreamInfo g_stDpMacTxDownStreamInfo;

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
StructDpTxDownStreamDscInfo g_stDpMacTxDownStreamDscInfo;
StructDpMacTxInputDscInfo g_stDpMacTxInputDscInfo;
#endif

// Tx Daisy Stream
BYTE g_pucDpMacTxStreamToIdMapping[_HW_DP_MST_ST_SOURCE_COUNT];
volatile StructTxStreamInfoBackup g_stDpMacTxStreamInfoBackup;

#if(_DP_TX_CONFIG_BY_USER_SUPPORT == _ON)
EnumDpMacTxConfig g_enumDpMacTxConfigSetting = _DP_TX_CONFIG_NONE;
#endif

EnumDPTxEdidVendorModel g_enumDpMacTxEdidVendorModel;
WORD g_usDpMacTxEdidBw;

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
EnumDpMacTxLinkEstablishStatus g_enumDpMacTxLinkEstablishStatus;
EnumDpLinkChannelCodingType g_enumDpMacTxBackupRxCodingType;
BYTE g_ucDpMacTxMainPortChange;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Tx Mode Handler
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxModeHandler(void)
{
#if(_DP_MST_SUPPORT == _ON)
    // Rx in MST Mode & Tx Port Sel to MST Mode
    if(ScalerDpMacTxGetUpReqEnableStatusChange() == _TRUE)
    {
        ScalerDpMacTxUpdateDfpDeviceMsgCapFieldStatus();
    }
#endif

    switch(GET_DP_TX_MODE_STATE())
    {
        case _DP_TX_MODE_STATUS_UNPLUG:

            if(GET_DP_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                // Reset Stream info
                ScalerDpMacTxStreamInfoReset();

                // Reset Link Config info
                ScalerDpMacTxLinkConfigInfoReset();

#if(_DP_MST_SUPPORT == _ON)
                // Reset Mst info
                ScalerDpMacTxMstInfoReset();
#endif

                // Power Down ML PHY
                ScalerDpPhyTxMLPowerOff();

                // Reset Cap info
                ScalerDpMacTxCapInfoReset();

                SET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT(0);
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_OFF:

            if(GET_DP_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                // Reset Stream info
                ScalerDpMacTxStreamInfoReset();

                // Reset Link Config info
                ScalerDpMacTxLinkConfigInfoReset();
            }

            break;

        case _DP_TX_MODE_STATUS_INITIAL:

            if((GET_DP_TX_POWER_STATUS() == _POWER_STATUS_NORMAL) && (GET_DP_MAC_TX_DOWNSTREAM_INFO_READY() == _FALSE))
            {
                // Get Downstream Link Configuration
                if(ScalerDpMacTxLinkConfigInitial() == _TRUE)
                {
                    SET_DP_MAC_TX_DOWNSTREAM_INFO_READY();
                }
            }

            if(GET_DP_MAC_TX_DOWNSTREAM_INFO_READY() == _TRUE)
            {
                SET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS(_DP_PLUG);
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_TRAINING:

            if(GET_DP_MAC_TX_DOWNSTREAM_INFO_READY() == _TRUE)
            {
                ScalerDpPhyTxBandWidthConfig();
                ScalerDpPhyTxLinkTraining();
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_ON:

            if(GET_DP_TX_MODE_STATE_CHANGE() == _TRUE)
            {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if((GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_HDCP2_TX_VERSION_SUPPORTED() == _TRUE))
                {
                    if(GET_DP_HDCP2_TX_AUTH_START() == _FALSE)
                    {
                        SET_DP_HDCP2_TX_DOWNSTREAM_EVENT(_DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_REAUTH);
                    }
                }
                else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#else
                if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#endif
                {
                    if(ScalerSyncDpHdcpDownstreamReAuthCheck() == _TRUE)
                    {
                        if(ScalerDpHdcp14TxDownstreamBksvChange() == _FALSE)
                        {
                            SET_DP_TX_HDCP_AUTH_START();
                        }
                        else
                        {
                            SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH);
                        }
                    }
                }

                // For Sec Setting When State Change to Link On State
                CLR_DP_MAC_TX_SEC_DATA_FIRST_APPLYED_DONE();
                CLR_DP_MAC_TX_SEC_COLOR_FIRST_APPLYED_DONE();
            }

            ScalerDpMacTxStreamHandler();

            break;

        case _DP_TX_MODE_STATUS_AUTOTEST:

            if(GET_DP_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_MODE_STATE_CHANGE();

                ScalerDpPhyTxAutoTest();

                CLR_DP_TX_CTS_TEST_REQUEST_TYPE();
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Tx Mode Judge
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxJudgeHandler(void)
{
    CLR_DP_TX_MODE_STATE_CHANGE();

    switch(GET_DP_TX_MODE_STATE())
    {
        case _DP_TX_MODE_STATUS_UNPLUG:

            if(GET_DP_TX_HPD_EVENT() == _DP_TX_HPD_PLUG_EVENT)
            {
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_INITIAL);
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_OFF:

            if(GET_DP_TX_HPD_EVENT() == _DP_TX_HPD_PLUG_EVENT)
            {
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_INITIAL);
            }
            else if(GET_DP_TX_HPD_DEBOUNCE() == _TRUE)
            {
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_UNPLUG);
            }

            break;

        case _DP_TX_MODE_STATUS_INITIAL:

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
            {
                CLR_DP_MAC_TX_DOWNSTREAM_INFO_READY();
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_INITIAL);
            }
            else if(GET_DP_MAC_TX_DOWNSTREAM_INFO_READY() == _TRUE)
            {
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
            }

            // For PHY CTS test
            if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_PHY_TEST_PATTERN) == _DP_TX_CTS_PHY_TEST_PATTERN)
            {
                DebugMessageDpTx("_DP_TX_MODE_STATUS_AUTOTEST--_DP_TX_MODE_STATUS_INITIAL", 0x00);

                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_AUTOTEST);
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_TRAINING:

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
            {
                CLR_DP_MAC_TX_DOWNSTREAM_INFO_READY();
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_INITIAL);
            }
            else if((GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) ||
                    (GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING))
            {
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
            }
            else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
            {
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_ON);
            }

            // For Link CTS test
            if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING)
            {
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
                DebugMessageDpTx("A1. DP Tx Mode Status Change Judge : LINK_TRAINING (CTS_TEST_LINK_TRAINING)", _DP_TX_MODE_STATUS_LINK_TRAINING);
            }

            // For PHY CTS test
            if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_PHY_TEST_PATTERN) == _DP_TX_CTS_PHY_TEST_PATTERN)
            {
                DebugMessageDpTx("_DP_TX_MODE_STATUS_AUTOTEST--_DP_TX_MODE_STATUS_LINK_TRAINING", 0x00);
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_AUTOTEST);
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_ON:

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
            {
                CLR_DP_MAC_TX_DOWNSTREAM_INFO_READY();
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_INITIAL);
            }
            else if((GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) ||
                    (GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING))
            {
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
            }

            // For Link CTS test
            if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING)
            {
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
                DebugMessageDpTx("A1. DP Tx Mode Status Change Judge : LINK_TRAINING (CTS_TEST_LINK_TRAINING)", _DP_TX_MODE_STATUS_LINK_ON);
            }

            // For PHY CTS test
            if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_PHY_TEST_PATTERN) == _DP_TX_CTS_PHY_TEST_PATTERN)
            {
                DebugMessageDpTx("_DP_TX_MODE_STATUS_AUTOTEST--_DP_TX_MODE_STATUS_LINK_ON", 0x00);

                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_AUTOTEST);
            }

            break;

        case _DP_TX_MODE_STATUS_AUTOTEST:

            // For PHY CTS test
            if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_PHY_TEST_PATTERN) == _DP_TX_CTS_PHY_TEST_PATTERN)
            {
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_AUTOTEST);
                CLR_DP_TX_CTS_TEST_REQUEST_TARGET_TYPE(_DP_TX_CTS_PHY_TEST_PATTERN);
            }

            // For Link CTS test
            if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING)
            {
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
                DebugMessageDpTx("A1. DP Tx Mode Status Change Judge : LINK_TRAINING (CTS_TEST_LINK_TRAINING)", _DP_TX_MODE_STATUS_LINK_ON);
            }
            break;


        default:

            break;
    }

    if(GET_DP_TX_HPD_EVENT() == _DP_TX_HPD_UNPLUG_EVENT)
    {
        if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_UNPLUG)
        {
#if(_DP_MST_SUPPORT == _ON)
            // Check MST to MST case
            if(ScalerDpMacTxMstCancelDebounceCheck() == _TRUE)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HPD_DEBOUNCE);

                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_UNPLUG);
            }
            else
#endif
            {
                ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_OFF);
            }
        }
    }

    if(GET_DP_TX_FORCE_LINK_TRAINING() == _TRUE)
    {
        CLR_DP_TX_FORCE_LINK_TRAINING();

        if((GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_UNPLUG) &&
           (GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_OFF) &&
           (GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_INITIAL))
        {
            ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
        }
    }

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
    // Mode Status Change to Unplug For Contol Aux Communication When HPD Detection Disable
    if(GET_DP_TX_HPD_DETECTION_ENABLE() == _DISABLE)
    {
        if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_UNPLUG)
        {
            DebugMessageDpTx("8. Dp Tx State Change to Unplug For Contol Aux Communication", 1);

            ScalerDpMacTxStateChangeEvent(_DP_TX_MODE_STATUS_UNPLUG);
        }
    }
#endif

    if((GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_UNPLUG) && (GET_DP_TX_MODE_STATE_CHANGE() == _TRUE))
    {
        DebugMessageDpTx("7. Dp Tx Mode State change to Unplug", 0);
    }
    else if((GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_LINK_OFF) && (GET_DP_TX_MODE_STATE_CHANGE() == _TRUE))
    {
        DebugMessageDpTx("7. Dp Tx Mode State change to Link Off", 1);
    }
    else if((GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_INITIAL) && (GET_DP_TX_MODE_STATE_CHANGE() == _TRUE))
    {
        DebugMessageDpTx("7. Dp Tx Mode State change to Intial", 2);
    }
    else if((GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_LINK_TRAINING) && (GET_DP_TX_MODE_STATE_CHANGE() == _TRUE))
    {
        DebugMessageDpTx("7. Dp Tx Mode State change to LinkTraining", 3);
    }
    else if((GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_LINK_ON) && (GET_DP_TX_MODE_STATE_CHANGE() == _TRUE))
    {
        DebugMessageDpTx("7. Dp Tx Mode State change to Link On", 4);
    }
}

//--------------------------------------------------
// Description  : DP Tx Training Pattern Setting_8b10b
// Input Value  : Training Pattern
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxMainLinkPatternSetting_8b10b(EnumDPTxMainLinkPattern enumDPTxMainLinkPattern)
{
    switch(enumDPTxMainLinkPattern)
    {
        case _DP_TX_OUTPUT_TPS1:

            // Disable scramble
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~(_BIT4 | _BIT0), 0x00);

            // Main Link switch to TP1 Pattern
            ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), enumDPTxMainLinkPattern);

            break;

        case _DP_TX_OUTPUT_TPS2:

            // Disable scramble
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~(_BIT4 | _BIT0), 0x00);

            // Main Link Switch to TPS2 Pattern
            ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), enumDPTxMainLinkPattern);

            break;

        case _DP_TX_OUTPUT_TPS3:

            // Disable scramble
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~(_BIT4 | _BIT0), 0x00);

            // Main Link Switch to TPS3 Pattern
            ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), enumDPTxMainLinkPattern);

            break;

        case _DP_TX_OUTPUT_EYE_PATTERN:

            // Disable Enhanced Mode
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, 0x00);

            // Enable Sramble and Enable BS replaced by SR
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT4, _BIT4);
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT0, _BIT0);

            // Main Link Switch to TPS4 Pattern
            ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), enumDPTxMainLinkPattern);

            // Select CP2520 pattern 3 "SR-BS-BS-SR-248 of 00h's"
            ScalerSetBit(PBB_0C_COMPLIANCE_EYE_PATTERN, ~(_BIT1 | _BIT0), _BIT1);

            // Set TPS4 eyecounter HW auto reset
            ScalerSetBit(PBB_9B_DUMMY_2, ~_BIT0, _BIT0);

            break;

        case _DP_TX_OUTPUT_IDLE_PATTERN:

            // Restore Enhanced Mode because Scramble Circuit can't Match SR-BS-BS-SR(TPS4 pattern) to Reset LFSR with TPS4 pattern in TP2 stage if Enhanced Mode is enable
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, ((BYTE)GET_DP_MAC_TX_DOWNSTREAM_ENHANCE_FRAMING() << 2));

            // Enable Sramble and Enable BS replaced by SR
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT4, _BIT4);
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT0, _BIT0);

            // Main Link switch to IDLE Pattern
            ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), enumDPTxMainLinkPattern);

            break;

        case _DP_TX_OUTPUT_VIDEO_PATTERN:

            // Main Link switch to VIDEO pattern
            ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), enumDPTxMainLinkPattern);

            break;

        default:
            break;
    }

    if(enumDPTxMainLinkPattern == _DP_TX_OUTPUT_VIDEO_PATTERN)
    {
        // Double buffer only by Vsync
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // Direct Apply Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~_BIT0, _BIT0);

        if(enumDPTxMainLinkPattern == _DP_TX_OUTPUT_IDLE_PATTERN)
        {
            // Toggle Arbiter to Avoid DPTX MAC FSM Dead Lock
            ScalerSetBit(PBB_C9_ARBITER_CTRL, ~(_BIT5 | _BIT0), 0x00);
            ScalerSetBit(PBB_C9_ARBITER_CTRL, ~(_BIT5 | _BIT0), _BIT0);
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Training Pattern Setting
// Input Value  : Training Pattern
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxMainLinkPatternSetting(EnumDPTxMainLinkPattern enumDPTxMainLinkPattern)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxMainLinkPatternSetting_128b132b(enumDPTxMainLinkPattern);
    }
    else
#endif
    {
        ScalerDpMacTxMainLinkPatternSetting_8b10b(enumDPTxMainLinkPattern);
    }
}

//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxInitial(void)
{
    // For HDCP Auth
    ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);

    // Set ECF by FW mode
    ScalerSetBit(PBB_64_HDCP_ECF_BYTE0, ~_BIT7, 0x00);

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerSetBit(P2B_4B_HDCP_ECF_CTL, ~_BIT0, 0x00);
#endif

    // Power Down ML PHY
    ScalerDpPhyTxMLPowerOff();

    // Power CMU PHY
    ScalerDpPhyTxCMUPowerOff();

    SET_DP_TX_HPD_FIRST_DETECT();

    // Set HPD 0.5ms Timer to 0.25ms
    ScalerDpMacTxSetHpdTimer(_DP_TX_HPD_5_TIMER, 250);

    // Set HPD 1ms Timer to 2ms
    ScalerDpMacTxSetHpdTimer(_DP_TX_HPD_10_TIMER, 2000);

    // Set HPD 2ms Timer to 2ms
    ScalerDpMacTxSetHpdTimer(_DP_TX_HPD_20_TIMER, 2000);

    // Set HPD 10ms Timer to 2ms
    ScalerDpMacTxSetHpdTimer(_DP_TX_HPD_100_TIMER, 2000);

    // Enable HPD Detection
    ScalerSetBit(PBB_70_HPD_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PBB_70_HPD_CTRL, ~_BIT7, _BIT7);

    // Delay for HPD Detection Timeout
    ScalerTimerDelayXms(3);

    // Clear HPD IRQ Flag
    ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);

    // Clear IRQ HPD Type Flag
    CLR_DP_TX_IRQ_HPD_TYPE();
    CLR_DP_TX_IRQ_HPD_TYPE_INT();
    CLR_DP_TX_IRQ_HPD_DETECTED();
    CLR_DP_TX_IRQ_HDCP_TYPE();

    // Reset HDCP info
    ScalerDpHdcp14TxResetInfo();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    CLR_DP_HDCP2_TX_IRQ_TYPE();
#endif

    // Enable Short IRQ and Disable Long IRQ
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~(_BIT6 | _BIT5), _BIT6);

#if(_DP_MST_SUPPORT == _ON)

    // Clear Up Req Msg Header
    CLR_DP_MST_TX_UP_REQUEST_MSG_HEADER();

    // HW will auto calculate Start and End
    SET_DP_MST_TX_REG_DOWNSTREAM_MSG_AUTO_MODE();

    // Set TX MSG Aux Write Burst Length 16bytes
    SET_DP_MST_TX_REG_DOWNSTREAM_MSG_BURST_LENGTH(_DP_MST_TX_AUX_WRITE_BURST_LENGTH);

    // Enable Only Read One SBMSG
    Scaler32SetBit(PB18083_80_AUX_TX_MSG_RD_CTRL, ~_BIT5, _BIT5);

    // Set TX MSG Aux Read Burst Length 16bytes
    SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_BURST_LENGTH(_DP_MST_TX_AUX_READ_BURST_LENGTH);

    // Enable DP Tx Link Clock
    ScalerDpMstTxLinkClockEn(_ENABLE);
#endif

    // Set DP TX CLK divider
    ScalerSetBit(PBB_E0_DPTX_CLK_GEN, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Enable Arbiter Stuffing and Framing
    ScalerSetBit(PBB_C9_ARBITER_CTRL, ~(_BIT5 | _BIT0), _BIT0);

    // Set Effect Time of Double Buffer As 1st BE of 1 Frame Period was Sent by DPTX for Sdp Decode Function
    ScalerSetBit(PBC_95_DUMMY_95, ~(_BIT7 | _BIT6), _BIT7);

    // Set DP Tx Default Coding Type
    SET_DP_MAC_TX_DOWNSTREAM_PRE_CODING_TYPE(_CODING_TYPE_8B10B);
    SET_DP_TX_LT_PROCESSING(_FALSE);

    if(ScalerDpMacTxNewComponentModeAvailable() == _TRUE)
    {
        // Set Component Format New Mode
        ScalerSetBit(PBB_FE_DPTX_TOP_RSV9, ~_BIT1, 0x00);
    }

    // Clear HDCP Flag
    CLR_DP_TX_HDCP_AUTH_START();
    CLR_DP_TX_HDCP_AUTH_HOLD();

#if(_DP_TX_AUDIO_SUPPORT == _ON)
    // Clear Audio Flag
    CLR_DP_TX_AUDIO_READY_TO_PLAY();
    CLR_DP_TX_AUDIO_SAMPLING_FREQUENCY();
    CLR_DP_TX_AUDIO_CHANNEL_COUNT();
    CLR_DP_TX_AUDIO_CODING_TYPE();
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

    // Clear Link CTS Request Type
    CLR_DP_TX_CTS_TEST_REQUEST_TYPE();

#if(_DP_SUPPORT == _ON)
#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
    SET_DP_RX_CAPABILITY_SWITCHED();
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    ScalerDpMacTxDscPassThroughReset();
#endif
#endif

#if((_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON) && (_DP_TX_FEC_SUPPORT == _ON))
    ScalerSetBit(P2B_1E_DPTX_FEC, ~_BIT1, 0x00);
#endif

    // Disable Reorder Tracking Mode Setting
    ScalerDpMacTxReorderReset();
}

//--------------------------------------------------
// Description  : DP Tx Set Hpd Timer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetHpdTimer(EnumDPTxHPDTimer enumDpTxHpdTimer, WORD usHpdTargetTimer)
{
    BYTE ucHpdClkDiv = 0;

    // HPD Clk Div
    ucHpdClkDiv = 8 << (ScalerGetBit(PBB_70_HPD_CTRL, (_BIT6 | _BIT5)) >> 5);

    // Target Clk Cnt = usHpdTargetTimer * GDI_CLK(Khz) / Div / 1000
    usHpdTargetTimer = ScalerGlobalComputeDwordMulDiv((DWORD)usHpdTargetTimer, _GDIPHY_RX_GDI_CLK_KHZ, (DWORD)ucHpdClkDiv) / 1000;

    switch(enumDpTxHpdTimer)
    {
        case _DP_TX_HPD_5_TIMER:
            ScalerSetBit(PBB_73_HPD_TIMER1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (HIBYTE(usHpdTargetTimer) << 4));
            ScalerSetByte(PBB_74_HPD_TIMER2, LOBYTE(usHpdTargetTimer));
            break;

        case _DP_TX_HPD_10_TIMER:
            ScalerSetBit(PBB_73_HPD_TIMER1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHpdTargetTimer) & 0x0F));
            ScalerSetByte(PBB_75_HPD_TIMER3, LOBYTE(usHpdTargetTimer));
            break;

        case _DP_TX_HPD_20_TIMER:
            ScalerSetBit(PBB_76_HPD_TIMER4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHpdTargetTimer) & 0x0F));
            ScalerSetByte(PBB_77_HPD_TIMER5, LOBYTE(usHpdTargetTimer));
            break;

        case _DP_TX_HPD_100_TIMER:
            ScalerSetByte(PBB_78_HPD_TIMER6, HIBYTE(usHpdTargetTimer));
            ScalerSetByte(PBB_79_HPD_TIMER7, LOBYTE(usHpdTargetTimer));
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Switch to Active State
// Input Value  : Target Tx Mode
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxStateChangeEvent(EnumDPTxModeStatus enumModeState)
{
    SET_DP_TX_MODE_STATE(enumModeState);
    SET_DP_TX_MODE_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : DP Tx HPD Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxHPDProc(void)
{
    SET_DP_TX_HPD_EVENT(_DP_TX_HPD_NO_EVENT);
    CLR_DP_TX_HPD_TYPE();
    CLR_DP_TX_IRQ_HPD_TYPE();

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
    if(GET_DP_TX_HPD_DETECTION_ENABLE() == _DISABLE)
    {
        DebugMessageDpTx("8. Dp Tx HPD Proc Return Directly", 1);

        return;
    }
#endif

#if((_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON) && (_PX_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    // Get Current PD HPD Queue
    ScalerDpMacTxGetHpdQueueProc();

    // Previous Backup Queue Type is High or Low High, Current Queue Type is None, Set Queue Type --> High
    if(GET_DP_TX_HPD_QUEUE_TYPE_BACKUP() == _DP_TX_HPD_QUEUE_HIGH)
    {
        CLR_DP_TX_HPD_QUEUE_TYPE_BACKUP();

        if((GET_DP_TX_HPD_QUEUE_TYPE() == _DP_TX_HPD_QUEUE_NONE) || (GET_DP_TX_HPD_QUEUE_TYPE() == _DP_TX_HPD_QUEUE_LOW_HIGH))
        {
            SET_DP_TX_HPD_QUEUE_TYPE(_DP_TX_HPD_QUEUE_HIGH);
        }
    }

    if(GET_DP_TX_PD_HPD_LEVEL() == _HIGH)
    {
        if(GET_DP_TX_HPD_QUEUE_TYPE() == _DP_TX_HPD_QUEUE_LOW)
        {
            SET_DP_TX_PD_HPD_LEVEL(_LOW);
            SET_DP_TX_HPD_TYPE(_DP_TX_HPD_UNPLUG);
            DebugMessageDpTx("7. Dp Tx PD Unplug Flag Set", 1);
        }

        if(GET_DP_TX_HPD_QUEUE_TYPE() == _DP_TX_HPD_QUEUE_LOW_HIGH)
        {
            SET_DP_TX_PD_HPD_LEVEL(_LOW);
            SET_DP_TX_HPD_TYPE(_DP_TX_HPD_UNPLUG);

            // Queue Type is Low High Need Backup High Type
            SET_DP_TX_HPD_QUEUE_TYPE_BACKUP(_DP_TX_HPD_QUEUE_HIGH);
            DebugMessageDpTx("7. Dp Tx PD Unplug Flag Set & Backup High", 1);
        }

        CLR_DP_TX_HPD_QUEUE_TYPE();
    }
    else
    {
        if((GET_DP_TX_HPD_QUEUE_TYPE() == _DP_TX_HPD_QUEUE_HIGH) || (GET_DP_TX_HPD_QUEUE_TYPE() == _DP_TX_HPD_QUEUE_LOW_HIGH))
        {
            SET_DP_TX_PD_HPD_LEVEL(_HIGH);
            SET_DP_TX_HPD_TYPE(_DP_TX_HPD_REPLUG);
            DebugMessageDpTx("7. Dp Tx PD Plug Flag Set", 1);
        }

        CLR_DP_TX_HPD_QUEUE_TYPE();
    }

    if(GET_DP_TX_IRQ_HPD_QUEUE() == _TRUE)
    {
        CLR_DP_TX_IRQ_HPD_QUEUE();
        SET_DP_TX_HPD_TYPE(_DP_TX_HPD_IRQ);
    }
#else
    // Disable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

    // Record which kind of HPD Change happened by now
    pData[0] = ScalerGetByte(PBB_71_HPD_IRQ);

    if((pData[0] & _BIT2) == _BIT2)
    {
        SET_DP_TX_HPD_TYPE(_DP_TX_HPD_REPLUG);
        DebugMessageDpTx("7. Dp Tx HW Replug Flag Set", pData[0]);
    }

    if((pData[0] & _BIT4) == _BIT4)
    {
        SET_DP_TX_HPD_TYPE(_DP_TX_HPD_UNPLUG);
        DebugMessageDpTx("7. Dp Tx HW Unplug Flag Set", 1);
    }

    if(((pData[0] | ((BYTE)GET_DP_TX_IRQ_HPD_DETECTED() << 6)) & _BIT6) == _BIT6)
    {
        SET_DP_TX_HPD_TYPE(_DP_TX_HPD_IRQ);
    }

    // Copy IRQ type Detected In INT
    SET_DP_TX_IRQ_HPD_TYPE(GET_DP_TX_IRQ_HPD_TYPE_INT());

    CLR_DP_TX_IRQ_HPD_DETECTED();

    // Clear IRQ type of Int.
    CLR_DP_TX_IRQ_HPD_TYPE_INT();
#endif

    // Determine Current HPD Event Status
    // Current HPD Level HIGH
    if(GET_DP_TX_HPD_DEBOUNCE_LEVEL() == _HIGH)
    {
        if(GET_DP_TX_HPD_TYPE(_DP_TX_HPD_UNPLUG) == _DP_TX_HPD_UNPLUG)
        {
            // HPD unplug Event
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_UNPLUG_EVENT);

            // Clear Unplug Flag
            ScalerSetBit(PBB_71_HPD_IRQ, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT4);
        }
        else if(GET_DP_TX_HPD_TYPE(_DP_TX_HPD_REPLUG) == _DP_TX_HPD_REPLUG)
        {
            // Plug HPD
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_PLUG_EVENT);

            // Clr All flag
            ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);
        }
        else if(GET_DP_TX_HPD_TYPE(_DP_TX_HPD_IRQ) == _DP_TX_HPD_IRQ)
        {
            // Short HPD
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_IRQ_EVENT);
        }

        // AC On Case, First HPD From Low to High
        if(GET_DP_TX_HPD_FIRST_DETECT() == _TRUE)
        {
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_PLUG_EVENT);

            // Clr All flag
            ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);

            CLR_DP_TX_HPD_FIRST_DETECT();
        }
    }
    else
    {
        if((GET_DP_TX_HPD_TYPE(_DP_TX_HPD_UNPLUG) == _DP_TX_HPD_UNPLUG) || (GET_DP_TX_HPD_FIRST_DETECT() == _TRUE))
        {
            CLR_DP_TX_HPD_FIRST_DETECT();

            // Plug HPD
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_UNPLUG_EVENT);

            // Clear Unplug Flag
            ScalerSetBit(PBB_71_HPD_IRQ, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT4);
        }
    }

    switch(GET_DP_TX_HPD_EVENT())
    {
        case _DP_TX_HPD_PLUG_EVENT:

#if(_DP_TX_HPD_HIGH_DEBOUNCE_SUPPORT == _ON)
            CLR_DP_TX_HPD_DEBOUNCE();

            ScalerTimerReactiveTimerEvent(100, _SCALER_TIMER_EVENT_DP_TX_HPD_DEBOUNCE);
#endif

            break;

        case _DP_TX_HPD_IRQ_EVENT:

            // Check Short HPD IRQ Type
            ScalerDpMacTxIRQEventCheck();

            break;

        case _DP_TX_HPD_UNPLUG_EVENT:

            CLR_DP_TX_HPD_DEBOUNCE();

            ScalerTimerReactiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_TX_HPD_DEBOUNCE);

            break;

        default:
            break;
    }

    // Enable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);
}

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DP Rx and DP Tx Channel Coding
// Input Value  : None
// Output Value : TRUE(go to Internal data path judge) or FALSE(DP Tx re-link training)
//--------------------------------------------------
void ScalerDpMacTxLinkEstablishManagement(void)
{
    BYTE ucDpRxLTResult = _DP_LINK_TRAINING_NONE;
    bit bDpRxLinkTrainingPass = _FALSE;
    EnumDPTxLTResult enumDpTxLTResult = _DP_TX_TRAINING_NO_RESULT;
    EnumInputPort enumInputPort = GET_DP_RX_MAIN_PORT();
    EnumDpLinkChannelCodingType enumDpRxCodingType = _CODING_TYPE_NONE;
    EnumDpLinkRate enumDpRxMaxLinkRateCapbility = _DP_LINK_NONE;

    enumDpRxCodingType = ScalerDpAuxRxGetCodingType(enumInputPort);
    enumDpRxMaxLinkRateCapbility = ScalerDpAuxRxGetDpcdMaxLinkRateCapability(enumInputPort);
    enumDpTxLTResult = GET_DP_TX_LT_RESULT();

    // Rx main port change
    if(GET_DP_MAC_TX_MAIN_PORT_CHANGE() == _TRUE)
    {
        CLR_DP_MAC_TX_MAIN_PORT_CHANGE();
        CLR_DP_MAC_TX_LINK_ESTABLISH_STATUS();
    }

    ucDpRxLTResult = ScalerDpAuxRxGetLTStatus(enumInputPort);

    if((ucDpRxLTResult == _DP_NORMAL_LINK_TRAINING_PASS) || (ucDpRxLTResult == _DP_FAKE_LINK_TRAINING_PASS))
    {
        bDpRxLinkTrainingPass = _TRUE;
    }

    // SST/MST case Rx link coding type change, tx check link again
    if(GET_DP_MAC_TX_BACKUP_RX_CODING_TYPE() != enumDpRxCodingType)
    {
        SET_DP_MAC_TX_BACKUP_RX_CODING_TYPE(enumDpRxCodingType);
        CLR_DP_MAC_TX_LINK_ESTABLISH_STATUS();
    }

    // Tx link training pass, tx check link again for DFP replug (eg.Long HPD, Capability change to DP20)
    if(enumDpTxLTResult == _DP_TX_TRAINING_PASS)
    {
        if((enumDpRxCodingType == _CODING_TYPE_8B10B) && (ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B))
        {
            CLR_DP_MAC_TX_LINK_ESTABLISH_STATUS();
        }
    }

    switch(enumDpTxLTResult)
    {
        case _DP_TX_TRAINING_NO_RESULT:

            if(GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() != _LINK_ESTABLISH_NONE)
            {
                CLR_DP_MAC_TX_LINK_ESTABLISH_STATUS();
            }

            if((bDpRxLinkTrainingPass == _TRUE) && (enumDpRxCodingType == _CODING_TYPE_8B10B))
            {
                // RX Link Training Pass: Use RX Coding Type as Reference
                SET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE(_CODING_TYPE_8B10B);
            }
            break;

        case _DP_TX_TRAINING_PASS:

            if(GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() != _LINK_ESTABLISH_READY)
            {
                if(bDpRxLinkTrainingPass == _TRUE)
                {
                    if(enumDpRxCodingType == _CODING_TYPE_128B132B)
                    {
                        if(GET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE() == _CODING_TYPE_8B10B)
                        {
                            // Condition : DP14 Source change to DP20 Source
                            SET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE(_CODING_TYPE_NONE);

                            if((GET_DP_MAC_TX_DOWNSTREAM_128B132B_SUPPORT() == _TRUE) && (ScalerDpMacTxGetChannelCodingType() != _CODING_TYPE_128B132B))
                            {
                                SET_DP_TX_FORCE_LINK_TRAINING();
                                SET_DP_MAC_TX_LINK_ESTABLISH_STATUS(_LINK_ESTABLISH_WAIT);
                                DebugMessageDpTx("[Link Establish] DP20 to DP14 : Force Re-link Training to Sink Cap. (DP20)", ScalerDpMacTxGetChannelCodingType());
                            }
                            else
                            {
                                SET_DP_MAC_TX_LINK_ESTABLISH_STATUS(_LINK_ESTABLISH_READY);
                                DebugMessageDpTx("[Link Establish] DP20 to DP20 : Don't need Re-link Training to Sink Cap.", ScalerDpMacTxGetChannelCodingType());
                            }
                        }
                        else
                        {
                            SET_DP_MAC_TX_LINK_ESTABLISH_STATUS(_LINK_ESTABLISH_READY);
                            DebugMessageDpTx("[Link Establish] READY (DP20 to DPXX)", ScalerDpMacTxGetChannelCodingType());
                        }
                    }
                    else
                    {
                        if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
                        {
                            // Change DP Tx Link Rate
                            SET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE(_CODING_TYPE_8B10B);
                            SET_DP_TX_FORCE_LINK_TRAINING();
                            SET_DP_MAC_TX_LINK_ESTABLISH_STATUS(_LINK_ESTABLISH_WAIT);
                            DebugMessageDpTx("[Link Establish] DP14 to DP20 : Force Re-link Training to DP14", ScalerDpMacTxGetChannelCodingType());
                        }
                        else
                        {
                            SET_DP_MAC_TX_LINK_ESTABLISH_STATUS(_LINK_ESTABLISH_READY);
                            DebugMessageDpTx("[Link Establish] DP14 to DP14 : Don't need Re-link Training", ScalerDpMacTxGetChannelCodingType());
                        }
                    }
                }
                else
                {
                    // DPRx Capbility Change Case
                    // RX Unknown Link Training Result: Use RX Max Link Rate Capability as Reference
                    if(enumDpRxMaxLinkRateCapbility >= _DP_LINK_UHBR10)
                    {
                        if(GET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE() == _CODING_TYPE_8B10B)
                        {
                            // Condition : DP14 Source change to DP Rx no link training (cable change or main port change)
                            SET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE(_CODING_TYPE_NONE);

                            if((GET_DP_MAC_TX_DOWNSTREAM_128B132B_SUPPORT() == _TRUE) && (ScalerDpMacTxGetChannelCodingType() != _CODING_TYPE_128B132B))
                            {
                                SET_DP_TX_FORCE_LINK_TRAINING();
                                SET_DP_MAC_TX_LINK_ESTABLISH_STATUS(_LINK_ESTABLISH_WAIT);
                                DebugMessageDpTx("[Link Establish] DP Rx unknown to DP14 : Force Re-link Training to Sink Cap. (DP20)", ScalerDpMacTxGetChannelCodingType());
                            }
                            else
                            {
                                SET_DP_MAC_TX_LINK_ESTABLISH_STATUS(_LINK_ESTABLISH_READY);
                                DebugMessageDpTx("[Link Establish] DP Rx unknown to DP20 : Don't need Re-link Training to Sink Cap.", ScalerDpMacTxGetChannelCodingType());
                            }
                        }
                        else
                        {
                            SET_DP_MAC_TX_LINK_ESTABLISH_STATUS(_LINK_ESTABLISH_READY);
                            DebugMessageDpTx("[Link Establish] DP Rx unknown to DP Link pass : Don't need Re-link Training to Sink Cap.", ScalerDpMacTxGetChannelCodingType());
                        }
                    }
                    else
                    {
                        if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
                        {
                            // Change DP Tx Link Rate
                            SET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE(_CODING_TYPE_8B10B);
                            SET_DP_TX_FORCE_LINK_TRAINING();
                            SET_DP_MAC_TX_LINK_ESTABLISH_STATUS(_LINK_ESTABLISH_WAIT);
                            DebugMessageDpTx("[Link Establish] DP Rx unknown(Max Link Rate <= HBR3) to DP20 : Force Re-link Training to DP14", ScalerDpMacTxGetChannelCodingType());
                        }
                        else
                        {
                            SET_DP_MAC_TX_LINK_ESTABLISH_STATUS(_LINK_ESTABLISH_READY);
                            DebugMessageDpTx("[Link Establish] DP Rx unknown to DP14 : Don't need Re-link Training", ScalerDpMacTxGetChannelCodingType());
                        }
                    }
                }
            }
            break;

        case _DP_TX_TRAINING_FAIL:

            SET_DP_MAC_TX_LINK_ESTABLISH_STATUS(_LINK_ESTABLISH_FAIL);
            break;

        default:

            SET_DP_MAC_TX_LINK_ESTABLISH_STATUS(_LINK_ESTABLISH_WAIT);
            break;
    }
}
#endif

#if((_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON) && (_PX_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Tx Get TypeC HPD Queue
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxGetHpdQueueProc(void)
{
    StructTypeCTxHpdQueue stHpdQueue;
    BYTE ucDpHpdCnt = 0;

    stHpdQueue = ScalerTypeCTxGetHPDQueue(_P0_OUTPUT_PORT);

    // Record if PD Queue has IRQ
    for(ucDpHpdCnt = 0; ucDpHpdCnt < stHpdQueue.b3TxHpdCnt; ucDpHpdCnt++)
    {
        DebugMessageDpTx("7. Dp Tx PD Queue Type", stHpdQueue.penumTxHpdType[ucDpHpdCnt]);

        if(stHpdQueue.penumTxHpdType[ucDpHpdCnt] == _PD_HPD_IRQ)
        {
            stHpdQueue.penumTxHpdType[ucDpHpdCnt] = _PD_HPD_NONE;
            SET_DP_TX_IRQ_HPD_QUEUE();
        }
    }

    for(ucDpHpdCnt = 0; ucDpHpdCnt < stHpdQueue.b3TxHpdCnt; ucDpHpdCnt++)
    {
        if(stHpdQueue.penumTxHpdType[ucDpHpdCnt] == _PD_HPD_LOW)
        {
            for(pData[0] = stHpdQueue.b3TxHpdCnt - 1; pData[0] > ucDpHpdCnt; pData[0]--)
            {
                if(stHpdQueue.penumTxHpdType[pData[0]] == _PD_HPD_HIGH)
                {
                    // Current Queue is (L,H) or (L,H,L,H) Set Queue Type --> Low High
                    SET_DP_TX_HPD_QUEUE_TYPE(_DP_TX_HPD_QUEUE_LOW_HIGH);
                    return;
                }
                else if(stHpdQueue.penumTxHpdType[pData[0]] == _PD_HPD_LOW)
                {
                    // Current Queue is (L,L)or (L,H,L) Set Queue Type --> Low
                    SET_DP_TX_HPD_QUEUE_TYPE(_DP_TX_HPD_QUEUE_LOW);
                    return;
                }
            }

            // Current Queue is L Set Queue Type --> Low
            SET_DP_TX_HPD_QUEUE_TYPE(_DP_TX_HPD_QUEUE_LOW);
            return;
        }
        else if(stHpdQueue.penumTxHpdType[ucDpHpdCnt] == _PD_HPD_HIGH)
        {
            for(pData[0] = stHpdQueue.b3TxHpdCnt - 1; pData[0] > ucDpHpdCnt; pData[0]--)
            {
                if(stHpdQueue.penumTxHpdType[pData[0]] == _PD_HPD_LOW)
                {
                    // Current Queue is (H,L) or (H,L,H,L) Set Queue Type --> Low
                    SET_DP_TX_HPD_QUEUE_TYPE(_DP_TX_HPD_QUEUE_LOW);
                    return;
                }
                else if(stHpdQueue.penumTxHpdType[pData[0]] == _PD_HPD_HIGH)
                {
                    // Current Queue is (H,H)or (H,L,H) Set Queue Type --> High
                    SET_DP_TX_HPD_QUEUE_TYPE(_DP_TX_HPD_QUEUE_HIGH);
                    return;
                }
            }

            // Current Queue is H Set Queue Type --> High
            SET_DP_TX_HPD_QUEUE_TYPE(_DP_TX_HPD_QUEUE_HIGH);
            return;
        }
    }
}

//--------------------------------------------------
// Description  : Dp Tx Link Maintance
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxGetIRQTypeProc(void)
{
    // Short HPD IRQ
    if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x00, 6, pData) == _TRUE)
    {
        if(((GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() == 1) && ((pData[2] & 0x07) != 0x07)) ||
           ((GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() == 2) && ((pData[2] & 0x77) != 0x77)) ||
           ((GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() == 4) && (((pData[2] & 0x77) != 0x77) || ((pData[3] & 0x77) != 0x77))) ||
           ((GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() != 1) && ((pData[4] & 0x01) != 0x01)))
        {
            SET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
        }

        if((pData[1] & _BIT2) == _BIT2)
        {
            SET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_CP_IRQ);
        }

        if((pData[1] & _BIT1) == _BIT1)
        {
            SET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST);
        }

        if((pData[4] & _BIT6) == _BIT6)
        {
            SET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_DOWNSTREAM_PORT_STATUS_CHANGE);
        }
    }

    if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
    {
        // Get IRQ Event Status Indicator
        if(ScalerDpAuxTxNativeRead(0x00, 0x20, 0x03, 3, pData) == _TRUE)
        {
            SET_DP_TX_IRQ_HPD_DETECTED();

            if((pData[0] & _BIT1) == _BIT1)
            {
                SET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST);
            }

            if((pData[0] & _BIT2) == _BIT2)
            {
                SET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_CP_IRQ);
            }

            if((pData[0] & _BIT3) == _BIT3)
            {
                SET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_MCCS_IRQ);
            }

            if(((pData[0] & _BIT4) == _BIT4) && (GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ) == 0x00))
            {
                SET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ);
            }

            if(((pData[0] & _BIT5) == _BIT5) && (GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ) == 0x00))
            {
                SET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ);
            }

            if((pData[2] & _BIT0) == _BIT0)
            {
                SET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ);
            }

            if((pData[2] & _BIT1) == _BIT1)
            {
                SET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
            }

            if((pData[2] & _BIT2) == _BIT2)
            {
                SET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ);
            }
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Dp Tx Link Maintance
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxIRQEventCheck(void)
{
    BYTE pucData[6] = {0};

#if((_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON) && (_PX_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    // Tx Get IRQ Type
    ScalerDpMacTxGetIRQTypeProc();
#endif

    if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
    {
        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
        {
            pucData[0] |= _BIT0;
        }

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
        {
            pucData[0] |= _BIT1;

            // Get Link Status
            ScalerDpAuxTxNativeRead(0x00, 0x20, 0x0C, 3, &pucData[1]);

            switch(GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM())
            {
                case _DP_ONE_LANE:
                    if((pucData[1] & 0x07) == 0x07)
                    {
                        CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
                    }
                    break;

                case _DP_TWO_LANE:
                    if(((pucData[1] & 0x77) == 0x77) && ((pucData[3] & 0x01) == 0x01))
                    {
                        CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
                    }
                    break;

                case _DP_FOUR_LANE:
                    if(((pucData[1] & 0x77) == 0x77) && ((pucData[2] & 0x77) == 0x77) && ((pucData[3] & 0x01) == 0x01))
                    {
                        CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
                    }
                    break;

                default:
                    break;
            }
        }

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ)
        {
            pucData[0] |= _BIT2;

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
            {
                CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ);
            }
        }

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_DOWNSTREAM_PORT_STATUS_CHANGE) == _DP_TX_IRQ_HPD_DOWNSTREAM_PORT_STATUS_CHANGE)
        {
            if(GET_DP_MAC_TX_DOWNSTREAM_INFO_READY() == _TRUE)
            {
                // Read DownStream Sink Count
                ScalerDpAuxTxNativeRead(0x00, 0x02, 0x00, 1, &pucData[1]);

                SET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT(pucData[1] & 0xBF);
            }

            CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_DOWNSTREAM_PORT_STATUS_CHANGE);
        }

        // CLR Rx_Cap_IRQ and Link_Status_CHG_IRQ and Stream_Status_CHG_IRQ
        if(pucData[0] != 0x00)
        {
            ScalerDpAuxTxNativeWrite(0x00, 0x20, 0x05, 1, pucData);
        }

        pucData[0] = 0x00;

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_CP_IRQ) == _DP_TX_IRQ_HPD_CP_IRQ)
        {
            pucData[0] |= _BIT2;

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
            {
                CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_CP_IRQ);
            }
            else
            {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if((ScalerDpHdcp2TxGetHdcpMode() == _ENABLE) && (GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE))
                {
                    // Read HDCP2 B Status
                    if(ScalerDpAuxTxNativeRead(0x06, 0x94, 0x93, 1, &pucData[1]) == _TRUE)
                    {
                        SET_DP_HDCP2_TX_IRQ_TYPE(pucData[1]);
                    }
                }
                else
#endif
                {
                    // Read HDCP B Status
                    if(ScalerDpAuxTxNativeRead(0x06, 0x80, 0x29, 1, &pucData[1]) == _TRUE)
                    {
                        SET_DP_TX_IRQ_HDCP_TYPE(pucData[1]);
                    }
                }
            }
        }

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_MCCS_IRQ) == _DP_TX_IRQ_HPD_MCCS_IRQ)
        {
            pucData[0] |= _BIT3;
        }
    }
    else
    {
        // CLR CP IRQ
        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_CP_IRQ) == _DP_TX_IRQ_HPD_CP_IRQ)
        {
            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
            {
                CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_CP_IRQ);
            }
            else
            {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if(ScalerDpHdcp2TxGetHdcpMode() == _ENABLE)
                {
                    // Read HDCP2 B Status
                    if(ScalerDpAuxTxNativeRead(0x06, 0x94, 0x93, 1, &pucData[1]) == _TRUE)
                    {
                        SET_DP_HDCP2_TX_IRQ_TYPE(pucData[1]);
                    }
                }
                else
#endif
                {
                    // Read HDCP B Status
                    if(ScalerDpAuxTxNativeRead(0x06, 0x80, 0x29, 1, &pucData[1]) == _TRUE)
                    {
                        SET_DP_TX_IRQ_HDCP_TYPE(pucData[1]);
                    }
                }
            }

            pucData[0] |= _BIT2;
        }
    }

    if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST) == _DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST)
    {
        CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST);

        pucData[0] |= _BIT1;

        // Read CTS Test Request Type
        if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x18, 1, &pucData[1]) == _TRUE)
        {
            SET_DP_TX_CTS_TEST_REQUEST_TYPE(pucData[1]);
        }

        // Support TEST_LINK_TRAINING
        if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING)
        {
            pucData[1] = _TEST_ACK;
        }
        else
        {
            // For PHY CTS test
            if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_PHY_TEST_PATTERN) != _DP_TX_CTS_PHY_TEST_PATTERN)
            {
                pucData[1] = _TEST_NAK;

                CLR_DP_TX_CTS_TEST_REQUEST_TYPE();
            }
        }

        // For PHY CTS test
        if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_PHY_TEST_PATTERN) != _DP_TX_CTS_PHY_TEST_PATTERN)
        {
            // Write TEST Response
            ScalerDpAuxTxNativeWrite(0x00, 0x02, 0x60, 1, &pucData[1]);
        }

        // Write TEST Response
        ScalerDpAuxTxNativeWrite(0x00, 0x02, 0x60, 1, &pucData[1]);
    }

    if(pucData[0] != 0x00)
    {
        if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
        {
            // CLR CP_IRQ and MCCS_IRQ
            ScalerDpAuxTxNativeWrite(0x00, 0x20, 0x03, 1, pucData);
        }

        // CLR CP_IRQ and AUTOMATED_TEST_REQUEST
        ScalerDpAuxTxNativeWrite(0x00, 0x02, 0x01, 1, pucData);
    }

#if(_DP_MST_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_4)
    {
        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_DSC_ERROR_STATUS_IRQ) == _DP_TX_IRQ_HPD_DSC_ERROR_STATUS_IRQ)
        {
            pucData[4] = _BIT4;

            // CLR DSC_IRQ
            ScalerDpAuxTxNativeWrite(0x00, 0x20, 0x04, 1, &pucData[4]);

            if(ScalerDpAuxTxNativeRead(0x00, 0x20, 0x11, 1, &pucData[5]) == _TRUE)
            {
                if(GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_LINK_ON)
                {
                    if(ScalerDpRxGetSrcMstUpRequestEnable(GET_DP_RX_MAIN_PORT()) == _TRUE)
                    {
                        if((pucData[5] & _BIT0) == _BIT0)
                        {
                            SET_DP_MST_TX_SINK_EVENT_ID(_SINK_EVENT_ID_DSC_RC_BUF_UNDERRUN);
                        }

                        if((pucData[5] & _BIT1) == _BIT1)
                        {
                            SET_DP_MST_TX_SINK_EVENT_ID(_SINK_EVENT_ID_DSC_RC_BUF_OVERFLOW);
                        }

                        if((pucData[5] & _BIT2) == _BIT2)
                        {
                            SET_DP_MST_TX_SINK_EVENT_ID(_SINK_EVENT_ID_DSC_CHUNCK_LEN_ERROR);
                        }
                    }
                }

                // CLR DSC Status
                ScalerDpAuxTxNativeWrite(0x00, 0x02, 0x0F, 1, &pucData[5]);
            }
        }
    }

    if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_CEC_IRQ) == _DP_TX_IRQ_HPD_CEC_IRQ)
    {
        if(ScalerDpAuxRxGetDpcdBitInfo(GET_DP_RX_MAIN_PORT(), 0x00, 0x01, 0x11, _BIT1) == _BIT1)
        {
            SET_DP_MST_TX_SINK_EVENT_ID(_SINK_EVENT_ID_CEC_IRQ);
        }

        pucData[0] = _BIT2;

        ScalerDpAuxTxNativeWrite(0x00, 0x20, 0x04, 1, pucData);
    }
#endif
}

//--------------------------------------------------
// Description  : Dp Tx Read DPCD Rx Capability
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpMacTxLinkConfigInitial(void)
{
#if(_DP_TX_HPD_HIGH_DEBOUNCE_SUPPORT == _ON)
    if(GET_DP_TX_HPD_DEBOUNCE() == _FALSE)
    {
        return _FALSE;
    }
#endif

    if(ScalerDpMacTxGetLttprInitialMode() != _DP_TX_LTTPR_NON_LTTPR_MODE)
    {
        if(ScalerDpMacTxDfpLTTPRInitial() == _FALSE)
        {
            DebugMessageDpTx("Read DFP LTTPR Failure", 0);

            return _FALSE;
        }
    }

    if(ScalerDpMacTxDfpDeviceWakeUpInitial() == _FALSE)
    {
        DebugMessageDpTx("Wake Up DFP Device Failure", 0);

        return _FALSE;
    }

    if(ScalerDpMacTxSetSourceOui() == _FALSE)
    {
        DebugMessageDpTx("Write Oui Failure", 0);
    }

    if(ScalerDpMacTxDfpDeviceCapChangeCheck() == _FALSE)
    {
        DebugMessageDpTx("Get Cap Change Check Failure", 0);

        return _FALSE;
    }

    ScalerDpMacTxDfpDeviceBasicCapSetting();

    if(ScalerDpMacTxGetDfpDeviceSinkCountProc() == _FALSE)
    {
        DebugMessageDpTx("Get Sink Count Proc Failure", 0);

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx Dfp LTTPR Initial
// Input Value  :
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxDfpLTTPRInitial(void)
{
    BYTE ucTemp = 0;
    BYTE pucData[1];

    ScalerDpAuxTxSetTimeout(_AUX_TIMEOUT_3200US);

    // Read LTTPR Field 0xF0000 ~ 0xF0007
    if(ScalerDpAuxTxNativeRead(0x0F, 0x00, 0x00, 8, g_pucDpMacTxDfpLTTPRCap) == _FALSE)
    {
        // Aux Failure
        return _FALSE;
    }

    // Set LTTPR Num
    if(g_pucDpMacTxDfpLTTPRCap[2] == 0x00)
    {
        SET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM(0);
        ScalerDpAuxTxSetTimeout(_AUX_TIMEOUT_400US);
    }
    else
    {
        for(ucTemp = 0; ucTemp < 8; ucTemp++)
        {
            if((g_pucDpMacTxDfpLTTPRCap[2] >> ucTemp) == 0x01)
            {
                SET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM(8 - ucTemp);
                break;
            }
        }
    }

    // Set PS Wakeup Timeout
    if(GET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM() > 0)
    {
        // LTTPR Mode: Set Sink Ext Wake Timeout (DPCD 2211h)
        if((g_pucDpMacTxDfpLTTPRCap[3] == 0x55) || (g_pucDpMacTxDfpLTTPRCap[3] == 0xAA))
        {
            if(ScalerDpAuxTxNativeRead(0x00, 0x01, 0x19, 1, pData) == _FALSE)
            {
                return _FALSE;
            }
            else
            {
                if((pData[0] & _BIT0) == _BIT0)
                {
                    if(ScalerDpAuxTxNativeRead(0x00, 0x22, 0x11, 1, pucData) == _FALSE)
                    {
                        return _FALSE;
                    }
                    else
                    {
                        if((pucData[0] > 0x00) && (pucData[0] <= 0x05))
                        {
                            SET_DP_MAC_TX_DOWNSTREAM_SINK_EXT_WAKE_TIMEOUT(pucData[0] * 20);
                        }
                        else
                        {
                            SET_DP_MAC_TX_DOWNSTREAM_SINK_EXT_WAKE_TIMEOUT(1);
                        }
                    }
                }
                else
                {
                    SET_DP_MAC_TX_DOWNSTREAM_SINK_EXT_WAKE_TIMEOUT(0);
                }
            }
        }

        // Lttpr Non-Transparent Mode: Set LTTPR EXT Wake Timeout (DPCD F0005h)
        if(g_pucDpMacTxDfpLTTPRCap[3] == 0xAA)
        {
            if((g_pucDpMacTxDfpLTTPRCap[5] & _BIT7) == _BIT7)
            {
                SET_DP_MAC_TX_DOWNSTREAM_LTTPR_EXT_WAKE_TIMEOUT((g_pucDpMacTxDfpLTTPRCap[5] & 0x7F) * 10);
            }
            else
            {
                SET_DP_MAC_TX_DOWNSTREAM_LTTPR_EXT_WAKE_TIMEOUT(0);
            }
        }
        else
        {
            SET_DP_MAC_TX_DOWNSTREAM_LTTPR_EXT_WAKE_TIMEOUT(0);
        }
    }
    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx Dfp Device Wake Up Initial
// Input Value  :
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxDfpDeviceWakeUpInitial(void)
{
    BYTE ucPowerInfo = 0;

    // 1. Set Power Normal Status
    ucPowerInfo |= _BIT0;

    if(ScalerDpMacTxGetLttprInitialMode() != _DP_TX_LTTPR_NON_LTTPR_MODE)
    {
        if(ScalerDpAuxTxNativeWrite(0x00, 0x06, 0x00, 1, &ucPowerInfo) == _FALSE)
        {
            // Aux Failure
            return _FALSE;
        }

        // 2. Wait Sink Wake Up
        ScalerDpMacTxLTTPRExtWakeTimeOut();
    }
    else
    {
        ScalerDpAuxTxSetTimeout(_AUX_TIMEOUT_3200US);

        // For LLCTS 4.2.1.1 First CMD TO 3.2ms
        SET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM(8);

        if(ScalerDpAuxTxNativeWrite(0x00, 0x06, 0x00, 1, &ucPowerInfo) == _FALSE)
        {
            // Set Aux TO 400us
            SET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM(0);

            // Aux Failure
            return _FALSE;
        }

        ScalerDpAuxTxSetTimeout(_AUX_TIMEOUT_400US);

        // Set Aux TO 400us
        SET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM(0);

        // Wait Sink Wake Up
        ScalerTimerDelayXms(25);
    }

    // 3. Read Sink Power Status
    if(ScalerDpAuxTxNativeRead(0x00, 0x06, 0x00, 1, pData) == _TRUE)
    {
        // Check Sink DPCD Power Info in Power Normal
        if((pData[0] & (_BIT2 | _BIT1 | _BIT0)) != ucPowerInfo)
        {
            // Aux Failure
            return _FALSE;
        }
    }
    else
    {
        // Aux Failure
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx LTTPR EXTENDED WAKE TIMEOUT
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxLTTPRExtWakeTimeOut(void)
{
    WORD usToltalWakeTimeout = 0;
    WORD usToltalWakeTimeoutMax = 0;

    usToltalWakeTimeout = GET_DP_MAC_TX_DOWNSTREAM_SINK_EXT_WAKE_TIMEOUT() + GET_DP_MAC_TX_DOWNSTREAM_LTTPR_EXT_WAKE_TIMEOUT();
    usToltalWakeTimeoutMax = 100 + 50 * GET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM();

    if(usToltalWakeTimeout <= 25)
    {
        ScalerTimerDelayXms(25);
    }
    else
    {
        if(usToltalWakeTimeout >= usToltalWakeTimeoutMax)
        {
            usToltalWakeTimeout = usToltalWakeTimeoutMax;
        }

        ScalerTimerDelayXms(usToltalWakeTimeout);
        // ScalerTimerActiveTimerEvent(usToltalWakeTimeout, _SCALER_TIMER_EVENT_DP_TX_DFP_WAKEUP);
    }
}

//--------------------------------------------------
// Description  : Write Dp Tx OUI to DFP Device
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxSetSourceOui(void)
{
    bit bAuxNormal = _TRUE;
    BYTE pucSourceOui[3];

    pucSourceOui[0] = 0x00;
    pucSourceOui[1] = 0xE0;
    pucSourceOui[2] = 0x4C;

    if(ScalerDpAuxTxNativeWrite(0x00, 0x03, 0x00, 3, pucSourceOui) == _FALSE)
    {
        // Aux Failure
        bAuxNormal = _FALSE;
    }

    return bAuxNormal;
}

//--------------------------------------------------
// Description  : Compare Previous Dfp Device Cap Processs
// Input Value  :
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxDfpDeviceCapChangeCheck(void)
{
    BYTE pucBasicCapInfo[16] = {0};
    BYTE pucExtenFieldCapInfo[16] = {0};

    CLR_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();

    if(ScalerDpAuxTxNativeRead(0x00, 0x00, 0x00, 16, pucBasicCapInfo) == _TRUE)
    {
        if((pucBasicCapInfo[14] & _BIT7) == _BIT7)
        {
            if(ScalerDpMacTxGetDfpDeviceExtendCapProc(pucExtenFieldCapInfo) == _FALSE)
            {
                // Extend Filed Capability Replaced by Basic Field Cap
                memcpy(g_pucDpMacTxPreviousDfpDeviceExtendCap, pucBasicCapInfo, 16);
            }
        }

        // Compare Previous DFP Device Capability
        if(memcmp(g_pucDpMacTxPreviousDfpDeviceCap, pucBasicCapInfo, 16) != 0)
        {
            SET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();

            // Update Previous Dfp Device Basic & Extend Cap
            memcpy(g_pucDpMacTxPreviousDfpDeviceCap, pucBasicCapInfo, 16);
        }

        if((pucBasicCapInfo[14] & _BIT7) == _BIT7)
        {
            if(memcmp(g_pucDpMacTxPreviousDfpDeviceExtendCap, pucExtenFieldCapInfo, 16) != 0)
            {
                SET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();

                memcpy(g_pucDpMacTxPreviousDfpDeviceExtendCap, pucExtenFieldCapInfo, 16);
            }

            // Choose to Use Extend Field Cap
            g_pucDpMacTxDownStreamCapTable = g_pucDpMacTxPreviousDfpDeviceExtendCap;
        }
        else
        {
            // Choose to Use Basic Field Cap
            g_pucDpMacTxDownStreamCapTable = g_pucDpMacTxPreviousDfpDeviceCap;
        }
    }
    else
    {
        return _FALSE;
    }

#if(_DP_MST_SUPPORT == _ON)

    // Check DownStream Mst Capability Info
    if(ScalerDpMacTxGetDfpDeviceMstCapProc() == _FALSE)
    {
        DebugMessageDpTx("7. Check Mst Fail", 0);
        return _FALSE;
    }

    // Check If MSG Has Reported Tx Unplug (e.g. Link Address During HPD Debounce)
    if(ScalerDpMstTxGetOutputPortStatusReported() == _CONNECT_STATUS_UNPLUG)
    {
        SET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();
    }

    // Check Tx Received MSG During HPD Debounce
    if(GET_DP_MST_TX_MSG_DURING_HPD_LOW_DEBOUNCE() == _TRUE)
    {
        SET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();
    }
#endif

#if(_DP_TX_FEC_SUPPORT == _ON)

    // Check DownStream Fec Capability Info
    if(ScalerDpMacTxGetDfpDeviceFecCapProc() == _FALSE)
    {
        DebugMessageDpTx("7. Check Fec Fail", 0);
        return _FALSE;
    }

#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    // Check DownStream DSC Capability Info
    if(ScalerDpMacTxGetDfpDeviceDscCapProc() == _FALSE)
    {
        DebugMessageDpTx("7. Check Dsc Fail", 0);
        return _FALSE;
    }
#endif

    // Check DownStream Extend Sdp Capability Info
    if(ScalerDpMacTxGetDfpDeviceExtendReceiverCapProc() == _FALSE)
    {
        DebugMessageDpTx("7. Check Extend Receiver Cap Fail", 0);
        return _FALSE;
    }

    // Check DownStream Detaile Capability Info for CTS 4.2.2.7
    if(ScalerDpAuxTxNativeRead(0x00, 0x00, 0x80, 16, pData) == _FALSE)
    {
        DebugMessageDpTx("7. Check Detail Cap Fail", 0);
        return _FALSE;
    }

#if(_DFP_SINK_EDID_CHANGE_CHECK_METHOD == _EDID_SHA_CODE)

    // Check DownStream EDID Change Process
    if(ScalerDpMacTxDfpDeviceEdidChangeCheck() == _FALSE)
    {
        DebugMessageDpTx("7. Check EDID Fail", 0);
    }

#else

    // Check DownStream EDID Change Process
    if(ScalerDpMacTxGetDfpDeviceReadEdid() == _FALSE)
    {
        DebugMessageDpTx("7. Check EDID Fail", 0);
    }

#endif

    ScalerDpMacTxDownStreamEdidCheckSpecialVendor();

    ScalerDpMacTxDownStreamEdidBwSetting();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx Read DFP Device Capability
// Input Value  :
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
void ScalerDpMacTxDfpDeviceBasicCapSetting(void)
{
    ScalerDpMacTxDfpDeviceVersionProc();

    ScalerDpMacTxGetDfpDeviceLinkBandwidth();

    ScalerDpMacTxGetDfpDeviceDownSpreadStatus();

    ScalerDpMacTxGetDfpDeviceMsaIgnored();

    ScalerDpMacTxGetDfpDeviceYcbcr420Support();

    ScalerDpHdcp14TxCheckDownstreamCapability();

#if(_DP_HDCP2_RX_SUPPORT == _ON)
    ScalerDpHdcp2TxCheckCapability();
#endif
}

//--------------------------------------------------
// Description  : DP Tx Get Dfp Device Sink Count Process
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxGetDfpDeviceSinkCountProc(void)
{
    BYTE ucDfpDeviceSinkCountInfo = 0;

    if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x00, 1, &ucDfpDeviceSinkCountInfo) == _TRUE)
    {
        SET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT(ucDfpDeviceSinkCountInfo & 0xBF);
    }
    else
    {
        return _FALSE;
    }

    return _TRUE;
}

#if(_DFP_SINK_EDID_CHANGE_CHECK_METHOD == _EDID_SHA_CODE)
//--------------------------------------------------
// Description  : Dfp device edid change check
// Input Value  :
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpMacTxDfpDeviceEdidChangeCheck(void)
{
    BYTE pucEdid[128];
    BYTE pucShaValue[_DP_TX_EDID_SHA1_VALUE_SIZE_MAX] = {0};
    BYTE ucEdidBlock = 0;
    BYTE ucEdidBlockCnt = 0;

    // Initial Sha1 Circuit
    ScalerDpMacTxSha1CircuitReset();

    do
    {
        memset(pucEdid, 0, sizeof(pucEdid));

        // Read Edid From Downsream Device
        if(ScalerDpMacTxReadDfpDeviceEdidOneBlock(pucEdid, ucEdidBlock) == _FALSE)
        {
            return _FALSE;
        }

        if(ucEdidBlock == 0)
        {
            ucEdidBlockCnt = pucEdid[0x7E] + 1;
        }

        ucEdidBlock++;

        // Import to Sha1 Circuit Calculate Sha1 Code
        ScalerDpMacTxSha1DataInput(pucEdid, 128, (ucEdidBlock == ucEdidBlockCnt) ? _FALSE : _TRUE);
    }
    while(ucEdidBlock < ucEdidBlockCnt);

    if(ucEdidBlockCnt >= 1)
    {
        ScalerDpMacTxReadOutShaCode(pucShaValue, _DP_TX_EDID_SHA1_VALUE_SIZE_MAX);
    }

    if(memcmp(g_pucDpMacTxPreviousDfpDeviceEdidSha1, pucShaValue, _DP_TX_EDID_SHA1_VALUE_SIZE_MAX) != 0)
    {
        // Backup Downstrean Device Sha Value
        memcpy(g_pucDpMacTxPreviousDfpDeviceEdidSha1, pucShaValue, _DP_TX_EDID_SHA1_VALUE_SIZE_MAX);

        // DFP Device Capability Change
        SET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();

        DebugMessageDpTx("Sink Edid changed:", 1);
    }

    return _TRUE;
}


//--------------------------------------------------
// Description  : Read Downstream port Edid Block
// Input Value  : pucEdid  --> Recived EDID Contect Buffer Pointer
//                ucBlockIndex --> Read EDID Data Block Index
// Output Value : True or False
//--------------------------------------------------
bit ScalerDpMacTxReadDfpDeviceEdidOneBlock(BYTE *pucEdid, BYTE ucBlockIndex)
{
    BYTE ucEdidSegment = 0;
    BYTE ucIndex = 0;
    BYTE ucEdidOffset = 0;

    ucEdidOffset = ((WORD)128 * ucBlockIndex) % 0x100;

    ucEdidSegment = ucBlockIndex / 2;

    if(ucEdidSegment >= 1)
    {
        if(ScalerDpAuxTxI2CoverWrite(0x30, 1, &ucEdidSegment, 1) == _FALSE)
        {
            return _FALSE;
        }
    }

    if(ScalerDpAuxTxI2CoverWrite(0x50, 1, &ucEdidOffset, 1) == _FALSE)
    {
        return _FALSE;
    }

    while(ucIndex < 0x80)
    {
        if(ucIndex == 0x70)
        {
            if(ScalerDpAuxTxI2CoverRead(0x50, 16, &pucEdid[ucIndex], 0) == _FALSE)
            {
                return _FALSE;
            }
        }
        else
        {
            if(ScalerDpAuxTxI2CoverRead(0x50, 16, &pucEdid[ucIndex], 1) == _FALSE)
            {
                return _FALSE;
            }
        }

        ucIndex += 0x10;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Read Out Sha1 Code
// Input Value  : pucShaValue --> Received Sha Value Buffer Pointer
//                ucShaLength --> Sha1 Value Length
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxReadOutShaCode(BYTE *pucShaValue, BYTE ucShaLength)
{
    BYTE ucIndex = 0;

    ucShaLength /= 4;

    do
    {
        // Set Sha-1 Read-out index
        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), (ucShaLength - 1) << 5);

        pucShaValue[ucIndex] = ScalerGetByte(PBB_60_DP_HDCP_TX_SHA_OUT_3);
        pucShaValue[ucIndex + 1] = ScalerGetByte(PBB_61_DP_HDCP_TX_SHA_OUT_2);
        pucShaValue[ucIndex + 2] = ScalerGetByte(PBB_62_DP_HDCP_TX_SHA_OUT_1);
        pucShaValue[ucIndex + 3] = ScalerGetByte(PBB_63_DP_HDCP_TX_SHA_OUT_0);

        ucIndex += 4;
    }while(--ucShaLength > 0);

    /* Retain for Print Sha Value Later In Debug Case
    pData[0] = 0;

    while(pData[0] < 20)
    {
        DebugMessageDpTx("Sha-1 Value:", pucShaValue[pData[0]]);

        pData[0]++;
    }
    */
}

//--------------------------------------------------
// Description  : Dp Tx SHA1 circuit Run
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSha1Run(bit bIsFirst)
{
    // Set First Run For SHA-1 Circuit
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT3 | _BIT0), ((bIsFirst == _TRUE) ? _BIT3 : 0x00));

    // Run SHA-1 Circuit
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT2 | _BIT0), _BIT2);

    ScalerTimerPollingFlagProc(5, PBB_5B_DP_HDCP_TX_SHA_CTRL, _BIT4, _TRUE);

    // Disable First Run and Disable SHA-1 Circuit
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT3 | _BIT2 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : Reset Sha circuit
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSha1CircuitReset(void)
{
    // Reset SHA Block counter
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT1 | _BIT0), _BIT1);

    // Start to Write SHA-1 Transform Input
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT1 | _BIT0), 0x00);

    // Clear Total Import Data Length End of One Sha Value Calculation
    SET_DP_TX_EDID_SHA1_TOTAL_COUNT(0);

    // Set Firt Import Data Flag End of One Sha Value Calculation
    SET_DP_TX_EDID_SHA1_FIRST_FLAG();
}

//--------------------------------------------------
// Description  : Import Raw Data into Sha circuit
// Input Value  : pucDataIn       --> Import Data
//                usDataInLength  --> Import Data Length, Request "usDataInLength" is Multiple of 4
//                bMOT            --> Middle Of Import Data Array Flag
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSha1DataInput(BYTE *pucDataIn, WORD usDataInLength, bit bMOT)
{
    BYTE pucDataTmep[_DP_SHA1_INPUT_SIZE];
    WORD usIndex = 0;
    WORD usDivBlockLenMax = 0;
    WORD usDivBlockLen = 0;
    WORD usSha1DbLength = _DP_SHA1_INPUT_SIZE;

    if(usDataInLength == 0)
    {
        return;
    }

    if(bMOT == _FALSE)
    {
        // +8 for 8 Byte Data Length (2^64 length)
        usDivBlockLenMax = ((usDataInLength + 8) / usSha1DbLength) + ((((usDataInLength + 8) % usSha1DbLength) == 0) ? 0 : 1);
    }
    else
    {
        usDivBlockLenMax = (usDataInLength / usSha1DbLength);
    }

    // Accumulacate Continuous Import Data Count
    SET_DP_TX_EDID_SHA1_TOTAL_COUNT(GET_DP_TX_EDID_SHA1_TOTAL_COUNT() + usDataInLength);

    /* Retain for Print Info Later In Debug Case
    DebugMessageDpTx("bMOT :", bMOT);
    DebugMessageDpTx("Total Import Data Length :", GET_DP_TX_EDID_SHA1_TOTAL_COUNT());
    */

    // Write the KSV List into SHA-1 Transform Input
    do
    {
        usIndex = 0;

        memset(pucDataTmep, 0, sizeof(pucDataTmep));

        if(((usDivBlockLen + 1) * usSha1DbLength) > usDataInLength)
        {
            memcpy(pucDataTmep, &pucDataIn[usDivBlockLen * usSha1DbLength], (usDataInLength % usSha1DbLength));

            if(bMOT == _FALSE)
            {
                // Fill end mark
                pucDataTmep[usDataInLength % usSha1DbLength] = 0x80;

                // Fill Sha1 Import Data Length High Byte
                pucDataTmep[62] = HIBYTE(GET_DP_TX_EDID_SHA1_TOTAL_COUNT() * 8);

                // Fill Sha1 Import Data Length Low Byte
                pucDataTmep[63] = LOBYTE(GET_DP_TX_EDID_SHA1_TOTAL_COUNT() * 8);
            }
        }
        else
        {
            memcpy(pucDataTmep, &pucDataIn[usDivBlockLen * usSha1DbLength], sizeof(pucDataTmep));
        }

        do
        {
            /* Retain for Print Info Later In Debug Case
            DebugMessageDpTx("Import Data :", pucDataTmep[usIndex]);
            DebugMessageDpTx("Import Data :", pucDataTmep[usIndex + 1]);
            DebugMessageDpTx("Import Data :", pucDataTmep[usIndex + 2]);
            DebugMessageDpTx("Import Data :", pucDataTmep[usIndex + 3]);
            */

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, pucDataTmep[usIndex]);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, pucDataTmep[usIndex + 1]);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, pucDataTmep[usIndex + 2]);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, pucDataTmep[usIndex + 3]);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usIndex += 4;

            if((usIndex % usSha1DbLength) == 0)
            {
                if(GET_DP_TX_EDID_SHA1_FIRST_FLAG() == _TRUE)
                {
                    // Clear Flag Once Firt Calculation Operation was implemented
                    CLR_DP_TX_EDID_SHA1_FIRST_FLAG();

                    ScalerDpMacTxSha1Run(_TRUE);
                }
                else
                {
                    ScalerDpMacTxSha1Run(_FALSE);
                }
            }
        }
        while((usIndex % usSha1DbLength) != 0x00);

        usDivBlockLen++;
    }while(usDivBlockLen < usDivBlockLenMax);

    if(bMOT == _FALSE)
    {
        // Clear Total Import Data Length End of One Sha Value Calculation
        SET_DP_TX_EDID_SHA1_TOTAL_COUNT(0);

        // Set Firt Import Data Flag End of One Sha Value Calculation
        SET_DP_TX_EDID_SHA1_FIRST_FLAG();
    }
}
#else // Else of #if(_DFP_SINK_EDID_CHANGE_CHECK_METHOD == _EDID_SHA_CODE)

//-------------------------------------------------------------
// Description  : Calculate one block of EDID checksum
// Input Value  : Edid Pointer, Start Address
// Output Value : None
//-------------------------------------------------------------
BYTE ScalerDpMacTxEdidCheckSumCal(BYTE *pucEdid, WORD usStartAddr)
{
    WORD usEDIDIndex = 0x0000;
    BYTE ucEDIDCheckSum = 0x00;

    for(usEDIDIndex = usStartAddr; usEDIDIndex <= (0x7F + usStartAddr); usEDIDIndex++)
    {
        ucEDIDCheckSum += pucEdid[usEDIDIndex];

        if (usEDIDIndex == (0x7E + usStartAddr))
        {
            ucEDIDCheckSum = (0 - ucEDIDCheckSum);

            break;
        }
    }

    return ucEDIDCheckSum;
}

//--------------------------------------------------
// Description  : Modify EDID Extension Block Count
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
void ScalerDpMacTxEdidModifyExtCnt(BYTE *pucEdid)
{
    BYTE ucEdidExt = (_DP_TX_EDID_SIZE_MAX / 128 - 1);

    if(pucEdid[0x7E] > ucEdidExt)
    {
        // Calculate Extension Block Counter
        pucEdid[0x7E] = ucEdidExt;

        // Checksum modify - Base block
        pucEdid[0x7F] = ScalerDpMacTxEdidCheckSumCal(pucEdid, 0x00);
    }
}

//--------------------------------------------------
// Description  : Read Downstream port Edid
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
bit ScalerDpMacTxGetDfpDeviceReadEdid(void)
{
    BYTE ucEdidOffset = 0;
    BYTE ucEdidSegment = 0;
    BYTE ucBlock = 0;
    BYTE ucIndex = 0;
    BYTE pucEDIDTemp[_DP_TX_EDID_SIZE_MAX] = {0};

    while((ucBlock <= pucEDIDTemp[0x7E]) && (ucBlock < (_DP_TX_EDID_SIZE_MAX / 128)))
    {
        ucEdidSegment = ucBlock / 2;

        if(ScalerDpAuxTxI2CoverWrite(0x30, 1, &ucEdidSegment, 1) == _FALSE)
        {
            if(ucEdidSegment > 0)
            {
                break;
            }
        }

        if(ScalerDpAuxTxI2CoverWrite(0x50, 1, &ucEdidOffset, 1) == _FALSE)
        {
            return _FALSE;
        }

        for(ucIndex = 0; ucIndex < 8; ucIndex ++)
        {
            if(ucIndex < 7)
            {
                if(ScalerDpAuxTxI2CoverRead(0x50, 16, &pucEDIDTemp[TO_WORD(ucEdidSegment, ucEdidOffset)], 1) == _FALSE)
                {
                    return _FALSE;
                }
            }
            else
            {
                if(ScalerDpAuxTxI2CoverRead(0x50, 16, &pucEDIDTemp[TO_WORD(ucEdidSegment, ucEdidOffset)], 0) == _FALSE)
                {
                    return _FALSE;
                }
            }

            ucEdidOffset += 16;
        }

        ucBlock ++;
    };

    // Modify Edid Extension Block Count.
    ScalerDpMacTxEdidModifyExtCnt(pucEDIDTemp);

    if(memcmp(g_pucDpMacTxPreviousDfpDeviceEdidBackup, pucEDIDTemp, _DP_TX_EDID_SIZE_MAX) != 0)
    {
        memcpy(g_pucDpMacTxPreviousDfpDeviceEdidBackup, pucEDIDTemp, _DP_TX_EDID_SIZE_MAX);

        // DFP Device Capability Change
        SET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();
    }

    return _TRUE;
}
#endif // End of #if(_DFP_SINK_EDID_CHANGE_CHECK_METHOD == _EDID_SHA_CODE)

#if(_MST_DFP_SINK_EDID_REPORT_SOURCE_METHOD == _BYPASS_RAW_DATA)
//--------------------------------------------------
// Description  : Read Tx Port EDID
// Input Value  : usOffset, ucLength, *pucDataArray
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpMacTxReadDfpDeviceEdid(WORD usOffset, BYTE ucLength, BYTE *pucDataArray)
{
    BYTE ucEdidSegment = 0;
    BYTE ucPrimaryLength = 0;
    BYTE ucRemainLength = 0;
    BYTE ucIndex = 0;
    BYTE ucOffsetTemp = 0;
    BYTE ucTemp = 0;

    /* Retain print message for Debug mode later
    DebugMessageMst("MST Read EDID Offset ", usOffset);
    DebugMessageMst("MST Read EDID ucLength ", ucLength);
    */

    // Read Edid Range Crossing two 0x100 Block
    if(((usOffset / 0x100) + 1) == ((usOffset + ucLength) / 0x100))
    {
        ucPrimaryLength = 0x100 - (usOffset % 0x100);
        ucRemainLength = ucLength - ucPrimaryLength;
    }
    else
    {
        ucPrimaryLength = ucLength;
        ucRemainLength = 0;
    }

    do
    {
        ucEdidSegment = usOffset / 0x100;
        ucOffsetTemp = usOffset % 0x100;

        if(ucEdidSegment >= 1)
        {
            if(ScalerDpAuxTxI2CoverWrite(0x30, 1, &ucEdidSegment, 1) == _FALSE)
            {
                return _FALSE;
            }
        }

        if(ScalerDpAuxTxI2CoverWrite(0x50, 1, &ucOffsetTemp, 1) == _FALSE)
        {
            return _FALSE;
        }

        while(ucIndex < ucPrimaryLength)
        {
            if((ucIndex == 0) && ((usOffset % 16) != 0x00)) // Start Address Not at 16 multiple
            {
                ucTemp = (usOffset % 16);

                if(ScalerDpAuxTxI2CoverRead(0x50, (16 - ucTemp), pucDataArray, (((ucIndex + (16 - ucTemp)) == ucPrimaryLength) ? 0 : 1)) == _FALSE)
                {
                    return _FALSE;
                }

                ucIndex += (16 - ucTemp);
                usOffset += (16 - ucTemp);
            }
            else
            {
                if((ucPrimaryLength - ucIndex) > 16) // 16 multiple page read
                {
                    if(ScalerDpAuxTxI2CoverRead(0x50, 16, (pucDataArray + ucIndex), 1) == _FALSE)
                    {
                        return _FALSE;
                    }

                    usOffset += 16;
                    ucIndex += 16;
                }
                else // Last one read trancation
                {
                    if(ScalerDpAuxTxI2CoverRead(0x50, (ucPrimaryLength - ucIndex), (pucDataArray + ucIndex), 0) == _FALSE)
                    {
                        return _FALSE;
                    }

                    usOffset += (ucPrimaryLength - ucIndex);
                    ucIndex += (ucPrimaryLength - ucIndex);
                }
            }
        }

        if(ucRemainLength != 0) // Change to read next 256 BYTE area
        {
            ucPrimaryLength = ucRemainLength;
            ucRemainLength = 0;

            continue;
        }
    }while(ucRemainLength > 0);

    return _TRUE;
}
#else
//--------------------------------------------------
// Description  : Get Tx Port EDID
// Input Value  : usOffset, ucLength, *pucDataArray
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpMacTxGetDfpDeviceStoredEdid(WORD usOffset, BYTE ucLength, BYTE *pucDataArray)
{
    if((GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG) && ((usOffset + ucLength) <= _DP_TX_EDID_SIZE_MAX))
    {
        memcpy(pucDataArray, &g_pucDpMacTxPreviousDfpDeviceEdidBackup[usOffset], ucLength);

        return _TRUE;
    }

    return _FALSE;
}
#endif // End of #if(_MST_DFP_SINK_EDID_REPORT_SOURCE_METHOD == _BYPASS_RAW_DATA)

//--------------------------------------------------
// Description  : Analysis Tx Edid 420 Capability
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpMacTxEdidAnalysisYcbcr420Capable(void)
{
    bit bEdid420VdbSupport = _FALSE;
    bit bEdid420CmdbSupport = _FALSE;

#if(_DFP_SINK_EDID_CHANGE_CHECK_METHOD == _EDID_SHA_CODE)
    BYTE ucEdidSegment = 0;
    BYTE ucEdidOffset = 0x84;
#endif

    BYTE pucEdidTemp[2] = {0, 0};
    BYTE ucEdidAddr7E = 0;
    BYTE ucEdidAddr82 = 0;
    WORD usAddrSum = 0x84;

#if(_DFP_SINK_EDID_CHANGE_CHECK_METHOD == _EDID_RAW_DATA)

    BYTE *pucEdidBuffer = g_pucDpMacTxPreviousDfpDeviceEdidBackup;

    ucEdidAddr7E = pucEdidBuffer[0x7E];
    ucEdidAddr82 = pucEdidBuffer[0x82];

#else

    ucEdidOffset = 0x7E;

    if(ScalerDpAuxTxI2CoverWrite(0x50, 1, &ucEdidOffset, 1) == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpAuxTxI2CoverRead(0x50, 1, &ucEdidAddr7E, 0) == _FALSE)
    {
        return _FALSE;
    }

    if(ucEdidAddr7E >= 0x01)
    {
        ucEdidOffset = 0x82;

        if(ScalerDpAuxTxI2CoverWrite(0x50, 1, &ucEdidOffset, 1) == _FALSE)
        {
            return _FALSE;
        }

        if(ScalerDpAuxTxI2CoverRead(0x50, 1, &ucEdidAddr82, 0) == _FALSE)
        {
            return _FALSE;
        }
    }

#endif


    if(ucEdidAddr7E >= 0x01)
    {
        do
        {
#if(_DFP_SINK_EDID_CHANGE_CHECK_METHOD == _EDID_RAW_DATA)

            pucEdidTemp[0] = pucEdidBuffer[usAddrSum];
            pucEdidTemp[1] = pucEdidBuffer[usAddrSum + 1];

#else

            ucEdidSegment = usAddrSum / 0x100;

            if(ucEdidSegment >= 1)
            {
                if(ScalerDpAuxTxI2CoverWrite(0x30, 1, &ucEdidSegment, 1) == _FALSE)
                {
                    return _FALSE;
                }
            }

            ucEdidOffset = usAddrSum % 0x100;
            if(ScalerDpAuxTxI2CoverWrite(0x50, 1, &ucEdidOffset, 1) == _FALSE)
            {
                return _FALSE;
            }

            if(ScalerDpAuxTxI2CoverRead(0x50, 2, pucEdidTemp, 0) == _FALSE)
            {
                return _FALSE;
            }

#endif

            // Check [EDID_420_VIDEO_DATA_BLOCK] 0xEX 0x0E OO OO OO.......
            // CTA-861-G Page_100
            if(((pucEdidTemp[0] & 0xE0) == 0xE0) &&
               (pucEdidTemp[1] == 0x0E))
            {
                bEdid420VdbSupport = _TRUE;

                break;
            }

            // Check [EDID_420_CAPABILITY_MAPPING_DATA_BLOCK] 0xEX 0x0F OO OO OO.......
            // CTA-861-G Page_112
            if(((pucEdidTemp[0] & 0xE0) == 0xE0) &&
               (pucEdidTemp[1] == 0x0F))
            {
                bEdid420CmdbSupport = _TRUE;

                break;
            }

            usAddrSum += ((pucEdidTemp[0] & 0x1F) + 1); // Data Length
        }while((usAddrSum < (ucEdidAddr82 + 0x80)) && (usAddrSum < ((ucEdidAddr7E + 1) * 128)));
    }

    if((bEdid420VdbSupport == _TRUE) || (bEdid420CmdbSupport == _TRUE))
    {
        DebugMessageDpTx("Dfp Sink Edid Support 420 Feature", 1);

        return _TRUE;
    }

    DebugMessageDpTx("Dfp Sink Edid Not Support 420 Feature", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DFP Device Extend Field Capability
// Input Value  : Record Extern Cap Array
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxGetDfpDeviceExtendCapProc(BYTE *pucExtenFieldCapInfo)
{
    BYTE ucRetryIndex = 0;
    bit bGetExtenFieldCapStatus = _FALSE;

    for(ucRetryIndex = 0; ucRetryIndex < 2; ucRetryIndex++)
    {
        if(ScalerDpAuxTxNativeRead(0x00, 0x22, 0x00, 16, pucExtenFieldCapInfo) == _TRUE)
        {
            if(pucExtenFieldCapInfo[0] != 0x00)
            {
                bGetExtenFieldCapStatus = _TRUE;

                return bGetExtenFieldCapStatus;
            }
        }
        else
        {
            return bGetExtenFieldCapStatus;
        }

        // Retry Interval
        ScalerTimerDelayXms(2);
    }

    return bGetExtenFieldCapStatus;
}

//--------------------------------------------------
// Description  : DP Tx Get Dfp DSC Cap
// Input Value  : None
// Output Value : bit
//--------------------------------------------------
bit ScalerDpMacTxGetDfpDeviceDscCap(void)
{
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    return GET_DP_TX_DOWNSTREAM_DSC_SUPPORT();
#else
    return _FALSE;
#endif
}

//--------------------------------------------------
// Description  : DP Tx Get Link Channel Coding Type
// Input Value  : None
// Output Value : EnumDpLinkChannelCodingType
//--------------------------------------------------
EnumDpLinkChannelCodingType ScalerDpMacTxGetChannelCodingType(void)
{
    return GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE();
}

//--------------------------------------------------
// Description  : Mst Tx Get Send Act flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacTxGetSendActFlag(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return (bit)ScalerGetBit(P2B_D1_ACT, _BIT0);
    }
    else
#endif
    {
        return (bit)ScalerGetBit(PA_05_DAISY_CTRL_0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : Mst Tx Clear Send Act flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxClearSendActFlag(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerSetBit(P2B_D1_ACT, ~(_BIT1 | _BIT0), _BIT0);
    }
    else
#endif
    {
        ScalerSetBit(PA_05_DAISY_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }
}

//--------------------------------------------------
// Description  : Mst Tx set Send Act enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxEnableSendAct(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxClearSendActFlag();
        ScalerSetBit(P2B_D1_ACT, ~(_BIT1 | _BIT0), _BIT1);
    }
    else
#endif
    {
        ScalerDpMacTxClearSendActFlag();
        ScalerSetBit(PA_05_DAISY_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
        if(GET_DP_MAC_TX_REG_SEND_ACT_FLAG() == _FALSE)
        {
            DELAY_XUS(485); /*1024 MTPH * 64 MTP * 1.2 margin / 162M Link Rate*/
            ScalerSetBit(PA_05_DAISY_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx CTS Fifo Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxCtsFifoReset(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerSetBit(P2B_EB_DPTX_CTSFIFO_CTRL, ~(_BIT2 | _BIT0), _BIT2);
        ScalerSetBit(P2B_EB_DPTX_CTSFIFO_CTRL, ~(_BIT2 | _BIT0), 0x00);
    }
    else
#endif
    {
        ScalerSetBit(PBB_D7_DPTX_CTSFIFO_CTRL, ~(_BIT3 | _BIT2 | _BIT0), _BIT2);
        ScalerSetBit(PBB_D7_DPTX_CTSFIFO_CTRL, ~(_BIT3 | _BIT2 | _BIT0), 0x00);
    }
}

#if(_DP_TX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DFP Device Fec Capability
// Input Value  :
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxGetDfpDeviceFecCapProc(void)
{
    BYTE ucFecCapInfo = 0;

    if(g_pucDpMacTxDownStreamCapTable[0] >= _DP_VERSION_1_4)
    {
        if(ScalerDpAuxTxNativeRead(0x00, 0x00, 0x90, 1, &ucFecCapInfo) == _FALSE)
        {
            return _FALSE;
        }

        if((ucFecCapInfo & _BIT0) != g_ucDpMacTxPreviousFecCapStatus)
        {
            // DFP Device Capability Change
            SET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();

            g_ucDpMacTxPreviousFecCapStatus = (ucFecCapInfo & _BIT0);
        }

        if((ucFecCapInfo & _BIT0) == _BIT0)
        {
            SET_DP_TX_DOWNSTREAM_FEC_SUPPORT();
        }
        else
        {
            CLR_DP_TX_DOWNSTREAM_FEC_SUPPORT();
        }

        DebugMessageDpTx("DPTX check downstream FEC cap.", GET_DP_TX_DOWNSTREAM_FEC_SUPPORT());
    }
    else
    {
        CLR_DP_TX_DOWNSTREAM_FEC_SUPPORT();

        DebugMessageDpTx("DPTX check downstream FEC cap. < DP1.4", GET_DP_TX_DOWNSTREAM_FEC_SUPPORT());
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Tx FEC Stream Change Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxFecStreamChangeCheck(void)
{
    if((GET_DP_TX_DOWNSTREAM_FEC_SUPPORT() == _TRUE) && (GET_DP_TX_FEC_ENCODE_8B10B() == _ENABLE))
    {
        if(ScalerDpMacTxFecSetting(_DISABLE) == _SUCCESS)
        {
            DebugMessageDpTx("DPTX downstream FEC setting PASS_MST/SST Switch Case", 0);
        }
        else
        {
            DebugMessageDpTx("DPTX downstream FEC setting Fail_MST/SST Switch Case", 0);
        }
    }
}

//--------------------------------------------------
// Description  : Tx FEC Stream Enable Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxFecStreamEnableCheck(void)
{
    bit bTxFecTargetStatus = _FALSE;

    if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE) || (GET_DP_TX_DOWNSTREAM_FEC_SUPPORT() == _FALSE))
    {
        return;
    }

    if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST) || (GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST))
    {
#if((_DP_SUPPORT == _ON) && (_DP_RX_FEC_SUPPORT == _ON))
        bTxFecTargetStatus = (((ScalerDpAuxRxGetFecStatus(GET_DP_RX_MAIN_PORT()) == _TRUE) && (ScalerDpMacDphyRxFecDecodeCheck(GET_DP_RX_MAIN_PORT()) == _TRUE)) ? _TRUE : _FALSE);
#endif
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        bTxFecTargetStatus = GET_DP_TX_FEC_CLONE_ENABLE_8B10B();
    }

    if(bTxFecTargetStatus != GET_DP_TX_FEC_ENCODE_8B10B())
    {
        if(ScalerDpMacTxFecSetting(bTxFecTargetStatus) == _SUCCESS)
        {
            DebugMessageDpTx("DPTX Downstream FEC Setting Pass", 0);
        }
        else
        {
            DebugMessageDpTx("DPTX Downstream FEC Setting Fail", 0);
        }
    }
}
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DFP Device VSC SDP Capability
// Input Value  :
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxGetDfpDeviceDscCapProc(void)
{
    BYTE ucDscInfo = 0;

    if(g_pucDpMacTxDownStreamCapTable[0] >= _DP_VERSION_1_4)
    {
        if(ScalerDpAuxTxNativeRead(0x00, 0x00, 0x60, 1, &ucDscInfo) == _FALSE)
        {
            return _FALSE;
        }

        if((ucDscInfo & _BIT0) != g_ucDpMacTxPreviousDscCapStatus)
        {
            // DFP Device Capability Change
            SET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();
            g_ucDpMacTxPreviousDscCapStatus = (ucDscInfo & _BIT0);
        }

        if((ucDscInfo & _BIT0) == _BIT0)
        {
            SET_DP_TX_DOWNSTREAM_DSC_SUPPORT();

            DebugMessageDpTx("Check DP Downstream DSC Cap On", 0x00);
        }
        else
        {
            CLR_DP_TX_DOWNSTREAM_DSC_SUPPORT();

            DebugMessageDpTx("Check DP Downstream DSC Cap Off", 0x00);
        }
    }
    else
    {
        CLR_DP_TX_DOWNSTREAM_DSC_SUPPORT();

        DebugMessageDpTx("Clear DP Downstream DSC Cap", 0x00);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set DP Mac Tx Transmit DSC PPS Packet
// Input Value  : enumDPTxDscPpsPktTransmitMode
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDscPpsPktTransmit(void)
{
    /////////////////////
    // PPS PKT HW Mode //
    /////////////////////

    // PPS transmission: Disable
    ScalerSetBit(PBC_01_SEC_RESERVED_0, ~_BIT0, 0x00);

    // Apply Directly for 1st PPS Tx transmit, Disable PPS in Idle_Pattern
    ScalerSetBit(PBC_3A_SEC_INFO_AVI_DB10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // PPS send position: only V blanking
    ScalerSetBit(PBC_31_SEC_INFO_AVI_DB1, ~_BIT2, _BIT2);

    // CEA, VESA, PPS receive control: Disable
    CLR_DP_TX_SDP_DECODE_TYPE(_DP_TX_SDP_DECODE_META_VESA);
    CLR_DP_TX_SDP_DECODE_TYPE(_DP_TX_SDP_DECODE_META_CEA);
    CLR_DP_TX_SDP_DECODE_TYPE(_DP_TX_SDP_DECODE_PPS);

    // PPS and Meta control: HW mode
    ScalerSetBit(PBC_34_SEC_INFO_AVI_DB4, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Set Header for DSC Stream
    ScalerDpMacTxSdpSetHeaderByte(_SEC_PACKET_TYPE_PPS, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);

    ScalerSetByte(PBC_CF_META_BYPASS_HB1_PPS, 0x10);

    // PPS transmission: Enable
    ScalerSetBit(PBC_01_SEC_RESERVED_0, ~_BIT0, _BIT0);

    // rs dec enable
    ScalerSetBit(PBC_4B_RS_DECODER, ~(_BIT7 | _BIT3 | _BIT2), _BIT7);

    // Decode en db rs-dec falling edge
    ScalerSetBit(PBC_95_DUMMY_95, ~(_BIT7 | _BIT6), 0x00);

    // Enable SP force 1, avoid PPS HW mode lost 8bytes
    ScalerSetBit(PBC_95_DUMMY_95, ~_BIT2, _BIT2);

    // PPS receive control: Enable
    SET_DP_TX_SDP_DECODE_TYPE(_DP_TX_SDP_DECODE_PPS);

    DebugMessageDpTx("[DSC Bypass] DP Tx : Set PPS decode enabled", 0x00);

    if(ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, PBC_96_DUMMY_96, _BIT0, _TRUE) == _FALSE)
    {
        DebugMessageDpTx("[DSC Bypass] DP Tx : PPS decode not enabled...", 0x00);
    }
    else
    {
        DebugMessageDpTx("[DSC Bypass] DP Tx : PPS decode enabled...", ScalerGetByte(PBC_96_DUMMY_96));
    }

    // Turn to Enble DB control for 2nd and more PPS Tx transmit, Disable PPS in Idle_Pattern
    ScalerSetBit(PBC_3A_SEC_INFO_AVI_DB10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // Reset Daisy Chain Async-fifo
    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, _BIT6);
    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : DP Mac Tx DSC Pass-Through Setting
// Input Value  : enumDPTxDscPpsPktTransmitMode
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDscPassThroughSetting(void)
{
    WORD usDscPicWidth = 0;
    WORD usDscSliceWidth = 0;
    BYTE ucDscSliceNum = 0;

    usDscPicWidth = usDscPicWidth;
    usDscSliceWidth = usDscSliceWidth;
    ucDscSliceNum = ucDscSliceNum;

#if(_DSC_DECODER_SUPPORT == _OFF)
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        return;
    }
#endif

    if((GET_DP_TX_DOWNSTREAM_DSC_SUPPORT() == _ENABLE) && (GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH() == _ENABLE))
    {
        DebugMessageDpTx("DP Downstream DSC PassThrough Start !!!", 0x00);

#if(_DSC_DECODER_SUPPORT == _ON)
        if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
        {
            BYTE ucDscMac = ScalerDscDecoderDxInputPortGetDscDecoderMac(ScalerDpMacTxCloneGetCurrentInputPort());

            // Get DSC Picture Width From PPS byte 8/9
            usDscPicWidth = ScalerDscDecoderGetDscPicWidth(ucDscMac);
            // Get DSC Slice Width From PPS byte 12/13
            usDscSliceWidth = ScalerDscDecoderGetDscSliceWidth(ucDscMac);
        }
        else
#endif
        {
#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
            // Get DSC Picture Width
            usDscPicWidth = GET_DP_TX_INPUT_DSC_PIC_WIDTH();
            // Get DSC Slice Width
            usDscSliceWidth = GET_DP_TX_INPUT_DSC_SLICE_WIDTH();
#endif
        }

        // Avoid DSC Slice Width = 0
        usDscSliceWidth = (usDscSliceWidth == 0 ? 1 : usDscSliceWidth);

        // Calculate DSC Slice Num
        ucDscSliceNum = (DWORD)usDscPicWidth * 10UL / usDscSliceWidth;
        ucDscSliceNum = ucDscSliceNum / 10 + ((ucDscSliceNum % 10 > 5) ? 1 : 0);

        // Avoid DSC Slice Num < 0
        ucDscSliceNum = ((ucDscSliceNum == 0) ? 1 : ucDscSliceNum);

        // Check DSC Slice Num
        if(usDscPicWidth != usDscSliceWidth * ucDscSliceNum)
        {
            DebugMessageMst("DSC Pass-Through Slice Num Issue", 0x00);
        }

        DebugMessageMst("usDscPicWidth", usDscPicWidth);
        DebugMessageMst("usDscSliceWidth", usDscSliceWidth);

        // Set DSC Slice Num
        ScalerSetBit(PBB_F2_FEC_TX_SETTING, ~(_BIT6 | _BIT5 | _BIT4), ((ucDscSliceNum - 1) << 4));

        // Set DSC Chunk Size from PPS
        ScalerSetBit(PBB_F2_FEC_TX_SETTING, ~_BIT2, _BIT2);

        // Set DSC PPS Packet Transmit HW Mode
        ScalerDpMacTxDscPpsPktTransmit();

        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        // Enable DSC TU HW Calculate Mode After Setting TU Data Size
        ScalerDpMacTxSetDscTuSizeAuto(_ENABLE);

        // Enable VBID[6] DSC Compression Flag
        ScalerSetBit(PBB_C7_VBID, ~_BIT3, _BIT3);

        // Enable DSC Stream Change Irq
        ScalerDpMacTxDscStreamIrq(_ENABLE);

        // Enable DSC Stream Change Watch Dog
        ScalerDpMacTxDscStreamWD(_ENABLE);

        // Wirte clear DPTx Irq Flag
        ScalerSetBit(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);

        // Set DPTx Irq Enable
        ScalerSetBit(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT7 | _BIT4 | _BIT1 | _BIT0), _BIT7);
    }
    else
    {
        DebugMessageDpTx("DP Downstream DSC PassThrough Off !!!", 0x00);

        // Wirte clear DPTx Irq Flag
        ScalerSetBit(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);

        // Set DPTx Irq Disable
        ScalerSetBit(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT7 | _BIT4 | _BIT1 | _BIT0), 0x00);

        // Disable DSC Stream Change Irq
        ScalerDpMacTxDscStreamIrq(_DISABLE);

        // Disable DSC Stream Change Watch Dog
        ScalerDpMacTxDscStreamWD(_DISABLE);

        // Disable VBID[6] DSC Compression Flag
        ScalerSetBit(PBB_C7_VBID, ~_BIT3, 0x00);

        // Enable DSC TU HW Calculate Mode After Setting TU Data Size
        ScalerDpMacTxSetDscTuSizeAuto(_DISABLE);

        // Disable SP force 1
        ScalerSetBit(PBC_95_DUMMY_95, ~_BIT2, _BIT2);
    }
}

//--------------------------------------------------
// Description  : DP Mac Tx DSC Stream Irq
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDscStreamIrq(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Write Clear The DSC Stream Change Flag
        ScalerSetBit(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT4 | _BIT1 | _BIT0), _BIT4);

        // Enable DSC Stream Change IRQ
        ScalerSetBit(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT6 | _BIT4 | _BIT1 | _BIT0), _BIT6);
    }
    else
    {
        // Disable DSC Stream Change IRQ
        ScalerSetBit(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT6 | _BIT4 | _BIT1 | _BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : DP Mac Tx DSC Stream Watch Dog
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDscStreamWD(bit bEnable)
{
    bit bDscReorderEnable = 0;

    bDscReorderEnable = ((ScalerGetBit(PBB_F1_DSC_FEC_SETTING0, _BIT7) == _BIT7) ? _ENABLE : _DISABLE);

    if(bEnable == _ENABLE)
    {
        // Enable DSC Stream Change WD
        ScalerSetBit(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT5);
    }
    else
    {
        if(bDscReorderEnable == _DISABLE)
        {
            // Switching DSC Stream Change WD Requires Clock
            ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~_BIT7, _BIT7);

            // Disable DSC Stream Change WD
            ScalerSetBit(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

            // Restore Original Value
            ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~_BIT7, 0x00);
        }
        else
        {
            // Disable DSC Stream Change WD
            ScalerSetBit(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : DP Mac Tx DSC Pass-Through Reset
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDscPassThroughReset(void)
{
    DebugMessageDpTx("DP Downstream DSC PassThrough Reset !!!", 0x00);

    // Disable VBID[6] DSC Compression Flag
    ScalerSetBit(PBB_C7_VBID, ~_BIT3, 0x00);

    // Wirte clear DPTx Irq Flag
    ScalerSetBit(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);

    // Set DPTx Irq Disable
    ScalerSetBit(PBB_A3_DPTX_IRQ_CTRL, ~(_BIT7 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // Disable DSC TU HW Calculate Mode After Setting TU Data Size
    ScalerDpMacTxSetDscTuSizeAuto(_DISABLE);

    // Disable DSC Stream Change Irq
    ScalerDpMacTxDscStreamIrq(_DISABLE);

    // Disable DSC Stream Change Watch Dog
    ScalerDpMacTxDscStreamWD(_DISABLE);
}

//--------------------------------------------------
// Description  : DP Mac Tx Get DSC Pass-Through Bit Per Pixel
// Input Value  : None
// Output Value : DSC Bit Per Pixel
//--------------------------------------------------
void ScalerDpMacTxDfpDscEnableProc(bit bEnable)
{
    // Check DFP DSC Enable Status
    if(bEnable == _ENABLE)
    {
        if(ScalerDpAuxTxNativeRead(0x00, 0x01, 0x60, 1, pData) == _TRUE)
        {
            if((pData[0] & _BIT0) != _BIT0)
            {
                pData[0] |= _BIT0;

                // Enable DFP DSC Stream
                ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x60, 1, pData);
            }
        }
    }
    else
    {
        if(ScalerDpAuxTxNativeRead(0x00, 0x01, 0x60, 1, pData) == _TRUE)
        {
            if((pData[0] & _BIT0) == _BIT0)
            {
                pData[0] &= ~_BIT0;

                // Disable DFP DSC Enable
                ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x60, 1, pData);
            }
        }
    }
}

//--------------------------------------------------
// Description  : DP Mac Tx Get DSC Pass-Through Bit Per Pixel
// Input Value  : None
// Output Value : DSC Bit Per Pixel
//--------------------------------------------------
WORD ScalerDpMacTxGetDscPassThroughBpp(void)
{
    WORD usDpTxBitPerPixel = 0;

    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
        // Get DSC Bit Per Pixel
        usDpTxBitPerPixel = GET_DP_TX_INPUT_DSC_COLOR_BPP();

        DebugMessageDpTx("[MST2SST]usDpTxBitPerPixel", usDpTxBitPerPixel);

        // Check DSC PPS Color Space Mode: BPP Need To Div 2 On 422/420 Mode
        if(GET_DP_TX_INPUT_DSC_COLOR_NATIVE_MODE() == _TRUE)
        {
            usDpTxBitPerPixel = usDpTxBitPerPixel >> 1;
        }
#endif
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
#if(_DSC_DECODER_SUPPORT == _ON)
        BYTE ucDscMac = ScalerDscDecoderDxInputPortGetDscDecoderMac(ScalerDpMacTxCloneGetCurrentInputPort());

        // Get DSC Bit Per Pixel From PPS byte 4/5
        usDpTxBitPerPixel = ScalerDscDecoderGetDscBitPerPixel(ucDscMac);

        DebugMessageDpTx("[SST2SST]usDpTxBitPerPixel", usDpTxBitPerPixel);

        // Check DSC PPS Color Space Mode: BPP Need To Div 2 On 422/420 Mode
        if(ScalerDscDecoderGetNativeMode(ucDscMac) == _TRUE)
        {
            usDpTxBitPerPixel = usDpTxBitPerPixel >> 1;
        }
#endif
    }

    return usDpTxBitPerPixel;
}

//--------------------------------------------------
// Description  : DP Mac Tx Set DSC TU Size Auto Setting
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetDscTuSizeAuto(bit bEnable)
{
    ScalerSetBit(PBB_DA_DPTX_TOP_RSV1, ~_BIT3, ((bEnable == _ENABLE) ? _BIT3 : 0x00));
}
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Down Device FreeSync En
// Input Value  : None
// Output Value : _SUCCESS, _FAIL
//--------------------------------------------------
bit ScalerDpMacTxDfpDeviceFreesyncEnable(void)
{
    BYTE ucFreeSyncConfig = 0x00;
    bit bEnable = 0;

    if(GET_DP_MAC_TX_DOWNSTREAM_MSA_IGNORED() == _TRUE)
    {
        // Repeater Need to Send Freesync Enable Info to Downstream if Source has enabled Freesync
        if(ScalerDpAuxTxNativeRead(0x00, 0x00, 0x07, 1, &ucFreeSyncConfig) == _TRUE)
        {
            bEnable = GET_FREESYNC_DP_TX_ENABLED();

            ucFreeSyncConfig = ((ucFreeSyncConfig & ~_BIT7) | ((BYTE)bEnable << 7));

            if(ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x07, 1, &ucFreeSyncConfig) == _TRUE)
            {
                return bEnable;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Decide Current Port DPTx whether Can Output or not
// Input Value  : EnumInputPort
// Output Value : _TRUE, _FAIL
//--------------------------------------------------
bit ScalerDpMacTxDrrCloneOutputCheck(EnumInputPort enumInputPort)
{
    if(ScalerDrrFreeSyncDpGetEnable(enumInputPort) == _TRUE)
    {
        if(GET_DP_MAC_TX_DOWNSTREAM_MSA_IGNORED() == _TRUE)
        {
            return _TRUE;
        }
        else
        {
            DebugMessageDpTx("Clone Mode Sink Not Support Freesync", 0);

            return _FALSE;
        }
    }
    else
    {
        return _TRUE;
    }
}
#endif

//--------------------------------------------------
// Description  : Get DFP Device Extend Receiver Capability
// Input Value  :
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxGetDfpDeviceExtendReceiverCapProc(void)
{
    BYTE ucExtendFeature = 0;

    if((g_pucDpMacTxDownStreamCapTable[14] & _BIT7) == _BIT7)
    {
        if(ScalerDpAuxTxNativeRead(0x00, 0x22, 0x10, 1, &ucExtendFeature) == _FALSE)
        {
            return _FALSE;
        }


        if((ucExtendFeature & (_BIT1 | _BIT3)) != g_ucDpMacTxPreviousVscSdpCapStatus)
        {
            // DFP Device Capability Change
            SET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();
            g_ucDpMacTxPreviousVscSdpCapStatus = (ucExtendFeature & (_BIT1 | _BIT3));
        }

        // Check Split Sdp Cap
        if((ucExtendFeature & _BIT1) == _BIT1)
        {
            SET_DP_TX_DOWNSTREAM_SPLIT_SDP_SUPPORT();
        }
        else
        {
            CLR_DP_TX_DOWNSTREAM_SPLIT_SDP_SUPPORT();
        }

        // Check VSC Sdp Cap
        if((ucExtendFeature & _BIT3) == _BIT3)
        {
            SET_DP_TX_DOWNSTREAM_VSC_SDP_SUPPORT();
        }
        else
        {
            CLR_DP_TX_DOWNSTREAM_VSC_SDP_SUPPORT();
        }
    }
    else
    {
        CLR_DP_TX_DOWNSTREAM_VSC_SDP_SUPPORT();
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx DFP Device Version Relative Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDfpDeviceVersionProc(void)
{
    BYTE ucDpcdVersion = g_pucDpMacTxDownStreamCapTable[0];
    BYTE ucTp3Info = g_pucDpMacTxDownStreamCapTable[2];
    BYTE ucTp4Info = g_pucDpMacTxDownStreamCapTable[3];

    // Step1:Get DownStream infromation
    if((ucDpcdVersion != _DP_VERSION_1_1) && (ucDpcdVersion != _DP_VERSION_1_2) && (ucDpcdVersion != _DP_VERSION_1_3) && (ucDpcdVersion != _DP_VERSION_1_4))
    {
        if(ucDpcdVersion >= _DP_VERSION_1_4)
        {
            ucDpcdVersion = _DP_VERSION_1_4;
        }
        else
        {
            ucDpcdVersion = _DP_VERSION_1_1;
        }
    }

    SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(ucDpcdVersion);

#if(_DP_TX_CONFIG_BY_USER_SUPPORT == _ON)
    // Set DP Tx Link Config by User
    ScalerDpMacTxLinkConfigAdjust(GET_DP_MAC_TX_CONFIG_SETTING());
#endif

    if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
    {
        if((ucTp3Info & _BIT6) == _BIT6)
        {
            SET_DP_MAC_TX_DOWNSTREAM_TP3_SUPPORT();
        }
        else
        {
            CLR_DP_MAC_TX_DOWNSTREAM_TP3_SUPPORT();
        }

        // Check TP4 support
        if((ucTp4Info & _BIT7) == _BIT7)
        {
            SET_DP_MAC_TX_DOWNSTREAM_TP4_SUPPORT();
        }
        else
        {
            CLR_DP_MAC_TX_DOWNSTREAM_TP4_SUPPORT();
        }

        ScalerDpMacTxMstPeerDeviceCapProc();
    }
    else // DPCD Revision 1.0/1.1
    {
        SET_DP_MAC_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_TX_SST_SINK);
        SET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS(_DP_TX_MSG_NO_SUPPORT);
        SET_DP_MAC_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_UNPLUG);
    }
}

//--------------------------------------------------
// Description  : Dp Tx Read DFP Device Link Rate & Lane Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxGetDfpDeviceLinkBandwidth(void)
{
    BYTE ucMaxLinkRate = g_pucDpMacTxDownStreamCapTable[1];
    BYTE ucMaxLaneCount = g_pucDpMacTxDownStreamCapTable[2];
    BYTE ucDpLinkRateLimit = _DP_LINK_RBR;

    ScalerDpMacTxGetDfpDeviceDownUHBRStatus(&ucMaxLinkRate);

#if(_DP_TX_CONFIG_BY_USER_SUPPORT == _ON)
    // Set DP Tx Link Config by User
    if(GET_DP_MAC_TX_CONFIG_SETTING() == _DP_TX_CONFIG_NONE)
#endif
    {
        if(ScalerDpMacTxGetLttprInitialMode() != _DP_TX_LTTPR_NON_LTTPR_MODE)
        {
            if(GET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM() > 0)
            {
                if(g_pucDpMacTxDfpLTTPRCap[0] == 0x14)
                {
                    // LTTPR Support 8b/10b DP Channel Coding
                    if(ucMaxLinkRate > g_pucDpMacTxDfpLTTPRCap[1])
                    {
                        ucMaxLinkRate = g_pucDpMacTxDfpLTTPRCap[1];
                    }
                }
                else if(g_pucDpMacTxDfpLTTPRCap[0] == 0x20)
                {
                    // LTTPR Support 128b/132b DP Channel Coding
                    if((g_pucDpMacTxDfpLTTPRCap[6] & _BIT0) == _BIT0)
                    {
                        BYTE ucMaxLinkRateLTTPR = ucMaxLinkRate;

                        if((g_pucDpMacTxDfpLTTPRCap[7] & _BIT1) == _BIT1)
                        {
                            ucMaxLinkRateLTTPR = _DP_LINK_UHBR20;
                        }
                        else if((g_pucDpMacTxDfpLTTPRCap[7] & _BIT2) == _BIT2)
                        {
                            ucMaxLinkRateLTTPR = _DP_LINK_UHBR13_5;
                        }
                        else if((g_pucDpMacTxDfpLTTPRCap[7] & _BIT0) == _BIT0)
                        {
                            ucMaxLinkRateLTTPR = _DP_LINK_UHBR10;
                        }

                        if(ucMaxLinkRate > ucMaxLinkRateLTTPR)
                        {
                            ucMaxLinkRate = ucMaxLinkRateLTTPR;
                        }
                    }
                    else
                    {
                        // LTTPR Support 8b/10b DP Channel Coding
                        if(ucMaxLinkRate > g_pucDpMacTxDfpLTTPRCap[1])
                        {
                            ucMaxLinkRate = g_pucDpMacTxDfpLTTPRCap[1];
                        }
                    }
                }

                if((ucMaxLaneCount & 0x1F) > (g_pucDpMacTxDfpLTTPRCap[4] & 0x1F))
                {
                    ucMaxLaneCount = ((ucMaxLaneCount & 0xE0) | (g_pucDpMacTxDfpLTTPRCap[4] & 0x1F));
                }
            }
        }
        // Step1:Get link Rate Limit
        if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_3)
        {
#if(_DP_SUPPORT == _ON)
            if((GET_DP_MAC_TX_DOWNSTREAM_128B132B_SUPPORT() == _TRUE) && (ScalerDpAuxRxGetDpcdMaxLinkRateCapability(GET_DP_RX_MAIN_PORT()) >= _DP_LINK_UHBR10))
            {
                ucDpLinkRateLimit = _DP_LINK_UHBR20;
            }
            else
#endif
            {
                ucDpLinkRateLimit = _DP_LINK_HBR3;
            }
        }
        else if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() == _DP_VERSION_1_2)
        {
            ucDpLinkRateLimit = _DP_LINK_HBR2;
        }
        else
        {
            ucDpLinkRateLimit = _DP_LINK_HBR;
        }

        // Step2:Get link Rate
        if((ucMaxLinkRate == _DP_LINK_RBR) || (ucMaxLinkRate == _DP_LINK_HBR) || (ucMaxLinkRate == _DP_LINK_HBR2) || (ucMaxLinkRate == _DP_LINK_HBR3) ||
           (ucMaxLinkRate == _DP_LINK_UHBR10) || (ucMaxLinkRate == _DP_LINK_UHBR13_5) || (ucMaxLinkRate == _DP_LINK_UHBR20))
        {
            if(ucMaxLinkRate > ucDpLinkRateLimit)
            {
                if(_P0_DP_LINK_CLK_RATE > ucDpLinkRateLimit)
                {
                    ucMaxLinkRate = ucDpLinkRateLimit;
                }
                else
                {
                    ucMaxLinkRate = _P0_DP_LINK_CLK_RATE;
                }
            }
            else
            {
                if(ucMaxLinkRate > _P0_DP_LINK_CLK_RATE)
                {
                    ucMaxLinkRate = _P0_DP_LINK_CLK_RATE;
                }
                else
                {
                    ucMaxLinkRate = ucMaxLinkRate;
                }
            }
        }
        else // Set the slowest link rate
        {
            ucMaxLinkRate = _DP_LINK_RBR;
        }

        if((ucMaxLaneCount & 0x1F) > _P0_DP_MAIN_LINK_LANES)
        {
            ucMaxLaneCount = (ucMaxLaneCount & 0xE0) | _P0_DP_MAIN_LINK_LANES;
        }
        else
        {
            ucMaxLaneCount = ucMaxLaneCount;
        }

        SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(ucMaxLinkRate);
        SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM((ucMaxLaneCount & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

        if(ucMaxLinkRate >= _DP_LINK_UHBR10)
        {
            SET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE(_CODING_TYPE_128B132B);
        }
        else
        {
            SET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE(_CODING_TYPE_8B10B);
        }
    }

    SET_DP_MAC_TX_DOWNSTREAM_ENHANCE_FRAMING((bit)(ucMaxLaneCount & _BIT7));
}

//--------------------------------------------------
// Description  : Dp Tx Read DFP Device UHBR
// Input Value  : None
// Output Value : Date rate
//--------------------------------------------------
void ScalerDpMacTxGetDfpDeviceDownUHBRStatus(BYTE *pucDpMaxLinkRate)
{
    BYTE ucCodingType = g_pucDpMacTxDownStreamCapTable[6];
    BYTE pucBasicCapInfo[1] = {0};

    if((ucCodingType & _BIT1) == _BIT1)
    {
        SET_DP_MAC_TX_DOWNSTREAM_128B132B_SUPPORT();

        ScalerDpAuxTxNativeRead(0x00, 0x22, 0x15, 1, pucBasicCapInfo);

        if((pucBasicCapInfo[0] & _BIT0) == _BIT0)
        {
            if(_P0_DP_LINK_CLK_RATE >= _DP_LINK_UHBR10)
            {
                SET_DP_MAC_TX_DOWNSTREAM_UHBR10_SUPPORT();
                *pucDpMaxLinkRate = _DP_LINK_UHBR10;
            }
        }

        if((pucBasicCapInfo[0] & _BIT2) == _BIT2)
        {
            if(_P0_DP_LINK_CLK_RATE >= _DP_LINK_UHBR13_5)
            {
                SET_DP_MAC_TX_DOWNSTREAM_UHBR13_5_SUPPORT();
                *pucDpMaxLinkRate = _DP_LINK_UHBR13_5;
            }
        }

        if((pucBasicCapInfo[0] & _BIT1) == _BIT1)
        {
            if(_P0_DP_LINK_CLK_RATE == _DP_LINK_UHBR20)
            {
                SET_DP_MAC_TX_DOWNSTREAM_UHBR20_SUPPORT();
                *pucDpMaxLinkRate = _DP_LINK_UHBR20;
            }
        }
    }
    else
    {
        CLR_DP_MAC_TX_DOWNSTREAM_128B132B_SUPPORT();
        CLR_DP_MAC_TX_DOWNSTREAM_UHBR10_SUPPORT();
        CLR_DP_MAC_TX_DOWNSTREAM_UHBR20_SUPPORT();
        CLR_DP_MAC_TX_DOWNSTREAM_UHBR13_5_SUPPORT();
    }
}

//--------------------------------------------------
// Description  : Dp Tx Read DFP Device SSC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxGetDfpDeviceDownSpreadStatus(void)
{
    BYTE ucSscInfo = g_pucDpMacTxDownStreamCapTable[3];

#if(_DP_TX_SSC_SUPPORT == _ON)
    if((ucSscInfo & _BIT0) == _BIT0)
    {
        SET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD(_TRUE);
    }
#else
    ucSscInfo = ucSscInfo;

    SET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD(_FALSE);
#endif
}

//--------------------------------------------------
// Description  : Dp Tx Read DFP Device Msa Ignored
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxGetDfpDeviceMsaIgnored(void)
{
    BYTE ucMsaIgnoredInfo = g_pucDpMacTxPreviousDfpDeviceCap[7];

    if((ucMsaIgnoredInfo & _BIT6) == _BIT6)
    {
        SET_DP_MAC_TX_DOWNSTREAM_MSA_IGNORED(_TRUE);
    }
    else
    {
        SET_DP_MAC_TX_DOWNSTREAM_MSA_IGNORED(_FALSE);
    }
}

//--------------------------------------------------
// Description  : Get Dfp Device Ycbcr 420 support
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxGetDfpDeviceYcbcr420Support(void)
{
    if((GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_4) && (ScalerDpMacTxEdidAnalysisYcbcr420Capable() == _TRUE))
    {
        SET_DP_MAC_TX_DOWNSTREAM_420_SUPPORT();
    }
    else
    {
        CLR_DP_MAC_TX_DOWNSTREAM_420_SUPPORT();
    }
}

//--------------------------------------------------
// Description  : DP Tx Peer Device Cap Relative Process
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
void ScalerDpMacTxMstPeerDeviceCapProc(void)
{
    BYTE ucReceiverPortInfo = g_pucDpMacTxDownStreamCapTable[4];
    BYTE ucDFPInfo = g_pucDpMacTxDownStreamCapTable[5];
    BYTE ucMstCapEnableInfo = 0x00;

    // Disable Downstream MST Mode
    if(ScalerDpAuxTxNativeRead(0x00, 0x01, 0x11, 1, &ucMstCapEnableInfo) == _TRUE)
    {
        if((ucMstCapEnableInfo & _BIT1) == _BIT1)
        {
            SET_DP_MAC_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS(_TRUE);
        }
        else
        {
            SET_DP_MAC_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS(_FALSE);
        }

        if((ucMstCapEnableInfo & _BIT0) == _BIT0)
        {
            ucMstCapEnableInfo = (ucMstCapEnableInfo & 0xFE);
            ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x11, 1, &ucMstCapEnableInfo);
        }
    }

#if(_DP_MST_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT)
    {
        SET_DP_MAC_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_TX_MST_OR_SST_BRANCH_DOWNSTREAM);
        SET_DP_MAC_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_UNPLUG);
    }
    else
#endif
    {
        SET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS(_DP_TX_MSG_NO_SUPPORT);

        if((ucReceiverPortInfo & _BIT0) == _BIT0)
        {
            SET_DP_MAC_TX_DOWNSTREAM_NUMBER_OF_SDP(1);

            SET_DP_MAC_TX_DOWNSTREAM_NUMBER_OF_SDP_SINK(1);
        }
        else
        {
            SET_DP_MAC_TX_DOWNSTREAM_NUMBER_OF_SDP(0);

            SET_DP_MAC_TX_DOWNSTREAM_NUMBER_OF_SDP_SINK(0);
        }

        if((ucDFPInfo & _BIT0) == _BIT0)
        {
            if((ucDFPInfo & (_BIT2 | _BIT1)) == _DP_TX_DP_TYPE)
            {
                SET_DP_MAC_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_TX_MST_OR_SST_BRANCH_DOWNSTREAM);
                SET_DP_MAC_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_UNPLUG);
            }
            else // SST Legacy Converter Device
            {
                SET_DP_MAC_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_TX_TO_LEGACY);
                SET_DP_MAC_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_PLUG);
            }
        }
        else // SST Sink Device
        {
            SET_DP_MAC_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_TX_SST_SINK);
            SET_DP_MAC_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_UNPLUG);
        }
    }
}

//--------------------------------------------------
// Description  : Get DP Tx Max Link Rate
// Input Value  : None
// Output Value : DP Tx Link Rate
//--------------------------------------------------
EnumDpLinkRate ScalerDpMacTxGetMaxLinkRate(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE() == _CODING_TYPE_8B10B)
    {
        if(GET_DP_MAC_TX_DOWNSTREAM_128B132B_SUPPORT() == _TRUE)
        {
            return _DP_LINK_HBR3;
        }
    }
#endif

    return GET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE();
}

//--------------------------------------------------
// Description  : Handle Tx Output stream
// Input Value  : DP Tx Input Source
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxStreamHandler(void)
{
#if(_DP_MST_SUPPORT == _ON)
    if(ScalerDpMacTxMstStreamChangeCheck() == _TRUE)
    {
        return;
    }
#endif

    if(GET_DP_TX_STREAM_SOURCE_CHANGE() == _TRUE)
    {
        CLR_DP_TX_STREAM_SOURCE_CHANGE();

#if(_DP_TX_FEC_SUPPORT == _ON)
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_8B10B)
#endif
        {
            ScalerDpMacTxFecStreamChangeCheck();
        }
#endif

        ScalerDpMacTxSyncInputInfo(GET_DP_TX_STREAM_SOURCE());

        switch(GET_DP_TX_STREAM_SOURCE())
        {
            case _DP_TX_SOURCE_NONE:

                if(ScalerDpMacTxHdcpGetEncryptStatus() == _TRUE)
                {
                    ScalerDpHdcp14TxEncryptSignalProc(_DISABLE);

                    ScalerTimerDelayXms(2);
                }

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
                {
                    ScalerDpMacTxSyncDownStreamTableSetting(0x00, 0x00, 0x3F);
                }
#endif
                // Main Link switch to IDLE Pattern
                ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_IDLE_PATTERN);

                // Disable Sdp Hw Bypass
                ScalerDpMacTxSdpHwBypassSetting(_DISABLE);

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
                // DP Tx DSC Pass-Through Reset
                ScalerDpMacTxDscPassThroughReset();

                // Set DFP DSC Enable Process
                ScalerDpMacTxDfpDscEnableProc(_DISABLE);
#endif
                ScalerDpMacTxReorderReset();

#if(_DP_TX_AUDIO_SUPPORT == _ON)

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))
                if(GET_DP_TX_AUDIO_STAND_ALONE() == _OFF)
#endif
                {
                    // Disable Audio
                    ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_OFF);
                }
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)
                break;

            case _DP_TX_SOURCE_MST:

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
                {
                    // Source Sel from DpRx
                    ScalerSetBit(P2B_D3_SOURCE_CTRL_0, ~_BIT6, 0x00);

                    // Clk from Daisy fifo
                    ScalerSetBit(P2B_FA_DPTX20_ARIBITER, ~_BIT0, 0x00);
                }
                else
#endif
                {
                    // RS decode clk sel to Rx link clk
                    ScalerSetBit(PA_03_MST2SST_CLK_GATE, ~_BIT7, 0x00);

                    // Reset Daisy Chain Async-fifo
                    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, _BIT6);
                    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, 0x00);
                }

#if(_DP_TX_AUDIO_SUPPORT == _ON)
                // Disable Audio
                ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_OFF);
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)
                break;

            case _DP_TX_SOURCE_MST2SST:
            case _DP_TX_SOURCE_CLONE:

#if(_DP_FREESYNC_SUPPORT == _ON)
                if(ScalerDpMacTxDfpDeviceFreesyncEnable() == _TRUE)
                {
                    DebugMessageDpTx("Enable Down Device Freesync", 1);
                }
#endif

                // Set DSC/Video from  & Set MST2SST/Clone Lane Config
                ScalerDpMacTxDataMuxConfig();

                // Setting DP TX MAC
                ScalerDpMacTxSSTSetting();

                // Main Link switch to VIDEO pattern
                ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_VIDEO_PATTERN);

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
                // Setting DP Tx DSC Pass-Through
                ScalerDpMacTxDscPassThroughSetting();
#endif
                // Enable Sdp Hw Bypass
                if((GET_DP_TX_STREAM_DATA_PATH_TYPE() == _DATA_PATH_VIDEO_REORDER) || (GET_DP_TX_STREAM_DATA_PATH_TYPE() == _DATA_PATH_DSC_REORDER))
                {
                    ScalerDpMacTxSdpHwBypassSetting(_ENABLE);
                }

                break;

            default:
                break;
        }
    }

#if(_DP_TX_FEC_SUPPORT == _ON)
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_8B10B)
#endif
    {
        ScalerDpMacTxFecStreamEnableCheck();
    }
#endif

#if(_DP_TX_AUDIO_SUPPORT == _ON)

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))
    ScalerDpMacTxSleepAudioControl();
#endif

    // Play Audio If Get Audio Packet or Replay Audio While Audio Format is Changed
    if((GET_DP_TX_AUDIO_READY_TO_PLAY() == _TRUE) && (ScalerDpMacTxSdpAudioGetFormatChange() == _TRUE))
    {
        ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_FORMAT_CHANGE);

        if(GET_DP_TX_AUDIO_SAMPLING_FREQUENCY() != _DP_TX_AUDIO_FREQ_NO_AUDIO)
        {
            ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_ON);
        }
    }
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

    ScalerDpMacTxSdpHandler();

#if(_DP_HDCP2_RX_SUPPORT == _ON)
    ScalerDpHdcp2TxOutputContentStreamHandler();
#endif
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Handle Tx Mst Stream Change Check
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxMstStreamChangeCheck(void)
{
    if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST) && (ScalerDpRxGetSrcMstEnable(GET_DP_RX_MAIN_PORT()) == _FALSE))
    {
        ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_NONE);
    }

    if(GET_DP_MST_TX_ENABLE() == _FALSE)
    {
        if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
        {
            DebugMessageDpTx("Set DPTx0 DPCD 00111h MST Mode", 0);

            SET_DP_TX_FORCE_LINK_TRAINING();

            return _TRUE;
        }
    }
    else
    {
        if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_MST)
        {
            DebugMessageDpTx("Set DPTx0 DPCD 00111h SST Mode", 0);

            SET_DP_TX_FORCE_LINK_TRAINING();

            return _TRUE;
        }
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : DP Tx MST Sync table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSyncTableProcess(void)
{
    // Timeslot & dasiy Fifo
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxSyncTableProcess_128b132b();
    }
    else
#endif
    {
        ScalerDpMacTxSyncTableProcess_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx MST Sync table_8b10b
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSyncTableProcess_8b10b(void)
{
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Get Stream Type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumDpStreamDataPath ScalerDpMacTxGetStreamDataPathType(void)
{
    switch(GET_DP_TX_STREAM_SOURCE())
    {
        case _DP_TX_SOURCE_MST2SST:
            return ScalerDpStreamGetDataPath(_STREAM_MST2SST);

        case _DP_TX_SOURCE_CLONE:
            return ScalerDpStreamGetDataPath(_STREAM_CLONE);

        default:
            break;
    }

    return _DATA_PATH_INVALID;
}
#endif

//--------------------------------------------------
// Description  : DP Tx Data mux Set
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDataMuxConfig(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxDataMuxConfig_128b132b();
    }
    else
#endif
    {
        ScalerDpMacTxDataMuxConfig_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Data mux Set
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDataMuxConfig_8b10b(void)
{
    switch(GET_DP_TX_STREAM_DATA_PATH_TYPE())
    {
        case _DATA_PATH_VESA:
        case _DATA_PATH_DSC_DECODER:

            // Enable Sclk Clk & Disable Dsc/Video Reordering
            ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~(_BIT7 | _BIT6 | _BIT2), _BIT2);

#if(_DP_TX_AUDIO_SUPPORT == _ON)
            if(GET_DP_TX_AUDIO_INPUT_PATH() == _DP_TX_AUDIO_PATH_RS_DECODER)
            {
                // Set MST Mode
                ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~_BIT5, _BIT5);
            }
            else
            {
                // Set SST Mode
                ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~_BIT5, 0x00);
            }
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
            ScalerDpMacTxSdpHwBypassSettingforVesaPath();
#endif
            break;

        case _DATA_PATH_VIDEO_REORDER:

            // MST2SST/Clone Lane Config
            ScalerDpMacTxSetMst2SstLaneConfig();

            // Select Main Link data from Dp Rx14 or Dp Rx20
            ScalerDpMacTxSetDpStreamSelect();

            // Set DSC/Vesa Reorder Lane Count and Mst Mode
            ScalerDpMacTxStreamReorderSetting();

            // Set DSC/Video from Dp Rx Main Link
            ScalerSetBit(PBB_F8_DPTX_TOP_RSV3, ~_BIT4, 0x00);

            // Disable Sclk Clk & Enable Video Reordering
            ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~(_BIT7 | _BIT6 | _BIT2), _BIT6);

            break;

        case _DATA_PATH_DSC_REORDER:

            // MST2SST/Clone Lane Config
            ScalerDpMacTxSetMst2SstLaneConfig();

            // Select Main Link data from DpRx14 or DpRx20
            ScalerDpMacTxSetDpStreamSelect();

            // Set DSC/Vesa Reorder Lane Count and Mst Mode
            ScalerDpMacTxStreamReorderSetting();

            // Set DSC/Video from DP Rx main link
            ScalerSetBit(PBB_F8_DPTX_TOP_RSV3, ~_BIT4, 0x00);

            // Disable Sclk clk & Enable Dsc Reordering
            ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT3));

            break;

        case _DATA_PATH_DSC_BYPASS:
        case _DATA_PATH_VIDEO_BYPASS:
        default:
            break;
    }

    // Set Tx Output Data from Arbiter
    ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, 0x00);
}

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Data Sdp HW Bypass Setting for VESA Path
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpHwBypassSettingforVesaPath(void)
{
    // DP20 MST DP14 SST ->  0x0A17 0xBBF1[5] 0x0A00[7] 0x2F00[6] 0xBBF1[3] 0x0A01[7]
    // DP20 SST DP14 SST ->         0xBBF1[5] 0x0A00[7] 0x2F00[6] 0xBBF1[3] 0xBBF2[0]
    // DP14 MST DP14 SST ->         0xBBF1[3] 0x0A01[7]
    // DP14 SST DP14 SST ->  0x0A17 0xBBF1[3] 0xBBF2[0]

    // AS SDP Bypass Mode: Set Daisy Chain Path for Clone Path
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        ScalerSetBit(PA_17_SOURCE_CTRL_0, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
    }

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(GET_DP_MAC_TX_INPUT_PORT()) == _CODING_TYPE_128B132B)
    {
        // AS SDP Bypass Mode: Set Daisy Chain Path for DP20MST to DP14SST
        if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
        {
            ScalerDpMacTxSetDaisySourceMuxReg_8b10b(_DP_ST_SOURCE1, GET_DP_MAC_TX_ST_SOURCE_BACKUP(_DP_ST_SOURCE1));
        }

        // Set RX MST Mode
        ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~_BIT5, _BIT5);

        // Set Main Link Stream Selection
        ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT7, _BIT7);

        // Set DP20 to DP14 Clk Enable flag
        ScalerSetBit(P2F_00_CTRL_ST1_00, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT6);
    }
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
    // Set RX FEC Ready Register(HDCP ON)
    if(ScalerDpMacDphyRxGetFecDecodeStatus(GET_DP_RX_MAIN_PORT()) == _TRUE)
    {
        ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~_BIT3, _BIT3);
    }
    else
    {
        ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~_BIT3, 0x00);
    }
#endif
}
#endif

//--------------------------------------------------
// Description  : DP Tx 6 to 4 Source Sel and MST Mode Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetMst2SstLaneConfig(void)
{
    // Swtich MST Daisy Chain or MST to SST Lane Num
    switch(GET_DP_MAC_TX_INPUT_LANE_COUNT())
    {
        case _DP_LINK_1_LANE:

            ScalerSetBit(PA_02_MST2SST_CONFIG, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_LINK_2_LANE:

            ScalerSetBit(PA_02_MST2SST_CONFIG, ~(_BIT4 | _BIT3), _BIT4);

            break;

        default:
        case _DP_LINK_4_LANE:

            ScalerSetBit(PA_02_MST2SST_CONFIG, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }
}

//--------------------------------------------------
// Description  : DP Tx data from Dp20/14 rx stream selection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetDpStreamSelect(void)
{
    // Video / DSC Reorder (DP14 SST to DP14 SST) ->  0x0A02[7]=0 0x0A17=10h 0x0AE0=80h
    // Video / DSC Reorder (DP14 MST to DP14 SST) ->  0x0A02[7]=1 0x0A17=20h 0x0AE0=80h
    // Video / DSC Reorder (DP20 SST to DP14 SST) ->  0x0A02[7]=1 0x2BDC=10h 0x0AE0=80h
    // Video / DSC Reorder (DP20 MST to DP14 SST) ->  0x0A02[7]=1 0x2BDC=20h 0x0AE0=80h
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        // Set Stream Source Select
        ScalerSetBit(PA_17_SOURCE_CTRL_0, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(GET_DP_MAC_TX_INPUT_PORT()) == _CODING_TYPE_128B132B)
        {
            // Set MST Mode
            ScalerSetBit(PA_02_MST2SST_CONFIG, ~_BIT7, _BIT7);
        }
        else
#endif
        {
            // Set SST Mode
            ScalerSetBit(PA_02_MST2SST_CONFIG, ~_BIT7, 0x00);
        }
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        // Set MST Mode
        ScalerSetBit(PA_02_MST2SST_CONFIG, ~_BIT7, _BIT7);
    }

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_INPUT_CHANNEL_CODING() == _CODING_TYPE_128B132B)
    {
        // From Dp20 Stream
        ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT7, _BIT7);

        // Enable Dp20 to 14
        ScalerSetBit(P2F_00_CTRL_ST1_00, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT6);

        // Block Daisy Fifo Full Flag : Switch from Daisy Path to Arbiter Path
        ScalerSetBit(P2F_10_CTRL_ST1_10, ~_BIT4, _BIT4);

#if(_DP_MST_SUPPORT == _ON)
        SET_DP_MST_TX_128B132B_TO_8B10B_MSA_CONVERT_ENABLE(_DP_ST_1);
#endif

        if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
        {
            // Set Stream Source Select
            ScalerDpMacTxSetDaisySourceMuxReg_128b132b(_DP_ST_SOURCE1, _DP_ST_1);
            ScalerDpMacTxSetDaisySourceMuxReg_8b10b(_DP_ST_SOURCE1, _DP_ST_1);
        }
        else
        {
            // Set Stream Source Select
            ScalerDpMacTxSetDaisySourceMuxReg_8b10b(_DP_ST_SOURCE1, GET_DP_MAC_TX_ST_SOURCE_BACKUP(_DP_ST_SOURCE1));
        }
    }
    else
#endif
    {
        // From Dp14 Stream
        ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT7, 0x00);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        // Disable Dp20 to 14
        ScalerSetBit(P2F_00_CTRL_ST1_00, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_DP_MST_SUPPORT == _ON)
        CLR_DP_MST_TX_128B132B_TO_8B10B_MSA_CONVERT_ENABLE(_DP_ST_1);
#endif
#endif
    }
}

//--------------------------------------------------
// Description  : DP Tx Reorder Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxStreamReorderSetting(void)
{
    // Video Reorder(DP14 SST to DP14 SST) ->  0xBBF1[6]=1 0xBBF1[5]=0 0xBBB2[1]=1 0x0AE0=80h
    // Video Reorder(DP14 MST to DP14 SST) ->  0xBBF1[6]=1 0xBBF1[5]=1 0xBBB2[1]=1 0x0AE0=80h
    // Video Reorder(DP20 SST to DP14 SST) ->  0xBBF1[6]=1 0xBBF1[5]=1 0xBBB2[1]=1 0x0AE0=80h
    // Video Reorder(DP20 MST to DP14 SST) ->  0xBBF1[6]=1 0xBBF1[5]=1 0xBBB2[1]=1 0x0AE0=80h

    // DSC Reorder(DP14 SST to DP14 SST)   ->  0xBBF1[7]=1 0xBBF1[5]=0 0xBBB2[1]=1 0x0AE0=80h
    // DSC Reorder(DP14 MST to DP14 SST)   ->  0xBBF1[7]=1 0xBBF1[5]=1 0xBBB2[1]=1 0x0AE0=80h
    // DSC Reorder(DP20 SST to DP14 SST)   ->  0xBBF1[7]=1 0xBBF1[5]=1 0xBBB2[1]=1 0x0AE0=80h
    // DSC Reorder(DP20 MST to DP14 SST)   ->  0xBBF1[7]=1 0xBBF1[5]=1 0xBBB2[1]=1 0x0AE0=80h

    EnumDpLaneCount enumDpLaneCount = _DP_LINK_4_LANE;

    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(GET_DP_MAC_TX_INPUT_PORT()) == _CODING_TYPE_128B132B)
        {
            enumDpLaneCount = GET_DP_MAC_TX_INPUT_LANE_COUNT();
        }
        else
#endif
        {
            enumDpLaneCount = (GET_DP_TX_STREAM_DATA_PATH_TYPE() == _DATA_PATH_VIDEO_REORDER) ? GET_DP_MAC_TX_INPUT_LANE_COUNT() : _DP_LINK_4_LANE;
        }
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        enumDpLaneCount = GET_DP_MAC_TX_INPUT_LANE_COUNT();
    }

    // Swtich Reorder Lane Num
    switch(enumDpLaneCount)
    {
        case _DP_LINK_1_LANE:

            ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~(_BIT1 | _BIT0), _BIT0);

            break;

        case _DP_LINK_2_LANE:

            ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~(_BIT1 | _BIT0), _BIT1);

            break;

        case _DP_LINK_4_LANE:
        default:

            ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            break;
    }

    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        // Set MST Mode
        ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~_BIT5, _BIT5);
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(GET_DP_MAC_TX_INPUT_PORT()) == _CODING_TYPE_128B132B)
        {
            // Set MST Mode
            ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~_BIT5, _BIT5);
        }
        else
#endif
        {
            // Set SST Mode
            ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~_BIT5, 0x00);
        }
    }

    // Reorder Tracking Mode(BS Mode) : Sync FEC_Ready Setting with RX (HCDP ON)
#if(_DP_RX_FEC_SUPPORT == _ON)
    if(ScalerDpMacDphyRxGetFecDecodeStatus(GET_DP_RX_MAIN_PORT()) == _TRUE)
    {
        ScalerSetBit(PA_01_MST2SST_ASYNC_FIFO, ~(_BIT7 | _BIT3 | _BIT2), _BIT7);
        ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~_BIT3, _BIT3);
    }
#endif

#if(_DP_SUPPORT == _ON)
    // Check if DP Mac Tx Need to Do Pll Tracking
    if(ScalerDpMacTxTrackingEnableCheck(GET_DP_TX_STREAM_SOURCE()) == _FALSE)
    {
        if(ScalerDpMacTxReorderTrackingPllSetting(GET_DP_TX_STREAM_SOURCE()) == _TRUE)
        {
            // Enable Video / DSC Reorder Tracking Mode : Utilize BS as Source HS
            ScalerSetBit(PBB_B2_NVID_ASYNC_M, ~(_BIT1 | _BIT0), _BIT1);
        }
        else
        {
            // Disable Video / DSC Reorder Tracking Mode
            ScalerSetBit(PBB_B2_NVID_ASYNC_M, ~_BIT1, 0x00);
            DebugMessageDpTx("DPTX Reorder Tracking Mode No Support: PLL Tracking Fail", GET_DP_TX_STREAM_SOURCE());
        }
    }
    else
    {
        // Check Corresponding DPRx Mac Tracking Status of DPTx Clone Port
        if(ScalerDpMacStreamRxTrackingStatusCheck(ScalerDpMacTxCloneGetCurrentInputPort()) == _TRUE)
        {
            // Enable Video / DSC Reorder Tracking Mode : Utilize BS as Source HS
            ScalerSetBit(PBB_B2_NVID_ASYNC_M, ~(_BIT1 | _BIT0), _BIT1);
        }
        else
        {
            // Disable Video / DSC Reorder Tracking Mode
            ScalerSetBit(PBB_B2_NVID_ASYNC_M, ~_BIT1, 0x00);
            DebugMessageDpTx("DPTX Reorder Tracking Mode No Support: DPRX Tracking Status Disable", GET_DP_TX_STREAM_SOURCE());
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Sync Tx Input Port Info
// Input Value  : DPTX STREAM SOURCE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSyncInputInfo(EnumDPTxInputSource enumStreamSource)
{
    EnumDpLaneCount enumDpLaneCount = _DP_LINK_NO_LANE;
    EnumDpLinkChannelCodingType enumDpCodingType = _CODING_TYPE_8B10B;
    BYTE ucDpMacTxStreamType = _DATA_PATH_NONE;
    EnumInputPort enumDpMacTxInputPort = _NO_INPUT_PORT;
    BYTE ucDpMacTxInputPixelMode = _1_PIXEL_MODE;

#if(_DP_SUPPORT == _ON)
    switch(enumStreamSource)
    {
        case _DP_TX_SOURCE_CLONE:

            enumDpLaneCount = ScalerDpStreamGetRxLaneCount(_STREAM_CLONE);
            enumDpCodingType = ScalerDpStreamGetRxCodingType(_STREAM_CLONE);
            ucDpMacTxStreamType = ScalerDpMacTxGetStreamDataPathType();
            enumDpMacTxInputPort = GET_DP_MAC_TX_CLONE_INPUT_PORT();
            break;

#if(_DP_MST_SUPPORT == _ON)
        case _DP_TX_SOURCE_MST:

            enumDpLaneCount = ScalerDpAuxRxGetLaneCount(GET_DP_RX_MAIN_PORT());

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
            enumDpCodingType = ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT());
#endif
            ucDpMacTxStreamType = _DATA_PATH_MST2MST;
            enumDpMacTxInputPort = GET_DP_RX_MAIN_PORT();
            break;

        case _DP_TX_SOURCE_MST2SST:

            enumDpLaneCount = ScalerDpStreamGetRxLaneCount(_STREAM_MST2SST);
            enumDpCodingType = ScalerDpStreamGetRxCodingType(_STREAM_MST2SST);
            ucDpMacTxStreamType = ScalerDpMacTxGetStreamDataPathType();
            enumDpMacTxInputPort = GET_DP_RX_MAIN_PORT();
            break;
#endif
        default:
            break;
    }
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        // Set Tx Input Pixel Mode
        ucDpMacTxInputPixelMode = ScalerDpMacTxGetInputPixelMode(enumDpMacTxInputPort);
    }
    else
#endif
    {
        ucDpMacTxInputPixelMode = _2_PIXEL_MODE;
    }

    // Set Rx Lane Count
    SET_DP_MAC_TX_INPUT_LANE_COUNT(enumDpLaneCount);

    // Set Rx Channel Coding Type
    SET_DP_MAC_TX_INPUT_CHANNEL_CODING(enumDpCodingType);

    // Set Tx Input Data Path Type
    SET_DP_TX_STREAM_DATA_PATH_TYPE(ucDpMacTxStreamType);

    // Set Tx Input Port
    SET_DP_MAC_TX_INPUT_PORT(enumDpMacTxInputPort);

    // Set Tx Input Pixel Mode
    SET_DP_MAC_TX_INPUT_PIXEL_MODE(ucDpMacTxInputPixelMode);
}

//--------------------------------------------------
// Description  : Get Tx Get Link Bw
// Input Value  : None
// Output Value : WORD
//--------------------------------------------------
WORD ScalerDpMacTxGetLinkBw(void)
{
    WORD usLinkRateBw = 0;

    //////////////////////////////////////////////////////////////////////////////////////
    // Link Rate BW By Pixel Unit Formular:                                             //
    // 270M * Link rate (RBR/HBR/HBR2/HBR3 Parameters) * Lane Count * 8 / 10 / 24 * 10  //
    // After Simply: Link rate (RBR/HBR/HBR2/HBR3 Parameters) * Lane Count * 90         //
    //////////////////////////////////////////////////////////////////////////////////////

    // Unit 0.1M
    usLinkRateBw = (WORD)90 * GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() * GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM();

    DebugMessageDpTx("DP Tx0 LT Link Rate BW", usLinkRateBw / 10);

    return usLinkRateBw;
}

//--------------------------------------------------
// Description  : Handle Tx Sink Count
// Input Value  : DP Tx Input Source
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSinkCountProc(void)
{
    CLR_DP_MAC_TX_DOWNSTREAM_SINK_COUNT_CHANGE();

    // Check Tx Port Sink Count Change
    if(GET_DP_MAC_TX_DOWNSTREAM_PRE_SINK_COUNT() != GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT())
    {
        SET_DP_MAC_TX_DOWNSTREAM_SINK_COUNT_CHANGE();

        if(GET_DP_MAC_TX_DOWNSTREAM_PRE_SINK_COUNT() == 0)
        {
            if(GET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE() == _TRUE)
            {
                CLR_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();
            }

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpMstTxSetCsnEvent(GET_DP_RX_MAIN_PORT(), _CONNECT_STATUS_PLUG);

#if(_DP_MST_TX_PLUG_CSN_DEBOUNCE_SUPPORT == _ON)
            SET_DP_MST_TX_PLUG_CSN_DEBOUNCING();
            ScalerTimerActiveTimerEvent(_DP_MST_TX_PLUG_CSN_DEBOUNCE_TIME, _SCALER_TIMER_EVENT_DP_TX_PLUG_CSN_DEBOUNCING);
#endif

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
            ScalerDpMstRxVirtualDpInitial(GET_DP_RX_MAIN_PORT(), ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT));
#endif
#endif

            DebugMessageDpTx("Dp Tx Sink Count 0 --> N", GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT());
        }
        else if(GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT() == 0)
        {
#if(_DP_MST_SUPPORT == _ON)
            ScalerDpMstTxSetCsnEvent(GET_DP_RX_MAIN_PORT(), _CONNECT_STATUS_UNPLUG);

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
            ScalerDpMstRxVirtualDpInitial(GET_DP_RX_MAIN_PORT(), ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT));
#endif
#endif

            DebugMessageDpTx("Dp Tx Sink Count N --> 0", GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT());
        }

        if((GET_DP_MAC_TX_DOWNSTREAM_PRE_SINK_COUNT() != 0) && (GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT() != 0))
        {
            if(GET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE() == _TRUE)
            {
                CLR_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpMstTxSetCsnEvent(GET_DP_RX_MAIN_PORT(), _CONNECT_STATUS_UNPLUG);
                ScalerDpMstTxSetCsnEvent(GET_DP_RX_MAIN_PORT(), _CONNECT_STATUS_PLUG);

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
                ScalerDpMstRxVirtualDpInitial(GET_DP_RX_MAIN_PORT(), ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT));
#endif
#endif
            }

            DebugMessageDpTx("Dp Tx Sink Count N --> N'", GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT());
        }

        SET_DP_MAC_TX_DOWNSTREAM_PRE_SINK_COUNT(GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT());
    }
    else
    {
        if(GET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE() == _TRUE)
        {
            CLR_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpMstTxSetCsnEvent(GET_DP_RX_MAIN_PORT(), _CONNECT_STATUS_UNPLUG);
            ScalerDpMstTxSetCsnEvent(GET_DP_RX_MAIN_PORT(), _CONNECT_STATUS_PLUG);

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
            ScalerDpMstRxVirtualDpInitial(GET_DP_RX_MAIN_PORT(), ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT));
#endif
#endif

            DebugMessageDpTx("Dp Tx Sink Count No Change & Cap Change", GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT());
        }
    }
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Tx Mst Info Reset
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
void ScalerDpMacTxMstInfoReset(void)
{
    // Reset Daisy Chain Position, Source Mux, Id mapping
    ScalerDpMacTxResetDaisyStreamPositionReg();
    ScalerDpMacTxResetDaisySourceMux();
    ScalerDpMacTxResetStreamToIdMapping();

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMstTxReset128b132bTo8b10bMsaConvert();
#endif

    // Reset MST Related Status
    SET_DP_TX_LINK_PBN_PER_TIMESOLT(0);

    // Reset TX Buffer Status
    SET_DP_MST_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);

    // Update Total Received Count
    if((GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() >= GET_DP_MST_TX_RECEIVED_MSG_COUNT()) && (GET_DP_MST_TX_RECEIVED_MSG_COUNT() > 0))
    {
        SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() - GET_DP_MST_TX_RECEIVED_MSG_COUNT());
    }
    else
    {
        SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(0);
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
    }

    // Reset Tx Received Count
    SET_DP_MST_TX_RECEIVED_MSG_COUNT(0);

    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_MSG_COUNT_RESET_EVENT);

    SET_DP_MAC_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_TX_NO_DEVICE);
    SET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS(_DP_TX_MSG_NO_SUPPORT);
    CLR_DP_MST_TX_DOWN_REPLY_READ_DISABLE();

    CLR_DP_MST_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY();

    // Clear Up Req Msg Header
    CLR_DP_MST_TX_UP_REQUEST_MSG_HEADER();

    CLR_DP_MST_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE();
    CLR_DP_MST_TX_MSG_DURING_HPD_LOW_DEBOUNCE();
}

//--------------------------------------------------
// Description  : Mst Case Check Cancel Debounce
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxMstCancelDebounceCheck(void)
{
    if(GET_DP_RX_MAIN_PORT() == _NO_INPUT_PORT)
    {
        return _FALSE;
    }

#if(_HW_DP_TX_HPD_DETECT_DURING_POWER_OFF == _OFF)
    if(GET_DP_TX_POWER_STATUS() == _POWER_STATUS_OFF)
    {
        return _TRUE;
    }
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if((ScalerDpRxGetSrcMstEnable(GET_DP_RX_MAIN_PORT()) == _TRUE) && (GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B))
    {
        return _TRUE;
    }
#endif

    if((ScalerDpRxGetSrcMstEnable(GET_DP_RX_MAIN_PORT()) == _TRUE) && (GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get MSG Cap Status Change
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacTxGetUpReqEnableStatusChange(void)
{
    if(GET_DP_MAC_TX_DOWNSTREAM_INFO_READY() == _FALSE)
    {
        return _FALSE;
    }

    if(GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_NO_SUPPORT)
    {
        return _FALSE;
    }

    if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() < _DP_VERSION_1_2)
    {
        return _FALSE;
    }

    if(GET_DP_MAC_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS() == _FALSE)
    {
        if(GET_DP_RX_MAIN_PORT() == _NO_INPUT_PORT)
        {
            return _FALSE;
        }

        if(ScalerDpAuxRxGetDpcdBitInfo(GET_DP_RX_MAIN_PORT(), 0x00, 0x01, 0x11, _BIT1) == _BIT1)
        {
            return _TRUE;
        }
    }
    else
    {
        // Check if Tx is sending or waiting a MSG before clear 111h[1]
        if((GET_DP_MST_RX_GEN_DOWN_REQUEST_MSG() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE) ||
           (GET_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG() == _TRUE) || (GET_DP_MST_TX_RECEIVED_MSG_COUNT() > 0))
        {
            return _FALSE;
        }

        if(GET_DP_RX_MAIN_PORT() == _NO_INPUT_PORT)
        {
            return _TRUE;
        }

        if(ScalerDpAuxRxGetDpcdBitInfo(GET_DP_RX_MAIN_PORT(), 0x00, 0x01, 0x11, _BIT1) == 0x00)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DFP Device Mst Capability
// Input Value  :
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxGetDfpDeviceMstCapProc(void)
{
    BYTE ucMstCapInfo = 0;

    if(ScalerDpAuxTxNativeRead(0x00, 0x00, 0x21, 1, &ucMstCapInfo) == _FALSE)
    {
        return _FALSE;
    }

    if((ucMstCapInfo & _BIT0) != g_ucDpMacTxPreviousMstCapStatus)
    {
        // DFP Device Capability Change
        SET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE();
        g_ucDpMacTxPreviousMstCapStatus = (ucMstCapInfo & _BIT0);
    }

    // MST Tx Port Select From Tx0 Mapping Port
    if((ucMstCapInfo & _BIT0) == _BIT0)
    {
        SET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS(_DP_TX_MSG_SUPPORT);
    }
    else
    {
        SET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS(_DP_TX_MSG_NO_SUPPORT);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Update DFP Device MSG Cap Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxUpdateDfpDeviceMsgCapFieldStatus(void)
{
    BYTE ucDpMstCap = 0;

    if(ScalerDpAuxTxNativeRead(0x00, 0x01, 0x11, 1, &ucDpMstCap) == _TRUE)
    {
        ucDpMstCap = (ucDpMstCap & ~_BIT1) | ((!GET_DP_MAC_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS()) << 1);

        if(ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x11, 1, &ucDpMstCap) == _TRUE)
        {
            SET_DP_MAC_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS((bit)(ucDpMstCap & _BIT1));

            // Clear Payload ID Only if Downstream PID Table is Not Empty
            if((GET_DP_MAC_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS() == _TRUE) && (GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_MST) &&
               (ScalerDpAuxTxNativeRead(0x00, 0x02, 0xC1, 1, pData) == _TRUE))
            {
                if(pData[0] != 0x00)
                {
                    // Set Flag to Gen Clear ID Table Msg
                    SET_DP_MST_RX_GEN_DOWN_REQUEST_MSG(_DP_MSG_CLEAR_PAYLOAD_ID_TABLE);
                }
            }
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Dp Tx Link Config Info Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxLinkConfigInfoReset(void)
{
    SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
    SET_DP_TX_LT_PROCESSING(_FALSE);
    SET_DP_MAC_TX_DOWNSTREAM_PRE_CODING_TYPE(_CODING_TYPE_8B10B);

    CLR_DP_MAC_TX_DOWNSTREAM_TP3_SUPPORT();
    CLR_DP_MAC_TX_DOWNSTREAM_TP4_SUPPORT();
    CLR_DP_MAC_TX_DOWNSTREAM_128B132B_SUPPORT();
    CLR_DP_MAC_TX_DOWNSTREAM_UHBR10_SUPPORT();
    CLR_DP_MAC_TX_DOWNSTREAM_UHBR20_SUPPORT();
    CLR_DP_MAC_TX_DOWNSTREAM_UHBR13_5_SUPPORT();

    CLR_DP_TX_DOWNSTREAM_VSC_SDP_SUPPORT();
    CLR_DP_TX_DOWNSTREAM_SPLIT_SDP_SUPPORT();

    SET_DP_MAC_TX_DOWNSTREAM_LTTPR_EXT_WAKE_TIMEOUT(0);
    SET_DP_MAC_TX_DOWNSTREAM_SINK_EXT_WAKE_TIMEOUT(0);

#if(_DP_TX_FEC_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_FEC_DECODE_DIS_FAIL_RETRAIN);

    CLR_DP_TX_DOWNSTREAM_FEC_SUPPORT();

    // Disable MSA ECO Funtion to Avoid Over Occupied the MSA Packet When DPTx FEC ON
    ScalerSetBit(PBB_C9_ARBITER_CTRL, ~(_BIT7 | _BIT5), 0x00);
#endif

    CLR_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
    CLR_DP_TX_HDCP_DOWNSTREAM_REPEATER();
    CLR_DP_TX_HDCP_AUTH_START();
    CLR_DP_TX_HDCP_AUTH_HOLD();

    // Reset HDCP info
    ScalerDpHdcp14TxResetInfo();

    SET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS(_DP_UNPLUG);
}

//--------------------------------------------------
// Description  : Dp Tx Stream Info Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxStreamInfoReset(void)
{
    CLR_DP_MAC_TX_DOWNSTREAM_INFO_READY();

    ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_NONE);

#if(_DP_SUPPORT == _ON)
    // Clear Data Path
    ScalerDpMacTxCloneSetDataPath(_DATA_PATH_NONE);
#endif

    // Clear DPTx Input Info
    ScalerDpMacTxSyncInputInfo(_DP_TX_SOURCE_NONE);

    CLR_DP_TX_STREAM_SOURCE_CHANGE();

    // Main Link switch to IDLE Pattern
    ScalerDpMacTxMainLinkPatternSetting_8b10b(_DP_TX_OUTPUT_IDLE_PATTERN);

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacTxMainLinkPatternSetting_128b132b(_DP_TX_OUTPUT_IDLE_PATTERN);
#endif

    // Clear Sdp Split
    ScalerDpMacTxSdpSplit(_DISABLE);

    // Clear Sdp Hw Bypass
    ScalerDpMacTxSdpHwBypassSetting(_DISABLE);

    // Tx Send Sec data Reset
    ScalerDpMacTxSdpReset();

    // Phy Input Data from Tx Mac SST
    CLR_DP_MST_TX_ENABLE();

#if(_DP_TX_AUDIO_SUPPORT == _ON)
    // Set Standalong Audio
    ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_OFF);
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    // Reset DSC Pass-Through Setting
    ScalerDpMacTxDscPassThroughReset();

    CLR_DP_TX_DOWNSTREAM_DSC_SUPPORT();
    CLR_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH();
    CLR_DP_TX_DOWNSTREAM_DSC_DETECT_PASSTHROUGH();
    CLR_DP_TX_DOWNSTREAM_DSC_DETECT_ENABLE();
    SET_DP_TX_DSC_PASSTHROUGH_TYPE(_SOURCE_PASSTHROUGH_DSC_BY_NONE);
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
    CLR_DP_MAC_MST2SST_DETECT_DSC_DECODE_ENABLE();
    CLR_DP_MAC_MST2SST_DSC_DECODE_ENABLE();
#endif

    // Disable Reorder Tracking Mode Setting
    ScalerDpMacTxReorderReset();

    CLR_DP_MAC_TX_DOWNSTREAM_420_SUPPORT();
}

//--------------------------------------------------
// Description  : Dp Tx Cap Info Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxCapInfoReset(void)
{
    // Reset Dfp Device Cap Backup info for Replug Compare
    memset(g_pucDpMacTxPreviousDfpDeviceCap, 0, 16);
    memset(g_pucDpMacTxPreviousDfpDeviceExtendCap, 0, 16);

#if(_DFP_SINK_EDID_CHANGE_CHECK_METHOD == _EDID_SHA_CODE)
    memset(g_pucDpMacTxPreviousDfpDeviceEdidSha1, 0, _DP_TX_EDID_SHA1_VALUE_SIZE_MAX);
#else
    memset(g_pucDpMacTxPreviousDfpDeviceEdidBackup, 0, _DP_TX_EDID_SIZE_MAX);
#endif

    g_ucDpMacTxPreviousMstCapStatus = 0;
    g_ucDpMacTxPreviousFecCapStatus = 0;
    g_ucDpMacTxPreviousDscCapStatus = 0;
    g_ucDpMacTxPreviousVscSdpCapStatus = 0;
}

//--------------------------------------------------
// Description  : DP Tx Sdp Packet Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpHandler(void)
{
    if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE) || (GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST))
    {
        switch(GET_DP_TX_STREAM_DATA_PATH_TYPE())
        {
            case _DATA_PATH_VESA:
            case _DATA_PATH_DSC_DECODER:
#if(_DP_SUPPORT == _ON)
#if(_DP_HDR10_SUPPORT == _ON)
                ScalerDpMacTxSdpHdrHandler();
#endif

#if(_DP_TX_AUDIO_SUPPORT == _ON)
                ScalerDpMacTxSdpAudioHandler();
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
                ScalerDpMacTxSdpFreeSyncHandler();
#endif

#if(_ADAPTIVESYNC_SUPPORT == _ON)
                ScalerDpMacTxSdpAdaptiveSyncHandler();
#endif
#endif
                ScalerDpMacTxColorimetryChangeHandler();

                break;

            case _DATA_PATH_VIDEO_REORDER:
            case _DATA_PATH_DSC_REORDER:

                ScalerDpMacTxColorimetryChangeHandler();

                break;

            default:

                ScalerDpMacTxSdpReset();

                break;
        }
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE)
    {
        ScalerDpMacTxSdpReset();
    }
}

#if(_DP_SUPPORT == _ON)
#if(_DP_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx HDR Setting
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSdpHdrHandler(void)
{
    EnumDpMacRxSdpChangeEvent enumDpTxSdpEvent = _SDP_EVENT_NONE;

    if(GET_DP_TX_HDR_INFOFRAME_RECEIVED() == _TRUE)
    {
        if(ScalerDpMacTxSdpSendEnableCheck(_SDP_INFOFRAME_HDR_EN) == _FALSE)
        {
            enumDpTxSdpEvent = _SDP_EVENT_HEADER_CHANGE;
        }
        else
        {
            if(GET_DP_TX_HDR_INFOFRAME_CHANGE() == _TRUE)
            {
                enumDpTxSdpEvent = GET_DP_TX_HDR_INFOFRAME_CHANGE_EVENT();
            }
        }
    }
    else
    {
        if(ScalerDpMacTxSdpSendEnableCheck(_SDP_INFOFRAME_HDR_EN) == _TRUE)
        {
            ScalerDpMacTxSdpSendEnableSwitch(_SDP_INFOFRAME_HDR_EN, _DISABLE);
        }
    }

    switch(enumDpTxSdpEvent)
    {
        case _SDP_EVENT_HEADER_CHANGE:

            if(ScalerDpMacTxSdpWaitUpdateSafeRegion() == _SUCCESS)
            {
                ScalerDpMacTxSdpSetHeaderByte(_SEC_PACKET_TYPE_INFOFRAME_HDR, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);
                ScalerDpMacTxSdpSetDataByte(_SEC_PACKET_TYPE_INFOFRAME_HDR, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);

                ScalerDpMacTxSdpSendEnableSwitch(_SDP_INFOFRAME_HDR_EN, _ENABLE);
            }

            break;

        case _SDP_EVENT_DATA_CHANGE:

            ScalerDpMacTxSdpSetDataByte(_SEC_PACKET_TYPE_INFOFRAME_HDR, _DP_TX_SDP_DBUF_WAIT_FOR_VBLANK_RISING);

            break;

        default:
            break;
    }
}
#endif

#if(_DP_TX_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Sdp Audio Handler
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSdpAudioHandler(void)
{
    EnumDpMacRxSdpChangeEvent enumDpTxSdpEvent = _SDP_EVENT_NONE;

    if(GET_DP_TX_AUDIO_INFOFRAME_RECEIVED() == _TRUE)
    {
        if(ScalerDpMacTxSdpSendEnableCheck(_SDP_INFOFRAME_AUDIO_EN) == _FALSE)
        {
            enumDpTxSdpEvent = _SDP_EVENT_HEADER_CHANGE;
        }
        else
        {
            if(GET_DP_TX_AUDIO_INFOFRAME_CHANGE() == _TRUE)
            {
                enumDpTxSdpEvent = GET_DP_TX_AUDIO_INFOFRAME_CHANGE_EVENT();
            }
        }
    }
    else
    {
        if(ScalerDpMacTxSdpSendEnableCheck(_SDP_INFOFRAME_AUDIO_EN) == _TRUE)
        {
            ScalerDpMacTxSdpSendEnableSwitch(_SDP_INFOFRAME_AUDIO_EN, _DISABLE);
        }
    }

    switch(enumDpTxSdpEvent)
    {
        case _SDP_EVENT_HEADER_CHANGE:

            if(ScalerDpMacTxSdpWaitUpdateSafeRegion() == _SUCCESS)
            {
                ScalerDpMacTxSdpSetHeaderByte(_SEC_PACKET_TYPE_INFOFRAME_AUDIO, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);
                ScalerDpMacTxSdpSetDataByte(_SEC_PACKET_TYPE_INFOFRAME_AUDIO, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);

                ScalerDpMacTxSdpSendEnableSwitch(_SDP_INFOFRAME_AUDIO_EN, _ENABLE);
            }

            break;

        case _SDP_EVENT_DATA_CHANGE:

            ScalerDpMacTxSdpSetDataByte(_SEC_PACKET_TYPE_INFOFRAME_AUDIO, _DP_TX_SDP_DBUF_WAIT_FOR_VBLANK_RISING);

            break;

        default:
            break;
    }
}
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Tx FreeSync Setting
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSdpFreeSyncHandler(void)
{
    EnumDpMacRxSdpChangeEvent enumDpTxSdpEvent = _SDP_EVENT_NONE;

    if(GET_DP_TX_SPD_INFOFRAME_RECEIVED() == _TRUE)
    {
        if(ScalerDpMacTxSdpSendEnableCheck(_SDP_INFOFRAME_FREESYNC_EN) == _FALSE)
        {
            enumDpTxSdpEvent = _SDP_EVENT_HEADER_CHANGE;
        }
        else
        {
            if(GET_DP_TX_SPD_INFOFRAME_CHANGE() == _TRUE)
            {
                enumDpTxSdpEvent = GET_DP_TX_SPD_INFOFRAME_CHANGE_EVENT();
            }
        }
    }
    else
    {
        if(ScalerDpMacTxSdpSendEnableCheck(_SDP_INFOFRAME_FREESYNC_EN) == _TRUE)
        {
            ScalerDpMacTxSdpSendEnableSwitch(_SDP_INFOFRAME_FREESYNC_EN, _DISABLE);
        }
    }

    switch(enumDpTxSdpEvent)
    {
        case _SDP_EVENT_HEADER_CHANGE:

            if(ScalerDpMacTxSdpWaitUpdateSafeRegion() == _SUCCESS)
            {
                ScalerDpMacTxSdpSetHeaderByte(_SEC_PACKET_TYPE_INFOFRAME_FREESYNC, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);
                ScalerDpMacTxSdpSetDataByte(_SEC_PACKET_TYPE_INFOFRAME_FREESYNC, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);

                ScalerDpMacTxSdpSendEnableSwitch(_SDP_INFOFRAME_FREESYNC_EN, _ENABLE);
            }

            break;

        case _SDP_EVENT_DATA_CHANGE:

            ScalerDpMacTxSdpSetDataByte(_SEC_PACKET_TYPE_INFOFRAME_FREESYNC, _DP_TX_SDP_DBUF_WAIT_FOR_VBLANK_RISING);

            break;

        default:
            break;
    }
}
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx AdaptiveSync SDP Bypass Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpAdaptiveSyncHandler(void)
{
    // DP20 TX(DP20 SST DP20 SST)           ->  0x2C00 0x2C5A 0x2C91 0x2C92
    // DP14 TX(DP20/DP14 MST/SST DP14 SST)  ->  0xBC00 0xBC5A 0xBC26 0xBC29

    if(GET_DP_TX_ADAPTIVESYNC_RECEIVED() == _TRUE)
    {
        if(GET_DP_TX_ADAPTIVESYNC_CHANGE() == _TRUE)
        {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
            {
                // HB Setting
                ScalerSetByte(P2C_91_AS_SDP_BYPASS_0, 0x00);
                ScalerSetByte(P2C_92_AS_SDP_BYPASS_1, 0x22);

                // Enable DP20 TX Transmit: Use Infoframe AVI Transimission Circuit
                ScalerSetBit(P2C_00_SEC_FUNCTION_CTRL, ~_BIT4, _BIT4);
                ScalerSetBit(P2C_5A_ADAPT_SYNC, ~_BIT0, _BIT0);
            }
            else
#endif
            {
                // HB Setting
                ScalerSetByte(PBC_26_SEC_INFO_AUD_DB0, 0x00);
                ScalerSetByte(PBC_29_SEC_INFO_AUD_DB3, 0x22);

                // Enable DP14 TX Transmit: Use Infoframe AVI Transimission Circuit
                ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~_BIT4, _BIT4);
                ScalerSetBit(PBC_5A_RESERVED_5A, ~_BIT0, _BIT0);
            }
        }
    }
    else
    {
        if(ScalerDpMacTxSdpSendEnableCheck(_SDP_ADAPTIVESYNC_EN) == _TRUE)
        {
            ScalerDpMacTxSdpSendEnableSwitch(_SDP_ADAPTIVESYNC_EN, _DISABLE);
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Dp Tx Infoframe Receive Check
// Input Value  : None
// Output Value : _TRUE: Receive, _FALSE: Non-receive
//--------------------------------------------------
bit ScalerDpMacTxSdpInfoRevStateCheck(EnumDpSdpType enumDpSdpType)
{
    EnumDpMacStreamSourceType enumDpStreamSourceType = _STREAM_SOURCE_NONE;

    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        enumDpStreamSourceType = ScalerDpRxGetMacStreamSourceType(ScalerDpRxGetMacSwitch(GET_DP_MAC_TX_CLONE_INPUT_PORT()));

        if(ScalerDpMacTxCloneModeSdpInfoRevCheck(enumDpSdpType) == _FALSE)
        {
            return _FALSE;
        }
    }
#if(_DP_MST_SUPPORT == _ON)
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        enumDpStreamSourceType = _STREAM_SOURCE_MST2SST;
    }
#endif

    return ScalerDpMacStreamRxGetSdpReceived(enumDpStreamSourceType, enumDpSdpType);
}

//--------------------------------------------------
// Description  : Dp Tx Infoframe Change Check
// Input Value  : SDP Type
// Output Value : _TRUE: Change, _FALSE: Non-Change
//--------------------------------------------------
bit ScalerDpMacTxSdpInfoChgCheck(EnumDpSdpType enumDpSdpType)
{
    EnumDpMacStreamSourceType enumDpStreamSourceType = _STREAM_SOURCE_NONE;

    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        enumDpStreamSourceType = ScalerDpRxGetMacStreamSourceType(ScalerDpRxGetMacSwitch(GET_DP_MAC_TX_CLONE_INPUT_PORT()));

        if(ScalerDpMacTxCloneModeSdpInfoRevCheck(enumDpSdpType) == _FALSE)
        {
            return _FALSE;
        }
    }
#if(_DP_MST_SUPPORT == _ON)
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        enumDpStreamSourceType = _STREAM_SOURCE_MST2SST;
    }
#endif

    return ScalerDpMacStreamRxGetSdpChanged(enumDpStreamSourceType, enumDpSdpType);
}

//--------------------------------------------------
// Description  : Dp Tx Infoframe Change Check
// Input Value  : SDP Type
// Output Value : _TRUE: Change, _FALSE: Non-Change
//--------------------------------------------------
EnumDpMacRxSdpChangeEvent ScalerDpMacTxSdpInfoChgEventCheck(EnumDpSdpType enumDpSdpType)
{
    EnumDpMacStreamSourceType enumDpStreamSourceType = _STREAM_SOURCE_NONE;

    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        enumDpStreamSourceType = ScalerDpRxGetMacStreamSourceType(ScalerDpRxGetMacSwitch(GET_DP_MAC_TX_CLONE_INPUT_PORT()));
    }
#if(_DP_MST_SUPPORT == _ON)
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        enumDpStreamSourceType = _STREAM_SOURCE_MST2SST;
    }
#endif

    return ScalerDpMacStreamRxGetSdpChangeEvent(enumDpStreamSourceType, enumDpSdpType);
}
#endif

//--------------------------------------------------
// Description  : Get HDCP TX Encrypt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacTxHdcpGetEncryptStatus(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
    {
        return (ScalerGetBit(P2B_48_DPTX_HDCP_CTRL1, _BIT1) == _BIT1);
    }
    else
#endif
    {
        return (ScalerGetBit(PBB_30_DPTX_HDCP_CTRL1, _BIT1) == _BIT1);
    }
}

//--------------------------------------------------
// Description  : DP Tx Colorimetry Change Handler
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxColorimetryChangeHandler(void)
{
    bit bUpdate = _FALSE;

    //===========================================================================================
    // 0. Check Change & Prepare Updated Data
    //===========================================================================================
    // Check Colorimetry Changed
    if(GET_DP_TX_DIGITAL_COLORIMETRY_CHANGED() == _TRUE)
    {
        bUpdate = _TRUE;

        DebugMessageDpTx("DP Tx Colorimetry change!!", 0);

        SET_DP_TX_INPUT_COLORIMETRY_CHANGED_VALUE();
    }

    // Check Quantization Range Changed
    if(GET_DP_TX_DIGITAL_QUANTIZATION_CHANGED() == _TRUE)
    {
        bUpdate = _TRUE;

        DebugMessageDpTx("DP Tx Quantization Range change!!", 0);

        SET_DP_TX_INPUT_QUANTIZATION_CHANGED_VALUE();
    }

    //===========================================================================================
    // 1. Update Values at Safe Region (after V_Active Rising Edge)
    //===========================================================================================
    if(bUpdate == _TRUE)
    {
        // Wait for Safe Region to Write SDP Content into HW Buffer
        if(ScalerDpMacTxSdpWaitUpdateSafeRegion() == _FAIL)
        {
            DebugMessageDpTx("DP Tx Non-Safe Region to Update SDP!!!!!!", 0);

            return;
        }

        // Update MSA & VSC SDP (Only for Colorimetry or Quantization Range Changed)
        if((GET_DP_TX_DIGITAL_COLORIMETRY_CHANGED() == _TRUE) || (GET_DP_TX_DIGITAL_QUANTIZATION_CHANGED() == _TRUE))
        {
            CLR_DP_TX_DIGITAL_COLORIMETRY_CHANGED();
            CLR_DP_TX_DIGITAL_QUANTIZATION_CHANGED();
            SET_DP_MAC_TX_SEC_COLOR_FIRST_APPLYED_DONE();

            ScalerDpMacTxMsaMiscSetting();

            if(GET_DP_TX_VSC_SDP_SEND_ENABLE() == _TRUE)
            {
                ScalerDpMacTxVscSdpSetting();
            }
            else
            {
                // Clear MISC1[6] to indicate VSC SDP is NOT used
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
                {
                    ScalerSetBit(P2B_AA_MN_STRM_ATTR_MISC1, ~_BIT6, 0x00);
                }
                else
#endif
                {
                    ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT6, 0x00);
                }
            }
        }
    }

    //===========================================================================================
    // 2. Set SEC Function Control & Check If Effective
    //===========================================================================================
    if(ScalerDpMacTxSdpSendEnableCheck(_SDP_VSC_EN) != GET_DP_TX_VSC_SDP_SEND_ENABLE())
    {
        if(GET_DP_TX_VSC_SDP_SEND_ENABLE() == _TRUE)
        {
            // Set VSC SDP Send Enable
            ScalerDpMacTxSdpSendEnableSwitch(_SDP_VSC_EN, _ENABLE);

            if(ScalerDpMacTxSdpVscEnable() == _TRUE)
            {
                // Set MISC1[6] to indicate VSC SDP is used and ignoring the info in MSA
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
                {
                    ScalerSetBit(P2B_AA_MN_STRM_ATTR_MISC1, ~_BIT6, _BIT6);
                }
                else
#endif
                {
                    ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT6, _BIT6);
                }
            }
        }
        else
        {
            // Set VSC SDP Send Disable
            ScalerDpMacTxSdpSendEnableSwitch(_SDP_VSC_EN, _DISABLE);
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Digital Colorimetry Change Check
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxDigitalColorimetryChangeCheck(void)
{
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
#if(_DP_SUPPORT == _ON)
        return (ScalerDpMacStreamRxGetColorimetryChange(_STREAM_SOURCE_MST2SST) ||
                ScalerDpMacStreamRxGetColorimetryExtChange(_STREAM_SOURCE_MST2SST));
#endif
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        switch(ScalerDpMacTxCloneGetCurrentInputPort())
        {
#if(_D0_DP_SUPPORT == _ON)
            case _D0_INPUT_PORT:
                return (ScalerDpMacStreamRxGetColorimetryChange(_STREAM_SOURCE_D0_DP) ||
                        ScalerDpMacStreamRxGetColorimetryExtChange(_STREAM_SOURCE_D0_DP));
#endif

#if(_D1_DP_SUPPORT == _ON)
            case _D1_INPUT_PORT:
                return (ScalerDpMacStreamRxGetColorimetryChange(_STREAM_SOURCE_D1_DP) ||
                        ScalerDpMacStreamRxGetColorimetryExtChange(_STREAM_SOURCE_D1_DP));
#endif

#if(_D2_DP_SUPPORT == _ON)
            case _D2_INPUT_PORT:
                return (ScalerDpMacStreamRxGetColorimetryChange(_STREAM_SOURCE_D2_DP) ||
                        ScalerDpMacStreamRxGetColorimetryExtChange(_STREAM_SOURCE_D2_DP));
#endif

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
            case _D3_INPUT_PORT:
                return (GET_RX3_COLORIMETRY_CHANGED() ||
                        GET_RX3_COLORIMETRY_EXT_CHANGED());
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
            case _D4_INPUT_PORT:
                return (GET_RX4_COLORIMETRY_CHANGED() ||
                        GET_RX4_COLORIMETRY_EXT_CHANGED());
#endif

            default:
                return _FALSE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Set Digital Colorimetry Change Value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetColorimetryChangeValue(void)
{
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        return;
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        EnumInputPort enumInputPort = ScalerDpMacTxCloneGetCurrentInputPort();

        if(enumInputPort != _NO_INPUT_PORT)
        {
            if(ScalerDpMacTxNewComponentModeAvailable() == _FALSE)
            {
                if(GET_DP_TX_DOWNSTREAM_VSC_SDP_SUPPORT() == _TRUE)
                {
                    switch(GET_COLORIMETRY(enumInputPort))
                    {
                        // Set Tx Colorimetry to VSC SDP Format for XRGB, SCRGB, DCI_P3, COLOR_PROFILE
                        case _COLORIMETRY_RGB_XRRGB:
                            SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_EXT);
                            SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_XRRGB);
                            break;

                        case _COLORIMETRY_RGB_SCRGB:
                            SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_EXT);
                            SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_SCRGB);
                            break;

                        case _COLORIMETRY_RGB_DCI_P3:
                            SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_EXT);
                            SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_DCI_P3);
                            break;

                        case _COLORIMETRY_RGB_COLOR_PROFILE:

                            SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_EXT);
                            SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE);
                            break;

                        default:
                            // Set Colorimetry
                            SET_DP_TX_INPUT_COLORIMETRY(GET_COLORIMETRY(enumInputPort));

                            // Set Ext Colorimetry
                            SET_DP_TX_INPUT_EXT_COLORIMETRY(GET_EXT_COLORIMETRY(enumInputPort));
                            break;
                    }
                }
                else
                {
                    SET_DP_TX_INPUT_COLORIMETRY(GET_COLORIMETRY(enumInputPort));
                    SET_DP_TX_INPUT_EXT_COLORIMETRY(GET_EXT_COLORIMETRY(enumInputPort));
                }
            }
            else
            {
                SET_DP_TX_INPUT_COLORIMETRY(GET_COLORIMETRY(enumInputPort));
                SET_DP_TX_INPUT_EXT_COLORIMETRY(GET_EXT_COLORIMETRY(enumInputPort));
            }
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Digital Quantization Change Check
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxDigitalQuantizationChangeCheck(void)
{
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        return GET_DP_TX_INPUT_DIGITAL_QUANTIZATION_CHANGED();
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        switch(ScalerDpMacTxCloneGetCurrentInputPort())
        {
#if(_D0_DP_SUPPORT == _ON)
            case _D0_INPUT_PORT:
                return ScalerDpMacStreamRxGetQuantizationChange(_STREAM_SOURCE_D0_DP);
#endif

#if(_D1_DP_SUPPORT == _ON)
            case _D1_INPUT_PORT:
                return ScalerDpMacStreamRxGetQuantizationChange(_STREAM_SOURCE_D1_DP);
#endif

#if(_D2_DP_SUPPORT == _ON)
            case _D2_INPUT_PORT:
                return ScalerDpMacStreamRxGetQuantizationChange(_STREAM_SOURCE_D2_DP);
#endif

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
            case _D3_INPUT_PORT:
                return (GET_RX3_QUANTIZATION_CHANGED());
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
            case _D4_INPUT_PORT:
                return (GET_RX4_QUANTIZATION_CHANGED());
#endif

            default:
                return _FALSE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Set Digital Quantization Change Value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetQuantizationChangeValue(void)
{
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        return;
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        EnumInputPort enumInputPort = ScalerDpMacTxCloneGetCurrentInputPort();

        if(enumInputPort != _NO_INPUT_PORT)
        {
            SET_DP_TX_INPUT_COLOR_RGB_QUANTIZATION_RANGE(GET_COLOR_RGB_QUANTIZATION_RANGE(enumInputPort));
            SET_DP_TX_INPUT_COLOR_YCC_QUANTIZATION_RANGE(GET_COLOR_YCC_QUANTIZATION_RANGE(enumInputPort));
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Clear Digital Colorimetry Change
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxColorimetryChangeFlagClear(void)
{
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
#if(_DP_SUPPORT == _ON)
        ScalerDpMacStreamRxClrColorimetryChange(_STREAM_SOURCE_MST2SST);
        ScalerDpMacStreamRxClrColorimetryExtChange(_STREAM_SOURCE_MST2SST);
#endif
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        switch(ScalerDpMacTxCloneGetCurrentInputPort())
        {
#if(_D0_DP_SUPPORT == _ON)
            case _D0_INPUT_PORT:

                ScalerDpMacStreamRxClrColorimetryChange(_STREAM_SOURCE_D0_DP);
                ScalerDpMacStreamRxClrColorimetryExtChange(_STREAM_SOURCE_D0_DP);

                break;
#endif

#if(_D1_DP_SUPPORT == _ON)
            case _D1_INPUT_PORT:

                ScalerDpMacStreamRxClrColorimetryChange(_STREAM_SOURCE_D1_DP);
                ScalerDpMacStreamRxClrColorimetryExtChange(_STREAM_SOURCE_D1_DP);

                break;
#endif

#if(_D2_DP_SUPPORT == _ON)
            case _D2_INPUT_PORT:

                ScalerDpMacStreamRxClrColorimetryChange(_STREAM_SOURCE_D2_DP);
                ScalerDpMacStreamRxClrColorimetryExtChange(_STREAM_SOURCE_D2_DP);

                break;
#endif

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
            case _D3_INPUT_PORT:

                CLR_RX3_COLORIMETRY_CHANGED();
                CLR_RX3_COLORIMETRY_EXT_CHANGED();

                break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
            case _D4_INPUT_PORT:

                CLR_RX4_COLORIMETRY_CHANGED();
                CLR_RX4_COLORIMETRY_EXT_CHANGED();

                break;
#endif

            default:

                break;
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Clear Quantization Colorimetry Change
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxQuantizationChangeFlagClear(void)
{
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        CLR_DP_TX_INPUT_DIGITAL_QUANTIZATION_CHANGED();
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        switch(ScalerDpMacTxCloneGetCurrentInputPort())
        {
#if(_D0_DP_SUPPORT == _ON)
            case _D0_INPUT_PORT:

                ScalerDpMacStreamRxClrQuantizationChange(_STREAM_SOURCE_D0_DP);

                break;
#endif

#if(_D1_DP_SUPPORT == _ON)
            case _D1_INPUT_PORT:

                ScalerDpMacStreamRxClrQuantizationChange(_STREAM_SOURCE_D1_DP);

                break;
#endif

#if(_D2_DP_SUPPORT == _ON)
            case _D2_INPUT_PORT:

                ScalerDpMacStreamRxClrQuantizationChange(_STREAM_SOURCE_D2_DP);

                break;
#endif

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
            case _D3_INPUT_PORT:

                CLR_RX3_QUANTIZATION_CHANGED();

                break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
            case _D4_INPUT_PORT:

                CLR_RX4_QUANTIZATION_CHANGED();

                break;
#endif

            default:

                break;
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Polling SEC VSC Enable Flag
// Input Value  :
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxSdpVscEnable(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return ((ScalerGetByte(P2C_00_SEC_FUNCTION_CTRL) & _SDP_VSC_EN) == _SDP_VSC_EN);
    }
    else
#endif
    {
        // Polling for double buffer active
        return ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, PBC_00_SEC_FUNCTION_CTRL, _SDP_VSC_EN, _TRUE);
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Sdp Split enable
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSdpSplit(bit bEnable)
{
    if(bEnable == _TRUE)
    {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
        {
            if(ScalerGetBit(P2C_95_DUMMY_95, _BIT3) != _BIT3)
            {
                ScalerSetBit(P2C_95_DUMMY_95, ~_BIT3, _BIT3);
            }
        }
        else
#endif
        {
            if(ScalerGetBit(PBC_95_DUMMY_95, _BIT3) != _BIT3)
            {
                ScalerSetBit(PBC_95_DUMMY_95, ~_BIT3, _BIT3);
            }
        }
    }
    else
    {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerSetBit(P2C_95_DUMMY_95, ~_BIT3, 0x00);
#endif

        ScalerSetBit(PBC_95_DUMMY_95, ~_BIT3, 0x00);
    }
}

//--------------------------------------------------
// Description  : Update SDP Content
// Input Value  : None
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerDpMacTxSdpWaitUpdateSafeRegion(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        if(ScalerDpMacTxPollingFlagAfterSetProc(_DP_ONE_FRAME_TIME_MAX, P2B_D0_ARBITER_DEBUG, _BIT3, _BIT3, _FALSE) == _TRUE)
        {
            ScalerSetByte(P2B_D0_ARBITER_DEBUG, _BIT3);

            if(ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, P2B_D0_ARBITER_DEBUG, _BIT3, _TRUE) == _TRUE)
            {
                return _SUCCESS;
            }
        }
    }
    else
#endif
    {
        if(ScalerDpMacTxPollingFlagAfterSetProc(_DP_ONE_FRAME_TIME_MAX, PBB_D6_ARBITER_DEBUG, _BIT3, _BIT3, _FALSE) == _TRUE)
        {
            ScalerSetByte(PBB_D6_ARBITER_DEBUG, _BIT3);

            if(ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, PBB_D6_ARBITER_DEBUG, _BIT3, _TRUE) == _TRUE)
            {
                return _SUCCESS;
            }
        }
    }

    return _FAIL;
}

//----------------------------------------------------------------------
// Description  : Polling Scaler Flag Process
// Input Value  : usTimeout --> Timeout number (Max: 65,535 ms)
//                usRegister--> Current Register
//                ucSetValue--> Value Set Before Polling The Flag
//                ucBit     --> Polling Bit
//                bSuccess  --> 1 or 0 when finished for Polling Bit
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------
bit ScalerDpMacTxPollingFlagAfterSetProc(WORD usTimeout, WORD usRegister, BYTE ucSetValue, BYTE ucBit, bit bSuccess)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;

    usPreviousTime = g_usTimerCounter;

    do
    {
        ScalerSetByte(usRegister, ucSetValue);

        if(((bit)ScalerGetBit(usRegister, ucBit) ^ bSuccess) == _FALSE)
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

//--------------------------------------------------
// Description  : Dp Tx Get HDR Infoframe
// Input Value  : Sdp Type & Infodata Store Buf
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpGetInfoData(EnumDpSdpType enumDpSdpType, BYTE *pucInfoData)
{
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        ScalerDpMacTxCloneModeGetSdpPktData(ScalerDpMacTxCloneGetCurrentInputPort(), enumDpSdpType, pucInfoData);
    }
#if(_DP_MST_SUPPORT == _ON)
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        ScalerDpMacMstToSstGetSdpPktData(enumDpSdpType, pucInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);
    }
#endif
}

//--------------------------------------------------
// Description  : Dp Tx Infoframe HB3 Check
// Input Value  : SDP Type
// Output Value : HB3
//--------------------------------------------------
BYTE ScalerDpMacTxSdpInfoHB3Value(EnumDpSdpType enumDpSdpType)
{
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        return ScalerDpMacTxCloneModeSdpInfoHB3(ScalerDpMacTxCloneGetCurrentInputPort(), enumDpSdpType);
    }
#if(_DP_MST_SUPPORT == _ON)
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        return ScalerDpMacMstToSstSdpInfoHB3(enumDpSdpType);
    }
#endif

    return 0x00;
}

//--------------------------------------------------
// Description  : Dp Tx Clone Case: Infoframe Receive Check
// Input Value  : Input port, Sdp Type
// Output Value : Received Flag
//--------------------------------------------------
bit ScalerDpMacTxCloneModeSdpInfoRevCheck(EnumDpSdpType enumDpSdpType)
{
    switch(enumDpSdpType)
    {
        case _DP_SDP_TYPE_INFOFRAME_SPD:

            if(GET_DP_MAC_TX_DOWNSTREAM_MSA_IGNORED() == _FALSE)
            {
                return _FALSE;
            }

            break;

        case _DP_SDP_TYPE_INFOFRAME_HDR:

            if(GET_DP_TX_DOWNSTREAM_VSC_SDP_SUPPORT() == _FALSE)
            {
                return _FALSE;
            }

            break;

        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx Clone Case: Get SDP Infoframe Data
// Input Value  : Input port, Sdp Type, Infodata Store Buf
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxCloneModeGetSdpPktData(EnumInputPort enumInputPort, EnumDpSdpType enumDpSdpType, BYTE *pucInfoData)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
#if(_D0_DP_SUPPORT == _ON)
            ScalerDpMacStreamRxGetSdpPktData(_D0_INPUT_PORT, enumDpSdpType, pucInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);
#endif
            break;

        case _D1_INPUT_PORT:
#if(_D1_DP_SUPPORT == _ON)
            ScalerDpMacStreamRxGetSdpPktData(_D1_INPUT_PORT, enumDpSdpType, pucInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);
#endif
            break;

        case _D2_INPUT_PORT:
#if(_D2_DP_SUPPORT == _ON)
            ScalerDpMacStreamRxGetSdpPktData(_D2_INPUT_PORT, enumDpSdpType, pucInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);
#endif
            break;

        case _D3_INPUT_PORT:

            break;

        case _D4_INPUT_PORT:

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Dp Tx Clone Case: Get SDP Infoframe HB3
// Input Value  : Clone Input port, Sdp Type
// Output Value : HB3
//--------------------------------------------------
BYTE ScalerDpMacTxCloneModeSdpInfoHB3(EnumInputPort enumInputPort, EnumDpSdpType enumDpSdpType)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
#if(_D0_DP_SUPPORT == _ON)
            return ScalerDpMacStreamRxGetSdpHB3(_D0_INPUT_PORT, enumDpSdpType);
#endif
            break;

        case _D1_INPUT_PORT:
#if(_D1_DP_SUPPORT == _ON)
            return ScalerDpMacStreamRxGetSdpHB3(_D1_INPUT_PORT, enumDpSdpType);
#endif
            break;

        case _D2_INPUT_PORT:
#if(_D2_DP_SUPPORT == _ON)
            return ScalerDpMacStreamRxGetSdpHB3(_D2_INPUT_PORT, enumDpSdpType);
#endif
            break;

        case _D3_INPUT_PORT:

            break;

        case _D4_INPUT_PORT:

            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Reset Reorder Tracking Mode Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxReorderReset(void)
{
    // Disable Video Reorder Tracking Mode
    ScalerSetBit(PBB_B2_NVID_ASYNC_M, ~_BIT1, 0x00);

    // Disable FEC Ready Setting
    ScalerSetBit(PA_01_MST2SST_ASYNC_FIFO, ~(_BIT7 | _BIT3 | _BIT2), 0x00);

    // Disable DSC / Video Reorder Setting
    ScalerSetBit(PBB_F1_DSC_FEC_SETTING0, ~(_BIT7 | _BIT6 | _BIT3), 0x00);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Use Daisy Fifo Full Flag To Judge Fifo Req
    ScalerSetBit(P2F_10_CTRL_ST1_10, ~_BIT4, 0x00);
#endif
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check if DP Mac Tx Need to Do Pll Tracking
// Input Value  : EnumDPTxInputSource
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxTrackingEnableCheck(EnumDPTxInputSource enumStreamSource)
{
#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _OFF)
    if((enumStreamSource == _DP_TX_SOURCE_MST2SST) || (enumStreamSource == _DP_TX_SOURCE_CLONE))
    {
        return _FALSE;
    }
#else
    if(enumStreamSource == _DP_TX_SOURCE_MST2SST)
    {
        return _FALSE;
    }
#endif
    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx Clone / MST2SST Case: Use MST2SST PLL Circuit in Video / DSC Reorder Tracking Mode
// Input Value  : EnumDPTxInputSource
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxReorderTrackingPllSetting(EnumDPTxInputSource enumStreamSource)
{
    StructDpInfo stDpInfo;
    EnumDpMacSel enumDpMacSelMst2sst = ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST);

    if(enumStreamSource == _DP_TX_SOURCE_MST2SST)
    {
        stDpInfo = *(ScalerDpMacStreamRxGetDpInfoPointer(_STREAM_SOURCE_MST2SST));
    }
    else if(enumStreamSource == _DP_TX_SOURCE_CLONE)
    {
        EnumInputPort enumInputPort = ScalerDpMacTxCloneGetCurrentInputPort();
        stDpInfo = *(ScalerDpMacStreamRxGetDpInfoPointer(ScalerDpRxDxMacSourceMapping(enumInputPort)));
    }
    else
    {
        return _FALSE;
    }

    return ScalerDpMacStreamRxPllSettingForReorderTracking(enumDpMacSelMst2sst, &stDpInfo);
}

//--------------------------------------------------
// Description  : Get DPTX Video / DSC Reorder Tracking Mode
// Input Value  : EnumDPTxInputSource
// Output Value : DP MAC RX Tracking Source BS or BE
//--------------------------------------------------
EnumDpMacRxTrackingSource ScalerDpMacTxGetRxReorderTrackingMode(EnumDPTxInputSource enumStreamSource)
{
    EnumDpMacSel enumMacIndex = 0;

    if(enumStreamSource == _DP_TX_SOURCE_MST2SST)
    {
        enumMacIndex = ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST);
    }
    else if(enumStreamSource == _DP_TX_SOURCE_CLONE)
    {
        EnumInputPort enumInputPort = ScalerDpMacTxCloneGetCurrentInputPort();
        enumMacIndex = ScalerDpRxGetMacSwitch(enumInputPort);
    }

    return (ScalerDpMacStreamRxGetTrackingSource(enumMacIndex));
}
#endif

//--------------------------------------------------
// Description  : Handle Tx Output stream
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxForceIdlePatternSetting(void)
{
    if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
    {
        if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE)
        {
            if(ScalerDpMacTxHdcpGetEncryptStatus() == _TRUE)
            {
                ScalerDpHdcp14TxEncryptSignalProc(_DISABLE);

                ScalerTimerDelayXms(2);
            }

            // Main Link switch to IDLE Pattern
            ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_IDLE_PATTERN);

            // Tx Send Sec data Reset
            ScalerDpMacTxSdpReset();

#if(_DP_TX_AUDIO_SUPPORT == _ON)

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))
            if(GET_DP_TX_AUDIO_STAND_ALONE() == _OFF)
#endif
            {
                // Disable Audio
                ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_OFF);
            }
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
            if(GET_DP_TX_DOWNSTREAM_DSC_SUPPORT() == _ENABLE)
            {
                if(GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH() == _ENABLE)
                {
                    // Reset DSC Pass-Through Setting
                    ScalerDpMacTxDscPassThroughReset();

                    // Set DFP DSC Enable Process
                    ScalerDpMacTxDfpDscEnableProc(_DISABLE);
                }
            }
#endif
            // Disable Sdp Hw Bypass
            ScalerDpMacTxSdpHwBypassSetting(_DISABLE);

            ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_NONE);
        }
    }
}

//--------------------------------------------------
// Description  : Set DP Tx Stream Source
// Input Value  : EnumDPTxInputSource
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetStreamSource(EnumDPTxInputSource enumStreamSource)
{
    SET_DP_TX_STREAM_SOURCE(enumStreamSource);
    SET_DP_TX_STREAM_SOURCE_CHANGE();

    if(enumStreamSource == _DP_TX_SOURCE_NONE)
    {
        // Clear Tx Clone Precheck flag
        SET_DP_MAC_TX_CLONE_STREAM_PRECHECK(_FALSE);

        // Clear Exceed BW Flag for Clone Mode
        CLR_DP_TX_EXCEED_LINK_BANDWIDTH();
    }
    else
    {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
        CLR_DP_HDCP2_TX_BACKUP_CONTENT_STREAM();
#endif
    }
}
//--------------------------------------------------
// Description  : DP Tx MAC Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSSTSetting(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        // Arbiter Disable Suffing
        ScalerSetBit(P2B_C3_ARBITER_CTRL, ~(_BIT7 | _BIT0), 0x00);

        switch(GET_DP_TX_STREAM_DATA_PATH_TYPE())
        {
            case _DATA_PATH_VESA:
            case _DATA_PATH_DSC_DECODER:

                // Source Sel from Arbiter
                ScalerSetBit(P2B_D3_SOURCE_CTRL_0, ~_BIT6, _BIT6);

                // Clk from Arbiter
                ScalerSetBit(P2B_FA_DPTX20_ARIBITER, ~_BIT0, _BIT0);

                // Arbiter Enable
                ScalerSetBit(P2B_C3_ARBITER_CTRL, ~(_BIT7 | _BIT0), _BIT0);

                ScalerDpMacTxSSTSetting_128b132b();
                ScalerDpMacTxSyncTableProcess_128b132b();

                break;
            case _DATA_PATH_VIDEO_REORDER:
            case _DATA_PATH_DSC_REORDER:
                break;

            case _DATA_PATH_DSC_BYPASS:
            case _DATA_PATH_VIDEO_BYPASS:
                // Source Sel from DpRx
                ScalerSetBit(P2B_D3_SOURCE_CTRL_0, ~_BIT6, 0x00);

                // Clk from Daisy fifo
                ScalerSetBit(P2B_FA_DPTX20_ARIBITER, ~_BIT0, 0x00);

                ScalerDpMacTxSyncTableProcess_128b132b();
                break;

            default:
                break;
        }
    }
    else
#endif
    {
        switch(GET_DP_TX_STREAM_DATA_PATH_TYPE())
        {
            case _DATA_PATH_VESA:
            case _DATA_PATH_DSC_DECODER:
            case _DATA_PATH_VIDEO_REORDER:
                ScalerDpMacTxSSTSetting_8b10b();
                break;

            case _DATA_PATH_DSC_REORDER:
                ScalerDpMacTxSSTSetting_8b10b();

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
                // Set DFP DSC Enable Process
                ScalerDpMacTxDfpDscEnableProc(_ENABLE);
#endif
                break;

            case _DATA_PATH_DSC_BYPASS:
            case _DATA_PATH_VIDEO_BYPASS:
                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx MAC Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSSTSetting_8b10b(void)
{
    bit bMvidHWMode = _TRUE;
    BYTE ucCnt = 0;
    BYTE ucValidHwMvidMeaCnt = 1;
    WORD usLoopCnt = 0;
    WORD usMeasureTime = 0;
    DWORD ulHwMvidMin = 0xFFFFFFFF;
    DWORD ulHwMvidMax = 0x00000000;
    DWORD ulMvidFWCal = 0;
    DWORD ulMvidHWMeasure = 0;
    DWORD ulMvid = 0;
    DWORD ulNvid = 0x8000;

    // Mvid = Stream clk x Nvid / Link clk
    ulMvidFWCal = (DWORD)GET_DP_TX_INPUT_PIXEL_CLK() * ulNvid;
    ulMvidFWCal /= ((GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() == _ENABLE) ? (27UL * (DWORD)GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() * 9975UL / 10000UL) : (27UL * (DWORD)GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE()));

    ulMvidFWCal = ulMvidFWCal / 10 + (ulMvidFWCal % 10 > 5 ? 1 : 0);

    // Calculate HW measure Mvid period time, / 5 for get 5us times
    usMeasureTime = (WORD)(ulNvid / ((GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() == _ENABLE) ? (27UL * (DWORD)GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() * 9975UL / 10000UL) : (27UL * (DWORD)GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE())) / 5UL);
    usMeasureTime *= 2;

    // Debounce 10 times
    ucCnt = 0x0A;

    // Set Nvid for FW mode
    ScalerSetByte(PBB_AC_MN_N_VID_H, (BYTE)(ulNvid >> 16));
    ScalerSetByte(PBB_AD_MN_N_VID_M, (BYTE)(ulNvid >> 8));
    ScalerSetByte(PBB_AE_MN_N_VID_L, (BYTE)(ulNvid >> 0));

    do
    {
        --ucCnt;

        // Enable HW Mvid measure
        ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6 | _BIT0), _BIT7);

        // Delay time for one HW mvid measurement period time
        for(usLoopCnt = 0; usLoopCnt < usMeasureTime; usLoopCnt++)
        {
            DELAY_5US();
        }

        // Enable HW Mvid measure Popup
        SET_DP_TX_MNVID_HW_MEASURE_POPUP();

        // Disable HW Mvid measure
        ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6 | _BIT0), 0x00);

        ulMvidHWMeasure = (((DWORD)ScalerGetByte(PBB_AF_MVID_AUTO_H) << 16) | ((DWORD)ScalerGetByte(PBB_B0_MVID_AUTO_M) << 8) | ScalerGetByte(PBB_B1_MVID_AUTO_L));

        // For RLE0779A/RL6449A disable auto Mvid is zero
        if(ulMvidHWMeasure == 0)
        {
            // HW Auto Mvid is wrong Set Mvid for FW mode
            ScalerSetByte(PBB_A9_MN_M_VID_H, (BYTE)(ulMvidFWCal >> 16));
            ScalerSetByte(PBB_AA_MN_M_VID_M, (BYTE)(ulMvidFWCal >> 8));
            ScalerSetByte(PBB_AB_MN_M_VID_L, (BYTE)(ulMvidFWCal >> 0));

            bMvidHWMode = _FALSE;

            break;
        }

        // (abs(ulMvidFWCal - ulMvidHWMeasure) > (ulMvidFWCal >> 2)) for HW measure abnormal
        if((DWORD)abs(ulMvidFWCal - ulMvidHWMeasure) > (ulMvidFWCal >> 2))
        {
            // Drop this time measure result
            continue;
        }

        // (ulMvid != 0) for get the first time measurement result
        if(ulMvid == 0)
        {
            if(ulMvidHWMeasure < ulHwMvidMin)
            {
                ulHwMvidMin = ulMvidHWMeasure;
            }

            if(ulMvidHWMeasure > ulHwMvidMax)
            {
                ulHwMvidMax = ulMvidHWMeasure;
            }

            ulMvid = ulMvidHWMeasure;
            continue;
        }

        // (abs(ulMvidHWMeasure - ulMvid) < 0x50) for avoid get the measurement value far away from the average value
        if(abs(ulMvid - ulMvidHWMeasure * ucValidHwMvidMeaCnt) < (0x50 * (WORD)ucValidHwMvidMeaCnt))
        {
            if(ulMvidHWMeasure < ulHwMvidMin)
            {
                ulHwMvidMin = ulMvidHWMeasure;
            }

            if(ulMvidHWMeasure > ulHwMvidMax)
            {
                ulHwMvidMax = ulMvidHWMeasure;
            }

            // Accumulate every hw measure mvid
            ulMvid += ulMvidHWMeasure;

            // Record total valid hw measure times
            ucValidHwMvidMeaCnt++;
        }
    }
    while(ucCnt > 0);

    if(bMvidHWMode == _TRUE)
    {
        // Drop the min and max value of hw mvid measurement result
        if(ucValidHwMvidMeaCnt > 2)
        {
            ulMvid -= (ulHwMvidMax + ulHwMvidMin);
            ucValidHwMvidMeaCnt -= 2;

            // Calculate the hw mvid average value
            ulMvid = ((ulMvid + (ucValidHwMvidMeaCnt / 2)) / ucValidHwMvidMeaCnt);

            if((DWORD)abs(ulMvidFWCal - ulMvid) > (ulMvidFWCal >> 1))
            {
                // HW Auto Mvid is wrong Set Mvid for FW mode
                ulMvid = ulMvidFWCal;
            }
        }
        else
        {
            // HW Auto Mvid is wrong Set Mvid for FW mode
            ulMvid = ulMvidFWCal;
        }

        // Set Mvid value
        ScalerSetByte(PBB_A9_MN_M_VID_H, (BYTE)(ulMvid >> 16));
        ScalerSetByte(PBB_AA_MN_M_VID_M, (BYTE)(ulMvid >> 8));
        ScalerSetByte(PBB_AB_MN_M_VID_L, (BYTE)(ulMvid >> 0));
    }

    // Set Mvid DB Direct Effective
    ScalerSetBit(PBB_B4_MSA_CTRL, ~(_BIT7 | _BIT6), 0x00);

    // For Mvid Auto New Mode, M/N mode Measure and Generate are Independant.
    // Enable HW auto measure and send HW measure Mvid to solve the ASUS PA248 display fail
    if(GET_DP_MAC_TX_EDID_VENDOR_MODEL() == _EDID_VENDOR_ASUS_PA248)
    {
        // Enable HW Auto Measure Mvid
        ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6 | _BIT0), _BIT7);

        // Send HW Auto Measure Mvid
        SET_DP_TX_MVID_HW_MODE();
    }
    else
    {
        // Set Mvid DB for FW mode
        ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6 | _BIT0), _BIT6);

        // SET_DP_TX_MVID_FW_MODE -> FW Manually Set Mvid/Nvid
        SET_DP_TX_MVID_FW_MODE();
    }

    // MSA fill
    ScalerDpMacTxSSTMSASetting_8b10b();

    // DP Tx TU Setting
    ScalerDpMacTxSSTDisplayFormatSetting_8b10b();

    // Clear FIFO Status
    ScalerSetBit(PBB_A4_PG_FIFO_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));

#if(_DP_TX_AUDIO_SUPPORT == _ON)

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))
    if(GET_DP_TX_AUDIO_STAND_ALONE() == _ON)
    {
        // Disable Audio
        ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_OFF);
    }
#endif

    // Check Input Source Support Audio or Not
    switch(GET_DP_TX_STREAM_SOURCE())
    {
#if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)
        case _DP_TX_SOURCE_MST2SST:

            // Set up Audio Output
            ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_PRESET);

            break;

#endif // End of #if(_DP_RX_MST2SST_AUDIO_SUPPORT == _OFF)

#if(_AUDIO_SUPPORT == _ON)
        case _DP_TX_SOURCE_CLONE:

            // Set up Audio Output
            ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_PRESET);

            break;

#endif // End of #if(_AUDIO_SUPPORT == _ON)

        default:

            // Disable up Audio Output
            ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_OFF);

            break;
    }
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : DP Tx Sdp HW Bypass Setting
// Input Value  : bEnable
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSdpHwBypassSetting(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
        {
            ScalerDpMacTxSdpHwBypassSetting_128b132b(_ENABLE);
        }
        else
#endif
        {
            ScalerDpMacTxSdpHwBypassSetting_8b10b(_ENABLE);
        }
    }
    else
    {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerDpMacTxSdpHwBypassSetting_128b132b(_DISABLE);
#endif
        ScalerDpMacTxSdpHwBypassSetting_8b10b(_DISABLE);
    }
}

//--------------------------------------------------
// Description  : DP Tx SEC Data Handler
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSdpHwBypassSetting_8b10b(bit bEnable)
{
    if(bEnable == _TRUE)
    {
        // HB0 Setting
        ScalerSetByte(PBC_AC_SEC_PANEL_REPLAY_RX_HB0, 0x00);

        // HB1 Setting
#if(_DP_HDR10_SUPPORT == _ON)
        ScalerSetByte(PBC_C5_SDP_BYPASS_TYPE0, _DP_SDP_TYPE_INFOFRAME_HDR);
#endif

#if(_DP_TX_AUDIO_SUPPORT == _ON)
        ScalerSetByte(PBC_C6_SDP_BYPASS_TYPE1, _DP_SDP_TYPE_INFOFRAME_AUDIO);
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        ScalerSetByte(PBC_C7_SDP_BYPASS_TYPE2, _DP_SDP_TYPE_INFOFRAME_SPD);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        // HB Setting
        ScalerSetByte(PBC_26_SEC_INFO_AUD_DB0, 0x00);
        ScalerSetByte(PBC_29_SEC_INFO_AUD_DB3, 0x22);

        // Enable Transmit
        ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~_BIT4, _BIT4);
        ScalerSetBit(PBC_5A_RESERVED_5A, ~_BIT0, _BIT0);
#endif

        // Enable Transmit
        ScalerSetBit(PBC_01_SEC_RESERVED_0, ~_BIT3, _BIT3);

        if(ScalerDpMacTxPollingFlagAfterSetProc(_DP_ONE_FRAME_TIME_MAX, PBC_96_DUMMY_96, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | (GET_DP_TX_SDP_DECODE_TYPE() & 0x0F)), (_BIT7 | _BIT6 | _BIT5 | _BIT4), _FALSE) == _TRUE)
        {
            DebugMessageDpTx("DP1.4 SDP HW Bypass Setting Succeed", 1);
        }
    }
    else
    {
        if(ScalerGetBit(PBC_01_SEC_RESERVED_0, _BIT3) == _BIT3)
        {
            // Disable Transmit
            ScalerSetBit(PBC_01_SEC_RESERVED_0, ~_BIT3, 0x00);

            // Disable SDP bypass decode 0xBC96[7:4] -> 0x00
            pData[0] = GET_DP_TX_SDP_DECODE_TYPE();
            ScalerSetByte(PBC_96_DUMMY_96, (pData[0] & 0x0F));

            // HB0 Setting
            ScalerSetByte(PBC_AC_SEC_PANEL_REPLAY_RX_HB0, 0x00);

            // HB1 Setting
#if(_DP_HDR10_SUPPORT == _ON)
            ScalerSetByte(PBC_C5_SDP_BYPASS_TYPE0, 0x00);
#endif

#if(_DP_TX_AUDIO_SUPPORT == _ON)
            ScalerSetByte(PBC_C6_SDP_BYPASS_TYPE1, 0x00);
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
            ScalerSetByte(PBC_C7_SDP_BYPASS_TYPE2, 0x00);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
            ScalerSetBit(PBC_5A_RESERVED_5A, ~_BIT0, 0x00);
            ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~_BIT4, 0x00);
            ScalerSetByte(PBC_26_SEC_INFO_AUD_DB0, 0x00);
            ScalerSetByte(PBC_29_SEC_INFO_AUD_DB3, 0x00);
#endif
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Set Header byte for Sec Data
// Input Value  : Packet Type & Double Buff Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpSetHeaderByte(EnumDPTxSecDataPacketType enumPackettype, EnumDPTxSdpDoubleBufferType enumDoubleBufferType)
{
    BYTE pucData[4] = {0};

    // Sec Data Packet ID
    pucData[0] = 0x00;

    // Packet Type
    pucData[1] = enumPackettype;

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        // Select Packet Type
        ScalerSetBit(P2C_7B_SEC_PH_PACKET_TYPE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), pucData[1]);
    }
    else
#endif
    {
        // Select Packet Type
        ScalerSetBit(PBC_7B_SEC_PH_PACKET_TYPE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), pucData[1]);
    }

    switch(enumPackettype)
    {
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _SEC_PACKET_TYPE_PPS:

            // Picture Parameter Set
            pucData[1] = 0x10;

            // DSC Stream LSB of (Data Byte count - 1)
            pucData[2] = 0x7F;

            // Reserved
            pucData[3] = 0x00;

            break;
#endif

        case _SEC_PACKET_TYPE_AUDIO_TIMESTAMP:

            // Audio Timestamp LSB of (Data Byte count - 1)
            pucData[2] = 0x17;

            // [1:0]: Audio Timestamp MSB of (Data Byte count - 1), [7:2] DP version number
            if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
            {
                pucData[3] = (_INFOFRAME_SDP_VERSION_1_2 << 2);
            }
            else
            {
                pucData[3] = (_INFOFRAME_SDP_VERSION_1_1 << 2);
            }

            break;

        case _SEC_PACKET_TYPE_AUDIO_STREAM:

            // Reserved
            pucData[2] = 0x00;

            // [7:4]: Coding type, [2:0]: Channel count
            pucData[3] = ((BYTE) GET_DP_TX_AUDIO_CODING_TYPE() << 4) | GET_DP_TX_AUDIO_CHANNEL_COUNT();

            break;

        case _SEC_PACKET_TYPE_VSC:

            if(GET_DP_TX_INPUT_COLORIMETRY() == _COLORIMETRY_EXT)
            {
                // [4:0]: Revision number
                pucData[2] = 0x05;

                // [4:0]: Number of valid data bytes
                pucData[3] = 0x13;
            }
            else
            {
                // [4:0]: Revision number
                pucData[2] = 0x01;

                // [4:0]: Number of valid data bytes
                pucData[3] = 0x01;
            }

            break;

        case _SEC_PACKET_TYPE_INFOFRAME_AVI:
        case _SEC_PACKET_TYPE_INFOFRAME_AUDIO:

            // Set CEA-861 InfoFrame
            pucData[1] = _BIT7 | (pucData[1] & 0x07);

            // LSB of (Data Byte count - 1)
            pucData[2] = 0x1B;

            // [1:0]: MSB of (Data Byte count - 1), [7:2] DP version number
            if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
            {
                pucData[3] = (_INFOFRAME_SDP_VERSION_1_2 << 2);
            }
            else
            {
                pucData[3] = (_INFOFRAME_SDP_VERSION_1_1 << 2);
            }

            break;

#if((_DP_FREESYNC_II_SUPPORT == _ON) || (_DP_FREESYNC_SUPPORT == _ON))
        case _SEC_PACKET_TYPE_INFOFRAME_FREESYNC:

            // DP AMD SPD Info
            pucData[1] = _DP_SDP_TYPE_INFOFRAME_SPD;

            // SPD Info Header
            pucData[3] = GET_DP_TX_SPD_INFOFRAME_HB3();

            // HB3[7:2]: Infoframe Version
            if((pucData[3] >> 2) >= _INFOFRAME_SDP_VERSION_1_3)
            {
                pucData[2] = 0x1D;
            }
            else
            {
                pucData[2] = 0x1B;
            }

            break;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
        case _SEC_PACKET_TYPE_INFOFRAME_HDR:

            // HDR infoframe type
            pucData[1] = _DP_SDP_TYPE_INFOFRAME_HDR;

            // LSB of (Data Byte count - 1)
            pucData[3] = GET_DP_TX_HDR_INFOFRAME_HB3();

            // HB3[7:2]: Infoframe Version
            if((pucData[3] >> 2) >= _INFOFRAME_SDP_VERSION_1_3)
            {
                pucData[2] = 0x1D;
            }
            else
            {
                pucData[2] = 0x1B;
            }

            break;
#endif

        default:
            break;
    }

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxSdpSetHeaderByte_128b132b(pucData, enumDoubleBufferType);
    }
    else
#endif
    {
        ScalerDpMacTxSdpSetHeaderByte_8b10b(pucData, enumDoubleBufferType);
    }
}

//--------------------------------------------------
// Description  : DP Tx Set Header byte for Sec Data
// Input Value  : Packet Header
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpSetHeaderByte_8b10b(BYTE *pucData, EnumDPTxSdpDoubleBufferType enumDoubleBufferType)
{
    // Set Header Byte
    ScalerSetByte(PBC_73_SEC_PH_HB0, pucData[0]);
    ScalerSetByte(PBC_74_SEC_PH_HB1, pucData[1]);
    ScalerSetByte(PBC_75_SEC_PH_HB2, pucData[2]);
    ScalerSetByte(PBC_76_SEC_PH_HB3, pucData[3]);

    // Set Parity Byte
    ScalerSetByte(PBC_77_SEC_PH_PB0, ScalerDpMacTxSdpGetParity(pucData[0]));
    ScalerSetByte(PBC_78_SEC_PH_PB1, ScalerDpMacTxSdpGetParity(pucData[1]));
    ScalerSetByte(PBC_79_SEC_PH_PB2, ScalerDpMacTxSdpGetParity(pucData[2]));
    ScalerSetByte(PBC_7A_SEC_PH_PB3, ScalerDpMacTxSdpGetParity(pucData[3]));

    // Set Double Buffer
    ScalerSetBit(PBC_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), enumDoubleBufferType);
}

//--------------------------------------------------
// Description  : Set InfoFrame Data Bytes
// Input Value  : DP Tx Sec Data Packet Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpSetDataByte(EnumDPTxSecDataPacketType enumPackettype, EnumDPTxSdpDoubleBufferType enumDoubleBufferType)
{
    BYTE pucInfoFrameData[_HW_DP_SDP_PAYLOAD_LENGTH] = {0};
    BYTE ucLength = 0;
    EnumDPTxSdpTypeForDB enumSdpTypeSel = _SDP_DB_TYPE_NONE;

    switch(enumPackettype)
    {
#if(_DP_TX_AUDIO_SUPPORT == _ON)
        case _SEC_PACKET_TYPE_INFOFRAME_AUDIO:

            enumSdpTypeSel = _SDP_DB_TYPE_INFOFRAME_AUDIO;

            ucLength = _DP_TX_AUDIO_INFO_LENGTH;

            GET_DP_TX_AUDIO_INFOFRAME_DATA(pucInfoFrameData);

            break;
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _SEC_PACKET_TYPE_INFOFRAME_FREESYNC:

            enumSdpTypeSel = _SDP_DB_TYPE_INFOFRAME_FREESYNC;

            ucLength = _DP_TX_FREESYNC_INFO_LENGTH;

            GET_DP_TX_FREESYNC_INFOFRAME_DATA(pucInfoFrameData);

            break;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
        case _SEC_PACKET_TYPE_INFOFRAME_HDR:

            enumSdpTypeSel = _SDP_DB_TYPE_INFOFRAME_HDR;

            ucLength = _DP_TX_HDR10_INFO_LENGTH;

            GET_DP_TX_HDR_INFOFRAME_DATA(pucInfoFrameData);

            break;
#endif

        case _SEC_PACKET_TYPE_VSC:

            enumSdpTypeSel = _SDP_DB_TYPE_INFOFRAME_VSC;

            ucLength = _DP_TX_INFOFRAME_DATA_LENGTH_MAX;

            pucInfoFrameData[16] = g_pucDpMacTxVscSdpDB16to18[0];
            pucInfoFrameData[17] = g_pucDpMacTxVscSdpDB16to18[1];
            pucInfoFrameData[18] = g_pucDpMacTxVscSdpDB16to18[2];

            break;

        default:
            break;
    }

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxSdpSetDataByte_128b132b(enumSdpTypeSel, pucInfoFrameData, ucLength, enumDoubleBufferType);
    }
    else
#endif
    {
        ScalerDpMacTxSdpSetDataByte_8b10b(enumSdpTypeSel, pucInfoFrameData, ucLength, enumDoubleBufferType);
    }
}

//--------------------------------------------------
// Description  : Set InfoFrame Data Bytes
// Input Value  : EnumDPTxSecDataPacketType
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpSetDataByte_8b10b(EnumDPTxSdpTypeForDB enumSdpTypeSel, BYTE *pucInfoFrameData, BYTE ucLength, EnumDPTxSdpDoubleBufferType enumDoubleBufferType)
{
    // Set SDP Type for Data Byte Storage Area Select
    ScalerSetBit(PBC_8D_RESERVED_8D, ~(_BIT2 | _BIT1 | _BIT0), enumSdpTypeSel);

    // Initial Addr
    ScalerSetByte(PBC_8B_SEC_INFO_VSIF_ADDR_8B, 0x00);

    for(pData[0] = 0; pData[0] < ucLength; pData[0] ++)
    {
        // Write Data Bytes to The Selected Storage Area
        ScalerSetByte(PBC_8C_SEC_INFO_VSIF_DATA_8C, pucInfoFrameData[pData[0]]);
    }

    for(pData[0] = ucLength; pData[0] < _DP_TX_INFOFRAME_DATA_LENGTH_MAX; pData[0] ++)
    {
        // padding zero
        ScalerSetByte(PBC_8C_SEC_INFO_VSIF_DATA_8C, 0x00);
    }

    // Set Double Buffer
    ScalerSetBit(PBC_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), enumDoubleBufferType);
}

//--------------------------------------------------
// Description  : DP Tx Clear Header byte for Sec Data
// Input Value  : Packet Header
// Output Value : Packet Parity
//--------------------------------------------------
void ScalerDpMacTxSdpClearHeaderByte(EnumDPTxSecDataPacketType enumPackettype)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxSdpClearHeaderByte_128b132b(enumPackettype);
    }
    else
#endif
    {
        ScalerDpMacTxSdpClearHeaderByte_8b10b(enumPackettype);
    }
}

//--------------------------------------------------
// Description  : DP Tx Clear Header byte for Sec Data
// Input Value  : Packet Header
// Output Value : Packet Parity
//--------------------------------------------------
void ScalerDpMacTxSdpClearHeaderByte_8b10b(EnumDPTxSecDataPacketType enumPackettype)
{
    // Select Packet Type
    ScalerSetBit(PBC_7B_SEC_PH_PACKET_TYPE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumPackettype);

    // Set Header Byte
    ScalerSetByte(PBC_73_SEC_PH_HB0, 0x00);
    ScalerSetByte(PBC_74_SEC_PH_HB1, 0x00);
    ScalerSetByte(PBC_75_SEC_PH_HB2, 0x00);
    ScalerSetByte(PBC_76_SEC_PH_HB3, 0x00);

    // Set Parity Byte
    ScalerSetByte(PBC_77_SEC_PH_PB0, 0x00);
    ScalerSetByte(PBC_78_SEC_PH_PB1, 0x00);
    ScalerSetByte(PBC_79_SEC_PH_PB2, 0x00);
    ScalerSetByte(PBC_7A_SEC_PH_PB3, 0x00);

    // Set Double Buffer
    ScalerSetBit(PBC_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : DP Tx Sdp Info Reset
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSdpReset(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacTxSdpReset_128b132b();
#endif
    ScalerDpMacTxSdpReset_8b10b();
}

//--------------------------------------------------
// Description  : DP Tx Sdp Info Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpReset_8b10b(void)
{
    if(ScalerGetByte(PBC_00_SEC_FUNCTION_CTRL) == 0x00)
    {
        return;
    }

    // Disable Infoframe Sdp and Vsc Sdp Transmission
    ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

    // Disable Meta_cea/vesa and Pps Sdp Transmission
    ScalerSetByte(PBC_01_SEC_RESERVED_0, 0x00);

    // Set Sdp Transmission Setting(0xBC00/0xBC01) Active Immediatly
    ScalerSetBit(PBC_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);
}

//--------------------------------------------------
// Description  : DP Tx Get Parity byte for Audio Packet Header
// Input Value  : Packet Header
// Output Value : Packet Parity
//--------------------------------------------------
BYTE ScalerDpMacTxSdpGetParity(BYTE ucHeader)
{
    BYTE ucParity = 0;

    // Bit 7
    ucParity |= ((BYTE)(GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT6(ucHeader))) << 7;

    // Bit 6
    ucParity |= ((BYTE)(GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT5(ucHeader))) << 6;

    // Bit 5
    ucParity |= ((BYTE)(GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT4(ucHeader) ^ GET_DATA_BIT7(ucHeader))) << 5;

    // Bit 4
    ucParity |= ((BYTE)(GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT7(ucHeader))) << 4;

    // Bit 3
    ucParity |= ((BYTE)(GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT6(ucHeader) ^ GET_DATA_BIT7(ucHeader))) << 3;

    // Bit 2
    ucParity |= ((BYTE)(GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT5(ucHeader) ^ GET_DATA_BIT6(ucHeader))) << 2;

    // Bit 1
    ucParity |= ((BYTE)(GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT4(ucHeader) ^ GET_DATA_BIT5(ucHeader) ^ GET_DATA_BIT7(ucHeader))) << 1;

    // Bit 0
    ucParity |= (GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT4(ucHeader) ^ GET_DATA_BIT7(ucHeader));

    return ucParity;
}

//--------------------------------------------------
// Description  : Get Tx SDP Send Enable
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpMacTxSdpSendEnableCheck(EnumDPTxSecFunctionCtrl enumDPTxSecFunctionCtrl)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return ((ScalerGetByte(P2C_00_SEC_FUNCTION_CTRL) & enumDPTxSecFunctionCtrl) == enumDPTxSecFunctionCtrl);
    }
    else
#endif
    {
        return ((ScalerGetByte(PBC_00_SEC_FUNCTION_CTRL) & enumDPTxSecFunctionCtrl) == enumDPTxSecFunctionCtrl);
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Tx SDP Send Enable Switch
// Input Value  : enumDPTxSecFunctionCtrl, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpSendEnableSwitch(EnumDPTxSecFunctionCtrl enumDPTxSecFunctionCtrl, bit bEnable)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerSetBit(P2C_00_SEC_FUNCTION_CTRL, ~enumDPTxSecFunctionCtrl, (bEnable == _ENABLE) ? enumDPTxSecFunctionCtrl : 0x00);
    }
    else
#endif
    {
        ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~enumDPTxSecFunctionCtrl, (bEnable == _ENABLE) ? enumDPTxSecFunctionCtrl : 0x00);

        // DP1.4 VSC SDP enable needs double buffer
        if(enumDPTxSecFunctionCtrl == _SDP_VSC_EN)
        {
            ScalerSetBit(PBC_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), _DP_TX_SDP_DBUF_WAIT_FOR_VBLANK_RISING);
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Arbiter
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSSTDisplayFormatSetting_8b10b(void)
{
    BYTE ucDpTxColorDepth = 24;
    WORD usDpTxBitPerPixel = 24;
    WORD usFifoOffset = 0;
    WORD usValidDataPerLane = 0;
    WORD usDpTxTuSize = 1;
    WORD usDpTxFecTuSize = 1;
    WORD usDpTxInputHWidth = 0;
    WORD usSdpPacketHB = 0;
    WORD usBe2Be = 0;
    WORD usBs2Be = 0;
    WORD usSdpPacketVB = 0;

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    WORD usDpTxDSCPassTuSize = 1;
    WORD usHblank = g_stDpMacTxInputTimingInfo.usHTotal - g_stDpMacTxInputTimingInfo.usHWidth;
#endif

    // Pixel Generation Block Reset
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT7, 0x00);

    // Set Interlace Bit of VBID as Interlace Mode Detected
    if(GET_DP_TX_INPUT_INTERLACE_MODE() == _ON)
    {
        ScalerSetBit(PBB_C7_VBID, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(PBB_C7_VBID, ~_BIT0, 0x00);
    }

    // Get Color Depth Value By Color Space
    ucDpTxColorDepth = ScalerSyncDpGetColorDepthValue(GET_DP_TX_INPUT_COLOR_DEPTH(), GET_DP_TX_INPUT_COLOR_SPACE());

    // Get Color Space
    switch(GET_DP_TX_INPUT_COLOR_SPACE())
    {
        case _COLOR_SPACE_YCBCR422:
            ucDpTxColorDepth = ucDpTxColorDepth << 1;
            break;

        case _COLOR_SPACE_YCBCR420:
            ucDpTxColorDepth = (ucDpTxColorDepth * 3) >> 1;
            break;

        case _COLOR_SPACE_Y_ONLY:
            ucDpTxColorDepth = ucDpTxColorDepth;
            break;

        default:
            ucDpTxColorDepth = ucDpTxColorDepth * 3;
            break;
    }

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    if((GET_DP_TX_DOWNSTREAM_DSC_SUPPORT() == _ENABLE) && (GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH() == _ENABLE))
    {
        // Get DSC Pass-Through BPP
        usDpTxBitPerPixel = ScalerDpMacTxGetDscPassThroughBpp();
    }
    else
#endif
    {
        // Pre Multiply by 16
        usDpTxBitPerPixel = ((DWORD)ucDpTxColorDepth) << 4;
    }

    // =========================================
    // Step 1: Cal vaild symbol in TU
    // =========================================

    // Average TU = TU Size x (Stream_Clk x Byte of 1 pixel / Lane Number) / Link Rate
    if(GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() == _FALSE)
    {
        DWORD ulA = (DWORD)_DP_TX_SST_TU_SIZE * usDpTxBitPerPixel;
        DWORD ulB = (DWORD)GET_DP_TX_INPUT_PIXEL_CLK() * 10UL;
        DWORD ulC = (DWORD)GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() * 270UL * GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE();

        // Average TU = TU Size x Color Depth x Stream_Clk / (Lane Number x Link Rate)
        usDpTxTuSize = (GET_DWORD_MUL_DIV(ulA, ulB, ulC) >> 4) + (((GET_DWORD_MUL_DIV(ulA, ulB, ulC) % 16) >= 8) ? 1 : 0);
    }
    else
    {
        DWORD ulA = (DWORD)_DP_TX_SST_TU_SIZE * usDpTxBitPerPixel;
        DWORD ulB = (DWORD)GET_DP_TX_INPUT_PIXEL_CLK() * 1000UL * 10UL;
        DWORD ulC = (DWORD)GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() * 27UL * GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() * 9975UL;

        // Average TU = TU Size x Color Depth x Stream_Clk / Lane Number * SSCG of Link Rate)
        usDpTxTuSize = (GET_DWORD_MUL_DIV(ulA, ulB, ulC) >> 4) + (((GET_DWORD_MUL_DIV(ulA, ulB, ulC) % 16) >= 8) ? 1 : 0);
    }

    usDpTxTuSize = usDpTxTuSize / 10 + ((usDpTxTuSize % 10 >= 5) ? 1 : 0);

#if(_DP_TX_FEC_SUPPORT == _ON)

    if(GET_DP_TX_DOWNSTREAM_FEC_SUPPORT() == _ENABLE)
    {
        // FEC Tu size
        // Average TU = TU Size x (Stream_Clk x Byte of 1 pixel / Lane Number) / Link Rate
        if(GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() == _FALSE)
        {
            // FEC overhead of 2.4%, down-spreading overhead of 0.5%, and MST Branch device link reference clock difference of up to 0.06% (= 600ppm) add up to approximately 3% total overhead
            DWORD ulA = (DWORD)_DP_TX_SST_TU_SIZE  * usDpTxBitPerPixel;
            DWORD ulB = (DWORD)GET_DP_TX_INPUT_PIXEL_CLK() * 1000UL * 10UL;
            DWORD ulC = (DWORD)GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() * 27UL * GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() * 9760UL;

            // Average TU = TU Size x Color Depth x Stream_Clk / (Lane Number x Link Rate)
            usDpTxFecTuSize = (GET_DWORD_MUL_DIV(ulA, ulB, ulC) >> 4) + (((GET_DWORD_MUL_DIV(ulA, ulB, ulC) % 16) >= 8) ? 1 : 0);
        }
        else
        {
            // FEC overhead of 2.4%, down-spreading overhead of 0.5%, and MST Branch device link reference clock difference of up to 0.06% (= 600ppm) add up to approximately 3% total overhead
            DWORD ulA = (DWORD)_DP_TX_SST_TU_SIZE  * usDpTxBitPerPixel;
            DWORD ulB = (DWORD)GET_DP_TX_INPUT_PIXEL_CLK() * 1000UL * 10UL;
            DWORD ulC = (DWORD)GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() * 27UL * GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() * 9735UL;

            // Average TU = TU Size x Color Depth x Stream_Clk / Lane Number * SSCG of Link Rate)
            usDpTxFecTuSize = (GET_DWORD_MUL_DIV(ulA, ulB, ulC) >> 4) + (((GET_DWORD_MUL_DIV(ulA, ulB, ulC) % 16) >= 8) ? 1 : 0);
        }
    }
#endif

    usDpTxFecTuSize = usDpTxFecTuSize / 10 + ((usDpTxFecTuSize % 10 >= 5) ? 1 : 0);

    ScalerSetByte(PBB_CC_TU_SIZE, (_BIT7 | _DP_TX_SST_TU_SIZE));

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    // DSC MST2SST passthrough, if hblank is < 160, TX FIFO may Fail. Increase TU data size to enlarge TX Hblank to 160.
    // TU' = TU * [Hwidth / {Hwidth - (160 - hblank)}]
    if((GET_DP_TX_DOWNSTREAM_DSC_SUPPORT() == _ENABLE) &&
       (GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH() == _ENABLE) &&
       (usHblank < 160))
    {
        usDpTxDSCPassTuSize = GET_DWORD_MUL_DIV((DWORD)usDpTxFecTuSize,
                                                (DWORD)g_stDpMacTxInputTimingInfo.usHWidth,
                                                (DWORD)(g_stDpMacTxInputTimingInfo.usHWidth - (160 - usHblank)));

        if(usDpTxDSCPassTuSize > (_DP_TX_SST_TU_SIZE << 3))
        {
            DebugMessageDpTx("Fail to Modify usDpTxDSCPassTuSize when HB < 160", usDpTxDSCPassTuSize);
        }
        else
        {
            // margin: increase TU 0.125 when TU' = TU
            if((usDpTxFecTuSize == usDpTxDSCPassTuSize) &&
               (usDpTxDSCPassTuSize < (_DP_TX_SST_TU_SIZE << 3)))
            {
                usDpTxDSCPassTuSize += 1;
            }

            usDpTxFecTuSize = usDpTxDSCPassTuSize;

            DebugMessageDpTx("Modify usDpTxDSCPassTuSize when HB < 160", usDpTxDSCPassTuSize);
        }
    }

    if((GET_DP_TX_DOWNSTREAM_DSC_SUPPORT() == _ENABLE) && (GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH() == _ENABLE))
    {
        ScalerSetByte(PBB_CD_TU_DATA_SIZE0, (usDpTxFecTuSize >> 3));
        ScalerSetByte(PBB_CE_TU_DATA_SIZE1, (usDpTxFecTuSize & 0x07));
    }
    else
#endif
    {
        ScalerSetByte(PBB_CD_TU_DATA_SIZE0, (usDpTxTuSize >> 3));
        ScalerSetByte(PBB_CE_TU_DATA_SIZE1, (usDpTxTuSize & 0x07));
    }

#if(_DP_TX_FEC_SUPPORT == _ON)
    if(GET_DP_TX_DOWNSTREAM_FEC_SUPPORT() == _TRUE)
    {
        ScalerSetByte(PBB_ED_FEC_TU_DATA_SIZE0, (usDpTxFecTuSize >> 3));
        ScalerSetByte(PBB_EE_FEC_TU_DATA_SIZE1, (usDpTxFecTuSize & 0x07));
    }
#endif

    DebugMessageDpTx("GET_DP_TX_INPUT_PIXEL_CLK()", GET_DP_TX_INPUT_PIXEL_CLK());
    DebugMessageDpTx("GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM()", GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM());
    DebugMessageDpTx("GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE()", GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE());

    if((GET_DP_TX_STREAM_DATA_PATH_TYPE() == _DATA_PATH_VIDEO_REORDER) || (GET_DP_TX_STREAM_DATA_PATH_TYPE() == _DATA_PATH_DSC_REORDER))
    {
        usDpTxInputHWidth = g_stDpMacTxInputTimingInfo.usHWidth;
    }
    else
    {
        usDpTxInputHWidth = g_usDpMacTxInputHWidthMeasure;
    }

    // Calculate Pixel Numbers Per Lane
    usValidDataPerLane = usDpTxInputHWidth / GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() + (((usDpTxInputHWidth % GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM()) > 0) ? 1 : 0);

    // Calculate Link Symbol Numbers Per Lane
    usValidDataPerLane = (DWORD)usValidDataPerLane * usDpTxBitPerPixel / (8UL << 4) + ((((DWORD)usValidDataPerLane * usDpTxBitPerPixel % (8UL << 4)) > 0) ? 1 : 0);

    // =========================================
    // Step 2. SET Data Count
    // =========================================

    // Set Valid Data Per Lane
    ScalerSetByte(PBB_CA_V_DATA_PER_LINE0, HIBYTE(usValidDataPerLane));
    ScalerSetByte(PBB_CB_V_DATA_PER_LINE1, LOBYTE(usValidDataPerLane));

    // Get TU Number Per Line
    PDATA_WORD(3) = (usValidDataPerLane << 3) / usDpTxTuSize + (((usValidDataPerLane << 3) % usDpTxTuSize > 0) ? 1 : 0);

    // Store Horizontal DE for Sec Data End Count
    SET_DP_TX_HORIZONTAL_DE_PERIOD(PDATA_WORD(3) * _DP_TX_SST_TU_SIZE);

    // SET Seccondary End Count for Audio OFF
    // Get BE2BE Period with Htotal
    usBe2Be = g_stDpMacTxInputTimingInfo.usHTotal * 270UL * GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() / GET_DP_TX_INPUT_PIXEL_CLK();
    // Get 70% of blanking period
    usBs2Be = (usBe2Be - GET_DP_TX_HORIZONTAL_DE_PERIOD()) * 7 / 10;

    // SDP_packet = SS&SE + HEADER&ECC BYTES / lane_num + (DATA_BYTES_HBlank + DATA_P_BYTES_HBlank) / lane_num.
    usSdpPacketHB = 2 + ((8 + 32 + 8) / GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM());

    // SET Seccondary End Count 70%Blanking-SDP_packet_HB
    ScalerSetByte(PBB_D4_ARBITER_SEC_END_CNT_HB, HIBYTE(usBs2Be - usSdpPacketHB));
    ScalerSetByte(PBB_D5_ARBITER_SEC_END_CNT_LB, LOBYTE(usBs2Be - usSdpPacketHB));

    // SET SEC_END_CNT_VBlank
    // SET Sec End Cnt VBlnk Md to Use Reg_Sec_End_Cnt_VBlnk
    ScalerSetBit(PBB_DB_DPTX_TOP_RSV2, ~_BIT7, _BIT7);

    // SDP_packet = SS&SE + HEADER&ECC BYTES / lane_num + (DATA_BYTES_VBlank + DATA_P_BYTES_VBlank) / lane_num.
    usSdpPacketVB = 2 + ((8 + 128 + 32) / GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM());

    // SET Seccondary End Count 70%Blanking-SDP_packet_VB
    ScalerSetBit(PBB_DB_DPTX_TOP_RSV2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usBs2Be - usSdpPacketVB));
    ScalerSetByte(PBB_FF_DPTX_TOP_RSV10, LOBYTE(usBs2Be - usSdpPacketVB));

    // Set SEC END CNT Double Buffer
    SET_DP_TX_SEC_END_CNT_DB_8B10B();

    // =========================================
    // Step 3: FW manual Calculate H Delay
    // =========================================

    // DP fifo size = 256 x 96bit
    // FifoOffset = (1/2 * (256 * 96) / (color space * depth per color))
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    if((GET_DP_TX_DOWNSTREAM_DSC_SUPPORT() == _ENABLE) && (GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH() == _ENABLE))
    {
        usFifoOffset = 12288UL / 11UL;
    }
    else
#endif
    {
        usFifoOffset = (12288UL << 4) / usDpTxBitPerPixel;
    }

    // Tx Reorder Hdelay Refer BS
    // Tx Vesa Hdelay Refer Hstart
    if((GET_DP_TX_STREAM_DATA_PATH_TYPE() == _DATA_PATH_VIDEO_REORDER) || (GET_DP_TX_STREAM_DATA_PATH_TYPE() == _DATA_PATH_DSC_REORDER))
    {
#if(_DP_SUPPORT == _ON)
        // Tx Reorder Tracking Mode On
        if(ScalerGetBit(PBB_B2_NVID_ASYNC_M, _BIT1) == _BIT1)
        {
            // DPRX Hsync Tracking Source: BE or BS
            if(ScalerDpMacTxGetRxReorderTrackingMode(GET_DP_TX_STREAM_SOURCE()) == _DP_MAC_RX_TRACKING_SOURCE_BE)
            {
                PDATA_WORD(2) = 0;
                PDATA_WORD(3) = g_stDpMacTxInputTimingInfo.usHWidth;
            }
            else
            {
                PDATA_WORD(2) = g_stDpMacTxInputTimingInfo.usHTotal - g_stDpMacTxInputTimingInfo.usHWidth;
                PDATA_WORD(3) = g_stDpMacTxInputTimingInfo.usHWidth;
            }
        }
        else
#endif
        {
            PDATA_WORD(2) = g_stDpMacTxInputTimingInfo.usHTotal - g_stDpMacTxInputTimingInfo.usHWidth;
            PDATA_WORD(3) = g_stDpMacTxInputTimingInfo.usHWidth;
        }
    }
    else
    {
        PDATA_WORD(2) = g_usDpMacTxInputHStartMeasure;
        PDATA_WORD(3) = g_usDpMacTxInputHWidthMeasure;
    }

    if((PDATA_WORD(2) + usFifoOffset) < PDATA_WORD(3))
    {
        PDATA_WORD(2) = (PDATA_WORD(2) + usFifoOffset) * (((DWORD)GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE()) * 270) / ((DWORD)GET_DP_TX_INPUT_PIXEL_CLK());
    }
    else
    {
        PDATA_WORD(2) = (PDATA_WORD(2) + (PDATA_WORD(3) / 2)) * (((DWORD)GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE()) * 270) / ((DWORD)GET_DP_TX_INPUT_PIXEL_CLK());
    }

    ScalerSetByte(PBB_CF_HDEALY0, (HIBYTE(PDATA_WORD(2)) & 0x7F));
    ScalerSetByte(PBB_D0_HDEALY1, LOBYTE(PDATA_WORD(2)));

    // Clear FIFO Status
    ScalerSetByte(PBB_A4_PG_FIFO_CTRL, 0xFC);
}

//--------------------------------------------------
// Description  : DP Tx MSA Generation
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSSTMSASetting_8b10b(void)
{
    // Enable Sdp Split
    ScalerDpMacTxSdpSplit(GET_DP_TX_DOWNSTREAM_SPLIT_SDP_SUPPORT());

    // Reset MSA Generation Block and SEC Block
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT6, _BIT6);
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT6, 0x00);

    // Set Htotal
    ScalerSetByte(PBB_B7_MN_STRM_ATTR_HTT_M, HIBYTE(g_stDpMacTxInputTimingInfo.usHTotal));
    ScalerSetByte(PBB_B8_MN_STRM_ATTR_HTT_L, LOBYTE(g_stDpMacTxInputTimingInfo.usHTotal));

    // Set Hstart
    ScalerSetByte(PBB_B9_MN_STRM_ATTR_HST_M, HIBYTE(g_stDpMacTxInputTimingInfo.usHStart));
    ScalerSetByte(PBB_BA_MN_STRM_ATTR_HST_L, LOBYTE(g_stDpMacTxInputTimingInfo.usHStart));

    // Set Hwidth
    ScalerSetByte(PBB_BB_MN_STRM_ATTR_HWD_M, HIBYTE(g_stDpMacTxInputTimingInfo.usHWidth));
    ScalerSetByte(PBB_BC_MN_STRM_ATTR_HWD_L, LOBYTE(g_stDpMacTxInputTimingInfo.usHWidth));

    // Set Hsyc and Polarity
    pData[0] = ((HIBYTE(g_stDpMacTxInputTimingInfo.usHSWidth) & 0x7F) | ((BYTE)g_stDpMacTxInputTimingInfo.b1HSP << 7));

    // Set Hsyc and Polarity
    ScalerSetByte(PBB_BD_MN_STRM_ATTR_HSW_M, pData[0]);
    ScalerSetByte(PBB_BE_MN_STRM_ATTR_HSW_L, LOBYTE(g_stDpMacTxInputTimingInfo.usHSWidth));

    // Set Vtotal
    ScalerSetByte(PBB_BF_MN_STRM_ATTR_VTTE_M, HIBYTE(g_stDpMacTxInputTimingInfo.usVTotal));
    ScalerSetByte(PBB_C0_MN_STRM_ATTR_VTTE_L, LOBYTE(g_stDpMacTxInputTimingInfo.usVTotal));

    // Set VStart
    ScalerSetByte(PBB_C1_MN_STRM_ATTR_VST_M, HIBYTE(g_stDpMacTxInputTimingInfo.usVStart));
    ScalerSetByte(PBB_C2_MN_STRM_ATTR_VST_L, LOBYTE(g_stDpMacTxInputTimingInfo.usVStart));

    // Set VHeight
    ScalerSetByte(PBB_C3_MN_STRM_ATTR_VHT_M, HIBYTE(g_stDpMacTxInputTimingInfo.usVHeight));
    ScalerSetByte(PBB_C4_MN_STRM_ATTR_VHT_L, LOBYTE(g_stDpMacTxInputTimingInfo.usVHeight));

    // Set Vsync and Polarity
    pData[0] = ((HIBYTE(g_stDpMacTxInputTimingInfo.usVSWidth) & 0x7F) | ((BYTE)g_stDpMacTxInputTimingInfo.b1VSP << 7));

    // Set Vsync and Polarity
    ScalerSetByte(PBB_C5_MN_STRM_ATTR_VSW_M, pData[0]);
    ScalerSetByte(PBB_C6_MN_STRM_ATTR_VSW_L, LOBYTE(g_stDpMacTxInputTimingInfo.usVSWidth));

    // Set Color Format
    ScalerDpMacTxMsaMiscSetting();

    // Set VSC SDP Send Disable
    ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~_BIT2, 0x00);

    if(GET_DP_TX_VSC_SDP_SEND_ENABLE() == _TRUE)
    {
        ScalerDpMacTxVscSdpSetting();

        // Set VSC SDP Send Enable
        ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~_BIT2, _BIT2);

        ScalerDpMacTxSdpSetHeaderByte(_SEC_PACKET_TYPE_VSC, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);

        // Set MISC1[6] to indicate VSC SDP is used and ignoring the info in MSA
        ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT6, _BIT6);
    }
    else
    {
        ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT6, 0x00);
    }

    DebugMessageDpTx("DP Tx MSA Color Space 1", GET_DP_TX_INPUT_COLOR_SPACE());

    // MSA_DB = 1
    ScalerSetBit(PBB_B4_MSA_CTRL, ~_BIT7, _BIT7);

    if(GET_DP_TX_INPUT_INTERLACE_MODE() == _ON)
    {
        // Set MISC1
        if(GET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER() == _EVEN)
        {
            ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT0, _BIT0);
        }
        else
        {
            ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT0, 0x00);
        }
    }

    // MSA_DB = 1
    ScalerSetBit(PBB_B4_MSA_CTRL, ~_BIT7, _BIT7);

    DebugMessageDpTx("DP Tx MSA Color Space 2", ScalerGetBit(PBB_B5_MSA_MISC0, (_BIT2 | _BIT1)));
}

//--------------------------------------------------
// Description  : DP Tx MSA MISC0/MISC1 setting
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxMsaMiscSetting(void)
{
    switch(GET_DP_TX_INPUT_COLOR_SPACE())
    {
        case _COLOR_SPACE_RGB:
        default:

            switch(GET_DP_TX_INPUT_COLORIMETRY())
            {
                case _COLORIMETRY_RGB_SRGB:
                default:

                    if(GET_DP_TX_INPUT_COLOR_RGB_QUANTIZATION_RANGE() == _RGB_QUANTIZATION_FULL_RANGE)
                    {
                        ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_SRGB_VESA);
                    }
                    else
                    {
                        ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_SRGB_CEA);
                    }

                    break;

                case _COLORIMETRY_RGB_XRRGB:
                    ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_XRRGB);
                    break;

                case _COLORIMETRY_RGB_SCRGB:
                    ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_SCRGB);
                    break;

                case _COLORIMETRY_RGB_ADOBERGB:
                    ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_ADOBERGB);
                    break;

                case _COLORIMETRY_RGB_DCI_P3:
                    ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_DCI_P3);
                    break;

                case _COLORIMETRY_RGB_COLOR_PROFILE:
                    ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_COLOR_PROFILE);
                    break;

                case _COLORIMETRY_EXT:

                    switch(GET_DP_TX_INPUT_EXT_COLORIMETRY())
                    {
                        case _COLORIMETRY_EXT_RGB_SRGB:
                        default:

                            if(GET_DP_TX_INPUT_COLOR_RGB_QUANTIZATION_RANGE() == _RGB_QUANTIZATION_FULL_RANGE)
                            {
                                ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_SRGB_VESA);
                            }
                            else
                            {
                                ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_SRGB_CEA);
                            }

                            break;

                        case _COLORIMETRY_EXT_RGB_XRRGB:
                            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_XRRGB);
                            break;

                        case _COLORIMETRY_EXT_RGB_SCRGB:
                            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_SCRGB);
                            break;

                        case _COLORIMETRY_EXT_RGB_ADOBERGB:
                            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_ADOBERGB);
                            break;

                        case _COLORIMETRY_EXT_RGB_DCI_P3:
                            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_DCI_P3);
                            break;

                        case _COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE:
                            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_COLOR_PROFILE);
                            break;
                    }
            }

            break;

        case _COLOR_SPACE_YCBCR422:

            switch(GET_DP_TX_INPUT_COLORIMETRY())
            {
                case _COLORIMETRY_YCC_ITUR_BT601:
                default:
                    ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC422_ITUR_BT601);
                    break;

                case _COLORIMETRY_YCC_ITUR_BT709:
                    ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC422_ITUR_BT709);
                    break;

                case _COLORIMETRY_YCC_XVYCC601:
                    ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC422_XVYCC601);
                    break;

                case _COLORIMETRY_YCC_XVYCC709:
                    ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC422_XVYCC709);
                    break;

                case _COLORIMETRY_EXT:

                    switch(GET_DP_TX_INPUT_EXT_COLORIMETRY())
                    {
                        case _COLORIMETRY_EXT_YCC_ITUR_BT601:
                        default:
                            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC422_ITUR_BT601);
                            break;

                        case _COLORIMETRY_EXT_YCC_ITUR_BT709:
                            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC422_ITUR_BT709);
                            break;

                        case _COLORIMETRY_EXT_YCC_XVYCC601:
                            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC422_XVYCC601);
                            break;

                        case _COLORIMETRY_EXT_YCC_XVYCC709:
                            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC422_XVYCC709);
                            break;
                    }
            }

            break;

        case _COLOR_SPACE_YCBCR444:

            switch(GET_DP_TX_INPUT_COLORIMETRY())
            {
                case _COLORIMETRY_YCC_ITUR_BT601:
                default:
                    ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC444_ITUR_BT601);
                    break;

                case _COLORIMETRY_YCC_ITUR_BT709:
                    ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC444_ITUR_BT709);
                    break;

                case _COLORIMETRY_YCC_XVYCC601:
                    ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC444_XVYCC601);
                    break;

                case _COLORIMETRY_YCC_XVYCC709:
                    ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC444_XVYCC709);
                    break;

                case _COLORIMETRY_EXT:

                    switch(GET_DP_TX_INPUT_EXT_COLORIMETRY())
                    {
                        case _COLORIMETRY_EXT_YCC_ITUR_BT601:
                        default:
                            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC444_ITUR_BT601);
                            break;

                        case _COLORIMETRY_EXT_YCC_ITUR_BT709:
                            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC444_ITUR_BT709);
                            break;

                        case _COLORIMETRY_EXT_YCC_XVYCC601:
                            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC444_XVYCC601);
                            break;

                        case _COLORIMETRY_EXT_YCC_XVYCC709:
                            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_YCC444_XVYCC709);
                            break;
                    }
            }

            break;

        case _COLOR_SPACE_Y_ONLY:
            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_Y_ONLY);
            break;

        case _COLOR_SPACE_RAW:
            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RAW);

            break;

        case _COLOR_SPACE_YCBCR420:
            // Component Format shall be set to 2b'00(RGB mode), because hw will refer it to arrange Ycbcr 420 content and only just with rgb mode
            ScalerDpMacTxMsaSetColorFormat(_DP_MSA_COLORIMETRY_RGB_SRGB_VESA);
            break;
    }
}

//--------------------------------------------------
// Description  : Set Tx Msa Color Format
// Input Value  : enumMsaColorimetry
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxMsaSetColorFormat(EnumDpMsaColorimetry enumMsaColorimetry)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerSetBit(P2B_AA_MN_STRM_ATTR_MISC1, ~_BIT7, (enumMsaColorimetry & _BIT7));

        ScalerSetBit(P2B_A9_MSA_MISC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1),
                     (GET_DP_TX_INPUT_COLOR_DEPTH() << 5) | (enumMsaColorimetry & (_BIT4 | _BIT3 | _BIT2 | _BIT1)));

        ScalerSetBit(P2B_A8_MSA_CTRL, ~_BIT7, _BIT7);
    }
    else
#endif
    {
        if(ScalerDpMacTxNewComponentModeAvailable() == _TRUE)
        {
            // Set Component Format PG : RGB/YCbCr444 00h; YCbCr422 01h; RGB/YCbCr444 10h; Yonly 11h;
            switch(enumMsaColorimetry)
            {
                case _DP_MSA_COLORIMETRY_RGB_XRRGB:
                case _DP_MSA_COLORIMETRY_RGB_SCRGB:
                case _DP_MSA_COLORIMETRY_RGB_DCI_P3:
                case _DP_MSA_COLORIMETRY_RGB_COLOR_PROFILE:
                    ScalerSetBit(PBB_FE_DPTX_TOP_RSV9, ~(_BIT3 | _BIT2), 0x00);
                    break;

                case _DP_MSA_COLORIMETRY_Y_ONLY:
                    ScalerSetBit(PBB_FE_DPTX_TOP_RSV9, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                    break;

                default:
                    ScalerSetBit(PBB_FE_DPTX_TOP_RSV9, ~(_BIT3 | _BIT2), ((enumMsaColorimetry & (_BIT2 | _BIT1)) << 1));
                    break;
            }
        }
        else
        {
            switch(enumMsaColorimetry)
            {
                case _DP_MSA_COLORIMETRY_RGB_XRRGB:
                case _DP_MSA_COLORIMETRY_RGB_SCRGB:
                case _DP_MSA_COLORIMETRY_RGB_DCI_P3:
                case _DP_MSA_COLORIMETRY_RGB_COLOR_PROFILE:

                    // Force Tx MSA Colorimetry Value to SRGB
                    if(GET_DP_TX_INPUT_COLOR_RGB_QUANTIZATION_RANGE() == _RGB_QUANTIZATION_FULL_RANGE)
                    {
                        enumMsaColorimetry = _DP_MSA_COLORIMETRY_RGB_SRGB_VESA;
                    }
                    else
                    {
                        enumMsaColorimetry = _DP_MSA_COLORIMETRY_RGB_SRGB_CEA;
                    }
                    break;

                default:
                    break;
            }
        }

        ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT7, (enumMsaColorimetry & _BIT7));

        ScalerSetBit(PBB_B5_MSA_MISC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1),
                     (GET_DP_TX_INPUT_COLOR_DEPTH() << 5) | (enumMsaColorimetry & (_BIT4 | _BIT3 | _BIT2 | _BIT1)));

        ScalerSetBit(PBB_B4_MSA_CTRL, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : Dp Tx Get Stream Source for User
// Input Value  : None
// Output Value : GET_DP_TX_STREAM_SOURCE
//--------------------------------------------------
EnumDPTxInputSource ScalerDpMacTxGetStreamSource(void)
{
    return GET_DP_TX_STREAM_SOURCE();
}

//--------------------------------------------------
// Description  : Dp Tx Get Downstream DP Plug Status for User
// Input Value  : None
// Output Value : _HIGH/_LOW
//--------------------------------------------------
bit ScalerDpMacTxUserGetDownstreamHPDStatus(void)
{
    if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
    {
        return _HIGH;
    }

    if(GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_LINK_OFF)
    {
        return _HIGH;
    }

    return _LOW;
}

//--------------------------------------------------
// Description  : Tx VSC SDP Bypass Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxVscSdpSetting(void)
{
    CLR_DP_TX_VSC_COLOR_INFO();

    // Set Color Space
    switch(GET_DP_TX_INPUT_COLOR_SPACE())
    {
        case _COLOR_SPACE_RGB:
        default:
            SET_DP_TX_VSC_COLOR_SPACE(_DP_VSC_COLOR_SPACE_RGB);
            break;

        case _COLOR_SPACE_YCBCR444:
            SET_DP_TX_VSC_COLOR_SPACE(_DP_VSC_COLOR_SPACE_YCBCR444);
            break;

        case _COLOR_SPACE_YCBCR422:
            SET_DP_TX_VSC_COLOR_SPACE(_DP_VSC_COLOR_SPACE_YCBCR422);
            break;

        case _COLOR_SPACE_YCBCR420:
            SET_DP_TX_VSC_COLOR_SPACE(_DP_VSC_COLOR_SPACE_YCBCR420);
            break;

        case _COLOR_SPACE_Y_ONLY:
            SET_DP_TX_VSC_COLOR_SPACE(_DP_VSC_COLOR_SPACE_Y_ONLY);
            break;

        case _COLOR_SPACE_RAW:
            SET_DP_TX_VSC_COLOR_SPACE(_DP_VSC_COLOR_SPACE_RAW);
            break;
    }

    // Set Colorimetry
    switch(GET_DP_TX_INPUT_EXT_COLORIMETRY())
    {
        case _COLORIMETRY_EXT_RGB_SRGB:
        default:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_RGB_SRGB);
            break;

        case _COLORIMETRY_EXT_RGB_XRRGB:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_RGB_XRRGB);
            break;

        case _COLORIMETRY_EXT_RGB_SCRGB:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_RGB_SCRGB);
            break;

        case _COLORIMETRY_EXT_RGB_ADOBERGB:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_RGB_ADOBERGB);
            break;

        case _COLORIMETRY_EXT_RGB_DCI_P3:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_RGB_DCI_P3);
            break;

        case _COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_RGB_COLOR_PROFILE);
            break;

        case _COLORIMETRY_EXT_RGB_ITUR_BT2020:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_RGB_ITUR_BT2020);
            break;

        case _COLORIMETRY_EXT_YCC_ITUR_BT601:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_YCC_ITUR_BT601);
            break;

        case _COLORIMETRY_EXT_YCC_ITUR_BT709:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_YCC_ITUR_BT709);
            break;

        case _COLORIMETRY_EXT_YCC_XVYCC601:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_YCC_XVYCC601);
            break;

        case _COLORIMETRY_EXT_YCC_XVYCC709:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_YCC_XVYCC709);
            break;

        case _COLORIMETRY_EXT_YCC_SYCC601:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_YCC_SYCC601);
            break;

        case _COLORIMETRY_EXT_YCC_ADOBEYCC601:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_YCC_ADOBEYCC601);
            break;

        case _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_YCC_ITUR_BT2020_CL);
            break;

        case _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_YCC_ITUR_BT2020_NCL);
            break;

        case _COLORIMETRY_EXT_Y_ONLY_DICOM_PART14:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_Y_ONLY_DICOM_PART14);
            break;

        case _COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE:
            SET_DP_TX_VSC_COLORIMETRY(_DP_VSC_COLORIMETRY_RAW_CUSTOM_COLOR_PROFILE);
            break;
    }

    SET_DP_TX_VSC_COLOR_DEPTH(GET_DP_TX_INPUT_COLOR_DEPTH());

    // Set Dynamic Range
    if((GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR420))
    {
        if(GET_DP_TX_INPUT_COLOR_YCC_QUANTIZATION_RANGE() == _YCC_QUANTIZATION_LIMIT_RANGE)
        {
            SET_DP_TX_VSC_DYNAMIC_RANGE((bit)_DP_VSC_QUANTIZATION_LIMIT_RANGE);
        }
        else
        {
            SET_DP_TX_VSC_DYNAMIC_RANGE((bit)_DP_VSC_QUANTIZATION_FULL_RANGE);
        }
    }
    else
    {
        if(GET_DP_TX_INPUT_COLOR_RGB_QUANTIZATION_RANGE() == _RGB_QUANTIZATION_LIMIT_RANGE)
        {
            SET_DP_TX_VSC_DYNAMIC_RANGE((bit)_DP_VSC_QUANTIZATION_LIMIT_RANGE);
        }
        else
        {
            SET_DP_TX_VSC_DYNAMIC_RANGE((bit)_DP_VSC_QUANTIZATION_FULL_RANGE);
        }
    }

    SET_DP_TX_VSC_CONTENT_TYPE(GET_DP_TX_INPUT_COLOR_CONTENT_TYPE());

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxSdpSetDataByte(_SEC_PACKET_TYPE_VSC, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);

        ScalerDpMacTxSdpSetHeaderByte(_SEC_PACKET_TYPE_VSC, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);
    }
    else
#endif
    {
        memcpy((volatile BYTE xdata *)PBC_14_SEC_PSR_DB16, g_pucDpMacTxVscSdpDB16to18, 3);

        ScalerDpMacTxSdpSetHeaderByte(_SEC_PACKET_TYPE_VSC, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);
    }
}

#if(_DP_TX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Tx FEC Initial Setting
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpMacTxFecInitialSetting(void)
{
    BYTE pucFECInfo[16] = {0};
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        pucFECInfo[0] = 0x00;

        if(ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x20, 1, pucFECInfo) == _TRUE)
        {
            ScalerDpMacTxPreCodingSet(_DISABLE);
        }
        else
        {
            return _FALSE;
        }

        SET_DP_TX_FEC_ENCODE_128B132B(_DISABLE);
    }
    else
#endif
    {
        if(GET_DP_TX_DOWNSTREAM_FEC_SUPPORT() == _TRUE)
        {
            // Clear FEC Seq Send Done Flag
            ScalerSetBit(PBB_EC_FEC_TX_FLG, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // dp14:fec ready 120h[0]
            pucFECInfo[0] = 0x01;

            if(ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x20, 1, pucFECInfo) == _TRUE)
            {
                SET_DP_TX_FEC_READY_8B10B(_ENABLE);
            }
            else
            {
                return _FALSE;
            }
        }
        else
        {
            pucFECInfo[0] = 0x00;

            ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x20, 1, pucFECInfo);

            SET_DP_TX_FEC_READY_8B10B(_DISABLE);
        }
        SET_DP_TX_FEC_ENCODE_8B10B(_DISABLE);
    }

    return _TRUE;
}

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Tx pre coding Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxPreCodingSet(bit bPreCodingEn)
{
    // Set Pre coding
    if(bPreCodingEn == _ENABLE)
    {
        // Enable pre coding
        ScalerSetBit(P2B_00_DP_PHY_CTRL, ~_BIT1, 0x00);
    }
    else
    {
        // Disable pre coding
        ScalerSetBit(P2B_00_DP_PHY_CTRL, ~_BIT1, _BIT1);
    }
}
#endif

//--------------------------------------------------
// Description  : DP Tx Link Training Link Rate Reduce
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpMacTxFecSetting(bit bEn)
{
    BYTE ucFECStatusRetry = 0;

    if(bEn == _ENABLE)
    {
        // Retry 3 Times 00280h Seq Detect Result
        for(ucFECStatusRetry = 0; ucFECStatusRetry < 3; ucFECStatusRetry++)
        {
            // Disable FEC Encode
            SET_DP_TX_FEC_ENCODE_8B10B(_DISABLE);

            // Clear FEC Seq Send Done Flag
            ScalerSetBit(PBB_EC_FEC_TX_FLG, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Enable FEC Encode
            SET_DP_TX_FEC_ENCODE_8B10B(_ENABLE);

            // Delay 5ms to retry
            ScalerTimerDelayXms(5);

            // Polling FEC Seq Send Done
            if(ScalerTimerPollingFlagProc(2, PBB_EC_FEC_TX_FLG, _BIT1, _TRUE) == _TRUE)
            {
                if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x80, 1, pData) == _FALSE)
                {
                    DebugMessageDpTx("DPTX FEC Read 00280h Fail", 0);

                    SET_DP_TX_FEC_ENCODE_8B10B(_DISABLE);

                    return _FALSE;
                }

                if((pData[0] & _BIT0) == _BIT0)
                {
                    pData[0] = (pData[0] & _BIT0);

                    if(ScalerDpAuxTxNativeWrite(0x00, 0x02, 0x80, 1, pData) == _FALSE)
                    {
                        DebugMessageDpTx("DPTX FEC Write 00280h Fail", 0);

                        SET_DP_TX_FEC_ENCODE_8B10B(_DISABLE);

                        return _FALSE;
                    }

                    return _SUCCESS;
                }
            }
            else
            {
                DebugMessageDpTx("DPTX FEC en seq don't send out", 0);
            }
        }
    }
    else
    {
        // Retry 3 Times 00280h Seq Detect Result
        for(ucFECStatusRetry = 0; ucFECStatusRetry < 3; ucFECStatusRetry++)
        {
            // Enable FEC Encode
            SET_DP_TX_FEC_ENCODE_8B10B(_ENABLE);

            // Clear FEC Seq Send Done Flag
            ScalerSetBit(PBB_EC_FEC_TX_FLG, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Disable FEC Encode
            SET_DP_TX_FEC_ENCODE_8B10B(_DISABLE);

            // Delay 5ms to retry
            ScalerTimerDelayXms(5);

            // Polling FEC Seq Send Done
            if(ScalerTimerPollingFlagProc(2, PBB_EC_FEC_TX_FLG, _BIT0, _TRUE) == _TRUE)
            {
                // If the DPTX has not received an IRQ_HPD >= 105 ms and then DPTX shall retrain the link.
                ScalerTimerActiveTimerEvent(105, _SCALER_TIMER_EVENT_DP_TX_FEC_DECODE_DIS_FAIL_RETRAIN);

                if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x80, 1, pData) == _FALSE)
                {
                    DebugMessageDpTx("DPTX FEC Read 00280h Fail", 0);

                    SET_DP_TX_FEC_ENCODE_8B10B(_DISABLE);

                    return _FALSE;
                }

                if((pData[0] & _BIT1) == _BIT1)
                {
                    pData[0] = (pData[0] & _BIT1);

                    if(ScalerDpAuxTxNativeWrite(0x00, 0x02, 0x80, 1, pData) == _FALSE)
                    {
                        DebugMessageDpTx("DPTX FEC Write 00280h Fail", 0);

                        SET_DP_TX_FEC_ENCODE_8B10B(_DISABLE);

                        return _FALSE;
                    }

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_FEC_DECODE_DIS_FAIL_RETRAIN);

                    return _SUCCESS;
                }
            }
            else
            {
                DebugMessageDpTx("DPTX FEC dis seq don't send out", 0);
            }
        }
    }

    SET_DP_TX_FEC_ENCODE_8B10B(_DISABLE);

    return _FAIL;
}

//--------------------------------------------------
// Description  : DP Tx FEC Re Link Training
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerDpMacTxFecDisableFailReLinkTraining(void)
{
    if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x80, 1, pData) == _TRUE)
    {
        if((pData[0] & _BIT1) == 0x00)
        {
            SET_DP_TX_FORCE_LINK_TRAINING();
        }
    }
}
#endif

//--------------------------------------------------
// Description  : On-line check for DPTX SST D0
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxMeasureGetMeasureResult(StructMeasureSyncData *pstMeasureSyncHV)
{
    if(ScalerTimerPollingFlagProc(_MEASURE_TIMEOUT, P16_42_DPTX_MEAS_CTL1, _BIT7, 0x00) == _FALSE)
    {
        return _FALSE;
    }

    // Check measure result status
    if(ScalerGetBit(P16_43_DPTX_MEAS_ERROR_FLG0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) != 0x00)
    {
        return _FALSE;
    }

    // Pop up measurement result
    ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~_BIT6, _BIT6);

    // Polarity
    pstMeasureSyncHV->b1HSP = (ScalerGetBit(P16_44_DPTX_MEAS_ERROR_FLG1, _BIT6) == 0);
    pstMeasureSyncHV->b1VSP = (ScalerGetBit(P16_44_DPTX_MEAS_ERROR_FLG1, _BIT7) == 0);

    // HSync Period
    pstMeasureSyncHV->usHSPeriod = ((((WORD)ScalerGetByte(P16_45_DPTX_MEAS_HS_PERIOD_A_M) & 0x1F) << 8) | (ScalerGetByte(P16_46_DPTX_MEAS_HS_PERIOD_A_L))) + 1;

    // VSync Period
    pstMeasureSyncHV->usVSPeriod = ((((WORD)ScalerGetByte(P16_48_DPTX_MEAS_VS_PERIOD_A_M) & 0x0F) << 8) | (ScalerGetByte(P16_49_DPTX_MEAS_VS_PERIOD_A_L))) + 1;

    // HSync Pulse Width
    pstMeasureSyncHV->usHSWidth = ((((WORD)ScalerGetByte(P16_4A_DPTX_MEAS_HS_PULSE_A_M) & 0x1F) << 8) | (ScalerGetByte(P16_4B_DPTX_MEAS_HS_PULSE_A_L))) + 1;

    // VSync Pulse Width
    pstMeasureSyncHV->usVSWidth = ((((WORD)ScalerGetByte(P16_4C_DPTX_MEAS_VS_PULSE_A_M) & 0xF) << 8) | (ScalerGetByte(P16_4D_DPTX_MEAS_VS_PULSE_A_L))) + 1;

    // H total
    pstMeasureSyncHV->usHTotal = ((((WORD)ScalerGetByte(P16_4E_DPTX_MEAS_HS_PERIOD_D_M) & 0x1F) << 8) | (ScalerGetByte(P16_4F_DPTX_MEAS_HS_PERIOD_D_L))) + 1;

    // V Height
    pstMeasureSyncHV->usVHeight = ((((WORD)ScalerGetByte(P16_51_DPTX_MEAS_VS_PERIOD_D_M) & 0x0F) << 8) | (ScalerGetByte(P16_52_DPTX_MEAS_VS_PERIOD_D_L))) + 1;

    // H Width
    pstMeasureSyncHV->usHWidth = ((((WORD)ScalerGetByte(P16_53_DPTX_MEAS_HS_PULSE_D_M) & 0x1F) << 8) | (ScalerGetByte(P16_54_DPTX_MEAS_HS_PULSE_D_L))) + 1;

    // For two pixel mode
    pstMeasureSyncHV->usHTotal <<= 1;
    pstMeasureSyncHV->usHWidth <<= 1;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Tx Input Info for DPTX SST D0
// Input Value  : enumDPTxInputInfoRef
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxGetInputMeasureTimingInfo(EnumInputPort enumInputPort)
{
    StructMeasureSyncData stMeasureSyncHV = {0};
    enumInputPort = enumInputPort;

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_DP_TX_ENABLED() == _TRUE)
    {
        // Bypass DP Tx Hw Measure because Dp Drr Deonly mode constraint
        ScalerSetBit(P16_5E_DPTX_MEAS_BYPASS, ~_BIT0, _BIT0);

        g_usDpMacTxInputHStartMeasure = ScalerDpMacStreamRxGetHstart(enumInputPort);
        g_usDpMacTxInputHWidthMeasure = ScalerDpMacStreamRxGetHwidth(enumInputPort);
    }
    else
#endif
    {
        // Bypass DP Tx Hw Measure because Dp Drr Deonly mode constraint
        ScalerSetBit(P16_5E_DPTX_MEAS_BYPASS, ~_BIT0, 0x00);

        // Power up DPTX measure; Measure Time Clock = 16384 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
        ScalerSetBit(P16_41_DPTX_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), (_BIT7 | _BIT6));

        // Use Auto function for ensuring that P16_5A_DPTX_MEAS2_HS_VS_DLY is ready
        // Start auto
        ScalerSetBit(P16_CD_DPTX_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);

        // Wait for auto
        if(ScalerTimerPollingFlagProc(90, P16_CD_DPTX_AUTO_ADJ_CTRL1, _BIT0, 0x00) == _FALSE)
        {
            DebugMessageDpTx("Tx Measure Auto Failed", 0x00);

            return _FALSE;
        }

        // Check Hs/Vs edge location
        switch(ScalerGetBit(P16_5A_DPTX_MEAS2_HS_VS_DLY, (_BIT7 | _BIT6 | _BIT5)))
        {
            case (_BIT6 | _BIT5):
                // 011: delay Vs
                ScalerSetBit(P16_5A_DPTX_MEAS2_HS_VS_DLY, ~(_BIT4 | _BIT3), _BIT3);
                break;
            case (_BIT5):
                // 001: delay Hs
                ScalerSetBit(P16_5A_DPTX_MEAS2_HS_VS_DLY, ~(_BIT4 | _BIT3), _BIT4);
                break;
            default:
                // reset Hs/Vs delay
                ScalerSetBit(P16_5A_DPTX_MEAS2_HS_VS_DLY, ~(_BIT4 | _BIT3), 0x00);
                break;
        }

        // Disable DPTX measure
        ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

        // Set DPTX VGIP sync polarity to default
        ScalerSetBit(P16_A1_DPTX_VGIP_SIGINV, ~(_BIT3 | _BIT2), 0x00);

        // Stop auto-function measure
        ScalerSetByte(P16_CD_DPTX_AUTO_ADJ_CTRL1, 0x80);

        // Set DPTX auto H boundary = 0x0000 ~ 0x1FFF
        ScalerSetByte(P16_C0_DPTX_H_BOUNDARY_H, 0x0F);
        ScalerSetByte(P16_C1_DPTX_H_BOUNDARY_STA_L, 0x00);
        ScalerSetByte(P16_C2_DPTX_H_BOUNDARY_END_L, 0xFF);
        ScalerSetBit(P16_C7_DPTX_GRN_NOISE_MARGIN, ~(_BIT1 | _BIT0), _BIT0);

        // Set DPTX auto V boundary = 0x0000 ~ 0x0FFF
        ScalerSetByte(P16_C3_DPTX_V_BOUNDARY_H, 0x0F);
        ScalerSetByte(P16_C4_DPTX_V_BOUNDARY_STA_L, 0x00);
        ScalerSetByte(P16_C5_DPTX_V_BOUNDARY_END_L, 0xFF);

        // Start DPTX measure
        ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

        // Pop-out measure result
        if(ScalerDpMacTxMeasureGetMeasureResult(&stMeasureSyncHV) == _FALSE)
        {
            DebugMessageDpTx("Tx Measure Pop Up Failed", 0x00);

            return _FALSE;
        }

        // Set DPTX VGIP sync polarity
        ScalerSetBit(P16_A1_DPTX_VGIP_SIGINV, ~(_BIT3 | _BIT2), ((stMeasureSyncHV.b1VSP == _DP_TX_SYNC_POLARITY_POSITIVE) ? 0x00 : _BIT3) | ((stMeasureSyncHV.b1HSP == _DP_TX_SYNC_POLARITY_POSITIVE) ? 0x00 : _BIT2));

        // Start auto
        ScalerSetBit(P16_CD_DPTX_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);

        // Wait for auto
        if(ScalerTimerPollingFlagProc(90, P16_CD_DPTX_AUTO_ADJ_CTRL1, _BIT0, 0x00) == _FALSE)
        {
            DebugMessageDpTx("Tx Measure Auto Failed", 0x00);

            return _FALSE;
        }

        // Update auto-function H result (13-bit)
        g_usDpMacTxInputHStartMeasure = (((WORD)ScalerGetBit(P16_C8_DPTX_BLU_NOISE_MARGIN, _BIT1) << 11) |
                                         ((WORD)ScalerGetBit(P16_D1_DPTX_H_START_END_H, 0xF0) << 4) |
                                         (ScalerGetByte(P16_D2_DPTX_H_START_L))) + 1;
        g_usDpMacTxInputHWidthMeasure = (((WORD)ScalerGetBit(P16_C8_DPTX_BLU_NOISE_MARGIN, _BIT0) << 12) |
                                         ((WORD)ScalerGetBit(P16_D1_DPTX_H_START_END_H, 0x0F) << 8) |
                                         (ScalerGetByte(P16_D3_DPTX_H_END_L))) + 1;
        g_usDpMacTxInputHWidthMeasure = g_usDpMacTxInputHWidthMeasure - g_usDpMacTxInputHStartMeasure + 1;

        // Calculate HWidth_Measure & HStart_Measure for 1/2/4 Pixel Mode
        // Calculate usHTotal & usHWidth for 1/2/4 Pixel Mode
        // Note: usHTotal & usHWidth are Calculated for Two Pixel Mode in ScalerDpMacTxMeasureGetMeasureResult
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
        {
            if(ScalerDpMacTxGetInputPixelMode(enumInputPort) == _DP_TX_2_PIXEL_MODE)
            {
                // For DP20 Two Pixel Mode
                g_usDpMacTxInputHWidthMeasure <<= 1;
                g_usDpMacTxInputHStartMeasure <<= 1;
            }
            else if(ScalerDpMacTxGetInputPixelMode(enumInputPort) == _DP_TX_4_PIXEL_MODE)
            {
                // For DP20 Four Pixel Mode
                g_usDpMacTxInputHWidthMeasure <<= 2;
                g_usDpMacTxInputHStartMeasure <<= 2;
                stMeasureSyncHV.usHTotal <<= 1;
                stMeasureSyncHV.usHWidth <<= 1;
            }
            else
            {
                // For DP20 One Pixel Mode
                stMeasureSyncHV.usHTotal >>= 1;
                stMeasureSyncHV.usHWidth >>= 1;
            }
        }
        else
#endif
        {
            // For DP14 Two Pixel Mode
            g_usDpMacTxInputHWidthMeasure <<= 1;
            g_usDpMacTxInputHStartMeasure <<= 1;
        }

        if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
        {
            g_usDpMacTxInputHWidthMeasure <<= 1;
            g_usDpMacTxInputHStartMeasure <<= 1;

            stMeasureSyncHV.usHTotal <<= 1;
            stMeasureSyncHV.usHWidth <<= 1;
        }

        // Update Freq result
        g_stDpMacTxInputTimingInfo.usHFreq = (_MEASURE_CLK * 10 * 2 / stMeasureSyncHV.usHSPeriod + 1) / 2;
        g_stDpMacTxInputTimingInfo.usVFreq = (_MEASURE_CLK * 1000 * 10 * 2 / stMeasureSyncHV.usHSPeriod / stMeasureSyncHV.usVSPeriod + 1) / 2;

        // Update auto-function V result
        g_stDpMacTxInputTimingInfo.usVStart = (((WORD)(ScalerGetByte(P16_CE_DPTX_VER_START_END_H) & 0xF0) << 4) | ScalerGetByte(P16_CF_DPTX_VER_START_L));
        g_stDpMacTxInputTimingInfo.usVHeight = ((((WORD)(ScalerGetByte(P16_CE_DPTX_VER_START_END_H) & 0x0F) << 8) | ScalerGetByte(P16_D0_DPTX_VER_END_L))) - g_stDpMacTxInputTimingInfo.usVStart + 1;

        g_stDpMacTxInputTimingInfo.usHWidth = g_usDpMacTxInputHWidthMeasure;
        g_stDpMacTxInputTimingInfo.usHStart = g_usDpMacTxInputHStartMeasure;

        // Update off-line measure result
        g_stDpMacTxInputTimingInfo.b1HSP = stMeasureSyncHV.b1HSP;
        g_stDpMacTxInputTimingInfo.b1VSP = stMeasureSyncHV.b1VSP;
        g_stDpMacTxInputTimingInfo.usHSWidth = ((DWORD)((stMeasureSyncHV.b1HSP == _DP_TX_SYNC_POLARITY_POSITIVE) ? stMeasureSyncHV.usHSWidth : (stMeasureSyncHV.usHSPeriod - stMeasureSyncHV.usHSWidth)) * GET_DP_TX_INPUT_PIXEL_CLK() * 100) / _MEASURE_CLK;
        g_stDpMacTxInputTimingInfo.usVSWidth = ((stMeasureSyncHV.b1VSP == _DP_TX_SYNC_POLARITY_POSITIVE) ? stMeasureSyncHV.usVSWidth : (stMeasureSyncHV.usVSPeriod - stMeasureSyncHV.usVSWidth));
        g_stDpMacTxInputTimingInfo.usVTotal = stMeasureSyncHV.usVSPeriod;
        g_stDpMacTxInputTimingInfo.usHTotal = stMeasureSyncHV.usHTotal;

        DebugMessageDpTx("Tx Measure Done!!", 0x00);
    }

    return _TRUE;
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Bandwidth Check
// Input Value  : enumInputPort --> target port
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxCloneSetDataPath(EnumDpStreamDataPath enumDataPath)
{
    SET_DP_MAC_TX_CLONE_DATA_PATH(enumDataPath);
}

//--------------------------------------------------
// Description  : DP Tx Bandwidth Check
// Input Value  : enumInputPort --> target port
// Output Value : None
//--------------------------------------------------
EnumDpStreamDataPath ScalerDpMacTxCloneGetDataPath(void)
{
    return GET_DP_MAC_TX_CLONE_DATA_PATH();
}
#endif

//--------------------------------------------------
// Description  : DP Tx Clone Check Interlace VTotal Odd
// Input Value  : None
// Output Value : _ODD/ _EVEN
//--------------------------------------------------
bit ScalerDpMacTxCloneCheckInterlaceVtotal(void)
{
    // Enable One Frame Measure
    ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~_BIT0, 0x00);
    ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~_BIT0, _BIT0);

    ScalerTimerPollingFlagProc(90, P16_42_DPTX_MEAS_CTL1, _BIT7, 0x00);

    // Pop up measurement result
    ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~_BIT6, _BIT6);

    // VSync Period
    PDATA_WORD(0) = ((((WORD)ScalerGetByte(P16_48_DPTX_MEAS_VS_PERIOD_A_M) & 0x0F) << 8) | (ScalerGetByte(P16_49_DPTX_MEAS_VS_PERIOD_A_L))) + 1;

    // Delay One Frame Plus 2ms Margin
    ScalerTimerDelayXms(10000 / g_stDpMacTxInputTimingInfo.usVFreq + 2);

    // Pop up measurement result
    ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~_BIT6, _BIT6);

    // VSync Period
    PDATA_WORD(1) = ((((WORD)ScalerGetByte(P16_48_DPTX_MEAS_VS_PERIOD_A_M) & 0x0F) << 8) | (ScalerGetByte(P16_49_DPTX_MEAS_VS_PERIOD_A_L))) + 1;

    DebugMessageDpTx("Clone Check Interlace Vtotal 1", PDATA_WORD(0));
    DebugMessageDpTx("Clone Check Interlace Vtotal 2", PDATA_WORD(1));

    if(PDATA_WORD(0) == PDATA_WORD(1))
    {
        return _EVEN;
    }
    else
    {
        // Set VTotal As the Smaller One
        g_stDpMacTxInputTimingInfo.usVTotal = (PDATA_WORD(0) < PDATA_WORD(1)) ? PDATA_WORD(0) : PDATA_WORD(1);
    }

    return _ODD;
}

//--------------------------------------------------
// Description  : DP Tx Clone Output Process
// Input Value  : Input Port Type to be Cloned
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxCloneOutputProc(EnumInputPort enumInputPort, EnumPortType enumPortType, bit bClone)
{
    // Do Nothing if Downstram unplug
    if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_UNPLUG)
    {
        return;
    }

#if(_DP_SUPPORT == _ON)
    // Only do This when Input is not DP or DP Tx Clone is enabled
    if((enumPortType != _PORT_DP) || (ScalerDpRxGetTxCloneEnable(enumInputPort) == _TRUE))
#endif
    {
        if(bClone == _FALSE)
        {
            // DebugMessageDpTx("Clone Off", 0);

            if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE)
            {
                ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_NONE);

                if(GET_DP_TX_HDCP_AUTH_STATE() != _DP_TX_HDCP_STATE_IDLE)
                {
                    ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
                }
            }
        }
        else
        {
            if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE) && (GET_DP_MAC_TX_CLONE_DATA_PATH() != _DATA_PATH_INVALID))
            {
                if(GET_DP_MAC_TX_CLONE_STREAM_PRECHECK() == _FALSE)
                {
                    if(ScalerDpMacTxClonePreCheck(enumInputPort, enumPortType) == _TRUE)
                    {
                        if(ScalerDpMacTxCloneGetInputInfo(enumInputPort, enumPortType) == _TRUE)
                        {
#if(_DP_SUPPORT == _ON)
                            if(enumPortType == _PORT_DP)
                            {
                                SET_DP_MAC_TX_CLONE_STREAM_INFO_TYPE(ScalerDpMacStreamRxGetStreamInfoType(ScalerDpRxGetMacStreamSourceType((ScalerDpRxGetMacSwitch(enumInputPort)))));
                            }
                            else
#endif
                            {
                                SET_DP_MAC_TX_CLONE_STREAM_INFO_TYPE(_INFO_TYPE_VIDEO);
                            }

                            SET_DP_MAC_TX_CLONE_STREAM_PRECHECK(_TRUE);
                        }
                        else
                        {
                            SET_DP_MAC_TX_CLONE_STREAM_INFO_TYPE(_INFO_TYPE_NONE);
                            SET_DP_MAC_TX_CLONE_STREAM_PRECHECK(_FALSE);
                            return;
                        }
                    }
                    else
                    {
                        SET_DP_MAC_TX_CLONE_STREAM_INFO_TYPE(_INFO_TYPE_NONE);
                        SET_DP_MAC_TX_CLONE_STREAM_PRECHECK(_FALSE);
                        return;
                    }
                }
                else
                {
                    if(GET_DP_MAC_TX_CLONE_DATA_PATH() != _DATA_PATH_NONE)
                    {
                        ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_CLONE);
                    }
                }
            }
            else
            {
                if(GET_DP_MAC_TX_CLONE_DATA_PATH() == _DATA_PATH_INVALID)
                {
                    DebugMessageDpTx("Tx Link Bw Check fai", GET_DP_TX_STREAM_SOURCE());
                    SET_DP_MAC_TX_CLONE_STREAM_PRECHECK(_FALSE);
                    ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_NONE);
                }

                if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_ON)
                {
                    DebugMessageDpTx("Tx Link Fail=> Reset Stream", GET_DP_TX_STREAM_SOURCE());

                    ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_NONE);
                }

                if(ScalerDpMacTxCloneGetCurrentInputPort() != enumInputPort)
                {
                    DebugMessageDpTx("DP TX Clone: Changed Input Port", enumInputPort);

                    ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_NONE);

                    if(GET_DP_TX_HDCP_AUTH_STATE() != _DP_TX_HDCP_STATE_IDLE)
                    {
                        ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
                    }
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Bandwidth Check
// Input Value  : enumInputPort --> target port
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacTxClonePreCheck(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
    // Check if Input Port is Supported
    if(ScalerDpMacTxCloneCheckInputPortSupport(enumInputPort) == _FALSE)
    {
        return _FALSE;
    }

    // Disable output if Rx Color Space is 420 but tx isn't supported
    if(ScalerDpMacTxBypass420Check(enumInputPort) == _FALSE)
    {
        return _FALSE;
    }

    // Link Training if Required
    if(((GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_ON) && (GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_TRAINING)) ||
       (ScalerDpMacTxLinkStatusCheck() == _FAIL))
    {
        DebugMessageDpTx("Clone Mode Tx State Not Link ON", GET_DP_TX_MODE_STATE());

        SET_DP_TX_FORCE_LINK_TRAINING();

        return _FALSE;
    }

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(enumPortType == _PORT_DP)
    {
        if(GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() != _LINK_ESTABLISH_READY)
        {
            return _FALSE;
        }
    }
#endif

    if(ScalerDpMacTxReAuthCheck(enumPortType) == _TRUE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Bandwidth Check
// Input Value  : enumInputPort --> target port
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacTxCloneGetInputInfo(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
#if(_DP_SUPPORT == _ON)
    StructDpInfo stDpInfo = {0};
#endif

    SET_DP_MAC_TX_CLONE_INPUT_PORT(enumInputPort);
    SET_DP_MAC_TX_CLONE_INPUT_PORT_TYPE(enumPortType);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(ScalerDrrFreeSyncDpGetEnable(enumInputPort) == _TRUE)
    {
        SET_FREESYNC_DP_TX_ENABLED();
    }
    else
    {
        CLR_FREESYNC_DP_TX_ENABLED();
    }
#endif

    // DPTX Color Info Get
    ScalerDpMacTxColorInfoSetting(enumInputPort);

    // Set Format Conversion for DP Tx Input
    ScalerDpMacTxCloneOutputRxMACSelect(enumInputPort, enumPortType);

    // DPTx CTS Fifo reset
    ScalerDpMacTxCtsFifoReset();

    // Get Tx Input Timing
#if(_DP_SUPPORT == _ON)
    if(enumPortType == _PORT_DP)
    {
        if(ScalerDpMacTxGetInputMeasureTimingInfo(enumInputPort) == _TRUE)
        {
            if(ScalerDpMacStreamRxGetMsaTimingInfo(enumInputPort, &stDpInfo) == _TRUE)
            {
                g_stDpMacTxInputTimingInfo = stDpInfo.stDpTimingInfo;
            }
            else
            {
                DebugMessageDpTx("7. DP Tx Clone Get Source MSA Info Fail", 0);
                return _FALSE;
            }
        }
        else
        {
            DebugMessageDpTx("7. DP Tx Clone Get Measure MSA Info Fail", 0);
            return _FALSE;
        }
    }
    else
#endif
    {
        if(ScalerDpMacTxGetInputMeasureTimingInfo(enumInputPort) == _FALSE)
        {
            DebugMessageDpTx("7. DP Tx Clone Get Measure MSA Info Fail", 0);
            return _FALSE;
        }
    }

    // DPTX Ycbcr420 Setting
    ScalerDpMacTxBypass420Setting(enumPortType);

    // Dp Tx Interlace info
    ScalerDpMacTxInterlaceInfoSetting(enumInputPort, enumPortType);

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Bandwidth Check
// Input Value  : enumInputPort --> target port
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxCloneBandwidthCheck(EnumInputPort enumInputPort)
{
    BYTE ucColorDepth = _COLOR_SPACE_RGB;
    DWORD ulBandwidth = 0;

    if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY)
    {
        ucColorDepth = GET_COLOR_DEPTH(enumInputPort);
    }
    else if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
    {
        ucColorDepth = GET_COLOR_DEPTH(enumInputPort) * 2;
    }
    else if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        ucColorDepth = (GET_COLOR_DEPTH(enumInputPort) * 3) >> 1;
    }
    else
    {
        ucColorDepth = GET_COLOR_DEPTH(enumInputPort) * 3;
    }

    // Get Link Bandwidth 0.1MHz
    ulBandwidth = (DWORD) GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() * _DP_TX_LINK_CLK_MHZ * 8 * 10;

#if(_DP_SUPPORT == _ON)
#if(_DP_TX_FEC_SUPPORT == _ON)
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_8B10B)
#endif
    {
        if(GET_DP_TX_FEC_ENCODE_8B10B() == _ENABLE)
        {
            if(ulBandwidth >= ((GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() == _ENABLE) ? (ScalerGlobalComputeDwordMulDiv(GET_DP_TX_INPUT_PIXEL_CLK(), ((DWORD)ucColorDepth * 1029), 1000)) : (ScalerGlobalComputeDwordMulDiv(GET_DP_TX_INPUT_PIXEL_CLK(), ((DWORD)ucColorDepth * 1024), 1000))))
            {
                ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_CLONE);
                SET_DP_TX_FEC_CLONE_ENABLE_8B10B();
            }
            else
            {
                DebugMessageDpTx("Link BW is not enough for DP TX Clone_Rx FEC ON and Tx FEC ON case", 0);
                CLR_DP_TX_FEC_CLONE_ENABLE_8B10B();
                SET_DP_TX_FEC_ENCODE_8B10B(_DISABLE);
            }
        }
        else
        {
            // BW must >= SSC 0.5%
            if(ulBandwidth >= ((GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() == _ENABLE) ? (ScalerGlobalComputeDwordMulDiv(GET_DP_TX_INPUT_PIXEL_CLK(), ((DWORD)ucColorDepth * 1005), 1000)) : (ScalerGlobalComputeDwordMulDiv(GET_DP_TX_INPUT_PIXEL_CLK(), ucColorDepth, 1))))
            {
                ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_CLONE);
                CLR_DP_TX_FEC_CLONE_ENABLE_8B10B();
            }
            else
            {
                DebugMessageDpTx("Link BW is not enough for DP TX Clone_Rx FEC ON and Tx FEC OFF case", 0);
                SET_DP_TX_EXCEED_LINK_BANDWIDTH();
                CLR_DP_TX_FEC_CLONE_ENABLE_8B10B();
            }
        }
    }
#endif
 /////SettingEnd///
#endif
}

//--------------------------------------------------
// Description  : DP Tx Source Switch Fixed Mode Check
// Input Value  : enumDisplayMode
// Output Value : _TRUE: Fixed Mode / _FALSE: Auto Mode
//--------------------------------------------------
bit ScalerDpMacTxCloneGetSourceSwitchFixedMode(EnumDisplayMode enumDisplayMode)
{
    if(enumDisplayMode == _DISPLAY_MODE_1P)
    {
        return (_DP_TX_SOURCE_SWITCH_MODE_1P == _DP_TX_SOURCE_FIXED_PORT);
    }
    else
    {
        return (_DP_TX_SOURCE_SWITCH_MODE_MTP == _DP_TX_SOURCE_FIXED_PORT);
    }
}

//--------------------------------------------------
// Description  : DP Tx MSA MISC0/MISC1 Setting
// Input Value  : enumInputPort --> target port
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxColorInfoSetting(EnumInputPort enumInputPort)
{
    // Set Color Space
    switch(GET_COLOR_SPACE(enumInputPort))
    {
        case _COLOR_SPACE_RGB:
        default:
            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
            break;

        case _COLOR_SPACE_YCBCR444:
            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
            break;

        case _COLOR_SPACE_YCBCR422:
            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
            break;

        case _COLOR_SPACE_YCBCR420:
            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR420);
            break;

        case _COLOR_SPACE_Y_ONLY:
            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
            break;

        case _COLOR_SPACE_RAW:
            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RAW);
            break;
    }

    if(ScalerDpMacTxNewComponentModeAvailable() == _FALSE)
    {
        if(GET_DP_TX_DOWNSTREAM_VSC_SDP_SUPPORT() == _TRUE)
        {
            switch(GET_COLORIMETRY(enumInputPort))
            {
                // Set Tx Colorimetry to VSC SDP Format for XRGB, SCRGB, DCI_P3, COLOR_PROFILE
                case _COLORIMETRY_RGB_XRRGB:
                    SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_EXT);
                    SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_XRRGB);
                    break;

                case _COLORIMETRY_RGB_SCRGB:
                    SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_EXT);
                    SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_SCRGB);
                    break;

                case _COLORIMETRY_RGB_DCI_P3:
                    SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_EXT);
                    SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_DCI_P3);
                    break;

                case _COLORIMETRY_RGB_COLOR_PROFILE:
                    SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_EXT);
                    SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE);
                    break;

                default:
                    // Set Colorimetry
                    SET_DP_TX_INPUT_COLORIMETRY(GET_COLORIMETRY(enumInputPort));

                    // Set Ext Colorimetry
                    SET_DP_TX_INPUT_EXT_COLORIMETRY(GET_EXT_COLORIMETRY(enumInputPort));
                    break;
            }
        }
        else
        {
            // Set Colorimetry
            SET_DP_TX_INPUT_COLORIMETRY(GET_COLORIMETRY(enumInputPort));

            // Set Ext Colorimetry
            SET_DP_TX_INPUT_EXT_COLORIMETRY(GET_EXT_COLORIMETRY(enumInputPort));
        }
    }
    else
    {
        // Set Colorimetry
        SET_DP_TX_INPUT_COLORIMETRY(GET_COLORIMETRY(enumInputPort));

        // Set Ext Colorimetry
        SET_DP_TX_INPUT_EXT_COLORIMETRY(GET_EXT_COLORIMETRY(enumInputPort));
    }

    // Set RGB Quantization Range
    SET_DP_TX_INPUT_COLOR_RGB_QUANTIZATION_RANGE(GET_COLOR_RGB_QUANTIZATION_RANGE(enumInputPort));

    // Set YCC Quantization Range
    SET_DP_TX_INPUT_COLOR_YCC_QUANTIZATION_RANGE(GET_COLOR_YCC_QUANTIZATION_RANGE(enumInputPort));

    // Set Color Content Type
    SET_DP_TX_INPUT_COLOR_CONTENT_TYPE(GET_CONTENT_TYPE(enumInputPort));

    // Set Color Depth
    if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_RAW)
    {
        switch(GET_COLOR_DEPTH(enumInputPort))
        {
            case _COLOR_DEPTH_6_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x01);
                break;

            case _COLOR_DEPTH_7_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x02);
                break;

            case _COLOR_DEPTH_8_BITS:
            default:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x03);
                break;

            case _COLOR_DEPTH_10_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x04);
                break;

            case _COLOR_DEPTH_12_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x05);
                break;

            case _COLOR_DEPTH_14_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x06);
                break;

            case _COLOR_DEPTH_16_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x07);
                break;
        }
    }
    else
    {
        switch(GET_COLOR_DEPTH(enumInputPort))
        {
            case _COLOR_DEPTH_6_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x00);
                break;

            case _COLOR_DEPTH_8_BITS:
            default:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x01);
                break;

            case _COLOR_DEPTH_10_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x02);
                break;

            case _COLOR_DEPTH_12_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x03);
                break;

            case _COLOR_DEPTH_16_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x04);
                break;
        }
    }

    DebugMessageDpTx("Get DP Tx Color Depth", GET_DP_TX_INPUT_COLOR_DEPTH());
}

//--------------------------------------------------
// Description  : DP Tx Interlace Info Setting
// Input Value  : InputPort & PortType
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxInterlaceInfoSetting(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
    if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
    {
        SET_DP_TX_INPUT_INTERLACE_MODE(_ON);

        if(enumPortType != _PORT_DP)
        {
            SET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER(ScalerDpMacTxCloneCheckInterlaceVtotal());
        }
        else
        {
#if(_DP_SUPPORT == _ON)
            SET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER(ScalerDpMacStreamRxCheckInterlaceVtotal(enumInputPort));
#endif
        }
    }
    else
    {
        SET_DP_TX_INPUT_INTERLACE_MODE(_OFF);
    }
}

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
//--------------------------------------------------
// Description  : DP Tx Clone Mode Switch
// Input Value  : Clone Mode on/off
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxCloneModeSwitch(EnumDPCloneOutputStatus enumClone)
{
    SET_DP_TX_TARGET_CLONE_MODE(enumClone);

#if(_DP_SUPPORT == _ON)
    SET_DP_RX_CAPABILITY_SWITCHED();
#endif
}

//--------------------------------------------------
// Description  : DP Tx Block Status Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacTxBlockStatusCheck(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_DP_SUPPORT == _ON)
    if(GET_DP_RX_TARGET_MST_PORT() != _DP_MST_NO_PORT)
    {
        DebugMessageDpTx("8. Dp Tx Block ON", 1);

        ScalerDpMacTxBlockStatusSet(_ENABLE);
    }
    else
#endif
    {
        if(GET_DP_TX_TARGET_CLONE_MODE() == _FALSE)
        {
            DebugMessageDpTx("8. Dp Tx Block OFF", 0);

            ScalerDpMacTxBlockStatusSet(_DISABLE);
        }
        else
        {
            DebugMessageDpTx("8. Dp Tx Block ON", 1);

            ScalerDpMacTxBlockStatusSet(_ENABLE);
        }
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Block Status Set
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxBlockStatusSet(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if(GET_DP_TX_HPD_DETECTION_ENABLE() == _DISABLE)
        {
            // Clr All flag
            ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);

            // Enable Short IRQ and Disable Long IRQ
            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~(_BIT6 | _BIT5), _BIT6);

            // Enable HPD Detection
            ScalerSetBit(PBB_70_HPD_CTRL, ~_BIT7, _BIT7);

            // For DP Tx HPD Proc Judge First HPD From Low to High
            SET_DP_TX_HPD_FIRST_DETECT();
        }
    }
    else
    {
        if(GET_DP_TX_HPD_DETECTION_ENABLE() == _ENABLE)
        {
            // Disable HPD Detection
            ScalerSetBit(PBB_70_HPD_CTRL, ~_BIT7, 0x00);

            // Disable HPD IRQ
            ScalerSetByte(PBB_72_HPD_IRQ_EN, 0x00);

            // Clr All flag
            ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);
        }
    }
}
#endif

//--------------------------------------------------
// Description  : DP Tx Clone Output Process
// Input Value  : Input Port Type to be Cloned
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacTxCloneCheckInputPortSupport(EnumInputPort enumInputPort)
{
    if((enumInputPort == _D0_INPUT_PORT) ||
       (enumInputPort == _D1_INPUT_PORT) ||
       (enumInputPort == _D2_INPUT_PORT) ||
       (enumInputPort == _D3_INPUT_PORT) ||
       (enumInputPort == _D4_INPUT_PORT) ||
       (enumInputPort == _A0_INPUT_PORT))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Check Link Status
// Input Value  : None
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
bit ScalerDpMacTxLinkStatusCheck(void)
{
    if(GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS)
    {
        return _FAIL;
    }

    // Check Downstream Power Status
    if(ScalerDpAuxTxNativeRead(0x00, 0x06, 0x00, 1, pData) == _TRUE)
    {
        pData[0] = pData[0] & (_BIT2 | _BIT1 | _BIT0);

        if(pData[0] != 0x01)
        {
            return _FAIL;
        }
    }
    else
    {
        return _FAIL;
    }

    // Check Link Status
    if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x02, 3, pData) == _TRUE)
    {
        if(((GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() == 1) && ((pData[0] & 0x07) != 0x07)) ||
           ((GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() == 2) && ((pData[0] & 0x77) != 0x77)) ||
           ((GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() == 4) && (((pData[0] & 0x77) != 0x77) || ((pData[1] & 0x77) != 0x77))) ||
           ((GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM() != 1) && ((pData[2] & 0x01) != 0x01)))
        {
            return _FAIL;
        }
    }
    else
    {
        return _FAIL;
    }

    return _SUCCESS;
}

#if(_DP_TX_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Set Audio Channel Count
// Input Value  :
// Output Value : Changed => _TRUE or No Changed => _FALSE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioFormatSetting(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxSdpAudioFormatSetting_128b132b();
    }
    else
#endif
    {
        ScalerDpMacTxSdpAudioFormatSetting_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Set Audio Channel Count
// Input Value  :
// Output Value : Changed => _TRUE or No Changed => _FALSE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioFormatSetting_8b10b(void)
{
    BYTE ucPacketPerSample = 0;
    WORD usMaxAudioPacket = 0;
    WORD usBe2Be = 0;
    WORD usSdpPacketHB = 0;
    WORD usMaxPacketHB = 0;

    WORD usSdpPacketVB = 0;
    WORD usMaxPacketVB = 0;

    if(GET_DP_TX_AUDIO_INPUT_PATH() == _DP_TX_AUDIO_PATH_RS_DECODER)
    {
        // Set TX Audio Channel Count
        SET_DP_TX_AUDIO_CHANNEL_COUNT(ScalerGetBit(PBC_4A_MST_SEC_PKT_HB3, (_BIT6 | _BIT5 | _BIT4)) >> 4);

        // Set TX Audio Coding Type
        SET_DP_TX_AUDIO_CODING_TYPE(ScalerGetBit(PBC_4A_MST_SEC_PKT_HB3, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        // Set Audio Source From MST(MST2SST), use RS Decoder Path
        ScalerSetBit(PBC_18_AUD_FUNCTION_CTRL1, ~_BIT7, _BIT7);
    }
    else
    {
#if((_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON) && (_DSC_DECODER_SUPPORT == _ON))
        if((GET_DP_TX_DOWNSTREAM_DSC_SUPPORT() == _ENABLE) && (GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH() == _ENABLE))
        {
            DebugMessageAudio("[SST2SST] AudioFormat DSC PassThrough", 0x00);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
            // =========================
            // Check Upstream Coding Type
            // =========================

            if(ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT()) == _CODING_TYPE_128B132B)
            {
#if(_AUDIO_SUPPORT == _ON)
                // Set TX Audio Channel Count
                SET_DP_TX_AUDIO_CHANNEL_COUNT(ScalerAudioGetRxChannelCount(_AUDIO_DPTX_OUT));

                // Set TX Audio Coding Type
                SET_DP_TX_AUDIO_CODING_TYPE(ScalerAudioGetRxCodingType(_AUDIO_DPTX_OUT));

                // Set Audio Channel Status and Channel Number
                ScalerDpMacTxSdpAudioChannelStatusSetting_8b10b();
#endif // End of #if(_AUDIO_SUPPORT == _ON)

                // Set Audio Source From SST(Clone), Use I2S Path
                ScalerSetBit(PBC_18_AUD_FUNCTION_CTRL1, ~_BIT7, 0x00);

                DebugMessageAudio("[SST2SST] Use I2S Path(128B132B to 8B10B)", 0x00);
            }
            else
#endif // End of #if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
            {
#if(_AUDIO_SUPPORT == _ON)
                // Set TX Audio Channel Count
                SET_DP_TX_AUDIO_CHANNEL_COUNT(ScalerAudioGetRxChannelCount(_AUDIO_DPTX_OUT));

                // Set TX Audio Coding Type
                SET_DP_TX_AUDIO_CODING_TYPE(ScalerAudioGetRxCodingType(_AUDIO_DPTX_OUT));
#endif // End of #if(_AUDIO_SUPPORT == _ON)

                // Set Audio Source From MST(MST2SST) with DSC Stream Clone
                ScalerSetBit(PBC_18_AUD_FUNCTION_CTRL1, ~_BIT7, _BIT7);

                DebugMessageAudio("[SST2SST] Use RS_Decoder(8B10B to 8B10B)", 0x00);
            }
        }
        else
#endif
        {
#if(_AUDIO_SUPPORT == _ON)
            // Set TX Audio Channel Count
            SET_DP_TX_AUDIO_CHANNEL_COUNT(ScalerAudioGetRxChannelCount(_AUDIO_DPTX_OUT));

            // Set TX Audio Coding Type
            SET_DP_TX_AUDIO_CODING_TYPE(ScalerAudioGetRxCodingType(_AUDIO_DPTX_OUT));

            // Set Audio Channel Status and Channel Number
            ScalerDpMacTxSdpAudioChannelStatusSetting_8b10b();
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            // Set Audio Source From SST(Clone), Use I2S Path
            ScalerSetBit(PBC_18_AUD_FUNCTION_CTRL1, ~_BIT7, 0x00);
        }
    }

    if(GET_DP_TX_AUDIO_CHANNEL_COUNT() > _AUDIO_CHANNEL_COUNT_2)
    {
        // Set 8 Channel Layout and Water Level of Audio SFIFO For Capturing Audio Sample
        ScalerSetBit(PBC_18_AUD_FUNCTION_CTRL1, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT3));

        // Set I2S Received Mode As 8 Channel Mode
        ScalerSetBit(PBC_48_AUD_FUNCTION_CTRL3, ~_BIT3, _BIT3);

        // Set I2S Data(SD) For 8 Channel and Enable HW Mode for Transmitting Preamble / Channel Status / Parity bit
        ScalerSetBit(PBC_8F_DPTX_I2S_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

        // Set Preamble Insert Method: All Channel
        ScalerSetBit(PBC_8F_DPTX_I2S_CTRL, ~_BIT3, _BIT3);

        // Set Audio Packet Per Sample
        ucPacketPerSample = 40;
    }
    else
    {
        // Set 2 Channel Layout and Water Level of Audio SFIFO For Capturing Audio Sample
        ScalerSetBit(PBC_18_AUD_FUNCTION_CTRL1, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

        // Set I2S Received Mode As 2 Channel Mode
        ScalerSetBit(PBC_48_AUD_FUNCTION_CTRL3, ~_BIT3, 0x00);

        // Set I2S Data(SD) For 2 Channel and Enable HW Mode for Transmitting Preamble / Channel Status / Parity bit
        ScalerSetBit(PBC_8F_DPTX_I2S_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

        // Set Preamble Insert Method: 2-Channel
        ScalerSetBit(PBC_8F_DPTX_I2S_CTRL, ~_BIT3, 0x00);

        // Set Audio Packet Per Sample
        ucPacketPerSample = 20;
    }

    // sec_end_cnt = max_audio_packet (lane_num, max_long_packet_cnt) + safe_margin
    // max_audio_packet = SS&SE + HEADER&ECC BYTES / lane_num + [(max_long_packet_cnt+1) * (minimum packet payload + 4)] / lane_num.
    usMaxAudioPacket = 2 + ((8 + ucPacketPerSample) / GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM());

    // SDP_packet = SS&SE + HEADER&ECC BYTES / lane_num + (DATA_BYTES_HB + DATA_P_BYTES_HB) / lane_num.
    usSdpPacketHB = 2 + ((8 + 32 + 8) / GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM());

    // MaxPacket = max(MaxAudioPacket, SdpPacket)
    usMaxPacketHB = MAXOF(usMaxAudioPacket, usSdpPacketHB);

    // Get BE2BE Period with Htotal
    usBe2Be = (DWORD)g_stDpMacTxInputTimingInfo.usHTotal * 270 * GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() / GET_DP_TX_INPUT_PIXEL_CLK();

    // Get 70% of Blanking Period
    usBe2Be = (DWORD)(usBe2Be - GET_DP_TX_HORIZONTAL_DE_PERIOD()) * 7 / 10;

    // if BS2BE > max(MaxAudioPacket,SdpPacket), Sec_end_count = BS2BE - max(MaxAudioPacket,SdpPacket)
    // else Sec_end_count = 0;
    if(usBe2Be > usMaxPacketHB)
    {
        // Set Secondary End Count HBlank
        ScalerSetByte(PBB_D4_ARBITER_SEC_END_CNT_HB, HIBYTE(usBe2Be - usMaxPacketHB));
        ScalerSetByte(PBB_D5_ARBITER_SEC_END_CNT_LB, LOBYTE(usBe2Be - usMaxPacketHB));
    }
    else
    {
        // Set Seccondary End Count HBlank
        ScalerSetByte(PBB_D4_ARBITER_SEC_END_CNT_HB, 0x00);
        ScalerSetByte(PBB_D5_ARBITER_SEC_END_CNT_LB, 0x00);
    }

    // SET SEC_END_CNT_VBlank
    // SET Sec End Cnt VBlnk Md to Use Reg_Sec_End_Cnt_VBlnk
    ScalerSetBit(PBB_DB_DPTX_TOP_RSV2, ~_BIT7, _BIT7);

    // SDP_packet = SS&SE + HEADER&ECC BYTES / lane_num + (DATA_BYTES_VB + DATA_P_BYTES_VB) / lane_num.
    usSdpPacketVB = 2 + ((8 + 128 + 32) / GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM());
    usMaxPacketVB = MAXOF(usMaxAudioPacket, usSdpPacketVB);

    // Get BE2BE Period with Htotal
    usBe2Be = (DWORD)g_stDpMacTxInputTimingInfo.usHTotal * 270 * GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() / GET_DP_TX_INPUT_PIXEL_CLK();

    // Get 70% of Blanking Period
    usBe2Be = (DWORD)(usBe2Be - GET_DP_TX_HORIZONTAL_DE_PERIOD()) * 7 / 10;

    if(usBe2Be > usMaxPacketVB)
    {
        // Set Secondary End Count VBlank
        ScalerSetBit(PBB_DB_DPTX_TOP_RSV2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usBe2Be - usMaxPacketVB));
        ScalerSetByte(PBB_FF_DPTX_TOP_RSV10, LOBYTE(usBe2Be - usMaxPacketVB));
    }
    else
    {
        // Set Secondary End Count VBlank
        ScalerSetBit(PBB_DB_DPTX_TOP_RSV2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(PBB_FF_DPTX_TOP_RSV10, 0x00);
    }

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))
    if(GET_DP_TX_AUDIO_STAND_ALONE() == _ON)
    {
        BYTE ucSecIdleEndCount = 0x00;

        // Calculate End Count in Ilde Pattern Mode
        ucSecIdleEndCount = 2 + (48 / GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM());

        // Add 50% Margin
        ucSecIdleEndCount = (ucSecIdleEndCount * 3) / 2;

        // Set Seccondary End Count
        ScalerSetByte(PBB_F0_ARBITER_SEC_IDLE_END_CNT, ucSecIdleEndCount);
    }
#endif

    // Set SEC END CNT Double Buffer
    SET_DP_TX_SEC_END_CNT_DB_8B10B();
}

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp TX Set Audio Channel Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpAudioChannelStatusSetting_8b10b(void)
{
    StructAudioChannelInfo stDpMacTxAudioStatus = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    stDpMacTxAudioStatus = ScalerAudioGetRxChannelStatus(_AUDIO_DPTX_OUT);

    // Set Audio Channel Info
    ScalerSetByte(PBC_85_CH_STATUS_0, stDpMacTxAudioStatus.ucChannelStaus0);
    ScalerSetByte(PBC_86_CH_STATUS_1, stDpMacTxAudioStatus.ucChannelStaus1);
    ScalerSetByte(PBC_87_CH_STATUS_2, stDpMacTxAudioStatus.ucChannelStaus2);
    ScalerSetByte(PBC_88_CH_STATUS_3, stDpMacTxAudioStatus.ucChannelStaus3);
    ScalerSetByte(PBC_89_CH_STATUS_4, stDpMacTxAudioStatus.ucChannelStaus4);

    ScalerSetByte(PBC_7C_CH_STATUS_CH12, stDpMacTxAudioStatus.ucChannelNumber12);
    ScalerSetByte(PBC_7D_CH_STATUS_CH34, stDpMacTxAudioStatus.ucChannelNumber34);
    ScalerSetByte(PBC_7E_CH_STATUS_CH56, stDpMacTxAudioStatus.ucChannelNumber56);
    ScalerSetByte(PBC_7F_CH_STATUS_CH78, stDpMacTxAudioStatus.ucChannelNumber78);
}
#endif

//--------------------------------------------------
// Description  : DP Tx Get Audio Format Change
// Input Value  : None
// Output Value : Changed => _TRUE or No Changed => _FALSE
//--------------------------------------------------
bit ScalerDpMacTxSdpAudioGetFormatChange(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacTxSdpAudioGetFormatChange_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacTxSdpAudioGetFormatChange_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Get Audio Format Change
// Input Value  : None
// Output Value : Changed => _TRUE or No Changed => _FALSE
//--------------------------------------------------
bit ScalerDpMacTxSdpAudioGetFormatChange_8b10b(void)
{
    BYTE ucSamplingFrequency = 0;
    EnumAudioChannelCount enumChannelCount = 0;
    BYTE ucCodingType = 0;
    bit bIsChanged = _FALSE;

    if(GET_DP_TX_AUDIO_INPUT_PATH() == _DP_TX_AUDIO_PATH_RS_DECODER)
    {
        // Get The Latest Input Audio Channel Count
        enumChannelCount = ScalerGetBit(PBC_4A_MST_SEC_PKT_HB3, (_BIT6 | _BIT5 | _BIT4)) >> 4;

        // Get The Latest Input Audio Coding Type
        ucCodingType = ScalerGetBit(PBC_4A_MST_SEC_PKT_HB3, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
#if(_AUDIO_SUPPORT == _ON)
        // Get The Latest Input Audio Channel Count
        enumChannelCount = ScalerAudioGetRxChannelCount(_AUDIO_DPTX_OUT);

        // Get The Latest Input Audio Coding Type
        ucCodingType = ScalerAudioGetRxCodingType(_AUDIO_DPTX_OUT);
#endif // End of #if(_AUDIO_SUPPORT == _ON)
    }

    // Get Audio Sampling Frequency
    ucSamplingFrequency = ScalerDpMacTxSdpAudioGetSamplingFreqRange();

    // Check If Sampling Frequency is Changed
    if(ucSamplingFrequency != GET_DP_TX_AUDIO_SAMPLING_FREQUENCY())
    {
        DebugMessageAudio("[DPTX] 1.4 Audio Changed FS", ucSamplingFrequency);

        bIsChanged = _TRUE;

        SET_DP_TX_AUDIO_SAMPLING_FREQUENCY(ucSamplingFrequency);
    }

    // Check If Channel Count is Changed
    if(enumChannelCount != GET_DP_TX_AUDIO_CHANNEL_COUNT())
    {
        DebugMessageAudio("[DPTX] 1.4 Audio Changed CC", enumChannelCount);

        bIsChanged = _TRUE;
    }

    // Check If Coding Type is Changed
    if(ucCodingType != GET_DP_TX_AUDIO_CODING_TYPE())
    {
        DebugMessageAudio("[DPTX] 1.4 Audio Changed CT", ucCodingType);

        bIsChanged = _TRUE;
    }

    return bIsChanged;
}

//--------------------------------------------------
// Description  : DP Tx Get Audio Sampling Frequency Packet
// Input Value  :
// Output Value : Packet Number
//--------------------------------------------------
WORD ScalerDpMacTxSdpAudioGetSamplingFreqPacket(EnumDPTxAudioSamplingFreq enumSamplingFrequency)
{
    CLR_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ();

    switch(enumSamplingFrequency)
    {
        case _DP_TX_AUDIO_FREQ_32K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_32K);
            return 320;

        case _DP_TX_AUDIO_FREQ_44_1K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_44_1K);
            return 441;

        case _DP_TX_AUDIO_FREQ_48K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_48K);
            return 480;

        case _DP_TX_AUDIO_FREQ_64K:

            return 640;

        case _DP_TX_AUDIO_FREQ_88_2K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_88_2K);
            return 882;

        case _DP_TX_AUDIO_FREQ_96K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_96K);
            return 960;

        case _DP_TX_AUDIO_FREQ_128K:

            return 1280;

        case _DP_TX_AUDIO_FREQ_176_4K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_176_4K);
            return 1764;

        case _DP_TX_AUDIO_FREQ_192K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_192K);
            return 1920;

        case _DP_TX_AUDIO_FREQ_256K:

            return 2560;

        case _DP_TX_AUDIO_FREQ_352_8K:

            return 3528;

        case _DP_TX_AUDIO_FREQ_384K:

            return 3840;

        case _DP_TX_AUDIO_FREQ_512K:

            return 5120;

        case _DP_TX_AUDIO_FREQ_705_6K:

            return 7056;

        case _DP_TX_AUDIO_FREQ_768K:

            return 7680;

        case _DP_TX_AUDIO_FREQ_NO_AUDIO:
        default:

            return 0;
    }
}

//--------------------------------------------------
// Description  : DP Tx Get Audio Sampling Frequency Range
// Input Value  :
// Output Value : Audio Frequency Range
//--------------------------------------------------
BYTE ScalerDpMacTxSdpAudioGetSamplingFreqRange(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacTxSdpAudioGetSamplingFreqRange_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacTxSdpAudioGetSamplingFreqRange_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Get Audio Sampling Frequency Range
// Input Value  :
// Output Value : Audio Frequency Range
//--------------------------------------------------
BYTE ScalerDpMacTxSdpAudioGetSamplingFreqRange_8b10b(void)
{
    BYTE ucSampleFreqRange = (ScalerGetBit(PBC_4F_SEC_AUD_SAMPLE_CNT_HB, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

    WORD usAudioPacket = (WORD)((ScalerGetBit(PBC_4F_SEC_AUD_SAMPLE_CNT_HB, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | ScalerGetByte(PBC_50_SEC_AUD_SAMPLE_CNT_LB));

    usAudioPacket = usAudioPacket;

    return ucSampleFreqRange;
}

//--------------------------------------------------
// Description  : Set DP TX Audio Play for DP MST2SST
// Input Value  : EnumDPTxAudioPlayState
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpAudioPlayProc(EnumDPTxAudioPlayState enumPlayState)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxSdpAudioPlayProc_128b132b(enumPlayState);
    }
    else
#endif
    {
        ScalerDpMacTxSdpAudioPlayProc_8b10b(enumPlayState);
    }
}

//--------------------------------------------------
// Description  : Set DP TX Audio Play for DP MST2SST
// Input Value  : EnumDPTxAudioPlayState
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpAudioPlayProc_8b10b(EnumDPTxAudioPlayState enumPlayState)
{
    switch(enumPlayState)
    {
        case _DP_TX_AUDIO_OFF:

            DebugMessageAudio("[DPTX] 1.4 Audio Play Off", enumPlayState);

            // Enable VBID[4] Audio Mute Flag
            ScalerDpMacTxSetAudioMuteFlag(_ENABLE);

            // Disable Audio Timestamp
            ScalerDpMacTxSdpAudioTimestampProc(_DISABLE);

            // Disable TX Audio Frequency Detection
            ScalerSetBit(PBC_4C_SEC_AUD_FREQDET_CTRL, ~(_BIT7 | _BIT3 | _BIT1), 0x00);

            // Disable All Audio Stream Decode
            ScalerDpMacTxSdpAudioDecodeDisable();

            // Disable Audio Stream
            ScalerDpMacTxSdpAudioStreamProc(_DISABLE);

            // Clear Audio Related Falg
            CLR_DP_TX_AUDIO_READY_TO_PLAY();
            CLR_DP_TX_AUDIO_SAMPLING_FREQUENCY();
            CLR_DP_TX_AUDIO_CHANNEL_COUNT();
            CLR_DP_TX_AUDIO_CODING_TYPE();

            break;

        case _DP_TX_AUDIO_PRESET:

            DebugMessageAudio("[DPTX] 1.4 Audio Play Preset", enumPlayState);

            // Set Keepout Regien of MSA as 0
            ScalerSetBit(PBB_D1_AUTO_HDEALY0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

            // Set Keepout Regien of Audio as 5
            ScalerSetBit(PBB_D1_AUTO_HDEALY0, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(PBB_D2_AUTO_HDEALY1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

            // Set Keepout Regien of Other Sec Data as 15
            ScalerSetBit(PBB_D2_AUTO_HDEALY1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(PBB_D3_LFIFO_WL_SET, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Set Audio Channel Count, Coding Type and End Count of SDP
            ScalerDpMacTxSdpAudioFormatSetting();

            // Enable Audio Stream
            ScalerDpMacTxSdpAudioStreamProc(_ENABLE);

            // Enable Audio Stream Decode
            ScalerDpMacTxSdpAudioDecodeEnable(GET_DP_TX_STREAM_SOURCE());

            // Enable TX Audio Frequency Detection
            ScalerSetBit(PBC_4C_SEC_AUD_FREQDET_CTRL, ~(_BIT7 | _BIT3 | _BIT1), _BIT7);

            SET_DP_TX_AUDIO_READY_TO_PLAY();
            CLR_DP_TX_AUDIO_SAMPLING_FREQUENCY();

            break;

        case _DP_TX_AUDIO_FORMAT_CHANGE:

            DebugMessageAudio("[DPTX] 1.4 Audio Play Change", enumPlayState);

            // Enable VBID[4] Audio Mute Flag
            ScalerDpMacTxSetAudioMuteFlag(_ENABLE);

            // Disable Audio Timestamp
            ScalerDpMacTxSdpAudioTimestampProc(_DISABLE);

            // Disable All Audio Stream Decode
            ScalerDpMacTxSdpAudioDecodeDisable();

            // Disable Audio Stream
            ScalerDpMacTxSdpAudioStreamProc(_DISABLE);

            // Set Audio Channel Count, Coding Type and End Count of SDP
            ScalerDpMacTxSdpAudioFormatSetting();

            // Enable Audio Stream
            ScalerDpMacTxSdpAudioStreamProc(_ENABLE);

            // Enable Audio Stream Decode
            ScalerDpMacTxSdpAudioDecodeEnable(GET_DP_TX_STREAM_SOURCE());

            break;

        case _DP_TX_AUDIO_ON:

            DebugMessageAudio("[DPTX] 1.4 Audio Play On", enumPlayState);

            // Enable Audio Timestamp
            ScalerDpMacTxSdpAudioTimestampProc(_ENABLE);

            // Disable VBID[4] Audio Mute Flag
            ScalerDpMacTxSetAudioMuteFlag(_DISABLE);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Enable or Disable Audio Timestamp of DP TX SDP
// Input Value  : _ENABLE or _DISABLE
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioTimestampProc(bit bEnable)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxSdpAudioTimestampProc_128b132b(bEnable);
    }
    else
#endif
    {
        ScalerDpMacTxSdpAudioTimestampProc_8b10b(bEnable);
    }
}

//--------------------------------------------------
// Description  : Enable or Disable Audio Timestamp of DP TX SDP
// Input Value  : _ENABLE or _DISABLE
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioTimestampProc_8b10b(bit bEnable)
{
    DWORD ulMaud = 0;
    DWORD ulNaud = 0;

    if(bEnable == _ENABLE)
    {
        // Naud
        ulNaud = 32768;

        // Maud
        ulMaud = (DWORD)(512 * ((ulNaud * ScalerDpMacTxSdpAudioGetSamplingFreqPacket(GET_DP_TX_AUDIO_SAMPLING_FREQUENCY())) / _DP_TX_LINK_CLK_MHZ)) / 1000 / 10;

        // Set Maud
        ScalerSetByte(PBC_20_AUD_TS_MAUD_H, (BYTE)(ulMaud >> 16));
        ScalerSetByte(PBC_21_AUD_TS_MAUD_M, (BYTE)(ulMaud >> 8));
        ScalerSetByte(PBC_22_AUD_TS_MAUD_L, (BYTE)(ulMaud >> 0));

        // Sed Naud
        ScalerSetByte(PBC_23_AUD_TS_NAUD_H, (BYTE)(ulNaud >> 16));
        ScalerSetByte(PBC_24_AUD_TS_NAUD_M, (BYTE)(ulNaud >> 8));
        ScalerSetByte(PBC_25_AUD_TS_NAUD_L, (BYTE)(ulNaud >> 0));

        // Set Header for Audio Timestamp
        ScalerDpMacTxSdpSetHeaderByte(_SEC_PACKET_TYPE_AUDIO_TIMESTAMP, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);

        // Enable Audio Timestamp
        ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Disable Audio Timestamp
        ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~_BIT1, 0x00);

        // Set Maud
        ScalerSetByte(PBC_20_AUD_TS_MAUD_H, 0x00);
        ScalerSetByte(PBC_21_AUD_TS_MAUD_M, 0x00);
        ScalerSetByte(PBC_22_AUD_TS_MAUD_L, 0x00);

        // Sed Naud
        ScalerSetByte(PBC_23_AUD_TS_NAUD_H, 0x00);
        ScalerSetByte(PBC_24_AUD_TS_NAUD_M, 0x00);
        ScalerSetByte(PBC_25_AUD_TS_NAUD_L, 0x00);

        // Clear Header for Audio Timestamp
        ScalerDpMacTxSdpClearHeaderByte_8b10b(_SEC_PACKET_TYPE_AUDIO_TIMESTAMP);
    }
}

//--------------------------------------------------
// Description  : Enable or Disable Audio Stream of DP TX SDP
// Input Value  : _ENABLE or _DISABLE
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioStreamProc(bit bEnable)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxSdpAudioStreamProc_128b132b(bEnable);
    }
    else
#endif
    {
        ScalerDpMacTxSdpAudioStreamProc_8b10b(bEnable);
    }
}

//--------------------------------------------------
// Description  : Enable or Disable Audio Stream of DP TX SDP
// Input Value  : _ENABLE or _DISABLE
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioStreamProc_8b10b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set Header for Audio Stream
        ScalerDpMacTxSdpSetHeaderByte(_SEC_PACKET_TYPE_AUDIO_STREAM, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);

        // Enable Audio Stream
        ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~_BIT0, _BIT0);
    }
    else
    {
        // Disable Audio Stream
        ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~_BIT0, 0x00);

        // Clear Header for Audio Stream
        ScalerDpMacTxSdpClearHeaderByte_8b10b(_SEC_PACKET_TYPE_AUDIO_STREAM);
    }
}

//--------------------------------------------------
// Description  : Enable Audio Decode
// Input Value  : ucDpTxStreamSource
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioDecodeEnable(BYTE ucDpTxStreamSource)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxSdpAudioDecodeEnable_128b132b(ucDpTxStreamSource);
    }
    else
#endif
    {
        ScalerDpMacTxSdpAudioDecodeEnable_8b10b(ucDpTxStreamSource);
    }
}

//--------------------------------------------------
// Description  : Enable Audio Decode
// Input Value  : ucDpTxStreamSource
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioDecodeEnable_8b10b(BYTE ucDpTxStreamSource)
{
    if((ucDpTxStreamSource == _DP_TX_SOURCE_MST2SST) && (GET_DP_MAC_TX_INPUT_CHANNEL_CODING() == _CODING_TYPE_8B10B))
    {
        // Enable Audio Decode for MST2SST
        SET_DP_TX_SDP_DECODE_TYPE(_DP_TX_SDP_DECODE_AUDIO);
    }
    else
    {
#if ((_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON) && (_DSC_DECODER_SUPPORT == _ON))
        if ((GET_DP_TX_DOWNSTREAM_DSC_SUPPORT() == _ENABLE) && (GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH() == _ENABLE))
        {
            // Enable Audio Decode for MST2SST
            SET_DP_TX_SDP_DECODE_TYPE(_DP_TX_SDP_DECODE_AUDIO);
        }
        else
#endif
        {
            // Enable I2S Decode for Clone
            ScalerSetBit(PBC_99_DUMMY_99, ~(_BIT6 | _BIT5 | _BIT2), _BIT2);
        }
    }
}

//--------------------------------------------------
// Description  : Disable Audio Decode
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioDecodeDisable(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxSdpAudioDecodeDisable_128b132b();
    }
    else
#endif
    {
        ScalerDpMacTxSdpAudioDecodeDisable_8b10b();
    }
}

//--------------------------------------------------
// Description  : Disable Audio Decode
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioDecodeDisable_8b10b(void)
{
    // Disable Audio Decode for MST2SST
    CLR_DP_TX_SDP_DECODE_TYPE(_DP_TX_SDP_DECODE_AUDIO);

    // Disable I2S Decode for Clone
    ScalerSetBit(PBC_99_DUMMY_99, ~(_BIT6 | _BIT5 | _BIT2), 0x00);

    // Disable I2S Data(SD), Channel Status Count for Clone
    ScalerSetBit(PBC_8F_DPTX_I2S_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : DP Tx Audio Mute Flag Setting
// Input Value  : _ENABLE or _DISABLE
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacTxSetAudioMuteFlag(bit bEnable)
{
#if (_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if (GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxSetAudioMuteFlag_128b132b(bEnable);
    }
    else
#endif
    {
        ScalerDpMacTxSetAudioMuteFlag_8b10b(bEnable);
    }
}

//--------------------------------------------------
// Description  : DP Tx Audio Mute Flag Setting
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetAudioMuteFlag_8b10b(bit bEnable)
{
    // Audio Mute Flag and No Video Flag Write Protect
    if (bEnable == _ENABLE)
    {
        ScalerSetBit(PBB_C7_VBID, ~_BIT2, _BIT2);
        ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, PBB_C7_VBID, _BIT2, _TRUE);
    }
    else
    {
        ScalerSetBit(PBB_C7_VBID, ~_BIT2, 0x00);
        ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, PBB_C7_VBID, _BIT2, _FALSE);
    }
}

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))
//--------------------------------------------------
// Description  : Handle Tx in Sleep Audio Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSleepAudioControl(void)
{
    if(GET_DP_TX_AUDIO_STAND_ALONE_CHANGE_EVENT() == _ON)
    {
        if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE)
        {
            if(GET_DP_TX_AUDIO_STAND_ALONE() == _ON)
            {
                if(GET_DP_TX_AUDIO_READY_TO_PLAY() == _FALSE)
                {
                    // Disable Audio
                    ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_OFF);

                    // Set Standalong Audio
                    ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_PRESET);
                }
            }
            else
            {
                if(GET_DP_TX_AUDIO_READY_TO_PLAY() == _TRUE)
                {
                    // Disable Audio
                    ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_OFF);
                }
            }
        }

        CLR_DP_TX_AUDIO_STAND_ALONE_CHANGE_EVENT();
    }
}

//--------------------------------------------------
// Description  : DP Tx Sleep Audio Support Setting
// Input Value  : _AUDIO_STAND_ALONE_TRUE / _AUDIO_STAND_ALONE_FALSE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetSleepAudioState(EnumAudioStandAloneStatus enumAudioStandAloneStatus)
{
    if(enumAudioStandAloneStatus == _AUDIO_STAND_ALONE_TRUE)
    {
        if(GET_DP_TX_AUDIO_STAND_ALONE() == _FALSE)
        {
            SET_DP_TX_AUDIO_STAND_ALONE();
            SET_DP_TX_AUDIO_STAND_ALONE_CHANGE_EVENT();
        }
    }
    else
    {
        if(GET_DP_TX_AUDIO_STAND_ALONE() == _TRUE)
        {
            CLR_DP_TX_AUDIO_STAND_ALONE();
            SET_DP_TX_AUDIO_STAND_ALONE_CHANGE_EVENT();
        }
    }
}
#endif // End of #if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Set Audio Channel Count
// Input Value  :
// Output Value : Changed => _TRUE or No Changed => _FALSE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioFormatSetting_128b132b(void)
{
    BYTE ucPacketPerSample = 0;
    WORD usMaxAudioPacket = 0;
    WORD usBe2Be = 0;
    WORD usSdpPacket = 0;
    WORD usMaxPacket = 0;

    // Set TX Audio Channel Count
    SET_DP_TX_AUDIO_CHANNEL_COUNT(ScalerAudioGetRxChannelCount(_AUDIO_DPTX_OUT));

    // Set TX Audio Coding Type
    SET_DP_TX_AUDIO_CODING_TYPE(ScalerAudioGetRxCodingType(_AUDIO_DPTX_OUT));

    // Set Audio Channel Status and Channel Number
    ScalerDpMacTxSdpAudioChannelStatusSetting_128b132b();

    // Check Audio Channel Count
    if(GET_DP_TX_AUDIO_CHANNEL_COUNT() > _AUDIO_CHANNEL_COUNT_2)
    {
        // Set 8 Channel Layout and Water Level of Audio SFIFO For Capturing Audio Sample
        ScalerSetBit(P2C_18_AUD_FUNCTION_CTRL1, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT3));

        // Set I2S Received Mode As 8 Channel Mode
        ScalerSetBit(P2C_48_AUD_FUNCTION_CTRL3, ~_BIT3, _BIT3);

        // Set I2S Data(SD) For 8 Channel and Enable HW Mode for Transmitting Preamble / Channel Status / Parity bit
        ScalerSetBit(P2C_8F_DPTX_I2S_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

        // Set Preamble Insert Method: All Channel
        ScalerSetBit(P2C_8F_DPTX_I2S_CTRL, ~_BIT3, _BIT3);

        // Set Audio Packet Per Sample
        ucPacketPerSample = 40;
    }
    else
    {
        // Set 2 Channel Layout and Water Level of Audio SFIFO For Capturing Audio Sample
        ScalerSetBit(P2C_18_AUD_FUNCTION_CTRL1, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

        // Set I2S Received Mode As 2 Channel Mode
        ScalerSetBit(P2C_48_AUD_FUNCTION_CTRL3, ~_BIT3, 0x00);

        // Set I2S Data(SD) For 2 Channel and Enable HW Mode for Transmitting Preamble / Channel Status / Parity bit
        ScalerSetBit(P2C_8F_DPTX_I2S_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

        // Set Preamble Insert Method: 2-Channel
        ScalerSetBit(P2C_8F_DPTX_I2S_CTRL, ~_BIT3, 0x00);

        // Set Audio Packet Per Sample
        ucPacketPerSample = 20;
    }

    // sec_end_cnt = max_audio_packet (lane_num, max_long_packet_cnt) + safe_margin
    // max_audio_packet = SS&SE + HEADER&ECC BYTES / lane_num + [(max_long_packet_cnt+1) * (minimum packet payload + 4)] / lane_num.
    usMaxAudioPacket = 2 + ((8 + ucPacketPerSample) / GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM());

    // SDP_packet = SS&SE + HEADER&ECC BYTES / lane_num + (DATA_BYTES + DATA_P_BYTES) / lane_num.
    usSdpPacket = 2 + ((8 + 32 + 8) / GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM());

    // MaxPacket = max(MaxAudioPacket, SdpPacket)
    usMaxPacket = MAXOF(usMaxAudioPacket, usSdpPacket);

    // Get BE2BE Period with Htotal
    usBe2Be = (DWORD)g_stDpMacTxInputTimingInfo.usHTotal * 10 * _DP_TX_LINK_CLK_MHZ_128B132B / GET_DP_TX_INPUT_PIXEL_CLK();

    // Get 70% of blanking period
    usBe2Be = (DWORD)(usBe2Be - GET_DP_TX_HORIZONTAL_DE_PERIOD()) * 7 / 10;

    // if BS2BE > max(MaxAudioPacket,SdpPacket), Sec_end_count = BS2BE - max(MaxAudioPacket,SdpPacket)
    // else Sec_end_count = 0;

    if(usBe2Be > usMaxPacket)
    {
        // Set Seccondary End Count
        ScalerSetByte(P2B_CE_ARBITER_SEC_END_CNT_HB, HIBYTE(usBe2Be - usMaxPacket));
        ScalerSetByte(P2B_CF_ARBITER_SEC_END_CNT_LB, LOBYTE(usBe2Be - usMaxPacket));
    }
    else
    {
        // Set Seccondary End Count
        ScalerSetByte(P2B_CE_ARBITER_SEC_END_CNT_HB, 0x00);
        ScalerSetByte(P2B_CF_ARBITER_SEC_END_CNT_LB, 0x00);
    }

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))
    if(GET_DP_TX_AUDIO_STAND_ALONE() == _ON)
    {
        BYTE ucSecIdleEndCount = 0x00;

        // Calculate End Count in Ilde Pattern Mode
        ucSecIdleEndCount = 2 + (48 / GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM());

        // Add 50% Margin
        ucSecIdleEndCount = (ucSecIdleEndCount * 3) / 2;

        // Set Seccondary End Count
        ScalerSetByte(P2B_F8_ARBITER_SEC_IDLE_END_CNT, ucSecIdleEndCount);
    }
#endif

    // Set SEC END CNT Double Buffer
    SET_DP_TX_SEC_END_CNT_DB_128B132B();
}

//--------------------------------------------------
// Description  : Dp TX Set Audio Channel Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpAudioChannelStatusSetting_128b132b(void)
{
    StructAudioChannelInfo stDpMacTxAudioStatus = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    stDpMacTxAudioStatus = ScalerAudioGetRxChannelStatus(_AUDIO_DPTX_OUT);

    // Set Audio Channel Info
    ScalerSetByte(P2C_85_CH_STATUS_0, stDpMacTxAudioStatus.ucChannelStaus0);
    ScalerSetByte(P2C_86_CH_STATUS_1, stDpMacTxAudioStatus.ucChannelStaus1);
    ScalerSetByte(P2C_87_CH_STATUS_2, stDpMacTxAudioStatus.ucChannelStaus2);
    ScalerSetByte(P2C_88_CH_STATUS_3, stDpMacTxAudioStatus.ucChannelStaus3);
    ScalerSetByte(P2C_89_CH_STATUS_4, stDpMacTxAudioStatus.ucChannelStaus4);

    ScalerSetByte(P2C_7C_CH_STATUS_CH12, stDpMacTxAudioStatus.ucChannelNumber12);
    ScalerSetByte(P2C_7D_CH_STATUS_CH34, stDpMacTxAudioStatus.ucChannelNumber34);
    ScalerSetByte(P2C_7E_CH_STATUS_CH56, stDpMacTxAudioStatus.ucChannelNumber56);
    ScalerSetByte(P2C_7F_CH_STATUS_CH78, stDpMacTxAudioStatus.ucChannelNumber78);
}

//--------------------------------------------------
// Description  : DP Tx Get Audio Format Change
// Input Value  : None
// Output Value : Changed => _TRUE or No Changed => _FALSE
//--------------------------------------------------
bit ScalerDpMacTxSdpAudioGetFormatChange_128b132b(void)
{
    BYTE ucSamplingFrequency = 0;
    EnumAudioChannelCount enumChannelCount = 0;
    BYTE ucCodingType = 0;
    bit bIsChanged = _FALSE;

    // Get The Latest Input Audio Channel Count
    enumChannelCount = ScalerAudioGetRxChannelCount(_AUDIO_DPTX_OUT);

    // Get The Latest Input Audio Coding Type
    ucCodingType = ScalerAudioGetRxCodingType(_AUDIO_DPTX_OUT);

    // Get Audio Sampling Frequency
    ucSamplingFrequency = ScalerDpMacTxSdpAudioGetSamplingFreqRange();

    // Check If Sampling Frequency is Changed
    if(ucSamplingFrequency != GET_DP_TX_AUDIO_SAMPLING_FREQUENCY())
    {
        DebugMessageAudio("[DPTX] 2.0 Audio Changed FS", ucSamplingFrequency);

        bIsChanged = _TRUE;

        SET_DP_TX_AUDIO_SAMPLING_FREQUENCY(ucSamplingFrequency);
    }

    // Check If Channel Count is Changed
    if(enumChannelCount != GET_DP_TX_AUDIO_CHANNEL_COUNT())
    {
        DebugMessageAudio("[DPTX] 2.0 Audio Changed CC", enumChannelCount);

        bIsChanged = _TRUE;
    }

    // Check If Coding Type is Changed
    if(ucCodingType != GET_DP_TX_AUDIO_CODING_TYPE())
    {
        DebugMessageAudio("[DPTX] 2.0 Audio Changed CT", ucCodingType);

        bIsChanged = _TRUE;
    }

    return bIsChanged;
}

//--------------------------------------------------
// Description  : DP Tx Get Audio Sampling Frequency Range
// Input Value  :
// Output Value : Audio Frequency Range
//--------------------------------------------------
BYTE ScalerDpMacTxSdpAudioGetSamplingFreqRange_128b132b(void)
{
    BYTE ucSampleFreqRange = (ScalerGetBit(P2C_4F_SEC_AUD_SAMPLE_CNT_HB, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

    WORD usAudioPacket = (WORD)((ScalerGetBit(P2C_4F_SEC_AUD_SAMPLE_CNT_HB, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | ScalerGetByte(P2C_50_SEC_AUD_SAMPLE_CNT_LB));

    usAudioPacket = usAudioPacket;

    return ucSampleFreqRange;
}

//--------------------------------------------------
// Description  : Set DP TX Audio Play for DP MST2SST
// Input Value  : EnumDPTxAudioPlayState
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpAudioPlayProc_128b132b(EnumDPTxAudioPlayState enumPlayState)
{
    switch(enumPlayState)
    {
        case _DP_TX_AUDIO_OFF:

            DebugMessageAudio("[DPTX] 2.0 Audio Play Off", enumPlayState);

            // Enable VBID[4] Audio Mute Flag
            ScalerDpMacTxSetAudioMuteFlag(_ENABLE);

            // Disable Audio Timestamp
            ScalerDpMacTxSdpAudioTimestampProc(_DISABLE);

            // Disable TX Audio Frequency Detection
            ScalerSetBit(P2C_4C_SEC_AUD_FREQDET_CTRL, ~(_BIT7 | _BIT3 | _BIT1), 0x00);

            // Disable All Audio Stream Decode
            ScalerDpMacTxSdpAudioDecodeDisable();

            // Disable Audio Stream
            ScalerDpMacTxSdpAudioStreamProc(_DISABLE);

            // Clear Audio Related Falg
            CLR_DP_TX_AUDIO_READY_TO_PLAY();
            CLR_DP_TX_AUDIO_SAMPLING_FREQUENCY();
            CLR_DP_TX_AUDIO_CHANNEL_COUNT();
            CLR_DP_TX_AUDIO_CODING_TYPE();

            break;

        case _DP_TX_AUDIO_PRESET:

            DebugMessageAudio("[DPTX] 2.0 Audio Play Preset", enumPlayState);

            // Set Keepout Regien of MSA as 0
            ScalerSetBit(P2B_CB_AUTO_HDEALY0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

            // Set Keepout Regien of Audio as 5
            ScalerSetBit(P2B_CB_AUTO_HDEALY0, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P2B_CC_AUTO_HDEALY1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

            // Set Keepout Regien of Other Sec Data as 15
            ScalerSetBit(P2B_CC_AUTO_HDEALY1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P2B_CD_LFIFO_WL_SET, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Set Audio Channel Count, Coding Type and End Count of SDP
            ScalerDpMacTxSdpAudioFormatSetting();

            // Enable Audio Stream
            ScalerDpMacTxSdpAudioStreamProc(_ENABLE);

            // Enable Audio Stream Decode
            ScalerDpMacTxSdpAudioDecodeEnable(GET_DP_TX_STREAM_SOURCE());

            // Enable TX Audio Frequency Detection
            ScalerSetBit(P2C_4C_SEC_AUD_FREQDET_CTRL, ~(_BIT7 | _BIT3 | _BIT1), _BIT7);

            SET_DP_TX_AUDIO_READY_TO_PLAY();
            CLR_DP_TX_AUDIO_SAMPLING_FREQUENCY();

            break;

        case _DP_TX_AUDIO_FORMAT_CHANGE:

            DebugMessageAudio("[DPTX] 2.0 Audio Play Change", enumPlayState);

            // Enable VBID[4] Audio Mute Flag
            ScalerDpMacTxSetAudioMuteFlag(_ENABLE);

            // Disable Audio Timestamp
            ScalerDpMacTxSdpAudioTimestampProc(_DISABLE);

            // Disable All Audio Stream Decode
            ScalerDpMacTxSdpAudioDecodeDisable();

            // Disable Audio Stream
            ScalerDpMacTxSdpAudioStreamProc(_DISABLE);

            // Set Audio Channel Count, Coding Type and End Count of SDP
            ScalerDpMacTxSdpAudioFormatSetting();

            // Enable Audio Stream
            ScalerDpMacTxSdpAudioStreamProc(_ENABLE);

            // Enable Audio Stream Decode
            ScalerDpMacTxSdpAudioDecodeEnable(GET_DP_TX_STREAM_SOURCE());

            break;

        case _DP_TX_AUDIO_ON:

            DebugMessageAudio("[DPTX] 2.0 Audio Play On", enumPlayState);

            // Enable Audio Timestamp
            ScalerDpMacTxSdpAudioTimestampProc(_ENABLE);

            // Disable VBID[4] Audio Mute Flag
            ScalerDpMacTxSetAudioMuteFlag(_DISABLE);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Enable or Disable Audio Timestamp of DP TX SDP
// Input Value  : _ENABLE or _DISABLE
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioTimestampProc_128b132b(bit bEnable)
{
    DWORD ulAfreq = 0;

    if(bEnable == _ENABLE)
    {
        // Get Real Audio Frequency in Hz
        ulAfreq = (DWORD)(100 * ScalerDpMacTxSdpAudioGetSamplingFreqPacket(GET_DP_TX_AUDIO_SAMPLING_FREQUENCY()));

        // Set Afreq = 512 * Fs
        ScalerSetByte(P2C_20_AUD_FREQ_0, 0x00);
        ScalerSetByte(P2C_21_AUD_FREQ_1, 0x00);
        ScalerSetByte(P2C_22_AUD_FREQ_2, (BYTE)(ulAfreq >> 15));
        ScalerSetByte(P2C_23_AUD_FREQ_3, (BYTE)(ulAfreq >> 7));
        ScalerSetByte(P2C_24_AUD_FREQ_4, (BYTE)(ulAfreq << 1));
        ScalerSetByte(P2C_25_AUD_FREQ_5, 0x00);

        // Set Header for Audio Timestamp
        ScalerDpMacTxSdpSetHeaderByte(_SEC_PACKET_TYPE_AUDIO_TIMESTAMP, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);

        // Enable Audio Timestamp
        ScalerSetBit(P2C_00_SEC_FUNCTION_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Disable Audio Timestamp
        ScalerSetBit(P2C_00_SEC_FUNCTION_CTRL, ~_BIT1, 0x00);

        // Set Afreq
        ScalerSetByte(P2C_20_AUD_FREQ_0, 0x00);
        ScalerSetByte(P2C_21_AUD_FREQ_1, 0x00);
        ScalerSetByte(P2C_22_AUD_FREQ_2, 0x00);
        ScalerSetByte(P2C_23_AUD_FREQ_3, 0x00);
        ScalerSetByte(P2C_24_AUD_FREQ_4, 0x00);
        ScalerSetByte(P2C_25_AUD_FREQ_5, 0x00);

        // Clear Header for Audio Timestamp
        ScalerDpMacTxSdpClearHeaderByte_128b132b(_SEC_PACKET_TYPE_AUDIO_TIMESTAMP);
    }
}

//--------------------------------------------------
// Description  : Enable or Disable Audio Stream of DP TX SDP
// Input Value  : _ENABLE or _DISABLE
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioStreamProc_128b132b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set Header for Audio Stream
        ScalerDpMacTxSdpSetHeaderByte(_SEC_PACKET_TYPE_AUDIO_STREAM, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);

        // Enable Audio Stream
        ScalerSetBit(P2C_00_SEC_FUNCTION_CTRL, ~_BIT0, _BIT0);
    }
    else
    {
        // Disable Audio Stream
        ScalerSetBit(P2C_00_SEC_FUNCTION_CTRL, ~_BIT0, 0x00);

        // Clear Header for Audio Stream
        ScalerDpMacTxSdpClearHeaderByte_128b132b(_SEC_PACKET_TYPE_AUDIO_STREAM);
    }
}

//--------------------------------------------------
// Description  : Enable Audio Decode
// Input Value  : ucDpTxStreamSource
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioDecodeEnable_128b132b(BYTE ucDpTxStreamSource)
{
    ucDpTxStreamSource = ucDpTxStreamSource;

    // Enable I2S Decode for MST2SST/Clone
    ScalerSetBit(P2C_99_DUMMY_99, ~(_BIT5 | _BIT2), _BIT2);
}

//--------------------------------------------------
// Description  : Disable Audio Decode
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacTxSdpAudioDecodeDisable_128b132b(void)
{
    // Disable I2S Decode for Clone
    ScalerSetBit(P2C_99_DUMMY_99, ~(_BIT5 | _BIT2), 0x00);

    // Disable I2S Data(SD), Channel Status Count for Clone
    ScalerSetBit(P2C_8F_DPTX_I2S_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : DP20 Tx Audio Mute Flag Setting
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetAudioMuteFlag_128b132b(bit bEnable)
{
    // Audio Mute Flag and No Video Flag Write Protect
    if (bEnable == _ENABLE)
    {
        ScalerSetBit(P2B_C1_VBID, ~_BIT2, _BIT2);
        ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, P2B_C1_VBID, _BIT2, _TRUE);
    }
    else
    {
        ScalerSetBit(P2B_C1_VBID, ~_BIT2, 0x00);
        ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, P2B_C1_VBID, _BIT2, _FALSE);
    }
}
#endif // End of #if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

//--------------------------------------------------
// Description  : DP++ Downstream Sink Type Detect
// Input Value  : EnumOutputPort --> _P0_OUTPUT_PORT / _P1_OUTPUT_PORT / _P2_OUTPUT_PORT / _P3_OUTPUT_PORT
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxCableDetect(void)
{
    return (ScalerGetBit(PBB_70_HPD_CTRL, _BIT2) >> 2);
}

//--------------------------------------------------
// Description  : DPTX ReAuth Check Process
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxReAuthCheck(EnumPortType enumPortType)
{
    bit bReAuthCheck = _FALSE;

    if((enumPortType == _PORT_DP) && (ScalerSyncDpHdcpGetUpstreamEncryptStatus() == _TRUE))
    {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
        if((GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_HDCP2_TX_VERSION_SUPPORTED() == _TRUE))
        {
            if((ScalerSyncDpHdcp2GetAuthState() == _DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE) &&
               (GET_DP_HDCP2_TX_AUTH_STATE() == _HDCP_2_2_TX_STATE_IDLE))
            {
                DebugMessageHDCP2("Dp TX Clone: HDCP2 Reauthen", 0);

                SET_DP_HDCP2_TX_DOWNSTREAM_EVENT(_DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_REAUTH);

                bReAuthCheck = _TRUE;
            }
        }
#endif
        if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
        {
            if((ScalerSyncDpHdcpGetAuthState() == _DP_RX_HDCP_STATE_AUTH_DONE) &&
               (GET_DP_TX_HDCP_AUTH_STATE() == _DP_TX_HDCP_STATE_IDLE))
            {
                DebugMessageHDCP2("Dp TX Clone: HDCP Reauthen", 0);

                SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH);

                bReAuthCheck = _TRUE;
            }
        }
    }

    return bReAuthCheck;
}

//--------------------------------------------------
// Description  : DPTX Bypass 420 Check
// Input Value  : enumInputPort
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxBypass420Check(EnumInputPort enumInputPort)
{
    // It should disable singal output when clone source color space is Ycbcr 420 but dp tx can't support Ycbcr 420 case
    if((GET_COLOR_SPACE(enumInputPort) == _COLOR_SPACE_YCBCR420) && (GET_DP_MAC_TX_DOWNSTREAM_420_SUPPORT() == _FALSE))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DPTX Bypass 420 Setting
// Input Value  : enumPortType
// Output Value : _NONE
//--------------------------------------------------
void ScalerDpMacTxBypass420Setting(EnumPortType enumPortType)
{
    if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        if((enumPortType == _PORT_HDMI20) || (enumPortType == _PORT_HDMI))
        {
            SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_EXT);
        }
    }
}

#if(_DP_TX_CONFIG_BY_USER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Tx Link Config by User
// Input Value  : enumDpTxConfig
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxLinkConfigAdjust(EnumDpMacTxConfig enumDpMacTxConfig)
{
    switch(enumDpMacTxConfig)
    {
        case _DP_TX_V11_1LANE_RBR:

            SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_1);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_ONE_LANE);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_RBR);

            break;

        case _DP_TX_V11_2LANE_RBR:

            SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_1);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_TWO_LANE);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_RBR);

            break;

        case _DP_TX_V11_4LANE_RBR:

            SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_1);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_FOUR_LANE);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_RBR);

            break;

        case _DP_TX_V11_1LANE_HBR:

            SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_1);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_ONE_LANE);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR);

            break;

        case _DP_TX_V11_2LANE_HBR:

            SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_1);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_TWO_LANE);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR);

            break;

        case _DP_TX_V11_4LANE_HBR:

            SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_1);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_FOUR_LANE);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR);

            break;

        case _DP_TX_V12_1LANE_HBR2:

            SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_2);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_ONE_LANE);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR2);

            break;

        case _DP_TX_V12_2LANE_HBR2:

            SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_2);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_TWO_LANE);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR2);

            break;

        case _DP_TX_V12_4LANE_HBR2:

            SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_2);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_FOUR_LANE);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR2);

            break;

        case _DP_TX_V14_1LANE_HBR3:

            SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_4);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_ONE_LANE);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR3);

            break;

        case _DP_TX_V14_2LANE_HBR3:

            SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_4);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_TWO_LANE);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR3);

            break;

        case _DP_TX_V14_4LANE_HBR3:

            SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_4);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_FOUR_LANE);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR3);

            break;

        case _DP_TX_CONFIG_NONE:
        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get Dp Tx Edid Bandwith
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD ScalerDpMacTxGetDownStreamEdidBw(void)
{
    return GET_DP_MAC_TX_EDID_BW();
}

//--------------------------------------------------
// Description  : Downsteram Edid Bw Settinf
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDownStreamEdidBwSetting(void)
{
    BYTE pucPixClkArray[2] = {0, 0};
    BYTE ucEdidOffset = 0x36;

#if(_DFP_SINK_EDID_CHANGE_CHECK_METHOD == _EDID_SHA_CODE)
    SET_DP_MAC_TX_EDID_BW(0);

    if(ScalerDpAuxTxI2CoverWrite(0x50, 1, &ucEdidOffset, 1) == _FALSE)
    {
        return;
    }

    if(ScalerDpAuxTxI2CoverRead(0x50, 2, pucPixClkArray, 0) == _FALSE)
    {
        return;
    }

    // Unit: 0.01M
    SET_DP_MAC_TX_EDID_BW((((WORD)pucPixClkArray[1] << 8) | pucPixClkArray[0]));
#else
    pucPixClkArray[0] = g_pucDpMacTxPreviousDfpDeviceEdidBackup[ucEdidOffset];
    pucPixClkArray[1] = g_pucDpMacTxPreviousDfpDeviceEdidBackup[ucEdidOffset + 1];

    // Unit: 0.01M
    SET_DP_MAC_TX_EDID_BW((((WORD)pucPixClkArray[1] << 8) | pucPixClkArray[0]));
#endif

    DebugMessageMst("Dp Mac Tx Port Downstream Edid Native Bw = ", GET_DP_MAC_TX_EDID_BW());
}

#if((_DP_MST_SUPPORT == _ON) || (_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Tx Sync Payload ID Table for DP
// Input Value  : Virtual ID and PBN
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacTxSyncPayloadIDTable(BYTE ucPayloadID, WORD usPBN)
{
    BYTE ucTxTargeTimeSlotLength = 0;
    BYTE ucTxTargetStartPosition = 0;

    if((ucPayloadID != 0) &&
       (GET_DP_MAC_TX_DAISY_STREAM_NOT_EXIST(ucPayloadID) == _TRUE) &&
       (GET_DP_MAC_TX_DAISY_NO_EMPTY_STREAM() == _TRUE))
    {
        DebugMessageMst("ucTxCurrentSTX Error", 0);
        // Failed to allocate VC, no empty stream to allocate a new stream
        return _FALSE;
    }

    if((GET_DP_MAC_TX_DAISY_STREAM_NOT_EXIST(ucPayloadID) == _TRUE) &&
       (usPBN == 0))
    {
        DebugMessageMst("TX SyncPayload: ID doesn't exist and PBN = 0", 0);
        // No more modifications needed
        return _FALSE;
    }

    // Calulate Timeslot need according to PBN
    if(usPBN == 0)
    {
        ucTxTargeTimeSlotLength = 0;
    }
    else
    {
        ucTxTargeTimeSlotLength = ScalerDpMacTxCalTimeslotNeed(usPBN);
    }

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        if(ucTxTargeTimeSlotLength > 64)
        {
            DebugMessageMst("Tx Sync Payload 128B132B > 64 timeslot", 0);
            return _FALSE;
        }
    }
    else
#endif
    {
        if(ucTxTargeTimeSlotLength > 63)
        {
            DebugMessageMst("Tx Sync Payload 8B10B > 63 timeslot", 0);
            return _FALSE;
        }
    }

    // Clear Daisy All stream
    if(ucPayloadID == 0)
    {
        ScalerDpMacTxDaisyClearPayloadIDProc();
    }
    // Modify Daisy Stream
    else if(ScalerDpMacTxCheckIDExisted(ucPayloadID) == _TRUE)
    {
        ucTxTargetStartPosition = ScalerDpMacTxDaisyModifyPayloadIDProc(ucPayloadID, ucTxTargeTimeSlotLength);
    }
    // Add New Daisy Stream
    else
    {
        ucTxTargetStartPosition = ScalerDpMacTxDaisyAddNewPayloadIDProc(ucPayloadID, ucTxTargeTimeSlotLength);
    }

    if(ucTxTargetStartPosition > 63)
    {
        return _FALSE;
    }

    if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
    {
        if((ucTxTargetStartPosition + ucTxTargeTimeSlotLength - 1) > 63)
        {
            ucTxTargeTimeSlotLength = 63 - ucTxTargetStartPosition + 1;
        }

        // Use 0x1C0~0x1C2 to Sync Table and Issuing ACT => Include Retry Once
        if((ScalerDpMacTxSyncDownStreamTableSetting(ucPayloadID, ucTxTargetStartPosition, ucTxTargeTimeSlotLength) == _TRUE) ||
           (ScalerDpMacTxSyncDownStreamTableSetting(ucPayloadID, ucTxTargetStartPosition, ucTxTargeTimeSlotLength) == _TRUE))
        {
            return _TRUE;
        }
        else
        {
            // Failed to allocate VC
            return _FALSE;
        }
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Mst TX daisy Clear Payload ID process
// Input Value  : Stream Number
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDaisyClearPayloadIDProc(void)
{
    ScalerDpMacTxResetDaisyStreamPositionReg();

#if((_DP_MST_SUPPORT == _ON) && (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
    ScalerDpMstTxReset128b132bTo8b10bMsaConvert();
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    // For Tx 128b132b SST Clone case, Set Source Mux here
    if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
    {
        if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
        {
            ScalerDpMacTxSetDaisySourceMuxBackup(_DP_ST_SOURCE1, _DP_ST_NONE);
        }
    }
#endif

    ScalerDpMacTxResetStreamToIdMapping();
}

//--------------------------------------------------
// Description  : Mst TX daisy Modify Payload ID process
// Input Value  : Stream Number
// Output Value : TargetStartPosition
//--------------------------------------------------
BYTE ScalerDpMacTxDaisyModifyPayloadIDProc(BYTE ucPayloadID, BYTE ucTxTargeTimeSlotLength)
{
    BYTE ucTxTargetStartPosition = 0;
    BYTE ucTxTargetEndPosition = 0;
    SBYTE chTxTimeSlotOffset = 0;
    BYTE ucIndex = 0;
    EnumDpStreamNum enumTxCurrentSTX = ScalerDpMacTxSearchMatchStream(ucPayloadID);

    // Modify Payload Load ID if Current Timeslot is assigned
    if(GET_DP_MAC_TX_DAISY_ST_STATUS_REG(enumTxCurrentSTX) == _ENABLE)
    {
        // Record Current Stream's Start End position
        ucTxTargetStartPosition = GET_DP_MAC_TX_DAISY_ST_START_POSITION_REG(enumTxCurrentSTX);
        ucTxTargetEndPosition = GET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(enumTxCurrentSTX);

        // Calculate TimeSlot offset: target length - current length
        chTxTimeSlotOffset = (SBYTE)ucTxTargeTimeSlotLength - (SBYTE)(GET_DP_MAC_TX_DAISY_ST_TIMESLOT_LENGTH(enumTxCurrentSTX));

        // Increasing or Decreasing Timeslots
        if(ucTxTargeTimeSlotLength != 0)
        {
            // Modify Timeslot End Position
            SET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(enumTxCurrentSTX, (ucTxTargetEndPosition + chTxTimeSlotOffset));
        }
        // Delete
        else
        {
            // Delete Allocate Timeslot
            SET_DP_MAC_TX_DAISY_ST_STATUS_REG(enumTxCurrentSTX, _DISABLE);
            SET_DP_MAC_TX_DAISY_ST_START_POSITION_REG(enumTxCurrentSTX, 0x00);
            SET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(enumTxCurrentSTX, 0x00);

#if((_DP_MST_SUPPORT == _ON) && (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
            // Disable MSA convert
            ScalerDpMstTxSet128b132bTo8b10bMsaConvert(enumTxCurrentSTX, _DISABLE);
#endif

#if((_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON) && (_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON))
            // For Rx 128b132b, Tx 128b132b SST Clone case, Set Source Mux here
            if((ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT()) == _CODING_TYPE_128B132B) &&
               (ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B))
            {
                if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
                {
                    ScalerDpMacTxSetDaisySourceMuxBackup(_DP_ST_SOURCE1, _DP_ST_NONE);
                }
            }
#endif
            ScalerDpMacTxSetStreamToIdMapping(enumTxCurrentSTX, 0);
        }

        // Based On Offset to Modify Other Stream 's Start End position
        for(ucIndex = _DP_ST_1; ucIndex <= _DP_ST_6; ucIndex++)
        {
            // Other stream
            if(enumTxCurrentSTX != ucIndex)
            {
                // Only modify stream whose location is behind the current stream's original position
                if(GET_DP_MAC_TX_DAISY_ST_START_POSITION_REG(ucIndex) > ucTxTargetStartPosition)
                {
                    // Modify Start Position
                    SET_DP_MAC_TX_DAISY_ST_START_POSITION_REG(ucIndex, (GET_DP_MAC_TX_DAISY_ST_START_POSITION_REG(ucIndex) + chTxTimeSlotOffset));

                    // Modify End Position
                    SET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(ucIndex, (GET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(ucIndex) + chTxTimeSlotOffset));
                }
            }
        }
    }
    return ucTxTargetStartPosition;
}

//--------------------------------------------------
// Description  : Mst TX daisy Add new Payload ID process
// Input Value  : Stream Number
// Output Value : TargetStartPosition
//--------------------------------------------------
BYTE ScalerDpMacTxDaisyAddNewPayloadIDProc(BYTE ucPayloadID, BYTE ucTxTargeTimeSlotLength)
{
    BYTE ucTxTargetStartPosition = 0;
    BYTE ucIndex = 0;

    // Find Available StreamX whose ID is 0
    EnumDpStreamNum enumTxCurrentSTX = ScalerDpMacTxSearchMatchStream(0);

    if(enumTxCurrentSTX == _DP_ST_NONE)
    {
        return 0;
    }

    // Mapping Payload ID to ST to ID Table
    ScalerDpMacTxSetStreamToIdMapping(enumTxCurrentSTX, ucPayloadID);

#if((_DP_MST_SUPPORT == _ON) && (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
    // Only Do MSA convert when Rx=128b132b, Tx=8b10b
    if((ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT()) == _CODING_TYPE_128B132B) &&
       (GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_8B10B))
    {
        ScalerDpMstTxSet128b132bTo8b10bMsaConvert(enumTxCurrentSTX, _ENABLE);
    }
#endif

    // First Stream in Daisy
    if(ScalerDpMacTxCheckDaisyNoStream() == _TRUE)
    {
        ucTxTargetStartPosition = ScalerDpMacTxSetDaisyFirstStreamStart();
    }
    else
    {
        // Find TimeSlot Start Position = Current Max End Position + 1
        for(ucIndex = _DP_ST_1; ucIndex <= _DP_ST_6; ucIndex++)
        {
            if(enumTxCurrentSTX != ucIndex)
            {
                if(GET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(ucIndex) >= ucTxTargetStartPosition)
                {
                    ucTxTargetStartPosition = GET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(ucIndex) + 1;
                }
            }
        }
    }

    // Set Daisy Chain Start TimeSlot Position
    SET_DP_MAC_TX_DAISY_ST_START_POSITION_REG(enumTxCurrentSTX, ucTxTargetStartPosition);

    // Set Daisy Chain End TimeSlot Position
    if((ucTxTargetStartPosition + ucTxTargeTimeSlotLength - 1) > 63)
    {
        SET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(enumTxCurrentSTX, 63);
    }
    else
    {
        SET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(enumTxCurrentSTX, (ucTxTargetStartPosition + ucTxTargeTimeSlotLength - 1));
    }

    // Set Daisy Chain Enable
    SET_DP_MAC_TX_DAISY_ST_STATUS_REG(enumTxCurrentSTX, _ENABLE);

    return ucTxTargetStartPosition;
}

//--------------------------------------------------
// Description  : Tx Sync Downstream Table
// Input Value  : ucPayloadID, ucStartPosition, ucLength
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacTxSyncDownStreamTableSetting(BYTE ucPayloadID, BYTE ucStartPosition, BYTE ucLength)
{
    BYTE ucIndex1 = 0;
    BYTE ucIndex2 = 0;
    BYTE ucReadTemp = 0;
    BYTE pucWriteTemp[3] = {0};

    pucWriteTemp[0] = 0x01;

    // Clear Table Update and ACT Bit
    if(ScalerDpAuxTxNativeWrite(0x00, 0x02, 0xC0, 1, &pucWriteTemp[0]) == _FALSE)
    {
        return _FALSE;
    }

    // Update Payload ID Table
    pucWriteTemp[0] = ucPayloadID;
    pucWriteTemp[1] = ucStartPosition;
    pucWriteTemp[2] = ucLength;

    if(ScalerDpAuxTxNativeWrite(0x00, 0x01, 0xC0, 3, &pucWriteTemp[0]) == _FALSE)
    {
        return _FALSE;
    }

    for(ucIndex1 = 0; ucIndex1 < 20; ucIndex1++)
    {
        // Wait Rx Table Update
        ScalerTimerDelayXms(5);

        if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0xC0, 1, &ucReadTemp) == _TRUE)
        {
            if((ucReadTemp & _BIT0) == _BIT0)
            {
                if((ucPayloadID == 0x00) && (ucStartPosition == 0x00) && (ucLength == 0x3F))
                {
                    return _TRUE;
                }
                // Transmit ACT
                SET_DP_MAC_TX_REG_SEND_ACT_ENABLE();

                for(ucIndex2 = 0; ucIndex2 < 20; ucIndex2++)
                {
                    ScalerTimerDelayXms(2);

                    // Check ACT Transmitted
                    if(GET_DP_MAC_TX_REG_SEND_ACT_FLAG() == _TRUE)
                    {
                        if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0xC0, 1, &ucReadTemp) == _TRUE)
                        {
                            if((ucReadTemp & _BIT1) == 0x00)
                            {
                                // Retry Transmit ACT
                                SET_DP_MAC_TX_REG_SEND_ACT_ENABLE();
                            }
                            else
                            {
                                pucWriteTemp[0] = _BIT0;

                                // Clear Update Table and ACT Bit
                                ScalerDpAuxTxNativeWrite(0x00, 0x02, 0xC0, 1, &pucWriteTemp[0]);

                                return _TRUE;
                            }
                        }
                    }
                }

                break;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Calculate Timeslot needed according to PBN
// Input Value  : PBN
// Output Value : Timeslot
//--------------------------------------------------
BYTE ScalerDpMacTxCalTimeslotNeed(WORD usPBN)
{
    // Calculate Required Timeslots Number to According to PBN
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        BYTE ucSearchlow = 0;
        BYTE ucSearchhigh = 63;
        BYTE ucSearchmid = 0;

        // Binary Search in UHBR PBN table
        while(ucSearchlow <= ucSearchhigh)
        {
            ucSearchmid = (ucSearchhigh + ucSearchlow) / 2;

            if(ScalerDpMacDphyRxGetPBN(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(), ucSearchmid) < usPBN)
            {
                ucSearchlow = ucSearchmid + 1;
            }
            else if(ScalerDpMacDphyRxGetPBN(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(), ucSearchmid) > usPBN)
            {
                ucSearchhigh = ucSearchmid - 1;
            }
            else
            {
                break;
            }
        }
        if(ScalerDpMacDphyRxGetPBN(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(), ucSearchmid) > usPBN)
        {
            return ucSearchmid;
        }
        else if(ScalerDpMacDphyRxGetPBN(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(), ucSearchmid) < usPBN)
        {
            return ucSearchmid + 1;
        }
        else
        {
            return ucSearchmid;
        }
    }
    else
#endif
    {
        return ((usPBN / GET_DP_MAC_DPHY_RX_PBN_PER_TIME_SLOT(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM())) +
                (((usPBN % GET_DP_MAC_DPHY_RX_PBN_PER_TIME_SLOT(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM())) > 0) ? 1 : 0));
    }
}

//--------------------------------------------------
// Description  : Set MST Tx stream to ID array
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetStreamToIdMapping(EnumDpStreamNum enumDpStreamNum, BYTE ucPayloadID)
{
    if(enumDpStreamNum >= (sizeof(g_pucDpMacTxStreamToIdMapping) / sizeof(g_pucDpMacTxStreamToIdMapping[0])))
    {
        return;
    }

    g_pucDpMacTxStreamToIdMapping[enumDpStreamNum] = ucPayloadID;
}

//--------------------------------------------------
// Description  : Reset MST Tx stream to ID array
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxResetStreamToIdMapping(void)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    // Reset Stream ID Mapping Table
    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        g_pucDpMacTxStreamToIdMapping[enumDpStreamNum] = 0;
    }
}

//--------------------------------------------------
// Description  : Set DP Mst Tx Stream Status Reg
// Input Value  : BYTE Stream x, bit status
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetDaisyStreamStatusReg(EnumDpStreamNum enumDpStreamNum, bit bEn)
{
    enumDpStreamNum = enumDpStreamNum;
    bEn = bEn;

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    BYTE ucEnable = (BYTE)bEn;

    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        switch(enumDpStreamNum)
        {
            case _DP_ST_1:

                ScalerSetBit(P2B_D3_SOURCE_CTRL_0, ~_BIT5, ucEnable << 5);
                break;

            case _DP_ST_2:

                ScalerSetBit(P2B_D3_SOURCE_CTRL_0, ~_BIT4, ucEnable << 4);
                break;

            case _DP_ST_3:

                ScalerSetBit(P2B_D3_SOURCE_CTRL_0, ~_BIT3, ucEnable << 3);
                break;

            case _DP_ST_4:

                ScalerSetBit(P2B_D3_SOURCE_CTRL_0, ~_BIT2, ucEnable << 2);
                break;

            case _DP_ST_5:

                ScalerSetBit(P2B_D3_SOURCE_CTRL_0, ~_BIT1, ucEnable << 1);
                break;

            case _DP_ST_6:

                ScalerSetBit(P2B_D3_SOURCE_CTRL_0, ~_BIT0, ucEnable << 0);
                break;

            default:
                break;
        }
    }
    else
#endif
    {
        // 8b10b Streamstatus
        // There are no registers to set stream status. Instead, streamposition indicates the stream status.
        // StreamPosition = 0 -> Disable
        // StreamPosition != 0 -> Enable
    }
}

//--------------------------------------------------
// Description  : Get DP Mst Tx Stream Status
// Input Value  : BYTE Stream x
// Output Value : bit Enable or Disable
//--------------------------------------------------
bit ScalerDpMacTxGetDaisyStreamStatusReg(EnumDpStreamNum enumDpStreamNum)
{
    if(enumDpStreamNum == _DP_ST_NONE)
    {
        return _DISABLE;
    }

    // 8b10b: start position = 0 -> disable, 128b132b: other bits control
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        switch(enumDpStreamNum)
        {
            case _DP_ST_1:

                return ScalerGetBit(P2B_D3_SOURCE_CTRL_0, _BIT5);

            case _DP_ST_2:

                return ScalerGetBit(P2B_D3_SOURCE_CTRL_0, _BIT4);

            case _DP_ST_3:

                return ScalerGetBit(P2B_D3_SOURCE_CTRL_0, _BIT3);

            case _DP_ST_4:

                return ScalerGetBit(P2B_D3_SOURCE_CTRL_0, _BIT2);

            case _DP_ST_5:

                return ScalerGetBit(P2B_D3_SOURCE_CTRL_0, _BIT1);

            case _DP_ST_6:

                return ScalerGetBit(P2B_D3_SOURCE_CTRL_0, _BIT0);

            default:

                return 0;
        }
    }
    else
#endif
    {
        return (GET_DP_MAC_TX_DAISY_ST_START_POSITION_REG(enumDpStreamNum) != 0 ? 1 : 0);
    }
}

//--------------------------------------------------
// Description  : Search ST1 ~ ST6 to Match Input Paramater
// Input Value  : Target ID
// Output Value : Match ST Number Index
//--------------------------------------------------
EnumDpStreamNum ScalerDpMacTxSearchMatchStream(BYTE ucTargetID)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        // Setting STx to ID Table
        if(g_pucDpMacTxStreamToIdMapping[enumDpStreamNum] == ucTargetID)
        {
            return enumDpStreamNum;
        }
    }
    return _DP_ST_NONE;
}

//--------------------------------------------------
// Description  : Check Add Payload ID Whether Existed Or Not
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacTxCheckIDExisted(BYTE ucPayloadID)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        // ID Exist in STx to ID Table
        if(ucPayloadID == g_pucDpMacTxStreamToIdMapping[enumDpStreamNum])
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DP Mst Daisy All Stream Status,
// Input Value  : None
// Output Value : bit _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxCheckDaisyNoStream(void)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_DAISY_START; enumDpStreamNum <= _DP_ST_DAISY_END; enumDpStreamNum++)
    {
        if(ScalerDpMacTxGetDaisyStreamStatusReg(enumDpStreamNum) == _ENABLE)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Tx Mst Daisy First Stream Position
// Input Value  : None
// Output Value : BYTE
//--------------------------------------------------
BYTE ScalerDpMacTxSetDaisyFirstStreamStart(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return 0;
    }
    else
#endif
    {
        return 1;
    }
}

//--------------------------------------------------
// Description  : Get DP Tx MST Daisy Stream Start Position Register Address
// Input Value  : EnumDpStreamSourceNum
// Output Value : Address
//--------------------------------------------------
WORD ScalerDpMacTxGetDaisyStreamStartPositionRegAddress(EnumDpStreamNum enumDpStreamNum)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Reg Address of Stream 1-4 is in sequence, 5-6 is in sequence2
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacTxGetDaisyStreamStartPositionRegAddress_128b132b(enumDpStreamNum);
    }
    else
#endif
    {
#if(_DP_MST_SUPPORT == _ON)
        return ScalerDpMacTxGetDaisyStreamStartPositionRegAddress_8b10b(enumDpStreamNum);
#endif
    }

    return 0;
}

//--------------------------------------------------
// Description  : Tx Mst Daisy Stream Position Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxResetDaisyStreamPositionReg(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacTxResetDaisyStreamPositionReg_128b132b();
#endif

#if(_DP_MST_SUPPORT == _ON)
    ScalerDpMacTxResetDaisyStreamPositionReg_8b10b();
#endif
}

//--------------------------------------------------
// Description  : Get Stream Source Status
// Input Value  : Source Number
// Output Value : Stream Number
//--------------------------------------------------
EnumDpStreamNum ScalerDpMacTxGetDaisySourceMuxBackup(EnumDpStreamSourceNum enumDpStreamSourceNum)
{
    return GET_DP_MAC_TX_ST_SOURCE_BACKUP(enumDpStreamSourceNum);
}

//--------------------------------------------------
// Description  : Backup ST1_Source ~ ST6_Source Mux
// Input Value  : EnumDpMstRxStreamSourceNum, EnumDpMstRxStreamNum
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetDaisySourceMuxBackup(EnumDpStreamSourceNum enumDpStreamSourceNum, EnumDpStreamNum enumDpStreamNum)
{
    if(GET_DP_MAC_TX_ST_SOURCE_BACKUP(enumDpStreamSourceNum) != enumDpStreamNum)
    {
        SET_DP_MAC_TX_ST_SOURCE_BACKUP(enumDpStreamSourceNum, enumDpStreamNum);

        SET_DP_MAC_TX_ST_SOURCE_CHANGE();
    }
}

//--------------------------------------------------
// Description  : Reset Tx Mst Daisy Stream Source Mux Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxResetDaisySourceMuxBackup(void)
{
    EnumDpStreamSourceNum enumDpStreamSourceNum = _DP_ST_SOURCE1;

    for(enumDpStreamSourceNum = _DP_ST_SOURCE1; enumDpStreamSourceNum <= _DP_ST_SOURCE_END; enumDpStreamSourceNum++)
    {
        SET_DP_MAC_TX_ST_SOURCE_BACKUP(enumDpStreamSourceNum, _DP_ST_NONE);
    }
}

//--------------------------------------------------
// Description  : DP MST Set St_source Mux Register
// Input Value  : enumSourceNum, ucValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetDaisySourceMuxReg(EnumDpStreamSourceNum enumDpStreamSourceNum, EnumDpStreamNum enumDpStreamNum)
{
#if((_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
    if(ScalerDpMacTxJudgeDaisySourceMuxCodingType() == _CODING_TYPE_128B132B)
    {
        ScalerDpMacTxSetDaisySourceMuxReg_128b132b(enumDpStreamSourceNum, enumDpStreamNum);
    }
    else
#endif
    {
#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
        ScalerDpMacTxSetDaisySourceMuxReg_8b10b(enumDpStreamSourceNum, enumDpStreamNum);
#endif
    }
}

//--------------------------------------------------
// Description  : Judge Tx Daisy Source Mux Coding
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMacTxJudgeDaisySourceMuxCodingType(void)
{
    // Rx=8b10b    Tx=128b132b MST to SST(TX MSG X) -> Set Tx14 mux
    // Rx=8b10b    Tx=128b132b MST to MST(TX MSG O) -> No support
    // Rx=8b10b    Tx=8b10b    MST to SST(TX MSG X) -> Set Tx14 mux
    // Rx=8b10b    Tx=8b10b    MST to MST(TX MSG O) -> Set Tx14 mux
    // Rx=128b132b Tx=128b132b SST to SST(TX MSG X) -> Set Tx20 mux
    // Rx=128b132b Tx=128b132b MST to SST(TX MSG X) -> Set Tx20 mux
    // Rx=128b132b Tx=128b132b MST to MST(TX MSG O) -> Set Tx20 mux
    // Rx=128b132b Tx=8b10b    MST to SST(TX MSG X) -> Set Tx20 mux
    // Rx=128b132b Tx=8b10b    MST to MST(TX MSG O) -> Set Tx14 mux

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT()) == _CODING_TYPE_8B10B)
    {
        return _CODING_TYPE_8B10B;
    }
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return _CODING_TYPE_128B132B;
    }
#endif

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if((ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT()) == _CODING_TYPE_128B132B) && (GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() != _DP_TX_MSG_SUPPORT))
    {
        return _CODING_TYPE_128B132B;
    }
#endif

    return _CODING_TYPE_8B10B;
}

//--------------------------------------------------
// Description  : Tx Mst Daisy Stream Source Mux Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxResetDaisySourceMuxReg(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacTxResetDaisySourceMuxReg_128b132b();
#endif

#if(_DP_MST_SUPPORT == _ON)
    ScalerDpMacTxResetDaisySourceMuxReg_8b10b();
#endif
}

//--------------------------------------------------
// Description  : Reset Backup and Reg ST1_Source ~ ST6_Source Mux
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxResetDaisySourceMux(void)
{
    ScalerDpMacTxResetDaisySourceMuxBackup();
    ScalerDpMacTxResetDaisySourceMuxReg();
}

//--------------------------------------------------
// Description  : Restore Stream Postion Infomation From Backup to Reg
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxRestoreDaisySourceMuxBackupToReg(void)
{
    EnumDpStreamSourceNum enumDpStreamSourceNum = _DP_ST_SOURCE1;

    for(enumDpStreamSourceNum = _DP_ST_SOURCE1; enumDpStreamSourceNum <= _DP_ST_SOURCE_END; enumDpStreamSourceNum++)
    {
        ScalerDpMacTxSetDaisySourceMuxReg(enumDpStreamSourceNum, GET_DP_MAC_TX_ST_SOURCE_BACKUP(enumDpStreamSourceNum));
    }
}

//--------------------------------------------------
// Description  : Restore Daisy Source Register When Main Port Is DP Active
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDaisyChangeHandler(void)
{
    EnumInputPort enumInputPort = GET_DP_RX_MAIN_PORT();

    if((ScalerSyncGetPortType(enumInputPort) != _PORT_DP) ||
       (ScalerDpAuxRxGetLTStatus(enumInputPort) != _DP_NORMAL_LINK_TRAINING_PASS))
    {
        if(GET_DP_MAC_TX_ST_SOURCE_CHANGE() == _FALSE)
        {
            SET_DP_MAC_TX_ST_SOURCE_CHANGE();

            ScalerDpMacTxResetDaisySourceMuxReg();
        }

        return;
    }

    if(GET_DP_MAC_TX_ST_SOURCE_CHANGE() == _TRUE)
    {
        ScalerDpMacTxRestoreDaisySourceMuxBackupToReg();

        CLR_DP_MAC_TX_ST_SOURCE_CHANGE();
    }
}

#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get DP Tx MST Daisy Stream Start Position Register Address
// Input Value  : EnumDpStreamSourceNum
// Output Value : Address
//--------------------------------------------------
WORD ScalerDpMacTxGetDaisyStreamStartPositionRegAddress_8b10b(EnumDpStreamNum enumDpStreamNum)
{
    switch(enumDpStreamNum)
    {
        case _DP_ST_1:

            return PA_06_DAISY_CTRL_1;

        case _DP_ST_2:

            return PA_08_DAISY_CTRL_3;

        case _DP_ST_3:

            return PA_0A_DAISY_CTRL_5;

        case _DP_ST_4:

            return PA_0C_DAISY_CTRL_7;

        case _DP_ST_5:

            return PA_12_DAISY_CTRL_9;

        case _DP_ST_6:

            return PA_14_DAISY_CTRL_11;

        default:

            return 0;
    }
}

//--------------------------------------------------
// Description  : Tx Mst Daisy Stream Position Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxResetDaisyStreamPositionReg_8b10b(void)
{
    // Reset st 1-6 start, end 8b10b

    // st1
    ScalerSetBit(PA_06_DAISY_CTRL_1, ~0x3F, 0x00);
    ScalerSetBit(PA_07_DAISY_CTRL_2, ~0x3F, 0x00);
    // st2
    ScalerSetBit(PA_08_DAISY_CTRL_3, ~0x3F, 0x00);
    ScalerSetBit(PA_09_DAISY_CTRL_4, ~0x3F, 0x00);
    // st3
    ScalerSetBit(PA_0A_DAISY_CTRL_5, ~0x3F, 0x00);
    ScalerSetBit(PA_0B_DAISY_CTRL_6, ~0x3F, 0x00);
    // st4
    ScalerSetBit(PA_0C_DAISY_CTRL_7, ~0x3F, 0x00);
    ScalerSetBit(PA_0D_DAISY_CTRL_8, ~0x3F, 0x00);
    // st5
    ScalerSetBit(PA_12_DAISY_CTRL_9, ~0x3F, 0x00);
    ScalerSetBit(PA_13_DAISY_CTRL_10, ~0x3F, 0x00);
    // st6
    ScalerSetBit(PA_14_DAISY_CTRL_11, ~0x3F, 0x00);
    ScalerSetBit(PA_15_DAISY_CTRL_12, ~0x3F, 0x00);
}

//--------------------------------------------------
// Description  : DP MST Set St_source Mux Register
// Input Value  : enumSourceNum, ucValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetDaisySourceMuxReg_8b10b(EnumDpStreamSourceNum enumDpStreamSourceNum, EnumDpStreamNum enumDpStreamNum)
{
    BYTE ucValue = (enumDpStreamNum == _DP_ST_NONE) ? 0 : enumDpStreamNum + 1;

    switch(enumDpStreamSourceNum)
    {
        // Set Tx Daisy Source Mux
        case _DP_ST_SOURCE1:

            ScalerSetBit(PA_17_SOURCE_CTRL_0, ~(_BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE2:

            ScalerSetBit(PA_17_SOURCE_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        case _DP_ST_SOURCE3:

            ScalerSetBit(PA_18_SOURCE_CTRL_1, ~(_BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE4:

            ScalerSetBit(PA_18_SOURCE_CTRL_1, ~(_BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        case _DP_ST_SOURCE5:

            ScalerSetBit(PA_19_SOURCE_CTRL_2, ~(_BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE6:

            ScalerSetBit(PA_19_SOURCE_CTRL_2, ~(_BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Tx Mst Daisy Stream Source Mux Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxResetDaisySourceMuxReg_8b10b(void)
{
    // Reset Tx Daisy Source Mux to Default nth Source to nth stream
    ScalerSetBit(PA_17_SOURCE_CTRL_0, ~(_BIT6 | _BIT5 | _BIT4), 0x00 << 4);
    ScalerSetBit(PA_17_SOURCE_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), 0x00 << 0);
    ScalerSetBit(PA_18_SOURCE_CTRL_1, ~(_BIT6 | _BIT5 | _BIT4), 0x00 << 4);
    ScalerSetBit(PA_18_SOURCE_CTRL_1, ~(_BIT2 | _BIT1 | _BIT0), 0x00 << 0);
    ScalerSetBit(PA_19_SOURCE_CTRL_2, ~(_BIT6 | _BIT5 | _BIT4), 0x00 << 4);
    ScalerSetBit(PA_19_SOURCE_CTRL_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00 << 0);
}
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Training Pattern Setting_128b132b
// Input Value  : Training Pattern
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxMainLinkPatternSetting_128b132b(EnumDPTxMainLinkPattern enumDPTxMainLinkPattern)
{
    // 128b132b Pattern
    ScalerSetBit(P2B_00_DP_PHY_CTRL, ~_BIT0, 0x00);
    ScalerSetByte(P2B_F4_DPTX_CLK_GEN, 0x01);

    switch(enumDPTxMainLinkPattern)
    {
        case _DP_TX_OUTPUT_IDLE_PATTERN:
            ScalerSetBit(P2B_01_DPTX_ML_PAT_SEL, ~_BIT0, 0x00);
            ScalerSetBit(P2B_07_DPTX_FUNC_MODE, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetBit(P2B_07_DPTX_FUNC_MODE, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT2));
            ScalerSetBit(P2B_C3_ARBITER_CTRL, ~(_BIT7 | _BIT5 | _BIT4), _BIT4);
            ScalerSetBit(P2B_C3_ARBITER_CTRL, ~_BIT7, _BIT7);

            // Toggle Arbiter to Avoid DPTX MAC FSM Dead Lock
            ScalerSetBit(P2B_C3_ARBITER_CTRL, ~(_BIT7 | _BIT0), 0x00);
            ScalerSetBit(P2B_C3_ARBITER_CTRL, ~(_BIT7 | _BIT0), _BIT0);

            break;
        case _DP_TX_OUTPUT_TPS1:
            ScalerSetBit(P2B_01_DPTX_ML_PAT_SEL, ~_BIT0, _BIT0);
            ScalerSetBit(P2B_07_DPTX_FUNC_MODE, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P2B_07_DPTX_FUNC_MODE, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), _BIT7);
            break;
        case _DP_TX_OUTPUT_TPS2:
            ScalerSetBit(P2B_01_DPTX_ML_PAT_SEL, ~_BIT0, 0x00);
            ScalerSetBit(P2B_07_DPTX_FUNC_MODE, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetBit(P2B_07_DPTX_FUNC_MODE, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT1));
            break;
        case _DP_TX_OUTPUT_VIDEO_PATTERN:
            ScalerSetBit(P2B_07_DPTX_FUNC_MODE, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetBit(P2B_07_DPTX_FUNC_MODE, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT2));
            ScalerSetBit(P2B_C3_ARBITER_CTRL, ~(_BIT7 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
            ScalerSetBit(P2B_C3_ARBITER_CTRL, ~_BIT7, _BIT7);
            break;
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Tx MST Calculate PBN_128b132b
// Input Value  : void
// Output Value : WORD
//--------------------------------------------------
WORD ScalerDpMacTxCalculateAllocatePBN_128b132b(void)
{
    BYTE ucColorDepth = 0;
    BYTE ucBitsPerPixel = 0;
    DWORD ulPBN = 0;
    DWORD ulA = 0;
    DWORD ulB = 0;
    DWORD ulC = 0;

    ucColorDepth = ScalerSyncDpGetColorDepthValue(GET_DP_TX_INPUT_COLOR_DEPTH(), GET_DP_TX_INPUT_COLOR_SPACE());

    // Get Color Space
    switch(GET_DP_TX_INPUT_COLOR_SPACE())
    {
        case _COLOR_SPACE_RGB: // bpp = bpc * 3
        case _COLOR_SPACE_YCBCR444: // bpp = bpc * 3
        default:
            ucBitsPerPixel = ucColorDepth * 3;
            break;

        case _COLOR_SPACE_YCBCR422: // bpp = bpc * 2
            ucBitsPerPixel = ucColorDepth << 1;
            break;

        case _COLOR_SPACE_YCBCR420: // bpp = bpc * 1.5
            ucBitsPerPixel = (ucColorDepth * 3) >> 1;
            break;

        case _COLOR_SPACE_Y_ONLY: // bpp = bpc * 1
        case _COLOR_SPACE_RAW: // bpp = bpc * 1
            ucBitsPerPixel = ucColorDepth;
            break;
    }

    // Calculate Required PBN value to allocate downstream device
    // PBN (54/64*MB/s) = Pixel Rate(Mhz) * bpp / 8 * (64/54)
    // Down spread * 1.006
    // data_bandwidth_efficiency = 0.9671
    // GET_DP_TX_INPUT_PIXEL_CLK(0.1Mhz)
    if(GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() == _FALSE)
    {
        ulA = (DWORD)GET_DP_TX_INPUT_PIXEL_CLK();
        ulB = (DWORD)ucBitsPerPixel * 64 * 1000UL;
        ulC = (DWORD)10 * 8 * 54;
        ulPBN = ScalerGlobalComputeDwordMulDiv(ulA, ulB, ulC);

        // ulPBN = (DWORD)(GET_DP_TX_INPUT_PIXEL_CLK() / 10) * ucBitsPerPixel / 8 * (64 / 54) * 1000UL;
    }
    else
    {
        ulA = (DWORD)GET_DP_TX_INPUT_PIXEL_CLK();
        ulB = (DWORD)ucBitsPerPixel * 64 * 1006UL;
        ulC = (DWORD)10 * 8 * 54;
        ulPBN = ScalerGlobalComputeDwordMulDiv(ulA, ulB, ulC);

        // ulPBN = (DWORD)(GET_DP_TX_INPUT_PIXEL_CLK() / 10) * ucBitsPerPixel / 8 * (64 / 54) * 1006UL;
    }

    ulPBN = ulPBN / 1000 + (ulPBN % 1000 > 0 ? 1 : 0);

    return (WORD)ulPBN;
}

//--------------------------------------------------
// Description  : DP Tx MST Measure PBN_128b132b
// Input Value  : void
// Output Value : WORD
//--------------------------------------------------
WORD ScalerDpMacTxMeasureAllocatePBN_128b132b(void)
{
    WORD usMeasurePBN = 0;
    WORD usMeasureTimeslotCnt = 0;
    // unit(0.01PBN)
    WORD usSourceOneTimeSlotPBN = ScalerDpMacDphyRxGetPBNPerTimeSlot(ScalerDpAuxRxGetLinkRate(GET_DP_RX_MAIN_PORT()), ScalerDpAuxRxGetLaneCount(GET_DP_RX_MAIN_PORT()));

    // enable measure
    ScalerSetBit(P2B_E8_MTP_MISC, ~(_BIT7 | _BIT3), _BIT3);

    // wait 1024MTP = 65536T
    // 10G : 1T = 3.2ns
    // 65536T = 209us
    DELAY_XUS(500);

    // measure done flag
    if(ScalerGetBit(P2B_E8_MTP_MISC, _BIT7) == _BIT7)
    {
        usMeasureTimeslotCnt = ScalerGetWord(P2B_E9_TIMESLOT_CNT_0);

        if((ScalerDpAuxRxGetDpcdInfo(GET_DP_RX_MAIN_PORT(), 0x00, 0x01, 0x07) & _BIT4) == _BIT4)
        {
            // (usMeasureTimeslotCnt * 1000 / 1006) * usSourceOneTimeSlotPBN / 102400
            // = usMeasureTimeslotCnt * usSourceOneTimeSlotPBN * 10 / (1006 * 1024)
            // ~=  usMeasureTimeslotCnt * usSourceOneTimeSlotPBN / 103014
            usMeasurePBN = GET_DWORD_MUL_DIV(usMeasureTimeslotCnt, usSourceOneTimeSlotPBN, 103014);
        }
        else
        {
            usMeasurePBN = GET_DWORD_MUL_DIV(usMeasureTimeslotCnt, usSourceOneTimeSlotPBN, 102400);
        }
    }

    // disable measure
    ScalerSetBit(P2B_E8_MTP_MISC, ~(_BIT7 | _BIT3), 0x00);

    return usMeasurePBN;
}

//--------------------------------------------------
// Description  : DP Tx MST Sync table_128b132b
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSyncTableProcess_128b132b(void)
{
    BYTE ucPayloadID = 1;
    WORD usPBN = ScalerDpMacTxCalculateAllocatePBN_128b132b();

    if((GET_DP_TX_STREAM_DATA_PATH_TYPE() == _DATA_PATH_VIDEO_BYPASS) ||
       (GET_DP_TX_STREAM_DATA_PATH_TYPE() == _DATA_PATH_DSC_BYPASS))
    {
        WORD usMeasurePBN = ScalerDpMacTxMeasureAllocatePBN_128b132b();

        if(usMeasurePBN > usPBN)
        {
            usPBN = usMeasurePBN;
        }
    }

    ScalerDpMacTxSyncPayloadIDTable(ucPayloadID, usPBN);
}

//--------------------------------------------------
// Description  : DP Tx Data mux Set_128b132b
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxDataMuxConfig_128b132b(void)
{
    switch(GET_DP_TX_STREAM_DATA_PATH_TYPE())
    {
        case _DATA_PATH_VESA:
        case _DATA_PATH_DSC_DECODER:
        case _DATA_PATH_VIDEO_REORDER:
        case _DATA_PATH_DSC_REORDER:
            break;

        case _DATA_PATH_DSC_BYPASS:
        case _DATA_PATH_VIDEO_BYPASS:

            if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
            {
                if(GET_DP_MAC_TX_ST_SOURCE_BACKUP(_DP_ST_SOURCE1) != _DP_ST_1)
                {
                    SET_DP_MAC_TX_ST_SOURCE_BACKUP(_DP_ST_SOURCE1, _DP_ST_1);

                    ScalerDpMacTxSetDaisySourceMuxReg_128b132b(_DP_ST_SOURCE1, _DP_ST_1);
                }
            }
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Tx SST Set_128b132b
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSSTSetting_128b132b(void)
{
    // MSA Setting
    ScalerDpMacTxSSTMSASetting_128b132b();

    ScalerDpMacTxSSTDisplayFormatSetting_128b132b();

#if(_DP_TX_AUDIO_SUPPORT == _ON)

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))
    if(GET_DP_TX_AUDIO_STAND_ALONE() == _ON)
    {
        // Disable Audio
        ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_OFF);
    }
#endif

    // Set up Audio Output
    ScalerDpMacTxSdpAudioPlayProc(_DP_TX_AUDIO_PRESET);
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : DP Tx MSA Setting_128b132b
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSSTMSASetting_128b132b(void)
{
    // MSA
    // VFreq[47:0]= pixel clk(Hz)
    // htotal,Hstart,HWidth,Vtotal,Start,Vheight,Vsync and Polarity,Hync and Polarity,Color Format
    // GET_DP_MAC_TX_INPUT_PIXEL_CLK
    // GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD
    // g_stDpMacTxXInputTimingInfo
    // GET_DP_MAC_TX_INPUT_COLOR_DEPTH
    // GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM
    // GET_DP_MAC_TX_INPUT_COLOR_SPACE
    // GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM
    // GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE

    // Enable Sdp Split
    ScalerDpMacTxSdpSplit(GET_DP_TX_DOWNSTREAM_SPLIT_SDP_SUPPORT());

    // Reset MSA Generation Block and SEC Block
    ScalerSetBit(P2B_A1_DP_RESET_CTRL, ~_BIT6, _BIT6);
    ScalerSetBit(P2B_A1_DP_RESET_CTRL, ~_BIT6, 0x00);

    // Set Htotal
    ScalerSetByte(P2B_AB_MN_STRM_ATTR_HTT_M, HIBYTE(g_stDpMacTxInputTimingInfo.usHTotal));
    ScalerSetByte(P2B_AC_MN_STRM_ATTR_HTT_L, LOBYTE(g_stDpMacTxInputTimingInfo.usHTotal));

    // Set Hstart
    ScalerSetByte(P2B_AD_MN_STRM_ATTR_HST_M, HIBYTE(g_stDpMacTxInputTimingInfo.usHStart));
    ScalerSetByte(P2B_AE_MN_STRM_ATTR_HST_L, LOBYTE(g_stDpMacTxInputTimingInfo.usHStart));

    // Set Hwidth
    ScalerSetByte(P2B_AF_MN_STRM_ATTR_HWD_M, HIBYTE(g_stDpMacTxInputTimingInfo.usHWidth));
    ScalerSetByte(P2B_B0_MN_STRM_ATTR_HWD_L, LOBYTE(g_stDpMacTxInputTimingInfo.usHWidth));

    // Set Hsyc and Polarity
    pData[0] = ((HIBYTE(g_stDpMacTxInputTimingInfo.usHSWidth) & 0x7F) | ((BYTE)g_stDpMacTxInputTimingInfo.b1HSP << 7));

    // Set Hsyc and Polarity
    ScalerSetByte(P2B_B1_MN_STRM_ATTR_HSW_M, pData[0]);
    ScalerSetByte(P2B_B2_MN_STRM_ATTR_HSW_L, LOBYTE(g_stDpMacTxInputTimingInfo.usHSWidth));

    // Set Vtotal
    ScalerSetByte(P2B_B3_MN_STRM_ATTR_VTTE_M, HIBYTE(g_stDpMacTxInputTimingInfo.usVTotal));
    ScalerSetByte(P2B_B4_MN_STRM_ATTR_VTTE_L, LOBYTE(g_stDpMacTxInputTimingInfo.usVTotal));

    // Set VStart
    ScalerSetByte(P2B_B5_MN_STRM_ATTR_VST_M, HIBYTE(g_stDpMacTxInputTimingInfo.usVStart));
    ScalerSetByte(P2B_B6_MN_STRM_ATTR_VST_L, LOBYTE(g_stDpMacTxInputTimingInfo.usVStart));

    // Set VHeight
    ScalerSetByte(P2B_B7_MN_STRM_ATTR_VHT_M, HIBYTE(g_stDpMacTxInputTimingInfo.usVHeight));
    ScalerSetByte(P2B_B8_MN_STRM_ATTR_VHT_L, LOBYTE(g_stDpMacTxInputTimingInfo.usVHeight));

    // Set Vsyc and Polarity
    pData[0] = ((HIBYTE(g_stDpMacTxInputTimingInfo.usVSWidth) & 0x7F) | ((BYTE)g_stDpMacTxInputTimingInfo.b1VSP << 7));

    // Set Vsyc and Polarity
    ScalerSetByte(P2B_B9_MN_STRM_ATTR_VSW_M, pData[0]);
    ScalerSetByte(P2B_BA_MN_STRM_ATTR_VSW_L, LOBYTE(g_stDpMacTxInputTimingInfo.usVSWidth));

    // Vfreq = (pixel clk) Hz
    ScalerSetByte(P2B_BB_MN_STRM_VREF_0, (BYTE)((GET_DP_TX_INPUT_PIXEL_CLK() * 100000 >> 24 >> 16)));
    ScalerSetByte(P2B_BC_MN_STRM_VREF_1, (BYTE)((GET_DP_TX_INPUT_PIXEL_CLK() * 100000 >> 24 >> 8)));
    ScalerSetByte(P2B_BD_MN_STRM_VREF_2, (BYTE)((GET_DP_TX_INPUT_PIXEL_CLK() * 100000 >> 24)));
    ScalerSetByte(P2B_BE_MN_STRM_VREF_3, (BYTE)((GET_DP_TX_INPUT_PIXEL_CLK() * 100000 >> 16)));
    ScalerSetByte(P2B_BF_MN_STRM_VREF_4, (BYTE)((GET_DP_TX_INPUT_PIXEL_CLK() * 100000 >> 8)));
    ScalerSetByte(P2B_C0_MN_STRM_VREF_5, (BYTE)(GET_DP_TX_INPUT_PIXEL_CLK() * 100000));

    // MSA_DB = 1
    ScalerSetBit(P2B_A8_MSA_CTRL, ~_BIT7, _BIT7);

    // Set Color Format
    ScalerDpMacTxMsaMiscSetting();

    // Set VSC SDP Send Disable
    ScalerSetBit(P2C_00_SEC_FUNCTION_CTRL, ~_BIT2, 0x00);

    if(GET_DP_TX_VSC_SDP_SEND_ENABLE() == _TRUE)
    {
        ScalerDpMacTxVscSdpSetting();

        // Set VSC SDP Send Enable
        ScalerSetBit(P2C_00_SEC_FUNCTION_CTRL, ~_BIT2, _BIT2);

        ScalerDpMacTxSdpSetHeaderByte(_SEC_PACKET_TYPE_VSC, _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);

        // Set MISC1[6] to indicate VSC SDP is used and ignoring the info in MSA
        ScalerSetBit(P2B_AA_MN_STRM_ATTR_MISC1, ~_BIT6, _BIT6);
    }
    else
    {
        ScalerSetBit(P2B_AA_MN_STRM_ATTR_MISC1, ~_BIT6, 0x00);
    }

    DebugMessageDpTx("DP Tx MSA Color Space 1", GET_DP_TX_INPUT_COLOR_SPACE());

    // MSA_DB = 1
    ScalerSetBit(P2B_A8_MSA_CTRL, ~_BIT7, _BIT7);

    if(GET_DP_TX_INPUT_INTERLACE_MODE() == _ON)
    {
        // Set MISC1
        if(GET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER() == _EVEN)
        {
            ScalerSetBit(P2B_AA_MN_STRM_ATTR_MISC1, ~_BIT0, _BIT0);
        }
        else
        {
            ScalerSetBit(P2B_AA_MN_STRM_ATTR_MISC1, ~_BIT0, 0x00);
        }
    }

    // MSA_DB = 1
    ScalerSetBit(P2B_A8_MSA_CTRL, ~_BIT7, _BIT7);

    DebugMessageDpTx("DP Tx MSA Color Space 2", ScalerGetBit(P2B_A9_MSA_MISC0, (_BIT2 | _BIT1)));
}

//--------------------------------------------------
// Description  : DP Tx SST Display FormatSetting_128b132b
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSSTDisplayFormatSetting_128b132b(void)
{
    // TU
    // hdelay
    // valid data per lane
    // GET_DP_MAC_TX_INPUT_PIXEL_CLK
    // GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD
    // g_stDpMacTxXInputTimingInfo
    // GET_DP_MAC_TX_INPUT_COLOR_DEPTH
    // GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM
    // GET_DP_MAC_TX_INPUT_COLOR_SPACE
    // GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM
    // GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE
    WORD usValidDataPerLane = 0;
    BYTE ucColorDepth = 0;
    WORD usFifoOffset = 0;
    BYTE ucMacLaneNum = 4;
    WORD usSdpPacket = 0;
    WORD usBe2Be = 0;
    WORD usBs2Be = 0;

    // Pixel Generation Block Reset
    ScalerSetBit(P2B_A1_DP_RESET_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(P2B_A1_DP_RESET_CTRL, ~_BIT7, 0x00);

    // Set Interlace Bit of VBID as Interlace Mode Detected and Set Video Flag of VBID
    if(GET_DP_TX_INPUT_INTERLACE_MODE() == _ON)
    {
        ScalerSetBit(P2B_C1_VBID, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(P2B_C1_VBID, ~_BIT0, 0x00);
    }

    ucColorDepth = ScalerSyncDpGetColorDepthValue(GET_DP_TX_INPUT_COLOR_DEPTH(), GET_DP_TX_INPUT_COLOR_SPACE());

    // Get Color Space
    switch(GET_DP_TX_INPUT_COLOR_SPACE())
    {
        case _COLOR_SPACE_YCBCR422:
            ucColorDepth = ucColorDepth << 1;
            break;

        case _COLOR_SPACE_YCBCR420:
            ucColorDepth = (ucColorDepth * 3) >> 1;
            break;

        case _COLOR_SPACE_Y_ONLY:
            ucColorDepth = ucColorDepth;
            break;

        default:
            ucColorDepth = ucColorDepth * 3;
            break;
    }

    // =========================================
    // Step 1: Cal vaild symbol in TU
    // =========================================

    // Average TU = TU Size x (Stream_Clk x Byte of 1 pixel / Lane Number) / Link Rate
    if(GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() == _FALSE)
    {
        DWORD ulA = (DWORD)_DP_TX_SST_TU_SIZE * ucColorDepth;
        DWORD ulB = (DWORD)GET_DP_TX_INPUT_PIXEL_CLK() * 10UL;
        DWORD ulC = (DWORD)ucMacLaneNum * 10UL * _DP_TX_LINK_CLK_MHZ_128B132B;

        // Average TU = TU Size x Color Depth x Stream_Clk / (Lane Number x Link Rate)
        PDATA_WORD(1) = GET_DWORD_MUL_DIV(ulA, ulB, ulC);
    }
    else
    {
        DWORD ulA = (DWORD)_DP_TX_SST_TU_SIZE * ucColorDepth;
        DWORD ulB = (DWORD)GET_DP_TX_INPUT_PIXEL_CLK() * 1000UL * 10UL;
        DWORD ulC = (DWORD)ucMacLaneNum * _DP_TX_LINK_CLK_MHZ_128B132B * 9975UL;

        // Average TU = TU Size x Color Depth x Stream_Clk / Lane Number * SSCG of Link Rate)
        PDATA_WORD(1) = GET_DWORD_MUL_DIV(ulA, ulB, ulC);
    }

    // PDATA_WORD(1) = PDATA_WORD(1) / 10 + (PDATA_WORD(1) % 10 >= 5 ? 1 : 0);

    ScalerSetByte(P2B_C6_TU_SIZE, _DP_TX_SST_TU_SIZE);
    ScalerSetByte(P2B_C7_TU_DATA_SIZE0, (PDATA_WORD(1) / 100) & 0x7F);
    ScalerSetByte(P2B_C8_TU_DATA_SIZE1, (((PDATA_WORD(1) % 100) << 8) / 100) + 1);

    // Calculate Pixel Numbers Per Lane
    usValidDataPerLane = g_stDpMacTxInputTimingInfo.usHWidth / ucMacLaneNum + (((g_stDpMacTxInputTimingInfo.usHWidth % ucMacLaneNum) > 0) ? 1 : 0);

    // Calculate Link Symbol Numbers Per Lane
    usValidDataPerLane = (DWORD)usValidDataPerLane * ucColorDepth / 32 + ((((DWORD)usValidDataPerLane * ucColorDepth % 32) > 0) ? 1 : 0);

    // =========================================
    // Step 2. SET Data Count
    // =========================================

    // Set Valid Data Per Lane
    ScalerSetByte(P2B_C4_V_DATA_PER_LINE0, HIBYTE(usValidDataPerLane));
    ScalerSetByte(P2B_C5_V_DATA_PER_LINE1, LOBYTE(usValidDataPerLane));

    // Get TU Number Per Line
    PDATA_WORD(0) = (usValidDataPerLane * 320) / PDATA_WORD(1) + (((usValidDataPerLane * 320) % PDATA_WORD(1) > 0) ? 1 : 0);

    // Store Horizontal DE for Sec Data End Count
    SET_DP_TX_HORIZONTAL_DE_PERIOD(PDATA_WORD(0) * _DP_TX_SST_TU_SIZE);

    // SET Seccondary End Count for Audio OFF
    // SDP_packet = SS&SE + HEADER&ECC BYTES / lane_num + (DATA_BYTES + DATA_P_BYTES) / lane_num.
    usSdpPacket = 2 + ((8 + 32 + 8) / GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM());

    // Get BE2BE Period with Htotal
    usBe2Be = g_stDpMacTxInputTimingInfo.usHTotal * 10UL * _DP_TX_LINK_CLK_MHZ_128B132B / GET_DP_TX_INPUT_PIXEL_CLK();

    // Get 70% of blanking period
    usBs2Be = (usBe2Be - GET_DP_TX_HORIZONTAL_DE_PERIOD()) * 7 / 10;

    // SET Seccondary End Count 70%Blanking-SDP_packet
    ScalerSetByte(P2B_CE_ARBITER_SEC_END_CNT_HB, HIBYTE(usBs2Be - usSdpPacket));
    ScalerSetByte(P2B_CF_ARBITER_SEC_END_CNT_LB, LOBYTE(usBs2Be - usSdpPacket));

    // Set SEC END CNT Double Buffer
    SET_DP_TX_SEC_END_CNT_DB_128B132B();

    // =========================================
    // Step 3: FW manual Calculate H Delay
    // =========================================

    // DP fifo size = 256 * 144 bit
    // FifoOffset = (1/2 * (256 * 144) / (color space * depth per color))
    usFifoOffset = (WORD)18432 / ucColorDepth;

    if((g_usDpMacTxInputHStartMeasure + usFifoOffset) < g_usDpMacTxInputHWidthMeasure)
    {
        PDATA_WORD(2) = (g_usDpMacTxInputHStartMeasure + usFifoOffset) * (((DWORD)_DP_TX_LINK_CLK_MHZ_128B132B) * 100) / ((DWORD)GET_DP_TX_INPUT_PIXEL_CLK() * 32);
    }
    else
    {
        PDATA_WORD(2) = (g_usDpMacTxInputHStartMeasure + g_usDpMacTxInputHWidthMeasure) * (((DWORD)_DP_TX_LINK_CLK_MHZ_128B132B) * 100) / ((DWORD)GET_DP_TX_INPUT_PIXEL_CLK() * 32);
    }

    ScalerSetByte(P2B_C9_HDEALY0, HIBYTE(PDATA_WORD(2)));
    ScalerSetByte(P2B_CA_HDEALY1, LOBYTE(PDATA_WORD(2)));

    // set pixel mode
    DebugMessageDpTx("DP Tx 2.0 Mac Pixel Mode Setting", GET_DP_MAC_TX_INPUT_PIXEL_MODE());
    ScalerSetBit(P2B_F7_PG_MODE, ~(_BIT3 | _BIT2), (GET_DP_MAC_TX_INPUT_PIXEL_MODE() << 2));

    // Clear FIFO Status
    ScalerSetByte(P2B_A4_PG_FIFO_CTRL, 0xFF);
}

//--------------------------------------------------
// Description  : DP Tx SEC Data Handler
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSdpHwBypassSetting_128b132b(bit bEnable)
{
    if(bEnable == _TRUE)
    {
        // HB0 Setting
        ScalerSetByte(P2C_B5_SEC_PANEL_REPLAY_RX_HB0, 0x00);

        // HB1 Setting
#if(_DP_HDR10_SUPPORT == _ON)
        ScalerSetByte(P2C_C0_SDP_BYPASS_TYPE0, _DP_SDP_TYPE_INFOFRAME_HDR);
#endif

#if(_DP_TX_AUDIO_SUPPORT == _ON)
        ScalerSetByte(P2C_C1_SDP_BYPASS_TYPE1, _DP_SDP_TYPE_INFOFRAME_AUDIO);
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        ScalerSetByte(P2C_C2_SDP_BYPASS_TYPE2, _DP_SDP_TYPE_INFOFRAME_SPD);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        // HB Setting
        ScalerSetByte(P2C_91_AS_SDP_BYPASS_0, 0x00);
        ScalerSetByte(P2C_92_AS_SDP_BYPASS_1, 0x22);

        // Enable Transmit
        ScalerSetBit(P2C_00_SEC_FUNCTION_CTRL, ~_BIT4, _BIT4);
        ScalerSetBit(P2C_5A_ADAPT_SYNC, ~_BIT0, _BIT0);
#endif
        // Enable Transmit
        ScalerSetBit(P2C_A5_SDP_CTRL1, ~_BIT0, _BIT0);

        if(ScalerDpMacTxPollingFlagAfterSetProc(_DP_ONE_FRAME_TIME_MAX, P2C_BF_SDP_BYPASS_DECODE_EN, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _FALSE) == _TRUE)
        {
            DebugMessageDpTx("DP2.0 SDP HW Bypass Setting Succeed", 1);
        }
    }
    else
    {
        if(ScalerGetBit(P2C_A5_SDP_CTRL1, _BIT0) == _BIT0)
        {
            // Disable Transmit
            ScalerSetBit(P2C_A5_SDP_CTRL1, ~_BIT0, 0x00);

            // Disable SDP bypass decode
            ScalerSetBit(P2C_BF_SDP_BYPASS_DECODE_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

            // HB0 Setting
            ScalerSetByte(P2C_B5_SEC_PANEL_REPLAY_RX_HB0, 0x00);

            // HB1 Setting
#if(_DP_HDR10_SUPPORT == _ON)
            ScalerSetByte(P2C_C0_SDP_BYPASS_TYPE0, 0x00);
#endif

#if(_DP_TX_AUDIO_SUPPORT == _ON)
            ScalerSetByte(P2C_C1_SDP_BYPASS_TYPE1, 0x00);
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
            ScalerSetByte(P2C_C2_SDP_BYPASS_TYPE2, 0x00);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
            ScalerSetBit(P2C_5A_ADAPT_SYNC, ~_BIT0, 0x00);
            ScalerSetBit(P2C_00_SEC_FUNCTION_CTRL, ~_BIT4, 0x00);
            ScalerSetByte(P2C_91_AS_SDP_BYPASS_0, 0x00);
            ScalerSetByte(P2C_92_AS_SDP_BYPASS_1, 0x00);
#endif
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Set Header byte for Sec Data
// Input Value  : Packet Header
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpSetHeaderByte_128b132b(BYTE *pucData, EnumDPTxSdpDoubleBufferType enumDoubleBufferType)
{
    // Set Header Byte
    ScalerSetByte(P2C_73_SEC_PH_HB0, pucData[0]);
    ScalerSetByte(P2C_74_SEC_PH_HB1, pucData[1]);
    ScalerSetByte(P2C_75_SEC_PH_HB2, pucData[2]);
    ScalerSetByte(P2C_76_SEC_PH_HB3, pucData[3]);

    // Set Double Buffer
    ScalerSetBit(P2C_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), enumDoubleBufferType);
}

//--------------------------------------------------
// Description  : Set InfoFrame Data Bytes
// Input Value  : EnumDPTxSecDataPacketType
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSdpSetDataByte_128b132b(EnumDPTxSdpTypeForDB enumSdpTypeSel, BYTE *pucInfoFrameData, BYTE ucLength, EnumDPTxSdpDoubleBufferType enumDoubleBufferType)
{
    // Set SDP Type for Data Byte Storage Area Select
    ScalerSetBit(P2C_8D_RESERVED_8D, ~(_BIT2 | _BIT1 | _BIT0), enumSdpTypeSel);

    // Initial Addr
    ScalerSetByte(P2C_8B_SEC_INFO_VSIF_ADDR_8B, 0x00);

    for(pData[0] = 0; pData[0] < ucLength; pData[0] ++)
    {
        // Write Data Bytes to The Selected Storage Area
        ScalerSetByte(P2C_8C_SEC_INFO_VSIF_DATA_8C, pucInfoFrameData[pData[0]]);
    }
    for(pData[0] = ucLength; pData[0] < _DP_TX_INFOFRAME_DATA_LENGTH_MAX; pData[0] ++)
    {
        // padding zero
        ScalerSetByte(P2C_8C_SEC_INFO_VSIF_DATA_8C, 0x00);
    }

    // Set Double Buffer
    ScalerSetBit(P2C_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), enumDoubleBufferType);
}

//--------------------------------------------------
// Description  : DP Tx Clear Header byte for Sec Data
// Input Value  : Packet Header
// Output Value : Packet Parity
//--------------------------------------------------
void ScalerDpMacTxSdpClearHeaderByte_128b132b(EnumDPTxSecDataPacketType enumPackettype)
{
    // Select Packet Type
    ScalerSetBit(P2C_7B_SEC_PH_PACKET_TYPE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumPackettype);

    // Set Header Byte
    ScalerSetByte(P2C_73_SEC_PH_HB0, 0x00);
    ScalerSetByte(P2C_74_SEC_PH_HB1, 0x00);
    ScalerSetByte(P2C_75_SEC_PH_HB2, 0x00);
    ScalerSetByte(P2C_76_SEC_PH_HB3, 0x00);

    // Set Double Buffer
    ScalerSetBit(P2C_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);
}

//--------------------------------------------------
// Description  : DP Tx Sdp Bypass Reset
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacTxSdpReset_128b132b(void)
{
    if(ScalerGetByte(P2C_00_SEC_FUNCTION_CTRL) == 0x00)
    {
        return;
    }

    // Disable Infoframe Sdp and Vsc Sdp Transmission
    ScalerSetByte(P2C_00_SEC_FUNCTION_CTRL, 0x00);

    // Set Sdp Transmission Setting(0x2C00) Active Immediatly
    ScalerSetBit(P2C_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE);
}
#endif

#if((_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get DP Tx MST Daisy Stream Start Position Register Address
// Input Value  : EnumDpStreamSourceNum
// Output Value : Address
//--------------------------------------------------
WORD ScalerDpMacTxGetDaisyStreamStartPositionRegAddress_128b132b(EnumDpStreamNum enumDpStreamNum)
{
    switch(enumDpStreamNum)
    {
        case _DP_ST_1:

            return P2B_D4_SOURCE_CTRL_1;

        case _DP_ST_2:

            return P2B_D6_SOURCE_CTRL_3;

        case _DP_ST_3:

            return P2B_D8_SOURCE_CTRL_5;

        case _DP_ST_4:

            return P2B_DA_SOURCE_CTRL_7;

        case _DP_ST_5:

            return P2B_90_SOURCE_CTRL_11;

        case _DP_ST_6:

            return P2B_92_SOURCE_CTRL_13;

        default:

            return 0;
    }
}

//--------------------------------------------------
// Description  : Tx Mst Daisy Stream Position Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxResetDaisyStreamPositionReg_128b132b(void)
{
    // Reset Stream 1-6 enable
    ScalerSetBit(P2B_D3_SOURCE_CTRL_0, ~0x3F, 0x00);

    // Reset Stream 1-6 start, end 8b10b

    // st1
    ScalerSetBit(P2B_D4_SOURCE_CTRL_1, ~0x3F, 0x00);
    ScalerSetBit(P2B_D5_SOURCE_CTRL_2, ~0x3F, 0x00);
    // st2
    ScalerSetBit(P2B_D6_SOURCE_CTRL_3, ~0x3F, 0x00);
    ScalerSetBit(P2B_D7_SOURCE_CTRL_4, ~0x3F, 0x00);
    // st3
    ScalerSetBit(P2B_D8_SOURCE_CTRL_5, ~0x3F, 0x00);
    ScalerSetBit(P2B_D9_SOURCE_CTRL_6, ~0x3F, 0x00);
    // st4
    ScalerSetBit(P2B_DA_SOURCE_CTRL_7, ~0x3F, 0x00);
    ScalerSetBit(P2B_DB_SOURCE_CTRL_8, ~0x3F, 0x00);
    // st5
    ScalerSetBit(P2B_90_SOURCE_CTRL_11, ~0x3F, 0x00);
    ScalerSetBit(P2B_91_SOURCE_CTRL_12, ~0x3F, 0x00);
    // st6
    ScalerSetBit(P2B_92_SOURCE_CTRL_13, ~0x3F, 0x00);
    ScalerSetBit(P2B_93_SOURCE_CTRL_14, ~0x3F, 0x00);
}

//--------------------------------------------------
// Description  : DP MST Set St_source Mux Register
// Input Value  : enumSourceNum, ucValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxSetDaisySourceMuxReg_128b132b(EnumDpStreamSourceNum enumDpStreamSourceNum, EnumDpStreamNum enumDpStreamNum)
{
    BYTE ucValue = (enumDpStreamNum == _DP_ST_NONE) ? 0 : enumDpStreamNum + 1;

    switch(enumDpStreamSourceNum)
    {
        // Set Tx Daisy Source Mux
        case _DP_ST_SOURCE1:

            ScalerSetBit(P2B_DC_SOURCE_CTRL_9, ~(_BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE2:

            ScalerSetBit(P2B_DC_SOURCE_CTRL_9, ~(_BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        case _DP_ST_SOURCE3:

            ScalerSetBit(P2B_DD_SOURCE_CTRL_10, ~(_BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE4:

            ScalerSetBit(P2B_DD_SOURCE_CTRL_10, ~(_BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        case _DP_ST_SOURCE5:

            ScalerSetBit(P2B_94_SOURCE_CTRL_15, ~(_BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE6:

            ScalerSetBit(P2B_94_SOURCE_CTRL_15, ~(_BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Tx Mst Daisy Stream Source Mux Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxResetDaisySourceMuxReg_128b132b(void)
{
    // Reset Tx Daisy Source Mux to Default nth Source to nth stream
    ScalerSetBit(P2B_DC_SOURCE_CTRL_9, ~(_BIT6 | _BIT5 | _BIT4), 0x00 << 4);
    ScalerSetBit(P2B_DC_SOURCE_CTRL_9, ~(_BIT2 | _BIT1 | _BIT0), 0x00 << 0);
    ScalerSetBit(P2B_DD_SOURCE_CTRL_10, ~(_BIT6 | _BIT5 | _BIT4), 0x00 << 4);
    ScalerSetBit(P2B_DD_SOURCE_CTRL_10, ~(_BIT2 | _BIT1 | _BIT0), 0x00 << 0);
    ScalerSetBit(P2B_94_SOURCE_CTRL_15, ~(_BIT6 | _BIT5 | _BIT4), 0x00 << 4);
    ScalerSetBit(P2B_94_SOURCE_CTRL_15, ~(_BIT2 | _BIT1 | _BIT0), 0x00 << 0);
}
#endif

//--------------------------------------------------
// Description  : Downsteram EDID Vendor and Product Info Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxDownStreamEdidCheckSpecialVendor(void)
{
    // EDID address 0x08-0x09:manufacturer, 0x0A-0x0B: Product
    BYTE pucVendorProduct[4] = {0};
    BYTE ucEdidReadLength = 0x04;
    BYTE ucEdidOffset = 0x08;
    WORD usManufacturer = 0x00;
    WORD usProductID = 0x00;
    EnumDPTxEdidVendorModel enumDPTxEdidVendorModel = 0x00;

    // Step1: Read Tx Downstream EDID of Vendor and Product only
#if(_DFP_SINK_EDID_CHANGE_CHECK_METHOD == _EDID_SHA_CODE)
    if(ScalerDpAuxTxI2CoverWrite(0x50, 1, &ucEdidOffset, 1) == _FALSE)
    {
        return;
    }

    if(ScalerDpAuxTxI2CoverRead(0x50, ucEdidReadLength, pucVendorProduct, 0) == _FALSE)
    {
        return;
    }
#else
    pucVendorProduct[0] = g_pucDpMacTxPreviousDfpDeviceEdidBackup[ucEdidOffset];
    pucVendorProduct[1] = g_pucDpMacTxPreviousDfpDeviceEdidBackup[ucEdidOffset + 1];
    pucVendorProduct[2] = g_pucDpMacTxPreviousDfpDeviceEdidBackup[ucEdidOffset + 2];
    pucVendorProduct[3] = g_pucDpMacTxPreviousDfpDeviceEdidBackup[ucEdidOffset + 3];
#endif

    usManufacturer = (((WORD)pucVendorProduct[1] << 8) | pucVendorProduct[0]);
    usProductID = (((WORD)pucVendorProduct[3] << 8) | pucVendorProduct[2]);

    // Step2: Check if it's a special vendor model and record the result
    if(usManufacturer == 0x6904)
    {
        if(usProductID == 0x24B1)
        {
            enumDPTxEdidVendorModel = _EDID_VENDOR_ASUS_PA248;
        }
    }
    else
    {
        enumDPTxEdidVendorModel = _EDID_VENDOR_NONE;
    }

    SET_DP_MAC_TX_EDID_VENDOR_MODEL(enumDPTxEdidVendorModel);
}

//--------------------------------------------------
// Description  : Write Downstream DPCD 00111[0] Mst Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxMstEnableSetting(void)
{
    BYTE ucDownstreamMSTStatus = 0x00;

    if(ScalerDpAuxTxNativeRead(0x00, 0x01, 0x11, 1, &ucDownstreamMSTStatus) == _FALSE)
    {
        ucDownstreamMSTStatus = GET_DP_MAC_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS() << 1;
    }

    if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_MST)
    {
        ucDownstreamMSTStatus = (ucDownstreamMSTStatus & 0x0FE);
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x11, 1, &ucDownstreamMSTStatus);

        return;
    }

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        if(GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _TRUE)
        {
            ucDownstreamMSTStatus = (ucDownstreamMSTStatus | _BIT0);
            ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x11, 1, &ucDownstreamMSTStatus);
        }
        else
        {
            ucDownstreamMSTStatus = (ucDownstreamMSTStatus & 0x0FE);
            ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x11, 1, &ucDownstreamMSTStatus);
        }
    }
    else
#endif
    {
        ucDownstreamMSTStatus = (ucDownstreamMSTStatus | _BIT0);
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x11, 1, &ucDownstreamMSTStatus);
    }
}

//--------------------------------------------------
// Description  : Get DPTx Lttpr Initial Mode
// Input Value  : None
// Output Value : Lttpr Mode
//--------------------------------------------------
BYTE ScalerDpMacTxGetLttprInitialMode(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)

    // 128b/132b DP TX Only Support Non-Transparent Mode
    return _DP_TX_LTTPR_NON_TRANSPARENT_MODE;
#else

    // 8b/10b DP Tx Lttpr Mode By User
    return _DP_TX_LTTPR_MODE_8B10B;
#endif
}

//--------------------------------------------------
// Description  : Grant DPTx Lttpr Ext Wake TimeOut
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxLttprExtWakeTimeOutGrant(void)
{
    BYTE pucData[1];

    if(g_pucDpMacTxDfpLTTPRCap[3] == 0x55)
    {
        // Lttpr Transparent Mode
        pucData[0] = 0x01;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x19, 1, pucData);
    }
    else if(g_pucDpMacTxDfpLTTPRCap[3] == 0xAA)
    {
        // Lttpr Non-Transparent Mode
        pucData[0] = (0x80 | g_pucDpMacTxDfpLTTPRCap[5]);
        ScalerDpAuxTxNativeWrite(0x0F, 0x00, 0x05, 1, pucData);

        pucData[0] = 0x01;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x19, 1, pucData);
    }
}
#endif // End for #if(_DP_MAC_TX_SUPPORT == _ON)

