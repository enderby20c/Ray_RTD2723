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
// ID Code      : ScalerAudio.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_AUDIO__

#include "ScalerFunctionInclude.h"
#include "Audio/ScalerAudio.h"

#if(_AUDIO_SUPPORT == _ON)
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
#warning "NOTE: _INTERNAL_AUDIO_TEST_SUPPORT is _ON!!!"

#if(_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON)
#warning "NOTE: _INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT is _ON!!!"
#endif

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
#warning "NOTE: IIS/SPDIF and Arc/eARC Output Path Should be Same Audio inputport!"
#endif
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
#if((_DP_RX_AUDIO_SUPPORT == _ON) && (_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _OFF))
#warning "NOTE: It's recommended to set _DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON when support DP audio with ITE external earc via parallel mode!"
#endif // End of #if((_DP_RX_AUDIO_SUPPORT == _ON) && (_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _OFF))
#endif // End of #if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_SPDIF_STRONG_DRIVING_PAD)

#endif // End of #if(_AUDIO_SUPPORT == _ON)


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_AUDIO_SUPPORT == _ON)
#if(_EMBEDDED_DAC_SUPPORT == _ON)
StructAudioDACInfo g_stAudioDACInfo;
#endif

#if(_DP_SUPPORT == _ON)
StructAudioDpCapabilityInfo g_stAudioDpCapabilityInfo;
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DUAL_DP_SUPPORT == _ON)
bit g_bAudioDpDualStatus = _FALSE;
#endif

bit g_bAudioDVCMuteCtrlStatus;

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
EnumPowerCut g_enumAudioGenPowerState;
StructAudioGenFreqParameter g_stAudioGenFreq;

