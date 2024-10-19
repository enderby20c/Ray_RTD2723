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
// ID Code      : ScalerDpMacStreamRx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_ST_RX_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DpMacStreamRx/ScalerDpMacStreamRx.h"

#if(_DP_SUPPORT == _ON)
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
// Description  : Get Spd HW Buffer Type
// Input Value  : EnumDpSdpType
// Output Value : EnumDpSdpRamIndex
//--------------------------------------------------
EnumDpSdpRamIndex ScalerDpMacStreamRxGetSdpBufferType_EXINT0(EnumDpSdpType enumDpSdpType)
{
    switch(enumDpSdpType)
    {
        case _DP_SDP_TYPE_INFOFRAME_HDR:
            return _DP_SDP_BUFF_HDR;

        case _DP_SDP_TYPE_INFOFRAME_SPD:
            return _DP_SDP_BUFF_SPD;

        case _DP_SDP_TYPE_INFOFRAME_AUDIO:
            return _DP_SDP_BUFF_ISRC;

        case _DP_SDP_TYPE_VSC:
            return _DP_SDP_BUFF_VSC;

        case _DP_SDP_TYPE_INFOFRAME_VENDOR_SPEC:
            return _DP_SDP_BUFF_RSV0;

        default:
            break;
    }

    return _DP_SDP_BUFF_NONE;
}

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSetNoVideoStreamIRQ_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerDpRxGetMacSwitch_EXINT0(enumInputPort))
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
            // ScalerDpMacRx4SetNoVideoStreamIRQ_EXINT0(bEnable);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Fifo Watch Dog Enable Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRxGetFifoWDStatus_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            return ScalerDpMacStreamRx0GetFifoWDStatus_EXINT0();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            return ScalerDpMacStreamRx1GetFifoWDStatus_EXINT0();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            return ScalerDpMacStreamRx2GetFifoWDStatus_EXINT0();
#endif

        default:
            break;
    }
    return 0x00;
}

//--------------------------------------------------
// Description  : CRC Calculate
// Input Value  : Dx port
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxCRCCalculate_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            SET_DP_MAC_STREAM_RX0_CRC_CALCULATE();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            SET_DP_MAC_STREAM_RX1_CRC_CALCULATE();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            SET_DP_MAC_STREAM_RX2_CRC_CALCULATE();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            SET_DP_MAC_STREAM_RX3_CRC_CALCULATE();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            SET_DP_MAC_STREAM_RX4_CRC_CALCULATE();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get CRC Calculate
// Input Value  : Dx port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxGetCRCCalculate_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_CRC_CALCULATE();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_CRC_CALCULATE();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_CRC_CALCULATE();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            // return GET_DP_MAC_RX3_CRC_CALCULATE();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            // return GET_DP_MAC_RX4_CRC_CALCULATE();

            break;
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Clear CRC Calculate
// Input Value  : Dx port
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxClrCRCCalculate_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            CLR_DP_MAC_STREAM_RX0_CRC_CALCULATE();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            CLR_DP_MAC_STREAM_RX1_CRC_CALCULATE();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            CLR_DP_MAC_STREAM_RX2_CRC_CALCULATE();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            // CLR_DP_MAC_RX3_CRC_CALCULATE();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            // CLR_DP_MAC_RX4_CRC_CALCULATE();

            break;
#endif

        default:

            break;
    }
}

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] IRQ
// Input Value  : enumInputPort, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxDscSetStreamIRQ_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerDpRxGetMacSwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx0DscSetStreamIRQ_EXINT0(enumInputPort, bEnable);
#endif
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx1DscSetStreamIRQ_EXINT0(enumInputPort, bEnable);
#endif
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx2DscSetStreamIRQ_EXINT0(enumInputPort, bEnable);
#endif
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Watch Dog
// Input Value  : enumInputPort, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxDscSetStreamWD_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerDpRxGetMacSwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx0DscSetStreamWD_EXINT0(enumInputPort, bEnable);
#endif
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx1DscSetStreamWD_EXINT0(enumInputPort, bEnable);
#endif
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx2DscSetStreamWD_EXINT0(enumInputPort, bEnable);
#endif
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Link Info from Measure Function
// Input Value  : enumInputPort
// Output Value : EnumDDomainRegion
//--------------------------------------------------
EnumDDomainRegion ScalerDpMacStreamRxGetForceBackgroundPath_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch_EXINT0(enumInputPort))
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

        default:
            break;
    }

    return _DDOMAIN_RGN_NONE;
}
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable DP PR Mode CRC Calculation
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxPRModeCrcCalculateEnable_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerDpRxGetMacSwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerDpMacStreamRx0PRModeCrcCalculateEnable_128b132b_EXINT0(bEnable);
            }
            else
