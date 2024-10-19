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
// ID Code      : ScalerDpMacMstToSst.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_MST_TO_SST__

#include "ScalerFunctionInclude.h"
#include "DpMacMstToSst/ScalerDpMacMstToSst.h"

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile bit g_bDpMacMstToSstEnable = 0;
bit g_bDpMacMstToSstInitial;
bit g_bDpMacMstToSstStreamJudge;

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
volatile bit g_bDpMacMstToSstDscDeodeEnable;
volatile bit g_bDpMacMstToSstDscDeodeDetectEnable;
#endif

#if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)
StructMstToSstAudio g_stDpMacMstToSstAudio;
#endif // End of #if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)

StructMstToSstStream g_stDpMacMstToSstStream;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Dp Multi-Stream Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstStreamsHandler(void)
{
    ScalerDpMacMstToSstProc();
}

//--------------------------------------------------
// Description  : Mst To Sst Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstInitial(void)
{
    // RS decode clk sel to Rx link clk
    ScalerSetBit(PA_03_MST2SST_CLK_GATE, ~_BIT7, 0x00);

    // Reset Daisy Chain Async-fifo
    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, _BIT6);
    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, 0x00);

    // Enable MST
    ScalerSetBit(PA_02_MST2SST_CONFIG, ~_BIT7, _BIT7);

    // Assign Mac For MST2SST
    ScalerDpRxMacStreamArbiterMst2Sst(ScalerDpRxGetMainPort());

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
    ScalerDscDecoderMacArbiterDpMstToSst(ScalerDpMstRxGetInputPort(GET_DP_RX_TARGET_MST_PORT()));
#endif

    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0MacInitial();

#if((_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON) || (_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON))
            // Initial DSC Pass-Through Setting
            ScalerDpMacStreamRx0DscInitial();
#endif

#if(_DP_AUDIO_RX0_SUPPORT == _ON)
            ScalerDpAudioRx0AudioInitial();
#endif // End of #if(_DP_AUDIO_RX0_SUPPORT == _ON)

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1MacInitial();

#if((_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON) || (_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON))
            // Initial DSC Pass-Through Setting
            ScalerDpMacStreamRx1DscInitial();
#endif

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
            ScalerDpAudioRx1AudioInitial();
#endif // End of #if(_DP_AUDIO_RX1_SUPPORT == _ON)

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2MacInitial();

#if((_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON) || (_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON))
            // Initial DSC Pass-Through Setting
            ScalerDpMacStreamRx2DscInitial();
#endif

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
            ScalerDpAudioRx2AudioInitial();
#endif // End of #if(_DP_AUDIO_RX2_SUPPORT == _ON)

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3MacInitial();

#if((_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON) || (_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON))
            // Initial DSC Pass-Through Setting
            ScalerDpMacStreamRx3DscInitial();
#endif

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
            ScalerDpAudioRx3AudioInitial();
#endif // End of #if(_DP_AUDIO_RX3_SUPPORT == _ON)

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4MacInitial();

#if((_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON) || (_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON))
            // Initial DSC Pass-Through Setting
            ScalerDpMacStreamRx4DscInitial();
#endif

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
            ScalerDpAudioRx4AudioInitial();
#endif // End of #if(_DP_AUDIO_RX4_SUPPORT == _ON)

            break;
#endif

        default:

            break;
    }

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    CLR_DP_TX_DOWNSTREAM_DSC_DETECT_PASSTHROUGH();
    CLR_DP_TX_DOWNSTREAM_DSC_DETECT_ENABLE();
    SET_DP_TX_DSC_PASSTHROUGH_TYPE(_SOURCE_PASSTHROUGH_DSC_BY_NONE);
    CLR_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH();
#endif

#if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)
    // Set Audio Status to Preparing
    ScalerDpMacMstToSstAudioChangeState(_MST2SST_AUDIO_STATUS_PREPARING);

    DebugMessageAudio("[Mst2Sst] Initial State Set to _PREPARING", _MST2SST_AUDIO_STATUS_PREPARING);
