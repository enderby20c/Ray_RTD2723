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
// ID Code      : ScalerDisplayDpTxX.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DISPLAY_DP_TX__

#include "ScalerFunctionInclude.h"
#include "DisplayDpTxX/ScalerDisplayDpTxX.h"

#if(_DISPLAY_DP_TXX_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

StructDownStreamInfo g_pstDisplayDpTxXInfo[_DISPLAY_DP_TX_PORT_MAX];
StructDisplayDPTxLTInfo g_pstDisplayDpTxXLTInfo[_DISPLAY_DP_TX_PORT_MAX];
StructTimingInfo g_pstDisplayDpTxXTimingInfo[_DISPLAY_DP_TX_PORT_MAX];
StructDisplayDPTxInputInfo g_pstDisplayDpTxXInputInfo[_DISPLAY_DP_TX_PORT_MAX];

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
BYTE g_pucDisplayDpTxXAuxPVth[_DISPLAY_DP_TX_PORT_MAX];
BYTE g_pucDisplayDpTxXAuxNVth[_DISPLAY_DP_TX_PORT_MAX];
#endif

EnumDpAuxReceiveMode g_penumDisplayDpTxXAuxReceiveMode[_DISPLAY_DP_TX_PORT_MAX];

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxXInitial(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    ScalerDisplayDpTxSetMacToPhyMux();

    ScalerDisplayDpTxXAuxInitial();

    ScalerDisplayDpTxXMacInitial(enumDisplayDpTxOutputPort);
}

//--------------------------------------------------
// Description  : Dp Tx Read DPCD Rx Capability
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXLinkConfig(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    bit bLTConfig = _TRUE;

    SET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_TRAINING_NO_RESULT);
    SET_DISPLAY_DP_TXX_LT_STATE(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_TRAINING_PATTERN1);

    // Set Power Normal
    pData[0] = 0x01;
    if(ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x06, 0x00, 1, pData) == _FALSE)
    {
        bLTConfig &= _FALSE;
    }

    ScalerTimerDelayXms(10);

    // Read Sink Power Status
    if(ScalerDisplayDpTxXNativeAuxRead(0x00, 0x06, 0x00, 1, pData) == _FALSE)
    {
        bLTConfig &= _FALSE;
    }

    // Check if Power State is Normal
    if(pData[0] != 0x01)
    {
        bLTConfig &= _FALSE;
    }

    // Read Sink Cabability
    if(ScalerDisplayDpTxXNativeAuxRead(0x00, 0x00, 0x00, 16, pData) == _FALSE)
    {
        bLTConfig &= _FALSE;
    }

    SET_DISPLAY_DP_TXX_LINK_CONFIG(enumDisplayDpTxOutputPort, bLTConfig);

    if(_PANEL_DPTX_LINK_RATE >= _PANEL_DPTX_LINK_HBR2)
    {
        // Check TP3 support
        if((_PANEL_DPTX_LT_TPS3_SUPPORT_BY_USER == _ON) && ((pData[2] & _BIT6) == _BIT6))
        {
            SET_DISPLAY_DP_TXX_TP3_SUPPORT(enumDisplayDpTxOutputPort);
        }
        else
        {
            CLR_DISPLAY_DP_TXX_TP3_SUPPORT(enumDisplayDpTxOutputPort);
        }
    }
    else
    {
        CLR_DISPLAY_DP_TXX_TP3_SUPPORT(enumDisplayDpTxOutputPort);
    }

    if(_PANEL_DPTX_LINK_RATE >= _PANEL_DPTX_LINK_HBR3)
    {
        // Check TP4 support
        if((_PANEL_DPTX_LT_TPS4_SUPPORT_BY_USER == _ON) && ((pData[3] & _BIT7) == _BIT7))
        {
            SET_DISPLAY_DP_TXX_TP4_SUPPORT(enumDisplayDpTxOutputPort);
        }
        else
        {
            CLR_DISPLAY_DP_TXX_TP4_SUPPORT(enumDisplayDpTxOutputPort);
        }
    }
    else
    {
        CLR_DISPLAY_DP_TXX_TP4_SUPPORT(enumDisplayDpTxOutputPort);
    }

    // Set Lane Number
    if(_PANEL_DPTX_LANE_NUMBER >= _PANEL_DPTX_LANE_NUMBER_4)
    {
        SET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort, _DP_FOUR_LANE);
    }
    else if(_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_2)
    {
        SET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort, _DP_TWO_LANE);
    }
    else
    {
        SET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort, _DP_ONE_LANE);
    }

    // Set Enhanceed Framing
    SET_DISPLAY_DP_TXX_ENHANCE_FRAMING(enumDisplayDpTxOutputPort, (bit)(pData[2] & _BIT7));

    // Set Max Downspread
    SET_DISPLAY_DP_TXX_DOWN_SPREAD(enumDisplayDpTxOutputPort, (bit)(pData[3] & _BIT0));

    // Set Framing Change for eDP
    SET_DISPLAY_DP_TXX_FRAMING_CHANGE_CAPABLE(enumDisplayDpTxOutputPort, (bit)(pData[13] & _BIT1));

    // Set Alternate SR Capable for eDP
    SET_DISPLAY_DP_TXX_ALTERNATE_SR_CAPABLE(enumDisplayDpTxOutputPort, (bit)(pData[13] & _BIT0));

    DebugMessageCheck("eDP TxX Link Config Port", enumDisplayDpTxOutputPort);
    DebugMessageCheck("eDP TxX Enhanceed Framing", GET_DISPLAY_DP_TXX_ENHANCE_FRAMING(enumDisplayDpTxOutputPort));
    DebugMessageCheck("eDP TxX Max Downspread", GET_DISPLAY_DP_TXX_DOWN_SPREAD(enumDisplayDpTxOutputPort));
    DebugMessageCheck("eDP TxX Framing change", GET_DISPLAY_DP_TXX_FRAMING_CHANGE_CAPABLE(enumDisplayDpTxOutputPort));
    DebugMessageCheck("eDP TxX Alternate SR Capable", GET_DISPLAY_DP_TXX_ALTERNATE_SR_CAPABLE(enumDisplayDpTxOutputPort));
}

//--------------------------------------------------
// Description  : Handle Tx0 Output stream
// Input Value  : DP Tx0 Input Source
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxXVideoStreamOutput(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, bit bOutput)
{
    bit bMvidHWMode = _TRUE;
    BYTE ucCnt = 0;
    BYTE ucValidHwMvidMeaCnt = 1;
    WORD usLoopCnt = 0;
    WORD usMeasureTime = 0;
    DWORD ulHwMvidMin = 0xFFFFFFFF;
    DWORD ulHwMvidMax = 0x00000000;
    DWORD ulFwMvid = 0;
    DWORD ulHwMivd = 0;
    DWORD ulMivdFinal = 0;
    DWORD ulNvid = 32768;

    EnumDisplayDpMacSel enumDisplayDpMacSel = ScalerDisplayDpTxGetMacSwitch(enumDisplayDpTxOutputPort);

    if(enumDisplayDpMacSel == _DISPLAY_DP_TX_NO_MAC)
    {
        return;
    }

    if(bOutput == _ENABLE)
    {
        if(GET_PANEL_DPTX_MSO_MODE() == _ON)
        {
            // Set MSO Section(8 section 2 lane)
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_00_DP_MAC_CTRL, ~(_BIT7 | _BIT6), _BIT7);
        }

        // DPTx CTS Fifo reset
        ScalerDisplayDpTxXCtsFifoReset();

        ScalerDisplayDpTxXMeasureInputInfo(enumDisplayDpMacSel);
        // Mvid = Stream clk x Nvid / Link clk
        ulFwMvid = GET_DWORD_MUL_DIV(GET_D_CLK_FREQ(), ulNvid, ((DWORD)_PANEL_DPTX_DCLK_DIV * 10UL));

        ulFwMvid /= ((GET_DISPLAY_DP_TX_SSCG_CONFIG() == _TRUE) ? (270UL * GET_DISPLAY_DP_TXX_MAX_LINK_RATE(enumDisplayDpTxOutputPort) * 9975UL / 10000UL) : (270UL * GET_DISPLAY_DP_TXX_MAX_LINK_RATE(enumDisplayDpTxOutputPort)));

        ulFwMvid = ulFwMvid / 10UL + (ulFwMvid % 10 > 5 ? 1 : 0);

        // Calculate HW measure Mvid period time, / 5 for get 5us times
        usMeasureTime = (WORD)(ulNvid / ((GET_DISPLAY_DP_TX_SSCG_CONFIG() == _TRUE) ? (27UL * GET_DISPLAY_DP_TXX_MAX_LINK_RATE(enumDisplayDpTxOutputPort) * 9975UL / 10000UL) : (27UL * GET_DISPLAY_DP_TXX_MAX_LINK_RATE(enumDisplayDpTxOutputPort))) / 5UL);
        usMeasureTime *= 2;

        // Debounce 10 times
        ucCnt = 0x0A;

        do
        {
            --ucCnt;

            // Enable HW Mvid measure
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_20_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6 | _BIT0), _BIT7);

            // Delay time for one HW mvid measurement period time
            for(usLoopCnt = 0; usLoopCnt < usMeasureTime; usLoopCnt++)
            {
                DELAY_5US();
            }

            // Disable HW Mvid measure
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_20_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6 | _BIT0), 0x00);

            ulHwMivd = ((DWORD)SCALER32_DISPLAY_DP_TX_GET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_2C_MVID_AUTO));

            // For RLE0779A/RL6449A disable auto Mvid is zero
            if(ulHwMivd == 0)
            {
                // HW Auto Mvid is wrong Set Mvid for FW mode
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_24_MN_M_VID, ulFwMvid);

                bMvidHWMode = _FALSE;

                break;
            }

            // (abs(ulFwMvid - ulHwMivd) > (ulFwMvid >> 2)) for HW measure abnormal
            if(ABSDWORD(ulFwMvid, ulHwMivd) > (ulFwMvid >> 2))
            {
                // Drop this time measure result
                continue;
            }

            // (ulMivdFinal != 0) for get the first time measurement result
            if(ulMivdFinal == 0)
            {
                if(ulHwMivd < ulHwMvidMin)
                {
                    ulHwMvidMin = ulHwMivd;
                }

                if(ulHwMivd > ulHwMvidMax)
                {
                    ulHwMvidMax = ulHwMivd;
                }

                ulMivdFinal = ulHwMivd;
                continue;
            }

            // (abs(ulHwMivd - ulMivdFinal) < 0x50) for avoid get the measurement value far away from the average value
            if(ABSDWORD(ulMivdFinal, ulHwMivd * ucValidHwMvidMeaCnt) < (0x50 * (WORD)ucValidHwMvidMeaCnt))
            {
                if(ulHwMivd < ulHwMvidMin)
                {
                    ulHwMvidMin = ulHwMivd;
                }

                if(ulHwMivd > ulHwMvidMax)
                {
                    ulHwMvidMax = ulHwMivd;
                }

                // Accumulate every hw measure mvid
                ulMivdFinal += ulHwMivd;

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
                ulMivdFinal -= (ulHwMvidMax + ulHwMvidMin);
                ucValidHwMvidMeaCnt -= 2;

                // Calculate the hw mvid average value
                ulMivdFinal = ((ulMivdFinal + (ucValidHwMvidMeaCnt / 2)) / ucValidHwMvidMeaCnt);

                if(ABSDWORD(ulFwMvid, ulMivdFinal) > (ulFwMvid >> 1))
                {
                    // HW Auto Mvid is wrong Set Mvid for FW mode
                    ulMivdFinal = ulFwMvid;
                }
            }
            else
            {
                // HW Auto Mvid is wrong Set Mvid for FW mode
                ulMivdFinal = ulFwMvid;
            }

            // Set Mvid value
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_24_MN_M_VID, ulMivdFinal);
        }

        // Set Nvid for FW mode
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_28_MN_N_VID, ulNvid);

        // Set Mvid DB Direct Effective
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_20_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6 | _BIT0), _BIT7);

        // Set Mvid DB for FW mode
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_20_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6 | _BIT0), _BIT6);

        // For Mvid Auto New Mode, M/N mode Measure and Generate are Independant.
        // SET_DISPLAY_DP_TX0_MVID_FW_MODE -> FW Manually Set Mvid/Nvid
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_20_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6 | _BIT0), 0x00);

        // MSA fill
        ScalerDisplayDpTxXDisplayMSASetting(enumDisplayDpMacSel);

        // DP Tx TU Setting
        ScalerDisplayDpTxXDisplayFormatSetting(enumDisplayDpTxOutputPort, enumDisplayDpMacSel);

        // Clear FIFO Status
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_10_PG_FIFO_CTRL, 0x00, 0xFF);

        // Main Link Switch to VIDEO pattern
        ScalerDisplayDpTxXSetTpsPattern(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_OUTPUT_VIDEO_PATTERN);

#if(_PANEL_DPTX_HPD_DETECT == _ON)
#if(_PANEL_DPTX_SET_HPD_DETECT_SEQUENCE == _HPD_DETECT_AFTER_VIDEO_STREAM)
        // Clear HPD IRQ Flag
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C4_HPD_IRQ, 0x00, 0xFE);

#if(_PANEL_DPTX_IRQ_HPD_DETECT == _ON)
        CLR_DISPLAY_DP_TXX_IRQ_HPD_DETECTED(enumDisplayDpTxOutputPort);

        // Enable IRQ HPD Int, Disable Long HPD Int
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C8_HPD_IRQ_EN, ~(_BIT6 | _BIT5), _BIT6);
#endif
#endif
        SET_DISPLAY_DP_TXX_STREAM_OUTPUT(enumDisplayDpTxOutputPort, _ENABLE);
