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
// ID Code      : ScalerDpMacDsc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_DSC__

#include "ScalerFunctionInclude.h"
#include "DpMacDsc/ScalerDpMacDsc.h"

#if((_DP_SUPPORT == _ON) && ((_DP_RX_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Video/DisplayFormat/Measure relative Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDscStreamRxSinkStatusSetting(EnumDpMacSel enumDpMacSel)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(enumDpMacSel);

    switch(ScalerDpRxGetMacStreamSourceType(enumDpMacSel))
    {
        case _STREAM_SOURCE_D0_DP:
        case _STREAM_SOURCE_D1_DP:
        case _STREAM_SOURCE_D2_DP:

            if(ScalerDpMacStreamRxCheckNoVideoStreamIRQStatus(enumInputPort) == _DISABLE)
            {
                ScalerDpMacStreamRxSetNoVideoStreamIRQ(enumInputPort, _ENABLE);
            }

            if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x02, 0x05, _BIT0) == 0x00)
            {
                // Set DP Receive Port0 In Sync
                ScalerDpAuxRxSinkStatusSet(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_IN_SYNC);
            }

            break;

        case _STREAM_SOURCE_PXP:
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            if(ScalerDpMacStreamRxCheckNoVideoStreamIRQStatus(enumInputPort) == _DISABLE)
            {
                ScalerDpMacStreamRxSetNoVideoStreamIRQ(enumInputPort, _ENABLE);
            }
#endif
            break;

        case _STREAM_SOURCE_MST2SST:
        default:
            break;
    }

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0MacSetting();
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1MacSetting();
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2MacSetting();
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3MacSetting();
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4MacSetting();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DSC DP Fifo IRQ
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDscFifoStatusIrqProc(EnumDpMacSel enumDpMacSel, BYTE ucFifoCondition)
{
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(enumDpMacSel);
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(enumDpMacSel);
    BYTE ucDscMac = ScalerDscDecoderDpMacRxxGetDscDecoderMac(enumDpMacSel);

    switch(enumDpMacStreamSourceType)
    {
        case _STREAM_SOURCE_D0_DP:
        case _STREAM_SOURCE_D1_DP:
        case _STREAM_SOURCE_D2_DP:
        {
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_MULTI_FUNCTION_SUPPORT == _ON))
            EnumDpMstPort enumDpMstPort = ScalerDpMstRxDxPortNumMapping(enumInputPort);

            if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumDpMstPort) == _ENABLE) &&
               (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x00, 0x60, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x01, 0x60, _BIT0) == _BIT0))
            {
                if(ScalerDpMacDscChunkLengthCheck(enumDpMacSel, ScalerDscDecoderGetChunkSizeCurrent(ucDscMac), ScalerDscDecoderGetHorSliceCount(ucDscMac)) == _FALSE)
                {
                    DebugMessageDSC("V-DPCD DSC Chunk Length Error", 0);
                    ScalerDpMstRxSetVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort, _SINK_EVENT_ID_DSC_CHUNCK_LEN_ERROR);
                }

                if((ucFifoCondition & _BIT0) == _BIT0)
                {
                    DebugMessageDSC("V-DPCD DSC Underflow", 0);
                    ScalerDpMstRxSetVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort, _SINK_EVENT_ID_DSC_RC_BUF_UNDERRUN);
                }
                else if((ucFifoCondition & _BIT1) == _BIT1)
                {
                    DebugMessageDSC("V-DPCD DSC Overflow", 0);
                    ScalerDpMstRxSetVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort, _SINK_EVENT_ID_DSC_RC_BUF_OVERFLOW);
                }
            }
            else