#endif // End of #if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Dp Mst to Sst Sdp Initial
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMacMstToSstSdpInitial(void)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SdpInitial();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SdpInitial();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SdpInitial();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SdpInitial();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SdpInitial();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Handle DP MST to SST Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstProc(void)
{
    // Stream Judge Handler
    ScalerDpMacMstToSstStreamJudgeHandler();

    // Stream Mode Handler
    ScalerDpMacMstToSstStreamModeHandler();

#if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)

    // Audio Play Process
    ScalerDpMacMstToSstAudioDigitalProc();

#endif // End of #if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Dp Mac Mst2Sst Stream Judge Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstStreamJudgeHandler(void)
{
    if((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_NO_PORT) && (GET_DP_MAC_MST2SST_STREAM_STATUS() != _MST2SST_STREAM_STATUS_NO_SIGNAL))
    {
        ScalerDpMacMstToSstStreamChangeState(_MST2SST_STREAM_STATUS_NO_SIGNAL);

        DebugMessageDpRx("[Mst2Sst Stream] Change State to: _NO_SIGNAL (MST No Port)", _MST2SST_STREAM_STATUS_NO_SIGNAL);
    }

    if((GET_DP_MAC_MST2SST_ENABLE() == _DISABLE) && (GET_DP_MAC_MST2SST_STREAM_STATUS() != _MST2SST_STREAM_STATUS_NO_SIGNAL))
    {
        ScalerDpMacMstToSstStreamChangeState(_MST2SST_STREAM_STATUS_NO_SIGNAL);

        DebugMessageDpRx("[Mst2Sst Stream] Change State: to _NO_SIGNAL", _MST2SST_STREAM_STATUS_NO_SIGNAL);
    }

    switch(GET_DP_MAC_MST2SST_STREAM_STATUS())
    {
        case _MST2SST_STREAM_STATUS_NO_SIGNAL:

            if(GET_DP_MAC_MST2SST_ENABLE() == _ENABLE)
            {
                ScalerDpMacMstToSstStreamChangeState(_MST2SST_STREAM_STATUS_SEARCH);

                DebugMessageDpRx("[Mst2Sst Stream] Change State: _NO_SIGNAL to _SEARCH", _MST2SST_STREAM_STATUS_SEARCH);
            }

            break;

        case _MST2SST_STREAM_STATUS_SEARCH:

            if(GET_DP_MAC_MST2SST_STREAM_JUDGE() == _TRUE)
            {
                ScalerDpMacMstToSstStreamChangeState(_MST2SST_STREAM_STATUS_ACTIVE);

                DebugMessageDpRx("[Mst2Sst Stream] Change State: _SEARCH to _ACTIVE", _MST2SST_STREAM_STATUS_ACTIVE);
            }

            break;

        case _MST2SST_STREAM_STATUS_ACTIVE:

            if(ScalerDpMacMstToSstStableDetect() == _FALSE)
            {
                ScalerDpMacTxForceIdlePatternSetting();

                ScalerDpMacMstToSstStreamChangeState(_MST2SST_STREAM_STATUS_NO_SIGNAL);

                DebugMessageDpRx("[Mst2Sst Stream] Change State: _ACTIVE to _NO_SIGNAL", _MST2SST_STREAM_STATUS_NO_SIGNAL);
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Mac Mst2Sst Stream Mode Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstStreamModeHandler(void)
{
    switch(GET_DP_MAC_MST2SST_STREAM_STATUS())
    {
        case _MST2SST_STREAM_STATUS_NO_SIGNAL:

            if(GET_DP_MAC_MST2SST_STREAM_STATUS_CHANGE() == _TRUE)
            {
                CLR_DP_MAC_MST2SST_STREAM_STATUS_CHANGE();

                CLR_DP_MAC_MST2SST_STREAM_JUDGE();

                ScalerDpMacMstToSstPreDetectReset();

#if((_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
                // Reset MST2SST Dsc DecodE Enable
                ScalerDpMacMstToSstDscReset();
#endif
                ScalerDpMacMstToSstSetFifoWD(_DISABLE);
            }

            break;

        case _MST2SST_STREAM_STATUS_SEARCH:

            if(GET_DP_MAC_MST2SST_STREAM_STATUS_CHANGE() == _TRUE)
            {
                CLR_DP_MAC_MST2SST_STREAM_STATUS_CHANGE();

                ScalerDpMacMstToSstInitial();
            }

            if(ScalerDpMacMstToSstScanInputPort() == _SOURCE_DP)
            {
                ScalerDpMacMstToSstStreamInfoSetting();

                ScalerDpMacMstToSstStreamAfterJudgeSetting();

                if(ScalerDpMacMstToSstMeasureInput() == _TRUE)
                {
                    SET_DP_MAC_MST2SST_STREAM_JUDGE();
                }
            }

            break;

        case _MST2SST_STREAM_STATUS_ACTIVE:

            // First Active Proc
            if(GET_DP_MAC_MST2SST_STREAM_STATUS_CHANGE() == _TRUE)
            {
                CLR_DP_MAC_MST2SST_STREAM_STATUS_CHANGE();

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
                if(ScalerDpMacStreamRxGetDataPath(_STREAM_SOURCE_MST2SST) == _DATA_PATH_DSC_DECODER)
                {
                    ScalerDpMacMstToSstDscDecoderSetFifoWD(_ENABLE);
                }
                else
#endif
                {
                    ScalerDpMacMstToSstSetFifoWD(_ENABLE);
                }

                // Clear Bs Miss Flag And Disable IRQ, Avoid Stable Detect Fail
                ScalerDpMacMstToSstSetBsMissDetectIRQ(_DISABLE);
            }

            if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE) &&
               (GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_LINK_ON) &&
               (ScalerDpStreamGetDataPath(_STREAM_MST2SST) != _DATA_PATH_VIDEO_BYPASS))
            {
                ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_MST2SST);
            }
            else
            {
                if((GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_ON) && (GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE))
                {
                    ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_NONE);
                    DebugMessageDpTx("Mst2sst Mode Not Link On: Reset Stream", GET_DP_TX_STREAM_SOURCE());
                }
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP MstToSst Stream Change State
// Input Value  : EnumDpMacMstToSstStreamStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstStreamChangeState(EnumDpMacMstToSstStreamStatus enumStreamStatus)
{
    SET_DP_MAC_MST2SST_STREAM_STATUS(enumStreamStatus);
    SET_DP_MAC_MST2SST_STREAM_STATUS_CHANGE();
}

//--------------------------------------------------
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : None
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
EnumSourceType ScalerDpMacMstToSstScanInputPort(void)
{
    EnumSourceType enumSourceType = _SOURCE_NONE;

    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            enumSourceType = ScalerDpMacStreamRx0ScanInputPort();
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            enumSourceType = ScalerDpMacStreamRx1ScanInputPort();
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            enumSourceType = ScalerDpMacStreamRx2ScanInputPort();
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            enumSourceType = ScalerDpMacStreamRx3ScanInputPort();
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            enumSourceType = ScalerDpMacStreamRx4ScanInputPort();
            break;
#endif

        default:
            break;
    }

    if((enumSourceType == _SOURCE_NONE) || (ScalerDpMacStreamRxGetDataPath(_STREAM_SOURCE_MST2SST) != _DATA_PATH_DSC_DECODER))
    {
        return enumSourceType;
    }

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
    if(ScalerDpMacMstToSstDscDecoderScanInputPort() == _TRUE)
    {
        return _SOURCE_DP;
    }
#endif

    return _SOURCE_NONE;
}

//--------------------------------------------------
// Description  : On Line Check DP stability
// Input Value  : None
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerDpMacMstToSstStableDetect(void)
{
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST);

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            if(ScalerDpMacStreamRx0StableDetect() == _FALSE)
            {
                return _FALSE;
            }

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            if(ScalerDpMacStreamRx1StableDetect() == _FALSE)
            {
                return _FALSE;
            }

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            if(ScalerDpMacStreamRx2StableDetect() == _FALSE)
            {
                return _FALSE;
            }

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            if(ScalerDpMacStreamRx3StableDetect() == _FALSE)
            {
                return _FALSE;
            }

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            if(ScalerDpMacStreamRx4StableDetect() == _FALSE)
            {
                return _FALSE;
            }

            break;
#endif

        default:

            return _FALSE;

            break;
    }

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    if(ScalerDpStreamGetDataPath(_STREAM_MST2SST) == _DATA_PATH_DSC_REORDER)
    {
        return ScalerDpMacMstToSstReorderStableDetect(enumDpMacSel);
    }
    else
#endif
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : DP MST to SST Measure
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacMstToSstMeasureInput(void)
{
    // Format Conversion Mux Setting
    ScalerDpMstTxToSstFCMuxSetting();

    // DPTx CTS Fifo reset
    ScalerDpMacTxCtsFifoReset();

    return ScalerDpMacMstToSstGetInputMsaTimingInfo();
}

//--------------------------------------------------
// Description  : Get Tx Input Info for DPTX SST D0
// Input Value  : enumDPTxInputInfoRef
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacMstToSstGetInputMsaTimingInfo(void)
{
    StructDpInfo stDpInfo;

    if(ScalerDpStreamGetDataPath(_STREAM_MST2SST) == _DATA_PATH_VESA)
    {
        if(ScalerDpMacTxGetInputMeasureTimingInfo(ScalerDpRxGetInputPortMappingSourceType(_STREAM_SOURCE_MST2SST)) == _FALSE)
        {
            DebugMessageDpTx("7. DP Tx Mst2sst Get Measure Info Fail", 0);

            return _FALSE;
        }
    }
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
    else if(ScalerDpStreamGetDataPath(_STREAM_MST2SST) == _DATA_PATH_DSC_DECODER)
    {
        if(ScalerDpMacTxGetInputMeasureTimingInfo(ScalerDpRxGetInputPortMappingSourceType(_STREAM_SOURCE_MST2SST)) == _FALSE)
        {
            DebugMessageDpTx("7. DP Tx Mst2sst Get Measure Info Fail", 0);

            return _FALSE;
        }
    }
#endif

    if(ScalerDpMacMstToSstGetMsaTimingInfo(&stDpInfo) == _TRUE)
    {
        g_stDpMacTxInputTimingInfo = stDpInfo.stDpTimingInfo;

        return _TRUE;
    }

    DebugMessageDpTx("7. DP Tx Mst2sst Get MSA Info Fail", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Dp MSA Timing Info
// Input Value  : DP Info Structure
// Output Value : True --> Get MSA Info
//--------------------------------------------------
bit ScalerDpMacMstToSstGetMsaTimingInfo(StructDpInfo *pstDpInfo)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetMsaTimingInfo(pstDpInfo);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetMsaTimingInfo(pstDpInfo);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetMsaTimingInfo(pstDpInfo);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetMsaTimingInfo(pstDpInfo);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetMsaTimingInfo(pstDpInfo);
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP MST2SST Set Color Info Macros
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstSetColorInfo(void)
{
    if(ScalerDpMacMstToSstGetVscSdpColorMode() == _TRUE)
    {
        // Set Color Space Macro
        switch(ScalerDpMacStreamRxGetColorSpacePreValue(_STREAM_SOURCE_MST2SST))
        {
            case _VSC_COLOR_SPACE_0:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;

            case _VSC_COLOR_SPACE_1:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
                break;

            case _VSC_COLOR_SPACE_2:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
                break;

            case _VSC_COLOR_SPACE_3:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR420);
                break;

            case _VSC_COLOR_SPACE_4:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
                break;

            case _VSC_COLOR_SPACE_5:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RAW);
                break;

            default:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;
        }

        // Set Colorimetry Ext
        ScalerDpMacMstToSstColorimetryExtSetting();

        SET_DP_TX_INPUT_COLOR_CONTENT_TYPE(ScalerDpMacStreamRxGetContentType(_STREAM_SOURCE_MST2SST));
    }
    else
    {
        // Set Color Space Macro
        switch(ScalerDpMacStreamRxGetColorSpacePreValue(_STREAM_SOURCE_MST2SST))
        {
            case _BIT1:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
                break;

            case _BIT2:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
                break;

            case _BIT7:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
                break;

            case (_BIT7 | _BIT1):
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RAW);
                break;

            default:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;
        }

        // Set Colorimetry
        ScalerDpMacMstToSstColorimetrySetting();
    }

    // Set Color Depth Macro
    SET_DP_TX_INPUT_COLOR_DEPTH(ScalerDpMacStreamRxGetColorDepthPreValue(_STREAM_SOURCE_MST2SST));

    // Set Quantization Range
    ScalerDpMacMstToSstQuantizationSetting();
}

