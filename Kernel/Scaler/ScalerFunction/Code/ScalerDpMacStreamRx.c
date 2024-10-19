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
// ID Code      : ScalerDpMacStreamRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_STREAM_RX__

#include "ScalerFunctionInclude.h"
#include "DpMacStreamRx/ScalerDpMacStreamRx.h"

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_DP_FREESYNC_SUPPORT == _ON)
StructDPMacRxDrrMsaInfo g_stDpMacStreamRxDrrMsaInfo;
#endif

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
StructDpMacStreamRxPowerStatus g_stDpMacStreamRxPowerStatus;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Dp Mac Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxMacInitial(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0MacInitial();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1MacInitial();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2MacInitial();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3MacInitial();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4MacInitial();

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0MacInitial();
            ScalerDpMacStreamRx1MacInitial();
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1MacInitial();
            ScalerDpMacStreamRx2MacInitial();
#endif
            break;
#endif

        default:

            break;
    }
#if(_DP_RX_FEC_SUPPORT == _ON)
    ScalerDpMacDphyRxFecInitial(enumInputPort);
#endif
}

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
//--------------------------------------------------
// Description  : DP MAC Stream power process
// Input Value  : EnumInputPort, EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxPowerProc(EnumDpMacSel enumDpMacSel, EnumPowerAction enumPowerAction)
{
#if(_AUDIO_SUPPORT == _ON)
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerDpMacStreamRxGetInternalAudioGenEnable(enumDpMacSel) == _ENABLE)
    {
        return;
    }
#endif
#endif

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0PowerProc(enumPowerAction);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1PowerProc(enumPowerAction);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2PowerProc(enumPowerAction);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3PowerProc(enumPowerAction);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4PowerProc(enumPowerAction);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP MAC Stream Unused Mac power process
// Input Value  : EnumInputPort, EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxUnusedMacPowerOffProc(void)
{
#if(_DP_MAC_RX0_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_0;
#elif(_DP_MAC_RX1_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_1;
#elif(_DP_MAC_RX2_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_2;
#endif

    // Search and Power Off the Mac which is Not Assigned to Any Stream Source
    for(EnumDpMacSel enumDpMacLoopIndex = enumDpMacSelStart; enumDpMacLoopIndex < _DP_MAC_ENTITY_MAX; enumDpMacLoopIndex++)
    {
        if(ScalerDpMacStreamRxCheckMacInUse(enumDpMacLoopIndex) == _FALSE)
        {
            ScalerDpMacStreamRxPowerProc(enumDpMacLoopIndex, _POWER_ACTION_NORMAL_TO_OFF);
        }
    }
}

//--------------------------------------------------
// Description  : Check DP Mac Stream Is In Use or Not
// Input Value  : EnumDpMacSel
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxCheckMacInUse(EnumDpMacSel enumDpMacSel)
{
    EnumDpMacStreamSourceType enumDpMacStreamSourceType = ScalerDpRxGetMacStreamSourceType(enumDpMacSel);

    if(enumDpMacStreamSourceType == _STREAM_SOURCE_NONE)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif

#if(_AUDIO_SUPPORT == _ON)
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Whether Internal Audio Pattern Gen is Enabled
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerDpMacStreamRxGetInternalAudioGenEnable(EnumDpMacSel enumDpMacSel)
{
#if(_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON)
    // Check Whether Audio Pattern Gen is Enable
    if(GET_AUDIO_INTERNAL_GEN_ENABLE_STATE() == _ON)
    {
        return _ENABLE;
    }
#endif // End of #if(_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON)


    switch(enumDpMacSel)
    {
#if(_DP_AUDIO_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpAudioRx0GetInternalAudioGenEnable();
            break;
#endif

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpAudioRx1GetInternalAudioGenEnable();
            break;
#endif

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpAudioRx2GetInternalAudioGenEnable();
            break;
#endif

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpAudioRx3GetInternalAudioGenEnable();
            break;
#endif

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpAudioRx4GetInternalAudioGenEnable();
            break;
#endif

        default:
            break;
    }

    return _DISABLE;
}
#endif
#endif

//--------------------------------------------------
// Description  : Dp Secondary Data Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSdpInitial(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SdpInitial();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx0SetSdpMetaSramRcvInitial();
#endif

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SdpInitial();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx1SetSdpMetaSramRcvInitial();
#endif

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SdpInitial();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx2SetSdpMetaSramRcvInitial();
#endif

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SdpInitial();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx3SetSdpMetaSramRcvInitial();
#endif

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SdpInitial();

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0SdpInitial();
            ScalerDpMacStreamRx1SdpInitial();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx0SetSdpMetaSramRcvInitial();
            ScalerDpMacStreamRx1SetSdpMetaSramRcvInitial();
#endif
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1SdpInitial();
            ScalerDpMacStreamRx2SdpInitial();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx1SetSdpMetaSramRcvInitial();
            ScalerDpMacStreamRx2SetSdpMetaSramRcvInitial();
#endif
#endif
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Mac Sdp Dtect
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSdpDataDetect(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SdpDataDetect();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SdpDataDetect();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SdpDataDetect();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SdpDataDetect();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SdpDataDetect();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Sdp Packet Check
// Input Value  : Dp Sdp Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSdpPacketCheck(EnumDpMacSel enumDpMacSel, EnumDpSdpType enumDpSdpType)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SdpPacketCheck(enumDpSdpType);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SdpPacketCheck(enumDpSdpType);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SdpPacketCheck(enumDpSdpType);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SdpPacketCheck(enumDpSdpType);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SdpPacketCheck(enumDpSdpType);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Sdp Packet Data
// Input Value  : Dp Sdp Ram Index & Sdp Buff
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxGetSdpPktData(EnumInputPort enumInputPort, EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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
// Description  : Sdp Infoframe Received Check
// Input Value  : Input port, Sdp Type
// Output Value : Received Flag
//--------------------------------------------------
EnumDpMacRxSdpReceiveStates ScalerDpMacStreamRxGetSdpReceived(EnumDpMacStreamSourceType enumMacSource, EnumDpSdpType enumDpSdpType)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetSdpReceived(enumDpSdpType);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetSdpReceived(enumDpSdpType);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetSdpReceived(enumDpSdpType);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetSdpReceived(enumDpSdpType);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetSdpReceived(enumDpSdpType);
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Sdp Infoframe Change Event Check
// Input Value  : EnumDpMacStreamSourceType, Sdp Type
// Output Value : Change Event
//--------------------------------------------------
EnumDpMacRxSdpChangeEvent ScalerDpMacStreamRxGetSdpChangeEvent(EnumDpMacStreamSourceType enumMacSource, EnumDpSdpType enumDpSdpType)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetSdpChangeEvent(enumDpSdpType);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetSdpChangeEvent(enumDpSdpType);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetSdpChangeEvent(enumDpSdpType);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetSdpChangeEvent(enumDpSdpType);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetSdpChangeEvent(enumDpSdpType);
#endif

        default:

            break;
    }

    return _SDP_EVENT_NONE;
}

//--------------------------------------------------
// Description  : Sdp Infoframe Changed Check
// Input Value  : Input port, Sdp Type
// Output Value : changed Flag
//--------------------------------------------------
bit ScalerDpMacStreamRxGetSdpChanged(EnumDpMacStreamSourceType enumMacSource, EnumDpSdpType enumDpSdpType)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetSdpChanged(enumDpSdpType);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetSdpChanged(enumDpSdpType);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetSdpChanged(enumDpSdpType);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetSdpChanged(enumDpSdpType);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetSdpChanged(enumDpSdpType);
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Spd Infoframe HB3
// Input Value  : Input port, Dp Sdp Type
// Output Value : HB3
//--------------------------------------------------
BYTE ScalerDpMacStreamRxGetSdpHB3(EnumInputPort enumInputPort, EnumDpSdpType enumDpSdpType)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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

    return 0x00;
}

//--------------------------------------------------
// Description  : Get Spd HW Buffer Type
// Input Value  : EnumDpSdpType
// Output Value : EnumDpSdpRamIndex
//--------------------------------------------------
EnumDpSdpRamIndex ScalerDpMacStreamRxGetSdpBufferType(EnumDpSdpType enumDpSdpType)
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

        case _DP_SDP_TYPE_ADAPTIVESYNC:
            return _DP_SDP_BUFF_ADAPTIVESYNC;

        default:
            break;
    }

    return _DP_SDP_BUFF_NONE;
}

//--------------------------------------------------
// Description  : CRC Calculate
// Input Value  : Dx port
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRxGetCRCCalculate(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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

            return GET_DP_MAC_STREAM_RX3_CRC_CALCULATE();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_CRC_CALCULATE();

            break;
#endif

        default:
            break;
    }

    return _DISABLE;
}

