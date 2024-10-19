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
// ID Code      : RL6952_Series_DpMacTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DPTX__

#include "ScalerFunctionInclude.h"
#include "DpMacTx/ScalerDpMacTx.h"

#if(_DP_MAC_TX_SUPPORT == _ON)

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
// Description  : DP Tx Clone Output MAC Select
// Input Value  : OSD Clone Input Port Select
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxCloneOutputRxMACSelect(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
    WORD usDpTxInputPixelClk = 0;

    if(enumPortType == _PORT_DP)
    {
#if(_DP_SUPPORT == _ON)
        // Set Tx Clone Rx Port Select
        ScalerDpMacRxSetTxCloneRxPortSel(enumInputPort);

        // Select DPTX Source from DPRX Mac
        ScalerSetBit(P6F_04_MUX_DPRX_OUT, ~(_BIT7 | _BIT6), (ScalerDpRxGetMacSwitch(enumInputPort)) << 6);
#endif // End of #if(_DP_SUPPORT == _ON)

        // RS decode clk sel to DP Rx Link clk
        ScalerSetBit(PA_03_MST2SST_CLK_GATE, ~_BIT7, 0x00);

        // Reset Daisy Chain Async-fifo
        ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, _BIT6);
        ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, 0x00);
    }
    else
    {
        // RS decode clk sel to GDI clk
        ScalerSetBit(PA_03_MST2SST_CLK_GATE, ~_BIT7, _BIT7);
    }

    // Set Format Conversion for DP Tx Input
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

        case _D0_INPUT_PORT:

            usDpTxInputPixelClk = GET_D0_INPUT_PIXEL_CLK();

#if(_D0_DP_SUPPORT == _ON)
            switch(ScalerDpRxGetMacSwitch(_D0_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    // Set source index to D0
                    ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_MAC_D0 << 4));

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                    // Set Audio Input Port for DP Tx
                    ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX0_PORT);
#endif

                    DebugMessageMst("DPTX clone Rx0", 0);
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    // Set source index to D1
                    ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_MAC_D1 << 4));

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                    // Set Audio Input Port for DP Tx
                    ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX1_PORT);
#endif

                    DebugMessageMst("DPTX clone Rx1", 0);
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    // Set source index to D2
                    ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_MAC_D2 << 4));

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                    // Set Audio Input Port for DP Tx
                    ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX2_PORT);
#endif

                    DebugMessageMst("DPTX clone Rx2", 0);
                    break;
#endif

                default:
                    break;
            }
#endif

            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

            usDpTxInputPixelClk = GET_D1_INPUT_PIXEL_CLK();

#if(_D1_DP_SUPPORT == _ON)
            switch(ScalerDpRxGetMacSwitch(_D1_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    // Set source index to D0
                    ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_MAC_D0 << 4));

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                    // Set Audio Input Port for DP Tx
                    ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX0_PORT);
#endif

                    DebugMessageMst("DPTX clone Rx0", 0);
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    // Set source index to D1
                    ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_MAC_D1 << 4));

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                    // Set Audio Input Port for DP Tx
                    ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX1_PORT);
#endif

                    DebugMessageMst("DPTX clone Rx1", 0);
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    // Set source index to D2
                    ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_MAC_D2 << 4));

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                    // Set Audio Input Port for DP Tx
                    ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX2_PORT);
#endif

                    DebugMessageMst("DPTX clone Rx2", 0);
                    break;
#endif

                default:
                    break;
            }
#endif

            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

            usDpTxInputPixelClk = GET_D2_INPUT_PIXEL_CLK();

#if(_D2_DP_SUPPORT == _ON)
            switch(ScalerDpRxGetMacSwitch(_D2_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    // Set source index to D0
                    ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_MAC_D0 << 4));

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                    // Set Audio Input Port for DP Tx
                    ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX0_PORT);
#endif

                    DebugMessageMst("DPTX clone Rx0", 0);
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    // Set source index to D1
                    ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_MAC_D1 << 4));

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                    // Set Audio Input Port for DP Tx
                    ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX1_PORT);