#endif
            {
                if(ScalerDpMacDscChunkLengthCheck(enumDpMacSel, ScalerDscDecoderGetChunkSizeCurrent(ucDscMac), ScalerDscDecoderGetHorSliceCount(ucDscMac)) == _FALSE)
                {
                    DebugMessageDSC("DSC Chunk Length Error", 0);
                    ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x0F, ~_BIT2, _BIT2);
                }

                if((ucFifoCondition & _BIT0) == _BIT0)
                {
                    DebugMessageDSC("DSC Underflow", 0);
                    ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x0F, ~_BIT0, _BIT0);
                }
                else if((ucFifoCondition & _BIT1) == _BIT1)
                {
                    DebugMessageDSC("DSC Overflow", 0);
                    ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x0F, ~_BIT1, _BIT1);
                }

                if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x02, 0x0F, (_BIT2 | _BIT1 | _BIT0)) != 0x00)
                {
                    // Set the DSC_ERROR_STATUS
                    ScalerDpAuxRxSetDpcdBitWrite1ClearValue(enumInputPort, 0x00, 0x20, 0x04, ~_BIT4, _BIT4);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
                    if(ScalerTypeCPcbxTypeCxMapping(ScalerTypeCDxConvertToPcbPort(enumInputPort)) != _EMB_TYPE_C_NOT_EXIST)
                    {
                        if(ScalerDpRxGetHotPlugStatus(enumInputPort) == _HIGH)
                        {
                            ScalerTypeCPdDpCTSForceHpdIrq(enumInputPort);
                        }
                    }
                    else
#endif
                    {
                        ScalerDpAuxRxHpdIrqAssert(enumInputPort);
                    }
                }
            }

            break;
        }

        case _STREAM_SOURCE_MST2SST:
        {
#if((_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON) && (_DP_MST_MULTI_FUNCTION_SUPPORT == _ON))
            EnumDpMstPort enumDpMstPort = ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT);

            if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumDpMstPort) == _ENABLE) &&
               (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x00, 0x60, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x01, 0x60, _BIT0) == _BIT0))
            {
                if(ScalerDpMacDscChunkLengthCheck(enumDpMacSel, ScalerDscDecoderGetChunkSizeCurrent(ucDscMac), ScalerDscDecoderGetHorSliceCount(ucDscMac)) == _FALSE)
                {
                    DebugMessageDSC("MST2SST DSC Chunk Length Error", 0);
                    ScalerDpMstRxSetVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort, _SINK_EVENT_ID_DSC_CHUNCK_LEN_ERROR);
                }

                if((ucFifoCondition & _BIT0) == _BIT0)
                {
                    DebugMessageDSC("MST2SST DSC Underflow", 0);
                    ScalerDpMstRxSetVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort, _SINK_EVENT_ID_DSC_RC_BUF_UNDERRUN);
                }
                else if((ucFifoCondition & _BIT1) == _BIT1)
                {
                    DebugMessageDSC("MST2SST DSC Overflow", 0);
                    ScalerDpMstRxSetVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort, _SINK_EVENT_ID_DSC_RC_BUF_OVERFLOW);
                }
            }
#endif
            break;
        }

        case _STREAM_SOURCE_PXP:
        {
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_MULTI_FUNCTION_SUPPORT == _ON))
            EnumDpMstPort enumDpMstPort = ScalerDpMstRxDxPortNumMapping(_D9_INPUT_PORT);

            if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumDpMstPort) == _ENABLE) &&
               (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x00, 0x60, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x01, 0x60, _BIT0) == _BIT0))
            {
                if(ScalerDpMacDscChunkLengthCheck(enumDpMacSel, ScalerDscDecoderGetChunkSizeCurrent(ucDscMac), ScalerDscDecoderGetHorSliceCount(ucDscMac)) == _FALSE)
                {
                    DebugMessageDSC("V-DPCD DSC Chunk Length Error", 0);
                    ScalerDpMstRxSetVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort, _SINK_EVENT_ID_DSC_CHUNCK_LEN_ERROR);
                }

                if((ucFifoCondition & _BIT0) == _BIT0)
                {
                    DebugMessageDSC("V-DPCD DSC Underflow", 0);
                    ScalerDpMstRxSetVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort, _SINK_EVENT_ID_DSC_RC_BUF_UNDERRUN);
                }
                else if((ucFifoCondition & _BIT1) == _BIT1)
                {
                    DebugMessageDSC("V-DPCD DSC Overflow", 0);
                    ScalerDpMstRxSetVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort, _SINK_EVENT_ID_DSC_RC_BUF_OVERFLOW);
                }
            }