#endif
    }
    else
    {
        // Main Link Switch to IDLE pattern
        ScalerDisplayDpTxXSetTpsPattern(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_OUTPUT_IDLE_PATTERN);

#if(_PANEL_DPTX_HPD_DETECT == _ON)
        SET_DISPLAY_DP_TXX_STREAM_OUTPUT(enumDisplayDpTxOutputPort, _DISABLE);
#endif

#if((_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON) && (_DRR_SUPPORT == _ON))
        ScalerSyncDrrDataExchangeProc(_DISABLE);
#endif
    }
}

//--------------------------------------------------
// Description  : DP Tx Arbiter
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXDisplayFormatSetting(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, EnumDisplayDpMacSel enumDisplayDpMacSel)
{
    WORD usColorDepth = 0;
    WORD usFifoOffset = 0;
    DWORD ulAverageTu = 0;
    DWORD ulVdataPerLine = 0;
    DWORD ulFwHdelay = 0;

    // Pixel Generation Block Reset
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_04_DP_RESET_CTRL, ~_BIT7, _BIT7);
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_04_DP_RESET_CTRL, ~_BIT7, 0x00);

    // Get Bit Per Chrome
    switch(GET_DISPLAY_DP_TXX_INPUT_COLOR_DEPTH(enumDisplayDpMacSel))
    {
        case _PANEL_DISP_18_BIT:
            usColorDepth = 6;
            break;

        case _PANEL_DISP_24_BIT:
            usColorDepth = 8;
            break;

        case _PANEL_DISP_30_BIT:
            usColorDepth = 10;
            break;

        case _PANEL_DISP_36_BIT:
            usColorDepth = 12;
            break;

        case _PANEL_DISP_48_BIT:
            usColorDepth = 16;
            break;

        default:
            usColorDepth = 8;
            break;
    }

    // Calculate Vaild Symbol in TU
    // Average TU = TU Size x (Stream_Clk x Byte of 1 pixel / Lane Number) / Link Rate
    if(GET_DISPLAY_DP_TX_SSCG_CONFIG() == _FALSE)
    {
        DWORD ulA = (DWORD)_DISPLAY_DP_TXX_TU_SIZE * 3UL * usColorDepth;
        DWORD ulB = (DWORD)GET_D_CLK_FREQ();
        DWORD ulC = (DWORD)_PANEL_DPTX_DCLK_DIV * 10UL * GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort) * 270UL * GET_DISPLAY_DP_TXX_MAX_LINK_RATE(enumDisplayDpTxOutputPort);

        // Average TU = TU Size x Color Depth x Stream_Clk / (Lane Number x Link Rate)
        ulAverageTu = GET_DWORD_MUL_DIV(ulA, ulB, ulC);
    }
    else
    {
        DWORD ulA = (DWORD)_DISPLAY_DP_TXX_TU_SIZE * 3UL * usColorDepth;
        DWORD ulB = (DWORD)GET_D_CLK_FREQ() * 100UL;
        DWORD ulC = (DWORD)_PANEL_DPTX_DCLK_DIV * GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort) * 27UL * GET_DISPLAY_DP_TXX_MAX_LINK_RATE(enumDisplayDpTxOutputPort) * 9975UL;

        // Average TU = TU Size x Color Depth x Stream_Clk / Lane Number * SSCG of Link Rate)
        ulAverageTu = GET_DWORD_MUL_DIV(ulA, ulB, ulC);
    }

    ulAverageTu = ulAverageTu / 10UL + (ulAverageTu % 10 >= 5 ? 1 : 0);

    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_70_TU_SIZE, _DISPLAY_DP_TXX_TU_SIZE);

    // HW Can't Set Valid TU < 1
    if((ulAverageTu >> 3) == 0x00)
    {
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_74_TU_DATA_SIZE, 0x100);
    }
    else
    {
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_74_TU_DATA_SIZE, ulAverageTu);
    }

    ulVdataPerLine = ((DWORD)g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHWidth * _PANEL_DPTX_MSO_DIV  * usColorDepth * 3) / (GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort) * 8);
    ulVdataPerLine += ((bit)(((DWORD)g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHWidth * _PANEL_DPTX_MSO_DIV * usColorDepth * 3) % (GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort) * 8)) ? 1 : 0);

    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_6C_V_DATA_PER_LINE0, ulVdataPerLine);

    // DP fifo size = 128 x 96bit
    // FifoOffset = (1/2 * (128 * 96) / (color space * depth per color))
    usFifoOffset = (WORD)6144 / (usColorDepth * 3);

    if((g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHStart + usFifoOffset) < (g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHWidth))
    {
        ulFwHdelay = ((g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHStart * _PANEL_DPTX_MSO_DIV) + usFifoOffset) * (((DWORD)GET_DISPLAY_DP_TXX_MAX_LINK_RATE(enumDisplayDpTxOutputPort)) * 270) / ((DWORD)GET_D_CLK_FREQ() / _PANEL_DPTX_DCLK_DIV / 100);
    }
    else
    {
        ulFwHdelay = ((g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHStart * _PANEL_DPTX_MSO_DIV) + (g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHWidth * _PANEL_DPTX_MSO_DIV) / 2) * (((DWORD)GET_DISPLAY_DP_TXX_MAX_LINK_RATE(enumDisplayDpTxOutputPort)) * 270) / ((DWORD)GET_D_CLK_FREQ() / _PANEL_DPTX_DCLK_DIV / 100);
    }

    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_78_HDEALY, ulFwHdelay);

    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_7C_ARBITER_SEC_END_CNT, 0x0A);

    // Second End Count Double Buffer
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_80_ARBITER_DEBUG, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
}

//--------------------------------------------------
// Description  : DP Tx MSA Generation
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXDisplayMSASetting(EnumDisplayDpMacSel enumDisplayDpMacSel)
{
    // Reset MSA Generation Block and SEC Block
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_04_DP_RESET_CTRL, ~_BIT6, _BIT6);
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_04_DP_RESET_CTRL, ~_BIT6, 0x00);

    // Set Htotal
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_40_MN_STRM_ATTR_HTT, g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHTotal);

    // Set Hstart
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_44_MN_STRM_ATTR_HST, g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHStart);

    // Set Hwidth
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_48_MN_STRM_ATTR_HWD, g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHWidth);

    // Set Hsyc
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_4C_MN_STRM_ATTR_HSW, g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHSWidth);

    // Set Vtotal
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_50_MN_STRM_ATTR_VTTE, g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usVTotal);

    // Set VStart
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_54_MN_STRM_ATTR_VST, g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usVStart);

    // Set VHeight
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_58_MN_STRM_ATTR_VHT, g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usVHeight);

    // Set Vsync
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_5C_MN_STRM_ATTR_VSW, g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usVSWidth);

    // Set Color Space; Set Color Depth
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_3C_MSA_MISC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), ((GET_DISPLAY_DP_TXX_INPUT_COLOR_DEPTH(enumDisplayDpMacSel) << 5) | (GET_DISPLAY_DP_TXX_INPUT_COLOR_SPACE(enumDisplayDpMacSel) << 3)));

    // MSA_DB = 1 and Bouble Buffer at V Blanking
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_38_MSA_CTRL, ~(_BIT7 | _BIT6), _BIT7);
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_F8_RESERVED_1, 0x33);
}

//--------------------------------------------------
// Description  : DP Tx Link Training
// Input Value  : enumDisplayDpTxOutputPort
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDpTxXLinkTraining(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    if(GET_DISPLAY_DP_TXX_LINK_CONFIG(enumDisplayDpTxOutputPort) == _TRUE)
    {
        ScalerDisplayDpTxXTPInitialSet(enumDisplayDpTxOutputPort);

        while((GET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort) != _DISPLAY_DP_TX_TRAINING_PASS) && (GET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort) != _DISPLAY_DP_TX_TRAINING_FAIL))
        {
            switch(GET_DISPLAY_DP_TXX_LT_STATE(enumDisplayDpTxOutputPort))
            {
                case _DISPLAY_DP_TX_TRAINING_PATTERN1:

                    SET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort, ScalerDisplayDpTxXTrainPattern1(enumDisplayDpTxOutputPort));

                    // CR OK
                    switch(GET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort))
                    {
                        case _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS:
                            SET_DISPLAY_DP_TXX_LT_STATE(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_TRAINING_PATTERN2);
                            DebugMessageCheck("eDP TxX LT1 Pass", enumDisplayDpTxOutputPort);
                            break;

                        // Can not Adjust voltage swing
                        case _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL:
                            SET_DISPLAY_DP_TXX_LT_STATE(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_TRAINING_PATTERN_END);
                            DebugMessageCheck("eDP TxX LT1 Freq Fail", enumDisplayDpTxOutputPort);
                            break;

                        default:
                            break;
                    }

                    break;

                case _DISPLAY_DP_TX_TRAINING_PATTERN2:

                    SET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort, ScalerDisplayDpTxXTrainPattern2(enumDisplayDpTxOutputPort));

                    switch(GET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort))
                    {
                        case _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS:
                        case _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL:
                            SET_DISPLAY_DP_TXX_LT_STATE(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_TRAINING_PATTERN_END);

                            if(GET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS)
                            {
                                DebugMessageCheck("eDP TxX LT2 Pass", enumDisplayDpTxOutputPort);
                            }
                            else
                            {
                                DebugMessageCheck("eDP TxX LT2 Lane or PN Fail", enumDisplayDpTxOutputPort);
                            }

                            break;

                        default:
                            break;
                    }

                    break;

                case _DISPLAY_DP_TX_TRAINING_PATTERN_END:

                    switch(GET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort))
                    {
                        case _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS:
                            SET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_TRAINING_PASS);
                            DebugMessageCheck("eDP TxX LTend Pass", enumDisplayDpTxOutputPort);
                            break;

                        default:
                            SET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_TRAINING_FAIL);
                            DebugMessageCheck("eDP TxX LTend Fail", enumDisplayDpTxOutputPort);
                            break;
                    }

                    ScalerDisplayDpTxXTrainPatternEnd(enumDisplayDpTxOutputPort);

                    break;

                default:

                    break;
            }
        }
    }
    else
    {
        DebugMessageCheck("eDP TxX Link Config Fail", enumDisplayDpTxOutputPort);
    }

    if(GET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_TRAINING_PASS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Inital Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXTPInitialSet(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    BYTE ucMsaIgnore = 0;

    // Panel DPTx Power Sequence Check Point
    ScalerDisplayDpTxSetPowerSequenceCheckPoint(enumDisplayDpTxOutputPort, _DPTX_POWER_SEQUENCE_LINK_TRAINING);

    SET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_TRAINING_NO_RESULT);
    SET_DISPLAY_DP_TXX_LT_STATE(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_TRAINING_PATTERN1);

    // Set Link Rate
    SET_DISPLAY_DP_TXX_MAX_LINK_RATE(enumDisplayDpTxOutputPort, _PANEL_DPTX_LINK_RATE);

    // Set Link Rate for DPCD table of the Sink
    ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x00, 1, &GET_DISPLAY_DP_TXX_MAX_LINK_RATE(enumDisplayDpTxOutputPort));

    if(GET_DISPLAY_DP_TXX_FRAMING_CHANGE_CAPABLE(enumDisplayDpTxOutputPort) == _TRUE)
    {
        // Set Link Count and Disable Enhance Framing for External DP Sink
        pData[0] = GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort);
        ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x01, 1, pData);

        // Set Enhance Framing Mode for eDP
        pData[0] = ((BYTE)GET_DISPLAY_DP_TXX_FRAMING_CHANGE_CAPABLE(enumDisplayDpTxOutputPort) << 1);
        ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x0A, 1, pData);

        ScalerDisplayDpTxXEnhanceFramingMode(_ENABLE);
    }
    else
    {
        // Set Link Count and Enhance Framing for DPCD table of the Sink
        pData[0] = ((BYTE)GET_DISPLAY_DP_TXX_ENHANCE_FRAMING(enumDisplayDpTxOutputPort) << 7) | GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort);
        ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x01, 1, pData);

        ScalerDisplayDpTxXEnhanceFramingMode(GET_DISPLAY_DP_TXX_ENHANCE_FRAMING(enumDisplayDpTxOutputPort));
    }

    // Initialize Main Link Signal for DPCD table of the Sink
    ScalerDisplayDpTxXSignalInitialSetting(enumDisplayDpTxOutputPort);

    ScalerDisplayDpTxXNativeAuxRead(0x00, 0x00, 0x07, 1, pData);

    ucMsaIgnore = ((pData[0] & _BIT6) == _BIT6 ? ((_PANEL_DPTX_MSA_TIMING_PAR_IGNORE_EN == _ENABLE) ? _BIT7 : 0x00) : 0x00);

    ScalerDisplayDpTxXNativeAuxRead(0x00, 0x01, 0x07, 1, pData);

    // Set Down Spread for DPCD table of the Sink
    pData[0] = ((pData[0] & ~_BIT4) | ((BYTE)GET_DISPLAY_DP_TX_SSCG_CONFIG() << 4) | ucMsaIgnore);
    ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x07, 1, pData);

    // Set DPTx Spread Spectrum
    ScalerDisplayDpTxSSCSet(GET_DISPLAY_DP_TX_SSCG_CONFIG());