#endif

                    DebugMessageMst("DPTX clone Rx1", 0);
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    // Set source index to D2
                    ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_MAC_D2 << 4));

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                    // Set Audio Input Port for DP Tx
                    ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX2_PORT);
#endif

                    DebugMessageMst("DPTX clone Rx2", 0);
                    break;
#endif

                default:
                    break;
            }
#endif

            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

            usDpTxInputPixelClk = GET_D3_INPUT_PIXEL_CLK();

            // Set source index to D3
            ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_MAC_D3 << 4));

            DebugMessageMst("DPTX clone Rx3", 0);

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
            // Set Audio Input Port for DP Tx
            ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX3_PORT);
#endif
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

            usDpTxInputPixelClk = GET_D4_INPUT_PIXEL_CLK();

            // Set source index to D4
            ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DPTX_OUTPUT_MAC_D4 << 4));

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
            // Set Audio Input Port for DP Tx
            ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_RX4_PORT);
#endif
            DebugMessageMst("DPTX clone Rx4", 0);

            break;
#endif

        default:
            break;
    }

    if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        usDpTxInputPixelClk *= 2;
    }

    // Set Dp Tx Pixel Clk
    SET_DP_TX_INPUT_PIXEL_CLK(usDpTxInputPixelClk);

#if(_DSC_DECODER_SUPPORT == _ON)
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    if(GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH() == _DISABLE)
#endif
    {
        switch(ScalerDscDecoderDxInputPortGetDscDecoderMac(enumInputPort))
        {
            case _DSC_MAC_0:

                // Format Conversion Select DSC MAC0 to Clone
                ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((_DPTX_OUTPUT_DSC0) << 4));

                DebugMessageMst("DPTX clone DSC MAC0: VESA", 0);
                break;

            case _DSC_MAC_1:

                // Format Conversion Select DSC MAC1 to Clone
                ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((_DPTX_OUTPUT_DSC1) << 4));

                DebugMessageMst("DPTX clone DSC MAC1: VESA", 0);
                break;

            default:
                break;
        }
    }
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        // Disable DP Tx FC 1 to 2 Mux
        ScalerSetBit(P31_83_FC_8KFB_CTRL0, ~_BIT0, 0x00);
    }
    else
#endif
    {
        // Check Rx Input Pixel mode
        if(ScalerDpMacTxGetInputPixelMode(enumInputPort) == _DP_TX_1_PIXEL_MODE)
        {
            // Enable DP Tx FC 1 to 2 Mux
            ScalerSetBit(P31_83_FC_8KFB_CTRL0, ~_BIT0, _BIT0);
        }
        else
        {
            // Disable DP Tx FC 1 to 2 Mux
            ScalerSetBit(P31_83_FC_8KFB_CTRL0, ~_BIT0, 0x00);
        }
    }

#if(_AUDIO_SUPPORT == _ON)
    // Set DPTX audio input path to I2S when in clone mode
    SET_DP_TX_AUDIO_INPUT_PATH(_DP_TX_AUDIO_PATH_I2S);
#endif
}