#if(_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON)
bit g_bAudioInternalGenEnable;
#endif
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#if(_AUDIO_ARC_SUPPORT == _ON)
EnumAudioArcMode g_enumAudioArcTxLinkMode;
StructAudioArcTxTimerCtrl g_stAudioArcTxTimerCtrl;
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
BYTE g_ucAudioRx3PllStableCnt;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
BYTE g_ucAudioRx4PllStableCnt;
#endif
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
StructAudioHbrSetting g_stAudioHbrSetting;
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Timer Event to Load Stable I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioLoadStableICodeEvent(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if(_DP_AUDIO_RX0_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_DP_AUDIO_RX0_LOAD_STABLE_I_CODE:

            ScalerDpAudioRx0LoadStableICodeEvent();
            break;
#endif

#if(_DP_AUDIO_RX1_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_DP_AUDIO_RX1_LOAD_STABLE_I_CODE:

            ScalerDpAudioRx1LoadStableICodeEvent();
            break;
#endif

#if(_DP_AUDIO_RX2_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_DP_AUDIO_RX2_LOAD_STABLE_I_CODE:

            ScalerDpAudioRx2LoadStableICodeEvent();
            break;
#endif

#if(_DP_AUDIO_RX3_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_DP_AUDIO_RX3_LOAD_STABLE_I_CODE:

            ScalerDpAudioRx3LoadStableICodeEvent();
            break;
#endif

#if(_DP_AUDIO_RX4_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_DP_AUDIO_RX4_LOAD_STABLE_I_CODE:

            ScalerDpAudioRx4LoadStableICodeEvent();
            break;
#endif

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_LOAD_STABLE_I_CODE:

            ScalerHdmiAudioRx3LoadStableICodeEvent();
            break;
#endif

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_HDMI_AUDIO_RX4_LOAD_STABLE_I_CODE:

            ScalerHdmiAudioRx4LoadStableICodeEvent();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Audio Sampling Freq Packet
// Input Value  : EnumAudioSamplingFreqType
// Output Value : EnumAudioSamplingFreqPacket
//--------------------------------------------------
EnumAudioSamplingFreqPacket ScalerAudioGetSamplingFreqPacket(EnumAudioSamplingFreqType enumSamplingFreqType)
{
    switch(enumSamplingFreqType)
    {
        case _AUDIO_FREQ_32K:
            return _AUDIO_FREQ_PACKET_32K;

        case _AUDIO_FREQ_44_1K:
            return _AUDIO_FREQ_PACKET_44_1K;

        case _AUDIO_FREQ_48K:
            return _AUDIO_FREQ_PACKET_48K;

        case _AUDIO_FREQ_64K:
            return _AUDIO_FREQ_PACKET_64K;

        case _AUDIO_FREQ_88_2K:
            return _AUDIO_FREQ_PACKET_88_2K;

        case _AUDIO_FREQ_96K:
            return _AUDIO_FREQ_PACKET_96K;

        case _AUDIO_FREQ_128K:
            return _AUDIO_FREQ_PACKET_128K;

        case _AUDIO_FREQ_176_4K:
            return _AUDIO_FREQ_PACKET_176_4K;

        case _AUDIO_FREQ_192K:
            return _AUDIO_FREQ_PACKET_192K;

        case _AUDIO_FREQ_256K:
            return _AUDIO_FREQ_PACKET_256K;

        case _AUDIO_FREQ_352_8K:
            return _AUDIO_FREQ_PACKET_352_8K;

        case _AUDIO_FREQ_384K:
            return _AUDIO_FREQ_PACKET_384K;

        case _AUDIO_FREQ_512K:
            return _AUDIO_FREQ_PACKET_512K;

        case _AUDIO_FREQ_705_6K:
            return _AUDIO_FREQ_PACKET_705_6K;

        case _AUDIO_FREQ_768K:
            return _AUDIO_FREQ_PACKET_768K;

        default:
            break;
    }

    return _AUDIO_FREQ_PACKET_NO_AUDIO;
}

//--------------------------------------------------
// Description  : Get User Define NF Code of Audio Sampling Freq
// Input Value  : EnumPortType
// Input Value  : EnumAudioSamplingFreqType
// Output Value : NF Code
//--------------------------------------------------
DWORD ScalerAudioGetUserSamplingFreqNFCode(EnumPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq)
{
    DWORD ulNFCode = 0x00;

    switch(enumAudioFreq)
    {
        case _AUDIO_FREQ_32K:
        case _AUDIO_FREQ_64K:
        case _AUDIO_FREQ_128K:
        case _AUDIO_FREQ_256K:
        case _AUDIO_FREQ_512K:

            if(enumPortType == _PORT_DP)
            {
                ulNFCode = _DP_SAMPLING_FREQ_32K_GROUP_NF_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ulNFCode = (((DWORD)_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE << 16) | _HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE);
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_44_1K:
        case _AUDIO_FREQ_88_2K:
        case _AUDIO_FREQ_176_4K:
        case _AUDIO_FREQ_352_8K:
        case _AUDIO_FREQ_705_6K:

            if(enumPortType == _PORT_DP)
            {
                ulNFCode = _DP_SAMPLING_FREQ_44K_GROUP_NF_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ulNFCode = (((DWORD)_HDMI_SAMPLING_FREQ_44K_GROUP_N_CODE << 16) | _HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE);
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_48K:
        case _AUDIO_FREQ_96K:
        case _AUDIO_FREQ_192K:
        case _AUDIO_FREQ_384K:
        case _AUDIO_FREQ_768K:

            if(enumPortType == _PORT_DP)
            {
                ulNFCode = _DP_SAMPLING_FREQ_48K_GROUP_NF_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ulNFCode = (((DWORD)_HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE << 16) | _HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE);
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_NO_AUDIO:
        default:

            if(enumPortType == _PORT_DP)
            {
                ulNFCode = _DP_SAMPLING_FREQ_48K_GROUP_NF_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ulNFCode = (((DWORD)_HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE << 16) | _HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE);
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;
    }

    return ulNFCode;
}

//--------------------------------------------------
// Description  : Get User Define S Code of Audio Sampling Freq
// Input Value  : EnumPortType
// Input Value  : EnumAudioSamplingFreqType
// Output Value : NF Code
//--------------------------------------------------
BYTE ScalerAudioGetUserSamplingFreqSCode(EnumPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq)
{
    BYTE ucSCode = 0x01;

    switch(enumAudioFreq)
    {
        case _AUDIO_FREQ_32K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_44_1K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_48K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_64K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 1;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 1;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_88_2K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 1;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 1;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_96K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 1;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 1;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_128K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 2;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 2;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_176_4K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 2;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 2;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_192K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 2;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 2;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_256K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 3;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 3;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_352_8K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 3;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 3;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_384K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 3;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 3;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_512K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 4;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 4;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_705_6K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 4;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 4;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_768K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 4;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 4;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_NO_AUDIO:
        default:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;
    }

    return ucSCode;
}

//--------------------------------------------------
// Description  : Get User Define NF Code of Audio Sampling Freq
// Input Value  : EnumPortType
// Input Value  : EnumAudioSamplingFreqType
// Output Value : NF Code
//--------------------------------------------------
DWORD ScalerAudioGetUserSamplingFreqNFCode_EXINT0(EnumPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq)
{
    DWORD ulNFCode = 0x00;

    switch(enumAudioFreq)
    {
        case _AUDIO_FREQ_32K:
        case _AUDIO_FREQ_64K:
        case _AUDIO_FREQ_128K:
        case _AUDIO_FREQ_256K:
        case _AUDIO_FREQ_512K:

            if(enumPortType == _PORT_DP)
            {
                ulNFCode = _DP_SAMPLING_FREQ_32K_GROUP_NF_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ulNFCode = (((DWORD)_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE << 16) | _HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE);
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_44_1K:
        case _AUDIO_FREQ_88_2K:
        case _AUDIO_FREQ_176_4K:
        case _AUDIO_FREQ_352_8K:
        case _AUDIO_FREQ_705_6K:

            if(enumPortType == _PORT_DP)
            {
                ulNFCode = _DP_SAMPLING_FREQ_44K_GROUP_NF_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ulNFCode = (((DWORD)_HDMI_SAMPLING_FREQ_44K_GROUP_N_CODE << 16) | _HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE);
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_48K:
        case _AUDIO_FREQ_96K:
        case _AUDIO_FREQ_192K:
        case _AUDIO_FREQ_384K:
        case _AUDIO_FREQ_768K:

            if(enumPortType == _PORT_DP)
            {
                ulNFCode = _DP_SAMPLING_FREQ_48K_GROUP_NF_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ulNFCode = (((DWORD)_HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE << 16) | _HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE);
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_NO_AUDIO:
        default:

            if(enumPortType == _PORT_DP)
            {
                ulNFCode = _DP_SAMPLING_FREQ_48K_GROUP_NF_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ulNFCode = (((DWORD)_HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE << 16) | _HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE);
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;
    }

    return ulNFCode;
}

//--------------------------------------------------
// Description  : Get User Define S Code of Audio Sampling Freq
// Input Value  : EnumPortType
// Input Value  : EnumAudioSamplingFreqType
// Output Value : NF Code
//--------------------------------------------------
BYTE ScalerAudioGetUserSamplingFreqSCode_EXINT0(EnumPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq)
{
    BYTE ucSCode = 0x01;

    switch(enumAudioFreq)
    {
        case _AUDIO_FREQ_32K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_44_1K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_48K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_64K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 1;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 1;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_88_2K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 1;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 1;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_96K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 1;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 1;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_128K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 2;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 2;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_176_4K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 2;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 2;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_192K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 2;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 2;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_256K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 3;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 3;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_352_8K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 3;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 3;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_384K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 3;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 3;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_512K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 4;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 4;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_705_6K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 4;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 4;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_768K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 4;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 4;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;

        case _AUDIO_FREQ_NO_AUDIO:
        default:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }
#if(_AUDIO_SUPPORT == _ON)
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            break;
    }

    return ucSCode;
}

//--------------------------------------------------
// Description  : Get Current Audio Port For Output Type
// Input Value  : None
// Output Value : audio port
//--------------------------------------------------
EnumAudioInputPort ScalerAudioGetDigitalAudioPort(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
            return (EnumAudioInputPort)(ScalerGetBit(P6F_01_MUX_DA_DVC_IN, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        case _AUDIO_I2S_OUT:
            return (EnumAudioInputPort)(ScalerGetBit(P6F_00_MUX_DIG_OUT, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

        case _AUDIO_SPDIF_OUT:
            return (EnumAudioInputPort)(ScalerGetBit(P6F_00_MUX_DIG_OUT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        case _AUDIO_DPTX_OUT:
            return (EnumAudioInputPort)(ScalerGetBit(P6F_02_MUX_DP_I2S_IN, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
            return (EnumAudioInputPort)(ScalerGetBit(P6F_01_MUX_DA_DVC_IN, (_BIT7 | _BIT6 | _BIT5)) >> 5);
#else
#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
            if(ScalerGetBit(P6F_00_MUX_DIG_OUT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT1))
            {
#if(_LINE_IN_SUPPORT == _ON)
                // Check really ADC Path? (Path for adjusting volume through embedded DVC)
                if(ScalerAudioGetInputSource(_AUDIO_ARC_OUT) == _LINE_IN_AUDIO)
                {
                    // ADC Path
                    return _AUDIO_FROM_ADC_PORT;
                }
                else
#endif
                {
                    // Check DVC Input
                    return (EnumAudioInputPort)(ScalerGetBit(P6F_01_MUX_DA_DVC_IN, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
                }
            }
            else
#endif
            {
                return (EnumAudioInputPort)(ScalerGetBit(P6F_00_MUX_DIG_OUT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
            }
#endif
#endif

        default:
            break;
    }

    return _AUDIO_FROM_RX0_PORT;
}

//--------------------------------------------------
// Description  : Recover Audio Frequency of HBR Audio
// Input Value  : EnumAudioSamplingFreqType
// Output Value : EnumAudioSamplingFreqType
//--------------------------------------------------
EnumAudioSamplingFreqType ScalerAudioDpRecoverHbrAudioFrequency(EnumAudioSamplingFreqType enumAudioFreq)
{
    switch(enumAudioFreq)
    {
        case _AUDIO_FREQ_32K:
            return _AUDIO_FREQ_128K;

        case _AUDIO_FREQ_44_1K:
            return _AUDIO_FREQ_176_4K;

        case _AUDIO_FREQ_48K:
            return _AUDIO_FREQ_192K;

        case _AUDIO_FREQ_64K:
            return _AUDIO_FREQ_256K;

        case _AUDIO_FREQ_88_2K:
            return _AUDIO_FREQ_352_8K;

        case _AUDIO_FREQ_96K:
            return _AUDIO_FREQ_384K;

        case _AUDIO_FREQ_128K:
            return _AUDIO_FREQ_512K;

        case _AUDIO_FREQ_176_4K:
            return _AUDIO_FREQ_705_6K;

        case _AUDIO_FREQ_192K:
            return _AUDIO_FREQ_768K;

        default:
            break;
    }

    return _AUDIO_FREQ_NO_AUDIO;
}

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
//--------------------------------------------------
// Description  : Set Dp Audio Capability State
// Input Value  : EnumAudioOutputType
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerAudioDpGetHbr8ChannelSupport(EnumAudioOutputType enumAudioOutput)
{
    switch(ScalerAudioGetDigitalAudioPort(enumAudioOutput))
    {
#if(_DP_AUDIO_RX0_SUPPORT == _ON)
        case _AUDIO_FROM_RX0_PORT:

            return GET_DP_AUDIO_RX0_HBR_RECEIVE_IN_8_CH();

            break;
#endif

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        case _AUDIO_FROM_RX1_PORT:

            return GET_DP_AUDIO_RX1_HBR_RECEIVE_IN_8_CH();

            break;
#endif

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
        case _AUDIO_FROM_RX2_PORT:

            return GET_DP_AUDIO_RX2_HBR_RECEIVE_IN_8_CH();

            break;
#endif

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
        case _AUDIO_FROM_PXP_PORT:

            return GET_DP_AUDIO_RX3_HBR_RECEIVE_IN_8_CH();

            break;
#endif

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
        case _AUDIO_FROM_MST2SST_PORT:

            return GET_DP_AUDIO_RX4_HBR_RECEIVE_IN_8_CH();

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set Dp Audio Capability State
// Input Value  : EnumAudioOutputType
// Output Value  : _ENABLE/_DISABLE
//--------------------------------------------------
bit ScalerAudioDpGetHbrOperationState(EnumAudioOutputType enumAudioOutput)
{
    switch(ScalerAudioGetDigitalAudioPort(enumAudioOutput))
    {
#if(_DP_AUDIO_RX0_SUPPORT == _ON)
        case _AUDIO_FROM_RX0_PORT:

            return GET_DP_AUDIO_RX0_HBR_OPERATION_DONE();

            break;
#endif

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
        case _AUDIO_FROM_RX1_PORT:

            return GET_DP_AUDIO_RX1_HBR_OPERATION_DONE();

            break;
#endif

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
        case _AUDIO_FROM_RX2_PORT:

            return GET_DP_AUDIO_RX2_HBR_OPERATION_DONE();

            break;
#endif

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
        case _AUDIO_FROM_PXP_PORT:

            return GET_DP_AUDIO_RX3_HBR_OPERATION_DONE();

            break;
#endif

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
        case _AUDIO_FROM_MST2SST_PORT:

            return GET_DP_AUDIO_RX4_HBR_OPERATION_DONE();

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)

//--------------------------------------------------
// Description  : Get Audio Channel Count of Rx Port
// Input Value  : None
// Output Value : Channel Count
//--------------------------------------------------
EnumAudioChannelCount ScalerAudioGetRxChannelCount(EnumAudioOutputType enumAudioOutput)
{
    EnumAudioChannelCount enumChannelCount = _AUDIO_CHANNEL_COUNT_MONO;

    switch(ScalerAudioGetDigitalAudioPort(enumAudioOutput))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_AUDIO_RX0_SUPPORT == _ON)
            enumChannelCount = GET_DP_AUDIO_RX0_CHANNEL_COUNT();
#endif
            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
            enumChannelCount = GET_DP_AUDIO_RX1_CHANNEL_COUNT();
#endif
            break;

        case _AUDIO_FROM_RX2_PORT:

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
            enumChannelCount = GET_DP_AUDIO_RX2_CHANNEL_COUNT();
#endif
            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
            enumChannelCount = GET_HDMI_AUDIO_RX3_CHANNEL_COUNT();
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
            enumChannelCount = GET_HDMI_AUDIO_RX4_CHANNEL_COUNT();
#endif
            break;

        case _AUDIO_FROM_ADC_PORT:

#if(_LINE_IN_SUPPORT == _ON)
            enumChannelCount = GET_LINE_IN_AUDIO_CHANNEL_COUNT();
#endif
            break;

        case _AUDIO_FROM_PXP_PORT:

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
            enumChannelCount = GET_DP_AUDIO_RX3_CHANNEL_COUNT();
#endif
            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
            enumChannelCount = GET_DP_AUDIO_RX4_CHANNEL_COUNT();
#endif
            break;

        default:
            break;
    }

    return enumChannelCount;
}

//--------------------------------------------------
// Description  : Get Audio Coding Type of Rx Port
// Input Value  : None
// Output Value : Coding Type
//--------------------------------------------------
BYTE ScalerAudioGetRxCodingType(EnumAudioOutputType enumAudioOutput)
{
    BYTE ucCodingType = 0;

    switch(ScalerAudioGetDigitalAudioPort(enumAudioOutput))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_AUDIO_RX0_SUPPORT == _ON)
            ucCodingType = GET_DP_AUDIO_RX0_CODING_TYPE();
#endif
            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
            ucCodingType = GET_DP_AUDIO_RX1_CODING_TYPE();
#endif
            break;

        case _AUDIO_FROM_RX2_PORT:

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
            ucCodingType = GET_DP_AUDIO_RX2_CODING_TYPE();
#endif
            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
            ucCodingType = GET_HDMI_AUDIO_RX3_CODING_TYPE();
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
            ucCodingType = GET_HDMI_AUDIO_RX4_CODING_TYPE();
#endif
            break;

        case _AUDIO_FROM_ADC_PORT:

#if(_LINE_IN_SUPPORT == _ON)
            ucCodingType = GET_LINE_IN_AUDIO_CODING_TYPE();
#endif
            break;

        case _AUDIO_FROM_PXP_PORT:

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
            ucCodingType = GET_DP_AUDIO_RX3_CODING_TYPE();
#endif
            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
            ucCodingType = GET_DP_AUDIO_RX4_CODING_TYPE();
#endif
            break;

        default:
            break;
    }

    return ucCodingType;
}

//--------------------------------------------------
// Description  : Get Audio Channel Status of Rx Port
// Input Value  : None
// Output Value : Channel Status
//--------------------------------------------------
StructAudioChannelInfo ScalerAudioGetRxChannelStatus(EnumAudioOutputType enumAudioOutput)
{
    StructAudioChannelInfo stAudioStatus = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    switch(ScalerAudioGetDigitalAudioPort(enumAudioOutput))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_AUDIO_RX0_SUPPORT == _ON)
            stAudioStatus = ScalerDpAudioRx0GetChannelStatus();
#endif
            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
            stAudioStatus = ScalerDpAudioRx1GetChannelStatus();
#endif
            break;

        case _AUDIO_FROM_RX2_PORT:

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
            stAudioStatus = ScalerDpAudioRx2GetChannelStatus();
#endif
            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
            stAudioStatus = ScalerHdmiAudioRx3GetChannelStatus();
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
            stAudioStatus = ScalerHdmiAudioRx4GetChannelStatus();
#endif
            break;

        case _AUDIO_FROM_ADC_PORT:

#if(_LINE_IN_SUPPORT == _ON)
            // Mode 0 channel status format for consumer use(IEC 60958)

            // [0] = 0, Consumer use;
            // [1] = 0, LPCM Audio;
            // [2] = 1, No Copyright;
            // [5:3] = 3'b000, 2-ch audio without pre-emphasis;
            // [7:6] = 2'b00, Mode 0.
            stAudioStatus.ucChannelStaus0 = 0x04;

            // [15:8] = 8'b10000000, Category code is not defined.
            stAudioStatus.ucChannelStaus1 = 0x80;

            // [19:16] = 4'b0000, Source number do not take into account;
            // [23:20] Set Dummy and Reference by AudioChannelNumStaus1 ~ 8.
            stAudioStatus.ucChannelStaus2 = 0x00;

            // [27:24] = 4'b0010, 48kHz;
            // [29:28] = 2'b00, Clock accuracy Level II.
            stAudioStatus.ucChannelStaus3 = 0x02;

            // [32] = 1, 24-bits Sample;
            // [35:33] = 3'b101;
            // [39:36] = 4'b0000, Original sampling frequency not indicated.
            stAudioStatus.ucChannelStaus4 = 0x0B;

            // Insert 2-Channel
            stAudioStatus.ucChannelNumber12 = 0x12;
            stAudioStatus.ucChannelNumber34 = 0x00;
            stAudioStatus.ucChannelNumber56 = 0x00;
            stAudioStatus.ucChannelNumber78 = 0x00;
#endif
            break;

        case _AUDIO_FROM_PXP_PORT:

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
            stAudioStatus = ScalerDpAudioRx3GetChannelStatus();
#endif
            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
            stAudioStatus = ScalerDpAudioRx4GetChannelStatus();
#endif
            break;

        default:
            break;
    }

    return stAudioStatus;
}

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
#if(_HW_DP_AUDIO_CHANNEL_STATUS_1S1D2S_RECEIVE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Get Audio Frequency of Channel Status
// Input Value  : EnumAudioSamplingFreqType
// Output Value : Channel Status[31:24]
//--------------------------------------------------
void ScalerAudioSetChannelStatusFrequency(EnumAudioSamplingFreqType enumAudioFreq, StructAudioChannelInfo *pstAudioStatus)
{
    // Set Channel_Status[31:24]
    switch(enumAudioFreq)
    {
        case _AUDIO_FREQ_32K:

            // [27:24] = 4'b0011, audio frequency is 32kHz
            // [29:28] = 2'b00, clock accuracy is level II.
            // [31:30] = 2'b00, reserved
            pstAudioStatus->ucChannelStaus3 = 0x03;

            break;

        case _AUDIO_FREQ_44_1K:

            // [27:24] = 4'b0000, audio frequency is 44.1kHz
            // [29:28] = 2'b00, clock accuracy is level II.
            // [31:30] = 2'b00, reserved
            pstAudioStatus->ucChannelStaus3 = 0x00;

            break;

        case _AUDIO_FREQ_48K:

            // [27:24] = 4'b0010, audio frequency is 48kHz
            // [29:28] = 2'b00, clock accuracy is level II.
            // [31:30] = 2'b00, reserved
            pstAudioStatus->ucChannelStaus3 = 0x02;

            break;

        case _AUDIO_FREQ_88_2K:

            // [27:24] = 4'b1000, audio frequency is 88.2kHz
            // [29:28] = 2'b00, clock accuracy is level II.
            // [31:30] = 2'b00, reserved
            pstAudioStatus->ucChannelStaus3 = 0x08;

            break;

        case _AUDIO_FREQ_96K:

            // [27:24] = 4'b1010, audio frequency is 96kHz
            // [29:28] = 2'b00, clock accuracy is level II.
            // [31:30] = 2'b00, reserved
            pstAudioStatus->ucChannelStaus3 = 0x0A;

            break;

        case _AUDIO_FREQ_176_4K:

            // [27:24] = 4'b1100, audio frequency is 176.4kHz
            // [29:28] = 2'b00, clock accuracy is level II.
            // [31:30] = 2'b00, reserved
            pstAudioStatus->ucChannelStaus3 = 0x0C;

            break;

        case _AUDIO_FREQ_192K:

            // [27:24] = 4'b1110, audio frequency is 192kHz
            // [29:28] = 2'b00, clock accuracy is level II.
            // [31:30] = 2'b00, reserved
            pstAudioStatus->ucChannelStaus3 = 0x0E;

            break;

        default:
            // [27:24] = 4'b0001, audio frequency is not indicated
            // [29:28] = 2'b00, clock accuracy is level II.
            // [31:30] = 2'b00, reserved
            pstAudioStatus->ucChannelStaus3 = 0x01;

            break;
    }
}

//--------------------------------------------------
// Description  : Get Audio Number of Channel Status
// Input Value  : EnumAudioChannelCount
// Output Value : Channel Status[23:20]
//--------------------------------------------------
void ScalerAudioSetChannelStatusNumber(EnumAudioChannelCount enumChannelCount, StructAudioChannelInfo *pstAudioStatus)
{
    // Set Channel Number with Channel Count
    switch(enumChannelCount)
    {
        case _AUDIO_CHANNEL_COUNT_MONO:

            pstAudioStatus->ucChannelNumber12 = 0x10;
            pstAudioStatus->ucChannelNumber34 = 0x00;
            pstAudioStatus->ucChannelNumber56 = 0x00;
            pstAudioStatus->ucChannelNumber78 = 0x00;

            break;

        case _AUDIO_CHANNEL_COUNT_2:

            pstAudioStatus->ucChannelNumber12 = 0x12;
            pstAudioStatus->ucChannelNumber34 = 0x00;
            pstAudioStatus->ucChannelNumber56 = 0x00;
            pstAudioStatus->ucChannelNumber78 = 0x00;

            break;

        case _AUDIO_CHANNEL_COUNT_3:

            pstAudioStatus->ucChannelNumber12 = 0x12;
            pstAudioStatus->ucChannelNumber34 = 0x30;
            pstAudioStatus->ucChannelNumber56 = 0x00;
            pstAudioStatus->ucChannelNumber78 = 0x00;

            break;

        case _AUDIO_CHANNEL_COUNT_4:

            pstAudioStatus->ucChannelNumber12 = 0x12;
            pstAudioStatus->ucChannelNumber34 = 0x34;
            pstAudioStatus->ucChannelNumber56 = 0x00;
            pstAudioStatus->ucChannelNumber78 = 0x00;

            break;

        case _AUDIO_CHANNEL_COUNT_5:

            pstAudioStatus->ucChannelNumber12 = 0x12;
            pstAudioStatus->ucChannelNumber34 = 0x34;
            pstAudioStatus->ucChannelNumber56 = 0x50;
            pstAudioStatus->ucChannelNumber78 = 0x00;

            break;

        case _AUDIO_CHANNEL_COUNT_6:

            pstAudioStatus->ucChannelNumber12 = 0x12;
            pstAudioStatus->ucChannelNumber34 = 0x34;
            pstAudioStatus->ucChannelNumber56 = 0x56;
            pstAudioStatus->ucChannelNumber78 = 0x00;

            break;

        case _AUDIO_CHANNEL_COUNT_7:

            pstAudioStatus->ucChannelNumber12 = 0x12;
            pstAudioStatus->ucChannelNumber34 = 0x34;
            pstAudioStatus->ucChannelNumber56 = 0x56;
            pstAudioStatus->ucChannelNumber78 = 0x70;

            break;

        case _AUDIO_CHANNEL_COUNT_8:

            pstAudioStatus->ucChannelNumber12 = 0x12;
            pstAudioStatus->ucChannelNumber34 = 0x34;
            pstAudioStatus->ucChannelNumber56 = 0x56;
            pstAudioStatus->ucChannelNumber78 = 0x78;

            break;

        default:

            // Set 2-Ch Audio
            pstAudioStatus->ucChannelNumber12 = 0x12;
            pstAudioStatus->ucChannelNumber34 = 0x00;
            pstAudioStatus->ucChannelNumber56 = 0x00;
            pstAudioStatus->ucChannelNumber78 = 0x00;

            break;
    }
}
#endif // End of #if(_HW_DP_AUDIO_CHANNEL_STATUS_1S1D2S_RECEIVE_SUPPORT == _OFF)
#endif // End of #if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif // End of #if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioInitial(void)
{
    ScalerAudioDigitalAudioInitial();

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
    ScalerAudioTtsInitial();
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

    ScalerAudioDVCInitial();
}

//--------------------------------------------------
// Description  : Audio Clcok Gatting Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioClockGatting(bit bEnable)
{
    if(bEnable == _DISABLE)
    {
        if(ScalerGetBit(P6_D5_SOFT_RESET_DAC, _BIT0) == 0x00)
        {
            // Disable Clcok Gatting
            ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~_BIT0, _BIT0);
        }
    }
    else
    {
        if(ScalerGetBit(P6_D5_SOFT_RESET_DAC, _BIT0) == _BIT0)
        {
            // Enable Clcok Gatting
            ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~_BIT0, 0x00);
        }
    }
}

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FW tracking Handler(fs <= 48kHz)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioFwTrackingHandler(void)
{
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
    if((GET_HDMI_AUDIO_RX3_FW_TRACKING_RESET() == _FALSE) && (GET_HDMI_AUDIO_RX3_SAMPLING_FREQ() <= _AUDIO_FREQ_48K))
    {
        // FW Tracking mode active only when fs <= 48kHz
        ScalerHdmiAudioRx3FwTrackingHandler();
    }
    else // FW Tracking mode reset
    {
        // Audio Tracking Reset
        ScalerHdmiAudioRx3FwTrackingReset();

        DebugMessageAudio("RX3 Audio: FW Tracking End", GET_HDMI_AUDIO_RX3_SAMPLING_FREQ());
    }
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
    if((GET_HDMI_AUDIO_RX4_FW_TRACKING_RESET() == _FALSE) && (GET_HDMI_AUDIO_RX4_SAMPLING_FREQ() <= _AUDIO_FREQ_48K))
    {
        // FW Tracking mode active only when fs <= 48kHz
        ScalerHdmiAudioRx4FwTrackingHandler();
    }
    else // FW Tracking mode reset
    {
        // Audio Tracking Reset
        ScalerHdmiAudioRx4FwTrackingReset();

        DebugMessageAudio("RX4 Audio: FW Tracking End", GET_HDMI_AUDIO_RX4_SAMPLING_FREQ());
    }
#endif
}
#endif // End of #if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FW tracking Handler(fs <= 48kHz)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioSpreadPcodeEnable(EnumAudioInputPort enumAudioInputPort)
{
    switch(enumAudioInputPort)
    {
        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
            {
                if(ScalerHdmiAudioRx3CheckNfCodeStable() == _FALSE)
                {
                    ScalerTimerActiveTimerEvent(200, _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_ENABLE_SPREAD_P_CODE);
                    g_ucAudioRx3PllStableCnt++;
                }
                else
                {
                    // Enable P Code Spread
                    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_E2_PORT_PAGE77_P_SPREAD_0, ~_BIT7, _BIT7);
                    g_ucAudioRx3PllStableCnt = 0x00;
                }
            }
            else
#endif
            {
                if(ScalerHdmiAudioRx3CheckNfCodeStable() == _FALSE)
                {
                    ScalerTimerActiveTimerEvent(200, _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_ENABLE_SPREAD_P_CODE);
                    g_ucAudioRx3PllStableCnt++;
                }
                else
                {
                    // Enable P Code Spread
                    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_E2_PORT_PAGE72_P_SPREAD_0, ~_BIT7, _BIT7);
                    g_ucAudioRx3PllStableCnt = 0x00;
                }
            }

#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX4_VERSION() == _AUDIO_INPUT_FROM_FRL)
            {
                if(ScalerHdmiAudioRx4CheckNfCodeStable() == _FALSE)
                {
                    ScalerTimerActiveTimerEvent(200, _SCALER_TIMER_EVENT_HDMI_AUDIO_RX4_ENABLE_SPREAD_P_CODE);
                    g_ucAudioRx4PllStableCnt++;
                }
                else
                {
                    // Enable P Code Spread
                    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_E2_PORT_PAGE78_P_SPREAD_0, ~_BIT7, _BIT7);
                    g_ucAudioRx4PllStableCnt = 0x00;
                }
            }
            else
#endif
            {
                if(ScalerHdmiAudioRx4CheckNfCodeStable() == _FALSE)
                {
                    ScalerTimerActiveTimerEvent(200, _SCALER_TIMER_EVENT_HDMI_AUDIO_RX4_ENABLE_SPREAD_P_CODE);
                    g_ucAudioRx4PllStableCnt++;
                }
                else
                {
                    // Enable P Code Spread
                    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_E2_PORT_PAGE73_P_SPREAD_0, ~_BIT7, _BIT7);
                    g_ucAudioRx4PllStableCnt = 0x00;
                }
            }

#endif
            break;

        default:
            break;
    }

    switch(enumAudioInputPort)
    {
        case _AUDIO_FROM_RX3_PORT:
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
            if(g_ucAudioRx3PllStableCnt == 0x08)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_ENABLE_SPREAD_P_CODE);

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
                if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
                {
                    // Enable P Code Spread
                    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_E2_PORT_PAGE77_P_SPREAD_0, ~_BIT7, _BIT7);
                    g_ucAudioRx3PllStableCnt = 0x00;
                }
                else
#endif
                {
                    // Enable P Code Spread
                    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_E2_PORT_PAGE72_P_SPREAD_0, ~_BIT7, _BIT7);
                    g_ucAudioRx3PllStableCnt = 0x00;
                }
            }
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:
#if(_HDMI_MAC_RX4_SUPPORT == _ON)
            if(g_ucAudioRx4PllStableCnt == 0x08)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_AUDIO_RX4_ENABLE_SPREAD_P_CODE);

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
                if(GET_HDMI_AUDIO_RX4_VERSION() == _AUDIO_INPUT_FROM_FRL)
                {
                    // Enable P Code Spread
                    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_E2_PORT_PAGE78_P_SPREAD_0, ~_BIT7, _BIT7);
                    g_ucAudioRx4PllStableCnt = 0x00;
                }
                else
#endif
                {
                    // Enable P Code Spread
                    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_E2_PORT_PAGE73_P_SPREAD_0, ~_BIT7, _BIT7);
                    g_ucAudioRx4PllStableCnt = 0x00;
                }
            }
#endif
            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Initial HDMI/DP audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalAudioInitial(void)
{
#if(_DP_MAC_RX0_SUPPORT == _ON)
    ScalerDpAudioRx0AudioInitial();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
    ScalerDpAudioRx1AudioInitial();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
    ScalerDpAudioRx2AudioInitial();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
    ScalerDpAudioRx3AudioInitial();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
    ScalerDpAudioRx4AudioInitial();
#endif

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    // Choose HDMI2.0 Mac as Default
    SET_HDMI_AUDIO_RX3_VERSION(_AUDIO_INPUT_FROM_TMDS);
#endif

    ScalerHdmiAudioRx3Initial();
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
    // Choose HDMI2.0 Mac as Default
    SET_HDMI_AUDIO_RX4_VERSION(_AUDIO_INPUT_FROM_TMDS);
#endif

    ScalerHdmiAudioRx4Initial();
#endif

#if((_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))
    ScalerAudioSetInternalGenTestUserState(_OFF);
#endif
}

//--------------------------------------------------
// Description  : Detect digital audio for HDMI/DP interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalDetect(void)
{
#if(_DP_MAC_RX0_SUPPORT == _ON)
    ScalerDpAudioRx0DigitalDetectProc();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
    ScalerDpAudioRx1DigitalDetectProc();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
    ScalerDpAudioRx2DigitalDetectProc();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
    ScalerDpAudioRx3DigitalDetectProc();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
    ScalerDpAudioRx4DigitalDetectProc();
#endif

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
    ScalerHdmiAudioRx3DigitalDetectProc();
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
    ScalerHdmiAudioRx4DigitalDetectProc();
#endif
}

//--------------------------------------------------
// Description  : Get Current Digital Audio Source
// Input Value  : None
// Output Value : Digital Audio Source
//--------------------------------------------------
BYTE ScalerAudioGetDigitalAudioSource(EnumInputPort enumInputPort)
{
    switch((ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT)))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _AUDIO_FROM_RX0_PORT:

            return GET_DP_AUDIO_RX0_DIGITAL_SOURCE();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _AUDIO_FROM_RX1_PORT:

            return GET_DP_AUDIO_RX1_DIGITAL_SOURCE();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _AUDIO_FROM_RX2_PORT:

            return GET_DP_AUDIO_RX2_DIGITAL_SOURCE();
#endif

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _AUDIO_FROM_RX3_PORT:

            return GET_HDMI_AUDIO_RX3_DIGITAL_SOURCE();
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _AUDIO_FROM_RX4_PORT:

            return GET_HDMI_AUDIO_RX4_DIGITAL_SOURCE();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _AUDIO_FROM_PXP_PORT:

            return GET_DP_AUDIO_RX3_DIGITAL_SOURCE();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _AUDIO_FROM_MST2SST_PORT:

            return GET_DP_AUDIO_RX4_DIGITAL_SOURCE();
#endif

        default:
            break;
    }

    return _DIGITAL_AUDIO_SOURCE_NONE;
}

//--------------------------------------------------
// Description  : Disable Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDisableAudioPLL(void)
{
#if(_LINE_IN_SUPPORT == _ON)
    // Power Down ADC PLL
    ScalerSetBit(PBF_A8_AUDIO_PLL_CONTROL, ~_BIT0, _BIT0);
#endif

#if(_DP_MAC_RX0_SUPPORT == _ON)
    // Power Down D0 DPLL
    ScalerDpAudioRx0AudioPLLPowerDown();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
    // Power Down D1 DPLL
    ScalerDpAudioRx1AudioPLLPowerDown();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
    // Power Down D2 DPLL
    ScalerDpAudioRx2AudioPLLPowerDown();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
    // Power Down PXP DPLL
    ScalerDpAudioRx3AudioPLLPowerDown();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
    // Power Down MST2SST DPLL
    ScalerDpAudioRx4AudioPLLPowerDown();
#endif

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
    // Power Down D3 DPLL
    ScalerSetBit(P72_87_PORT_PAGE72_HDMI_DPLL_ANASET_1, ~_BIT0, _BIT0);
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
    // Power Down D4 DPLL
    ScalerSetBit(P73_87_PORT_PAGE73_HDMI_DPLL_ANASET_1, ~_BIT0, _BIT0);
#endif
}

//--------------------------------------------------
// Description  : Switch Audio Input Port For Each Audio Output
// Input Value  : ucAudioOutput, ucAudioInput
// Output Value : None
//--------------------------------------------------
void ScalerAudioInputPortSwitch(EnumAudioInputPort enumAudioInput)
{
    // Set DAC Input
    ScalerSetBit(P6F_01_MUX_DA_DVC_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumAudioInput);

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _OFF)
    // Set IIS Input
    ScalerSetBit(P6F_00_MUX_DIG_OUT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (enumAudioInput << 4));

    // Set SPDIF Input
    ScalerSetBit(P6F_00_MUX_DIG_OUT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumAudioInput);
#endif

#if(_DP_TX_SUPPORT == _ON)
#if(_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _ON)
    // Set DP Tx Input
    ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumAudioInput);
#endif
#endif
}

//--------------------------------------------------
// Description  : Get if Digital Audio Port Changed
// Input Value  : enumInputPort
// Output Value : _TRUE of _FALSE
//--------------------------------------------------
bit ScalerAudioGetAudioInputPortChanged(EnumAudioInputSource enumAudioSourceType, EnumInputPort enumInputPort)
{
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioGetInternalAudioGenEnable(enumInputPort) == _ENABLE)
    {
        // Avoid Port Switching when in audio gen play
        return _FALSE;
    }
#endif

#if(_LINE_IN_SUPPORT == _ON)
    if(enumAudioSourceType != ScalerAudioGetInputSource(_AUDIO_DAC_OUT))
    {
        return _TRUE;
    }
#endif

    if(enumAudioSourceType == _DIGITAL_AUDIO)
    {
        if(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_TARGET) != ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT))
        {
            return _TRUE;
        }
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Get if Digital Audio Port Changed
// Input Value  : enumInputPort, bTarget(Target or Current)
// Output Value : _TRUE of _FALSE
//--------------------------------------------------
EnumAudioInputPort ScalerAudioDxToRxMapping(EnumInputPort enumInputPort, EnumAudioPortMapType enumAudioPortMapType)
{
    EnumAudioInputPort enumAudioInput = _AUDIO_FROM_RX0_PORT;

    enumAudioPortMapType = enumAudioPortMapType;

    switch(enumInputPort)
    {
#if((_LINE_IN_SUPPORT == _ON) && (_VGA_SUPPORT == _ON))
        case _A0_INPUT_PORT:
            enumAudioInput = _AUDIO_FROM_ADC_PORT;
            break;
#endif

#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            switch(ScalerDpRxGetMacSwitch(_D0_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    enumAudioInput = _AUDIO_FROM_RX0_PORT;
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    enumAudioInput = _AUDIO_FROM_RX1_PORT;
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    enumAudioInput = _AUDIO_FROM_RX2_PORT;
                    break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
                case _DP_MAC_3:
                    enumAudioInput = _AUDIO_FROM_PXP_PORT;
                    break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
                case _DP_MAC_4:
                    enumAudioInput = _AUDIO_FROM_MST2SST_PORT;
                    break;
#endif

                default:
                    break;
            }
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            switch(ScalerDpRxGetMacSwitch(_D1_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    enumAudioInput = _AUDIO_FROM_RX0_PORT;
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    enumAudioInput = _AUDIO_FROM_RX1_PORT;
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    enumAudioInput = _AUDIO_FROM_RX2_PORT;
                    break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
                case _DP_MAC_3:
                    enumAudioInput = _AUDIO_FROM_PXP_PORT;
                    break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
                case _DP_MAC_4:
                    enumAudioInput = _AUDIO_FROM_MST2SST_PORT;
                    break;
#endif

                default:
                    break;
            }
            break;
#elif(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            switch(ScalerTmdsMacRxDxRxMapping(_D1_INPUT_PORT))
            {
                case _RX3:
                    enumAudioInput = _AUDIO_FROM_RX3_PORT;
                    break;
                case _RX4:
                    enumAudioInput = _AUDIO_FROM_RX4_PORT;
                    break;
                default:
                    break;
            }
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            switch(ScalerDpRxGetMacSwitch(_D2_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    enumAudioInput = _AUDIO_FROM_RX0_PORT;
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    enumAudioInput = _AUDIO_FROM_RX1_PORT;
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    enumAudioInput = _AUDIO_FROM_RX2_PORT;
                    break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
                case _DP_MAC_3:
                    enumAudioInput = _AUDIO_FROM_PXP_PORT;
                    break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
                case _DP_MAC_4:
                    enumAudioInput = _AUDIO_FROM_MST2SST_PORT;
                    break;
#endif

                default:
                    break;
            }
            break;

#elif(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            switch(ScalerTmdsMacRxDxRxMapping(_D2_INPUT_PORT))
            {
                case _RX3:
                    enumAudioInput = _AUDIO_FROM_RX3_PORT;
                    break;
                case _RX4:
                    enumAudioInput = _AUDIO_FROM_RX4_PORT;
                    break;
                default:
                    break;
            }
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            switch(ScalerTmdsMacRxDxRxMapping(_D3_INPUT_PORT))
            {
                case _RX3:
                    enumAudioInput = _AUDIO_FROM_RX3_PORT;
                    break;
                case _RX4:
                    enumAudioInput = _AUDIO_FROM_RX4_PORT;
                    break;
                default:
                    break;
            }
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            switch(ScalerTmdsMacRxDxRxMapping(_D4_INPUT_PORT))
            {
                case _RX3:
                    enumAudioInput = _AUDIO_FROM_RX3_PORT;
                    break;
                case _RX4:
                    enumAudioInput = _AUDIO_FROM_RX4_PORT;
                    break;
                default:
                    break;
            }
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            switch(ScalerTmdsMacRxDxRxMapping(_D5_INPUT_PORT))
            {
                case _RX3:
                    enumAudioInput = _AUDIO_FROM_RX3_PORT;
                    break;
                case _RX4:
                    enumAudioInput = _AUDIO_FROM_RX4_PORT;
                    break;
                default:
                    break;
            }
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:
            switch(ScalerDpRxGetMacSwitch(GET_DUAL_DP_PORT_SWITCH_SELECT()))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    enumAudioInput = _AUDIO_FROM_RX0_PORT;
                    break;
#endif
#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    enumAudioInput = _AUDIO_FROM_RX1_PORT;
                    break;
#endif
#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    enumAudioInput = _AUDIO_FROM_RX2_PORT;
                    break;
#endif
                case _DP_MAC_DUAL:
                    if(enumAudioPortMapType == _AUDIO_PORT_MAP_TO_CURRENT)
                    {
                        enumAudioInput = ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT);
                    }
                    else
                    {
#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
                        if(GET_DP_AUDIO_RX0_PACKET_DETECT() == _TRUE)
                        {
                            enumAudioInput = _AUDIO_FROM_RX0_PORT;
                        }
                        else if(GET_DP_AUDIO_RX1_PACKET_DETECT() == _TRUE)
                        {
                            enumAudioInput = _AUDIO_FROM_RX1_PORT;
                        }
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
                        if(GET_DP_AUDIO_RX1_PACKET_DETECT() == _TRUE)
                        {
                            enumAudioInput = _AUDIO_FROM_RX1_PORT;
                        }
                        else if(GET_DP_AUDIO_RX2_PACKET_DETECT() == _TRUE)
                        {
                            enumAudioInput = _AUDIO_FROM_RX2_PORT;
                        }
#endif
                    }
                    break;
                default:
                    break;
            }
            break;
#endif

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
#if(_D9_DP_SUPPORT == _ON)
        case _D9_INPUT_PORT:

            switch(ScalerDpRxGetMacSwitch(_D9_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    enumAudioInput = _AUDIO_FROM_RX0_PORT;
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    enumAudioInput = _AUDIO_FROM_RX1_PORT;
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    enumAudioInput = _AUDIO_FROM_RX2_PORT;
                    break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
                case _DP_MAC_3:
                    enumAudioInput = _AUDIO_FROM_PXP_PORT;
                    break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
                case _DP_MAC_4:
                    enumAudioInput = _AUDIO_FROM_MST2SST_PORT;
                    break;
#endif

                default:
                    break;
            }
            break;
#endif
#endif

        default:
            break;
    }

    return enumAudioInput;
}