#if(_PANEL_DPTX_SCRAMBLE_SEED_TYPE == _PANEL_DPTX_SCRAMBLE_SEED_AUTO)

    if(GET_DISPLAY_DP_TXX_ALTERNATE_SR_CAPABLE(enumDisplayDpTxOutputPort) == _TRUE)
    {
        // Scrambling Seed Select to 0xFFFE
        SET_DISPLAY_DP_TXX_SCRAMBLE_TYPE(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_SCRAMBLE_SEED_0XFFFE);
    }
    else
    {
        // Scrambling Seed Select to 0xFFFF
        SET_DISPLAY_DP_TXX_SCRAMBLE_TYPE(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_SCRAMBLE_SEED_0XFFFF);
    }
#elif(_PANEL_DPTX_SCRAMBLE_SEED_TYPE == _PANEL_DPTX_SCRAMBLE_SEED_0XFFFE)

    // Scrambling Seed Select to 0xFFFE
    SET_DISPLAY_DP_TXX_SCRAMBLE_TYPE(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_SCRAMBLE_SEED_0XFFFE);
#elif(_PANEL_DPTX_SCRAMBLE_SEED_TYPE == _PANEL_DPTX_SCRAMBLE_SEED_0XFFFF)

    // Scrambling Seed Select to 0xFFFF
    SET_DISPLAY_DP_TXX_SCRAMBLE_TYPE(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_SCRAMBLE_SEED_0XFFFF);
#endif // End of #if(_PANEL_DPTX_SCRAMBLE_SEED_TYPE == _PANEL_DPTX_SCRAMBLE_SEED_AUTO)
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDisplayDpTxXTrainPattern1(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Start TP1 Process
    if(GET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_TRAINING_NO_RESULT)
    {
        // Select TP1
        ScalerDisplayDpTxXSetTpsPattern(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_OUTPUT_TPS1);

        pData[0] = (_DISPLAY_DP_TX_TPS_1 | _DISPLAY_DP_TX_SCRAMBLING_DISABLE);
        pData[1] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane0Adjust;
        pData[2] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane1Adjust;
        pData[3] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane2Adjust;
        pData[4] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane3Adjust;

        // Write DPCD 102h to Start TP1
        ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x02, 5, pData);
    }
    else
    {
        // Set Output Signal According to Request
        ScalerDisplayDpTxXMLPHYSet(enumDisplayDpTxOutputPort);

        pData[0] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane0Adjust;
        pData[1] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane1Adjust;
        pData[2] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane2Adjust;
        pData[3] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane3Adjust;

        // Write DPCD 103h-107h  (Voltage Swing and Pre-emphasis)
        ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x03, 4, pData);
    }

    // Delay Time us [400,x] Delay 400us
    DELAY_XUS(400);

    // Read Lane Status and Request Adjust Level
    ScalerDisplayDpTxXNativeAuxRead(0x00, 0x02, 0x02, 6, pData);
    g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane01LTStatus = pData[0];
    g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane23LTStatus = pData[1];
    g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucAdjustReqLane01 = pData[4];
    g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucAdjustReqLane23 = pData[5];

    switch(GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort))
    {
        case _DP_FOUR_LANE:

            if((GET_DISPLAY_DP_TXX_LANE3_CR_DONE(enumDisplayDpTxOutputPort) == _TRUE) &&
               (GET_DISPLAY_DP_TXX_LANE2_CR_DONE(enumDisplayDpTxOutputPort) == _TRUE) &&
               (GET_DISPLAY_DP_TXX_LANE1_CR_DONE(enumDisplayDpTxOutputPort) == _TRUE) &&
               (GET_DISPLAY_DP_TXX_LANE0_CR_DONE(enumDisplayDpTxOutputPort) == _TRUE))
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS;
            }

            if((ScalerDisplayDpTxXTP1Lane3Adjust(enumDisplayDpTxOutputPort) == _FAIL) ||
               (ScalerDisplayDpTxXTP1Lane2Adjust(enumDisplayDpTxOutputPort) == _FAIL) ||
               (ScalerDisplayDpTxXTP1Lane1Adjust(enumDisplayDpTxOutputPort) == _FAIL) ||
               (ScalerDisplayDpTxXTP1Lane0Adjust(enumDisplayDpTxOutputPort) == _FAIL))
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;

        case _DP_TWO_LANE:

            if((GET_DISPLAY_DP_TXX_LANE1_CR_DONE(enumDisplayDpTxOutputPort) == _TRUE) &&
               (GET_DISPLAY_DP_TXX_LANE0_CR_DONE(enumDisplayDpTxOutputPort) == _TRUE))
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS;
            }

            if((ScalerDisplayDpTxXTP1Lane1Adjust(enumDisplayDpTxOutputPort) == _FAIL) ||
               (ScalerDisplayDpTxXTP1Lane0Adjust(enumDisplayDpTxOutputPort) == _FAIL))
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;

        case _DP_ONE_LANE:
        default:

            if(GET_DISPLAY_DP_TXX_LANE0_CR_DONE(enumDisplayDpTxOutputPort) == _TRUE)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS;
            }

            if(ScalerDisplayDpTxXTP1Lane0Adjust(enumDisplayDpTxOutputPort) == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;
    }

    return _DISPLAY_DP_TX_TRAINING_PATTERN1_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDisplayDpTxXTrainPattern2(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Start TP2 Process
    if(GET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS)
    {
        if(GET_DISPLAY_DP_TXX_TP4_SUPPORT(enumDisplayDpTxOutputPort) == _TRUE)
        {
            // Enable Scrambling
            ScalerDisplayDpTxXSetScrambleSeed(_ENABLE, GET_DISPLAY_DP_TXX_SCRAMBLE_TYPE(enumDisplayDpTxOutputPort));

            // Set TP2 Pattern Type
            pData[0] = ScalerDisplayDpTxXSetTp2PatternType(enumDisplayDpTxOutputPort);
        }
        else
        {
            // Disable De-Scrambling
            ScalerDisplayDpTxXSetScrambleSeed(_DISABLE, GET_DISPLAY_DP_TXX_SCRAMBLE_TYPE(enumDisplayDpTxOutputPort));

            // Set TP2 Pattern Type
            pData[0] = ScalerDisplayDpTxXSetTp2PatternType(enumDisplayDpTxOutputPort) | _DISPLAY_DP_TX_SCRAMBLING_DISABLE;
        }

        pData[1] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane0Adjust;
        pData[2] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane1Adjust;
        pData[3] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane2Adjust;
        pData[4] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane3Adjust;

        // Write DPCD 102h-107h to Start TP2
        ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x02, 5, pData);
    }
    else
    {
        // Set Output Signal According to Request
        ScalerDisplayDpTxXMLPHYSet(enumDisplayDpTxOutputPort);

        pData[0] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane0Adjust;
        pData[1] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane1Adjust;
        pData[2] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane2Adjust;
        pData[3] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane3Adjust;

        // Write DPCD 103h-107h (Voltage Swing and Pre-emphasis)
        ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x03, 4, pData);
    }

    // Delay Time us [400,x] Delay 400us
    DELAY_XUS(400);

    // Read Lane Status and Request Adjust Level
    ScalerDisplayDpTxXNativeAuxRead(0x00, 0x02, 0x02, 6, pData);
    g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane01LTStatus = pData[0];
    g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane23LTStatus = pData[1];
    g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLaneAlignStatus = pData[2];
    g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucAdjustReqLane01 = pData[4];
    g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucAdjustReqLane23 = pData[5];

    // CDR unlock => Reduce bit rate and return to TP1
    switch(GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort))
    {
        case _DP_FOUR_LANE:

            if((GET_DISPLAY_DP_TXX_LANE3_CR_DONE(enumDisplayDpTxOutputPort) != _TRUE) ||
               (GET_DISPLAY_DP_TXX_LANE2_CR_DONE(enumDisplayDpTxOutputPort) != _TRUE) ||
               (GET_DISPLAY_DP_TXX_LANE1_CR_DONE(enumDisplayDpTxOutputPort) != _TRUE) ||
               (GET_DISPLAY_DP_TXX_LANE0_CR_DONE(enumDisplayDpTxOutputPort) != _TRUE))
            {
                CLR_DISPLAY_DP_TXX_TP2_CNT(enumDisplayDpTxOutputPort);

                return _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
            }

            if((GET_DISPLAY_DP_TXX_LANE3_EQ_DONE(enumDisplayDpTxOutputPort) == _TRUE) &&
               (GET_DISPLAY_DP_TXX_LANE2_EQ_DONE(enumDisplayDpTxOutputPort) == _TRUE) &&
               (GET_DISPLAY_DP_TXX_LANE1_EQ_DONE(enumDisplayDpTxOutputPort) == _TRUE) &&
               (GET_DISPLAY_DP_TXX_LANE0_EQ_DONE(enumDisplayDpTxOutputPort) == _TRUE))
            {
                if(GET_DISPLAY_DP_TXX_LANE_ALIGN_DONE(enumDisplayDpTxOutputPort) == _TRUE)
                {
                    CLR_DISPLAY_DP_TXX_TP2_CNT(enumDisplayDpTxOutputPort);

                    return _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS;
                }
            }

            break;

        case _DP_TWO_LANE:

            if((GET_DISPLAY_DP_TXX_LANE1_CR_DONE(enumDisplayDpTxOutputPort) != _TRUE) ||
               (GET_DISPLAY_DP_TXX_LANE0_CR_DONE(enumDisplayDpTxOutputPort) != _TRUE))
            {
                CLR_DISPLAY_DP_TXX_TP2_CNT(enumDisplayDpTxOutputPort);

                return _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
            }

            if((GET_DISPLAY_DP_TXX_LANE1_EQ_DONE(enumDisplayDpTxOutputPort) == _TRUE) &&
               (GET_DISPLAY_DP_TXX_LANE0_EQ_DONE(enumDisplayDpTxOutputPort) == _TRUE))
            {
                if(GET_DISPLAY_DP_TXX_LANE_ALIGN_DONE(enumDisplayDpTxOutputPort) == _TRUE)
                {
                    CLR_DISPLAY_DP_TXX_TP2_CNT(enumDisplayDpTxOutputPort);

                    return _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS;
                }
            }
            break;

        case _DP_ONE_LANE:
        default:

            if(GET_DISPLAY_DP_TXX_LANE0_CR_DONE(enumDisplayDpTxOutputPort) != _TRUE)
            {
                CLR_DISPLAY_DP_TXX_TP2_CNT(enumDisplayDpTxOutputPort);

                return _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
            }

            if(GET_DISPLAY_DP_TXX_LANE0_EQ_DONE(enumDisplayDpTxOutputPort) == _TRUE)
            {
                if(GET_DISPLAY_DP_TXX_LANE_ALIGN_DONE(enumDisplayDpTxOutputPort) == _TRUE)
                {
                    CLR_DISPLAY_DP_TXX_TP2_CNT(enumDisplayDpTxOutputPort);

                    return _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS;
                }
            }

            break;
    }

    if(GET_DISPLAY_DP_TXX_TP2_CNT(enumDisplayDpTxOutputPort) == 5)
    {
        CLR_DISPLAY_DP_TXX_TP2_CNT(enumDisplayDpTxOutputPort);

        return _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
    }
    else
    {
        ADD_DISPLAY_DP_TXX_TP2_CNT(enumDisplayDpTxOutputPort);
    }

    switch(GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort))
    {
        case _DP_FOUR_LANE:

            ScalerDisplayDpTxXTP2Lane3Adjust(enumDisplayDpTxOutputPort);
            ScalerDisplayDpTxXTP2Lane2Adjust(enumDisplayDpTxOutputPort);
            ScalerDisplayDpTxXTP2Lane1Adjust(enumDisplayDpTxOutputPort);
            ScalerDisplayDpTxXTP2Lane0Adjust(enumDisplayDpTxOutputPort);
            break;

        case _DP_TWO_LANE:

            ScalerDisplayDpTxXTP2Lane1Adjust(enumDisplayDpTxOutputPort);
            ScalerDisplayDpTxXTP2Lane0Adjust(enumDisplayDpTxOutputPort);
            break;

        case _DP_ONE_LANE:
        default:

            ScalerDisplayDpTxXTP2Lane0Adjust(enumDisplayDpTxOutputPort);
            break;
    }

    return _DISPLAY_DP_TX_TRAINING_PATTERN2_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training Pattern End
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXTrainPatternEnd(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
#if(_PANEL_DPTX_AUX_SET_TP_END_SEQUENCE == _TRAIN_PATTERN_END_BEFORE_IDEL_PATTERN)
    // Write TRAINING_PATTERN_SET = 00
    pData[0] = _DISPLAY_DP_TX_TPS_NONE;
    ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x02, 1, pData);
#endif

    if(GET_DISPLAY_DP_TXX_LT_RESULT(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_TRAINING_PASS)
    {
        // Enable Scramble Seed
        ScalerDisplayDpTxXSetScrambleSeed(_ENABLE, GET_DISPLAY_DP_TXX_SCRAMBLE_TYPE(enumDisplayDpTxOutputPort));

#if(_PANEL_DPTX_SCRAMBLE_SEED_TYPE == _PANEL_DPTX_SCRAMBLE_SEED_AUTO)
        if(GET_DISPLAY_DP_TXX_ALTERNATE_SR_CAPABLE(enumDisplayDpTxOutputPort) == _TRUE)
        {
            pData[0] = ((BYTE)GET_DISPLAY_DP_TXX_FRAMING_CHANGE_CAPABLE(enumDisplayDpTxOutputPort) << 1) | _BIT0;
            ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x0A, 1, pData);
        }
#endif
        // Enable BS replaced by SR
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

        // Main Link switch to IDLE Pattern
        ScalerDisplayDpTxXVideoStreamOutput(enumDisplayDpTxOutputPort, _DISABLE);

        // Panel DPTx Power Sequence Check Point
        ScalerDisplayDpTxSetPowerSequenceCheckPoint(enumDisplayDpTxOutputPort, _DPTX_POWER_SEQUENCE_IDLE_PATTERN);
    }
    else
    {
        // Main Link switch to IDLE Pattern
        ScalerDisplayDpTxXVideoStreamOutput(enumDisplayDpTxOutputPort, _DISABLE);

        // Panel DPTx Power Sequence Check Point
        ScalerDisplayDpTxSetPowerSequenceCheckPoint(enumDisplayDpTxOutputPort, _DPTX_POWER_SEQUENCE_IDLE_PATTERN);
    }
}