//--------------------------------------------------
// Description  : Get Sdp Packet Data
// Input Value  : Dp Sdp Ram Index & Sdp Buff
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstGetSdpPktData(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0GetSdpPktData(enumDpSdpType, pucSdpData, ucOffset, ucLength);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1GetSdpPktData(enumDpSdpType, pucSdpData, ucOffset, ucLength);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2GetSdpPktData(enumDpSdpType, pucSdpData, ucOffset, ucLength);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3GetSdpPktData(enumDpSdpType, pucSdpData, ucOffset, ucLength);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4GetSdpPktData(enumDpSdpType, pucSdpData, ucOffset, ucLength);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Dp MST2SST Infoframe HB3 Check
// Input Value  : SDP Type
// Output Value : HB3
//--------------------------------------------------
BYTE ScalerDpMacMstToSstSdpInfoHB3(EnumDpSdpType enumDpSdpType)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetSdpInfoHB3(enumDpSdpType);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetSdpInfoHB3(enumDpSdpType);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetSdpInfoHB3(enumDpSdpType);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetSdpInfoHB3(enumDpSdpType);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetSdpInfoHB3(enumDpSdpType);
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP MST2SST Pre Detect Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstPreDetectReset(void)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0StreamPreDetectReset();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1StreamPreDetectReset();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2StreamPreDetectReset();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3StreamPreDetectReset();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4StreamPreDetectReset();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Enable Mst To Sst Fifo Under/OverFlow Watch Dog
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstSetFifoWD(bit bEn)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SetFifoWD(bEn);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SetFifoWD(bEn);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SetFifoWD(bEn);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SetFifoWD(bEn);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SetFifoWD(bEn);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Dp Mst To Sst Colorimetry Ext PreValue
// Input Value  : None
// Output Value : Mst To Sst Colorimetry Ext PreValue
//--------------------------------------------------
BYTE ScalerDpMacMstToSstGetColorimetryExtPreValue(void)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_COLORIMETRY_EXT_PREVALUE();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_PREVALUE();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_COLORIMETRY_EXT_PREVALUE();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_COLORIMETRY_EXT_PREVALUE();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_COLORIMETRY_EXT_PREVALUE();

            break;
#endif

        default:

            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get Dp Mst To Sst Colorimetry Ext PreValue
// Input Value  : None
// Output Value : Mst To Sst Colorimetry Ext PreValue
//--------------------------------------------------
BYTE ScalerDpMacMstToSstGetColorimetryPreValue(void)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_COLORIMETRY_PREVALUE();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_COLORIMETRY_PREVALUE();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_COLORIMETRY_PREVALUE();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_COLORIMETRY_PREVALUE();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_COLORIMETRY_PREVALUE();

            break;
#endif

        default:

            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get Dp Mst To Sst Quantization Ext PreValue
// Input Value  : None
// Output Value : Mst To Sst Quantization Ext PreValue
//--------------------------------------------------
BYTE ScalerDpMacMstToSstGetQuantizationPreValue(void)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_QUANTIZATION_PREVALUE();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_QUANTIZATION_PREVALUE();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_QUANTIZATION_PREVALUE();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_QUANTIZATION_PREVALUE();

            break;
#endif

        default:

            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get Dp Mst To Sst Vsc Sdp Color Mode
// Input Value  : None
// Output Value : Mst To Sst Vsc Sdp Color Mode
//--------------------------------------------------
bit ScalerDpMacMstToSstGetVscSdpColorMode(void)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_VSC_SDP_COLOR_MODE();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_VSC_SDP_COLOR_MODE();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_VSC_SDP_COLOR_MODE();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_VSC_SDP_COLOR_MODE();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_VSC_SDP_COLOR_MODE();

            break;
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Mst2Sst Input Pixel Mode
// Input Value  : None
// Output Value : One Pixel or Two Pixel Mode
//--------------------------------------------------
EnumDpRxMacPixelMode ScalerDpMacMstToSstGetInputPixelMode(void)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)

        case _DP_MAC_0:

            return ScalerDpMacStreamRx0InputPixelMode();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1InputPixelMode();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2InputPixelMode();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3InputPixelMode();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4InputPixelMode();
#endif

        default:

            break;
    }

    return _DP_RX_MAC_PIXEL_MODE_NONE;
}

//--------------------------------------------------
// Description  : DP Mst To Sst Stream Info Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstStreamInfoSetting(void)
{
    WORD usDpTxInputPixelClk = ScalerDpMacStreamRxGetPredectStreamClock(_STREAM_SOURCE_MST2SST) / 100000;
    StructDpInfo *pstDpInfo = ScalerDpMacStreamRxGetDpInfoPointer(_STREAM_SOURCE_MST2SST);

    ScalerDpMacMstToSstSetColorInfo();

    if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        usDpTxInputPixelClk *= 2;
    }

    // Recoed Input Pixel Clock (Unit is 0.1MHz)
    SET_DP_TX_INPUT_PIXEL_CLK(usDpTxInputPixelClk);

    SET_DP_TX_INPUT_INTERLACE_MODE(pstDpInfo->stDpLinkInfo.b1InterlaceStatus);

    if(pstDpInfo->stDpLinkInfo.b1InterlaceOddMode == _TRUE)
    {
        SET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER(_ODD);
    }
    else
    {
        SET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER(_EVEN);
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(ScalerDpMacStreamRxGetFreeSyncEnable(_STREAM_SOURCE_MST2SST) == _TRUE)
    {
        SET_FREESYNC_DP_TX_ENABLED();
    }
    else
    {
        CLR_FREESYNC_DP_TX_ENABLED();
    }
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    if(ScalerDpStreamGetDataPath(_STREAM_MST2SST) == _DATA_PATH_DSC_REORDER)
    {
        ScalerDpMacMstToSstDscGetPpsInfo();
    }
#endif
}

//--------------------------------------------------
// Description  : Dp Mst To Sst Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstColorimetrySetting(void)
{
    BYTE ucColorimetryValue = (ScalerDpMacMstToSstGetColorimetryPreValue() << 1);

    if((GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(ucColorimetryValue & (_BIT4 | _BIT3))
        {
            case 0:
                SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_YCC_XVYCC601);
                DebugMessageDpTx("_COLORIMETRY_YCC_XVYCC601", 0);
                break;

            case _BIT3:
                SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT601);
                DebugMessageDpTx("_COLORIMETRY_YCC_ITUR_BT601", 0);
                break;

            case _BIT4:
                SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_YCC_XVYCC709);
                DebugMessageDpTx("_COLORIMETRY_YCC_XVYCC709", 0);
                break;

            case (_BIT4 | _BIT3):
                SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT709);
                DebugMessageDpTx("_COLORIMETRY_YCC_ITUR_BT709", 0);
                break;

            default:
                break;
        }
    }
    else if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(ucColorimetryValue & (_BIT4 | _BIT3 | _BIT2 | _BIT1))
        {
            case 0:
                SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageDpTx("_COLORIMETRY_RGB_SRGB_VESA", 0);
                break;

            case _BIT3:
                SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageDpTx("_COLORIMETRY_RGB_SRGB_CEA", 0);
                break;

            case (_BIT2 | _BIT1):
                SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_RGB_XRRGB);
                DebugMessageDpTx("_COLORIMETRY_RGB_XRRGB", 0);
                break;

            case (_BIT4 | _BIT2 | _BIT1):
                SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_RGB_SCRGB);
                DebugMessageDpTx("_COLORIMETRY_RGB_SCRGB", 0);
                break;

            case (_BIT4 | _BIT3):
                SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_RGB_ADOBERGB);
                DebugMessageDpTx("_COLORIMETRY_RGB_ADOBERGB", 0);
                break;

            case (_BIT3 | _BIT2 | _BIT1):
                SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_RGB_DCI_P3);
                DebugMessageDpTx("_COLORIMETRY_RGB_DCI_P3", 0);
                break;

            case (_BIT4 | _BIT3 | _BIT2 | _BIT1):
                SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_RGB_COLOR_PROFILE);
                DebugMessageDpTx("_COLORIMETRY_RGB_COLOR_PROFILE", 0);
                break;

            default:
                SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageDpTx("_COLORIMETRY_RGB_SRGB", 0);
                break;
        }
    }
    else if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY)
    {
        SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_Y_ONLY);
        DebugMessageDpTx("_COLORIMETRY_Y_ONLY", 0);
    }
    else if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_RAW)
    {
        SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_RAW);
        DebugMessageDpTx("_COLORIMETRY_RAW", 0);
    }
}