//--------------------------------------------------
// Description  : Set User Define Audio Frequency S/N.F Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioSyncUserDefineFrequencyPllSetting(void)
{
#if(_DP_MAC_RX0_SUPPORT == _ON)
    ScalerDpAudioRx0SyncUserDefineFrequencyPllSetting();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
    ScalerDpAudioRx1SyncUserDefineFrequencyPllSetting();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
    ScalerDpAudioRx2SyncUserDefineFrequencyPllSetting();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
    ScalerDpAudioRx3SyncUserDefineFrequencyPllSetting();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
    ScalerDpAudioRx4SyncUserDefineFrequencyPllSetting();
#endif

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
    ScalerHdmiAudioRx3SyncUserDefineFrequencyPllSetting();
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
    ScalerHdmiAudioRx4SyncUserDefineFrequencyPllSetting();
#endif
}

//--------------------------------------------------
// Description  : SPDIF/IIS Output By Channel Allocation
// Input Value  : Channel Allocation
// Output Value : Which channel need active
//--------------------------------------------------
BYTE ScalerAudioChannelOutputSel(BYTE ucCa)
{
    // ucRseult[0/1/2/3] = SPDIF/IIS Lane 4/3/2/1
    BYTE ucResult = 0x0F;

    switch(ucCa)
    {
        case 0x01:
        case 0x02:
        case 0x03:

            // Lane1,2
            ucResult = 0x03;
            break;

        case 0x04:
        case 0x08:

            // Lane1,3
            ucResult = 0x05;
            break;

        case 0x05:
        case 0x06:
        case 0x07:
        case 0x09:
        case 0x0A:
        case 0x0B:

            // Lane1,2,3
            ucResult = 0x07;
            break;

        case 0x14:

            // Lane1,4
            ucResult = 0x09;
            break;

        case 0x15:
        case 0x16:
        case 0x17:

            // Lane1,2,4
            ucResult = 0x0B;
            break;

        case 0x0C:
        case 0x10:
        case 0x18:
        case 0x1C:
        case 0x24:
        case 0x26:

            // Lane1,3,4
            ucResult = 0x0D;
            break;

        case 0x0D:
        case 0x0E:
        case 0x0F:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x25:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        case 0x2D:
        case 0x2E:
        case 0x2F:
        case 0x30:
        case 0x31:

            // Lane1,2,3,4
            ucResult = 0x0F;
            break;

        default:
            break;
    }

    return ucResult;
}

//--------------------------------------------------
// Description  : Get Current Audio Port For Output Type
// Input Value  : None
// Output Value : audio port
//--------------------------------------------------
EnumAudioInputPort ScalerAudioGetDigitalAudioPort_EXINT0(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
            return (EnumAudioInputPort)(ScalerGetBit_EXINT(P6F_01_MUX_DA_DVC_IN, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        case _AUDIO_I2S_OUT:
            return (EnumAudioInputPort)(ScalerGetBit_EXINT(P6F_00_MUX_DIG_OUT, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

        case _AUDIO_SPDIF_OUT:
            return (EnumAudioInputPort)(ScalerGetBit_EXINT(P6F_00_MUX_DIG_OUT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        case _AUDIO_DPTX_OUT:
            return (EnumAudioInputPort)(ScalerGetBit_EXINT(P6F_02_MUX_DP_I2S_IN, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
            return (EnumAudioInputPort)(ScalerGetBit_EXINT(P6F_01_MUX_DA_DVC_IN, (_BIT7 | _BIT6 | _BIT5)) >> 5);
#else
#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
            if(ScalerGetBit_EXINT(P6F_00_MUX_DIG_OUT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT1))
            {
#if(_LINE_IN_SUPPORT == _ON)
                // Check really ADC Path? (Path for adjusting volume through embedded DVC)
                if(ScalerAudioGetInputSource_EXINT0(_AUDIO_ARC_OUT) == _LINE_IN_AUDIO)
                {
                    // ADC Path
                    return _AUDIO_FROM_ADC_PORT;
                }
                else
#endif
                {
                    // Check DVC Input
                    return (EnumAudioInputPort)(ScalerGetBit_EXINT(P6F_01_MUX_DA_DVC_IN, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
                }
            }
            else
#endif
            {
                return (EnumAudioInputPort)(ScalerGetBit_EXINT(P6F_00_MUX_DIG_OUT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
            }
#endif
#endif

        default:
            break;
    }

    return _AUDIO_FROM_RX0_PORT;
}

//--------------------------------------------------
// Description  : Get if Digital Audio Port Changed
// Input Value  : enumInputPort, bTarget(Target or Current)
// Output Value : _TRUE of _FALSE
//--------------------------------------------------
EnumAudioInputPort ScalerAudioDxToRxMapping_EXINT0(EnumInputPort enumInputPort, EnumAudioPortMapType enumAudioPortMapType)
{
    EnumAudioInputPort enumAudioInput = _AUDIO_FROM_RX0_PORT;

    enumAudioPortMapType = enumAudioPortMapType;

    switch(enumInputPort)
    {
#if((_LINE_IN_SUPPORT == _ON) && (_VGA_SUPPORT == _ON))
        case _A0_INPUT_PORT:
            enumAudioInput = _AUDIO_FROM_ADC_PORT;
            break;
#endif

#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            switch(ScalerDpRxGetMacSwitch_EXINT0(_D0_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    enumAudioInput = _AUDIO_FROM_RX0_PORT;
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    enumAudioInput = _AUDIO_FROM_RX1_PORT;
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    enumAudioInput = _AUDIO_FROM_RX2_PORT;
                    break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
                case _DP_MAC_3:
                    enumAudioInput = _AUDIO_FROM_PXP_PORT;
                    break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
                case _DP_MAC_4:
                    enumAudioInput = _AUDIO_FROM_MST2SST_PORT;
                    break;
#endif

                default:
                    break;
            }
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            switch(ScalerDpRxGetMacSwitch_EXINT0(_D1_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    enumAudioInput = _AUDIO_FROM_RX0_PORT;
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    enumAudioInput = _AUDIO_FROM_RX1_PORT;
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    enumAudioInput = _AUDIO_FROM_RX2_PORT;
                    break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
                case _DP_MAC_3:
                    enumAudioInput = _AUDIO_FROM_PXP_PORT;
                    break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
                case _DP_MAC_4:
                    enumAudioInput = _AUDIO_FROM_MST2SST_PORT;
                    break;
#endif

                default:
                    break;
            }
            break;
#elif(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            switch(ScalerTmdsMacRxDxRxMapping_EXINT0(_D1_INPUT_PORT))
            {
                case _RX3:
                    enumAudioInput = _AUDIO_FROM_RX3_PORT;
                    break;
                case _RX4:
                    enumAudioInput = _AUDIO_FROM_RX4_PORT;
                    break;
                default:
                    break;
            }
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            switch(ScalerDpRxGetMacSwitch_EXINT0(_D2_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    enumAudioInput = _AUDIO_FROM_RX0_PORT;
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    enumAudioInput = _AUDIO_FROM_RX1_PORT;
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    enumAudioInput = _AUDIO_FROM_RX2_PORT;
                    break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
                case _DP_MAC_3:
                    enumAudioInput = _AUDIO_FROM_PXP_PORT;
                    break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
                case _DP_MAC_4:
                    enumAudioInput = _AUDIO_FROM_MST2SST_PORT;
                    break;
#endif

                default:
                    break;
            }
            break;

#elif(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            switch(ScalerTmdsMacRxDxRxMapping_EXINT0(_D2_INPUT_PORT))
            {
                case _RX3:
                    enumAudioInput = _AUDIO_FROM_RX3_PORT;
                    break;
                case _RX4:
                    enumAudioInput = _AUDIO_FROM_RX4_PORT;
                    break;
                default:
                    break;
            }
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            switch(ScalerTmdsMacRxDxRxMapping_EXINT0(_D3_INPUT_PORT))
            {
                case _RX3:
                    enumAudioInput = _AUDIO_FROM_RX3_PORT;
                    break;
                case _RX4:
                    enumAudioInput = _AUDIO_FROM_RX4_PORT;
                    break;
                default:
                    break;
            }
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            switch(ScalerTmdsMacRxDxRxMapping_EXINT0(_D4_INPUT_PORT))
            {
                case _RX3:
                    enumAudioInput = _AUDIO_FROM_RX3_PORT;
                    break;
                case _RX4:
                    enumAudioInput = _AUDIO_FROM_RX4_PORT;
                    break;
                default:
                    break;
            }
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            switch(ScalerTmdsMacRxDxRxMapping_EXINT0(_D5_INPUT_PORT))
            {
                case _RX3:
                    enumAudioInput = _AUDIO_FROM_RX3_PORT;
                    break;
                case _RX4:
                    enumAudioInput = _AUDIO_FROM_RX4_PORT;
                    break;
                default:
                    break;
            }
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:
            switch(ScalerDpRxGetMacSwitch_EXINT0(GET_DUAL_DP_PORT_SWITCH_SELECT()))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    enumAudioInput = _AUDIO_FROM_RX0_PORT;
                    break;
#endif
#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    enumAudioInput = _AUDIO_FROM_RX1_PORT;
                    break;
#endif
#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    enumAudioInput = _AUDIO_FROM_RX2_PORT;
                    break;
#endif
                case _DP_MAC_DUAL:
                    if(enumAudioPortMapType == _AUDIO_PORT_MAP_TO_CURRENT)
                    {
                        enumAudioInput = ScalerAudioGetDigitalAudioPort_EXINT0(_AUDIO_DAC_OUT);
                    }
                    else
                    {
#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
                        if(GET_DP_AUDIO_RX0_PACKET_DETECT() == _TRUE)
                        {
                            enumAudioInput = _AUDIO_FROM_RX0_PORT;
                        }
                        else if(GET_DP_AUDIO_RX1_PACKET_DETECT() == _TRUE)
                        {
                            enumAudioInput = _AUDIO_FROM_RX1_PORT;
                        }
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
                        if(GET_DP_AUDIO_RX1_PACKET_DETECT() == _TRUE)
                        {
                            enumAudioInput = _AUDIO_FROM_RX1_PORT;
                        }
                        else if(GET_DP_AUDIO_RX2_PACKET_DETECT() == _TRUE)
                        {
                            enumAudioInput = _AUDIO_FROM_RX2_PORT;
                        }
#endif
                    }
                    break;
                default:
                    break;
            }
            break;
#endif

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
#if(_D9_DP_SUPPORT == _ON)
        case _D9_INPUT_PORT:

            switch(ScalerDpRxGetMacSwitch_EXINT0(_D9_INPUT_PORT))
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:
                    enumAudioInput = _AUDIO_FROM_RX0_PORT;
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:
                    enumAudioInput = _AUDIO_FROM_RX1_PORT;
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:
                    enumAudioInput = _AUDIO_FROM_RX2_PORT;
                    break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
                case _DP_MAC_3:
                    enumAudioInput = _AUDIO_FROM_PXP_PORT;
                    break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
                case _DP_MAC_4:
                    enumAudioInput = _AUDIO_FROM_MST2SST_PORT;
                    break;
#endif

                default:
                    break;
            }
            break;
#endif
#endif

        default:
            break;
    }

    return enumAudioInput;
}

//--------------------------------------------------
// Description  : Mode Switch Process by Port
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioModeSwitchProcess(EnumInputPort enumInputPort)
{
    switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        // While Rx3 HDMI Port HDMI2.0 <-> 2.1 Switch, Re-Initial Related Audio Reg
        case _AUDIO_FROM_RX3_PORT:

            ScalerHdmiAudioRx3SetVersion();
            ScalerHdmiAudioRx3Initial();

            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        // While Rx4 HDMI Port HDMI2.0 <-> 2.1 Switch, Re-Initial Related Audio Reg
        case _AUDIO_FROM_RX4_PORT:

            ScalerHdmiAudioRx4SetVersion();
            ScalerHdmiAudioRx4Initial();

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Switch Digital Audio Output Mute
// Input Value  : _ON => Mute On
// Output Value : None
//--------------------------------------------------
void ScalerAudioInputDigitalMute(bit bMute, EnumAudioOutputType enumAudioOutput)
{
    bMute = bMute;

    switch(ScalerAudioGetDigitalAudioPort(enumAudioOutput))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_MAC_RX0_SUPPORT == _ON)
            ScalerDpAudioRx0SetAudioOutputMute(bMute);
#endif
            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_MAC_RX1_SUPPORT == _ON)
            ScalerDpAudioRx1SetAudioOutputMute(bMute);
#endif
            break;

        case _AUDIO_FROM_RX2_PORT:

#if(_DP_MAC_RX2_SUPPORT == _ON)
            ScalerDpAudioRx2SetAudioOutputMute(bMute);
#endif
            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_MAC_RX3_SUPPORT == _ON)

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
            {
#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
                if(bMute == _OFF)
                {
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                    if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_E2_PORT_PAGE77_P_SPREAD_0, _BIT7) == 0x00)
                    {
                        // Enable P Code Spread
                        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_E2_PORT_PAGE77_P_SPREAD_0, ~_BIT7, _BIT7);
                    }
#else
                    g_ucAudioRx3PllStableCnt = 0x00;

                    // Enable P Code Spread
                    if(ScalerHdmiAudioRx3CheckNfCodeStable() == _FALSE)
                    {
                        ScalerTimerActiveTimerEvent(200, _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_ENABLE_SPREAD_P_CODE);
                    }
                    else
                    {
                        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_E2_PORT_PAGE77_P_SPREAD_0, ~_BIT7, _BIT7);
                    }
#endif
                }
                else
                {
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                    if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, _BIT6) == 0x00)
                    {
                        // Set X Value
                        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_32_PORT_PAGE77_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Set Y Value
                        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_33_PORT_PAGE77_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // audio hw mode
                        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~_BIT6, _BIT6);
                        // manual gain enable
                        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~_BIT3, _BIT3);

                        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_9F_PORT_PAGE77_PRESET_AFSM_MOD, ~_BIT5, _BIT5);

                        CLR_HDMI_RX3_HBR_AUDIO_IS_SETTING();

#if(_SCPU_SUPPORT == _ON)
                        SET_AUDIO_SCPU_AUDIO_STATE(_PARALLELMODE_HBR_IDLE_STATE);
#endif
                    }
#endif
                    // Disable P Code Spread
                    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_E2_PORT_PAGE77_P_SPREAD_0, ~_BIT7, 0x00);
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_ENABLE_SPREAD_P_CODE);
                }
#endif

                // HDMI MAC DVC Mute On/Off
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_07_PORT_PAGE77_HDMI_MAG_M_FINAL, ~(_BIT1 | _BIT0), (((!bMute) == _ENABLE) ? (_BIT1 | _BIT0) : 0x00));
                ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_08_PORT_PAGE77_HDMI_MAG_L_FINAL, 0x00);
                ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_09_PORT_PAGE77_HDMI_MAG_R_FINAL, 0x00);
            }
            else
#endif
            {
#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
                if(bMute == _OFF)
                {
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                    if(ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_E2_PORT_PAGE72_P_SPREAD_0, _BIT7) == 0x00)
                    {
                        // Enable P Code Spread
                        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_E2_PORT_PAGE72_P_SPREAD_0, ~_BIT7, _BIT7);
                    }
#else
                    g_ucAudioRx3PllStableCnt = 0x00;

                    // Enable P Code Spread
                    if(ScalerHdmiAudioRx3CheckNfCodeStable() == _FALSE)
                    {
                        ScalerTimerActiveTimerEvent(200, _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_ENABLE_SPREAD_P_CODE);
                    }
                    else
                    {
                        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_E2_PORT_PAGE72_P_SPREAD_0, ~_BIT7, _BIT7);
                    }