//--------------------------------------------------
// Description  : Set Tx0 Tx Bist Mode
// Input Value  : _DISPLAY_DP_TX_TPS_NONE, _DISPLAY_DP_TX_TPS_1, _DISPLAY_DP_TX_TPS_2, _DISPLAY_DP_TX_TPS_3
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxXSetTpsPattern(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, EnumDisplayDPTxMainLinkPattern enumDisplayDPTxMainLinkPattern)
{
    switch(enumDisplayDPTxMainLinkPattern)
    {
        case _DISPLAY_DP_TX_OUTPUT_TPS1:

#if(_HW_DISPLAY_DPTX_TPS1_8_BIT_MODE == _ON)
            // Set 8 Bits Mode
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#else
            // Set 10 Bits Mode
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~(_BIT7 | _BIT6), 0x00);
#endif
            // Set TP1 Type
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_04_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), enumDisplayDPTxMainLinkPattern);

            break;

        case _DISPLAY_DP_TX_OUTPUT_TPS2:

            // Set 8 Bits Mode
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Set TP2 Type
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_04_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), enumDisplayDPTxMainLinkPattern);

            break;

        case _DISPLAY_DP_TX_OUTPUT_TPS3:

            // Set 8 Bits Mode
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Set TP3 Type
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_04_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), enumDisplayDPTxMainLinkPattern);

            break;

        case _DISPLAY_DP_TX_OUTPUT_TPS4:

            // Disable Enhanced Mode
            ScalerDisplayDpTxXEnhanceFramingMode(_DISABLE);

            // Enable BS replaced by SR
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~_BIT4, _BIT4);

            // Set 8 Bits Mode
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Set TP4 Type
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_04_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), enumDisplayDPTxMainLinkPattern);

            // Select CP2520 pattern 3 "SR-BS-BS-SR-248 of 00h's"
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_30_COMPLIANCE_EYE_PATTERN, ~(_BIT1 | _BIT0), _BIT1);

            // Set TPS4 eyecounter HW auto reset
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_4C_DUMMY_2, ~(_BIT0), _BIT0);

            break;

        case _DISPLAY_DP_TX_OUTPUT_IDLE_PATTERN:

            // Main Link Switch to IDLE pattern
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_04_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), enumDisplayDPTxMainLinkPattern);

            break;

        case _DISPLAY_DP_TX_OUTPUT_VIDEO_PATTERN:

            if(GET_DISPLAY_DP_TXX_FRAMING_CHANGE_CAPABLE(enumDisplayDpTxOutputPort) == _TRUE)
            {
                ScalerDisplayDpTxXEnhanceFramingMode(_ENABLE);
            }
            else
            {
                ScalerDisplayDpTxXEnhanceFramingMode(GET_DISPLAY_DP_TXX_ENHANCE_FRAMING(enumDisplayDpTxOutputPort));
            }

            // Set 8 Bits Mode
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~(_BIT7), _BIT7);

            // Set Video Pattern Type
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_04_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), enumDisplayDPTxMainLinkPattern);

            break;

        default:
            break;
    }

    if(enumDisplayDPTxMainLinkPattern == _DISPLAY_DP_TX_OUTPUT_VIDEO_PATTERN)
    {
        // Double buffer only by Vsync
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_04_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // Direct Apply Pattern
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_04_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), 0x00);
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_04_DPTX_ML_PAT_SEL, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : Set Tx0 Tx Scramble Seed
// Input Value  : ucScambleSeed
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxXSetScrambleSeed(bit bEnable, EnumDisplayDPTxScrambleSeedType enumDisplayDPTxScrambleSeedType)
{
    if(bEnable == _ENABLE)
    {
        if(enumDisplayDPTxScrambleSeedType == _DISPLAY_DP_TX_SCRAMBLE_SEED_0XFFFF)
        {
            // Scramble default value = 16'hffff
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~(_BIT1), 0x00);
        }
        else
        {
            // Scramble default value = 16'hfffe
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~(_BIT1), _BIT1);
        }

        // Enable Scramble
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~(_BIT0), _BIT0);
    }
    else
    {
        // Disable Scramble
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~(_BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane0 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDpTxXTP1Lane0Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TXX_LANE0_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort) + GET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort)) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE0_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort, (_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort)));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) == GET_DISPLAY_DP_TXX_LANE0_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort))
    {
        ADD_DISPLAY_DP_TXX_TP1_LANE0_SAME_VOL_CNT(enumDisplayDpTxOutputPort);

        if((GET_DISPLAY_DP_TXX_TP1_LANE0_SAME_VOL_CNT(enumDisplayDpTxOutputPort) == 5) || ((GET_DISPLAY_DP_TXX_TP1_LANE0_SAME_VOL_CNT(enumDisplayDpTxOutputPort) == 1) && (GET_DISPLAY_DP_TXX_LANE0_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TXX_TP1_LANE0_SAME_VOL_CNT(enumDisplayDpTxOutputPort);

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TXX_TP1_LANE0_SAME_VOL_CNT(enumDisplayDpTxOutputPort);
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE0_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort));
    SET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE0_ADJUST_PRE_EMPHASIS(enumDisplayDpTxOutputPort));

    if(GET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }

    if(GET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane1 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDpTxXTP1Lane1Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TXX_LANE1_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort) + GET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort)) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE1_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort, (_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort)));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) == GET_DISPLAY_DP_TXX_LANE1_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort))
    {
        ADD_DISPLAY_DP_TXX_TP1_LANE1_SAME_VOL_CNT(enumDisplayDpTxOutputPort);

        if((GET_DISPLAY_DP_TXX_TP1_LANE1_SAME_VOL_CNT(enumDisplayDpTxOutputPort) == 5) || ((GET_DISPLAY_DP_TXX_TP1_LANE1_SAME_VOL_CNT(enumDisplayDpTxOutputPort) == 1) && (GET_DISPLAY_DP_TXX_LANE1_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TXX_TP1_LANE1_SAME_VOL_CNT(enumDisplayDpTxOutputPort);

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TXX_TP1_LANE1_SAME_VOL_CNT(enumDisplayDpTxOutputPort);
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE1_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort));
    SET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE1_ADJUST_PRE_EMPHASIS(enumDisplayDpTxOutputPort));

    if(GET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }

    if(GET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane2 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDpTxXTP1Lane2Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TXX_LANE2_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort) + GET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort)) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE2_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort, (_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort)));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) == GET_DISPLAY_DP_TXX_LANE2_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort))
    {
        ADD_DISPLAY_DP_TXX_TP1_LANE2_SAME_VOL_CNT(enumDisplayDpTxOutputPort);

        if((GET_DISPLAY_DP_TXX_TP1_LANE2_SAME_VOL_CNT(enumDisplayDpTxOutputPort) == 5) || ((GET_DISPLAY_DP_TXX_TP1_LANE2_SAME_VOL_CNT(enumDisplayDpTxOutputPort) == 1) && (GET_DISPLAY_DP_TXX_LANE2_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TXX_TP1_LANE2_SAME_VOL_CNT(enumDisplayDpTxOutputPort);

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TXX_TP1_LANE2_SAME_VOL_CNT(enumDisplayDpTxOutputPort);
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE2_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort));
    SET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE2_ADJUST_PRE_EMPHASIS(enumDisplayDpTxOutputPort));

    if(GET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }

    if(GET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane3 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDpTxXTP1Lane3Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TXX_LANE3_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort) + GET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort)) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE3_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort, (_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort)));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) == GET_DISPLAY_DP_TXX_LANE3_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort))
    {
        ADD_DISPLAY_DP_TXX_TP1_LANE3_SAME_VOL_CNT(enumDisplayDpTxOutputPort);

        if((GET_DISPLAY_DP_TXX_TP1_LANE3_SAME_VOL_CNT(enumDisplayDpTxOutputPort) == 5) || ((GET_DISPLAY_DP_TXX_TP1_LANE3_SAME_VOL_CNT(enumDisplayDpTxOutputPort) == 1) && (GET_DISPLAY_DP_TXX_LANE3_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TXX_TP1_LANE3_SAME_VOL_CNT(enumDisplayDpTxOutputPort);

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TXX_TP1_LANE3_SAME_VOL_CNT(enumDisplayDpTxOutputPort);
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE3_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort));
    SET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE3_ADJUST_PRE_EMPHASIS(enumDisplayDpTxOutputPort));

    if(GET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }

    if(GET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane0  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXTP2Lane0Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) + GET_DISPLAY_DP_TXX_LANE0_ADJUST_PRE_EMPHASIS(enumDisplayDpTxOutputPort)) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, (_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort)));
    }
    else
    {
        SET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE0_ADJUST_PRE_EMPHASIS(enumDisplayDpTxOutputPort));
        SET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE0_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort));
    }

    if(GET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }

    if(GET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane1  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXTP2Lane1Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) + GET_DISPLAY_DP_TXX_LANE1_ADJUST_PRE_EMPHASIS(enumDisplayDpTxOutputPort)) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, (_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort)));
    }
    else
    {
        SET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE1_ADJUST_PRE_EMPHASIS(enumDisplayDpTxOutputPort));
        SET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE1_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort));
    }

    if(GET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }

    if(GET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane2  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXTP2Lane2Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) + GET_DISPLAY_DP_TXX_LANE2_ADJUST_PRE_EMPHASIS(enumDisplayDpTxOutputPort)) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, (_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort)));
    }
    else
    {
        SET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE2_ADJUST_PRE_EMPHASIS(enumDisplayDpTxOutputPort));
        SET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE2_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort));
    }

    if(GET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }

    if(GET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane3  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXTP2Lane3Adjust(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) + GET_DISPLAY_DP_TXX_LANE3_ADJUST_PRE_EMPHASIS(enumDisplayDpTxOutputPort)) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, (_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort)));
    }
    else
    {
        SET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE3_ADJUST_PRE_EMPHASIS(enumDisplayDpTxOutputPort));
        SET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort, GET_DISPLAY_DP_TXX_LANE3_ADJUST_VOL_SWING(enumDisplayDpTxOutputPort));
    }

    if(GET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    }

    if(GET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort) == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }
    else
    {
        CLR_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);
    }
}

#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Link Signal Force Output
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXLinkForceOutput(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    ScalerDisplayDpTxXForceOutputPreCheck(enumDisplayDpTxOutputPort);

    ScalerDisplayDpTxXTPInitialSet(enumDisplayDpTxOutputPort);

    // Set Output Signal According to Request
    ScalerDisplayDpTxXMLPHYSet(enumDisplayDpTxOutputPort);

    // Select TP1
    ScalerDisplayDpTxXSetTpsPattern(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_OUTPUT_TPS1);

    pData[0] = (_DISPLAY_DP_TX_TPS_1 | _DISPLAY_DP_TX_SCRAMBLING_DISABLE);
    pData[1] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane0Adjust;
    pData[2] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane1Adjust;
    pData[3] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane2Adjust;
    pData[4] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane3Adjust;

    // Write DPCD 102h-107h to Start TP1
    ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x02, 5, pData);

    // Delay Time us [400,x] Delay 400us
    DELAY_XUS(400);

    if(_PANEL_DPTX_LINK_RATE >= _PANEL_DPTX_LINK_HBR3)
    {
        // Enable Scrambling
        ScalerDisplayDpTxXSetScrambleSeed(_ENABLE, GET_DISPLAY_DP_TXX_SCRAMBLE_TYPE(enumDisplayDpTxOutputPort));

        // Select TP4
        ScalerDisplayDpTxXSetTpsPattern(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_OUTPUT_TPS4);

        pData[0] = _DISPLAY_DP_TX_TPS_4;
    }
    else if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
    {
        // Disable De-Scrambling
        ScalerDisplayDpTxXSetScrambleSeed(_DISABLE, _DISPLAY_DP_TX_SCRAMBLE_SEED_NONE);

        // Select TP3
        ScalerDisplayDpTxXSetTpsPattern(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_OUTPUT_TPS3);

        pData[0] = (_DISPLAY_DP_TX_TPS_3 | _DISPLAY_DP_TX_SCRAMBLING_DISABLE);
    }
    else
    {
        // Disable De-Scrambling
        ScalerDisplayDpTxXSetScrambleSeed(_DISABLE, _DISPLAY_DP_TX_SCRAMBLE_SEED_NONE);

        // Select TP2
        ScalerDisplayDpTxXSetTpsPattern(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_OUTPUT_TPS2);

        pData[0] = (_DISPLAY_DP_TX_TPS_2 | _DISPLAY_DP_TX_SCRAMBLING_DISABLE);
    }

    pData[1] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane0Adjust;
    pData[2] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane1Adjust;
    pData[3] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane2Adjust;
    pData[4] = g_pstDisplayDpTxXLTInfo[enumDisplayDpTxOutputPort].ucLane3Adjust;

    // Write DPCD 102h-107h to Start TP2
    ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x02, 5, pData);

    // Delay Time us [400,x] Delay 400us
    DELAY_XUS(400);