//--------------------------------------------------
// Description  : Dp Mst To Sst Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstColorimetryExtSetting(void)
{
    BYTE ucColorimetryExtPreValue = ScalerDpMacMstToSstGetColorimetryExtPreValue();

    SET_DP_TX_INPUT_COLORIMETRY(_COLORIMETRY_EXT);

    if((GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(ucColorimetryExtPreValue)
        {
            case _VSC_COLORIMETRY_0:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT601);
                DebugMessageDpTx("_COLORIMETRY_EXT_YCC_ITUR_BT601", 0);
                break;

            case _VSC_COLORIMETRY_1:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT709);
                DebugMessageDpTx("_COLORIMETRY_EXT_YCC_ITUR_BT709", 0);
                break;

            case _VSC_COLORIMETRY_2:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC601);
                DebugMessageDpTx("_COLORIMETRY_EXT_YCC_XVYCC601", 0);
                break;

            case _VSC_COLORIMETRY_3:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC709);
                DebugMessageDpTx("_COLORIMETRY_EXT_YCC_XVYCC709", 0);
                break;

            case _VSC_COLORIMETRY_4:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_SYCC601);
                DebugMessageDpTx("_COLORIMETRY_EXT_YCC_SYCC601", 0);
                break;

            case _VSC_COLORIMETRY_5:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ADOBEYCC601);
                DebugMessageDpTx("_COLORIMETRY_EXT_YCC_ADOBEYCC601", 0);
                break;

            case _VSC_COLORIMETRY_6:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);
                DebugMessageDpTx("_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL", 0);
                break;

            case _VSC_COLORIMETRY_7:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);
                DebugMessageDpTx("_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL", 0);
                break;

            default:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);
                DebugMessageDpTx("_COLORIMETRY_EXT_RESERVED", 0);
                break;
        }
    }
    else if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(ucColorimetryExtPreValue)
        {
            case _VSC_COLORIMETRY_0:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_SRGB);
                DebugMessageDpTx("_COLORIMETRY_EXT_RGB_SRGB", 0);
                break;

            case _VSC_COLORIMETRY_1:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_XRRGB);
                DebugMessageDpTx("_COLORIMETRY_EXT_RGB_XRRGB", 0);
                break;

            case _VSC_COLORIMETRY_2:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_SCRGB);
                DebugMessageDpTx("_COLORIMETRY_EXT_RGB_SCRGB", 0);
                break;

            case _VSC_COLORIMETRY_3:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ADOBERGB);
                DebugMessageDpTx("_COLORIMETRY_EXT_RGB_ADOBERGB", 0);
                break;

            case _VSC_COLORIMETRY_4:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_DCI_P3);
                DebugMessageDpTx("_COLORIMETRY_EXT_RGB_DCI_P3", 0);
                break;

            case _VSC_COLORIMETRY_5:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE);
                DebugMessageDpTx("_COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE", 0);
                break;

            case _VSC_COLORIMETRY_6:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ITUR_BT2020);
                DebugMessageDpTx("_COLORIMETRY_EXT_RGB_ITUR_BT2020", 0);
                break;

            default:
                SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);
                DebugMessageDpTx("_COLORIMETRY_EXT_RESERVED", 0);
                break;
        }
    }
    else if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY)
    {
        SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_Y_ONLY_DICOM_PART14);
        DebugMessageDpTx("_COLORIMETRY_EXT_Y_ONLY_DICOM_PART14", 0);
    }
    else if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_RAW)
    {
        SET_DP_TX_INPUT_EXT_COLORIMETRY(_COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE);
        DebugMessageDpTx("_COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE", 0);
    }
}

//--------------------------------------------------
// Description  : DP Mst To Sst Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstQuantizationSetting(void)
{
    switch(GET_DP_TX_INPUT_COLOR_SPACE())
    {
        case _COLOR_SPACE_YCBCR420:
        case _COLOR_SPACE_YCBCR422:
        case _COLOR_SPACE_YCBCR444:

            // Special case for xvYCC
            if((GET_DP_TX_INPUT_COLORIMETRY() == _COLORIMETRY_YCC_XVYCC601) || (GET_DP_TX_INPUT_COLORIMETRY() == _COLORIMETRY_YCC_XVYCC709))
            {
                SET_DP_TX_INPUT_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);
                DebugMessageDpTx("_YCC_QUANTIZATION_LIMIT_RANGE", 0);
            }
            else
            {
                if(ScalerDpMacMstToSstGetQuantizationPreValue() == _DP_COLOR_QUANTIZATION_FULL)
                {
                    SET_DP_TX_INPUT_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);
                    DebugMessageDpTx("_YCC_QUANTIZATION_FULL_RANGE", 0);
                }
                else
                {
                    SET_DP_TX_INPUT_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);
                    DebugMessageDpTx("_YCC_QUANTIZATION_LIMIT_RANGE", 0);
                }
            }

            SET_DP_TX_INPUT_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

            break;

        default:
        case _COLOR_SPACE_RGB:

            // Special case for AdobeRGB
            if(GET_DP_TX_INPUT_COLORIMETRY() == _COLORIMETRY_RGB_ADOBERGB)
            {
                SET_DP_TX_INPUT_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);
                DebugMessageDpTx("_RGB_QUANTIZATION_FULL_RANGE", 0);
            }
            else
            {
                if(ScalerDpMacMstToSstGetQuantizationPreValue() == _DP_COLOR_QUANTIZATION_FULL)
                {
                    SET_DP_TX_INPUT_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);
                    DebugMessageDpTx("_RGB_QUANTIZATION_FULL_RANGE", 0);
                }
                else
                {
                    SET_DP_TX_INPUT_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_LIMIT_RANGE);
                    DebugMessageDpTx("_RGB_QUANTIZATION_LIMIT_RANGE", 0);
                }
            }

            SET_DP_TX_INPUT_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);

            break;
    }
}

//--------------------------------------------------
// Description  : Enable DP BS Miss Detect IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstSetBsMissDetectIRQ(bit bEn)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SetBsMissDetectIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SetBsMissDetectIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SetBsMissDetectIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SetBsMissDetectIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SetBsMissDetectIRQ(bEn);

            break;