//-----------------------------------------------------------------------
// Description  : Set DP MAC Clock Output / PLL Power Off
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------------
void ScalerDpMacStreamRxLowPowerProc(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0LowPowerProc();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1LowPowerProc();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2LowPowerProc();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3LowPowerProc();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4LowPowerProc();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Dp MSA Timing Info
// Input Value  : DP Info Structure
// Output Value : True --> Get MSA Info
//--------------------------------------------------
bit ScalerDpMacStreamRxGetMsaTimingInfo(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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
// Description  : Get Dp Check Interlace Vtotal for Clone Mode
// Input Value  : DP Info Structure
// Output Value : bit EVEN or ODD
//--------------------------------------------------
bit ScalerDpMacStreamRxCheckInterlaceVtotal(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_INTERLACE_VTOTAL_NUMBER();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_INTERLACE_VTOTAL_NUMBER();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_INTERLACE_VTOTAL_NUMBER();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_INTERLACE_VTOTAL_NUMBER();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_INTERLACE_VTOTAL_NUMBER();

            break;
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : DP RGB Output Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxAVMute(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0AVMute();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1AVMute();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2AVMute();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3AVMute();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4AVMute();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check Rx Input Pixel Mode
// Input Value  : None
// Output Value : One Pixel or Two Pixel Mode
//--------------------------------------------------
EnumDpRxMacPixelMode ScalerDpMacStreamRxInputPixelMode(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dp Rx Interlace Mode Config
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRxInterlaceModeConfig(EnumInputPort enumInputPort, BYTE ucInterlaceReference)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)

        case _DP_MAC_0:

            return ScalerDpMacStreamRx0InterlaceModeConfig(ucInterlaceReference);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1InterlaceModeConfig(ucInterlaceReference);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2InterlaceModeConfig(ucInterlaceReference);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3InterlaceModeConfig(ucInterlaceReference);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4InterlaceModeConfig(ucInterlaceReference);
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DP MAC Source Port
// Input Value  : enumMacSel
// Output Value : Physical InputPort
//--------------------------------------------------
EnumInputPort ScalerDpMacStreamRxGetSourcePort(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    switch(enumDpMacStreamSourceType)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _STREAM_SOURCE_D0_DP:
            return _D0_INPUT_PORT;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _STREAM_SOURCE_D1_DP:
            return _D1_INPUT_PORT;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _STREAM_SOURCE_D2_DP:
            return _D2_INPUT_PORT;
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
        case _STREAM_SOURCE_PXP:
            return ((GET_DP_MST_RX_PXP_INPUT_PORT() < _NO_INPUT_PORT) ? GET_DP_MST_RX_PXP_INPUT_PORT() : _NO_INPUT_PORT);
#endif

#if(_DP_MST2SST_SUPPORT == _ON)
        case _STREAM_SOURCE_MST2SST:
            return ((GET_DP_RX_MAIN_PORT() < _NO_INPUT_PORT) ? GET_DP_RX_MAIN_PORT() : _NO_INPUT_PORT);
#endif

        default:
            break;
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : Judge Timing for using DE-Only mode or not
// Input Value  : StructDpInfo *pstDpInfo
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxDeOnlyTimngCheck(StructDpInfo *pstDpInfo, DWORD ulFrameRate)
{
    // Timing-1 : 1280x1024@120Hz (Source : Apple MacBook Air 13" / ChipSet : Apple M1)
    if((pstDpInfo->stDpTimingInfo.usHWidth == 0x500) && (pstDpInfo->stDpTimingInfo.usVHeight == 0x400) &&
       ((ulFrameRate >= 11800) && (ulFrameRate <= 12200)))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Judge for using DE-Only mode or not
// Input Value  : StructDpInfo *pstDpInfo
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxDeOnlyJudge_8b10b(StructDpInfo *pstDpInfo)
{
    DWORD ulFrameRate = 0;
    DWORD ulLineRate = 0;
    WORD usMeasureVtotal = 0;
    WORD usDiffVtotal = 0;

    if(pstDpInfo->stDpLinkInfo.ulVBsToBsCountN == 0x00)
    {
        return _FALSE;
    }

    // Frame Rate (Unit is 0.01Hz)
    ulFrameRate = ScalerGlobalComputeDwordMulDiv((DWORD)_GDIPHY_RX_GDI_CLK_KHZ, 100000, pstDpInfo->stDpLinkInfo.ulVBsToBsCountN);

    if(ScalerDpMacStreamRxDeOnlyTimngCheck(pstDpInfo, ulFrameRate) == _TRUE)
    {
        if(pstDpInfo->stDpLinkInfo.usHBsToBsCount == 0x00)
        {
            return _FALSE;
        }

        // Line Rate (Unit : 0.01Hz)
        ulLineRate = ScalerGlobalComputeDwordMulDiv(pstDpInfo->stDpLinkInfo.ulLinkClockHz, 1, (DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount * 2) * 100;

        // Vtotal by Measure (Unit : Line Number)
        usMeasureVtotal = (WORD)((ulLineRate + (ulFrameRate / 2)) / ulFrameRate);

        // Difference of Vtotal by Measure and MSA
        usDiffVtotal = abs(usMeasureVtotal - pstDpInfo->stDpTimingInfo.usVTotal);

        if((usDiffVtotal >= 4) && (usDiffVtotal <= 6))
        {
            pstDpInfo->stDpTimingInfo.usVTotal = usMeasureVtotal;

            DebugMessageDpRx("Votal (Measure vs MSA) is different !!!", usDiffVtotal);

            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Interlace by VBID or Measure
// Input Value  : None
// Output Value : True --> Interlace
//--------------------------------------------------
bit ScalerDpMacStreamRxInterlaceCheck(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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
// Description  : DP Stream Clk PLL Setting
// Input Value  : StructDpInfo
// Output Value : True --> Stream CLK Regen. ok
//--------------------------------------------------
bit ScalerDpMacStreamRxStreamClkRegenerate(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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
bit ScalerDpMacStreamRxTrackingSetting(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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
// Description  : Target Stream Clock Within Pll Capability Check
// Input Value  : enumInputPort, ulTargetStreamClockHz
// Output Value : NONE
//--------------------------------------------------
bit ScalerDpMacStreamRxSclkWithinPllCapabilityCheck(EnumInputPort enumInputPort, DWORD ulTargetStreamClockHz)
{
    enumInputPort = enumInputPort;

    DWORD ulDataPathSpeedLimit = (DWORD)_HW_DATA_PATH_SPEED_LIMIT * 100000;

    // ulDataPathSpeedLimit * (1 + 1% margin)
    ulDataPathSpeedLimit = GET_DWORD_MUL_DIV(ulDataPathSpeedLimit, 101, 100);

#if((_DP_MAC_RX_128B132B_CODING_TYPE_SUPPORT == _ON) && (_DP_MAC_RX_128B132B_FOUR_PIXEL_MODE_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_PIXEL_MODE == _ON))
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        if(ulTargetStreamClockHz > (4 * ulDataPathSpeedLimit))
        {
            return _FALSE;
        }
    }
    else
#endif
    {
        if(ulTargetStreamClockHz > (2 * ulDataPathSpeedLimit))
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Stream Clk PLL Setting for Reorder Tracking
// Input Value  : Dp Mac Sel& pstDpInfo
// Output Value : _FALSE or _TRUE
//--------------------------------------------------
bit ScalerDpMacStreamRxPllSettingForReorderTracking(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo)
{
    StructDpInfo stDpInfo = *pstDpInfo;

    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(enumDpMacSel);

    /////////////////////////////////
    // Adjust Target Clock And Htt //
    /////////////////////////////////

    while(ScalerDpMacStreamRxSclkWithinPllCapabilityCheck(enumInputPort, stDpInfo.stDpLinkInfo.ulInitStreamClockHz) == _FALSE)
    {
        stDpInfo.stDpLinkInfo.ulInitStreamClockHz /= 2;

        stDpInfo.stDpTimingInfo.usHTotal /= 2;

        DebugMessageDpRx("DP MAC RX: Adjusted Htt For Reorder Tracking", stDpInfo.stDpTimingInfo.usHTotal);
        DebugMessageDpRx("DP MAC RX: Adjusted Sclk For Reorder Tracking", stDpInfo.stDpLinkInfo.ulInitStreamClockHz);
    }


    //////////////////////////////
    // PLL and Tracking Setting //
    //////////////////////////////

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            if(ScalerDpMacStreamRx0StreamClkRegenerate(&stDpInfo) == _FALSE)
            {
                return _FALSE;
            }

            if(ScalerDpMacStreamRx0TrackingSetting(&stDpInfo) == _FALSE)
            {
                return _FALSE;
            }

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            if(ScalerDpMacStreamRx1StreamClkRegenerate(&stDpInfo) == _FALSE)
            {
                return _FALSE;
            }

            if(ScalerDpMacStreamRx1TrackingSetting(&stDpInfo) == _FALSE)
            {
                return _FALSE;
            }
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            if(ScalerDpMacStreamRx2StreamClkRegenerate(&stDpInfo) == _FALSE)
            {
                return _FALSE;
            }

            if(ScalerDpMacStreamRx2TrackingSetting(&stDpInfo) == _FALSE)
            {
                return _FALSE;
            }
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            if(ScalerDpMacStreamRx3StreamClkRegenerate(&stDpInfo) == _FALSE)
            {
                return _FALSE;
            }

            if(ScalerDpMacStreamRx3TrackingSetting(&stDpInfo) == _FALSE)
            {
                return _FALSE;
            }
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            if(ScalerDpMacStreamRx4StreamClkRegenerate(&stDpInfo) == _FALSE)
            {
                return _FALSE;
            }

            if(ScalerDpMacStreamRx4TrackingSetting(&stDpInfo) == _FALSE)
            {
                return _FALSE;
            }
            break;
#endif
        default:
            return _FALSE;
    }
    return _TRUE;
}

//--------------------------------------------------
// Description  : DP NF PLL Setting for PLL Power Off Process
// Input Value  : ulvcoFreq --> VCO Frequency(Hz)
//              : ucNcode --> PLL N Code
//              : ucpllo --> divider o code
//              : ucdivs --> divider s code
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSetPLLNfOffProc(EnumInputPort enumInputPort, DWORD ulPllVcoClockHz, BYTE ucNcode, BYTE ucpllo, BYTE ucdivs)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SetPLLNfOffProc(ulPllVcoClockHz, ucNcode, ucpllo, ucdivs);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SetPLLNfOffProc(ulPllVcoClockHz, ucNcode, ucpllo, ucdivs);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SetPLLNfOffProc(ulPllVcoClockHz, ucNcode, ucpllo, ucdivs);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SetPLLNfOffProc(ulPllVcoClockHz, ucNcode, ucpllo, ucdivs);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SetPLLNfOffProc(ulPllVcoClockHz, ucNcode, ucpllo, ucdivs);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP NF PLL Setting for PLL Power Off Process
// Input Value  : ucNcode --> PLL N Code
//              : ucFcode_MSB4b --> PLL F Code (MSB 4 bits)
//              : usFcode_LSB16b --> PLL F Code (LSB 16 bits)
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRxSetPLLNfOnProc(EnumInputPort enumInputPort, BYTE ucNcode, BYTE ucFcode_MSB4b, WORD usFcode_LSB16b, bit bPllVcoHighFreqStatus)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0SetPLLNfOnProc(ucNcode, ucFcode_MSB4b, usFcode_LSB16b, bPllVcoHighFreqStatus);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1SetPLLNfOnProc(ucNcode, ucFcode_MSB4b, usFcode_LSB16b, bPllVcoHighFreqStatus);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2SetPLLNfOnProc(ucNcode, ucFcode_MSB4b, usFcode_LSB16b, bPllVcoHighFreqStatus);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3SetPLLNfOnProc(ucNcode, ucFcode_MSB4b, usFcode_LSB16b, bPllVcoHighFreqStatus);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4SetPLLNfOnProc(ucNcode, ucFcode_MSB4b, usFcode_LSB16b, bPllVcoHighFreqStatus);

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Get Video Info
// Input Value  : None
// Output Value : TRUE --> Get successfully
//--------------------------------------------------
bit ScalerDpMacStreamRxGetVideoInfo(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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
void ScalerDpMacStreamRxSetColorInfo(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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
// Description  : Video/DisplayFormat/Measure relative Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxMacSetting(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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
// Description  : Get DP Link Info from Measure Function
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxGetMeasureLinkInfo(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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
// Description  : Set DP MAC V Front Porch
// Input Value  : ucVfrontporch
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSetVfrontPorch(EnumInputPort enumInputPort, BYTE ucVfrontporch)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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
// Description  : Set DP MAC V Height
// Input Value  : usVheight
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSetVheight(EnumInputPort enumInputPort, WORD usVheight)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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
// Description  : DP Timing Info Adjust
// Input Value  : enumInputPort, *pstDpInfo
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxTimingInfoAdjust(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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
// Description  : DP Timing Info Adjust for Reorder Tracking
// Input Value  : Dp Rx Mac & stDpInfo
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxTimingInfoAdjustForReorderTracking(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0TimingInfoAdjustForReorderTracking(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1TimingInfoAdjustForReorderTracking(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2TimingInfoAdjustForReorderTracking(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3TimingInfoAdjustForReorderTracking(pstDpInfo);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4TimingInfoAdjustForReorderTracking(pstDpInfo);

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check DP Link Info from Measure Function
// Input Value  : StructDpInfo pointer
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxMeasureInfoCheck(StructDpInfo *pstDpInfo)
{
    // Bs2Bs Count Check, CNT=0 => IDLE pattern
    if((pstDpInfo->stDpLinkInfo.usHBsToBsCount == 0) ||
       (pstDpInfo->stDpLinkInfo.ulVBsToBsCountN == 0) ||
       (pstDpInfo->stDpLinkInfo.ulVBsToBsCountN1 == 0))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Update timing info HS/VS polarity
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxPolarity(EnumInputPort enumInputPort)
{
#if(_DUAL_DP_SUPPORT == _ON)
    EnumDpMacSel enumDualDpMacSel = _DP_MAC_NONE;
#endif

    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0Polarity();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1Polarity();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2Polarity();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3Polarity();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4Polarity();

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

            enumDualDpMacSel = ScalerDpRxGetMacSwitch(GET_DUAL_DP_PORT_SWITCH_SELECT());

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            if(enumDualDpMacSel == _DP_MAC_1)
            {
                ScalerDpMacStreamRx1Polarity();
            }
            else
            {
                ScalerDpMacStreamRx0Polarity();
            }
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            if(enumDualDpMacSel == _DP_MAC_2)
            {
                ScalerDpMacStreamRx2Polarity();
            }
            else
            {
                ScalerDpMacStreamRx1Polarity();
            }
#endif
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check Dp Interlace Mode VBID
// Input Value  : INPUT_PORT
// Output Value : True --> Get Interlace Mode
//--------------------------------------------------
bit ScalerDpMacStreamRxGetInterlaceMode(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetVbidInfo(_DP_VBID_INTERLACE_MODE);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetVbidInfo(_DP_VBID_INTERLACE_MODE);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetVbidInfo(_DP_VBID_INTERLACE_MODE);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetVbidInfo(_DP_VBID_INTERLACE_MODE);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetVbidInfo(_DP_VBID_INTERLACE_MODE);
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Clr Colorimetry Changed
// Input Value  : INPUT PORT
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacStreamRxDigitalClrColorimetryChanged(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            CLR_DP_MAC_STREAM_RX0_COLORIMETRY_CHANGED();
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            CLR_DP_MAC_STREAM_RX1_COLORIMETRY_CHANGED();
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            CLR_DP_MAC_STREAM_RX2_COLORIMETRY_CHANGED();
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            CLR_DP_MAC_STREAM_RX3_COLORIMETRY_CHANGED();
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
            CLR_DP_MAC_STREAM_RX4_COLORIMETRY_CHANGED();
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:
#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            CLR_DP_MAC_STREAM_RX0_COLORIMETRY_CHANGED();
            CLR_DP_MAC_STREAM_RX1_COLORIMETRY_CHANGED();
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            CLR_DP_MAC_STREAM_RX1_COLORIMETRY_CHANGED();
            CLR_DP_MAC_STREAM_RX2_COLORIMETRY_CHANGED();
#endif
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clr ColorimetryExt Changed
// Input Value  : INPUT PORT
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacStreamRxDigitalClrColorimetryExtChanged(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            CLR_DP_MAC_STREAM_RX0_COLORIMETRY_EXT_CHANGED();
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            CLR_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_CHANGED();
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            CLR_DP_MAC_STREAM_RX2_COLORIMETRY_EXT_CHANGED();
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            CLR_DP_MAC_STREAM_RX3_COLORIMETRY_EXT_CHANGED();
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
            CLR_DP_MAC_STREAM_RX4_COLORIMETRY_EXT_CHANGED();
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:
#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            CLR_DP_MAC_STREAM_RX0_COLORIMETRY_EXT_CHANGED();
            CLR_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_CHANGED();
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            CLR_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_CHANGED();
            CLR_DP_MAC_STREAM_RX2_COLORIMETRY_EXT_CHANGED();
#endif
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clr ColorimetryChanged
// Input Value  : INPUT PORT
// Output Value : NONE
//--------------------------------------------------
void ScalerDpMacStreamRxDigitalClrQuantizationChanged(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            CLR_DP_MAC_STREAM_RX0_QUANTIZATION_CHANGED();
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            CLR_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED();
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            CLR_DP_MAC_STREAM_RX2_QUANTIZATION_CHANGED();
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            CLR_DP_MAC_STREAM_RX3_QUANTIZATION_CHANGED();
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
            CLR_DP_MAC_STREAM_RX4_QUANTIZATION_CHANGED();
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:
#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            CLR_DP_MAC_STREAM_RX0_QUANTIZATION_CHANGED();
            CLR_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED();
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            CLR_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED();
            CLR_DP_MAC_STREAM_RX2_QUANTIZATION_CHANGED();
#endif
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : ScalerDpMacForceBckgrdPath
// Input Value  : PORT & enumDDomainRegion
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxForceBckgrdPath(EnumInputPort enumInputPort, EnumDDomainRegion enumDDomainRegion)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            SET_DP_MAC_STREAM_RX0_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            SET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            SET_DP_MAC_STREAM_RX2_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            SET_DP_MAC_STREAM_RX3_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
            SET_DP_MAC_STREAM_RX4_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:
#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            SET_DP_MAC_STREAM_RX0_FORCE_BCKGRD_PATH(enumDDomainRegion);
            SET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH(enumDDomainRegion);
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            SET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH(enumDDomainRegion);
            SET_DP_MAC_STREAM_RX2_FORCE_BCKGRD_PATH(enumDDomainRegion);
#endif
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : ScalerDpMacClrForceBckgrdPath
// Input Value  : PORT & enumDDomainRegion
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxClrForceBckgrdPath(EnumInputPort enumInputPort, EnumDDomainRegion enumDDomainRegion)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            CLR_DP_MAC_STREAM_RX0_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            CLR_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            CLR_DP_MAC_STREAM_RX2_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            CLR_DP_MAC_STREAM_RX3_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
            CLR_DP_MAC_STREAM_RX4_FORCE_BCKGRD_PATH(enumDDomainRegion);
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:
#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            CLR_DP_MAC_STREAM_RX0_FORCE_BCKGRD_PATH(enumDDomainRegion);
            CLR_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH(enumDDomainRegion);
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            CLR_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH(enumDDomainRegion);
            CLR_DP_MAC_STREAM_RX2_FORCE_BCKGRD_PATH(enumDDomainRegion);
#endif
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check Dp Video Straam Msa Info
// Input Value  : EnumInputPort, EnumDpRxMsaType
// Output Value : UnionDpRxMsaValue
//--------------------------------------------------
UnionDpRxMsaValue ScalerDpMacStreamRxGetMsaInfo(EnumInputPort enumInputPort, EnumDpRxMsaType enumDpRxMsaType)
{
    UnionDpRxMsaValue unDpRxMsaValue;

    if(ScalerDpAuxRxGetLTStatus(enumInputPort) != _DP_NORMAL_LINK_TRAINING_PASS)
    {
        unDpRxMsaValue.uqDpRxMsaError = 0xFFFF;

        return unDpRxMsaValue;
    }

    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetMsaInfo(enumDpRxMsaType);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetMsaInfo(enumDpRxMsaType);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetMsaInfo(enumDpRxMsaType);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetMsaInfo(enumDpRxMsaType);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetMsaInfo(enumDpRxMsaType);
#endif
        default:
            unDpRxMsaValue.uqDpRxMsaError = 0xFFFF;
            break;
    }

    return unDpRxMsaValue;
}

//--------------------------------------------------
// Description  : Check Dp Video Straam VBID
// Input Value  : INPUT_PORT
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpMacStreamRxGetVideoStream(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetVbidInfo(_DP_VBID_VIDEO_STREAM);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetVbidInfo(_DP_VBID_VIDEO_STREAM);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetVbidInfo(_DP_VBID_VIDEO_STREAM);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetVbidInfo(_DP_VBID_VIDEO_STREAM);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetVbidInfo(_DP_VBID_VIDEO_STREAM);
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp DSC Straam VBID
// Input Value  : INPUT_PORT
// Output Value : True --> Get DSC Stream
//--------------------------------------------------
bit ScalerDpMacStreamRxGetDscStream(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetVbidInfo(_DP_VBID_DSC_STREAM);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetVbidInfo(_DP_VBID_DSC_STREAM);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetVbidInfo(_DP_VBID_DSC_STREAM);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetVbidInfo(_DP_VBID_DSC_STREAM);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetVbidInfo(_DP_VBID_DSC_STREAM);
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Sdp Packet Check
// Input Value  : Dp Sdp Type
// Output Value : None
//--------------------------------------------------
WORD ScalerDpMacStreamRxGetPpsElementInfo(EnumDpMacSel enumDpMacSel, EnumDpStreamPpsElement enumDpStreamPpsElement)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetPpsElementInfo(enumDpStreamPpsElement);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetPpsElementInfo(enumDpStreamPpsElement);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetPpsElementInfo(enumDpStreamPpsElement);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetPpsElementInfo(enumDpStreamPpsElement);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetPpsElementInfo(enumDpStreamPpsElement);

            break;
#endif

        default:

            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Check Dp Audio Straam VBID
// Input Value  : INPUT_PORT
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpMacStreamRxGetAudioStream(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetVbidInfo(_DP_VBID_AUDIO_STREAM);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetVbidInfo(_DP_VBID_AUDIO_STREAM);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetVbidInfo(_DP_VBID_AUDIO_STREAM);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetVbidInfo(_DP_VBID_AUDIO_STREAM);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetVbidInfo(_DP_VBID_AUDIO_STREAM);
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Mac Stream Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxStreamReset(EnumInputPort enumInputPort)
{
    // Disable DP Fifo Under/OverFlow Watch Dog
    ScalerDpMacStreamRxDisableFifoWD(enumInputPort);

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
    // Disable DP Color Sapace Change WD
    ScalerDpMacStreamRxSetColorSpaceChangeWD(enumInputPort, _DISABLE);

    // Disable DP Msa Change IRQ
    ScalerDpMacStreamRxSstSetMsaChangeIRQ(enumInputPort, _DISABLE);
#endif

    // Disable DP Fifo Under/OverFlow IRQ
    ScalerDpMacStreamRxDisableFifoIRQ(enumInputPort);

    // Disable DP No Video Stream IRQ
    ScalerDpMacStreamRxDisableNoVideoStreamIRQ(enumInputPort);

    // Disable DP BS Miss Detect IRQ
    ScalerDpMacStreamRxSetBsMissDetectIRQ(enumInputPort, _DISABLE);

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
    // Disable DP 8b10b Decoder Error WD
    ScalerDpMacDphyRxSet8b10bDecErrorWD(enumInputPort, _DISABLE);
#endif

    ScalerDpMacStreamRxStreamPreDetectReset(enumInputPort);

#if((_DP_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE) || (_DM_FUNCTION == _ON))
    // Disable DP RSV0 Ram Receive IRQ
    ScalerDpMacStreamRxSdpIrqEnable(enumInputPort, _DP_SDP_BUFF_RSV0, _DISABLE);
#endif
}

//--------------------------------------------------
// Description  : DP Pre Detect Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxStreamPreDetectReset(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0StreamPreDetectReset();
            ScalerDpMacStreamRx1StreamPreDetectReset();
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1StreamPreDetectReset();
            ScalerDpMacStreamRx2StreamPreDetectReset();
#endif
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Mac Stream Info Type
// Input Value  : enumDpMacStreamSourceType
// Output Value : None
//--------------------------------------------------
EnumDpStreamInfoType ScalerDpMacStreamRxGetStreamInfoType(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_STREAM_INFO_TYPE();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_STREAM_INFO_TYPE();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_STREAM_INFO_TYPE();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_STREAM_INFO_TYPE();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_STREAM_INFO_TYPE();
#endif

        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Set DP Mac Data Path
// Input Value  : enumDpMacStreamSourceType, enumDpStreamDataPath
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSetDataPath(EnumDpMacStreamSourceType enumMacSource, EnumDpStreamDataPath enumDpStreamDataPath)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            SET_DP_MAC_STREAM_RX0_STREAM_DATA_PATH(enumDpStreamDataPath);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            SET_DP_MAC_STREAM_RX1_STREAM_DATA_PATH(enumDpStreamDataPath);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            SET_DP_MAC_STREAM_RX2_STREAM_DATA_PATH(enumDpStreamDataPath);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            SET_DP_MAC_STREAM_RX3_STREAM_DATA_PATH(enumDpStreamDataPath);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            SET_DP_MAC_STREAM_RX4_STREAM_DATA_PATH(enumDpStreamDataPath);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Mac Data Path
// Input Value  : enumDpMacStreamSourceType
// Output Value : None
//--------------------------------------------------
EnumDpStreamDataPath ScalerDpMacStreamRxGetDataPath(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_STREAM_DATA_PATH();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_STREAM_DATA_PATH();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_STREAM_DATA_PATH();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_STREAM_DATA_PATH();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_STREAM_DATA_PATH();
#endif

        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Get DP Color Depth
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value : DP Color Depth
//--------------------------------------------------
WORD ScalerDpMacStreamRxGetColorDepthPreValue(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_COLOR_DEPTH_PREVALUE();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_COLOR_DEPTH_PREVALUE();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_COLOR_DEPTH_PREVALUE();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_COLOR_DEPTH_PREVALUE();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Get DP Content Type
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value : DP Color Depth
//--------------------------------------------------
WORD ScalerDpMacStreamRxGetContentType(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_CONTENT_TYPE();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_CONTENT_TYPE();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_CONTENT_TYPE();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_CONTENT_TYPE();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_CONTENT_TYPE();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Get DP Color Space
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value : DP Color Space
//--------------------------------------------------
WORD ScalerDpMacStreamRxGetColorSpacePreValue(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_COLOR_SPACE_PREVALUE();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_COLOR_SPACE_PREVALUE();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_COLOR_SPACE_PREVALUE();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_COLOR_SPACE_PREVALUE();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Get DP Colorimetry Change
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value : DP Colorimetry Change flag
//--------------------------------------------------
bit ScalerDpMacStreamRxGetColorimetryChange(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_COLORIMETRY_CHANGED();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_COLORIMETRY_CHANGED();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_COLORIMETRY_CHANGED();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_COLORIMETRY_CHANGED();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_COLORIMETRY_CHANGED();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Clr DP Colorimetry Change
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value :
//--------------------------------------------------
void ScalerDpMacStreamRxClrColorimetryChange(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            CLR_DP_MAC_STREAM_RX0_COLORIMETRY_CHANGED();
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            CLR_DP_MAC_STREAM_RX1_COLORIMETRY_CHANGED();
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            CLR_DP_MAC_STREAM_RX2_COLORIMETRY_CHANGED();
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            CLR_DP_MAC_STREAM_RX3_COLORIMETRY_CHANGED();
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            CLR_DP_MAC_STREAM_RX4_COLORIMETRY_CHANGED();
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Colorimetry Ext Change
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value : DP Colorimetry Change flag
//--------------------------------------------------
bit ScalerDpMacStreamRxGetColorimetryExtChange(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_COLORIMETRY_EXT_CHANGED();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_CHANGED();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_COLORIMETRY_EXT_CHANGED();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_COLORIMETRY_EXT_CHANGED();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_COLORIMETRY_EXT_CHANGED();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Clr DP Colorimetry Ext Change
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value :
//--------------------------------------------------
void ScalerDpMacStreamRxClrColorimetryExtChange(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            CLR_DP_MAC_STREAM_RX0_COLORIMETRY_EXT_CHANGED();
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            CLR_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_CHANGED();
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            CLR_DP_MAC_STREAM_RX2_COLORIMETRY_EXT_CHANGED();
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            CLR_DP_MAC_STREAM_RX3_COLORIMETRY_EXT_CHANGED();
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            CLR_DP_MAC_STREAM_RX4_COLORIMETRY_EXT_CHANGED();
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Quantization Change
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value : DP Quantization Change flag
//--------------------------------------------------
bit ScalerDpMacStreamRxGetQuantizationChange(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_QUANTIZATION_CHANGED();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_QUANTIZATION_CHANGED();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_QUANTIZATION_CHANGED();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_QUANTIZATION_CHANGED();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Clr DP Quantization Change
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value :
//--------------------------------------------------
void ScalerDpMacStreamRxClrQuantizationChange(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            CLR_DP_MAC_STREAM_RX0_QUANTIZATION_CHANGED();
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            CLR_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED();
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            CLR_DP_MAC_STREAM_RX2_QUANTIZATION_CHANGED();
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            CLR_DP_MAC_STREAM_RX3_QUANTIZATION_CHANGED();
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            CLR_DP_MAC_STREAM_RX4_QUANTIZATION_CHANGED();
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Color Space
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value : EnumColorSpace
//--------------------------------------------------
EnumColorSpace ScalerDpMacStreamRxGetColorSpace(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_COLOR_SPACE();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_COLOR_SPACE();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_COLOR_SPACE();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_COLOR_SPACE();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_COLOR_SPACE();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Get DP Color Depth
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value : BYTE
//--------------------------------------------------
BYTE ScalerDpMacStreamRxGetColorDepth(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_COLOR_DEPTH();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_COLOR_DEPTH();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_COLOR_DEPTH();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_COLOR_DEPTH();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_COLOR_DEPTH();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Get DP Colorimetry
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value : EnumColorimetry
//--------------------------------------------------
EnumColorimetry ScalerDpMacStreamRxGetColorimetry(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_COLORIMETRY();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_COLORIMETRY();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_COLORIMETRY();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_COLORIMETRY();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_COLORIMETRY();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Get DP EXT Colorimetry
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value : EnumColorimetryExt
//--------------------------------------------------
EnumColorimetryExt ScalerDpMacStreamRxGetExtColorimetry(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_EXT_COLORIMETRY();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_EXT_COLORIMETRY();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_EXT_COLORIMETRY();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_EXT_COLORIMETRY();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Get DP YCC Quantization Range
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value : EnumColorYCCQuantization
//--------------------------------------------------
EnumColorYCCQuantization ScalerDpMacStreamRxGetYCCQuantizationRange(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_COLOR_YCC_QUANTIZATION_RANGE();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_COLOR_YCC_QUANTIZATION_RANGE();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_COLOR_YCC_QUANTIZATION_RANGE();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_COLOR_YCC_QUANTIZATION_RANGE();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_COLOR_YCC_QUANTIZATION_RANGE();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Get DP RGB Quantization Range
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value : EnumColorRGBQuantization
//--------------------------------------------------
EnumColorRGBQuantization ScalerDpMacStreamRxGetRGBQuantizationRange(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_COLOR_RGB_QUANTIZATION_RANGE();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_COLOR_RGB_QUANTIZATION_RANGE();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_COLOR_RGB_QUANTIZATION_RANGE();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_COLOR_RGB_QUANTIZATION_RANGE();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_COLOR_RGB_QUANTIZATION_RANGE();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Get DP Pixel Clock
// Input Value  : None
// Output Value : DP Stream Clock(Unit is Hz)
//--------------------------------------------------
DWORD ScalerDpMacStreamRxGetPredectStreamClock(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_STREAM_CLOCK();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_STREAM_CLOCK();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_STREAM_CLOCK();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_STREAM_CLOCK();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_STREAM_CLOCK();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Get DP Native Pixel Clock
// Input Value  : None
// Output Value : DP Stream Clock(Unit is Hz)
//--------------------------------------------------
DWORD ScalerDpMacStreamRxGetNativePixelClock(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_NATIVE_PIXEL_CLOCK();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_NATIVE_PIXEL_CLOCK();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_NATIVE_PIXEL_CLOCK();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_NATIVE_PIXEL_CLOCK();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_NATIVE_PIXEL_CLOCK();
#endif
        default:

            break;
    }
    return 0;
}

//--------------------------------------------------
// Description  : Dp Stream Get Element
// Input Value  : EnumDpMacStreamSourceType EnumDpStreamElement
// Output Value : Conetent
//--------------------------------------------------
DWORD ScalerDpMacStreamRxGetElement(EnumDpMacStreamSourceType enumMacSource, EnumDpStreamElement enumElement)
{
    switch(enumElement)
    {
        case _COLOR_SPACE:
            return ScalerDpMacStreamRxGetColorSpace(enumMacSource);

        case _COLOR_DEPTH:
            return ScalerDpMacStreamRxGetColorDepth(enumMacSource);

        case _PIXEL_CLOCK:
            return ScalerDpMacStreamRxGetPredectStreamClock(enumMacSource);

        case _DSC_PPS_STATUS:
            return ScalerDpMacStreamRxGetSdpReceived(enumMacSource, _DP_SDP_TYPE_PPS);

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Check Corresponding DPRx Mac Tracking Status of DPTx Clone Port
// Input Value  : EnumInputPort
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxTrackingStatusCheck(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            if(ScalerGetBit(PB5_E0_VS_TRACK_EN, _BIT7) == _BIT7)
            {
                return _TRUE;
            }
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            if(ScalerGetBit(PB8_E0_VS_TRACK_EN, _BIT7) == _BIT7)
            {
                return _TRUE;
            }
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            if(ScalerGetBit(PC6_E0_VS_TRACK_EN, _BIT7) == _BIT7)
            {
                return _TRUE;
            }
            break;
#endif
#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            if(ScalerGetBit(PEE_E0_VS_TRACK_EN, _BIT7) == _BIT7)
            {
                return _TRUE;
            }
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            if(ScalerGetBit(PA_E0_VS_TRACK_EN, _BIT7) == _BIT7)
            {
                return _TRUE;
            }
            break;
#endif
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DPRx Mac Tracking Source
// Input Value  : EnumDpMacSel
// Output Value : DP MAC RX Tracking Source BS or BE
//--------------------------------------------------
EnumDpMacRxTrackingSource ScalerDpMacStreamRxGetTrackingSource(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            if(ScalerGetBit(PB5_EA_HS_TRACKING_NEW_MODE1, _BIT4) == _BIT4)
            {
                return _DP_MAC_RX_TRACKING_SOURCE_BE;
            }
            else
            {
                return _DP_MAC_RX_TRACKING_SOURCE_BS;
            }
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            if(ScalerGetBit(PB8_EA_HS_TRACKING_NEW_MODE1, _BIT4) == _BIT4)
            {
                return _DP_MAC_RX_TRACKING_SOURCE_BE;
            }
            else
            {
                return _DP_MAC_RX_TRACKING_SOURCE_BS;
            }
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            if(ScalerGetBit(PC6_EA_HS_TRACKING_NEW_MODE1, _BIT4) == _BIT4)
            {
                return _DP_MAC_RX_TRACKING_SOURCE_BE;
            }
            else
            {
                return _DP_MAC_RX_TRACKING_SOURCE_BS;
            }
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            if(ScalerGetBit(PEE_EA_HS_TRACKING_NEW_MODE1, _BIT4) == _BIT4)
            {
                return _DP_MAC_RX_TRACKING_SOURCE_BE;
            }
            else
            {
                return _DP_MAC_RX_TRACKING_SOURCE_BS;
            }
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            if(ScalerGetBit(PA_EA_HS_TRACKING_NEW_MODE1, _BIT4) == _BIT4)
            {
                return _DP_MAC_RX_TRACKING_SOURCE_BE;
            }
            else
            {
                return _DP_MAC_RX_TRACKING_SOURCE_BS;
            }
            break;
#endif
        default:
            break;
    }

    return _DP_MAC_RX_TRACKING_SOURCE_BS;
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerDpMacStreamRxPowerDataRecover(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SdpInitial();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx0SetSdpMetaSramRcvInitial();
#endif

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SdpInitial();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx1SetSdpMetaSramRcvInitial();
#endif

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SdpInitial();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx2SetSdpMetaSramRcvInitial();
#endif

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SdpInitial();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx3SetSdpMetaSramRcvInitial();
#endif

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
// Description  : DP HDCP Measure Check
// Input Value  : None
// Output Value : FALSE => Measure Check Fail
//--------------------------------------------------
bit ScalerDpMacStreamRxHdcpMeasureCheck(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0HdcpMeasureCheck();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1HdcpMeasureCheck();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2HdcpMeasureCheck();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Rx Source Type Judge Status
// Input Value  : EnumInputPort
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxGetSourceTypeJudgeStatus(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_SOURCE_TYPE_JUDGE();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_SOURCE_TYPE_JUDGE();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_SOURCE_TYPE_JUDGE();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_SOURCE_TYPE_JUDGE();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_SOURCE_TYPE_JUDGE();
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get Rx Source Type Judge Status
// Input Value  : None
// Output Value : FALSE => Measure Check Fail
//--------------------------------------------------
void ScalerDpMacStreamRxClrSourceTypeJudge(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            CLR_DP_MAC_STREAM_RX0_SOURCE_TYPE_JUDGE();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            CLR_DP_MAC_STREAM_RX1_SOURCE_TYPE_JUDGE();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            CLR_DP_MAC_STREAM_RX2_SOURCE_TYPE_JUDGE();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            CLR_DP_MAC_STREAM_RX3_SOURCE_TYPE_JUDGE();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            CLR_DP_MAC_STREAM_RX4_SOURCE_TYPE_JUDGE();

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : VBIOS MSA Check
// Input Value  : EnumInputPort
// Output Value : True or False
//--------------------------------------------------
bit ScalerDpMacStreamRxVbiosMsaCheck(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0VbiosMsaCheck();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1VbiosMsaCheck();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2VbiosMsaCheck();
#endif

        default:
            break;
    }

    return _FALSE;
}

#if(_DP_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current HDR Packet
// Input Value  : Input port, Rcv Var Pointer, Chg Var Pointer, Info Data Pointer
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxHDR10GetCurrentStatus(EnumInputPort enumInputPort, bit *pbHDRInfoReceive, BYTE *pucSdpInfoData)
{
    bit bInfoDataShift2Byte = _FALSE;
    BYTE ucShift = 31;

    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            *pbHDRInfoReceive = GET_DP_MAC_STREAM_RX0_HDR_INFO_FRAME_RECEIVED_STATE();

            ScalerDpMacStreamRx0GetSdpPktData(_DP_SDP_TYPE_INFOFRAME_HDR, pucSdpInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);

            // HB3[7:2]: Infoframe Version
            if(((ScalerDpMacStreamRx0GetSdpInfoHB3(_DP_SDP_TYPE_INFOFRAME_HDR) >> 2) == _INFOFRAME_SDP_VERSION_1_2) ||
               ((ScalerDpMacStreamRx0GetSdpInfoHB3(_DP_SDP_TYPE_INFOFRAME_HDR) >> 2) == _INFOFRAME_SDP_VERSION_1_1))
            {
                bInfoDataShift2Byte = _TRUE;
            }

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            *pbHDRInfoReceive = GET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_RECEIVED_STATE();

            ScalerDpMacStreamRx1GetSdpPktData(_DP_SDP_TYPE_INFOFRAME_HDR, pucSdpInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);

            // HB3[7:2]: Infoframe Version
            if(((ScalerDpMacStreamRx1GetSdpInfoHB3(_DP_SDP_TYPE_INFOFRAME_HDR) >> 2) == _INFOFRAME_SDP_VERSION_1_2) ||
               ((ScalerDpMacStreamRx1GetSdpInfoHB3(_DP_SDP_TYPE_INFOFRAME_HDR) >> 2) == _INFOFRAME_SDP_VERSION_1_1))
            {
                bInfoDataShift2Byte = _TRUE;
            }

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            *pbHDRInfoReceive = GET_DP_MAC_STREAM_RX2_HDR_INFO_FRAME_RECEIVED_STATE();

            ScalerDpMacStreamRx2GetSdpPktData(_DP_SDP_TYPE_INFOFRAME_HDR, pucSdpInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);

            // HB3[7:2]: Infoframe Version
            if(((ScalerDpMacStreamRx2GetSdpInfoHB3(_DP_SDP_TYPE_INFOFRAME_HDR) >> 2) == _INFOFRAME_SDP_VERSION_1_2) ||
               ((ScalerDpMacStreamRx2GetSdpInfoHB3(_DP_SDP_TYPE_INFOFRAME_HDR) >> 2) == _INFOFRAME_SDP_VERSION_1_1))
            {
                bInfoDataShift2Byte = _TRUE;
            }

            break;
#endif

        default:

            break;
    }

    if(bInfoDataShift2Byte == _TRUE)
    {
        for(ucShift = 31; ucShift >= 2; ucShift --)
        {
            pucSdpInfoData[ucShift] = pucSdpInfoData[ucShift - 2];
        }

        pucSdpInfoData[1] = 0x1A;
        pucSdpInfoData[0] = 0x01;
    }
}
#endif

#if((_DP_FREESYNC_II_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get Current FreeSyncII Packet
// Input Value  : Input port, Rcv Var Pointer, Chg Var Pointer, Info Data Pointer
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxFreeSyncIIGetCurrentStatus(EnumInputPort enumInputPort, BYTE *pucFreeSyncIIInfoReceive, BYTE *pucFreeSyncIIInfoChange, BYTE *pucSdpInfoData)
{
    bit bInfoDataShift2Byte = _FALSE;
    BYTE ucShift = 0;

    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            *pucFreeSyncIIInfoReceive = GET_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_RECEIVED_STATE();

            *pucFreeSyncIIInfoChange = GET_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_CHANGE();

            if(*pucFreeSyncIIInfoReceive == _SDP_STATE_RECEIVED)
            {
                ScalerDpMacStreamRx0GetSdpPktData(_DP_SDP_TYPE_INFOFRAME_SPD, pucSdpInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);

                // HB3[7:2]: Infoframe Version
                if(GET_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_VERSION() > _INFOFRAME_SDP_VERSION_1_2)
                {
                    bInfoDataShift2Byte = _TRUE;
                }
            }

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            *pucFreeSyncIIInfoReceive = GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE();

            *pucFreeSyncIIInfoChange = GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE();

            if(*pucFreeSyncIIInfoReceive == _SDP_STATE_RECEIVED)
            {
                ScalerDpMacStreamRx1GetSdpPktData(_DP_SDP_TYPE_INFOFRAME_SPD, pucSdpInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);

                // HB3[7:2]: Infoframe Version
                if(GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_VERSION() > _INFOFRAME_SDP_VERSION_1_2)
                {
                    bInfoDataShift2Byte = _TRUE;
                }
            }

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            *pucFreeSyncIIInfoReceive = GET_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_RECEIVED_STATE();

            *pucFreeSyncIIInfoChange = GET_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_CHANGE();

            if(*pucFreeSyncIIInfoReceive == _SDP_STATE_RECEIVED)
            {
                ScalerDpMacStreamRx2GetSdpPktData(_DP_SDP_TYPE_INFOFRAME_SPD, pucSdpInfoData, 0, _HW_DP_SDP_PAYLOAD_LENGTH);

                // HB3[7:2]: Infoframe Version
                if(GET_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_VERSION() > _INFOFRAME_SDP_VERSION_1_2)
                {
                    bInfoDataShift2Byte = _TRUE;
                }
            }

            break;
#endif

        default:

            break;
    }

    if(bInfoDataShift2Byte == _TRUE)
    {
        for(ucShift = 0; ucShift <= 29; ucShift ++)
        {
            pucSdpInfoData[ucShift] = pucSdpInfoData[ucShift + 2];
        }

        pucSdpInfoData[30] = 0x00;
        pucSdpInfoData[31] = 0x00;
    }
}
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DP Mac FreesyncEnable
// Input Value  : enumDpMacStreamSourceType
// Output Value : bENABLE
//--------------------------------------------------
bit ScalerDpMacStreamRxFreeSyncGetStreamConfig(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    EnumInputPort enumInputPort = ScalerDpMacStreamRxGetSourcePort(enumDpMacStreamSourceType);

#if(_DP_FORCE_FREESYNC_SUPPORT == _ON)
    return _TRUE;
#endif

    switch(enumDpMacStreamSourceType)
    {
        case _STREAM_SOURCE_D0_DP:
        case _STREAM_SOURCE_D1_DP:
        case _STREAM_SOURCE_D2_DP:
        {
#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
            EnumDpMstPort enumDpMstPort = ScalerDpMstRxDxPortNumMapping(enumInputPort);

            if((ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumDpMstPort) == _TRUE) && (ScalerDpRxGetSrcMstEnable(enumInputPort) == _TRUE))
            {
                return (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x01, 0x07, _BIT7) == _BIT7);
            }
            else
#endif
            {
                return ((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x07) & _BIT7) == _BIT7);
            }

            break;
        }

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _STREAM_SOURCE_PXP:
        {
#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
            EnumDpMstPort enumDpMstPort = ScalerDpMstRxDxPortNumMapping(_D9_INPUT_PORT);

            if(ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumDpMstPort) == _TRUE)
            {
                return (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x01, 0x07, _BIT7) == _BIT7);
            }
#endif

            break;
        }
#endif

#if(_DP_MST2SST_SUPPORT == _ON)
        case _STREAM_SOURCE_MST2SST:
        {
#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
            EnumDpMstPort enumDpMstPort = ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT);

            if(ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumDpMstPort) == _TRUE)
            {
                return (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x01, 0x07, _BIT7) == _BIT7);
            }
#endif

            break;
        }
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Input port, Content of Interest
// Output Value : Content Value
//--------------------------------------------------
DWORD ScalerDpMacStreamRxFreeSyncGetAmdSpdInfo(EnumInputPort enumInputPort, EnumAmdSpdInfoContent enumContent)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_AMD_SPD_INFO(enumContent);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_AMD_SPD_INFO(enumContent);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_AMD_SPD_INFO(enumContent);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_AMD_SPD_INFO(enumContent);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_AMD_SPD_INFO(enumContent);

            break;
#endif

        default:

            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get AMD SPD Info Receive
// Input Value  : Input port
// Output Value : Content Value
//--------------------------------------------------
bit ScalerDpMacStreamRxFreeSyncGetAmdSpdInfoReceive(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            if((GET_DP_MAC_STREAM_RX0_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE) && (GET_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_RECEIVED_STATE() == _SDP_STATE_RECEIVED))
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            if((GET_DP_MAC_STREAM_RX1_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE) && (GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE() == _SDP_STATE_RECEIVED))
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            if((GET_DP_MAC_STREAM_RX2_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE) && (GET_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_RECEIVED_STATE() == _SDP_STATE_RECEIVED))
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;
#endif


#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            if((GET_DP_MAC_STREAM_RX3_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE) && (GET_DP_MAC_STREAM_RX3_SPD_INFO_FRAME_RECEIVED_STATE() == _SDP_STATE_RECEIVED))
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;
#endif


#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            if((GET_DP_MAC_STREAM_RX4_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE) && (GET_DP_MAC_STREAM_RX4_SPD_INFO_FRAME_RECEIVED_STATE() == _SDP_STATE_RECEIVED))
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get MAC FreeSync Enable
// Input Value  : enumDpMacStreamSourceType
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxGetFreeSyncEnable(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumDpMacStreamSourceType))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_STREAM_FREESYNC_ENABLE();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_STREAM_FREESYNC_ENABLE();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_STREAM_FREESYNC_ENABLE();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_STREAM_FREESYNC_ENABLE();
#endif

        default:

            break;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Get Current DP H Period
// Input Value  : enumInputPort --> Source Search Port
// Output Value : H period in nano sec
//--------------------------------------------------
DWORD ScalerDpMacStreamRxGetHSPeriod(EnumInputPort enumInputPort)
{
#if(_DUAL_DP_SUPPORT == _ON)
    EnumDpMacSel enumDualDpMacSel = _DP_MAC_NONE;
#endif

    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_H_PERIOD();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_H_PERIOD();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_H_PERIOD();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_H_PERIOD();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_H_PERIOD();
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

            enumDualDpMacSel = ScalerDpRxGetMacSwitch(GET_DUAL_DP_PORT_SWITCH_SELECT());

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            if(enumDualDpMacSel == _DP_MAC_0)
            {
                return GET_DP_MAC_STREAM_RX0_H_PERIOD();
            }
            else
            {
                return GET_DP_MAC_STREAM_RX1_H_PERIOD();
            }
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            if(enumDualDpMacSel == _DP_MAC_1)
            {
                return GET_DP_MAC_STREAM_RX1_H_PERIOD();
            }
            else
            {
                return GET_DP_MAC_STREAM_RX2_H_PERIOD();
            }
#endif
            break;
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get Current DP H Sync Width
// Input Value  : enumInputPort --> Source Search Port
// Output Value : H Sync Width in pixel clk
//--------------------------------------------------
WORD ScalerDpMacStreamRxGetHSW(EnumInputPort enumInputPort)
{
    DWORD ulStreamClock = 0;

    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ulStreamClock = GET_DP_MAC_STREAM_RX0_STREAM_CLOCK() / 1000;

            if(ulStreamClock == 0x00)
            {
                return 0;
            }

            return ScalerGlobalComputeDwordMulDiv(GET_DP_MAC_STREAM_RX0_HSW(), _MEASURE_CLK, ulStreamClock);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ulStreamClock = GET_DP_MAC_STREAM_RX1_STREAM_CLOCK() / 1000;

            if(ulStreamClock == 0x00)
            {
                return 0;
            }

            return ScalerGlobalComputeDwordMulDiv(GET_DP_MAC_STREAM_RX1_HSW(), _MEASURE_CLK, ulStreamClock);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ulStreamClock = GET_DP_MAC_STREAM_RX2_STREAM_CLOCK() / 1000;

            if(ulStreamClock == 0x00)
            {
                return 0;
            }

            return ScalerGlobalComputeDwordMulDiv(GET_DP_MAC_STREAM_RX2_HSW(), _MEASURE_CLK, ulStreamClock);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ulStreamClock = GET_DP_MAC_STREAM_RX3_STREAM_CLOCK() / 1000;

            if(ulStreamClock == 0x00)
            {
                return 0;
            }

            return ScalerGlobalComputeDwordMulDiv(GET_DP_MAC_STREAM_RX3_HSW(), _MEASURE_CLK, ulStreamClock);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ulStreamClock = GET_DP_MAC_STREAM_RX4_STREAM_CLOCK() / 1000;

            if(ulStreamClock == 0x00)
            {
                return 0;
            }

            return ScalerGlobalComputeDwordMulDiv(GET_DP_MAC_STREAM_RX4_HSW(), _MEASURE_CLK, ulStreamClock);
#endif

#if(_DUAL_DP_SUPPORT == _ON)
#if((_DP_MAC_RX0_SUPPORT == _ON) && (_DP_MAC_RX1_SUPPORT == _ON))
        case _DP_MAC_DUAL:

            if(ScalerDpRxGetMacSwitch(GET_DUAL_DP_PORT_SWITCH_SELECT()) == _DP_MAC_0)
            {
                ulStreamClock = GET_DP_MAC_STREAM_RX0_STREAM_CLOCK() / 1000;

                if(ulStreamClock == 0x00)
                {
                    return 0;
                }

                return ScalerGlobalComputeDwordMulDiv(GET_DP_MAC_STREAM_RX0_HSW(), _MEASURE_CLK, ulStreamClock);
            }
            else
            {
                ulStreamClock = GET_DP_MAC_STREAM_RX1_STREAM_CLOCK() / 1000;

                if(ulStreamClock == 0x00)
                {
                    return 0;
                }

                return ScalerGlobalComputeDwordMulDiv(GET_DP_MAC_STREAM_RX1_HSW(), _MEASURE_CLK, ulStreamClock);
            }

            break;
#endif
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Dp Get Vfreq
// Input Value  : enumInputPort --> Source Search Port
// Output Value : VFreq in 0.1Hz
//--------------------------------------------------
WORD ScalerDpMacStreamRxGetVFreq(EnumInputPort enumInputPort)
{
#if(_DUAL_DP_SUPPORT == _ON)
    EnumDpMacSel enumDualDpMacSel = _DP_MAC_NONE;
#endif

    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_V_FREQ();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_V_FREQ();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_V_FREQ();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_V_FREQ();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_V_FREQ();
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

            enumDualDpMacSel = ScalerDpRxGetMacSwitch(GET_DUAL_DP_PORT_SWITCH_SELECT());

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            if(enumDualDpMacSel == _DP_MAC_0)
            {
                return GET_DP_MAC_STREAM_RX0_V_FREQ();
            }
            else
            {
                return GET_DP_MAC_STREAM_RX1_V_FREQ();
            }
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            if(enumDualDpMacSel == _DP_MAC_1)
            {
                return GET_DP_MAC_STREAM_RX1_V_FREQ();
            }
            else
            {
                return GET_DP_MAC_STREAM_RX2_V_FREQ();
            }
#endif
            break;
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get Current DP V Period
// Input Value  : enumInputPort --> Source Search Port
// Output Value : V period in line
//--------------------------------------------------
WORD ScalerDpMacStreamRxGetVSPeriod(EnumInputPort enumInputPort)
{
#if(_DUAL_DP_SUPPORT == _ON)
    EnumDpMacSel enumDualDpMacSel = _DP_MAC_NONE;
#endif

    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_V_PERIOD();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_V_PERIOD();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_V_PERIOD();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_V_PERIOD();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_V_PERIOD();
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

            enumDualDpMacSel = ScalerDpRxGetMacSwitch(GET_DUAL_DP_PORT_SWITCH_SELECT());

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            if(enumDualDpMacSel == _DP_MAC_0)
            {
                return GET_DP_MAC_STREAM_RX0_V_PERIOD();
            }
            else
            {
                return GET_DP_MAC_STREAM_RX1_V_PERIOD();
            }
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            if(enumDualDpMacSel == _DP_MAC_1)
            {
                return GET_DP_MAC_STREAM_RX1_V_PERIOD();
            }
            else
            {
                return GET_DP_MAC_STREAM_RX2_V_PERIOD();
            }
#endif
            break;
#endif

        default:
            break;
    }

    return 0;
}

#if((_DP_RX_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP DSC Flag Status
// Input Value  : enumDpMacStreamSourceType
// Output Value : _TRUE / _FALSE
//------------------------------------------------
bit ScalerDpMacStreamRxDscGetFlagStatus(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    EnumInputPort enumInputPort = ScalerDpMacStreamRxGetSourcePort(enumDpMacStreamSourceType);

    switch(enumDpMacStreamSourceType)
    {
        case _STREAM_SOURCE_D0_DP:
        case _STREAM_SOURCE_D1_DP:
        case _STREAM_SOURCE_D2_DP:
        {
            if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x60, _BIT0) == _BIT0) && (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x60, _BIT0) == _BIT0))
            {
                DebugMessageDSC("Dx DPCD DSC Flag Enable: DSC Decoder", (enumInputPort - _D0_INPUT_PORT));
                return _TRUE;
            }

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
            EnumDpMstPort enumDpMstPort = ScalerDpMstRxDxPortNumMapping(enumInputPort);

            if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumDpMstPort) == _ENABLE) &&
               (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x00, 0x60, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x01, 0x60, _BIT0) == _BIT0))
            {
                DebugMessageDSC("Dx V-DPCD DSC Flag Enable: DSC Decoder", (enumInputPort - _D0_INPUT_PORT));
                return _TRUE;
            }
#endif

            break;
        }

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _STREAM_SOURCE_PXP:
        {
#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
            EnumDpMstPort enumDpMstPort = ScalerDpMstRxDxPortNumMapping(_D9_INPUT_PORT);

            if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumDpMstPort) == _ENABLE) &&
               (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x00, 0x60, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x01, 0x60, _BIT0) == _BIT0))
            {
                DebugMessageDSC("PXP V-DPCD DSC Flag Enable: DSC Decoder", 0);
                return _TRUE;
            }
#endif

            break;
        }
#endif

#if(_DP_MST2SST_SUPPORT == _ON)
        case _STREAM_SOURCE_MST2SST:
        {
#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
            EnumDpMstPort enumDpMstPort = ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT);

            if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumDpMstPort) == _ENABLE))
            {
                if((ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x00, 0x60, _BIT0) == _BIT0) && (ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x01, 0x60, _BIT0) == _BIT0))
                {
                    DebugMessageDSC("MST2SST V-DPCD DSC Flag Enable: DSC Decoder", 0);
                    return _TRUE;
                }

                if(ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, enumDpMstPort, 0x00, 0x00, 0x60, _BIT1) == _BIT1)
                {
                    DebugMessageDSC("MST2SST V-DPCD DSC Flag Enable: DSC Bypass", 0);
                    return _TRUE;
                }
            }
#endif

            break;
        }
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Change Check
// Input Value  : None
// Output Value : False --> CompressionStream_Flag VB-ID[6] Changed and Video Stream without Compression
//--------------------------------------------------
bit ScalerDpMacStreamRxDscStreamChangeCheck(EnumDpMacSel enumDpMacSel)
{
    switch(enumDpMacSel)
    {
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            return ScalerDpMacStreamRx0DscStreamChangeCheck();
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            return ScalerDpMacStreamRx1DscStreamChangeCheck();
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            return ScalerDpMacStreamRx2DscStreamChangeCheck();
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            return ScalerDpMacStreamRx3DscStreamChangeCheck();
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
            return ScalerDpMacStreamRx4DscStreamChangeCheck();
            break;
#endif
#endif

        default:
            break;
    }

    return _FALSE;
}
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] IRQ and Watch Dog
// Input Value  : enumInputPort, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxDscSetStreamIRQAndWD(EnumInputPort enumInputPort, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Before IRQ is enabled, set the WD flag and write 1 to clear it to avoid getting stuck on INT
        ScalerDpMacStreamRxDscSetStreamWD(enumInputPort, bEnable);

        ScalerDpMacStreamRxDscSetStreamIRQ(enumInputPort, bEnable);
    }
    else
    {
        ScalerDpMacStreamRxDscSetStreamIRQ(enumInputPort, bEnable);

        // After IRQ is disabled, set the WD flag and write 1 to clear it to avoid getting stuck on INT
        ScalerDpMacStreamRxDscSetStreamWD(enumInputPort, bEnable);
    }
}

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] Watch Dog
// Input Value  : enumInputPort, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxDscSetStreamWD(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx0DscSetStreamWD(enumInputPort, bEnable);
#endif
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx1DscSetStreamWD(enumInputPort, bEnable);
#endif
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx2DscSetStreamWD(enumInputPort, bEnable);
#endif
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
#if(_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx3DscSetStreamWD(enumInputPort, bEnable);
#endif
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
#if(_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx4DscSetStreamWD(enumInputPort, bEnable);
#endif
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : CompressionStream_Flag VB-ID[6] IRQ
// Input Value  : enumInputPort, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxDscSetStreamIRQ(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx0DscSetStreamIRQ(enumInputPort, bEnable);
#endif
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx1DscSetStreamIRQ(enumInputPort, bEnable);
#endif
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx2DscSetStreamIRQ(enumInputPort, bEnable);
#endif
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
#if(_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx3DscSetStreamIRQ(enumInputPort, bEnable);
#endif
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
#if(_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
            ScalerDpMacStreamRx4DscSetStreamIRQ(enumInputPort, bEnable);
#endif
            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get Current DP H Width
// Input Value  : enumInputPort --> Source Search Port
// Output Value : H Width
//--------------------------------------------------
WORD ScalerDpMacStreamRxGetHwidth(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetDisplayFormat(_DP_H_WIDTH);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetDisplayFormat(_DP_H_WIDTH);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetDisplayFormat(_DP_H_WIDTH);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetDisplayFormat(_DP_H_WIDTH);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetDisplayFormat(_DP_H_WIDTH);
#endif

        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            return (ScalerDpMacStreamRx0GetDisplayFormat(_DP_H_WIDTH) + ScalerDpMacStreamRx1GetDisplayFormat(_DP_H_WIDTH));
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            return (ScalerDpMacStreamRx1GetDisplayFormat(_DP_H_WIDTH) + ScalerDpMacStreamRx2GetDisplayFormat(_DP_H_WIDTH));
#endif
        default:

            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get Current DP V Height
// Input Value  : enumInputPort --> Source Search Port
// Output Value : V Height
//--------------------------------------------------
WORD ScalerDpMacStreamRxGetVheight(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetDisplayFormat(_DP_V_HEIGHT);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetDisplayFormat(_DP_V_HEIGHT);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetDisplayFormat(_DP_V_HEIGHT);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetDisplayFormat(_DP_V_HEIGHT);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetDisplayFormat(_DP_V_HEIGHT);
#endif

        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            return ScalerDpMacStreamRx0GetDisplayFormat(_DP_V_HEIGHT);
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            return ScalerDpMacStreamRx1GetDisplayFormat(_DP_V_HEIGHT);
#endif
        default:

            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get Current DP H Start
// Input Value  : enumInputPort --> Source Search Port
// Output Value : H Start
//--------------------------------------------------
WORD ScalerDpMacStreamRxGetHstart(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetDisplayFormat(_DP_H_START);
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetDisplayFormat(_DP_H_START);
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetDisplayFormat(_DP_H_START);
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetDisplayFormat(_DP_H_START);
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetDisplayFormat(_DP_H_START);
#endif

        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            return (ScalerDpMacStreamRx0GetDisplayFormat(_DP_H_START) + ScalerDpMacStreamRx1GetDisplayFormat(_DP_H_START));
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            return (ScalerDpMacStreamRx1GetDisplayFormat(_DP_H_START) + ScalerDpMacStreamRx2GetDisplayFormat(_DP_H_START));
#endif
        default:

            break;
    }

    return 0;
}

#if(_3DDI_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get 3DDI available
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxGetInterlace3ddiAvaible(StructDpInfo *pstDpInfo)
{
    DWORD ul3DDIPixelClockLimit = ((DWORD)_3DDI_PCLK_LIMIT * 1000);

    // 3DDI Check for 2x clk from Mac
    if((pstDpInfo->stDpLinkInfo.b1InterlaceStatus == _TRUE) &&
       (pstDpInfo->stDpLinkInfo.ulStreamClockHz < ul3DDIPixelClockLimit))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Aux Rx PR Mode DPCD Setting
// Input Value  : None
// Output Value : None
//-----------------------------------------------
bit ScalerDpMacStreamRxPRModeFlagStatus(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    EnumInputPort enumInputPort = ScalerDpMacStreamRxGetSourcePort(enumDpMacStreamSourceType);

    switch(enumDpMacStreamSourceType)
    {
        case _STREAM_SOURCE_D0_DP:
        case _STREAM_SOURCE_D1_DP:
        case _STREAM_SOURCE_D2_DP:

            return ScalerDpAuxRxPRModeFlagStatus(enumInputPort);

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _STREAM_SOURCE_PXP:

            break;
#endif

#if(_DP_MST2SST_SUPPORT == _ON)
        case _STREAM_SOURCE_MST2SST:

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get MAC FreeSync Enable
// Input Value  : enumDpMacStreamSourceType
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxGetPRModeEnable(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    EnumInputPort enumInputPort = ScalerDpMacStreamRxGetSourcePort(enumDpMacStreamSourceType);

    enumInputPort = enumInputPort;

    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumDpMacStreamSourceType))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_STREAM_RX0_PR_ENABLE_128B132B();
            }
            else
#endif
            {
                return GET_DP_MAC_STREAM_RX0_PR_ENABLE_8B10B();
            }

#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_STREAM_RX1_PR_ENABLE_128B132B();
            }
            else
#endif
            {
                return GET_DP_MAC_STREAM_RX1_PR_ENABLE_8B10B();
            }

#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_STREAM_RX2_PR_ENABLE_128B132B();
            }
            else
#endif
            {
                return GET_DP_MAC_STREAM_RX2_PR_ENABLE_8B10B();
            }

#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_STREAM_RX3_PR_ENABLE_128B132B();
            }
            else
#endif
            {
                return GET_DP_MAC_STREAM_RX3_PR_ENABLE_8B10B();
            }

#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_STREAM_RX4_PR_ENABLE_128B132B();
            }
            else
#endif
            {
                return GET_DP_MAC_STREAM_RX4_PR_ENABLE_8B10B();
            }

#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check DP PR Enable Change
// Input Value  : enumInputPort
// Output Value : True: PR Change
//--------------------------------------------------
bit ScalerDpMacStreamRxPRModeGetFlagChange(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    if(ScalerDpMacStreamRxPRModeFlagStatus(enumDpMacStreamSourceType) != ScalerDpMacStreamRxGetPRModeEnable(enumDpMacStreamSourceType))
    {
        DebugMessageDpRx("7.PR Mode Enable Change", 0);
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : PR Mode SDP Reset
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxPRModeSdpReset(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0PRModeSdpReset();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1PRModeSdpReset();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2PRModeSdpReset();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3PRModeSdpReset();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4PRModeSdpReset();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Mac Rx PR Mode Check Process
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxPRModeCheckProc(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0PRModeCheckProc(enumInputPort);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1PRModeCheckProc(enumInputPort);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2PRModeCheckProc(enumInputPort);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3PRModeCheckProc(enumInputPort);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4PRModeCheckProc(enumInputPort);

            break;
#endif

        default:

            break;
    }
}
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Mac Rx ALPM Enable
// Input Value  : enumDpMacStreamSourceType
// Output Value : ALPM Enable
//--------------------------------------------------
bit ScalerDpMacStreamRxGetAuxlessAlpmEnable(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumDpMacStreamSourceType))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_ALPM_ENABLE();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_ALPM_ENABLE();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_ALPM_ENABLE();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_ALPM_ENABLE();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_ALPM_ENABLE();
#endif

        default:
            return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : Get DP Info Pointer
// Input Value  : EnumDpMacStreamSourceTyp
// Output Value : StructDpInfo*
//--------------------------------------------------
StructDpInfo *ScalerDpMacStreamRxGetDpInfoPointer(EnumDpMacStreamSourceType enumMacSource)
{
    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumMacSource))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return &g_stDpMacStreamRx0Info;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return &g_stDpMacStreamRx1Info;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return &g_stDpMacStreamRx2Info;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return &g_stDpMacStreamRx3Info;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return &g_stDpMacStreamRx4Info;
#endif
        default:

            break;
    }

    return _NULL_POINTER;
}

//--------------------------------------------------
// Description  : DP Sec Data Reset
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSecDataReset(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)

        case _DP_MAC_0:

            ScalerDpMacStreamRx0SecDataBlockReset();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx0SdpMetaSramReset();
#endif

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)

        case _DP_MAC_1:

            ScalerDpMacStreamRx1SecDataBlockReset();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx1SdpMetaSramReset();
#endif

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)

        case _DP_MAC_2:

            ScalerDpMacStreamRx2SecDataBlockReset();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx2SdpMetaSramReset();
#endif

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)

        case _DP_MAC_3:

            ScalerDpMacStreamRx3SecDataBlockReset();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx3SdpMetaSramReset();
#endif

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)

        case _DP_MAC_4:

            ScalerDpMacStreamRx4SecDataBlockReset();

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)

        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0SecDataBlockReset();
            ScalerDpMacStreamRx1SecDataBlockReset();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx0SdpMetaSramReset();
            ScalerDpMacStreamRx1SdpMetaSramReset();
#endif

#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1SecDataBlockReset();
            ScalerDpMacStreamRx2SecDataBlockReset();

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
            ScalerDpMacStreamRx1SdpMetaSramReset();
            ScalerDpMacStreamRx2SdpMetaSramReset();
#endif
#endif
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Mac Rx Sink Status Setting
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSinkStatusSetting(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)

        case _DP_MAC_0:

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                if(ScalerGetBit(P1B_3B_DP_IRQ_CTRL1, _BIT4) == 0x00)
                {
                    // Enable DP No Video Stream IRQ
                    ScalerDpMacStreamRx0SetNoVideoStreamIRQ(_ENABLE);
                }
            }
            else
#endif
            {
                if(ScalerGetBit(PB6_3F_DP_IRQ_CTRL1, _BIT4) == 0x00)
                {
                    // Enable DP No Video Stream IRQ
                    ScalerDpMacStreamRx0SetNoVideoStreamIRQ(_ENABLE);
                }
            }
            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)

        case _DP_MAC_1:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                if(ScalerGetBit(P75_3B_DP_IRQ_CTRL1, _BIT4) == 0x00)
                {
                    // Enable DP No Video Stream IRQ
                    ScalerDpMacStreamRx1SetNoVideoStreamIRQ(_ENABLE);
                }
            }
            else
#endif
            {
                if(ScalerGetBit(PB9_3F_DP_IRQ_CTRL1, _BIT4) == 0x00)
                {
                    // Enable DP No Video Stream IRQ
                    ScalerDpMacStreamRx1SetNoVideoStreamIRQ(_ENABLE);
                }
            }
            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)

        case _DP_MAC_2:

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                if(ScalerGetBit(PD4_3B_DP_IRQ_CTRL1, _BIT4) == 0x00)
                {
                    // Enable DP No Video Stream IRQ
                    ScalerDpMacStreamRx2SetNoVideoStreamIRQ(_ENABLE);
                }
            }
            else
#endif
            {
                if(ScalerGetBit(PC7_3F_DP_IRQ_CTRL1, _BIT4) == 0x00)
                {
                    // Enable DP No Video Stream IRQ
                    ScalerDpMacStreamRx2SetNoVideoStreamIRQ(_ENABLE);
                }
            }
            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)

        case _DP_MAC_3:

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                if(ScalerGetBit(PF2_3B_DP_IRQ_CTRL1, _BIT4) == 0x00)
                {
                    // Enable DP No Video Stream IRQ
                    ScalerDpMacStreamRx3SetNoVideoStreamIRQ(_ENABLE);
                }
            }
            else
#endif
            {
                if(ScalerGetBit(PEF_3F_DP_IRQ_CTRL1, _BIT4) == 0x00)
                {
                    // Enable DP No Video Stream IRQ
                    ScalerDpMacStreamRx3SetNoVideoStreamIRQ(_ENABLE);
                }
            }
            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)

        case _DP_MAC_4:

#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                if(ScalerGetBit(PE1_3B_DP_IRQ_CTRL1, _BIT4) == 0x00)
                {
                    // Enable DP No Video Stream IRQ
                    ScalerDpMacStreamRx4SetNoVideoStreamIRQ(_ENABLE);
                }
            }
            else
#endif
            {
                if(ScalerGetBit(P35_3F_DP_IRQ_CTRL1, _BIT4) == 0x00)
                {
                    // Enable DP No Video Stream IRQ
                    ScalerDpMacStreamRx4SetNoVideoStreamIRQ(_ENABLE);
                }
            }
            break;
#endif

        default:

            break;
    }

    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x02, 0x05, _BIT0) == 0x00)
    {
        // Set DP Receive Port0 In Sync
        ScalerDpAuxRxSinkStatusSet(enumInputPort, _DP_SINK_REVEICE_PORT0, _DP_SINK_IN_SYNC);
    }
}

//--------------------------------------------------
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
EnumSourceType ScalerDpMacStreamRxScanInputPort(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
    EnumSourceType enumSourceType = _SOURCE_NONE;

#if(_DUAL_DP_SUPPORT == _ON)
    EnumDpMacSel enumDualDpMacSel = _DP_MAC_NONE;
    EnumDpMacSel enumDpMacSelMain = _DP_MAC_NONE;
    EnumDpMacSel enumDpMacSelSub = _DP_MAC_NONE;
#endif

    enumPortType = enumPortType;

    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

            enumDualDpMacSel = ScalerDpRxGetMacSwitch(GET_DUAL_DP_PORT_SWITCH_SELECT());
            enumDpMacSelMain = ScalerDpRxGetMacSwitch(_DUAL_DP_MAIN_PORT);
            enumDpMacSelSub = ScalerDpRxGetMacSwitch(_DUAL_DP_SUB_PORT);

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            switch(enumDualDpMacSel)
            {
                case _DP_MAC_0:

                    if(ScalerDpMacStreamRx0ScanInputPort() != _SOURCE_DP)
                    {
                        return _SOURCE_NONE;
                    }
                    break;

                case _DP_MAC_1:

                    if(ScalerDpMacStreamRx1ScanInputPort() != _SOURCE_DP)
                    {
                        return _SOURCE_NONE;
                    }
                    break;

                default:
                case _DP_MAC_DUAL:

                    // Check main port first
                    if(((enumDpMacSelMain == _DP_MAC_0) && (ScalerDpMacStreamRx0ScanInputPort() != _SOURCE_DP)) ||
                       ((enumDpMacSelMain == _DP_MAC_1) && (ScalerDpMacStreamRx1ScanInputPort() != _SOURCE_DP)))
                    {
#if(_DUAL_DP_SEARCH_MAIN_PORT_ONLY == _OFF)
                        // Check sub port when main failed
                        if(((enumDpMacSelSub == _DP_MAC_0) && (ScalerDpMacStreamRx0ScanInputPort() == _SOURCE_DP)) ||
                           ((enumDpMacSelSub == _DP_MAC_1) && (ScalerDpMacStreamRx1ScanInputPort() == _SOURCE_DP)))
                        {
                            SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_SUB_PORT);
                            break;
                        }
#endif
                        return _SOURCE_NONE;
                    }
                    else
                    {
#if(_DUAL_DP_SEARCH_MAIN_PORT_ONLY == _ON)
                        if(ScalerSyncDualDpDoubleCheck(_DUAL_DP_MAIN_PORT) == _TRUE)
                        {
                            // Switch back to main port when valid
                            SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_MAIN_PORT);
                            break;
                        }
#endif

                        // Check sub port when main passed
                        if(((enumDpMacSelSub == _DP_MAC_0) && (ScalerDpMacStreamRx0ScanInputPort() != _SOURCE_DP)) ||
                           ((enumDpMacSelSub == _DP_MAC_1) && (ScalerDpMacStreamRx1ScanInputPort() != _SOURCE_DP)))
                        {
#if(_DUAL_DP_SEARCH_MAIN_PORT_ONLY == _OFF)
                            SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_MAIN_PORT);
#else
                            return _SOURCE_NONE;
#endif
                        }
                    }

                    break;
            }

#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            switch(enumDualDpMacSel)
            {
                case _DP_MAC_1:

                    if(ScalerDpMacStreamRx1ScanInputPort() != _SOURCE_DP)
                    {
                        return _SOURCE_NONE;
                    }
                    break;

                case _DP_MAC_2:

                    if(ScalerDpMacStreamRx2ScanInputPort() != _SOURCE_DP)
                    {
                        return _SOURCE_NONE;
                    }
                    break;

                default:
                case _DP_MAC_DUAL:

                    // Check main port first
                    if(((enumDpMacSelMain == _DP_MAC_1) && (ScalerDpMacStreamRx1ScanInputPort() != _SOURCE_DP)) ||
                       ((enumDpMacSelMain == _DP_MAC_2) && (ScalerDpMacStreamRx2ScanInputPort() != _SOURCE_DP)))
                    {
#if(_DUAL_DP_SEARCH_MAIN_PORT_ONLY == _OFF)
                        // Check sub port when main failed
                        if(((enumDpMacSelSub == _DP_MAC_1) && (ScalerDpMacStreamRx1ScanInputPort() == _SOURCE_DP)) ||
                           ((enumDpMacSelSub == _DP_MAC_2) && (ScalerDpMacStreamRx2ScanInputPort() == _SOURCE_DP)))
                        {
                            SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_SUB_PORT);
                            break;
                        }
#endif
                        return _SOURCE_NONE;
                    }
                    else
                    {
#if(_DUAL_DP_SEARCH_MAIN_PORT_ONLY == _ON)
                        if(ScalerSyncDualDpDoubleCheck(_DUAL_DP_MAIN_PORT) == _TRUE)
                        {
                            // Switch back to main port when valid
                            SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_MAIN_PORT);
                            break;
                        }
#endif

                        // Check sub port when main passed
                        if(((enumDpMacSelSub == _DP_MAC_1) && (ScalerDpMacStreamRx1ScanInputPort() != _SOURCE_DP)) ||
                           ((enumDpMacSelSub == _DP_MAC_2) && (ScalerDpMacStreamRx2ScanInputPort() != _SOURCE_DP)))
                        {
#if(_DUAL_DP_SEARCH_MAIN_PORT_ONLY == _OFF)
                            SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_MAIN_PORT);
#else
                            return _SOURCE_NONE;
#endif
                        }
                    }

                    break;
            }