#if(_PANEL_DPTX_AUX_SET_TP_END_SEQUENCE == _TRAIN_PATTERN_END_BEFORE_IDEL_PATTERN)
    // Training Pattern End For Link Training
    pData[0] = _DISPLAY_DP_TX_TPS_NONE;
    ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x02, 1, pData);
#endif

    // Enable Scramble Seed
    ScalerDisplayDpTxXSetScrambleSeed(_ENABLE, GET_DISPLAY_DP_TXX_SCRAMBLE_TYPE(enumDisplayDpTxOutputPort));

#if(_PANEL_DPTX_SCRAMBLE_SEED_TYPE == _PANEL_DPTX_SCRAMBLE_SEED_AUTO)
    if(GET_DISPLAY_DP_TXX_ALTERNATE_SR_CAPABLE(enumDisplayDpTxOutputPort) == _TRUE)
    {
        pData[0] = ((BYTE)GET_DISPLAY_DP_TXX_FRAMING_CHANGE_CAPABLE(enumDisplayDpTxOutputPort) << 1) | _BIT0;
        ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x0A, 1, pData);
    }
#endif

    // Enable BS replaced by SR
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

    // Main Link switch to IDLE Pattern
    ScalerDisplayDpTxXVideoStreamOutput(enumDisplayDpTxOutputPort, _DISABLE);
}

//--------------------------------------------------
// Description  : DP Tx Force Output Pre-Check
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXForceOutputPreCheck(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    if(GET_DISPLAY_DP_TXX_LINK_CONFIG(enumDisplayDpTxOutputPort) == _TRUE)
    {
        return;
    }

    switch(_PANEL_DPTX_LANE_NUMBER)
    {
        case _PANEL_DPTX_LANE_NUMBER_1:

            // Set Lane Number: 1
            SET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort, _DP_ONE_LANE);

            break;

        case _PANEL_DPTX_LANE_NUMBER_2:

            // Set Lane Number: 2
            SET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort, _DP_TWO_LANE);

            break;

        case _PANEL_DPTX_LANE_NUMBER_4:
        case _PANEL_DPTX_LANE_NUMBER_8:
        case _PANEL_DPTX_LANE_NUMBER_16:

            // Set Lane Number: 4
            SET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort, _DP_FOUR_LANE);

            break;

        default:

            // Set Lane Number: 4
            SET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort, _DP_FOUR_LANE);

            break;
    }

    if(_PANEL_DPTX_LINK_RATE >= _PANEL_DPTX_LINK_HBR2)
    {
        // Check TP3 support
        if(_PANEL_DPTX_LT_TPS3_SUPPORT_BY_USER == _ON)
        {
            SET_DISPLAY_DP_TXX_TP3_SUPPORT(enumDisplayDpTxOutputPort);
        }
        else
        {
            CLR_DISPLAY_DP_TXX_TP3_SUPPORT(enumDisplayDpTxOutputPort);
        }
    }
    else
    {
        CLR_DISPLAY_DP_TXX_TP3_SUPPORT(enumDisplayDpTxOutputPort);
    }

    if(_PANEL_DPTX_LINK_RATE >= _PANEL_DPTX_LINK_HBR3)
    {
        // Check TP4 support
        if(_PANEL_DPTX_LT_TPS4_SUPPORT_BY_USER == _ON)
        {
            SET_DISPLAY_DP_TXX_TP4_SUPPORT(enumDisplayDpTxOutputPort);
        }
        else
        {
            CLR_DISPLAY_DP_TXX_TP4_SUPPORT(enumDisplayDpTxOutputPort);
        }
    }
    else
    {
        CLR_DISPLAY_DP_TXX_TP4_SUPPORT(enumDisplayDpTxOutputPort);
    }

    // Set Enhanceed Framing
    SET_DISPLAY_DP_TXX_ENHANCE_FRAMING(enumDisplayDpTxOutputPort, _PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING);

    // Set Max Downspread
    SET_DISPLAY_DP_TXX_DOWN_SPREAD(enumDisplayDpTxOutputPort, _PANEL_DPTX_FORCE_MSA_DOWN_SPREAD);

    // Set Framing Change for eDP
    SET_DISPLAY_DP_TXX_FRAMING_CHANGE_CAPABLE(enumDisplayDpTxOutputPort, _PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP);

    // Set Alternate SR Capable for eDP
    SET_DISPLAY_DP_TXX_ALTERNATE_SR_CAPABLE(enumDisplayDpTxOutputPort, _PANEL_DPTX_FORCE_ALTERNATE_SR_CAP);
}
#endif

//--------------------------------------------------
// Description  : DP Tx Link Training Link Rate Reduce
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXSignalReset(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Set Voltage Swing and pre-emphasis Variable to level 0
    CLR_DISPLAY_DP_TXX_TP1_LANE0_SAME_VOL_CNT(enumDisplayDpTxOutputPort);
    CLR_DISPLAY_DP_TXX_TP1_LANE1_SAME_VOL_CNT(enumDisplayDpTxOutputPort);
    CLR_DISPLAY_DP_TXX_TP1_LANE2_SAME_VOL_CNT(enumDisplayDpTxOutputPort);
    CLR_DISPLAY_DP_TXX_TP1_LANE3_SAME_VOL_CNT(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    SET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    SET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    SET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);

    SET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING_MAX_REACH(enumDisplayDpTxOutputPort);
    SET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH(enumDisplayDpTxOutputPort);

    // Clear TP2 Count
    CLR_DISPLAY_DP_TXX_TP2_CNT(enumDisplayDpTxOutputPort);

    // Set Output Signal According to Request
    ScalerDisplayDpTxXMLPHYSet(enumDisplayDpTxOutputPort);
}

//--------------------------------------------------
// Description  : Handle Enhance Framing
// Input Value  : _ENABLE of _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxXEnhanceFramingMode(bit bEnable)
{
    // Enable Enhancement
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_00_DP_MAC_CTRL, ~_BIT2, ((BYTE)bEnable << 2));
}

//--------------------------------------------------
// Description  : Measure function for DPTX SST D0
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDisplayDpTxXMeasureInputInfo(EnumDisplayDpMacSel enumDisplayDpMacSel)
{
    // DVTotal
    WORD usDVTotal = 0;

#if(_FRC_SUPPORT == _ON)
    BYTE ucTemp = 0;
    StructMemoryMNTracking stMNTracking = {0};
#endif

    // Htotal
    g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHTotal = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_H_TOTAL) / _PANEL_DPTX_DCLK_DIV / _PANEL_DPTX_MSO_DIV;

    // Hstart
    g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHStart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START) / _PANEL_DPTX_DCLK_DIV / _PANEL_DPTX_MSO_DIV;

    // Hwidth
    g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHWidth = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_WIDTH) / _PANEL_DPTX_DCLK_DIV / _PANEL_DPTX_MSO_DIV;

    // Hsyc
    g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHSWidth = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_HS_WIDTH) / _PANEL_DPTX_DCLK_DIV / _PANEL_DPTX_MSO_DIV;

    // Hsyc polarity
    g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].b1HSP = 1;

    switch(ScalerMDomainGetFrameSyncMode())
    {
#if(_FRC_SUPPORT == _ON)
        case _MN_FRAME_SYNC_MODE:

            // Get DVtotal of frame sync frame in M:N case
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, _BIT5);
            ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

            // Get N+1 frame
            ScalerMemoryGetMNRatio(&stMNTracking, GET_FS_ACTIVE_INFO_DVF_SELECT());
            ucTemp = stMNTracking.ucNcode + 1;

            // Wait N+1 dvs for get correct data
            do
            {
                ucTemp--;
                ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
            }
            while(ucTemp > 0);

            usDVTotal = ScalerMDomainGetDVtotalLastline();
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);

            PDATA_WORD(1) = GET_FREE_RUN_DVTOTAL();

            // Compare DVtotal of frame sync frame and DVtotal of free run frame
            if(PDATA_WORD(1) < usDVTotal)
            {
                usDVTotal = PDATA_WORD(1);
            }

            break;
#endif

        case _FRAME_SYNC_MODE:

            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
            ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
            ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
            ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
            usDVTotal = ScalerMDomainGetDVtotalLastline();

            break;

        default:

            usDVTotal = GET_FREE_RUN_DVTOTAL();

            break;
    }

    // Vtotal
    g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usVTotal = ((usDVTotal + 1) & 0x1FFF);

    // VStart
    g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usVStart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START);

    // VHeight
    g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usVHeight = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_HEIGHT);

    // Vsync
    g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usVSWidth = ScalerDDomainGetDisplayFormat_R1a1(_DISPLAY_FORMAT_VS_WIDTH);

    // Vsyc polarity
    g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].b1VSP = 1;

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
    DebugMessageScaler("Display Dp Tx usVTotal", g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usVTotal);
    DebugMessageScaler("Display Dp Tx usVHeight", g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usVHeight);
    DebugMessageScaler("Display Dp Tx usHTotal", g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHTotal);
    DebugMessageScaler("Display Dp Tx usHWidth", g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel].usHWidth);

    switch(enumDisplayDpMacSel)
    {
        case _DISPLAY_DP_TX_MAC0:

            if(ScalerMcuDataExchangeSendData(_DATA_EXCHANGE_KERNEL_DATA, _DATA_EXCHANGE_KERNEL_DATA_TIMING_INFO_0, sizeof(g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel]), (BYTE *)(&g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel])) == _TRUE)
            {
                DebugMessageScaler("Data Exchange Send DataTiming Info done", 0);
            }
            else
            {
                DebugMessageScaler("Data Exchange Send DataTiming Info false", 0);
            }

            break;

        case _DISPLAY_DP_TX_MAC1:

            if(ScalerMcuDataExchangeSendData(_DATA_EXCHANGE_KERNEL_DATA, _DATA_EXCHANGE_KERNEL_DATA_TIMING_INFO_1, sizeof(g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel]), (BYTE *)(&g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel])) == _TRUE)
            {
                DebugMessageScaler("Data Exchange Send DataTiming Info done", 1);
            }
            else
            {
                DebugMessageScaler("Data Exchange Send DataTiming Info false", 1);
            }

            break;

        case _DISPLAY_DP_TX_MAC2:

            if(ScalerMcuDataExchangeSendData(_DATA_EXCHANGE_KERNEL_DATA, _DATA_EXCHANGE_KERNEL_DATA_TIMING_INFO_2, sizeof(g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel]), (BYTE *)(&g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel])) == _TRUE)
            {
                DebugMessageScaler("Data Exchange Send DataTiming Info done", 2);
            }
            else
            {
                DebugMessageScaler("Data Exchange Send DataTiming Info false", 2);
            }

            break;

        case _DISPLAY_DP_TX_MAC3:

            if(ScalerMcuDataExchangeSendData(_DATA_EXCHANGE_KERNEL_DATA, _DATA_EXCHANGE_KERNEL_DATA_TIMING_INFO_3, sizeof(g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel]), (BYTE *)(&g_pstDisplayDpTxXTimingInfo[enumDisplayDpMacSel])) == _TRUE)
            {
                DebugMessageScaler("Data Exchange Send DataTiming Info done", 3);
            }
            else
            {
                DebugMessageScaler("Data Exchange Send DataTiming Info false", 3);
            }

            break;

        default:
            break;
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3     //Linqian
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXMLPHYSet(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    switch(GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort))
    {
        case _DP_FOUR_LANE:

            // Adjust Lane3 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDpTxXSetSignalLevel(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LANE_3, GET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort), GET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort));

            // Adjust Lane2 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDpTxXSetSignalLevel(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LANE_2, GET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort), GET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort));

            // Adjust Lane1 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDpTxXSetSignalLevel(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LANE_1, GET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort), GET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort));

            // Adjust Lane0 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDpTxXSetSignalLevel(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort), GET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort));

            break;

        case _DP_TWO_LANE:

            // Adjust Lane1 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDpTxXSetSignalLevel(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LANE_1, GET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort), GET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort));

            // Adjust Lane0 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDpTxXSetSignalLevel(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort), GET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort));

            break;

        case _DP_ONE_LANE:

            // Adjust Lane0 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDpTxXSetSignalLevel(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort), GET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort));

            break;

        default:

            // Adjust Lane0 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDpTxXSetSignalLevel(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(enumDisplayDpTxOutputPort), GET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(enumDisplayDpTxOutputPort));

            break;
    }
}

