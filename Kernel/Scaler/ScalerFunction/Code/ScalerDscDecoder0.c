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
// ID Code      : ScalerDscDecoder0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DSC0__

#include "ScalerFunctionInclude.h"
#include "DscDecoder0/ScalerDscDecoder0.h"

#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructDscMacInfo g_stDscDecoder0MacInfo;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DSC0 Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0Initial(void)
{
    ScalerDscDecoder0MacReset();

    // DP DSC Friendly Setting: PPS Byte Swap, Data Byte No Swap, Set DP Mode, Clear PPS Active Flag, Set DSC PPS Update Mode: All PPS Updated
    ScalerSetByte(P7_00_DSC_DEC_CTRL_00, (_BIT6 | _BIT2));

    // Set DSC Pixel Clk Source Selection
    ScalerSetBit(P7_01_DSC_DEC_CTRL_01, ~_BIT5, (_HW_DSC_MAC_CLK_SOURCE) << 5);

#if(_DP_PR_MODE_SUPPORT == _ON)
    // Set DSC FIFO Detect Reference From PR Mode
    ScalerSetBit(P7_02_DSC_IRQ_CTRL0, ~(_BIT6 | _BIT4 | _BIT1 | _BIT0), _BIT4);
#endif

    // Avoid DSC Vertical Slice Corruption
    ScalerSetBit(P7_11_DSC_DECODER_OPTION, ~_BIT3, _BIT3);

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    // Set DSC ALPM Setting
    ScalerSetBit(P7_15_DSC_DECDER_ALPM, ~_BIT6, _BIT6);
#endif

    // Set DSC CRC Setting
    ScalerSetBit(P7_17_DSC_DECODER_CRC, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1), 0x00);
}