#endif

        default:

            break;
    }
}

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Bs Miss Detect Period Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstSetBsMissDetectPeriod(void)
{
    StructDpInfo *pstDpInfo = ScalerDpMacStreamRxGetDpInfoPointer(_STREAM_SOURCE_MST2SST);

    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SetBsMissDetectPeriod(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SetBsMissDetectPeriod(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SetBsMissDetectPeriod(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SetBsMissDetectPeriod(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SetBsMissDetectPeriod(pstDpInfo);

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : DP MST2SST Stream After Judge Setting
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstStreamAfterJudgeSetting(void)
{
#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
    ScalerDpMacMstToSstSetBsMissDetectPeriod();
#endif
}

#if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Mst To Sst Audio Judge Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstAudioJudgeHandler(void)
{
    if(GET_DP_MAC_MST2SST_ENABLE() == _ENABLE)
    {
        // Digital Audio Detect
        ScalerDpMacMstToSstDigitalAudioDetectProc();
    }
    else
    {
        if(GET_DP_MAC_MST2SST_AUDIO_STATUS() != _MST2SST_AUDIO_STATUS_PREPARING)
        {
            ScalerDpMacMstToSstAudioChangeState(_MST2SST_AUDIO_STATUS_PREPARING);
        }
    }

    // Audio State Judgment
    switch(GET_DP_MAC_MST2SST_AUDIO_STATUS())
    {
        case _MST2SST_AUDIO_STATUS_PREPARING:

            // 1. (Prepare)Audio Detect Proc(FS) = 1 => Setting Mode (tracking)
            if(GET_DP_MAC_MST2SST_ENABLE() == _ENABLE)
            {
                // Check Audio Packet
                if(ScalerDpMacMstToSstSamplingFreqDetect() == _TRUE)
                {
                    // =====================
                    // State Change
                    // =====================

                    // Change Audio State to Setting
                    ScalerDpMacMstToSstAudioChangeState(_MST2SST_AUDIO_STATUS_SETTING);

                    DebugMessageAudio("[Mst2Sst] Change State: _PREPARING to _SETTING", _MST2SST_AUDIO_STATUS_SETTING);
                }
            }

            break;

        case _MST2SST_AUDIO_STATUS_SETTING:

            // Check DP_TX Stream Source
            if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE)
            {
                // =====================
                // State Change
                // =====================

                // Change Audio State to Preparing
                ScalerDpMacMstToSstAudioChangeState(_MST2SST_AUDIO_STATUS_PREPARING);

                DebugMessageAudio("[Mst2Sst] Change State: _SETTING to _PREPARING", _MST2SST_AUDIO_STATUS_PREPARING);
            }
            else
            {
                // 2. (Setting)audio stable detect => Playback Mode

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
                {
                    // Check if DP Rx Audio Stable
                    if(ScalerDpMacMstToSstGetAudioDetected() == _TRUE)
                    {
                        // =====================
                        // State Change
                        // =====================

                        // Change Audio State to Playback
                        ScalerDpMacMstToSstAudioChangeState(_MST2SST_AUDIO_STATUS_PLAYBACK);

                        DebugMessageAudio("[Mst2Sst] Change State: _SETTING to _PLAYBACK(128B132B to 128B132B)", _MST2SST_AUDIO_STATUS_PLAYBACK);
                    }
                }
                else
#endif // End of #if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                {
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    // =========================
                    // Check Upstream Coding Type
                    // =========================

                    if(ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT()) == _CODING_TYPE_128B132B)
                    {
                        // Check if DP Rx Audio Stable
                        if(ScalerDpMacMstToSstGetAudioDetected() == _TRUE)
                        {
                            // =====================
                            // State Change
                            // =====================

                            // Change Audio State to Playback
                            ScalerDpMacMstToSstAudioChangeState(_MST2SST_AUDIO_STATUS_PLAYBACK);

                            DebugMessageAudio("[Mst2Sst] Change State: _SETTING to _PLAYBACK(128B132B to 8B10B)", _MST2SST_AUDIO_STATUS_PLAYBACK);
                        }
                    }
                    else
#endif // End of #if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    {
                        // =====================
                        // State Change
                        // =====================

                        // Change Audio State to Playback
                        ScalerDpMacMstToSstAudioChangeState(_MST2SST_AUDIO_STATUS_PLAYBACK);

                        DebugMessageAudio("[Mst2Sst] Change State: _SETTING to _PLAYBACK(8B10B to 8B10B)", _MST2SST_AUDIO_STATUS_PLAYBACK);
                    }
                }
            }

            break;

        case _MST2SST_AUDIO_STATUS_PLAYBACK:

            // Check DP_TX Stream Source
            if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE)
            {
                DebugMessageAudio("[Mst2Sst] No Stream Source !", 0);

                // =====================
                // State Change
                // =====================

                // Change Audio State to Preparing
                ScalerDpMacMstToSstAudioChangeState(_MST2SST_AUDIO_STATUS_PREPARING);

                DebugMessageAudio("[Mst2Sst] Change State: _PLAYBACK to _PREPARING", _MST2SST_AUDIO_STATUS_PREPARING);
            }
            else
            {
                // 3. (Playback)audio stable detect => reset proc on playback mode

                // Check if DP Rx Audio Not Stable
                if(ScalerDpMacMstToSstGetAudioDetected() == _FALSE)
                {
                    DebugMessageAudio("[Mst2Sst] No Audio Packet !", 0);

                    // =====================
                    // Reset Process
                    // =====================
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
                    {
                        // Mute Audio Output
                        ScalerDpMacMstToSstSetAudioOutputMute(_ON);

                        // Disable Audio Watchdog
                        ScalerDpMacMstToSstWatchDogProc(_OFF);

                        DebugMessageAudio("[Mst2Sst] Disable DPRX_Audio_MAC(128B132B to 128B132B)", 0);
                    }
                    else
#endif // End of #if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    {
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
                        // =========================
                        // Check Upstream Coding Type
                        // =========================

                        if(ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT()) == _CODING_TYPE_128B132B)
                        {
                            // Mute Audio Output
                            ScalerDpMacMstToSstSetAudioOutputMute(_ON);

                            // Disable Audio Watchdog
                            ScalerDpMacMstToSstWatchDogProc(_OFF);

                            DebugMessageAudio("[Mst2Sst] Disable DPRX_Audio_MAC(128B132B to 8B10B)", 0);
                        }
                        else
#endif // End of #if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
                        {
                            // Disable Audio RS Decoder for MST2SST
                            ScalerDpMacMstToSstRsDecoderControl(_DISABLE);

                            DebugMessageAudio("[Mst2Sst] Disable RS_Decoder(8B10B to 8B10B)", 0);
                        }
                    }

                    // =====================
                    // State Change
                    // =====================

                    // Change Audio State to Preparing
                    ScalerDpMacMstToSstAudioChangeState(_MST2SST_AUDIO_STATUS_PREPARING);

                    DebugMessageAudio("[Mst2Sst] Change State: _PLAYBACK to _PREPARING", _MST2SST_AUDIO_STATUS_PREPARING);
                }
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Mst To Sst Audio Mode Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstAudioModeHandler(void)
{
    switch(GET_DP_MAC_MST2SST_AUDIO_STATUS())
    {
        case _MST2SST_AUDIO_STATUS_PREPARING:

            // 1. Prepare => audio initial/mute proc (change flag)

            // Check If First Mode Change or Not
            if(GET_DP_MAC_MST2SST_AUDIO_STATUS_CHANGE() == _TRUE)
            {
                // Clear Flag
                CLR_DP_MAC_MST2SST_AUDIO_STATUS_CHANGE();

                // =====================
                // Disable Audio Output
                // =====================

                // Mute Audio Output
                ScalerDpMacMstToSstSetAudioOutputMute(_ON);

                // Disable Audio Watchdog
                ScalerDpMacMstToSstWatchDogProc(_OFF);
                ScalerTimerDelayXms(3);
            }

            break;

        case _MST2SST_AUDIO_STATUS_SETTING:

            // 2. Setting => tracking parametter / rs decode en

            // Check If First Mode Change or Not
            if(GET_DP_MAC_MST2SST_AUDIO_STATUS_CHANGE() == _TRUE)
            {
                // Clear Flag
                CLR_DP_MAC_MST2SST_AUDIO_STATUS_CHANGE();

                // =====================
                // Audio Pre-Setting
                // =====================

                // Check Coding Type
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
                {
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    if(ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT()) == _CODING_TYPE_128B132B)
                    {
                        // Use I2S when Coding Type of DPTX source is 1288B132B
                        // Case:
                        // 1. N/A: DP 2.0 to DP 2.0

                        // Set DPTX Audio Input Path to I2S
                        SET_DP_TX_AUDIO_INPUT_PATH(_DP_TX_AUDIO_PATH_I2S);

                        // Switch DPTX Mux to MST2SST
                        ScalerDpMacMstToSstAudioMuxControl();

                        DebugMessageAudio("[Mst2Sst] Set Path to I2S(128B132B to 128B132B)", _DP_TX_AUDIO_PATH_I2S);
                    }
#endif // End of #if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
                }
                else
#endif // End of #if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                {
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    // =========================
                    // Check Upstream Coding Type
                    // =========================

                    if(ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT()) == _CODING_TYPE_128B132B)
                    {
                        // Use I2S when Coding Type of DPTX source is 1288B132B
                        // Case:
                        // 1. Clone_Mode: DP 2.0 to DP 1.4
                        // 2. MST2SST_Mode: DP 2.0 to DP 1.4

                        // Set DPTX Audio Input Path to I2S
                        SET_DP_TX_AUDIO_INPUT_PATH(_DP_TX_AUDIO_PATH_I2S);

                        // Switch DPTX Mux to MST2SST
                        ScalerDpMacMstToSstAudioMuxControl();

                        DebugMessageAudio("[Mst2Sst] Set Path to I2S(128B132B to 8B10B)", _DP_TX_AUDIO_PATH_I2S);
                    }
                    else
#endif // End of #if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    {
                        // Use RS Decoder when Coding Type of DPTX source is 8B10B
                        // Case:
                        // 1. MST2SST_Mode: DP 1.4 to DP 1.4

                        // Set DPTX Audio Input Path to RS Decoder
                        SET_DP_TX_AUDIO_INPUT_PATH(_DP_TX_AUDIO_PATH_RS_DECODER);

                        DebugMessageAudio("[Mst2Sst] Set Path to RS_Decoder(8B10B to 8B10B)", _DP_TX_AUDIO_PATH_RS_DECODER);
                    }
                }
            }

            break;

        case _MST2SST_AUDIO_STATUS_PLAYBACK:

            // 3. playback => first playback setting (change flag)

            // Check If First Mode Change or Not
            if(GET_DP_MAC_MST2SST_AUDIO_STATUS_CHANGE() == _TRUE)
            {
                // Clear Flag
                CLR_DP_MAC_MST2SST_AUDIO_STATUS_CHANGE();

                // =====================
                // Enable Audio Output
                // =====================

                // Check Coding Type
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
                {
                    // Enable Watchdog
                    ScalerDpMacMstToSstWatchDogProc(_ON);

                    // Enable Digital Output
                    ScalerDpMacMstToSstSetAudioOutputMute(_OFF);

                    DebugMessageAudio("[Mst2Sst] Enable DPRX_Audio_MAC(128B132B to 128B132B)", 0);
                }
                else
#endif // End of #if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                {
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    // =========================
                    // Check Upstream Coding Type
                    // =========================

                    if(ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT()) == _CODING_TYPE_128B132B)
                    {
                        // Enable Watchdog
                        ScalerDpMacMstToSstWatchDogProc(_ON);

                        // Enable Digital Output
                        ScalerDpMacMstToSstSetAudioOutputMute(_OFF);

                        DebugMessageAudio("[Mst2Sst] Enable DPRX_Audio_MAC(128B132B to 8B10B)", 0);
                    }
                    else