#endif
#endif
            break;
        }

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DSC DP Chunk Check Proccess
// Input Value  : enumInputPort
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacDscChunkCheckProc(EnumDpMacSel enumDpMacSel)
{
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(enumDpMacSel);
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(enumDpMacSel);
    BYTE ucDscMac = ScalerDscDecoderDpMacRxxGetDscDecoderMac(enumDpMacSel);

    switch(enumDpMacStreamSourceType)
    {
        case _STREAM_SOURCE_D0_DP:
        case _STREAM_SOURCE_D1_DP:
        case _STREAM_SOURCE_D2_DP:
        {
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_MULTI_FUNCTION_SUPPORT == _ON))
            EnumDpMstPort enumDpMstPort = ScalerDpMstRxDxPortNumMapping(enumInputPort);

            if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumDpMstPort) == _ENABLE) &&
               (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x00, 0x60, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x01, 0x60, _BIT0) == _BIT0))
            {
                if(ScalerDpMacDscChunkLengthCheck(enumDpMacSel, ScalerDscDecoderGetChunkSizeCurrent(ucDscMac), ScalerDscDecoderGetHorSliceCount(ucDscMac)) == _FALSE)
                {
                    DebugMessageDSC("V-DPCD DSC Chunk Length Error", 0);
                    ScalerDpMstRxSetVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort, _SINK_EVENT_ID_DSC_CHUNCK_LEN_ERROR);

                    return _FALSE;
                }
            }
            else
#endif
            {
                if(ScalerDpMacDscChunkLengthCheck(enumDpMacSel, ScalerDscDecoderGetChunkSizeCurrent(ucDscMac), ScalerDscDecoderGetHorSliceCount(ucDscMac)) == _FALSE)
                {
                    DebugMessageDSC("DSC Chunk Length Error", 0);
                    ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(enumInputPort, 0x00, 0x02, 0x0F, ~_BIT2, _BIT2);

                    // Set the DSC_ERROR_STATUS
                    ScalerDpAuxRxSetDpcdBitWrite1ClearValue(enumInputPort, 0x00, 0x20, 0x04, ~_BIT4, _BIT4);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
                    if(ScalerTypeCPcbxTypeCxMapping(ScalerTypeCDxConvertToPcbPort(enumInputPort)) != _EMB_TYPE_C_NOT_EXIST)
                    {
                        if(ScalerDpRxGetHotPlugStatus(enumInputPort) == _HIGH)
                        {
                            ScalerTypeCPdDpCTSForceHpdIrq(enumInputPort);
                        }
                    }
                    else
#endif
                    {
                        ScalerDpAuxRxHpdIrqAssert(enumInputPort);
                    }

                    return _FALSE;
                }
            }

            break;
        }

        case _STREAM_SOURCE_MST2SST:
        {
#if((_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON) && (_DP_MST_MULTI_FUNCTION_SUPPORT == _ON))
            EnumDpMstPort enumDpMstPort = ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT);

            if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumDpMstPort) == _ENABLE) &&
               (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x00, 0x60, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x01, 0x60, _BIT0) == _BIT0))
            {
                if(ScalerDpMacDscChunkLengthCheck(enumDpMacSel, ScalerDscDecoderGetChunkSizeCurrent(ucDscMac), ScalerDscDecoderGetHorSliceCount(ucDscMac)) == _FALSE)
                {
                    DebugMessageDSC("MST2SST DSC Chunk Length Error", 0);
                    ScalerDpMstRxSetVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort, _SINK_EVENT_ID_DSC_CHUNCK_LEN_ERROR);

                    return _FALSE;
                }
            }
#endif
            break;
        }

        case _STREAM_SOURCE_PXP:
        {
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_MULTI_FUNCTION_SUPPORT == _ON))
            EnumDpMstPort enumDpMstPort = ScalerDpMstRxDxPortNumMapping(_D9_INPUT_PORT);

            if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumDpMstPort) == _ENABLE) &&
               (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x00, 0x60, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x01, 0x60, _BIT0) == _BIT0))
            {
                if(ScalerDpMacDscChunkLengthCheck(enumDpMacSel, ScalerDscDecoderGetChunkSizeCurrent(ucDscMac), ScalerDscDecoderGetHorSliceCount(ucDscMac)) == _FALSE)
                {
                    DebugMessageDSC("V-DPCD DSC Chunk Length Error", 0);
                    ScalerDpMstRxSetVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort, _SINK_EVENT_ID_DSC_CHUNCK_LEN_ERROR);

                    return _FALSE;
                }
            }
#endif
#endif
            break;
        }

        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP DSC Chunk Length Check