#endif
                }
                else
                {
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                    if(ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, _BIT6) == 0x00)
                    {
                        // Set X Value
                        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_32_PORT_PAGE72_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Set Y Value
                        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_33_PORT_PAGE72_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // audio hw mode
                        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~_BIT6, _BIT6);
                        // manual gain enable
                        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~_BIT3, _BIT3);

                        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_9F_PORT_PAGE72_PRESET_AFSM_MOD, ~_BIT5, _BIT5);

                        CLR_HDMI_RX3_HBR_AUDIO_IS_SETTING();

#if(_SCPU_SUPPORT == _ON)
                        SET_AUDIO_SCPU_AUDIO_STATE(_PARALLELMODE_HBR_IDLE_STATE);
#endif
                    }
#endif
                    // Disable P Code Spread
                    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_E2_PORT_PAGE72_P_SPREAD_0, ~_BIT7, 0x00);
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_ENABLE_SPREAD_P_CODE);
                }
#endif

                // HDMI MAC DVC Mute On/Off
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_07_PORT_PAGE72_HDMI_MAG_M_FINAL, ~(_BIT1 | _BIT0), (((!bMute) == _ENABLE) ? (_BIT1 | _BIT0) : 0x00));
                ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_08_PORT_PAGE72_HDMI_MAG_L_FINAL, 0x00);
                ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_09_PORT_PAGE72_HDMI_MAG_R_FINAL, 0x00);
            }

#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_MAC_RX4_SUPPORT == _ON)

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX4_VERSION() == _AUDIO_INPUT_FROM_FRL)
            {
#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
                if(bMute == _OFF)
                {
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                    if(ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_E2_PORT_PAGE78_P_SPREAD_0, _BIT7) == 0x00)
                    {
                        // Enable P Code Spread
                        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_E2_PORT_PAGE78_P_SPREAD_0, ~_BIT7, _BIT7);
                    }
#else
                    g_ucAudioRx4PllStableCnt = 0x00;

                    // Enable P Code Spread
                    if(ScalerHdmiAudioRx4CheckNfCodeStable() == _FALSE)
                    {
                        ScalerTimerActiveTimerEvent(200, _SCALER_TIMER_EVENT_HDMI_AUDIO_RX4_ENABLE_SPREAD_P_CODE);
                    }
                    else
                    {
                        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_E2_PORT_PAGE78_P_SPREAD_0, ~_BIT7, _BIT7);
                    }
#endif
                }
                else
                {
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                    if(ScalerGetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_03_PORT_PAGE78_HDMI_AFCR, _BIT6) == 0x00)
                    {
                        // Set X Value
                        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_32_PORT_PAGE78_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Set Y Value
                        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_33_PORT_PAGE78_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // audio hw mode
                        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_03_PORT_PAGE78_HDMI_AFCR, ~_BIT6, _BIT6);
                        // manual gain enable
                        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_03_PORT_PAGE78_HDMI_AFCR, ~_BIT3, _BIT3);

                        ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_9F_PORT_PAGE78_PRESET_AFSM_MOD, ~_BIT5, _BIT5);

                        CLR_HDMI_RX4_HBR_AUDIO_IS_SETTING();

#if(_SCPU_SUPPORT == _ON)
                        SET_AUDIO_SCPU_AUDIO_STATE(_PARALLELMODE_HBR_IDLE_STATE);
#endif
                    }
#endif
                    // Disable P Code Spread
                    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_E2_PORT_PAGE78_P_SPREAD_0, ~_BIT7, 0x00);
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_AUDIO_RX4_ENABLE_SPREAD_P_CODE);
                }
#endif

                // HDMI MAC DVC Mute On/Off
                ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_07_PORT_PAGE78_HDMI_MAG_M_FINAL, ~(_BIT1 | _BIT0), (((!bMute) == _ENABLE) ? (_BIT1 | _BIT0) : 0x00));
                ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_08_PORT_PAGE78_HDMI_MAG_L_FINAL, 0x00);
                ScalerSetDataPortByte(P78_C9_HDMI_AP, _P78_CA_PT_09_PORT_PAGE78_HDMI_MAG_R_FINAL, 0x00);
            }
            else
#endif
            {
#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
                if(bMute == _OFF)
                {
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                    if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_E2_PORT_PAGE73_P_SPREAD_0, _BIT7) == 0x00)
                    {
                        // Enable P Code Spread
                        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_E2_PORT_PAGE73_P_SPREAD_0, ~_BIT7, _BIT7);
                    }
#else
                    g_ucAudioRx4PllStableCnt = 0x00;

                    // Enable P Code Spread
                    if(ScalerHdmiAudioRx4CheckNfCodeStable() == _FALSE)
                    {
                        ScalerTimerActiveTimerEvent(200, _SCALER_TIMER_EVENT_HDMI_AUDIO_RX4_ENABLE_SPREAD_P_CODE);
                    }
                    else
                    {
                        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_E2_PORT_PAGE73_P_SPREAD_0, ~_BIT7, _BIT7);
                    }
#endif
                }
                else
                {
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                    if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_03_PORT_PAGE73_HDMI_AFCR, _BIT6) == 0x00)
                    {
                        // Set X Value
                        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_32_PORT_PAGE73_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Set Y Value
                        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_33_PORT_PAGE73_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // audio hw mode
                        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_03_PORT_PAGE73_HDMI_AFCR, ~_BIT6, _BIT6);
                        // manual gain enable
                        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_03_PORT_PAGE73_HDMI_AFCR, ~_BIT3, _BIT3);

                        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_9F_PORT_PAGE73_PRESET_AFSM_MOD, ~_BIT5, _BIT5);

                        CLR_HDMI_RX4_HBR_AUDIO_IS_SETTING();

#if(_SCPU_SUPPORT == _ON)
                        SET_AUDIO_SCPU_AUDIO_STATE(_PARALLELMODE_HBR_IDLE_STATE);
#endif
                    }
#endif
                    // Disable P Code Spread
                    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_E2_PORT_PAGE73_P_SPREAD_0, ~_BIT7, 0x00);
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_AUDIO_RX4_ENABLE_SPREAD_P_CODE);
                }
#endif

                // HDMI MAC DVC Mute On/Off
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_07_PORT_PAGE73_HDMI_MAG_M_FINAL, ~(_BIT1 | _BIT0), (((!bMute) == _ENABLE) ? (_BIT1 | _BIT0) : 0x00));
                ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_08_PORT_PAGE73_HDMI_MAG_L_FINAL, 0x00);
                ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_09_PORT_PAGE73_HDMI_MAG_R_FINAL, 0x00);
            }
#endif
            break;

        case _AUDIO_FROM_PXP_PORT:

#if(_DP_MAC_RX3_SUPPORT == _ON)
            ScalerDpAudioRx3SetAudioOutputMute(bMute);
#endif
            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_MAC_RX4_SUPPORT == _ON)
            ScalerDpAudioRx4SetAudioOutputMute(bMute);
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerAudioGetAudioDetected(EnumInputPort enumInputPort)
{
    switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _AUDIO_FROM_RX0_PORT:

            return ScalerDpAudioRx0GetAudioDetected();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _AUDIO_FROM_RX1_PORT:

            return ScalerDpAudioRx1GetAudioDetected();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _AUDIO_FROM_RX2_PORT:

            return ScalerDpAudioRx2GetAudioDetected();
#endif

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _AUDIO_FROM_RX3_PORT:

            return ScalerHdmiAudioRx3GetAudioDetected();
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _AUDIO_FROM_RX4_PORT:

            return ScalerHdmiAudioRx4GetAudioDetected();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _AUDIO_FROM_PXP_PORT:

            return ScalerDpAudioRx3GetAudioDetected();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _AUDIO_FROM_MST2SST_PORT:

            return ScalerDpAudioRx4GetAudioDetected();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Current Audio Port
// Input Value  : None
// Output Value : Digital Input Port
//--------------------------------------------------
EnumInputPort ScalerAudioGetDigitalAudioPortMapping(EnumAudioOutputType enumAudioOutput)
{
    switch(ScalerAudioGetDigitalAudioPort(enumAudioOutput))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_SUPPORT == _ON)
#if(_DUAL_DP_SUPPORT == _ON)
            return ((GET_AUDIO_DUAL_DP_STATUS() == _FALSE) ? _D0_INPUT_PORT : _DUAL_DP_INPUT_PORT);
#elif(_DP_MAC_RX0_SUPPORT == _ON)
            return ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0);
#endif
#endif
            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_SUPPORT == _ON)
#if(_DUAL_DP_SUPPORT == _ON)
            return ((GET_AUDIO_DUAL_DP_STATUS() == _FALSE) ? _D1_INPUT_PORT : _DUAL_DP_INPUT_PORT);
#elif(_DP_MAC_RX1_SUPPORT == _ON)
            return ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1);
#endif
#endif
            break;

        case _AUDIO_FROM_RX2_PORT:

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX2_SUPPORT == _ON))
            return ScalerDpRxMacGetInputPortSwitch(_DP_MAC_2);
#endif
            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_SUPPORT == _ON)
            return ScalerTmdsMacRxRxDxMapping(_RX3);
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_SUPPORT == _ON)
            return ScalerTmdsMacRxRxDxMapping(_RX4);
#endif
            break;

        case _AUDIO_FROM_PXP_PORT:

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX3_SUPPORT == _ON))
            return ScalerDpRxMacGetInputPortSwitch(_DP_MAC_3);
#endif
            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX4_SUPPORT == _ON))
            return ScalerDpRxMacGetInputPortSwitch(_DP_MAC_4);
#endif
            break;

        default:
            break;
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : Check Audio whether Audio LPCM By Audio Data
// Input Value  :None
// Output Value : _TRUE => LPCM / _FALSE => NON-LPCM
//--------------------------------------------------
bit ScalerAudioLPCMCheckData(EnumAudioOutputType enumAudioOutput)
{
    switch(ScalerAudioGetDigitalAudioPort(enumAudioOutput))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_MAC_RX0_SUPPORT == _ON)
            return ScalerDpAudioRx0LPCMCheckData();
#endif
            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_MAC_RX1_SUPPORT == _ON)
            return ScalerDpAudioRx1LPCMCheckData();
#endif
            break;

        case _AUDIO_FROM_RX2_PORT:

#if(_DP_MAC_RX2_SUPPORT == _ON)
            return ScalerDpAudioRx2LPCMCheckData();
#endif
            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_MAC_RX3_SUPPORT == _ON)

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                if(ScalerGetBit(P77_CB_HDMI_SR, _BIT4) == 0x00)
                {
                    return _TRUE;
                }
                else
                {
                    return _FALSE;
                }
            }
            else
#endif
            {
                if(ScalerGetBit(P72_CB_HDMI_SR, _BIT4) == 0x00)
                {
                    return _TRUE;
                }
                else
                {
                    return _FALSE;
                }
            }

#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_MAC_RX4_SUPPORT == _ON)

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6)
            {
                if(ScalerGetBit(P78_CB_HDMI_SR, _BIT4) == 0x00)
                {
                    return _TRUE;
                }
                else
                {
                    return _FALSE;
                }
            }
            else
#endif
            {
                if(ScalerGetBit(P73_CB_HDMI_SR, _BIT4) == 0x00)
                {
                    return _TRUE;
                }
                else
                {
                    return _FALSE;
                }
            }
#endif
            break;

        case _AUDIO_FROM_PXP_PORT:

#if(_DP_MAC_RX3_SUPPORT == _ON)
            return ScalerDpAudioRx3LPCMCheckData();
#endif
            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_MAC_RX4_SUPPORT == _ON)
            return ScalerDpAudioRx4LPCMCheckData();
#endif
            break;

        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Audio Coding Change or Not
// Input Value  : None
// Output Value : _TRUE => LPCM / _FALSE => Un-Change
//--------------------------------------------------
bit ScalerAudioLPCMCheckChange(EnumAudioOutputType enumAudioOutput)
{
    switch(ScalerAudioGetDigitalAudioPort(enumAudioOutput))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_MAC_RX0_SUPPORT == _ON)

            return ScalerDpAudioRx0LPCMCheckChange();

#endif
            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_MAC_RX1_SUPPORT == _ON)

            return ScalerDpAudioRx1LPCMCheckChange();

#endif

            break;

        case _AUDIO_FROM_RX2_PORT:

#if(_DP_MAC_RX2_SUPPORT == _ON)

            return ScalerDpAudioRx2LPCMCheckChange();

#endif

            break;

        case _AUDIO_FROM_RX3_PORT:

            break;

        case _AUDIO_FROM_RX4_PORT:

            break;

        case _AUDIO_FROM_RX5_PORT:

            break;

        case _AUDIO_FROM_PXP_PORT:

#if(_DP_MAC_RX3_SUPPORT == _ON)

            return ScalerDpAudioRx3LPCMCheckChange();

#endif
            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_MAC_RX4_SUPPORT == _ON)

            return ScalerDpAudioRx4LPCMCheckChange();

#endif
            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Reset Audio Coding Type Detect INT
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioLPCMResetProc(EnumInputPort enumInputPort, EnumAudioOutputType enumAudioOutput)
{
    enumAudioOutput = enumAudioOutput;

#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource(enumAudioOutput) == _DIGITAL_AUDIO)
#endif
    {
        switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
        {
            case _AUDIO_FROM_RX0_PORT:

#if(_DP_MAC_RX0_SUPPORT == _ON)

                ScalerDpAudioRx0LPCMResetProc();

#endif
                break;

            case _AUDIO_FROM_RX1_PORT:

#if(_DP_MAC_RX1_SUPPORT == _ON)

                ScalerDpAudioRx1LPCMResetProc();

#endif

                break;

            case _AUDIO_FROM_RX2_PORT:

#if(_DP_MAC_RX2_SUPPORT == _ON)

                ScalerDpAudioRx2LPCMResetProc();

#endif

                break;

            case _AUDIO_FROM_RX3_PORT:

                break;

            case _AUDIO_FROM_RX4_PORT:

                break;

            case _AUDIO_FROM_RX5_PORT:

                break;

            case _AUDIO_FROM_PXP_PORT:

#if(_DP_MAC_RX3_SUPPORT == _ON)

                ScalerDpAudioRx3LPCMResetProc();

#endif
                break;

            case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_MAC_RX4_SUPPORT == _ON)

                ScalerDpAudioRx4LPCMResetProc();

#endif
                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Get Current Digital Audio LPCM status
// Input Value  : None
// Output Value : Digital Audio Source
//--------------------------------------------------
EnumAudioCodingType ScalerAudioGetNonLPCMStatus(void)
{
    if(ScalerAudioLPCMCheckData(_AUDIO_DAC_OUT) == _TRUE)
    {
#if(_HDMI_SUPPORT == _ON)
        if(ScalerAudioDigitalAudioSourceType(_AUDIO_DAC_OUT) == _SOURCE_HDMI)
        {
            if(ScalerAudioLPCMCheckInfo(_AUDIO_DAC_OUT) == _TRUE)
            {
                return _AUDIO_LPCM;
            }
            else
            {
                return _AUDIO_NON_LPCM;
            }
        }
#endif
        return _AUDIO_LPCM;
    }
    return _AUDIO_NON_LPCM;
}

//--------------------------------------------------
// Description  : Get Current Path Non LPCM status
// Input Value  : None
// Output Value : Digital Audio Source
//--------------------------------------------------
EnumAudioCodingType ScalerAudioGetPathNonLPCMStatus(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
            return ScalerAudioGetNonLPCMStatus();
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
            return ScalerAudioGetArcNonLPCMStatus();
            break;
#endif
        default:
            break;
    }
    return _AUDIO_NON_LPCM;
}

//--------------------------------------------------
// Description  : Detect Audio Sampling Freq
// Input Value  : enumInputPort
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqPacket ScalerAudioSamplingFreqDetect(EnumInputPort enumInputPort)
{
    // Initial the value for checker
    EnumAudioSamplingFreqType enumSamplingFreqType = _AUDIO_FREQ_NO_AUDIO;

    switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_MAC_RX0_SUPPORT == _ON)
            enumSamplingFreqType = ScalerDpAudioRx0SamplingFreqDetect();
#endif
            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_MAC_RX1_SUPPORT == _ON)
            enumSamplingFreqType = ScalerDpAudioRx1SamplingFreqDetect();
#endif
            break;

        case _AUDIO_FROM_RX2_PORT:

#if(_DP_MAC_RX2_SUPPORT == _ON)
            enumSamplingFreqType = ScalerDpAudioRx2SamplingFreqDetect();
#endif
            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
            enumSamplingFreqType = ScalerHdmiAudioRx3SamplingFreqDetect();
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
            enumSamplingFreqType = ScalerHdmiAudioRx4SamplingFreqDetect();
#endif
            break;

        case _AUDIO_FROM_PXP_PORT:

#if(_DP_MAC_RX3_SUPPORT == _ON)
            enumSamplingFreqType = ScalerDpAudioRx3SamplingFreqDetect();
#endif
            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_MAC_RX4_SUPPORT == _ON)
            enumSamplingFreqType = ScalerDpAudioRx4SamplingFreqDetect();
#endif
            break;

        default:
            break;
    }

    return ScalerAudioGetSamplingFreqPacket(enumSamplingFreqType);
}

//--------------------------------------------------
// Description  : Check Audio Sampling Frequency Change or Not
// Input Value  : None
// Output Value : _TRUE => Change / _FALSE => Un-Change
//--------------------------------------------------
bit ScalerAudioSamplingFreqChange(EnumAudioOutputType enumAudioOutput)
{
    switch(ScalerAudioGetDigitalAudioPort(enumAudioOutput))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_MAC_RX0_SUPPORT == _ON)

            return ScalerDpAudioRx0SamplingFreqChange();

#endif
            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_MAC_RX1_SUPPORT == _ON)

            return ScalerDpAudioRx1SamplingFreqChange();

#endif
            break;

        case _AUDIO_FROM_RX2_PORT:

#if(_DP_MAC_RX2_SUPPORT == _ON)

            return ScalerDpAudioRx2SamplingFreqChange();

#endif
            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)

            return ScalerHdmiAudioRx3SamplingFreqChange();
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)

            return ScalerHdmiAudioRx4SamplingFreqChange();
#endif
            break;

        case _AUDIO_FROM_PXP_PORT:

#if(_DP_MAC_RX3_SUPPORT == _ON)

            return ScalerDpAudioRx3SamplingFreqChange();

#endif
            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_MAC_RX4_SUPPORT == _ON)

            return ScalerDpAudioRx4SamplingFreqChange();

#endif
            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio Watch Dog Proc