//--------------------------------------------------
// Description  : DP Tx Clone Output Process
// Input Value  : Input Port Type to be Cloned
// Output Value : None
//--------------------------------------------------
EnumInputPort ScalerDpMacTxCloneGetCurrentInputPort(void)
{
    switch(ScalerGetBit(P31_02_FC_INPUT_DPTX_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4)
    {
#if(_DP_SUPPORT == _ON)
        case _DPTX_OUTPUT_MAC_D0:
#if(_DP_MAC_RX0_SUPPORT == _ON)
            return ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0);
#endif
            break;

        case _DPTX_OUTPUT_MAC_D1:
#if(_DP_MAC_RX1_SUPPORT == _ON)
            return ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
#endif
            break;

        case _DPTX_OUTPUT_MAC_D2:
#if(_DP_MAC_RX2_SUPPORT == _ON)
            return ScalerDpRxMacGetInputPortSwitch(_DP_MAC_2);
#endif
            break;
#endif

        case _DPTX_OUTPUT_MAC_D3:

            return _D3_INPUT_PORT;

        case _DPTX_OUTPUT_MAC_D4:

            return _D4_INPUT_PORT;

        case _DPTX_OUTPUT_DSC0:
#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
            return ScalerDscDecoderGetDxInputPort(_DSC_MAC_0);
#endif
            break;

        case _DPTX_OUTPUT_DSC1:
#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
            return ScalerDscDecoderGetDxInputPort(_DSC_MAC_1);
#endif
            break;

        default:
            break;
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : Get Tx Get Link Bw
// Input Value  : None
// Output Value : WORD
//--------------------------------------------------
EnumDpTxPixelMode ScalerDpMacTxGetInputPixelMode(EnumInputPort enumDpTxInputPort)
{
    EnumDPTxOutputSelMacFrom enumTxSourceType = _DPTX_OUTPUT_NONE;

    // Get Tx input Select form Fc Tx Mux
    enumTxSourceType = ScalerGetBit(P31_02_FC_INPUT_DPTX_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4;

    switch(enumTxSourceType)
    {
#if(_DP_SUPPORT == _ON)
        case _DPTX_OUTPUT_MAC_D0:
        case _DPTX_OUTPUT_MAC_D1:
        case _DPTX_OUTPUT_MAC_D2:
            switch(ScalerDpMacStreamRxInputPixelMode(enumDpTxInputPort))
            {
                case _DP_RX_MAC_FOUR_PIXEL_MODE:
                    return _DP_TX_4_PIXEL_MODE;
                case _DP_RX_MAC_TWO_PIXEL_MODE:
                    return _DP_TX_2_PIXEL_MODE;
                default:
                    return _DP_TX_1_PIXEL_MODE;
                    break;
            }
            break;
#endif

#if(_DSC_DECODER_SUPPORT == _ON)
        case _DPTX_OUTPUT_DSC0:
            switch(ScalerDscDecoderGetPixelMode(_DSC_MAC_0))
            {
                default:
                case 0x00:
                    break;
                case _BIT0:
                    return _DP_TX_2_PIXEL_MODE;
                case _BIT1:
                case (_BIT1 | _BIT0):
                    return _DP_TX_4_PIXEL_MODE;
            }
            break;

        case _DPTX_OUTPUT_DSC1:
            switch(ScalerDscDecoderGetPixelMode(_DSC_MAC_1))
            {
                default:
                case 0x00:
                    break;
                case _BIT0:
                    return _DP_TX_2_PIXEL_MODE;
                case _BIT1:
                case (_BIT1 | _BIT0):
                    return _DP_TX_4_PIXEL_MODE;
            }
            break;

#endif

#if(_HDMI_FRL_SUPPORT == _ON)
        case _DPTX_OUTPUT_MAC_D3:
        case _DPTX_OUTPUT_MAC_D4:
            if(ScalerTmdsMacRxGetHdmiVer(enumDpTxInputPort) != _FROM_HDMI_TMDS_MAC)
            {
                switch(ScalerHdmiFrlMacRxGetDpfPixelMode(enumDpTxInputPort))
                {
                    case _HDMI_FRL_MAC_RX_DPF_FOUR_PIXEL_MODE:
                        return _DP_TX_4_PIXEL_MODE;
                    case _HDMI_FRL_MAC_RX_DPF_TWO_PIXEL_MODE:
                        return _DP_TX_2_PIXEL_MODE;
                    default:
                        break;
                }
            }
            break;
#endif

        default:
            break;
    }

    return _DP_TX_1_PIXEL_MODE;
}

//--------------------------------------------------
// Description  : Check DP Mac Tx Component New Mode Support
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacTxNewComponentModeAvailable(void)
{
    return _TRUE;
}
#endif