// Input Value  : EnumDpMacSel
// Output Value : FALSE => Measure Check Fail
//--------------------------------------------------
bit ScalerDpMacDscChunkLengthCheck(EnumDpMacSel enumDpMacSel, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(enumDpMacSel);

    if((usDscPpsChunkLength == 0) || (ucDscPpsSliceCnt == 0))
    {
        return _FALSE;
    }

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
            return ScalerDpMacStreamRx0DscChunkLengthCheck(enumInputPort, usDscPpsChunkLength, ucDscPpsSliceCnt);
#endif
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
            return ScalerDpMacStreamRx1DscChunkLengthCheck(enumInputPort, usDscPpsChunkLength, ucDscPpsSliceCnt);
#endif
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
            return ScalerDpMacStreamRx2DscChunkLengthCheck(enumInputPort, usDscPpsChunkLength, ucDscPpsSliceCnt);
#endif
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
#if(_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
            return ScalerDpMacStreamRx3DscChunkLengthCheck(enumInputPort, usDscPpsChunkLength, ucDscPpsSliceCnt);
#endif
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
#if(_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
            return ScalerDpMacStreamRx4DscChunkLengthCheck(enumInputPort, usDscPpsChunkLength, ucDscPpsSliceCnt);
#endif
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Dp MSA Timing Info
// Input Value  : DP Info Structure
// Output Value : True --> Get MSA Info
//--------------------------------------------------
bit ScalerDpMacDscStreamRxGetMsaTimingInfo(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetMsaTimingInfo(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetMsaTimingInfo(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetMsaTimingInfo(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetMsaTimingInfo(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetMsaTimingInfo(pstDpInfo);

            break;
#endif
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Dp MSA Vstart Info
// Input Value  : EnumDpMacSel
// Output Value : MSA Vstart
//--------------------------------------------------
WORD ScalerDpMacDscStreamRxGetMsaVstart(EnumDpMacSel enumDpMacSel)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(enumDpMacSel);
    enumInputPort = enumInputPort;

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return TO_WORD(ScalerGetByte(P1B_1A_MSA_VST_0), ScalerGetByte(P1B_1B_MSA_VST_1));
            }
            else
#endif
            {
                return TO_WORD(ScalerGetByte(PB6_14_MSA_VST_0), ScalerGetByte(PB6_15_MSA_VST_1));
            }

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return TO_WORD(ScalerGetByte(P75_1A_MSA_VST_0), ScalerGetByte(P75_1B_MSA_VST_1));
            }
            else
#endif
            {
                return TO_WORD(ScalerGetByte(PB9_14_MSA_VST_0), ScalerGetByte(PB9_15_MSA_VST_1));
            }

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return TO_WORD(ScalerGetByte(PD4_1A_MSA_VST_0), ScalerGetByte(PD4_1B_MSA_VST_1));
            }
            else
#endif
            {
                return TO_WORD(ScalerGetByte(PC7_14_MSA_VST_0), ScalerGetByte(PC7_15_MSA_VST_1));
            }

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return TO_WORD(ScalerGetByte(PF2_1A_MSA_VST_0), ScalerGetByte(PF2_1B_MSA_VST_1));
            }
            else
#endif
            {
                return TO_WORD(ScalerGetByte(PEF_14_MSA_VST_0), ScalerGetByte(PEF_15_MSA_VST_1));
            }

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return TO_WORD(ScalerGetByte(PE1_1A_MSA_VST_0), ScalerGetByte(PE1_1B_MSA_VST_1));
            }
            else
#endif
            {
                return TO_WORD(ScalerGetByte(P35_14_MSA_VST_0), ScalerGetByte(P35_15_MSA_VST_1));
            }

            break;
#endif
        default:
            return 0;
            break;
    }
}