#endif
            {
                ScalerDpMacStreamRx0PRModeCrcCalculateEnable_8b10b_EXINT0(bEnable);
            }

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerDpMacStreamRx1PRModeCrcCalculateEnable_128b132b_EXINT0(bEnable);
            }
            else
#endif
            {
                ScalerDpMacStreamRx1PRModeCrcCalculateEnable_8b10b_EXINT0(bEnable);
            }

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerDpMacStreamRx2PRModeCrcCalculateEnable_128b132b_EXINT0(bEnable);
            }
            else
#endif
            {
                ScalerDpMacStreamRx2PRModeCrcCalculateEnable_8b10b_EXINT0(bEnable);
            }

            break;
#endif
        default:

            break;
    }
}
#endif

#if(_DP_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
//--------------------------------------------------
// Description  : Hdr10 plus Sdp Vsif data Struct Mapping
// Input Value  : Sdp Data Pointer & StructAdvancedHDR10MetaData
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxAdvancedHdr10VsifDataStrcutMapping_EXINT0(BYTE *pucSdpData, StructAdvancedHDR10MetaData *pstSyncAdvancedHDR10Metadata)
{
    BYTE ucindex = 0;
    pstSyncAdvancedHDR10Metadata->pucOUICode[0] = pucSdpData[3];
    pstSyncAdvancedHDR10Metadata->pucOUICode[1] = pucSdpData[4];
    pstSyncAdvancedHDR10Metadata->pucOUICode[2] = pucSdpData[5];
    pstSyncAdvancedHDR10Metadata->ucVersion = pucSdpData[0];
    pstSyncAdvancedHDR10Metadata->ucTargetDisplayLv = (pucSdpData[6] & 0x3F) >> 1;
    pstSyncAdvancedHDR10Metadata->ucDistribution50 = pucSdpData[12];
    pstSyncAdvancedHDR10Metadata->ucDistribution99 = pucSdpData[16];
    pstSyncAdvancedHDR10Metadata->pusKneePoint[0] = (((WORD)pucSdpData[17] & 0x0F) << 6) | ((pucSdpData[18] & 0xFC) >> 2);
    pstSyncAdvancedHDR10Metadata->pusKneePoint[1] = (((WORD)pucSdpData[18] & 0x03) << 8) | pucSdpData[19];

    for(ucindex = 0; ucindex < 9; ucindex++)
    {
        pstSyncAdvancedHDR10Metadata->pucBezierAnchor[ucindex] = pucSdpData[20 + ucindex];
    }

    pstSyncAdvancedHDR10Metadata->ucGraphicOverlayFlag = (pucSdpData[29] & _BIT7) >> 7;
    pstSyncAdvancedHDR10Metadata->ucNoDelayFlag = (pucSdpData[29] & _BIT6) >> 6;
}
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : DP DRA Infoframe Received Check
// Input Value  : Input port, Sdp Type
// Output Value : Received Flag
//--------------------------------------------------
bit ScalerDpMacStreamRxGetDMDRAMReceived_EXINT0(EnumInputPort enumInputPort)
{
    WORD usDpDMDRAMReceivedAddress = 0x00;

    switch(ScalerDpRxGetMacSwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usDpDMDRAMReceivedAddress = P1B_33_DP_SDP_HDR_INFO_CTRL;
            }
            else
#endif
            {
                usDpDMDRAMReceivedAddress = PB6_37_DP_SDP_HDR_INFO_CTRL;
            }

#if(_DP_MAC_RX0_DM_SUPPORT == _ON)
            if(ScalerGetBit_EXINT(usDpDMDRAMReceivedAddress, _BIT6) == _BIT6)
            {
                ScalerSetBit_EXINT(usDpDMDRAMReceivedAddress, ~_BIT6, _BIT6);

                return _TRUE;
            }
            else
#endif
            {
                return _FALSE;
            }
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usDpDMDRAMReceivedAddress = P75_33_DP_SDP_HDR_INFO_CTRL;
            }
            else
#endif
            {
                usDpDMDRAMReceivedAddress = PB9_37_DP_SDP_HDR_INFO_CTRL;
            }

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
            if(ScalerGetBit_EXINT(usDpDMDRAMReceivedAddress, _BIT6) == _BIT6)
            {
                ScalerSetBit_EXINT(usDpDMDRAMReceivedAddress, ~_BIT6, _BIT6);

                return _TRUE;
            }
            else
#endif
            {
                return _FALSE;
            }
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usDpDMDRAMReceivedAddress = PD4_33_DP_SDP_HDR_INFO_CTRL;
            }
            else
#endif
            {
                usDpDMDRAMReceivedAddress = PC7_37_DP_SDP_HDR_INFO_CTRL;
            }

