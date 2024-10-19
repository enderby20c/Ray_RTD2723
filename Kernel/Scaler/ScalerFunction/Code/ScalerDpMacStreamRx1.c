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
// ID Code      : ScalerDpMacStreamRx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_STREAM_RX1__

#include "ScalerFunctionInclude.h"
#include "DpMacStreamRx1/ScalerDpMacStreamRx1.h"

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX1_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile bit g_bDpMacStreamRx1CrcCalculate;
BYTE g_ucDpMacStreamRx1MSAFailRsetCount;
BYTE g_ucDpMacStreamRx1HPorchEnalrge;
bit g_bDpMacStreamRx1InterlaceVtotalNum;
WORD g_usDpMacStreamRx1Vfrontporch;
EnumDDomainRegion g_enumDpMacStreamRx1IrqForceBackgrd;

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
volatile bit g_bDpMacStreamRx1MiscCheckFail;
#endif

bit g_bDpMacStreamRx1VscSdpColorMode;

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1SPDInfoFrameCtrl;
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1HDRInfoFrameCtrl;
#endif

#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1AdvancedHDR10InfoFrameCtrl;
#endif

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1DMVsifInfoFrameCtrl;
#endif

#if(_AUDIO_SUPPORT == _ON)
StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1AudioInfoFrameCtrl;
BYTE g_pucDpMacRx1AudioInfoSdpData[_HW_DP_SDP_PAYLOAD_LENGTH];
#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
bit g_bDpMacStreamRx1SourceTypeJudge = _FALSE;
#endif

StructDpStreamInfo g_stDpMacStreamRx1StreamInfo;
StructDpInfo g_stDpMacStreamRx1Info;

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
bit g_bDpMacStreamRx1LocalDimmingDisableControl;
#endif

bit g_bDpMacStreamRx1Vbid3Chg;

StructDigitalColorInfo g_stDpMacStreamRx1ColorInfo;
StructDigitalColorInfoChanged g_stDpMacStreamRx1ColorInfoChanged;

StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1PpsSdpCtrl;
StructDpMacRxDscInfo g_stDpMacStreamRx1DscInfo;

#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
volatile bit g_bDpMacStreamRx1JudgeOOR;
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
bit g_bDpMacStreamRx1FifoIrqTriggerCheck;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Dp Mac Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1MacInitial(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    // DP RGB Output Enable
    ScalerSetBit(P70_01_DPF_CTRL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // 0x00:disable error correction, 0xF4:enable all error correction
    ScalerSetBit(P75_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);

    // Disable DP Fifo Under/OverFlow Watch Dog
    ScalerSetBit(P75_38_DP_WD_CTRL_0, ~(_BIT5 | _BIT4), 0x00);

    // Disable DP Fifo Under/OverFlow IRQ
    ScalerSetBit(P75_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

    // Pps Read Out Config Address
    ScalerSetByte(P7E_AC_DP_PPS_RO_CONFIG_ADDR_0, 0x05);

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    CLR_DP_MAC_STREAM_RX1_ALPM_ENABLE_128B132B();
#endif
#endif

    // DP RGB Output Enable
    ScalerSetBit(PB8_31_DP_OUTPUT_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // DP CLK Output Enable
    ScalerSetBit(PB8_A2_PLL_OUT_CONTROL, ~(_BIT7), (_BIT7));

    // 0x00:disable error correction, 0xF4:enable all error correction
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);

    // Disable DP BS Miss Detect IRQ
    ScalerDpMacStreamRx1SetBsMissDetectIRQ(_DISABLE);

    // Enable DP BS Miss Detect
#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
    ScalerDpMacStreamRx1SetBsMissDetectStart(_ENABLE);
#endif

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
    // Disable Dp 8b10b Decoder Error WD
    ScalerDpMacDphyRxSet8b10bDecErrorWD(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1), _DISABLE);
#endif

    // Disable DP Fifo Under/OverFlow Watch Dog
    ScalerSetBit(PB9_3C_DP_WD_CTRL_0, ~(_BIT5 | _BIT4), 0x00);

    // Pps Read Out Config Address
    ScalerSetByte(P26_AC_DP_PPS_RO_CONFIG_ADDR_0, 0x05);

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
    // Disable DP Color Space Change WD
    ScalerDpMacStreamRx1SetColorSpaceChangeWD(_DISABLE);

    // Disable Msa Change IRQ
    ScalerDpMacStreamRx1SstSetMsaChangeIRQ(_DISABLE);
#endif

    // Disable DP Fifo Under/OverFlow IRQ
    ScalerSetBit(PB9_3C_DP_WD_CTRL_0, ~(_BIT1 | _BIT0), 0x00);

    // Disable VBID[3] No Video IRQ And Clear Flag
    ScalerDpMacStreamRx1DisableNoVideoStreamIRQ();

    ScalerDpMacStreamRx1SetSdpReset();

    ScalerDpMacStreamRx1SetMsaReset();

    ScalerDpMacStreamRx1SetHblankSupportNoSfMode();

#if(_DP_PR_MODE_SUPPORT == _ON)
    ScalerDpMacStreamRx1PRModeInitial();
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    CLR_DP_MAC_STREAM_RX1_H_PORCH_ENLARGE();
#endif

    CLR_DP_MAC_STREAM_RX1_MSA_FAIL_RESET_COUNT();

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    CLR_DP_MAC_STREAM_RX1_ALPM_ENABLE_8B10B();
#endif

#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
    CLR_DP_MAC_STREAM_RX1_JUDGE_OOR();
#endif
}

//--------------------------------------------------
// Description  : Dp Secondary Data Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpInitial(void)
{
    // Sec Ram Receive Initial
    ScalerDpMacStreamRx1SetSdpBuffRcvInitial();

    // Mac Receive Metadata SDP Type Inital, Set by EDID/Display ID
    ScalerDpMacStreamRx1SetMetaSdpRcvInitial(_DP_SDP_TYPE_VSC_EXT_VESA);

    // VSC Inital
    ScalerDpMacStreamRx1SetVscSdpRcvInitial();
}

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
//--------------------------------------------------
// Description  : DP MAC Stream power process
// Input Value  : EnumInputPort, EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PowerProc(EnumPowerAction enumPowerAction)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_OFF:

            if(GET_DP_MAC_STREAM_RX1_POWER_CUT_STATUS() == _OFF)
            {
                DebugMessageDpRx("DP MAC Stream Rx1 Power Off", 0);

                ScalerDpAuxRxSetManualMode(enumInputPort);

                // DP MAC1 Power Cut Enable
                if(ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP14_MAC, _POWER_CUT_ON, _POWER_ON_DELAY_NONE) == _SUCCESS)
                {
                    SET_DP_MAC_STREAM_RX1_POWER_CUT_STATUS(_ON);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP20_MAC, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
#endif
                }

                ScalerDpAuxRxSetAutoMode(enumInputPort);
            }

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

            if(GET_DP_MAC_STREAM_RX1_POWER_CUT_STATUS() == _ON)
            {
                DebugMessageDpRx("DP MAC Stream Rx1 Power On", 0);

                // DP MAC1 Power Cut Disable
                if(ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP14_MAC, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS) == _SUCCESS)
                {
                    SET_DP_MAC_STREAM_RX1_POWER_CUT_STATUS(_OFF);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
                    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP20_MAC, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
#endif

                    // Recover Data from Power Cut State
                    ScalerDpMacStreamRxPowerDataRecover(enumInputPort);

#if(_AUDIO_SUPPORT == _ON)
#if(_EMBEDDED_DAC_SUPPORT == _ON)
                    // Avoid Audio DAC Pop Noise
                    ScalerAudioDACNormalToDepopCheck(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT));
#endif

                    // Audio Re-Initial from Power Cut State
                    ScalerDpAudioRx1AudioInitial();

                    // Avoid Audio Phase Delay Between L Channel and R Channel
                    ScalerAudioDVCResetProcCheck(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT));
#endif
                }
            }

            break;

        default:
            break;
    }
}
#endif

//-----------------------------------------------------------------------
// Description  : Set DP MAC Clock Output / PLL Power Off
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------------
void ScalerDpMacStreamRx1LowPowerProc(void)
{
    // Turn Off Output Clock
    ScalerSetBit(PB8_A2_PLL_OUT_CONTROL, ~_BIT7, 0x00);

    // Turn Off SCLK PLL
    ScalerSetBit(PB8_A8_M2PLL_CONTROL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Dp Secondary Data Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SecDataBlockReset(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Sec Data Block Reset
    ScalerSetBit(P70_05_DP20MAC_RESET, ~_BIT1, _BIT1);
    ScalerSetBit(P70_05_DP20MAC_RESET, ~_BIT1, 0x00);
#endif
    // Sec Data Block Reset
    ScalerSetBit(PB8_1E_MAC_DIG_RESET_CTRL, ~_BIT4, _BIT4);
    ScalerSetBit(PB8_1E_MAC_DIG_RESET_CTRL, ~_BIT4, 0x00);

    // Wait 2T LCLK Time For Data Block Reset Ready
    DELAY_10US();
}

//--------------------------------------------------
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : None
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
EnumSourceType ScalerDpMacStreamRx1ScanInputPort(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
    EnumDpMacRxStreamVideoType enumDpMacRxStreamVideoType = _DP_STREAM_NONE;

    if(GET_DP_MAC_STREAM_RX1_STREAM_PREDETECT() == _FALSE)
    {
        if(ScalerDpMacStreamRx1StreamPreDetect(enumInputPort) == _TRUE)
        {
            SET_DP_MAC_STREAM_RX1_STREAM_PREDETECT(_TRUE);
        }
    }
    else
    {
        enumDpMacRxStreamVideoType = ScalerDpMacStreamRx1StreamVideoSetting(enumInputPort);

        if(enumDpMacRxStreamVideoType == _DP_STREAM_PASS)
        {
            return _SOURCE_DP;
        }
        else if(enumDpMacRxStreamVideoType == _DP_STREAM_FAIL)
        {
            SET_DP_MAC_STREAM_RX1_STREAM_PREDETECT(_FALSE);
        }
    }

    return _SOURCE_NONE;
}

//--------------------------------------------------
// Description  : DP Mac Rx1 Stream Pre Scan Port
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerDpMacStreamRx1StreamPreDetect(EnumInputPort enumInputPort)
{
    // 2nd Scramble Setting Sync
    ScalerDpMacDphyRxScrambleSetting(enumInputPort);

    // Cts Fifo Must Be Reset After Link Clk Stable, Until DPF Enable
    ScalerDpMacStreamRx1CtsFifoReset();

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1StreamPreDetect_128b132b(enumInputPort);
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1StreamPreDetect_8b10b(enumInputPort);
    }
}

//--------------------------------------------------
// Description  : DP Mac Rx1 Stream Setting
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
EnumDpMacRxStreamVideoType ScalerDpMacStreamRx1StreamVideoSetting(EnumInputPort enumInputPort)
{
    EnumDpMacRxStreamVideoType enumDpMacRxStreamVideoType = _DP_STREAM_NONE;

    switch(GET_DP_MAC_STREAM_RX1_STREAM_DATA_PATH())
    {
        case _DATA_PATH_VESA:

            enumDpMacRxStreamVideoType = ScalerDpMacStreamRx1StreamVesaVideoSetting(enumInputPort);

            if(enumDpMacRxStreamVideoType == _DP_STREAM_PASS)
            {
                ScalerDpMacStreamRx1StreamJudgeSetting(enumInputPort);
            }

            return enumDpMacRxStreamVideoType;

        case _DATA_PATH_VIDEO_BYPASS:

            return _DP_STREAM_PASS;

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
        case _DATA_PATH_DSC_DECODER:

            ScalerDpMacStreamRx1TimingInfoAdjustForReorderTracking(&g_stDpMacStreamRx1Info);

            ScalerDpMacStreamRx1DscSetting();

            ScalerDpMacStreamRx1StreamJudgeSetting(enumInputPort);

            return _DP_STREAM_PASS;

#endif
        case _DATA_PATH_DSC_BYPASS:

            return _DP_STREAM_PASS;

        case _DATA_PATH_VIDEO_REORDER:
        case _DATA_PATH_DSC_REORDER:

            ScalerDpMacStreamRx1TimingInfoAdjustForReorderTracking(&g_stDpMacStreamRx1Info);

#if(_AUDIO_SUPPORT == _ON)
            // Enable Audio Channel
            ScalerDpAudioRx1AudioEnableControl(_ENABLE);
#endif

            ScalerDpMacStreamRx1SdpDataDetect();

            return _DP_STREAM_PASS;

        case _DATA_PATH_NONE:
        default:

            return _DP_STREAM_NONE;
    }
}

//--------------------------------------------------
// Description  : DP Mac Rx1 Judge Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1StreamJudgeSetting(EnumInputPort enumInputPort)
{
    // Use for Audio/Sdp relative Settings.
    ScalerDpMacStreamRx1SdpSetting();

#if(_DP_MST_SUPPORT == _ON)
    ScalerDpAuxRxClrSourceFirstPowerOn(enumInputPort);
#endif

    ScalerDpAuxRxCancelHdcpLongHotplug(enumInputPort);

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    SET_DP_MAC_STREAM_RX1_SOURCE_TYPE_JUDGE();
#endif
}

//--------------------------------------------------
// Description  : DP Mac Rx1 Vesa Video Setting
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
EnumDpMacRxStreamVideoType ScalerDpMacStreamRx1StreamVesaVideoSetting(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1StreamVesaVideoSetting_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1StreamVesaVideoSetting_8b10b();
    }
}

//--------------------------------------------------
// Description  : PreDetect Stream Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1StreamPreDetectReset(void)
{
    SET_DP_MAC_STREAM_RX1_STREAM_INFO_TYPE(_INFO_TYPE_NONE);

    SET_DP_MAC_STREAM_RX1_STREAM_PREDETECT(_FALSE);

    SET_DP_MAC_STREAM_RX1_STREAM_CLOCK(0);

    SET_DP_MAC_STREAM_RX1_NATIVE_PIXEL_CLOCK(0);
}

//--------------------------------------------------
// Description  : On Line Check DP stability
// Input Value  : None
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerDpMacStreamRx1StableDetect(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1StableDetect_128b132b(enumInputPort);
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1StableDetect_8b10b(enumInputPort);
    }
}

//--------------------------------------------------
// Description  : DP Timing Info Adjust
// Input Value  : *pstDpInfo
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1TimingInfoAdjust(StructDpInfo *pstDpInfo)
{
    WORD pusTemp[2];

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
    if(ScalerDpMacStreamRx1GetDscReorder() == _FALSE)
#endif
    {
        if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
        {
            DebugMessageDpRx("DP MAC RX1: Horizontal Timing Info Modify(Div 2) for YCbCr420", 0);
            pstDpInfo->stDpTimingInfo.usHTotal /= 2;
            pstDpInfo->stDpTimingInfo.usHStart /= 2;
            pstDpInfo->stDpTimingInfo.usHWidth /= 2;
            pstDpInfo->stDpTimingInfo.usHSWidth /= 2;
        }
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
    {
        WORD usInputPixelClk = GET_DP_MAC_STREAM_RX1_STREAM_CLOCK() / 100000;

        // Get HSW
        pstDpInfo->stDpTimingInfo.usHSWidth = ScalerSyncGetHSWbyClk(usInputPixelClk);

        // Get HStart
        pstDpInfo->stDpTimingInfo.usHStart = ScalerSyncGetHStartbyHSW(pstDpInfo->stDpTimingInfo.usHSWidth, usInputPixelClk);
    }
    else
#endif
    {
        // Check if MSA HSW is more than Hstart
        if(pstDpInfo->stDpTimingInfo.usHSWidth >= pstDpInfo->stDpTimingInfo.usHStart)
        {
            // Check if _DE_ONLY_MODE_HSW is more than Hstart
            if(_DE_ONLY_MODE_HSW >= pstDpInfo->stDpTimingInfo.usHStart)
            {
                // Adjust HSW = Hstart - 2
                pstDpInfo->stDpTimingInfo.usHSWidth = pstDpInfo->stDpTimingInfo.usHStart - 2;
            }
            else
            {
                // Adjust HSW = _DE_ONLY_MODE_HSW
                pstDpInfo->stDpTimingInfo.usHSWidth = _DE_ONLY_MODE_HSW;
            }
        }

        // Get HSW min by Measure clock
        pusTemp[0] = ((DWORD) _DP_HSYNC_WIDTH_MEASURE_COUNTER * (GET_DP_MAC_STREAM_RX1_STREAM_CLOCK() / 1000)) / _MEASURE_CLK + 1;

        // Get Current H Blanking
        pusTemp[1] = pstDpInfo->stDpTimingInfo.usHTotal - pstDpInfo->stDpTimingInfo.usHWidth;

        // Check if HSW is less thane HSW min
        if(pstDpInfo->stDpTimingInfo.usHSWidth <= pusTemp[0])
        {
            // Check if H Blanking is more than HSW min
            if((pusTemp[1]) >= pusTemp[0])
            {
                // Adjust HSW = HSW min
                pstDpInfo->stDpTimingInfo.usHSWidth = pusTemp[0];
            }
            else
            {
                // Adjust HSW = Max H Porch
                pstDpInfo->stDpTimingInfo.usHSWidth = pusTemp[1];
            }
        }

        // Adjust VStart because V front porch must not be less than 2 line in scaling down block
        pstDpInfo->stDpTimingInfo.usVStart = pstDpInfo->stDpTimingInfo.usVTotal - pstDpInfo->stDpTimingInfo.usVHeight - GET_DP_MAC_STREAM_RX1_VFRONT_PORCH();
    }

    if(ScalerDpMacStreamRx1FrameSyncBeModeCheck() == _TRUE)
    {
        // Set VStart 0 in BE framesync Mode
        pstDpInfo->stDpTimingInfo.usVStart = 0x00;

        // Set VSW 1 in BE framesync Mode
        pstDpInfo->stDpTimingInfo.usVSWidth = 0x01;
    }
}

//--------------------------------------------------
// Description  : Check Frame Sync Be Mode Or Not
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRx1FrameSyncBeModeCheck(void)
{
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_ALPM_ENABLE() == _TRUE)
    {
        return _TRUE;
    }
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) && (_FW_DP_RX_FREESYNC_DPF_MODE_FRAME_SYNC_BE_DRR == _ON))
    if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Timing Info Adjust For Reorder Tracking
// Input Value  : *pstDpInfo
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1TimingInfoAdjustForReorderTracking(StructDpInfo *pstDpInfo)
{
    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        DebugMessageDpRx("DP MAC RX1: Horizontal Timing Info Modify(Div 2) for YCbCr420", 0);
        pstDpInfo->stDpTimingInfo.usHTotal /= 2;
        pstDpInfo->stDpTimingInfo.usHStart /= 2;
        pstDpInfo->stDpTimingInfo.usHWidth /= 2;
        pstDpInfo->stDpTimingInfo.usHSWidth /= 2;
    }
}

//--------------------------------------------------
// Description  : DP RGB Output Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1AVMute(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacStreamRx1AVMute_128b132b();
    }
    else
#endif
    {
        ScalerDpMacStreamRx1AVMute_8b10b();
    }
}

//--------------------------------------------------
// Description  : Bs Miss Flag Clear
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1BsMissFlagClear(void)
{
    // Clear BS Detect Flag
    ScalerSetBit(_REG_DP_MAC_STREAM_RX1_BS_MISS_CTRL, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : Enable DP BS Miss Detect IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetBsMissDetectIRQ(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Clear BS Detect Flag
        ScalerDpMacStreamRx1BsMissFlagClear();

        // BS Detect IRQ Setting
        ScalerSetBit(_REG_DP_MAC_STREAM_RX1_BS_MISS_CTRL, ~(_BIT7 | _BIT6), _BIT7);
    }
    else
    {
        // BS Detect IRQ Setting
        ScalerSetBit(_REG_DP_MAC_STREAM_RX1_BS_MISS_CTRL, ~(_BIT7 | _BIT6), 0x00);

        // Clear BS Detect Flag
        ScalerDpMacStreamRx1BsMissFlagClear();
    }
}

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetFifoIRQ(bit bEn)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        ScalerSetBit(P75_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), ((bEn == _ENABLE) ? (_BIT1 | _BIT0) : 0x00));
    }
    else
#endif
    {
        ScalerSetBit(PB9_3E_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), ((bEn == _ENABLE) ? (_BIT1 | _BIT0) : 0x00));
    }
}

//--------------------------------------------------
// Description  : Disable DP Fifo Under/OverFlow IRQ
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DisableFifoIRQ(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerSetBit(P75_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);
#endif
    ScalerSetBit(PB9_3E_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow Watch Dog
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetFifoWD(bit bEn)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        ScalerSetBit(P75_38_DP_WD_CTRL_0, ~(_BIT5 | _BIT4), ((bEn == _ENABLE) ? (_BIT5 | _BIT4) : 0x00));
    }
    else
#endif
    {
        ScalerSetBit(PB9_3C_DP_WD_CTRL_0, ~(_BIT5 | _BIT4), ((bEn == _ENABLE) ? (_BIT5 | _BIT4) : 0x00));
    }
}

//--------------------------------------------------
// Description  : Disable DP Fifo Under/OverFlow Watch Dog
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DisableFifoWD(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerSetBit(P75_38_DP_WD_CTRL_0, ~(_BIT5 | _BIT4), 0x00);
#endif
    ScalerSetBit(PB9_3C_DP_WD_CTRL_0, ~(_BIT5 | _BIT4), 0x00);
}

//--------------------------------------------------
// Description  : Get DP Fifo Watch Dog Enable Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetFifoWDStatus(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return (ScalerGetBit(P75_38_DP_WD_CTRL_0, _BIT5) == _BIT5) ? _TRUE : _FALSE;
    }
    else
#endif
    {
        return (ScalerGetBit(PB9_3C_DP_WD_CTRL_0, _BIT5) == _BIT5) ? _TRUE : _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check Dp Video Stream VBID 8b10b
// Input Value  : None
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetVideoStream(void)
{
#if((_DP_MST_SUPPORT == _ON) || (_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON))
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(_DP_MAC_1);
    EnumInputPort enumInputPort = ScalerDpMacStreamRxGetSourcePort(enumDpMacStreamSourceType);

    // Check if ST Source is Assigned the STx Stream In MST Mode
    if((ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _TRUE) &&
       (ScalerDpMacDphyRxGetMstStreamExist(enumDpMacStreamSourceType) == _FALSE))
    {
        return _FALSE;
    }
#endif

    if(GET_DP_MAC_STREAM_RX1_VBID3_CHANGED() == _TRUE)
    {
        CLR_DP_MAC_STREAM_RX1_VBID3_CHANGED();

        return _FALSE;
    }

    if(ScalerDpMacStreamRx1GetVbidInfo(_DP_VBID_VIDEO_STREAM) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check DP Rx Set Hblank Support No Sf Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetHblankSupportNoSfMode(void)
{
    if(ScalerDpMacStreamRxHblankNoSfModeSupport() == _TRUE)
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerSetBit(P70_08_INTERLACE_CTRL_2, ~_BIT2, _BIT2);
#endif

        ScalerSetBit(PB8_94_DP_RSV4, ~_BIT4, _BIT4);
    }
}

//--------------------------------------------------
// Description  : Get Dp MSA Timing Info
// Input Value  : DP Info Structure
// Output Value : True --> Get MSA Info
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetMsaTimingInfo(StructDpInfo *pstDpInfo)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1GetMsaTimingInfo_128b132b(pstDpInfo);
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1GetMsaTimingInfo_8b10b(pstDpInfo);
    }
}

//--------------------------------------------------
// Description  : Get DP Link Info from Measure Function
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetMeasureLinkInfo(StructDpInfo *pstDpInfo)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1GetMeasureLinkInfo_128b132b(pstDpInfo);
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1GetMeasureLinkInfo_8b10b(pstDpInfo);
    }
}

//--------------------------------------------------
// Description  : Display Format Gen Info Adjust
// Input Value  : StructDpInfo
// Output Value : TRUE --> Adjust successfully
//--------------------------------------------------
bit ScalerDpMacStreamRx1StreamInfoSetting(StructDpInfo *pstDpInfo)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
    enumInputPort = enumInputPort;

    /////////////////////////////
    // Hblanking Modify Adjust //
    /////////////////////////////

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
    if(ScalerDpMacStreamRxHlankingModifyCheck(enumInputPort, pstDpInfo) == _TRUE)
    {
        // Update HBE/HBR DPCD Timing Info To DPF
        ScalerDpMacStreamRxHblankingModifyDpfUpdate(pstDpInfo);

        DebugMessageDpRx("DP MAC RX1: Hblanking Modify Mode Check True", 0);
    }
#endif

    //////////////////////////////////////////
    // Record Before H Porch Enlarge Adjust //
    //////////////////////////////////////////

    // Record Native Input Pixel Clock (Unit is 0.1MHz) For Lut
    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        SET_DP_MAC_STREAM_RX1_NATIVE_PIXEL_CLOCK(pstDpInfo->stDpLinkInfo.ulStreamClockHz / 2);
    }
    else
    {
        SET_DP_MAC_STREAM_RX1_NATIVE_PIXEL_CLOCK(pstDpInfo->stDpLinkInfo.ulStreamClockHz);
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
    {
        ScalerDpMacStreamRx1SetDrrMsaForLut(pstDpInfo);
    }
#endif

    ////////////////////////////
    // H Porch Enlarge Adjust //
    ////////////////////////////

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    // Calculate for H Porch Enlarge
    ScalerDpMacStreamRx1HPorchEnlarge(&pstDpInfo->stDpTimingInfo);

    if(GET_DP_MAC_STREAM_RX1_H_PORCH_ENLARGE() != 0x00)
    {
        if(pstDpInfo->stDpTimingInfo.usHTotal <= GET_DP_MAC_STREAM_RX1_H_PORCH_ENLARGE())
        {
            DebugMessageDpRx("DP MAC RX1: (Htotal <= H_PORCH_ENLARGE) is invalid", 0);

            return _FALSE;
        }

        // Calculate Stream Clock After Enlarging HTotal (Unit is Hz)
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
        {
            PDATA_WORD(0) = pstDpInfo->stDpTimingInfo.usHTotal - GET_DP_MAC_STREAM_RX1_H_PORCH_ENLARGE();

            pstDpInfo->stDpLinkInfo.ulStreamClockHz = ScalerGlobalComputeDwordMulDiv((DWORD)pstDpInfo->stDpLinkInfo.ulStreamClockHz, pstDpInfo->stDpTimingInfo.usHTotal, PDATA_WORD(0));
        }
        else
#endif
        {
#if(_DP_FREESYNC_SUPPORT == _ON)
            if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
            {
                PDATA_WORD(0) = pstDpInfo->stDpTimingInfo.usHTotal - GET_DP_MAC_STREAM_RX1_H_PORCH_ENLARGE();

                pstDpInfo->stDpLinkInfo.ulStreamClockHz = ScalerGlobalComputeDwordMulDiv((DWORD)pstDpInfo->stDpLinkInfo.ulStreamClockHz, pstDpInfo->stDpTimingInfo.usHTotal, PDATA_WORD(0));
            }
            else
#endif
            {
#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
                if(GET_DP_MAC_STREAM_RX1_JUDGE_OOR() == _TRUE)
                {
                    pstDpInfo->stDpLinkInfo.ulStreamClockHz = ScalerGlobalComputeDwordMulDiv(pstDpInfo->stDpTimingInfo.usHTotal, pstDpInfo->stDpLinkInfo.ulLinkClockHz / 2, (DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount);
                }
                else
#endif
                {
                    pstDpInfo->stDpLinkInfo.ulStreamClockHz = ((((DWORD)pstDpInfo->stDpTimingInfo.usHTotal * ((DWORD)pstDpInfo->stDpTimingInfo.usVTotal) * 100) / pstDpInfo->stDpLinkInfo.ulVBsToBsCountN) * _GDIPHY_RX_GDI_CLK_KHZ * 10);
                }
            }
        }
    }
#endif

    ///////////////////////
    // For YUV420 Adjust //
    ///////////////////////

    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        pstDpInfo->stDpLinkInfo.ulStreamClockHz /= 2;
    }

    /////////////////////////////
    // For PLL Tracking Adjust //
    /////////////////////////////

    // Initial Value Need to be Lower than the Target Value for Tracking (Margin is 0.07%)
    pstDpInfo->stDpLinkInfo.ulInitStreamClockHz = ScalerGlobalComputeDwordMulDiv(pstDpInfo->stDpLinkInfo.ulStreamClockHz, 9993, 10000);

    SET_DP_MAC_STREAM_RX1_STREAM_CLOCK(pstDpInfo->stDpLinkInfo.ulStreamClockHz);

    DebugMessageDpRx("DP MAC RX1: Stream Clock After Adjust", pstDpInfo->stDpLinkInfo.ulStreamClockHz);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Dp BS Status
// Input Value  : None
// Output Value : Stable --> BS Exist
//--------------------------------------------------
bit ScalerDpMacStreamRx1BsMissCheck(void)
{
    return (bit)(ScalerGetBit(_REG_DP_MAC_STREAM_RX1_BS_MISS_CTRL, _BIT6) == _BIT6);
}

//--------------------------------------------------
// Description  : Check Dp Interlace by VBID or Measure
// Input Value  : None
// Output Value : True --> Interlace
//--------------------------------------------------
bit ScalerDpMacStreamRx1InterlaceCheck(StructDpInfo *pstDpInfo)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1InterlaceCheck_128b132b(pstDpInfo);
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1InterlaceCheck_8b10b(pstDpInfo);
    }
}

//--------------------------------------------------
// Description  : DP Get Video Info
// Input Value  : None
// Output Value : TRUE --> Get successfully
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetVideoInfo(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1GetVideoInfo_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1GetVideoInfo_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Set Color Info Macros
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetColorInfo(void)
{
    BYTE ucColorDepth = 0;

    if(GET_DP_MAC_STREAM_RX1_VSC_SDP_COLOR_MODE() == _TRUE)
    {
        // Use VSC SDP
        // Set Color Space Macro
        switch(GET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE())
        {
            case _VSC_COLOR_SPACE_0:
                SET_DP_MAC_STREAM_RX1_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;

            case _VSC_COLOR_SPACE_1:
                SET_DP_MAC_STREAM_RX1_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
                break;

            case _VSC_COLOR_SPACE_2:
                SET_DP_MAC_STREAM_RX1_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
                break;

            case _VSC_COLOR_SPACE_3:
                SET_DP_MAC_STREAM_RX1_COLOR_SPACE(_COLOR_SPACE_YCBCR420);
                break;

            case _VSC_COLOR_SPACE_4:
                SET_DP_MAC_STREAM_RX1_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
                break;

            case _VSC_COLOR_SPACE_5:
                SET_DP_MAC_STREAM_RX1_COLOR_SPACE(_COLOR_SPACE_RAW);
                break;

            default:
                SET_DP_MAC_STREAM_RX1_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;
        }

        // Set Colorimetry Ext
        ScalerDpMacStreamRx1ColorimetryExtSetting();
    }
    else
    {
        // Set Color Space Macro
        switch(GET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE())
        {
            case _BIT1:
                SET_DP_MAC_STREAM_RX1_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
                break;

            case _BIT2:
                SET_DP_MAC_STREAM_RX1_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
                break;

            case _BIT7:
                SET_DP_MAC_STREAM_RX1_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
                break;

            case (_BIT7 | _BIT1):
                SET_DP_MAC_STREAM_RX1_COLOR_SPACE(_COLOR_SPACE_RAW);
                break;

            default:
                SET_DP_MAC_STREAM_RX1_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;
        }

        // Set Colorimetry
        ScalerDpMacStreamRx1ColorimetrySetting();
    }

    // Get Color Depth Value By Color Space
    ucColorDepth = ScalerSyncDpGetColorDepthValue(GET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE(), GET_DP_MAC_STREAM_RX1_COLOR_SPACE());

    // Set Color Depth Macro
    SET_DP_MAC_STREAM_RX1_COLOR_DEPTH(ucColorDepth);

    // Set Porch Color
    if((GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420))
    {
        if(GET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_LIMIT)
        {
            SET_DP_MAC_STREAM_RX1_PORCH_COLOR_YCC_LIMIT();
        }
        else if(GET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_FULL)
        {
            SET_DP_MAC_STREAM_RX1_PORCH_COLOR_YCC_FULL();
        }
    }
    else
    {
        SET_DP_MAC_STREAM_RX1_PORCH_COLOR_RGB();
    }

    // Set Quantization Range
    ScalerDpMacStreamRx1QuantizationSetting();
}

//--------------------------------------------------
// Description  : DP Stream Clk PLL Setting
// Input Value  : StructDpInfo
// Output Value : True --> Stream CLK Regen. ok
//--------------------------------------------------
bit ScalerDpMacStreamRx1StreamClkRegenerate(StructDpInfo *pstDpInfo)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
    DWORD ulPllTargetClockHz = 0;
    DWORD ulDataPathSpeedLimit = (DWORD)_HW_DATA_PATH_SPEED_LIMIT * 100000;
    EnumDpStreamPixelMode enumPixelMode = _NONE_PIXEL_MODE;

    // ulDataPathSpeedLimit * (1 + 1% margin)
    ulDataPathSpeedLimit = GET_DWORD_MUL_DIV(ulDataPathSpeedLimit, 101, 100);


    /////////////////////////////
    // PLL Input Clock Setting //
    /////////////////////////////

    // Set PLL Input Clock and Divider for Link Clock
    if(ScalerDpMacStreamRx1SetPLLInputClockSetting(enumInputPort, pstDpInfo) == _FALSE)
    {
        return _FALSE;
    }

    DebugMessageDpRx("DP MAC RX1: PLL In Clk", pstDpInfo->stDpLinkInfo.ulPllInputClockHz);


    ///////////////////////////////////
    // Multiple Clock Feature Enable //
    ///////////////////////////////////

    if(ScalerDpMacStreamRx1CheckMultipleClkFeatureSupport(pstDpInfo, ulDataPathSpeedLimit) == _FALSE)
    {
        return _FALSE;
    }


    /////////////////////////////////////////
    // PLL Target Clock & Pixel Mode Judge //
    /////////////////////////////////////////

    if(ScalerDpMacStreamRx1PllTargetClockPixelModeJudge(pstDpInfo, ulDataPathSpeedLimit, &ulPllTargetClockHz, &enumPixelMode) == _FALSE)
    {
        return _FALSE;
    }

    DebugMessageDpRx("DP MAC RX1: PLL Out Clk", ulPllTargetClockHz);


    ////////////////////////
    // Pixel Mode Setting //
    ////////////////////////

    if(ScalerDpMacStreamRx1PixelModeSetting(enumInputPort, enumPixelMode) == _FALSE)
    {
        return _FALSE;
    }

    DebugMessageDpRx("DP MAC RX1: Pixel Mode", enumPixelMode);


    ////////////////////////////////
    // PLL Output Divider Setting //
    ////////////////////////////////

    if(ScalerDpMacStreamRx1PllOutputDivSetting(enumInputPort, enumPixelMode) == _FALSE)
    {
        return _FALSE;
    }


    /////////////////////
    // PLL VCO Setting //
    /////////////////////

    if(ScalerDpMacStreamRx1SetPLLFreqNf(ulPllTargetClockHz, pstDpInfo, ulDataPathSpeedLimit) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP NF PLL Tracking Enable
// Input Value  : StructDpMacRxInfo *pstDpInfo
// Output Value : True --> Tracking Stable
//--------------------------------------------------
bit ScalerDpMacStreamRx1TrackingSetting(StructDpInfo *pstDpInfo)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumDpLinkChannelCodingType enumDpLinkChannelCodingType = ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1));
#endif

    WORD usTrackingHtotal = 0;
    BYTE ucSscLineNumber = 0;
    WORD usHalfBSDelayCnt = 0;
    BYTE ucOneFrameTime = 0;
    DWORD ulTemp = 0;
#if(_DP_DE_ONLY_MODE_WITH_FULL_LAST_LINE_SUPPORT == _OFF)
    WORD usHttDeonlyMinus = 0;
#endif

    // Disable Tracking
    ScalerSetBit(PB8_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(enumDpLinkChannelCodingType == _CODING_TYPE_128B132B)
    {
        // 128B132B Tracking HTT = dpf_htt / pixel mode
        usTrackingHtotal = pstDpInfo->stDpTimingInfo.usHTotal / pstDpInfo->stDpLinkInfo.ucPixelMode;
    }
    else
#endif
    {
        // 8B10B Tracking HTT = dpf_htt / 2
        usTrackingHtotal = pstDpInfo->stDpTimingInfo.usHTotal / 2;
    }

    // Set Tracking HTT
    ScalerSetByte(PB8_F2_DSC_HTT_0, HIBYTE(usTrackingHtotal));
    ScalerSetByte(PB8_F3_DSC_HTT_1, LOBYTE(usTrackingHtotal));

    // Set Tracking VHT
    ScalerSetByte(PB8_F4_DSC_VHT_0, HIBYTE(pstDpInfo->stDpTimingInfo.usVHeight));
    ScalerSetByte(PB8_F5_DSC_VHT_1, LOBYTE(pstDpInfo->stDpTimingInfo.usVHeight));

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_ALPM_ENABLE() == _TRUE)
    {
        // For HS Tracking, pick BE as hsync
        ScalerSetBit(PB8_EA_HS_TRACKING_NEW_MODE1, ~_BIT5, _BIT5);

#if(_DP_PR_MODE_SUPPORT == _ON)
        if(GET_DP_MAC_STREAM_RX1_PR_ENABLE() == _TRUE)
        {
            // Set Tracking refer to Adaptive-Sync Sdp to Stop Tracking and reset BE counter
            ScalerSetBit(PB8_E0_VS_TRACK_EN, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
        }
        else
#endif
        {
            // Set Tracking refer to ML_PHY sleep and ML_PHY Wake Sequence to Stop Tracking and reset BE counter
            ScalerSetBit(PB8_E0_VS_TRACK_EN, ~(_BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT3));
        }
    }
    else
#endif
    {
        // For HS Tracking, pick BS as hsync
        ScalerSetBit(PB8_EA_HS_TRACKING_NEW_MODE1, ~_BIT4, 0x00);

        // Set Tracking Normal Mode
        ScalerSetBit(PB8_E0_VS_TRACK_EN, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }

    //////////////////////////////////
    // HS Tracking Tracking Setting //
    //////////////////////////////////

    // Set HS Tracking
    ScalerSetBit(PB8_E1_VS_TRACK_MODE, ~_BIT7, _BIT7);

    // Avoid Too Large PE When Stream Clock is Smaller than 20MHz.
    if(pstDpInfo->stDpLinkInfo.ulStreamClockHz < 20000000)
    {
        // PE Clock = VCO Clock div 8
        ScalerSetByte(PB8_DA_MN_TRACKING_DIVS, 0x04);
    }
    else
    {
        // PE Clock = VCO Clock div 4
        ScalerSetByte(PB8_DA_MN_TRACKING_DIVS, 0x02);
    }

    // Firset Set Tracking Period with every line Tracking
    ScalerSetByte(PB8_E3_VS_TRACK1, 0x00);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(enumDpLinkChannelCodingType == _CODING_TYPE_128B132B)
    {
        // DE Only Mode
        if(ScalerDpMacStreamRx1GetDPFRegenMode() == _DPF_MODE_DE_ONLY)
        {
            ulTemp = pstDpInfo->stDpLinkInfo.ulLinkClockHz / 1000;

            if(ulTemp == 0x00)
            {
                return _FALSE;
            }

            // Get Half BS to BS delay (Counted by GDI_CLK) = HBs2BsCount / (1/2 * Link_clk) * GDI_clk / 2
            usHalfBSDelayCnt = ScalerGlobalComputeDwordMulDiv((DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount, (DWORD)_GDIPHY_RX_GDI_CLK_KHZ, ulTemp);

#if(_DP_DE_ONLY_MODE_WITH_FULL_LAST_LINE_SUPPORT == _ON)
            // Enable Full Last Line mode for DE only mode
            ScalerDpMacStreamRx1SetDPFRegenMode(_DPF_MODE_DE_ONLY_FULL_LAST_LINE);

            // Generate de_mod_de_window by cr_be (avoid BS lost case)
            ScalerSetBit(P70_03_DPF_CTRL_3, ~_BIT2, _BIT2);
#else
            // usHttDeonlyMinus = (htotal - (hstart + hwidth)) / pixel mode
            usHttDeonlyMinus = ((pstDpInfo->stDpTimingInfo.usHTotal - (pstDpInfo->stDpTimingInfo.usHWidth + pstDpInfo->stDpTimingInfo.usHStart)) / pstDpInfo->stDpLinkInfo.ucPixelMode);

            // Check if usHttDeonlyMinus is less than Safety factor 10
            if(usHttDeonlyMinus < 10)
            {
                // htt_deonly_minus = usHttDeonlyMinus
                usHttDeonlyMinus = usHttDeonlyMinus;
            }
            else
            {
                // htt_deonly_minus = usHttDeonlyMinus - Safety factor 10
                usHttDeonlyMinus = usHttDeonlyMinus - 10;
            }

            // Set Htt Deonly Minus when deonly_mode = 1, deonly_htt_min_mode = 1 and deonly_full_mode = 0
            ScalerSetByte(P70_3B_DP_HTT_DEONLY_MINUS, usHttDeonlyMinus);
#endif
        }
        else
        {
            // Orginal formula : ulTemp = 2 * pstDpInfo->stDpLinkInfo.ulStreamClockHz / 1000;
            // Simplify formula for overflow issue (when StreamClockHz >= 2147.5MHz)
            ulTemp = pstDpInfo->stDpLinkInfo.ulStreamClockHz / 500;

            if(ulTemp == 0x00)
            {
                return _FALSE;
            }

            // Get Half BS to BS delay (Counted by GDI_CLK) = HTotal / 2 * GDI_CLK(27MHz) / Stream Clock
            usHalfBSDelayCnt = ScalerGlobalComputeDwordMulDiv((DWORD)pstDpInfo->stDpTimingInfo.usHTotal, (DWORD)_GDIPHY_RX_GDI_CLK_KHZ, ulTemp);
        }
    }
    else
#endif
    {
        // DE Only Mode
        if(ScalerDpMacStreamRx1GetDPFRegenMode() == _DPF_MODE_DE_ONLY)
        {
            ulTemp = pstDpInfo->stDpLinkInfo.ulLinkClockHz / 1000;

            if(ulTemp == 0x00)
            {
                return _FALSE;
            }

            // Get Half BS to BS delay (Counted by GDI_CLK) = HBs2BsCount / (1/2 * Link_clk) * GDI_clk / 2
            usHalfBSDelayCnt = ScalerGlobalComputeDwordMulDiv((DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount, (DWORD)_GDIPHY_RX_GDI_CLK_KHZ, ulTemp);

#if(_DP_DE_ONLY_MODE_WITH_FULL_LAST_LINE_SUPPORT == _ON)
            // Enable Full Last Line mode for DE only mode
            ScalerDpMacStreamRx1SetDPFRegenMode(_DPF_MODE_DE_ONLY_FULL_LAST_LINE);

            // Generate de_mod_de_window by cr_be (avoid BS lost case)
            ScalerSetBit(PB8_94_DP_RSV4, ~_BIT0, _BIT0);
#else
            // usHttDeonlyMinus = (htotal - (hstart + hwidth)) / 2
            usHttDeonlyMinus = ((pstDpInfo->stDpTimingInfo.usHTotal - (pstDpInfo->stDpTimingInfo.usHWidth + pstDpInfo->stDpTimingInfo.usHStart)) / 2);

            // Check if usHttDeonlyMinus is less than Safety factor 10
            if(usHttDeonlyMinus < 10)
            {
                // htt_deonly_minus = usHttDeonlyMinus
                usHttDeonlyMinus = usHttDeonlyMinus;
            }
            else
            {
                // htt_deonly_minus = usHttDeonlyMinus - Safety factor 10
                usHttDeonlyMinus = usHttDeonlyMinus - 10;
            }

            // Set Htt Deonly Minus when deonly_mode = 1, deonly_htt_min_mode = 1 and deonly_full_mode = 0
            ScalerSetByte(PB8_95_DP_HTT_DEONLY_MINUS, usHttDeonlyMinus);
#endif
        }
        else
        {
            // Orginal formula : ulTemp = 2 * pstDpInfo->stDpLinkInfo.ulStreamClockHz / 1000;
            // Simplify formula for overflow issue (when StreamClockHz >= 2147.5MHz)
            ulTemp = pstDpInfo->stDpLinkInfo.ulStreamClockHz / 500;

            if(ulTemp == 0x00)
            {
                return _FALSE;
            }

            // Get Half BS to BS delay (Counted by GDI_CLK) = HTotal / 2 * GDI_CLK(27MHz) / Stream Clock
            usHalfBSDelayCnt = ScalerGlobalComputeDwordMulDiv((DWORD)pstDpInfo->stDpTimingInfo.usHTotal, (DWORD)_GDIPHY_RX_GDI_CLK_KHZ, ulTemp);
        }
    }

    // Set Half BS to BS delay For Precision Mode
    ScalerSetBit(PB8_EA_HS_TRACKING_NEW_MODE1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usHalfBSDelayCnt));
    ScalerSetByte(PB8_EB_HS_TRACKING_NEW_MODE2, LOBYTE(usHalfBSDelayCnt));

    DebugMessageDpRx("DP MAC RX1: Half BS2BS", usHalfBSDelayCnt);

    // Only Enable Tracking at Active Region
    ScalerDpMacStreamRx1HSActiveTrackingMode(_DP_HS_TRACKING_FW_MODE);

#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_JUDGE_OOR() == _TRUE)
    {
        // Get 1 Frame Time for Vfreq = 5Hz, unit is ms
        ucOneFrameTime = 250;
    }
    else
#endif
    {
        // Get 1 Frame Time, unit is ms
        ucOneFrameTime = pstDpInfo->stDpLinkInfo.ulVBsToBsCountN / _GDIPHY_RX_GDI_CLK_KHZ + 1;
    }

    DebugMessageDpRx("DP MAC RX1: Loop 1 Frame Time", ucOneFrameTime);

#if((_DP_AUXLESS_ALPM_SUPPORT == _ON) || (_DP_FREESYNC_SUPPORT == _ON))
    if(ScalerDpMacStreamRx1GetDPFRegenMode() == _DPF_MODE_FRAME_SYNC_BE)
    {
        // Disable P Gain Spread
        ScalerDpMacStreamRx1PLLPCodeSpreadCtrl(_OFF, 0);

        // Only Tracking Fast Lock Mode
        ScalerDpMacStreamRx1SetPllTrackingMode(_DP_TRACKING_FAST_LOCK_MODE, ucOneFrameTime);

        // Enable P Gain Spread
        ScalerDpMacStreamRx1PLLPCodeSpreadCtrl(_ON, ucOneFrameTime);
    }
    else
#endif
    {
        // Disable P Gain Spread
        ScalerDpMacStreamRx1PLLPCodeSpreadCtrl(_OFF, 0);

        // 1st Tracking Fast Lock Mode
        ScalerDpMacStreamRx1SetPllTrackingMode(_DP_TRACKING_FAST_LOCK_MODE, ucOneFrameTime);

        // 2nd Tracking Presicion Mode
        ScalerDpMacStreamRx1SetPllTrackingMode(_DP_TRACKING_PRECISION_MODE, ucOneFrameTime);

        // If not Freesync mode, Enable P Gain Spread
#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _FALSE)
#endif
        {
            ScalerDpMacStreamRx1PLLPCodeSpreadCtrl(_ON, ucOneFrameTime);
        }
    }

    // Get How Many Lines Per SSC Period
    // SSC(33khz)'s time to update.
    ucSscLineNumber = (BYTE)((pstDpInfo->stDpLinkInfo.ulStreamClockHz / pstDpInfo->stDpTimingInfo.usHTotal + 11500) / 33000);

    if(ucSscLineNumber > 0)
    {
        ucSscLineNumber--;
    }

    // Set Tracking Period
    ScalerSetByte(PB8_E3_VS_TRACK1, ucSscLineNumber);

    DebugMessageDpRx("DP MAC RX1: Tracking Per Line", ScalerGetByte(PB8_E3_VS_TRACK1));

    // Check Disable Tracking Or Not
    if(ScalerDpMacStreamRx1NoNeedKeepTrackingCheck() == _TRUE)
    {
        // Disable Tracking
        ScalerSetBit(PB8_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);

        DebugMessageDpRx("DP MAC RX1: Disable Tracking After PLL Freq Stable", 0x00);
    }


    /////////////////////////////////////
    // Display Format Generator Enable //
    /////////////////////////////////////

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(enumDpLinkChannelCodingType == _CODING_TYPE_128B132B)
    {
        // Start Generate Display Format
        ScalerSetBit(P70_00_DPF_CTRL_0, ~_BIT7, _BIT7);

        // Polling Vertical BS
        ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, P75_01_DP_VBID, _BIT0, _TRUE);
    }
    else
#endif
    {
        // Start Generate Display Format
        ScalerSetBit(PB8_30_DPF_CTRL_0, ~_BIT7, _BIT7);

        // Polling Vertical BS
        ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, PB9_01_DP_VBID, _BIT0, _TRUE);
    }

    // Delay 1 Frame Time for PG Stable
    ScalerTimerDelayXms(ucOneFrameTime);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Disable Tracking Or Not
// Input Value  : None
// Output Value : _TRUE -> Need Disable Tracking
//                _FALSE -> Cannot Disable Tracking
//--------------------------------------------------
bit ScalerDpMacStreamRx1NoNeedKeepTrackingCheck(void)
{
    // DE Only Mode
    if(ScalerDpMacStreamRx1GetDPFRegenMode() == _DPF_MODE_DE_ONLY)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP NF PLL Setting for PLL Power Off Process
// Input Value  : ulvcoFreq --> VCO Frequency(Hz)
//              : ucNcode --> PLL N Code
//              : ucpllo --> divider o code
//              : ucdivs --> divider s code
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetPLLNfOffProc(DWORD ulPllVcoClockHz, BYTE ucNcode, BYTE ucpllo, BYTE ucdivs)
{
    // Power Off PLL
    ScalerSetBit(PB8_A8_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // Set Rs, Icp
    pData[1] = ScalerDpRxPllRsIcpCalculate(ucNcode);
    ScalerSetByte(PB8_A6_M2PLL_0, pData[1]);

    // Set Vco Band11, Ipi
    if(ulPllVcoClockHz < 400000000)
    {
        pData[1] = 0;
    }
    else if(ulPllVcoClockHz < 500000000)
    {
        pData[1] = 1;
    }
    else if(ulPllVcoClockHz < 600000000)
    {
        pData[1] = 2;
    }
    else
    {
        pData[1] = 3;
    }

    // Set Ipi , VCO Band:11, Disable PI bypass
    ScalerSetBit(PB8_A7_M2PLL_1, ~(_BIT2 | _BIT1 | _BIT0), (pData[1] & 0x03));

    // Set CP Enable, close loop. Set Vc, Set LPF Enable
    ScalerSetBit(PB8_AA_M2PLL_DUMMY, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT0));

    // Set VCO Mode
    ScalerSetBit(PB8_A7_M2PLL_1, ~_BIT7, _BIT7);

    // Set preDiv byPass, Output Div
    ScalerSetBit(PB8_A5_M2PLL_DIVIDER1, ~(_BIT7 | _BIT1 | _BIT0), ucpllo);
    ScalerSetBit(PB8_A2_PLL_OUT_CONTROL, ~(_BIT2 | _BIT1 | _BIT0), ucdivs);
}

//--------------------------------------------------
// Description  : DP NF PLL Setting for PLL Power Off Process
// Input Value  : ucNcode --> PLL N Code
//              : ucFcode_MSB4b --> PLL F Code (MSB 4 bits)
//              : usFcode_LSB16b --> PLL F Code (LSB 16 bits)
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRx1SetPLLNfOnProc(BYTE ucNcode, BYTE ucFcode_MSB4b, WORD usFcode_LSB16b, bit bPllVcoHighFreqStatus)
{
    // PI Control Enable
    ScalerSetBit(PB8_C5_TRACKING_5, ~(_BIT7 | _BIT6), _BIT7);

    // Power On M2PLL
    ScalerSetBit(PB8_A8_M2PLL_CONTROL, ~_BIT0, 0x00);

    // Delay 200us
    // Delay Time us [200,x]
    DELAY_XUS(200);

    // Enable VCO/4 & High VCO frequency
    ScalerSetBit(PB8_A8_M2PLL_CONTROL, ~(_BIT7 | _BIT6), (_BIT7 | (((BYTE)bPllVcoHighFreqStatus) << 6)));

    // Check N code must set to >= 5
    ucNcode = ucNcode - 2;

    if(ucNcode < 5)
    {
        DebugMessageDpRx("DP MAC RX1: PLL N Code is out of Spec", ucNcode);

        ucNcode = 5;

        return _FALSE;
    }

    // Set N[7:0]
    ScalerSetByte(PB8_AD_N_F_CODE_1, ucNcode);

    // Set F[19:16] Code
    ScalerSetByte(PB8_AE_N_F_CODE_2, (ucFcode_MSB4b & 0x0F));

    // Set F[15:8] Code
    ScalerSetByte(PB8_AF_N_F_CODE_3, ((usFcode_LSB16b & 0xFF00) >> 8));

    // Set F[7:0] Code
    ScalerSetByte(PB8_B0_N_F_CODE_4, (usFcode_LSB16b & 0x00FF));

    // Load N.F
    ScalerSetBit(PB8_AC_N_F_CODE_0, ~_BIT0, _BIT0);

    // Power Off M2PLL
    ScalerSetBit(PB8_A8_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // Power On M2PLL
    ScalerSetBit(PB8_A8_M2PLL_CONTROL, ~_BIT0, 0x00);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check VGIP VS bypass for DP
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRx1CheckVgipVsBypass(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        // Get Hstart
        PDATA_WORD(0) = ScalerGetWord(P70_12_MN_DPF_HST_M);

        // Get Vstart
        PDATA_WORD(1) = ScalerGetWord(P70_1A_MN_DPF_VST_M);
    }
    else
#endif
    {
        // Get Hstart
        PDATA_WORD(0) = ScalerGetWord(PB8_43_MN_DPF_HST_M);

        // Get Vstart
        PDATA_WORD(1) = ScalerGetWord(PB8_4B_MN_DPF_VST_M);
    }

    // Check for nVedia 2560x1440@144Hz timing (reduced blanking)
    if((PDATA_WORD(0) < _VGIP_IH_CAPTURE_MIN_VALUE) ||
       (PDATA_WORD(1) <= _VGIP_IV_CAPTURE_MIN_VALUE))
    {
        DebugMessageDpRx("DP MAC RX1: VGIP VS Bypass Mode", PDATA_WORD(0));

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetNoVideoStreamIRQ(bit bEn)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        // VB-ID[3] Change Flag
        ScalerSetBit(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

        // VB-ID[3] Change IRQ
        ScalerSetBit(P75_3B_DP_IRQ_CTRL1, ~_BIT4, ((bEn == _ENABLE) ? _BIT4 : 0x00));
    }
    else
#endif
    {
        // VB-ID[3] Change Flag
        ScalerSetBit(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

        // VB-ID[3] Change IRQ
        ScalerSetBit(PB9_3F_DP_IRQ_CTRL1, ~_BIT4, ((bEn == _ENABLE) ? _BIT4 : 0x00));
    }
}

//--------------------------------------------------
// Description  : Disable DP Fifo Under/OverFlow IRQ
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DisableNoVideoStreamIRQ(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    // VB-ID[3] Change IRQ
    ScalerSetBit(P75_3B_DP_IRQ_CTRL1, ~_BIT4, 0x00);

    // VB-ID[3] Change Flag
    ScalerSetBit(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);
#endif
    // VB-ID[3] Change IRQ
    ScalerSetBit(PB9_3F_DP_IRQ_CTRL1, ~_BIT4, 0x00);

    // VB-ID[3] Change Flag
    ScalerSetBit(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

    CLR_DP_MAC_STREAM_RX1_VBID3_CHANGED();
}

//--------------------------------------------------
// Description  : Check Rx Input Pixel Mode
// Input Value  : None
// Output Value : One Pixel or Two Pixel Mode
//--------------------------------------------------
EnumDpRxMacPixelMode ScalerDpMacStreamRx1InputPixelMode(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
#if(_DP_MAC_RX_128B132B_FOUR_PIXEL_MODE_SUPPORT == _ON)
        if(ScalerGetBit(P70_02_DPF_CTRL_2, (_BIT1 | _BIT0)) == _BIT1)
        {
            return _DP_RX_MAC_FOUR_PIXEL_MODE;
        }
        else
#endif
        {
            if(ScalerGetBit(P70_02_DPF_CTRL_2, (_BIT1 | _BIT0)) == _BIT0)
            {
                return _DP_RX_MAC_TWO_PIXEL_MODE;
            }
            else if(ScalerGetBit(P70_02_DPF_CTRL_2, (_BIT1 | _BIT0)) == 0x00)
            {
                return _DP_RX_MAC_ONE_PIXEL_MODE;
            }
        }
    }
    else
#endif
    {
        if(ScalerGetBit(PB8_1F_SOURCE_SEL_4, _BIT0) == _BIT0)
        {
            return _DP_RX_MAC_TWO_PIXEL_MODE;
        }
        else
        {
            return _DP_RX_MAC_ONE_PIXEL_MODE;
        }
    }

    return _DP_RX_MAC_PIXEL_MODE_NONE;
}

//--------------------------------------------------
// Description  : Dp Rx Interlace Mode Check
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRx1InterlaceModeConfig(BYTE ucInterlaceReference)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        if(ucInterlaceReference == _REF_VBID)
        {
            if(ScalerGetBit(P70_06_INTERLACE_CTRL_0, (_BIT7 | _BIT6)) == _BIT7)
            {
                return _ENABLE;
            }
        }
        else if(ucInterlaceReference == _REF_BS_COUNTER)
        {
            if(ScalerGetBit(P70_06_INTERLACE_CTRL_0, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
            {
                return _ENABLE;
            }
        }
    }
    else
#endif
    {
        if(ucInterlaceReference == _REF_VBID)
        {
            if(ScalerGetBit(PB8_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == _BIT7)
            {
                return _ENABLE;
            }
        }
        else if(ucInterlaceReference == _REF_BS_COUNTER)
        {
            if(ScalerGetBit(PB8_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
            {
                return _ENABLE;
            }
        }
    }

    return _DISABLE;
}

//--------------------------------------------------
// Description  : Update timing info HS/VS polarity
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1Polarity(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        // Pop out DP polarity
        ScalerSetBit(P75_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT5));
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1HSP = (bit)(ScalerGetBit(P75_16_MSA_HSW_0, _BIT7) == 0x00);
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1VSP = (bit)(ScalerGetBit(P75_1E_MSA_VSW_0, _BIT7) == 0x00);
    }
    else
#endif
    {
        // Pop out DP polarity
        ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT5));
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1HSP = (bit)(ScalerGetBit(PB9_0E_MSA_HSW_0, _BIT7) == 0x00);
        g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1VSP = (bit)(ScalerGetBit(PB9_18_MSA_VSW_0, _BIT7) == 0x00);
    }
}

//--------------------------------------------------
// Description  : Keep Measure Enable Check
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRx1KeepMeasureEnableCheck(void)
{
#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
    {
        return _TRUE;
    }
#endif

    if(ScalerDpMacStreamRx1GetDPFRegenMode() == _DPF_MODE_FRAME_SYNC_BE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Video/DisplayFormat/Measure relative Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1MacSetting(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        if(ScalerDpMacStreamRx1KeepMeasureEnableCheck() == _TRUE)
        {
            // Measurement Enable for On-Line VFreq check
            ScalerSetBit(P70_40_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), _BIT7);
        }

        // RGB Output
        ScalerSetBit(P70_01_DPF_CTRL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    }
    else
#endif
    {
        if(ScalerDpMacStreamRx1KeepMeasureEnableCheck() == _TRUE)
        {
            // Measurement Enable for On-Line VFreq check
            ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), _BIT7);
        }

        // RGB Output
        ScalerSetBit(PB8_31_DP_OUTPUT_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    }
}

//--------------------------------------------------
// Description  : Audio/Sdp relative Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpSetting(void)
{
#if(_AUDIO_SUPPORT == _ON)
    // Enable Audio Channel
    ScalerDpAudioRx1AudioEnableControl(_ENABLE);
#endif

#if((_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    // Enable RSV0 Ram Receive IRQ
    ScalerDpMacStreamRx1SdpIrqEnable(_DP_SDP_BUFF_RSV0, _ENABLE);
#endif

    ScalerDpMacStreamRx1SdpDataDetect();

#if(_DP_FREESYNC_SUPPORT == _ON)
    ScalerDpMacStreamRx1GetSPDVfreqMaxMin();
#endif
}

//--------------------------------------------------
// Description  : Get VBID Information
// Input Value  : VBID Content
// Output Value : VBID Information
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetVbidInfo(EnumDpVbidInfo enumDpVbidInfo)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1GetVbidInfo_128b132b(enumDpVbidInfo);
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1GetVbidInfo_8b10b(enumDpVbidInfo);
    }
}

//--------------------------------------------------
// Description  : Get MSA Information
// Input Value  : EnumDpRxMsaType
// Output Value : UnionDpRxMsaValue
//--------------------------------------------------
UnionDpRxMsaValue ScalerDpMacStreamRx1GetMsaInfo(EnumDpRxMsaType enumDpRxMsaType)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1GetMsaInfo_128b132b(enumDpRxMsaType);
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1GetMsaInfo_8b10b(enumDpRxMsaType);
    }
}

//--------------------------------------------------
// Description  : Sdp Dtect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpDataDetect(void)
{
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
    ScalerDpMacStreamRx1SdpPacketCheck(_DP_SDP_TYPE_INFOFRAME_SPD);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    ScalerDpMacStreamRx1SdpPacketCheck(_DP_SDP_TYPE_ADAPTIVESYNC);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
    ScalerDpMacStreamRx1SdpPacketCheck(_DP_SDP_TYPE_INFOFRAME_HDR);
#endif

#if((_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    ScalerDpMacStreamRx1SdpPacketCheck(_DP_SDP_TYPE_INFOFRAME_VENDOR_SPEC);
#endif

#if(_AUDIO_SUPPORT == _ON)
    ScalerDpMacStreamRx1SdpPacketCheck(_DP_SDP_TYPE_INFOFRAME_AUDIO);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    ScalerDpMacStreamRx1SdpPacketCheck(_DP_SDP_TYPE_PPS);
#endif
}

//--------------------------------------------------
// Description  : Sdp Packet Check
// Input Value  : Dp Sdp Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpPacketCheck(EnumDpSdpType enumDpSdpType)
{
#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
#endif

    switch(enumDpSdpType)
    {
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _DP_SDP_TYPE_INFOFRAME_SPD:

            CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE_EVENT();

            if(GET_DP_MAC_STREAM_RX1_SPD_IFNOFRAME_DETECTING() == _FALSE)
            {
                SET_DP_MAC_STREAM_RX1_SPD_IFNOFRAME_DETECTING();

                ScalerDpMacStreamRx1SdpRevDetect(_DP_SDP_TYPE_INFOFRAME_SPD);

                if(GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE() == _SDP_STATE_RECEIVED)
                {
                    ScalerDpMacStreamRx1SdpChgDetect(_DP_SDP_TYPE_INFOFRAME_SPD);

                    // HB3[7:2]: Infoframe Version
                    if(GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_VERSION() < _INFOFRAME_SDP_VERSION_1_3)
                    {
                        ScalerDpMacStreamRx1SpdInfoDataRemappingDisable();
                    }
                }

                ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_SPD_INFOFRAME_DETECTING_DONE);
            }

            break;
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        case _DP_SDP_TYPE_ADAPTIVESYNC:

            CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE_EVENT();

            if(GET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_DETECTING() == _FALSE)
            {
                SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_DETECTING();

                ScalerDpMacStreamRx1SdpRevDetect(_DP_SDP_TYPE_ADAPTIVESYNC);

                if(GET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_RECEIVED_STATE() == _SDP_STATE_RECEIVED)
                {
                    ScalerDpMacStreamRx1SdpChgDetect(_DP_SDP_TYPE_ADAPTIVESYNC);
                }

                ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_ADAPTIVESYNC_SDP_DETECTING_DONE);
            }

            break;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_HDR:

            CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE_EVENT();

            if(GET_DP_MAC_STREAM_RX1_HDR_IFNOFRAME_DETECTING() == _FALSE)
            {
                SET_DP_MAC_STREAM_RX1_HDR_IFNOFRAME_DETECTING();

                ScalerDpMacStreamRx1SdpRevDetect(_DP_SDP_TYPE_INFOFRAME_HDR);

                if(GET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_RECEIVED_STATE() == _SDP_STATE_RECEIVED)
                {
                    ScalerDpMacStreamRx1SdpChgDetect(_DP_SDP_TYPE_INFOFRAME_HDR);

                    // HB3[7:2]: Infoframe Version
                    if(GET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_VERSION() < _INFOFRAME_SDP_VERSION_1_3)
                    {
                        ScalerDpMacStreamRx1HdrInfoDataRemappingDisable();
                    }
                }

                ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_HDR_INFOFRAME_DETECTING_DONE);
            }

            break;
#endif

        case _DP_SDP_TYPE_INFOFRAME_VENDOR_SPEC:

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            if((ScalerDMGetMetadataSupport(enumInputPort) == _TRUE) && (GET_DP_MAC_STREAM_RX1_DM_VSIF_DETECTING() == _FALSE))
            {
                if(GET_DP_MAC_STREAM_RX1_DM_VSIF_RECEIVED_STATE() == _SDP_STATE_RECEIVED)
                {
                    CLR_DP_MAC_STREAM_RX1_DM_VSIF_RECEIVED_STATE();
                }
                else
                {
                    // Case for DM VSIF no packet
                }

                SET_DP_MAC_STREAM_RX1_DM_VSIF_DETECTING();
                ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_DM_VSIF_DETECTING_DONE);
            }
            else
#endif
#endif
            {
#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
                if((GET_ADVANCED_HDR10_METADATA_SUPPORT() == _ADVANCED_HDR10_SUPPORT_ON) && (GET_ADVANCED_HDR10_INITIAL_READY() == _TRUE) && (GET_DP_MAC_STREAM_RX1_ADVANCED_HDR10_DETECTING() == _FALSE))
                {
                    if(GET_DP_MAC_STREAM_RX1_ADVANCED_HDR10_RECEIVED_STATE() == _SDP_STATE_RECEIVED)
                    {
                        CLR_DP_MAC_STREAM_RX1_ADVANCED_HDR10_RECEIVED_STATE();
                    }
                    else
                    {
                        // Clr HDR10+ data strucr if no received
                        CLR_ADVANCED_HDR10_INFO_DATA();
                        CLR_ADVANCED_HDR10_BACK_UP_INFO_DATA();
                    }

                    SET_DP_MAC_STREAM_RX1_ADVANCED_HDR10_DETECTING();
                    ScalerTimerActiveTimerEvent(GET_ADVANCED_HDR10_METADATA_DETECT_TIME(), _SCALER_TIMER_EVENT_DP_RX1_ADVANCED_HDR10_DETECTING_DONE);
                }
#endif
            }

            break;

#if(_AUDIO_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_AUDIO:

            CLR_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_CHANGE_EVENT();

            if(GET_DP_MAC_STREAM_RX1_AUDIO_IFNOFRAME_DETECTING() == _FALSE)
            {
                SET_DP_MAC_STREAM_RX1_AUDIO_IFNOFRAME_DETECTING();

                ScalerDpMacStreamRx1SdpRevDetect(_DP_SDP_TYPE_INFOFRAME_AUDIO);

                if(GET_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_RECEIVED_STATE() == _SDP_STATE_RECEIVED)
                {
                    ScalerDpMacStreamRx1SdpChgDetect(_DP_SDP_TYPE_INFOFRAME_AUDIO);
                }

                ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_AUDIO_INFOFRAME_DETECTING_DONE);
            }

            break;
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _DP_SDP_TYPE_PPS:

            if(GET_DP_MAC_STREAM_RX1_PPS_SDP_DETECTING() == _FALSE)
            {
                SET_DP_MAC_STREAM_RX1_PPS_SDP_DETECTING();

                ScalerDpMacStreamRx1SdpRevDetect(_DP_SDP_TYPE_PPS);

                if(GET_DP_MAC_STREAM_RX1_PPS_SDP_RECEIVED_STATE() == _SDP_STATE_RECEIVED)
                {
                    ScalerDpMacStreamRx1SdpChgDetect(_DP_SDP_TYPE_PPS);

                    ScalerDpMacStreamRx1GetPpsSdpInfo();
                }

                ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_PPS_SDP_INFOFRAME_DETECTING_DONE);
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Sdp Received
// Input Value  : Dp Sdp Type
// Output Value : Received Flag
//--------------------------------------------------
EnumDpMacRxSdpReceiveStates ScalerDpMacStreamRx1GetSdpReceived(EnumDpSdpType enumDpSdpType)
{
    switch(enumDpSdpType)
    {
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _DP_SDP_TYPE_INFOFRAME_SPD:

            return GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE();

            break;
#endif
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        case _DP_SDP_TYPE_ADAPTIVESYNC:

            return GET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_RECEIVED_STATE();

            break;
#endif
#if(_DP_HDR10_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_HDR:

            return GET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_RECEIVED_STATE();

            break;
#endif
#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_VENDOR_SPEC:

            return GET_DP_MAC_STREAM_RX1_ADVANCED_HDR10_RECEIVED_STATE();

            break;
#endif
#if(_AUDIO_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_AUDIO:

            return GET_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_RECEIVED_STATE();

            break;
#endif
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _DP_SDP_TYPE_PPS:

            return GET_DP_MAC_STREAM_RX1_PPS_SDP_RECEIVED_STATE();

            break;
#endif
        default:
            break;
    }

    return _SDP_STATE_NOT_RECEIVED;
}

//--------------------------------------------------
// Description  : Get Sdp Change Event
// Input Value  : Dp Sdp Type
// Output Value : Change Event
//--------------------------------------------------
EnumDpMacRxSdpChangeEvent ScalerDpMacStreamRx1GetSdpChangeEvent(EnumDpSdpType enumDpSdpType)
{
    switch(enumDpSdpType)
    {
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _DP_SDP_TYPE_INFOFRAME_SPD:

            return GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE_EVENT();

            break;
#endif
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        case _DP_SDP_TYPE_ADAPTIVESYNC:

            return GET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE_EVENT();

            break;
#endif
#if(_DP_HDR10_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_HDR:

            return GET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE_EVENT();

            break;
#endif
#if(_AUDIO_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_AUDIO:

            return GET_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_CHANGE_EVENT();

            break;
#endif
        default:
            break;
    }

    return _SDP_EVENT_NONE;
}

//--------------------------------------------------
// Description  : Get Sdp Changed
// Input Value  : Dp Sdp Type
// Output Value : Chg Flag
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetSdpChanged(EnumDpSdpType enumDpSdpType)
{
    switch(enumDpSdpType)
    {
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _DP_SDP_TYPE_INFOFRAME_SPD:

            return GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE();

            break;
#endif
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        case _DP_SDP_TYPE_ADAPTIVESYNC:

            return GET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE();

            break;
#endif
#if(_DP_HDR10_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_HDR:

            return GET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE();

            break;
#endif
#if(_AUDIO_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_AUDIO:

            return GET_DP_MAC_STREAM_RX1_AUDIO_INFO_FRAME_CHANGE();

            break;
#endif
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _DP_SDP_TYPE_PPS:

            return GET_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE();

            break;
#endif
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Sdp Packet Data
// Input Value  : Dp Sdp Ram Index & Sdp Buff
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1GetSdpPktData(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength)
{
    BYTE ucIndex = 0;

    BYTE pucTmepData1[_HW_DP_SDP_PAYLOAD_LENGTH];

    WORD usInfoFrameAddrByte = 0x00;
    WORD usInfoFrameDataByte = 0x00;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
#endif

    switch(ScalerDpMacStreamRxGetSdpBufferType(enumDpSdpType))
    {
        case _DP_SDP_BUFF_SPD:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usInfoFrameAddrByte = P75_2E_DP_SDP_SPD_ADR;
                usInfoFrameDataByte = P75_2F_DP_SDP_SPD_DAT;
            }
            else
#endif
            {
                usInfoFrameAddrByte = PB9_32_DP_SDP_SPD_ADR;
                usInfoFrameDataByte = PB9_33_DP_SDP_SPD_DAT;
            }

            break;

        case _DP_SDP_BUFF_HDR:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usInfoFrameAddrByte = P75_35_DP_SDP_HDR_INFO_ADR;
                usInfoFrameDataByte = P75_36_DP_SDP_HDR_INFO_DAT;
            }
            else
#endif
            {
                usInfoFrameAddrByte = PB9_39_DP_SDP_HDR_INFO_ADR;
                usInfoFrameDataByte = PB9_3A_DP_SDP_HDR_INFO_DAT;
            }

            break;

        case _DP_SDP_BUFF_ISRC:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usInfoFrameAddrByte = P75_E4_SDP_ISRC_ADR;
                usInfoFrameDataByte = P75_E5_SDP_ISRC_DATA;
            }
            else
#endif
            {
                usInfoFrameAddrByte = PB9_E4_SDP_ISRC_ADR;
                usInfoFrameDataByte = PB9_E5_SDP_ISRC_DATA;
            }

            break;

        case _DP_SDP_BUFF_VSC:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usInfoFrameAddrByte = P75_47_VSC7;
                usInfoFrameDataByte = P75_48_VSC8;
            }
            else
#endif
            {
                usInfoFrameAddrByte = PB9_47_VSC7;
                usInfoFrameDataByte = PB9_48_VSC8;
            }

            break;

        case _DP_SDP_BUFF_RSV0:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usInfoFrameAddrByte = P75_F4_DP_SDP_RSV0_ADR;
                usInfoFrameDataByte = P75_F5_DP_SDP_RSV0_DAT;
            }
            else
#endif
            {
                usInfoFrameAddrByte = PB9_F4_DP_SDP_RSV0_ADR;
                usInfoFrameDataByte = PB9_F5_DP_SDP_RSV0_DAT;
            }

            break;

        case _DP_SDP_BUFF_ADAPTIVESYNC:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usInfoFrameAddrByte = P75_26_DP_SDP_ADP_SYNC_ADDR;
                usInfoFrameDataByte = P75_27_DP_SDP_ADP_SYNC_DAT;
            }
            else
#endif
            {
                usInfoFrameAddrByte = PB9_4D_DP_LR_SEL;
                usInfoFrameDataByte = PB9_4C_DP_SDP_ADP_SYNC_DAT;
            }

            break;

        default:
            break;
    }

    if((usInfoFrameAddrByte != 0x00) && (usInfoFrameDataByte != 0x00))
    {
        ucLength = ((ucLength + ucOffset) > _HW_DP_SDP_PAYLOAD_LENGTH) ? (_HW_DP_SDP_PAYLOAD_LENGTH - ucOffset) : ucLength;

        while(ucIndex < ucLength)
        {
            ScalerSetByte(usInfoFrameAddrByte, (ucOffset + ucIndex));
            pucTmepData1[ucIndex] = ScalerGetByte(usInfoFrameDataByte);

            ucIndex ++;
        }

        memcpy(pucSdpData, pucTmepData1, ucLength);
    }
}

//--------------------------------------------------
// Description  : Get Spd Infoframe HB3
// Input Value  : Dp Sdp Type
// Output Value : HB3
//--------------------------------------------------
BYTE ScalerDpMacStreamRx1GetSdpInfoHB3(EnumDpSdpType enumDpSdpType)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    enumInputPort = enumInputPort;

    switch(enumDpSdpType)
    {
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _DP_SDP_TYPE_INFOFRAME_SPD:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return (ScalerGetByte(P75_2A_DP_SDP_SPD_HB3));
            }
            else
#endif
            {
                return (ScalerGetByte(PB9_2E_DP_SDP_SPD_HB3));
            }
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        case _DP_SDP_TYPE_ADAPTIVESYNC:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return (ScalerGetByte(P75_23_DP_SDP_ADP_SYNC_HB3));
            }
            else
#endif
            {
                return (ScalerGetByte(PB9_5F_DP_SDP_ADP_SYNC_HB3));
            }
#endif

#if(_DP_HDR10_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_HDR:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return (ScalerGetByte(P75_32_DP_SDP_HDR_INFO_HB3));
            }
            else
#endif
            {
                return (ScalerGetByte(PB9_36_DP_SDP_HDR_INFO_HB3));
            }
#endif

#if((_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
        case _DP_SDP_TYPE_INFOFRAME_VENDOR_SPEC:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return (ScalerGetByte(P75_F2_DP_SDP_RSV0_HB3));
            }
            else
#endif
            {
                return (ScalerGetByte(PB9_F2_DP_SDP_RSV0_HB3));
            }
#endif

        default:
            break;
    }

    return 0x00;
}

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set SDP Meta Sram Rcv Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetSdpMetaSramRcvInitial(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#if(((_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON) && (_DP_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    // Set HB1 = 0x20 For HDR10+ and Dolby VSIF
    ScalerDpMacStreamRx1SetSdpMetaSramRcvMode_128b132b(_DP_SDP_META_0, _DP_SDP_TYPE_VSC_EXT_VESA, _DP_SDP_META_RCV_CHAIN);
#endif

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
    // Meta Sram Reset Mode: FW mode
    ScalerSetBit(P7E_E0_META_SRAM_CTRL, ~(_BIT7 | _BIT6 | _BIT2 | _BIT0), _BIT7);
#else
    // Meta Sram Reset Mode: HW mode
    ScalerSetBit(P7E_E0_META_SRAM_CTRL, ~(_BIT7 | _BIT6 | _BIT2 | _BIT0), 0x00);
#endif
#endif

#if(((_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON) && (_DP_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    // Set HB1 = 0x20 For HDR10+ and Dolby VSIF
    ScalerDpMacStreamRx1SetSdpMetaSramRcvMode_8b10b(_DP_SDP_META_0, _DP_SDP_TYPE_VSC_EXT_VESA, _DP_SDP_META_RCV_CHAIN);
#endif

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
    // Meta Sram Reset Mode: FW mode
    ScalerSetBit(P26_E0_META_SRAM_CTRL, ~(_BIT7 | _BIT6 | _BIT2 | _BIT0), _BIT7);
#else
    // Meta Sram Reset Mode: HW mode
    ScalerSetBit(P26_E0_META_SRAM_CTRL, ~(_BIT7 | _BIT6 | _BIT2 | _BIT0), 0x00);
#endif
}

//--------------------------------------------------
// Description  : Set SDP Meta Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpMetaSramReset(void)
{
#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
    ScalerDpMacStreamRx1Set1stBeIrqEnable_8b10b(_DISABLE);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacStreamRx1Set1stBeIrqEnable_128b132b(_DISABLE);
#endif
#endif

    // Reset Meta Sram
    ScalerSetBit_EXINT(P26_E0_META_SRAM_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT0), _BIT6);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerSetBit_EXINT(P7E_E0_META_SRAM_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT0), _BIT6);
#endif
}
#endif

//--------------------------------------------------
// Description  : Cts Fifo Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1CtsFifoReset(void)
{
    // Must Be Reset After Link Clk Stable, Until DPF Enable
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerSetBit(P70_02_DPF_CTRL_2, ~(_BIT7 | _BIT3 | _BIT2), _BIT3);
    ScalerSetBit(P70_02_DPF_CTRL_2, ~(_BIT7 | _BIT3 | _BIT2), 0x00);
#endif

    ScalerSetBit(PB8_1F_SOURCE_SEL_4, ~(_BIT7 | _BIT2 | _BIT1), _BIT2);
    ScalerSetBit(PB8_1F_SOURCE_SEL_4, ~(_BIT7 | _BIT2 | _BIT1), 0x00);
}

//--------------------------------------------------
// Description  : VBIOS MSA Check
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
bit ScalerDpMacStreamRx1VbiosMsaCheck(void)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Nvid
    pData[0] = ScalerGetByte(PB9_1D_MSA_NVID_0);
    pData[1] = ScalerGetByte(PB9_1E_MSA_NVID_1);
    pData[2] = ScalerGetByte(PB9_1F_MSA_NVID_2);

    // Get Hactive
    PDATA_WORD(2) = ScalerGetWord(PB9_0C_MSA_HWD_0);

    // Get Vactive
    PDATA_WORD(3) = ScalerGetWord(PB9_16_MSA_VHT_0);

    // Get Hstart
    PDATA_WORD(4) = ScalerGetWord(PB9_0A_MSA_HST_0);

    // Get Vstart
    PDATA_WORD(5) = ScalerGetWord(PB9_14_MSA_VST_0);

    if(((((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0)) != 0x00) &&
       (PDATA_WORD(2) != 0x00) && (PDATA_WORD(3) != 0x00) && (PDATA_WORD(4) != 0x00) && (PDATA_WORD(5) != 0x00) &&
       (PDATA_WORD(2) > PDATA_WORD(4)) && (PDATA_WORD(3) > PDATA_WORD(5)))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Display Format Regen Mode
// Input Value  : enumInputPort --> Source Search Port
// Output Value : DPF Regen Mode
//--------------------------------------------------
EnumDpMacRxDPFRegenMode ScalerDpMacStreamRx1GetDPFRegenMode(void)
{
    WORD usDpfModeRegAddr = 0x00;
    EnumDpMacRxDPFRegenMode enumDpMacRxDPFRegenMode = _DPF_MODE_NONE;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        usDpfModeRegAddr = P70_00_DPF_CTRL_0;
    }
    else
#endif
    {
        usDpfModeRegAddr = PB8_30_DPF_CTRL_0;
    }

    switch(ScalerGetBit(usDpfModeRegAddr, (_BIT5 | _BIT4)))
    {
        default:
        case (_BIT4):

            if(ScalerGetBit(usDpfModeRegAddr, _BIT6) == _BIT6)
            {
                enumDpMacRxDPFRegenMode = _DPF_MODE_DE_ONLY_FULL_LAST_LINE;
            }
            else
            {
                enumDpMacRxDPFRegenMode = _DPF_MODE_DE_ONLY;
            }

            break;

        case 0x00:

            enumDpMacRxDPFRegenMode = _DPF_MODE_FULL_LAST_LINE;

            break;

        case (_BIT5):

            if(ScalerGetBit(usDpfModeRegAddr, _BIT3) == _BIT3)
            {
                enumDpMacRxDPFRegenMode = _DPF_MODE_FRAME_SYNC_BE;
            }
            else
            {
                enumDpMacRxDPFRegenMode = _DPF_MODE_FRAME_SYNC;
            }

            break;
    }

    return enumDpMacRxDPFRegenMode;
}

//--------------------------------------------------
// Description  : Set Display Format Regen Mode
// Input Value  : EnumDpMacRxDPFRegenMode
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetDPFRegenMode(EnumDpMacRxDPFRegenMode enumDpMacRxDPFRegenMode)
{
    WORD usDpfModeRegAddr = PB8_30_DPF_CTRL_0;
    BYTE ucDpfRegBitFiledSetting = 0x00;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        usDpfModeRegAddr = P70_00_DPF_CTRL_0;
    }
    else
#endif
    {
        usDpfModeRegAddr = PB8_30_DPF_CTRL_0;
    }

    switch(enumDpMacRxDPFRegenMode)
    {
        case _DPF_MODE_DE_ONLY:

            ucDpfRegBitFiledSetting = _BIT4;

            break;

        case _DPF_MODE_FULL_LAST_LINE:

            ucDpfRegBitFiledSetting = 0x00;

            break;

        case _DPF_MODE_DE_ONLY_FULL_LAST_LINE:

            ucDpfRegBitFiledSetting = (_BIT6 | _BIT4);

            break;

        case _DPF_MODE_FRAME_SYNC:

            ucDpfRegBitFiledSetting = _BIT5;

            break;

        case _DPF_MODE_FRAME_SYNC_BE:

            ucDpfRegBitFiledSetting = (_BIT5 | _BIT3);

            break;

        default:
            break;
    }

    ScalerSetBit(usDpfModeRegAddr, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), ucDpfRegBitFiledSetting);
}

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Spd Infoframe Detecting Done
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetSpdInfoDetectingDone(void)
{
    CLR_DP_MAC_STREAM_RX1_SPD_IFNOFRAME_DETECTING();
}

//--------------------------------------------------
// Description  : Set Spd Data Remapping Enable
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SpdInfoDataRemappingDisable(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerSetBit(P75_2B_DP_SDP_SPD_CTRL, ~(_BIT6 | _BIT4), 0x00);
#endif
    ScalerSetBit(PB9_2F_DP_SDP_SPD_CTRL, ~(_BIT6 | _BIT4), 0x00);
}
#endif

#if((_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Mac Tx DSC Pass-Through Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscStatusReset(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacStreamRx1DscStatusReset_128b132b();
#endif
    ScalerDpMacStreamRx1DscStatusReset_8b10b();
}

//--------------------------------------------------
// Description  : DP Mac Tx DSC Pass-Through Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscInitial(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Enable DP Mac Pps Receive Ctrl
    ScalerSetBit(P75_E7_DP_MAC_PPS_DYN_MDATA_CTRL, ~(_BIT7 | _BIT6 | _BIT4), _BIT7);

    // Pps Read Out Config Address
    ScalerSetByte(P7E_AC_DP_PPS_RO_CONFIG_ADDR_0, 0x05);
#endif

    // Enable DP Mac Pps Receive Ctrl
    ScalerSetBit(PB9_E7_DP_MAC_PPS_DYN_MDATA_CTRL, ~(_BIT7 | _BIT6 | _BIT4), _BIT7);

    // Pps Read Out Config Address
    ScalerSetByte(P26_AC_DP_PPS_RO_CONFIG_ADDR_0, 0x05);

    ScalerDpMacStreamRx1DscStatusReset();

    ScalerDpMacStreamRx1SetSdpInitStatus(_DP_SDP_BUFF_PPS);
}
#endif

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Check
// Input Value  : enumInputPort
// Output Value : False --> CompressionStream_Flag VB-ID[6] Changed and Video Stream without Compression
//--------------------------------------------------
bit ScalerDpMacStreamRx1DscStreamCheck(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1GetVbidInfo_128b132b(_DP_VBID_DSC_STREAM);
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1GetVbidInfo_8b10b(_DP_VBID_DSC_STREAM);
    }
}

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Pps Sdp Infoframe Detecting Done
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetPpsSdpInfoDetectingDone(void)
{
    CLR_DP_MAC_STREAM_RX1_PPS_SDP_DETECTING();
}

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Change Check
// Input Value  : None
// Output Value : False --> CompressionStream_Flag VB-ID[6] Changed and Video Stream without Compression
//--------------------------------------------------
bit ScalerDpMacStreamRx1DscStreamChangeCheck(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1DscStreamChangeCheck_128b132b();
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1DscStreamChangeCheck_8b10b();
    }
}
#endif

#if(_DP_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Hdr Infoframe Detecting Done
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetHdrInfoDetectingDone(void)
{
    CLR_DP_MAC_STREAM_RX1_HDR_IFNOFRAME_DETECTING();
}

//--------------------------------------------------
// Description  : Set Hdr Infoframe Remapping Diable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1HdrInfoDataRemappingDisable(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerSetBit(P75_33_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT4), 0x00);
#endif
    ScalerSetBit(PB9_37_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT4), 0x00);
}
#endif

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Audio Infoframe Detecting Done
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetAudioInfoDetectingDone(void)
{
    CLR_DP_MAC_STREAM_RX1_AUDIO_IFNOFRAME_DETECTING();
}
#endif

#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Hdr Infoframe Detecting Done
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetAdvancedHdr10InfoDetectingDone(void)
{
    CLR_DP_MAC_STREAM_RX1_ADVANCED_HDR10_DETECTING();
}
#endif

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DM VSIF Infoframe Detecting Done
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetDMVsifInfoDetectingDone(void)
{
    CLR_DP_MAC_STREAM_RX1_DM_VSIF_DETECTING();
}
#endif

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP MAC Rx1 DSC Setting
// Input Value  : None
// Output Value : None
//------------------------------------------------
void ScalerDpMacStreamRx1DscSetting(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        SET_DP_MAC_STREAM_RX1_DSC_SUPPORT_128B132B();

        ScalerSetBit(PB8_A3_PLL_IN_CONTROL, ~_BIT2, _BIT2);
    }
    else
#endif
    {
        SET_DP_MAC_STREAM_RX1_DSC_SUPPORT_8B10B();

        ScalerSetBit(PB8_A3_PLL_IN_CONTROL, ~_BIT2, 0x00);
    }
}

//--------------------------------------------------
// Description  : DP MAC Rx1 Get DSC Reorder
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetDscReorder(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return GET_DP_MAC_STREAM_RX1_DSC_SUPPORT_128B132B();
    }
    else
#endif
    {
        return GET_DP_MAC_STREAM_RX1_DSC_SUPPORT_8B10B();
    }
}

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Watch Dog
// Input Value  : enumInputPort, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscSetStreamWD(EnumInputPort enumInputPort, bit bEnable)
{
    enumInputPort = enumInputPort;

    if(bEnable == _ENABLE)
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
        {
            ScalerDpMacStreamRx1DscSetStreamWD_128b132b(_ENABLE);
        }
        else
#endif
        {
            ScalerDpMacStreamRx1DscSetStreamWD_8b10b(_ENABLE);
        }
    }
    else
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerDpMacStreamRx1DscSetStreamWD_128b132b(_DISABLE);
#endif
        ScalerDpMacStreamRx1DscSetStreamWD_8b10b(_DISABLE);
    }
}

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] IRQ
// Input Value  : enumInputPort, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscSetStreamIRQ(EnumInputPort enumInputPort, bit bEnable)
{
    enumInputPort = enumInputPort;

    if(bEnable == _ENABLE)
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
        {
            ScalerDpMacStreamRx1DscSetStreamIRQ_128b132b(_ENABLE);
        }
        else
#endif
        {
            ScalerDpMacStreamRx1DscSetStreamIRQ_8b10b(_ENABLE);
        }
    }
    else
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerDpMacStreamRx1DscSetStreamIRQ_128b132b(_DISABLE);
#endif
        ScalerDpMacStreamRx1DscSetStreamIRQ_8b10b(_DISABLE);
    }
}

//--------------------------------------------------
// Description  : DP DSC Chunk Length Check
// Input Value  : enumInputPort, PPS Chunk Length, PPS Slice Count
// Output Value : FALSE => Measure Check Fail
//--------------------------------------------------
bit ScalerDpMacStreamRx1DscChunkLengthCheck(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt)
{
    enumInputPort = enumInputPort;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1DscChunkLengthCheck_128b132b(enumInputPort, usDscPpsChunkLength, ucDscPpsSliceCnt);
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1DscChunkLengthCheck_8b10b(enumInputPort, usDscPpsChunkLength, ucDscPpsSliceCnt);
    }
}
#endif

//--------------------------------------------------
// Description  : Get Display Format Information
// Input Value  : Display Format Content
// Output Value : Display Format Information
//--------------------------------------------------
WORD ScalerDpMacStreamRx1GetDisplayFormat(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1GetDisplayFormat_128b132b(enumDpDisplayFormatInfo);
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1GetDisplayFormat_8b10b(enumDpDisplayFormatInfo);
    }
}

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
DWORD ScalerDpMacStreamRx1GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    BYTE pucAmdSpdData[_HW_DP_SDP_PAYLOAD_LENGTH] = {0};
    WORD usFreesyncVfreqmax = 0;
    WORD usFreesyncVfreqmin = 0;
    DWORD ulTargetOutputPixelRate = 0;
    WORD usAmdVfreqMaxBit = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDrrGetAmdVsdbVer(enumInputPort) < _AMD_VER3)
    {
        usAmdVfreqMaxBit = _8_BIT;
    }
    else
    {
        usAmdVfreqMaxBit = _10_BIT;
    }

    ScalerDpMacStreamRx1GetSdpPktData(_DP_SDP_TYPE_INFOFRAME_SPD, pucAmdSpdData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);

    if(GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE() == _SDP_STATE_RECEIVED)
    {
        if(enumContent == _SPD_INFO_OUI)
        {
            return (TO_DWORD(0, pucAmdSpdData[3], pucAmdSpdData[2], pucAmdSpdData[1]));
        }

        // Check AMD OUI
        if((pucAmdSpdData[1] == 0x1A) && (pucAmdSpdData[2] == 0x00) && (pucAmdSpdData[3] == 0x00))
        {
            switch(enumContent)
            {
                case _SPD_INFO_FREESYNC_SUPPORT:
                    return (((pucAmdSpdData[6] & _BIT0) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ENABLE:
                    return (((pucAmdSpdData[6] & _BIT1) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ACTIVE:
                    return (((pucAmdSpdData[6] & _BIT2) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_SEAMLESS_LOCAL_DIMMING_DISABLE_CONTROL:
                    return (((pucAmdSpdData[6] & _BIT5) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_PQ_EOTF_ACTIVE:
                    return (((pucAmdSpdData[9] & _BIT5) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_MIN_VFREQ:

                    usFreesyncVfreqmin = (((WORD)pucAmdSpdData[11] << 8) | pucAmdSpdData[7]);

                    usFreesyncVfreqmin &= usAmdVfreqMaxBit;

                    if(((usFreesyncVfreqmin * 10) < _PANEL_DP_FREESYNC_MIN_FRAME_RATE) || ((usFreesyncVfreqmin * 10) > _PANEL_DP_FREESYNC_MAX_FRAME_RATE))
                    {
                        DebugMessageDpRx("DP MAC RX1: Freesync SPD info abnormal", 0);
                    }

                    return usFreesyncVfreqmin;
                    break;

                case _SPD_INFO_FREESYNC_MAX_VFREQ:

                    usFreesyncVfreqmax = (((WORD)pucAmdSpdData[12] << 8) | pucAmdSpdData[8]);

                    usFreesyncVfreqmax &= usAmdVfreqMaxBit;

                    if(((usFreesyncVfreqmax * 10) < _PANEL_DP_FREESYNC_MIN_FRAME_RATE) || ((usFreesyncVfreqmax * 10) > _PANEL_DP_FREESYNC_MAX_FRAME_RATE))
                    {
                        DebugMessageDpRx("DP MAC RX1: Freesync SPD info abnormal", 0);
                    }

                    return usFreesyncVfreqmax;
                    break;

                case _SPD_INFO_TARGET_OUTPUT_PIXEL_RATE:

                    ulTargetOutputPixelRate = (((DWORD)pucAmdSpdData[15] << 16) | ((DWORD)pucAmdSpdData[14] << 8) | pucAmdSpdData[13]);

                    return ulTargetOutputPixelRate;

                case _SPD_INFO_FIXED_RATE_CONTENT_ACTIVE:

                    return (((pucAmdSpdData[16] & _BIT0) != 0x00) ? _ON : _OFF);

                default:
                    return 0x00;
                    break;
            }
        }
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Set Freesync AMD SPD info Vfreq max and min
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1GetSPDVfreqMaxMin(void)
{
    if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
    {
        if(GET_DP_MAC_STREAM_RX1_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE)
        {
            // Get DP DRR SPD Vmax
            SET_DRR_VFREQ_MAX((WORD)GET_DP_MAC_STREAM_RX1_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MAX_VFREQ) * 10);
            SET_DRR_VFREQ_MIN((WORD)GET_DP_MAC_STREAM_RX1_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MIN_VFREQ) * 10);
        }
        else
        {
            SET_DRR_VFREQ_MAX(_PANEL_DP_FREESYNC_MAX_FRAME_RATE);
            SET_DRR_VFREQ_MIN(_PANEL_DP_FREESYNC_MIN_FRAME_RATE);
            DebugMessageDpRx("DP MAC RX1: DRR without SPD info", 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Set DP Freesync Htotal info
// Input Value  : Dp Timing Info
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetDrrMsaForLut(StructDpInfo *pstDpInfo)
{
    WORD usTempMeasureHtotal = pstDpInfo->stDpTimingInfo.usHTotal;
    WORD usTempMsaHtotal = 0;
    WORD usTempMsaHtotalMargin = ((DWORD)usTempMeasureHtotal * _EDID_ANALYSIS_HTOTAL_MARGIN / 100);
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    enumInputPort = enumInputPort;

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
    // Hblanking Modify Mode, Measure Result Is Not True
    if(pstDpInfo->stDpHblankingModifyInfo.enumHblankingModifyMode != _NO_HBLANKING_MODIFY)
    {
        usTempMsaHtotal = pstDpInfo->stDpHblankingModifyInfo.usDpcdHTotal;
    }
    else
#endif
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
        {
            usTempMsaHtotal = TO_WORD(ScalerGetByte(P75_10_MSA_HTT_0), ScalerGetByte(P75_11_MSA_HTT_1));
        }
        else
#endif
        {
            usTempMsaHtotal = TO_WORD(ScalerGetByte(PB9_08_MSA_HTT_0), ScalerGetByte(PB9_09_MSA_HTT_1));
        }
    }

    if((usTempMsaHtotal > (usTempMeasureHtotal + usTempMsaHtotalMargin)) || (usTempMsaHtotal < (usTempMeasureHtotal - usTempMsaHtotalMargin)))
    {
        SET_DP_MAC_STREAM_RX1_HTOTAL(usTempMeasureHtotal);

        SET_DP_MAC_STREAM_RX1_HTOTAL_MARGIN(usTempMsaHtotalMargin);

        DebugMessageDpRx("7. DP MAC RX1: Freesync Get MSA Htotal Fail  ", usTempMsaHtotal);
    }
    else
    {
        SET_DP_MAC_STREAM_RX1_HTOTAL(usTempMsaHtotal);

        SET_DP_MAC_STREAM_RX1_HTOTAL_MARGIN(1);

        pstDpInfo->stDpTimingInfo.usHTotal = usTempMsaHtotal;
    }
}
#endif

//--------------------------------------------------
// Description  : Get Current DP H Period
// Input Value  : None
// Output Value : H period in nano sec
//--------------------------------------------------
DWORD ScalerDpMacStreamRx1GetHPeriod(void)
{
    DWORD ulHPeriodInNs = 0;

    ulHPeriodInNs = ScalerGlobalComputeDwordMulDiv(g_stDpMacStreamRx1Info.stDpTimingInfo.usHTotal, 1000000000UL, GET_DP_MAC_STREAM_RX1_STREAM_CLOCK());

    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        ulHPeriodInNs = ulHPeriodInNs * 2;
    }

    return ulHPeriodInNs;
}

//--------------------------------------------------
// Description  : Get Current DP H Sync Width
// Input Value  : None
// Output Value : H Sync Width in pixel clk
//--------------------------------------------------
WORD ScalerDpMacStreamRx1GetHSW(void)
{
    WORD usHSWidth = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
    enumInputPort = enumInputPort;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        usHSWidth = ((((WORD)ScalerGetByte(P70_16_MN_DPF_HSW_M) << 8) | (ScalerGetByte(P70_17_MN_DPF_HSW_L))) & 0x7FFF);
    }
    else
#endif
    {
        usHSWidth = ((((WORD)ScalerGetByte(PB8_47_MN_DPF_HSW_M) << 8) | (ScalerGetByte(PB8_48_MN_DPF_HSW_L))) & 0x7FFF);
    }

    return usHSWidth;
}

//--------------------------------------------------
// Description  : Get Current DP V Freq
// Input Value  : None
// Output Value : VFreq in 0.1Hz
//--------------------------------------------------
WORD ScalerDpMacStreamRx1GetVFreq(void)
{
    DWORD ulVBs2BsCount = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
    enumInputPort = enumInputPort;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // Pop up The result
        SET_DP_MAC_STREAM_RX1_MEASURE_POP_UP_128B132B();

        ulVBs2BsCount = ((((DWORD)(ScalerGetByte(P70_41_MN_MEAS_VLN_H) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(P70_42_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(P70_43_MN_MEAS_VLN_L)));
    }
    else
#endif
    {
        // Pop up The result
        SET_DP_MAC_STREAM_RX1_MEASURE_POP_UP_8B10B();

        ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB8_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PB8_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PB8_5A_MN_MEAS_VLN_L)));
    }

    return (DWORD)_GDIPHY_RX_GDI_CLK_KHZ * 1000 / (ulVBs2BsCount / 10);
}

//--------------------------------------------------
// Description  : Get Current DP V Period
// Input Value  : None
// Output Value : V period in line
//--------------------------------------------------
WORD ScalerDpMacStreamRx1GetVPeriod(void)
{
    DWORD ulVBs2BsCount = 0;
    WORD usHBs2BsCount = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // Pop up The result
        SET_DP_MAC_STREAM_RX1_MEASURE_POP_UP_128B132B();

        // VBs2BS count in GDI clk
        ulVBs2BsCount = ((((DWORD)(ScalerGetByte(P70_41_MN_MEAS_VLN_H) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(P70_42_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(P70_43_MN_MEAS_VLN_L)));

        // HBs2Bs count in Link Clk / 2
        usHBs2BsCount = (((DWORD)ScalerGetByte(P70_44_MN_MEAS_HLN_M)) << 8) | ((DWORD)ScalerGetByte(P70_45_MN_MEAS_HLN_L));
    }
    else
#endif
    {
        // Pop up The result
        SET_DP_MAC_STREAM_RX1_MEASURE_POP_UP_8B10B();

        // VBs2BS count in GDI clk
        ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB8_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PB8_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PB8_5A_MN_MEAS_VLN_L)));

        // HBs2Bs count in Link Clk / 2
        usHBs2BsCount = (((DWORD)ScalerGetByte(PB8_5B_MN_MEAS_HLN_M)) << 8) | ((DWORD)ScalerGetByte(PB8_5C_MN_MEAS_HLN_L));
    }

    // VTotal in line, Link Clk / 2 : (Link Rate * 27 / 2)
    return (ulVBs2BsCount * (ScalerDpAuxRxGetDpcdLinkRate(enumInputPort) * 27 / 2) / usHBs2BsCount * 1000 / _GDIPHY_RX_GDI_CLK_KHZ);
}

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mac Rx1 PR Mode Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PRModeInitial(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Set Pr Mode Update Su_valid and Crc_valid Signal Option Once Mode
    ScalerSetBit(P75_4A_VSC10, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Disable Pr State Change Irq
    ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_128b132b(_DISABLE);

    // Disable Pr Crc Irq
    ScalerSetBit(P75_4A_VSC10, ~_BIT5, 0x00);

    // Clr Pr Irq Flag
    ScalerSetBit(P75_4B_VSC11, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    CLR_DP_MAC_STREAM_RX1_PR_ENABLE_128B132B();
#endif

    // Set Pr Mode Update Su_valid and Crc_valid Signal Option Once Mode
    ScalerSetBit(PB9_4A_DUMMY_4A, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Disable Pr State Change Irq
    ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_8b10b(_DISABLE);

    // Disable Pr Crc Irq
    ScalerSetBit(PB9_4A_DUMMY_4A, ~_BIT5, 0x00);

    // Clr Pr Irq Flag
    ScalerSetBit(PB9_4B_DUMMY_4B, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    CLR_DP_MAC_STREAM_RX1_PR_ENABLE_8B10B();
}

//--------------------------------------------------
// Description  : PR Mode SDP Reset
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PRModeSdpReset(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Reset VSC SDP
    ScalerSetBit(P75_40_VSC0, ~_BIT0, _BIT0);
    ScalerSetBit(P75_40_VSC0, ~_BIT0, 0x00);

    // Clr VSC SDP Received Flag
    ScalerSetBit(P75_49_VSC9, ~_BIT7, _BIT7);
    ScalerSetBit(P75_49_VSC9, ~_BIT7, 0x00);
#endif
    // Reset VSC SDP
    ScalerSetBit(PB9_40_VSC0, ~_BIT0, _BIT0);
    ScalerSetBit(PB9_40_VSC0, ~_BIT0, 0x00);

    // Clr VSC SDP Received Flag
    ScalerSetBit(PB9_49_VSC9, ~_BIT7, _BIT7);
    ScalerSetBit(PB9_49_VSC9, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Mac Rx PR Mode Check Process
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PRModeCheckProc(EnumInputPort enumInputPort)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1PRModeCheckProc_128b132b(enumInputPort);
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1PRModeCheckProc_8b10b(enumInputPort);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Pr_State Change IRQ_en
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
        {
            ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_128b132b(bEnable);
        }
        else
#endif
        {
            ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_8b10b(bEnable);
        }
    }
    else
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_128b132b(bEnable);
#endif
        ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_8b10b(bEnable);
    }
}
#endif

//--------------------------------------------------
// Description  : DP Mac Rx1 Stream Pre Scan Port 8b10b
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerDpMacStreamRx1StreamPreDetect_8b10b(EnumInputPort enumInputPort)
{
    EnumDpStreamInfoType enumDpStreamInfoType = _INFO_TYPE_NONE;
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(_DP_MAC_1);

    enumDpMacStreamSourceType = enumDpMacStreamSourceType;

    SET_DP_MAC_STREAM_RX1_STREAM_INFO_TYPE(_INFO_TYPE_NONE);

    memset(&g_stDpMacStreamRx1Info, 0, sizeof(StructDpInfo));

    if(ScalerDpAuxRxGetLTStatus(enumInputPort) != _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return _FALSE;
    }

    if(ScalerDpMacDphyRxHdcpCheck(enumInputPort) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: HDCP Check Fail", 0);

        ScalerDpMacDphyRxCpIRQ(enumInputPort, _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

        ScalerDpHdcpRxSetHdcpCpirqFlag(enumInputPort);

#if(_DP_LONG_HPD_AFTER_CPIRQ_SUPPORT == _ON)
        if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _DISABLE)
        {
            ScalerDpAuxRxReactiveHdcpLongHotplug(enumInputPort);
        }
#endif

        return _FALSE;
    }

    if(ScalerDpMacStreamRx1GetVideoStream() == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Video Stream Fail", 0);

        return _FALSE;
    }

#if((_DP_RX_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
    if(ScalerDpMacDscRxDscStreamCheck(_DP_MAC_1) == _TRUE)
    {
        if(ScalerDpMacStreamRxDscGetFlagStatus(enumDpMacStreamSourceType) == _TRUE)
        {
            enumDpStreamInfoType = _INFO_TYPE_DSC;
        }
        else
        {
            DebugMessageDpRx("7. DP MAC RX1: Get Abnormal Compression Flag", 0);

            return _FALSE;
        }
    }
    else
#endif
    {
        enumDpStreamInfoType = _INFO_TYPE_VIDEO;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(ScalerDpMacStreamRxFreeSyncGetStreamConfig(enumDpMacStreamSourceType) == _TRUE)
    {
        SET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE();
    }
    else
    {
        CLR_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE();
    }
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
    if(ScalerDpMacStreamRxPRModeFlagStatus(enumDpMacStreamSourceType) == _TRUE)
    {
        // Enable Pr State Change Irq
        ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_8b10b(_ENABLE);

        SET_DP_MAC_STREAM_RX1_PR_ENABLE_8B10B();
    }
    else
    {
        // Disable Pr State Change Irq
        ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_8b10b(_DISABLE);

        CLR_DP_MAC_STREAM_RX1_PR_ENABLE_8B10B();
    }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x16, (_BIT2 | _BIT0)) == (_BIT2 | _BIT0))
    {
        ScalerDpMacDphyRxAuxlessAlpmEnable(enumInputPort, _ENABLE);

        SET_DP_MAC_STREAM_RX1_ALPM_ENABLE_8B10B();
    }
    else
    {
        ScalerDpMacDphyRxAuxlessAlpmEnable(enumInputPort, _DISABLE);

        CLR_DP_MAC_STREAM_RX1_ALPM_ENABLE_8B10B();
    }
#endif

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)

    // Disable DP Mac Rx1 Support DSC
    CLR_DP_MAC_STREAM_RX1_DSC_SUPPORT_8B10B();

#endif

    if(ScalerDpMacStreamRx1GetMsaTimingInfo_8b10b(&g_stDpMacStreamRx1Info) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Get MSA Info Fail", 0);

        return _FALSE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    if(ScalerDpMacStreamRx1GetVideoInfo_8b10b() == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Get Video Info Fail", 0);

        return _FALSE;
    }
    else
    {
        ScalerDpMacStreamRx1SetColorInfo();
    }

    if(ScalerDpMacStreamRx1GetMeasureLinkInfo_8b10b(&g_stDpMacStreamRx1Info) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Get Measure Info Fail", 0);

        return _FALSE;
    }

    if(ScalerDpMacStreamRx1StreamInfoSetting(&g_stDpMacStreamRx1Info) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Stream Info Setting Fail", 0);

        return _FALSE;
    }

    // Secondary Data Sram Reset Prevent Sdp Change Flag and Sram Data Mismacth
    ScalerDpMacStreamRx1SdpSramReset_8b10b();

    SET_DP_MAC_STREAM_RX1_STREAM_INFO_TYPE_CHANGE();

    SET_DP_MAC_STREAM_RX1_STREAM_INFO_TYPE(enumDpStreamInfoType);

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Get Video Info 8b10b
// Input Value  : None
// Output Value : TRUE --> Get successfully
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetVideoInfo_8b10b(void)
{
    BYTE pucColorInfoByte[3] = {0};

    CLR_DP_MAC_STREAM_RX1_VSC_SDP_COLOR_MODE();

    // Check MISC1[6]
    if((ScalerGetBit(PB9_03_MN_STRM_ATTR_MISC1, _BIT6)) == _BIT6)
    {
        // Use VSC SDP
        SET_DP_MAC_STREAM_RX1_VSC_SDP_COLOR_MODE();

        // Get VSC SDP Data Packet, Read DB16~18 --> pucColorInfoByte[0:2]
        ScalerDpMacStreamRx1GetSdpPktData(_DP_SDP_TYPE_VSC, pucColorInfoByte, 16, 3);

        // Set Color Info PreValue
        SET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_PREVALUE(pucColorInfoByte[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        SET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE((pucColorInfoByte[1] & _BIT7) >> 7);
        SET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE(pucColorInfoByte[1] & (_BIT2 | _BIT1 | _BIT0));
        SET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE(pucColorInfoByte[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4));
        SET_DP_MAC_STREAM_RX1_CONTENT_TYPE(pucColorInfoByte[2] & (_BIT2 | _BIT1 | _BIT0));

        DebugMessageDpRx("DP MAC RX1: VSC DB16", pucColorInfoByte[0]);
        DebugMessageDpRx("DP MAC RX1: VSC DB17", pucColorInfoByte[1]);
    }
    else
    {
        // Get MISC Info
        pucColorInfoByte[0] = ScalerGetByte(PB9_02_MN_STRM_ATTR_MISC);
        pucColorInfoByte[1] = ScalerGetByte(PB9_03_MN_STRM_ATTR_MISC1);

        // Set Color Info PreValue
        SET_DP_MAC_STREAM_RX1_COLORIMETRY_PREVALUE((pucColorInfoByte[0] & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
        SET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE((pucColorInfoByte[0] & _BIT3) >> 3);
        SET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE((pucColorInfoByte[0] & (_BIT7 | _BIT6 | _BIT5)) >> 5);
        SET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE((pucColorInfoByte[1] & _BIT7) | (pucColorInfoByte[0] & (_BIT2 | _BIT1)));
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get VBID Information 8b10b
// Input Value  : VBID Content
// Output Value : VBID Information
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetVbidInfo_8b10b(EnumDpVbidInfo enumDpVbidInfo)
{
    switch(enumDpVbidInfo)
    {
        case _DP_VBID_INTERLACE_MODE:

            return (ScalerGetBit(PB9_01_DP_VBID, _BIT2) == _BIT2);

        case _DP_VBID_VIDEO_STREAM:

            return (ScalerGetBit(PB9_01_DP_VBID, _BIT3) == 0x00);

        case _DP_VBID_DSC_STREAM:

            return (ScalerGetBit(PB9_01_DP_VBID, _BIT5) == _BIT5);

        case _DP_VBID_AUDIO_STREAM:

            return (ScalerGetBit(PB9_01_DP_VBID, _BIT4) == 0x00);

        default:

            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get MSA Information
// Input Value  : EnumDpRxMsaType
// Output Value : UnionDpRxMsaValue
//--------------------------------------------------
UnionDpRxMsaValue ScalerDpMacStreamRx1GetMsaInfo_8b10b(EnumDpRxMsaType enumDpRxMsaType)
{
    UnionDpRxMsaValue unDpRxMsaValue;

    switch(enumDpRxMsaType)
    {
        case _DP_RX_MSA_HTOTAL:
            unDpRxMsaValue.usDpRxMsaHtotal = (TO_WORD(ScalerGetByte(PB9_08_MSA_HTT_0), ScalerGetByte(PB9_09_MSA_HTT_1)));
            break;

        case _DP_RX_MSA_HSTART:
            unDpRxMsaValue.usDpRxMsaHstart = (TO_WORD(ScalerGetByte(PB9_0A_MSA_HST_0), ScalerGetByte(PB9_0B_MSA_HST_1)));
            break;

        case _DP_RX_MSA_HWIDTH:
            unDpRxMsaValue.usDpRxMsaHwidth = (TO_WORD(ScalerGetByte(PB9_0C_MSA_HWD_0), ScalerGetByte(PB9_0D_MSA_HWD_1)));
            break;

        case _DP_RX_MSA_HSP:
            unDpRxMsaValue.bDpRxMsaHsp = (bit)(ScalerGetBit(PB9_0E_MSA_HSW_0, _BIT7));
            break;

        case _DP_RX_MSA_HSW:
            unDpRxMsaValue.usDpRxMsaHsw = (TO_WORD((ScalerGetByte(PB9_0E_MSA_HSW_0) & (0x7F)), ScalerGetByte(PB9_0F_MSA_HSW_1)));
            break;

        case _DP_RX_MSA_VTOTAL:
            unDpRxMsaValue.usDpRxMsaVtotal = (TO_WORD(ScalerGetByte(PB9_10_MSA_VTTE_0), ScalerGetByte(PB9_11_MSA_VTTE_1)));
            break;

        case _DP_RX_MSA_VSTART:
            unDpRxMsaValue.usDpRxMsaVstart = (TO_WORD(ScalerGetByte(PB9_14_MSA_VST_0), ScalerGetByte(PB9_15_MSA_VST_1)));
            break;

        case _DP_RX_MSA_VHEIGHT:
            unDpRxMsaValue.usDpRxMsaVheight = (TO_WORD(ScalerGetByte(PB9_16_MSA_VHT_0), ScalerGetByte(PB9_17_MSA_VHT_1)));
            break;

        case _DP_RX_MSA_VSP:
            unDpRxMsaValue.bDpRxMsaVsp = (bit)(ScalerGetBit(PB9_18_MSA_VSW_0, _BIT7));
            break;

        case _DP_RX_MSA_VSW:
            unDpRxMsaValue.usDpRxMsaVsw = (TO_WORD((ScalerGetByte(PB9_18_MSA_VSW_0) & (0x7F)), ScalerGetByte(PB9_19_MSA_VSW_1)));
            break;

        case _DP_RX_MSA_MVID:
            unDpRxMsaValue.ulDpRxMsaMvid = (TO_DWORD(0x00, ScalerGetByte(PB9_1A_MSA_MVID_0),
                                                     ScalerGetByte(PB9_1B_MSA_MVID_1), ScalerGetByte(PB9_1C_MSA_MVID_2)));
            break;

        case _DP_RX_MSA_NVID:
            unDpRxMsaValue.ulDpRxMsaNvid = (TO_DWORD(0x00, ScalerGetByte(PB9_1D_MSA_NVID_0),
                                                     ScalerGetByte(PB9_1E_MSA_NVID_1), ScalerGetByte(PB9_1F_MSA_NVID_2)));
            break;

        case _DP_RX_MSA_MAUD:
            unDpRxMsaValue.ulDpRxMsaMaud = (TO_DWORD(0x00, ScalerGetByte(PB9_20_MSA_MAUD_0),
                                                     ScalerGetByte(PB9_21_MSA_MAUD_1), ScalerGetByte(PB9_22_MSA_MAUD_2)));
            break;

        case _DP_RX_MSA_NAUD:
            unDpRxMsaValue.ulDpRxMsaNaud = (TO_DWORD(0x00, ScalerGetByte(PB9_23_MSA_NAUD_0),
                                                     ScalerGetByte(PB9_24_MSA_NAUD_1), ScalerGetByte(PB9_25_MSA_NAUD_2)));
            break;

        default:
            unDpRxMsaValue.uqDpRxMsaError = 0xFFFF;
            break;
    }

    return unDpRxMsaValue;
}

//--------------------------------------------------
// Description  : Get Dp MSA Timing Info 8b10b
// Input Value  : DP Info Structure
// Output Value : True --> Get MSA Info
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetMsaTimingInfo_8b10b(StructDpInfo *pstDpInfo)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    // Pop up Main Stream Attributes
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get HWidth
    pstDpInfo->stDpTimingInfo.usHWidth = TO_WORD(ScalerGetByte(PB9_0C_MSA_HWD_0), ScalerGetByte(PB9_0D_MSA_HWD_1));

    // Get VHeight
    pstDpInfo->stDpTimingInfo.usVHeight = TO_WORD(ScalerGetByte(PB9_16_MSA_VHT_0), ScalerGetByte(PB9_17_MSA_VHT_1));

    // Get HTotal
    pstDpInfo->stDpTimingInfo.usHTotal = TO_WORD(ScalerGetByte(PB9_08_MSA_HTT_0), ScalerGetByte(PB9_09_MSA_HTT_1));

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
    // BackUp HTotal For Hblanking Modify Mode
    pstDpInfo->stDpHblankingModifyInfo.usMsaHTotal = pstDpInfo->stDpTimingInfo.usHTotal;
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
    {
        // Check if MSA is Valid
        if((pstDpInfo->stDpTimingInfo.usHWidth == 0x00) || (pstDpInfo->stDpTimingInfo.usVHeight == 0x00))
        {
            return _FALSE;
        }

        // Get HStart
        pstDpInfo->stDpTimingInfo.usHStart = _DE_ONLY_MODE_HSTART;

        // Get HSW
        pstDpInfo->stDpTimingInfo.usHSWidth = _DE_ONLY_MODE_HSW;

        // Get HS Polarity
        pstDpInfo->stDpTimingInfo.b1HSP = _SYNC_POLARITY_POSITIVE;

        // Get VStart
        pstDpInfo->stDpTimingInfo.usVStart = _DE_ONLY_MODE_VSTART;

        // Get VSW
        pstDpInfo->stDpTimingInfo.usVSWidth = _DE_ONLY_MODE_VSW;

        // Get VS Polarity
        pstDpInfo->stDpTimingInfo.b1VSP = _SYNC_POLARITY_POSITIVE;
    }
    else
#endif
    {
        // Get HStart
        pstDpInfo->stDpTimingInfo.usHStart = TO_WORD(ScalerGetByte(PB9_0A_MSA_HST_0), ScalerGetByte(PB9_0B_MSA_HST_1));

        // Get HSW
        pstDpInfo->stDpTimingInfo.usHSWidth = TO_WORD(ScalerGetBit(PB9_0E_MSA_HSW_0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)), ScalerGetByte(PB9_0F_MSA_HSW_1));

        // Get HS Polarity
        pstDpInfo->stDpTimingInfo.b1HSP = (bit) ScalerGetBit(PB9_0E_MSA_HSW_0, _BIT7);

        // Get VTotal
        pstDpInfo->stDpTimingInfo.usVTotal = TO_WORD(ScalerGetByte(PB9_10_MSA_VTTE_0), ScalerGetByte(PB9_11_MSA_VTTE_1));

        // Get VTotal Odd
        pstDpInfo->stDpTimingInfo.usVTotalOdd = TO_WORD(ScalerGetByte(PB9_12_MSA_VTTO_0), ScalerGetByte(PB9_13_MSA_VTTO_1));

        // Get VStart
        pstDpInfo->stDpTimingInfo.usVStart = TO_WORD(ScalerGetByte(PB9_14_MSA_VST_0), ScalerGetByte(PB9_15_MSA_VST_1));

        // Get VSW
        pstDpInfo->stDpTimingInfo.usVSWidth = TO_WORD(ScalerGetBit(PB9_18_MSA_VSW_0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)), ScalerGetByte(PB9_19_MSA_VSW_1));

        // Get VS Polarity
        pstDpInfo->stDpTimingInfo.b1VSP = (bit) ScalerGetBit(PB9_18_MSA_VSW_0, _BIT7);

        // Check if MSA is Valid
        if((pstDpInfo->stDpTimingInfo.usHTotal == 0x00) || (pstDpInfo->stDpTimingInfo.usHStart == 0x00) ||
           (pstDpInfo->stDpTimingInfo.usHWidth == 0x00) || (pstDpInfo->stDpTimingInfo.usHSWidth == 0x00) ||
           (pstDpInfo->stDpTimingInfo.usVTotal == 0x00) || (pstDpInfo->stDpTimingInfo.usVStart == 0x00) ||
           (pstDpInfo->stDpTimingInfo.usVHeight == 0x00) || (pstDpInfo->stDpTimingInfo.usVSWidth == 0x00))
        {
            if((pstDpInfo->stDpTimingInfo.usHTotal == 0x00) && (pstDpInfo->stDpTimingInfo.usHStart == 0x00) &&
               (pstDpInfo->stDpTimingInfo.usHWidth == 0x00) && (pstDpInfo->stDpTimingInfo.usHSWidth == 0x00) &&
               (pstDpInfo->stDpTimingInfo.usVTotal == 0x00) && (pstDpInfo->stDpTimingInfo.usVStart == 0x00) &&
               (pstDpInfo->stDpTimingInfo.usVHeight == 0x00) && (pstDpInfo->stDpTimingInfo.usVSWidth == 0x00))
            {
#if(_DP_MST_SUPPORT == _ON)
                if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _FALSE)
#endif
                {
                    if(ScalerDpMacDphyRxHdcpCheckValid(enumInputPort) == _TRUE)
                    {
                        if(GET_DP_MAC_STREAM_RX1_MSA_FAIL_RESET_COUNT() < 10)
                        {
                            ADD_DP_MAC_STREAM_RX1_MSA_FAIL_RESET_COUNT();
                        }
                        else
                        {
                            CLR_DP_MAC_STREAM_RX1_MSA_FAIL_RESET_COUNT();

                            ScalerDpMacDphyRxDigitalPhyReset(enumInputPort);

                            // Delay a Complete Frame
                            ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);

                            ScalerDpMacDphyRxDecodeErrorCountReset(enumInputPort, _DP_MAC_DECODE_METHOD_8B10B);
                        }
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }

            return _FALSE;
        }

        CLR_DP_MAC_STREAM_RX1_MSA_FAIL_RESET_COUNT();
    }

    // Set V Front Porch
    SET_DP_MAC_STREAM_RX1_VFRONT_PORCH(_DP_VSYNC_FRONT_PORCH);

    // Get Mvid
    pstDpInfo->stDpLinkInfo.ulMvid = TO_DWORD(0x00, ScalerGetByte(PB9_1A_MSA_MVID_0), ScalerGetByte(PB9_1B_MSA_MVID_1), ScalerGetByte(PB9_1C_MSA_MVID_2));

    // Check if Mvid is Valid
    if(pstDpInfo->stDpLinkInfo.ulMvid == 0x00)
    {
        return _FALSE;
    }

    // Get Nvid
    pstDpInfo->stDpLinkInfo.ulNvid = TO_DWORD(0x00, ScalerGetByte(PB9_1D_MSA_NVID_0), ScalerGetByte(PB9_1E_MSA_NVID_1), ScalerGetByte(PB9_1F_MSA_NVID_2));

    // Check if Nvid is Valid
    if(pstDpInfo->stDpLinkInfo.ulNvid == 0x00)
    {
        return _FALSE;
    }

    DebugMessageDpRx("DP MAC RX1: MSA HTotal", pstDpInfo->stDpTimingInfo.usHTotal);
    DebugMessageDpRx("DP MAC RX1: MSA HStart", pstDpInfo->stDpTimingInfo.usHStart);
    DebugMessageDpRx("DP MAC RX1: MSA HWidth", pstDpInfo->stDpTimingInfo.usHWidth);
    DebugMessageDpRx("DP MAC RX1: MSA HSW", pstDpInfo->stDpTimingInfo.usHSWidth);
    DebugMessageDpRx("DP MAC RX1: MSA HSP", pstDpInfo->stDpTimingInfo.b1HSP);
    DebugMessageDpRx("DP MAC RX1: MSA VTotal", pstDpInfo->stDpTimingInfo.usVTotal);
    DebugMessageDpRx("DP MAC RX1: MSA VStart", pstDpInfo->stDpTimingInfo.usVStart);
    DebugMessageDpRx("DP MAC RX1: MSA VHeight", pstDpInfo->stDpTimingInfo.usVHeight);
    DebugMessageDpRx("DP MAC RX1: MSA VSW", pstDpInfo->stDpTimingInfo.usVSWidth);
    DebugMessageDpRx("DP MAC RX1: MSA VSP", pstDpInfo->stDpTimingInfo.b1VSP);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get DP Link Info from Measure Function 8b10b
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetMeasureLinkInfo_8b10b(StructDpInfo *pstDpInfo)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
    WORD usTemp = 0;

    ///////////////////////
    // Get Measured Info //
    ///////////////////////

    // Reset Interlace mode
    ScalerDpMacStreamRx1InterlaceReset_8b10b();

    // Enable Measurement
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), 0x00);
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Pop up The Measured Result
    SET_DP_MAC_STREAM_RX1_MEASURE_POP_UP_8B10B();

    // Get BS To BS Count of Frame N
    pstDpInfo->stDpLinkInfo.ulVBsToBsCountN = TO_DWORD(0x00, ScalerGetBit(PB8_58_MN_MEAS_CTRL, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)), ScalerGetByte(PB8_59_MN_MEAS_VLN_M), ScalerGetByte(PB8_5A_MN_MEAS_VLN_L));

    // Delaying 1 frame time be used to wait time passed for upstream dptx generated different picture size of the firt frame and second frame
    ScalerTimerDelayXms((pstDpInfo->stDpLinkInfo.ulVBsToBsCountN / _GDIPHY_RX_GDI_CLK_KHZ) + 2);

    // Pop up The Measured Result
    SET_DP_MAC_STREAM_RX1_MEASURE_POP_UP_8B10B();

    // Get BS To BS Count of Frame N
    pstDpInfo->stDpLinkInfo.ulVBsToBsCountN = TO_DWORD(0x00, ScalerGetBit(PB8_58_MN_MEAS_CTRL, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)), ScalerGetByte(PB8_59_MN_MEAS_VLN_M), ScalerGetByte(PB8_5A_MN_MEAS_VLN_L));

    // Delay 2ms To Get VBID
    ScalerTimerDelayXms(2);

    // Get Interlace Field Flag VBID[1] of Frame N
    pstDpInfo->stDpLinkInfo.b1InterlaceFieldN = (bit)ScalerGetBit(PB9_01_DP_VBID, _BIT1);

    // Delay 1 Frame Time, unit is ms
    ScalerTimerDelayXms((pstDpInfo->stDpLinkInfo.ulVBsToBsCountN / _GDIPHY_RX_GDI_CLK_KHZ) + 2);

    // Pop up The Measured Result
    SET_DP_MAC_STREAM_RX1_MEASURE_POP_UP_8B10B();

    // Get BS To BS Count of Frame N+1
    pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1 = TO_DWORD(0x00, ScalerGetBit(PB8_58_MN_MEAS_CTRL, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)), ScalerGetByte(PB8_59_MN_MEAS_VLN_M), ScalerGetByte(PB8_5A_MN_MEAS_VLN_L));

    // Get Interlace Field Flag VBID[1] of Frame N+1
    pstDpInfo->stDpLinkInfo.b1InterlaceFieldN1 = (bit)ScalerGetBit(PB9_01_DP_VBID, _BIT1);

    // Get Interlace HW Detect Result
    pstDpInfo->stDpLinkInfo.b1HwInterlaceDetect = (bit)ScalerGetBit(PB8_57_INTERLACE_MODE_CONFIG, _BIT5);
    pstDpInfo->stDpLinkInfo.b1HwFakeInterlaceDetect = (bit)ScalerGetBit(PB8_57_INTERLACE_MODE_CONFIG, _BIT0);

    // Disable Measurement
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), 0x00);

    // Get HBs2Bs Count By Link Clk / 2
    pstDpInfo->stDpLinkInfo.usHBsToBsCount = (((WORD)ScalerGetByte(PB8_5B_MN_MEAS_HLN_M)) << 8) | ((WORD)ScalerGetByte(PB8_5C_MN_MEAS_HLN_L));

    /////////////////////
    // Check the value //
    /////////////////////
    if(ScalerDpMacStreamRxMeasureInfoCheck(pstDpInfo) == _FALSE)
    {
        return _FALSE;
    }

    ////////////////////
    // Get Link Clock //
    ////////////////////

    usTemp = ScalerDpMacDphyRxSignalDetectMeasureCount(enumInputPort, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0), _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_2000_CYCLE);

    if(usTemp == 0)
    {
        switch(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort))
        {
            case _DP_LINK_HBR3_9G:

                usTemp = _DP_RX_VCO_TARGET_COUNT_2000_HBR3_9G_SAVED;

                break;

            case _DP_LINK_HBR3:

                usTemp = _DP_RX_VCO_TARGET_COUNT_2000_HBR3_SAVED;

                break;

            case _DP_LINK_HBR2:

                usTemp = _DP_RX_VCO_TARGET_COUNT_2000_HBR2_SAVED;

                break;

            case _DP_LINK_HBR:

                usTemp = _DP_RX_VCO_TARGET_COUNT_2000_HBR_SAVED;

                break;

            case _DP_LINK_RBR:
            default:

                usTemp = _DP_RX_VCO_TARGET_COUNT_2000_RBR_SAVED;

                break;
        }
    }

    // Get Link Clock, Unit is Hz
    // Measure Period = 2000 GDI_Clock Cycle, Count by 1/2 Link Clock
    pstDpInfo->stDpLinkInfo.ulLinkClockHz = (((DWORD)usTemp) * _GDIPHY_RX_GDI_CLK_KHZ);

    // Check if Measure Data is Valid
    if((pstDpInfo->stDpLinkInfo.ulVBsToBsCountN == 0x00) || (pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1 == 0x00) ||
       (pstDpInfo->stDpLinkInfo.usHBsToBsCount == 0x00) || (pstDpInfo->stDpLinkInfo.ulLinkClockHz == 0x00))
    {
        DebugMessageDpRx("DP MAC RX1: Measure data is invalid", 0);

        return _FALSE;
    }

#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
    // Calculate Stream Clock (Unit is Hz)
    pstDpInfo->stDpLinkInfo.ulStreamClockHz = ScalerGlobalComputeDwordMulDiv(pstDpInfo->stDpTimingInfo.usHTotal, pstDpInfo->stDpLinkInfo.ulLinkClockHz / 2, (DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount);

    WORD usIVfreq_OOR = ScalerGlobalComputeDwordMulDiv(pstDpInfo->stDpLinkInfo.ulStreamClockHz, 10, ((DWORD)pstDpInfo->stDpTimingInfo.usHTotal * pstDpInfo->stDpTimingInfo.usVTotal));

    DebugMessageDpRx("DP MAC RX1: IVfreq", usIVfreq_OOR);

    if(usIVfreq_OOR <= 200)
    {
        SET_DP_MAC_STREAM_RX1_JUDGE_OOR();

        DebugMessageDpRx("DP MAC RX1: Judge for OOR Case", 0);
    }
    else
    {
        CLR_DP_MAC_STREAM_RX1_JUDGE_OOR();
    }
#endif


    //////////////////////
    // Get Stream Clock //
    //////////////////////

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
    {
#if(_DRR_FREE_RUN_DISPLAY_SUPPORT == _OFF)
        {
#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
            if(GET_DP_MAC_STREAM_RX1_JUDGE_OOR() == _FALSE)
#endif
            {
                // Get IVfreq
                WORD usIVfreq = ((DWORD)_GDIPHY_RX_GDI_CLK_KHZ * 1000 / (pstDpInfo->stDpLinkInfo.ulVBsToBsCountN / 10));

                if((usIVfreq < (_PANEL_DP_FREESYNC_MIN_FRAME_RATE - _PANEL_FRAME_SYNC_MARGIN)) ||
                   (usIVfreq > (_PANEL_DP_FREESYNC_MAX_FRAME_RATE + _PANEL_FRAME_SYNC_MARGIN)))
                {
                    return _FALSE;
                }
            }
        }
#endif

        if(pstDpInfo->stDpLinkInfo.usHBsToBsCount == 0x00)
        {
            return _FALSE;
        }

        // VTotal in line, Link Clk / 2 : (Link Rate * 27 / 2)
        pstDpInfo->stDpTimingInfo.usVTotal = ScalerGlobalComputeDwordMulDiv(pstDpInfo->stDpLinkInfo.ulVBsToBsCountN, (pstDpInfo->stDpLinkInfo.ulLinkClockHz / 1000 / 2), (DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount) / _GDIPHY_RX_GDI_CLK_KHZ;

        if(ScalerDpRxGetSrcMstEnable(enumInputPort) == _TRUE)
        {
            // Calculate Stream Clock (Unit is Hz)
            pstDpInfo->stDpLinkInfo.ulStreamClockHz = ScalerGlobalComputeDwordMulDiv(pstDpInfo->stDpTimingInfo.usHTotal, pstDpInfo->stDpLinkInfo.ulLinkClockHz / 2, (DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount);
            DebugMessageDpRx("DP MAC RX1: MST Stream Clock 8b10b Calculate", pstDpInfo->stDpLinkInfo.ulStreamClockHz);
        }
        else
        {
            // Calculate Stream Clock (Unit is Hz)
            pstDpInfo->stDpLinkInfo.ulStreamClockHz = pstDpInfo->stDpLinkInfo.ulMvid * (pstDpInfo->stDpLinkInfo.ulLinkClockHz / pstDpInfo->stDpLinkInfo.ulNvid);
            pstDpInfo->stDpLinkInfo.ulStreamClockHz += pstDpInfo->stDpLinkInfo.ulLinkClockHz % pstDpInfo->stDpLinkInfo.ulNvid * 100 / pstDpInfo->stDpLinkInfo.ulNvid * pstDpInfo->stDpLinkInfo.ulMvid / 100;
        }

        DWORD ulTemp = pstDpInfo->stDpLinkInfo.ulLinkClockHz / 1000 / 2;

        if(ulTemp == 0x00)
        {
            return _FALSE;
        }

        // HTotal in Pixel Clk, Link Clk / 2 : (Link Rate * 27 / 2)
        pstDpInfo->stDpTimingInfo.usHTotal = ScalerGlobalComputeDwordMulDiv((DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount, (pstDpInfo->stDpLinkInfo.ulStreamClockHz / 1000), ulTemp);
    }
    else
#endif
    {
#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
        if(GET_DP_MAC_STREAM_RX1_JUDGE_OOR() == _FALSE)
#endif
        {
            // Calculate Stream Clock (Unit is Hz)
            pstDpInfo->stDpLinkInfo.ulStreamClockHz = ((((DWORD)pstDpInfo->stDpTimingInfo.usHTotal * ((DWORD)pstDpInfo->stDpTimingInfo.usVTotal) * 100) / pstDpInfo->stDpLinkInfo.ulVBsToBsCountN) * _GDIPHY_RX_GDI_CLK_KHZ * 10);
        }
    }

    DebugMessageDpRx("DP MAC RX1: MAC111111 From Dx", enumInputPort);
    DebugMessageDpRx("DP MAC RX1: VBs2Bs N", pstDpInfo->stDpLinkInfo.ulVBsToBsCountN);
    DebugMessageDpRx("DP MAC RX1: VBs2Bs N+1", pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1);
    DebugMessageDpRx("DP MAC RX1: HBs2Bs", pstDpInfo->stDpLinkInfo.usHBsToBsCount);
    DebugMessageDpRx("DP MAC RX1: Link Clock", pstDpInfo->stDpLinkInfo.ulLinkClockHz);
    DebugMessageDpRx("DP MAC RX1: Mvid", pstDpInfo->stDpLinkInfo.ulMvid);
    DebugMessageDpRx("DP MAC RX1: Nvid", pstDpInfo->stDpLinkInfo.ulNvid);
    DebugMessageDpRx("DP MAC RX1: Stream Clock", pstDpInfo->stDpLinkInfo.ulStreamClockHz);

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Stream Vesa Video Setting 8b10b
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
EnumDpMacRxStreamVideoType ScalerDpMacStreamRx1StreamVesaVideoSetting_8b10b(void)
{
    if(ScalerDpMacStreamRx1DisplayFormatSetting_8b10b(&g_stDpMacStreamRx1Info) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Display Format Fail", 0);

        return _DP_STREAM_FAIL;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _DP_STREAM_NONE;
    }
#endif

    if(ScalerDpMacStreamRx1StreamClkRegenerate(&g_stDpMacStreamRx1Info) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Stream Clk Fail", 0);

        return _DP_STREAM_FAIL;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _DP_STREAM_NONE;
    }
#endif

    if(ScalerDpMacStreamRx1TrackingSetting(&g_stDpMacStreamRx1Info) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Tracking Fail", 0);

        return _DP_STREAM_FAIL;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _DP_STREAM_NONE;
    }
#endif

    if(ScalerDpMacStreamRx1FifoCheckProc_8b10b(_DP_FIFO_DELAY_CHECK, &g_stDpMacStreamRx1Info) == _FAIL)
    {
#if(_URGENT_EVENT_CHECK_MODE == _ON)
        if(ScalerSyncCheckUrgentEvent() == _TRUE)
        {
            return _DP_STREAM_NONE;
        }
#endif

        DebugMessageDpRx("7. DP MAC RX1: Fifo Fail", 0);

        return _DP_STREAM_FAIL;
    }

    // Calculating Stream clock from final n.f code of PLL
    ScalerDpMacStreamRx1StreamClockSetting(&g_stDpMacStreamRx1Info);

    // Use for Video/DisplayFormat/Measure relative Settings.
    ScalerDpMacStreamRx1MacSetting();

    return _DP_STREAM_PASS;
}

//--------------------------------------------------
// Description  : DP Display Format Generator Setting 8b10b
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRx1DisplayFormatSetting_8b10b(StructDpInfo *pstDpInfo)
{
    bit bDeOnlyModeJudge = _FALSE;

    ////////////////////////////////////
    // Display Format Generator Reset //
    ////////////////////////////////////

    // Disable Generate Display Format
    ScalerSetBit(PB8_30_DPF_CTRL_0, ~_BIT7, 0x00);

    // Display Format Generator Reset
    ScalerSetBit(PB8_1E_MAC_DIG_RESET_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(PB8_1E_MAC_DIG_RESET_CTRL, ~_BIT7, 0x00);


    //////////////////////////
    // Interlace Mode Check //
    //////////////////////////

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _FALSE)
#endif
    {
        if(ScalerDpMacStreamRx1InterlaceCheck(pstDpInfo) == _TRUE)
        {
            pstDpInfo->stDpLinkInfo.b1InterlaceStatus = _TRUE;

            DebugMessageDpRx("7. DP MAC RX1: Interlace Mode - VTotal", pstDpInfo->stDpTimingInfo.usVTotal);
        }
        else
        {
            pstDpInfo->stDpLinkInfo.b1InterlaceStatus = _FALSE;

            DebugMessageDpRx("7. DP MAC RX1: Progressive Mode", 0);

            // Judge DE_Only Mode Use or not
            if(ScalerDpMacStreamRxDeOnlyJudge_8b10b(pstDpInfo) == _TRUE)
            {
                bDeOnlyModeJudge = _TRUE;
            }
        }
    }


    ////////////////////////
    // Adjust Timing Info //
    ////////////////////////

    ScalerDpMacStreamRx1TimingInfoAdjust(pstDpInfo);


    ///////////////////////////////////
    // Display Format Timing Setting //
    ///////////////////////////////////

    // Set HTotal
    ScalerSetByte(PB8_41_MN_DPF_HTT_M, HIBYTE(pstDpInfo->stDpTimingInfo.usHTotal));
    ScalerSetByte(PB8_42_MN_DPF_HTT_L, LOBYTE(pstDpInfo->stDpTimingInfo.usHTotal));

    // Set HStart
    ScalerSetByte(PB8_43_MN_DPF_HST_M, HIBYTE(pstDpInfo->stDpTimingInfo.usHStart));
    ScalerSetByte(PB8_44_MN_DPF_HST_L, LOBYTE(pstDpInfo->stDpTimingInfo.usHStart));

    // Set HWidth
    ScalerSetByte(PB8_45_MN_DPF_HWD_M, HIBYTE(pstDpInfo->stDpTimingInfo.usHWidth));
    ScalerSetByte(PB8_46_MN_DPF_HWD_L, LOBYTE(pstDpInfo->stDpTimingInfo.usHWidth));

    // Set HSW
    ScalerSetByte(PB8_47_MN_DPF_HSW_M, HIBYTE(pstDpInfo->stDpTimingInfo.usHSWidth));
    ScalerSetByte(PB8_48_MN_DPF_HSW_L, LOBYTE(pstDpInfo->stDpTimingInfo.usHSWidth));

    // Set HSP = Positive
    ScalerSetBit(PB8_47_MN_DPF_HSW_M, ~_BIT7, ((BYTE)_SYNC_POLARITY_POSITIVE) << 7);

    // Set Vtotal
    ScalerSetByte(PB8_49_MN_DPF_VTT_M, HIBYTE(pstDpInfo->stDpTimingInfo.usVTotal));
    ScalerSetByte(PB8_4A_MN_DPF_VTT_L, LOBYTE(pstDpInfo->stDpTimingInfo.usVTotal));

    // Set VStart
    ScalerSetByte(PB8_4B_MN_DPF_VST_M, HIBYTE(pstDpInfo->stDpTimingInfo.usVStart));
    ScalerSetByte(PB8_4C_MN_DPF_VST_L, LOBYTE(pstDpInfo->stDpTimingInfo.usVStart));

    // Set VHeight
    ScalerSetByte(PB8_4D_MN_DPF_VHT_M, HIBYTE(pstDpInfo->stDpTimingInfo.usVHeight));
    ScalerSetByte(PB8_4E_MN_DPF_VHT_L, LOBYTE(pstDpInfo->stDpTimingInfo.usVHeight));

    // Set VSW
    ScalerSetByte(PB8_4F_MN_DPF_VSW_M, HIBYTE(pstDpInfo->stDpTimingInfo.usVSWidth));
    ScalerSetByte(PB8_50_MN_DPF_VSW_L, LOBYTE(pstDpInfo->stDpTimingInfo.usVSWidth));

    // Set VSP = Positive
    ScalerSetBit(PB8_4F_MN_DPF_VSW_M, ~_BIT7, ((BYTE)_SYNC_POLARITY_POSITIVE) << 7);

    // Set Color Format
    ScalerDpMacStreamRx1VideoSetting_8b10b();


    //////////////////////////////////////
    // Display Format Generator Setting //
    //////////////////////////////////////

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_ALPM_ENABLE() == _TRUE)
    {
#if(_DP_PR_MODE_SUPPORT == _ON)
        if(GET_DP_MAC_STREAM_RX1_PR_ENABLE_8B10B() == _TRUE)
        {
            // Set Vstart as Alpm T1 Count
            ScalerSetByte(PB8_67_ALPM_T1_L, TO_WORD(ScalerGetByte(PB9_14_MSA_VST_0), ScalerGetByte(PB9_15_MSA_VST_1)));

            // Set 1 line as Alpm T2 Set Up Time
            ScalerSetBit(PB8_96_DP_ALPM0, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);
        }
#endif
        ////////////////////////
        // BE Frame Sync Mode //
        ////////////////////////

        // Set BE to VS Delay
        ScalerDpMacStreamRx1SetBxToVsDelay_8b10b(pstDpInfo);

        // Set 1 when using framesync be mode otherwise set to 0
        ScalerSetBit(PB8_51_MN_DPF_BG_RED_M, ~_BIT4, _BIT4);

        // Set DRR mode enable and DRR mode sel vs doesn't overlap first hs
        ScalerSetBit(PB8_90_DP_RSV0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Set vstart zero mode
        ScalerSetBit(PB8_94_DP_RSV4, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Set display format Be framesync Mode
        ScalerDpMacStreamRx1SetDPFRegenMode(_DPF_MODE_FRAME_SYNC_BE);

        // Use vbid[0] rising edge to do vblktovs for Be framesync Mode
        ScalerSetBit(PB8_31_DP_OUTPUT_CTRL, ~(_BIT5 | _BIT3), 0x00);
    }
    else
#endif
    {
#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
        {
#if(_FW_DP_RX_FREESYNC_DPF_MODE_FRAME_SYNC_BE_DRR == _ON)
            ////////////////////////
            // BE Frame Sync Mode //
            ////////////////////////

            // Set BE to VS Delay
            ScalerDpMacStreamRx1SetBxToVsDelay_8b10b(pstDpInfo);

            // Set 1 when using framesync be mode otherwise set to 0
            ScalerSetBit(PB8_51_MN_DPF_BG_RED_M, ~_BIT4, _BIT4);

            // Set DRR mode enable and DRR mode sel vs doesn't overlap first hs
            ScalerSetBit(PB8_90_DP_RSV0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Set vstart zero mode
            ScalerSetBit(PB8_94_DP_RSV4, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Set display format Be framesync Mode
            ScalerDpMacStreamRx1SetDPFRegenMode(_DPF_MODE_FRAME_SYNC_BE);

            // Use vbid[0] rising edge to do vblktovs for Be framesync Mode
            ScalerSetBit(PB8_31_DP_OUTPUT_CTRL, ~(_BIT5 | _BIT3), 0x00);

            DebugMessageDpRx("DP MAC RX1: BE Frame Sync Mode Enabled!!", ScalerGetByte(PB8_30_DPF_CTRL_0));
#else
            //////////////////
            // DE Only Mode //
            //////////////////

            // Set Vsync Front Porch for DE Only Mode
            ScalerSetByte(PB8_40_VS_FRONT_PORCH, GET_DP_MAC_STREAM_RX1_VFRONT_PORCH());

            // Set BS to HS Delay
            ScalerDpMacStreamRx1SetBsToHsDelay_8b10b(&(pstDpInfo->stDpTimingInfo));

            // Enable DP Freesync Mode(DRR Mode)
            ScalerSetBit(PB8_90_DP_RSV0, ~_BIT0, _BIT0);

            // Set DE Only Mode
            ScalerDpMacStreamRx1SetDPFRegenMode(_DPF_MODE_DE_ONLY);

            DebugMessageDpRx("DP MAC RX1: DE Only Mode Enabled!!", ScalerGetByte(PB8_30_DPF_CTRL_0));
#endif

            DebugMessageDpRx("DP MAC RX1: Freesync Mode Enabled!!", ScalerGetByte(PB8_30_DPF_CTRL_0));
        }
        else
#endif
        {
            // Disable DP Freesync Mode(DRR mode)
            ScalerSetBit(PB8_90_DP_RSV0, ~_BIT0, 0x00);

            if(bDeOnlyModeJudge == _TRUE)
            {
                //////////////////
                // DE Only Mode //
                //////////////////

                // Set Vsync Front Porch for DE Only Mode
                ScalerSetByte(PB8_40_VS_FRONT_PORCH, GET_DP_MAC_STREAM_RX1_VFRONT_PORCH());

                // Set BS to HS Delay
                ScalerDpMacStreamRx1SetBsToHsDelay_8b10b(&(pstDpInfo->stDpTimingInfo));

                // Set DE Only Mode
                ScalerDpMacStreamRx1SetDPFRegenMode(_DPF_MODE_DE_ONLY);

                DebugMessageDpRx("DP MAC RX1: DE_Only Mode Use !!!", ScalerGetByte(PB8_30_DPF_CTRL_0));
            }
            else
            {
                /////////////////////////
                // Full Last Line Mode //
                /////////////////////////

                // Set BS to VS Delay
                ScalerDpMacStreamRx1SetBxToVsDelay_8b10b(pstDpInfo);

                // Set Full Last Line Mode
                ScalerDpMacStreamRx1SetDPFRegenMode(_DPF_MODE_FULL_LAST_LINE);
            }
        }
    }

    // Choose VS Rising to Reset FIFO
    ScalerSetBit(PB8_21_PG_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), 0x00);

    // Solve Abnormal Full Flag and Max. FIFO Level While Resetting by VSync
    ScalerSetBit(PB8_26_SRAM_BIST_1, ~_BIT7, _BIT7);

    return _TRUE;
}

//--------------------------------------------------
// Description  : On Line Check DP 8b10b stability
// Input Value  : None
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerDpMacStreamRx1StableDetect_8b10b(EnumInputPort enumInputPort)
{
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(_DP_MAC_1);

    enumDpMacStreamSourceType = enumDpMacStreamSourceType;

    if(ScalerDpPhyRxEnableEyeMonitor(enumInputPort) == _TRUE)
    {
        ScalerDpPhyRxEyeMonitor(enumInputPort);
    }

#if(_DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER == _ON)
    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
#else
    if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
       (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
#endif
    {
        DebugMessageDpRx("7. DP MAC RX1: Power Down", 0);

        return _FALSE;
    }

    if((ScalerDpMacDphyRxCDRCheck(enumInputPort) == _FALSE) ||
       (ScalerDpMacDphyRxAlignCheck(enumInputPort) == _FALSE) ||
       (ScalerDpMacDphyRxDecodeCheck(enumInputPort) == _FALSE) ||
       ((ScalerDpPhyRxDFECheck(enumInputPort) == _FALSE) && (ScalerDpMacDphyRxSignalCheck(enumInputPort) == _FALSE)))
    {
        DebugMessageDpRx("7. DP MAC RX1: Link Fail", 0);

        return _FALSE;
    }

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
    if(ScalerDpMacDphyRxCheck8b10bDecErrorStatus(enumInputPort) == _FAIL)
    {
        DebugMessageDpRx("7. DP 8b10b Acc Dec Err", 0);

        return _FALSE;
    }
#endif

    if(ScalerDpMacStreamRxBsMissCheck(enumDpMacStreamSourceType) == _TRUE)
    {
        DebugMessageDpRx("7. DP MAC RX1: BS Unstable", 0);

        return _FALSE;
    }

    if(ScalerDpMacStreamRx1GetVideoStream() == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Video Stream Fail", 0);

        return _FALSE;
    }

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)

    if(ScalerDpMacDscRxDscStreamGetChange(_DP_MAC_1) == _ENABLE)
    {
        DebugMessageDpRx("7. DP MAC RX1: DSC Capability Change", 0);

        ScalerDpMacDscRxDscStreamClearChange(_DP_MAC_1);

        return _FALSE;
    }

    if(ScalerDpMacStreamRx1GetDscReorder() == _TRUE)
    {
        if(ScalerDpMacStreamRx1DscStreamCheck() == _FALSE)
        {
            DebugMessageDpRx("7. DP MAC RX1: Video Stream Compression Disable", 0);

            return _FALSE;
        }

        if(ScalerDpMacStreamRx1MiscCheck_8b10b() == _FALSE)
        {
            DebugMessageDpRx("7. DP MAC RX1: Misc Change", 0);

            return _FALSE;
        }

        if(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1) != _DSC_MAC_NONE)
        {
            BYTE ucDscMac = ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1);

            if(ScalerDscDecoderPpsChangeCheck(ucDscMac) == _FALSE)
            {
                ScalerDpMacDscFifoStatusIrqProc(_DP_MAC_1, ScalerDscDecoderGetFifoStatus(ucDscMac));

                DebugMessageDpRx("7. DP MAC RX1: DSC PPS Change", 0);

                return _FALSE;
            }

            if(ScalerDscDecoderFifoCheck(ucDscMac, _DSC_FIFO_STABLE_CHECK) == _FALSE)
            {
                ScalerDpMacDscFifoStatusIrqProc(_DP_MAC_1, ScalerDscDecoderGetFifoStatus(ucDscMac));

                DebugMessageDpRx("7. DP MAC RX1: DSC Fifo Under/Overflow", 0);

                return _FALSE;
            }
        }
    }
    else
#endif
    {
        if(GET_DP_MAC_STREAM_RX1_STREAM_DATA_PATH() == _DATA_PATH_VESA)
        {
#if((_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
            if(ScalerDpMacStreamRxDscGetFlagStatus(enumDpMacStreamSourceType) == _TRUE)
            {
                if(ScalerDpMacStreamRx1DscStreamCheck() == _TRUE)
                {
                    DebugMessageDpRx("7. DP MAC RX1: Stable Detect DSC Enable", 0);

                    return _FALSE;
                }
            }
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
            if(GET_DP_MAC_STREAM_RX1_MISC_CHECK_FAIL() == _TRUE)
            {
                CLR_DP_MAC_STREAM_RX1_MISC_CHECK_FAIL();

                DebugMessageDpRx("7. DP MAC RX1: Misc Check Fail", 0);

                return _FALSE;
            }
#endif

            if(ScalerDpMacStreamRx1MiscCheck_8b10b() == _FALSE)
            {
#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
                if(ScalerDpMacStreamRx1GetMsaDebounceStatus() == _DISABLE)
                {
                    ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);

                    if(ScalerDpMacStreamRx1MiscCheck_8b10b() == _FALSE)
                    {
                        DebugMessageDpRx("7. DP MAC RX1: Misc Change", 0);

                        return _FALSE;
                    }
                }
                else
#endif
                {
                    DebugMessageDpRx("7. DP MAC RX1: Misc Change", 0);

                    return _FALSE;
                }
            }

            if(ScalerDpMacStreamRx1FifoCheck_8b10b(_DP_FIFO_POLLING_CHECK) == _FALSE)
            {
                DebugMessageDpRx("7. DP MAC RX1: Fifo Under/Overflow", 0);

                return _FALSE;
            }

            if(ScalerDpMacStreamRx1MSAActiveChange_8b10b() == _TRUE)
            {
#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
                if(ScalerDpMacStreamRx1GetMsaDebounceStatus() == _DISABLE)
                {
                    ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);

                    if(ScalerDpMacStreamRx1MSAActiveChange_8b10b() == _TRUE)
                    {
                        DebugMessageDpRx("7. DP MAC RX1: Misc Change", 0);

                        return _FALSE;
                    }
                }
                else
#endif
                {
                    DebugMessageDpRx("7. DP MAC RX1: MSA Timing Change", 0);

                    return _FALSE;
                }
            }
        }
    }

#if(_DP_FORCE_FREESYNC_SUPPORT == _OFF)
#if(_DP_FREESYNC_SUPPORT == _ON)
    if(ScalerDpMacStreamRx1GetFreeSyncStatusChange() == _TRUE)
    {
        return _FALSE;
    }
#endif
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
    if(ScalerDpMacStreamRxPRModeGetFlagChange(enumDpMacStreamSourceType) == _TRUE)
    {
        return _FALSE;
    }
#endif

    // Clear CPIRQ Flag
    ScalerDpMacDphyRxCheckHdcpCpirqStatus(enumInputPort);

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
    if(ScalerDpMacStreamRx1GetDscReorder() == _TRUE)
    {
        if(ScalerDscDecoderDpCrcCalculate(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1)) == _TRUE)
        {
            ScalerDpMacStreamRx1CrcCalculate_8b10b();
        }
    }
    else
#endif
    {
        ScalerDpMacStreamRx1CrcCalculate_8b10b();
    }

    ScalerDpMacStreamRx1SdpDataDetect();

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_STREAM_DATA_PATH() == _DATA_PATH_DSC_REORDER)
    {
        if(ScalerDpMacStreamRx1DscStreamCheck() == _FALSE)
        {
            DebugMessageDpRx("7. DP MAC RX1: Video Stream Compression Disable", 0);

            return _FALSE;
        }

        if(ScalerDpMacStreamRx1MiscCheck_8b10b() == _FALSE)
        {
            DebugMessageDpRx("7. DP MAC RX1: Misc Change", 0);

            return _FALSE;
        }

        // DP Mac Rx Check PPS SDP Change
        if(ScalerDpMacStreamRx1GetSdpChanged(_DP_SDP_TYPE_PPS) == _TRUE)
        {
            DebugMessageDpRx("7. DP MAC RX1: PPS SDP Change", 0);

            return _FALSE;
        }
    }
#endif

    return _TRUE;
}

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Color Space Chg Watch Dog Status
// Input Value  : None
// Output Value : True --> WD enable
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetColorSpaceChgWDStatus(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        if(ScalerGetBit(P7E_96_DP_MSA_COLOR_CTRL1, _BIT4) == _BIT4)
        {
            return _TRUE;
        }
    }
    else
#endif
    {
        if(ScalerGetBit(P26_96_DP_MSA_COLOR_CTRL1, _BIT4) == _BIT4)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DP Fifo IRQ Status
// Input Value  : None
// Output Value : True --> IRQ enable
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetFifoIRQStatus(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        if(ScalerGetBit(P75_3A_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) != 0x00)
        {
            return _TRUE;
        }
    }
    else
#endif
    {
        if(ScalerGetBit(PB9_3E_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) != 0x00)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Clr Fifo Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1ClrFifoFlag(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        ScalerSetByte(P70_21_PG_CTRL_1, 0x7F);
    }
    else
#endif
    {
        ScalerSetByte(PB8_21_PG_CTRL_1, 0x7F);
    }
}

//--------------------------------------------------
// Description  : Seamless Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DMColorFormatChgWoResetSetting(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
    bit bColorSpaceWDBackup = ScalerDpMacStreamRx1GetColorSpaceChgWDStatus();
#endif
    bit bDpFifoIRQBackup = ScalerDpMacStreamRx1GetFifoIRQStatus();
    bit bDpFifoWDBackup = ScalerDpMacStreamRx1GetFifoWDStatus();

    CLR_DP_MAC_STREAM_RX1_FIFO_IRQ_TRIGGER_CHECK();

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
    if(ScalerDpRxColorSpaceAndDepthChangeFlagValidCheck() == _TRUE)
    {
        // Disable DP Color Space Change WD
        ScalerDpMacStreamRx1SetColorSpaceChangeWD(_DISABLE);
    }
#endif

    // Disable DP overflow/ underflow IRQ
    ScalerDpMacStreamRx1SetFifoIRQ(_DISABLE);

    // Disable DP overflow/ underflow WD
    ScalerDpMacStreamRx1SetFifoWD(_DISABLE);

    if(GET_DP_MAC_STREAM_RX1_FIFO_IRQ_TRIGGER_CHECK() == _FALSE)
    {
        // YUV422 12bpc --> YUV444/RGB 8bpc or YUV444/RGB 8bit --> YUV422 12pc Seamless Condition, Other Not seamless Condition
        DebugMessageDpRx("DP MAC RX1: SDR_DM Seamless flow", 0x00);

        // Set Color Format
        ScalerDpMacStreamRx1SetColorInfo();
        ScalerDpMacStreamRx1VideoSetting();

        // Use for Video/DisplayFormat/Measure relative Settings.
        ScalerDpMacStreamRx1MacSetting();

        // DP Extern Info Setting For Other IP to Use
        ScalerDpRxStreamExternInfoSetting(enumInputPort);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
        {
            // Polling 1 Frame Vertical BS
            ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, P75_01_DP_VBID, _BIT0, _TRUE);
            ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, P75_01_DP_VBID, _BIT0, _FALSE);
            ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, P75_01_DP_VBID, _BIT0, _TRUE);
        }
        else
#endif
        {
            // Polling 1 Frame Vertical BS
            ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, PB9_01_DP_VBID, _BIT0, _TRUE);
            ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, PB9_01_DP_VBID, _BIT0, _FALSE);
            ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, PB9_01_DP_VBID, _BIT0, _TRUE);
        }

        // Clr Fifo Flag
        ScalerDpMacStreamRx1ClrFifoFlag();

        if(bDpFifoWDBackup == _TRUE)
        {
            // Enable DP overflow/ underflow WD
            ScalerDpMacStreamRx1SetFifoWD(_ENABLE);
        }

        if(bDpFifoIRQBackup == _TRUE)
        {
            // Enable DP overflow/ underflow IRQ
            ScalerDpMacStreamRx1SetFifoIRQ(_ENABLE);
        }

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
        if(ScalerDpRxColorSpaceAndDepthChangeFlagValidCheck() == _TRUE)
        {
            if(bColorSpaceWDBackup == _TRUE)
            {
                // Enable DP Color Space Change WD
                ScalerDpMacStreamRx1SetColorSpaceChangeWD(_ENABLE);
            }
        }
#endif
    }
}
#endif

//--------------------------------------------------
// Description  : DP Video Setting for PG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1VideoSetting(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacStreamRx1VideoSetting_128b132b();
    }
    else
#endif
    {
        ScalerDpMacStreamRx1VideoSetting_8b10b();
    }
}

//--------------------------------------------------
// Description  : Check DP Misc Information 8b10b
// Input Value  : None
// Output Value : True --> DP Misc Check Ok
//--------------------------------------------------
bit ScalerDpMacStreamRx1MiscCheck_8b10b(void)
{
#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
    bit bColorFormatChange = _FALSE;
#endif

    // Pop up Main Stream Attributes
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Check MISC1[6]
    if((ScalerGetBit(PB9_03_MN_STRM_ATTR_MISC1, _BIT6)) == _BIT6)
    {
        return ScalerDpMacStreamRx1VscCheck();
    }
    else
    {
        // Get MISC Info
        BYTE ucMisc0 = ScalerGetByte(PB9_02_MN_STRM_ATTR_MISC);
        BYTE ucColorSpaceValue = (ScalerGetBit(PB9_03_MN_STRM_ATTR_MISC1, _BIT7)) | (ucMisc0 & (_BIT2 | _BIT1));

        // Color Space Check
        // Color format info source change from VSC --> MISC
        if(GET_DP_MAC_STREAM_RX1_VSC_SDP_COLOR_MODE() == _TRUE)
        {
            switch(ucColorSpaceValue)
            {
                case _BIT1:
                    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_YCBCR422)
                    {
                        DebugMessageDpRx("DP MAC RX1: Misc change: Color Format, _COLOR_SPACE_YCBCR422", 0);
                        return _FALSE;
                    }
                    break;

                case _BIT2:
                    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_YCBCR444)
                    {
                        DebugMessageDpRx("DP MAC RX1: Misc change: Color Format, _COLOR_SPACE_YCBCR444", 0);
                        return _FALSE;
                    }
                    break;

                case _BIT7:
                    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_Y_ONLY)
                    {
                        DebugMessageDpRx("DP MAC RX1: Misc change: Color Format, _COLOR_SPACE_Y_ONLY", 0);
                        return _FALSE;
                    }
                    break;

                case (_BIT7 | _BIT1):
                    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_RAW)
                    {
                        DebugMessageDpRx("DP MAC RX1: Misc change: Color Format, _COLOR_SPACE_RAW", 0);
                        return _FALSE;
                    }
                    break;

                default:
                    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_RGB)
                    {
                        DebugMessageDpRx("DP MAC RX1: Misc change: Color Format, _COLOR_SPACE_RGB", 0);
                        return _FALSE;
                    }
                    break;
            }
        }
        else
        {
            if(ucColorSpaceValue != GET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE())
            {
                DebugMessageDpRx("DP MAC RX1: Misc change: Color Space", 0);

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
                if(GET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    SET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE(ucColorSpaceValue);
                    bColorFormatChange = _TRUE;
                }
                else
#endif
                {
                    return _FALSE;
                }
            }
        }

        // Color Depth Check
        if((((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5) != GET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE())
        {
            DebugMessageDpRx("DP MAC RX1: Misc change: Color Depth", (((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5));

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
            if(GET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                SET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE(((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5);
                bColorFormatChange = _TRUE;
            }
            else
#endif
            {
                return _FALSE;
            }
        }

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
        if(bColorFormatChange == _TRUE)
        {
            ScalerDpMacStreamRx1DMColorFormatChgWoResetSetting();
        }
#endif

        // Colorimetry Check
        if(GET_DP_MAC_STREAM_RX1_COLORIMETRY() != _COLORIMETRY_EXT)
        {
            if(((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1) != GET_DP_MAC_STREAM_RX1_COLORIMETRY_PREVALUE())
            {
                DebugMessageDpRx("DP MAC RX1: Misc change: Colorimetry", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_MAC_STREAM_RX1_COLORIMETRY_PREVALUE((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
                    ScalerDpMacStreamRx1ColorimetrySetting();
                    SET_DP_MAC_STREAM_RX1_COLORIMETRY_CHANGED();
                }
            }
        }
        else
        {
            DebugMessageDpRx("DP MAC RX1: Misc change: Colorimetry", 0);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_COLORIMETRY_PREVALUE((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
                ScalerDpMacStreamRx1ColorimetrySetting();
                SET_DP_MAC_STREAM_RX1_COLORIMETRY_CHANGED();
            }
        }

        // Dynamic Range Check
#if(_YCC_QUANTIZATION_RANGE_FUNCTION == _ON)
        if((GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422))
        {
            if(((ucMisc0 & _BIT3) >> 3) != GET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE())
            {
                DebugMessageDpRx("DP MAC RX1: Misc change: Dynamic Range", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE((ucMisc0 & _BIT3) >> 3);
                    ScalerDpMacStreamRx1QuantizationSetting();
                    SET_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED();
                }
            }
        }
        else
#endif
        {
#if(_RGB_QUANTIZATION_RANGE_FUNCTION == _ON)
            if(((ucMisc0 & _BIT3) >> 3) != GET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE())
            {
                DebugMessageDpRx("DP MAC RX1: Misc change: Dynamic Range", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE((ucMisc0 & _BIT3) >> 3);
                    ScalerDpMacStreamRx1QuantizationSetting();
                    SET_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED();
                }
            }
#endif
        }

#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _FALSE)
#endif
        {
            // Get HSW
            PDATA_WORD(0) = (ScalerGetWord(PB9_0E_MSA_HSW_0) & 0x7FFF);

            // Get VSW
            PDATA_WORD(1) = (ScalerGetWord(PB9_18_MSA_VSW_0) & 0x7FFF);

            if((PDATA_WORD(0) == 0x00) || (PDATA_WORD(1) == 0x00))
            {
                return _FALSE;
            }
        }

        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Check DP MSA Vactive / Hactive Change 8b10b
// Input Value  : None
// Output Value : True --> DP Vactive / Hactive Information Check Ok
//--------------------------------------------------
bit ScalerDpMacStreamRx1MSAActiveChange_8b10b(void)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Display Format Hactive
    PDATA_WORD(0) = ScalerGetWord(PB8_45_MN_DPF_HWD_M);

    // Get MSA Hactive
    PDATA_WORD(1) = ScalerGetWord(PB9_0C_MSA_HWD_0);

    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        PDATA_WORD(1) /= 2;
    }

    // Get Display Format Vactive
    PDATA_WORD(2) = ScalerGetWord(PB8_4D_MN_DPF_VHT_M);

    // Get MSA Vactive
    PDATA_WORD(3) = ScalerGetWord(PB9_16_MSA_VHT_0);

    if((PDATA_WORD(0) != PDATA_WORD(1)) || (PDATA_WORD(2) != PDATA_WORD(3)))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Interlace by VBID or Measure 8b10b
// Input Value  : None
// Output Value : True --> Interlace
//--------------------------------------------------
bit ScalerDpMacStreamRx1InterlaceCheck_8b10b(StructDpInfo *pstDpInfo)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
    WORD usTempVTotal = pstDpInfo->stDpTimingInfo.usVTotal;
    WORD usHTotalCount = 0;

    // Convert HTotal Count from 1/2 Link Clk to GDI Clk
    usHTotalCount = ((DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount * _GDIPHY_RX_GDI_CLK_KHZ * 2 + ((pstDpInfo->stDpLinkInfo.ulLinkClockHz / 1000) >> 1)) / (pstDpInfo->stDpLinkInfo.ulLinkClockHz / 1000);

#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_JUDGE_OOR() == _TRUE)
    {
        pstDpInfo->stDpLinkInfo.b1InterlaceOddMode = _FALSE;
    }
    else
#endif
    {
        // if VTotal Difference > 1/2 HTotal
        if((ABSDWORD(pstDpInfo->stDpLinkInfo.ulVBsToBsCountN, pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1)) > (usHTotalCount / 2))
        {
            // Set VTotal as MSA info if MST is Enabled
            if(ScalerDpRxGetSrcMstEnable(enumInputPort) == _TRUE)
            {
                // Set VTotal As the Smaller One
                usTempVTotal = (pstDpInfo->stDpTimingInfo.usVTotal < pstDpInfo->stDpTimingInfo.usVTotalOdd) ? pstDpInfo->stDpTimingInfo.usVTotal : pstDpInfo->stDpTimingInfo.usVTotalOdd;
            }
            else
            {
                if(ScalerDpMacStreamRx1InterlaceVtotalGetMSACheck_8b10b(pstDpInfo) == _TRUE)
                {
                    usTempVTotal = TO_WORD(ScalerGetByte(PB9_10_MSA_VTTE_0), ScalerGetByte(PB9_11_MSA_VTTE_1));
                }
                else
                {
                    if(pstDpInfo->stDpLinkInfo.ulVBsToBsCountN < pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1)
                    {
                        usTempVTotal = ((pstDpInfo->stDpLinkInfo.ulVBsToBsCountN + (usHTotalCount >> 1)) / usHTotalCount);
                    }
                    else
                    {
                        usTempVTotal = ((pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1 + (usHTotalCount >> 1)) / usHTotalCount);
                    }
                }
            }

            pstDpInfo->stDpLinkInfo.b1InterlaceOddMode = _TRUE;
        }
        else
        {
            pstDpInfo->stDpLinkInfo.b1InterlaceOddMode = _FALSE;
        }
    }

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
    // Check N and N+1 Frame Vs2Vs Count
    if((pstDpInfo->stDpLinkInfo.b1InterlaceOddMode) == _TRUE)
    {
        // Enable DP Interlace
        ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

        // Enable Field Sync by BE
        ScalerSetBit(PB8_91_DP_RSV1, ~(_BIT6 | _BIT0), _BIT0);

        // HW Check Interlace
        if(pstDpInfo->stDpLinkInfo.b1HwInterlaceDetect == _TRUE)
        {
            // Field reference HW
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);
        }
        else
        {
            // Field reference VBID
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);
        }

        // Set Vtt odd fw mode
        SET_DP_MAC_STREAM_RX1_INTERLACE_VTT_FW_MODE_8B10B(_ODD);

        pstDpInfo->stDpTimingInfo.usVTotal = usTempVTotal;

        return _TRUE;
    }
    else
    {
        // Check VBID Field Toggle and VBID Interlace Info
        if((pstDpInfo->stDpLinkInfo.b1InterlaceFieldN != pstDpInfo->stDpLinkInfo.b1InterlaceFieldN1) && (ScalerGetBit(PB9_01_DP_VBID, _BIT2) == _BIT2))
        {
            // Enable DP Interlace
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

            // Field reference VBID
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

            // Enable Field Sync by BE
            ScalerSetBit(PB8_91_DP_RSV1, ~(_BIT6 | _BIT0), _BIT0);

            // Set Vtt Even fw mode
            SET_DP_MAC_STREAM_RX1_INTERLACE_VTT_FW_MODE_8B10B(_EVEN);

            pstDpInfo->stDpTimingInfo.usVTotal = usTempVTotal;

            return _TRUE;
        }

        // Enable DP Progressive Mode
        ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), 0x00);

        // Field reference VBID
        ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

        // Enable Field Sync by VBID
        ScalerSetBit(PB8_91_DP_RSV1, ~(_BIT6 | _BIT0), 0x00);

        // Set Vtt Even fw mode
        SET_DP_MAC_STREAM_RX1_INTERLACE_VTT_FW_MODE_8B10B(_EVEN);

        return _FALSE;
    }
#else
    // Check if VBID[2] is Interlace Mode
    if(ScalerGetBit(PB9_01_DP_VBID, _BIT2) == _BIT2)
    {
        // Enable DP Interlace
        ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

        if(pstDpInfo->stDpLinkInfo.b1InterlaceOddMode == _FALSE)
        {
            // Disable DP Interlace
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), 0x00);
        }

        // Check Interlace Field Toggle by Frame
        if(pstDpInfo->stDpLinkInfo.b1InterlaceFieldN != pstDpInfo->stDpLinkInfo.b1InterlaceFieldN1)
        {
            if(pstDpInfo->stDpLinkInfo.b1InterlaceOddMode == _TRUE)
            {
                // Field Signal Refer to HW
                ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);
            }
            else
            {
                // Field Signal Refer to VBID
                ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);
            }

            if((pstDpInfo->stDpLinkInfo.b1HwFakeInterlaceDetect == _FALSE) &&
               (((pstDpInfo->stDpLinkInfo.b1InterlaceFieldN == _TRUE) && (pstDpInfo->stDpLinkInfo.b1InterlaceFieldN1 == _FALSE) &&
                 (pstDpInfo->stDpLinkInfo.ulVBsToBsCountN < pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1)) ||
                ((pstDpInfo->stDpLinkInfo.b1InterlaceFieldN == _FALSE) && (pstDpInfo->stDpLinkInfo.b1InterlaceFieldN1 == _TRUE) &&
                 (pstDpInfo->stDpLinkInfo.ulVBsToBsCountN > pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1))))
            {
                // Field inverse enable
                ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), _BIT4);
            }
        }
        else
        {
            // Field reference HW
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);
        }

        pstDpInfo->stDpTimingInfo.usVTotal = usTempVTotal;

        return _TRUE;
    }
    else if(pstDpInfo->stDpLinkInfo.b1InterlaceOddMode == _TRUE)
    {
        // Delay a Complete Frame
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        if(pstDpInfo->stDpLinkInfo.b1HwFakeInterlaceDetect == _TRUE)
        {
            DebugMessageDpRx("DP MAC RX1: Fake Interlace", 0);
            pstDpInfo->stDpLinkInfo.b1InterlaceOddMode = _FALSE;
        }
        else
        {
            // Enable interlace mode, field reference HW
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), (_BIT7 | _BIT6));

            pstDpInfo->stDpTimingInfo.usVTotal = usTempVTotal;

            return _TRUE;
        }
    }

    // Disable DP Interlace
    ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), 0x00);

    return _FALSE;
#endif
}

//--------------------------------------------------
// Description  : Judge Vtotal from MSA or not
// Input Value  : None
// Output Value : TRUE --> Get Vtotal from MSA
//--------------------------------------------------
bit ScalerDpMacStreamRx1InterlaceVtotalGetMSACheck_8b10b(StructDpInfo *pstDpInfo)
{
    WORD usVfreq = 0;

    // Vfreq (unit : 0.01Hz)
    usVfreq = _GDIPHY_RX_GDI_CLK_KHZ * 1000 * 100 / pstDpInfo->stDpLinkInfo.ulVBsToBsCountN;

    // Solve interlace issue for Astro VG870 for timing : EIA1920 x 1080i @ 119.88 Hz
    // Central Vfreq = 120Hz +/- 1% = 118.8Hz ~ 121.2Hz
    if((TO_WORD(ScalerGetByte(PB9_08_MSA_HTT_0), ScalerGetByte(PB9_09_MSA_HTT_1)) == 2200) &&
       (TO_WORD(ScalerGetByte(PB9_10_MSA_VTTE_0), ScalerGetByte(PB9_11_MSA_VTTE_1)) == 562) &&
       ((usVfreq > 11880) && (usVfreq < 12120)) && (ScalerGetBit(PB9_01_DP_VBID, _BIT2) == _BIT2))
    {
        return _TRUE;
    }

    // Solve interlace issue for QD-980 for timing : 480i @ 60 Hz
    // Central Vfreq = 60Hz +/- 1% = 59.4Hz ~ 60.6Hz
    if((TO_WORD(ScalerGetByte(PB9_08_MSA_HTT_0), ScalerGetByte(PB9_09_MSA_HTT_1)) == 858) &&
       (TO_WORD(ScalerGetByte(PB9_10_MSA_VTTE_0), ScalerGetByte(PB9_11_MSA_VTTE_1)) == 262) &&
       ((usVfreq > 5940) && (usVfreq < 6060)) && (ScalerGetBit(PB9_01_DP_VBID, _BIT2) == _BIT2))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Reset Interlace Mode
// Input Value  : EnumHDCPType
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1InterlaceReset_8b10b(void)
{
    // Interlace mode disable, refer to VBID[1], Field Inverse Disable, Clear Hwardware Detect Interlace Flag, Clear Fake Interlace Flag
    ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT5 | _BIT0));

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
    // Enable Field Sync by VBID
    ScalerSetBit(PB8_91_DP_RSV1, ~(_BIT6 | _BIT0), 0x00);

    // Set Vtt odd fw mode
    SET_DP_MAC_STREAM_RX1_INTERLACE_VTT_FW_MODE_8B10B(_ODD);
#endif
}

//--------------------------------------------------
// Description  : Mac FIFO Check 8b10b
// Input Value  : None
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
bit ScalerDpMacStreamRx1FifoCheckProc_8b10b(EnumDpFifoCheckCondition enumFifoCheckCondition, StructDpInfo *pstDpInfo)
{
    if(ScalerDpMacStreamRx1FifoCheck_8b10b(enumFifoCheckCondition) == _FALSE)
    {
#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
        {
            return _FAIL;
        }
        else
#endif
        {
            ScalerDpMacStreamRx1AdjustVsyncDelay_8b10b(pstDpInfo);

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if(ScalerSyncCheckUrgentEvent() == _TRUE)
            {
                return _FAIL;
            }
#endif

            if(ScalerDpMacStreamRx1FifoCheck_8b10b(enumFifoCheckCondition) == _FALSE)
            {
                ScalerDpMacStreamRx1AdjustVsyncDelay_8b10b(pstDpInfo);

#if(_URGENT_EVENT_CHECK_MODE == _ON)
                if(ScalerSyncCheckUrgentEvent() == _TRUE)
                {
                    return _FAIL;
                }
#endif

                if(ScalerDpMacStreamRx1FifoCheck_8b10b(enumFifoCheckCondition) == _FALSE)
                {
                    return _FAIL;
                }
            }
        }
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP CRC Calculate 8b10b
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1CrcCalculate_8b10b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(GET_DP_MAC_STREAM_RX1_CRC_CALCULATE() == _TRUE)
    {
        DebugMessageDpRx("7. DP MAC RX1: CRC Test Start", 0);

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
        if(ScalerDpMacStreamRx1GetDscReorder() == _TRUE)
        {
            ScalerSetBit(PB8_70_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2), 0x00);
        }
        else
#endif
        {
            if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
            {
                ScalerSetBit(PB8_70_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2), _BIT4);
            }
            else if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
            {
                ScalerSetBit(PB8_70_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2), _BIT2);
            }
            else
            {
                ScalerSetBit(PB8_70_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2), 0x00);
            }
        }

        // Start CRC Calculation
        ScalerSetBit(PB8_70_DP_CRC_CTRL, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_70_DP_CRC_CTRL, _BIT6, _TRUE) == _TRUE)
        {
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
            if(ScalerDpMacStreamRx1GetDscReorder() == _TRUE)
            {
                if(ScalerDscDecoderFifoCheck(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1), _DSC_FIFO_POLLING_CHECK) == _TRUE)
                {
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x62, ScalerGetByte(PB8_72_DP_CRC_R_L));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x63, ScalerGetByte(PB8_71_DP_CRC_R_M));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x64, ScalerGetByte(PB8_74_DP_CRC_G_L));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x65, ScalerGetByte(PB8_73_DP_CRC_G_M));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x66, ScalerGetByte(PB8_76_DP_CRC_B_L));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x67, ScalerGetByte(PB8_75_DP_CRC_B_M));

                    CLR_DP_MAC_STREAM_RX1_CRC_CALCULATE();

                    // Update _TEST_CRC_COUNT
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x46, 0x21);
                }
            }
            else
#endif
            {
                if(ScalerDpMacStreamRx1FifoCheck_8b10b(_DP_FIFO_POLLING_CHECK) == _TRUE)
                {
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x40, ScalerGetByte(PB8_72_DP_CRC_R_L));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x41, ScalerGetByte(PB8_71_DP_CRC_R_M));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x42, ScalerGetByte(PB8_74_DP_CRC_G_L));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x43, ScalerGetByte(PB8_73_DP_CRC_G_M));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x44, ScalerGetByte(PB8_76_DP_CRC_B_L));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x45, ScalerGetByte(PB8_75_DP_CRC_B_M));

                    CLR_DP_MAC_STREAM_RX1_CRC_CALCULATE();

                    // Update _TEST_CRC_COUNT
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x46, 0x21);
                }
            }
        }

#if(_DP_PR_MODE_SUPPORT == _OFF)
        // Stop CRC Calculation
        ScalerSetBit(PB8_70_DP_CRC_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : DP RGB Output Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1AVMute_8b10b(void)
{
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
    BYTE ucDscMac = ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1);

    if(ScalerDscDecoderCheckFifoIRQ(ucDscMac) == _TRUE)
    {
        // Enable Output Force to Backgound Color
        ScalerDscDecoderSetForceToBackGround(ucDscMac, _ENABLE);

        // Disable fifo overflwo/ underflwo IRQ
        ScalerDscDecoderSetFifoIRQ(ucDscMac, _DISABLE);

        // Set D Domain Region Free run/ Force to Background
        ScalerDDomainResetDDomainRgn(GET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH());
    }
    else if(ScalerGetBit(PB9_3E_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
#else
    if(ScalerGetBit(PB9_3E_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
#endif
    {
        // Set D Domain Region Free run/ Force to Background
        ScalerDDomainResetDDomainRgn(GET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH());
    }

    // Disable BS Miss Detect IRQ
    ScalerDpMacStreamRx1SetBsMissDetectIRQ(_DISABLE);

    // Disable fifo overflwo/ underflwo IRQ
    ScalerSetBit(PB9_3E_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
    // Disable Msa Change IRQ
    ScalerDpMacStreamRx1SstSetMsaChangeIRQ_8b10b(_DISABLE);
#endif

    // Disable RGB Output
    ScalerSetBit(PB8_31_DP_OUTPUT_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_AUDIO_SUPPORT == _ON)
    // Disable Audio Channel
    ScalerDpAudioRx1AudioEnableControl(_DISABLE);
#endif

    ScalerDpMacStreamRx1SetSdpReset_8b10b();
}

//--------------------------------------------------
// Description  : DP BS to HS Delay Calculation
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
void ScalerDpMacStreamRx1SetBsToHsDelay_8b10b(StructTimingInfo *pstDpTimingInfo)
{
    WORD usFifoOffset = 0;
    WORD usBsToHsDelay = 0;

    // DP fifo size = 256 x 96bit
    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
    {
        // FifoOffset = (1/2 * (256 * 96) / (2 * depth per color)), color format is YCbCr 4:2:2
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE_8B10B / (4 * ((WORD)GET_DP_MAC_STREAM_RX1_COLOR_DEPTH()));
    }
    else
    {
        // FifoOffset = (1/2 * (256 * 96) / (3 * depth per color)), color format is RGB or YCbCr 4:4:4 or YCbCr 4:2:0 or others
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE_8B10B / (6 * ((WORD)GET_DP_MAC_STREAM_RX1_COLOR_DEPTH()));
    }

    // De Only Mode HW constraint: BS2HS delay < Htotal => 1/2 FIFO < H Width, Enough Margin = 1/2 H Width
    if(usFifoOffset > (pstDpTimingInfo->usHWidth >> 1))
    {
        usFifoOffset = (pstDpTimingInfo->usHWidth >> 1);
    }

    // Get BS to HS delay according to (HBlanking + 1/2 FIFO - HStart), Unit is 2 pixel mode
    usBsToHsDelay = ((pstDpTimingInfo->usHTotal - pstDpTimingInfo->usHWidth) + usFifoOffset - pstDpTimingInfo->usHStart) >> 1;

    // Set BS to HS Delay
    ScalerSetByte(PB8_38_BS2HS_0, HIBYTE(usBsToHsDelay));
    ScalerSetByte(PB8_39_BS2HS_1, LOBYTE(usBsToHsDelay));
}

//------------------------------------------------------
// Description  : Get Display Format Information 8b/10b
// Input Value  : Display Format Content
// Output Value : Display Format Information
//------------------------------------------------------
WORD ScalerDpMacStreamRx1GetDisplayFormat_8b10b(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo)
{
    switch(enumDpDisplayFormatInfo)
    {
        case _DP_V_HEIGHT:

            return (((WORD)ScalerGetByte(PB8_4D_MN_DPF_VHT_M) << 8) | ScalerGetByte(PB8_4E_MN_DPF_VHT_L));

        case _DP_H_WIDTH:

            return (((WORD)ScalerGetByte(PB8_45_MN_DPF_HWD_M) << 8) | ScalerGetByte(PB8_46_MN_DPF_HWD_L));

        case _DP_H_START:

            return (((WORD)ScalerGetByte(PB8_43_MN_DPF_HST_M) << 8) | ScalerGetByte(PB8_44_MN_DPF_HST_L));

        default:

            break;
    }

    return 0;
}

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mac Rx PR Mode Check Process 8b10b
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PRModeCheckProc_8b10b(EnumInputPort enumInputPort)
{
    // Check Pr Sink Status Active
    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x20, 0x22, (_BIT2 | _BIT1 | _BIT0)) == _DP_PR_MODE_ACTIVE)
    {
        if(ScalerTimerPollingDataBitFlagProc(_DP_TWO_FRAME_TIME_MAX, PB9_47_VSC7, 0x01, _BIT0, _TRUE) == _TRUE)
        {
            if(ScalerTimerPollingDataBitFlagProc(_DP_ONE_FRAME_TIME_MAX, PB9_47_VSC7, 0x01, _BIT3, _TRUE) == _FALSE)
            {
                // If Pr Sink Status Active and DB1[0] Pr_state = 1, DB1[3] Su_valid = 0, Update DPCD Error Status RFB Storage Error
                ScalerDpAuxRxDpcdPRModeErrorStateUpdate(enumInputPort, _DP_PR_MODE_RFB_STORAGE_ERROR);
            }
        }
        else
        {
            // If Pr Sink Status Active and Not Receive Vsc Sdp DB1[0] Pr_state = 1, Update DPCD Error Status RFB Storage Error
            ScalerDpAuxRxDpcdPRModeErrorStateUpdate(enumInputPort, _DP_PR_MODE_RFB_STORAGE_ERROR);
        }
    }

    if(ScalerDpAuxRxGetPRModeDpcdCrcEnable(enumInputPort) == _ENABLE)
    {
        if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
        {
            ScalerSetBit(PB8_70_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
        }
        else
        {
            ScalerSetBit(PB8_70_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        }

        // Disable CRC Calculation
        ScalerSetBit(PB8_70_DP_CRC_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // Start CRC Calculation
        ScalerSetBit(PB8_70_DP_CRC_CTRL, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_70_DP_CRC_CTRL, _BIT6, _TRUE) == _TRUE)
        {
            // Clr Pr CRC Irq Flag
            ScalerSetBit(PB9_4B_DUMMY_4B, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

            // Enable Pr Crc Irq
            ScalerSetBit(PB9_4A_DUMMY_4A, ~_BIT5, _BIT5);
        }
    }
}

//--------------------------------------------------
// Description  : PR Mode SDP Pr State Change Irq
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_8b10b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Clear flag
        ScalerSetBit(PB9_4B_DUMMY_4B, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        // Enable Pr_State Chang Irq
        ScalerSetBit(PB9_4A_DUMMY_4A, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable Pr_State Chang Irq
        ScalerSetBit(PB9_4A_DUMMY_4A, ~_BIT7, 0x00);

        // Clear flag
        ScalerSetBit(PB9_4B_DUMMY_4B, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
    }
}
#endif

//---------------------------------------------------------------
// Description  : DP Pixel Mode Setting
// Input Value  : InputPort, PixelMode
// Output Value : _TRUE --> Register Setting Pass for Pixel Mode
//---------------------------------------------------------------
bit ScalerDpMacStreamRx1PixelModeSetting(EnumInputPort enumInputPort, EnumDpStreamPixelMode enumPixelMode)
{
    enumInputPort = enumInputPort;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacStreamRx1PixelModeSetting_128b132b(enumPixelMode);
    }
    else
#endif
    {
        return ScalerDpMacStreamRx1PixelModeSetting_8b10b(enumPixelMode);
    }
}

//--------------------------------------------------
// Description  : DP Rx1 SEC Type Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetSdpBuffRcvInitial(void)
{
    //---------------------------------------
    // Clr Status Register, Ram Receive SDP Type Inital
    //---------------------------------------
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
    ScalerDpMacStreamRx1SetSdpBuffRcvMode(_DP_SDP_BUFF_SPD, _DP_SDP_TYPE_INFOFRAME_SPD);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    ScalerDpMacStreamRx1SetSdpBuffRcvMode(_DP_SDP_BUFF_ADAPTIVESYNC, _DP_SDP_TYPE_ADAPTIVESYNC);
#endif

#if((_DP_HDR10_SUPPORT == _ON) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    ScalerDpMacStreamRx1SetSdpBuffRcvMode(_DP_SDP_BUFF_HDR, _DP_SDP_TYPE_INFOFRAME_HDR);
#endif

#if((_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    ScalerDpMacStreamRx1SetSdpBuffRcvMode(_DP_SDP_BUFF_RSV0, _DP_SDP_TYPE_INFOFRAME_VENDOR_SPEC);
#endif

#if(_AUDIO_SUPPORT == _ON)
    ScalerDpMacStreamRx1SetSdpBuffRcvMode(_DP_SDP_BUFF_ISRC, _DP_SDP_TYPE_INFOFRAME_AUDIO);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    ScalerDpMacStreamRx1SetSdpBuffRcvMode(_DP_SDP_BUFF_PPS, _DP_SDP_TYPE_PPS);
#endif
}

//--------------------------------------------------
// Description  : DP Rx1 Set SDP Ram Receive SDP Type(None Audio Releted)
// Input Value  : Dp Sdp Ram Index, Dp Sdp Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetSdpBuffRcvMode(EnumDpSdpRamIndex enumDpSdpRamIndex, EnumDpSdpType enumDpSdpType)
{
    switch(enumDpSdpRamIndex)
    {
        case _DP_SDP_BUFF_SPD:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set SPD Ram Receive SDP HB1(Infoframe Type Value)
            ScalerSetByte(P75_28_DP_SDP_SPD_MAT_HB1, enumDpSdpType);

            // Set SPD Ram Receive SDP Offset
            ScalerSetBit(P75_2E_DP_SDP_SPD_ADR, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
#endif
            // Set SPD Ram Receive SDP HB1(Infoframe Type Value)
            ScalerSetByte(PB9_2C_DP_SDP_SPD_MAT_HB1, enumDpSdpType);

            // Set SPD Ram Receive SDP Offset
            ScalerSetBit(PB9_32_DP_SDP_SPD_ADR, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            break;

        case _DP_SDP_BUFF_HDR:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set HDR Ram Receive SDP HB1(Infoframe Type Value)
            ScalerSetByte(P75_30_DP_SDP_HDR_INFO_MAT_HB1, enumDpSdpType);

            // Set HDR Ram Receive SDP Offset
            ScalerSetBit(P75_35_DP_SDP_HDR_INFO_ADR, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
#endif
            // Set HDR Ram Receive SDP HB1(Infoframe Type Value)
            ScalerSetByte(PB9_34_DP_SDP_HDR_INFO_MAT_HB1, enumDpSdpType);

            // Set HDR Ram Receive SDP Offset
            ScalerSetBit(PB9_39_DP_SDP_HDR_INFO_ADR, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            break;

        case _DP_SDP_BUFF_ISRC:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set ISRC Ram Receive SDP HB1(Infoframe Type Value)
            ScalerSetByte(P75_E6_DP_SDP_ISRC_MAT_HB1, enumDpSdpType);

            // Set ISRC Ram Receive SDP Offset
            ScalerSetBit(P75_E4_SDP_ISRC_ADR, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            if(enumDpSdpType == _DP_SDP_TYPE_ISRC)
            {
                // ISRC SDP HB3[3] ignore
                ScalerSetBit(P75_E3_SDP_ISRC_0, ~_BIT0, _BIT0);
            }
#endif
            // Set ISRC Ram Receive SDP HB1(Infoframe Type Value)
            ScalerSetByte(PB9_E6_DP_SDP_ISRC_MAT_HB1, enumDpSdpType);

            // Set ISRC Ram Receive SDP Offset
            ScalerSetBit(PB9_E4_SDP_ISRC_ADR, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            if(enumDpSdpType == _DP_SDP_TYPE_ISRC)
            {
                // ISRC SDP HB3[3] ignore
                ScalerSetBit(PB9_E3_SDP_ISRC_0, ~_BIT0, _BIT0);
            }

            break;

        case _DP_SDP_BUFF_RSV0:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set RSV0 Receive SDP HB1(Infoframe Type Value)
            ScalerSetByte(P75_F0_DP_SDP_RSV0_MAT_HB1, enumDpSdpType);

            // Set RSV0 Receive SDP Offset
            ScalerSetBit(P75_F4_DP_SDP_RSV0_ADR, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // Disable RSV0 Ram Receive IRQ
            ScalerDpMacStreamRx1SdpIrqEnable_128b132b(_DP_SDP_BUFF_RSV0, _DISABLE);
#endif
            // Set RSV0 Receive SDP HB1(Infoframe Type Value)
            ScalerSetByte(PB9_F0_DP_SDP_RSV0_MAT_HB1, enumDpSdpType);

            // Set RSV0 Receive SDP Offset
            ScalerSetBit(PB9_F4_DP_SDP_RSV0_ADR, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // Disable RSV0 Ram Receive IRQ
            ScalerDpMacStreamRx1SdpIrqEnable_8b10b(_DP_SDP_BUFF_RSV0, _DISABLE);

            break;

        case _DP_SDP_BUFF_ADAPTIVESYNC:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set Adaptivesync Receive SDP HB1(Infoframe Type Value)
            ScalerSetByte(P75_26_DP_SDP_ADP_SYNC_ADDR, enumDpSdpType);
#endif
            // Set Adaptivesync Receive SDP HB1(Infoframe Type Value)
            ScalerSetByte(PB9_5C_DP_SDP_ADP_SYNC_MAT_HB1, enumDpSdpType);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Rx1 Set Mac Receive PPS or Metadata SDP
// Input Value  : Dp Sdp Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetMetaSdpRcvInitial(EnumDpSdpType enumDpSdpType)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Metadata SDP HB1 Set
    ScalerSetByte(P75_E8_DP_MAC_DYN_MDATA_HB1, enumDpSdpType);

    // Metadata SDP HB0 Set
    ScalerSetByte(P75_FC_DP_MAC_DYN_MDATA_HB0, 0x00);
#endif

    // Metadata SDP HB1 Set
    ScalerSetByte(PB9_E8_DP_MAC_DYN_MDATA_HB1, enumDpSdpType);

    // Metadata SDP HB0 Set
    ScalerSetByte(PB9_FC_DP_MAC_DYN_MDATA_HB0, 0x00);
}

//--------------------------------------------------
// Description  : DP Rx1 Set VSC SDP Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetVscSdpRcvInitial(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Set VSC Receive SDP HB0(Secondary-Data Packet ID)
    ScalerSetByte(P75_42_VSC2, 0x00);

    // Set VSC Receive SDP HB1(Infoframe Type Value)
    ScalerSetByte(P75_43_VSC3, _DP_SDP_TYPE_VSC);

    // Set VSC Receive SDP HB2(Revision Number)
    ScalerSetByte(P75_44_VSC4, 0x02);

    // Set VSC Receive SDP HB3(Number of Valid Data Bytes)
    ScalerSetByte(P75_45_VSC5, 0x08);

    // Set VSC Receive SDP HB2/HB3 Care
    ScalerSetBit(P75_40_VSC0, ~_BIT7, 0x00);
#endif

    // Set VSC Receive SDP HB0(Secondary-Data Packet ID)
    ScalerSetByte(PB9_42_VSC2, 0x00);

    // Set VSC Receive SDP HB1(Infoframe Type Value)
    ScalerSetByte(PB9_43_VSC3, _DP_SDP_TYPE_VSC);

    // Set VSC Receive SDP HB2(Revision Number)
    ScalerSetByte(PB9_44_VSC4, 0x02);

    // Set VSC Receive SDP HB3(Number of Valid Data Bytes)
    ScalerSetByte(PB9_45_VSC5, 0x08);

    // Set VSC Receive SDP HB2/HB3 Care
    ScalerSetBit(PB9_40_VSC0, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Check DP VSC SDP Information
// Input Value  : None
// Output Value : True --> DP VSC SDP Check Ok
//--------------------------------------------------
bit ScalerDpMacStreamRx1VscCheck(void)
{
    BYTE pucColorInfoByte[3] = {0};

    // Get VSC SDP Data Packet, Read DB16~18 --> pucColorInfoByte[0:2]
    ScalerDpMacStreamRx1GetSdpPktData(_DP_SDP_TYPE_VSC, pucColorInfoByte, 16, 3);

    SET_DP_MAC_STREAM_RX1_CONTENT_TYPE(pucColorInfoByte[2] & (_BIT2 | _BIT1 | _BIT0));

    // Color Space Check
    if(GET_DP_MAC_STREAM_RX1_VSC_SDP_COLOR_MODE() == _FALSE)
    {
        // Color format info source change from MISC --> VSC
        switch(pucColorInfoByte[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4))
        {
            case _VSC_COLOR_SPACE_0:
                if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_RGB)
                {
                    DebugMessageDpRx("DP MAC RX1: VSC change: Color Space, _COLOR_SPACE_RGB", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_1:
                if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_YCBCR444)
                {
                    DebugMessageDpRx("DP MAC RX1: VSC change: Color Space, _COLOR_SPACE_YCBCR444", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_2:
                if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_YCBCR422)
                {
                    DebugMessageDpRx("DP MAC RX1: VSC change: Color Space, _COLOR_SPACE_YCBCR422", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_3:
                if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_YCBCR420)
                {
                    DebugMessageDpRx("DP MAC RX1: VSC change: Color Space, _COLOR_SPACE_YCBCR420", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_4:
                if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_Y_ONLY)
                {
                    DebugMessageDpRx("DP MAC RX1: VSC change: Color Space, _COLOR_SPACE_Y_ONLY", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_5:
                if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_RAW)
                {
                    DebugMessageDpRx("DP MAC RX1: VSC change: Color Space, _COLOR_SPACE_RAW", 0);
                    return _FALSE;
                }

                break;

            default:
                if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_RGB)
                {
                    DebugMessageDpRx("DP MAC RX1: VSC change: Color Space, _COLOR_SPACE_RGB", 0);
                    return _FALSE;
                }

                break;
        }
    }
    else
    {
        if((pucColorInfoByte[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) != GET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE())
        {
            DebugMessageDpRx("DP MAC RX1: VSC change: Color Space", 0);
            return _FALSE;
        }
    }

    // Color Depth Check
    if((pucColorInfoByte[1] & (_BIT2 | _BIT1 | _BIT0)) != GET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE())
    {
        DebugMessageDpRx("DP MAC RX1: VSC change: Color Depth", 0);
        return _FALSE;
    }

    // Colorimetry Ext Check
    if(GET_DP_MAC_STREAM_RX1_COLORIMETRY() == _COLORIMETRY_EXT)
    {
        if((pucColorInfoByte[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != GET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_PREVALUE())
        {
            DebugMessageDpRx("DP MAC RX1: VSC change: Colorimetry Ext", 0);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_PREVALUE(pucColorInfoByte[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerDpMacStreamRx1ColorimetryExtSetting();
                SET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_CHANGED();
            }
        }
    }
    else
    {
        DebugMessageDpRx("DP MAC RX1: VSC change: Colorimetry Ext", 0);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
        {
            return _FALSE;
        }
        else
        {
            SET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_PREVALUE(pucColorInfoByte[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerDpMacStreamRx1ColorimetryExtSetting();
            SET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_CHANGED();
        }
    }

    // Dynamic Range Check
#if(_YCC_QUANTIZATION_RANGE_FUNCTION == _ON)
    if((GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420))
    {
        if(((pucColorInfoByte[1] & _BIT7) >> 7) != GET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE())
        {
            DebugMessageDpRx("DP MAC RX1: VSC change: Dynamic Range", ((pucColorInfoByte[1] & _BIT7) >> 7));

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE((pucColorInfoByte[1] & _BIT7) >> 7);
                ScalerDpMacStreamRx1QuantizationSetting();
                SET_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED();
            }
        }
    }
    else
#endif
    {
#if(_RGB_QUANTIZATION_RANGE_FUNCTION == _ON)
        if(((pucColorInfoByte[1] & _BIT7) >> 7) != GET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE())
        {
            DebugMessageDpRx("DP MAC RX1: VSC change: Dynamic Range", ((pucColorInfoByte[1] & _BIT7) >> 7));

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE((pucColorInfoByte[1] & _BIT7) >> 7);
                ScalerDpMacStreamRx1QuantizationSetting();
                SET_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED();
            }
        }
#endif
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Mas Info Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetMsaReset(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Msa Inner Reset
    ScalerSetBit(P75_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), _BIT0);

    // Msa Popup Reset
    ScalerSetBit(P75_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), _BIT2);
#endif
    // Msa Inner Reset
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), _BIT0);

    // Msa Popup Reset
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), _BIT2);
}

//--------------------------------------------------
// Description  : DP Rx1 SDP Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetSdpReset(void)
{
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
    ScalerDpMacStreamRx1SetSdpInitStatus(_DP_SDP_BUFF_SPD);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    ScalerDpMacStreamRx1SetSdpInitStatus(_DP_SDP_BUFF_ADAPTIVESYNC);
#endif

#if((_DP_HDR10_SUPPORT == _ON) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    ScalerDpMacStreamRx1SetSdpInitStatus(_DP_SDP_BUFF_HDR);
#endif

#if((_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    ScalerDpMacStreamRx1SetSdpInitStatus(_DP_SDP_BUFF_RSV0);
#endif

#if(_AUDIO_SUPPORT == _ON)
    ScalerDpMacStreamRx1SetSdpInitStatus(_DP_SDP_BUFF_ISRC);
#endif
}

//--------------------------------------------------
// Description  : DP Rx1 SDP Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetSdpReset_8b10b(void)
{
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
    ScalerDpMacStreamRx1SetSdpInitStatus_8b10b(_DP_SDP_BUFF_SPD);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    ScalerDpMacStreamRx1SetSdpInitStatus_8b10b(_DP_SDP_BUFF_ADAPTIVESYNC);
#endif

#if((_DP_HDR10_SUPPORT == _ON) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    ScalerDpMacStreamRx1SetSdpInitStatus_8b10b(_DP_SDP_BUFF_HDR);
#endif

#if((_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    ScalerDpMacStreamRx1SetSdpInitStatus_8b10b(_DP_SDP_BUFF_RSV0);
#endif

#if(_AUDIO_SUPPORT == _ON)
    ScalerDpMacStreamRx1SetSdpInitStatus_8b10b(_DP_SDP_BUFF_ISRC);
#endif
}

//--------------------------------------------------
// Description  : DP Rx1 Set Clr Status Flag
// Input Value  : Dp Sdp Ram Index
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetSdpInitStatus(EnumDpSdpRamIndex enumDpSdpRamIndex)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacStreamRx1SetSdpInitStatus_128b132b(enumDpSdpRamIndex);
#endif
    ScalerDpMacStreamRx1SetSdpInitStatus_8b10b(enumDpSdpRamIndex);
}

//--------------------------------------------------
// Description  : DSC Get PPS Packet Byte
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1GetPpsSdpInfo(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacStreamRx1GetPpsSdpInfo_128b132b();
    }
    else
#endif
    {
        ScalerDpMacStreamRx1GetPpsSdpInfo_8b10b();
    }

    if(GET_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE() == _TRUE)
    {
        DebugMessageDpRx("7. DP MAC RX1: DSC PT pic height", GET_DP_MAC_STREAM_RX1_DSC_PIC_HEIGHT());
        DebugMessageDpRx("7. DP MAC RX1: DSC PT pic width", GET_DP_MAC_STREAM_RX1_DSC_PIC_WIDTH());
        DebugMessageDpRx("7. DP MAC RX1: DSC PT slice height", GET_DP_MAC_STREAM_RX1_DSC_SLICE_HEIGHT());
        DebugMessageDpRx("7. DP MAC RX1: DSC PT slice WIDTH", GET_DP_MAC_STREAM_RX1_DSC_SLICE_WIDTH());
        DebugMessageDpRx("7. DP MAC RX1: DSC PT bpp", GET_DP_MAC_STREAM_RX1_DSC_COLOR_BPP());
        DebugMessageDpRx("7. DP MAC RX1: DSC PT bpc", GET_DP_MAC_STREAM_RX1_DSC_COLOR_BPC());
    }
}

//--------------------------------------------------
// Description  : DSC Get PPS Packet Element Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD ScalerDpMacStreamRx1GetPpsElementInfo(EnumDpStreamPpsElement enumDpStreamPpsElement)
{
    switch(enumDpStreamPpsElement)
    {
        case _PPS_BIT_PER_COMPONENT:
            return GET_DP_MAC_STREAM_RX1_DSC_COLOR_BPC();
            break;

        case _PPS_BITS_PER_PIXEL:
            return GET_DP_MAC_STREAM_RX1_DSC_COLOR_BPP();
            break;

        case _PPS_PIC_HEIGHT:
            return GET_DP_MAC_STREAM_RX1_DSC_PIC_HEIGHT();
            break;

        case _PPS_PIC_WIDTH:
            return GET_DP_MAC_STREAM_RX1_DSC_PIC_WIDTH();
            break;

        case _PPS_SLICE_HEIGHT:
            return GET_DP_MAC_STREAM_RX1_DSC_SLICE_HEIGHT();
            break;

        case _PPS_SLICE_WIDTH:
            return GET_DP_MAC_STREAM_RX1_DSC_SLICE_WIDTH();
            break;

        case _PPS_NATIVE_420:
            return GET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_420();
            break;

        case _PPS_NATIVE_422:
            return GET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_422();
            break;

        case _PPS_SIMPLE_422:
            return GET_DP_MAC_STREAM_RX1_DSC_COLOR_SIMPLE_422();
            break;

        case _PPS_NATIVE_MODE:
            return (GET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_422() || GET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_420());
            break;

        case _PPS_HOR_SLICE_COUNT:
            return ((GET_DP_MAC_STREAM_RX1_DSC_PIC_WIDTH() + GET_DP_MAC_STREAM_RX1_DSC_SLICE_WIDTH() - 1) / GET_DP_MAC_STREAM_RX1_DSC_SLICE_WIDTH());
            break;

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Sdp Receive Check
// Input Value  : Dp Sdp Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpRevDetect(EnumDpSdpType enumDpSdpType)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacStreamRx1SdpRevDetect_128b132b(enumDpSdpType);
    }
    else
#endif
    {
        ScalerDpMacStreamRx1SdpRevDetect_8b10b(enumDpSdpType);
    }
}

//--------------------------------------------------
// Description  : Sdp Change Dtect
// Input Value  : Dp Sdp Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpChgDetect(EnumDpSdpType enumDpSdpType)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacStreamRx1SdpChgDetect_128b132b(enumDpSdpType);
    }
    else
#endif
    {
        ScalerDpMacStreamRx1SdpChgDetect_8b10b(enumDpSdpType);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable SDP IRQ_en
// Input Value  : RSV Number, ENABLE/DISABLE bit
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpIrqEnable(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
        {
            ScalerDpMacStreamRx1SdpIrqEnable_128b132b(enumDpSdpRamIndex, bEnable);
        }
        else
#endif
        {
            ScalerDpMacStreamRx1SdpIrqEnable_8b10b(enumDpSdpRamIndex, bEnable);
        }
    }
    else
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerDpMacStreamRx1SdpIrqEnable_128b132b(enumDpSdpRamIndex, bEnable);
#endif
        ScalerDpMacStreamRx1SdpIrqEnable_8b10b(enumDpSdpRamIndex, bEnable);
    }
}

//--------------------------------------------------
// Description  : DP Rx1 Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1ColorimetrySetting(void)
{
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(_DP_MAC_1);

    BYTE ucColorimetryValue = (GET_DP_MAC_STREAM_RX1_COLORIMETRY_PREVALUE() << 1);

    if((GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(ucColorimetryValue & (_BIT4 | _BIT3))
        {
            case 0:

                SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_YCC_XVYCC601);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_YCC_XVYCC601", 0);
                break;

            case _BIT3:
                SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT601);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_YCC_ITUR_BT601", 0);
                break;

            case _BIT4:
                SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_YCC_XVYCC709);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_YCC_XVYCC709", 0);
                break;

            case (_BIT4 | _BIT3):
                SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT709);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_YCC_ITUR_BT709", 0);
                break;

            default:
                break;
        }
    }
    else if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(ucColorimetryValue & (_BIT4 | _BIT3 | _BIT2 | _BIT1))
        {
            case 0:
                SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_RGB_SRGB_VESA", 0);
                break;

            case _BIT3:
                SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_RGB_SRGB_CEA", 0);
                break;

            case (_BIT2 | _BIT1):
                SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_RGB_XRRGB);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_RGB_XRRGB", 0);
                break;

            case (_BIT4 | _BIT2 | _BIT1):
                SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_RGB_SCRGB);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_RGB_SCRGB", 0);
                break;

            case (_BIT4 | _BIT3):
                SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_RGB_ADOBERGB);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_RGB_ADOBERGB", 0);
                break;

            case (_BIT3 | _BIT2 | _BIT1):
                SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_RGB_DCI_P3);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_RGB_DCI_P3", 0);
                break;

            case (_BIT4 | _BIT3 | _BIT2 | _BIT1):
                SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_RGB_COLOR_PROFILE);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_RGB_COLOR_PROFILE", 0);
                break;

            default:
                SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_RGB_SRGB", 0);
                break;
        }
    }
    else if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY)
    {
        SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_Y_ONLY);
        DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_Y_ONLY", 0);
    }
    else if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_RAW)
    {
        SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_RAW);
        DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_RAW", 0);
    }

    ScalerDpRxStreamColorimetryInfoSetting(enumDpMacStreamSourceType);
}

//--------------------------------------------------
// Description  : DP Rx1 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1ColorimetryExtSetting(void)
{
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(_DP_MAC_1);

    SET_DP_MAC_STREAM_RX1_COLORIMETRY(_COLORIMETRY_EXT);

    if((GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(GET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_PREVALUE())
        {
            case _VSC_COLORIMETRY_0:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT601);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_YCC_ITUR_BT601", 0);
                break;

            case _VSC_COLORIMETRY_1:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT709);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_YCC_ITUR_BT709", 0);
                break;

            case _VSC_COLORIMETRY_2:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC601);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_YCC_XVYCC601", 0);
                break;

            case _VSC_COLORIMETRY_3:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC709);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_YCC_XVYCC709", 0);
                break;

            case _VSC_COLORIMETRY_4:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_SYCC601);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_YCC_SYCC601", 0);
                break;

            case _VSC_COLORIMETRY_5:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ADOBEYCC601);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_YCC_ADOBEYCC601", 0);
                break;

            case _VSC_COLORIMETRY_6:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL", 0);
                break;

            case _VSC_COLORIMETRY_7:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL", 0);
                break;

            default:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_RESERVED", 0);
                break;
        }
    }
    else if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(GET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_PREVALUE())
        {
            case _VSC_COLORIMETRY_0:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_SRGB);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_RGB_SRGB", 0);
                break;

            case _VSC_COLORIMETRY_1:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_XRRGB);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_RGB_XRRGB", 0);
                break;

            case _VSC_COLORIMETRY_2:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_SCRGB);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_RGB_SCRGB", 0);
                break;

            case _VSC_COLORIMETRY_3:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ADOBERGB);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_RGB_ADOBERGB", 0);
                break;

            case _VSC_COLORIMETRY_4:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_DCI_P3);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_RGB_DCI_P3", 0);
                break;

            case _VSC_COLORIMETRY_5:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE", 0);
                break;

            case _VSC_COLORIMETRY_6:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ITUR_BT2020);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_RGB_ITUR_BT2020", 0);
                break;

            default:
                SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);
                DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_RESERVED", 0);
                break;
        }
    }
    else if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY)
    {
        SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_Y_ONLY_DICOM_PART14);
        DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_Y_ONLY_DICOM_PART14", 0);
    }
    else if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_RAW)
    {
        SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(_COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE);
        DebugMessageDpRx("DP MAC RX1: _COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE", 0);
    }

    ScalerDpRxStreamColorimetryInfoSetting(enumDpMacStreamSourceType);

    ScalerDpRxStreamColorimetryExtInfoSetting(enumDpMacStreamSourceType);
}

//--------------------------------------------------
// Description  : DP Rx1 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1QuantizationSetting(void)
{
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(_DP_MAC_1);

    switch(GET_DP_MAC_STREAM_RX1_COLOR_SPACE())
    {
        case _COLOR_SPACE_YCBCR420:
        case _COLOR_SPACE_YCBCR422:
        case _COLOR_SPACE_YCBCR444:

            // Special case for xvYCC
            if((GET_DP_MAC_STREAM_RX1_COLORIMETRY() == _COLORIMETRY_YCC_XVYCC601) || (GET_DP_MAC_STREAM_RX1_COLORIMETRY() == _COLORIMETRY_YCC_XVYCC709))
            {
                SET_DP_MAC_STREAM_RX1_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);
                DebugMessageDpRx("DP MAC RX1: _YCC_QUANTIZATION_LIMIT_RANGE", 0);
            }
            else
            {
                if(GET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_FULL)
                {
                    SET_DP_MAC_STREAM_RX1_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);
                    DebugMessageDpRx("DP MAC RX1: _YCC_QUANTIZATION_FULL_RANGE", 0);
                }
                else
                {
                    SET_DP_MAC_STREAM_RX1_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);
                    DebugMessageDpRx("DP MAC RX1: _YCC_QUANTIZATION_LIMIT_RANGE", 0);
                }
            }

            SET_DP_MAC_STREAM_RX1_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

            break;

        default:
        case _COLOR_SPACE_RGB:

            // Special case for AdobeRGB
            if(GET_DP_MAC_STREAM_RX1_COLORIMETRY() == _COLORIMETRY_RGB_ADOBERGB)
            {
                SET_DP_MAC_STREAM_RX1_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);
                DebugMessageDpRx("DP MAC RX1: _RGB_QUANTIZATION_FULL_RANGE", 0);
            }
            else
            {
                if(GET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_FULL)
                {
                    SET_DP_MAC_STREAM_RX1_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);
                    DebugMessageDpRx("DP MAC RX1: _RGB_QUANTIZATION_FULL_RANGE", 0);
                }
                else
                {
                    SET_DP_MAC_STREAM_RX1_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_LIMIT_RANGE);
                    DebugMessageDpRx("DP MAC RX1: _RGB_QUANTIZATION_LIMIT_RANGE", 0);
                }
            }

            SET_DP_MAC_STREAM_RX1_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);

            break;
    }

    ScalerDpRxStreamQuantizationInfoSetting(enumDpMacStreamSourceType);
}

//--------------------------------------------------
// Description  : DP NF PLL Input Clock Setting
// Input Value  : Input Clock, Link Clock
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRx1SetPLLInputClockSetting(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo)
{
    BYTE ucprediv = 2;
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    BYTE ucPllRefClk = 25;
#endif

    // [7:6] PLL Input Clock(Fin) : Link_Clk(27MHz),
    // [5] Enable DP14 Pixel Clock
    // [4] Enable DP20 Pixel Clock
    // [2] Video Select : 0(DP14)/1(DP20)
    // [0] Tracking Sclk Clock : from local PLL
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerSetBit(PB8_A3_PLL_IN_CONTROL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2));
    }
    else
#endif
    {
        ScalerSetBit(PB8_A3_PLL_IN_CONTROL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT5));
    }

    // If Fin = Link CLock, Set Divdier for Link Clock
    if(ScalerGetBit(PB8_A3_PLL_IN_CONTROL, (_BIT7 | _BIT6)) == _BIT6)
    {
        switch(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort))
        {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            case _DP_LINK_UHBR20:
            case _DP_LINK_UHBR13_5:
            case _DP_LINK_UHBR10:

                // Idel Ref Clk of PLL = 25MHz ((Link_Clock / _HW_DP_RX_PLL_INPUT_CLK_DIV_128B132B) / predivider)
                ucprediv = (((pstDpInfo->stDpLinkInfo.ulLinkClockHz / 100000) / _HW_DP_RX_PLL_INPUT_CLK_DIV_128B132B) + (ucPllRefClk >> 1)) / ucPllRefClk;

                // Set Pll Input Clock, Unit is Hz
                pstDpInfo->stDpLinkInfo.ulPllInputClockHz = ((pstDpInfo->stDpLinkInfo.ulLinkClockHz / ucprediv) * 10) / _HW_DP_RX_PLL_INPUT_CLK_DIV_128B132B;

                break;
#endif
            case _DP_LINK_HBR3_9G:

                // predivider = (1/2 link clk) / 27M
                ucprediv = _DP_LINK_HBR3_9G / 2;

                // Set Pll Input Clock, Unit is Hz
                pstDpInfo->stDpLinkInfo.ulPllInputClockHz = pstDpInfo->stDpLinkInfo.ulLinkClockHz / _DP_LINK_HBR3_9G;

                break;

            case _DP_LINK_HBR3:

                // predivider = (1/2 link clk) / 27M
                ucprediv = _DP_LINK_HBR3 / 2;

                // Set Pll Input Clock, Unit is Hz
                pstDpInfo->stDpLinkInfo.ulPllInputClockHz = pstDpInfo->stDpLinkInfo.ulLinkClockHz / _DP_LINK_HBR3;

                break;

            case _DP_LINK_HBR2:

                // predivider = (1/2 link clk) / 27M
                ucprediv = _DP_LINK_HBR2 / 2;

                // Set Pll Input Clock, Unit is Hz
                pstDpInfo->stDpLinkInfo.ulPllInputClockHz = pstDpInfo->stDpLinkInfo.ulLinkClockHz / _DP_LINK_HBR2;

                break;

            case _DP_LINK_HBR:

                // predivider = (1/2 link clk) / 27M
                ucprediv = _DP_LINK_HBR / 2;

                // Set Pll Input Clock, Unit is Hz
                pstDpInfo->stDpLinkInfo.ulPllInputClockHz = pstDpInfo->stDpLinkInfo.ulLinkClockHz / _DP_LINK_HBR;

                break;

            case _DP_LINK_RBR:

                // predivider = (1/2 link clk) / 27M
                ucprediv = _DP_LINK_RBR / 2;

                // Set Pll Input Clock, Unit is Hz
                pstDpInfo->stDpLinkInfo.ulPllInputClockHz = pstDpInfo->stDpLinkInfo.ulLinkClockHz / _DP_LINK_RBR;

                break;

            default:

                return _FALSE;
        }

        ScalerSetByte(PB8_A4_M2PLL_DIVIDER0, (ucprediv - 2));
    }
    else
    {
        // Unit is Hz
        pstDpInfo->stDpLinkInfo.ulPllInputClockHz = _GDIPHY_RX_GDI_CLK_KHZ * 1000;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP NF PLL Setting
// Input Value  : None
// Output Value : ulvcoFreq --> VCO Frequency Value
//--------------------------------------------------
bit ScalerDpMacStreamRx1SetPLLFreqNf(DWORD ulPllTargetClockHz, StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit)
{
    BYTE ucpllo = 0;
    BYTE ucdivs = 0;
    BYTE ucBuf = 0;
    BYTE ucdiv_pllo = 1;
    BYTE ucdiv_divs = 1;
    BYTE ucNcode = 0;
    BYTE ucFcode_MSB4b = 0;
    WORD usFcode_LSB16b = 0;
    DWORD ulPllVcoClockHz = 0;
    DWORD ulPllInputClockHz = 0;
    bit bPllVcoHighFreqStatus = _FALSE;

    ulPllInputClockHz = pstDpInfo->stDpLinkInfo.ulPllInputClockHz;

    if((ulPllTargetClockHz < ulDataPathSpeedLimit) && (ulPllTargetClockHz >= 270000000))
    {
        if(ulPllTargetClockHz >= 660000000)
        {
            bPllVcoHighFreqStatus = _TRUE;
        }

        // Total Div = 1
        ucpllo = 0;
        ucdivs = 0;
    }
    else if((ulPllTargetClockHz < 270000000) && (ulPllTargetClockHz >= 4218750))
    {
        if((ulPllTargetClockHz < 270000000) && (ulPllTargetClockHz >= 135000000))
        {
            // Total Div = 2
            ucpllo = 1;
            ucdivs = 0;
        }
        else if((ulPllTargetClockHz < 135000000) && (ulPllTargetClockHz >= 67500000))
        {
            // Total Div = 4
            ucpllo = 2;
            ucdivs = 0;
        }
        else if((ulPllTargetClockHz < 67500000) && (ulPllTargetClockHz >= 33750000))
        {
            // Total Div = 8
            ucpllo = 3;
            ucdivs = 0;
        }
        else if((ulPllTargetClockHz < 33750000) && (ulPllTargetClockHz >= 16875000))
        {
            // Total Div = 16
            ucpllo = 3;
            ucdivs = 1;
        }
        else if((ulPllTargetClockHz < 16875000) && (ulPllTargetClockHz >= 8437500))
        {
            // Total Div = 32
            ucpllo = 3;
            ucdivs = 3;
        }
        else
        {
            // Total Div = 64
            ucpllo = 3;
            ucdivs = 7;
        }
    }
    else
    {
        return _FALSE;
    }

    ucdiv_divs = ucdivs + 1;

    if(ucpllo != 0)
    {
        ucdiv_pllo = 1;

        for(ucBuf = 0; ucBuf < ucpllo; ucBuf++)
        {
            ucdiv_pllo = 2 * ucdiv_pllo;
        }
    }
    else
    {
        ucdiv_pllo = 1;
    }

    pstDpInfo->stDpLinkInfo.ucPllDivs = ucdiv_divs;
    pstDpInfo->stDpLinkInfo.ucPllDivo = ucdiv_pllo;

    // Get PLL VCO Clock
    ulPllVcoClockHz = ulPllTargetClockHz * ucdiv_divs * ucdiv_pllo;

    if(ulPllInputClockHz == 0x00)
    {
        DebugMessageDpRx("DP MAC RX1: Pll Input Clk is invalid", 0);

        return _FALSE;
    }

    // Get N Code
    ucNcode = ulPllVcoClockHz / ulPllInputClockHz;

    // Get F Code
    ucFcode_MSB4b = ((ulPllVcoClockHz - ulPllInputClockHz * ucNcode) << 4) / ulPllInputClockHz;

    usFcode_LSB16b = ScalerGlobalComputeDwordMulDiv((((ulPllVcoClockHz - ulPllInputClockHz * ucNcode) << 4) - ucFcode_MSB4b * ulPllInputClockHz), 1UL << 16, ulPllInputClockHz);

    ScalerDpMacStreamRx1SetPLLNfOffProc(ulPllVcoClockHz, ucNcode, ucpllo, ucdivs);

    if(ScalerDpMacStreamRx1SetPLLNfOnProc(ucNcode, ucFcode_MSB4b, usFcode_LSB16b, bPllVcoHighFreqStatus) == _FALSE)
    {
        return _FALSE;
    }

    DebugMessageDpRx("DP MAC RX1: PLL Vco Clk", ulPllVcoClockHz);

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP NF PLL P Gain Clamp Setting
// Input Value  : ucPGainB3 --> p_gain_clamp_value[26:24]
//              : ucPGainB2 --> p_gain_clamp_value[15:8]
//              : ucPGainB1 --> p_gain_clamp_value[7:0]
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetPLLPGainClampValue(BYTE ucPGainB3, BYTE ucPGainB2, BYTE ucPGainB1)
{
    // 1st tracking : 0x0 10 00 00
    // 2nd tracking : 0x0 01 00 00
    ScalerSetByte(PB8_D1_MN_PI_CODE_9, ucPGainB3);
    ScalerSetByte(PB8_D2_MN_PI_CODE_A, ucPGainB2);
    ScalerSetByte(PB8_D3_MN_PI_CODE_B, ucPGainB1);
    ScalerSetByte(PB8_D4_MN_PI_CODE_C, 0x00);
}

//--------------------------------------------------
// Description  : DP NF PLL P Code Spread Control Setting
// Input Value  : ucPCodeCtrl --> Enable/Disable Spread Control
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PLLPCodeSpreadCtrl(BYTE ucPCodeCtrl, BYTE ucOneFrameTime)
{
    if(ucPCodeCtrl == _ON)
    {
        ScalerSetByte(PB8_EF_P_CODE_SPREAD_1, 0x00);
        ScalerSetByte(PB8_F0_P_CODE_SPREAD_2, 0x01);
        ScalerSetByte(PB8_F1_P_CODE_SPREAD_3, 0x00);

        // Wait for V-Blaning Start
        ScalerDpMacStreamRx1WaitVBlanking(ucOneFrameTime);

        ScalerSetBit(PB8_EE_P_CODE_SPREAD_0, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetBit(PB8_EE_P_CODE_SPREAD_0, ~_BIT7, 0x00);

        ScalerSetByte(PB8_EF_P_CODE_SPREAD_1, 0x00);
        ScalerSetByte(PB8_F0_P_CODE_SPREAD_2, 0x00);
        ScalerSetByte(PB8_F1_P_CODE_SPREAD_3, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set PLL Tracking Mode
// Input Value  : BYTE ucOneFrameTime
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetPllTrackingMode(EnumDpTrackingMode enumDpTrackingMode, BYTE ucOneFrameTime)
{
    WORD usTemp = 0;
    WORD usFastLockTrakingFrames = 0;
    EnumDpMacRxDPFRegenMode enumDpMacRxDPFRegenMode = _DPF_MODE_NONE;

    // Wait for V-Blaning Start
    ScalerDpMacStreamRx1WaitVBlanking(ucOneFrameTime);

    if(enumDpTrackingMode == _DP_TRACKING_FAST_LOCK_MODE)
    {
        // I Gain Clamp = 0x00 01 00 00

        // P Gain Clamp = 0x00 10 00 00
        ScalerDpMacStreamRx1SetPLLPGainClampValue(0x00, 0x10, 0x00);

        // P Code = 0x0 00 FF FF
        ScalerSetBit(PB8_C9_MN_PI_CODE_1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(PB8_CA_MN_PI_CODE_2, 0x00);
        ScalerSetByte(PB8_CB_MN_PI_CODE_3, 0xFF);
        ScalerSetByte(PB8_CC_MN_PI_CODE_4, 0xFF);

        // I Code = 0x08
        ScalerSetByte(PB8_C8_MN_PI_CODE_0, 0x08);

        enumDpMacRxDPFRegenMode = ScalerDpMacStreamRx1GetDPFRegenMode();

        if((enumDpMacRxDPFRegenMode == _DPF_MODE_DE_ONLY) || (enumDpMacRxDPFRegenMode == _DPF_MODE_DE_ONLY_FULL_LAST_LINE))
        {
            usFastLockTrakingFrames = 5;
        }
        else
        {
            usFastLockTrakingFrames = 3;
        }

        // Set PE Nonlock Threshold
        ScalerSetByte(PB8_E4_VS_TRACK2, 0x3F);

        // Wait for V-Blaning Start
        ScalerDpMacStreamRx1WaitVBlanking(ucOneFrameTime);

        // Set Fast Lock Mode
        ScalerSetBit(PB8_E1_VS_TRACK_MODE, ~(_BIT3 | _BIT2 | _BIT1), _BIT3);

        // Enable Tracking
        ScalerSetBit(PB8_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), _BIT7);

        usTemp = 0;

        // Waiting for Stream Clk Stable
        while(usTemp < 10)
        {
            // Clear PE Max Record
            ScalerSetByte(PB8_E5_VS_TRACK3, 0xFF);

            // Clear PE Flag
            ScalerSetBit(PB8_E0_VS_TRACK_EN, ~_BIT0, _BIT0);

            // Delay 1 Frame
            ScalerTimerDelayXms(ucOneFrameTime);

            usTemp++;

            // Fast lock mode tracking at least 2 Frames
            if((usTemp >= usFastLockTrakingFrames) && ((ScalerGetBit(PB8_E0_VS_TRACK_EN, _BIT0) == 0x00)))
            {
                break;
            }
        }

        DebugMessageDpRx("DP MAC RX1: 1st PE Loop", usTemp);
        DebugMessageDpRx("DP MAC RX1: 1st PE Max Record", ScalerGetByte(PB8_E5_VS_TRACK3));
    }
    else
    {
        // I Gain Clamp = 0x00 10 00 00

        // P Gain Clamp = 0x00 10 00 00
        ScalerDpMacStreamRx1SetPLLPGainClampValue(0x00, 0x10, 0x00);

        // P Code = 0x0 00 FF FF
        ScalerSetBit(PB8_C9_MN_PI_CODE_1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(PB8_CA_MN_PI_CODE_2, 0x00);
        ScalerSetByte(PB8_CB_MN_PI_CODE_3, 0xFF);
        ScalerSetByte(PB8_CC_MN_PI_CODE_4, 0xFF);

        // I Code = 0x04
        ScalerSetByte(PB8_C8_MN_PI_CODE_0, 0x04);

        // Wait for V-Blaning Start
        ScalerDpMacStreamRx1WaitVBlanking(ucOneFrameTime);

        // Set Precision Mode
        ScalerSetBit(PB8_E1_VS_TRACK_MODE, ~(_BIT3 | _BIT2 | _BIT1), _BIT2);

        // Set PE Nonlock Threshold
        ScalerSetByte(PB8_E4_VS_TRACK2, 0x1F);

        usTemp = 0;

        // Waiting for Stream Clk Stable
        do
        {
            // Clear PE Max Record
            ScalerSetByte(PB8_E5_VS_TRACK3, 0xFF);

            // Clear PE Flag
            ScalerSetBit(PB8_E0_VS_TRACK_EN, ~_BIT0, _BIT0);

            // Delay 1 Frame
            ScalerTimerDelayXms(ucOneFrameTime);

            usTemp++;
        }
        while((ScalerGetBit(PB8_E0_VS_TRACK_EN, _BIT0) == _BIT0) && (usTemp < 10));

        DebugMessageDpRx("DP MAC RX1: 2nd PE Loop", usTemp);
        DebugMessageDpRx("DP MAC RX1: 2nd PE Max Record", ScalerGetByte(PB8_E5_VS_TRACK3));
    }
}

//--------------------------------------------------
// Description  : Wait for Vertical Blanking Start
// Input Value  : EnumDpLinkChannelCodingType enumDpLinkChannelCodingType, BYTE ucOneFrameTime
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1WaitVBlanking(BYTE ucOneFrameTime)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumDpLinkChannelCodingType enumDpLinkChannelCodingType = ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1));

    if(enumDpLinkChannelCodingType == _CODING_TYPE_128B132B)
    {
        ScalerDpMacStreamRx1WaitVBlanking_128B132B(ucOneFrameTime);
    }
    else
#endif
    {
        ScalerDpMacStreamRx1WaitVBlanking_8B10B(ucOneFrameTime);
    }
}

//--------------------------------------------------
// Description  : DP Hs Tracking Active Region Setting
// Input Value  : Hs Tracking Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType)
{
    if(enumHSTrackingType == _DP_HS_TRACKING_FW_MODE)
    {
        // HS Tracking Region By FW Setting, Tracking Source ref from BE signal
        ScalerSetBit(PB8_EA_HS_TRACKING_NEW_MODE1, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

        // BE Start Num = 2 line
        ScalerSetBit(PB8_EC_VBID_MAN_MADE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);

        // BE End Num = 2 line
        ScalerSetBit(PB8_EC_VBID_MAN_MADE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // HS Tracking Region By FW Setting, Tracking Source ref from BE signal
        ScalerSetBit(PB8_EA_HS_TRACKING_NEW_MODE1, ~(_BIT5 | _BIT4), _BIT4);
    }
}

//--------------------------------------------------------------------
// Description  : Judge for Enabling Multiple Pixel Clock Mode or Not
// Input Value  : StructDpInfo, DataPathSpeedLimit
// Output Value : _TRUE --> Can Be Supported
//--------------------------------------------------------------------
bit ScalerDpMacStreamRx1CheckMultipleClkFeatureSupport(StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit)
{
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(_DP_MAC_1);

    // Disable x2 pixel clock output
    CLR_DP_MAC_STREAM_RX1_STREAM_OUTPUT_X2_CLK();

    if(enumDpMacStreamSourceType == _STREAM_SOURCE_MST2SST)
    {
        return _TRUE;
    }

    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        if(pstDpInfo->stDpLinkInfo.ulStreamClockHz > (ulDataPathSpeedLimit * 2))
        {
            // Stream clock > 1400MHz, YUV420 cannot support.
            return _FALSE;
        }
        else if(pstDpInfo->stDpLinkInfo.ulStreamClockHz <= (ulDataPathSpeedLimit / 2))
        {
            // Enable x2 pixel clock output
            SET_DP_MAC_STREAM_RX1_STREAM_OUTPUT_X2_CLK();

            return _TRUE;
        }
    }

#if(_3DDI_FUNCTION == _ON)
    if(ScalerDpMacStreamRxGetInterlace3ddiAvaible(pstDpInfo) == _TRUE)
    {
        // Enable x2 pixel clock output
        SET_DP_MAC_STREAM_RX1_STREAM_OUTPUT_X2_CLK();

        return _TRUE;
    }
#endif

    return _TRUE;
}

//---------------------------------------------------------------------------
// Description  : Judge for PLL Target & Pixel Mode
// Input Value  : StreamClock, DataPathSpeedLimit, PllTargetClock, PixelMode
// Output Value : _TRUE --> Judge Pass for Pll Target Clock & Pixel Mode
//---------------------------------------------------------------------------
bit ScalerDpMacStreamRx1PllTargetClockPixelModeJudge(StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit, DWORD *pulPllTargetClockHz, EnumDpStreamPixelMode *penumPixelMode)
{
    ulDataPathSpeedLimit = ulDataPathSpeedLimit;

    if(GET_DP_MAC_STREAM_RX1_STREAM_OUTPUT_X2_CLK() == _TRUE)
    {
        *pulPllTargetClockHz = pstDpInfo->stDpLinkInfo.ulInitStreamClockHz * 2;

        *penumPixelMode = _1_PIXEL_MODE;

        pstDpInfo->stDpLinkInfo.ucPixelMode = 1;
    }
    else
    {
#if((_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON) && (_DP_MAC_RX_128B132B_FOUR_PIXEL_MODE_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON))
        if(pstDpInfo->stDpLinkInfo.ulStreamClockHz > (2 * ulDataPathSpeedLimit))
        {
            *pulPllTargetClockHz = pstDpInfo->stDpLinkInfo.ulInitStreamClockHz / _DIV_4;

            *penumPixelMode = _4_PIXEL_MODE;

            pstDpInfo->stDpLinkInfo.ucPixelMode = 4;
        }
        else
#endif
        {
#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
            if(pstDpInfo->stDpLinkInfo.ulStreamClockHz > ulDataPathSpeedLimit)
            {
                *pulPllTargetClockHz = pstDpInfo->stDpLinkInfo.ulInitStreamClockHz / _DIV_2;

                *penumPixelMode = _2_PIXEL_MODE;

                pstDpInfo->stDpLinkInfo.ucPixelMode = 2;
            }
            else
#endif
            {
                *pulPllTargetClockHz = pstDpInfo->stDpLinkInfo.ulInitStreamClockHz;

                *penumPixelMode = _1_PIXEL_MODE;

                pstDpInfo->stDpLinkInfo.ucPixelMode = 1;
            }
        }
    }

    if(*penumPixelMode == _NONE_PIXEL_MODE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//----------------------------------------------------------------------
// Description  : PLL Output Divider Setting
// Input Value  : eInputPort, PixelMode
// Output Value : True --> Register Setting Pass for PLL Output Divider
//----------------------------------------------------------------------
bit ScalerDpMacStreamRx1PllOutputDivSetting(EnumInputPort enumInputPort, EnumDpStreamPixelMode enumPixelMode)
{
    enumInputPort = enumInputPort;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        if(GET_DP_MAC_STREAM_RX1_STREAM_OUTPUT_X2_CLK() == _TRUE)
        {
            // sclk2x = sclk4x/2, sclk = sclk2x
            ScalerSetBit(PB8_A2_PLL_OUT_CONTROL, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
        }
        else
        {
            // sclk2x = sclk4x, sclk = sclk2x
            ScalerSetBit(PB8_A2_PLL_OUT_CONTROL, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
        }
    }
    else
#endif
    {
#if(_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON)
        if(enumPixelMode == _2_PIXEL_MODE)
        {
            if(GET_DP_MAC_STREAM_RX1_STREAM_OUTPUT_X2_CLK() == _TRUE)
            {
                // sclk2x = sclk4x/2, sclk = sclk2x
                ScalerSetBit(PB8_A2_PLL_OUT_CONTROL, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
            }
            else
            {
                // sclk2x = sclk4x, sclk = sclk2x
                ScalerSetBit(PB8_A2_PLL_OUT_CONTROL, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
            }
        }
        else
#endif
        {
            if(enumPixelMode == _1_PIXEL_MODE)
            {
                if(GET_DP_MAC_STREAM_RX1_STREAM_OUTPUT_X2_CLK() == _TRUE)
                {
                    // sclk2x = sclk4x/2, sclk = sclk2x/2
                    ScalerSetBit(PB8_A2_PLL_OUT_CONTROL, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
                }
                else
                {
                    // sclk2x = sclk4x, sclk = sclk2x/2
                    ScalerSetBit(PB8_A2_PLL_OUT_CONTROL, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
                }
            }
            else
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//-------------------------------------------------------------
// Description  : Stream Clock Setting by final n.f code of PLL
// Input Value  : None
// Output Value : None
//-------------------------------------------------------------
void ScalerDpMacStreamRx1StreamClockSetting(StructDpInfo *pstDpInfo)
{
    DWORD ulClockHz = 0;
    BYTE ucNcode = 0;
    DWORD ulFcode = 0;
    DWORD ulNFcode = 0;
    BYTE ucdiv_sum = 1;

    // Get final n.f code of PLL
    ucNcode = ScalerGetByte(PB8_B3_N_F_REPORT0) + 2;
    ulFcode = TO_DWORD(0x00, ScalerGetBit(PB8_B4_N_F_REPORT1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)), ScalerGetByte(PB8_B5_N_F_REPORT2), ScalerGetByte(PB8_B6_N_F_REPORT3));
    ulNFcode = ((DWORD)ucNcode << 20) + ulFcode;

    // Calculating Vco clock from final n.f code of PLL
    ulClockHz = ScalerGlobalComputeDwordMulDiv(ulNFcode, pstDpInfo->stDpLinkInfo.ulPllInputClockHz, 1UL << 20);

    ucdiv_sum = pstDpInfo->stDpLinkInfo.ucPllDivs * pstDpInfo->stDpLinkInfo.ucPllDivo;

    ulClockHz = (ulClockHz + (ucdiv_sum >> 1)) / ucdiv_sum;

    if(GET_DP_MAC_STREAM_RX1_STREAM_OUTPUT_X2_CLK() == _TRUE)
    {
        // Fix using 1-Pixel Mode
        ulClockHz /= 2;
    }
    else
    {
        ulClockHz *= pstDpInfo->stDpLinkInfo.ucPixelMode;
    }

    pstDpInfo->stDpLinkInfo.ulStreamClockHz = ulClockHz;

    SET_DP_MAC_STREAM_RX1_STREAM_CLOCK(pstDpInfo->stDpLinkInfo.ulStreamClockHz);

    DebugMessageDpRx("DP MAC RX1: Final Stream Clock", pstDpInfo->stDpLinkInfo.ulStreamClockHz);
}

//--------------------------------------------------
// Description  : DP HDCP Measure Check
// Input Value  : None
// Output Value : FALSE => Measure Check Fail
//--------------------------------------------------
bit ScalerDpMacStreamRx1HdcpMeasureCheck(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
    WORD usVtotal = 0;
    DWORD ulLinkClk = 0;
    WORD usHTotalCount = 0;

    // Pop up Main Stream Attributes
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Vtotal
    usVtotal = ScalerGetWord(PB9_10_MSA_VTTE_0);

    if(usVtotal == 0)
    {
        return _FALSE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
    {
        return _FALSE;
    }
#endif

    PDATA_DWORD(0) = ScalerDpMacDphyRxSignalDetectMeasureCount(enumInputPort, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0), _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_2000_CYCLE);

    if(PDATA_DWORD(0) == 0)
    {
        switch(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort))
        {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            case _DP_LINK_UHBR20:

                PDATA_DWORD(0) = _DP_RX_VCO_TARGET_COUNT_2000_UHBR20_SAVED;

                break;

            case _DP_LINK_UHBR13_5:

                PDATA_DWORD(0) = _DP_RX_VCO_TARGET_COUNT_2000_UHBR13_5_SAVED;

                break;

            case _DP_LINK_UHBR10:

                PDATA_DWORD(0) = _DP_RX_VCO_TARGET_COUNT_2000_UHBR10_SAVED;

                break;
#endif
            case _DP_LINK_HBR3_9G:

                PDATA_DWORD(0) = _DP_RX_VCO_TARGET_COUNT_2000_HBR3_9G_SAVED;

                break;

            case _DP_LINK_HBR3:

                PDATA_DWORD(0) = _DP_RX_VCO_TARGET_COUNT_2000_HBR3_SAVED;

                break;

            case _DP_LINK_HBR2:

                PDATA_DWORD(0) = _DP_RX_VCO_TARGET_COUNT_2000_HBR2_SAVED;

                break;

            case _DP_LINK_HBR:

                PDATA_DWORD(0) = _DP_RX_VCO_TARGET_COUNT_2000_HBR_SAVED;

                break;

            case _DP_LINK_RBR:
            default:

                PDATA_DWORD(0) = _DP_RX_VCO_TARGET_COUNT_2000_RBR_SAVED;

                break;
        }
    }

    PDATA_DWORD(0) = (PDATA_DWORD(0) * _GDIPHY_RX_GDI_CLK_KHZ);

    // Link Clk in KHz
    ulLinkClk = (PDATA_DWORD(0) / 1000);

    DebugMessageDpRx("DP MAC RX1: Current Link Clk", ulLinkClk);

    // Start to Measure Vertical BS to BS Counter by GDI Clock
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), 0x00);
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Pop up The result
    SET_DP_MAC_STREAM_RX1_MEASURE_POP_UP_8B10B();

    // Get Measure Result
    PDATA_DWORD(0) = TO_DWORD(0,
                              (ScalerGetByte(PB8_58_MN_MEAS_CTRL) & 0x1F),
                              ScalerGetByte(PB8_59_MN_MEAS_VLN_M),
                              ScalerGetByte(PB8_5A_MN_MEAS_VLN_L));

    // Get Measure Htotal Counts
    PDATA_WORD(3) = ScalerGetWord(PB8_5B_MN_MEAS_HLN_M);

    // Disable Measure Block
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), 0x00);

    // Convert HTotal Count from 1/2 Link Clk to GDI Clk
    usHTotalCount = ((DWORD)PDATA_WORD(3) * _GDIPHY_RX_GDI_CLK_KHZ * 2 + (ulLinkClk >> 1)) / ulLinkClk;
    PDATA_DWORD(1) = ((DWORD)usHTotalCount & 0x0000FFFF);

    PDATA_WORD(2) = PDATA_DWORD(0) / PDATA_DWORD(1);

    // 2% Tolerance
    if((ABSDWORD(PDATA_WORD(2), usVtotal)) > (usVtotal * 2 / 100))
    {
        return _FALSE;
    }

    return _TRUE;
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP H Porch Enlarge
// Input Value  : Vlaue for H Proch Enlarge
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1HPorchEnlarge(StructTimingInfo *pstDpTimingInfo)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
    WORD usTempHtotal = pstDpTimingInfo->usHTotal;
    WORD usTempHWidth = pstDpTimingInfo->usHWidth;
    BYTE ucDpHPorchExtend = _INPUT_H_PORCH_EXTEND;
    enumInputPort = enumInputPort;

    if(ScalerDpRxGetMacStreamSourceType(_DP_MAC_1) == _STREAM_SOURCE_MST2SST)
    {
        CLR_DP_MAC_STREAM_RX1_H_PORCH_ENLARGE();

        return;
    }

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        if(ScalerDpMacStreamRx1DualCableJudge_128b132b() == _TRUE)
        {
            // For Two Cable Mode
            ucDpHPorchExtend /= 2;
        }
    }
    else
#endif
    {
        if(ScalerDpMacStreamRx1DualCableJudge_8b10b() == _TRUE)
        {
            // For Two Cable Mode
            ucDpHPorchExtend /= 2;
        }
    }

    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        // Check if H porch is less than ucDpHPorchExtend
        if((usTempHtotal - usTempHWidth) < ucDpHPorchExtend)
        {
            SET_DP_MAC_STREAM_RX1_H_PORCH_ENLARGE(ucDpHPorchExtend - (usTempHtotal - usTempHWidth));

            usTempHtotal = usTempHtotal + GET_DP_MAC_STREAM_RX1_H_PORCH_ENLARGE();
        }
        else
        {
            CLR_DP_MAC_STREAM_RX1_H_PORCH_ENLARGE();
        }
    }
    else
    {
        CLR_DP_MAC_STREAM_RX1_H_PORCH_ENLARGE();
    }

    if((usTempHtotal % 2) != 0)
    {
        // Avoid Htotal value is odd.
        usTempHtotal += 1;
    }

    pstDpTimingInfo->usHTotal = usTempHtotal;
}
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check FREESYNC Enable
// Input Value  : None
// Output Value : _TRUE: FREESYNC change
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetFreeSyncStatusChange(void)
{
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(_DP_MAC_1);

#if(_DRR_FREE_RUN_DISPLAY_SUPPORT == _OFF)
    if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
    {
        WORD usIVfreq = ScalerDpMacStreamRx1GetVFreq();

        if((usIVfreq < (_PANEL_DP_FREESYNC_MIN_FRAME_RATE - _PANEL_FRAME_SYNC_MARGIN)) ||
           (usIVfreq > (_PANEL_DP_FREESYNC_MAX_FRAME_RATE + _PANEL_FRAME_SYNC_MARGIN)))
        {
            DebugMessageDpRx("7. DP MAC RX1: FREESYNC IVF out of panel range", usIVfreq);
            return _TRUE;
        }
    }
#endif

    if(ScalerDpMacStreamRxFreeSyncGetStreamConfig(enumDpMacStreamSourceType) != GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE())
    {
        DebugMessageDpRx("7. DP MAC RX1: FREESYNC ignore MSA 0 -> 1", 0);
        return _TRUE;
    }

    return _FALSE;
}
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DP Color Sapace Change WD
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetColorSpaceChangeWD(bit bEn)
{
    if(bEn == _ENABLE)
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
        {
            ScalerDpMacStreamRx1SetColorSpaceChangeWD_128b132b(bEn);
        }
        else
#endif
        {
            ScalerDpMacStreamRx1SetColorSpaceChangeWD_8b10b(bEn);
        }
    }
    else
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerDpMacStreamRx1SetColorSpaceChangeWD_128b132b(bEn);
#endif
        ScalerDpMacStreamRx1SetColorSpaceChangeWD_8b10b(bEn);
    }
}

//--------------------------------------------------
// Description  : Enable DP MSA Change IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SstSetMsaChangeIRQ(bit bEn)
{
    if(bEn == _ENABLE)
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B)
        {
            // DP20(In MST) No Need
        }
        else
#endif
        {
            ScalerDpMacStreamRx1SstSetMsaChangeIRQ_8b10b(bEn);
        }
    }
    else
    {
        // DP20(In MST) No Need
        ScalerDpMacStreamRx1SstSetMsaChangeIRQ_8b10b(bEn);
    }
}

//--------------------------------------------------
// Description  : Check Msa Misc Chang Support or Not
// Input Value  : None
// Output Value : _ON(Support)/_OFF(Not Support)
//--------------------------------------------------
bit ScalerDpMacStreamRx1MsaMiscChangeSupportCheck(void)
{
#if(_DP_FREESYNC_SUPPORT == _ON)
    BYTE pucMSATemp0[18] = {0};
    BYTE pucMSATemp1[18] = {0};
#endif

    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return _OFF;
    }

    // Msa Misc Change Check only when SST
    if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _ENABLE)
    {
        return _OFF;
    }

    // Msa Misc Change Check Only When MISC color mode
    if(GET_DP_MAC_STREAM_RX1_VSC_SDP_COLOR_MODE() == _TRUE)
    {
        return _OFF;
    }

    // Msa Misc Change Check Only When YUV444 Or RGB
    if((GET_COLOR_SPACE(enumInputPort) != _COLOR_SPACE_RGB) && (GET_COLOR_SPACE(enumInputPort) != _COLOR_SPACE_YCBCR444))
    {
        return _OFF;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    // FreeSync mode: Msa Misc Change Check Enable Only When MSA not Random Change
    if(ScalerDrrFreeSyncDpGetEnable(enumInputPort) == _TRUE)
    {
        // Pop up Main Stream Attributes
        ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

        memcpy(pucMSATemp0, (volatile BYTE xdata *)PB9_08_MSA_HTT_0, sizeof(pucMSATemp0));

        ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);

        // Pop up Main Stream Attributes
        ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

        memcpy(pucMSATemp1, (volatile BYTE xdata *)PB9_08_MSA_HTT_0, sizeof(pucMSATemp1));

        if(memcmp(pucMSATemp0, pucMSATemp1, sizeof(pucMSATemp0)) != 0)
        {
            return _OFF;
        }
    }
#endif

    return _ON;
}

//--------------------------------------------------
// Description  : Get Msa Debounce Status
// Input Value  : NONE
// Output Value : _ENABLE/ DISABLE
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetMsaDebounceStatus(void)
{
    if(ScalerGetBit(PB9_00_MN_STRM_ATTR_CTRL, _BIT1) == _BIT1)
    {
        return _ENABLE;
    }
    else
    {
        return _DISABLE;
    }
}
#endif

//--------------------------------------------------------------
// Description  : DP Pixel Mode Setting
// Input Value  : PixelMode
// Output Value : True --> Register Setting Pass for Pixel Mode
//--------------------------------------------------------------
bit ScalerDpMacStreamRx1PixelModeSetting_8b10b(EnumDpStreamPixelMode enumPixelMode)
{
    switch(enumPixelMode)
    {
        case _1_PIXEL_MODE:

            ScalerSetBit(PB8_1F_SOURCE_SEL_4, ~(_BIT7 | _BIT1 | _BIT0), 0x00);

            return _TRUE;

        case _2_PIXEL_MODE:

            ScalerSetBit(PB8_1F_SOURCE_SEL_4, ~(_BIT7 | _BIT1 | _BIT0), _BIT0);

            return _TRUE;

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP Video Setting for PG 8b10b
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1VideoSetting_8b10b(void)
{
    // Set Color Space for Display Format Gen.
    switch(GET_DP_MAC_STREAM_RX1_COLOR_SPACE())
    {
        case _COLOR_SPACE_RGB:
            DebugMessageDpRx("DP MAC RX1: _COLOR_SPACE_RGB", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
            break;

        case _COLOR_SPACE_YCBCR444:
            DebugMessageDpRx("DP MAC RX1: _COLOR_SPACE_YCBCR444", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
            break;

        case _COLOR_SPACE_YCBCR422:
            DebugMessageDpRx("DP MAC RX1: _COLOR_SPACE_YCBCR422", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), _BIT3);
            break;

        case _COLOR_SPACE_YCBCR420:
            DebugMessageDpRx("DP MAC RX1: _COLOR_SPACE_YCBCR420", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
            break;

        case _COLOR_SPACE_Y_ONLY:
            DebugMessageDpRx("DP MAC RX1: _COLOR_SPACE_Y_ONLY", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
            break;

        case _COLOR_SPACE_RAW:
            DebugMessageDpRx("DP MAC RX1: _COLOR_SPACE_RAW", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
            break;

        default:
            // RGB
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
            break;
    }

    // Set Color Depth for Display Format Gen.
    ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), GET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE());
    DebugMessageDpRx("DP MAC RX1: _COLOR_DEPTH", GET_DP_MAC_STREAM_RX1_COLOR_DEPTH());
}

//--------------------------------------------------
// Description  : DP BS/BE to VS Delay Calculation
// Input Value  : None
// Output Value : BS/BE to VS Delay
//--------------------------------------------------
void ScalerDpMacStreamRx1SetBxToVsDelay_8b10b(StructDpInfo *pstDpInfo)
{
    DWORD ulVFrontPorch = 0;
    DWORD ulHFrontPorch = 0;
    DWORD ulBxToVsDelay = 0;
    WORD usFifoOffset = 0;

    // Get V Front Porch, unit is pixel clock
    ulVFrontPorch = ((DWORD)GET_DP_MAC_STREAM_RX1_VFRONT_PORCH()) * pstDpInfo->stDpTimingInfo.usHTotal;

    // Get H Front Porch, unit is pixel clock
    ulHFrontPorch = (DWORD)(pstDpInfo->stDpTimingInfo.usHTotal - pstDpInfo->stDpTimingInfo.usHWidth - pstDpInfo->stDpTimingInfo.usHStart);

    // Get Video FIFO Size, unit is pixel clock
    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
    {
        // FifoOffset = (Video FIFO Size / (2 * depth per color)), color format is YCbCr 4:2:2
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE_8B10B / (2 * (WORD)GET_DP_MAC_STREAM_RX1_COLOR_DEPTH());
    }
    else
    {
        // FifoOffset = (Video FIFO Size / (3 * depth per color)), color format is RGB or YCbCr 4:4:4 or others
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE_8B10B / (3 * (WORD)GET_DP_MAC_STREAM_RX1_COLOR_DEPTH());
    }

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
    // HBR/HBE Adjust Fifo Offset
    if(pstDpInfo->stDpHblankingModifyInfo.enumHblankingModifyMode != _NO_HBLANKING_MODIFY)
    {
        usFifoOffset = ScalerDpMacStreamRxHblankingModifyFifoOffsetUpdate(pstDpInfo, usFifoOffset);
    }
#endif
    {
        usFifoOffset = usFifoOffset / 2;
    }

    if(ScalerDpMacStreamRx1FrameSyncBeModeCheck() == _TRUE)
    {
        if(pstDpInfo->stDpLinkInfo.ulStreamClockHz == 0x00)
        {
            DebugMessageDpRx("DP MAC RX1: Stream Clk is invalid", 0);

            return;
        }

        // Get BE to VS Delay, unit is 1/2 link clock
        ulBxToVsDelay = ScalerGlobalComputeDwordMulDiv(((DWORD)usFifoOffset - pstDpInfo->stDpTimingInfo.usHStart), pstDpInfo->stDpLinkInfo.ulLinkClockHz / 2, pstDpInfo->stDpLinkInfo.ulStreamClockHz);
    }
    else
    {
        if(pstDpInfo->stDpLinkInfo.ulStreamClockHz == 0x00)
        {
            DebugMessageDpRx("DP MAC RX1: Stream Clk is invalid", 0);

            return;
        }

        // Get BS to VS Delay, unit is 1/2 link clock
        ulBxToVsDelay = ScalerGlobalComputeDwordMulDiv((ulVFrontPorch + ulHFrontPorch + (DWORD)usFifoOffset), pstDpInfo->stDpLinkInfo.ulLinkClockHz / 2, pstDpInfo->stDpLinkInfo.ulStreamClockHz);
    }

    // Set BX to VS Delay of Odd Field
    ScalerSetByte(PB8_35_OVBLK2VS_H, LOBYTE(HIWORD(ulBxToVsDelay)));
    ScalerSetByte(PB8_36_OVBLK2VS_M, HIBYTE(LOWORD(ulBxToVsDelay)));
    ScalerSetByte(PB8_37_OVBLK2VS_L, LOBYTE(LOWORD(ulBxToVsDelay)));

    if(pstDpInfo->stDpLinkInfo.b1InterlaceOddMode == _TRUE)
    {
        if(pstDpInfo->stDpLinkInfo.ulStreamClockHz == 0x00)
        {
            DebugMessageDpRx("DP MAC RX1: Stream Clk is invalid", 0);

            return;
        }

        // BxtoVsDelay = BxtoVsDelay + 1 Line(Unit is 1/2 Link Clock)
        ulBxToVsDelay += ScalerGlobalComputeDwordMulDiv((DWORD)pstDpInfo->stDpTimingInfo.usHTotal, pstDpInfo->stDpLinkInfo.ulLinkClockHz / 2, pstDpInfo->stDpLinkInfo.ulStreamClockHz);

        SET_DP_MAC_STREAM_RX1_INTERLACE_VTOTAL_NUMBER(_ODD);
    }
    else
    {
        SET_DP_MAC_STREAM_RX1_INTERLACE_VTOTAL_NUMBER(_EVEN);
    }

    // Set BX to VS Delay of Even Field
    ScalerSetByte(PB8_32_EVBLK2VS_H, LOBYTE(HIWORD(ulBxToVsDelay)));
    ScalerSetByte(PB8_33_EVBLK2VS_M, HIBYTE(LOWORD(ulBxToVsDelay)));
    ScalerSetByte(PB8_34_EVBLK2VS_L, LOBYTE(LOWORD(ulBxToVsDelay)));
}

//--------------------------------------------------
// Description  : DP Video Fifo Check 8b10b
// Input Value  : Fifo Check Condition
// Output Value : True --> Fifo not over/underflow
//--------------------------------------------------
bit ScalerDpMacStreamRx1FifoCheck_8b10b(EnumDpFifoCheckCondition enumFifoCheckCondition)
{
    if(enumFifoCheckCondition == _DP_FIFO_DELAY_CHECK)
    {
        ScalerSetBit(PB8_21_PG_CTRL_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        pData[0] = 0;

        while(pData[0] < 6)
        {
            ScalerTimerDelayXms(10);

            if((ScalerGetBit(PB8_21_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(PB8_21_PG_CTRL_1, _BIT2) == _BIT2))
            {
                return _FALSE;
            }

            pData[0]++;
        }
    }
    else
    {
        if((ScalerGetBit(PB8_21_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(PB8_21_PG_CTRL_1, _BIT2) == _BIT2))
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Adjust Vsync Delay
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1AdjustVsyncDelay_8b10b(StructDpInfo *pstDpInfo)
{
    DWORD ulBStoVSDelayDelta = 0;
    BYTE ucOneFrameTime = 0;

    if(ScalerGetBit(PB8_21_PG_CTRL_1, (_BIT1 | _BIT0)) == 0x00)// Fifo Ok
    {
        return;
    }
    else if(ScalerGetBit(PB8_21_PG_CTRL_1, _BIT0) == _BIT0) // Fifo Overflow
    {
        if(pstDpInfo->stDpLinkInfo.ulStreamClockHz == 0x00)
        {
            DebugMessageDpRx("DP MAC RX1: Stream Clk is invalid", 0);

            return;
        }

        // 1 Line = HTotal * (1/2 Link Clock) / Stream Clock
        ulBStoVSDelayDelta = ScalerGlobalComputeDwordMulDiv((DWORD)pstDpInfo->stDpTimingInfo.usHTotal, pstDpInfo->stDpLinkInfo.ulLinkClockHz / 2, pstDpInfo->stDpLinkInfo.ulStreamClockHz);

        DebugMessageDpRx("7. DP MAC RX1: Fifo Overflow --> nVidia Case", ulBStoVSDelayDelta);
    }
    else if(ScalerGetBit(PB8_21_PG_CTRL_1, _BIT1) == _BIT1) // Fifo Underflow
    {
        if(pstDpInfo->stDpTimingInfo.usHWidth != 1366)
        {
            return;
        }

        PDATA_WORD(0) = pstDpInfo->stDpTimingInfo.usHWidth - 2;

        // Set HWidth
        ScalerSetByte(PB8_45_MN_DPF_HWD_M, HIBYTE(PDATA_WORD(0)));
        ScalerSetByte(PB8_46_MN_DPF_HWD_L, LOBYTE(PDATA_WORD(0)));

        // BS2BS Delta = 2 * (1/2 Link Clock) / Stream Clock
        ulBStoVSDelayDelta = pstDpInfo->stDpLinkInfo.ulLinkClockHz / pstDpInfo->stDpLinkInfo.ulStreamClockHz;

        DebugMessageDpRx("7. DP MAC RX1: Fifo Underflow --> QD882 Case", ulBStoVSDelayDelta);
    }

    // Get BStoVSDelay of Even Field
    PDATA_DWORD(0) = TO_DWORD(0,
                              ScalerGetByte(PB8_32_EVBLK2VS_H),
                              ScalerGetByte(PB8_33_EVBLK2VS_M),
                              ScalerGetByte(PB8_34_EVBLK2VS_L));

    // Get BStoVSDelay of Odd Field
    PDATA_DWORD(1) = TO_DWORD(0,
                              ScalerGetByte(PB8_35_OVBLK2VS_H),
                              ScalerGetByte(PB8_36_OVBLK2VS_M),
                              ScalerGetByte(PB8_37_OVBLK2VS_L));

    // BStoVSDelay of Even Field = BStoVSDelay of Even Field - BStoVSDelayDelta
    PDATA_DWORD(0) -= ulBStoVSDelayDelta;

    // BStoVSDelay of Odd Field = BStoVSDelay of Odd Field - BStoVSDelayDelta
    PDATA_DWORD(1) -= ulBStoVSDelayDelta;

    // Set Even Field BS to VS Delay
    ScalerSetByte(PB8_32_EVBLK2VS_H, (BYTE)(PDATA_DWORD(0) >> 16));
    ScalerSetByte(PB8_33_EVBLK2VS_M, (BYTE)(PDATA_DWORD(0) >> 8));
    ScalerSetByte(PB8_34_EVBLK2VS_L, (BYTE)(PDATA_DWORD(0) >> 0));

    // Set Odd Field BS to VS Delay
    ScalerSetByte(PB8_35_OVBLK2VS_H, (BYTE)(PDATA_DWORD(1) >> 16));
    ScalerSetByte(PB8_36_OVBLK2VS_M, (BYTE)(PDATA_DWORD(1) >> 8));
    ScalerSetByte(PB8_37_OVBLK2VS_L, (BYTE)(PDATA_DWORD(1) >> 0));

    // Reset Display Format Gen
    ScalerSetBit(PB8_30_DPF_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(PB8_30_DPF_CTRL_0, ~_BIT7, _BIT7);

    // Polling Vertical BS
    ScalerTimerPollingFlagProc(50, PB9_01_DP_VBID, _BIT0, _TRUE);

#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_JUDGE_OOR() == _TRUE)
    {
        // Get 1 Frame Time for Vfreq = 5Hz, unit is ms
        ucOneFrameTime = 250;
    }
    else
#endif
    {
        // Get 1 Frame Time, unit is ms
        ucOneFrameTime = pstDpInfo->stDpLinkInfo.ulVBsToBsCountN / _GDIPHY_RX_GDI_CLK_KHZ + 1;
    }

    // Delay 1 Frame Time for PG Stable
    ScalerTimerDelayXms(ucOneFrameTime);
}

//--------------------------------------------------------
// Description  : Wait for Vertical Blanking for 8B/10B
// Input Value  : BYTE ucOneFrameTime
// Output Value : None
//--------------------------------------------------------
void ScalerDpMacStreamRx1WaitVBlanking_8B10B(BYTE ucOneFrameTime)
{
    WORD usTemp = 0;

    // Unit In 100us (Polling Interval)
    WORD usTwoFrameCounter = (WORD)ucOneFrameTime * 10 * 2;

    if(ScalerGetBit(PB9_01_DP_VBID, _BIT0) == _BIT0)
    {
        while((ScalerGetBit(PB9_01_DP_VBID, _BIT0) == _BIT0) && (usTemp < usTwoFrameCounter))
        {
            DELAY_XUS(100);

            usTemp += 1;
        }

        usTemp = 0;

        while((ScalerGetBit(PB9_01_DP_VBID, _BIT0) == 0x00) && (usTemp < usTwoFrameCounter))
        {
            DELAY_XUS(100);

            usTemp += 1;
        }
    }
    else
    {
        while((ScalerGetBit(PB9_01_DP_VBID, _BIT0) == 0x00) && (usTemp < usTwoFrameCounter))
        {
            DELAY_XUS(100);

            usTemp += 1;
        }
    }
}

//--------------------------------------------------
// Description  : Sdp Change Dtect
// Input Value  : Dp Sdp Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpChgDetect_8b10b(EnumDpSdpType enumDpSdpType)
{
    BYTE ucInfoFrameVersion = 0;

    ucInfoFrameVersion = ucInfoFrameVersion;

    switch(enumDpSdpType)
    {
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _DP_SDP_TYPE_INFOFRAME_SPD:
        {
            bit bAmdSdpInfolocalDimmingDisableControl = 0;

            bAmdSdpInfolocalDimmingDisableControl = (bit)(GET_DP_MAC_STREAM_RX1_AMD_SPD_INFO(_SPD_INFO_SEAMLESS_LOCAL_DIMMING_DISABLE_CONTROL));

            if((ScalerGetBit(PB9_31_DP_SDP_SPD_CHG, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00) || (bAmdSdpInfolocalDimmingDisableControl != GET_DP_MAC_STREAM_RX1_AMD_SPD_LOCAL_DIMMING()))
            {
                ScalerSetBit(PB9_31_DP_SDP_SPD_CHG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                SET_DP_MAC_STREAM_RX1_AMD_SPD_LOCAL_DIMMING(bAmdSdpInfolocalDimmingDisableControl);

                SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE();

                ucInfoFrameVersion = (ScalerDpMacStreamRx1GetSdpInfoHB3(_DP_SDP_TYPE_INFOFRAME_SPD) >> 2);

                if(GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_VERSION() != ucInfoFrameVersion)
                {
                    SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_VERSION(ucInfoFrameVersion);

                    SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE_EVENT(_SDP_EVENT_HEADER_CHANGE);
                }
                else
                {
                    SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE_EVENT(_SDP_EVENT_DATA_CHANGE);
                }
            }
            else
            {
                CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE();
            }

            break;
        }
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        case _DP_SDP_TYPE_ADAPTIVESYNC:

            if(ScalerGetBit(PB9_60_DP_SDP_ADP_SYNC_CTRL, (_BIT6 | _BIT4)) != 0x00)
            {
                ScalerSetBit(PB9_60_DP_SDP_ADP_SYNC_CTRL, ~(_BIT6 | _BIT4 | _BIT3), (_BIT6 | _BIT4));

                SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE();

                SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE_EVENT(_SDP_EVENT_HEADER_CHANGE);
            }
            else
            {
                CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE();
            }

            break;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_HDR:

            if(ScalerGetBit(PB9_38_DP_SDP_HDR_INFO_MNT, (_BIT6 | _BIT4)) != 0x00)
            {
                ScalerSetBit(PB9_38_DP_SDP_HDR_INFO_MNT, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

                SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE();

                ucInfoFrameVersion = (ScalerDpMacStreamRx1GetSdpInfoHB3(_DP_SDP_TYPE_INFOFRAME_HDR) >> 2);

                if(GET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_VERSION() != ucInfoFrameVersion)
                {
                    SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_VERSION(ucInfoFrameVersion);

                    SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE_EVENT(_SDP_EVENT_HEADER_CHANGE);
                }
                else
                {
                    SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE_EVENT(_SDP_EVENT_DATA_CHANGE);
                }
            }
            else
            {
                CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE();
            }

            break;
#endif

#if(_AUDIO_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_AUDIO:
        {
            BYTE pucAudioInfoSdpData[_HW_DP_SDP_PAYLOAD_LENGTH] = {0};

            ScalerDpMacStreamRx1GetSdpPktData(_DP_SDP_TYPE_INFOFRAME_AUDIO, pucAudioInfoSdpData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);

            if(memcmp(pucAudioInfoSdpData, g_pucDpMacRx1AudioInfoSdpData, _HW_DP_SDP_PAYLOAD_LENGTH) != 0)
            {
                memcpy(g_pucDpMacRx1AudioInfoSdpData, pucAudioInfoSdpData, _HW_DP_SDP_PAYLOAD_LENGTH);

                SET_DP_MAC_STREAM_RX1_AUDIO_INFO_FRAME_CHANGE();

                SET_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_CHANGE_EVENT(_SDP_EVENT_HEADER_CHANGE);
            }
            else
            {
                CLR_DP_MAC_STREAM_RX1_AUDIO_INFO_FRAME_CHANGE();
            }

            break;
        }
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _DP_SDP_TYPE_PPS:

            if(ScalerGetBit(P26_BF_DP_PPS_RO_CTRL, _BIT6) == _BIT6)
            {
                ScalerSetBit(P26_BF_DP_PPS_RO_CTRL, ~_BIT6, _BIT6);

                SET_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE();
            }
            else
            {
                CLR_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE();
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Sdp Receive Check
// Input Value  : Dp Sdp Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpRevDetect_8b10b(EnumDpSdpType enumDpSdpType)
{
    switch(enumDpSdpType)
    {
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _DP_SDP_TYPE_INFOFRAME_SPD:

            if(ScalerGetBit(PB9_2F_DP_SDP_SPD_CTRL, _BIT6) == _BIT6)
            {
                ScalerSetBit(PB9_2F_DP_SDP_SPD_CTRL, ~_BIT6, _BIT6);

                SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE(_SDP_STATE_RECEIVED);
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE(_SDP_STATE_NOT_RECEIVED);
            }

            break;
#endif
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        case _DP_SDP_TYPE_ADAPTIVESYNC:

            if(ScalerGetBit(PB9_60_DP_SDP_ADP_SYNC_CTRL, _BIT6) == _BIT6)
            {
                ScalerSetBit(PB9_60_DP_SDP_ADP_SYNC_CTRL, ~(_BIT6 | _BIT3), _BIT6);

                SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_RECEIVED_STATE(_SDP_STATE_RECEIVED);
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_RECEIVED_STATE(_SDP_STATE_NOT_RECEIVED);
            }

            break;
#endif
#if(_DP_HDR10_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_HDR:
        {
#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
            EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

            if((ScalerDpRxGetDramReceiveFromDmDetect(enumInputPort) == _TRUE) || (ScalerGetBit(PB9_37_DP_SDP_HDR_INFO_CTRL, _BIT6) == _BIT6))
#else
            if(ScalerGetBit(PB9_37_DP_SDP_HDR_INFO_CTRL, _BIT6) == _BIT6)
#endif
            {
#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
                // if realtime OSD support DM
                if(ScalerDpRxGetOsdDmSupport(enumInputPort) == _ON)
                {
                    // clear FW flag only, don't w1c hdr received bit due to DM Detecting need
                    ScalerDpRxClrDramReceiveFromDmDetect(enumInputPort);
                }
                else
                {
                    ScalerSetBit(PB9_37_DP_SDP_HDR_INFO_CTRL, ~_BIT6, _BIT6);
                }
#else
                ScalerSetBit(PB9_37_DP_SDP_HDR_INFO_CTRL, ~_BIT6, _BIT6);
#endif
                SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_RECEIVED_STATE(_SDP_STATE_RECEIVED);
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_RECEIVED_STATE(_SDP_STATE_NOT_RECEIVED);
            }

            break;
        }
#endif
#if(_AUDIO_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_AUDIO:

            if(ScalerGetBit(PB9_E0_SDP_ACM_ISRC_INT, _BIT1) == _BIT1)
            {
                ScalerSetBit(PB9_E0_SDP_ACM_ISRC_INT, ~(_BIT6 | _BIT5 | _BIT2 | _BIT1), _BIT1);

                SET_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_RECEIVED_STATE(_SDP_STATE_RECEIVED);
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_RECEIVED_STATE(_SDP_STATE_NOT_RECEIVED);
            }

            break;
#endif
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _DP_SDP_TYPE_PPS:

            // Check SDP PPS Received Status
            if(ScalerGetBit(PB9_E7_DP_MAC_PPS_DYN_MDATA_CTRL, _BIT6) == _BIT6)
            {
                ScalerSetBit(PB9_E7_DP_MAC_PPS_DYN_MDATA_CTRL, ~(_BIT6 | _BIT4), _BIT6);

                SET_DP_MAC_STREAM_RX1_PPS_SDP_RECEIVED_STATE(_SDP_STATE_RECEIVED);
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_PPS_SDP_RECEIVED_STATE(_SDP_STATE_NOT_RECEIVED);
            }

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DSC Get PPS Packet Byte
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1GetPpsSdpInfo_8b10b(void)
{
    // Backup The DSC PPS with Picture Height
    SET_DP_MAC_STREAM_RX1_DSC_PIC_HEIGHT((WORD)ScalerGetByte(P26_B6_DP_PPS_RO_DATA_BYTE_6) << 8 | ScalerGetByte(P26_B7_DP_PPS_RO_DATA_BYTE_7));

    // Backup The DSC PPS with Picture Width
    SET_DP_MAC_STREAM_RX1_DSC_PIC_WIDTH((WORD)ScalerGetByte(P26_B8_DP_PPS_RO_DATA_BYTE_8) << 8 | ScalerGetByte(P26_B9_DP_PPS_RO_DATA_BYTE_9));

    // Backup The DSC PPS with Slice Height
    SET_DP_MAC_STREAM_RX1_DSC_SLICE_HEIGHT((WORD)ScalerGetByte(P26_BA_DP_PPS_RO_DATA_BYTE_10) << 8 | ScalerGetByte(P26_BB_DP_PPS_RO_DATA_BYTE_11));

    // Backup The DSC PPS with Slice Width
    SET_DP_MAC_STREAM_RX1_DSC_SLICE_WIDTH((WORD)ScalerGetByte(P26_BC_DP_PPS_RO_DATA_BYTE_12) << 8 | ScalerGetByte(P26_BD_DP_PPS_RO_DATA_BYTE_13));

    // Backup The DSC PPS with BPP
    SET_DP_MAC_STREAM_RX1_DSC_COLOR_BPP(((WORD)ScalerGetByte(P26_B5_DP_PPS_RO_DATA_BYTE_4) & 0x03) << 8 | ScalerGetByte(P26_B0_DP_PPS_RO_CONFIG_DATA_0));

    // Backup The DSC PPS with BPC
    SET_DP_MAC_STREAM_RX1_DSC_COLOR_BPC((ScalerGetByte(P26_B4_DP_PPS_RO_DATA_BYTE_3) & 0xF0) >> 4);

    // Backup The DSC PPS with Native 420
    SET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_420((ScalerGetByte(P26_BE_DP_PPS_RO_DATA_BYTE_88) & _BIT1) >> 1);

    // Backup The DSC PPS with Native 422
    SET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_422((ScalerGetByte(P26_BE_DP_PPS_RO_DATA_BYTE_88) & _BIT0) >> 0);

    // Backup The DSC PPS with Simple 422
    SET_DP_MAC_STREAM_RX1_DSC_COLOR_SIMPLE_422((ScalerGetByte(P26_B5_DP_PPS_RO_DATA_BYTE_4) & _BIT3) >> 3);
}

//--------------------------------------------------
// Description  : Clr Sdp Ram
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpSramReset_8b10b(void)
{
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
    // Reset Spd Sdp Sram
    ScalerSetBit(PB9_2F_DP_SDP_SPD_CTRL, ~(_BIT6 | _BIT0), _BIT0);
    ScalerSetBit(PB9_2F_DP_SDP_SPD_CTRL, ~(_BIT6 | _BIT0), 0x00);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
    // Reset Hdr Sdp Sram
    ScalerSetBit(PB9_37_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT0), _BIT0);
    ScalerSetBit(PB9_37_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT0), 0x00);
#endif

#if(_AUDIO_SUPPORT == _ON)
    // Reset Isrc Sdp Sram
    ScalerSetBit(PB9_E0_SDP_ACM_ISRC_INT, ~(_BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB9_E0_SDP_ACM_ISRC_INT, ~(_BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif

#if((_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    // Reset Rsv0 Sdp Sram
    ScalerSetBit(PB9_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT4), _BIT4);
    ScalerSetBit(PB9_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT4), 0x00);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    // Reset Adaptivsync Sdp Sram
    ScalerSetBit(PB9_60_DP_SDP_ADP_SYNC_CTRL, ~(_BIT6 | _BIT4 | _BIT3), _BIT4);
    ScalerSetBit(PB9_60_DP_SDP_ADP_SYNC_CTRL, ~(_BIT6 | _BIT4 | _BIT3), 0x00);
#endif
}

//--------------------------------------------------
// Description  : DP Rx1 Set Clr Status Flag
// Input Value  : Dp Sdp Ram Index
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetSdpInitStatus_8b10b(EnumDpSdpRamIndex enumDpSdpRamIndex)
{
    switch(enumDpSdpRamIndex)
    {
        case _DP_SDP_BUFF_SPD:

            // Clr SPD Received Flag, Reset Sdp
            ScalerSetBit(PB9_2F_DP_SDP_SPD_CTRL, ~(_BIT6 | _BIT0), (_BIT6 | _BIT0));
            ScalerSetBit(PB9_2F_DP_SDP_SPD_CTRL, ~(_BIT6 | _BIT0), 0x00);

            // Clr SPD Chg Flag
            ScalerSetByte(PB9_31_DP_SDP_SPD_CHG, 0xFF);

            // Set Info Data Byte Re-mapping
            ScalerSetBit(PB9_2F_DP_SDP_SPD_CTRL, ~(_BIT6 | _BIT4), _BIT4);

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
            CLR_DP_MAC_STREAM_RX1_SPD_IFNOFRAME_DETECTING();
            CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE();
            CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_VERSION();
            CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE_EVENT();
            CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE();
            SET_DP_MAC_STREAM_RX1_AMD_SPD_LOCAL_DIMMING(_FALSE);
#endif
            break;

        case _DP_SDP_BUFF_HDR:

            // Clr HDR Received Flag, Reset Sdp
            ScalerSetBit(PB9_37_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT0), (_BIT6 | _BIT0));
            ScalerSetBit(PB9_37_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT0), 0x00);

            // Clr HDR Chg Flag
            ScalerSetBit(PB9_38_DP_SDP_HDR_INFO_MNT, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

            // Set Info Data Byte Re-mapping
            ScalerSetBit(PB9_37_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT4), _BIT4);

#if(_DP_HDR10_SUPPORT == _ON)
            CLR_DP_MAC_STREAM_RX1_HDR_IFNOFRAME_DETECTING();
            CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE();
            CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_VERSION();
            CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE_EVENT();
            CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_RECEIVED_STATE();
#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
            ScalerDpRxClrDramReceiveFromDmDetect(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1));
#endif
#endif

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
            CLR_DP_MAC_STREAM_RX1_DM_DRAM_INFO_FRAME_RECEIVED();
#endif
            break;

        // Audio Infoframe use ISRC SDP buff
        case _DP_SDP_BUFF_ISRC:

            // Clr ISRC Flag, Reset Sdp
            ScalerSetBit(PB9_E0_SDP_ACM_ISRC_INT, ~(_BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(PB9_E0_SDP_ACM_ISRC_INT, ~(_BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_AUDIO_SUPPORT == _ON)
            // Initial Audio Info Sdp Data
            memset(g_pucDpMacRx1AudioInfoSdpData, 0, 32);

            CLR_DP_MAC_STREAM_RX1_AUDIO_IFNOFRAME_DETECTING();
            CLR_DP_MAC_STREAM_RX1_AUDIO_INFO_FRAME_CHANGE();
            CLR_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_CHANGE_EVENT();
            CLR_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_RECEIVED_STATE();
#endif
            break;

        case _DP_SDP_BUFF_RSV0:

            // Disable RSV0 Ram Receive IRQ
            ScalerDpMacStreamRx1SdpIrqEnable_8b10b(_DP_SDP_BUFF_RSV0, _DISABLE);

            // Clr RSV0 Received Flag, Reset Sdp
            ScalerSetBit(PB9_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));
            ScalerSetBit(PB9_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT4), 0x00);

#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
            CLR_DP_MAC_STREAM_RX1_ADVANCED_HDR10_DETECTING();
            CLR_DP_MAC_STREAM_RX1_ADVANCED_HDR10_RECEIVED_STATE();
#endif

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
            CLR_DP_MAC_STREAM_RX1_DM_VSIF_DETECTING();
            CLR_DP_MAC_STREAM_RX1_DM_VSIF_RECEIVED_STATE();
#endif
            break;

        case _DP_SDP_BUFF_ADAPTIVESYNC:

            // Clr Adaptivsync Received Flag & Chg Flag, Reset Sdp
            ScalerSetBit(PB9_60_DP_SDP_ADP_SYNC_CTRL, ~(_BIT6 | _BIT4 | _BIT3), (_BIT6 | _BIT4 | _BIT3));
            ScalerSetBit(PB9_60_DP_SDP_ADP_SYNC_CTRL, ~(_BIT6 | _BIT4 | _BIT3), 0x00);

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
            CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_DETECTING();
            CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE();
            CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_VERSION();
            CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE_EVENT();
            CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_RECEIVED_STATE();
#endif
            break;

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _DP_SDP_BUFF_PPS:

            // Clr PPS Received Flag
            ScalerSetBit(PB9_E7_DP_MAC_PPS_DYN_MDATA_CTRL, ~(_BIT6 | _BIT4), _BIT6);

            // Clr PPS Chg Flag
            ScalerSetBit(P26_BF_DP_PPS_RO_CTRL, ~_BIT6, _BIT6);

            CLR_DP_MAC_STREAM_RX1_PPS_SDP_DETECTING();
            CLR_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE();
            CLR_DP_MAC_STREAM_RX1_PPS_SDP_RECEIVED_STATE();

            break;
#endif

        default:
            break;
    }
}

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
//----------------------------------------------------------------------
// Description  : Set SDP Meta Sram Rcv Mode
// Input Value  : enumDpSdpMetaIndex/enumDpSdpType/enumDpSdpMetaRcvMd
// Output Value : None
//----------------------------------------------------------------------
void ScalerDpMacStreamRx1SetSdpMetaSramRcvMode_8b10b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, EnumDpSdpType enumDpSdpType, EnumDpSdpMetaRcvMd enumDpSdpMetaRcvMd)
{
    switch(enumDpSdpMetaIndex)
    {
        case _DP_SDP_META_0:

            // Set SDP0 SRAM Receive SDP HB1
            ScalerSetByte(P26_D0_META_SDP0_TYPE, enumDpSdpType);

            // Set SDP0 SRAM Receive Mode(Chain or No-chain)
            ScalerSetBit(P26_D5_META_SDP0_CTRL1, ~_BIT5, enumDpSdpMetaRcvMd << 5);

            break;

        case _DP_SDP_META_1:

            // Set SDP1 SRAM Receive SDP HB1
            ScalerSetByte(P26_D1_META_SDP1_TYPE, enumDpSdpType);

            // Set SDP1 SRAM Receive Mode(Chain or No-chain)
            ScalerSetBit(P26_D6_META_SDP1_CTRL1, ~_BIT5, enumDpSdpMetaRcvMd << 5);

            break;

        case _DP_SDP_META_2:

            // Set SDP2 SRAM Receive SDP HB1
            ScalerSetByte(P26_D2_META_SDP2_TYPE, enumDpSdpType);

            // Set SDP2 SRAM Receive Mode(Chain or No-chain)
            ScalerSetBit(P26_D7_META_SDP2_CTRL1, ~_BIT5, enumDpSdpMetaRcvMd << 5);

            break;

        case _DP_SDP_META_3:

            // Set SDP3 SRAM Receive SDP HB1
            ScalerSetByte(P26_D3_META_SDP3_TYPE, enumDpSdpType);

            // Set SDP3 SRAM Receive Mode(Chain or No-chain)
            ScalerSetBit(P26_D8_META_SDP3_CTRL1, ~_BIT5, enumDpSdpMetaRcvMd << 5);

            break;

        case _DP_SDP_META_4:

            // Set SDP4 SRAM Receive SDP HB1
            ScalerSetByte(P26_D4_META_SDP4_TYPE, enumDpSdpType);

            // Set SDP4 SRAM Receive Mode(Chain or No-chain)
            ScalerSetBit(P26_D9_META_SDP4_CTRL1, ~_BIT5, enumDpSdpMetaRcvMd << 5);

            break;

        default:
            break;
    }

    ScalerDpMacStreamRx1SdpMetaSramIrqEnable_8b10b(enumDpSdpMetaIndex, _ENABLE);
}

//----------------------------------------------------------------
// Description  : Enable/Disable SDP Meta Sram IRQ
// Input Value  : enumDpSdpMetaIndex, ENABLE/DISABLE bit
// Output Value : None
//----------------------------------------------------------------
void ScalerDpMacStreamRx1SdpMetaSramIrqEnable_8b10b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, bit bEnable)
{
    switch(enumDpSdpMetaIndex)
    {
        case _DP_SDP_META_0:

            if(bEnable == _ENABLE)
            {
                // Set Meta SDP0 Rcv Done IRQ Enable
                ScalerSetBit(P26_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P26_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }
            else
            {
                // Set Meta SDP0 Rcv Done IRQ Disable
                ScalerSetBit(P26_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

            break;

        case _DP_SDP_META_1:

            if(bEnable == _ENABLE)
            {
                // Set Meta SDP1 Rcv Done IRQ Enable
                ScalerSetBit(P26_DB_META_SDP1_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P26_DB_META_SDP1_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }
            else
            {
                // Set Meta SDP1 Rcv Done IRQ Disable
                ScalerSetBit(P26_DB_META_SDP1_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

            break;

        case _DP_SDP_META_2:

            if(bEnable == _ENABLE)
            {
                // Set Meta SDP2 Rcv Done IRQ Enable
                ScalerSetBit(P26_DC_META_SDP2_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P26_DC_META_SDP2_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }
            else
            {
                // Set Meta SDP2 Rcv Done IRQ Disable
                ScalerSetBit(P26_DC_META_SDP2_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

            break;

        case _DP_SDP_META_3:

            if(bEnable == _ENABLE)
            {
                // Set Meta SDP3 Rcv Done IRQ Enable
                ScalerSetBit(P26_DD_META_SDP3_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P26_DD_META_SDP3_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }
            else
            {
                // Set Meta SDP3 Rcv Done IRQ Disable
                ScalerSetBit(P26_DD_META_SDP3_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

            break;

        case _DP_SDP_META_4:

            if(bEnable == _ENABLE)
            {
                // Set Meta SDP4 Rcv Done IRQ Enable
                ScalerSetBit(P26_DE_META_SDP4_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P26_DE_META_SDP4_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }
            else
            {
                // Set Meta SDP4 Rcv Done IRQ Disable
                ScalerSetBit(P26_DE_META_SDP4_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Enable/Disable SDP IRQ_en
// Input Value  : RSV Number, ENABLE/DISABLE bit
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpIrqEnable_8b10b(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable)
{
    switch(enumDpSdpRamIndex)
    {
        case _DP_SDP_BUFF_HDR:

            if(bEnable == _ENABLE)
            {
                // Set HDR IRQ Enable
                ScalerSetBit(PB9_37_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT5), _BIT5);
            }
            else
            {
                // Set HDR IRQ Disable
                ScalerSetBit(PB9_37_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT5), 0x00);
            }

            break;

        case _DP_SDP_BUFF_RSV0:

            if(bEnable == _ENABLE)
            {
                // Set RSV0 IRQ Enable
                ScalerSetBit(PB9_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT5), _BIT5);
            }
            else
            {
                // Set RSV0 IRQ Disable
                ScalerSetBit(PB9_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT5), 0x00);
            }

            break;

        default:
            break;
    }
}

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
//--------------------------------------------------
// Description  : Set First Be Irq 8b10b
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1Set1stBeIrqEnable_8b10b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Clr BE_1st Flag and Enable IRQ
        ScalerSetBit_EXINT(P26_E0_META_SRAM_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT0), _BIT2);
        ScalerSetBit_EXINT(P26_E0_META_SRAM_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT0), _BIT3);
    }
    else
    {
        // Clr Flag and Disable BE_1st Int
        ScalerSetBit_EXINT(P26_E0_META_SRAM_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT0), _BIT2);
    }
}
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Judge Output Cable No. is Dual or not
// Input Value  : None
// Output Value : _TRUE or _FLASE
//--------------------------------------------------
bit ScalerDpMacStreamRx1DualCableJudge_8b10b(void)
{
    WORD usHwidth = 0;
    WORD usVHeight = 0;

    usHwidth = (((WORD)ScalerGetByte(PB9_0C_MSA_HWD_0) << 8) | ScalerGetByte(PB9_0D_MSA_HWD_1));
    usVHeight = (((WORD)ScalerGetByte(PB9_16_MSA_VHT_0) << 8) | ScalerGetByte(PB9_17_MSA_VHT_1));

    // Make sure the MSA Value is Valid
    if((usHwidth == 0) || (usVHeight == 0))
    {
        return _FALSE;
    }

    // For Normal Aspect Ratio
    if(usHwidth < usVHeight)
    {
        return _TRUE;
    }
    else
    {
        PDATA_WORD(0) = ((DWORD)usHwidth * 100 / usVHeight);

        // For 21:9 Aspect
        if((PDATA_WORD(0) > 115) && (PDATA_WORD(0) < 120))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}
#endif

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Watch Dog
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscSetStreamWD_8b10b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // DSC VB-ID[6] Watch Dog Setting
        ScalerSetBit(PB9_3C_DP_WD_CTRL_0, ~_BIT2, _BIT2);
    }
    else
    {
        // DSC VB-ID[6] Watch Dog Setting
        ScalerSetBit(PB9_3C_DP_WD_CTRL_0, ~_BIT2, 0x00);

        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
    }
}

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] IRQ
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscSetStreamIRQ_8b10b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // DSC VB-ID[6] IRQ Setting
        ScalerSetBit(PB9_3E_DP_IRQ_CTRL0, ~_BIT2, _BIT2);
    }
    else
    {
        // DSC VB-ID[6] IRQ Setting
        ScalerSetBit(PB9_3E_DP_IRQ_CTRL0, ~_BIT2, 0x00);

        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
    }
}

//--------------------------------------------------
// Description  : DP DSC Chunk Length Check
// Input Value  : enumInputPort, PPS Chunk Length, PPS Slice Count
// Output Value : FALSE => Measure Check Fail
//--------------------------------------------------
bit ScalerDpMacStreamRx1DscChunkLengthCheck_8b10b(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt)
{
    WORD usDscChunkLengthCalculate = 0;
    WORD usDscChunkLengthMeasure = 0;
    BYTE ucDpMacLaneCnt = 0;

    // Set DP Measure DSC Chunk Length Type: DP MAC measure Main Link DSC Chunk Length Cycle
    ScalerSetBit(PB8_65_VIDEO_EN_CNT_2, ~(_BIT7 | _BIT6), _BIT6);

    // Start to Measure DSC Chunk Length Counter by GDI Clock
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), 0x00);
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_65_VIDEO_EN_CNT_2, _BIT5, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Get Measure DSC Chunk Length Counts
    usDscChunkLengthMeasure = ScalerGetWord(PB8_63_VIDEO_EN_CNT_0);

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_MULTI_FUNCTION_SUPPORT == _ON))
    EnumDpMstPort enumDpMstPort = ScalerDpMstRxDxPortNumMapping(enumInputPort);

    if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumDpMstPort) == _ENABLE) &&
       (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x00, 0x60, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x01, 0x60, _BIT0) == _BIT0))
    {
        ucDpMacLaneCnt = 4;
    }
    else
#endif
    {
        ucDpMacLaneCnt = ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

    if(ucDpMacLaneCnt == 0)
    {
        return _FALSE;
    }

    // Calculate DSC Chunk Length divide by DP MAC Lane Count
    usDscChunkLengthCalculate = usDscPpsChunkLength / ucDpMacLaneCnt + (((usDscPpsChunkLength % ucDpMacLaneCnt) > 0) ? 1 : 0);

    // DP MAC measure Main Link DSC Chunk Length Cycle: (cycle of main link - slice of eoc) / slice
    usDscChunkLengthMeasure = (usDscChunkLengthMeasure - ucDscPpsSliceCnt) / ucDscPpsSliceCnt;

    // Clear Measure Video Count Mode
    ScalerSetBit(PB8_65_VIDEO_EN_CNT_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), 0x00);

    // Disable Measure Block
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Check DSC Chunk Length
    if(usDscChunkLengthCalculate != usDscChunkLengthMeasure)
    {
        // Measure second times only when usDpMacDscChunkLength = 2*usDscChunkLengthCalculate
        if(usDscChunkLengthCalculate == (usDscChunkLengthMeasure >> 1))
        {
            // Set DP Measure DSC Chunk Length Type: DP MAC measure Main Link DSC Chunk Length Cycle
            ScalerSetBit(PB8_65_VIDEO_EN_CNT_2, ~(_BIT7 | _BIT6), _BIT6);

            // Start to Measure DSC Chunk Length Counter by GDI Clock
            ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), 0x00);
            ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), _BIT7);

            if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_65_VIDEO_EN_CNT_2, _BIT5, _TRUE) == _FALSE)
            {
                return _FALSE;
            }

            // Get Measure DSC Chunk Length Counts
            usDscChunkLengthMeasure = ScalerGetWord(PB8_63_VIDEO_EN_CNT_0);

            ucDpMacLaneCnt = ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            if(ucDpMacLaneCnt == 0)
            {
                return _FALSE;
            }

            // Calculate DSC Chunk Length divide by DP MAC Lane Count
            usDscChunkLengthCalculate = usDscPpsChunkLength / ucDpMacLaneCnt + (((usDscPpsChunkLength % ucDpMacLaneCnt) > 0) ? 1 : 0);

            // DP MAC measure Main Link DSC Chunk Length Cycle: (cycle of main link - slice of eoc) / slice
            usDscChunkLengthMeasure = (usDscChunkLengthMeasure - ucDscPpsSliceCnt) / ucDscPpsSliceCnt;

            // Clear Measure Video Count Mode
            ScalerSetBit(PB8_65_VIDEO_EN_CNT_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), 0x00);

            // Disable Measure Block
            ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // Check DSC Chunk Length
            if(usDscChunkLengthCalculate != usDscChunkLengthMeasure)
            {
                DebugMessageDSC("DSC Chunk Size Mismatch 0", usDscChunkLengthMeasure);

                return _FALSE;
            }
        }
        else
        {
            DebugMessageDSC("DSC Chunk Size Mismatch 1", usDscChunkLengthMeasure);

            return _FALSE;
        }
    }

    return _TRUE;
}
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Change Check
// Input Value  : None
// Output Value : False --> CompressionStream_Flag VB-ID[6] Changed and Video Stream without Compression
//--------------------------------------------------
bit ScalerDpMacStreamRx1DscStreamChangeCheck_8b10b(void)
{
    // Check DSC Compression Stream Flag
    if(ScalerGetBit(PB9_3B_DP_GLB_STATUS, _BIT1) == _BIT1)
    {
        // Clear DSC Stream Change Flag
        ScalerSetBit(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        return _TRUE;
    }

    return _FALSE;
}
#endif

#if((_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Mac Tx DSC Pass-Through Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscStatusReset_8b10b(void)
{
    DebugMessageMst("MST2SST DSC PassThrough Reset !!!", 0x00);

    // Clear DSC Stream Change Flag
    ScalerSetBit(PB9_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

    // Clear DSC PPS Change Flag
    ScalerSetBit(P26_BF_DP_PPS_RO_CTRL, ~_BIT6, _BIT6);
}
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DP Color Sapace Change WD
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetColorSpaceChangeWD_8b10b(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Clear flag
        ScalerSetByte(P26_96_DP_MSA_COLOR_CTRL1, _BIT7);

        // Enable Color Sapace Change WD
        ScalerSetBit(P26_96_DP_MSA_COLOR_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
    }
    else
    {
        // Disable Color Sapace Change WD
        ScalerSetBit(P26_96_DP_MSA_COLOR_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Clear flag
        ScalerSetByte(P26_96_DP_MSA_COLOR_CTRL1, _BIT7);
    }
}

//--------------------------------------------------
// Description  : Enable DP MSA Change IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SstSetMsaChangeIRQ_8b10b(bit bEn)
{
    CLR_DP_MAC_STREAM_RX1_MISC_CHECK_FAIL();

    if(bEn == _ENABLE)
    {
        // Disable MSA Debounce
        ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Clear flag
        ScalerSetByte(PB9_3B_DP_GLB_STATUS, _BIT4);

        // Enable MSA Change IRQ
        ScalerSetBit(PB9_3F_DP_IRQ_CTRL1, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable MSA Change IRQ
        ScalerSetBit(PB9_3F_DP_IRQ_CTRL1, ~_BIT7, 0x00);

        // Clear flag
        ScalerSetByte(PB9_3B_DP_GLB_STATUS, _BIT4);

        // Enable MSA Debounce
        ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
    }
}
#endif

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Mac Rx1 Stream Pre Scan Port 128b132b
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerDpMacStreamRx1StreamPreDetect_128b132b(EnumInputPort enumInputPort)
{
    EnumDpStreamInfoType enumDpStreamInfoType = _INFO_TYPE_NONE;
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(_DP_MAC_1);

    enumDpMacStreamSourceType = enumDpMacStreamSourceType;

    SET_DP_MAC_STREAM_RX1_STREAM_INFO_TYPE(_INFO_TYPE_NONE);

    memset(&g_stDpMacStreamRx1Info, 0, sizeof(StructDpInfo));

    if(ScalerDpAuxRxGetLTStatus(enumInputPort) != _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return _FALSE;
    }

    if(ScalerDpMacDphyRxHdcpCheck(enumInputPort) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: HDCP Check Fail", 0);

        ScalerDpMacDphyRxCpIRQ(enumInputPort, _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

        ScalerDpHdcpRxSetHdcpCpirqFlag(enumInputPort);

#if(_DP_LONG_HPD_AFTER_CPIRQ_SUPPORT == _ON)
        if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _DISABLE)
        {
            ScalerDpAuxRxReactiveHdcpLongHotplug(enumInputPort);
        }
#endif

        return _FALSE;
    }

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    ScalerDpMacStreamRxPxpStreamMuxCheck(enumInputPort);
#endif

    if(ScalerDpMacStreamRx1GetVideoStream() == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Video Stream Fail", 0);

        return _FALSE;
    }

#if((_DP_RX_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
    if(ScalerDpMacDscRxDscStreamCheck(_DP_MAC_1) == _TRUE)
    {
        if(ScalerDpMacStreamRxDscGetFlagStatus(enumDpMacStreamSourceType) == _TRUE)
        {
            enumDpStreamInfoType = _INFO_TYPE_DSC;
        }
        else
        {
            DebugMessageDpRx("7. DP MAC RX1: Get Abnormal Compression Flag", 0);

            return _FALSE;
        }
    }
    else
#endif
    {
        enumDpStreamInfoType = _INFO_TYPE_VIDEO;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(ScalerDpMacStreamRxFreeSyncGetStreamConfig(enumDpMacStreamSourceType) == _TRUE)
    {
        SET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE();
    }
    else
    {
        CLR_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE();
    }
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
    if(ScalerDpMacStreamRxPRModeFlagStatus(enumDpMacStreamSourceType) == _TRUE)
    {
        // Enable Pr State Change Irq
        ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_128b132b(_ENABLE);

        SET_DP_MAC_STREAM_RX1_PR_ENABLE_128B132B();
    }
    else
    {
        // Disable Pr State Change Irq
        ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_128b132b(_DISABLE);

        CLR_DP_MAC_STREAM_RX1_PR_ENABLE_128B132B();
    }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x16, (_BIT2 | _BIT0)) == (_BIT2 | _BIT0))
    {
        ScalerDpMacDphyRxAuxlessAlpmEnable(enumInputPort, _ENABLE);

        SET_DP_MAC_STREAM_RX1_ALPM_ENABLE_128B132B();
    }
    else
    {
        ScalerDpMacDphyRxAuxlessAlpmEnable(enumInputPort, _DISABLE);

        CLR_DP_MAC_STREAM_RX1_ALPM_ENABLE_128B132B();
    }
#endif

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)

    // Disable DP Mac Rx1 Support DSC
    CLR_DP_MAC_STREAM_RX1_DSC_SUPPORT_128B132B();

#endif

    if(ScalerDpMacStreamRx1GetMsaTimingInfo_128b132b(&g_stDpMacStreamRx1Info) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Get MSA Info Fail", 0);

        return _FALSE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    if(ScalerDpMacStreamRx1GetVideoInfo_128b132b() == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Get Video Info Fail", 0);

        return _FALSE;
    }
    else
    {
        ScalerDpMacStreamRx1SetColorInfo();
    }

    if(ScalerDpMacStreamRx1GetMeasureLinkInfo_128b132b(&g_stDpMacStreamRx1Info) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Get Measure Info Fail", 0);

        return _FALSE;
    }

    if(ScalerDpMacStreamRx1StreamInfoSetting(&g_stDpMacStreamRx1Info) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Stream Info Setting Fail", 0);

        return _FALSE;
    }

    // Secondary Data Sram Reset Prevent Sdp Change Flag and Sram Data Mismacth
    ScalerDpMacStreamRx1SdpSramReset_128b132b();

    SET_DP_MAC_STREAM_RX1_STREAM_INFO_TYPE_CHANGE();

    SET_DP_MAC_STREAM_RX1_STREAM_INFO_TYPE(enumDpStreamInfoType);

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Get Video Info 128b132b
// Input Value  : None
// Output Value : TRUE --> Get successfully
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetVideoInfo_128b132b(void)
{
    BYTE pucColorInfoByte[3] = {0};

    CLR_DP_MAC_STREAM_RX1_VSC_SDP_COLOR_MODE();

    // Check MISC1[6]
    if((ScalerGetBit(P75_03_MN_STRM_ATTR_MISC1, _BIT6)) == _BIT6)
    {
        // Use VSC SDP
        SET_DP_MAC_STREAM_RX1_VSC_SDP_COLOR_MODE();

        // Get VSC SDP Data Packet, Read DB16~18 --> pucColorInfoByte[0:2]
        ScalerDpMacStreamRx1GetSdpPktData(_DP_SDP_TYPE_VSC, pucColorInfoByte, 16, 3);

        // Set Color Info PreValue
        SET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_PREVALUE(pucColorInfoByte[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        SET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE((pucColorInfoByte[1] & _BIT7) >> 7);
        SET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE(pucColorInfoByte[1] & (_BIT2 | _BIT1 | _BIT0));
        SET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE(pucColorInfoByte[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4));
        SET_DP_MAC_STREAM_RX1_CONTENT_TYPE(pucColorInfoByte[2] & (_BIT2 | _BIT1 | _BIT0));

        DebugMessageDpRx("DP MAC RX1: VSC DB16", pucColorInfoByte[0]);
        DebugMessageDpRx("DP MAC RX1: VSC DB17", pucColorInfoByte[1]);
    }
    else
    {
        // Get MISC Info
        pucColorInfoByte[0] = ScalerGetByte(P75_02_MN_STRM_ATTR_MISC);
        pucColorInfoByte[1] = ScalerGetByte(P75_03_MN_STRM_ATTR_MISC1);

        // Set Color Info PreValue
        SET_DP_MAC_STREAM_RX1_COLORIMETRY_PREVALUE((pucColorInfoByte[0] & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
        SET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE((pucColorInfoByte[0] & _BIT3) >> 3);
        SET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE((pucColorInfoByte[0] & (_BIT7 | _BIT6 | _BIT5)) >> 5);
        SET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE((pucColorInfoByte[1] & _BIT7) | (pucColorInfoByte[0] & (_BIT2 | _BIT1)));
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get VBID Information 128b132b
// Input Value  : VBID Content
// Output Value : VBID Information
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetVbidInfo_128b132b(EnumDpVbidInfo enumDpVbidInfo)
{
    switch(enumDpVbidInfo)
    {
        case _DP_VBID_INTERLACE_MODE:

            return (ScalerGetBit(P75_01_DP_VBID, _BIT2) == _BIT2);

        case _DP_VBID_VIDEO_STREAM:

            return (ScalerGetBit(P75_01_DP_VBID, _BIT3) == 0x00);

        case _DP_VBID_DSC_STREAM:

            return (ScalerGetBit(P75_01_DP_VBID, _BIT5) == _BIT5);

        case _DP_VBID_AUDIO_STREAM:

            return (ScalerGetBit(P75_01_DP_VBID, _BIT4) == 0x00);

        default:

            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get MSA Information
// Input Value  : EnumDpRxMsaType
// Output Value : UnionDpRxMsaValue
//--------------------------------------------------
UnionDpRxMsaValue ScalerDpMacStreamRx1GetMsaInfo_128b132b(EnumDpRxMsaType enumDpRxMsaType)
{
    UnionDpRxMsaValue unDpRxMsaValue;

    switch(enumDpRxMsaType)
    {
        case _DP_RX_MSA_HTOTAL:
            unDpRxMsaValue.usDpRxMsaHtotal = (TO_WORD(ScalerGetByte(P75_10_MSA_HTT_0), ScalerGetByte(P75_11_MSA_HTT_1)));
            break;

        case _DP_RX_MSA_HSTART:
            unDpRxMsaValue.usDpRxMsaHstart = (TO_WORD(ScalerGetByte(P75_12_MSA_HST_0), ScalerGetByte(P75_13_MSA_HST_1)));
            break;

        case _DP_RX_MSA_HWIDTH:
            unDpRxMsaValue.usDpRxMsaHwidth = (TO_WORD(ScalerGetByte(P75_14_MSA_HWD_0), ScalerGetByte(P75_15_MSA_HWD_1)));
            break;

        case _DP_RX_MSA_HSP:
            unDpRxMsaValue.bDpRxMsaHsp = (bit)(ScalerGetBit(P75_16_MSA_HSW_0, _BIT7));
            break;

        case _DP_RX_MSA_HSW:
            unDpRxMsaValue.usDpRxMsaHsw = (TO_WORD((ScalerGetByte(P75_16_MSA_HSW_0) & (0x7F)), ScalerGetByte(P75_17_MSA_HSW_1)));
            break;

        case _DP_RX_MSA_VTOTAL:
            unDpRxMsaValue.usDpRxMsaVtotal = (TO_WORD(ScalerGetByte(P75_18_MSA_VTT_0), ScalerGetByte(P75_19_MSA_VTT_1)));
            break;

        case _DP_RX_MSA_VSTART:
            unDpRxMsaValue.usDpRxMsaVstart = (TO_WORD(ScalerGetByte(P75_1A_MSA_VST_0), ScalerGetByte(P75_1B_MSA_VST_1)));
            break;

        case _DP_RX_MSA_VHEIGHT:
            unDpRxMsaValue.usDpRxMsaVheight = (TO_WORD(ScalerGetByte(P75_1C_MSA_VHT_0), ScalerGetByte(P75_1D_MSA_VHT_1)));
            break;

        case _DP_RX_MSA_VSP:
            unDpRxMsaValue.bDpRxMsaVsp = (bit)(ScalerGetBit(P75_1E_MSA_VSW_0, _BIT7));
            break;

        case _DP_RX_MSA_VSW:
            unDpRxMsaValue.usDpRxMsaVsw = (TO_WORD((ScalerGetByte(P75_1E_MSA_VSW_0) & (0x7F)), ScalerGetByte(P75_1F_MSA_VSW_1)));
            break;

        case _DP_RX_MSA_VFREQ:
            unDpRxMsaValue.uqDpRxMsaVfreq = TO_QWORD(TO_DWORD(0x00, 0x00, ScalerGetByte(P75_04_MSA_VFREQ_0), ScalerGetByte(P75_05_MSA_VFREQ_1)),
                                                     TO_DWORD(ScalerGetByte(P75_06_MSA_VFREQ_2), ScalerGetByte(P75_07_MSA_VFREQ_3),
                                                              ScalerGetByte(P75_08_MSA_VFREQ_4), ScalerGetByte(P75_09_MSA_VFREQ_5)));
            break;

        case _DP_RX_MSA_AFREQ:
            unDpRxMsaValue.uqDpRxMsaAfreq = TO_QWORD(TO_DWORD(0x00, 0x00, ScalerGetByte(P75_0A_MSA_AFREQ_0), ScalerGetByte(P75_0B_MSA_AFREQ_1)),
                                                     TO_DWORD(ScalerGetByte(P75_0C_MSA_AFREQ_2), ScalerGetByte(P75_0D_MSA_AFREQ_3),
                                                              ScalerGetByte(P75_0E_MSA_AFREQ_4), ScalerGetByte(P75_0F_MSA_AFREQ_5)));
            break;

        default:
            unDpRxMsaValue.uqDpRxMsaError = 0xFFFF;
            break;
    }

    return unDpRxMsaValue;
}

//--------------------------------------------------
// Description  : Get Dp MSA Timing Info 128b132b
// Input Value  : DP Info Structure
// Output Value : True --> Get MSA Info
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetMsaTimingInfo_128b132b(StructDpInfo *pstDpInfo)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(P75_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get HWidth
    pstDpInfo->stDpTimingInfo.usHWidth = TO_WORD(ScalerGetByte(P75_14_MSA_HWD_0), ScalerGetByte(P75_15_MSA_HWD_1));

    // Get VHeight
    pstDpInfo->stDpTimingInfo.usVHeight = TO_WORD(ScalerGetByte(P75_1C_MSA_VHT_0), ScalerGetByte(P75_1D_MSA_VHT_1));

    // Get HTotal
    pstDpInfo->stDpTimingInfo.usHTotal = TO_WORD(ScalerGetByte(P75_10_MSA_HTT_0), ScalerGetByte(P75_11_MSA_HTT_1));

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
    // BackUp HTotal For Hblanking Modify Mode
    pstDpInfo->stDpHblankingModifyInfo.usMsaHTotal = pstDpInfo->stDpTimingInfo.usHTotal;
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
    {
        // Check if MSA is Valid
        if((pstDpInfo->stDpTimingInfo.usHWidth == 0x00) || (pstDpInfo->stDpTimingInfo.usVHeight == 0x00))
        {
            return _FALSE;
        }

        // Get HStart
        pstDpInfo->stDpTimingInfo.usHStart = _DE_ONLY_MODE_HSTART;

        // Get HSW
        pstDpInfo->stDpTimingInfo.usHSWidth = _DE_ONLY_MODE_HSW;

        // Get HS Polarity
        pstDpInfo->stDpTimingInfo.b1HSP = _SYNC_POLARITY_POSITIVE;

        // Get VStart
        pstDpInfo->stDpTimingInfo.usVStart = _DE_ONLY_MODE_VSTART;

        // Get VSW
        pstDpInfo->stDpTimingInfo.usVSWidth = _DE_ONLY_MODE_VSW;

        // Get VS Polarity
        pstDpInfo->stDpTimingInfo.b1VSP = _SYNC_POLARITY_POSITIVE;
    }
    else
#endif
    {
        // Get HStart
        pstDpInfo->stDpTimingInfo.usHStart = TO_WORD(ScalerGetByte(P75_12_MSA_HST_0), ScalerGetByte(P75_13_MSA_HST_1));

        // Get HSW
        pstDpInfo->stDpTimingInfo.usHSWidth = TO_WORD(ScalerGetBit(P75_16_MSA_HSW_0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)), ScalerGetByte(P75_17_MSA_HSW_1));

        // Get HS Polarity
        pstDpInfo->stDpTimingInfo.b1HSP = (bit) ScalerGetBit(P75_16_MSA_HSW_0, _BIT7);

        // Get VTotal
        pstDpInfo->stDpTimingInfo.usVTotal = TO_WORD(ScalerGetByte(P75_18_MSA_VTT_0), ScalerGetByte(P75_19_MSA_VTT_1));

        // Get VStart
        pstDpInfo->stDpTimingInfo.usVStart = TO_WORD(ScalerGetByte(P75_1A_MSA_VST_0), ScalerGetByte(P75_1B_MSA_VST_1));

        // Get VSW
        pstDpInfo->stDpTimingInfo.usVSWidth = TO_WORD(ScalerGetBit(P75_1E_MSA_VSW_0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)), ScalerGetByte(P75_1F_MSA_VSW_1));

        // Get VS Polarity
        pstDpInfo->stDpTimingInfo.b1VSP = (bit) ScalerGetBit(P75_1E_MSA_VSW_0, _BIT7);

        // Check if MSA is Valid
        if((pstDpInfo->stDpTimingInfo.usHTotal == 0x00) || (pstDpInfo->stDpTimingInfo.usHStart == 0x00) ||
           (pstDpInfo->stDpTimingInfo.usHWidth == 0x00) || (pstDpInfo->stDpTimingInfo.usHSWidth == 0x00) ||
           (pstDpInfo->stDpTimingInfo.usVTotal == 0x00) || (pstDpInfo->stDpTimingInfo.usVStart == 0x00) ||
           (pstDpInfo->stDpTimingInfo.usVHeight == 0x00) || (pstDpInfo->stDpTimingInfo.usVSWidth == 0x00))
        {
            return _FALSE;
        }
    }

    // Set V Front Porch
    SET_DP_MAC_STREAM_RX1_VFRONT_PORCH(_DP_VSYNC_FRONT_PORCH);

    // Get Vfreq
    pstDpInfo->stDpLinkInfo.ulMsaVfreqClk128b132b = TO_DWORD(ScalerGetByte(P75_06_MSA_VFREQ_2), ScalerGetByte(P75_07_MSA_VFREQ_3), ScalerGetByte(P75_08_MSA_VFREQ_4), ScalerGetByte(P75_09_MSA_VFREQ_5));

    // Check if Vfreq is Valid
    if(pstDpInfo->stDpLinkInfo.ulMsaVfreqClk128b132b == 0x00)
    {
        return _FALSE;
    }

    DebugMessageDpRx("DP MAC RX1: MSA HTotal", pstDpInfo->stDpTimingInfo.usHTotal);
    DebugMessageDpRx("DP MAC RX1: MSA HStart", pstDpInfo->stDpTimingInfo.usHStart);
    DebugMessageDpRx("DP MAC RX1: MSA HWidth", pstDpInfo->stDpTimingInfo.usHWidth);
    DebugMessageDpRx("DP MAC RX1: MSA HSW", pstDpInfo->stDpTimingInfo.usHSWidth);
    DebugMessageDpRx("DP MAC RX1: MSA HSP", pstDpInfo->stDpTimingInfo.b1HSP);
    DebugMessageDpRx("DP MAC RX1: MSA VTotal", pstDpInfo->stDpTimingInfo.usVTotal);
    DebugMessageDpRx("DP MAC RX1: MSA VStart", pstDpInfo->stDpTimingInfo.usVStart);
    DebugMessageDpRx("DP MAC RX1: MSA VHeight", pstDpInfo->stDpTimingInfo.usVHeight);
    DebugMessageDpRx("DP MAC RX1: MSA VSW", pstDpInfo->stDpTimingInfo.usVSWidth);
    DebugMessageDpRx("DP MAC RX1: MSA VSP", pstDpInfo->stDpTimingInfo.b1VSP);
    DebugMessageDpRx("DP MAC RX1: MSA Vfreq", pstDpInfo->stDpLinkInfo.ulMsaVfreqClk128b132b);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get DP Link Info from Measure Function 128b132b
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRx1GetMeasureLinkInfo_128b132b(StructDpInfo *pstDpInfo)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
    DWORD ulTemp = 0;

    ///////////////////////
    // Get Measured Info //
    ///////////////////////

    // Reset Interlace mode
    ScalerDpMacStreamRx1InterlaceReset_128b132b();

    // Enable Measurement
    ScalerSetBit(P70_40_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), 0x00);
    ScalerSetBit(P70_40_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, P70_40_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Pop up The Measured Result
    SET_DP_MAC_STREAM_RX1_MEASURE_POP_UP_128B132B();

    // Get BS To BS Count of Frame N
    pstDpInfo->stDpLinkInfo.ulVBsToBsCountN = TO_DWORD(0x00, ScalerGetBit(P70_41_MN_MEAS_VLN_H, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)), ScalerGetByte(P70_42_MN_MEAS_VLN_M), ScalerGetByte(P70_43_MN_MEAS_VLN_L));

    // Delaying 1 frame time be used to wait time passed for upstream dptx generated different picture size of the firt frame and second frame
    ScalerTimerDelayXms((pstDpInfo->stDpLinkInfo.ulVBsToBsCountN / _GDIPHY_RX_GDI_CLK_KHZ) + 2);

    // Pop up The Measured Result
    SET_DP_MAC_STREAM_RX1_MEASURE_POP_UP_128B132B();

    // Get BS To BS Count of Frame N
    pstDpInfo->stDpLinkInfo.ulVBsToBsCountN = TO_DWORD(0x00, ScalerGetBit(P70_41_MN_MEAS_VLN_H, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)), ScalerGetByte(P70_42_MN_MEAS_VLN_M), ScalerGetByte(P70_43_MN_MEAS_VLN_L));

    // Delay 2ms To Get VBID
    ScalerTimerDelayXms(2);

    // Get Interlace Field Flag VBID[1] of Frame N
    pstDpInfo->stDpLinkInfo.b1InterlaceFieldN = (bit)ScalerGetBit(P75_01_DP_VBID, _BIT1);

    // Delay 1 Frame Time, unit is ms
    ScalerTimerDelayXms((pstDpInfo->stDpLinkInfo.ulVBsToBsCountN / _GDIPHY_RX_GDI_CLK_KHZ) + 2);

    // Pop up The Measured Result
    SET_DP_MAC_STREAM_RX1_MEASURE_POP_UP_128B132B();

    // Get BS To BS Count of Frame N+1
    pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1 = TO_DWORD(0x00, ScalerGetBit(P70_41_MN_MEAS_VLN_H, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)), ScalerGetByte(P70_42_MN_MEAS_VLN_M), ScalerGetByte(P70_43_MN_MEAS_VLN_L));

    // Get Interlace Field Flag VBID[1] of Frame N+1
    pstDpInfo->stDpLinkInfo.b1InterlaceFieldN1 = (bit)ScalerGetBit(P75_01_DP_VBID, _BIT1);

    // Get Interlace HW Detect Result
    pstDpInfo->stDpLinkInfo.b1HwInterlaceDetect = (bit)ScalerGetBit(P70_07_INTERLACE_CTRL_1, _BIT7);
    pstDpInfo->stDpLinkInfo.b1HwFakeInterlaceDetect = (bit)ScalerGetBit(P70_07_INTERLACE_CTRL_1, _BIT6);

    // Disable Measurement
    ScalerSetBit(P70_40_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), 0x00);

    // Get HBs2Bs Count By Link Clk / 3.2
    pstDpInfo->stDpLinkInfo.usHBsToBsCount = (((WORD)ScalerGetByte(P70_44_MN_MEAS_HLN_M)) << 8) | ((WORD)ScalerGetByte(P70_45_MN_MEAS_HLN_L));

    /////////////////////
    // Check the value //
    /////////////////////
    if(ScalerDpMacStreamRxMeasureInfoCheck(pstDpInfo) == _FALSE)
    {
        return _FALSE;
    }

    ////////////////////
    // Get Link Clock //
    ////////////////////

    ulTemp = ScalerDpMacDphyRxSignalDetectMeasureCount(enumInputPort, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0), _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_2000_CYCLE);

    if(ulTemp == 0)
    {
        switch(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort))
        {
            case _DP_LINK_UHBR20:

                ulTemp = _DP_RX_VCO_TARGET_COUNT_2000_UHBR20_SAVED;

                break;

            case _DP_LINK_UHBR13_5:

                ulTemp = _DP_RX_VCO_TARGET_COUNT_2000_UHBR13_5_SAVED;

                break;

            case _DP_LINK_UHBR10:
            default:

                ulTemp = _DP_RX_VCO_TARGET_COUNT_2000_UHBR10_SAVED;

                break;
        }
    }

    // Get Link Clock, Unit is Hz
    // Measure Period = 2000 GDI_Clock Cycle, Count by 1/2 Link Clock
    pstDpInfo->stDpLinkInfo.ulLinkClockHz = (ulTemp * _GDIPHY_RX_GDI_CLK_KHZ);

    // Check if Measure Data is Valid
    if((pstDpInfo->stDpLinkInfo.ulVBsToBsCountN == 0x00) || (pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1 == 0x00) ||
       (pstDpInfo->stDpLinkInfo.usHBsToBsCount == 0x00) || (pstDpInfo->stDpLinkInfo.ulLinkClockHz == 0x00))
    {
        DebugMessageDpRx("DP MAC RX1: Measure data is invalid", 0);

        return _FALSE;
    }


    //////////////////////
    // Get Stream Clock //
    //////////////////////

    // Calculate Stream Clock (Unit is Hz)
    pstDpInfo->stDpLinkInfo.ulStreamClockHz = pstDpInfo->stDpLinkInfo.ulMsaVfreqClk128b132b;

#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
    WORD usIVfreq_OOR = ScalerGlobalComputeDwordMulDiv(pstDpInfo->stDpLinkInfo.ulStreamClockHz, 10, ((DWORD)pstDpInfo->stDpTimingInfo.usHTotal * pstDpInfo->stDpTimingInfo.usVTotal));

    DebugMessageDpRx("DP MAC RX1: IVfreq", usIVfreq_OOR);

    if(usIVfreq_OOR <= 200)
    {
        SET_DP_MAC_STREAM_RX1_JUDGE_OOR();

        DebugMessageDpRx("DP MAC RX1: Judge for OOR Case", 0);
    }
    else
    {
        CLR_DP_MAC_STREAM_RX1_JUDGE_OOR();
    }
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
    {
#if(_DRR_FREE_RUN_DISPLAY_SUPPORT == _OFF)
        {
#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
            if(GET_DP_MAC_STREAM_RX1_JUDGE_OOR() == _FALSE)
#endif
            {
                // Get IVfreq
                WORD usIVfreq = ((DWORD)_GDIPHY_RX_GDI_CLK_KHZ * 1000 / (pstDpInfo->stDpLinkInfo.ulVBsToBsCountN / 10));

                if((usIVfreq < (_PANEL_DP_FREESYNC_MIN_FRAME_RATE - _PANEL_FRAME_SYNC_MARGIN)) ||
                   (usIVfreq > (_PANEL_DP_FREESYNC_MAX_FRAME_RATE + _PANEL_FRAME_SYNC_MARGIN)))
                {
                    return _FALSE;
                }
            }
        }
#endif

        if(pstDpInfo->stDpLinkInfo.usHBsToBsCount == 0x00)
        {
            return _FALSE;
        }

        // VTotal in line, VBsToBs Count By GDI clk
        pstDpInfo->stDpTimingInfo.usVTotal = ScalerGlobalComputeDwordMulDiv(pstDpInfo->stDpLinkInfo.ulVBsToBsCountN, (pstDpInfo->stDpLinkInfo.ulLinkClockHz / 100 / 32), (DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount) / _GDIPHY_RX_GDI_CLK_KHZ;

        ulTemp = pstDpInfo->stDpLinkInfo.ulLinkClockHz / 100 / 32;

        if(ulTemp == 0x00)
        {
            return _FALSE;
        }

        // HTotal in Pixel Clk, HBsToBs Count By Link clk / 3.2
        pstDpInfo->stDpTimingInfo.usHTotal = ScalerGlobalComputeDwordMulDiv((DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount, (pstDpInfo->stDpLinkInfo.ulStreamClockHz / 1000), ulTemp);
    }
#endif

    DebugMessageDpRx("DP MAC RX1: MAC111111 From Dx", enumInputPort);
    DebugMessageDpRx("DP MAC RX1: VBs2Bs N", pstDpInfo->stDpLinkInfo.ulVBsToBsCountN);
    DebugMessageDpRx("DP MAC RX1: VBs2Bs N+1", pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1);
    DebugMessageDpRx("DP MAC RX1: HBs2Bs", pstDpInfo->stDpLinkInfo.usHBsToBsCount);
    DebugMessageDpRx("DP MAC RX1: Link Clock", pstDpInfo->stDpLinkInfo.ulLinkClockHz);
    DebugMessageDpRx("DP MAC RX1: Stream Clock", pstDpInfo->stDpLinkInfo.ulStreamClockHz);

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Stream Vesa Video Setting
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
EnumDpMacRxStreamVideoType ScalerDpMacStreamRx1StreamVesaVideoSetting_128b132b(void)
{
    if(ScalerDpMacStreamRx1DisplayFormatSetting_128b132b(&g_stDpMacStreamRx1Info) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Display Format Fail", 0);

        return _DP_STREAM_FAIL;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _DP_STREAM_NONE;
    }
#endif

    if(ScalerDpMacStreamRx1StreamClkRegenerate(&g_stDpMacStreamRx1Info) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Stream Clk Fail", 0);

        return _DP_STREAM_FAIL;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _DP_STREAM_NONE;
    }
#endif

    if(ScalerDpMacStreamRx1TrackingSetting(&g_stDpMacStreamRx1Info) == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Tracking Fail", 0);

        return _DP_STREAM_FAIL;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _DP_STREAM_NONE;
    }
#endif

    if(ScalerDpMacStreamRx1FifoCheckProc_128b132b(_DP_FIFO_DELAY_CHECK, &g_stDpMacStreamRx1Info) == _FAIL)
    {
#if(_URGENT_EVENT_CHECK_MODE == _ON)
        if(ScalerSyncCheckUrgentEvent() == _TRUE)
        {
            return _DP_STREAM_NONE;
        }
#endif

        DebugMessageDpRx("7. DP MAC RX1: Fifo Fail", 0);

        return _DP_STREAM_FAIL;
    }

    // Calculating Stream clock from final n.f code of PLL
    ScalerDpMacStreamRx1StreamClockSetting(&g_stDpMacStreamRx1Info);

    // Use for Video/DisplayFormat/Measure relative Settings.
    ScalerDpMacStreamRx1MacSetting();

    return _DP_STREAM_PASS;
}

//--------------------------------------------------
// Description  : DP Display Format Generator Setting 128b132b
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRx1DisplayFormatSetting_128b132b(StructDpInfo *pstDpInfo)
{
    bit bDeOnlyModeJudge = _FALSE;

    ////////////////////////////////////
    // Display Format Generator Reset //
    ////////////////////////////////////

    // Disable Generate Display Format
    ScalerSetBit(P70_00_DPF_CTRL_0, ~_BIT7, 0x00);

    // Display Format Generator Reset
    ScalerSetBit(P70_05_DP20MAC_RESET, ~_BIT4, _BIT4);
    ScalerSetBit(P70_05_DP20MAC_RESET, ~_BIT4, 0x00);


    //////////////////////////
    // Interlace Mode Check //
    //////////////////////////

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _FALSE)
#endif
    {
        if(ScalerDpMacStreamRx1InterlaceCheck_128b132b(pstDpInfo) == _TRUE)
        {
            pstDpInfo->stDpLinkInfo.b1InterlaceStatus = _TRUE;

            DebugMessageDpRx("7. DP MAC RX1: Interlace Mode - VTotal", pstDpInfo->stDpTimingInfo.usVTotal);
        }
        else
        {
            pstDpInfo->stDpLinkInfo.b1InterlaceStatus = _FALSE;

            DebugMessageDpRx("7. DP MAC RX1: Progressive Mode", 0);

            // Judge DE_Only Mode Use or not
            if(ScalerDpMacStreamRxDeOnlyJudge_128b132b(pstDpInfo) == _TRUE)
            {
                bDeOnlyModeJudge = _TRUE;
            }
        }
    }


    ////////////////////////
    // Adjust Timing Info //
    ////////////////////////

    ScalerDpMacStreamRx1TimingInfoAdjust(pstDpInfo);


    ///////////////////////////////////
    // Display Format Timing Setting //
    ///////////////////////////////////

    // Set HTotal
    ScalerSetByte(P70_10_MN_DPF_HTT_M, HIBYTE(pstDpInfo->stDpTimingInfo.usHTotal));
    ScalerSetByte(P70_11_MN_DPF_HTT_L, LOBYTE(pstDpInfo->stDpTimingInfo.usHTotal));

    // Set HStart
    ScalerSetByte(P70_12_MN_DPF_HST_M, HIBYTE(pstDpInfo->stDpTimingInfo.usHStart));
    ScalerSetByte(P70_13_MN_DPF_HST_L, LOBYTE(pstDpInfo->stDpTimingInfo.usHStart));

    // Set HWidth
    ScalerSetByte(P70_14_MN_DPF_HWD_M, HIBYTE(pstDpInfo->stDpTimingInfo.usHWidth));
    ScalerSetByte(P70_15_MN_DPF_HWD_L, LOBYTE(pstDpInfo->stDpTimingInfo.usHWidth));

    // Set HSW
    ScalerSetByte(P70_16_MN_DPF_HSW_M, HIBYTE(pstDpInfo->stDpTimingInfo.usHSWidth));
    ScalerSetByte(P70_17_MN_DPF_HSW_L, LOBYTE(pstDpInfo->stDpTimingInfo.usHSWidth));

    // Set HSP = Positive
    ScalerSetBit(P70_16_MN_DPF_HSW_M, ~_BIT7, ((BYTE)_SYNC_POLARITY_POSITIVE) << 7);

    // Set Vtotal
    ScalerSetByte(P70_18_MN_DPF_VTT_M, HIBYTE(pstDpInfo->stDpTimingInfo.usVTotal));
    ScalerSetByte(P70_19_MN_DPF_VTT_L, LOBYTE(pstDpInfo->stDpTimingInfo.usVTotal));

    // Set VStart
    ScalerSetByte(P70_1A_MN_DPF_VST_M, HIBYTE(pstDpInfo->stDpTimingInfo.usVStart));
    ScalerSetByte(P70_1B_MN_DPF_VST_L, LOBYTE(pstDpInfo->stDpTimingInfo.usVStart));

    // Set VHeight
    ScalerSetByte(P70_1C_MN_DPF_VHT_M, HIBYTE(pstDpInfo->stDpTimingInfo.usVHeight));
    ScalerSetByte(P70_1D_MN_DPF_VHT_L, LOBYTE(pstDpInfo->stDpTimingInfo.usVHeight));

    // Set VSW
    ScalerSetByte(P70_1E_MN_DPF_VSW_M, HIBYTE(pstDpInfo->stDpTimingInfo.usVSWidth));
    ScalerSetByte(P70_1F_MN_DPF_VSW_L, LOBYTE(pstDpInfo->stDpTimingInfo.usVSWidth));

    // Set VSP = Positive
    ScalerSetBit(P70_1E_MN_DPF_VSW_M, ~_BIT7, ((BYTE)_SYNC_POLARITY_POSITIVE) << 7);

    // Set Color Format
    ScalerDpMacStreamRx1VideoSetting_128b132b();


    //////////////////////////////////////
    // Display Format Generator Setting //
    //////////////////////////////////////

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_ALPM_ENABLE() == _TRUE)
    {
#if(_DP_PR_MODE_SUPPORT == _ON)
        if(GET_DP_MAC_STREAM_RX1_PR_ENABLE_128B132B() == _TRUE)
        {
            // Set Vstart as Alpm T1 Count
            ScalerSetByte(P70_3D_ALPM_T1_L, TO_WORD(ScalerGetByte(P75_1A_MSA_VST_0), ScalerGetByte(P75_1B_MSA_VST_1)));

            // Set 1 line as Alpm T2 Set Up Time
            ScalerSetBit(P70_57_DP_ALPM0, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);
        }
#endif
        ////////////////////////
        // BE Frame Sync Mode //
        ////////////////////////

        // Set BE to VS Delay
        ScalerDpMacStreamRx1SetBxToVsDelay_128b132b(pstDpInfo);

        // Set 1 when using framesync be mode otherwise set to 0
        ScalerSetBit(P70_29_RANDOM_PG, ~_BIT4, _BIT4);

        // Set DRR mode enable and DRR mode sel vs doesn't overlap first hs and vstart zero mode
        ScalerSetBit(P70_04_DPF_CTRL_4, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

        // Set display format Be framesync Mode
        ScalerDpMacStreamRx1SetDPFRegenMode(_DPF_MODE_FRAME_SYNC_BE);

        // Use vbid[0] rising edge to do vblktovs for Be framesync Mode
        ScalerSetBit(P70_01_DPF_CTRL_1, ~(_BIT5 | _BIT3), 0x00);
    }
    else
#endif
    {
#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
        {
#if(_FW_DP_RX_FREESYNC_DPF_MODE_FRAME_SYNC_BE_DRR == _ON)
            ////////////////////////
            // BE Frame Sync Mode //
            ////////////////////////

            // Set BE to VS Delay
            ScalerDpMacStreamRx1SetBxToVsDelay_128b132b(pstDpInfo);

            // Set 1 when using framesync be mode otherwise set to 0
            ScalerSetBit(P70_29_RANDOM_PG, ~_BIT4, _BIT4);

            // Set DRR mode enable and DRR mode sel vs doesn't overlap first hs and vstart zero mode
            ScalerSetBit(P70_04_DPF_CTRL_4, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            // Set display format Be framesync Mode
            ScalerDpMacStreamRx1SetDPFRegenMode(_DPF_MODE_FRAME_SYNC_BE);

            // Use vbid[0] rising edge to do vblktovs for Be framesync Mode
            ScalerSetBit(P70_01_DPF_CTRL_1, ~(_BIT5 | _BIT3), 0x00);

            DebugMessageDpRx("DP MAC RX1: BE Frame Sync Mode Enabled!!", ScalerGetByte(P70_00_DPF_CTRL_0));
#else
            //////////////////
            // DE Only Mode //
            //////////////////

            // Set Vsync Front Porch for DE Only Mode
            ScalerSetByte(P70_39_VS_FRONT_PORCH_1, GET_DP_MAC_STREAM_RX1_VFRONT_PORCH());

            // Set BS to HS Delay
            ScalerDpMacStreamRx1SetBsToHsDelay_128b132b(&(pstDpInfo->stDpTimingInfo));

            // Enable DP Freesync Mode(DRR Mode)
            ScalerSetBit(P70_04_DPF_CTRL_4, ~_BIT6, _BIT6);

            // Set DE Only Mode
            ScalerDpMacStreamRx1SetDPFRegenMode(_DPF_MODE_DE_ONLY);

            DebugMessageDpRx("DP MAC RX1: DE Only Mode Enabled!!", ScalerGetByte(P70_00_DPF_CTRL_0));
#endif

            DebugMessageDpRx("DP MAC RX1: Freesync Mode Enabled!!", ScalerGetByte(P70_00_DPF_CTRL_0));
        }
        else
#endif
        {
            // Disable DP Freesync Mode(DRR mode)
            ScalerSetBit(P70_04_DPF_CTRL_4, ~_BIT6, 0x00);

            if(bDeOnlyModeJudge == _TRUE)
            {
                //////////////////
                // DE Only Mode //
                //////////////////

                // Set Vsync Front Porch for DE Only Mode
                ScalerSetByte(P70_39_VS_FRONT_PORCH_1, GET_DP_MAC_STREAM_RX1_VFRONT_PORCH());

                // Set BS to HS Delay
                ScalerDpMacStreamRx1SetBsToHsDelay_128b132b(&(pstDpInfo->stDpTimingInfo));

                // Set DE Only Mode
                ScalerDpMacStreamRx1SetDPFRegenMode(_DPF_MODE_DE_ONLY);

                DebugMessageDpRx("DP MAC RX1: DE_Only Mode Use !!!", ScalerGetByte(P70_00_DPF_CTRL_0));
            }
            else
            {
                /////////////////////////
                // Full Last Line Mode //
                /////////////////////////

                // Set BS to VS Delay
                ScalerDpMacStreamRx1SetBxToVsDelay_128b132b(pstDpInfo);

                // Set Full Last Line Mode
                ScalerDpMacStreamRx1SetDPFRegenMode(_DPF_MODE_FULL_LAST_LINE);
            }
        }
    }

    // Choose VS Rising to Reset FIFO
    ScalerSetBit(P70_21_PG_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), 0x00);

    // Solve Abnormal Full Flag and Max. FIFO Level While Resetting by VSync
    ScalerSetBit(P70_24_FIFO_STATUS_CNT, ~_BIT7, _BIT7);

    return _TRUE;
}

//--------------------------------------------------
// Description  : On Line Check DP 128b132b stability
// Input Value  : None
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerDpMacStreamRx1StableDetect_128b132b(EnumInputPort enumInputPort)
{
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(_DP_MAC_1);

    enumDpMacStreamSourceType = enumDpMacStreamSourceType;

    if(ScalerDpPhyRxEnableEyeMonitor(enumInputPort) == _TRUE)
    {
        ScalerDpPhyRxEyeMonitor(enumInputPort);
    }

#if(_DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER == _ON)
    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
#else
    if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
       (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
#endif
    {
        DebugMessageDpRx("7. DP MAC RX1: Power Down", 0);

        return _FALSE;
    }

    if((ScalerDpMacDphyRxCDRCheck(enumInputPort) == _FALSE) ||
       (ScalerDpMacDphyRxAlignCheck(enumInputPort) == _FALSE) ||
       (ScalerDpMacDphyRxDecodeCheck(enumInputPort) == _FALSE) ||
       ((ScalerDpPhyRxDFECheck(enumInputPort) == _FALSE) && (ScalerDpMacDphyRxSignalCheck(enumInputPort) == _FALSE)))
    {
        DebugMessageDpRx("7. DP MAC RX1: Link Fail", 0);

        return _FALSE;
    }

    if(ScalerDpMacStreamRxBsMissCheck(enumDpMacStreamSourceType) == _TRUE)
    {
        DebugMessageDpRx("7. DP MAC RX1: BS Unstable", 0);

        return _FALSE;
    }

    if(ScalerDpMacStreamRx1GetVideoStream() == _FALSE)
    {
        DebugMessageDpRx("7. DP MAC RX1: Video Stream Fail", 0);

        return _FALSE;
    }

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)

    if(ScalerDpMacDscRxDscStreamGetChange(_DP_MAC_1) == _ENABLE)
    {
        DebugMessageDpRx("7. DP MAC RX1: DSC Capability Change", 0);

        ScalerDpMacDscRxDscStreamClearChange(_DP_MAC_1);

        return _FALSE;
    }

    if(ScalerDpMacStreamRx1GetDscReorder() == _TRUE)
    {
        if(ScalerDpMacStreamRx1DscStreamCheck() == _FALSE)
        {
            DebugMessageDpRx("7. DP MAC RX1: Video Stream Compression Disable", 0);

            return _FALSE;
        }

        if(ScalerDpMacStreamRx1MiscCheck_128b132b() == _FALSE)
        {
            DebugMessageDpRx("7. DP MAC RX1: Misc Change", 0);

            return _FALSE;
        }

        if(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1) != _DSC_MAC_NONE)
        {
            BYTE ucDscMac = ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1);

            if(ScalerDscDecoderPpsChangeCheck(ucDscMac) == _FALSE)
            {
                ScalerDpMacDscFifoStatusIrqProc(_DP_MAC_1, ScalerDscDecoderGetFifoStatus(ucDscMac));

                DebugMessageDpRx("7. DP MAC RX1: DSC PPS Change", 0);

                return _FALSE;
            }

            if(ScalerDscDecoderFifoCheck(ucDscMac, _DSC_FIFO_STABLE_CHECK) == _FALSE)
            {
                ScalerDpMacDscFifoStatusIrqProc(_DP_MAC_1, ScalerDscDecoderGetFifoStatus(ucDscMac));

                DebugMessageDpRx("7. DP MAC RX1: DSC Fifo Under/Overflow", 0);

                return _FALSE;
            }
        }
    }
    else
#endif
    {
        if(GET_DP_MAC_STREAM_RX1_STREAM_DATA_PATH() == _DATA_PATH_VESA)
        {
#if((_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
            if(ScalerDpMacStreamRxDscGetFlagStatus(enumDpMacStreamSourceType) == _TRUE)
            {
                if(ScalerDpMacStreamRx1DscStreamCheck() == _TRUE)
                {
                    DebugMessageDpRx("7. DP MAC RX1: Stable Detect DSC Enable", 0);

                    return _FALSE;
                }
            }
#endif

            if(ScalerDpMacStreamRx1MiscCheck_128b132b() == _FALSE)
            {
                DebugMessageDpRx("7. DP MAC RX1: Misc Change", 0);

                return _FALSE;
            }

            if(ScalerDpMacStreamRx1FifoCheck_128b132b(_DP_FIFO_POLLING_CHECK) == _FALSE)
            {
                DebugMessageDpRx("7. DP MAC RX1: Fifo Under/Overflow", 0);

                return _FALSE;
            }

            if(ScalerDpMacStreamRx1MSAActiveChange_128b132b() == _TRUE)
            {
                DebugMessageDpRx("7. DP MAC RX1: MSA Timing Change", 0);

                return _FALSE;
            }
        }
    }

#if(_DP_FORCE_FREESYNC_SUPPORT == _OFF)
#if(_DP_FREESYNC_SUPPORT == _ON)
    if(ScalerDpMacStreamRx1GetFreeSyncStatusChange() == _TRUE)
    {
        return _FALSE;
    }
#endif
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
    if(ScalerDpMacStreamRxPRModeGetFlagChange(enumDpMacStreamSourceType) == _TRUE)
    {
        return _FALSE;
    }
#endif

    // Clear CPIRQ Flag
    ScalerDpMacDphyRxCheckHdcpCpirqStatus(enumInputPort);

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
    if(ScalerDpMacStreamRx1GetDscReorder() == _TRUE)
    {
        if(ScalerDscDecoderDpCrcCalculate(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1)) == _TRUE)
        {
            ScalerDpMacStreamRx1CrcCalculate_128b132b();
        }
    }
    else
#endif
    {
        ScalerDpMacStreamRx1CrcCalculate_128b132b();
    }

    ScalerDpMacStreamRx1SdpDataDetect();

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_STREAM_DATA_PATH() == _DATA_PATH_DSC_REORDER)
    {
        if(ScalerDpMacStreamRx1DscStreamCheck() == _FALSE)
        {
            DebugMessageDpRx("7. DP MAC RX1: Video Stream Compression Disable", 0);

            return _FALSE;
        }

        if(ScalerDpMacStreamRx1MiscCheck_128b132b() == _FALSE)
        {
            DebugMessageDpRx("7. DP MAC RX1: Misc Change", 0);

            return _FALSE;
        }

        // DP Mac Rx Check PPS SDP Change
        if(ScalerDpMacStreamRx1GetSdpChanged(_DP_SDP_TYPE_PPS) == _TRUE)
        {
            DebugMessageDpRx("7. DP MAC RX1: PPS SDP Change", 0);

            return _FALSE;
        }
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check DP Misc Information 128b132b
// Input Value  : None
// Output Value : True --> DP Misc Check Ok
//--------------------------------------------------
bit ScalerDpMacStreamRx1MiscCheck_128b132b(void)
{
#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
    bit bColorFormatChange = _FALSE;
#endif

    // Check MISC1[6]
    if((ScalerGetBit(P75_03_MN_STRM_ATTR_MISC1, _BIT6)) == _BIT6)
    {
        return ScalerDpMacStreamRx1VscCheck();
    }
    else
    {
        // Get MISC Info
        BYTE ucMisc0 = ScalerGetByte(P75_02_MN_STRM_ATTR_MISC);
        BYTE ucColorSpaceValue = (ScalerGetBit(P75_03_MN_STRM_ATTR_MISC1, _BIT7)) | (ucMisc0 & (_BIT2 | _BIT1));

        // Color Space Check
        // Color format info source change from VSC --> MISC
        if(GET_DP_MAC_STREAM_RX1_VSC_SDP_COLOR_MODE() == _TRUE)
        {
            switch(ucColorSpaceValue)
            {
                case _BIT1:
                    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_YCBCR422)
                    {
                        DebugMessageDpRx("DP MAC RX1: Misc change: Color Format, _COLOR_SPACE_YCBCR422", 0);
                        return _FALSE;
                    }
                    break;

                case _BIT2:
                    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_YCBCR444)
                    {
                        DebugMessageDpRx("DP MAC RX1: Misc change: Color Format, _COLOR_SPACE_YCBCR444", 0);
                        return _FALSE;
                    }
                    break;

                case _BIT7:
                    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_Y_ONLY)
                    {
                        DebugMessageDpRx("DP MAC RX1: Misc change: Color Format, _COLOR_SPACE_Y_ONLY", 0);
                        return _FALSE;
                    }
                    break;

                case (_BIT7 | _BIT1):
                    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_RAW)
                    {
                        DebugMessageDpRx("DP MAC RX1: Misc change: Color Format, _COLOR_SPACE_RAW", 0);
                        return _FALSE;
                    }
                    break;

                default:
                    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() != _COLOR_SPACE_RGB)
                    {
                        DebugMessageDpRx("DP MAC RX1: Misc change: Color Format, _COLOR_SPACE_RGB", 0);
                        return _FALSE;
                    }
                    break;
            }
        }
        else
        {
            if(ucColorSpaceValue != GET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE())
            {
                DebugMessageDpRx("DP MAC RX1: Misc change: Color Space", 0);

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
                if(GET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    SET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE(ucColorSpaceValue);
                    bColorFormatChange = _TRUE;
                }
                else
#endif
                {
                    return _FALSE;
                }
            }
        }

        // Color Depth Check
        if((((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5) != GET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE())
        {
            DebugMessageDpRx("DP MAC RX1: Misc change: Color Depth", (((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5));

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
            if(GET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                SET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE(((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5);
                bColorFormatChange = _TRUE;
            }
            else
#endif
            {
                return _FALSE;
            }
        }

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
        if(bColorFormatChange == _TRUE)
        {
            ScalerDpMacStreamRx1DMColorFormatChgWoResetSetting();
        }
#endif

        // Colorimetry Check
        if(GET_DP_MAC_STREAM_RX1_COLORIMETRY() != _COLORIMETRY_EXT)
        {
            if(((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1) != GET_DP_MAC_STREAM_RX1_COLORIMETRY_PREVALUE())
            {
                DebugMessageDpRx("DP MAC RX1: Misc change: Colorimetry", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_MAC_STREAM_RX1_COLORIMETRY_PREVALUE((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
                    ScalerDpMacStreamRx1ColorimetrySetting();
                    SET_DP_MAC_STREAM_RX1_COLORIMETRY_CHANGED();
                }
            }
        }
        else
        {
            DebugMessageDpRx("DP MAC RX1: Misc change: Colorimetry", 0);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_COLORIMETRY_PREVALUE((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
                ScalerDpMacStreamRx1ColorimetrySetting();
                SET_DP_MAC_STREAM_RX1_COLORIMETRY_CHANGED();
            }
        }

        // Dynamic Range Check
#if(_YCC_QUANTIZATION_RANGE_FUNCTION == _ON)
        if((GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422))
        {
            if(((ucMisc0 & _BIT3) >> 3) != GET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE())
            {
                DebugMessageDpRx("DP MAC RX1: Misc change: Dynamic Range", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE((ucMisc0 & _BIT3) >> 3);
                    ScalerDpMacStreamRx1QuantizationSetting();
                    SET_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED();
                }
            }
        }
        else
#endif
        {
#if(_RGB_QUANTIZATION_RANGE_FUNCTION == _ON)
            if(((ucMisc0 & _BIT3) >> 3) != GET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE())
            {
                DebugMessageDpRx("DP MAC RX1: Misc change: Dynamic Range", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE((ucMisc0 & _BIT3) >> 3);
                    ScalerDpMacStreamRx1QuantizationSetting();
                    SET_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED();
                }
            }
#endif
        }

#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _FALSE)
#endif
        {
            // Get HSW
            PDATA_WORD(0) = (ScalerGetWord(P75_16_MSA_HSW_0) & 0x7FFF);

            // Get VSW
            PDATA_WORD(1) = (ScalerGetWord(P75_1E_MSA_VSW_0) & 0x7FFF);

            if((PDATA_WORD(0) == 0x00) || (PDATA_WORD(1) == 0x00))
            {
                return _FALSE;
            }
        }

        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Check DP MSA Vactive / Hactive Change 128b132b
// Input Value  : None
// Output Value : True --> DP Vactive / Hactive Information Check Ok
//--------------------------------------------------
bit ScalerDpMacStreamRx1MSAActiveChange_128b132b(void)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(P75_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Display Format Hactive
    PDATA_WORD(0) = ScalerGetWord(P70_14_MN_DPF_HWD_M);

    // Get MSA Hactive
    PDATA_WORD(1) = ScalerGetWord(P75_14_MSA_HWD_0);

    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        PDATA_WORD(1) /= 2;
    }

    // Get Display Format Vactive
    PDATA_WORD(2) = ScalerGetWord(P70_1C_MN_DPF_VHT_M);

    // Get MSA Vactive
    PDATA_WORD(3) = ScalerGetWord(P75_1C_MSA_VHT_0);

    if((PDATA_WORD(0) != PDATA_WORD(1)) || (PDATA_WORD(2) != PDATA_WORD(3)))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Interlace by VBID or Measure 128b132b
// Input Value  : None
// Output Value : True --> Interlace
//--------------------------------------------------
bit ScalerDpMacStreamRx1InterlaceCheck_128b132b(StructDpInfo *pstDpInfo)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
    WORD usTempVTotal = pstDpInfo->stDpTimingInfo.usVTotal;
    WORD usHTotalCount = 0;

    // Convert HTotal Count from 1/2 Link Clk to GDI Clk
    usHTotalCount = ((DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount * _GDIPHY_RX_GDI_CLK_KHZ * 2 + ((pstDpInfo->stDpLinkInfo.ulLinkClockHz / 1000) >> 1)) / (pstDpInfo->stDpLinkInfo.ulLinkClockHz / 1000);

#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_JUDGE_OOR() == _TRUE)
    {
        pstDpInfo->stDpLinkInfo.b1InterlaceOddMode = _FALSE;
    }
    else
#endif
    {
        // if VTotal Difference > 1/2 HTotal
        if((ABSDWORD(pstDpInfo->stDpLinkInfo.ulVBsToBsCountN, pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1)) > (usHTotalCount / 2))
        {
            // Set VTotal as MSA info if MST is Enabled
            if(ScalerDpRxGetSrcMstEnable(enumInputPort) == _TRUE)
            {
                // Set VTotal As the Smaller One
                usTempVTotal = pstDpInfo->stDpTimingInfo.usVTotal;
            }
            else
            {
                if(ScalerDpMacStreamRx1InterlaceVtotalGetMSACheck_128b132b(pstDpInfo) == _TRUE)
                {
                    usTempVTotal = TO_WORD(ScalerGetByte(P75_18_MSA_VTT_0), ScalerGetByte(P75_19_MSA_VTT_1));
                }
                else
                {
                    if(pstDpInfo->stDpLinkInfo.ulVBsToBsCountN < pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1)
                    {
                        usTempVTotal = ((pstDpInfo->stDpLinkInfo.ulVBsToBsCountN + (usHTotalCount >> 1)) / usHTotalCount);
                    }
                    else
                    {
                        usTempVTotal = ((pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1 + (usHTotalCount >> 1)) / usHTotalCount);
                    }
                }
            }

            pstDpInfo->stDpLinkInfo.b1InterlaceOddMode = _TRUE;
        }
        else
        {
            pstDpInfo->stDpLinkInfo.b1InterlaceOddMode = _FALSE;
        }
    }

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
    // Check N and N+1 Frame Vs2Vs Count
    if((pstDpInfo->stDpLinkInfo.b1InterlaceOddMode) == _TRUE)
    {
        // Enable DP Interlace
        ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT7), _BIT7);

        // Enable Field Sync by BE
        ScalerSetBit(P70_08_INTERLACE_CTRL_2, ~(_BIT7), _BIT7);

        // HW Check Interlace
        if(pstDpInfo->stDpLinkInfo.b1HwInterlaceDetect == _TRUE)
        {
            // Field reference HW
            ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT6), _BIT6);
        }
        else
        {
            // Field reference VBID
            ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT6), 0x00);
        }

        // Set Vtt odd fw mode
        SET_DP_MAC_STREAM_RX1_INTERLACE_VTT_FW_MODE_128B132B(_ODD);

        pstDpInfo->stDpTimingInfo.usVTotal = usTempVTotal;

        return _TRUE;
    }
    else
    {
        // Check VBID Field Toggle and VBID Interlace Info
        if((pstDpInfo->stDpLinkInfo.b1InterlaceFieldN != pstDpInfo->stDpLinkInfo.b1InterlaceFieldN1) && (ScalerGetBit(P75_01_DP_VBID, _BIT2) == _BIT2))
        {
            // Enable DP Interlace
            ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT7), _BIT7);

            // Field reference VBID
            ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT6), 0x00);

            // Enable Field Sync by BE
            ScalerSetBit(P70_08_INTERLACE_CTRL_2, ~(_BIT7), _BIT7);

            // Set Vtt Even fw mode
            SET_DP_MAC_STREAM_RX1_INTERLACE_VTT_FW_MODE_128B132B(_EVEN);

            pstDpInfo->stDpTimingInfo.usVTotal = usTempVTotal;

            return _TRUE;
        }

        // Enable DP Progressive Mode
        ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT7), 0x00);

        // Field reference VBID
        ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT6), 0x00);

        // Enable Field Sync by VBID
        ScalerSetBit(P70_08_INTERLACE_CTRL_2, ~(_BIT7), _BIT7);

        // Set Vtt Even fw mode
        SET_DP_MAC_STREAM_RX1_INTERLACE_VTT_FW_MODE_128B132B(_EVEN);

        return _FALSE;
    }
#else
    // Check if VBID[2] is Interlace Mode
    if(ScalerGetBit(P75_01_DP_VBID, _BIT2) == _BIT2)
    {
        // Enable DP Interlace
        ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT7), _BIT7);

        if(pstDpInfo->stDpLinkInfo.b1InterlaceOddMode == _FALSE)
        {
            // Disable DP Interlace
            ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT7), 0x00);
        }

        // Check Interlace Field Toggle by Frame
        if(pstDpInfo->stDpLinkInfo.b1InterlaceFieldN != pstDpInfo->stDpLinkInfo.b1InterlaceFieldN1)
        {
            if(pstDpInfo->stDpLinkInfo.b1InterlaceOddMode == _TRUE)
            {
                // Field Signal Refer to HW
                ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT6), _BIT6);
            }
            else
            {
                // Field Signal Refer to VBID
                ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT6), 0x00);
            }

            if((pstDpInfo->stDpLinkInfo.b1HwFakeInterlaceDetect == _FALSE) &&
               (((pstDpInfo->stDpLinkInfo.b1InterlaceFieldN == _TRUE) && (pstDpInfo->stDpLinkInfo.b1InterlaceFieldN1 == _FALSE) &&
                 (pstDpInfo->stDpLinkInfo.ulVBsToBsCountN < pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1)) ||
                ((pstDpInfo->stDpLinkInfo.b1InterlaceFieldN == _FALSE) && (pstDpInfo->stDpLinkInfo.b1InterlaceFieldN1 == _TRUE) &&
                 (pstDpInfo->stDpLinkInfo.ulVBsToBsCountN > pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1))))
            {
                // Field inverse enable
                ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT5 | _BIT4 | _BIT0), _BIT4);
            }
        }
        else
        {
            // Field reference HW
            ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT6), _BIT6);
        }

        pstDpInfo->stDpTimingInfo.usVTotal = usTempVTotal;

        return _TRUE;
    }
    else if(pstDpInfo->stDpLinkInfo.b1InterlaceOddMode == _TRUE)
    {
        // Delay a Complete Frame
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        if(pstDpInfo->stDpLinkInfo.b1HwFakeInterlaceDetect == _TRUE)
        {
            DebugMessageDpRx("DP MAC RX1: Fake Interlace", 0);
            pstDpInfo->stDpLinkInfo.b1InterlaceOddMode = _FALSE;
        }
        else
        {
            // Enable interlace mode, field reference HW
            ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            pstDpInfo->stDpTimingInfo.usVTotal = usTempVTotal;

            return _TRUE;
        }
    }

    // Disable DP Interlace
    ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT7 | _BIT6), 0x00);

    return _FALSE;
#endif
}

//--------------------------------------------------
// Description  : Judge Vtotal from MSA or not
// Input Value  : None
// Output Value : TRUE --> Get Vtotal from MSA
//--------------------------------------------------
bit ScalerDpMacStreamRx1InterlaceVtotalGetMSACheck_128b132b(StructDpInfo *pstDpInfo)
{
    WORD usVfreq = 0;

    // Vfreq (unit : 0.01Hz)
    usVfreq = _GDIPHY_RX_GDI_CLK_KHZ * 1000 * 100 / pstDpInfo->stDpLinkInfo.ulVBsToBsCountN;

    // Solve interlace issue for Astro VG870 for timing : EIA1920 x 1080i @ 119.88 Hz
    // Central Vfreq = 120Hz +/- 1% = 118.8Hz ~ 121.2Hz
    if((TO_WORD(ScalerGetByte(P75_10_MSA_HTT_0), ScalerGetByte(P75_11_MSA_HTT_1)) == 2200) &&
       (TO_WORD(ScalerGetByte(P75_18_MSA_VTT_0), ScalerGetByte(P75_19_MSA_VTT_1)) == 562) &&
       ((usVfreq > 11880) && (usVfreq < 12120)) && (ScalerGetBit(P75_01_DP_VBID, _BIT2) == _BIT2))
    {
        return _TRUE;
    }

    // Solve interlace issue for QD-980 for timing : 480i @ 60 Hz
    // Central Vfreq = 60Hz +/- 1% = 59.4Hz ~ 60.6Hz
    if((TO_WORD(ScalerGetByte(P75_10_MSA_HTT_0), ScalerGetByte(P75_11_MSA_HTT_1)) == 858) &&
       (TO_WORD(ScalerGetByte(P75_18_MSA_VTT_0), ScalerGetByte(P75_19_MSA_VTT_1)) == 262) &&
       ((usVfreq > 5940) && (usVfreq < 6060)) && (ScalerGetBit(P75_01_DP_VBID, _BIT2) == _BIT2))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Reset Interlace Mode
// Input Value  : EnumHDCPType
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1InterlaceReset_128b132b(void)
{
    // Interlace mode disable, refer to VBID[1], Field Inverse Disable, Inverse the inner field disable
    ScalerSetBit(P70_06_INTERLACE_CTRL_0, ~(_BIT7 | _BIT6 | _BIT4), 0x00);

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
    // Enable Field Sync by VBID
    ScalerSetBit(P70_08_INTERLACE_CTRL_2, ~_BIT7, 0x00);

    // Set Vtt odd fw mode
    SET_DP_MAC_STREAM_RX1_INTERLACE_VTT_FW_MODE_128B132B(_ODD);
#endif
}

//--------------------------------------------------
// Description  : Mac FIFO Check 128b132b
// Input Value  : None
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
bit ScalerDpMacStreamRx1FifoCheckProc_128b132b(EnumDpFifoCheckCondition enumFifoCheckCondition, StructDpInfo *pstDpInfo)
{
    if(ScalerDpMacStreamRx1FifoCheck_128b132b(enumFifoCheckCondition) == _FALSE)
    {
#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE() == _TRUE)
        {
            return _FAIL;
        }
        else
#endif
        {
            ScalerDpMacStreamRx1AdjustVsyncDelay_128b132b(pstDpInfo);

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if(ScalerSyncCheckUrgentEvent() == _TRUE)
            {
                return _FAIL;
            }
#endif

            if(ScalerDpMacStreamRx1FifoCheck_128b132b(enumFifoCheckCondition) == _FALSE)
            {
                ScalerDpMacStreamRx1AdjustVsyncDelay_128b132b(pstDpInfo);

#if(_URGENT_EVENT_CHECK_MODE == _ON)
                if(ScalerSyncCheckUrgentEvent() == _TRUE)
                {
                    return _FAIL;
                }
#endif

                if(ScalerDpMacStreamRx1FifoCheck_128b132b(enumFifoCheckCondition) == _FALSE)
                {
                    return _FAIL;
                }
            }
        }
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP CRC Calculate 128b132b
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1CrcCalculate_128b132b(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

    if(GET_DP_MAC_STREAM_RX1_CRC_CALCULATE() == _TRUE)
    {
        DebugMessageDpRx("7. DP MAC RX1: CRC Test Start", 0);

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
        if(ScalerDpMacStreamRx1GetDscReorder() == _TRUE)
        {
            ScalerSetBit(P70_50_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
#endif
        {
            if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
            {
                ScalerSetBit(P70_50_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT1 | _BIT0), _BIT0);
            }
            else if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
            {
                ScalerSetBit(P70_50_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT1 | _BIT0), _BIT1);
            }
            else
            {
                ScalerSetBit(P70_50_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT1 | _BIT0), 0x00);
            }
        }

        // Start CRC Calculation
        ScalerSetBit(P70_50_DP_CRC_CTRL, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, P70_50_DP_CRC_CTRL, _BIT6, _TRUE) == _TRUE)
        {
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
            if(ScalerDpMacStreamRx1GetDscReorder() == _TRUE)
            {
                if(ScalerDscDecoderFifoCheck(ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1), _DSC_FIFO_POLLING_CHECK) == _TRUE)
                {
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x62, ScalerGetByte(P70_52_DP_CRC_R_L));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x63, ScalerGetByte(P70_51_DP_CRC_R_M));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x64, ScalerGetByte(P70_54_DP_CRC_G_L));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x65, ScalerGetByte(P70_53_DP_CRC_G_M));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x66, ScalerGetByte(P70_56_DP_CRC_B_L));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x67, ScalerGetByte(P70_55_DP_CRC_B_M));

                    CLR_DP_MAC_STREAM_RX1_CRC_CALCULATE();

                    // Update _TEST_CRC_COUNT
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x46, 0x21);
                }
            }
            else
#endif
            {
                if(ScalerDpMacStreamRx1FifoCheck_128b132b(_DP_FIFO_POLLING_CHECK) == _TRUE)
                {
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x40, ScalerGetByte(P70_52_DP_CRC_R_L));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x41, ScalerGetByte(P70_51_DP_CRC_R_M));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x42, ScalerGetByte(P70_54_DP_CRC_G_L));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x43, ScalerGetByte(P70_53_DP_CRC_G_M));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x44, ScalerGetByte(P70_56_DP_CRC_B_L));
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x45, ScalerGetByte(P70_55_DP_CRC_B_M));

                    CLR_DP_MAC_STREAM_RX1_CRC_CALCULATE();

                    // Update _TEST_CRC_COUNT
                    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x46, 0x21);
                }
            }
        }

#if(_DP_PR_MODE_SUPPORT == _OFF)
        // Stop CRC Calculation
        ScalerSetBit(P70_50_DP_CRC_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : DP RGB Output Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1AVMute_128b132b(void)
{
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
    BYTE ucDscMac = ScalerDscDecoderDpMacRxxGetDscDecoderMac(_DP_MAC_1);

    if(ScalerDscDecoderCheckFifoIRQ(ucDscMac) == _TRUE)
    {
        // Enable Output Force to Backgound Color
        ScalerDscDecoderSetForceToBackGround(ucDscMac, _ENABLE);

        // Disable fifo overflwo/ underflwo IRQ
        ScalerDscDecoderSetFifoIRQ(ucDscMac, _DISABLE);

        // Set D Domain Region Free run/ Force to Background
        ScalerDDomainResetDDomainRgn(GET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH());
    }
    else if(ScalerGetBit(P75_3A_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
#else
    if(ScalerGetBit(P75_3A_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
#endif
    {
        // Set D Domain Region Free run/ Force to Background
        ScalerDDomainResetDDomainRgn(GET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH());
    }

    // Disable BS Miss Detect IRQ
    ScalerDpMacStreamRx1SetBsMissDetectIRQ(_DISABLE);

    // Disable fifo overflwo/ underflwo IRQ
    ScalerSetBit(P75_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

    // Disable RGB Output
    ScalerSetBit(P70_01_DPF_CTRL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_AUDIO_SUPPORT == _ON)
    // Disable Audio Channel
    ScalerDpAudioRx1AudioEnableControl(_DISABLE);
#endif

    ScalerDpMacStreamRx1SetSdpReset_128b132b();
}

//--------------------------------------------------
// Description  : DP BS to HS Delay Calculation 128b132b
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
void ScalerDpMacStreamRx1SetBsToHsDelay_128b132b(StructTimingInfo *pstDpTimingInfo)
{
    WORD usFifoOffset = 0;
    WORD usBsToHsDelay = 0;
    BYTE ucDiv = 0;

    // DP fifo size = 256 x 96bit
    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
    {
        // FifoOffset = (1/2 * (256 * 96) / (2 * depth per color)), color format is YCbCr 4:2:2
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE_128B132B / (4 * ((WORD)GET_DP_MAC_STREAM_RX1_COLOR_DEPTH()));
    }
    else
    {
        // FifoOffset = (1/2 * (256 * 96) / (3 * depth per color)), color format is RGB or YCbCr 4:4:4 or YCbCr 4:2:0 or others
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE_128B132B / (6 * ((WORD)GET_DP_MAC_STREAM_RX1_COLOR_DEPTH()));
    }

    // De Only Mode HW constraint: BS2HS delay < Htotal => 1/2 FIFO < H Width, Enough Margin = 1/2 H Width
    if(usFifoOffset > (pstDpTimingInfo->usHWidth >> 1))
    {
        usFifoOffset = (pstDpTimingInfo->usHWidth >> 1);
    }

    switch(ScalerDpMacStreamRx1InputPixelMode())
    {
#if(_DP_MAC_RX_128B132B_FOUR_PIXEL_MODE_SUPPORT == _ON)
        case _DP_RX_MAC_FOUR_PIXEL_MODE:

            ucDiv = 2;

            break;
#endif

        case _DP_RX_MAC_TWO_PIXEL_MODE:

            ucDiv = 1;

            break;

        case _DP_RX_MAC_ONE_PIXEL_MODE:

            ucDiv = 0;

            break;

        default:

            break;
    }

    // Get BS to HS delay according to (HBlanking + 1/2 FIFO - HStart), Unit is depend on pixel mode
    usBsToHsDelay = ((pstDpTimingInfo->usHTotal - pstDpTimingInfo->usHWidth) + usFifoOffset - pstDpTimingInfo->usHStart) >> ucDiv;

    // Set BS to HS Delay
    ScalerSetByte(P70_36_BS2HS_0, HIBYTE(usBsToHsDelay));
    ScalerSetByte(P70_37_BS2HS_1, LOBYTE(usBsToHsDelay));
}

//---------------------------------------------------------
// Description  : Get Display Format Information 128b/132b
// Input Value  : Display Format Content
// Output Value : Display Format Information
//---------------------------------------------------------
WORD ScalerDpMacStreamRx1GetDisplayFormat_128b132b(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo)
{
    switch(enumDpDisplayFormatInfo)
    {
        case _DP_V_HEIGHT:

            return (((WORD)ScalerGetByte(P70_1C_MN_DPF_VHT_M) << 8) | ScalerGetByte(P70_1D_MN_DPF_VHT_L));

        case _DP_H_WIDTH:

            return (((WORD)ScalerGetByte(P70_14_MN_DPF_HWD_M) << 8) | ScalerGetByte(P70_15_MN_DPF_HWD_L));

        case _DP_H_START:

            return (((WORD)ScalerGetByte(P70_12_MN_DPF_HST_M) << 8) | ScalerGetByte(P70_13_MN_DPF_HST_L));

        default:

            break;
    }

    return 0;
}

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mac Rx PR Mode Check Process 128b132b
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PRModeCheckProc_128b132b(EnumInputPort enumInputPort)
{
    // Check Pr Sink Status Active
    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x20, 0x22, (_BIT2 | _BIT1 | _BIT0)) == _DP_PR_MODE_ACTIVE)
    {
        if(ScalerTimerPollingDataBitFlagProc(_DP_TWO_FRAME_TIME_MAX, P75_47_VSC7, 0x01, _BIT0, _TRUE) == _TRUE)
        {
            if(ScalerTimerPollingDataBitFlagProc(_DP_ONE_FRAME_TIME_MAX, P75_47_VSC7, 0x01, _BIT3, _TRUE) == _FALSE)
            {
                // If Pr Sink Status Active and DB1[0] Pr_state = 1, DB1[3] Su_valid = 0, Update DPCD Error Status RFB Storage Error
                ScalerDpAuxRxDpcdPRModeErrorStateUpdate(enumInputPort, _DP_PR_MODE_RFB_STORAGE_ERROR);
            }
        }
        else
        {
            // If Pr Sink Status Active and Not Receive Vsc Sdp DB1[0] Pr_state = 1, Update DPCD Error Status RFB Storage Error
            ScalerDpAuxRxDpcdPRModeErrorStateUpdate(enumInputPort, _DP_PR_MODE_RFB_STORAGE_ERROR);
        }
    }

    if(ScalerDpAuxRxGetPRModeDpcdCrcEnable(enumInputPort) == _ENABLE)
    {
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
        if(GET_DP_MAC_STREAM_RX1_DSC_SUPPORT_128B132B() == _TRUE)
        {
            ScalerSetBit(P70_50_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
#endif
        {
            if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
            {
                ScalerSetBit(P70_50_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT1 | _BIT0), _BIT0);
            }
            else if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
            {
                ScalerSetBit(P70_50_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT1 | _BIT0), _BIT1);
            }
            else
            {
                ScalerSetBit(P70_50_DP_CRC_CTRL, ~(_BIT6 | _BIT5 | _BIT1 | _BIT0), 0x00);
            }
        }

        // Disable CRC Calculation
        ScalerSetBit(P70_50_DP_CRC_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // Start CRC Calculation
        ScalerSetBit(P70_50_DP_CRC_CTRL, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, P70_50_DP_CRC_CTRL, _BIT6, _TRUE) == _TRUE)
        {
            // Clr Pr CRC Irq Flag
            ScalerSetBit(P75_4B_VSC11, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

            // Enable Pr Crc Irq
            ScalerSetBit(P75_4A_VSC10, ~_BIT5, _BIT5);
        }
    }
}

//--------------------------------------------------
// Description  : PR Mode SDP Pr State Change Irq
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_128b132b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Clear flag
        ScalerSetBit(P75_4B_VSC11, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        // Enable Pr_State Chang Irq
        ScalerSetBit(P75_4A_VSC10, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable Pr_State Chang Irq
        ScalerSetBit(P75_4A_VSC10, ~_BIT7, 0x00);

        // Clear flag
        ScalerSetBit(P75_4B_VSC11, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
    }
}
#endif

//--------------------------------------------------------------
// Description  : DP Pixel Mode Setting
// Input Value  : PixelMode
// Output Value : True --> Register Setting Pass for Pixel Mode
//--------------------------------------------------------------
bit ScalerDpMacStreamRx1PixelModeSetting_128b132b(EnumDpStreamPixelMode enumPixelMode)
{
    switch(enumPixelMode)
    {
        case _1_PIXEL_MODE:

            ScalerSetBit(P70_02_DPF_CTRL_2, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), 0x00);

            return _TRUE;

        case _2_PIXEL_MODE:

            ScalerSetBit(P70_02_DPF_CTRL_2, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT0);

            return _TRUE;

#if(_DP_MAC_RX_128B132B_FOUR_PIXEL_MODE_SUPPORT == _ON)
        case _4_PIXEL_MODE:

            ScalerSetBit(P70_02_DPF_CTRL_2, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT1);

            return _TRUE;
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP Video Setting for PG 128b132b
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1VideoSetting_128b132b(void)
{
    // Set Color Space for Display Format Gen.
    switch(GET_DP_MAC_STREAM_RX1_COLOR_SPACE())
    {
        case _COLOR_SPACE_RGB:
            DebugMessageDpRx("DP MAC RX1: _COLOR_SPACE_RGB", 0);
            ScalerSetBit(P70_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
            break;

        case _COLOR_SPACE_YCBCR444:
            DebugMessageDpRx("DP MAC RX1: _COLOR_SPACE_YCBCR444", 0);
            ScalerSetBit(P70_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
            break;

        case _COLOR_SPACE_YCBCR422:
            DebugMessageDpRx("DP MAC RX1: _COLOR_SPACE_YCBCR422", 0);
            ScalerSetBit(P70_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), _BIT3);
            break;

        case _COLOR_SPACE_YCBCR420:
            DebugMessageDpRx("DP MAC RX1: _COLOR_SPACE_YCBCR420", 0);
            ScalerSetBit(P70_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
            break;

        case _COLOR_SPACE_Y_ONLY:
            DebugMessageDpRx("DP MAC RX1: _COLOR_SPACE_Y_ONLY", 0);
            ScalerSetBit(P70_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
            break;

        case _COLOR_SPACE_RAW:
            DebugMessageDpRx("DP MAC RX1: _COLOR_SPACE_RAW", 0);
            ScalerSetBit(P70_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
            break;

        default:
            // RGB
            ScalerSetBit(P70_20_PG_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
            break;
    }

    // Set Color Depth for Display Format Gen.
    ScalerSetBit(P70_20_PG_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), GET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE());
    DebugMessageDpRx("DP MAC RX1: _COLOR_DEPTH", GET_DP_MAC_STREAM_RX1_COLOR_DEPTH());
}

//--------------------------------------------------
// Description  : DP BS/BE to VS Delay Calculation
// Input Value  : None
// Output Value : BS/BE to VS Delay
//--------------------------------------------------
void ScalerDpMacStreamRx1SetBxToVsDelay_128b132b(StructDpInfo *pstDpInfo)
{
    DWORD ulVFrontPorch = 0;
    DWORD ulHFrontPorch = 0;
    DWORD ulBxToVsDelay = 0;
    WORD usFifoOffset = 0;

    // Get V Front Porch, unit is pixel clock
    ulVFrontPorch = ((DWORD)GET_DP_MAC_STREAM_RX1_VFRONT_PORCH()) * pstDpInfo->stDpTimingInfo.usHTotal;

    // Get H Front Porch, unit is pixel clock
    ulHFrontPorch = (DWORD)(pstDpInfo->stDpTimingInfo.usHTotal - pstDpInfo->stDpTimingInfo.usHWidth - pstDpInfo->stDpTimingInfo.usHStart);

    // Get Video FIFO Size, unit is pixel clock
    if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
    {
        // FifoOffset = (Video FIFO Size / (2 * depth per color)), color format is YCbCr 4:2:2
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE_128B132B / (2 * (WORD)GET_DP_MAC_STREAM_RX1_COLOR_DEPTH());
    }
    else
    {
        // FifoOffset = (Video FIFO Size / (3 * depth per color)), color format is RGB or YCbCr 4:4:4 or others
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE_128B132B / (3 * (WORD)GET_DP_MAC_STREAM_RX1_COLOR_DEPTH());
    }

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
    // HBR/HBE Adjust Fifo Offset
    if(pstDpInfo->stDpHblankingModifyInfo.enumHblankingModifyMode != _NO_HBLANKING_MODIFY)
    {
        usFifoOffset = ScalerDpMacStreamRxHblankingModifyFifoOffsetUpdate(pstDpInfo, usFifoOffset);
    }
#endif
    {
        usFifoOffset = usFifoOffset / 2;
    }

    if(ScalerDpMacStreamRx1FrameSyncBeModeCheck() == _TRUE)
    {
        if(pstDpInfo->stDpLinkInfo.ulStreamClockHz == 0x00)
        {
            DebugMessageDpRx("DP MAC RX1: Stream Clk is invalid", 0);

            return;
        }

        // Get BE to VS Delay, unit is 1/32 link clock
        ulBxToVsDelay = ScalerGlobalComputeDwordMulDiv(((DWORD)usFifoOffset - pstDpInfo->stDpTimingInfo.usHStart), (pstDpInfo->stDpLinkInfo.ulLinkClockHz / 32) * 10, pstDpInfo->stDpLinkInfo.ulStreamClockHz);
    }
    else
    {
        if(pstDpInfo->stDpLinkInfo.ulStreamClockHz == 0x00)
        {
            DebugMessageDpRx("DP MAC RX1: Stream Clk is invalid", 0);

            return;
        }

        // Get BS to VS Delay, unit is 1/32 link clock
        ulBxToVsDelay = ScalerGlobalComputeDwordMulDiv((ulVFrontPorch + ulHFrontPorch + (DWORD)usFifoOffset), (pstDpInfo->stDpLinkInfo.ulLinkClockHz / 32) * 10, pstDpInfo->stDpLinkInfo.ulStreamClockHz);
    }

    // Set BX to VS Delay of Odd Field
    ScalerSetByte(P70_33_OVBLK2VS_H, LOBYTE(HIWORD(ulBxToVsDelay)));
    ScalerSetByte(P70_34_OVBLK2VS_M, HIBYTE(LOWORD(ulBxToVsDelay)));
    ScalerSetByte(P70_35_OVBLK2VS_L, LOBYTE(LOWORD(ulBxToVsDelay)));

    if(pstDpInfo->stDpLinkInfo.b1InterlaceOddMode == _TRUE)
    {
        if(pstDpInfo->stDpLinkInfo.ulStreamClockHz == 0x00)
        {
            DebugMessageDpRx("DP MAC RX1: Stream Clk is invalid", 0);

            return;
        }

        // ulBxToVsDelay = ulBxToVsDelay + 1 Line(Unit is 1/32 Link Clock)
        ulBxToVsDelay += ScalerGlobalComputeDwordMulDiv((DWORD)pstDpInfo->stDpTimingInfo.usHTotal, (pstDpInfo->stDpLinkInfo.ulLinkClockHz / 32) * 10, pstDpInfo->stDpLinkInfo.ulStreamClockHz);

        SET_DP_MAC_STREAM_RX1_INTERLACE_VTOTAL_NUMBER(_ODD);
    }
    else
    {
        SET_DP_MAC_STREAM_RX1_INTERLACE_VTOTAL_NUMBER(_EVEN);
    }

    // Set BX to VS Delay of Even Field
    ScalerSetByte(P70_30_EVBLK2VS_H, LOBYTE(HIWORD(ulBxToVsDelay)));
    ScalerSetByte(P70_31_EVBLK2VS_M, HIBYTE(LOWORD(ulBxToVsDelay)));
    ScalerSetByte(P70_32_EVBLK2VS_L, LOBYTE(LOWORD(ulBxToVsDelay)));
}

//--------------------------------------------------
// Description  : DP Video Fifo Check 128b132b
// Input Value  : Fifo Check Condition
// Output Value : True --> Fifo not over/underflow
//--------------------------------------------------
bit ScalerDpMacStreamRx1FifoCheck_128b132b(EnumDpFifoCheckCondition enumFifoCheckCondition)
{
    if(enumFifoCheckCondition == _DP_FIFO_DELAY_CHECK)
    {
        ScalerSetBit(P70_21_PG_CTRL_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        pData[0] = 0;

        while(pData[0] < 6)
        {
            ScalerTimerDelayXms(10);

            if((ScalerGetBit(P70_21_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(P70_21_PG_CTRL_1, _BIT2) == _BIT2))
            {
                return _FALSE;
            }

            pData[0]++;
        }
    }
    else
    {
        if((ScalerGetBit(P70_21_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(P70_21_PG_CTRL_1, _BIT2) == _BIT2))
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Adjust Vsync Delay
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1AdjustVsyncDelay_128b132b(StructDpInfo *pstDpInfo)
{
    DWORD ulBStoVSDelayDelta = 0;
    BYTE ucOneFrameTime = 0;

    if(ScalerGetBit(P70_21_PG_CTRL_1, (_BIT1 | _BIT0)) == 0x00)// Fifo Ok
    {
        return;
    }
    else if(ScalerGetBit(P70_21_PG_CTRL_1, _BIT0) == _BIT0) // Fifo Overflow
    {
        if(pstDpInfo->stDpLinkInfo.ulStreamClockHz == 0x00)
        {
            DebugMessageDpRx("DP MAC RX1: Stream Clk is invalid", 0);

            return;
        }

        // 1 Line = HTotal * (1/2 Link Clock) / Stream Clock
        ulBStoVSDelayDelta = ScalerGlobalComputeDwordMulDiv((DWORD)pstDpInfo->stDpTimingInfo.usHTotal, pstDpInfo->stDpLinkInfo.ulLinkClockHz / 2, pstDpInfo->stDpLinkInfo.ulStreamClockHz);

        DebugMessageDpRx("7. DP MAC RX1: Fifo Overflow --> nVidia Case", ulBStoVSDelayDelta);
    }
    else if(ScalerGetBit(P70_21_PG_CTRL_1, _BIT1) == _BIT1) // Fifo Underflow
    {
        if(pstDpInfo->stDpTimingInfo.usHWidth != 1366)
        {
            return;
        }

        PDATA_WORD(0) = pstDpInfo->stDpTimingInfo.usHWidth - 2;

        // Set HWidth
        ScalerSetByte(P70_14_MN_DPF_HWD_M, HIBYTE(PDATA_WORD(0)));
        ScalerSetByte(P70_15_MN_DPF_HWD_L, LOBYTE(PDATA_WORD(0)));

        // BS2BS Delta = 2 * (1/2 Link Clock) / Stream Clock
        ulBStoVSDelayDelta = pstDpInfo->stDpLinkInfo.ulLinkClockHz / pstDpInfo->stDpLinkInfo.ulStreamClockHz;

        DebugMessageDpRx("7. DP MAC RX1: Fifo Underflow --> QD882 Case", ulBStoVSDelayDelta);
    }

    // Get BStoVSDelay of Even Field
    PDATA_DWORD(0) = TO_DWORD(0,
                              ScalerGetByte(P70_30_EVBLK2VS_H),
                              ScalerGetByte(P70_31_EVBLK2VS_M),
                              ScalerGetByte(P70_32_EVBLK2VS_L));

    // Get BStoVSDelay of Odd Field
    PDATA_DWORD(1) = TO_DWORD(0,
                              ScalerGetByte(P70_33_OVBLK2VS_H),
                              ScalerGetByte(P70_34_OVBLK2VS_M),
                              ScalerGetByte(P70_35_OVBLK2VS_L));

    // BStoVSDelay of Even Field = BStoVSDelay of Even Field - BStoVSDelayDelta
    PDATA_DWORD(0) -= ulBStoVSDelayDelta;

    // BStoVSDelay of Odd Field = BStoVSDelay of Odd Field - BStoVSDelayDelta
    PDATA_DWORD(1) -= ulBStoVSDelayDelta;

    // Set Even Field BS to VS Delay
    ScalerSetByte(P70_30_EVBLK2VS_H, (BYTE)(PDATA_DWORD(0) >> 16));
    ScalerSetByte(P70_31_EVBLK2VS_M, (BYTE)(PDATA_DWORD(0) >> 8));
    ScalerSetByte(P70_32_EVBLK2VS_L, (BYTE)(PDATA_DWORD(0) >> 0));

    // Set Odd Field BS to VS Delay
    ScalerSetByte(P70_33_OVBLK2VS_H, (BYTE)(PDATA_DWORD(1) >> 16));
    ScalerSetByte(P70_34_OVBLK2VS_M, (BYTE)(PDATA_DWORD(1) >> 8));
    ScalerSetByte(P70_35_OVBLK2VS_L, (BYTE)(PDATA_DWORD(1) >> 0));

    // Reset Display Format Gen
    ScalerSetBit(P70_00_DPF_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(P70_00_DPF_CTRL_0, ~_BIT7, _BIT7);

    // Polling Vertical BS
    ScalerTimerPollingFlagProc(50, P75_01_DP_VBID, _BIT0, _TRUE);

#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
    if(GET_DP_MAC_STREAM_RX1_JUDGE_OOR() == _TRUE)
    {
        // Get 1 Frame Time for Vfreq = 5Hz, unit is ms
        ucOneFrameTime = 250;
    }
    else
#endif
    {
        // Get 1 Frame Time, unit is ms
        ucOneFrameTime = pstDpInfo->stDpLinkInfo.ulVBsToBsCountN / _GDIPHY_RX_GDI_CLK_KHZ + 1;
    }

    // Delay 1 Frame Time for PG Stable
    ScalerTimerDelayXms(ucOneFrameTime);
}

//--------------------------------------------------------
// Description  : Wait for Vertical Blanking for 128B/132B
// Input Value  : BYTE ucOneFrameTime
// Output Value : None
//--------------------------------------------------------
void ScalerDpMacStreamRx1WaitVBlanking_128B132B(BYTE ucOneFrameTime)
{
    WORD usTemp = 0;

    // Unit In 100us (Polling Interval)
    WORD usTwoFrameCounter = (WORD)ucOneFrameTime * 10 * 2;

    if(ScalerGetBit(P75_01_DP_VBID, _BIT0) == _BIT0)
    {
        while((ScalerGetBit(P75_01_DP_VBID, _BIT0) == _BIT0) && (usTemp < usTwoFrameCounter))
        {
            DELAY_XUS(100);

            usTemp += 1;
        }

        usTemp = 0;

        while((ScalerGetBit(P75_01_DP_VBID, _BIT0) == 0x00) && (usTemp < usTwoFrameCounter))
        {
            DELAY_XUS(100);

            usTemp += 1;
        }
    }
    else
    {
        while((ScalerGetBit(P75_01_DP_VBID, _BIT0) == 0x00) && (usTemp < usTwoFrameCounter))
        {
            DELAY_XUS(100);

            usTemp += 1;
        }
    }
}

//--------------------------------------------------
// Description  : Sdp Change Dtect
// Input Value  : Dp Sdp Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpChgDetect_128b132b(EnumDpSdpType enumDpSdpType)
{
    BYTE ucInfoFrameVersion = 0;

    ucInfoFrameVersion = ucInfoFrameVersion;

    switch(enumDpSdpType)
    {
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _DP_SDP_TYPE_INFOFRAME_SPD:
        {
            bit bAmdSdpInfolocalDimmingDisableControl = 0;

            bAmdSdpInfolocalDimmingDisableControl = (bit)(GET_DP_MAC_STREAM_RX1_AMD_SPD_INFO(_SPD_INFO_SEAMLESS_LOCAL_DIMMING_DISABLE_CONTROL));

            if((ScalerGetBit(P75_2D_DP_SDP_SPD_CHG, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00) || (bAmdSdpInfolocalDimmingDisableControl != GET_DP_MAC_STREAM_RX1_AMD_SPD_LOCAL_DIMMING()))
            {
                ScalerSetBit(P75_2D_DP_SDP_SPD_CHG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                SET_DP_MAC_STREAM_RX1_AMD_SPD_LOCAL_DIMMING(bAmdSdpInfolocalDimmingDisableControl);

                SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE();

                ucInfoFrameVersion = (ScalerDpMacStreamRx1GetSdpInfoHB3(_DP_SDP_TYPE_INFOFRAME_SPD) >> 2);

                if(GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_VERSION() != ucInfoFrameVersion)
                {
                    SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_VERSION(ucInfoFrameVersion);

                    SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE_EVENT(_SDP_EVENT_HEADER_CHANGE);
                }
                else
                {
                    SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE_EVENT(_SDP_EVENT_DATA_CHANGE);
                }
            }
            else
            {
                CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE();
            }

            break;
        }
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        case _DP_SDP_TYPE_ADAPTIVESYNC:

            if(ScalerGetBit(P75_24_DP_SDP_ADP_SYNC_CTRL_0, (_BIT6 | _BIT4)) != 0x00)
            {
                ScalerSetBit(P75_24_DP_SDP_ADP_SYNC_CTRL_0, ~(_BIT6 | _BIT4 | _BIT3), (_BIT6 | _BIT4));

                SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE();

                SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE_EVENT(_SDP_EVENT_HEADER_CHANGE);
            }
            else
            {
                CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE();
            }

            break;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_HDR:

            if(ScalerGetBit(P75_34_DP_SDP_HDR_INFO_MNT, (_BIT6 | _BIT4)) != 0x00)
            {
                ScalerSetBit(P75_34_DP_SDP_HDR_INFO_MNT, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

                SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE();

                ucInfoFrameVersion = (ScalerDpMacStreamRx1GetSdpInfoHB3(_DP_SDP_TYPE_INFOFRAME_HDR) >> 2);

                if(GET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_VERSION() != ucInfoFrameVersion)
                {
                    SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_VERSION(ucInfoFrameVersion);

                    SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE_EVENT(_SDP_EVENT_HEADER_CHANGE);
                }
                else
                {
                    SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE_EVENT(_SDP_EVENT_DATA_CHANGE);
                }
            }
            else
            {
                CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE();
            }

            break;
#endif

#if(_AUDIO_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_AUDIO:
        {
            BYTE pucAudioInfoSdpData[_HW_DP_SDP_PAYLOAD_LENGTH] = {0};

            ScalerDpMacStreamRx1GetSdpPktData(_DP_SDP_TYPE_INFOFRAME_AUDIO, pucAudioInfoSdpData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);

            if(memcmp(pucAudioInfoSdpData, g_pucDpMacRx1AudioInfoSdpData, _HW_DP_SDP_PAYLOAD_LENGTH) != 0)
            {
                memcpy(g_pucDpMacRx1AudioInfoSdpData, pucAudioInfoSdpData, _HW_DP_SDP_PAYLOAD_LENGTH);

                SET_DP_MAC_STREAM_RX1_AUDIO_INFO_FRAME_CHANGE();

                SET_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_CHANGE_EVENT(_SDP_EVENT_HEADER_CHANGE);
            }
            else
            {
                CLR_DP_MAC_STREAM_RX1_AUDIO_INFO_FRAME_CHANGE();
            }

            break;
        }
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)

        case _DP_SDP_TYPE_PPS:

            if(ScalerGetBit(P7E_BF_DP_PPS_RO_CTRL, _BIT6) == _BIT6)
            {
                ScalerSetBit(P7E_BF_DP_PPS_RO_CTRL, ~_BIT6, _BIT6);

                SET_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE();
            }
            else
            {
                CLR_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE();
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Sdp Receive Check
// Input Value  : Dp Sdp Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpRevDetect_128b132b(EnumDpSdpType enumDpSdpType)
{
    switch(enumDpSdpType)
    {
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
        case _DP_SDP_TYPE_INFOFRAME_SPD:

            if(ScalerGetBit(P75_2B_DP_SDP_SPD_CTRL, _BIT6) == _BIT6)
            {
                ScalerSetBit(P75_2B_DP_SDP_SPD_CTRL, ~_BIT6, _BIT6);

                SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE(_SDP_STATE_RECEIVED);
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE(_SDP_STATE_NOT_RECEIVED);
            }

            break;
#endif
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        case _DP_SDP_TYPE_ADAPTIVESYNC:

            if(ScalerGetBit(P75_24_DP_SDP_ADP_SYNC_CTRL_0, _BIT6) == _BIT6)
            {
                ScalerSetBit(P75_24_DP_SDP_ADP_SYNC_CTRL_0, ~(_BIT6 | _BIT4 | _BIT3), _BIT6);

                SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_RECEIVED_STATE(_SDP_STATE_RECEIVED);
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_RECEIVED_STATE(_SDP_STATE_NOT_RECEIVED);
            }

            break;
#endif
#if(_DP_HDR10_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_HDR:
        {
#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
            EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);

            if((ScalerDpRxGetDramReceiveFromDmDetect(enumInputPort) == _TRUE) || (ScalerGetBit(P75_33_DP_SDP_HDR_INFO_CTRL, _BIT6) == _BIT6))
#else
            if(ScalerGetBit(P75_33_DP_SDP_HDR_INFO_CTRL, _BIT6) == _BIT6)
#endif
            {
#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
                // if realtime OSD support DM
                if(ScalerDpRxGetOsdDmSupport(enumInputPort) == _ON)
                {
                    // clear FW flag only, don't w1c hdr received bit due to DM Detecting need
                    ScalerDpRxClrDramReceiveFromDmDetect(enumInputPort);
                }
                else
                {
                    ScalerSetBit(P75_33_DP_SDP_HDR_INFO_CTRL, ~_BIT6, _BIT6);
                }
#else
                ScalerSetBit(P75_33_DP_SDP_HDR_INFO_CTRL, ~_BIT6, _BIT6);
#endif
                SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_RECEIVED_STATE(_SDP_STATE_RECEIVED);
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_RECEIVED_STATE(_SDP_STATE_NOT_RECEIVED);
            }

            break;
        }
#endif
#if(_AUDIO_SUPPORT == _ON)
        case _DP_SDP_TYPE_INFOFRAME_AUDIO:

            if(ScalerGetBit(P75_E0_SDP_ACM_ISRC_INT, _BIT1) == _BIT1)
            {
                ScalerSetBit(P75_E0_SDP_ACM_ISRC_INT, ~(_BIT6 | _BIT5 | _BIT2 | _BIT1), _BIT1);

                SET_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_RECEIVED_STATE(_SDP_STATE_RECEIVED);
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_RECEIVED_STATE(_SDP_STATE_NOT_RECEIVED);
            }

            break;
#endif
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _DP_SDP_TYPE_PPS:

            // Check SDP PPS Received Status
            if(ScalerGetBit(P75_E7_DP_MAC_PPS_DYN_MDATA_CTRL, _BIT6) == _BIT6)
            {
                ScalerSetBit(P75_E7_DP_MAC_PPS_DYN_MDATA_CTRL, ~(_BIT6 | _BIT4), _BIT6);

                SET_DP_MAC_STREAM_RX1_PPS_SDP_RECEIVED_STATE(_SDP_STATE_RECEIVED);
            }
            else
            {
                SET_DP_MAC_STREAM_RX1_PPS_SDP_RECEIVED_STATE(_SDP_STATE_NOT_RECEIVED);
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DSC Get PPS Packet Byte
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1GetPpsSdpInfo_128b132b(void)
{
    // Backup The DSC PPS with Picture Height
    SET_DP_MAC_STREAM_RX1_DSC_PIC_HEIGHT((WORD)ScalerGetByte(P7E_B6_DP_PPS_RO_DATA_BYTE_6) << 8 | ScalerGetByte(P7E_B7_DP_PPS_RO_DATA_BYTE_7));

    // Backup The DSC PPS with Picture Width
    SET_DP_MAC_STREAM_RX1_DSC_PIC_WIDTH((WORD)ScalerGetByte(P7E_B8_DP_PPS_RO_DATA_BYTE_8) << 8 | ScalerGetByte(P7E_B9_DP_PPS_RO_DATA_BYTE_9));

    // Backup The DSC PPS with Slice Height
    SET_DP_MAC_STREAM_RX1_DSC_SLICE_HEIGHT((WORD)ScalerGetByte(P7E_BA_DP_PPS_RO_DATA_BYTE_10) << 8 | ScalerGetByte(P7E_BB_DP_PPS_RO_DATA_BYTE_11));

    // Backup The DSC PPS with Slice Width
    SET_DP_MAC_STREAM_RX1_DSC_SLICE_WIDTH((WORD)ScalerGetByte(P7E_BC_DP_PPS_RO_DATA_BYTE_12) << 8 | ScalerGetByte(P7E_BD_DP_PPS_RO_DATA_BYTE_13));

    // Backup The DSC PPS with BPP
    SET_DP_MAC_STREAM_RX1_DSC_COLOR_BPP(((WORD)ScalerGetByte(P7E_B5_DP_PPS_RO_DATA_BYTE_4) & 0x03) << 8 | ScalerGetByte(P7E_B0_DP_PPS_RO_CONFIG_DATA_0));

    // Backup The DSC PPS with BPC
    SET_DP_MAC_STREAM_RX1_DSC_COLOR_BPC((ScalerGetByte(P7E_B4_DP_PPS_RO_DATA_BYTE_3) & 0xF0) >> 4);

    // Backup The DSC PPS with Native 420
    SET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_420((ScalerGetByte(P7E_BE_DP_PPS_RO_DATA_BYTE_88) & _BIT1) >> 1);

    // Backup The DSC PPS with Native 422
    SET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_422((ScalerGetByte(P7E_BE_DP_PPS_RO_DATA_BYTE_88) & _BIT0) >> 0);

    // Backup The DSC PPS with Simple 422
    SET_DP_MAC_STREAM_RX1_DSC_COLOR_SIMPLE_422((ScalerGetByte(P7E_B5_DP_PPS_RO_DATA_BYTE_4) & _BIT3) >> 3);
}

//--------------------------------------------------
// Description  : Clr Sdp Ram
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpSramReset_128b132b(void)
{
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
    // Reset Spd Sdp Sram
    ScalerSetBit(P75_2B_DP_SDP_SPD_CTRL, ~(_BIT6 | _BIT0), _BIT0);
    ScalerSetBit(P75_2B_DP_SDP_SPD_CTRL, ~(_BIT6 | _BIT0), 0x00);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
    // Reset Hdr Sdp Sram
    ScalerSetBit(P75_33_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT0), _BIT0);
    ScalerSetBit(P75_33_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT0), 0x00);
#endif

#if(_AUDIO_SUPPORT == _ON)
    // Reset Isrc Sdp Sram
    ScalerSetBit(P75_E0_SDP_ACM_ISRC_INT, ~(_BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P75_E0_SDP_ACM_ISRC_INT, ~(_BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif

#if((_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    // Reset Rsv0 Sdp Sram
    ScalerSetBit(P75_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT4), _BIT4);
    ScalerSetBit(P75_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT4), 0x00);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    // Reset Adaptivsync Sdp Sram
    ScalerSetBit(P75_24_DP_SDP_ADP_SYNC_CTRL_0, ~(_BIT6 | _BIT4 | _BIT3), _BIT4);
    ScalerSetBit(P75_24_DP_SDP_ADP_SYNC_CTRL_0, ~(_BIT6 | _BIT4 | _BIT3), 0x00);
#endif
}

//--------------------------------------------------
// Description  : DP Rx1 Set Clr Status Flag
// Input Value  : Dp Sdp Ram Index
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetSdpInitStatus_128b132b(EnumDpSdpRamIndex enumDpSdpRamIndex)
{
    switch(enumDpSdpRamIndex)
    {
        case _DP_SDP_BUFF_SPD:

            // Clr SPD Received Flag, Reset Sdp
            ScalerSetBit(P75_2B_DP_SDP_SPD_CTRL, ~(_BIT6 | _BIT0), (_BIT6 | _BIT0));
            ScalerSetBit(P75_2B_DP_SDP_SPD_CTRL, ~(_BIT6 | _BIT0), 0x00);

            // Clr SPD Chg Flag
            ScalerSetByte(P75_2D_DP_SDP_SPD_CHG, 0xFF);

            // Set Info Data Byte Re-mapping
            ScalerSetBit(P75_2B_DP_SDP_SPD_CTRL, ~(_BIT6 | _BIT4), _BIT4);

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
            CLR_DP_MAC_STREAM_RX1_SPD_IFNOFRAME_DETECTING();
            CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE();
            CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_VERSION();
            CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE_EVENT();
            CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE();
            SET_DP_MAC_STREAM_RX1_AMD_SPD_LOCAL_DIMMING(_FALSE);
#endif
            break;

        case _DP_SDP_BUFF_HDR:

            // Clr HDR Received Flag, Reset Sdp
            ScalerSetBit(P75_33_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT0), (_BIT6 | _BIT0));
            ScalerSetBit(P75_33_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT0), 0x00);

            // Clr HDR Chg Flag
            ScalerSetBit(P75_34_DP_SDP_HDR_INFO_MNT, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

            // Set Info Data Byte Re-mapping
            ScalerSetBit(P75_33_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT4), _BIT4);

#if(_DP_HDR10_SUPPORT == _ON)
            CLR_DP_MAC_STREAM_RX1_HDR_IFNOFRAME_DETECTING();
            CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE();
            CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_VERSION();
            CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE_EVENT();
            CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_RECEIVED_STATE();
#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
            ScalerDpRxClrDramReceiveFromDmDetect(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1));
#endif
#endif

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
            CLR_DP_MAC_STREAM_RX1_DM_DRAM_INFO_FRAME_RECEIVED();
#endif
            break;

        // Audio Infoframe use ISRC SDP buff
        case _DP_SDP_BUFF_ISRC:

            // Clr ISRC Flag, Reset Sdp
            ScalerSetBit(P75_E0_SDP_ACM_ISRC_INT, ~(_BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(P75_E0_SDP_ACM_ISRC_INT, ~(_BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_AUDIO_SUPPORT == _ON)
            // Initial Audio Info Sdp Data
            memset(g_pucDpMacRx1AudioInfoSdpData, 0, 32);

            CLR_DP_MAC_STREAM_RX1_AUDIO_IFNOFRAME_DETECTING();
            CLR_DP_MAC_STREAM_RX1_AUDIO_INFO_FRAME_CHANGE();
            CLR_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_CHANGE_EVENT();
            CLR_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_RECEIVED_STATE();
#endif
            break;

        case _DP_SDP_BUFF_RSV0:

            // Disable RSV0 Ram Receive IRQ
            ScalerDpMacStreamRx1SdpIrqEnable_128b132b(_DP_SDP_BUFF_RSV0, _DISABLE);

            // Clr RSV0 Received Flag, Reset Sdp
            ScalerSetBit(P75_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));
            ScalerSetBit(P75_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT4), 0x00);

#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
            CLR_DP_MAC_STREAM_RX1_ADVANCED_HDR10_DETECTING();
            CLR_DP_MAC_STREAM_RX1_ADVANCED_HDR10_RECEIVED_STATE();
#endif

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
            CLR_DP_MAC_STREAM_RX1_DM_VSIF_DETECTING();
            CLR_DP_MAC_STREAM_RX1_DM_VSIF_RECEIVED_STATE();
#endif
            break;

        case _DP_SDP_BUFF_ADAPTIVESYNC:

            // Clr Adaptivsync Received Flag & Chg Flag, Reset Sdp
            ScalerSetBit(P75_24_DP_SDP_ADP_SYNC_CTRL_0, ~(_BIT6 | _BIT4 | _BIT3), (_BIT6 | _BIT4 | _BIT3));
            ScalerSetBit(P75_24_DP_SDP_ADP_SYNC_CTRL_0, ~(_BIT6 | _BIT4 | _BIT3), 0x00);

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
            CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_DETECTING();
            CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE();
            CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_VERSION();
            CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE_EVENT();
            CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_RECEIVED_STATE();
#endif
            break;

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        case _DP_SDP_BUFF_PPS:

            // Clr PPS Received Flag
            ScalerSetBit(P75_E7_DP_MAC_PPS_DYN_MDATA_CTRL, ~(_BIT6 | _BIT4), _BIT6);

            // Clr PPS Chg Flag
            ScalerSetBit(P7E_BF_DP_PPS_RO_CTRL, ~_BIT6, _BIT6);

            CLR_DP_MAC_STREAM_RX1_PPS_SDP_DETECTING();
            CLR_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE();
            CLR_DP_MAC_STREAM_RX1_PPS_SDP_RECEIVED_STATE();

            break;
#endif

        default:
            break;
    }
}

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
//----------------------------------------------------------------------
// Description  : Set SDP Meta Sram Rcv Mode
// Input Value  : enumDpSdpMetaIndex/enumDpSdpType/enumDpSdpMetaRcvMd
// Output Value : None
//----------------------------------------------------------------------
void ScalerDpMacStreamRx1SetSdpMetaSramRcvMode_128b132b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, EnumDpSdpType enumDpSdpType, EnumDpSdpMetaRcvMd enumDpSdpMetaRcvMd)
{
    switch(enumDpSdpMetaIndex)
    {
        case _DP_SDP_META_0:

            // Set SDP0 SRAM Receive SDP HB1
            ScalerSetByte(P7E_D0_META_SDP0_TYPE, enumDpSdpType);

            // Set SDP0 SRAM Receive Mode(Chain or No-chain)
            ScalerSetBit(P7E_D5_META_SDP0_CTRL1, ~_BIT5, enumDpSdpMetaRcvMd << 5);

            break;

        case _DP_SDP_META_1:

            // Set SDP1 SRAM Receive SDP HB1
            ScalerSetByte(P7E_D1_META_SDP1_TYPE, enumDpSdpType);

            // Set SDP1 SRAM Receive Mode(Chain or No-chain)
            ScalerSetBit(P7E_D6_META_SDP1_CTRL1, ~_BIT5, enumDpSdpMetaRcvMd << 5);

            break;

        case _DP_SDP_META_2:

            // Set SDP2 SRAM Receive SDP HB1
            ScalerSetByte(P7E_D2_META_SDP2_TYPE, enumDpSdpType);

            // Set SDP2 SRAM Receive Mode(Chain or No-chain)
            ScalerSetBit(P7E_D7_META_SDP2_CTRL1, ~_BIT5, enumDpSdpMetaRcvMd << 5);

            break;

        case _DP_SDP_META_3:

            // Set SDP3 SRAM Receive SDP HB1
            ScalerSetByte(P7E_D3_META_SDP3_TYPE, enumDpSdpType);

            // Set SDP3 SRAM Receive Mode(Chain or No-chain)
            ScalerSetBit(P7E_D8_META_SDP3_CTRL1, ~_BIT5, enumDpSdpMetaRcvMd << 5);

            break;

        case _DP_SDP_META_4:

            // Set SDP4 SRAM Receive SDP HB1
            ScalerSetByte(P7E_D4_META_SDP4_TYPE, enumDpSdpType);

            // Set SDP4 SRAM Receive Mode(Chain or No-chain)
            ScalerSetBit(P7E_D9_META_SDP4_CTRL1, ~_BIT5, enumDpSdpMetaRcvMd << 5);

            break;

        default:
            break;
    }

    ScalerDpMacStreamRx1SdpMetaSramIrqEnable_128b132b(enumDpSdpMetaIndex, _ENABLE);
}

//----------------------------------------------------------------
// Description  : Enable/Disable SDP Meta Sram IRQ
// Input Value  : enumDpSdpMetaIndex, ENABLE/DISABLE bit
// Output Value : None
//----------------------------------------------------------------
void ScalerDpMacStreamRx1SdpMetaSramIrqEnable_128b132b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, bit bEnable)
{
    switch(enumDpSdpMetaIndex)
    {
        case _DP_SDP_META_0:

            if(bEnable == _ENABLE)
            {
                // Set Meta SDP0 Rcv Done IRQ Enable
                ScalerSetBit(P7E_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P7E_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }
            else
            {
                // Set Meta SDP0 Rcv Done IRQ Disable
                ScalerSetBit(P7E_DA_META_SDP0_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

            break;

        case _DP_SDP_META_1:

            if(bEnable == _ENABLE)
            {
                // Set Meta SDP1 Rcv Done IRQ Enable
                ScalerSetBit(P7E_DB_META_SDP1_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P7E_DB_META_SDP1_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }
            else
            {
                // Set Meta SDP1 Rcv Done IRQ Disable
                ScalerSetBit(P7E_DB_META_SDP1_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

            break;

        case _DP_SDP_META_2:

            if(bEnable == _ENABLE)
            {
                // Set Meta SDP2 Rcv Done IRQ Enable
                ScalerSetBit(P7E_DC_META_SDP2_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P7E_DC_META_SDP2_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }
            else
            {
                // Set Meta SDP2 Rcv Done IRQ Disable
                ScalerSetBit(P7E_DC_META_SDP2_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

            break;

        case _DP_SDP_META_3:

            if(bEnable == _ENABLE)
            {
                // Set Meta SDP3 Rcv Done IRQ Enable
                ScalerSetBit(P7E_DD_META_SDP3_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P7E_DD_META_SDP3_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }
            else
            {
                // Set Meta SDP3 Rcv Done IRQ Disable
                ScalerSetBit(P7E_DD_META_SDP3_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

            break;

        case _DP_SDP_META_4:

            if(bEnable == _ENABLE)
            {
                // Set Meta SDP4 Rcv Done IRQ Enable
                ScalerSetBit(P7E_DE_META_SDP4_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                ScalerSetBit(P7E_DE_META_SDP4_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }
            else
            {
                // Set Meta SDP4 Rcv Done IRQ Disable
                ScalerSetBit(P7E_DE_META_SDP4_CTRL2, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Enable/Disable SDP IRQ_en
// Input Value  : RSV Number, ENABLE/DISABLE bit
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SdpIrqEnable_128b132b(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable)
{
    switch(enumDpSdpRamIndex)
    {
        case _DP_SDP_BUFF_HDR:

            if(bEnable == _ENABLE)
            {
                // Set HDR IRQ Enable
                ScalerSetBit(P75_33_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT5), _BIT5);
            }
            else
            {
                // Set HDR IRQ Disable
                ScalerSetBit(P75_33_DP_SDP_HDR_INFO_CTRL, ~(_BIT6 | _BIT5), 0x00);
            }

            break;

        case _DP_SDP_BUFF_RSV0:

            if(bEnable == _ENABLE)
            {
                // Set RSV0 IRQ Enable
                ScalerSetBit(P75_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT5), _BIT5);
            }
            else
            {
                // Set RSV0 IRQ Disable
                ScalerSetBit(P75_F3_DP_SDP_RSV0_CTRL, ~(_BIT6 | _BIT5), 0x00);
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Rx1 SDP Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetSdpReset_128b132b(void)
{
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
    ScalerDpMacStreamRx1SetSdpInitStatus_128b132b(_DP_SDP_BUFF_SPD);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    ScalerDpMacStreamRx1SetSdpInitStatus_128b132b(_DP_SDP_BUFF_ADAPTIVESYNC);
#endif

#if((_DP_HDR10_SUPPORT == _ON) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    ScalerDpMacStreamRx1SetSdpInitStatus_128b132b(_DP_SDP_BUFF_HDR);
#endif

#if((_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON) || (_DP_MAC_RX1_DM_SUPPORT == _ON))
    ScalerDpMacStreamRx1SetSdpInitStatus_128b132b(_DP_SDP_BUFF_RSV0);
#endif

#if(_AUDIO_SUPPORT == _ON)
    ScalerDpMacStreamRx1SetSdpInitStatus_128b132b(_DP_SDP_BUFF_ISRC);
#endif
}

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
//--------------------------------------------------
// Description  : Set First Be Irq 128b132b
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1Set1stBeIrqEnable_128b132b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Clr BE_1st Flag and Enable IRQ
        ScalerSetBit_EXINT(P7E_E0_META_SRAM_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT0), _BIT2);
        ScalerSetBit_EXINT(P7E_E0_META_SRAM_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT0), _BIT3);
    }
    else
    {
        // Clr Flag and Disable BE_1st Int
        ScalerSetBit_EXINT(P7E_E0_META_SRAM_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT0), _BIT2);
    }
}
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Judge Output Cable No. is Dual or not
// Input Value  : None
// Output Value : _TRUE or _FLASE
//--------------------------------------------------
bit ScalerDpMacStreamRx1DualCableJudge_128b132b(void)
{
    WORD usHwidth = 0;
    WORD usVHeight = 0;

    usHwidth = (((WORD)ScalerGetByte(P75_14_MSA_HWD_0) << 8) | ScalerGetByte(P75_15_MSA_HWD_1));
    usVHeight = (((WORD)ScalerGetByte(P75_1C_MSA_VHT_0) << 8) | ScalerGetByte(P75_1D_MSA_VHT_1));

    // Make sure the MSA Value is Valid
    if((usHwidth == 0) || (usVHeight == 0))
    {
        return _FALSE;
    }

    // For Normal Aspect Ratio
    if(usHwidth < usVHeight)
    {
        return _TRUE;
    }
    else
    {
        PDATA_WORD(0) = ((DWORD)usHwidth * 100 / usVHeight);

        // For 21:9 Aspect
        if((PDATA_WORD(0) > 115) && (PDATA_WORD(0) < 120))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}
#endif

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Watch Dog
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscSetStreamWD_128b132b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // DSC VB-ID[6] Watch Dog Setting
        ScalerSetBit(P75_38_DP_WD_CTRL_0, ~_BIT2, _BIT2);
    }
    else
    {
        // DSC VB-ID[6] Watch Dog Setting
        ScalerSetBit(P75_38_DP_WD_CTRL_0, ~_BIT2, 0x00);

        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
    }
}

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] IRQ
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscSetStreamIRQ_128b132b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // DSC VB-ID[6] IRQ Setting
        ScalerSetBit(P75_3A_DP_IRQ_CTRL0, ~_BIT2, _BIT2);
    }
    else
    {
        // DSC VB-ID[6] IRQ Setting
        ScalerSetBit(P75_3A_DP_IRQ_CTRL0, ~_BIT2, 0x00);

        // Write 1 Clear DSC VB-ID[6]
        ScalerSetBit(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
    }
}

//--------------------------------------------------
// Description  : DP DSC Chunk Length Check
// Input Value  : enumInputPort, PPS Chunk Length, PPS Slice Count
// Output Value : FALSE => Measure Check Fail
//--------------------------------------------------
bit ScalerDpMacStreamRx1DscChunkLengthCheck_128b132b(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt)
{
    enumInputPort = enumInputPort;

    // Set DP Measure DSC Chunk Length Type: DP MAC measure Main Link DSC Chunk Length Cycle
    ScalerSetBit(P70_4E_VIDEO_EN_CNT_2, ~_BIT7, _BIT7);

    // Start to Measure DSC Chunk Length Counter by GDI Clock
    ScalerSetBit(P70_40_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), 0x00);
    ScalerSetBit(P70_40_MN_MEAS_CTRL, ~(_BIT7 | _BIT5), _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, P70_4E_VIDEO_EN_CNT_2, _BIT5, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Get Measure DSC Chunk Length Counts
    PDATA_WORD(0) = ScalerGetWord(P70_4C_VIDEO_EN_CNT_0);

    // DP MAC measure Main Link DSC Chunk Length Cycle: (cycle of main link * 16) / slice
    PDATA_WORD(0) = ((DWORD)PDATA_WORD(0) << 4) / ucDscPpsSliceCnt;

    // Clear Measure Video Count Mode
    ScalerSetBit(P70_4E_VIDEO_EN_CNT_2, ~(_BIT7 | _BIT5 | _BIT3), 0x00);

    // Disable Measure Block
    ScalerSetBit(P70_40_MN_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Check DSC Chunk Length
    if((PDATA_WORD(0) < usDscPpsChunkLength) || (ABSDWORD(PDATA_WORD(0), usDscPpsChunkLength) > 16))
    {
        DebugMessageDSC("DSC Chunk Size Mismatch", PDATA_WORD(0));

        return _FALSE;
    }

    return _TRUE;
}
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Change Check
// Input Value  : None
// Output Value : False --> CompressionStream_Flag VB-ID[6] Changed and Video Stream without Compression
//--------------------------------------------------
bit ScalerDpMacStreamRx1DscStreamChangeCheck_128b132b(void)
{
    // Check DSC Compression Stream Flag
    if(ScalerGetBit(P75_37_DP_GLB_STATUS, _BIT1) == _BIT1)
    {
        // Clear DSC Stream Change Flag
        ScalerSetBit(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        return _TRUE;
    }

    return _FALSE;
}
#endif

#if((_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Mac Tx DSC Pass-Through Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1DscStatusReset_128b132b(void)
{
    DebugMessageMst("MST2SST DSC PassThrough Reset !!!", 0x00);

    // Clear DSC Stream Change Flag
    ScalerSetBit(P75_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

    // Clear DSC PPS Change Flag
    ScalerSetBit(P7E_BF_DP_PPS_RO_CTRL, ~_BIT6, _BIT6);
}
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DP Color Sapace Change WD
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetColorSpaceChangeWD_128b132b(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Clear flag
        ScalerSetByte(P7E_96_DP_MSA_COLOR_CTRL1, _BIT7);

        // Enable Color Sapace Change WD
        ScalerSetBit(P7E_96_DP_MSA_COLOR_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
    }
    else
    {
        // Disable Color Sapace Change WD
        ScalerSetBit(P7E_96_DP_MSA_COLOR_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Clear flag
        ScalerSetByte(P7E_96_DP_MSA_COLOR_CTRL1, _BIT7);
    }
}
#endif
#endif // End of #if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

#endif