//--------------------------------------------------
// Description  : DP Get Video Info
// Input Value  : None
// Output Value : TRUE --> Get successfully
//--------------------------------------------------
bit ScalerDpMacDscStreamRxGetVideoInfo(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetVideoInfo();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetVideoInfo();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetVideoInfo();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetVideoInfo();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetVideoInfo();

            break;
#endif
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Set Color Info Macros
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDscStreamRxSetColorInfo(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SetColorInfo();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SetColorInfo();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SetColorInfo();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SetColorInfo();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SetColorInfo();

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Link Info from Measure Function
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacDscStreamRxGetMeasureLinkInfo(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetMeasureLinkInfo(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetMeasureLinkInfo(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetMeasureLinkInfo(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetMeasureLinkInfo(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetMeasureLinkInfo(pstDpInfo);

            break;
#endif
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Display Format Gen Info Adjust
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacDscStreamRxStreamInfoSetting(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0StreamInfoSetting(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1StreamInfoSetting(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2StreamInfoSetting(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3StreamInfoSetting(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4StreamInfoSetting(pstDpInfo);

            break;
#endif
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Timing Info Adjust
// Input Value  : enumInputPort, *pstDpInfo
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDscStreamRxTimingInfoAdjust(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0TimingInfoAdjust(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1TimingInfoAdjust(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2TimingInfoAdjust(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3TimingInfoAdjust(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4TimingInfoAdjust(pstDpInfo);

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Stream Clk PLL Setting
// Input Value  : StructDpInfo
// Output Value : True --> Stream CLK Regen. ok
//--------------------------------------------------
bit ScalerDpMacDscStreamRxStreamClkRegenerate(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0StreamClkRegenerate(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1StreamClkRegenerate(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2StreamClkRegenerate(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3StreamClkRegenerate(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4StreamClkRegenerate(pstDpInfo);

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP NF PLL Tracking Enable
// Input Value  : StructDpMacRxInfo *pstDpInfo
// Output Value : True --> Tracking Stable
//--------------------------------------------------
bit ScalerDpMacDscStreamRxTrackingSetting(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0TrackingSetting(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1TrackingSetting(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2TrackingSetting(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3TrackingSetting(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4TrackingSetting(pstDpInfo);

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set DP MAC V Height
// Input Value  : usVheight
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDscStreamRxSetVheight(EnumDpMacSel enumDpMacSel, WORD usVheight)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(enumDpMacSel);

    if(enumInputPort == _NO_INPUT_PORT)
    {
        return;
    }

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                SET_DP_MAC_STREAM_RX0_V_HEIGHT_REG_128B132B(usVheight);
            }
            else
#endif
            {
                SET_DP_MAC_STREAM_RX0_V_HEIGHT_REG_8B10B(usVheight);
            }

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                SET_DP_MAC_STREAM_RX1_V_HEIGHT_REG_128B132B(usVheight);
            }
            else
#endif
            {
                SET_DP_MAC_STREAM_RX1_V_HEIGHT_REG_8B10B(usVheight);
            }

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                SET_DP_MAC_STREAM_RX2_V_HEIGHT_REG_128B132B(usVheight);
            }
            else
#endif
            {
                SET_DP_MAC_STREAM_RX2_V_HEIGHT_REG_8B10B(usVheight);
            }

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                SET_DP_MAC_STREAM_RX3_V_HEIGHT_REG_128B132B(usVheight);
            }
            else
#endif
            {
                SET_DP_MAC_STREAM_RX3_V_HEIGHT_REG_8B10B(usVheight);
            }

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                SET_DP_MAC_STREAM_RX4_V_HEIGHT_REG_128B132B(usVheight);
            }
            else
#endif
            {
                SET_DP_MAC_STREAM_RX4_V_HEIGHT_REG_8B10B(usVheight);
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set DP MAC V Front Porch
// Input Value  : ucVfrontporch
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDscStreamRxSetVfrontPorch(EnumDpMacSel enumDpMacSel, BYTE ucVfrontporch)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(enumDpMacSel);

    if(enumInputPort == _NO_INPUT_PORT)
    {
        return;
    }

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                SET_DP_MAC_STREAM_RX0_VFRONT_PORCH_REG_128B132B(ucVfrontporch);
            }
            else
#endif
            {
                SET_DP_MAC_STREAM_RX0_VFRONT_PORCH_REG_8B10B(ucVfrontporch);
            }

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                SET_DP_MAC_STREAM_RX1_VFRONT_PORCH_REG_128B132B(ucVfrontporch);
            }
            else
#endif
            {
                SET_DP_MAC_STREAM_RX1_VFRONT_PORCH_REG_8B10B(ucVfrontporch);
            }

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                SET_DP_MAC_STREAM_RX2_VFRONT_PORCH_REG_128B132B(ucVfrontporch);
            }
            else
#endif
            {
                SET_DP_MAC_STREAM_RX2_VFRONT_PORCH_REG_8B10B(ucVfrontporch);
            }

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                SET_DP_MAC_STREAM_RX3_VFRONT_PORCH_REG_128B132B(ucVfrontporch);
            }
            else
#endif
            {
                SET_DP_MAC_STREAM_RX3_VFRONT_PORCH_REG_8B10B(ucVfrontporch);
            }

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                SET_DP_MAC_STREAM_RX4_VFRONT_PORCH_REG_128B132B(ucVfrontporch);
            }
            else
#endif
            {
                SET_DP_MAC_STREAM_RX4_VFRONT_PORCH_REG_8B10B(ucVfrontporch);
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check Dp Interlace by VBID or Measure
// Input Value  : None
// Output Value : True --> Interlace
//--------------------------------------------------
bit ScalerDpMacDscStreamRxInterlaceCheck(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0InterlaceCheck(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1InterlaceCheck(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2InterlaceCheck(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3InterlaceCheck(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4InterlaceCheck(pstDpInfo);

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP DSC Flag Status
// Input Value  : None
// Output Value : None
//------------------------------------------------
bit ScalerDpMacDscGetDscFlagStatus(EnumDpMacSel enumDpMacSel)
{
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(enumDpMacSel);

    return ScalerDpMacStreamRxDscGetFlagStatus(enumDpMacStreamSourceType);
}

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable DP audio FSM
// Input Value  : Enable or Disable, Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDscAudioRxDisableSetting_EXINT0(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
    {
#if(_DP_AUDIO_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpAudioRx0DisableSetting_EXINT0();

            break;
#endif

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpAudioRx1DisableSetting_EXINT0();

            break;
#endif

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpAudioRx2DisableSetting_EXINT0();

            break;
#endif

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpAudioRx3DisableSetting_EXINT0();

            break;
#endif

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpAudioRx4DisableSetting_EXINT0();

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Enable DP audio FSM
// Input Value  : Enable or Disable, Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDscAudioEnable_EXINT0(EnumDpMacSel enumDpMacSel, bit bEnable)
{
#if((_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))
    // Check Whether Audio Pattern Gen is Enable
    if((bEnable == _DISABLE) && (GET_AUDIO_INTERNAL_GEN_ENABLE_STATE() == _ON))
    {
        return;
    }
#endif // End of #if((_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))

    switch(enumDpMacSel)
    {
#if(_DP_AUDIO_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpAudioRx0AudioEnableControl_EXINT0(bEnable);

            break;
#endif

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpAudioRx1AudioEnableControl_EXINT0(bEnable);

            break;
#endif

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpAudioRx2AudioEnableControl_EXINT0(bEnable);

            break;
#endif

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpAudioRx3AudioEnableControl_EXINT0(bEnable);

            break;
#endif

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpAudioRx4AudioEnableControl_EXINT0(bEnable);

            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get DP Link Info from Measure Function
// Input Value  : enumInputPort
// Output Value : EnumDDomainRegion
//--------------------------------------------------
EnumDDomainRegion ScalerDpMacDscStreamRxGetForceBackgroundPath_EXINT0(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_FORCE_BCKGRD_PATH();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_FORCE_BCKGRD_PATH();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_FORCE_BCKGRD_PATH();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_FORCE_BCKGRD_PATH();

            break;
#endif

        default:
            break;
    }

    return _DDOMAIN_RGN_NONE;
}
//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDscStreamRxSetNoVideoStreamIRQ_EXINT0(EnumDpMacSel enumDpMacSel, bit bEnable)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            ScalerDpMacStreamRx0SetNoVideoStreamIRQ_EXINT0(bEnable);
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            ScalerDpMacStreamRx1SetNoVideoStreamIRQ_EXINT0(bEnable);
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            ScalerDpMacStreamRx2SetNoVideoStreamIRQ_EXINT0(bEnable);
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            ScalerDpMacStreamRx3SetNoVideoStreamIRQ_EXINT0(bEnable);
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
            ScalerDpMacStreamRx4SetNoVideoStreamIRQ_EXINT0(bEnable);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Sync Dsc Decoder Color Info
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDscSyncDscColorInfo(EnumDpMacSel enumDpMacSel, EnumColorSpace enumColorSpace, BYTE ucColorDepth)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(enumDpMacSel);

    switch(ScalerDpRxGetMacStreamSourceType(enumDpMacSel))
    {
        case _STREAM_SOURCE_D0_DP:
        case _STREAM_SOURCE_D1_DP:
        case _STREAM_SOURCE_D2_DP:
        case _STREAM_SOURCE_PXP:

            if(enumInputPort == _NO_INPUT_PORT)
            {
                return;
            }

            if(GET_COLOR_SPACE(enumInputPort) != enumColorSpace)
            {
                DebugMessageDpRx("DSC & DP Color Space Mismatch!!!", enumColorSpace);
            }

            SET_COLOR_SPACE(enumInputPort, enumColorSpace);
            SET_COLOR_DEPTH(enumInputPort, ucColorDepth);
            break;

        case _STREAM_SOURCE_MST2SST:

#if(_DP_MAC_TX_SUPPORT == _ON)
            SET_DP_TX_INPUT_COLOR_SPACE(enumColorSpace);
            SET_DP_TX_INPUT_COLOR_DEPTH(ucColorDepth);
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Set Color Info Macros
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMacDscStreamRxGetQuantizationPreValue(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
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

    return _DP_COLOR_QUANTIZATION_LIMIT;
}

//--------------------------------------------------
// Description  : Set Dp Input Pixel Clk According to DSC Decoder
// Input Value  : enumDpMacSel, stream Clk
// Output Value : bit
//--------------------------------------------------
void ScalerDpMacDscSetInputPixelClk(EnumDpMacSel enumDpMacSel, DWORD ulStreamClk)
{
    switch(ScalerDpRxGetMacStreamSourceType(enumDpMacSel))
    {
        case _STREAM_SOURCE_D0_DP:
        case _STREAM_SOURCE_D1_DP:
        case _STREAM_SOURCE_D2_DP:
        case _STREAM_SOURCE_PXP:

            ScalerDpRxSetInputPixelClock(ScalerDpRxMacGetInputPortSwitch(enumDpMacSel), ulStreamClk);
            break;

        case _STREAM_SOURCE_MST2SST:
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set Native Pixel Clk According to DSC Decoder
// Input Value  : enumDpMacSel, stream Clk
// Output Value : bit
//--------------------------------------------------
bit ScalerDpMacDscSetNativeInputPixelClkCheck(EnumDpMacSel enumDpMacSel)
{
    switch(ScalerDpRxGetMacStreamSourceType(enumDpMacSel))
    {
        case _STREAM_SOURCE_D0_DP:
        case _STREAM_SOURCE_D1_DP:
        case _STREAM_SOURCE_D2_DP:
        case _STREAM_SOURCE_PXP:

            return _TRUE;

        case _STREAM_SOURCE_MST2SST:

            return _FALSE;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DSC Get Change Status
// Input Value  : enumDpMacStreamSourceType
// Output Value : bit
//--------------------------------------------------
bit ScalerDpMacDscRxDscStreamGetChange(EnumDpMacSel enumDpMacSel)
{
    return ScalerDscDecoderGetChange(ScalerDscDecoderDpMacRxxDscMacStreamSourceMapping(enumDpMacSel));
}

//--------------------------------------------------
// Description  : DSC Get Change Status
// Input Value  : enumDpMacStreamSourceType
// Output Value : bit
//--------------------------------------------------
void ScalerDpMacDscRxDscStreamSetChange(EnumDpMacSel enumDpMacSel, bit bEnable)
{
    ScalerDscDecoderSetChange(ScalerDscDecoderDpMacRxxDscMacStreamSourceMapping(enumDpMacSel), bEnable);
}

//--------------------------------------------------
// Description  : DSC Get Change Status
// Input Value  : enumDpMacStreamSourceType
// Output Value : bit
//--------------------------------------------------
void ScalerDpMacDscRxDscStreamSetChange_EXINT0(EnumDpMacSel enumDpMacSel, bit bEnable)
{
    ScalerDscDecoderSetChange_EXINT0(ScalerDscDecoderDpMacRxxDscMacStreamSourceMapping_EXINT0(enumDpMacSel), bEnable);
}

//--------------------------------------------------
// Description  : DSC Clear Change Status
// Input Value  : enumDpMacStreamSourceType
// Output Value : bit
//--------------------------------------------------
void ScalerDpMacDscRxDscStreamClearChange(EnumDpMacSel enumDpMacSel)
{
    ScalerDscDecoderSetChange(ScalerDscDecoderDpMacRxxDscMacStreamSourceMapping(enumDpMacSel), _DISABLE);
}

//--------------------------------------------------
// Description  : Dp Info Setting After Judge
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDscStreamAfterJudgeSetting(EnumDpMacSel enumDpMacSel)
{
    ScalerDpMacDscStreamRxBsMissFlagClear(enumDpMacSel);

    ScalerDpMacDscStreamRxSinkStatusSetting(enumDpMacSel);
}

//--------------------------------------------------
// Description  : Dp Info Setting After Judge
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDscStreamRxBsMissFlagClear(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0BsMissFlagClear();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1BsMissFlagClear();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2BsMissFlagClear();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3BsMissFlagClear();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4BsMissFlagClear();

            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Check
// Input Value  : None
// Output Value : False --> CompressionStream_Flag VB-ID[6] Changed and Video Stream without Compression
//--------------------------------------------------
bit ScalerDpMacDscRxDscStreamCheck(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            return ScalerDpMacStreamRx0DscStreamCheck();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            return ScalerDpMacStreamRx1DscStreamCheck();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            return ScalerDpMacStreamRx2DscStreamCheck();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            return ScalerDpMacStreamRx3DscStreamCheck();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
            return ScalerDpMacStreamRx4DscStreamCheck();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Active / Cancel PPS Timeout Event
// Input Value  : enumDpMacSel, Enable / Disable
// Output Value : bit
//--------------------------------------------------
void ScalerDpMacDscPpsTimeOutProc(EnumDpMacSel enumDpMacSel, bit bEn)
{
    bEn = bEn;

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
            if(bEn == _ENABLE)
            {
                ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_MAC_STREAM_RX0_PPS_RECEIVE_TIMEOUT);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX0_PPS_RECEIVE_TIMEOUT);
            }
#endif
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
            if(bEn == _ENABLE)
            {
                ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_MAC_STREAM_RX1_PPS_RECEIVE_TIMEOUT);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX1_PPS_RECEIVE_TIMEOUT);
            }
#endif
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
            if(bEn == _ENABLE)
            {
                ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_MAC_STREAM_RX2_PPS_RECEIVE_TIMEOUT);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX2_PPS_RECEIVE_TIMEOUT);
            }
#endif
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
#if(_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
            if(bEn == _ENABLE)
            {
                ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_MAC_STREAM_RX3_PPS_RECEIVE_TIMEOUT);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX3_PPS_RECEIVE_TIMEOUT);
            }
#endif
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
#if(_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
            if(bEn == _ENABLE)
            {
                ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_MAC_STREAM_RX4_PPS_RECEIVE_TIMEOUT);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MAC_STREAM_RX4_PPS_RECEIVE_TIMEOUT);
            }
#endif
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Process PPS Timeout Event
// Input Value  : StreamSourceType
// Output Value : bit
//--------------------------------------------------
void ScalerDpMacDscPpsTimeOutEventProc(EnumDpMacSel enumDpMacSel)
{
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(enumDpMacSel);

    if(!((ScalerDpMacStreamRxDscGetFlagStatus(enumDpMacStreamSourceType) == _TRUE) && (ScalerDpMacDscRxDscStreamCheck(enumDpMacSel) == _TRUE)))
    {
        return;
    }

    switch(enumDpMacStreamSourceType)
    {
        case _STREAM_SOURCE_D0_DP:
        case _STREAM_SOURCE_D1_DP:
        case _STREAM_SOURCE_D2_DP:

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            if(ScalerDpMacStreamRxGetElement(enumDpMacStreamSourceType, _DSC_PPS_STATUS) == _FALSE)
            {
                DebugMessageDpRx("DP Mac Do Not Receive PPS Packet, Active TimeOut IRQ", 0);
                ScalerDpAuxRxDscPpsTimeOutProc(ScalerDpRxMacGetInputPortSwitch(enumDpMacSel));
            }
#endif
            break;

#if(_DP_MST2SST_SUPPORT == _ON)
        case _STREAM_SOURCE_MST2SST:

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
            if(ScalerDpMacStreamRxGetElement(enumDpMacStreamSourceType, _DSC_PPS_STATUS) == _FALSE)
            {
                DebugMessageDpRx("DP Mac Do Not Receive PPS Packet, Active TimeOut CSN", 0);

                ScalerDpMstTxSetCsnEvent(GET_DP_RX_MAIN_PORT(), _CONNECT_STATUS_UNPLUG);
                ScalerDpMstTxSetCsnEvent(GET_DP_RX_MAIN_PORT(), _CONNECT_STATUS_PLUG);
            }
#endif
            break;
#endif

        default:
            break;
    }
}
#endif // End for #if((_DP_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON))