#endif
            // Check dual DP resolution
            if(ScalerSyncDualDpDoubleCheck(GET_DUAL_DP_PORT_SWITCH_SELECT()) == _TRUE)
            {
                ScalerDpRxStreamExternInfoSetting(_DUAL_DP_MAIN_PORT);
                ScalerDpRxStreamExternInfoSetting(_DUAL_DP_SUB_PORT);

                ScalerDpRxStreamAfterJudgeSetting(_DUAL_DP_MAIN_PORT);
                ScalerDpRxStreamAfterJudgeSetting(_DUAL_DP_SUB_PORT);

                return _SOURCE_DP;
            }

            break;
#endif

        default:

            break;
    }

    if(enumSourceType == _SOURCE_DP)
    {
        // DP Extern Info Setting For Other IP to Use
        ScalerDpRxStreamExternInfoSetting(enumInputPort);

        // DP Inner Info Setting After DP Rx Stream Judge
        ScalerDpRxStreamAfterJudgeSetting(enumInputPort);

        return _SOURCE_DP;
    }

    return _SOURCE_NONE;
}

//--------------------------------------------------
// Description  : On Line Check DP stability
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerDpMacStreamRxStableDetect(EnumInputPort enumInputPort, EnumSourceType enumSourceType)
{
#if(_DUAL_DP_SUPPORT == _ON)
    EnumDpMacSel enumDualDpMacSel = _DP_MAC_NONE;
#endif

    enumSourceType = enumSourceType;

    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)

        case _DP_MAC_0:

            return ScalerDpMacStreamRx0StableDetect();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1StableDetect();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)

        case _DP_MAC_2:

            return ScalerDpMacStreamRx2StableDetect();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)

        case _DP_MAC_3:

            return ScalerDpMacStreamRx3StableDetect();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)

        case _DP_MAC_4:

            return ScalerDpMacStreamRx4StableDetect();
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

            enumDualDpMacSel = ScalerDpRxGetMacSwitch(GET_DUAL_DP_PORT_SWITCH_SELECT());

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            switch(enumDualDpMacSel)
            {
                case _DP_MAC_0:
                    return ScalerDpMacStreamRx0StableDetect();
                case _DP_MAC_1:
                    return ScalerDpMacStreamRx1StableDetect();

                default:
                    return ((ScalerDpMacStreamRx0StableDetect() == _TRUE) &&
                            (ScalerDpMacStreamRx1StableDetect() == _TRUE));
            }
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            switch(enumDualDpMacSel)
            {
                case _DP_MAC_1:
                    return ScalerDpMacStreamRx1StableDetect();
                case _DP_MAC_2:
                    return ScalerDpMacStreamRx2StableDetect();

                default:
                    return ((ScalerDpMacStreamRx1StableDetect() == _TRUE) &&
                            (ScalerDpMacStreamRx2StableDetect() == _TRUE));
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
// Description  : Enable DP BS Miss Detect IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSetBsMissDetectIRQ(EnumInputPort enumInputPort, bit bEn)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0SetBsMissDetectIRQ(bEn);
            ScalerDpMacStreamRx1SetBsMissDetectIRQ(bEn);
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1SetBsMissDetectIRQ(bEn);
            ScalerDpMacStreamRx2SetBsMissDetectIRQ(bEn);
#endif
            break;
#endif

        default:

            break;
    }
}

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Calculate Bs Miss Detect Period
// Input Value  : StructDpInfo(usHBsToBsCount/ulLinkClockHz)
// Output Value : Bs Miss Detect Period Value(WORD)
//--------------------------------------------------
WORD ScalerDpMacStreamRxBsMissDetectPeriodCalculate(StructDpInfo *pstDpInfo)
{
    WORD usHTotalCount = 0;

    // Convert HTotal Count from 1/2 Link Clk to GDI Clk
    usHTotalCount = ((DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount * _GDIPHY_RX_GDI_CLK_KHZ * 2 + ((pstDpInfo->stDpLinkInfo.ulLinkClockHz / 1000) >> 1)) / (pstDpInfo->stDpLinkInfo.ulLinkClockHz / 1000);

    // Set Bs Miss Detect Period = 4 lines
    return (usHTotalCount * 4);
}

//--------------------------------------------------
// Description  : Set Bs Miss Detect Period
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSetBsMissDetectPeriod(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SetBsMissDetectPeriod(&g_stDpMacStreamRx0Info);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SetBsMissDetectPeriod(&g_stDpMacStreamRx1Info);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SetBsMissDetectPeriod(&g_stDpMacStreamRx2Info);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SetBsMissDetectPeriod(&g_stDpMacStreamRx3Info);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SetBsMissDetectPeriod(&g_stDpMacStreamRx4Info);

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0SetBsMissDetectPeriod(&g_stDpMacStreamRx0Info);
            ScalerDpMacStreamRx1SetBsMissDetectPeriod(&g_stDpMacStreamRx1Info);
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1SetBsMissDetectPeriod(&g_stDpMacStreamRx1Info);
            ScalerDpMacStreamRx2SetBsMissDetectPeriod(&g_stDpMacStreamRx2Info);
#endif
            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSetFifoIRQ(EnumInputPort enumInputPort, bit bEn)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SetFifoIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SetFifoIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SetFifoIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SetFifoIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SetFifoIRQ(bEn);

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0SetFifoIRQ(bEn);
            ScalerDpMacStreamRx1SetFifoIRQ(bEn);
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1SetFifoIRQ(bEn);
            ScalerDpMacStreamRx2SetFifoIRQ(bEn);
#endif
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Disable DP Fifo Under/OverFlow IRQ
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxDisableFifoIRQ(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0DisableFifoIRQ();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1DisableFifoIRQ();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2DisableFifoIRQ();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3DisableFifoIRQ();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4DisableFifoIRQ();

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0DisableFifoIRQ();
            ScalerDpMacStreamRx1DisableFifoIRQ();
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1DisableFifoIRQ();
            ScalerDpMacStreamRx2DisableFifoIRQ();
#endif
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow Watch Dog
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSetFifoWD(EnumInputPort enumInputPort, bit bEn)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0SetFifoWD(bEn);
            ScalerDpMacStreamRx1SetFifoWD(bEn);
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1SetFifoWD(bEn);
            ScalerDpMacStreamRx2SetFifoWD(bEn);
#endif
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Disable DP Fifo Under/OverFlow Watch Dog
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxDisableFifoWD(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0DisableFifoWD();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1DisableFifoWD();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2DisableFifoWD();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3DisableFifoWD();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4DisableFifoWD();

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0DisableFifoWD();
            ScalerDpMacStreamRx1DisableFifoWD();
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1DisableFifoWD();
            ScalerDpMacStreamRx2DisableFifoWD();
#endif
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Enable/Disable SDP IRQ_en
// Input Value  : EnumInputPort, RSV Number, ENABLE/DISABLE bit
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSdpIrqEnable(EnumInputPort enumInputPort, EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SdpIrqEnable(enumDpSdpRamIndex, bEnable);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SdpIrqEnable(enumDpSdpRamIndex, bEnable);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SdpIrqEnable(enumDpSdpRamIndex, bEnable);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SdpIrqEnable(enumDpSdpRamIndex, bEnable);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SdpIrqEnable(enumDpSdpRamIndex, bEnable);

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0SdpIrqEnable(enumDpSdpRamIndex, bEnable);
            ScalerDpMacStreamRx1SdpIrqEnable(enumDpSdpRamIndex, bEnable);
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1SdpIrqEnable(enumDpSdpRamIndex, bEnable);
            ScalerDpMacStreamRx2SdpIrqEnable(enumDpSdpRamIndex, bEnable);
#endif
            break;

#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Fifo Watch Dog Enable Status
// Input Value  : None
// Output Value : _TRUE/ _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxGetFifoWDStatus(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetFifoWDStatus();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetFifoWDStatus();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetFifoWDStatus();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetFifoWDStatus();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetFifoWDStatus();
#endif

        default:

            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Check DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRxCheckNoVideoStreamIRQStatus(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_STREAM_RX0_NO_VIDEO_IRQ_STATUS_128B132B();
            }
            else
#endif
            {
                return GET_DP_MAC_STREAM_RX0_NO_VIDEO_IRQ_STATUS_8B10B();
            }
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_STREAM_RX1_NO_VIDEO_IRQ_STATUS_128B132B();
            }
            else
#endif
            {
                return GET_DP_MAC_STREAM_RX1_NO_VIDEO_IRQ_STATUS_8B10B();
            }
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_STREAM_RX2_NO_VIDEO_IRQ_STATUS_128B132B();
            }
            else
#endif
            {
                return GET_DP_MAC_STREAM_RX2_NO_VIDEO_IRQ_STATUS_8B10B();
            }
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_STREAM_RX3_NO_VIDEO_IRQ_STATUS_128B132B();
            }
            else
#endif
            {
                return GET_DP_MAC_STREAM_RX3_NO_VIDEO_IRQ_STATUS_8B10B();
            }
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_STREAM_RX4_NO_VIDEO_IRQ_STATUS_128B132B();
            }
            else
#endif
            {
                return GET_DP_MAC_STREAM_RX4_NO_VIDEO_IRQ_STATUS_8B10B();
            }
#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSetNoVideoStreamIRQ(EnumInputPort enumInputPort, bit bEn)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SetNoVideoStreamIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SetNoVideoStreamIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SetNoVideoStreamIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SetNoVideoStreamIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SetNoVideoStreamIRQ(bEn);

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0SetNoVideoStreamIRQ(bEn);
            ScalerDpMacStreamRx1SetNoVideoStreamIRQ(bEn);
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1SetNoVideoStreamIRQ(bEn);
            ScalerDpMacStreamRx2SetNoVideoStreamIRQ(bEn);
#endif
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Disable DP Fifo Under/OverFlow IRQ
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxDisableNoVideoStreamIRQ(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0DisableNoVideoStreamIRQ();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1DisableNoVideoStreamIRQ();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2DisableNoVideoStreamIRQ();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3DisableNoVideoStreamIRQ();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4DisableNoVideoStreamIRQ();

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0DisableNoVideoStreamIRQ();
            ScalerDpMacStreamRx1DisableNoVideoStreamIRQ();
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1DisableNoVideoStreamIRQ();
            ScalerDpMacStreamRx2DisableNoVideoStreamIRQ();
#endif
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Set Color Info Macros
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMacStreamRxGetQuantizationPreValue(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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
// Description : check Bs Status
// Input Value  : enumInputPort
// Output Value : _UNSTABLE or _STABLE
//--------------------------------------------------
bit ScalerDpMacStreamRxBsMissCheck(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    bit bReturn = _UNSTABLE;

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpMacStreamRxGetSourcePort(enumDpMacStreamSourceType);

    ScalerDpMacDphyRxAuxlessAlpmClrOccurred(enumInputPort);
#endif

    switch(ScalerDpRxGetMacSwitchMappingSourceType(enumDpMacStreamSourceType))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            bReturn = ScalerDpMacStreamRx0BsMissCheck();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            bReturn = ScalerDpMacStreamRx1BsMissCheck();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            bReturn = ScalerDpMacStreamRx2BsMissCheck();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            bReturn = ScalerDpMacStreamRx3BsMissCheck();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            bReturn = ScalerDpMacStreamRx4BsMissCheck();

            break;
#endif

        default:
            break;
    }

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(ScalerDpMacDphyRxAuxlessAlpmGetOccurred(enumInputPort) == _TRUE)
    {
        return _STABLE;
    }
    else
#endif
    {
        return bReturn;
    }
}

//--------------------------------------------------
// Description : Clear BS Miss Flag
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxBsMissFlagClear(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
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

//--------------------------------------------------
// Description  : Get Display Format Regen Mode
// Input Value  : enumInputPort --> Source Search Port
// Output Value : DPF Regen Mode
//--------------------------------------------------
EnumDpMacRxDPFRegenMode ScalerDpMacStreamRxGetDPFRegenMode(EnumInputPort enumInputPort)
{
#if(_DUAL_DP_SUPPORT == _ON)
    EnumDpMacSel enumDualDpMacSel = _DP_MAC_NONE;
#endif

    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0GetDPFRegenMode();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1GetDPFRegenMode();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2GetDPFRegenMode();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3GetDPFRegenMode();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4GetDPFRegenMode();
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

            enumDualDpMacSel = ScalerDpRxGetMacSwitch(GET_DUAL_DP_PORT_SWITCH_SELECT());

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            if(enumDualDpMacSel == _DP_MAC_0)
            {
                return ScalerDpMacStreamRx0GetDPFRegenMode();
            }
            else
            {
                return ScalerDpMacStreamRx1GetDPFRegenMode();
            }
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            if(enumDualDpMacSel == _DP_MAC_1)
            {
                return ScalerDpMacStreamRx1GetDPFRegenMode();
            }
            else
            {
                return ScalerDpMacStreamRx2GetDPFRegenMode();
            }
#endif
            break;
#endif

        default:
            break;
    }

    return _DPF_MODE_NONE;
}

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DP Color Sapace Change Support Check
// Input Value  : void
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxColorSpaceChangeSupportCheck(void)
{
    return ScalerDpRxColorSpaceAndDepthChangeFlagValidCheck();
}

//--------------------------------------------------
// Description  : Set DP Color Sapace Change WD
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSetColorSpaceChangeWD(EnumInputPort enumInputPort, bit bEn)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SetColorSpaceChangeWD(bEn);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SetColorSpaceChangeWD(bEn);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SetColorSpaceChangeWD(bEn);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SetColorSpaceChangeWD(bEn);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SetColorSpaceChangeWD(bEn);

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0SetColorSpaceChangeWD(bEn);
            ScalerDpMacStreamRx1SetColorSpaceChangeWD(bEn);
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1SetColorSpaceChangeWD(bEn);
            ScalerDpMacStreamRx2SetColorSpaceChangeWD(bEn);
#endif
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check Msa Misc Chang Support or Not
// Input Value  : enumInputPort
// Output Value : _ON(Support)/_OFF(Not Support)
//--------------------------------------------------
bit ScalerDpMacStreamRxMsaMiscChangeSupportCheck(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0MsaMiscChangeSupportCheck();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1MsaMiscChangeSupportCheck();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2MsaMiscChangeSupportCheck();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3MsaMiscChangeSupportCheck();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4MsaMiscChangeSupportCheck();
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            return (ScalerDpMacStreamRx0MsaMiscChangeSupportCheck() && ScalerDpMacStreamRx1MsaMiscChangeSupportCheck());
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            return (ScalerDpMacStreamRx1MsaMiscChangeSupportCheck() && ScalerDpMacStreamRx2MsaMiscChangeSupportCheck());
#endif
#endif

        default:

            break;
    }

    return _OFF;
}

//--------------------------------------------------
// Description  : Enable DP MSA Change IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxSstSetMsaChangeIRQ(EnumInputPort enumInputPort, bit bEn)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            ScalerDpMacStreamRx0SstSetMsaChangeIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            ScalerDpMacStreamRx1SstSetMsaChangeIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            ScalerDpMacStreamRx2SstSetMsaChangeIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            ScalerDpMacStreamRx3SstSetMsaChangeIRQ(bEn);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            ScalerDpMacStreamRx4SstSetMsaChangeIRQ(bEn);

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
            ScalerDpMacStreamRx0SstSetMsaChangeIRQ(bEn);
            ScalerDpMacStreamRx1SstSetMsaChangeIRQ(bEn);
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
            ScalerDpMacStreamRx1SstSetMsaChangeIRQ(bEn);
            ScalerDpMacStreamRx2SstSetMsaChangeIRQ(bEn);
#endif
            break;
#endif
        default:

            break;
    }
}
#endif

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HBR Fifo Offset Update
// Input Value  : StructDpInfo/ WORD
// Output Value : WORD
//--------------------------------------------------
WORD ScalerDpMacStreamRxHblankingModifyFifoOffsetUpdate(StructDpInfo *pstDpInfo, WORD usFifoOffset)
{
    DWORD ulFifoUsageRateTarget = 0;
    WORD usMsaHtotal = pstDpInfo->stDpHblankingModifyInfo.usMsaHTotal;
    WORD usDpcdHtotal = pstDpInfo->stDpHblankingModifyInfo.usDpcdHTotal;

    if((usMsaHtotal == 0) || (usDpcdHtotal == 0))
    {
        DebugMessageDpRx("DP MAC RX: Hblanking Modify Info is invalid", 0);

        return 0xFF;
    }

    if(pstDpInfo->stDpHblankingModifyInfo.enumHblankingModifyMode == _HBR_MODE)
    {
        // Less Pixel to wait:
        // x = (HWD / PClk_O) - (HWD / PClk_I) => (sec) to pixel need (* PClk_O)
        // x = HWD * (1 - PClk_O / PClk_I) => (pixel)
        // x = HWD * (1 - Htt_dpcd / Htt_msa) => (pixel)
        ulFifoUsageRateTarget = pstDpInfo->stDpTimingInfo.usHWidth - ScalerGlobalComputeDwordMulDiv(pstDpInfo->stDpTimingInfo.usHWidth, usDpcdHtotal, usMsaHtotal);

        // FIFO Usage Rate Target
        // LC Tank 3% accuracy, Down Spread 0.5%
        // Total: 100 - 4 = 96%
        // FIFO Offset Real = (FIFO_total - x) / 2
        usFifoOffset = usFifoOffset * 12 / 25 - ulFifoUsageRateTarget / 2;
    }
    else
    {
        // More Pixel need to Diff Pixel Clock wait
        // (HWD - X) / PClk_I = HWD / PClk_O
        // X = HWD(1 - PClk_I / PClk_O)
        // X = HWD(1 - Htt_msa / Htt_dpcd) => (pixel)
        ulFifoUsageRateTarget = pstDpInfo->stDpTimingInfo.usHWidth - ScalerGlobalComputeDwordMulDiv(pstDpInfo->stDpTimingInfo.usHWidth, usMsaHtotal, usDpcdHtotal);

        // FIFO Usage Rate Target
        // LC Tank 3% accuracy, Down Spread 0.5%
        // Total: 100 - 4 = 96%
        // FIFO Target % = (100 * X / FIFO + 96) / 2
        // FIFO Offset Real = "FIFO Target %" * FIFO / 100 = X / 2 + 48 * FIFO / 100
        usFifoOffset = usFifoOffset * 12 / 25 + ulFifoUsageRateTarget / 2;
    }

    return usFifoOffset;
}