//--------------------------------------------------
// Description  : DP Tx Native Aux Write
// Input Value  : ucCommand --> Native Aux Write Command
//                ucHighAddress --> High Byte of  Native Aux Write Address
//                ucMidAddress --> Middle Byte of  Native Aux Write Address
//                ucLowAddress --> Low Byte of  Native Aux Write Address
//                ucLength --> Native Aux Write Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of  Native Aux Write
// Output Value : TRUE --> Native Aux Write Sucessful
//--------------------------------------------------
bit ScalerDisplayDpTxXNativeAuxWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray)
{
    if(ScalerDisplayDpTxXAuxWrite((0x80 | ucAddrH), ucAddrM, ucAddrL, ucLength, pucWriteArray) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Native Aux Read
// Input Value  : ucCommand --> Native Aux Read Command
//                ucHighAddress --> High Byte of  Native Aux Read Address
//                ucMidAddress --> Middle Byte of  Native Aux Read Address
//                ucLowAddress --> Low Byte of  Native Aux Read Address
//                ucLength --> Native Aux Read Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of  Native Aux Read
// Output Value : TRUE --> Native Aux Read Sucessful
//--------------------------------------------------
bit ScalerDisplayDpTxXNativeAuxRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    if(ScalerDisplayDpTxXAuxRead((0x90 | ucAddrH), ucAddrM, ucAddrL, ucLength, pucReadArray) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx I2CoverAux Write
// Input Value  : ucSlaveAddress --> SlaveAddress of I2CoverAux Write
//                ucSubAddress --> SubAddress of I2CoverAux Write
//                ucLength --> Length of I2CoverAux Write
//                pWriteArray --> Data of I2CoverAux Write
// Output Value : TRUE --> Native Aux Write Sucessful
//--------------------------------------------------
bit ScalerDisplayDpTxXAuxI2CoverWrite(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT)
{
    if(ScalerDisplayDpTxXAuxWrite((0x00 | ((BYTE)bMOT << 6)), 0x00, ucSlaveAddress, ucLength, pucDataArray) == _FALSE)
    {
        if(ScalerDisplayDpTxXAuxWrite((0x00 | ((BYTE)bMOT << 6)), 0x00, ucSlaveAddress, ucLength, pucDataArray) == _FALSE)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx I2CoverAux Write
// Input Value  : ucSlaveAddress --> SlaveAddress of I2CoverAux Read
//                ucSubAddress --> SubAddress of I2CoverAux Read
//                ucLength --> Length of I2CoverAux Read
//                pWriteArray --> Data of I2CoverAux Read
// Output Value : TRUE --> Native Aux Write Sucessful
//--------------------------------------------------
bit ScalerDisplayDpTxXAuxI2CoverRead(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT)
{
    if(ScalerDisplayDpTxXAuxRead((0x10 | ((BYTE)bMOT << 6)), 0x00, ucSlaveAddress, ucLength, pucDataArray) == _FALSE)
    {
        if(ScalerDisplayDpTxXAuxRead((0x10 | ((BYTE)bMOT << 6)), 0x00, ucSlaveAddress, ucLength, pucDataArray) == _FALSE)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Aux Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxXAuxInitial(void)
{
    // Power Down Aux Channel
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_40_AUX_TX_CTRL, ~_BIT0, 0x00);

    SET_DISPLAY_DP_TXX_AUX_RECEIVE_MODE(GET_DISPLAY_DP_TX_PORT(), _AUX_DIFF_MODE);

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
    ScalerDisplayDpTxXAuxAutoCalibration();
#endif

    // Setting Aux
    ScalerDisplayDpTxXAuxPHYSet(_DISPLAY_DP_TX_AUX_DIFF_MODE);

    // Set Aux Timeout Enable
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_44_AUX_TIMEOUT, ~_BIT15, _BIT15);

    // Set Aux Timeout
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_44_AUX_TIMEOUT, 0x00, 0x15);

    // Set Aux HW Retry
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_7C_AUX_RETRY_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _DISPLAY_DP_TX_AUX_RETRY_LIMIT);

    // Sync end Pattern Error Handle Disable
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_08_AUX_IRQ_EN, ~_BIT1, _BIT1);

    // Power On Aux Channel
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_40_AUX_TX_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Dp Tx Aux PHY Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXAuxPHYSet(BYTE ucMode)
{
#if(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_WITH_AUTO_CALIBRATION)
    BYTE ucPVTH = 0;
    BYTE ucNVTH = 0;

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
#if(_HW_DP_AUX_AUTO_CALIBRATION_ORIENTATION == _DP_AUX_AUTO_CALIBRATION_PN_INVERSE)
    if((SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_24_AUX_REV_0, 0x00) & _BIT0) == _BIT0)
    {
        ucPVTH = g_pucDisplayDpTxXAuxNVth[GET_DISPLAY_DP_TX_PORT()];
        ucNVTH = g_pucDisplayDpTxXAuxPVth[GET_DISPLAY_DP_TX_PORT()];
    }
    else
#endif
    {
        ucPVTH = g_pucDisplayDpTxXAuxPVth[GET_DISPLAY_DP_TX_PORT()];
        ucNVTH = g_pucDisplayDpTxXAuxNVth[GET_DISPLAY_DP_TX_PORT()];
    }
#else
#if(_HW_DP_AUX_AUTO_CALIBRATION_ORIENTATION == _DP_AUX_AUTO_CALIBRATION_PN_INVERSE)
    if((SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_24_AUX_REV_0, 0x00) & _BIT0) == _BIT0)
    {
        ucPVTH = 0;
        ucNVTH = _DP_AUX_AUTO_CALIBRATION_VTH;
    }
    else
#endif
    {
        ucPVTH = _DP_AUX_AUTO_CALIBRATION_VTH;
        ucNVTH = 0;
    }
#endif
#endif

    // Set Aux Tx LDO = 1.1V
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_14_AUX_5, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _PANEL_DPTX_AUX_SWING_LEVEL);

    // Rx Vcom = 0.5V
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_10_AUX_4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _ON)
    if(ucMode == _DISPLAY_DP_TX_AUX_SINGLE_MODE)
    {
        // Enable Single-Ended Mode
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_08_AUX_2, ~_BIT5, _BIT5);

        // Vth = 50mV
#if(_HW_DP_AUX_SINGLE_END_GEN == _DP_AUX_SINGLE_END_ONLY)
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_00_DIG_TX_04, ~(_BIT1 | _BIT0), _BIT0);
#elif(_HW_DP_AUX_SINGLE_END_GEN == _DP_AUX_SINGLE_END_COMBO_RX2)
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_00_DIG_TX_04, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
#endif

        // Open ADJR_P
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_04_AUX_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Open ADJR_N
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_18_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
#endif
    {
        switch(GET_DISPLAY_DP_TXX_AUX_RECEIVE_MODE(GET_DISPLAY_DP_TX_PORT()))
        {
            case _AUX_PN_SWAP_MODE:
                // Enable Aux DPHY Swap
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_00_AUX_DIG_PHY, ~_BIT0, _BIT0);

                // aux_inv = 0
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_00_AUX_DIG_PHY, ~_BIT1, 0x00);

#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _ON)
                // Disable Single-Ended Mode
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_08_AUX_2, ~_BIT5, 0x00);
#endif

#if(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_ONLY)
                // Vth = 75mV
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_24_AUX_REV_0, (_BIT2 | _BIT1));
#elif(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_WITH_AUTO_CALIBRATION)
                // Set Vth = 75mV + Offset, |(Bit12:8 - Bit20:16)*5| = Vth
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_24_AUX_AUTO_K, TO_DWORD(0, ucNVTH, ucPVTH, 0));
#endif

                // Set Aux Listen Mode ADJR_P
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_04_AUX_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_AUX_LISTEN_MODE_Z0);


                // Set Aux Listen Mode ADJR_N
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_18_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_AUX_LISTEN_MODE_Z0);

                // Set Aux Talk Mode ADJR
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_3C_DIG_TX_03_2, 0x00, 0x17);
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_1C_DIG_TX_03_1, 0x00, 0x17);

                break;
            case _AUX_DIFF_MODE:
            default:
                // Disable Aux DPHY Swap
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_00_AUX_DIG_PHY, ~_BIT0, 0x00);

                // aux_inv = 0
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_00_AUX_DIG_PHY, ~_BIT1, 0x00);

#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _ON)
                // Disable Single-Ended Mode
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_08_AUX_2, ~_BIT5, 0x00);
#endif

#if(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_ONLY)
                // Vth = 75mV
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_24_AUX_REV_0, (_BIT2 | _BIT1));
#elif(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_WITH_AUTO_CALIBRATION)
                // Set Vth = 75mV + Offset, |(Bit12:8 - Bit20:16)*5| = Vth
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_24_AUX_AUTO_K, TO_DWORD(0, ucNVTH, ucPVTH, 0));
#endif

                // Set Aux Listen Mode ADJR_P
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_04_AUX_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_AUX_LISTEN_MODE_Z0);

                // Set Aux Listen Mode ADJR_N
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_18_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_AUX_LISTEN_MODE_Z0);

                // Set Aux Talk Mode ADJR
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_3C_DIG_TX_03_2, 0x00, 0x17);
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_1C_DIG_TX_03_1, 0x00, 0x17);

                break;
        }
    }

    // Set Aux Talk Mode ADJR
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_3C_DIG_TX_03_2, 0x17);
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_1C_DIG_TX_03_1, 0x17);

    // Aux PN Swap Setting
#if(_PANEL_DPTX_AUX_PN_SWAP_ENABLE == _ENABLE)
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_00_AUX_DIG_PHY, ~_BIT0, _BIT0);
#else
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_00_AUX_DIG_PHY, ~_BIT0, 0x00);
#endif
}

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
//-------------------------------------------------------
// Description  : Aux Rx Auto Calibration offset
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDisplayDpTxXAuxAutoCalibration(void)
{
    EnumDpAuxRxAutoKState enumDisplayDpTxAuxAutoKState = _AUTO_CALIBRATION_INIT;
    BYTE ucDisplayDpTxAuxPVthBackup = 0;
    BYTE ucDisplayDpTxAuxNVthBackup = 0;
    BYTE ucDisplayDpTxAuxPVthBackup2 = 0;
    BYTE ucDisplayDpTxAuxNVthBackup2 = 0;
    BYTE ucTimeout = 0;
    BYTE ucDisplayDpTxAuxPVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
    BYTE ucDisplayDpTxAuxNVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
    BYTE ucAutoCalibrationCount = 0;

    // debsp_time = Value/Dphy Clk ~ 100ns
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_28_AUX_AUTO_K, 0x02, 0x03);

#if(_HW_DP_AUX_AUTO_CALIBRATION_ORIENTATION == _DP_AUX_AUTO_CALIBRATION_PN_INVERSE)
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_18_AUX_6, ~_BIT6, _BIT6);
#endif

    // Set autok_toggle_num = 3(Bit31:29), autok_chk_num = Value*8/Dphy Clk(Bit28:24) ~ 1us, Detect Range N(Bit20:16)/P(Bit12:8), aux_d1_deb_en = 1(Bit2)
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_24_AUX_AUTO_K, TO_DWORD(0x64, ucDisplayDpTxAuxNVthStart, ucDisplayDpTxAuxPVthStart, (_BIT7 | _BIT6 | _BIT2)));

    while((enumDisplayDpTxAuxAutoKState == _AUTO_CALIBRATION_INIT) && (ucAutoCalibrationCount < 2))
    {
        // Enable auto calibration
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_24_AUX_AUTO_K, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), _BIT3);

        // Wait FSM = SET_INIT
        if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_28_AUX_AUTO_K, _BIT(23, 21)) != _BIT21)
        {
            DELAY_5US();
        }

        // aux_rx_vth_set_done = 1
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_24_AUX_AUTO_K, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // Set Timeout
        ucTimeout = 2 * (ucDisplayDpTxAuxNVthStart + ucDisplayDpTxAuxPVthStart) / 5;

        // Polling auto_k_done = 1
        while((SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_24_AUX_AUTO_K, _BIT6) != _BIT6) && (ucTimeout != 0))
        {
            DELAY_5US();

            ucTimeout--;
        }

        // Check fail flag
        if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_24_AUX_AUTO_K, _BIT7) == _BIT7)
        {
            // Detect from n->p
            if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_24_AUX_AUTO_K, _BIT4) == 0x00)
            {
                // Fail result in Aux Trigger at Start Point
                if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_28_AUX_AUTO_K, 0x01) == ucDisplayDpTxAuxNVthStart)
                {
                    if(ucDisplayDpTxAuxNVthStart == _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                    {
                        // Auto Calibration Fail
                        enumDisplayDpTxAuxAutoKState = _AUTO_CALIBRATION_FAIL;
                    }
                    else
                    {
                        // Offset should be Negative or Zero
                        ucDisplayDpTxAuxPVthStart = 5;
                        ucDisplayDpTxAuxNVthStart += 5;

                        // Avoid Vth over limit
                        if(ucDisplayDpTxAuxNVthStart > _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                        {
                            ucDisplayDpTxAuxNVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
                        }
                    }
                }
                // Fail result in Aux never Trigger
                else if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_28_AUX_AUTO_K, 0x00) == ucDisplayDpTxAuxPVthStart)
                {
                    if(ucDisplayDpTxAuxPVthStart == _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                    {
                        // Auto Calibration Fail
                        enumDisplayDpTxAuxAutoKState = _AUTO_CALIBRATION_FAIL;
                    }
                    else
                    {
                        // Offset should be Positive or Zero
                        ucDisplayDpTxAuxPVthStart += 5;
                        ucDisplayDpTxAuxNVthStart = 5;

                        // Avoid Vth over limit
                        if(ucDisplayDpTxAuxPVthStart > _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                        {
                            ucDisplayDpTxAuxPVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
                        }
                    }
                }
            }
            // Detect from p->n
            else
            {
                // Fail result in Aux Trigger at Start Point
                if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_28_AUX_AUTO_K, 0x00) == ucDisplayDpTxAuxPVthStart)
                {
                    if(ucDisplayDpTxAuxPVthStart == _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                    {
                        // Auto Calibration Fail
                        enumDisplayDpTxAuxAutoKState = _AUTO_CALIBRATION_FAIL;
                    }
                    else
                    {
                        // Offset should be Positive or Zero
                        ucDisplayDpTxAuxPVthStart += 5;
                        ucDisplayDpTxAuxNVthStart = 5;

                        // Avoid Vth over limit
                        if(ucDisplayDpTxAuxPVthStart > _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                        {
                            ucDisplayDpTxAuxPVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
                        }
                    }
                }
                // Fail result in Aux never Trigger
                else if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_28_AUX_AUTO_K, 0x01) == ucDisplayDpTxAuxNVthStart)
                {
                    if(ucDisplayDpTxAuxNVthStart == _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                    {
                        // Auto Calibration Fail
                        enumDisplayDpTxAuxAutoKState = _AUTO_CALIBRATION_FAIL;
                    }
                    else
                    {
                        // Offset should be Negative or Zero
                        ucDisplayDpTxAuxPVthStart = 5;
                        ucDisplayDpTxAuxNVthStart += 5;

                        // Avoid Vth over limit
                        if(ucDisplayDpTxAuxNVthStart > _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                        {
                            ucDisplayDpTxAuxNVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
                        }
                    }
                }
            }

            // Refresh Detect Range P/N, Disable auto calibration
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_24_AUX_AUTO_K, TO_DWORD(0x64, ucDisplayDpTxAuxNVthStart, ucDisplayDpTxAuxPVthStart, _BIT2));
        }
        else
        {
            // Detect from n->p, First Loop Finish
            if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_24_AUX_AUTO_K, _BIT4) == 0x00)
            {
                // Backup First Loop Result
                ucDisplayDpTxAuxPVthBackup = SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_28_AUX_AUTO_K, 0x00);
                ucDisplayDpTxAuxNVthBackup = SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_28_AUX_AUTO_K, 0x01);

                if(ucDisplayDpTxAuxPVthBackup == 0x00)
                {
                    ucDisplayDpTxAuxNVthBackup++;
                }
                else
                {
                    ucDisplayDpTxAuxPVthBackup--;
                }

                // Change to Detect Fron p->n
                SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_24_AUX_AUTO_K, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
            }
            else
            {
                // Backup Second Loop Result
                ucDisplayDpTxAuxPVthBackup2 = SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_28_AUX_AUTO_K, 0x00);
                ucDisplayDpTxAuxNVthBackup2 = SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_28_AUX_AUTO_K, 0x01);

                // Finish
                enumDisplayDpTxAuxAutoKState = _AUTO_CALIBRATION_DONE;
            }
        }

        // Disable auto calibration
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_24_AUX_AUTO_K, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), 0x00);

        // Clear auto_k_done & Fail
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_24_AUX_AUTO_K, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));

        ucAutoCalibrationCount++;
    }

    if(enumDisplayDpTxAuxAutoKState == _AUTO_CALIBRATION_DONE)
    {
        g_pucDisplayDpTxXAuxPVth[GET_DISPLAY_DP_TX_PORT()] = (ucDisplayDpTxAuxPVthBackup + ucDisplayDpTxAuxPVthBackup2) / 2 + _DP_AUX_AUTO_CALIBRATION_VTH;
        g_pucDisplayDpTxXAuxNVth[GET_DISPLAY_DP_TX_PORT()] = (ucDisplayDpTxAuxNVthBackup + ucDisplayDpTxAuxNVthBackup2) / 2;
    }
    else
    {
        g_pucDisplayDpTxXAuxPVth[GET_DISPLAY_DP_TX_PORT()] = _DP_AUX_AUTO_CALIBRATION_VTH;
        g_pucDisplayDpTxXAuxNVth[GET_DISPLAY_DP_TX_PORT()] = 0;
    }