// Input Value  : bOn
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioWatchDogProc(bit bOn, EnumInputPort enumInputPort, EnumAudioOutputType enumAudioOutput)
{
    bOn = bOn;
    enumAudioOutput = enumAudioOutput;

#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource(enumAudioOutput) == _DIGITAL_AUDIO)
#endif
    {
        switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
        {
            case _AUDIO_FROM_RX0_PORT:

#if(_DP_MAC_RX0_SUPPORT == _ON)

                ScalerDpAudioRx0WatchDogProc(bOn);
                DebugMessageAudio("Audio RX0: WatchDog", bOn);
#endif
                break;

            case _AUDIO_FROM_RX1_PORT:

#if(_DP_MAC_RX1_SUPPORT == _ON)
                ScalerDpAudioRx1WatchDogProc(bOn);
                DebugMessageAudio("Audio RX1: WatchDog", bOn);
#endif
                break;

            case _AUDIO_FROM_RX2_PORT:

#if(_DP_MAC_RX2_SUPPORT == _ON)

                ScalerDpAudioRx2WatchDogProc(bOn);
                DebugMessageAudio("Audio RX2: WatchDog", bOn);
#endif
                break;

            case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
                if(GET_HDMI_RX3_HBR_AUDIO_IS_SETTING() == _FALSE)
#endif
                {
                    ScalerHdmiAudioRx3WatchDogProc(bOn);
                    DebugMessageAudio("Audio RX3: WatchDog", bOn);
                }
#endif
                break;

            case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
                if(GET_HDMI_RX4_HBR_AUDIO_IS_SETTING() == _FALSE)
#endif
                {
                    ScalerHdmiAudioRx4WatchDogProc(bOn);
                    DebugMessageAudio("Audio RX4: WatchDog", bOn);
                }
#endif
                break;

            case _AUDIO_FROM_PXP_PORT:

#if(_DP_MAC_RX3_SUPPORT == _ON)

                ScalerDpAudioRx3WatchDogProc(bOn);
                DebugMessageAudio("Audio PXP: WatchDog", bOn);
#endif
                break;

            case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_MAC_RX4_SUPPORT == _ON)

                ScalerDpAudioRx4WatchDogProc(bOn);
                DebugMessageAudio("Audio MST2SST: WatchDog", bOn);
#endif
                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Audio HBR Mode Control
// Input Value  : bOn
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioHbrModeControl(bit bOn, EnumInputPort enumInputPort, EnumAudioOutputType enumAudioOutput)
{
    bOn = bOn;
    enumAudioOutput = enumAudioOutput;

#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource(enumAudioOutput) == _DIGITAL_AUDIO)
#endif
    {
        switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
        {
            case _AUDIO_FROM_RX0_PORT:

#if(_DP_MAC_RX0_SUPPORT == _ON)

                ScalerDpAudioRx0HbrModeControl(bOn);
                DebugMessageAudio("Audio RX0: HBR Mode Control", bOn);
#endif
                break;

            case _AUDIO_FROM_RX1_PORT:

#if(_DP_MAC_RX1_SUPPORT == _ON)
                ScalerDpAudioRx1HbrModeControl(bOn);
                DebugMessageAudio("Audio RX1: HBR Mode Control", bOn);
#endif
                break;

            case _AUDIO_FROM_RX2_PORT:

#if(_DP_MAC_RX2_SUPPORT == _ON)

                ScalerDpAudioRx2HbrModeControl(bOn);
                DebugMessageAudio("Audio RX2: HBR Mode Control", bOn);
#endif
                break;

            case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
                DebugMessageAudio("Audio RX3: HBR Mode Control", bOn);
#endif
                break;

            case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
                DebugMessageAudio("Audio RX4: HBR Mode Control", bOn);
#endif
                break;

            case _AUDIO_FROM_PXP_PORT:

#if(_DP_MAC_RX3_SUPPORT == _ON)

                ScalerDpAudioRx3HbrModeControl(bOn);
                DebugMessageAudio("Audio PXP: HBR Mode Control", bOn);
#endif
                break;

            case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_MAC_RX4_SUPPORT == _ON)

                ScalerDpAudioRx4HbrModeControl(bOn);
                DebugMessageAudio("Audio MST2SST: HBR Mode Control", bOn);
#endif
                break;

            default:
                break;
        }
    }
}

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Frequency Limitation Reset
// Input Value  : EnumInputPort
// Input Value  : EnumAudioOutputType
// Output Value : None
//--------------------------------------------------
void ScalerAudioResetSamplingFreqLimitProc(EnumInputPort enumInputPort, EnumAudioOutputType enumAudioOutput)
{
    enumAudioOutput = enumAudioOutput;

#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource(enumAudioOutput) == _DIGITAL_AUDIO)
#endif
    {
        switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
        {
            case _AUDIO_FROM_RX0_PORT:

#if(_DP_MAC_RX0_SUPPORT == _ON)
                ScalerDpAudioRx0ResetSamplingFreqLimitProc();
                DebugMessageAudio("Audio RX0: Frequency Limit Reset", 0);
#endif
                break;

            case _AUDIO_FROM_RX1_PORT:

#if(_DP_MAC_RX1_SUPPORT == _ON)
                ScalerDpAudioRx1ResetSamplingFreqLimitProc();
                DebugMessageAudio("Audio RX1: Frequency Limit Reset", 0);
#endif
                break;

            case _AUDIO_FROM_RX2_PORT:

#if(_DP_MAC_RX2_SUPPORT == _ON)
                ScalerDpAudioRx2ResetSamplingFreqLimitProc();
                DebugMessageAudio("Audio RX2: Frequency Limit Reset", 0);
#endif
                break;

            case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
                DebugMessageAudio("Audio RX3: Frequency Limit Reset", 0);
#endif
                break;

            case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
                DebugMessageAudio("Audio RX4: Frequency Limit Reset", 0);
#endif
                break;

            case _AUDIO_FROM_PXP_PORT:

#if(_DP_MAC_RX3_SUPPORT == _ON)
                ScalerDpAudioRx3ResetSamplingFreqLimitProc();
                DebugMessageAudio("Audio PXP: Frequency Limit Reset", 0);
#endif
                break;

            case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_MAC_RX4_SUPPORT == _ON)
                ScalerDpAudioRx4ResetSamplingFreqLimitProc();
                DebugMessageAudio("Audio MST2SST: Frequency Limit Reset", 0);
#endif
                break;

            default:
                break;
        }
    }
}
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Check Audio Mode Switch (ex. HDMI2.0 <-> 2.1 Mac Switch)
// Input Value  : enumInputPort
// Output Value : _TRUE-> Change Mode
//--------------------------------------------------
bit ScalerAudioCheckModeSwitch(EnumInputPort enumInputPort)
{
    EnumAudioInputPort enumAudioInputPort = ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT);

    switch(enumAudioInputPort)
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        case _AUDIO_FROM_RX3_PORT:
            if(ScalerHdmiAudioRx3CheckVersionChange() == _TRUE)
            {
                return _TRUE;
            }
            break;
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
        case _AUDIO_FROM_RX4_PORT:
            if(ScalerHdmiAudioRx4CheckVersionChange() == _TRUE)
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
// Description  : Adjust Digital volume
// Input Value  : ucVolume
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalAdjustVolume(WORD usVolume)
{
    ScalerAudioDVCSetVolumeZCDTimeout(usVolume);

    ScalerAudioDVCAdjustVolume(usVolume);
}

//--------------------------------------------------
// Description  : Audio Mute proc
// Input Value  : bMute, usVolume
// Output Value : None
//--------------------------------------------------
void ScalerAudioMuteProc(bit bMute, WORD usVolume)
{
    ScalerAudioDigitalVolumeMute(bMute, usVolume);
}

//--------------------------------------------------
// Description  : Smooth adjust digital volume for mute/unmute
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalVolumeMute(bit bMute, WORD usVolume)
{
    ScalerAudioDVCVolumeMute(bMute, usVolume);
}

//--------------------------------------------------
// Description  : Initial DVC Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCInitial(void)
{
    // Disable Clcok Gatting
    ScalerAudioClockGatting(_DISABLE);

    // Enable DVC function and counter
    ScalerSetBit(P8_A0_DVC_EN, ~(_BIT7 | _BIT6), _BIT7);

    // Set DVC ZCD window size
    ScalerSetBit(P8_A3_DVC_ZC_WIN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(_DVC_ZCD_TIMEOUT_DEFAULT));
    ScalerSetByte(P8_A4_DVC_ZC_WIN_CTRL_1, LOBYTE(_DVC_ZCD_TIMEOUT_DEFAULT));

    // Select DVC Volume Adjust Type
    ScalerAudioDVCVolumeAdjustType(_DVC_ADJUST_TYPE);

    // Initial DVC gain = 0
    ScalerAudioDVCAdjustVolume(0x00);

    // Initial DVC Mute Control Status
    SET_AUDIO_DVC_MUTE_CTRL_STATUS(_ON);

#if((_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON) || (_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE))
#if(_LINE_IN_SUPPORT == _OFF)
    // Set Sampling Frequency "48kHz" For S/PDIF Output From ADC In
    ScalerSetBit(P6_E2_AD_SPDIF_CS_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_48KHZ);

#if(_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_0)
    // Set Channel Count "2 ch" For S/PDIF Output From ADC In
    ScalerSetBit(P6_E3_AD_SPDIF_CS_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Enable I2S Output for ADC In
    ScalerSetBit(P6_E7_AD_I2S_CTRL, ~_BIT7, _BIT7);
#elif(_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_1)
    // Set S/PDIF & I2S From ADC Input
    ScalerAudioADCDigitalOutputSetting();
#endif
#endif

    // Select SPDIF from DVC path
    ScalerSetBit(P6_E1_AD_SPDIF_CTRL, ~_BIT4, _BIT4);

    // Select I2S from DVC path
    ScalerSetBit(P6_E7_AD_I2S_CTRL, ~_BIT5, _BIT5);

    // Set I2S and SPDIF From DVC path
    ScalerSetByte(P6F_00_MUX_DIG_OUT, ((_AUDIO_FROM_ADC_PORT << 4) | _AUDIO_FROM_ADC_PORT));
#endif // End of #if((_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON) || (_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE))
}

//--------------------------------------------------
// Description  : Select DVC Volume Adjust Type
// Input Value  : _DB_GAIN, _VOLUME_STEP_SIZE
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCVolumeAdjustType(bit bAdjustType)
{
    if(bAdjustType == _DB_GAIN)
    {
        // Select value mode and set DB gain setp
        ScalerSetBit(P8_A0_DVC_EN, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((_DB_GAIN_DOWN_VALUE << 2) | _DB_GAIN_UP_VALUE));

        // Initial volume step size for DB gain mode
        ScalerSetBit(P8_A1_DVC_VA_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P8_A2_DVC_VA_LSB, 0x01);
    }
    else // _VOLUME_STEP_SIZE
    {
        // Select value mode
        ScalerSetBit(P8_A0_DVC_EN, ~(_BIT4), _BIT4);

        // Set volume step size
        ScalerSetBit(P8_A1_DVC_VA_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(_VOLUME_STEP_SIZE_VALUE));
        ScalerSetByte(P8_A2_DVC_VA_LSB, LOBYTE(_VOLUME_STEP_SIZE_VALUE));
    }
}

#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Select DVC Volume Fast Adjust Type
// Input Value  : _DB_GAIN, _VOLUME_STEP_SIZE
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCVolumeFastAdjustType(bit bAdjustType)
{
    if(bAdjustType == _DB_GAIN)
    {
        // Select value mode and set DB gain setp
        ScalerSetBit(P8_A0_DVC_EN, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((_DB_GAIN_FAST_DOWN_VALUE << 2) | _DB_GAIN_FAST_UP_VALUE));

        // Initial volume step size for DB gain mode
        ScalerSetBit(P8_A1_DVC_VA_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P8_A2_DVC_VA_LSB, 0x01);
    }
    else // _VOLUME_STEP_SIZE
    {
        // Select value mode
        ScalerSetBit(P8_A0_DVC_EN, ~(_BIT4), _BIT4);

        // Set volume step size
        ScalerSetBit(P8_A1_DVC_VA_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(_VOLUME_STEP_SIZE_VALUE));
        ScalerSetByte(P8_A2_DVC_VA_LSB, LOBYTE(_VOLUME_STEP_SIZE_VALUE));
    }
}
#endif

//--------------------------------------------------
// Description  : Adjust digital volume for DVC function
// Input Value  : ucVolume
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCAdjustVolume(WORD usVolume)
{
    // DVC gain MSB
    ScalerSetBit(P8_A5_DVC_GAIN_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usVolume));

    // DVC gain LSB  (double buffer)
    ScalerSetByte(P8_A6_DVC_GAIN_LSB, LOBYTE(usVolume));

    // Set Double Buffer
    ScalerSetBit(P8_A7_DVC_GAIN_READ_MSB, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : Mute/Unmute for DVC function
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCVolumeMute(bit bMute, WORD usVolume)
{
    ScalerAudioDVCVolumeAdjustType(_DVC_ADJUST_TYPE);

    ScalerAudioDVCSetMuteZCDTimeout(bMute, usVolume, _DVC_ADJUST_TYPE, _DVC_VOLUME_MUTE_TIMER);

    PDATA_WORD(0) = (((WORD) ScalerGetByte(P8_A7_DVC_GAIN_READ_MSB) << 8) | ScalerGetByte(P8_A8_DVC_GAIN_READ_LSB));

    if(bMute == _ON)
    {
        if(PDATA_WORD(0) != 0)
        {
            ScalerAudioDVCAdjustVolume(0);

            PDATA_WORD(1) = 0;

            do
            {
                ScalerTimerDelayXms(1);
                PDATA_WORD(1)++;
            }
            while((ScalerGetBit(P8_A9_DVC_GAIN_DONE, _BIT7) != _BIT7) && (PDATA_WORD(1) < _DVC_VOLUME_MUTE_TIMER));

            DebugMessageAudio("0.[Top Audio]Top DVC Volume Mute", 0x00);
        }
    }
    else // Unmute
    {
        if(PDATA_WORD(0) != usVolume)
        {
            ScalerAudioDVCAdjustVolume(usVolume);

            DebugMessageAudio("0.[Top Audio]Top DVC HByte-Volume Un-Mute", HIBYTE(usVolume));
            DebugMessageAudio("0.[Top Audio]Top DVC LByte-Volume Un-Mute", LOBYTE(usVolume));
        }
    }
}


#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Fast Mute/Unmute for DVC function
// Input Value  : bMute / usVolume
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCVolumeFastMute(bit bMute, WORD usVolume)
{
    ScalerAudioDVCVolumeFastAdjustType(_DVC_ADJUST_TYPE);

    if(bMute == _ON)
    {
        ScalerAudioDVCSetMuteZCDTimeout(bMute, usVolume, _DVC_ADJUST_TYPE, _DVC_FAST_VOLUME_MUTE_TIMER);
    }
    else
    {
        ScalerAudioDVCSetMuteZCDTimeout(bMute, usVolume, _DVC_ADJUST_TYPE, _DVC_FAST_VOLUME_UNMUTE_TIMER);
    }

    PDATA_WORD(0) = (((WORD) ScalerGetByte(P8_A7_DVC_GAIN_READ_MSB) << 8) | ScalerGetByte(P8_A8_DVC_GAIN_READ_LSB));

    if(bMute == _ON)
    {
        if(PDATA_WORD(0) != 0)
        {
            ScalerAudioDVCAdjustVolume(0);

            PDATA_WORD(1) = 0;

            do
            {
                ScalerTimerDelayXms(1);
                PDATA_WORD(1)++;
            }
            while((ScalerGetBit(P8_A9_DVC_GAIN_DONE, _BIT7) != _BIT7) && (PDATA_WORD(1) < _DVC_FAST_VOLUME_MUTE_TIMER));
        }
    }
    else // Unmute
    {
        if(PDATA_WORD(0) != usVolume)
        {
            ScalerAudioDVCAdjustVolume(usVolume);
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Set ZCD Timeout
// Input Value  : bMute, usVolume, bAdjustType
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCSetMuteZCDTimeout(bit bMute, WORD usVolume, bit bAdjustType, WORD usTimeout)
{
    EnumAudioSamplingFreqPacket enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_NO_AUDIO;

    // Get Sampling Rate
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource(_AUDIO_DAC_OUT) == _LINE_IN_AUDIO)
    {
        enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_48K;
    }
    else
#endif
    {
        enumSamplingFreqPacket = ScalerAudioSamplingFreqDetect(ScalerAudioGetDigitalAudioPortMapping(_AUDIO_DAC_OUT));
    }

    if(bAdjustType == _DB_GAIN)
    {
        // Get down or up step
        pData[0] = (bMute == _ON) ? (ScalerGetBit(P8_A0_DVC_EN, (_BIT3 | _BIT2)) >> 2) : ScalerGetBit(P8_A0_DVC_EN, (_BIT1 | _BIT0));

        // Get numbers of the volume step for mute or unmute
        PDATA_WORD(0) = _DVC_DB_STEP_NUMBER << pData[0];
    }
    else
    {
        PDATA_WORD(0) = usVolume / _VOLUME_STEP_SIZE_VALUE + 1;
    }

    // Calculate samples of ZCD timeout
    PDATA_DWORD(1) = (DWORD)enumSamplingFreqPacket * usTimeout / PDATA_WORD(0);

    // Avoid Overflow
    if(PDATA_DWORD(1) > 0x0FFF)
    {
        PDATA_WORD(0) = 0x0FFF;
    }
    else
    {
        PDATA_WORD(0) = (WORD)PDATA_DWORD(1);
    }

    // Set DVC ZCD window size
    ScalerSetBit(P8_A3_DVC_ZC_WIN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(0)));
    ScalerSetByte(P8_A4_DVC_ZC_WIN_CTRL_1, LOBYTE(PDATA_WORD(0)));
}

//--------------------------------------------------
// Description  : Set ZCD Timeout, only use the type "_VOLUME_STEP_SIZE"
// Input Value  : usVolume
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCSetVolumeZCDTimeout(WORD usVolume)
{
    EnumAudioSamplingFreqPacket enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_NO_AUDIO;

    ScalerAudioDVCVolumeAdjustType(_VOLUME_STEP_SIZE);

    // Get Sampling Rate
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource(_AUDIO_DAC_OUT) == _LINE_IN_AUDIO)
    {
        enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_48K;
    }
    else
#endif
    {
        enumSamplingFreqPacket = ScalerAudioSamplingFreqDetect(ScalerAudioGetDigitalAudioPortMapping(_AUDIO_DAC_OUT));
    }

    // Get Current Volume
    PDATA_WORD(0) = ((WORD)(ScalerGetByte(P8_A5_DVC_GAIN_MSB) & 0x3F) << 8) | ((WORD)ScalerGetByte(P8_A6_DVC_GAIN_LSB));

    PDATA_WORD(0) = (PDATA_WORD(0) > usVolume) ? (PDATA_WORD(0) - usVolume) : (usVolume - PDATA_WORD(0));

    PDATA_WORD(0) = PDATA_WORD(0) / _VOLUME_STEP_SIZE_VALUE + 1;

    // Calculate samples of ZCD timeout
    PDATA_DWORD(1) = (DWORD)enumSamplingFreqPacket * _DVC_VOLUME_ADJUST_TIMER / PDATA_WORD(0);

    // Avoid Overflow
    if(PDATA_DWORD(1) > 0x0FFF)
    {
        PDATA_WORD(0) = 0x0FFF;
    }
    else
    {
        PDATA_WORD(0) = (WORD)PDATA_DWORD(1);
    }

    // Set DVC ZCD window size
    ScalerSetBit(P8_A3_DVC_ZC_WIN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(0)));
    ScalerSetByte(P8_A4_DVC_ZC_WIN_CTRL_1, LOBYTE(PDATA_WORD(0)));
}

//--------------------------------------------------
// Description  : Set DVC Mute Status
// Input Value  : None
// Output Value : _ON or _OFF
//--------------------------------------------------
void ScalerAudioDVCSetVolumeMuteStatus(bit bMute)
{
    SET_AUDIO_DVC_MUTE_CTRL_STATUS(bMute);
}

//--------------------------------------------------
// Description  : Get DVC Mute Status
// Input Value  : None
// Output Value : _ON or _OFF
//--------------------------------------------------
bit ScalerAudioDVCGetVolumeMuteStatus(void)
{
    return GET_AUDIO_DVC_MUTE_CTRL_STATUS();
}

//--------------------------------------------------
// Description  : DVC Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCResetProc(void)
{
#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(ScalerAudioDACGetState() == _AUDIO_DAC_READY)
    {
        // Switch Audio DAC State to _AUDIO_DAC_DEPOP
        ScalerAudioDACNormalToDepop();
    }
#endif

    // Reset DVC Counter
    ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, _BIT6);

    // At Least Delay 2 Cycle of 1 / 256 * FS (= 32KHz)
    DELAY_5US();

    // Enable DVC Counter
    ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : Check if do DVC Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCResetProcCheck(EnumAudioInputPort enumAudioInput)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource(_AUDIO_DAC_OUT) == _DIGITAL_AUDIO)
#endif
    {
        if(ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT) == enumAudioInput)
        {
            // Resolve Audio Phase Delay of L/R Channel
            ScalerAudioDVCResetProc();
        }
    }
}

//--------------------------------------------------
// Description  : Audio Source Chnage Check
// Input Value  : EnumInputPort, EnumPortType
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerAudioSourceChangeCheck(EnumInputPort enumPowerCutOnPort, EnumPortType enumPowerCutOnPortType)
{
    enumPowerCutOnPort = enumPowerCutOnPort;
    enumPowerCutOnPortType = enumPowerCutOnPortType;

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
    if(enumPowerCutOnPortType == _PORT_DP)
    {
        switch(ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT))
        {
            case _AUDIO_FROM_RX0_PORT:
#if(_DP_MAC_RX0_SUPPORT == _ON)
                if(ScalerDpRxGetMacStreamSourceType(_DP_MAC_0) == _STREAM_SOURCE_NONE)
                {
                    return _TRUE;
                }
#endif
                break;

            case _AUDIO_FROM_RX1_PORT:
#if(_DP_MAC_RX1_SUPPORT == _ON)
                if(ScalerDpRxGetMacStreamSourceType(_DP_MAC_1) == _STREAM_SOURCE_NONE)
                {
                    return _TRUE;
                }
#endif
                break;

            case _AUDIO_FROM_RX2_PORT:
#if(_DP_MAC_RX2_SUPPORT == _ON)
                if(ScalerDpRxGetMacStreamSourceType(_DP_MAC_2) == _STREAM_SOURCE_NONE)
                {
                    return _TRUE;
                }
#endif
                break;

            case _AUDIO_FROM_PXP_PORT:
#if(_DP_MAC_RX3_SUPPORT == _ON)
                if(ScalerDpRxGetMacStreamSourceType(_DP_MAC_3) == _STREAM_SOURCE_NONE)
                {
                    return _TRUE;
                }
#endif
                break;

            default:
                break;
        }
    }
    else