#endif // End of #if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    {
                        // Enable TX Audio RS Decoder
                        ScalerDpMacMstToSstRsDecoderControl(_ENABLE);

                        DebugMessageAudio("[Mst2Sst] Enable RS_Decoder(8B10B to 8B10B)", 0);
                    }
                }
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Mst To Sst Audio Play Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstAudioDigitalProc(void)
{
    // Audio Judge Handler
    ScalerDpMacMstToSstAudioJudgeHandler();

    // Audio Mode Handler
    ScalerDpMacMstToSstAudioModeHandler();
}

//--------------------------------------------------
// Description  : DP MstToSst Audio Change State
// Input Value  : EnumDpMacMstToSstAudioStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstAudioChangeState(EnumDpMacMstToSstAudioStatus enumAudioStatus)
{
    SET_DP_MAC_MST2SST_AUDIO_STATUS(enumAudioStatus);
    SET_DP_MAC_MST2SST_AUDIO_STATUS_CHANGE();
}

//--------------------------------------------------
// Description  : DP Mst To Sst Detect Digital Audio
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstDigitalAudioDetectProc(void)
{
    // Select Mst2Sst MAC
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_AUDIO_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            // Digital Audio Detect
            ScalerDpAudioRx0DigitalDetectProc();

            break;
#endif // End of #if(_DP_AUDIO_RX0_SUPPORT == _ON)

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            // Digital Audio Detect
            ScalerDpAudioRx1DigitalDetectProc();

            break;
#endif // End of #if(_DP_AUDIO_RX1_SUPPORT == _ON)

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            // Digital Audio Detect
            ScalerDpAudioRx2DigitalDetectProc();

            break;
#endif // End of #if(_DP_AUDIO_RX2_SUPPORT == _ON)

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            // Digital Audio Detect
            ScalerDpAudioRx3DigitalDetectProc();

            break;
#endif // End of #if(_DP_AUDIO_RX3_SUPPORT == _ON)

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            // Digital Audio Detect
            ScalerDpAudioRx4DigitalDetectProc();

            break;
#endif // End of #if(_DP_AUDIO_RX4_SUPPORT == _ON)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Mst To Sst Detect Audio Frequency
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpMacMstToSstSamplingFreqDetect(void)
{
    // Select Mst2Sst MAC
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_AUDIO_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            // Digital Audio Detect
            return ((ScalerDpAudioRx0SamplingFreqDetect() != 0x00) && (ScalerDpMacStreamRx0GetVbidInfo(_DP_VBID_AUDIO_STREAM) == _TRUE));

            break;
#endif // End of #if(_DP_AUDIO_RX0_SUPPORT == _ON)

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            // Digital Audio Detect
            return ((ScalerDpAudioRx1SamplingFreqDetect() != 0x00) && (ScalerDpMacStreamRx1GetVbidInfo(_DP_VBID_AUDIO_STREAM) == _TRUE));

            break;
#endif // End of #if(_DP_AUDIO_RX1_SUPPORT == _ON)

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            // Digital Audio Detect
            return ((ScalerDpAudioRx2SamplingFreqDetect() != 0x00) && (ScalerDpMacStreamRx2GetVbidInfo(_DP_VBID_AUDIO_STREAM) == _TRUE));

            break;
#endif // End of #if(_DP_AUDIO_RX2_SUPPORT == _ON)

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            // Digital Audio Detect
            return ((ScalerDpAudioRx3SamplingFreqDetect() != 0x00) && (ScalerDpMacStreamRx3GetVbidInfo(_DP_VBID_AUDIO_STREAM) == _TRUE));

            break;
#endif // End of #if(_DP_AUDIO_RX3_SUPPORT == _ON)

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            // Digital Audio Detect
            return ((ScalerDpAudioRx4SamplingFreqDetect() != 0x00) && (ScalerDpMacStreamRx4GetVbidInfo(_DP_VBID_AUDIO_STREAM) == _TRUE));

            break;
#endif // End of #if(_DP_AUDIO_RX4_SUPPORT == _ON)

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Mst To Sst Get Audio Detect Result
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpMacMstToSstGetAudioDetected(void)
{
    // Select Mst2Sst MAC
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_AUDIO_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            // Digital Audio Detect
            return ScalerDpAudioRx0GetAudioDetected();

            break;
#endif // End of #if(_DP_AUDIO_RX0_SUPPORT == _ON)

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            // Digital Audio Detect
            return ScalerDpAudioRx1GetAudioDetected();

            break;
#endif // End of #if(_DP_AUDIO_RX1_SUPPORT == _ON)

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            // Digital Audio Detect
            return ScalerDpAudioRx2GetAudioDetected();

            break;
#endif // End of #if(_DP_AUDIO_RX2_SUPPORT == _ON)

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            // Digital Audio Detect
            return ScalerDpAudioRx3GetAudioDetected();

            break;
#endif // End of #if(_DP_AUDIO_RX3_SUPPORT == _ON)

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            // Digital Audio Detect
            return ScalerDpAudioRx4GetAudioDetected();

            break;
#endif // End of #if(_DP_AUDIO_RX4_SUPPORT == _ON)

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Mst To Sst Detect Digital Audio
// Input Value  : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstSetAudioOutputMute(bit bMute)
{
    // Select Mst2Sst MAC
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_AUDIO_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            // Audio Mute Control
            ScalerDpAudioRx0SetAudioOutputMute(bMute);

            break;
#endif // End of #if(_DP_AUDIO_RX0_SUPPORT == _ON)

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            // Audio Mute Control
            ScalerDpAudioRx1SetAudioOutputMute(bMute);

            break;
#endif // End of #if(_DP_AUDIO_RX1_SUPPORT == _ON)

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            // Audio Mute Control
            ScalerDpAudioRx2SetAudioOutputMute(bMute);

            break;
#endif // End of #if(_DP_AUDIO_RX2_SUPPORT == _ON)

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            // Audio Mute Control
            ScalerDpAudioRx3SetAudioOutputMute(bMute);

            break;
#endif // End of #if(_DP_AUDIO_RX3_SUPPORT == _ON)

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            // Audio Mute Control
            ScalerDpAudioRx4SetAudioOutputMute(bMute);

            break;
#endif // End of #if(_DP_AUDIO_RX4_SUPPORT == _ON)

        default:

            bMute = bMute;

            break;
    }
}

//--------------------------------------------------
// Description  : DP Mst To Sst Audio Watch Dog Proc
// Input Value  : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstWatchDogProc(bit bOn)
{
    // Select Mst2Sst MAC
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_AUDIO_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            // Watch Dog Control
            ScalerDpAudioRx0WatchDogProc(bOn);

            break;
#endif // End of #if(_DP_AUDIO_RX0_SUPPORT == _ON)

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            // Watch Dog Control
            ScalerDpAudioRx1WatchDogProc(bOn);

            break;
#endif // End of #if(_DP_AUDIO_RX1_SUPPORT == _ON)

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            // Watch Dog Control
            ScalerDpAudioRx2WatchDogProc(bOn);

            break;
#endif // End of #if(_DP_AUDIO_RX2_SUPPORT == _ON)

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            // Watch Dog Control
            ScalerDpAudioRx3WatchDogProc(bOn);

            break;
#endif // End of #if(_DP_AUDIO_RX3_SUPPORT == _ON)

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            // Watch Dog Control
            ScalerDpAudioRx4WatchDogProc(bOn);

            break;
#endif // End of #if(_DP_AUDIO_RX4_SUPPORT == _ON)

        default:

            bOn = bOn;

            break;
    }
}

//--------------------------------------------------
// Description  : DP Mst To Sst Audio RS Decoder Control
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstRsDecoderControl(bit bEnable)
{
    // Select Mst2Sst MAC
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_AUDIO_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            // RS Decoder Control
            ScalerDpAudioRx0RsDecoderControl(bEnable);

            break;
#endif // End of #if(_DP_AUDIO_RX0_SUPPORT == _ON)

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            // RS Decoder Control
            ScalerDpAudioRx1RsDecoderControl(bEnable);

            break;
#endif // End of #if(_DP_AUDIO_RX1_SUPPORT == _ON)

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            // RS Decoder Control
            ScalerDpAudioRx2RsDecoderControl(bEnable);

            break;
#endif // End of #if(_DP_AUDIO_RX2_SUPPORT == _ON)

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            // RS Decoder Control
            ScalerDpAudioRx3RsDecoderControl(bEnable);

            break;
#endif // End of #if(_DP_AUDIO_RX3_SUPPORT == _ON)

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            // RS Decoder Control
            ScalerDpAudioRx4RsDecoderControl(bEnable);

            break;
#endif // End of #if(_DP_AUDIO_RX4_SUPPORT == _ON)

        default:

            bEnable = bEnable;

            break;
    }
}

//--------------------------------------------------
// Description  : DP Mst To Sst Audio Mux Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstAudioMuxControl(void)
{
    // Select Mst2Sst MAC
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_AUDIO_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            // DPTX I2S Mux Switch to Rx0
            ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX0_PORT);

            break;