//--------------------------------------------------
// Description  : Dp Stream Check HBE HBR Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacStreamRxHlankingModifyCheck(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo)
{
    WORD usDpcdHTotal = 0;
    WORD usDpcdHStart = 0;
    WORD usDpcdHSWidth = 0;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_MULTI_FUNCTION_SUPPORT == _ON))
    if((ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _TRUE) && (ScalerDpMstRxGetVirtualDpEnable(enumInputPort, _DP_PORT8) == _ENABLE))
    {
        // get virtaul DPCD value
        usDpcdHTotal = TO_WORD(ScalerDpMstRxGetVirtualDpcdInfo(enumInputPort, _DP_PORT8, 0x00, 0x30, 0x55), ScalerDpMstRxGetVirtualDpcdInfo(enumInputPort, _DP_PORT8, 0x00, 0x30, 0x54));
        usDpcdHStart = TO_WORD(ScalerDpMstRxGetVirtualDpcdInfo(enumInputPort, _DP_PORT8, 0x00, 0x30, 0x57), ScalerDpMstRxGetVirtualDpcdInfo(enumInputPort, _DP_PORT8, 0x00, 0x30, 0x56));
        usDpcdHSWidth = TO_WORD(ScalerDpMstRxGetVirtualDpcdInfo(enumInputPort, _DP_PORT8, 0x00, 0x30, 0x59), ScalerDpMstRxGetVirtualDpcdInfo(enumInputPort, _DP_PORT8, 0x00, 0x30, 0x58));
    }
    else