#if(_DP_MAC_RX2_DM_SUPPORT == _ON)
            if(ScalerGetBit_EXINT(usDpDMDRAMReceivedAddress, _BIT6) == _BIT6)
            {
                ScalerSetBit_EXINT(usDpDMDRAMReceivedAddress, ~_BIT6, _BIT6);

                return _TRUE;
            }
            else
#endif
            {
                return _FALSE;
            }
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usDpDMDRAMReceivedAddress = PF2_33_DP_SDP_HDR_INFO_CTRL;
            }
            else
#endif
            {
                usDpDMDRAMReceivedAddress = PEF_37_DP_SDP_HDR_INFO_CTRL;
            }

#if(_DP_MAC_RX3_DM_SUPPORT == _ON)
            if(ScalerGetBit_EXINT(usDpDMDRAMReceivedAddress, _BIT6) == _BIT6)
            {
                ScalerSetBit_EXINT(usDpDMDRAMReceivedAddress, ~_BIT6, _BIT6);

                return _TRUE;
            }
            else
#endif
            {
                return _FALSE;
            }
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                usDpDMDRAMReceivedAddress = PE1_33_DP_SDP_HDR_INFO_CTRL;
            }
            else
#endif
            {
                usDpDMDRAMReceivedAddress = P35_37_DP_SDP_HDR_INFO_CTRL;
            }

#if(_DP_MAC_RX4_DM_SUPPORT == _ON)
            if(ScalerGetBit_EXINT(usDpDMDRAMReceivedAddress, _BIT6) == _BIT6)
            {
                ScalerSetBit_EXINT(usDpDMDRAMReceivedAddress, ~_BIT6, _BIT6);

                return _TRUE;
            }
            else
#endif
            {
                return _FALSE;
            }
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DM Recheck InterFace Packet Irq Receive
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxDMPacketReCheck_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

#if(_DP_MAC_RX0_DM_SUPPORT == _ON)
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerDpMacStreamRx0DMPacketReCheck_128b132b_EXINT0(enumInputPort);
            }
            else
#endif
            {
                ScalerDpMacStreamRx0DMPacketReCheck_8b10b_EXINT0(enumInputPort);
            }

            break;
#endif
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerDpMacStreamRx1DMPacketReCheck_128b132b_EXINT0(enumInputPort);
            }
            else
#endif
            {
                ScalerDpMacStreamRx1DMPacketReCheck_8b10b_EXINT0(enumInputPort);
            }

            break;
#endif
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

#if(_DP_MAC_RX2_DM_SUPPORT == _ON)
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerDpMacStreamRx2DMPacketReCheck_128b132b_EXINT0(enumInputPort);
            }
            else
#endif
            {
                ScalerDpMacStreamRx2DMPacketReCheck_8b10b_EXINT0(enumInputPort);
            }

            break;
#endif
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

#if(_DP_MAC_RX3_DM_SUPPORT == _ON)
#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerDpMacStreamRx3DMPacketReCheck_128b132b_EXINT0(enumInputPort);
            }
            else
#endif
            {
                ScalerDpMacStreamRx3DMPacketReCheck_8b10b_EXINT0(enumInputPort);
            }

            break;
#endif
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

#if(_DP_MAC_RX4_DM_SUPPORT == _ON)
#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerDpMacStreamRx4DMPacketReCheck_128b132b_EXINT0(enumInputPort);
            }
            else
#endif
            {
                ScalerDpMacStreamRx4DMPacketReCheck_8b10b_EXINT0(enumInputPort);
            }

            break;
#endif
#endif
        default:

            break;
    }
}
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : For Stream MST2SST
// Input Value  : None
// Output Value : EnumDpStreamSourceNum
//--------------------------------------------------
EnumDpStreamSourceNum ScalerDpMacStreamRxGetStreamSourceTypeToSourceMux_EXINT0(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    return ScalerDpMacStreamRxGetMacToSourceMux_EXINT0(ScalerDpRxGetMacSwitchMappingSourceType_EXINT0(enumDpMacStreamSourceType));
}

//--------------------------------------------------
// Description  : Get Mac To Source Mux Mapping
// Input Value  : None
// Output Value : EnumDpStreamSourceNum
//--------------------------------------------------
EnumDpStreamSourceNum ScalerDpMacStreamRxGetMacToSourceMux_EXINT0(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            return _HW_DP_MST_RX_MAC0_SOURCEX_MAPPING;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            return _HW_DP_MST_RX_MAC1_SOURCEX_MAPPING;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            return _HW_DP_MST_RX_MAC2_SOURCEX_MAPPING;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            return _HW_DP_MST_RX_MAC3_SOURCEX_MAPPING;
#endif

        default:
            return _DP_NO_SOURCE;
    }
}
#endif


#endif