#endif
    {
        if(ScalerAudioDxToRxMapping(enumPowerCutOnPort, _AUDIO_PORT_MAP_TO_CURRENT) == ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Switch IIS/Spdif Path
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioInputDigitalReset(EnumInputPort enumInputPort, EnumAudioOutputType enumAudioOutput)
{
    ScalerAudioLPCMResetProc(enumInputPort, enumAudioOutput);

    ScalerAudioWatchDogProc(_OFF, enumInputPort, enumAudioOutput);

    ScalerAudioHbrModeControl(_OFF, enumInputPort, enumAudioOutput);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    ScalerAudioResetSamplingFreqLimitProc(enumInputPort, enumAudioOutput);
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Dp Audio Case: Get SDP Infoframe Data
// Input Value  : Input port
// Output Value : ucAudioInfoSdpDataCA
//--------------------------------------------------
BYTE ScalerAudioGetInputChannelAllocation(EnumInputPort enumInputPort)
{
    switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_AUDIO_RX0_SUPPORT == _ON)
            // Get SDP Audio Infoframe for Channel Allocation
            return ScalerDpAudioRx0GetAudioInfoFrame(_ADUIO_INFO_PB4);
#endif
            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
            // Get SDP Audio Infoframe for Channel Allocation
            return ScalerDpAudioRx1GetAudioInfoFrame(_ADUIO_INFO_PB4);
#endif
            break;

        case _AUDIO_FROM_RX2_PORT:

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
            // Get SDP Audio Infoframe for Channel Allocation
            return ScalerDpAudioRx2GetAudioInfoFrame(_ADUIO_INFO_PB4);
#endif
            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
            // Get Audio Infoframe for Channel Allocation
            return GET_HDMI_AUDIO_RX3_CHANNEL_ALLOCATION();
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
            // Get Audio Infoframe for Channel Allocation
            return GET_HDMI_AUDIO_RX4_CHANNEL_ALLOCATION();
#endif
            break;

        case _AUDIO_FROM_ADC_PORT:

#if(_LINE_IN_SUPPORT == _ON)
            return GET_LINE_IN_AUDIO_CHANNEL_ALLOCATION();
#endif
            break;

        case _AUDIO_FROM_PXP_PORT:

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
            // Get SDP Audio Infoframe for Channel Allocation
            return ScalerDpAudioRx3GetAudioInfoFrame(_ADUIO_INFO_PB4);
#endif
            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
            // Get SDP Audio Infoframe for Channel Allocation
            return ScalerDpAudioRx4GetAudioInfoFrame(_ADUIO_INFO_PB4);
#endif
            break;

        default:
            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get Input Audio Channel Count
// Input Value  : EnumInputPort
// Output Value : Channel Count
//--------------------------------------------------
EnumAudioChannelCount ScalerAudioGetInputChannelCount(EnumInputPort enumInputPort)
{
    EnumAudioChannelCount enumChannelCount = _AUDIO_CHANNEL_COUNT_MONO;

    switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_AUDIO_RX0_SUPPORT == _ON)
            enumChannelCount = GET_DP_AUDIO_RX0_CHANNEL_COUNT();

            DebugMessageAudio("Audio RX0: Channel Count", GET_DP_AUDIO_RX0_CHANNEL_COUNT());
#endif
            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
            enumChannelCount = GET_DP_AUDIO_RX1_CHANNEL_COUNT();

            DebugMessageAudio("Audio RX1: Channel Count", GET_DP_AUDIO_RX1_CHANNEL_COUNT());
#endif
            break;

        case _AUDIO_FROM_RX2_PORT:

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
            enumChannelCount = GET_DP_AUDIO_RX2_CHANNEL_COUNT();

            DebugMessageAudio("Audio RX2: Channel Count", GET_DP_AUDIO_RX2_CHANNEL_COUNT());
#endif
            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
            enumChannelCount = GET_HDMI_AUDIO_RX3_CHANNEL_COUNT();

            DebugMessageAudio("Audio RX3: Channel Count", GET_HDMI_AUDIO_RX3_CHANNEL_COUNT());
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
            enumChannelCount = GET_HDMI_AUDIO_RX4_CHANNEL_COUNT();

            DebugMessageAudio("Audio RX4: Channel Count", GET_HDMI_AUDIO_RX4_CHANNEL_COUNT());
#endif
            break;

        case _AUDIO_FROM_ADC_PORT:

#if(_LINE_IN_SUPPORT == _ON)
            enumChannelCount = GET_LINE_IN_AUDIO_CHANNEL_COUNT();

            DebugMessageAudio("Audio LINE_IN: Channel Count", GET_LINE_IN_AUDIO_CHANNEL_COUNT());
#endif
            break;

        case _AUDIO_FROM_PXP_PORT:

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
            enumChannelCount = GET_DP_AUDIO_RX3_CHANNEL_COUNT();

            DebugMessageAudio("Audio PxP: Channel Count", GET_DP_AUDIO_RX3_CHANNEL_COUNT());
#endif
            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
            enumChannelCount = GET_DP_AUDIO_RX4_CHANNEL_COUNT();

            DebugMessageAudio("Audio MST2SST: Channel Count", GET_DP_AUDIO_RX4_CHANNEL_COUNT());
#endif
            break;

        default:
            break;
    }

    return enumChannelCount;
}

//--------------------------------------------------
// Description  : Get Audio Channel Status of Rx Port
// Input Value  : None
// Output Value : Channel Status
//--------------------------------------------------
StructAudioChannelInfo ScalerAudioGetInputChannelStatus(EnumInputPort enumInputPort)
{
    StructAudioChannelInfo stAudioStatus = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_AUDIO_RX0_SUPPORT == _ON)
            stAudioStatus = ScalerDpAudioRx0GetChannelStatus();
#endif
            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
            stAudioStatus = ScalerDpAudioRx1GetChannelStatus();
#endif
            break;

        case _AUDIO_FROM_RX2_PORT:

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
            stAudioStatus = ScalerDpAudioRx2GetChannelStatus();
#endif
            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
            stAudioStatus = ScalerHdmiAudioRx3GetChannelStatus();
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
            stAudioStatus = ScalerHdmiAudioRx4GetChannelStatus();
#endif
            break;

        case _AUDIO_FROM_ADC_PORT:

#if(_LINE_IN_SUPPORT == _ON)
            // Mode 0 channel status format for consumer use(IEC 60958)

            // [0] = 0, Consumer use;
            // [1] = 0, LPCM Audio;
            // [2] = 1, No Copyright;
            // [5:3] = 3'b000, 2-ch audio without pre-emphasis;
            // [7:6] = 2'b00, Mode 0.
            stAudioStatus.ucChannelStaus0 = 0x04;

            // [15:8] = 8'b10000000, Category code is not defined.
            stAudioStatus.ucChannelStaus1 = 0x80;

            // [19:16] = 4'b0000, Source number do not take into account;
            // [23:20] Set Dummy and Reference by AudioChannelNumStaus1 ~ 8.
            stAudioStatus.ucChannelStaus2 = 0x00;

            // [27:24] = 4'b0010, 48kHz;
            // [29:28] = 2'b00, Clock accuracy Level II.
            stAudioStatus.ucChannelStaus3 = 0x02;

            // [32] = 1, 24-bits Sample;
            // [35:33] = 3'b101;
            // [39:36] = 4'b0000, Original sampling frequency not indicated.
            stAudioStatus.ucChannelStaus4 = 0x0B;

            // Insert 2-Channel
            stAudioStatus.ucChannelNumber12 = 0x12;
            stAudioStatus.ucChannelNumber34 = 0x00;
            stAudioStatus.ucChannelNumber56 = 0x00;
            stAudioStatus.ucChannelNumber78 = 0x00;
#endif
            break;

        case _AUDIO_FROM_PXP_PORT:

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
            stAudioStatus = ScalerDpAudioRx3GetChannelStatus();
#endif
            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
            stAudioStatus = ScalerDpAudioRx4GetChannelStatus();
#endif
            break;

        default:
            break;
    }

    return stAudioStatus;
}

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Switch IIS/Spdif Path
// Input Value  : Audiopath/InputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioSwitchI2sSpdifPath(bit bAudiopath, EnumInputPort enumInputPort)
{
    EnumAudioInputPort enumAudioInput = ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT);

    if(bAudiopath == _AUDIO_BYPASS_PATH)
    {
        // Set IIS Input
        ScalerSetBit(P6F_00_MUX_DIG_OUT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (enumAudioInput << 4));

        // Set SPDIF Input
        ScalerSetBit(P6F_00_MUX_DIG_OUT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumAudioInput);

        DebugMessageAudio("IIS/SPDIF Path From Inputport", bAudiopath);
    }
    else
    {
        // Set Sampling Frequency For S/PDIF Output From ADC In
        ScalerAudioSpdifCheckIfSamplingFrequencyChange(enumInputPort);

#if(_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_0)
        // Set Channel Count "2 ch" For S/PDIF Output From ADC In
        ScalerSetBit(P6_E3_AD_SPDIF_CS_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Enable I2S Output for ADC In
        ScalerSetBit(P6_E7_AD_I2S_CTRL, ~_BIT7, _BIT7);
#elif(_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_1)
        // Set S/PDIF & I2S From ADC Input
        ScalerAudioADCDigitalOutputSetting();
#endif

        // Select SPDIF from DVC path
        ScalerSetBit(P6_E1_AD_SPDIF_CTRL, ~_BIT4, _BIT4);

        // Select I2S from DVC path
        ScalerSetBit(P6_E7_AD_I2S_CTRL, ~_BIT5, _BIT5);

        // Set I2S and SPDIF From DVC path
        ScalerSetByte(P6F_00_MUX_DIG_OUT, (_AUDIO_FROM_ADC_PORT << 4) | _AUDIO_FROM_ADC_PORT);

        DebugMessageAudio("IIS/SPDIF Path From DVC Path", bAudiopath);
    }
}
#endif

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable DP audio FSM
// Input Value  : Enable or Disable, Input Port
// Output Value : None
//--------------------------------------------------
void ScalerAudioDpAudioEnable(EnumInputPort enumInputPort, bit bEnable)
{
#if((_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))
    // Check Whether Audio Pattern Gen is Enable
    if((bEnable == _DISABLE) && (GET_AUDIO_INTERNAL_GEN_ENABLE_STATE() == _ON))
    {
        return;
    }
#endif // End of #if((_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))

    switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _AUDIO_FROM_RX0_PORT:

            ScalerDpAudioRx0AudioEnableControl(bEnable);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _AUDIO_FROM_RX1_PORT:

            ScalerDpAudioRx1AudioEnableControl(bEnable);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _AUDIO_FROM_RX2_PORT:

            ScalerDpAudioRx2AudioEnableControl(bEnable);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _AUDIO_FROM_PXP_PORT:

            ScalerDpAudioRx3AudioEnableControl(bEnable);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _AUDIO_FROM_MST2SST_PORT:

            ScalerDpAudioRx4AudioEnableControl(bEnable);

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
void ScalerAudioDpAudioEnable_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
#if((_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))
    // Check Whether Audio Pattern Gen is Enable
    if((bEnable == _DISABLE) && (GET_AUDIO_INTERNAL_GEN_ENABLE_STATE() == _ON))
    {
        return;
    }
#endif // End of #if((_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))

    switch(ScalerAudioDxToRxMapping_EXINT0(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _AUDIO_FROM_RX0_PORT:

            ScalerDpAudioRx0AudioEnableControl_EXINT0(bEnable);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _AUDIO_FROM_RX1_PORT:

            ScalerDpAudioRx1AudioEnableControl_EXINT0(bEnable);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _AUDIO_FROM_RX2_PORT:

            ScalerDpAudioRx2AudioEnableControl_EXINT0(bEnable);

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _AUDIO_FROM_PXP_PORT:

            ScalerDpAudioRx3AudioEnableControl_EXINT0(bEnable);

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _AUDIO_FROM_MST2SST_PORT:

            ScalerDpAudioRx4AudioEnableControl_EXINT0(bEnable);

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
void ScalerAudioRxDisableSetting_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerAudioDxToRxMapping_EXINT0(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _AUDIO_FROM_RX0_PORT:

            ScalerDpAudioRx0DisableSetting_EXINT0();

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _AUDIO_FROM_RX1_PORT:

            ScalerDpAudioRx1DisableSetting_EXINT0();

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _AUDIO_FROM_RX2_PORT:

            ScalerDpAudioRx2DisableSetting_EXINT0();

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _AUDIO_FROM_PXP_PORT:

            ScalerDpAudioRx3DisableSetting_EXINT0();

            break;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _AUDIO_FROM_MST2SST_PORT:

            ScalerDpAudioRx4DisableSetting_EXINT0();

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Dp Audio Capability Change
// Input Value  : Input Port
// Output Value : _TRUE => Change / _FALSE => Un-Change
//--------------------------------------------------
bit ScalerAudioDpGetCapabilityChange(EnumInputPort enumInputPort)
{
    bit bResult = _FALSE;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            bResult = GET_AUDIO_DP_D0_CAPABILITY_SWITCH();

            CLR_AUDIO_DP_D0_CAPABILITY_SWITCH();

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            bResult = GET_AUDIO_DP_D1_CAPABILITY_SWITCH();

            CLR_AUDIO_DP_D1_CAPABILITY_SWITCH();

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            bResult = GET_AUDIO_DP_D2_CAPABILITY_SWITCH();

            CLR_AUDIO_DP_D2_CAPABILITY_SWITCH();

            break;
#endif

        default:

            break;
    }

    return bResult;
}

//--------------------------------------------------
// Description  : Set Dp Audio Capability State
// Input Value  : Input Port
// Input Value  : EnumAudioDpDpcdSupport
// Output Value : None
//--------------------------------------------------
void ScalerAudioDpSetCapabilityState(EnumInputPort enumInputPort, EnumAudioDpDpcdSupport enumDpcdSupport)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            // Check Previous DP Capability
            if(GET_AUDIO_DP_D0_SUPPORT() != enumDpcdSupport)
            {
                // Set User Define DP Capability
                SET_AUDIO_DP_D0_SUPPORT(enumDpcdSupport);
                SET_AUDIO_DP_D0_CAPABILITY_SWITCH();

                // Change DPCD
                SET_DP_RX_CAPABILITY_SWITCHED();
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            // Check Previous DP Capability
            if(GET_AUDIO_DP_D1_SUPPORT() != enumDpcdSupport)
            {
                // Set User Define DP Capability
                SET_AUDIO_DP_D1_SUPPORT(enumDpcdSupport);
                SET_AUDIO_DP_D1_CAPABILITY_SWITCH();

                // Change DPCD
                SET_DP_RX_CAPABILITY_SWITCHED();
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            // Check Previous DP Capability
            if(GET_AUDIO_DP_D2_SUPPORT() != enumDpcdSupport)
            {
                // Set User Define DP Capability
                SET_AUDIO_DP_D2_SUPPORT(enumDpcdSupport);
                SET_AUDIO_DP_D2_CAPABILITY_SWITCH();

                // Change DPCD
                SET_DP_RX_CAPABILITY_SWITCHED();
            }

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set Dp Audio Capability State
// Input Value  : Input Port
// Output Value : EnumAudioDpDpcdSupport
//--------------------------------------------------
EnumAudioDpDpcdSupport ScalerAudioDpGetCapabilityState(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            // Get User Define DP Capability
            return GET_AUDIO_DP_D0_SUPPORT();

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            // Get User Define DP Capability
            return GET_AUDIO_DP_D1_SUPPORT();

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            // Get User Define DP Capability
            return GET_AUDIO_DP_D2_SUPPORT();

            break;
#endif

        default:

            break;
    }

    return _AUDIO_DP_DPCD_NOT_SUPPORT;
}

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
//--------------------------------------------------
// Description  : Get Dp audio Status for Sleep Audio
// Input Value  : Input Port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerAudioGetDpStandaloneAudioStatus(EnumInputPort enumInputPort)
{
    return ((ScalerAudioGetDigitalAudioSource(enumInputPort) == _DIGITAL_AUDIO_SOURCE_DP) ? _TRUE : _FALSE);
}
#endif // End of #if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
#endif // End of #if(_DP_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Audio Soft Reset for DAC Path
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACSoftReset(void)
{
#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
    // I2S/SPDIF DVC Soft Audio Enable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~(_BIT3 | _BIT2), 0x00);
#endif

    // Soft Reset Enable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
    // I2S/SPDIF DVC Soft Audio Disable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
#endif

    // DAC Soft Reset Disable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~_BIT4, _BIT4);

    // DA Gain Double buffer
    ScalerSetBit(P6_D2_DA_GAIN_L, ~_BIT7, _BIT7);

    // Top DVC Soft Reset Disable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~_BIT5, _BIT5);

    // TTS DVC Soft Reset Disable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~_BIT6, _BIT6);

    // Mixer DVC Soft Reset Disable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~_BIT7, _BIT7);
}

#if(_HDMI_SUPPORT == _ON)
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
//--------------------------------------------------
// Description  : HDMI HDR Audio Reset Process
// Input Value  : enumAudioOutput
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerAudioHdmiHbrSettingProc(EnumAudioOutputType enumAudioOutput)
{
    switch(ScalerAudioGetDigitalAudioPort(enumAudioOutput))
    {
        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
            {
                return ScalerHdmiAudioRx3HbrAudioSettingForFrl();
            }
            else
#endif
            {
                return ScalerHdmiAudioRx3HbrAudioSettingForTmds();
            }
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX4_VERSION() == _AUDIO_INPUT_FROM_FRL)
            {
                return ScalerHdmiAudioRx4HbrAudioSettingForFrl();
            }
            else
#endif
            {
                return ScalerHdmiAudioRx4HbrAudioSettingForTmds();
            }
#endif
            break;

        default:
            break;
    }
    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Check Audio whether Audio LPCM By Info Frame
// Input Value  : enumInputPort
// Output Value : _TRUE => LPCM
//--------------------------------------------------
bit ScalerAudioLPCMCheckInfo(EnumAudioOutputType enumAudioOutput)
{
    switch(ScalerAudioGetDigitalAudioPort(enumAudioOutput))
    {
        case _AUDIO_FROM_RX0_PORT:

            break;

        case _AUDIO_FROM_RX1_PORT:

            break;

        case _AUDIO_FROM_RX2_PORT:

            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_MAC_RX3_SUPPORT == _ON)

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
            {
                pData[0] = ScalerGetDataPortSingleByte(P77_CD_HDMI_PSAP, 0x15);
            }
            else
#endif
            {
                pData[0] = ScalerGetDataPortSingleByte(P72_CD_HDMI_PSAP, 0x15);
            }

            if(((pData[0] & 0xF0) == 0x00) || ((pData[0] & 0xF0) == 0x10))
            {
                return _TRUE;
            }
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_MAC_RX4_SUPPORT == _ON)

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX4_VERSION() == _AUDIO_INPUT_FROM_FRL)
            {
                pData[0] = ScalerGetDataPortSingleByte(P78_CD_HDMI_PSAP, 0x15);
            }
            else
#endif
            {
                pData[0] = ScalerGetDataPortSingleByte(P73_CD_HDMI_PSAP, 0x15);
            }

            if(((pData[0] & 0xF0) == 0x00) || ((pData[0] & 0xF0) == 0x10))
            {
                return _TRUE;
            }
#endif
            break;

        case _AUDIO_FROM_PXP_PORT:

            break;

        case _AUDIO_FROM_MST2SST_PORT:

            break;

        default:
            break;
    }

    return _FALSE;
}

#if(_HW_HDMI_AUDIO_8CH_LAYOUT_NORMAL_OUTPUT == _OFF)
//--------------------------------------------------
// Description  : Audio SPDIF/IIS Output Select
// Input Value  : EnumAudioIisSpdifOutput
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioHdmiI2sSpdifChannelOutputSelect(EnumAudioIisSpdifOutput enumAudioIisSpdifOutput, EnumInputPort enumInputPort)
{
    enumAudioIisSpdifOutput = enumAudioIisSpdifOutput;

    switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
    {
        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
            ScalerHdmiAudioRx3I2sSpdifChannelOutputSelect(enumAudioIisSpdifOutput);
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
            ScalerHdmiAudioRx4I2sSpdifChannelOutputSelect(enumAudioIisSpdifOutput);
#endif
            break;

        default:
            break;
    }
}
#endif
#endif

//--------------------------------------------------
// Description  : Get Current Digital Audio Source type
// Input Value  : None
// Output Value : Digital Audio Source
//--------------------------------------------------
EnumSourceType ScalerAudioDigitalAudioSourceType(EnumAudioOutputType enumAudioOutput)
{
    switch(ScalerAudioGetDigitalAudioPort(enumAudioOutput))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _AUDIO_FROM_RX0_PORT:

            return _SOURCE_DP;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _AUDIO_FROM_RX1_PORT:

            return _SOURCE_DP;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _AUDIO_FROM_RX2_PORT:

            return _SOURCE_DP;
#endif

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
        case _AUDIO_FROM_RX3_PORT:

            return _SOURCE_HDMI;
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
        case _AUDIO_FROM_RX4_PORT:

            return _SOURCE_HDMI;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _AUDIO_FROM_PXP_PORT:

            return _SOURCE_DP;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _AUDIO_FROM_MST2SST_PORT:

            return _SOURCE_DP;
#endif

        default:
            break;
    }

    return _SOURCE_NONE;
}

#if(_LINE_IN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current DAC Input Source
// Input Value  : None
// Output Value : _LINE_IN_AUDIO/ _DIGITAL_AUDIO
//--------------------------------------------------
EnumAudioInputSource ScalerAudioGetInputSource(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
            return ((ScalerGetBit(P6F_01_MUX_DA_DVC_IN, (_BIT7 | _BIT6 | _BIT5)) != (_BIT7 | _BIT6)) ? _DIGITAL_AUDIO : _LINE_IN_AUDIO);
#else
            return ((ScalerGetBit(P6_D1_DA_MUTE, _BIT3) == 0x00) ? _DIGITAL_AUDIO : _LINE_IN_AUDIO);
#endif
            break;
#endif

        case _AUDIO_DAC_OUT:
            return ((ScalerGetBit(P6_D1_DA_MUTE, _BIT3) == 0x00) ? _DIGITAL_AUDIO : _LINE_IN_AUDIO);
            break;

        default:
            break;
    }
    return _DIGITAL_AUDIO;
}