#endif
    {
        usDpcdHTotal = TO_WORD(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x30, 0x55), ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x30, 0x54));
        usDpcdHStart = TO_WORD(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x30, 0x57), ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x30, 0x56));
        usDpcdHSWidth = TO_WORD(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x30, 0x59), ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x30, 0x58));
    }

    if((usDpcdHTotal == 0x00) || (usDpcdHStart == 0x00) || (usDpcdHSWidth == 0x00))
    {
        return _FALSE;
    }

    if(usDpcdHTotal > pstDpInfo->stDpHblankingModifyInfo.usMsaHTotal)
    {
        pstDpInfo->stDpHblankingModifyInfo.enumHblankingModifyMode = _HBE_MODE;
        DebugMessageDpRx("DP MAC RX: HBE Mode Enable", 0);
    }
    else if(usDpcdHTotal < pstDpInfo->stDpHblankingModifyInfo.usMsaHTotal)
    {
        pstDpInfo->stDpHblankingModifyInfo.enumHblankingModifyMode = _HBR_MODE;
        DebugMessageDpRx("DP MAC RX: HBR Mode Enable", 0);
    }
    else
    {
        pstDpInfo->stDpHblankingModifyInfo.enumHblankingModifyMode = _NO_HBLANKING_MODIFY;
        return _FALSE;
    }

    pstDpInfo->stDpHblankingModifyInfo.usDpcdHTotal = usDpcdHTotal;
    pstDpInfo->stDpHblankingModifyInfo.usDpcdHStart = usDpcdHStart;
    pstDpInfo->stDpHblankingModifyInfo.b1DpcdHSP = usDpcdHSWidth >> 15;
    pstDpInfo->stDpHblankingModifyInfo.usDpcdHSWidth = usDpcdHSWidth & 0x7FFF;

    DebugMessageDpRx("DP MAC RX: DPCD_HTT", pstDpInfo->stDpHblankingModifyInfo.usDpcdHTotal);
    DebugMessageDpRx("DP MAC RX: DPCD_HST", pstDpInfo->stDpHblankingModifyInfo.usDpcdHStart);
    DebugMessageDpRx("DP MAC RX: DPCD_HSW", pstDpInfo->stDpHblankingModifyInfo.usDpcdHSWidth);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Hblanking Modify Dpf Update
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxHblankingModifyDpfUpdate(StructDpInfo *pstDpInfo)
{
    WORD usMsaHtotal = pstDpInfo->stDpHblankingModifyInfo.usMsaHTotal;
    WORD usDpcdHTotal = pstDpInfo->stDpHblankingModifyInfo.usDpcdHTotal;

    // OverWrite Timing Info According DPCD Info
    pstDpInfo->stDpTimingInfo.usHTotal = usDpcdHTotal;
    pstDpInfo->stDpTimingInfo.usHStart = pstDpInfo->stDpHblankingModifyInfo.usDpcdHStart;
    pstDpInfo->stDpTimingInfo.b1HSP = pstDpInfo->stDpHblankingModifyInfo.b1DpcdHSP;
    pstDpInfo->stDpTimingInfo.usHSWidth = pstDpInfo->stDpHblankingModifyInfo.usDpcdHSWidth;

    if(usMsaHtotal == 0x00)
    {
        DebugMessageDpRx("DP MAC RX: MSA Htotal Not Valid", 0);

        return;
    }

    // Calculate Sclk For HBR/HBE
    pstDpInfo->stDpLinkInfo.ulStreamClockHz = ScalerGlobalComputeDwordMulDiv(pstDpInfo->stDpLinkInfo.ulStreamClockHz, usDpcdHTotal, usMsaHtotal);
}
#endif