#endif // End of #if(_DP_AUDIO_RX0_SUPPORT == _ON)

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            // DPTX I2S Mux Switch to Rx1
            ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX1_PORT);

            break;
#endif // End of #if(_DP_AUDIO_RX1_SUPPORT == _ON)

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            // DPTX I2S Mux Switch to Rx2
            ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX2_PORT);

            break;
#endif // End of #if(_DP_AUDIO_RX2_SUPPORT == _ON)

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            // DPTX I2S Mux Switch to Rx3
            ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_PXP_PORT);

            break;
#endif // End of #if(_DP_AUDIO_RX3_SUPPORT == _ON)

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            // DPTX I2S Mux Switch to Rx4
            ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_MST2SST_PORT);

            break;
#endif // End of #if(_DP_AUDIO_RX4_SUPPORT == _ON)

        default:
            break;
    }
}
#endif // End of #if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Mac Tx DSC Reorder Detect
// Input Value  : enumDpMacSel
// Output Value : True, False
//--------------------------------------------------
bit ScalerDpMacMstToSstDscReorderDetect(void)
{
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST);

    CLR_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH();

    if(GET_DP_TX_DOWNSTREAM_DSC_SUPPORT() == _ENABLE)
    {
        if(GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH() == _DISABLE)
        {
            // Check DSC Stream
            if(ScalerDpMacDscRxDscStreamCheck(enumDpMacSel) == _TRUE)
            {
                if((GET_DP_TX_DOWNSTREAM_DSC_DETECT_PASSTHROUGH() == _ENABLE) &&
                   (GET_DP_TX_DOWNSTREAM_DSC_DETECT_ENABLE() == _DISABLE))
                {
                    // Source Set The DSC Virtual DPCD 00160h[1]
                    SET_DP_TX_DSC_PASSTHROUGH_TYPE(_SOURCE_PASSTHROUGH_DSC_BY_ENABLE_BRANCH);

                    DebugMessageMst("_SOURCE_PASSTHROUGH_DSC_BY_ENABLE_BRANCH", 0x00);
                }
                else if((GET_DP_TX_DOWNSTREAM_DSC_DETECT_PASSTHROUGH() == _DISABLE) &&
                        (GET_DP_TX_DOWNSTREAM_DSC_DETECT_ENABLE() == _ENABLE))
                {
                    // Source Set The DFP Sink DSC Phy-DPCD 00160h[0]
                    SET_DP_TX_DSC_PASSTHROUGH_TYPE(_SOURCE_PASSTHROUGH_DSC_BY_ENABLE_DFP_SINK);

                    DebugMessageMst("_SOURCE_PASSTHROUGH_DSC_BY_ENABLE_DFP_SINK", 0x00);
                }
                else if((GET_DP_TX_DOWNSTREAM_DSC_DETECT_PASSTHROUGH() == _ENABLE) &&
                        (GET_DP_TX_DOWNSTREAM_DSC_DETECT_ENABLE() == _ENABLE))
                {
                    // Source Set The DSC Virtual DPCD 00160h[1] and Set The DFP Sink DSC Phy-DPCD 00160h[0]
                    SET_DP_TX_DSC_PASSTHROUGH_TYPE(_SOURCE_PASSTHROUGH_DSC_BY_ENABLE_BRANCH_AND_DFP_SINK);

                    DebugMessageMst("_SOURCE_PASSTHROUGH_DSC_BY_ENABLE_BRANCH_AND_DFP_SINK", 0x00);
                }

                ScalerDpMacStreamRxSdpPacketCheck(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST), _DP_SDP_TYPE_PPS);

                if(ScalerDpStreamGetRxVideoElement(_STREAM_MST2SST, _DSC_PPS_STATUS) == _TRUE)
                {
                    // Check DSC PassThrough Type
                    if(GET_DP_TX_DSC_PASSTHROUGH_TYPE() == _SOURCE_PASSTHROUGH_DSC_BY_NONE)
                    {
                        // Source Send The DSC Stream and PPS To DPF Sink
                        SET_DP_TX_DSC_PASSTHROUGH_TYPE(_SOURCE_PASSTHROUGH_DSC_BY_ENABLE_DSC_STREAM);
                    }

                    DebugMessageMst("DPTx DSC Stream PassThrough Enable", GET_DP_TX_DSC_PASSTHROUGH_TYPE());

                    SET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH();
                    return _TRUE;
                }
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Mac Tx DSC Pass-Through Change Detect
// Input Value  : enumDpMacSel
// Output Value : True, False
//--------------------------------------------------
bit ScalerDpMacMstToSstReorderStableDetect(EnumDpMacSel enumDpMacSel)
{
    if(GET_DP_TX_DOWNSTREAM_DSC_SUPPORT() == _ENABLE)
    {
        if(GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH() == _ENABLE)
        {
            if((GET_DP_TX_DSC_PASSTHROUGH_TYPE() == _SOURCE_PASSTHROUGH_DSC_BY_ENABLE_DFP_SINK) ||
               (GET_DP_TX_DSC_PASSTHROUGH_TYPE() == _SOURCE_PASSTHROUGH_DSC_BY_ENABLE_BRANCH_AND_DFP_SINK))
            {
                if(GET_DP_TX_DOWNSTREAM_DSC_DETECT_ENABLE() == _DISABLE)
                {
                    DebugMessageMst("DPTx Detect PassThrough Disable", GET_DP_TX_DSC_PASSTHROUGH_TYPE());

                    return _FALSE;
                }
            }

            if((GET_DP_TX_DSC_PASSTHROUGH_TYPE() == _SOURCE_PASSTHROUGH_DSC_BY_ENABLE_BRANCH) ||
               (GET_DP_TX_DSC_PASSTHROUGH_TYPE() == _SOURCE_PASSTHROUGH_DSC_BY_ENABLE_BRANCH_AND_DFP_SINK))
            {
                if(GET_DP_TX_DOWNSTREAM_DSC_DETECT_PASSTHROUGH() == _DISABLE)

                {
                    DebugMessageMst("DPTx Detect PassThrough Disable", GET_DP_TX_DSC_PASSTHROUGH_TYPE());

                    return _FALSE;
                }
            }

            if((ScalerDpMacStreamRxDscStreamChangeCheck(enumDpMacSel) == _TRUE) ||
               (ScalerDpMacDscRxDscStreamCheck(enumDpMacSel) == _FALSE))
            {
                DebugMessageMst("DPTx DSC Stream Check Change", 0x00);

                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DSC Get PPS Packet Byte
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstDscGetPpsInfo(void)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            // Backup The DSC PPS with Picture Width
            SET_DP_TX_INPUT_DSC_PIC_WIDTH(GET_DP_MAC_STREAM_RX0_DSC_PIC_WIDTH());

            // Backup The DSC PPS with Slice Width
            SET_DP_TX_INPUT_DSC_SLICE_WIDTH(GET_DP_MAC_STREAM_RX0_DSC_SLICE_WIDTH());

            // Backup The DSC PPS with BPP
            SET_DP_TX_INPUT_DSC_COLOR_BPP(GET_DP_MAC_STREAM_RX0_DSC_COLOR_BPP());

            // Backup The DSC PPS with Native 420
            SET_DP_TX_INPUT_DSC_COLOR_NATIVE_420(GET_DP_MAC_STREAM_RX0_DSC_COLOR_NATIVE_420());

            // Backup The DSC PPS with Native 422
            SET_DP_TX_INPUT_DSC_COLOR_NATIVE_422(GET_DP_MAC_STREAM_RX0_DSC_COLOR_NATIVE_422());

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            // Backup The DSC PPS with Picture Width
            SET_DP_TX_INPUT_DSC_PIC_WIDTH(GET_DP_MAC_STREAM_RX1_DSC_PIC_WIDTH());

            // Backup The DSC PPS with Slice Width
            SET_DP_TX_INPUT_DSC_SLICE_WIDTH(GET_DP_MAC_STREAM_RX1_DSC_SLICE_WIDTH());

            // Backup The DSC PPS with BPP
            SET_DP_TX_INPUT_DSC_COLOR_BPP(GET_DP_MAC_STREAM_RX1_DSC_COLOR_BPP());

            // Backup The DSC PPS with Native 420
            SET_DP_TX_INPUT_DSC_COLOR_NATIVE_420(GET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_420());

            // Backup The DSC PPS with Native 422
            SET_DP_TX_INPUT_DSC_COLOR_NATIVE_422(GET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_422());

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            // Backup The DSC PPS with Picture Width
            SET_DP_TX_INPUT_DSC_PIC_WIDTH(GET_DP_MAC_STREAM_RX2_DSC_PIC_WIDTH());

            // Backup The DSC PPS with Slice Width
            SET_DP_TX_INPUT_DSC_SLICE_WIDTH(GET_DP_MAC_STREAM_RX2_DSC_SLICE_WIDTH());

            // Backup The DSC PPS with BPP
            SET_DP_TX_INPUT_DSC_COLOR_BPP(GET_DP_MAC_STREAM_RX2_DSC_COLOR_BPP());

            // Backup The DSC PPS with Native 420
            SET_DP_TX_INPUT_DSC_COLOR_NATIVE_420(GET_DP_MAC_STREAM_RX2_DSC_COLOR_NATIVE_420());

            // Backup The DSC PPS with Native 422
            SET_DP_TX_INPUT_DSC_COLOR_NATIVE_422(GET_DP_MAC_STREAM_RX2_DSC_COLOR_NATIVE_422());

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            // Backup The DSC PPS with Picture Width
            SET_DP_TX_INPUT_DSC_PIC_WIDTH(GET_DP_MAC_STREAM_RX3_DSC_PIC_WIDTH());

            // Backup The DSC PPS with Slice Width
            SET_DP_TX_INPUT_DSC_SLICE_WIDTH(GET_DP_MAC_STREAM_RX3_DSC_SLICE_WIDTH());

            // Backup The DSC PPS with BPP
            SET_DP_TX_INPUT_DSC_COLOR_BPP(GET_DP_MAC_STREAM_RX3_DSC_COLOR_BPP());

            // Backup The DSC PPS with Native 420
            SET_DP_TX_INPUT_DSC_COLOR_NATIVE_420(GET_DP_MAC_STREAM_RX3_DSC_COLOR_NATIVE_420());

            // Backup The DSC PPS with Native 422
            SET_DP_TX_INPUT_DSC_COLOR_NATIVE_422(GET_DP_MAC_STREAM_RX3_DSC_COLOR_NATIVE_422());

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            // Backup The DSC PPS with Picture Width
            SET_DP_TX_INPUT_DSC_PIC_WIDTH(GET_DP_MAC_STREAM_RX4_DSC_PIC_WIDTH());

            // Backup The DSC PPS with Slice Width
            SET_DP_TX_INPUT_DSC_SLICE_WIDTH(GET_DP_MAC_STREAM_RX4_DSC_SLICE_WIDTH());

            // Backup The DSC PPS with BPP
            SET_DP_TX_INPUT_DSC_COLOR_BPP(GET_DP_MAC_STREAM_RX4_DSC_COLOR_BPP());

            // Backup The DSC PPS with Native 420
            SET_DP_TX_INPUT_DSC_COLOR_NATIVE_420(GET_DP_MAC_STREAM_RX4_DSC_COLOR_NATIVE_420());

            // Backup The DSC PPS with Native 422
            SET_DP_TX_INPUT_DSC_COLOR_NATIVE_422(GET_DP_MAC_STREAM_RX4_DSC_COLOR_NATIVE_422());

            break;
#endif
        default:

            break;
    }
}
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mst2sst DSC ScanInput Port
// Input Value  : None
// Output Value : Source Type
//--------------------------------------------------
bit ScalerDpMacMstToSstDscDecoderScanInputPort(void)
{
    BYTE ucDscMac = GET_MST2SST_BRANCH_DSC_X_MAPPING();

    DebugMessageDSC("MST2SST DSC Scan Input Type", 0);

    ScalerDpMacMstToSstDscDecoderRxMacReset();

    // Power On DSC MAC
    ScalerDscDecoderPowerCutControl(ucDscMac, _DSC_POWER_CUT_OFF);

    // Initial DSC MAC
    ScalerDscDecoderInitial(ucDscMac);

    // Set DSC MACx Stream Source According to 5to1 Mux for Scan Port
    SET_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(ScalerDscDecoderGetDscMacStreamSource(ucDscMac), ucDscMac);

    // DSC Decoder Mac Scan Port
    if(ScalerDscDecoderMacScanInputPort(ucDscMac) == _TRUE)
    {
        DebugMessageDSC("Mst2sst DSC Decoder Mac Scan Pass, MST2SST DSC Decoder Enable Successfully", ucDscMac);

        return _TRUE;
    }

    // Power off Dsc Mac if Scan Fail;
    ScalerDscDecoderPowerCutControl(ucDscMac, _DSC_POWER_CUT_ON);

    // CLR DSC MAC Stream Source
    CLR_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(ScalerDscDecoderGetDscMacStreamSource(ucDscMac));

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Mac MST2SST DSC Decode Check
// Input Value  : void
// Output Value : True, False
//--------------------------------------------------
bit ScalerDpMacMstToSstDscDecodeCheck(void)
{
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST);

    if(ScalerDpMacDscRxDscStreamCheck(enumDpMacSel) == _TRUE)
    {
        if(GET_DP_MAC_MST2SST_DETECT_DSC_DECODE_ENABLE() == _TRUE)
        {
            SET_DP_MAC_MST2SST_DSC_DECODE_ENABLE();
            return _TRUE;
        }
    }
    else
    {
        CLR_DP_MAC_MST2SST_DSC_DECODE_ENABLE();
        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Enable Dsc Fifo Under/OverFlow Watch Dog
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstDscDecoderSetFifoWD(bit bEn)
{
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST);

    ScalerDscDecoderSetFifoWD(ScalerDscDecoderDpMacRxxGetDscDecoderMac(enumDpMacSel), bEn);
}

//--------------------------------------------------
// Description  : DSC Dx Mac Reset
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstDscDecoderRxMacReset(void)
{
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
    ScalerDpMacMstToSstDscDecoderSetFifoWD(_DISABLE);
#endif

    ScalerDpMacDscRxDscStreamClearChange(enumDpMacSel);

    CLR_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(ScalerDscDecoderDpMacRxxDscMacStreamSourceMapping(enumDpMacSel));
}
#endif

#if((_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
//--------------------------------------------------
// Description  : MstToSst Dsc Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstDscReset(void)
{
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST);

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            ScalerDpMacStreamRx0DscStatusReset();
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX0_PPS_RECEIVE_TIMEOUT);
#endif
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            ScalerDpMacStreamRx1DscStatusReset();
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX1_PPS_RECEIVE_TIMEOUT);
#endif
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            ScalerDpMacStreamRx2DscStatusReset();
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX2_PPS_RECEIVE_TIMEOUT);
#endif
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            ScalerDpMacStreamRx3DscStatusReset();
#if(_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX3_PPS_RECEIVE_TIMEOUT);
#endif
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
            ScalerDpMacStreamRx4DscStatusReset();
#if(_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX4_PPS_RECEIVE_TIMEOUT);
#endif
            break;
#endif
        default:
            break;
    }

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    SET_DP_TX_DSC_PASSTHROUGH_TYPE(_SOURCE_PASSTHROUGH_DSC_BY_NONE);

    CLR_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH();
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)

    ScalerDpMacMstToSstDscDecoderRxMacReset();

    // CLR Source Enable DSC Flag
    CLR_DP_MAC_MST2SST_DSC_DECODE_ENABLE();

    // Reset DSC MAC
    ScalerDscDecoderInitial(GET_MST2SST_BRANCH_DSC_X_MAPPING());

    // Power Off Dsc Mac
    ScalerDscDecoderPowerCutControl(GET_MST2SST_BRANCH_DSC_X_MAPPING(), _DSC_POWER_CUT_ON);