//--------------------------------------------------
// Description  : Get Current DAC Input Source
// Input Value  : None
// Output Value : _LINE_IN_AUDIO/ _DIGITAL_AUDIO
//--------------------------------------------------
EnumAudioInputSource ScalerAudioGetInputSource_EXINT0(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
            return ((ScalerGetBit_EXINT(P6F_01_MUX_DA_DVC_IN, (_BIT7 | _BIT6 | _BIT5)) != (_BIT7 | _BIT6)) ? _DIGITAL_AUDIO : _LINE_IN_AUDIO);
#else
            return ((ScalerGetBit_EXINT(P6_D1_DA_MUTE, _BIT3) == 0x00) ? _DIGITAL_AUDIO : _LINE_IN_AUDIO);
#endif
            break;
#endif

        case _AUDIO_DAC_OUT:
            return ((ScalerGetBit_EXINT(P6_D1_DA_MUTE, _BIT3) == 0x00) ? _DIGITAL_AUDIO : _LINE_IN_AUDIO);
            break;

        default:
            break;
    }
    return _DIGITAL_AUDIO;
}

//--------------------------------------------------
// Description  : Audio Soft Reset for ADC&DAC Path
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioADCDACSoftReset(void)
{
#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
    // I2S/SPDIF DVC Soft Audio Enable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~(_BIT3 | _BIT2), 0x00);
#else
    // I2S/SPDIF Audio Soft Audio Enable
    ScalerSetBit(P6_BB_SOFT_RESET_ADC, ~(_BIT6 | _BIT5), 0x00);
#endif

    // Soft Reset Enable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // ADC Filter Soft Reset Enable
    ScalerSetBit(P6_BB_SOFT_RESET_ADC, ~_BIT7, 0x00);

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
    // I2S/SPDIF DVC Soft Audio Disable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
#else
    // I2S/SPDIF Audio Soft Audio Disable
    ScalerSetBit(P6_BB_SOFT_RESET_ADC, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
#endif

    // DAC Soft Reset Disable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~_BIT4, _BIT4);

    // DA Gain Double buffer
    ScalerSetBit(P6_D2_DA_GAIN_L, ~_BIT7, _BIT7);

    // Top DVC Soft Reset Disable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~_BIT5, _BIT5);

    // TTS DVC Soft Reset Disable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~_BIT6, _BIT6);

    // Mixer DVC Soft Reset Disable
    ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~_BIT7, _BIT7);

    // ADC Filter Soft Reset Disable
    ScalerSetBit(P6_BB_SOFT_RESET_ADC, ~_BIT7, _BIT7);

    // AD Gain Double buffer
    ScalerSetBit(_REG_AD_GAIN_DB_L, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Initial ADC Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioSetADCAudioPLL(void)
{
    // Set ADC Audio PLL Off Proc
    ScalerAudioSetADCAudioPLLOffProc();

    // Set ADC Audio PLL On Proc
    ScalerAudioSetADCAudioPLLOnProc();
}

//--------------------------------------------------
// Description  : Set ADC Audio PLL On Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioSetADCAudioPLLOnProc(void)
{
    // Audio PLL Power On
    ScalerSetBit(PBF_A8_AUDIO_PLL_CONTROL, ~_BIT0, 0x00);

#if(_EXT_XTAL == _XTAL14318K)
    // Set Xtal as Audio PLL Input clock
    ScalerSetBit(PBF_A3_PLL_IN_CONTROL, ~(_BIT7 | _BIT6), _AUDIO_PLL_IN_EXT_XTAL_CLK);
#endif

    // Set N-code of NF PLL ref Xtal 14.318M
    // Set Audio PLL Analog Divider, need double buffer
    // Set Audio PLL Predivider
    ScalerSetByte(PBF_A4_M2PLL_DIVIDER0, (_AUDIO_PLL_PREDIVIDER_N - 2));

    // Set Audio PLL Output Divider (Analog)
    ScalerSetBit(PBF_A5_AUDIO_PLL_DIVIDER1, ~(_BIT7 | _BIT1 | _BIT0), (((BYTE)_AUDIO_PLL_PREDIVIDER_BPN << 7) | _AUDIO_PLL_O_DIV));

    ScalerSetByte(PBF_AD_N_F_CODE_1, _ADC_AUDIO_PLL_N);

    // Set F-code of NF PLL
    ScalerSetBit(PBF_AE_N_F_CODE_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIWORD(_ADC_AUDIO_PLL_F) & 0x0F));
    ScalerSetByte(PBF_AF_N_F_CODE_3, HIBYTE(LOWORD(_ADC_AUDIO_PLL_F)));
    ScalerSetByte(PBF_B0_N_F_CODE_4, LOBYTE(LOWORD(_ADC_AUDIO_PLL_F)));

    // Dobule Buffer
    ScalerSetByte(PBF_AC_N_F_CODE_0, _BIT0);

    // Power On Audio PLL
    ScalerSetBit(PBF_A8_AUDIO_PLL_CONTROL, ~_BIT0, 0x00);

    DebugMessageAudio("0.[Top Audio]Audio ADC PLL Proc ON", 0x00);
}

//--------------------------------------------------
// Description  : Set ADC Audio PLL Off Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioSetADCAudioPLLOffProc(void)
{
    // Audio PLL Power Down
    ScalerSetBit(PBF_A8_AUDIO_PLL_CONTROL, ~_BIT0, _BIT0);

    // Set Output Divider = 6 (Digital)
    ScalerSetBit(PBF_A2_PLL_OUT_CONTROL, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    //**********************************************************************
    // Audio ADC PLL Parameters Setting
    // Fref = Xtal = 14.318MHz
    // Target Clock = 393.216MHz => N = 27, F = 0.463053191
    // --------------------
    // U28 Icp Calculate
    // --------------------
    // N = 25 + 2 => 0x19 (Hex)
    // F = 0.463053191 x 2^16 = 0x768AA
    // VCO band = 2b'10 (320MHz ~ 380MHz) => Kvco = 1804
    // Icp = (700 * loopdivider * 2 * pi) / (Kvco * Rs)
    // Icp = (700 * 27 * 2 * 3.14) / (1804 * 6.5)
    // Icp = 10.122uA
    // --------------------
    // U22 Icp Calculate
    // --------------------
    // N = 25 + 2 => 27 (Dec)
    // Icp = 27 * 0.25uA
    // Icp = 6.75uA
    // reg_dpll_cp_i = 2'b010 (7.5uA)
    //**********************************************************************

    // Set Audio PLL Output Divider (Analog)
    ScalerSetBit(PBF_A5_AUDIO_PLL_DIVIDER1, ~(_BIT1 | _BIT0), (_AUDIO_PLL_O_DIV));

#if(_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_0)
    // Set Icp Current = 10uA
    ScalerSetBit(PBF_A6_AUDIO_PLL_0, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
#elif(_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_1)
    // Set Icp Current = 7.5uA
    ScalerSetBit(PBF_A6_AUDIO_PLL_0, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
#endif

    // Initial VCO Band = 10
    ScalerSetBit(PBF_A7_AUDIO_PLL_1, ~(_BIT5 | _BIT4), _BIT5);

#if(_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_0)
    // Initial PI current = 5uA
    ScalerSetBit(PBF_A7_AUDIO_PLL_1, ~(_BIT1 | _BIT0), _BIT1);
#elif(_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_1)
    // Initial PI current = 2.5uA
    ScalerSetBit(PBF_A7_AUDIO_PLL_1, ~(_BIT1 | _BIT0), 0x00);
#endif
}

#endif // End of #if(_LINE_IN_SUPPORT == _ON)

#if(_EMBEDDED_DAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Change Auido DAC State
// Input Value  : Target Audio DAC State
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACSetState(EnumAudioDACState enumTargetState)
{
    SET_AUDIO_DAC_STATE(enumTargetState);
    SET_AUDIO_DAC_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Get Curretn DAC State
// Input Value  : None
// Output Value : Current DAC State
//--------------------------------------------------
EnumAudioDACState ScalerAudioDACGetState(void)
{
    return GET_AUDIO_DAC_STATE();
}

//--------------------------------------------------
// Description  : Get Curretn DAC State Change
// Input Value  : None
// Output Value : TRUE => State Changed
//--------------------------------------------------
bit ScalerAudioDACGetStateChange(void)
{
    return GET_AUDIO_DAC_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Clear DAC State Change
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACClrStateChange(void)
{
    CLR_AUDIO_DAC_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Check if do Normal to Depop flow
// Input Value  : EnumAudioInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACNormalToDepopCheck(EnumAudioInputPort enumAudioInput)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource(_AUDIO_DAC_OUT) == _DIGITAL_AUDIO)
#endif
    {
        if(ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT) == enumAudioInput)
        {
            if(ScalerAudioDACGetState() == _AUDIO_DAC_READY)
            {
                ScalerAudioDACNormalToDepop();
            }
        }
    }
}
#endif

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Handle Smapling Frequency Infomation in SPDIF format
// Input Value  : enumAudioSource, enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioSpdifChannelStatusProc(EnumAudioInputSource enumAudioSourceType, EnumInputPort enumInputPort)
{
    if(enumAudioSourceType == _DIGITAL_AUDIO)
    {
        ScalerAudioSpdifCheckIfSamplingFrequencyChange(enumInputPort);
    }
    else if(enumAudioSourceType == _LINE_IN_AUDIO)
    {
        ScalerSetBit(_REG_AD_SPDIF_CS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_48KHZ);
    }
}

//--------------------------------------------------
// Description  : Detect and Change Smapling Frequency Infomation in SPDIF format
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioSpdifCheckIfSamplingFrequencyChange(EnumInputPort enumInputPort)
{
    switch(ScalerAudioSamplingFreqDetect(enumInputPort))
    {
        case _AUDIO_FREQ_PACKET_32K:

            ScalerSetBit(_REG_AD_SPDIF_CS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_32KHZ);

            break;

        case _AUDIO_FREQ_PACKET_44_1K:

            ScalerSetBit(_REG_AD_SPDIF_CS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_44_1KHZ);

            break;

        case _AUDIO_FREQ_PACKET_48K:

            ScalerSetBit(_REG_AD_SPDIF_CS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_48KHZ);

            break;

        case _AUDIO_FREQ_PACKET_88_2K:

            ScalerSetBit(_REG_AD_SPDIF_CS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_88_2KHZ);

            break;

        case _AUDIO_FREQ_PACKET_96K:

            ScalerSetBit(_REG_AD_SPDIF_CS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_96KHZ);

            break;

        case _AUDIO_FREQ_PACKET_176_4K:

            ScalerSetBit(_REG_AD_SPDIF_CS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_176_4KHZ);

            break;

        case _AUDIO_FREQ_PACKET_192K:

            ScalerSetBit(_REG_AD_SPDIF_CS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_192KHZ);

            break;

        default:

            ScalerSetBit(_REG_AD_SPDIF_CS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_NOT_INDICATED);

            break;
    }
}
#endif // End of #if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)

#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Parallel Mode spdif Setting
// Input Value  : EnumAudioSpdifParallelMode/EnumAudioCodingType
// Output Value : None
//--------------------------------------------------
void ScalerAudioSpdifParallelModeSet(EnumAudioSpdifParallelMode enumAudioSpdifParallelMode)
{
    enumAudioSpdifParallelMode = enumAudioSpdifParallelMode;

    // Enable SPDIF Parallel Mode
    ScalerSetBit(P6F_C0_SPDIF_GEN_CTRL_0, ~(_BIT7 | _BIT0), _BIT7);

    // Enable BCM Decode
    ScalerSetBit(P6F_C1_SPDIF_GEN_CTRL_1, ~_BIT7, _BIT7);

#if(_AUDIO_FORCE_PARALLEL_MODE == _ON)
    // Set Parallel Mode 1 to 1
    ScalerSetBit(P6F_C0_SPDIF_GEN_CTRL_0, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

    DebugMessageAudio("Audio Parallel Mode SPDIF 1 to 1", 0x00);
#else
    if(enumAudioSpdifParallelMode == _SPDIF_1_TO_4)
    {
        // Set Parallel Mode 1 to 4
        ScalerSetBit(P6F_C0_SPDIF_GEN_CTRL_0, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);

        // Channel Status Regen Mode,   V/U Bit Bypass
        ScalerSetBit(P6F_C0_SPDIF_GEN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

        // Set Channel Status HBR Mode
        ScalerSetBit(P6F_C1_SPDIF_GEN_CTRL_1, ~_BIT3, _BIT3);

        if(ScalerTimerPollingFlagProc(10, P6F_E0_SPDIF_GEN_CTRL_8, _BIT1, _TRUE) == _TRUE)
        {
            ScalerSetByte(P6F_C8_CH_STATUS_REGEN_BYTE_0, (ScalerGetByte(P6F_E1_CH_STATUS_PARSER_0)));
            ScalerSetByte(P6F_C9_CH_STATUS_REGEN_BYTE_1, (ScalerGetByte(P6F_E2_CH_STATUS_PARSER_1)));
            ScalerSetByte(P6F_CA_CH_STATUS_REGEN_BYTE_2, (ScalerGetByte(P6F_E3_CH_STATUS_PARSER_2)));
            ScalerSetByte(P6F_CB_CH_STATUS_REGEN_BYTE_3, (ScalerGetByte(P6F_E4_CH_STATUS_PARSER_3)));
            ScalerSetByte(P6F_CC_CH_STATUS_REGEN_BYTE_4, (ScalerGetByte(P6F_E5_CH_STATUS_PARSER_4)));
            ScalerSetByte(P6F_CD_CH_STATUS_REGEN_BYTE_5, (ScalerGetByte(P6F_E6_CH_STATUS_PARSER_5)));
            ScalerSetByte(P6F_CE_CH_STATUS_REGEN_BYTE_6, (ScalerGetByte(P6F_E7_CH_STATUS_PARSER_6)));
            ScalerSetByte(P6F_CF_CH_STATUS_REGEN_BYTE_7, (ScalerGetByte(P6F_E8_CH_STATUS_PARSER_7)));
            ScalerSetByte(P6F_D0_CH_STATUS_REGEN_BYTE_8, (ScalerGetByte(P6F_E9_CH_STATUS_PARSER_8)));
            ScalerSetByte(P6F_D1_CH_STATUS_REGEN_BYTE_9, (ScalerGetByte(P6F_EA_CH_STATUS_PARSER_9)));
            ScalerSetByte(P6F_D2_CH_STATUS_REGEN_BYTE_10, (ScalerGetByte(P6F_EB_CH_STATUS_PARSER_10)));
            ScalerSetByte(P6F_D3_CH_STATUS_REGEN_BYTE_11, (ScalerGetByte(P6F_EC_CH_STATUS_PARSER_11)));
            ScalerSetByte(P6F_D4_CH_STATUS_REGEN_BYTE_12, (ScalerGetByte(P6F_ED_CH_STATUS_PARSER_12)));
            ScalerSetByte(P6F_D5_CH_STATUS_REGEN_BYTE_13, (ScalerGetByte(P6F_EE_CH_STATUS_PARSER_13)));
            ScalerSetByte(P6F_D6_CH_STATUS_REGEN_BYTE_14, (ScalerGetByte(P6F_EF_CH_STATUS_PARSER_14)));
            ScalerSetByte(P6F_D7_CH_STATUS_REGEN_BYTE_15, (ScalerGetByte(P6F_F0_CH_STATUS_PARSER_15)));
            ScalerSetByte(P6F_D8_CH_STATUS_REGEN_BYTE_16, (ScalerGetByte(P6F_F1_CH_STATUS_PARSER_16)));
            ScalerSetByte(P6F_D9_CH_STATUS_REGEN_BYTE_17, (ScalerGetByte(P6F_F2_CH_STATUS_PARSER_17)));
            ScalerSetByte(P6F_DA_CH_STATUS_REGEN_BYTE_18, (ScalerGetByte(P6F_F3_CH_STATUS_PARSER_18)));
            ScalerSetByte(P6F_DB_CH_STATUS_REGEN_BYTE_19, (ScalerGetByte(P6F_F4_CH_STATUS_PARSER_19)));
            ScalerSetByte(P6F_DC_CH_STATUS_REGEN_BYTE_20, (ScalerGetByte(P6F_F5_CH_STATUS_PARSER_20)));
            ScalerSetByte(P6F_DD_CH_STATUS_REGEN_BYTE_21, (ScalerGetByte(P6F_F6_CH_STATUS_PARSER_21)));
            ScalerSetByte(P6F_DE_CH_STATUS_REGEN_BYTE_22, (ScalerGetByte(P6F_F7_CH_STATUS_PARSER_22)));
            ScalerSetByte(P6F_DF_CH_STATUS_REGEN_BYTE_23, (ScalerGetByte(P6F_F8_CH_STATUS_PARSER_23)));
        }

        DebugMessageAudio("Audio Parallel Mode SPDIF 1 to 4", 0x00);
    }
    else if(enumAudioSpdifParallelMode == _SPDIF_1_TO_2)
    {
        // Set Parallel Mode 1 to 2
        ScalerSetBit(P6F_C0_SPDIF_GEN_CTRL_0, ~(_BIT6 | _BIT5 | _BIT0), _BIT5);

        // V/U Bit / Channel Status Bypass Mode
        ScalerSetBit(P6F_C0_SPDIF_GEN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        DebugMessageAudio("Audio Parallel Mode SPDIF 1 to 2", 0x00);
    }
#endif

    // Set Preamble Regen Mode
    ScalerSetBit(P6F_C0_SPDIF_GEN_CTRL_0, ~(_BIT4 | _BIT0), _BIT4);

    // Set Pa/Pb Detect
    ScalerSetBit(P6F_C1_SPDIF_GEN_CTRL_1, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // Set Zero Padding Count Detect(4 Zero Padding)
    ScalerSetByte(P6F_C7_SPDIF_GEN_CTRL_7, 0x02);

    // Set Pa/Pb
    ScalerSetByte(P6F_C3_SPDIF_GEN_CTRL_3, 0xF8);
    ScalerSetByte(P6F_C4_SPDIF_GEN_CTRL_4, 0x72);
    ScalerSetByte(P6F_C5_SPDIF_GEN_CTRL_5, 0x4E);
    ScalerSetByte(P6F_C6_SPDIF_GEN_CTRL_6, 0x1F);

    // Enable SPDIF Parallel Mode
    ScalerSetBit(P6F_C0_SPDIF_GEN_CTRL_0, ~(_BIT7 | _BIT0), 0x00);
    ScalerSetBit(P6F_C0_SPDIF_GEN_CTRL_0, ~(_BIT7 | _BIT0), _BIT7);

    // SPDIF AFIFO Write
    ScalerSetBit(P6F_E0_SPDIF_GEN_CTRL_8, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1), _BIT3);

    // Switch To SPDIF Parallel Mode Path
    ScalerSetBit(P6F_08_ADI_IIS_SPDIF_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Audio Parallel Mode spdif Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioSpdifParallelModeReset(void)
{
    // Switch To ADI Path
    ScalerSetBit(P6F_08_ADI_IIS_SPDIF_CTRL, ~_BIT0, 0x00);

    // SPDIF AFIFO Write / Channel Status Reset
    ScalerSetBit(P6F_E0_SPDIF_GEN_CTRL_8, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT2 | _BIT1));

    // Disable BCM Decode
    ScalerSetBit(P6F_C1_SPDIF_GEN_CTRL_1, ~_BIT7, 0x00);

    // Disable SPDIF Parallel Mode
    ScalerSetBit(P6F_C0_SPDIF_GEN_CTRL_0, ~(_BIT7 | _BIT0), _BIT0);

    DebugMessageAudio("Audio SPDIF Parallel Mode Reset", 0x00);
}
#endif

#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Parallel Mode spdif Setting
// Input Value  : StructAudioI2sParallelMode
// Output Value : None
//--------------------------------------------------
void ScalerAudioI2sParallelModeSet(EnumAudioI2sParallelMode enumAudioI2sParallelMode, EnumAudioI2sParallelType enumAudioI2sParallelType)
{
#if(_AUDIO_FORCE_PARALLEL_MODE == _ON)
    // Set Parallel Mode 1 to 1
    ScalerSetBit(P6F_FA_IIS_GEN_CTRL_0, ~(_BIT6 | _BIT5), 0x00);

    DebugMessageAudio("Audio I2S Parallel Mode 1 to 1", 0x00);
#else
    if(enumAudioI2sParallelMode == _I2S_1_TO_4)
    {
        // Set Parallel Mode 1 to 4
        ScalerSetBit(P6F_FA_IIS_GEN_CTRL_0, ~(_BIT6 | _BIT5), _BIT6);

        DebugMessageAudio("Audio I2S Parallel Mode 1 to 4", 0x00);
    }
    else if(enumAudioI2sParallelMode == _I2S_1_TO_2)
    {
        // Set Parallel Mode 1 to 2
        ScalerSetBit(P6F_FA_IIS_GEN_CTRL_0, ~(_BIT6 | _BIT5), _BIT5);

        DebugMessageAudio("Audio I2S Parallel Mode 1 to 2", 0x00);
    }
#endif

    if(enumAudioI2sParallelType == _I2S_PHILIP32_24BIT)
    {
        // Set I2S_PHILIP32_24BIT Type
        ScalerSetBit(P6F_FB_IIS_GEN_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT5);

        if(enumAudioI2sParallelMode == _I2S_1_TO_2)
        {
            // Set MCK/SCK For I2S_PHILIP32_24BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
        }
        else if(enumAudioI2sParallelMode == _I2S_1_TO_4)
        {
            // Set MCK/SCK For I2S_PHILIP32_24BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));
        }
    }
    else if(enumAudioI2sParallelType == _I2S_PHILIP32_16BIT)
    {
        // Set I2S_PHILIP32_16BIT Type
        ScalerSetBit(P6F_FB_IIS_GEN_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT4 | _BIT1));

        if(enumAudioI2sParallelMode == _I2S_1_TO_2)
        {
            // Set MCK/SCK For I2S_PHILIP32_16BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
        }
        else if(enumAudioI2sParallelMode == _I2S_1_TO_4)
        {
            // Set MCK/SCK For I2S_PHILIP32_16BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));
        }
    }
    else if(enumAudioI2sParallelType == _I2S_PHILIP16_16BIT)
    {
        // Set I2S_PHILIP16_16BIT Type
        ScalerSetBit(P6F_FB_IIS_GEN_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT1);

        if(enumAudioI2sParallelMode == _I2S_1_TO_2)
        {
            // Set MCK/SCK For I2S_PHILIP16_16BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        }
        else if(enumAudioI2sParallelMode == _I2S_1_TO_4)
        {
            // Set MCK/SCK For I2S_PHILIP16_16BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
        }
    }
    else if(enumAudioI2sParallelType == _I2S_LEFT32_24BIT)
    {
        // Set I2S_LEFT32_24BIT Type
        ScalerSetBit(P6F_FB_IIS_GEN_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

        if(enumAudioI2sParallelMode == _I2S_1_TO_2)
        {
            // Set MCK/SCK For I2S_LEFT32_24BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
        }
        else if(enumAudioI2sParallelMode == _I2S_1_TO_4)
        {
            // Set MCK/SCK For I2S_LEFT32_24BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));
        }
    }
    else if(enumAudioI2sParallelType == _I2S_LEFT32_16BIT)
    {
        // Set I2S_LEFT32_16BIT Type
        ScalerSetBit(P6F_FB_IIS_GEN_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT0));

        if(enumAudioI2sParallelMode == _I2S_1_TO_2)
        {
            // Set MCK/SCK For I2S_LEFT32_16BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
        }
        else if(enumAudioI2sParallelMode == _I2S_1_TO_4)
        {
            // Set MCK/SCK For I2S_LEFT32_16BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));
        }
    }
    else if(enumAudioI2sParallelType == _I2S_RIGHT32_24BIT)
    {
        // Set I2S_RIGHT32_24BIT Type
        ScalerSetBit(P6F_FB_IIS_GEN_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT1));

        if(enumAudioI2sParallelMode == _I2S_1_TO_2)
        {
            // Set MCK/SCK For I2S_RIGHT32_24BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
        }
        else if(enumAudioI2sParallelMode == _I2S_1_TO_4)
        {
            // Set MCK/SCK For I2S_RIGHT32_24BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));
        }
    }
    else if(enumAudioI2sParallelType == _I2S_RIGHT32_16BIT)
    {
        // Set I2S_RIGHT32_16BIT Type
        ScalerSetBit(P6F_FB_IIS_GEN_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT7 | _BIT4 | _BIT0));

        if(enumAudioI2sParallelMode == _I2S_1_TO_2)
        {
            // Set MCK/SCK For I2S_RIGHT32_16BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
        }
        else if(enumAudioI2sParallelMode == _I2S_1_TO_4)
        {
            // Set MCK/SCK For I2S_RIGHT32_16BIT Type
            ScalerSetBit(P6F_FD_IIS_GEN_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));
        }
    }

    // Enable I2S Parallel Mode
    ScalerSetBit(P6F_FA_IIS_GEN_CTRL_0, ~_BIT7, _BIT7);

    // Switch To I2S Parallel Mode Path
    ScalerSetBit(P6F_08_ADI_IIS_SPDIF_CTRL, ~_BIT1, _BIT1);
}

//--------------------------------------------------
// Description  : Audio Parallel Mode spdif Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioI2sParallelModeReset(void)
{
    // Switch To ADI Path
    ScalerSetBit(P6F_08_ADI_IIS_SPDIF_CTRL, ~_BIT1, 0x00);

    // Disable I2S Parallel Mode
    ScalerSetBit(P6F_FA_IIS_GEN_CTRL_0, ~_BIT7, 0x00);

    DebugMessageAudio("Audio Parallel Mode I2S Reset", 0x00);
}
#endif

//--------------------------------------------------
// Description  : Audio Parallel Mode Stable Check
// Input Value  : None
// Output Value : TRUE/FALSE
//--------------------------------------------------
bit ScalerAudioParallelModePlaybackStableCheck(void)
{
#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
    if((ScalerGetBit(P6F_E0_SPDIF_GEN_CTRL_8, _BIT6) == _BIT6) && (ScalerGetBit(P6F_C0_SPDIF_GEN_CTRL_0, _BIT7) == _BIT7))
    {
        // Write 1 Clear SPDIF CTS FIFO Unsatble Flag
        ScalerSetBit(P6F_E0_SPDIF_GEN_CTRL_8, ~(_BIT6 | _BIT2 | _BIT1), _BIT6);

        DebugMessageAudio("Audio Parallel Mode SPDIF CTS FIFO Unsatble", 0x00);

        return _FALSE;
    }
#endif

#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
    if((ScalerGetBit(P6F_FC_IIS_GEN_CTRL_2, _BIT7) == _BIT7) && (ScalerGetBit(P6F_FA_IIS_GEN_CTRL_0, _BIT7) == _BIT7))
    {
        // Write 1 Clear I2S CTS FIFO Unsatble Flag
        ScalerSetBit(P6F_FC_IIS_GEN_CTRL_2, ~_BIT7, _BIT7);

        DebugMessageAudio("Audio Parallel Mode I2S CTS FIFO Unsatble", 0x00);

        return _FALSE;
    }
#endif
    return _TRUE;
}
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Frequency Set By User Define
// Input Value  : EnumAudioSamplingFreqType
// Output Value : None
//--------------------------------------------------
void ScalerAudioSetUserDefineAudioGenFrequency(EnumAudioSamplingFreqType enumAudioFreq)
{
    BYTE ucSCode = ScalerAudioGetSamplingFreqPacket(enumAudioFreq);

    // Avoid Divider to be 0
    ucSCode = (ucSCode == 0 ? _AUDIO_FREQ_32K : ucSCode);

    // Update Audio Frequency
    SET_AUDIO_GEN_FREQ_MAPPING(enumAudioFreq);

    // Set Frequency Parameters
    switch(enumAudioFreq)
    {
        case _AUDIO_FREQ_32K:
        case _AUDIO_FREQ_64K:
        case _AUDIO_FREQ_128K:
        case _AUDIO_FREQ_256K:
        case _AUDIO_FREQ_512K:

            ucSCode = ((WORD)48 * 32) / ucSCode;

            SET_AUDIO_GEN_FREQ_S_CODE(ucSCode | _BIT7);
            SET_AUDIO_GEN_FREQ_N_CODE(_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE);
            SET_AUDIO_GEN_FREQ_F_CODE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE);

            break;

        case _AUDIO_FREQ_44_1K:
        case _AUDIO_FREQ_88_2K:
        case _AUDIO_FREQ_176_4K:
        case _AUDIO_FREQ_352_8K:
        case _AUDIO_FREQ_705_6K:

            ucSCode = ((WORD)32 * 44) / ucSCode;

            SET_AUDIO_GEN_FREQ_S_CODE(ucSCode | _BIT7);
            SET_AUDIO_GEN_FREQ_N_CODE(_HDMI_SAMPLING_FREQ_44K_GROUP_N_CODE);
            SET_AUDIO_GEN_FREQ_F_CODE(_HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE);

            break;

        case _AUDIO_FREQ_48K:
        case _AUDIO_FREQ_96K:
        case _AUDIO_FREQ_192K:
        case _AUDIO_FREQ_384K:
        case _AUDIO_FREQ_768K:

            ucSCode = ((WORD)32 * 48) / ucSCode;

            SET_AUDIO_GEN_FREQ_S_CODE(ucSCode | _BIT7);
            SET_AUDIO_GEN_FREQ_N_CODE(_HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE);
            SET_AUDIO_GEN_FREQ_F_CODE(_HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE);

            break;

        default:

            // Set Frequency Parameters to 500Hz
            SET_AUDIO_GEN_FREQ_S_CODE(_HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);
            SET_AUDIO_GEN_FREQ_N_CODE(_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE);
            SET_AUDIO_GEN_FREQ_F_CODE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE);

            break;
    }
}

//--------------------------------------------------
// Description  : Get Whether Internal Audio Pattern Gen is Enabled
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerAudioGetInternalAudioGenEnable(EnumInputPort enumInputPort)
{
#if(_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON)
    // Check Whether Audio Pattern Gen is Enable
    if(GET_AUDIO_INTERNAL_GEN_ENABLE_STATE() == _ON)
    {
        return _ENABLE;
    }
#endif // End of #if(_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON)

    switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_MAC_RX0_SUPPORT == _ON)
            return ScalerDpAudioRx0GetInternalAudioGenEnable();
#endif

            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_MAC_RX1_SUPPORT == _ON)
            return ScalerDpAudioRx1GetInternalAudioGenEnable();
#endif

            break;

        case _AUDIO_FROM_RX2_PORT:

#if(_DP_MAC_RX2_SUPPORT == _ON)
            return ScalerDpAudioRx2GetInternalAudioGenEnable();
#endif

            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
            return ScalerHdmiAudioRx3GetInternalAudioGenEnable();
#endif

            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
            return ScalerHdmiAudioRx4GetInternalAudioGenEnable();
#endif

            break;

        case _AUDIO_FROM_PXP_PORT:

#if(_DP_MAC_RX3_SUPPORT == _ON)
            return ScalerDpAudioRx3GetInternalAudioGenEnable();
#endif

            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_MAC_RX4_SUPPORT == _ON)
            return ScalerDpAudioRx4GetInternalAudioGenEnable();
#endif

            break;

        default:
            break;
    }

    return _DISABLE;
}