//--------------------------------------------------
// Description  : Check VGIP VS bypass for DP
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxCheckVgipVsBypass(EnumInputPort enumInputPort)
{
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitch(enumInputPort);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
    BYTE ucDscMac = ScalerDscDecoderDpMacRxxGetDscDecoderMac(enumDpMacSel);

    if(ucDscMac != _DSC_MAC_NONE)
    {
        return ScalerDscDecoderCheckVgipVsBypass(ucDscMac);
    }
#endif

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerDpMacStreamRx0CheckVgipVsBypass();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerDpMacStreamRx1CheckVgipVsBypass();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerDpMacStreamRx2CheckVgipVsBypass();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return ScalerDpMacStreamRx3CheckVgipVsBypass();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return ScalerDpMacStreamRx4CheckVgipVsBypass();
#endif

        default:

            return _FALSE;
    }
}

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Mst Check Pxp Stream Mux
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRxPxpStreamMuxCheck(EnumInputPort enumInputPort)
{
    if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON)
    {
#if(_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON)
        if(enumInputPort == _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
        {
            return;
        }
#endif
        // For DP20 case Pxp Mac clone Rx input
        if((ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _TRUE) &&
           (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, _BIT0) == 0x00))
        {
            if(ScalerDpMacDphyRxGetMstStreamExist(ScalerDpRxDxMacSourceMapping(enumInputPort)) == _FALSE)
            {
                if(enumInputPort == _D9_INPUT_PORT)
                {
                    // Pxp input port stream predetect pass ==> Pxp D9 clone Rx input
                    if((ScalerDpMacStreamRxGetStreamPredetect(GET_DP_MST_RX_PXP_INPUT_PORT()) == _TRUE) &&
                       (ScalerDpMacStreamRxGetStreamInfoType(ScalerDpRxGetMacStreamSourceType(ScalerDpRxGetMacSwitch(GET_DP_MST_RX_PXP_INPUT_PORT()))) == _INFO_TYPE_VIDEO))
                    {
                        EnumDpStreamSourceNum enumDpSourceTemp = ScalerDpMacStreamRxGetStreamSourceTypeToSourceMux(ScalerDpRxDxMacSourceMapping(enumInputPort));
                        EnumDpStreamNum enumDpStream = ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, ScalerDpMstRxDxPortNumMapping(GET_DP_MST_RX_PXP_INPUT_PORT()));

                        ScalerDpMacDphyRxSetSourceMuxBackup(enumInputPort, enumDpSourceTemp, enumDpStream);
                    }
                }
                else
                {
                    // Pxp D9 port stream predetect pass ==> Rx input clone Pxp D9
                    if((ScalerDpMacStreamRxGetStreamPredetect(_D9_INPUT_PORT) == _TRUE) &&
                       (ScalerDpMacStreamRxGetStreamInfoType(ScalerDpRxGetMacStreamSourceType(ScalerDpRxGetMacSwitch(_D9_INPUT_PORT))) == _INFO_TYPE_VIDEO))
                    {
                        EnumDpStreamSourceNum enumDpSourceTemp = ScalerDpMacStreamRxGetStreamSourceTypeToSourceMux(ScalerDpRxDxMacSourceMapping(enumInputPort));
                        EnumDpStreamNum enumDpStream = ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, ScalerDpMstRxDxPortNumMapping(_D9_INPUT_PORT));

                        ScalerDpMacDphyRxSetSourceMuxBackup(enumInputPort, enumDpSourceTemp, enumDpStream);
                    }
                }
            }
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Get Mst protocol(MTP or SST format) Status of inputport
// Input Value  : enumInputport
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerDpMacStreamRxGetStreamPredetect(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:
            return GET_DP_MAC_STREAM_RX0_STREAM_PREDETECT();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:
            return GET_DP_MAC_STREAM_RX1_STREAM_PREDETECT();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:
            return GET_DP_MAC_STREAM_RX2_STREAM_PREDETECT();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
            return GET_DP_MAC_STREAM_RX3_STREAM_PREDETECT();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
            return GET_DP_MAC_STREAM_RX4_STREAM_PREDETECT();
#endif

        default:
            break;
    }

    return _FALSE;
}

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Judge for using DE-Only mode or not
// Input Value  : StructDpInfo *pstDpInfo
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxDeOnlyJudge_128b132b(StructDpInfo *pstDpInfo)
{
    DWORD ulFrameRate = 0;
    DWORD ulLineRate = 0;
    WORD usMeasureVtotal = 0;
    WORD usDiffVtotal = 0;

    if(pstDpInfo->stDpLinkInfo.ulVBsToBsCountN == 0x00)
    {
        return _FALSE;
    }

    // Frame Rate (Unit is 0.01Hz)
    ulFrameRate = ScalerGlobalComputeDwordMulDiv((DWORD)_GDIPHY_RX_GDI_CLK_KHZ, 100000, pstDpInfo->stDpLinkInfo.ulVBsToBsCountN);

    if(ScalerDpMacStreamRxDeOnlyTimngCheck(pstDpInfo, ulFrameRate) == _TRUE)
    {
        if(pstDpInfo->stDpLinkInfo.usHBsToBsCount == 0x00)
        {
            return _FALSE;
        }

        // Line Rate (Unit : 0.01Hz)
        ulLineRate = ScalerGlobalComputeDwordMulDiv(pstDpInfo->stDpLinkInfo.ulLinkClockHz, 10, (DWORD)pstDpInfo->stDpLinkInfo.usHBsToBsCount * 32) * 100;

        // Vtotal by Measure (Unit : Line Number)
        usMeasureVtotal = (WORD)((ulLineRate + (ulFrameRate / 2)) / ulFrameRate);

        // Difference of Vtotal by Measure and MSA
        usDiffVtotal = abs(usMeasureVtotal - pstDpInfo->stDpTimingInfo.usVTotal);

        if((usDiffVtotal >= 4) && (usDiffVtotal <= 6))
        {
            pstDpInfo->stDpTimingInfo.usVTotal = usMeasureVtotal;

            DebugMessageDpRx("Votal (Measure vs MSA) is different !!!", usDiffVtotal);

            return _TRUE;
        }
    }

    return _FALSE;
}
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : For Stream MST2SST
// Input Value  : None
// Output Value : EnumDpStreamSourceNum
//--------------------------------------------------
EnumDpStreamSourceNum ScalerDpMacStreamRxGetStreamSourceTypeToSourceMux(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    return ScalerDpMacStreamRxGetMacToSourceMux(ScalerDpRxGetMacSwitchMappingSourceType(enumDpMacStreamSourceType));
}

//--------------------------------------------------
// Description  : Get Mac To Source Mux Mapping
// Input Value  : None
// Output Value : EnumDpStreamSourceNum
//--------------------------------------------------
EnumDpStreamSourceNum ScalerDpMacStreamRxGetMacToSourceMux(EnumDpMacSel enumDpMacSel)
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