#endif
}
#endif

#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : MstToSst Reset Source Mux Reg
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstResetSourceMuxReg(void)
{
    // Clear MST to SST Rx Mux
    EnumInputPort enumInputPort = GET_DP_RX_MAIN_PORT();
    EnumDpStreamSourceNum enumDpSourceTemp = ScalerDpMacStreamRxGetStreamSourceTypeToSourceMux(_STREAM_SOURCE_MST2SST);

    ScalerDpMacDphyRxSetSourceMuxReg(enumInputPort, enumDpSourceTemp, _DP_ST_NONE);
}

//--------------------------------------------------
// Description  : MstToSst Restore Source Mux
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacMstToSstRestoreSourceMuxBackupToReg(void)
{
    // Recover MST to SST Rx Mux
    if(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST) != _DP_MAC_NONE)
    {
        EnumInputPort enumInputPort = GET_DP_RX_MAIN_PORT();
        EnumDpStreamSourceNum enumDpSourceTemp = ScalerDpMacStreamRxGetStreamSourceTypeToSourceMux(_STREAM_SOURCE_MST2SST);
        EnumDpStreamNum enumDpStreamTemp = ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT));

        ScalerDpMacDphyRxSetSourceMuxReg(enumInputPort, enumDpSourceTemp, enumDpStreamTemp);
    }
}
#endif


#endif // End for #if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