//--------------------------------------------------
// Description  : Auido Speaker Testing Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerAudioInternalAudioGenSwitch(bit bOn, EnumInputPort enumInputPort, EnumAudioLeftRightChannelSelect enumAudioLeftRightChannelSelect)
{
    switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
    {
        case _AUDIO_FROM_RX0_PORT:

#if(_DP_MAC_RX0_SUPPORT == _ON)
            ScalerDpAudioRx0InternalAudioGenSwitch(bOn, enumAudioLeftRightChannelSelect);
#endif
            break;

        case _AUDIO_FROM_RX1_PORT:

#if(_DP_MAC_RX1_SUPPORT == _ON)
            ScalerDpAudioRx1InternalAudioGenSwitch(bOn, enumAudioLeftRightChannelSelect);
#endif
            break;

        case _AUDIO_FROM_RX2_PORT:

#if(_DP_MAC_RX2_SUPPORT == _ON)
            ScalerDpAudioRx2InternalAudioGenSwitch(bOn, enumAudioLeftRightChannelSelect);
#endif
            break;

        case _AUDIO_FROM_RX3_PORT:

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
            ScalerHdmiAudioRx3InternalAudioGenSwitch(bOn, enumAudioLeftRightChannelSelect);
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
            ScalerHdmiAudioRx4InternalAudioGenSwitch(bOn, enumAudioLeftRightChannelSelect);
#endif
            break;

        case _AUDIO_FROM_PXP_PORT:

#if(_DP_MAC_RX3_SUPPORT == _ON)
            ScalerDpAudioRx3InternalAudioGenSwitch(bOn, enumAudioLeftRightChannelSelect);
#endif
            break;

        case _AUDIO_FROM_MST2SST_PORT:

#if(_DP_MAC_RX4_SUPPORT == _ON)
            ScalerDpAudioRx4InternalAudioGenSwitch(bOn, enumAudioLeftRightChannelSelect);
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Auido Speaker Testing Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerAudioInternalAudioGenPowerControl(bit bOn, EnumInputPort enumInputPort)
{
    bOn = bOn;

    switch(ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_CURRENT))
    {
        case _AUDIO_FROM_RX0_PORT:

            break;

        case _AUDIO_FROM_RX1_PORT:

            break;

        case _AUDIO_FROM_RX2_PORT:

            break;

        case _AUDIO_FROM_RX3_PORT:

            break;

        case _AUDIO_FROM_RX4_PORT:

            break;

        case _AUDIO_FROM_RX5_PORT:

            break;

        default:
            break;
    }
}

#if(_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON)
//--------------------------------------------------
// Description  : Set Internal Audio Gen Test Statue
// Input Value  : _ON/ _OFF
// Output Value : None
//--------------------------------------------------
void ScalerAudioSetInternalGenTestUserState(bit bOn)
{
    SET_AUDIO_INTERNAL_GEN_ENABLE_STATE(bOn);
}
#endif // End of #if(_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON)
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Switch IIS/Spdif Path
// Input Value  : Audiopath/InputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioSwitchArcSpdifPath(EnumAudioInputSource enumAudioSourceType, EnumInputPort enumInputPort)
{
    EnumAudioInputPort enumAudioInputPort = ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_TARGET);

    if(enumAudioSourceType == _LINE_IN_AUDIO)
    {
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
        ScalerSetByte(P6F_00_MUX_DIG_OUT, (_AUDIO_FROM_ADC_PORT << 4) | _AUDIO_FROM_ADC_PORT);
#else
        // Set SPDIF Input
        ScalerSetBit(P6F_01_MUX_DA_DVC_IN, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));
#endif
    }
    else
    {
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
        // Set IIS Input
        ScalerSetBit(P6F_00_MUX_DIG_OUT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (enumAudioInputPort << 4));

        // Set SPDIF Input
        ScalerSetBit(P6F_00_MUX_DIG_OUT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumAudioInputPort);
#else
        // Set SPDIF Input
        ScalerSetBit(P6F_01_MUX_DA_DVC_IN, ~(_BIT7 | _BIT6 | _BIT5), (enumAudioInputPort << 5));
#endif
    }
}

//--------------------------------------------------
// Description  : Switch IIS/Spdif Path
// Input Value  : Audiopath/InputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioGetArcInterfaceInfo(StructAudioInterfaceInfoForArc *pstInterfaceAudioInfo)
{
    StructAudioChannelInfo stAudioChStatus;

    stAudioChStatus = ScalerAudioGetRxChannelStatus(_AUDIO_ARC_OUT);
    pstInterfaceAudioInfo->ucAudioChStatusByte0 = stAudioChStatus.ucChannelStaus0;
    pstInterfaceAudioInfo->ucAudioChStatusByte1 = stAudioChStatus.ucChannelStaus1;
    pstInterfaceAudioInfo->ucAudioChStatusByte2 = stAudioChStatus.ucChannelStaus2;
    pstInterfaceAudioInfo->ucAudioChStatusByte3 = stAudioChStatus.ucChannelStaus3;
    pstInterfaceAudioInfo->ucAudioChStatusByte4 = stAudioChStatus.ucChannelStaus4;

    pstInterfaceAudioInfo->ucAudioInfoPb4 = ScalerAudioGetArcAudioInfo(_ADUIO_INFO_PB4);
    pstInterfaceAudioInfo->ucAudioInfoPb5 = ScalerAudioGetArcAudioInfo(_ADUIO_INFO_PB5);
    pstInterfaceAudioInfo->ucAudioInfoPb6 = ScalerAudioGetArcAudioInfo(_ADUIO_INFO_PB6);
    pstInterfaceAudioInfo->ucAudioInfoPb7 = ScalerAudioGetArcAudioInfo(_ADUIO_INFO_PB7);
    pstInterfaceAudioInfo->ucAudioInfoPb8 = ScalerAudioGetArcAudioInfo(_ADUIO_INFO_PB8);
    pstInterfaceAudioInfo->ucAudioInfoPb9 = ScalerAudioGetArcAudioInfo(_ADUIO_INFO_PB9);
    pstInterfaceAudioInfo->ucAudioInfoPb10 = ScalerAudioGetArcAudioInfo(_ADUIO_INFO_PB10);

    pstInterfaceAudioInfo->enumAudioCodingType = ScalerAudioGetPathNonLPCMStatus(_AUDIO_ARC_OUT);
    pstInterfaceAudioInfo->enumAudioChannelCount = ScalerAudioGetRxChannelCount(_AUDIO_ARC_OUT);
    pstInterfaceAudioInfo->enumAudioFs = ScalerAudioSamplingFreqDetect(ScalerAudioGetDigitalAudioPortMapping(_AUDIO_ARC_OUT));
}

//--------------------------------------------------
// Description  : Get Audio Info
// Input Value  : enumAudioInfoContent
// Output Value : ucAudioInfo
//--------------------------------------------------
BYTE ScalerAudioGetArcAudioInfo(EnumAudioInfoContent enumAudioInfoContent)
{
    enumAudioInfoContent = enumAudioInfoContent;

    switch(ScalerAudioGetDigitalAudioPort(_AUDIO_ARC_OUT))
    {
        case _AUDIO_FROM_RX0_PORT:
#if(_DP_AUDIO_RX0_SUPPORT == _ON)
            // Get SDP Audio Infoframe
            return ScalerDpAudioRx0GetAudioInfoFrame(enumAudioInfoContent);
#endif
            break;

        case _AUDIO_FROM_RX1_PORT:
#if(_DP_AUDIO_RX1_SUPPORT == _ON)
            // Get SDP Audio Infoframe
            return ScalerDpAudioRx1GetAudioInfoFrame(enumAudioInfoContent);
#endif
            break;

        case _AUDIO_FROM_RX2_PORT:
#if(_DP_AUDIO_RX2_SUPPORT == _ON)
            // Get SDP Audio Infoframe
            return ScalerDpAudioRx2GetAudioInfoFrame(enumAudioInfoContent);
#endif
            break;

        case _AUDIO_FROM_RX3_PORT:
#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
            // Get SDP Audio Infoframe
            return ScalerHdmiAudioRx3GetAudioInfo(enumAudioInfoContent);
#endif
            break;

        case _AUDIO_FROM_RX4_PORT:
#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
            // Get SDP Audio Infoframe
            return ScalerHdmiAudioRx4GetAudioInfo(enumAudioInfoContent);
#endif
            break;

        case _AUDIO_FROM_ADC_PORT:
#if(_LINE_IN_SUPPORT == _ON)
#endif
            break;

        default:
            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Audio ARC Tx Get ARC Dx Port
// Input Value  : None
// Output Value : EnumOutputPort
//--------------------------------------------------
EnumInputPort ScalerAudioGetArcDxPort(void)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    if((_D1_HDMI_ARC_TX_PIN == _HDMI_ARC_TX) || (_D1_HDMI_ARC_TX_PIN == _HDMI_EARC_TX))
    {
        enumInputPort = _D1_INPUT_PORT;
    }
    else if((_D2_HDMI_ARC_TX_PIN == _HDMI_ARC_TX) || (_D2_HDMI_ARC_TX_PIN == _HDMI_EARC_TX))
    {
        enumInputPort = _D2_INPUT_PORT;
    }
    else if((_D3_HDMI_ARC_TX_PIN == _HDMI_ARC_TX) || (_D3_HDMI_ARC_TX_PIN == _HDMI_EARC_TX))
    {
        enumInputPort = _D3_INPUT_PORT;
    }
    else if((_D4_HDMI_ARC_TX_PIN == _HDMI_ARC_TX) || (_D4_HDMI_ARC_TX_PIN == _HDMI_EARC_TX))
    {
        enumInputPort = _D4_INPUT_PORT;
    }

    return enumInputPort;
}

//--------------------------------------------------
// Description  : Audio Trigger ARC Port HPD Toggle
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTriggerArcPortHpdToggle(void)
{
#if(_HDMI_SUPPORT == _ON)
    ScalerTmdsMacRxSetHPDTriggerEvent(ScalerAudioGetArcDxPort(), _TMDS_MAC_RX_HPD_ARC_EARC_INITIATE);
#endif
}

//--------------------------------------------------
// Description  : Get Current Digital Audio LPCM status
// Input Value  : None
// Output Value : Digital Audio Source
//--------------------------------------------------
EnumAudioCodingType ScalerAudioGetArcNonLPCMStatus(void)
{
    if(ScalerAudioLPCMCheckData(_AUDIO_ARC_OUT) == _TRUE)
    {
#if(_HDMI_SUPPORT == _ON)
        if(ScalerAudioDigitalAudioSourceType(_AUDIO_ARC_OUT) == _SOURCE_HDMI)
        {
            if(ScalerAudioLPCMCheckInfo(_AUDIO_ARC_OUT) == _TRUE)
            {
                return _AUDIO_LPCM;
            }
            else
            {
                return _AUDIO_NON_LPCM;
            }
        }
#endif
        return _AUDIO_LPCM;
    }
    return _AUDIO_NON_LPCM;
}
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_SUPPORT == _ON)