#if(_HW_DP_AUX_AUTO_CALIBRATION_ORIENTATION == _DP_AUX_AUTO_CALIBRATION_PN_INVERSE)
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58000_18_AUX_6, ~_BIT6, 0x00);
#endif
}
#endif

//--------------------------------------------------
// Description  : DP Tx Aux Read
// Input Value  : ucCommand --> Aux Read Command
//                ucHighAddress --> High Byte of  Aux Read Address
//                ucMidAddress --> Middle Byte of  Aux Read Address
//                ucLowAddress --> Low Byte of  Aux Read Address
//                ucLength --> Aux Read Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of Aux Read
// Output Value : TRUE --> Aux Read Sucessful
//--------------------------------------------------
bit ScalerDisplayDpTxXAuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    bit bReceiveFlag = _FALSE;
    BYTE ucAuxPollingCount = 0;
    BYTE ucDataCount = 0;
    BYTE ucReadRetryNum = 0;
    BYTE ucResidualReceiveTimes = 16;
    BYTE ucCheckLength = 0;
    DWORD ulCommandAddr = TO_DWORD(0x00, ucCommandAddrH, ucAddrM, ucAddrL);

    // if aux_en = 0, return false
    if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_40_AUX_TX_CTRL, _BIT0) == 0x00)
    {
        return _FALSE;
    }

    if(((ulCommandAddr & 0xFFFFF) + ucLength) > 0x100000)
    {
        ucLength = 0x100000 - (ulCommandAddr & 0xFFFFF);
    }

    // Enable AUX FW Handle Mode & Disable Address only transaction
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT5 | _BIT0), _BIT5);

    do
    {
        ucReadRetryNum = 0;

        // Reset Retry Mechanism
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~_BIT7, 0x00);

        // Enable Retry Mechanism & Timeout HW Retry
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

        // CLR Flag
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

        // Reset AUX FIFO
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        ucLength = ucLength - ucCheckLength;

        if(ucLength == 0)
        {
            ucLength = 1;
        }
        else if(ucLength > 16)
        {
            ucLength = 16;
        }

        ulCommandAddr += ucCheckLength;

        // Setting Tx REQ Addr & TX_LEN = ucLength-1
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_50_AUXTX_REQ_CMD, ((ulCommandAddr << 8) | (ucLength - 1)));

        // Reset AUX Start Bit
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

        // Enable Aux to Start Read
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

        do
        {
            // Delay Time us [400,x] Delay 400us
            DELAY_XUS(400);

            // Delay Time us [5,175] Polling AUX Done Bit (Delay 25 Loop = 175us)
            for(ucAuxPollingCount = 0; ucAuxPollingCount < 25; ucAuxPollingCount++)
            {
                DELAY_5US();

                if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, _BIT5) == _BIT5)
                {
                    // Reply Error or Nack or Command is not ACK
                    if((SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, _BIT2) != 0x00) || (SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_58_AUX_REPLY_CMD, (_BIT5 | _BIT4)) != 0x00))
                    {
                        // CLR Flag
                        SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

                        if(ucReadRetryNum != _DISPLAY_DP_TX_AUX_RETRY_LIMIT)
                        {
                            // Reset AUX FIFO
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            // Reset AUX Start Bit
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                            // Enable Aux to Start Read
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);
                        }
                        else
                        {
                            // Disable Timeout Retry
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                            // CLR Flag
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

                            // Reset AUX FIFO
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                        }
                    }
                    else
                    {
                        ucCheckLength = SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_78_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

                        // Avoid Aux Reply too much data
                        if(ucCheckLength > ucLength)
                        {
                            ucCheckLength = ucLength;
                        }

                        // Read Data From Buffer
                        for(ucDataCount = 0; ucDataCount < ucCheckLength; ucDataCount++)
                        {
                            *pucReadArray = SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_5C_AUX_REPLY_DATA, 0x00);
                            pucReadArray++;
                        }

                        if(ucCheckLength == ucLength)
                        {
                            // Disable Timeout Retry
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                            // CLR Flag
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

                            // Reset AUX FIFO
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            return _TRUE;
                        }
                        else
                        {
                            // break loop to retry read residual data
                            bReceiveFlag = _TRUE;
                        }
                    }

                    break;
                }
                else
                {
                    // HW Retry Times Reaches RETRY_NUM
                    if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                    {
                        // Disable Timeout Retry
                        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                        // CLR Flag
                        SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        return _FALSE;
                    }
                }
            }

            // Increasing Retry Num
            ucReadRetryNum++;
        }
        while((ucReadRetryNum <= _DISPLAY_DP_TX_AUX_RETRY_LIMIT) && (SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_78_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00) && (bReceiveFlag == _FALSE));

        // clear receive flag
        bReceiveFlag = _FALSE;

        // residual times decrease
        ucResidualReceiveTimes--;
    }
    while(ucResidualReceiveTimes > 0);

    // Disable Timeout Retry
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

    // Reset AUX FIFO
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [400,x] Delay 400us
    DELAY_XUS(400);

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Aux Write
// Input Value  : ucCommand --> Aux Write Command
//                ucHighAddress --> High Byte of  Aux Write Address
//                ucMidAddress --> Middle Byte of  Aux Write Address
//                ucLowAddress --> Low Byte of  Aux Write Address
//                ucLength --> Aux Write Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of Aux Write
// Output Value : TRUE --> Aux Write Sucessful
//--------------------------------------------------
bit ScalerDisplayDpTxXAuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray)
{
    BYTE ucAuxPollingCount = 0;
    BYTE ucDataCount = 0;
    BYTE ucWriteRetryNum = 0;

    // if aux_en = 0, return false
    if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_40_AUX_TX_CTRL, _BIT0) == 0x00)
    {
        return _FALSE;
    }

    // Enable Timeout Retry
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

    // Reset FIFO
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // CLR Flag
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

    // Disable Address only transaction
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT0), 0x00);

    // Check Length
    if(ucLength == 0)
    {
        ucLength = 1;
    }
    else if(ucLength > 16)
    {
        ucLength = 16;
    }

    // Setting Tx REQ Addr & TX_LEN = ucLength-1
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_50_AUXTX_REQ_CMD, TO_DWORD(ucCommandAddrH, ucAddrM, ucAddrL, (ucLength - 1)));

    // Write Data to Buffer
    for(ucDataCount = 0; ucDataCount < ucLength; ucDataCount++)
    {
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_54_AUXTX_REQ_DATA, 0x00, pucWriteArray[ucDataCount]);
    }

    // Reset AUX Start Bit
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

    // Enable Aux to Start Write
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

    while(ucWriteRetryNum <= _DISPLAY_DP_TX_AUX_RETRY_LIMIT)
    {
        // Delay Time us [400,x] Delay 400us
        DELAY_XUS(400);

        // Delay Time us [5,175] Polling AUX Done Bit (Delay 25 Loop = 175us)
        for(ucAuxPollingCount = 0; ucAuxPollingCount < 25; ucAuxPollingCount++)
        {
            DELAY_5US();

            if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, _BIT5) == _BIT5)
            {
                // Reply Error or Nack or Command is not ACK
                if((SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, _BIT2) != 0x00) || (SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_58_AUX_REPLY_CMD, (_BIT5 | _BIT4)) != 0x00))
                {
                    // CLR Flag
                    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

                    if(ucWriteRetryNum != _DISPLAY_DP_TX_AUX_RETRY_LIMIT)
                    {
                        // Reset FIFO
                        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Write Data to Buffer
                        for(ucDataCount = 0; ucDataCount < ucLength; ucDataCount++)
                        {
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_54_AUXTX_REQ_DATA, 0x00, pucWriteArray[ucDataCount]);
                        }

                        // Reset AUX Start Bit
                        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                        // Enable Aux to Start Write
                        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);
                    }

                    break;
                }
                else
                {
                    // Disable Timeout Retry
                    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // CLR Flag
                    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    return _TRUE;
                }
            }
            else
            {
                // HW Retry Times Reaches RETRY_NUM
                if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                {
                    // Disable Timeout Retry
                    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // CLR Flag
                    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    return _FALSE;
                }
            }
        }

        // Increasing Retry Num
        ucWriteRetryNum += 1;
    }

    // Disable Timeout Retry
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

    // Reset FIFO
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [400,x] Delay 400us
    DELAY_XUS(400);

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Hpd Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxXMacInitial(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    EnumDisplayDpMacSel enumDisplayDpMacSel = ScalerDisplayDpTxGetMacSwitch(enumDisplayDpTxOutputPort);

    if(enumDisplayDpMacSel == _DISPLAY_DP_TX_NO_MAC)
    {
        return;
    }

    // Set HPD 0.5ms Timer to 0.25ms
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_CC_HPD_TIMER1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_D0_HPD_TIMER2, 0x00, 0xA5);

    // Set HPD 1ms Timer to 2ms
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_CC_HPD_TIMER1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_D4_HPD_TIMER3, 0x00, 0x2C);

#if(_PANEL_DPTX_HPD_DETECT == _ON)
#if(_PANEL_DPTX_HPD_UNPLUG_TIME == _DPTX_HPD_TIME_2_MS)
    // Set HPD 10ms Timer to 2ms
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_E0_HPD_TIMER6, 0x00, 0x0D);
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_E4_HPD_TIMER7, 0x00, 0x2C);
#else
    // Set HPD 10ms Timer to 30ms
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_E0_HPD_TIMER6, 0x00, 0xC5);
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_E4_HPD_TIMER7, 0x00, 0xBD);
#endif
#endif

    // Enable HPD Detection
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C0_HPD_CTRL, ~_BIT7, 0x00);
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C0_HPD_CTRL, ~_BIT7, _BIT7);

    // Clear HPD IRQ Flag
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C4_HPD_IRQ, 0x00, 0xFE);

