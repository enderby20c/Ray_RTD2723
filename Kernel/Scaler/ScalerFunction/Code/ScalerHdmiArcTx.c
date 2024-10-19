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
// ID Code      : ScalerHdmiArcTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_HDMIARCTX__

#include "ScalerFunctionInclude.h"
#include "HdmiArcTx/ScalerHdmiArcTx.h"

#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
EnumAudioArcMode g_enumHdmiArcTxOsdArcMode;
EnumArcAudioChanelStatus g_enumHdmiArcTxOsdChannelNum;
StructAudioInterfaceInfoForArc g_stHdmiArcTxAudioSourceInfo;
volatile StructHdmiArcTxCtrlInfo g_stHdmiArcTxCtrlInfo;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxDisable(void)
{
    ScalerHdmiArcTxPowerOff();

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    CLR_HDMI_ARC_TX_EARC_AUDIO_LATENCY_CHANGE_EVENT();
    CLR_HDMI_ARC_TX_EARC_CDS_CHANGE_EVENT();
    CLR_HDMI_ARC_TX_EARC_LOST_HEARTBEAT_EVENT();
    CLR_HDMI_ARC_TX_EARC_DISC_TIMEOUT_EVENT();
    CLR_HDMI_ARC_TX_EARC_DISCOVERY_EVENT();
#endif
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Power Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxPowerOff(void)
{
    ScalerHdmiArcTxPhyPowerOff();

    ScalerHdmiArcTxReset();

    // disable CMDC
    ScalerSetBit(PE5_B4_EARC_TX_CMDC_DISC_CTRL_0, ~(_BIT7 | _BIT6), 0x00);

    // disable eARC Tx MAC
    ScalerSetBit(PE5_00_EARC_TX_CKGEN_CTRL_0, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxReset(void)
{
    // disable BMC encoder
    ScalerSetBit(PE5_B2_EARC_TX_DMAC_FRAME_ENC_0, ~_BIT7, 0x00);

    // disble ECC encoder
    ScalerSetBit(PE5_B0_EARC_TX_DMAC_ECC_CTRL_0, ~_BIT7, 0x00);

    // disble Audio FIFO
    ScalerSetBit(PE5_60_AUDIO_TX_FIFO_CTRL_0, ~(_BIT7 | _BIT6), 0x00);

    // Disable MN Tracking
    ScalerSetBit(PE5_73_AUDIO_MN_TRACK_CTRL_0, ~(_BIT7 | _BIT0), _BIT0);

    // disable SDM
    ScalerSetBit(PE5_70_AUDIO_NF_PLL_SDM, ~(_BIT7 | _BIT5 | _BIT4), _BIT5);

    // disable SPDIF in converter
    ScalerSetBit(PE5_05_SPDIF_CONVERT_CTRL_0, ~_BIT7, 0x00);

    // Clear No Z Flag
    ScalerSetBit(PE5_07_SPDIF_IN_BMC_DEC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // reset CS in table & done flag
    ScalerSetBit(PE5_10_SPDIF_IN_CH_STATUS_CTRL_0, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));

    // reset CS regen table
    ScalerSetBit(PE5_28_CH_STATUS_REGEN_TABLE_CTRL, ~_BIT7, _BIT7);

    // reset U regen table
    ScalerSetBit(PE5_29_U_MSG_REGEN_TABLE_CTRL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // stop U regen
    ScalerSetBit(PE5_3A_VUC_INSERT_CTRL_2, ~(_BIT7 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT4);

    // disable b regen ref papb
    ScalerSetBit(PE5_32_PREAMBLE_B_REGEN_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

    // BVUC bypass
    ScalerSetBit(PE5_31_PREAMBLE_B_REGEN_CTRL_0, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(PE5_38_VUC_INSERT_CTRL_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
}

//--------------------------------------------------
// Description  : Scaler HDMI Arc Tx ARC Mode Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxArcModeInitial(void)
{
    ScalerHdmiArcTxPhyInitial();

    // enable eARC Tx MAC
    ScalerSetBit(PE5_00_EARC_TX_CKGEN_CTRL_0, ~_BIT7, _BIT7);

    // spdif_512fs_clk_src_sel = CK_EARC_1X(from eARC Tx N.F PLL)
    ScalerSetBit(PE5_00_EARC_TX_CKGEN_CTRL_0, ~_BIT4, 0x00);

    SET_HDMI_ARC_TX_LINK_MODE(_ARC_MODE);

    DebugMessageArcTx("[ARC Tx] ARC Initial", 0x00);
}

//--------------------------------------------------
// Description  : Scaler HDMI Arc Tx ARC Mode Output Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxArcModeOutputReset(void)
{
    ScalerHdmiArcTxPhySetArcMode(_DISABLE);
    ScalerHdmiArcTxPhyPllPowerOff();
    ScalerHdmiArcTxReset();
}

//--------------------------------------------------
// Description  : Scaler HDMI Arc Tx Audio Output Format Setting
// Input Value  : EnumArcAudioChanelStatus, StructAudioInterfaceInfoForArc
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxAudioOutputFormatSetting(EnumArcAudioChanelStatus enumArcOsdChannelNum, StructAudioInterfaceInfoForArc stArcAudioSourceInfo)
{
    // Get ARC OSD Channel Num
    g_enumHdmiArcTxOsdChannelNum = enumArcOsdChannelNum;

    // Get Audio Input Info
    g_stHdmiArcTxAudioSourceInfo = stArcAudioSourceInfo;

    DebugMessageArcTx("[ARC Tx] Audio Input FS", GET_HDMI_ARC_TX_SOURCE_SAMPLING_FREQ());
    DebugMessageArcTx("[ARC Tx] Audio Input Channel Num", GET_HDMI_ARC_TX_SOURCE_CHANNEL_NUM());
    DebugMessageArcTx("[ARC Tx] Audio Input Coding Type", GET_HDMI_ARC_TX_SOURCE_CODING_TYPE());
    DebugMessageArcTx("[ARC Tx] Audio Input Word Length", GET_HDMI_ARC_TX_SOURCE_WORD_LENGTH());

    SET_HDMI_ARC_TX_AUDIO_OUTPUT_CODING_TYPE(GET_HDMI_ARC_TX_SOURCE_CODING_TYPE());
    SET_HDMI_ARC_TX_AUDIO_OUTPUT_WORD_LENGTH(GET_HDMI_ARC_TX_SOURCE_WORD_LENGTH());

    if(GET_HDMI_ARC_TX_SOURCE_CHANNEL_NUM() <= _AUDIO_CHANNEL_COUNT_2)
    {
        DebugMessageArcTx("[ARC Tx] _AUDIO_CHANNEL_COUNT_2", 0x00);

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
        if(GET_HDMI_ARC_TX_LINK_MODE() == _EARC_MODE)
        {
            if((GET_HDMI_ARC_TX_SOURCE_CODING_TYPE() == _AUDIO_NON_LPCM) && (GET_HDMI_ARC_TX_SOURCE_SAMPLING_FREQ() <= _AUDIO_FREQ_PACKET_192K) &&
               (GET_HDMI_ARC_TX_OSD_CHANNEL_NUM() == _ARC_AUDIO_8CH) && (_COMPRESSED_B_LAYOUT_SUPPORT == _ON))
            {
                SET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ(ScalerHdmiArcTxAudioSamplingFreqMulti4(GET_HDMI_ARC_TX_SOURCE_SAMPLING_FREQ()));
                SET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE(_AUDIO_LAYOUT_8CH);
                SET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM(_AUDIO_CHANNEL_COUNT_2);

                DebugMessageArcTx("[ARC Tx] _AUDIO_LAYOUT_8CH", 0x00);
            }
            else
            {
                SET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ(GET_HDMI_ARC_TX_SOURCE_SAMPLING_FREQ());
                SET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE(_AUDIO_LAYOUT_2CH);
                SET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM(_AUDIO_CHANNEL_COUNT_2);

                DebugMessageArcTx("[ARC Tx] _AUDIO_LAYOUT_2CH", 0x00);
            }
        }
        else
#endif
        {
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ(GET_HDMI_ARC_TX_SOURCE_SAMPLING_FREQ());
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE(_AUDIO_LAYOUT_2CH);
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM(_AUDIO_CHANNEL_COUNT_2);

            DebugMessageArcTx("[ARC Tx] _AUDIO_LAYOUT_2CH", 0x00);
        }
    }
    else if(GET_HDMI_ARC_TX_SOURCE_CHANNEL_NUM() <= _AUDIO_CHANNEL_COUNT_4)
    {
        DebugMessageArcTx("[ARC Tx] _AUDIO_CHANNEL_COUNT_4", 0x00);

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
        if((GET_HDMI_ARC_TX_LINK_MODE() == _EARC_MODE) && (GET_HDMI_ARC_TX_OSD_CHANNEL_NUM() != _ARC_AUDIO_2CH))
        {
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ(ScalerHdmiArcTxAudioSamplingFreqMulti4(GET_HDMI_ARC_TX_SOURCE_SAMPLING_FREQ()));
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE(_AUDIO_LAYOUT_8CH);
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM(_AUDIO_CHANNEL_COUNT_4);

            DebugMessageArcTx("[ARC Tx] _AUDIO_LAYOUT_8CH", 0x00);
        }
        else
#endif
        {
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ(GET_HDMI_ARC_TX_SOURCE_SAMPLING_FREQ());
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE(_AUDIO_LAYOUT_2CH);
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM(_AUDIO_CHANNEL_COUNT_2);

            DebugMessageArcTx("[ARC Tx] _AUDIO_LAYOUT_2CH", 0x00);
        }
    }
    else if(GET_HDMI_ARC_TX_SOURCE_CHANNEL_NUM() <= _AUDIO_CHANNEL_COUNT_6)
    {
        DebugMessageArcTx("[ARC Tx] _AUDIO_CHANNEL_COUNT_6", 0x00);

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
        if((GET_HDMI_ARC_TX_LINK_MODE() == _EARC_MODE) && (GET_HDMI_ARC_TX_OSD_CHANNEL_NUM() != _ARC_AUDIO_2CH))
        {
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ(ScalerHdmiArcTxAudioSamplingFreqMulti4(GET_HDMI_ARC_TX_SOURCE_SAMPLING_FREQ()));
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE(_AUDIO_LAYOUT_8CH);
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM(_AUDIO_CHANNEL_COUNT_6);

            DebugMessageArcTx("[ARC Tx] _AUDIO_LAYOUT_8CH", 0x00);
        }
        else
#endif
        {
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ(GET_HDMI_ARC_TX_SOURCE_SAMPLING_FREQ());
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE(_AUDIO_LAYOUT_2CH);
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM(_AUDIO_CHANNEL_COUNT_2);

            DebugMessageArcTx("[ARC Tx] _AUDIO_LAYOUT_2CH", 0x00);
        }
    }
    else
    {
        DebugMessageArcTx("[ARC Tx] _AUDIO_CHANNEL_COUNT_8", 0x00);

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
        if((GET_HDMI_ARC_TX_LINK_MODE() == _EARC_MODE) && (GET_HDMI_ARC_TX_OSD_CHANNEL_NUM() != _ARC_AUDIO_2CH))
        {
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ(ScalerHdmiArcTxAudioSamplingFreqMulti4(GET_HDMI_ARC_TX_SOURCE_SAMPLING_FREQ()));
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE(_AUDIO_LAYOUT_8CH);
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM(_AUDIO_CHANNEL_COUNT_8);

            DebugMessageArcTx("[ARC Tx] _AUDIO_LAYOUT_8CH", 0x00);
        }
        else
#endif
        {
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ(GET_HDMI_ARC_TX_SOURCE_SAMPLING_FREQ());
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE(_AUDIO_LAYOUT_2CH);

            DebugMessageArcTx("[ARC Tx] _AUDIO_LAYOUT_2CH", 0x00);
            SET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM(_AUDIO_CHANNEL_COUNT_2);
        }
    }
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Stream Handler
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerHdmiArcTxStreamHandler(void)
{
    // Audio Fifo initial before enable
    if(ScalerGetBit(PE5_60_AUDIO_TX_FIFO_CTRL_0, _BIT7) == 0x00)
    {
        if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() > _AUDIO_FREQ_PACKET_192K)
        {
            DebugMessageArcTx("[ARC Tx] Ouput Sampling Freq > 192K over ARC limit", GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ());

            return _FALSE;
        }

        ScalerHdmiArcTxSpdifInputConverterInitial();

        // TODO: need check with DIC
        ScalerTimerDelayXms(10);

        // Wait at least 10ms for waiting HW que 192bit channel status
        if(ScalerTimerPollingFlagProc(10, PE5_10_SPDIF_IN_CH_STATUS_CTRL_0, _BIT3, _TRUE) == _FALSE)
        {
            DebugMessageArcTx("[ARC Tx] HW que 192bit rx channel status fail", 0x00);

            return _FALSE;
        }

        // pop cs table
        ScalerSetBit(PE5_10_SPDIF_IN_CH_STATUS_CTRL_0, ~(_BIT3 | _BIT2), _BIT2);
        DELAY_5US();

        CLR_HDMI_ARC_TX_SOURCE_CH_STATUS_CHANGE_EVENT();

        // enable cs change irq
        ScalerSetBit(PE5_13_SPDIF_IN_CH_STATUS_CTRL_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        ScalerHdmiArcTxSetAudioOutputConfig();

        ScalerHdmiArcTxPhySetPll();

        if(ScalerHdmiArcTxSetMnTracking() == _FALSE)
        {
            return _FALSE;
        }

        if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE() == _AUDIO_LAYOUT_2CH)
        {
            // Set Audio FIFO Depth = 0x0E
            ScalerSetByte(PE5_62_AUDIO_TX_FIFO_CTRL_2, 0x0E);
        }
        else
        {
            // Set Audio FIFO Depth = 0x1F
            ScalerSetByte(PE5_62_AUDIO_TX_FIFO_CTRL_2, 0x1F);
        }

        // Enable Audio Tx FIFO(normal output)
        ScalerSetBit(PE5_60_AUDIO_TX_FIFO_CTRL_0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    else
    {
        // Wait depth reaching target depth
        if(ScalerGetBit(PE5_61_AUDIO_TX_FIFO_CTRL_1, _BIT1) == _BIT1)
        {
            if(ScalerHdmiArcTxMonitorFifoStatus() == _FALSE)
            {
                // Disable Audio Tx FIFO
                ScalerSetBit(PE5_60_AUDIO_TX_FIFO_CTRL_0, ~(_BIT7 | _BIT6), 0x00);

                return _FALSE;
            }

            if(ScalerGetBit(PE5_B2_EARC_TX_DMAC_FRAME_ENC_0, _BIT7) == 0x00)
            {
                // frame encoder enable
                ScalerSetBit(PE5_B2_EARC_TX_DMAC_FRAME_ENC_0, ~_BIT7, _BIT7);

                // set Tx phy to ARC Mode & output enable
                // ScalerHdmiArcTxPhySetArcMode(_ENABLE);
            }

            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx SPIDF Input Converter Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxSpdifInputConverterInitial(void)
{
    // Set Audio Top Input Source Mux
    switch(ScalerAudioGetDigitalAudioPort(_AUDIO_ARC_OUT))
    {
        case _AUDIO_FROM_RX0_PORT:

            // mux_arc_src_in = Rx0 DP
            ScalerSetBit(P6F_01_MUX_DA_DVC_IN, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // mux_arc_wd_src = Rx0 DP
            ScalerSetBit(P6F_11_ADI_DUMMY_1, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

            break;

        case _AUDIO_FROM_RX1_PORT:

            // mux_arc_src_in = Rx1 DP
            ScalerSetBit(P6F_01_MUX_DA_DVC_IN, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

            // mux_arc_wd_src = Rx1 DP
            ScalerSetBit(P6F_11_ADI_DUMMY_1, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

            break;

        case _AUDIO_FROM_RX2_PORT:

            // mux_arc_src_in = Rx2 DP
            ScalerSetBit(P6F_01_MUX_DA_DVC_IN, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

            // mux_arc_wd_src = Rx2 DP
            ScalerSetBit(P6F_11_ADI_DUMMY_1, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

            break;

        case _AUDIO_FROM_RX3_PORT:

            // mux_arc_src_in = Rx3 HDMI
            ScalerSetBit(P6F_01_MUX_DA_DVC_IN, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

            // mux_arc_wd_src = Rx3 HDMI
            ScalerSetBit(P6F_11_ADI_DUMMY_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

            break;

        case _AUDIO_FROM_RX4_PORT:

            // mux_arc_src_in = Rx4 HDMI
            ScalerSetBit(P6F_01_MUX_DA_DVC_IN, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

            // mux_arc_wd_src = Rx4 HDMI
            ScalerSetBit(P6F_11_ADI_DUMMY_1, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

            break;

        default:

            // mux_arc_src_in = reseved(Rx4 HDMI)
            ScalerSetBit(P6F_01_MUX_DA_DVC_IN, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            // mux_arc_wd_src = reseved(Rx4 HDMI)
            ScalerSetBit(P6F_11_ADI_DUMMY_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

            break;
    }

    if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE() == _AUDIO_LAYOUT_2CH)
    {
        // spdif_in_ch_num = 2ch
        ScalerSetBit(PE5_05_SPDIF_CONVERT_CTRL_0, ~(_BIT6 | _BIT5), 0x00);
    }
    // (GET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE() == _AUDIO_LAYOUT_8CH)
    else
    {
        // spdif_in_ch_num = 8ch
        ScalerSetBit(PE5_05_SPDIF_CONVERT_CTRL_0, ~(_BIT6 | _BIT5), _BIT6);
    }

    if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM() == _AUDIO_CHANNEL_COUNT_2)
    {
        // spdif_in_ch01_en = enable(ch23/45/67 disable)
        ScalerSetBit(PE5_05_SPDIF_CONVERT_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

        // spdif_out_ch_en = ch01 enable
        ScalerSetByte(PE5_0B_SPDIF_OUT_CH_CTRL, 0x03);
    }
    else if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM() == _AUDIO_CHANNEL_COUNT_4)
    {
        // spdif_in_ch01_en = enable(45/67 disable)
        ScalerSetBit(PE5_05_SPDIF_CONVERT_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

        // spdif_out_ch_en = ch01~23 enable
        ScalerSetByte(PE5_0B_SPDIF_OUT_CH_CTRL, 0x0F);
    }
    else if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM() == _AUDIO_CHANNEL_COUNT_6)
    {
        // spdif_in_ch01_en = enable(67 disable)
        ScalerSetBit(PE5_05_SPDIF_CONVERT_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

        // spdif_out_ch_en = ch01~45 enable
        ScalerSetByte(PE5_0B_SPDIF_OUT_CH_CTRL, 0x3F);
    }
    // (GET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM() == _AUDIO_CHANNEL_COUNT_8)
    else
    {
        // spdif_in_ch01_en = all enable
        ScalerSetBit(PE5_05_SPDIF_CONVERT_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // spdif_out_ch_en = all enable
        ScalerSetByte(PE5_0B_SPDIF_OUT_CH_CTRL, 0xFF);
    }

    // spdif_in_analy_src_mux = from spdif converter
    ScalerSetBit(PE5_0D_SPDIF_IN_ANALY_SRC_MUX, ~_BIT7, 0x00);

    // b_align_ch_sel = ch01
    ScalerSetBit(PE5_06_SPDIF_CONVERT_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // enable spdif converter
    ScalerSetBit(PE5_05_SPDIF_CONVERT_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(PE5_05_SPDIF_CONVERT_CTRL_0, ~_BIT7, _BIT7);

    // clear rx cs table done flag
    ScalerSetBit(PE5_10_SPDIF_IN_CH_STATUS_CTRL_0, ~(_BIT3 | _BIT2), _BIT3);

    // reset spdif_fifo_unstable flag
    ScalerSetBit(PE5_06_SPDIF_CONVERT_CTRL_1, ~_BIT5, _BIT5);
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Audio Sampling Freq Multipled by 4
// Input Value  : EnumArcAudioFreqType
// Output Value : EnumArcAudioFreqType
//--------------------------------------------------
EnumAudioSamplingFreqPacket ScalerHdmiArcTxAudioSamplingFreqMulti4(EnumAudioSamplingFreqPacket enumAudioFreq)
{
    EnumAudioSamplingFreqPacket enumAudioFreqMulti4 = _AUDIO_FREQ_PACKET_NO_AUDIO;

    switch(enumAudioFreq)
    {
        case _AUDIO_FREQ_PACKET_32K:

            enumAudioFreqMulti4 = _AUDIO_FREQ_PACKET_128K;
            break;

        case _AUDIO_FREQ_PACKET_44_1K:

            enumAudioFreqMulti4 = _AUDIO_FREQ_PACKET_176_4K;
            break;

        case _AUDIO_FREQ_PACKET_48K:

            enumAudioFreqMulti4 = _AUDIO_FREQ_PACKET_192K;
            break;

        case _AUDIO_FREQ_PACKET_64K:

            enumAudioFreqMulti4 = _AUDIO_FREQ_PACKET_256K;
            break;

        case _AUDIO_FREQ_PACKET_88_2K:

            enumAudioFreqMulti4 = _AUDIO_FREQ_PACKET_352_8K;
            break;

        case _AUDIO_FREQ_PACKET_96K:

            enumAudioFreqMulti4 = _AUDIO_FREQ_PACKET_384K;
            break;

        case _AUDIO_FREQ_PACKET_128K:

            enumAudioFreqMulti4 = _AUDIO_FREQ_PACKET_512K;
            break;

        case _AUDIO_FREQ_PACKET_176_4K:

            enumAudioFreqMulti4 = _AUDIO_FREQ_PACKET_705_6K;
            break;

        case _AUDIO_FREQ_PACKET_192K:

            enumAudioFreqMulti4 = _AUDIO_FREQ_PACKET_768K;
            break;

        default:

            enumAudioFreqMulti4 = enumAudioFreq;
            DebugMessageArcTx("[ARC Tx] Audio Sampling Feq is too fast to Multi4", 0);
            break;
    }

    return enumAudioFreqMulti4;
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Audio Sampling Freq Div by 4
// Input Value  : EnumArcAudioFreqType
// Output Value : EnumArcAudioFreqType
//--------------------------------------------------
EnumAudioSamplingFreqPacket ScalerHdmiArcTxAudioSamplingFreqDiv4(EnumAudioSamplingFreqPacket enumAudioFreq)
{
    EnumAudioSamplingFreqPacket enumAudioFreqDiv4 = _AUDIO_FREQ_PACKET_NO_AUDIO;

    switch(enumAudioFreq)
    {
        case _AUDIO_FREQ_PACKET_128K:

            enumAudioFreqDiv4 = _AUDIO_FREQ_PACKET_32K;
            break;

        case _AUDIO_FREQ_PACKET_176_4K:

            enumAudioFreqDiv4 = _AUDIO_FREQ_PACKET_44_1K;
            break;

        case _AUDIO_FREQ_PACKET_192K:

            enumAudioFreqDiv4 = _AUDIO_FREQ_PACKET_48K;
            break;

        case _AUDIO_FREQ_PACKET_256K:

            enumAudioFreqDiv4 = _AUDIO_FREQ_PACKET_64K;
            break;

        case _AUDIO_FREQ_PACKET_352_8K:

            enumAudioFreqDiv4 = _AUDIO_FREQ_PACKET_88_2K;
            break;

        case _AUDIO_FREQ_PACKET_384K:

            enumAudioFreqDiv4 = _AUDIO_FREQ_PACKET_96K;
            break;

        case _AUDIO_FREQ_PACKET_512K:

            enumAudioFreqDiv4 = _AUDIO_FREQ_PACKET_128K;
            break;

        case _AUDIO_FREQ_PACKET_705_6K:

            enumAudioFreqDiv4 = _AUDIO_FREQ_PACKET_176_4K;
            break;

        case _AUDIO_FREQ_PACKET_768K:

            enumAudioFreqDiv4 = _AUDIO_FREQ_PACKET_192K;
            break;

        default:

            enumAudioFreqDiv4 = enumAudioFreq;
            DebugMessageArcTx("[ARC Tx] Audio Sampling Feq is too slow to Div4", 0);
            break;
    }

    return enumAudioFreqDiv4;
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Set Audio Output Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxSetAudioOutputConfig(void)
{
    // reset BVUC regen
    ScalerSetBit(PE5_31_PREAMBLE_B_REGEN_CTRL_0, ~(_BIT6 | _BIT5), _BIT5);
    ScalerSetBit(PE5_31_PREAMBLE_B_REGEN_CTRL_0, ~(_BIT6 | _BIT5), 0x00);

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    if(GET_HDMI_ARC_TX_LINK_MODE() == _EARC_MODE)
    {
        // Load Chanel Status
        ScalerHdmiArcTxEarcLoadChannelStatus();

        // LPCM
        if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_CODING_TYPE() == _AUDIO_LPCM)
        {
            // bch_interleave_en = disable
            ScalerSetBit(PE5_B0_EARC_TX_DMAC_ECC_CTRL_0, ~_BIT7, 0x00);

            // v force 0
            ScalerSetBit(PE5_39_VUC_INSERT_CTRL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }
        else
        {
            // bch_interleave_en = enable
            ScalerSetBit(PE5_B0_EARC_TX_DMAC_ECC_CTRL_0, ~_BIT7, _BIT7);

            // v force 1
            ScalerSetBit(PE5_39_VUC_INSERT_CTRL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // zero padding = 4 subframe
            ScalerSetByte(PE5_37_PREAMBLE_B_REGEN_CTRL_6, 0x02);

            if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE() == _AUDIO_LAYOUT_8CH)
            {
                ScalerSetBit(PE5_32_PREAMBLE_B_REGEN_CTRL_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1), _BIT1);
            }

            // enable b regen ref papb
            ScalerSetBit(PE5_32_PREAMBLE_B_REGEN_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);
        }

        // Set BVUC = regen(U force 0)
        ScalerSetBit(PE5_31_PREAMBLE_B_REGEN_CTRL_0, ~(_BIT7 | _BIT6), _BIT7);
        ScalerSetBit(PE5_38_VUC_INSERT_CTRL_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5 | _BIT4));
    }
    else
#endif
    {
        // BVUC bypass
        ScalerSetBit(PE5_31_PREAMBLE_B_REGEN_CTRL_0, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(PE5_38_VUC_INSERT_CTRL_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }

    ScalerTimerDelayXms(10);
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Monitor Tx FIFO Status
// Input Value  : None
// Output Value : _UNSTABLE or _STABLE
//--------------------------------------------------
bit ScalerHdmiArcTxMonitorFifoStatus(void)
{
    BYTE ucRetryTimes = 0;

    for(ucRetryTimes = 0; ucRetryTimes < 5; ucRetryTimes++)
    {
        // Underflow or Overflow
        if(ScalerGetBit(PE5_61_AUDIO_TX_FIFO_CTRL_1, (_BIT5 | _BIT3)) != 0x00)
        {
            // Reset Audio Tx FIFO
            ScalerSetBit(PE5_60_AUDIO_TX_FIFO_CTRL_0, ~(_BIT7 | _BIT6), 0x00);
            ScalerSetBit(PE5_60_AUDIO_TX_FIFO_CTRL_0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Clear FIFO overflow/underflow flag
            ScalerSetBit(PE5_61_AUDIO_TX_FIFO_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), (_BIT5 | _BIT3));

            ScalerTimerDelayXms(2);
        }
        else
        {
            return _STABLE;
        }
    }

    DebugMessageArcTx("[ARC Tx] Tx FIFO Under/Overflow", 0);

    return _UNSTABLE;
}

//--------------------------------------------------
// Description  : Scaler HDMI Arc Tx Stable Detect
// Input Value  : None
// Output Value : _STABLE/_UNSTABLE
//--------------------------------------------------
bit ScalerHdmiArcTxStableDetect(void)
{
    // Check Audio Tx FIFO under/overflow
    if(ScalerGetBit(PE5_61_AUDIO_TX_FIFO_CTRL_1, (_BIT5 | _BIT3)) != 0x00)
    {
        DebugMessageArcTx("[ARC Tx] Tx FIFO Over/Underflow", 0x00);

        return _UNSTABLE;
    }

    // Check Rx BMC Decoder No Z Flag
    if(ScalerGetBit(PE5_07_SPDIF_IN_BMC_DEC, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
    {
        DebugMessageArcTx("[ARC Tx] Rx BMC Decoder No Z Flag", 0x00);

        return _UNSTABLE;
    }

    // Check Rx Channel Status Change
    if(GET_HDMI_ARC_TX_SOURCE_CH_STATUS_CHANGE_EVENT() == _TRUE)
    {
        ScalerSetByte(PE5_11_SPDIF_IN_CH_STATUS_TABLE_ADDR, 0x00)

        DebugMessageArcTx("[ARC Tx] Rx Channel Status Change", ScalerGetByte(PE5_12_SPDIF_IN_CH_STATUS_TABLE_DATA));

        return _UNSTABLE;
    }

    return _STABLE;
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Mute Process
// Input Value  : _ON => Mute On
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxMuteProc(bit bMute)
{
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    if(GET_HDMI_ARC_TX_LINK_MODE() == _EARC_MODE)
    {
        if(bMute == _ON)
        {
            ScalerHdmiArcTxPhyEarcDiffDrivingPower(_OFF);
        }
        else
        {
            ScalerHdmiArcTxPhyEarcDiffDrivingPower(_ON);
        }
    }
    else
#endif
    {
        if(bMute == _ON)
        {
            // set Tx phy to eARC Mode & output disable
            ScalerHdmiArcTxPhySetArcMode(_DISABLE);
        }
        else
        {
            // set Tx phy to ARC Mode & output enable
            ScalerHdmiArcTxPhySetArcMode(_ENABLE);
        }
    }
}

//----------------------------------------
// Description  : Scaler HDMI ARC Tx Power On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxPowerOnInitial(EnumAudioArcMode enumArcMode)
{
    g_enumHdmiArcTxOsdArcMode = enumArcMode;

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    ScalerHdmiArcTxPhyEarcInitial();

    // Enable eARC Tx MAC
    ScalerSetBit(PE5_00_EARC_TX_CKGEN_CTRL_0, ~_BIT7, _BIT7);

    // spdif_512fs_clk_src_sel = CK_EARC_1X(from eARC Tx N.F PLL)
    ScalerSetBit(PE5_00_EARC_TX_CKGEN_CTRL_0, ~_BIT4, 0x00);

    // cm_check_time = Tbit_windowns*80%
    ScalerSetBit(PE5_F4_EARC_TX_DPHY_CM_BMC_DEC_ENC_4, ~(_BIT4 | _BIT3), _BIT4);

    // cs regen table auto inc disable & reset table
    ScalerSetBit(PE5_28_CH_STATUS_REGEN_TABLE_CTRL, ~(_BIT7 | _BIT6), _BIT7);
#endif
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Set MN Tracking
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerHdmiArcTxSetMnTracking(void)
{
    WORD usTemp = 0x00;

    //---------------------------------
    // MN Tracking setting
    //---------------------------------
    // Set PI Code For the first Stage
    ScalerHdmiArcTxFirstSetPiCode();

    // Enable MN Tracking
    ScalerHdmiArcTxEnableMnTracking();

    usTemp = 300;

    //====== Check 1st Tracking Stable =====//
    while((ScalerHdmiArcTxMonitorPhaseError() == _UNSTABLE) && (--usTemp != 0))
    {
        DELAY_5US();
    }

    if(usTemp == 0)
    {
        DebugMessageArcTx("[ARC Tx] 1st tracking fail", 0);

        return _FALSE;
    }

    ScalerHdmiArcTxSecondSetPiCode();

    usTemp = 300;

    //====== Check 2rd Tracking Stable =====//
    while((ScalerHdmiArcTxMonitorPhaseError() == _UNSTABLE) && (--usTemp != 0))
    {
        DELAY_5US();
    }

    if(usTemp == 0)
    {
        DebugMessageArcTx("[ARC Tx] 2nd tracking fail", 0);
        return _FALSE;
    }

    // Wait PLL stable for 10ms
    ScalerTimerDelayXms(10);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Set First PI Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxFirstSetPiCode(void)
{
    // Set PI code and P/I gain clamp value for the first stage
    // Set P Code: 0x1FFFF
    ScalerSetByte(PE5_80_AUDIO_MN_TRACK_CTRL_13, 0x00); // Pcode[26:24] -> [2:0]
    ScalerSetByte(PE5_81_AUDIO_MN_TRACK_CTRL_14, 0x01); // Pcode[23:16] -> [7:0]
    ScalerSetByte(PE5_82_AUDIO_MN_TRACK_CTRL_15, 0xFF); // Pcode[15: 8] -> [7:0]
    ScalerSetByte(PE5_83_AUDIO_MN_TRACK_CTRL_16, 0xFF); // Pcode[ 7: 0] -> [7:0]

    // Set I Code: 0x3FF
    ScalerSetByte(PE5_7C_AUDIO_MN_TRACK_CTRL_9, 0x00); // Icode[26:24] -> [2:0]
    ScalerSetByte(PE5_7D_AUDIO_MN_TRACK_CTRL_10, 0x00); // Icode[23:16] -> [7:0]
    ScalerSetByte(PE5_7E_AUDIO_MN_TRACK_CTRL_11, 0x03); // Icode[15: 8] -> [7:0]
    ScalerSetByte(PE5_7F_AUDIO_MN_TRACK_CTRL_12, 0xFF); // Icode[ 7: 0] -> [7:0]

    // PI Double Buffer
    ScalerSetBit(PE5_A0_NF_CODE_CTRL_0, ~(_BIT7 | _BIT6 | _BIT4), _BIT7);

    // Set PE mode: new mode
    ScalerSetBit(PE5_70_AUDIO_NF_PLL_SDM, ~(_BIT5 | _BIT4 | _BIT2), _BIT2);

    // PI Control enable(SDM)
    ScalerSetBit(PE5_70_AUDIO_NF_PLL_SDM, ~(_BIT7 | _BIT5 | _BIT4), _BIT7);

    // enable PI control
    ScalerSetBit(PE5_69_AUDIO_TX_FIFO_CTRL_9, ~(_BIT7 | _BIT0), _BIT7);
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Set First PI Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxSecondSetPiCode(void)
{
    if(GET_HDMI_ARC_TX_SOURCE_SAMPLING_FREQ() <= _AUDIO_FREQ_PACKET_192K)
    {
        // Set PI code and P/I gain clamp value for the first stage
        // Set P Code: 0x1FFF
        ScalerSetByte(PE5_80_AUDIO_MN_TRACK_CTRL_13, 0x00); // Pcode[26:24] -> [2:0]
        ScalerSetByte(PE5_81_AUDIO_MN_TRACK_CTRL_14, 0x00); // Pcode[23:16] -> [7:0]
        ScalerSetByte(PE5_82_AUDIO_MN_TRACK_CTRL_15, 0x1F); // Pcode[15: 8] -> [7:0]
        ScalerSetByte(PE5_83_AUDIO_MN_TRACK_CTRL_16, 0xFF); // Pcode[ 7: 0] -> [7:0]
    }
    else
    {
        // Set PI code and P/I gain clamp value for the first stage
        // Set P Code: 0x7FF
        ScalerSetByte(PE5_80_AUDIO_MN_TRACK_CTRL_13, 0x00); // Pcode[26:24] -> [2:0]
        ScalerSetByte(PE5_81_AUDIO_MN_TRACK_CTRL_14, 0x00); // Pcode[23:16] -> [7:0]
        ScalerSetByte(PE5_82_AUDIO_MN_TRACK_CTRL_15, 0x07); // Pcode[15: 8] -> [7:0]
        ScalerSetByte(PE5_83_AUDIO_MN_TRACK_CTRL_16, 0xFF); // Pcode[ 7: 0] -> [7:0]
    }

    // Set I Code: 0x04
    ScalerSetByte(PE5_7C_AUDIO_MN_TRACK_CTRL_9, 0x00); // Icode[26:24] -> [2:0]
    ScalerSetByte(PE5_7D_AUDIO_MN_TRACK_CTRL_10, 0x00); // Icode[23:16] -> [7:0]
    ScalerSetByte(PE5_7E_AUDIO_MN_TRACK_CTRL_11, 0x00); // Icode[15: 8] -> [7:0]
    ScalerSetByte(PE5_7F_AUDIO_MN_TRACK_CTRL_12, 0x04); // Icode[ 7: 0] -> [7:0]

    // Set MN Tracking Div = div4 = 2*ck_mn_divs
    ScalerSetByte(PE5_72_AUDIO_NF_PLL_CLK_TK_CRTL_1, 0x01);

    // set double buffer to apply
    ScalerSetBit(PE5_A0_NF_CODE_CTRL_0, ~(_BIT7 | _BIT6 | _BIT4), _BIT7);
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Enable MN Tracking
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxEnableMnTracking(void)
{
    DWORD ulMnTracking_Mcode = 0;
    DWORD ulMnTracking_Ncode = 0;

    if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE() == _AUDIO_LAYOUT_6CH_ONE_BIT_AUDIO)
    {
        // MNTracking_Mcode = 128*8sample*3 = 3072
        ulMnTracking_Mcode = 3072;

        // MNTracking_Ncode = 128*8sample = 1024
        ulMnTracking_Ncode = 1024;
    }
    else if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE() == _AUDIO_LAYOUT_8CH)
    {
        // MNTracking_Mcode = 128*8sample*4 = 4096
        ulMnTracking_Mcode = 4096;

        // MNTracking_Ncode = 128*8sample = 1024
        ulMnTracking_Ncode = 1024;
    }
    else
    {
        // MNTracking_Mcode = 128*8sample = 1024
        ulMnTracking_Mcode = 1024;

        // MNTracking_Ncode = 128*8sample = 1024
        ulMnTracking_Ncode = 1024;
    }

    DebugMessageArcTx("[ARC Tx] M_code", ulMnTracking_Mcode);
    DebugMessageArcTx("[ARC Tx] N_code", ulMnTracking_Ncode);

    // Set M Code
    ScalerSetByte(PE5_74_AUDIO_MN_TRACK_CTRL_1, (BYTE)(ulMnTracking_Mcode >> 16));
    ScalerSetByte(PE5_75_AUDIO_MN_TRACK_CTRL_2, (BYTE)(ulMnTracking_Mcode >> 8));
    ScalerSetByte(PE5_76_AUDIO_MN_TRACK_CTRL_3, (BYTE) ulMnTracking_Mcode);

    // Set N Code
    ScalerSetByte(PE5_77_AUDIO_MN_TRACK_CTRL_4, (BYTE)(ulMnTracking_Ncode >> 16)); // MNTracking_Ncode[23:16] -> [7:0]
    ScalerSetByte(PE5_78_AUDIO_MN_TRACK_CTRL_5, (BYTE)(ulMnTracking_Ncode >> 8));  // MNTracking_Ncode[15:8]  -> [7:0]
    ScalerSetByte(PE5_79_AUDIO_MN_TRACK_CTRL_6, (BYTE) ulMnTracking_Ncode);        // MNTracking_Ncode[7:0]

    // Set MN Tracking Div = div2
    ScalerSetByte(PE5_72_AUDIO_NF_PLL_CLK_TK_CRTL_1, 0x00);

    // Enable MN Tracking
    ScalerSetBit(PE5_73_AUDIO_MN_TRACK_CTRL_0, ~(_BIT7 | _BIT0), _BIT7);

    // set double buffer to apply
    ScalerSetBit(PE5_A0_NF_CODE_CTRL_0, ~(_BIT7 | _BIT6 | _BIT4), _BIT7);
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Monitor Phase Error
// Input Value  : None
// Output Value : _STABLE or _UNSTABLE
//--------------------------------------------------
bit ScalerHdmiArcTxMonitorPhaseError(void)
{
    // MN non-lock flag, write 1 to clear, (if phase error > TH_NLOCK_MN , assert), Clr MN non-lock flag
    ScalerSetBit(PE5_73_AUDIO_MN_TRACK_CTRL_0, ~_BIT0, _BIT0);

    // maximum Phase error recorded after write clear this byte. Write 0xFF to clear, Clr maximum Phase error
    ScalerSetByte(PE5_7B_AUDIO_MN_TRACK_CTRL_8, 0xFF);

    DELAY_XUS(1000);

    // MN non-lock flag =1 || maximum Phase error > 0x0A
    if((ScalerGetBit(PE5_73_AUDIO_MN_TRACK_CTRL_0, _BIT0) == _BIT0) || (ScalerGetByte(PE5_7B_AUDIO_MN_TRACK_CTRL_8) > 0x0A))
    {
        // MN non-lock flag, write 1 to clear, (if phase error > TH_NLOCK_MN , assert), Clr MN non-lock flag
        ScalerSetBit(PE5_73_AUDIO_MN_TRACK_CTRL_0, ~_BIT0, _BIT0);

        // maximum Phase error recorded after write clear this byte. Write 0xFF to clear, Clr maximum Phase error
        ScalerSetByte(PE5_7B_AUDIO_MN_TRACK_CTRL_8, 0xFF);

        return _UNSTABLE; // 0
    }

    return _STABLE; // 1
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx OSD Change Process(eARC/ARC/OFF)
// Input Value  : enumArcMode
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxOsdChangeProc(EnumAudioArcMode enumArcMode)
{
    g_enumHdmiArcTxOsdArcMode = enumArcMode;
}

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Scaler HDMI eArc Tx Load Channel Status
// Input Value  : None
// Output Value : _STABLE/_UNSTABLE
//--------------------------------------------------
void ScalerHdmiArcTxEarcLoadChannelStatus(void)
{
    EnumAudioSamplingFreqPacket enumChStatusSamplingFreq = _AUDIO_FREQ_PACKET_NO_AUDIO;

    // reset cs regen table
    ScalerSetBit(PE5_28_CH_STATUS_REGEN_TABLE_CTRL, ~_BIT7, _BIT7);

    if((GET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE() == _AUDIO_LAYOUT_8CH) &&
       ((GET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM() <= _AUDIO_CHANNEL_COUNT_2) && (GET_HDMI_ARC_TX_AUDIO_OUTPUT_CODING_TYPE() == _AUDIO_LPCM)))
    {
        enumChStatusSamplingFreq = ScalerHdmiArcTxAudioSamplingFreqDiv4(GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ());
    }
    else
    {
        enumChStatusSamplingFreq = GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ();
    }

    // Load CS Sampling Freq
    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x03);

    switch(enumChStatusSamplingFreq)
    {
        case _AUDIO_FREQ_PACKET_32K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x03);
            break;

        case _AUDIO_FREQ_PACKET_44_1K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x00);
            break;

        case _AUDIO_FREQ_PACKET_48K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x02);
            break;

        case _AUDIO_FREQ_PACKET_64K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x0B);
            break;

        case _AUDIO_FREQ_PACKET_88_2K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x08);
            break;

        case _AUDIO_FREQ_PACKET_96K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x0A);
            break;

        case _AUDIO_FREQ_PACKET_128K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x2B);
            break;

        case _AUDIO_FREQ_PACKET_176_4K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x0C);
            break;

        case _AUDIO_FREQ_PACKET_192K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x0E);
            break;

        case _AUDIO_FREQ_PACKET_256K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x09);
            break;

        case _AUDIO_FREQ_PACKET_352_8K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x1B);
            break;

        case _AUDIO_FREQ_PACKET_512K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x3B);
            break;

        case _AUDIO_FREQ_PACKET_705_6K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x2D);
            break;

        case _AUDIO_FREQ_PACKET_768K:

            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x09);
            break;

        default:
            break;
    }

    // Set Word Length
    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x04);
    pData[0] = (ScalerGetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA) & (~(_BIT3 | _BIT2 | _BIT1 | _BIT0)));

    // LPCM
    if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_CODING_TYPE() == _AUDIO_LPCM)
    {
        // word_length = according to source
        pData[0] = pData[0] | (GET_HDMI_ARC_TX_AUDIO_OUTPUT_WORD_LENGTH() & 0x0F);
    }
    else
    {
        // force word_length = 16bit
        pData[0] = pData[0] | 0x02;
    }

    ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, pData[0]);

    // Sync Rx Ch Status to Tx
    // copyright
    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x00);
    pData[0] = (ScalerGetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA) & (~_BIT2)) | (GET_HDMI_ARC_TX_SOURCE_AUDIO_CH_STATUS_BYTE0() & _BIT2);
    ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, pData[0]);

    // category code
    ScalerSetByte(PE5_11_SPDIF_IN_CH_STATUS_TABLE_ADDR, 0x01);
    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x01);
    ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, GET_HDMI_ARC_TX_SOURCE_AUDIO_CH_STATUS_BYTE1());

    // channel num
    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x02);
    ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, GET_HDMI_ARC_TX_SOURCE_AUDIO_CH_STATUS_BYTE2());

    // original sampling freq
    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x04);
    pData[0] = (ScalerGetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA) & (~(_BIT7 | _BIT6 | _BIT5 | _BIT4))) | (GET_HDMI_ARC_TX_SOURCE_AUDIO_CH_STATUS_BYTE4() & 0xF0);
    ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, pData[0]);

    // Load CS Audio InfoFrame
    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x11);
    ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB4());

    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x12);
    ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB5());

    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x13);
    ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB6());

    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x14);
    ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB7());

    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x15);
    ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB8());

    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x16);
    ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB9());

    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x17);
    ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB10());

    // Set Mute Flag = Mute
    ScalerHdmiArcTxEarcSetChStatusMuteFlag(_AUDIO_MUTE_ON);

    DebugMessageArcTx("[ARC Tx] OUTPUT_CODING_TYPE", GET_HDMI_ARC_TX_AUDIO_OUTPUT_CODING_TYPE());

    // LPCM
    if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_CODING_TYPE() == _AUDIO_LPCM)
    {
        if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE() == _AUDIO_LAYOUT_2CH)
        {
            if(GET_HDMI_ARC_TX_OSD_CHANNEL_NUM() == _ARC_AUDIO_2CH)
            {
                // data_format = Unencrypted LPCM(0x0)
                ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x00);
                pData[0] = ((ScalerGetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA) & (~(_BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0))) | 0x00);
                ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, pData[0]);
            }
            else
            {
                // data_format = Unencrypted Multi-Ch(0x10)
                ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x00);
                pData[0] = ((ScalerGetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA) & (~(_BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0))) | 0x20);
                ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, pData[0]);
            }

            // layout_type = 2ch(0x0)
            ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x05);
            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x00);
        }
        else
        {
            // data_format = Unencrypted Multi-Ch(0x10)
            ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x00);
            pData[0] = ((ScalerGetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA) & (~(_BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0))) | 0x20);
            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, pData[0]);

            // layout_type = 8ch(0x7)
            ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x05);
            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x70);
        }
    }
    // NON_LPCM
    else
    {
        // data_format = Unencrypted IEC 61937(0x2)
        ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x00);
        pData[0] = ((ScalerGetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA) & (~(_BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0))) | 0x02);
        ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, pData[0]);

        if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE() == _AUDIO_LAYOUT_2CH)
        {
            // layout_type = Compressed A(0x0)
            ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x05);
            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x00);
        }
        else
        {
            // layout_type = Compressed B(0x7)
            ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x05);
            ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, 0x70);
        }
    }
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Set Mute Flag
// Input Value  : EnumAudioMuteStatus
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxEarcSetChStatusMuteFlag(EnumAudioMuteStatus enumArcMute)
{
    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x12);

    if(enumArcMute == _AUDIO_MUTE_ON)
    {
        // Set Mute Flag = Mute
        pData[0] = ((ScalerGetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA) & (~_BIT2)) | _BIT2);
    }
    else
    {
        // Set Mute Flag = Unmute
        pData[0] = ((ScalerGetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA) & (~_BIT2)) | 0x00);
    }

    ScalerSetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA, pData[0]);
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Get Mute Flag
// Input Value  : None
// Output Value : EnumAudioMuteStatus
//--------------------------------------------------
EnumAudioMuteStatus ScalerHdmiArcTxEarcGetChStatusMuteFlag(void)
{
    EnumAudioMuteStatus enumArcMute = _AUDIO_MUTE_OFF;

    ScalerSetByte(PE5_26_CH_STATUS_REGEN_TABLE_ADDR, 0x12);

    if((ScalerGetByte(PE5_27_CH_STATUS_REGEN_TABLE_DATA) & _BIT2) == _BIT2)
    {
        enumArcMute = _AUDIO_MUTE_ON;
    }
    else
    {
        enumArcMute = _AUDIO_MUTE_OFF;
    }

    return enumArcMute;
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Output Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxEarcModeOutputReset(void)
{
    ScalerHdmiArcTxPhyEarcDiffDrivingPower(_OFF);
    ScalerHdmiArcTxPhyPllPowerOff();
    ScalerHdmiArcTxReset();
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Check Discovery Pass
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit ScalerHdmiArcTxEarcCheckDiscoveryPass(void)
{
    if(GET_HDMI_ARC_TX_EARC_DISCOVERY_EVENT() == _TRUE)
    {
        CLR_HDMI_ARC_TX_EARC_DISCOVERY_EVENT();

        SET_HDMI_ARC_TX_LINK_MODE(_EARC_MODE);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Check Discovery Timeout
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit ScalerHdmiArcTxEarcCheckDiscoveryTimeout(void)
{
    if(GET_HDMI_ARC_TX_EARC_DISC_TIMEOUT_EVENT() == _TRUE)
    {
        CLR_HDMI_ARC_TX_EARC_DISC_TIMEOUT_EVENT();

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Stream Handler
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerHdmiArcTxEarcStreamHandler(void)
{
    // Audio Fifo initial before enable
    if(ScalerGetBit(PE5_60_AUDIO_TX_FIFO_CTRL_0, _BIT7) == 0x00)
    {
        ScalerHdmiArcTxSpdifInputConverterInitial();

        // TODO: need check with DIC
        ScalerTimerDelayXms(10);

        // Wait at least 10ms for waiting HW que 192bit channel status
        if(ScalerTimerPollingFlagProc(10, PE5_10_SPDIF_IN_CH_STATUS_CTRL_0, _BIT3, _TRUE) == _FALSE)
        {
            DebugMessageArcTx("[ARC Tx] HW que 192bit rx channel status fail", 0x00);

            return _FALSE;
        }

        // pop cs table
        ScalerSetBit(PE5_10_SPDIF_IN_CH_STATUS_CTRL_0, ~(_BIT7 | _BIT3 | _BIT2), _BIT2);
        DELAY_5US();

        CLR_HDMI_ARC_TX_SOURCE_CH_STATUS_CHANGE_EVENT();

        // enable cs change irq
        ScalerSetBit(PE5_13_SPDIF_IN_CH_STATUS_CTRL_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        ScalerHdmiArcTxSetAudioOutputConfig();

        ScalerHdmiArcTxPhySetPll();

        if(ScalerHdmiArcTxSetMnTracking() == _FALSE)
        {
            return _FALSE;
        }

        if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE() == _AUDIO_LAYOUT_2CH)
        {
            // Set Audio FIFO Depth = 0x0E
            ScalerSetByte(PE5_62_AUDIO_TX_FIFO_CTRL_2, 0x0E);
        }
        else
        {
            // Set Audio FIFO Depth = 0x1F
            ScalerSetByte(PE5_62_AUDIO_TX_FIFO_CTRL_2, 0x1F);
        }

        // Enable Audio Tx FIFO(normal output)
        ScalerSetBit(PE5_60_AUDIO_TX_FIFO_CTRL_0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    else
    {
        // Wait depth reaching target depth
        if(ScalerGetBit(PE5_61_AUDIO_TX_FIFO_CTRL_1, _BIT1) == _BIT1)
        {
            if(ScalerHdmiArcTxMonitorFifoStatus() == _FALSE)
            {
                // Disable Audio Tx FIFO
                ScalerSetBit(PE5_60_AUDIO_TX_FIFO_CTRL_0, ~(_BIT7 | _BIT6), 0x00);

                return _FALSE;
            }

            if(ScalerGetBit(PE5_B2_EARC_TX_DMAC_FRAME_ENC_0, _BIT7) == 0x00)
            {
                // frame encoder enable
                ScalerSetBit(PE5_B2_EARC_TX_DMAC_FRAME_ENC_0, ~_BIT7, _BIT7);

                // Set Tx phy duty
                ScalerHdmiArcTxPhyEarcSetDuty();
                // ScalerHdmiArcTxPhyEarcDiffDrivingPower(_ON);
            }

            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Set HB HPD Status
// Input Value  : _HIGH/_LOW
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxEarcSetHbHpdStatus(BYTE ucValue)
{
    if(ucValue == _HIGH)
    {
        ScalerSetBit(PE5_CC_EARC_TX_HEARTBEAT_CTRL_7, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(PE5_CC_EARC_TX_HEARTBEAT_CTRL_7, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Check Audio Latency Update
// Input Value  : pucAudioLatency
// Output Value : _FLASE / _TRUE
//--------------------------------------------------
bit ScalerHdmiArcTxEarcCheckAudioLatencyUpdate(BYTE *pucAudioLatency)
{
    if(GET_HDMI_ARC_TX_EARC_AUDIO_LATENCY_CHANGE_EVENT() == _TRUE)
    {
        if(ScalerHdmiArcTxEarcAudioLatencyReload(pucAudioLatency) == _TRUE)
        {
            CLR_HDMI_ARC_TX_EARC_AUDIO_LATENCY_CHANGE_EVENT();

            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Audio Latency Reload
// Input Value  : pucAudioLatency
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerHdmiArcTxEarcAudioLatencyReload(BYTE *pucAudioLatency)
{
    WORD usTemp = 0x00;

    // Max Read estimate time(1bytes)*1.1 = ((26us*6 + 27us*3 + 40us*3) + (26us*2 + 27us + 40us)*(15 + 15 + 1 + 1))*1.1 = 4581us
    // cm_trans_estimate_time(unit 100us) = 46
    ScalerSetByte(PE5_DD_EARC_TX_CM_MASTER_CTRL_13, 0x2E);

    // cm_rw_length = 1
    ScalerSetByte(PE5_D4_EARC_TX_CM_MASTER_CTRL_4, 0x00);

    // cm_device_id = 74
    ScalerSetByte(PE5_D5_EARC_TX_CM_MASTER_CTRL_5, 0x74);

    // cm_offset = D2
    ScalerSetByte(PE5_D6_EARC_TX_CM_MASTER_CTRL_6, 0xD2);

    // cm_rw_mode = Read
    ScalerSetBit(PE5_D0_EARC_TX_CM_MASTER_CTRL_0, ~(_BIT6 | _BIT5), 0x00);

    // clear cm_trans_finish_flag
    ScalerSetBit(PE5_D0_EARC_TX_CM_MASTER_CTRL_0, ~_BIT5, _BIT5);

    // clear error flags
    ScalerSetByte(PE5_D1_EARC_TX_CM_MASTER_CTRL_1, 0xFC);

    // cm_trans_ready = 1
    ScalerSetBit(PE5_D0_EARC_TX_CM_MASTER_CTRL_0, ~(_BIT7 | _BIT5), _BIT7);

    usTemp = 50;

    // wait cm r/w finish
    while((ScalerGetBit(PE5_D0_EARC_TX_CM_MASTER_CTRL_0, _BIT5) == 0x00) && (--usTemp != 0))
    {
        DELAY_XUS(1000);
    }

    if(usTemp == 0)
    {
        DebugMessageArcTx("[ARC Tx] CM Read/Write Timeout", 0);

        return _FALSE;
    }
    else if(ScalerGetBit(PE5_D1_EARC_TX_CM_MASTER_CTRL_1, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
    {
        DebugMessageArcTx("[ARC Tx] CM Read/Write fail", 0);

        return _FALSE;
    }

    ScalerGetDataPortByte(PE5_D7_EARC_TX_CM_MASTER_CTRL_7, _PE5_D8_PT_00_PORT_PAGEE5_CM_READ_DATA_BYTE_0, 1, pData, _AUTOINC);

    DebugMessageArcTx("[ARC Tx] Audio Latency Reload", pData[0]);

    *pucAudioLatency = pData[0];

    return _TRUE;
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Audio Latency Reload
// Input Value  : ucAudioLatency
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerHdmiArcTxEarcSetRequestAudioLatency(BYTE ucAudioLatency)
{
    ucAudioLatency = ucAudioLatency;
    // TODO:
    return _FALSE;
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Check CDS Update
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit ScalerHdmiArcTxEarcCheckCdsUpdate(void)
{
    if(GET_HDMI_ARC_TX_EARC_CDS_CHANGE_EVENT() == _TRUE)
    {
        CLR_HDMI_ARC_TX_EARC_CDS_CHANGE_EVENT();

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Capability Data Structure Reload
// Input Value  : pucEarcRxCdsTable
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerHdmiArcTxEarcCdsReload(BYTE *pucEarcRxCdsTable)
{
    WORD usTemp = 0x00;
    BYTE ucIndex = 0x00;

    for(ucIndex = 0; ucIndex < 16; ucIndex++)
    {
        // Max Read estimate time(16bytes)*1.1 = ((26us*6 + 27us*3 + 40us*3) + (26us*2 + 27us + 40us)*(15 + 15 + 16 + 1))*1.1 = 6545us
        // cm_trans_estimate_time(unit 100us) = 65
        ScalerSetByte(PE5_DD_EARC_TX_CM_MASTER_CTRL_13, 0x41);

        // cm_rw_length = 16
        ScalerSetByte(PE5_D4_EARC_TX_CM_MASTER_CTRL_4, 0x0F);

        // cm_device_id = A0
        ScalerSetByte(PE5_D5_EARC_TX_CM_MASTER_CTRL_5, 0xA0);

        // cm_offset
        ScalerSetByte(PE5_D6_EARC_TX_CM_MASTER_CTRL_6, 16 * ucIndex);

        // cm_rw_mode = Read
        ScalerSetBit(PE5_D0_EARC_TX_CM_MASTER_CTRL_0, ~(_BIT6 | _BIT5), 0x00);

        // clear cm_trans_finish_flag
        ScalerSetBit(PE5_D0_EARC_TX_CM_MASTER_CTRL_0, ~_BIT5, _BIT5);

        // clear error flags
        ScalerSetByte(PE5_D1_EARC_TX_CM_MASTER_CTRL_1, 0xFC);

        // cm_trans_ready = 1
        ScalerSetBit(PE5_D0_EARC_TX_CM_MASTER_CTRL_0, ~(_BIT7 | _BIT5), _BIT7);

        usTemp = 50;

        // wait cm r/w finish
        while((ScalerGetBit(PE5_D0_EARC_TX_CM_MASTER_CTRL_0, _BIT5) == 0x00) && (--usTemp != 0))
        {
            DELAY_XUS(1000);
        }

        if(usTemp == 0)
        {
            DebugMessageArcTx("[ARC Tx] CM Read/Write Timeout", ucIndex);

            return _FALSE;
        }
        else if(ScalerGetBit(PE5_D1_EARC_TX_CM_MASTER_CTRL_1, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
        {
            DebugMessageArcTx("[ARC Tx] CM Read/Write fail", ucIndex);

            return _FALSE;
        }

        ScalerGetDataPortByte(PE5_D7_EARC_TX_CM_MASTER_CTRL_7, _PE5_D8_PT_00_PORT_PAGEE5_CM_READ_DATA_BYTE_0, 16, pData, _AUTOINC);

        memcpy(pucEarcRxCdsTable + (ucIndex * 16), pData, 16);

        // Print out the first 80 bytes of CDS Table
        if(ucIndex < 5)
        {
            for(usTemp = 0; usTemp < 16; usTemp++)
            {
                DebugMessageArcTx("[ARC Tx] CDS Reload", pData[usTemp]);
            }
        }

        if((pData[15] == 0) && (pData[14] == 0) && (pData[13] == 0) &&
           (pData[12] == 0) && (pData[11] == 0))
        {
            DebugMessageArcTx("[ARC Tx] CDS at least 5 bytes all zero", ucIndex);
            break;
        }
    }

    return _TRUE;
}
#endif // End of #if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
#endif // End of #if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