//--------------------------------------------------
// Description  : DSC0 Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0MacReset(void)
{
    // Enable DSC Watch Dog Force To Background
    ScalerDscDecoder0SetForceToBackGround(_ENABLE);

    // Disable Display Format Generator
    ScalerSetBit(P7_30_DPF_CTRL_0, ~_BIT7, 0x00);

    // Disable DSC Decoder, Clear Force PPS Active Enable
    ScalerSetBit(P7_00_DSC_DEC_CTRL_00, ~(_BIT7 | _BIT3 | _BIT0), 0x00);

    // Clear Merge Buffer and DSC 2X Speed
    ScalerSetBit(P7_01_DSC_DEC_CTRL_01, ~(_BIT2 | _BIT0), 0x00);

    // Clear Output UV(RB) Swap
    ScalerSetBit(P7_04_DSC_OUT_FORMAT, ~(_BIT6 | _BIT4), 0x00);

    // Reset Disply Format Block
    ScalerSetBit(P7_2F_MAC_DIG_RESET_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(P7_2F_MAC_DIG_RESET_CTRL, ~_BIT7, 0x00);

    // Disable DSC Fifo Under/OverFlow Watch Dog
    ScalerDscDecoder0SetFifoWD(_DISABLE);

    // Disable DSC Fifo Under/OverFlow IRQ
    ScalerDscDecoder0SetFifoIRQ(_DISABLE);

    SET_DRR_DSC0_ENABLED(_DISABLE);

#if(_FW_DP_DSC_MUTE_INSTANT_RECOVER_SUPPORT == _ON)
    CLR_DSC0_FORCE_BG_ENABLE();
#endif
}

//--------------------------------------------------
// Description  : DSC0 Set DSC Decode Type
// Input Value  : enumPortType
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0SetDecodeType(void)
{
    EnumInputPort enumInputPort = ScalerDscDecoderGetDxInputPort(_DSC_MAC_0);
    EnumPortType enumPortType = ScalerSyncGetPortType(enumInputPort);

    switch(enumPortType)
    {
#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            // Disable PPS Byte Swap, Enable Data Byte Swap, Set DSC HDMI Decode Mode, Clear PPS Active Flag,
            ScalerSetBit(P7_00_DSC_DEC_CTRL_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0), (_BIT5 | _BIT4));
#endif
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            // Enable PPS Byte Swap, Disable Data Byte Swap, Set DSC DP Decode Mode
            ScalerSetBit(P7_00_DSC_DEC_CTRL_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT6);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                // Set DSC DP Decode New Mode For 128b132b
                ScalerSetBit(P7_01_DSC_DEC_CTRL_01, ~_BIT4, _BIT4);
            }
            else
#endif
            {
                // Set DSC DP Decode Old Mode For 8b10b
                ScalerSetBit(P7_01_DSC_DEC_CTRL_01, ~_BIT4, 0x00);
            }

#endif
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Enable DSC Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0SetFifoIRQ(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Clear DSC Handshaked Related IRQ : PPS Identifier Changed / DSC Overflow and Underflow
        ScalerSetBit(P7_02_DSC_IRQ_CTRL0, ~(_BIT6 | _BIT1 | _BIT0), (_BIT6 | _BIT1 | _BIT0));

        // Enable DSC Handshaked Related IRQ : PPS Identifier Changed / DSC Overflow and Underflow
        ScalerSetBit(P7_02_DSC_IRQ_CTRL0, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
    }
    else
    {
        // Clear DSC Handshaked Related IRQ : PPS Identifier Changed / DSC Overflow and Underflow
        ScalerSetBit(P7_02_DSC_IRQ_CTRL0, ~(_BIT6 | _BIT1 | _BIT0), (_BIT6 | _BIT1 | _BIT0));

        // Disable DSC Handshaked Related IRQ : PPS Identifier Changed / DSC Overflow and Underflow
        ScalerSetBit(P7_02_DSC_IRQ_CTRL0, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : Check DSC Fifo Under/OverFlow IRQ Enable Status
// Input Value  : NONE
// Output Value : True, False
//--------------------------------------------------
bit ScalerDscDecoder0CheckFifoIRQ(void)
{
    return (ScalerGetBit(P7_02_DSC_IRQ_CTRL0, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2));
}

//--------------------------------------------------
// Description  : Check DSC Fifo Under/OverFlow IRQ Status
// Input Value  : NONE
// Output Value : True, False
//--------------------------------------------------
BYTE ScalerDscDecoder0GetFifoStatus(void)
{
    return (ScalerGetBit(P7_02_DSC_IRQ_CTRL0, (_BIT1 | _BIT0)));
}
//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow Watch Dog
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0SetFifoWD(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Enable DSC Watch Dog Force To Background
        ScalerSetBit(P7_05_DSC_WATCH_DOG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1), (_BIT7 | _BIT5 | _BIT4 | _BIT1));
    }
    else
    {
        // Disable DSC Watch Dog Force To Background
        ScalerSetBit(P7_05_DSC_WATCH_DOG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1), 0x00);
    }
}

//--------------------------------------------------
// Description  : Set DSC Force To BackGround Colors
// Input Value  : ucDscMac, bEn
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0SetForceToBackGround(bit bEn)
{
    if(bEn == _ENABLE)
    {
        ScalerSetBit(P7_05_DSC_WATCH_DOG, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    else
    {
        ScalerSetBit(P7_05_DSC_WATCH_DOG, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : DSC Decode0 Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0IntHandler_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDscDecoderGetDxInputPort_EXINT0(_DSC_MAC_0);
    EnumDpMacSel enumDpMacSel = ScalerDscDecoderGetDpMacRxxInput(_DSC_MAC_0);

#if(_FW_DP_DSC_MUTE_INSTANT_RECOVER_SUPPORT == _ON)
    EnumPortType enumPortType = ScalerSyncGetPortType(enumInputPort);
#endif

    if((ScalerGetBit_EXINT(P7_02_DSC_IRQ_CTRL0, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2)) &&
       (ScalerGetBit_EXINT(P7_02_DSC_IRQ_CTRL0, (_BIT1 | _BIT0)) != 0x00))
    {
        // Disable DSC Handshaked Related IRQ : PPS Identifier Changed / DSC Overflow and Underflow
        ScalerSetBit_EXINT(P7_02_DSC_IRQ_CTRL0, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_FW_DP_DSC_MUTE_INSTANT_RECOVER_SUPPORT == _ON)
        if(enumPortType == _PORT_DP)
        {
            // Enable D-domain force-to-background
            ScalerDDomainBackgroundEnable(ScalerDpMacStreamRxGetForceBackgroundPath_EXINT0(enumInputPort), _ENABLE);
        }
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
#if(_AUDIO_SUPPORT == _ON)
        // Disable INT for Auido and Reset Function
        ScalerDpMacDscAudioRxDisableSetting_EXINT0(enumDpMacSel);

        // Disable Audio FSM
        ScalerDpMacDscAudioEnable_EXINT0(enumDpMacSel, _DISABLE);
#endif

#if(_FW_DP_DSC_MUTE_INSTANT_RECOVER_SUPPORT == _ON)
        if(enumPortType == _PORT_HDMI)
#endif
        {
            // Set D Domain Region Free run/ Force to Background
            ScalerDDomainResetDDomainRgn(ScalerDpMacDscStreamRxGetForceBackgroundPath_EXINT0(enumDpMacSel));

            // Disable DP No Video Stream IRQ
            ScalerDpMacDscStreamRxSetNoVideoStreamIRQ_EXINT0(enumDpMacSel, _DISABLE);
        }

        // Set DP Receive Port0 Out of Sync
        ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);

        // Set DP Stream Regen Out of Sync
        ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_STREAM_REGENERATION_STATUS, _DP_SINK_OUT_OF_SYNC);
#endif

#if(_DP_TX_SUPPORT == _ON)
        if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE) && (ScalerDpMacTxCloneGetCurrentInputPort() == enumInputPort))
        {
#if(_FW_DP_DSC_MUTE_INSTANT_RECOVER_SUPPORT == _ON)
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
            // Check if DPTx is Not DSC PassThrough
            if(!((GET_DP_TX_DOWNSTREAM_DSC_SUPPORT() == _ENABLE) && (GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH() == _ENABLE)))
#endif
#endif
            {
                // Main Link switch to Idle Pattern
                ScalerDpMacTxForceIdlePattern_EXINT0();
            }
        }
#endif

#if(_FW_DP_DSC_MUTE_INSTANT_RECOVER_SUPPORT == _ON)
        if(enumPortType == _PORT_DP)
        {
            SET_DSC0_FORCE_BG_ENABLE();
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Initial Setting for DSC0 Scanning Port(Power Normal)
// Input Value  : SourceMac, SourceType
// Output Value : Source Type
//--------------------------------------------------
bit ScalerDscDecoder0MacScanInputPort(void)
{
    EnumPortType enumPortType = ScalerSyncGetPortType(ScalerDscDecoderGetDxInputPort(_DSC_MAC_0));

    StructDscTimingInfo stDscTimingInfo = {0};

    ScalerDscDecoder0SetDecodeType();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    // Read DSC0 PPS Value
    if(ScalerTimerPollingFlagProc(50, P7_00_DSC_DEC_CTRL_00, _BIT3, _TRUE) == _TRUE)
    {
        // Force DSC0 PPS Double Buffer Write
        ScalerSetBit(P7_00_DSC_DEC_CTRL_00, ~(_BIT7 | _BIT0), _BIT0);

        DebugMessageDSC("3. DSC0 PPS Apply", 0);

#if(_DP_RX_DSC_DECODER_SUPPORT == _TRUE)
        if(enumPortType == _PORT_DP)
        {
            ScalerDpMacDscPpsTimeOutProc(ScalerDscDecoderGetDpMacRxxInput(_DSC_MAC_0), _DISABLE);
        }
#endif
    }
    else
    {
#if(_DP_RX_DSC_DECODER_SUPPORT == _TRUE)
        if(enumPortType == _PORT_DP)
        {
            ScalerDpMacDscPpsTimeOutProc(ScalerDscDecoderGetDpMacRxxInput(_DSC_MAC_0), _ENABLE);

            if(GET_DSC0_COLOR_BPC_CURRENT() != 0)
            {
                // Force DSC0 PPS Double Buffer Write
                ScalerSetBit(P7_00_DSC_DEC_CTRL_00, ~(_BIT7 | _BIT0), _BIT0);

                DebugMessageDSC("3. DSC0 PPS Force Apply", 0);
            }
            else
            {
                DebugMessageDSC("3. DSC0 PPS not ready", 0);
                return _FALSE;
            }
        }
        else
#endif
        {
            DebugMessageDSC("3. DSC0 PPS not ready", 0);
            return _FALSE;
        }
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    if(ScalerDscDecoder0DecInfoCheck() == _FALSE)
    {
        DebugMessageDSC("3. DSC0 Dec info fail", 0);

        return _FALSE;
    }

    if(ScalerDscDecoder0TimingInfoCheck(&stDscTimingInfo) == _FALSE)
    {
        DebugMessageDSC("3. DSC0 Timing Check Fail", 0);

        return _FALSE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    if(ScalerDscDecoderStreamCheck(_DSC_MAC_0) == _FALSE)
    {
        DebugMessageDSC("3. DSC0 Video Stream Not Enable", 0);

        return _FALSE;
    }

    if(ScalerDscDecoder0StreamSetting(&stDscTimingInfo) == _TRUE)
    {
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
        if(enumPortType == _PORT_DP)
        {
            if(ScalerDpMacDscChunkCheckProc(ScalerDscDecoderGetDpMacRxxInput(_DSC_MAC_0)) == _FALSE)
            {
                DebugMessageDSC("3. DSC0 Chunk Size Check Fail", 0);

                return _FALSE;
            }
        }
#endif
    }
    else
    {
        DebugMessageDSC("3. DSC0 Stream Setting Fail", 0);

        return _FALSE;
    }

    if(ScalerDscDecoder0DisplayFormatSetting(&stDscTimingInfo) == _FALSE)
    {
        DebugMessageDSC("3. DSC0 Display Format Setting Fail", 0);

        return _FALSE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    if(ScalerDscDecoder0StreamClkRegenerate(&stDscTimingInfo) == _FALSE)
    {
        DebugMessageDSC("3. DSC0 Stream Clk Regenerate Fail", 0);

        return _FALSE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    if(ScalerDscDecoder0SetPLLTrackingNf(&stDscTimingInfo) == _FALSE)
    {
        DebugMessageDSC("3. DSC0 Clk Tracking Fail", 0);

        return _FALSE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    if(ScalerDscDecoder0FifoCheck(_DSC_FIFO_DELAY_CHECK) == _FALSE)
    {
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
        if(enumPortType == _PORT_DP)
        {
            ScalerDpMacDscFifoStatusIrqProc(ScalerDscDecoderGetDpMacRxxInput(_DSC_MAC_0), ScalerDscDecoder0GetFifoStatus());
        }
#endif

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
        if(enumPortType == _PORT_HDMI)
        {
            // Set HDMI SCDC Dsc decode fail field
            ScalerHdmiFrlMacRxSetDscDecodeFailStatus(ScalerDscDecoderGetDxInputPort(_DSC_MAC_0));
        }
#endif
        DebugMessageDSC("3. DSC0 Fifo Fail", 0);

        return _FALSE;
    }

#if(_DP_RX_DSC_DECODER_SUPPORT == _TRUE)
    if(enumPortType == _PORT_DP)
    {
        ScalerDpMacDscPpsTimeOutProc(ScalerDscDecoderGetDpMacRxxInput(_DSC_MAC_0), _DISABLE);
    }
#endif

    // Disable DSC Watch Dog Force To Background
    ScalerDscDecoder0SetForceToBackGround(_DISABLE);

    return _TRUE;
}

//--------------------------------------------------
// Description  : DSC0 Fifo Check
// Input Value  : enumInputPort
// Output Value : True --> Fifo not over/underflow
//--------------------------------------------------
bit ScalerDscDecoder0FifoCheck(EnumDscFifoCheckCondition enumDscFifoCheckCondition)
{
    if(enumDscFifoCheckCondition == _DSC_FIFO_DELAY_CHECK)
    {
        if(ScalerGetBit(P7_02_DSC_IRQ_CTRL0, (_BIT1 | _BIT0)) != 0x00)
        {
            ScalerTimerDelayXms(GET_DSC0_STREAM_FRAME_DELAY());

            // Clear Underflow / Overflow Flag
            ScalerSetBit(P7_02_DSC_IRQ_CTRL0, ~(_BIT6 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            ScalerTimerDelayXms(GET_DSC0_STREAM_FRAME_DELAY() << 1);

            pData[0] = 0;

            while(pData[0] < 6)
            {
                ScalerTimerDelayXms(10);

                if((ScalerGetBit(P7_02_DSC_IRQ_CTRL0, _BIT1) == _BIT1) || (ScalerGetBit(P7_02_DSC_IRQ_CTRL0, _BIT0) == _BIT0))
                {
                    return _FALSE;
                }

                pData[0]++;
            }
        }

#if(_FW_DP_DSC_MUTE_INSTANT_RECOVER_SUPPORT == _ON)
        EnumInputPort enumInputPort = ScalerDscDecoderGetDxInputPort(_DSC_MAC_0);

        // Check DSC Force BG Enable
        if(GET_DSC0_FORCE_BG_ENABLE() == _TRUE)
        {
            // Disable D-domain force-to-background
            ScalerDDomainBackgroundEnable(ScalerDpMacStreamRxGetForceBackgroundPath_EXINT0(enumInputPort), _DISABLE);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x05, _BIT0) == 0x00)
            {
                // Set DP Receive Port0 In Sync
                ScalerDpAuxRxSinkStatusSet_EXINT0(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_IN_SYNC);
            }
#endif

            // Clear DSC Watch Dog Force To Background
            ScalerSetBit(P7_05_DSC_WATCH_DOG, ~_BIT6, 0x00);

            // Enable DSC Fifo Under/OverFlow IRQ
            ScalerDscDecoder0SetFifoIRQ(_ENABLE);

            CLR_DSC0_FORCE_BG_ENABLE();
        }
#endif
    }
    else
    {
        if(ScalerGetBit(P7_02_DSC_IRQ_CTRL0, (_BIT1 | _BIT0)) != 0x00)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DSC0 Block PPS Information Check
// Input Value  : enumPortType
// Output Value : True/ False
//--------------------------------------------------
bit ScalerDscDecoder0DecInfoCheck(void)
{
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    EnumInputPort enumDx = ScalerDscDecoderGetDxInputPort(_DSC_MAC_0);
    EnumPortType enumPortType = ScalerSyncGetPortType(enumDx);
#endif

    // Get DSC PPS: Version
    SET_DSC0_VERSION(GET_DSC0_VERSION_CURRENT());

    // Get DSC PPS: Pictue Height
    SET_DSC0_PIC_HEIGHT(GET_DSC0_PIC_HEIGHT_CURRENT());

    // Get DSC PPS: Pictue Width
    SET_DSC0_PIC_WIDTH(GET_DSC0_PIC_WIDTH_CURRENT());

    // Get DSC PPS: Slice Height
    SET_DSC0_SLICE_HEIGHT(GET_DSC0_SLICE_HEIGHT_CURRENT());

    // Get DSC PPS: Slice Width
    SET_DSC0_SLICE_WIDTH(GET_DSC0_SLICE_WIDTH_CURRENT());

    if(GET_DSC0_SLICE_WIDTH() == 0x00)
    {
        DebugMessageDSC("DSC0 Slice Width Abnormal", GET_DSC0_SLICE_WIDTH());
        return _FALSE;
    }

    // Calculate Horizontal Slice Count
    SET_DSC0_HOR_SLICE_CNT((BYTE)((GET_DSC0_PIC_WIDTH() + GET_DSC0_SLICE_WIDTH() - 1) / GET_DSC0_SLICE_WIDTH()));

    // Get DSC PPS: Chunk Size
    SET_DSC0_CHUNK_SIZE(GET_DSC0_CHUNK_SIZE_CURRENT());

    // Get DSC PPS: Initial Decoder Delay
    SET_DSC0_INIT_DEC_DELAY(GET_DSC0_INIT_DEC_DELAY_CURRENT());

    // Get DSC PPS: RC Model Size
    SET_DSC0_RC_MODEL_SIZE(GET_DSC0_RC_MODEL_SIZE_CURRENT());

    // Get DSC PPS: Color Depth of Bit Per Pixel
    SET_DSC0_COLOR_BPP(GET_DSC0_COLOR_BPP_CURRENT());

    // Get DSC PPS: Color Depth of Bit Per Component
    SET_DSC0_COLOR_BPC(GET_DSC0_COLOR_BPC_CURRENT());

    // Get DSC PPS: Color Space of Native 420 Mode
    SET_DSC0_COLOR_NATIVE_420(GET_DSC0_COLOR_NATIVE_420_CURRENT());

    // Get DSC PPS: Color Space of Native 422 Mode
    SET_DSC0_COLOR_NATIVE_422(GET_DSC0_COLOR_NATIVE_422_CURRENT());

    // Get DSC PPS: Color Space of Simple 422 Mode
    SET_DSC0_COLOR_SIMPLE_422(GET_DSC0_COLOR_SIMPLE_422_CURRENT());

    DebugMessageDSC("DSC0 PPS - Pic Height", GET_DSC0_PIC_HEIGHT());
    DebugMessageDSC("DSC0 PPS - Pic Width", GET_DSC0_PIC_WIDTH());
    DebugMessageDSC("DSC0 PPS - Slice Height", GET_DSC0_SLICE_HEIGHT());
    DebugMessageDSC("DSC0 PPS - Slice Width", GET_DSC0_SLICE_WIDTH());
    DebugMessageDSC("DSC0 PPS - Slice Count", GET_DSC0_HOR_SLICE_CNT());
    DebugMessageDSC("DSC0 PPS - Chunk Size", GET_DSC0_CHUNK_SIZE());
    DebugMessageDSC("DSC0 PPS - Init Dec Delay", GET_DSC0_INIT_DEC_DELAY());
    DebugMessageDSC("DSC0 PPS - Bits Per Pixel", GET_DSC0_COLOR_BPP());
    DebugMessageDSC("DSC0 PPS - Bits Per Componet", GET_DSC0_COLOR_BPC());
    DebugMessageDSC("DSC0 PPS - Native420", GET_DSC0_COLOR_NATIVE_420());
    DebugMessageDSC("DSC0 PPS - Native422", GET_DSC0_COLOR_NATIVE_422());
    DebugMessageDSC("DSC0 PPS - Simple422", GET_DSC0_COLOR_SIMPLE_422());

    if(GET_DSC0_HOR_SLICE_CNT() > _HW_DSC_MAC_MAX_SLICE_CNT)
    {
        DebugMessageDSC("DSC0 Slice Count Exceed", GET_DSC0_HOR_SLICE_CNT());

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
        if(enumPortType == _PORT_HDMI)
        {
            // Set HDMI SCDC Dsc decode fail field
            ScalerHdmiFrlMacRxSetDscDecodeFailStatus(enumDx);
        }
#endif
        return _FALSE;
    }

    if(GET_DSC0_HOR_SLICE_CNT() == 6)
    {
        DebugMessageDSC("DSC0 Slice not supported", GET_DSC0_HOR_SLICE_CNT());

        return _FALSE;
    }

    if(GET_DSC0_SLICE_WIDTH() > ((_HW_DSC_MAC_SLICE_MERGE_SUPPORT == _ON) ? (_HW_DSC_MAC_MAX_SLICE_WIDTH << 1) : _HW_DSC_MAC_MAX_SLICE_WIDTH))
    {
        DebugMessageDSC("DSC0 Slice Width Exceed", GET_DSC0_SLICE_WIDTH());

#if((_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) && (_HDMI_DSC_DEC_FAIL_NOTIFY == _ON))
        if(enumPortType == _PORT_HDMI)
        {
            // Set HDMI SCDC Dsc decode fail field
            ScalerHdmiFrlMacRxSetDscDecodeFailStatus(enumDx);
        }
#endif
        return _FALSE;
    }

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(enumPortType == _PORT_HDMI)
    {
        if(GET_DSC0_SLICE_HEIGHT() < 96)
        {
            DebugMessageDSC("DSC0 Slice Height Exceed Limit", GET_DSC0_SLICE_WIDTH());

#if(_HDMI_DSC_DEC_FAIL_NOTIFY == _ON)
            // Set HDMI SCDC Dsc decode fail field
            ScalerHdmiFrlMacRxSetDscDecodeFailStatus(enumDx);
#endif
            return _FALSE;
        }
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : DSC0 Block PPS Change Check
// Input Value  : None
// Output Value : True/ False
//--------------------------------------------------
bit ScalerDscDecoder0PpsChangeCheck(void)
{
    // Get DSC PPS: Pictue Height
    if(GET_DSC0_PIC_HEIGHT() != GET_DSC0_PIC_HEIGHT_CURRENT())
    {
        DebugMessageDSC("DSC0 Pic Height Change", 0x00);
        return _FALSE;
    }

    // Get DSC PPS: Pictue Width
    if(GET_DSC0_PIC_WIDTH() != GET_DSC0_PIC_WIDTH_CURRENT())
    {
        DebugMessageDSC("DSC0 Pic Width Change", 0x00);
        return _FALSE;
    }

    // Get DSC PPS: Slice Height
    if(GET_DSC0_SLICE_HEIGHT() != GET_DSC0_SLICE_HEIGHT_CURRENT())
    {
        DebugMessageDSC("DSC0 Slice Height Change", 0x00);
        return _FALSE;
    }

    // Get DSC PPS: Slice Width
    if(GET_DSC0_SLICE_WIDTH() != GET_DSC0_SLICE_WIDTH_CURRENT())
    {
        DebugMessageDSC("DSC0 Slice Width Change", 0x00);
        return _FALSE;
    }

    // Get DSC PPS: Color Depth of Bit Per Component
    if(GET_DSC0_COLOR_BPC() != GET_DSC0_COLOR_BPC_CURRENT())
    {
        DebugMessageDSC("DSC0 BPC Change", 0x00);
        return _FALSE;
    }

    // Get DSC PPS: Color Space of Native 420 Mode
    if(GET_DSC0_COLOR_NATIVE_420() != GET_DSC0_COLOR_NATIVE_420_CURRENT())
    {
        DebugMessageDSC("DSC0 Native420 Change", 0x00);
        return _FALSE;
    }

    // Get DSC PPS: Color Space of Native 422 Mode
    if(GET_DSC0_COLOR_NATIVE_422() != GET_DSC0_COLOR_NATIVE_422_CURRENT())
    {
        DebugMessageDSC("DSC0 Native422 Change", 0x00);
        return _FALSE;
    }

    // Get DSC PPS: Color Space of Simple 422 Mode
    if(GET_DSC0_COLOR_SIMPLE_422() != GET_DSC0_COLOR_SIMPLE_422_CURRENT())
    {
        DebugMessageDSC("DSC0 Simple422 Change", 0x00);
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DSC0 Timing Info Check
// Input Value  : enumInputPort, enumPortType
// Output Value : None
//--------------------------------------------------
bit ScalerDscDecoder0TimingInfoCheck(StructDscTimingInfo *pstDscTimingInfo)
{
    EnumPortType enumPortType = ScalerSyncGetPortType(ScalerDscDecoderGetDxInputPort(_DSC_MAC_0));

    switch(enumPortType)
    {
#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            if(ScalerDscDecoder0GetHdmiTimingInfo(pstDscTimingInfo) == _FALSE)
            {
                return _FALSE;
            }
#endif
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            if(ScalerDscDecoder0GetDpTimingInfo(pstDscTimingInfo) == _FALSE)
            {
                return _FALSE;
            }
#endif
            break;
#endif

        default:
            break;
    }

    if(ScalerDscDecoder0PpsTimingCheck(pstDscTimingInfo) == _FALSE)
    {
        DebugMessageDSC("3. DSC0 MSA and PPS Not Match", 0);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DSC0 Decode Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0DecEnable(void)
{
    ScalerSetBit(P7_00_DSC_DEC_CTRL_00, ~(_BIT7 | _BIT0), _BIT7);
}

//--------------------------------------------------
// Description  : DSC Decoder Get Element
// Input Value  : enumType --> Type
// Output Value : Conetent
//--------------------------------------------------
WORD ScalerDscDecoder0GetElement(EnumDpStreamPpsElement enumElement)
{
    switch(enumElement)
    {
        case _PPS_BIT_PER_COMPONENT:
            return GET_DSC0_COLOR_BPC();
            break;

        case _PPS_BITS_PER_PIXEL:
            return GET_DSC0_COLOR_BPP();
            break;

        case _PPS_NATIVE_MODE:
            return GET_DSC0_COLOR_NATIVE_MODE();
            break;

        case _PPS_NATIVE_420:
            return GET_DSC0_COLOR_NATIVE_420();
            break;

        case _PPS_NATIVE_422:
            return GET_DSC0_COLOR_NATIVE_422();
            break;

        case _PPS_SIMPLE_422:
            return GET_DSC0_COLOR_SIMPLE_422();
            break;

        case _PPS_PIC_HEIGHT:
            return GET_DSC0_PIC_HEIGHT();
            break;

        case _PPS_PIC_WIDTH:
            return GET_DSC0_PIC_WIDTH();
            break;

        case _PPS_SLICE_HEIGHT:
            return GET_DSC0_SLICE_HEIGHT();
            break;

        case _PPS_SLICE_WIDTH:
            return GET_DSC0_SLICE_WIDTH();
            break;

        case _PPS_HOR_SLICE_COUNT:
            return GET_DSC0_HOR_SLICE_CNT();
            break;

        case _PPS_CHUNK_SIZE:
            return GET_DSC0_CHUNK_SIZE();
            break;

        case _PPS_INIT_DEC_DELAY:
            return GET_DSC0_INIT_DEC_DELAY();
            break;

        case _PPS_DSC_PIXEL_CLOCK:
            return GET_DSC0_PIXEL_CLK();
            break;

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : DSC force background
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0ForceBackgroundSetting(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable DSC force background
        ScalerSetBit(P7_05_DSC_WATCH_DOG, ~_BIT6, _BIT6);
    }
    else
    {
        // Disable DSC force background
        ScalerSetBit(P7_05_DSC_WATCH_DOG, ~_BIT6, 0x00);
    }
}

//--------------------------------------------------
// Description  : DSC Decoder Get Element
// Input Value  : None
// Output Value : BYTE
//--------------------------------------------------
BYTE ScalerDscDecoder0GetPixelMode(void)
{
    return GET_DSC0_PIXEL_MODE();
}

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DSC0 Get DP Timing Info
// Input Value  : enumInputPort, pstDscTimingInfo
// Output Value : TRUE, FALSE
//--------------------------------------------------
bit ScalerDscDecoder0GetDpTimingInfo(StructDscTimingInfo *pstDscTimingInfo)
{
    EnumDpMacSel enumDpMacSel = ScalerDscDecoderGetDpMacRxxInput(_DSC_MAC_0);
    StructDpInfo stDpInfo = {0};

    if(ScalerDpMacDscStreamRxGetMsaTimingInfo(enumDpMacSel, &stDpInfo) == _FALSE)
    {
        DebugMessageDSC("7. DP Get MSA Info Fail", 0);

        return _FALSE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return _FALSE;
    }
#endif

    if(ScalerDpMacDscStreamRxGetVideoInfo(enumDpMacSel) == _FALSE)
    {
        DebugMessageDSC("7. DP Get Video Info Fail", 0);

        return _FALSE;
    }
    else
    {
        ScalerDpMacDscStreamRxSetColorInfo(enumDpMacSel);
    }

    if(ScalerDpMacDscStreamRxGetMeasureLinkInfo(enumDpMacSel, &stDpInfo) == _FALSE)
    {
        DebugMessageDSC("7. DP Get Measure Info Fail", 0);

        return _FALSE;
    }

    if(ScalerDpMacDscStreamRxStreamInfoSetting(enumDpMacSel, &stDpInfo) == _FALSE)
    {
        DebugMessageDSC("7. DP Stream Info Setting Fail", 0);

        return _FALSE;
    }

    ScalerDpMacDscStreamRxTimingInfoAdjust(enumDpMacSel, &stDpInfo);

    // DP PLL Setting
    ScalerDpMacDscStreamRxStreamClkRegenerate(enumDpMacSel, &stDpInfo);

    // DP Tracking Setting
    ScalerDpMacDscStreamRxTrackingSetting(enumDpMacSel, &stDpInfo);

    pstDscTimingInfo->usHTotal = stDpInfo.stDpTimingInfo.usHTotal;
    pstDscTimingInfo->usHStart = stDpInfo.stDpTimingInfo.usHStart;
    pstDscTimingInfo->usHWidth = stDpInfo.stDpTimingInfo.usHWidth;
    pstDscTimingInfo->usHSWidth = stDpInfo.stDpTimingInfo.usHSWidth;
    pstDscTimingInfo->b1HSP = stDpInfo.stDpTimingInfo.b1HSP;
    pstDscTimingInfo->usHBsToBsCount = stDpInfo.stDpLinkInfo.usHBsToBsCount;
    pstDscTimingInfo->usVTotal = stDpInfo.stDpTimingInfo.usVTotal;
    pstDscTimingInfo->usVTotalOdd = stDpInfo.stDpTimingInfo.usVTotalOdd;
    pstDscTimingInfo->usVStart = stDpInfo.stDpTimingInfo.usVStart;
    pstDscTimingInfo->usVHeight = stDpInfo.stDpTimingInfo.usVHeight;
    pstDscTimingInfo->usVSWidth = stDpInfo.stDpTimingInfo.usVSWidth;
    pstDscTimingInfo->b1VSP = stDpInfo.stDpTimingInfo.b1VSP;
    pstDscTimingInfo->ulLinkClockHz = stDpInfo.stDpLinkInfo.ulLinkClockHz;
    pstDscTimingInfo->ulVBsToBsCountN = stDpInfo.stDpLinkInfo.ulVBsToBsCountN;
    pstDscTimingInfo->ulVBsToBsCountN1 = stDpInfo.stDpLinkInfo.ulVBsToBsCountN1;
    pstDscTimingInfo->b1InterlaceFieldN = stDpInfo.stDpLinkInfo.b1InterlaceFieldN;
    pstDscTimingInfo->b1InterlaceFieldN1 = stDpInfo.stDpLinkInfo.b1InterlaceFieldN1;

    return _TRUE;
}
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DSC0 Get HDMI Timing Info
// Input Value  : enumInputPort, pstDscTimingInfo
// Output Value : TRUE, FALSE
//--------------------------------------------------
bit ScalerDscDecoder0GetHdmiTimingInfo(StructDscTimingInfo *pstDscTimingInfo)
{
    switch(ScalerDscDecoderGetHdmiMacRxxInput(_DSC_MAC_0))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _RX3:
#if(_HDMI_FRL_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
            ScalerHdmiFrlMacRx3GetTimingInfo(pstDscTimingInfo);

            SET_DSC0_HC_ACTIVE(pstDscTimingInfo->usHWidth);
            SET_DSC0_HC_BLANK((pstDscTimingInfo->usHTotalAfterDSC - pstDscTimingInfo->usHWidth));

            return _TRUE;
#endif
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _RX4:
#if(_HDMI_FRL_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
            ScalerHdmiFrlMacRx4GetTimingInfo(pstDscTimingInfo);

            SET_DSC0_HC_ACTIVE(pstDscTimingInfo->usHWidth);
            SET_DSC0_HC_BLANK((pstDscTimingInfo->usHTotalAfterDSC - pstDscTimingInfo->usHWidth));

            return _TRUE;
#endif
            break;
#endif

        default:
            break;
    }

    pstDscTimingInfo->ulStreamClockHz = 0;

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : DSC0 MSA and PPS Match Check
// Input Value  : enumInputPort, pstDscTimingInfo
// Output Value : None
//--------------------------------------------------
bit ScalerDscDecoder0PpsTimingCheck(StructDscTimingInfo *pstDscTimingInfo)
{
    EnumPortType enumPortType = ScalerSyncGetPortType(ScalerDscDecoderGetDxInputPort(_DSC_MAC_0));
    WORD usInputHwidth = 0;
    WORD usInputVheight = 0;

    // Get Horizontal Width and Vertical Height
    usInputHwidth = pstDscTimingInfo->usHWidth;
    usInputVheight = pstDscTimingInfo->usVHeight;

    switch(enumPortType)
    {
#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)

            // Get HDMI DSC Bytes Target: Slice_Cnt * Ceiling[(Fractional_BPP / 16) * Slice_Width / 8] = Slice_Cnt * Ceiling[(Fractional_BPP) * Slice_Width / (16 * 8)]
            PDATA_WORD(0) = ((((DWORD)GET_DSC0_COLOR_BPP() * GET_DSC0_SLICE_WIDTH() / (16 * 8)) + ((((DWORD)GET_DSC0_COLOR_BPP() * GET_DSC0_SLICE_WIDTH() % (16 * 8)) > 0) ? 1 : 0)) * GET_DSC0_HOR_SLICE_CNT()) >> ((GET_DSC0_COLOR_NATIVE_MODE() == _TRUE) ? 1 : 0);

            // Compare Active Region
            if((usInputHwidth == PDATA_WORD(0)) && (usInputVheight == GET_DSC0_PIC_HEIGHT()))
            {
                return _TRUE;
            }
            else
            {
                DebugMessageDSC("HDMI Rx Hcactive", usInputHwidth);
                DebugMessageDSC("HDMI PPS Hcactive", PDATA_WORD(0));
                DebugMessageDSC("HDMI Rx Vheight", usInputVheight);
                DebugMessageDSC("HDMI PPS Vheight", GET_DSC0_PIC_HEIGHT());
            }
#endif
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)

            // Compare Active Region
            if((usInputHwidth == GET_DSC0_PIC_WIDTH()) && (usInputVheight == GET_DSC0_PIC_HEIGHT()))
            {
                return _TRUE;
            }
            else
            {
                DebugMessageDSC("DP Rx Hwidth", usInputHwidth);
                DebugMessageDSC("DP PPS Hwidth", GET_DSC0_PIC_WIDTH());
                DebugMessageDSC("DP Rx Vheight", usInputVheight);
                DebugMessageDSC("DP PPS Vheight", GET_DSC0_PIC_HEIGHT());
            }
#endif
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DSC Timing Info Adjust
// Input Value  : *pstDscTimingInfo
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0RxTimingInfoAdjust(StructDscTimingInfo *pstDscTimingInfo)
{
    WORD usModAdjust = (GET_DSC0_PIXEL_CLK() > GET_DSC0_CLK()) ? (GET_DSC0_PIXEL_CLK() / GET_DSC0_CLK()) : 1;

    if((pstDscTimingInfo->usHSWidth % usModAdjust) != 0)
    {
        // Make Sure HSW is a Multiple of usModAdjust
        pstDscTimingInfo->usHSWidth += (usModAdjust - (pstDscTimingInfo->usHSWidth % usModAdjust));
    }

    // Check if HSW is more than Hstart
    if(pstDscTimingInfo->usHSWidth >= pstDscTimingInfo->usHStart)
    {
        pstDscTimingInfo->usHStart = ScalerSyncGetHStartbyHSW(pstDscTimingInfo->usHSWidth, GET_DSC0_PIXEL_CLK());
    }
}

//--------------------------------------------------
// Description  : DSC0 Stream Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDscDecoder0StreamSetting(StructDscTimingInfo *pstDscTimingInfo)
{
    if(ScalerDscDecoder0StreamInfo(pstDscTimingInfo) == _FALSE)
    {
        return _FALSE;
    }

    // One Frame Delay
    SET_DSC0_STREAM_FRAME_DELAY((1000 + GET_DSC0_STREAM_FRAME_RATE() / 2) / GET_DSC0_STREAM_FRAME_RATE() + 1);

    // Set Pixel Mode
    ScalerSetBit(P7_04_DSC_OUT_FORMAT, ~(_BIT1 | _BIT0), GET_DSC0_PIXEL_MODE());

    // DSC 2x Speed Control
    ScalerSetBit(P7_01_DSC_DEC_CTRL_01, ~_BIT0, GET_DSC0_2X_SPEED());

    // Set source div = 1 , dsc tracking div = 2
    ScalerSetBit(P7_03_DSC_DIV_CTRL0, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT2);

    // Set dsc_out_div for pixel mode
    if(GET_DSC0_BUF_CLK() == GET_DSC0_OUTPUT_CLK())
    {
        ScalerSetBit(P7_03_DSC_DIV_CTRL0, ~(_BIT5 | _BIT4), 0x00);
    }
    else if((GET_DSC0_BUF_CLK() >> 1) == GET_DSC0_OUTPUT_CLK())
    {
        ScalerSetBit(P7_03_DSC_DIV_CTRL0, ~(_BIT5 | _BIT4), _BIT4);
    }
    else if((GET_DSC0_BUF_CLK() >> 2) == GET_DSC0_OUTPUT_CLK())
    {
        ScalerSetBit(P7_03_DSC_DIV_CTRL0, ~(_BIT5 | _BIT4), _BIT5);
    }
    else if((GET_DSC0_BUF_CLK() >> 3) == GET_DSC0_OUTPUT_CLK())
    {
        ScalerSetBit(P7_03_DSC_DIV_CTRL0, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
    }

    // reg_pre_pixel_mode = pix_clk / (buffer_clk / (1+speed2X)); (= 0.5 / 1 / 2 / 4)
    if(((GET_DSC0_PIXEL_CLK() >> 2) / (GET_DSC0_BUF_CLK() >> GET_DSC0_2X_SPEED())) == 1)
    {
        // pre-pixel mode = 4
        ScalerSetBit(P7_04_DSC_OUT_FORMAT, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

        // dsc_clk / pixel_clk = 1/8
        SET_DSC0_HTOTAL((pstDscTimingInfo->usHTotal << GET_DSC0_2X_SPEED()) >> 3);

        DebugMessageDSC("Case1: DSC0_HTOTAL", GET_DSC0_HTOTAL());

        // Set dsc buffer clk
        pstDscTimingInfo->ulBufferClockHz = (pstDscTimingInfo->ulStreamClockHz << GET_DSC0_2X_SPEED()) >> 2;
    }
    else if(((GET_DSC0_PIXEL_CLK() >> 1) / (GET_DSC0_BUF_CLK() >> GET_DSC0_2X_SPEED())) == 1)
    {
        // pre-pixel mode = 2
        ScalerSetBit(P7_04_DSC_OUT_FORMAT, ~(_BIT3 | _BIT2), _BIT3);

        // dsc_clk / pixel_clk = 1/4
        SET_DSC0_HTOTAL((pstDscTimingInfo->usHTotal << GET_DSC0_2X_SPEED()) >> 2);

        DebugMessageDSC("Case2: DSC0_HTOTAL", GET_DSC0_HTOTAL());

        // Set dsc buffer clk
        pstDscTimingInfo->ulBufferClockHz = (pstDscTimingInfo->ulStreamClockHz << GET_DSC0_2X_SPEED()) >> 1;
    }
    else if(((GET_DSC0_PIXEL_CLK()) / (GET_DSC0_BUF_CLK() >> GET_DSC0_2X_SPEED())) == 1)
    {
        // pre-pixel mode = 1
        ScalerSetBit(P7_04_DSC_OUT_FORMAT, ~(_BIT3 | _BIT2), _BIT2);

        // dsc_clk / pixel_clk = 1/2
        SET_DSC0_HTOTAL((pstDscTimingInfo->usHTotal << GET_DSC0_2X_SPEED()) >> 1);

        DebugMessageDSC("Case3: DSC0_HTOTAL", GET_DSC0_HTOTAL());

        // Set dsc buffer clk
        pstDscTimingInfo->ulBufferClockHz = (pstDscTimingInfo->ulStreamClockHz << GET_DSC0_2X_SPEED());
    }
    else if(((GET_DSC0_PIXEL_CLK() << 1) / (GET_DSC0_BUF_CLK() >> GET_DSC0_2X_SPEED())) == 1)
    {
        // pre-pixel mode = 0.5
        ScalerSetBit(P7_04_DSC_OUT_FORMAT, ~(_BIT3 | _BIT2), 0x00);

        // dsc_clk / pixel_clk = 1
        SET_DSC0_HTOTAL((pstDscTimingInfo->usHTotal << GET_DSC0_2X_SPEED()));

        DebugMessageDSC("Case4: DSC0_HTOTAL", GET_DSC0_HTOTAL());

        // Set dsc buffer clk
        pstDscTimingInfo->ulBufferClockHz = (pstDscTimingInfo->ulStreamClockHz << GET_DSC0_2X_SPEED()) << 1;
    }
    else
    {
        DebugMessageDSC("Case Fail: DSC0_HTOTAL", GET_DSC0_HTOTAL());
    }

    // for debug purpose, output variable and output VCO clk/16 start
    DebugMessageDSC("2. DSC pixcel clock", GET_DSC0_PIXEL_CLK());
    DebugMessageDSC("2. Pixel Mode", (1 << GET_DSC0_PIXEL_MODE()));
    DebugMessageDSC("2. DSC Buffclk", GET_DSC0_BUF_CLK());
    DebugMessageDSC("2. Speed2X", (1 << GET_DSC0_2X_SPEED()));
    DebugMessageDSC("2. pre-pixel mode", ScalerGetBit(P7_04_DSC_OUT_FORMAT, (_BIT3 | _BIT2)) >> 2);
    DebugMessageDSC("2. DSC Clk", GET_DSC0_CLK());

    if(GET_DSC0_COLOR_NATIVE_MODE() == _TRUE)
    {
        if((GET_DSC0_PIXEL_CLK() / GET_DSC0_HOR_SLICE_CNT()) > (_HW_DSC_MAC_DEC_MAX_BW << 1))
        {
            DebugMessageDSC("!!! Native Mode Exceed DSC Slice Max BW", (GET_DSC0_PIXEL_CLK() / GET_DSC0_HOR_SLICE_CNT()));

            return _FALSE;
        }
    }
    else
    {
        if((GET_DSC0_PIXEL_CLK() / GET_DSC0_HOR_SLICE_CNT()) > _HW_DSC_MAC_DEC_MAX_BW)
        {
            DebugMessageDSC("!!! Simple Mode Exceed DSC Slice Max BW", (GET_DSC0_PIXEL_CLK() / GET_DSC0_HOR_SLICE_CNT()));

            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DSC0 Stream Information
// Input Value  : enumPortType, pusInputHtotal, pulStreamClkValue, pstDscTimingInfo
// Output Value : None
//--------------------------------------------------
bit ScalerDscDecoder0StreamInfo(StructDscTimingInfo *pstDscTimingInfo)
{
    EnumInputPort enumInputPort = ScalerDscDecoderGetDxInputPort(_DSC_MAC_0);
    EnumPortType enumPortType = ScalerSyncGetPortType(enumInputPort);

    WORD usDsc_min_clk = 0;
    WORD usInputHwidth = 0;
    WORD usDscDFGHBs2Be = 0;
    WORD usDscDFGHfp = 0;
    BYTE ucDSCDFGMultiple = 0;
    BYTE ucOutput_div = 0;
    WORD usDscTargetDFGHBs2Be = 12;
    bit bDscStreamClockCheckDone = _FALSE;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    // PQC/PQDC Hw Limitaion
    BYTE ucDscHPorchExtend = _INPUT_H_PORCH_EXTEND;
#endif

    // Get Horizontal Width
    usInputHwidth = GET_DSC0_PIC_WIDTH();

    switch(enumPortType)
    {
#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)

            if((pstDscTimingInfo->usHTotalAfterDSC == 0) || (pstDscTimingInfo->usVTotal == 0))
            {
                return _FALSE;
            }

            // Set IVfreq: frame rate in Hz
            SET_DSC0_STREAM_FRAME_RATE((pstDscTimingInfo->ulCompStreamClockHz * 8UL + ((DWORD)pstDscTimingInfo->usHTotalAfterDSC * pstDscTimingInfo->usVTotal)) / ((DWORD)pstDscTimingInfo->usHTotalAfterDSC * pstDscTimingInfo->usVTotal * 2UL));

            // Set DSC Native Input Pixel Clk
            ScalerDscDecoderSetNativeInputPixelClock(enumInputPort, ScalerGlobalComputeDwordMulDiv((DWORD)pstDscTimingInfo->usHTotal * pstDscTimingInfo->usVTotal, (DWORD)pstDscTimingInfo->ulCompStreamClockHz * 4UL, (DWORD)pstDscTimingInfo->usHTotalAfterDSC * pstDscTimingInfo->usVTotal * (1 + GET_DSC0_COLOR_NATIVE_420())));
#endif
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)

            if(pstDscTimingInfo->ulVBsToBsCountN == 0)
            {
                return _FALSE;
            }

            // Set IVfreq: frame rate in Hz
            SET_DSC0_STREAM_FRAME_RATE((_GDIPHY_RX_GDI_CLK_KHZ * 2000UL + pstDscTimingInfo->ulVBsToBsCountN) / (pstDscTimingInfo->ulVBsToBsCountN * 2UL));

            // Set VHeight
            ScalerDpMacDscStreamRxSetVheight(ScalerDscDecoderDscMacStreamSourceDpMacRxxMapping(GET_DSC_DECODER_MAC_0_STREAM_SOURCE()), pstDscTimingInfo->usVHeight);

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
            if(ScalerDpMacDscSetNativeInputPixelClkCheck(ScalerDscDecoderDscMacStreamSourceDpMacRxxMapping(GET_DSC_DECODER_MAC_0_STREAM_SOURCE())) == _TRUE)
#endif
            {
                // Set DX Port DSC Native Input Pixel Clk
                ScalerDscDecoderSetNativeInputPixelClock(enumInputPort, ScalerGlobalComputeDwordMulDiv((DWORD)pstDscTimingInfo->usHTotal * pstDscTimingInfo->usVTotal, (DWORD)_GDIPHY_RX_GDI_CLK_KHZ * 1000UL, (DWORD)pstDscTimingInfo->ulVBsToBsCountN * (1 + GET_DSC0_COLOR_NATIVE_420())));
            }
#endif
            break;
#endif

        default:
            return _FALSE;
            break;
    }

    if(GET_DSC0_STREAM_FRAME_RATE() == 0)
    {
        DebugMessageDSC("2.X Frame Rate Error", GET_DSC0_STREAM_FRAME_RATE());
        return _FALSE;
    }
    else
    {
        DebugMessageDSC("2. Frame Rate", GET_DSC0_STREAM_FRAME_RATE());
    }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    // Check PQC/PQDC Hw Limitaion
    if((pstDscTimingInfo->usHTotal - usInputHwidth) < ucDscHPorchExtend)
    {
        pstDscTimingInfo->usHTotal = usInputHwidth + ucDscHPorchExtend;

        DebugMessageDSC("Input Htotal with PQC/PQDC", pstDscTimingInfo->usHTotal);
    }
#endif

    while(bDscStreamClockCheckDone == _FALSE)
    {
        if(enumPortType == _PORT_DP)
        {
            // Calculate streamclk (Unit is Hz)
            pstDscTimingInfo->ulStreamClockHz = ScalerGlobalComputeDwordMulDiv((DWORD)pstDscTimingInfo->usHTotal * pstDscTimingInfo->usVTotal, (DWORD)_GDIPHY_RX_GDI_CLK_KHZ * 1000UL, pstDscTimingInfo->ulVBsToBsCountN);
        }
        else
        {
            // Calculate streamclk (Unit is Hz)
            pstDscTimingInfo->ulStreamClockHz = ScalerGlobalComputeDwordMulDiv((DWORD)pstDscTimingInfo->usHTotal * pstDscTimingInfo->usVTotal, (DWORD)pstDscTimingInfo->ulCompStreamClockHz * 4UL, (DWORD)pstDscTimingInfo->usHTotalAfterDSC * pstDscTimingInfo->usVTotal);
        }

        bDscStreamClockCheckDone = _TRUE;

        DebugMessageDSC("Input Vtotal", pstDscTimingInfo->usVTotal);
        DebugMessageDSC("Input Htotal", pstDscTimingInfo->usHTotal);
        DebugMessageDSC("Input HWdith", usInputHwidth);

        // Input Pixel CLK (Unit is 0.1 M)
        SET_DSC0_PIXEL_CLK(pstDscTimingInfo->ulStreamClockHz / 100000);

        if(GET_DSC0_PIXEL_CLK() == 0)
        {
            return _FALSE;
        }

        if(GET_DSC0_COLOR_NATIVE_420() == _TRUE)
        {
            if((GET_DSC0_PIXEL_CLK() >> 1) > GET_DWORD_MUL_DIV(_HW_DSC_DATA_PATH_MAX_BOUNDARY, 101, 100))
            {
                // Pixel Clk > 1400M, Pixel mode = 2
                SET_DSC0_PIXEL_MODE(1);
            }
            else
            {
                // Pixel Clk <= 1400M, Pixel mode = 1
                SET_DSC0_PIXEL_MODE(0);
            }
        }
        else
        {
            // Select Pixel Mode
            if((GET_DSC0_PIXEL_CLK() >> 1) > GET_DWORD_MUL_DIV(_HW_DSC_DATA_PATH_MAX_BOUNDARY, 101, 100))
            {
                // Pixel Clk > 1400M, Pixel mode = 4
                SET_DSC0_PIXEL_MODE(2);
            }
            else if(GET_DSC0_PIXEL_CLK() > GET_DWORD_MUL_DIV(_HW_DSC_DATA_PATH_MAX_BOUNDARY, 101, 100))
            {
                // Pixel Clk > 700M, Pixel mode = 2
                SET_DSC0_PIXEL_MODE(1);
            }
            else
            {
                // Pixel Clk <= 700M, Pixel mode = 1
                SET_DSC0_PIXEL_MODE(0);
            }
        }

        // dsc_min_clk = pix_clk / hor_slice_cnt / (1 + native_mode);
        usDsc_min_clk = (GET_DSC0_PIXEL_CLK() / GET_DSC0_HOR_SLICE_CNT()) >> ((GET_DSC0_COLOR_NATIVE_MODE() == _TRUE) ? 1 : 0);

        // output_clk = pix_clk / pixel_mode / (1 + native_420);
        SET_DSC0_OUTPUT_CLK(GET_DSC0_PIXEL_CLK() >> (GET_DSC0_PIXEL_MODE() + ((GET_DSC0_COLOR_NATIVE_420() == _TRUE) ? 1 : 0)));

        // Set DSC Buffer Clk
        if((GET_DSC0_OUTPUT_CLK() << ((GET_DSC0_COLOR_NATIVE_420() == _TRUE) ? 1 : 0)) >= (usDsc_min_clk << 1))
        {
            if(GET_DSC0_OUTPUT_CLK() < 3400)
            {
                SET_DSC0_BUF_CLK(GET_DSC0_OUTPUT_CLK() << ((GET_DSC0_COLOR_NATIVE_420() == _TRUE) ? 1 : 0));
            }
            else
            {
                SET_DSC0_BUF_CLK(GET_DSC0_OUTPUT_CLK());
            }
        }
        else
        {
            SET_DSC0_BUF_CLK(usDsc_min_clk << 1);
        }

        // Set DSC 2x Speed if (buf_clk < 340MHz) & (Slice Count > 1)
        // For Format Conversion Duplicate Mode in 680M~700M with Native 420, DSC Should Set DSC 2x Speed
        if(((GET_DSC0_BUF_CLK() < 3400) && (GET_DSC0_HOR_SLICE_CNT() > 1)) ||
           ((GET_DSC0_COLOR_NATIVE_420() == _TRUE) && ((GET_DSC0_PIXEL_CLK() > 6800) && (GET_DSC0_PIXEL_CLK() <= 7000))))
        {
            SET_DSC0_2X_SPEED();
            SET_DSC0_BUF_CLK(GET_DSC0_BUF_CLK() << 1);
        }
        else
        {
            CLR_DSC0_2X_SPEED();
        }

        // Set DSC Clk
        SET_DSC0_CLK(GET_DSC0_BUF_CLK() >> 1);

        if(GET_DSC0_PIXEL_CLK() < GET_DSC0_CLK())
        {
            ucDSCDFGMultiple = GET_DSC0_CLK() / GET_DSC0_PIXEL_CLK();
            usDscDFGHBs2Be = (pstDscTimingInfo->usHTotal - usInputHwidth) * ucDSCDFGMultiple;

            // DSC DPF Front Porch + Back Porch should be larger than usDscTargetDFGHBs2Be
            if(usDscDFGHBs2Be < usDscTargetDFGHBs2Be)
            {
                pstDscTimingInfo->usHTotal = ((usDscTargetDFGHBs2Be) / ucDSCDFGMultiple) + usInputHwidth;
                bDscStreamClockCheckDone = _FALSE;
            }
        }
        else
        {
            ucDSCDFGMultiple = GET_DSC0_PIXEL_CLK() / GET_DSC0_CLK();
            usDscDFGHBs2Be = (pstDscTimingInfo->usHTotal - usInputHwidth) / ucDSCDFGMultiple;

            // DSC DPF Front Porch + Back Porch should be larger than usDscTargetDFGHBs2Be
            if(usDscDFGHBs2Be < usDscTargetDFGHBs2Be)
            {
                pstDscTimingInfo->usHTotal = (usDscTargetDFGHBs2Be * ucDSCDFGMultiple) + usInputHwidth;
                bDscStreamClockCheckDone = _FALSE;
            }
        }

        DebugMessageDSC("usDscDFGHBs2Be", usDscDFGHBs2Be);

        ScalerDscDecoder0RxTimingInfoAdjust(pstDscTimingInfo);

        // Get dsc_out_div
        if(GET_DSC0_BUF_CLK() == GET_DSC0_OUTPUT_CLK())
        {
            ucOutput_div = 0;
        }
        else if((GET_DSC0_BUF_CLK() >> 1) == GET_DSC0_OUTPUT_CLK())
        {
            ucOutput_div = 1;
        }
        else if((GET_DSC0_BUF_CLK() >> 2) == GET_DSC0_OUTPUT_CLK())
        {
            ucOutput_div = 2;
        }
        else if((GET_DSC0_BUF_CLK() >> 3) == GET_DSC0_OUTPUT_CLK())
        {
            ucOutput_div = 3;
        }

        // For DSC Decoder H-Front porch output limit
        if(GET_DSC0_COLOR_NATIVE_420() == _TRUE)
        {
            // For 420, DSC Decoder H-Front porch >= 8 * 2 * pixel_mode / (2 ^ (reg_dsc_out_div - reg_speed_2x))
            usDscDFGHfp = (16UL << (GET_DSC0_PIXEL_MODE() + GET_DSC0_2X_SPEED())) >> ucOutput_div;
        }
        else
        {
            // For RGB/444/422, DSC Decoder H-Front porch >= 6 * pixel_mode / (2 ^ (reg_dsc_out_div - reg_speed_2x))
            usDscDFGHfp = (6UL << (GET_DSC0_PIXEL_MODE() + GET_DSC0_2X_SPEED())) >> ucOutput_div;
        }

        // Check Htotal after Timing Info Adjust
        if(pstDscTimingInfo->usHTotal < (usInputHwidth + pstDscTimingInfo->usHStart))
        {
            pstDscTimingInfo->usHTotal = (usInputHwidth + pstDscTimingInfo->usHStart);
            bDscStreamClockCheckDone = _FALSE;
        }

        if((pstDscTimingInfo->usHTotal - usInputHwidth - pstDscTimingInfo->usHStart) < usDscDFGHfp)
        {
            DebugMessageDSC("DSC DFG HF-Porch", (pstDscTimingInfo->usHTotal - usInputHwidth - pstDscTimingInfo->usHStart));
            DebugMessageDSC("DSC DFG HF-Porch modified!!", usDscDFGHfp);

            pstDscTimingInfo->usHTotal += (usDscDFGHfp - (pstDscTimingInfo->usHTotal - usInputHwidth - pstDscTimingInfo->usHStart));
            bDscStreamClockCheckDone = _FALSE;
        }
    }

    DebugMessageDSC("!!! Modified Input Htotal", pstDscTimingInfo->usHTotal);

    return _TRUE;
}

//--------------------------------------------------
// Description  : DSC0 Get Display Format DRR Enable
// Input Value  : None
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
bit ScalerDscDecoder0GetDrrEnable(void)
{
#if(_DRR_SUPPORT == _ON)
    if(ScalerDrrGetType(ScalerDscDecoderGetDxInputPort(_DSC_MAC_0)) != _DRR_NONE_TYPE)
    {
        return _TRUE;
    }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    // Check DSC ALPM Status Enable
    if(ScalerDpRxAuxlessAlpmGetEnable(ScalerDscDecoderGetDxInputPort(_DSC_MAC_0)) == _ENABLE)
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : DSC0 Display Format Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDscDecoder0DisplayFormatSetting(StructDscTimingInfo *pstDscTimingInfo)
{
    EnumInputPort enumInputPort = ScalerDscDecoderGetDxInputPort(_DSC_MAC_0);
    EnumPortType enumPortType = ScalerSyncGetPortType(enumInputPort);

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSel = ScalerDscDecoderGetDpMacRxxInput(_DSC_MAC_0);
#endif

    BYTE ucDscDFGMultiple = 0;
    WORD usDscDFGHstart = 0;
    WORD usDscDFGHwidth = 0;
    WORD usDscDFGHSyncWidth = 0;

    // Get DSC Pre-Pixel Mode
    ucDscDFGMultiple = ScalerGetBit(P7_04_DSC_OUT_FORMAT, (_BIT3 | _BIT2)) >> 2;

    // Get Horizontal Start
    usDscDFGHstart = pstDscTimingInfo->usHStart << GET_DSC0_2X_SPEED() >> ucDscDFGMultiple;

    // Get Horizontal Width
    usDscDFGHwidth = GET_DSC0_PIC_WIDTH() << GET_DSC0_2X_SPEED() >> ucDscDFGMultiple;

    // Get Horizontal Sync Width
    usDscDFGHSyncWidth = pstDscTimingInfo->usHSWidth << GET_DSC0_2X_SPEED() >> ucDscDFGMultiple;


    ////////////////////////////////////
    // Display Format Generator Reset //
    ////////////////////////////////////

    // Disable Generate Display Format
    ScalerSetBit(P7_30_DPF_CTRL_0, ~_BIT7, 0x00);

    // Display Format Generator Reset
    ScalerSetBit(P7_2F_MAC_DIG_RESET_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(P7_2F_MAC_DIG_RESET_CTRL, ~_BIT7, 0x00);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
    if(enumPortType == _PORT_DP)
    {
        //////////////////////////
        // Interlace Mode Check //
        //////////////////////////

#if(_DP_FREESYNC_SUPPORT == _ON)
        if(ScalerDrrFreeSyncDpGetEnable(enumInputPort) == _FALSE)
#endif
        {
            if(ScalerDscDecoder0DpInterlaceCheck(pstDscTimingInfo) == _TRUE)
            {
                DebugMessageDSC("7. Interlace Mode - VTotal", pstDscTimingInfo->usVTotal);
            }
            else
            {
                DebugMessageDSC("7. Progressive Mode", 0);
            }
        }

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
        // Set Alpm T1 Vstart
        ScalerDscDecoder0SetAlpmT1Vstart(ScalerDpMacDscStreamRxGetMsaVstart(enumDpMacSel));

        // Set Alpm T2 Vstart = 1 line
        ScalerSetByte(P7_35_MN_DPF_ALPM_VST, 0x01);
#endif
    }
#endif


    ///////////////////////////////////
    // Display Format Timing Setting //
    ///////////////////////////////////

    // Set HTotal
    ScalerSetByte(P7_41_MN_DPF_HTT_M, HIBYTE(GET_DSC0_HTOTAL()));
    ScalerSetByte(P7_42_MN_DPF_HTT_L, LOBYTE(GET_DSC0_HTOTAL()));

    // Set HStart
    ScalerSetByte(P7_43_MN_DPF_HST_M, HIBYTE(usDscDFGHstart));
    ScalerSetByte(P7_44_MN_DPF_HST_L, LOBYTE(usDscDFGHstart));

    // Set HWidth
    ScalerSetByte(P7_45_MN_DPF_HWD_M, HIBYTE(usDscDFGHwidth));
    ScalerSetByte(P7_46_MN_DPF_HWD_L, LOBYTE(usDscDFGHwidth));

    // Set HSW
    ScalerSetByte(P7_47_MN_DPF_HSW_M, HIBYTE(usDscDFGHSyncWidth));
    ScalerSetByte(P7_48_MN_DPF_HSW_L, LOBYTE(usDscDFGHSyncWidth));

    // Set HSP = Positive
    ScalerSetBit(P7_47_MN_DPF_HSW_M, ~_BIT7, ((BYTE)pstDscTimingInfo->b1HSP) << 7);

    // Set Vtotal
    ScalerSetByte(P7_49_MN_DPF_VTT_M, HIBYTE(pstDscTimingInfo->usVTotal));
    ScalerSetByte(P7_4A_MN_DPF_VTT_L, LOBYTE(pstDscTimingInfo->usVTotal));

    // Set VStart
    ScalerSetByte(P7_4B_MN_DPF_VST_M, HIBYTE(pstDscTimingInfo->usVStart));
    ScalerSetByte(P7_4C_MN_DPF_VST_L, LOBYTE(pstDscTimingInfo->usVStart));

    // Set VHeight
    ScalerSetByte(P7_4D_MN_DPF_VHT_M, HIBYTE(pstDscTimingInfo->usVHeight));
    ScalerSetByte(P7_4E_MN_DPF_VHT_L, LOBYTE(pstDscTimingInfo->usVHeight));

    // Set VSW
    ScalerSetByte(P7_4F_MN_DPF_VSW_M, HIBYTE(pstDscTimingInfo->usVSWidth));
    ScalerSetByte(P7_50_MN_DPF_VSW_L, LOBYTE(pstDscTimingInfo->usVSWidth));

    // Set VSP = Positive
    ScalerSetBit(P7_4F_MN_DPF_VSW_M, ~_BIT7, ((BYTE)pstDscTimingInfo->b1VSP) << 7);

    DebugMessageDSC("DSC0 DFG Htotal", GET_DSC0_HTOTAL());
    DebugMessageDSC("DSC0 DFG Hstart", usDscDFGHstart);
    DebugMessageDSC("DSC0 DFG Hwidth", usDscDFGHwidth);
    DebugMessageDSC("DSC0 DFG HSW", usDscDFGHSyncWidth);

    DebugMessageDSC("DSC0 DFG Vtotal", pstDscTimingInfo->usVTotal);
    DebugMessageDSC("DSC0 DFG Vstart", pstDscTimingInfo->usVStart);
    DebugMessageDSC("DSC0 DFG Vheight", pstDscTimingInfo->usVHeight);
    DebugMessageDSC("DSC0 DFG VSW", pstDscTimingInfo->usVSWidth);

    // Set Color Information
    ScalerDscDecoder0SetColorInfo();

    //////////////////////////////////////
    // Display Format Generator Setting //
    //////////////////////////////////////

    if(enumPortType == _PORT_DP)
    {
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
        if(ScalerDscDecoder0GetDrrEnable() == _TRUE)
        {
            /////////////////////////
            // DRR Frame Sync Mode //
            /////////////////////////

            // DRR Mode Set VStart = 1
            ScalerSetByte(P7_4B_MN_DPF_VST_M, 0x00);
            ScalerSetByte(P7_4C_MN_DPF_VST_L, 0x01);

            // Enable DP Freesync Mode(DRR Mode)
            ScalerSetBit(P7_32_DP_RSV0, ~_BIT0, _BIT0);
            SET_DRR_DSC0_ENABLED(_ENABLE);

            // Set Frame Sync Mode, Set DSC DPF Source of virtual VS: BE
            ScalerSetBit(P7_30_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT3));

            DebugMessageDSC("Freesync Mode Enabled!!", ScalerGetByte(P7_30_DPF_CTRL_0));
        }
        else
        {
            /////////////////////////
            // Full Last Line Mode //
            /////////////////////////

            // Disable DP Freesync Mode(DRR mode)
            ScalerSetBit(P7_32_DP_RSV0, ~_BIT0, 0x00);
            SET_DRR_DSC0_ENABLED(_DISABLE);

            // Set Full Last Line Mode, Set DSC DPF Source of virtual VS: BS
            ScalerSetBit(P7_30_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3), 0x00);
        }

        // Set Vertical Front Porch = 0
        ScalerDpMacDscStreamRxSetVfrontPorch(ScalerDscDecoderDscMacStreamSourceDpMacRxxMapping(GET_DSC_DECODER_MAC_0_STREAM_SOURCE()), 0);

        pstDscTimingInfo->usVFrontPorch = 0;
#endif
    }
    else
    {
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
#if(_FW_DSC_FRL_IVS_PRODUCE_BE == _ON)
        /////////////////////////
        // DRR Frame Sync Mode //
        /////////////////////////

        // DRR Mode Set VStart = 1
        ScalerSetByte(P7_4B_MN_DPF_VST_M, 0x00);
        ScalerSetByte(P7_4C_MN_DPF_VST_L, 0x01);

        // Enable DP Freesync Mode(DRR Mode)
        ScalerSetBit(P7_32_DP_RSV0, ~_BIT0, _BIT0);
        SET_DRR_DSC0_ENABLED(_ENABLE);

        // Set Frame Sync Mode, Set DSC DPF Source of virtual VS: BE
        ScalerSetBit(P7_30_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT3));
#else
        if(ScalerDscDecoder0GetDrrEnable() == _TRUE)
        {
            /////////////////////////
            // DRR Frame Sync Mode //
            /////////////////////////

            // DRR Mode Set VStart = 1
            ScalerSetByte(P7_4B_MN_DPF_VST_M, 0x00);
            ScalerSetByte(P7_4C_MN_DPF_VST_L, 0x01);

            // Enable DP Freesync Mode(DRR Mode)
            ScalerSetBit(P7_32_DP_RSV0, ~_BIT0, _BIT0);
            SET_DRR_DSC0_ENABLED(_ENABLE);

            // Set Frame Sync Mode, Set DSC DPF Source of virtual VS: BE
            ScalerSetBit(P7_30_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT3));
        }
        else
        {
            /////////////////////
            // Frame Sync Mode //
            /////////////////////

            // Disable DP Freesync Mode(DRR mode)
            ScalerSetBit(P7_32_DP_RSV0, ~_BIT0, 0x00);
            SET_DRR_DSC0_ENABLED(_DISABLE);

            // Select Frame sync Mode, Set DSC DPF Source of virtual VS: BS
            ScalerSetBit(P7_30_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3), _BIT5);
        }
#endif
#endif
    }

    // Select Vblktovs Made from VS
    ScalerSetBit(P7_31_DP_OUTPUT_CTRL, ~(_BIT5 | _BIT3), 0x00);

    // Set BS to VS Delay
    ScalerDscDecoder0SetBsToVsDelay(pstDscTimingInfo);

    return _TRUE;
}
//--------------------------------------------------
// Description  : DSC0 Set Color Information
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0SetColorInfo(void)
{
    EnumInputPort enumInputPort = ScalerDscDecoderGetDxInputPort(_DSC_MAC_0);

    if(enumInputPort == _NO_INPUT_PORT)
    {
        return;
    }

    EnumPortType enumPortType = ScalerSyncGetPortType(enumInputPort);
    EnumColorSpace enumColorSpace = _COLOR_SPACE_RGB;

    // Set DP/ HDMI Color Space
    if(ScalerGetBit(P6_04_DSC_PPS_04, _BIT4) == _BIT4)
    {
        enumColorSpace = _COLOR_SPACE_RGB;
        SET_DSC0_PORCH_COLOR_RGB();
        DebugMessageDSC("DSC Color Space RGB Mode !!!", 0x00);
    }
    else
    {
        if(GET_DSC0_COLOR_NATIVE_420() == _TRUE)
        {
            enumColorSpace = _COLOR_SPACE_YCBCR420;
            DebugMessageDSC("DSC Color Space YUV420 Mode !!!", 0x00);
        }
        else if(GET_DSC0_COLOR_NATIVE_422() == _TRUE)
        {
            enumColorSpace = _COLOR_SPACE_YCBCR422;
            DebugMessageDSC("DSC Color Space YUV422 Mode !!!", 0x00);
        }
        else if(GET_DSC0_COLOR_SIMPLE_422() == _TRUE)
        {
            enumColorSpace = _COLOR_SPACE_YCBCR422;
            ScalerSetBit(P7_04_DSC_OUT_FORMAT, ~_BIT6, _BIT6);
            DebugMessageDSC("DSC Color Space YUV422 Mode !!!", 0x00);
        }
        else
        {
            enumColorSpace = _COLOR_SPACE_YCBCR444;
            DebugMessageDSC("DSC Color Space YUV444 Mode !!!", 0x00);
        }

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
        if(enumPortType == _PORT_DP)
        {
            if(ScalerDpMacDscStreamRxGetQuantizationPreValue(ScalerDscDecoderGetDpMacRxxInput(_DSC_MAC_0)) == _DP_COLOR_QUANTIZATION_LIMIT)
            {
                SET_DSC0_PORCH_COLOR_YCC_LIMIT();
            }
            else if(ScalerDpMacDscStreamRxGetQuantizationPreValue(ScalerDscDecoderGetDpMacRxxInput(_DSC_MAC_0)) == _DP_COLOR_QUANTIZATION_FULL)
            {
                SET_DSC0_PORCH_COLOR_YCC_FULL();
            }
        }
        else
#endif
        {
            SET_DSC0_PORCH_COLOR_YCC_LIMIT();
        }
    }

    // Enable Merge Buffer when Horizontal Slice Count < (_HW_DSC_MAC_MAX_SLICE_CNT / 2)
    if(GET_DSC0_HOR_SLICE_CNT() <= (_HW_DSC_MAC_MAX_SLICE_CNT >> 1))
    {
        ScalerSetBit(P7_01_DSC_DEC_CTRL_01, ~_BIT2, _BIT2);
    }
    else
    {
        ScalerSetBit(P7_01_DSC_DEC_CTRL_01, ~_BIT2, 0x00);
    }

    // Set Output UV(RB) Swap for 420 mode
    ScalerSetBit(P7_04_DSC_OUT_FORMAT, ~_BIT4, ((GET_DSC0_COLOR_NATIVE_420() == _TRUE) ? _BIT4 : 0x00));

    switch(enumPortType)
    {
        case _PORT_DP:
            ScalerDpMacDscSyncDscColorInfo(ScalerDscDecoderGetDpMacRxxInput(_DSC_MAC_0), enumColorSpace, GET_DSC0_COLOR_BPC());
            break;

        case _PORT_HDMI:
            SET_COLOR_DEPTH(enumInputPort, GET_DSC0_COLOR_BPC());
            SET_COLOR_SPACE(enumInputPort, enumColorSpace);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DSC0 Set Color Information
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0SetBsToVsDelay(StructDscTimingInfo *pstDscTimingInfo)
{
    BYTE ucDscDFGMultiple = 0;
    WORD usDscDFGHwidth = 0;
    WORD usDscTargetDlyLine = 0;
    WORD usDscTargetDlyPixel = 0;
    DWORD ulDscDFGBs2VsDelay = 0;

    // Get DSC Pre-Pixel Mode
    ucDscDFGMultiple = ScalerGetBit(P7_04_DSC_OUT_FORMAT, (_BIT3 | _BIT2)) >> 2;

    // Get Horizontal Width
    usDscDFGHwidth = GET_DSC0_PIC_WIDTH() << GET_DSC0_2X_SPEED() >> ucDscDFGMultiple;

    // Setting for BPP variation
    ScalerDscDecoder0SetInitialDecDelay();

    // BS2VS Delay (DT) TBD
    usDscTargetDlyLine = (WORD)(GET_DSC0_INIT_DEC_DELAY() / GET_DSC0_SLICE_WIDTH());
    usDscTargetDlyPixel = GET_DSC0_INIT_DEC_DELAY() - (WORD)(usDscTargetDlyLine * GET_DSC0_SLICE_WIDTH());

    // Margin
    usDscTargetDlyPixel += 300;

    // Check if Virtual VS reference BE
    if(ScalerGetBit(P7_30_DPF_CTRL_0, _BIT3) == _BIT3)
    {
        ulDscDFGBs2VsDelay = ((DWORD)(usDscTargetDlyLine) * GET_DSC0_HTOTAL()) +
                             ((DWORD)(GET_DSC0_HTOTAL() - usDscDFGHwidth) << 1) +
                             ((DWORD)usDscDFGHwidth * (GET_DSC0_HOR_SLICE_CNT() - 1) / GET_DSC0_HOR_SLICE_CNT()) +
                             ((DWORD)usDscTargetDlyPixel * GET_DSC0_HOR_SLICE_CNT() << GET_DSC0_2X_SPEED() >> ucDscDFGMultiple);

        ulDscDFGBs2VsDelay = (ulDscDFGBs2VsDelay > GET_DSC0_HTOTAL()) ? (ulDscDFGBs2VsDelay - GET_DSC0_HTOTAL()) : 0;
    }
    else
    {
        ulDscDFGBs2VsDelay = ((DWORD)(pstDscTimingInfo->usVTotal - pstDscTimingInfo->usVHeight - pstDscTimingInfo->usVStart - pstDscTimingInfo->usVFrontPorch + usDscTargetDlyLine) * GET_DSC0_HTOTAL()) +
                             ((DWORD)(GET_DSC0_HTOTAL() - usDscDFGHwidth) << 1) +
                             ((DWORD)usDscDFGHwidth * (GET_DSC0_HOR_SLICE_CNT() - 1) / GET_DSC0_HOR_SLICE_CNT()) +
                             ((DWORD)usDscTargetDlyPixel * GET_DSC0_HOR_SLICE_CNT() << GET_DSC0_2X_SPEED() >> ucDscDFGMultiple);
    }

    // Set BS to VS Delay of Odd Field
    ScalerSetByte(P7_3D_OVBLK2VS_H, LOBYTE(HIWORD(ulDscDFGBs2VsDelay)));
    ScalerSetByte(P7_3E_OVBLK2VS_M, HIBYTE(LOWORD(ulDscDFGBs2VsDelay)));
    ScalerSetByte(P7_3F_OVBLK2VS_L, LOBYTE(LOWORD(ulDscDFGBs2VsDelay)));

    if(pstDscTimingInfo->b1InterlaceOddMode == _TRUE)
    {
        ulDscDFGBs2VsDelay += GET_DSC0_HTOTAL();
    }

    // Set BS to VS Delay of Even Field
    ScalerSetByte(P7_3A_EVBLK2VS_H, LOBYTE(HIWORD(ulDscDFGBs2VsDelay)));
    ScalerSetByte(P7_3B_EVBLK2VS_M, HIBYTE(LOWORD(ulDscDFGBs2VsDelay)));
    ScalerSetByte(P7_3C_EVBLK2VS_L, LOBYTE(LOWORD(ulDscDFGBs2VsDelay)));

    DebugMessageDSC("DSC0 Target Delay Line", usDscTargetDlyLine);
    DebugMessageDSC("DSC0 Target Delay Pixel", usDscTargetDlyPixel);
    DebugMessageDSC("DSC0 Debug1", ((DWORD)(pstDscTimingInfo->usVTotal - pstDscTimingInfo->usVHeight - pstDscTimingInfo->usVStart + usDscTargetDlyLine) * GET_DSC0_HTOTAL()));
    DebugMessageDSC("DSC0 Debug2", (DWORD)(GET_DSC0_HTOTAL() - usDscDFGHwidth) << 1);
    DebugMessageDSC("DSC0 Debug3", ((DWORD)usDscDFGHwidth * (GET_DSC0_HOR_SLICE_CNT() - 1) / GET_DSC0_HOR_SLICE_CNT()));
    DebugMessageDSC("DSC0 Debug4", ((DWORD)usDscTargetDlyPixel * GET_DSC0_HOR_SLICE_CNT() << GET_DSC0_2X_SPEED() >> ucDscDFGMultiple));
    DebugMessageDSC("DSC0 Bs2VsDelay", ulDscDFGBs2VsDelay);
}

//--------------------------------------------------
// Description  : DSC0 Set Initial Decode Delay
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0SetInitialDecDelay(void)
{
    DWORD ulInitialOffSet = 6144;

    if(GET_DSC0_COLOR_NATIVE_MODE() == _TRUE)
    {
        ulInitialOffSet = 2048;

        if(GET_DSC0_COLOR_NATIVE_422() == _TRUE)
        {
            // Native422 Max Initial Dec Delay happend when bpp = 8
            SET_DSC0_INIT_DEC_DELAY((GET_DSC0_RC_MODEL_SIZE() - ulInitialOffSet + 4096 + (GET_DSC0_SLICE_WIDTH() / 2 * 5) - 4096) / 8);
        }
        else if(GET_DSC0_COLOR_NATIVE_420() == _TRUE)
        {
            if(GET_DSC0_SLICE_WIDTH() > 114)
            {
                // Native420 Max Initial Dec Delay happend when bpp = 6
                SET_DSC0_INIT_DEC_DELAY((GET_DSC0_RC_MODEL_SIZE() - ulInitialOffSet + 4096 + (GET_DSC0_SLICE_WIDTH() / 2 * 5) + (GET_DSC0_SLICE_WIDTH() / 2 * 4) - 4096) / 6);
            }
            else
            {
                // Native420 Max Initial Dec Delay happend when bpp = 6
                SET_DSC0_INIT_DEC_DELAY((GET_DSC0_RC_MODEL_SIZE() - ulInitialOffSet + 4096 + (GET_DSC0_SLICE_WIDTH() / 2 * 5) + ((114 * 3 - GET_DSC0_SLICE_WIDTH() / 2) * 4) - 4096) / 6);
            }
        }
    }
    else
    {
        if(GET_DSC0_SLICE_WIDTH() <= 1230)
        {
            ulInitialOffSet = 2048;

            // Max Initial Dec Delay happend when bpp = 12
            SET_DSC0_INIT_DEC_DELAY((GET_DSC0_RC_MODEL_SIZE() - ulInitialOffSet + 4096 + (GET_DSC0_SLICE_WIDTH() * 5) - 4096) / 12);
        }
        else
        {
            ulInitialOffSet = 6144;

            // Max Initial Dec Delay happend when bpp = 8
            SET_DSC0_INIT_DEC_DELAY((GET_DSC0_RC_MODEL_SIZE() - ulInitialOffSet + 4096 + (GET_DSC0_SLICE_WIDTH() * 5) - 4096) / 8);
        }
    }

    DebugMessageDSC("DSC0 PPS - Cal Init Dec Delay", GET_DSC0_INIT_DEC_DELAY());
}

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Dp Interlace by VBID or Measure
// Input Value  : None
// Output Value : True --> Interlace
//--------------------------------------------------
bit ScalerDscDecoder0DpInterlaceCheck(StructDscTimingInfo *pstDscTimingInfo)
{
    StructDpInfo stDpInfo = {0};

    stDpInfo.stDpTimingInfo.usVTotal = pstDscTimingInfo->usVTotal;
    stDpInfo.stDpTimingInfo.usVTotalOdd = pstDscTimingInfo->usVTotalOdd;
    stDpInfo.stDpLinkInfo.usHBsToBsCount = pstDscTimingInfo->usHBsToBsCount;
    stDpInfo.stDpLinkInfo.ulLinkClockHz = pstDscTimingInfo->ulLinkClockHz;
    stDpInfo.stDpLinkInfo.ulVBsToBsCountN = pstDscTimingInfo->ulVBsToBsCountN;
    stDpInfo.stDpLinkInfo.ulVBsToBsCountN1 = pstDscTimingInfo->ulVBsToBsCountN1;
    stDpInfo.stDpLinkInfo.b1InterlaceFieldN = pstDscTimingInfo->b1InterlaceFieldN;
    stDpInfo.stDpLinkInfo.b1InterlaceFieldN1 = pstDscTimingInfo->b1InterlaceFieldN1;

    if(ScalerDpMacDscStreamRxInterlaceCheck(ScalerDscDecoderDscMacStreamSourceDpMacRxxMapping(GET_DSC_DECODER_MAC_0_STREAM_SOURCE()), &stDpInfo) == _TRUE)
    {
        // Field Inverse Enable
        ScalerSetBit(P7_34_INTERLACE_MODE_CONFIG, ~_BIT7, _BIT7);

        pstDscTimingInfo->b1InterlaceOddMode = stDpInfo.stDpLinkInfo.b1InterlaceOddMode;

        return _TRUE;
    }
    else
    {
        // Field Inverse Disable
        ScalerSetBit(P7_34_INTERLACE_MODE_CONFIG, ~_BIT7, 0x00);

        pstDscTimingInfo->b1InterlaceOddMode = stDpInfo.stDpLinkInfo.b1InterlaceOddMode;

        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DSC0 DP CRC Calculate
// Input Value  : NenumInputPortone
// Output Value : None
//--------------------------------------------------
bit ScalerDscDecoder0DpCrcCalculate(void)
{
    EnumInputPort enumInputPort = ScalerDscDecoderGetDxInputPort(_DSC_MAC_0);

    if((ScalerDpMacStreamRxGetCRCCalculate(enumInputPort) == _TRUE) && (ScalerDscDecoder0FifoCheck(_DSC_FIFO_DELAY_CHECK) == _TRUE))
    {
        DebugMessageDSC("7. DP DSC CRC Test Start", 0);

        // Start CRC Calculation
        ScalerSetBit(P7_17_DSC_DECODER_CRC, ~(_BIT7 | _BIT6), _BIT7);

        if(ScalerTimerPollingFlagProc((GET_DSC0_STREAM_FRAME_DELAY() << 1), P7_17_DSC_DECODER_CRC, _BIT6, _TRUE) == _TRUE)
        {
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x40, ScalerGetByte(P7_19_DSC_CRC_R_L));
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x41, ScalerGetByte(P7_18_DSC_CRC_R_M));
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x42, ScalerGetByte(P7_1B_DSC_CRC_G_L));
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x43, ScalerGetByte(P7_1A_DSC_CRC_G_M));
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x44, ScalerGetByte(P7_1D_DSC_CRC_B_L));
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x45, ScalerGetByte(P7_1C_DSC_CRC_B_M));

            // Update _TEST_CRC_COUNT
            // ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x02, 0x46, 0x21);

            // Stop CRC Calculation, write 1 clear CRC Done Bit
            ScalerSetBit(P7_17_DSC_DECODER_CRC, ~(_BIT7 | _BIT6), _BIT6);

            return _TRUE;
        }
        else
        {
            // Stop CRC Calculation, write 1 clear CRC Done Bit
            ScalerSetBit(P7_17_DSC_DECODER_CRC, ~(_BIT7 | _BIT6), _BIT6);

            return _FALSE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check VGIP VS bypass for DP
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDscDecoder0CheckVgipVsBypass(void)
{
    BYTE ucDscDFGMultiple = 0;

    // Get DSC Pre-Pixel Mode
    ucDscDFGMultiple = ScalerGetBit(P7_04_DSC_OUT_FORMAT, (_BIT3 | _BIT2)) >> 2;

    // Get Hstart
    PDATA_WORD(0) = ScalerGetWord(P7_43_MN_DPF_HST_M) << ucDscDFGMultiple >> GET_DSC0_2X_SPEED();

    // Get Vstart
    PDATA_WORD(1) = ScalerGetWord(P7_4B_MN_DPF_VST_M);

    // Check for nVedia 2560x1440@144Hz timing (reduced blanking)
    if((PDATA_WORD(0) < _VGIP_IH_CAPTURE_MIN_VALUE) ||
       (PDATA_WORD(1) <= _VGIP_IV_CAPTURE_MIN_VALUE))
    {
        DebugMessageDSC("DSC VGIP VS Bypass Mode", PDATA_WORD(0));

        return _TRUE;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : DSC Stream clk regenerate
// Input Value  : enumInputPort
// Output Value : True/ False
//--------------------------------------------------
bit ScalerDscDecoder0StreamClkRegenerate(StructDscTimingInfo *pstDscTimingInfo)
{
    DWORD ulPllInputClockHz = 1;
    DWORD ulPllTargetClockHz = 1;

    EnumInputPort enumInputPort = ScalerDscDecoderGetDxInputPort(_DSC_MAC_0);
    EnumPortType enumPortType = ScalerSyncGetPortType(enumInputPort);

    /////////////////////////////
    // PLL Input Clock Setting //
    /////////////////////////////

    switch(enumPortType)
    {
#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)

            // Select DACPLL input clock source: HDMI compression clk
            ScalerSetBit(P55_A3_PLL_IN_CONTROL, ~_BIT7, _BIT7);

            // Set DACPLL input clk: HDMI compression clk (Hz)
            ulPllInputClockHz = pstDscTimingInfo->ulCompStreamClockHz;

            BYTE ucDivCount = 0;

            while(ulPllInputClockHz > 28000000)
            {
                ulPllInputClockHz /= 2;
                ucDivCount++;
            }

            if(ucDivCount > 3)
            {
                BYTE ucPreDivN = 1 << (ucDivCount - 3);
                ScalerSetBit(P55_A3_PLL_IN_CONTROL, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
                ScalerSetByte(P55_A4_DSCPLL_DIVIDER0, (ucPreDivN - 2));
                ScalerSetBit(P55_A5_DSCPLL_DIVIDER1, ~_BIT7, 0x00);
            }
            else
            {
                ScalerSetBit(P55_A3_PLL_IN_CONTROL, ~(_BIT6 | _BIT5), (ucDivCount << 5));
                ScalerSetBit(P55_A5_DSCPLL_DIVIDER1, ~_BIT7, _BIT7);
            }

            // Set HDMI input port pixel clk (0.1MHz)
            ScalerTmdsMacRxSetInputPixel(enumInputPort, (pstDscTimingInfo->ulStreamClockHz / (1 + GET_DSC0_COLOR_NATIVE_420()) / 100000));

#endif
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)

            // Select DACPLL input clock source: GDI_CLK
            ScalerSetBit(P55_A3_PLL_IN_CONTROL, ~_BIT7, 0x00);

            // Set DACPLL input clk: GDI clk (Hz)
            ulPllInputClockHz = _GDIPHY_RX_GDI_CLK_KHZ * 1000;

            // Set preDiv byPass
            ScalerSetBit(P55_A5_DSCPLL_DIVIDER1, ~_BIT7, _BIT7);

            // Set DP input port pixel clk (Hz)
            ScalerDpMacDscSetInputPixelClk(ScalerDscDecoderGetDpMacRxxInput(_DSC_MAC_0), pstDscTimingInfo->ulStreamClockHz / (1 + GET_DSC0_COLOR_NATIVE_420()));

#endif
            break;
#endif

        default:
            return _FALSE;
            break;
    }


    //////////////////////////////
    // PLL Target Clock Setting //
    //////////////////////////////

    ulPllTargetClockHz = pstDscTimingInfo->ulBufferClockHz;


    /////////////////////
    // PLL VCO Setting //
    /////////////////////

    if(ScalerDscDecoder0SetPLLFreqNf(ulPllTargetClockHz, ulPllInputClockHz) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DSC PLL Setting
// Input Value  : enumInputPort, ulPllTargetClockHz, ulPllInputClockHz
// Output Value : ulvcoFreq --> VCO Frequency Value
//--------------------------------------------------
bit ScalerDscDecoder0SetPLLFreqNf(DWORD ulPllTargetClockHz, DWORD ulPllInputClockHz)
{
    BYTE ucpllo = 0;
    BYTE ucdivs = 0;
    BYTE ucdiv_pllo = 0;
    BYTE ucdiv_divs = 0;
    DWORD ulvcoFreq = 0;
    BYTE ucNcode = 0;
    BYTE ucFcode_MSB4b = 0;
    WORD usFcode_LSB16b = 0;

    if(ulPllInputClockHz == 0)
    {
        return _FALSE;
    }

    if((ulPllTargetClockHz <= 700000000) && (ulPllTargetClockHz >= 350000000))
    {
        // Total Div = 1
        ucpllo = 0;   // DIV = 1
        ucdivs = 0;   // DIV = 1
    }
    else if((ulPllTargetClockHz < 350000000) && (ulPllTargetClockHz >= 175000000))
    {
        // Total Div = 1/2
        ucpllo = 1;   // DIV = 1/2
        ucdivs = 0;   // DIV = 1
    }
    else if((ulPllTargetClockHz < 175000000) && (ulPllTargetClockHz >= 87500000))
    {
        // Total Div = 1/4
        ucpllo = 2;   // DIV = 1/4
        ucdivs = 0;   // DIV = 1
    }
    else if((ulPllTargetClockHz < 87500000) && (ulPllTargetClockHz >= 43750000))
    {
        // Total Div = 1/8
        ucpllo = 3;   // DIV = 1/8
        ucdivs = 0;   // DIV = 1
    }
    else if((ulPllTargetClockHz < 43750000) && (ulPllTargetClockHz >= 21875000))
    {
        // Total Div = 1/16
        ucpllo = 3;   // DIV = 1/8
        ucdivs = 1;   // DIV = 1/2
    }
    else if((ulPllTargetClockHz < 21875000) && (ulPllTargetClockHz >= 10937500))
    {
        // Total Div = 1/32
        ucpllo = 3;   // DIV = 1/8
        ucdivs = 2;   // DIV = 1/4
    }
    else if((ulPllTargetClockHz < 10937500) && (ulPllTargetClockHz >= 5468750))
    {
        // Total Div = 1/64
        ucpllo = 3;   // DIV = 1/8
        ucdivs = 3;   // DIV = 1/8
    }

    ucdiv_pllo = 1 << ucpllo;
    ucdiv_divs = 1 << ucdivs;

    // Calculate N.F
    // ulvcoFreq = ulPllTargetClockHz * ucdiv_divs * ucdiv_pllo;
    // NFcode = ulvcoFreq / ulPllInputClockHz; (bypass Pre-divider)
    ulvcoFreq = ulPllTargetClockHz * ucdiv_divs *  ucdiv_pllo;
    ucNcode = ulvcoFreq / ulPllInputClockHz;
    ucFcode_MSB4b = ((ulvcoFreq - ((DWORD)ulPllInputClockHz) * ucNcode) << 4) / ulPllInputClockHz;
    usFcode_LSB16b = ScalerGlobalComputeDwordMulDiv((((ulvcoFreq - ulPllInputClockHz * ucNcode) << 4) - ucFcode_MSB4b * ulPllInputClockHz), 1UL << 16, ulPllInputClockHz);

    ScalerDscDecoder0SetPLLNfOffProc(ulvcoFreq, ucNcode, ucpllo, ucdivs);

    if(ScalerDscDecoder0SetPLLNfOnProc(ucNcode, ucFcode_MSB4b, usFcode_LSB16b) == _FALSE)
    {
        return _FALSE;
    }

    DebugMessageDSC("DSC PLL Vco Clk", ulvcoFreq);

    return _TRUE;
}

//--------------------------------------------------
// Description  : DSC PLL P Gain Clamp Setting
// Input Value  : ucPGainB3 --> p_gain_clamp_value[26:24]
//              : ucPGainB2 --> p_gain_clamp_value[15:8]
//              : ucPGainB1 --> p_gain_clamp_value[7:0]
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0SetPLLPGainClampValue(BYTE ucPGainB3, BYTE ucPGainB2, BYTE ucPGainB1)
{
    // 1st tracking : 0x0 10 00 00
    // 2nd tracking : 0x0 01 00 00
    ScalerSetByte(P55_D1_MN_PI_CODE_9, ucPGainB3);
    ScalerSetByte(P55_D2_MN_PI_CODE_A, ucPGainB2);
    ScalerSetByte(P55_D3_MN_PI_CODE_B, ucPGainB1);
    ScalerSetByte(P55_D4_MN_PI_CODE_C, 0x00);
}

//--------------------------------------------------
// Description  : DSC NF PLL P Code Spread Control Setting
// Input Value  : ucPCodeCtrl --> Enable/Disable Spread Control
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0PLLPCodeSpreadCtrl(BYTE ucPCodeCtrl)
{
    if(ucPCodeCtrl == _ON)
    {
        ScalerSetByte(P55_EF_P_CODE_SPREAD_1, 0x00);
        ScalerSetByte(P55_F0_P_CODE_SPREAD_2, 0x01);
        ScalerSetByte(P55_F1_P_CODE_SPREAD_3, 0x00);

        ScalerSetBit(P55_EE_P_CODE_SPREAD_0, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetBit(P55_EE_P_CODE_SPREAD_0, ~_BIT7, 0x00);

        ScalerSetByte(P55_EF_P_CODE_SPREAD_1, 0x00);
        ScalerSetByte(P55_F0_P_CODE_SPREAD_2, 0x00);
        ScalerSetByte(P55_F1_P_CODE_SPREAD_3, 0x00);
    }
}

//--------------------------------------------------
// Description  : DSC Tracking Active Region Setting
// Input Value  : Hs Tracking Type
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder0HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType, EnumDpHSTrackingSelect enumDpHSTrackingSelect)
{
    if(enumHSTrackingType == _DP_HS_TRACKING_FW_MODE)
    {
        // HS Tracking Region By FW Setting, Pick BS/BE as hsync tracking
        ScalerSetBit(P55_EA_HS_TRACKING_NEW_MODE1, ~(_BIT5 | _BIT4), (_BIT5 | ((enumDpHSTrackingSelect == _DP_BE_TRACKING) ? _BIT4 : 0x00)));

        // BE Start Num = 2 line
        ScalerSetBit(P55_EC_VBID_MAN_MADE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);

        // BE End Num = 2 line
        ScalerSetBit(P55_EC_VBID_MAN_MADE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // HS Tracking Region By Source VBID[0], Pick BS as hsync tracking
        ScalerSetBit(P55_EA_HS_TRACKING_NEW_MODE1, ~(_BIT5 | _BIT4), ((enumDpHSTrackingSelect == _DP_BE_TRACKING) ? _BIT4 : 0x00));
    }
}

//--------------------------------------------------
// Description  : DSC PLL Tracking Enable
// Input Value  : ulvcoFreq --> VCO Frequency(Hz)
// Output Value : True --> Tracking Stable
//--------------------------------------------------
bit ScalerDscDecoder0SetPLLTrackingNf(StructDscTimingInfo *pstDscTimingInfo)
{
    BYTE ucSscLineNumber = 0;
    WORD usHalfBSDelayCnt = 0;
    WORD usTemp = 0;
    WORD usFastLockTrakingFrames = 0;
    BYTE ucOneFrameTime = 0;
    DWORD ulVcoFreq = 0;
    BYTE ucTrackingClockDiv = 2;

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDscDecoderGetDxInputPort(_DSC_MAC_0);
#endif

    if(pstDscTimingInfo->usHTotal == 0)
    {
        return _FALSE;
    }

    // Disable Tracking
    ScalerSetBit(P55_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);

    //////////////////////////////////
    // HS Tracking Tracking Setting //
    //////////////////////////////////

    // Set HS Tracking
    ScalerSetBit(P55_E1_VS_TRACK_MODE, ~_BIT7, _BIT7);

    ulVcoFreq = (pstDscTimingInfo->ulStreamClockHz) >> (GET_DSC0_COLOR_NATIVE_420() + GET_DSC0_PIXEL_MODE());

    for(ucTrackingClockDiv = 2; ucTrackingClockDiv <= 6; ucTrackingClockDiv++)
    {
        if((ulVcoFreq << ucTrackingClockDiv) >= 350000000)
        {
            break;
        }
    }

    // Avoid Too Large PE
    ScalerSetByte(P55_DA_MN_TRACKING_DIVS, (_BIT0 << (ucTrackingClockDiv - 1)));

    // First Set Tracking Period with every line Tracking
    ScalerSetByte(P55_E3_VS_TRACK1, 0x00);

    // DE Only Mode
    if(ScalerGetBit(P7_30_DPF_CTRL_0, (_BIT5 | _BIT4)) == _BIT4)
    {
        // Get Half BS to BS delay (Counted by GDI_CLK) = HBs2BsCount / (1/2 * Link_clk) * GDI_clk / 2
        usHalfBSDelayCnt = ScalerGlobalComputeDwordMulDiv((DWORD)pstDscTimingInfo->usHBsToBsCount, (DWORD)_GDIPHY_RX_GDI_CLK_KHZ, pstDscTimingInfo->ulLinkClockHz / 1000);

#if(_DP_DE_ONLY_MODE_WITH_FULL_LAST_LINE_SUPPORT == _ON)
        // Enable Full Last Line mode for DE only mode
        ScalerSetBit(P7_30_DPF_CTRL_0, ~_BIT6, _BIT6);
#endif
    }
    else
    {
        // Get Half BS to BS delay (Counted by GDI_CLK) = HTotal / 2 * GDI_CLK(27MHz) / Stream Clock
        usHalfBSDelayCnt = ScalerGlobalComputeDwordMulDiv((DWORD)pstDscTimingInfo->usHTotal, (DWORD)_GDIPHY_RX_GDI_CLK_KHZ, pstDscTimingInfo->ulStreamClockHz / 500);
    }

    // Set Half BS to BS delay For Precision Mode
    ScalerSetBit(P55_EA_HS_TRACKING_NEW_MODE1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usHalfBSDelayCnt));
    ScalerSetByte(P55_EB_HS_TRACKING_NEW_MODE2, LOBYTE(usHalfBSDelayCnt));

    DebugMessageDSC("Half BS2BS", usHalfBSDelayCnt);

    // Check Port Type
    if(ScalerGetBit(P7_00_DSC_DEC_CTRL_00, _BIT4) == _BIT4)
    {
        // Only Enable Tracking at Active Region By Fw Mode, Tracking By BE
        ScalerDscDecoder0HSActiveTrackingMode(_DP_HS_TRACKING_FW_MODE, _DP_BE_TRACKING);
    }
    else
    {
        // Only Enable Tracking at Active Region By Fw Mode, Tracking By BS
        ScalerDscDecoder0HSActiveTrackingMode(_DP_HS_TRACKING_FW_MODE, _DP_BS_TRACKING);
    }

    // Get 1 Frame Time, unit is ms
    ucOneFrameTime = (1000UL / ((GET_DSC0_STREAM_FRAME_RATE() == 0) ? 1 : GET_DSC0_STREAM_FRAME_RATE())) + 1;

    DebugMessageDSC("Loop 1 Frame Time", ucOneFrameTime);

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    // Check DSC ALPM Status Enable
    if(ScalerDpRxAuxlessAlpmGetEnable(enumInputPort) == _ENABLE)
    {
        DebugMessageDSC("DSC ALPM Enable", 0x00);

        // Set alpm_tracking_en, stop_tracking_under_alpm when rfb_update = 0
        ScalerSetBit(P55_E0_VS_TRACK_EN, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    }
    else
#endif
    {
        DebugMessageDSC("DSC ALPM Disable", 0x00);

        // Set alpm_tracking_en, stop_tracking_under_alpm when rfb_update = 0
        ScalerSetBit(P55_E0_VS_TRACK_EN, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    }

    /////////////////////////////////
    // 1st Tracking Fast Lock Mode //
    /////////////////////////////////

    // I Gain Clamp = 0x00 01 00 00

    // P Gain Clamp = 0x00 10 00 00
    ScalerDscDecoder0SetPLLPGainClampValue(0x00, 0x10, 0x00);

    // P Code = 0x0 00 FF FF
    ScalerSetBit(P55_C9_MN_PI_CODE_1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P55_CA_MN_PI_CODE_2, 0x00);
    ScalerSetByte(P55_CB_MN_PI_CODE_3, 0xFF);
    ScalerSetByte(P55_CC_MN_PI_CODE_4, 0xFF);

    // I Code = 0x08
    ScalerSetByte(P55_C8_MN_PI_CODE_0, 0x08);

    // DE Only Mode
    if(ScalerGetBit(P7_30_DPF_CTRL_0, (_BIT5 | _BIT4)) == _BIT4)
    {
        usFastLockTrakingFrames = 5;
    }
    else
    {
        usFastLockTrakingFrames = 3;
    }

    // Set PE Nonlock Threshold
    ScalerSetByte(P55_E4_VS_TRACK2, 0x3F);

    // Check Port Type
    if(ScalerGetBit(P7_00_DSC_DEC_CTRL_00, _BIT4) == _BIT4)
    {
        // Enable Fast Lock Mode
        ScalerSetBit(P55_E1_VS_TRACK_MODE, ~(_BIT3 | _BIT2 | _BIT1), _BIT3);

        // If not DRR mode, Enable P Gain Spread
        if(ScalerDscDecoder0GetDrrEnable() == _FALSE)
        {
            // Enable P Gain Spread
            ScalerDscDecoder0PLLPCodeSpreadCtrl(_ON);
        }
    }
    else
    {
        // Set Tracking All BS
        ScalerSetBit(P55_E1_VS_TRACK_MODE, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

        // Disable P Gain Spread
        ScalerDscDecoder0PLLPCodeSpreadCtrl(_OFF);

        // Enable Tracking
        ScalerSetBit(P55_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), _BIT7);

        usTemp = 0;

        // Waiting for Stream Clk Stable
        while(usTemp < 10)
        {
            // Clear PE Max Record
            ScalerSetByte(P55_E5_VS_TRACK3, 0xFF);

            // Clear PE Flag
            ScalerSetBit(P55_E0_VS_TRACK_EN, ~_BIT0, _BIT0);

            // Delay 1 Frame
            ScalerTimerDelayXms(ucOneFrameTime);

            usTemp++;

            // Fast lock mode tracking at least 2 Frames
            if((usTemp >= usFastLockTrakingFrames) && ((ScalerGetBit(P55_E0_VS_TRACK_EN, _BIT0) == 0x00)))
            {
                break;
            }
        }

        DebugMessageDSC("1st PE Loop", usTemp);
        DebugMessageDSC("1st PE Max Record", ScalerGetByte(P55_E5_VS_TRACK3));

        // Check PE Status
        if(ScalerGetByte(P55_E5_VS_TRACK3) == 0xFF)
        {
            DebugMessageDSC("Change To BE tracking", 0x00);

            // Disable Tracking
            ScalerSetBit(P55_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);

            // Only Enable Tracking at Active Region By Fw Mode, Tracking By BE
            ScalerDscDecoder0HSActiveTrackingMode(_DP_HS_TRACKING_FW_MODE, _DP_BE_TRACKING);

            // Set Fast Lock Mode
            ScalerSetBit(P55_E1_VS_TRACK_MODE, ~(_BIT3 | _BIT2 | _BIT1), _BIT3);

            // Enable Tracking
            ScalerSetBit(P55_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), _BIT7);

            usTemp = 0;

            // Waiting for Stream Clk Stable
            while(usTemp < 10)
            {
                // Clear PE Max Record
                ScalerSetByte(P55_E5_VS_TRACK3, 0xFF);

                // Clear PE Flag
                ScalerSetBit(P55_E0_VS_TRACK_EN, ~_BIT0, _BIT0);

                // Delay 1 Frame
                ScalerTimerDelayXms(ucOneFrameTime);

                usTemp++;

                // Fast lock mode tracking at least 2 Frames
                if((usTemp >= usFastLockTrakingFrames) && ((ScalerGetBit(P55_E0_VS_TRACK_EN, _BIT0) == 0x00)))
                {
                    break;
                }
            }

            DebugMessageDSC("Retry 1st PE Loop", usTemp);
            DebugMessageDSC("Retry 1st PE Max Record", ScalerGetByte(P55_E5_VS_TRACK3));
        }

        // Disable Tracking
        ScalerSetBit(P55_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);

        /////////////////////////////////
        // 2nd Tracking Presicion Mode //
        /////////////////////////////////

        // I Gain Clamp = 0x00 10 00 00

        // P Gain Clamp = 0x00 10 00 00
        ScalerDscDecoder0SetPLLPGainClampValue(0x00, 0x10, 0x00);

        // P Code = 0x0 00 FF FF
        ScalerSetBit(P55_C9_MN_PI_CODE_1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P55_CA_MN_PI_CODE_2, 0x00);
        ScalerSetByte(P55_CB_MN_PI_CODE_3, 0xFF);
        ScalerSetByte(P55_CC_MN_PI_CODE_4, 0xFF);

        // I Code = 0x04
        ScalerSetByte(P55_C8_MN_PI_CODE_0, 0x04);

        // If not DRR mode, Enable P Gain Spread
        if(ScalerDscDecoder0GetDrrEnable() == _FALSE)
        {
            ScalerDscDecoder0PLLPCodeSpreadCtrl(_ON);
        }

        // Set PE Nonlock Threshold
        ScalerSetByte(P55_E4_VS_TRACK2, 0x1F);

        // Check if Fast Lock Mode
        if(ScalerGetBit(P55_E1_VS_TRACK_MODE, _BIT3) == _BIT3)
        {
            // Set Precision Mode
            ScalerSetBit(P55_E1_VS_TRACK_MODE, ~(_BIT3 | _BIT2 | _BIT1), _BIT2);
        }
    }

    // Set manual tracking Htotal
    ScalerSetBit(P55_F2_DSC_HTT_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((GET_DSC0_HTOTAL() >> 8) & 0x3F));
    ScalerSetByte(P55_F3_DSC_HTT_1, (GET_DSC0_HTOTAL() & 0xFF));

    // Enable manual Htotal
    ScalerSetBit(P55_F2_DSC_HTT_0, ~_BIT7, _BIT7);

    // Enable Tracking
    ScalerSetBit(P55_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), _BIT7);

    usTemp = 0;

    // Waiting for Stream Clk Stable
    do
    {
        // Clear PE Max Record
        ScalerSetByte(P55_E5_VS_TRACK3, 0xFF);

        // Clear PE Flag
        ScalerSetBit(P55_E0_VS_TRACK_EN, ~_BIT0, _BIT0);

        // Delay 1 Frame
        ScalerTimerDelayXms(ucOneFrameTime);

        usTemp++;
    }
    while((ScalerGetBit(P55_E0_VS_TRACK_EN, _BIT0) == _BIT0) && (usTemp < 10));

    DebugMessageDSC("2nd PE Loop", usTemp);
    DebugMessageDSC("2nd PE Max Record", ScalerGetByte(P55_E5_VS_TRACK3));

    // Get How Many Lines Per SSC Period
    // SSC(33khz)'s time to update.
    ucSscLineNumber = (BYTE)((pstDscTimingInfo->ulStreamClockHz / pstDscTimingInfo->usHTotal + 11500) / 33000);

    if(ucSscLineNumber > 0)
    {
        ucSscLineNumber--;
    }

    // Set Tracking Period
    ScalerSetByte(P55_E3_VS_TRACK1, ucSscLineNumber);

    DebugMessageDSC("Tracking Per Line", ScalerGetByte(P55_E3_VS_TRACK1));

#if(_DP_DE_ONLY_MODE_WITH_FULL_LAST_LINE_SUPPORT == _OFF)
    // DE Only Mode
    if(ScalerGetBit(P7_30_DPF_CTRL_0, (_BIT5 | _BIT4)) == _BIT4)
    {
        // Disable Tracking
        ScalerSetBit(P55_E0_VS_TRACK_EN, ~(_BIT7 | _BIT0), 0x00);
    }
#endif


    /////////////////////////////////////
    // Display Format Generator Enable //
    /////////////////////////////////////

    // Enable DSC Decoder
    ScalerDscDecoder0DecEnable();

    // Start Generate Display Format
    ScalerSetBit(P7_30_DPF_CTRL_0, ~_BIT7, _BIT7);

    // Delay 2 Frame Time for PG Stable
    ScalerTimerDelayXms(ucOneFrameTime << 1);

    return _TRUE;
}

#endif // End of #if(_DSC_MAC_DECODER_0_SUPPORT == _ON)