#if((_PANEL_DPTX_HPD_DETECT == _ON) && (_PANEL_DPTX_IRQ_HPD_DETECT == _ON))
#if(_PANEL_DPTX_SET_HPD_DETECT_SEQUENCE == _HPD_DETECT_AFTER_PANEL_HPD_T2_TIME)
    CLR_DISPLAY_DP_TXX_IRQ_HPD_DETECTED(enumDisplayDpTxOutputPort);

    // Enable IRQ HPD Int, Disable Long HPD Int
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C8_HPD_IRQ_EN, ~(_BIT6 | _BIT5), _BIT6);
#endif
#else
    // Disable Short IRQ and Disable Long IRQ
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C8_HPD_IRQ_EN, 0x00, 0x00);
#endif

    // d2a fifo Read Start Point Depth Position, Set 0 fifo water level be in the middle
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_5C_EDPTX0_SFIFO_CTRL2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Enable DPTX0 Small FIFO ouput 10bits data for each lane of Analog PHY driver ciruit.
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_58_EDPTX0_SFIFO_CTRL1, ~_BIT7, _BIT7);

    // Enable Arbiter Stuffing and Framing
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_68_ARBITER_CTRL, ~(_BIT5 | _BIT0), _BIT0);

    SET_DISPLAY_DP_TXX_INPUT_COLOR_DEPTH(enumDisplayDpMacSel, _PANEL_DISP_BIT_MODE);
    SET_DISPLAY_DP_TXX_INPUT_COLOR_SPACE(enumDisplayDpMacSel, _COLOR_SPACE_RGB);

    SET_DISPLAY_DP_TXX_MAX_LINK_RATE(enumDisplayDpTxOutputPort, _PANEL_DPTX_LINK_RATE);

    if(_PANEL_DPTX_LANE_NUMBER >= _PANEL_DPTX_LANE_NUMBER_4)
    {
        SET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort, _DP_FOUR_LANE);
    }
    else if(_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_2)
    {
        SET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort, _DP_TWO_LANE);
    }
    else
    {
        SET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort, _DP_ONE_LANE);
    }

#if(_PANEL_DPTX_HPD_DETECT == _ON)
    SET_DISPLAY_DP_TXX_STREAM_OUTPUT(enumDisplayDpTxOutputPort, _DISABLE);
    CLR_DISPLAY_DP_TXX_FORCE_TO_LT(enumDisplayDpTxOutputPort);
#endif

    // Lane Skew Enable
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_34_DPTX_PHY_CTRL, ~_BIT2, _BIT2);
}

#if(_PANEL_DPTX_HPD_DETECT == _ON)
//--------------------------------------------------
// Description  : Display DP Tx Stable Detection
// Input Value  : EnumDisplayDpTxOutputPort
// Output Value : None
//--------------------------------------------------
bit ScalerDisplayDpTxXStableDetectCheck(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
#if(_PANEL_DPTX_SET_HPD_DETECT_SEQUENCE == _HPD_DETECT_AFTER_VIDEO_STREAM)
    if(GET_DISPLAY_DP_TXX_STREAM_OUTPUT(enumDisplayDpTxOutputPort) != _ENABLE)
    {
        return _TRUE;
    }
#endif

    if(ScalerDisplayDpTxXHpdDetect(enumDisplayDpTxOutputPort) == _TRUE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Display DP Tx HPD Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDisplayDpTxXHpdDetect(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Determine Current HPD Event Status
    // Current HPD Level HIGH
    if((SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C0_HPD_CTRL, _BIT2) >> 2) == _HIGH)
    {
        // Long HPD
        if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C4_HPD_IRQ, _BIT2) == _BIT2)
        {
            // Clr All flag
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C4_HPD_IRQ, 0x00, 0xFE);

            SET_DISPLAY_DP_TXX_FORCE_TO_LT(enumDisplayDpTxOutputPort);

            return _TRUE;
        }

#if(_PANEL_DPTX_IRQ_HPD_DETECT == _ON)
        // IRQ HPD
        if(GET_DISPLAY_DP_TXX_IRQ_HPD_DETECTED(enumDisplayDpTxOutputPort) == _TRUE)
        {
            CLR_DISPLAY_DP_TXX_IRQ_HPD_DETECTED(enumDisplayDpTxOutputPort);

            SET_DISPLAY_DP_TXX_FORCE_TO_LT(enumDisplayDpTxOutputPort);

            return _TRUE;
        }
#endif
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Dp Tx Main Link Power on
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXSignalInitialSetting(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Set Tx Lane & PN Swap
    ScalerDisplayDpTxXSetLaneAndPNSwap(enumDisplayDpTxOutputPort);

    // Set Voltage Swing and pre-emphasis level 0
    ScalerDisplayDpTxXSignalReset(enumDisplayDpTxOutputPort);

    // Initial bist mode
    ScalerDisplayDpTxXSetTpsPattern(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_OUTPUT_TPS1);

    // Disable scrambling
    ScalerDisplayDpTxXSetScrambleSeed(_DISABLE, _DISPLAY_DP_TX_SCRAMBLE_SEED_NONE);

    // Set Mac Lane Output Enable
    ScalerDisplayDpTxXSetLaneOutputEnable(enumDisplayDpTxOutputPort);

    // Set APHY Output Enable
    ScalerDisplayDpTxXSetAphyOutputEnable(enumDisplayDpTxOutputPort);
}

//--------------------------------------------------
// Description  : Set TP2 Pattern Type
// Input Value  : None
// Output Value : _DISPLAY_DP_TX_TPS_2 or _DISPLAY_DP_TX_TPS_3
//--------------------------------------------------
EnumDisplayDPTxTrainPattern ScalerDisplayDpTxXSetTp2PatternType(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // Check TP4 Supported
    if(GET_DISPLAY_DP_TXX_TP4_SUPPORT(enumDisplayDpTxOutputPort) == _TRUE)
    {
        // Main Link Switch to TPS4 Pattern
        ScalerDisplayDpTxXSetTpsPattern(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_OUTPUT_TPS4);

        return _DISPLAY_DP_TX_TPS_4;
    }
    else if(GET_DISPLAY_DP_TXX_TP3_SUPPORT(enumDisplayDpTxOutputPort) == _TRUE)
    {
        // Main Link Switch to TPS3 Pattern
        ScalerDisplayDpTxXSetTpsPattern(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_OUTPUT_TPS3);

        return _DISPLAY_DP_TX_TPS_3;
    }
    else
    {
        // Main Link Switch to TPS2 Pattern
        ScalerDisplayDpTxXSetTpsPattern(enumDisplayDpTxOutputPort, _DISPLAY_DP_TX_OUTPUT_TPS2);

        return _DISPLAY_DP_TX_TPS_2;
    }
}

//--------------------------------------------------
// Description  : Handle Tx Cts FIFO Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxXCtsFifoReset(void)
{
    // DPTx CTS Fifo reset
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_84_DPTX_CTSFIFO_CTRL, ~(_BIT2 | _BIT0), _BIT2);
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_84_DPTX_CTSFIFO_CTRL, ~(_BIT2 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : DPTX LT Training Pattern End Sequence
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxXTraininPatternEndSequence(void)
{
    // Write TRAINING_PATTERN_SET = 00
    pData[0] = _DISPLAY_DP_TX_TPS_NONE;

    ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x01, 0x02, 1, pData);
}

//--------------------------------------------------
// Description  : Set Display Dp Tx Vendor Aux Write
// Input Value  : None
// Output Value : None SPECIFIC 004F1H
//--------------------------------------------------
void ScalerDisplayDpTxXVendorSpecific004F1hAuxWrite(void)
{
    pData[0] = 0x01;

    ScalerDisplayDpTxXNativeAuxWrite(0x00, 0x04, 0xF1, 1, pData);
}

//--------------------------------------------------
// Description  : Set Display Dp Tx PN & Lane Swap
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxXSetLaneAndPNSwap(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    BYTE ucDpTxXLanePNSwap = 0;
    BYTE ucDpTxXLaneSwap = 0;

    switch(enumDisplayDpTxOutputPort)
    {
        case _DISPLAY_DP_TX_PORT_0:

            if(GET_PANEL_DPTX_PORT_0_LANE_PN_SWAP() == _ENABLE)
            {
                ucDpTxXLanePNSwap = (_BIT3 | _BIT2 | _BIT1 | _BIT0);
            }
            else
            {
                ucDpTxXLanePNSwap = 0x00;
            }

            if(GET_PANEL_DPTX_PORT_0_LANE_SWAP() == _ENABLE)
            {
                if(GET_DISPLAY_DP_TXX_LANE_NUM(_DISPLAY_DP_TX_PORT_0) == _DP_TWO_LANE)
                {
                    // lane 0 1 2 3--> 1 0 1 0
                    ucDpTxXLaneSwap = 0x44;
                }
                else
                {
                    // lane 0 1 2 3--> 3 2 1 0
                    ucDpTxXLaneSwap = 0xE4;
                }
            }
            else
            {
                // lane 0 1 2 3--> 0 1 2 3
                ucDpTxXLaneSwap = 0x1B;
            }

            break;

        case _DISPLAY_DP_TX_PORT_1:

            if(GET_PANEL_DPTX_PORT_1_LANE_PN_SWAP() == _ENABLE)
            {
                ucDpTxXLanePNSwap = (_BIT3 | _BIT2 | _BIT1 | _BIT0);
            }
            else
            {
                ucDpTxXLanePNSwap = 0x00;
            }

            if(GET_PANEL_DPTX_PORT_1_LANE_SWAP() == _ENABLE)
            {
                if(GET_DISPLAY_DP_TXX_LANE_NUM(_DISPLAY_DP_TX_PORT_1) == _DP_TWO_LANE)
                {
                    // lane 0 1 2 3--> 1 0 1 0
                    ucDpTxXLaneSwap = 0x44;
                }
                else
                {
                    // lane 0 1 2 3 --> 3 2 1 0
                    ucDpTxXLaneSwap = 0xE4;
                }
            }
            else
            {
                // lane 0 1 2 3 --> 0 1 2 3
                ucDpTxXLaneSwap = 0x1B;
            }

            break;

        case _DISPLAY_DP_TX_PORT_2:

            if(GET_PANEL_DPTX_PORT_2_LANE_PN_SWAP() == _ENABLE)
            {
                ucDpTxXLanePNSwap = (_BIT3 | _BIT2 | _BIT1 | _BIT0);
            }
            else
            {
                ucDpTxXLanePNSwap = 0x00;
            }

            if(GET_PANEL_DPTX_PORT_2_LANE_SWAP() == _ENABLE)
            {
                if(GET_DISPLAY_DP_TXX_LANE_NUM(_DISPLAY_DP_TX_PORT_2) == _DP_TWO_LANE)
                {
                    // lane 0 1 2 3--> 1 0 1 0
                    ucDpTxXLaneSwap = 0x44;
                }
                else
                {
                    // lane 0 1 2 3--> 3 2 1 0
                    ucDpTxXLaneSwap = 0xE4;
                }
            }
            else
            {
                // lane 0 1 2 3 --> 0 1 2 3
                ucDpTxXLaneSwap = 0x1B;
            }

            break;

        case _DISPLAY_DP_TX_PORT_3:

            if(GET_PANEL_DPTX_PORT_3_LANE_PN_SWAP() == _ENABLE)
            {
                ucDpTxXLanePNSwap = (_BIT3 | _BIT2 | _BIT1 | _BIT0);
            }
            else
            {
                ucDpTxXLanePNSwap = 0x00;
            }

            if(GET_PANEL_DPTX_PORT_3_LANE_SWAP() == _ENABLE)
            {
                if(GET_DISPLAY_DP_TXX_LANE_NUM(_DISPLAY_DP_TX_PORT_3) == _DP_TWO_LANE)
                {
                    // lane 0 1 2 3--> 1 0 1 0
                    ucDpTxXLaneSwap = 0x44;
                }
                else
                {
                    // lane 0 1 2 3 --> 3 2 1 0
                    ucDpTxXLaneSwap = 0xE4;
                }
            }
            else
            {
                // lane 0 1 2 3 --> 0 1 2 3
                ucDpTxXLaneSwap = 0x1B;
            }

            break;

        default:

            ucDpTxXLanePNSwap = 0x00;
            ucDpTxXLaneSwap = 0x1B;

            break;
    }

    // Set DP TX Port PN Swap
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_54_EDPTX0_SFIFO_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucDpTxXLanePNSwap);

    // Set Lane Swap
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_38_DPTX_LANE_SWAP, 0x00, ucDpTxXLaneSwap);
}
//--------------------------------------------------
// Description  : Set Display Dp Tx Mac Lane Output Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxXSetLaneOutputEnable(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    switch(GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort))
    {
        case _DP_ONE_LANE:

            // Set Mac 1 Lane
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_00_DP_MAC_CTRL, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT6 | _BIT0));

            // Dig PHY Set
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_00_DP_PHY_CTRL, ~(_BIT3 | _BIT2), _BIT2);

            // Reset Small FIFO Before Output Enable
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_58_EDPTX0_SFIFO_CTRL1, ~_BIT7, 0x00);
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_58_EDPTX0_SFIFO_CTRL1, ~_BIT7, _BIT7);

            break;

        case _DP_TWO_LANE:

            // Set Mac 2 Lane
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_00_DP_MAC_CTRL, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT7 | _BIT1));

            // Dig PHY Set
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_00_DP_PHY_CTRL, ~(_BIT3 | _BIT2), _BIT3);

            // Reset Small FIFO Before Output Enable
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_58_EDPTX0_SFIFO_CTRL1, ~_BIT7, 0x00);
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_58_EDPTX0_SFIFO_CTRL1, ~_BIT7, _BIT7);

            break;

        case _DP_FOUR_LANE:

#if(_HW_DISPLAY_DPTX_MULTI_SST_OPERATION == _ON)
            // Set MSO 4 lane / Mac 4 Lane
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_00_DP_MAC_CTRL, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
#else
            // Set Mac 4 Lane
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58010_00_DP_MAC_CTRL, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT1 | _BIT0));
#endif

            // Dig PHY Set
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_00_DP_PHY_CTRL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // Reset Small FIFO Before Output Enable
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_58_EDPTX0_SFIFO_CTRL1, ~_BIT7, 0x00);
            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(GET_DISPLAY_DP_TX_MAC_OFFSET(), PB58020_58_EDPTX0_SFIFO_CTRL1, ~_BIT7, _BIT7);

            break;

        default:
            break;
    }
}
#endif // End of #if(_DISPLAY_DP_TXX_SUPPORT == _ON)
