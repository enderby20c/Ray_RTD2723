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
// ID Code      : UserCommonDsc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_DSC__

#include "UserCommonInclude.h"
#include "Dsc/UserCommonDsc.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Switch Port DSC Capability
// Input Value  : ucPreviousPort, ucCurrentPort
// Output Value :
//--------------------------------------------------
void UserCommonDscSwitchPortCapability(BYTE ucPreviousPort, BYTE ucCurrentPort)
{
    EnumDisplayMode enumDisplayModeTrans = GET_DISPLAY_MODE();
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayModeTrans = ScalerRegionEagleSightTransDisplayMode(enumDisplayModeTrans);
#endif

    if(enumDisplayModeTrans == _DISPLAY_MODE_1P)
    {
        EnumDscSelectPort enumDscSelectPortStart = _DSC_FROM_D0_PORT;
        EnumDscSelectPort enumDscSelectPortEnd = _DSC_FROM_D4_PORT;
        EnumDscSelectPort enumDscSelectPortCnt = enumDscSelectPortStart;

        // Turn off All Port's DSC_ON Config
        if(ucPreviousPort != _DSC_FROM_NO_PORT)
        {
            if(ucCurrentPort == _DSC_FROM_NO_PORT)
            {
#if(_AUDIO_SUPPORT == _ON)
                // Mute Audio Output
                UserCommonAudioMuteCurrentDigitalPortProc(ucCurrentPort);
#endif
                for(enumDscSelectPortCnt = enumDscSelectPortStart; enumDscSelectPortCnt <= enumDscSelectPortEnd; enumDscSelectPortCnt++)
                {
                    WORD usDscPortTypeCnt = UserCommonDscMenuKeyGetInputPortType(enumDscSelectPortCnt);
                    EnumInputPort enumDscInputPortCnt = GET_INPUT_PORT(usDscPortTypeCnt);
                    EnumPortType enumDscPortTypeCnt = GET_PORT_TYPE(usDscPortTypeCnt);

                    UserCommonDscSwitchPortCapabilityProc(enumDscInputPortCnt, enumDscPortTypeCnt, _DSC_DECODER_SUPPORT_OFF);
                }
            }
        }

        // Turn on All Port's DSC_ON Config
        if(ucCurrentPort != _DSC_FROM_NO_PORT)
        {
            if(ucPreviousPort == _DSC_FROM_NO_PORT)
            {
#if(_AUDIO_SUPPORT == _ON)
                // Mute Audio Output
                UserCommonAudioMuteCurrentDigitalPortProc(ucCurrentPort);
#endif
                for(enumDscSelectPortCnt = enumDscSelectPortStart; enumDscSelectPortCnt <= enumDscSelectPortEnd; enumDscSelectPortCnt++)
                {
                    WORD usDscPortTypeCnt = UserCommonDscMenuKeyGetInputPortType(enumDscSelectPortCnt);
                    EnumInputPort enumDscInputPortCnt = GET_INPUT_PORT(usDscPortTypeCnt);
                    EnumPortType enumDscPortTypeCnt = GET_PORT_TYPE(usDscPortTypeCnt);

                    UserCommonDscSwitchPortCapabilityProc(enumDscInputPortCnt, enumDscPortTypeCnt, _DSC_DECODER_SUPPORT_ON);
                }
            }
        }
    }
    else
#if(_DSC_MULTI_DISPLAY_AUTO_SELECT_SUPPORT == _ON)
    {
        EnumDscSelectPort enumDscSelectPortStart = _DSC_FROM_D0_PORT;
        EnumDscSelectPort enumDscSelectPortEnd = _DSC_FROM_D4_PORT;
        EnumDscSelectPort enumDscSelectPortCnt = enumDscSelectPortStart;

        // Turn off All Port's DSC_ON Config
        if(ucPreviousPort != _DSC_FROM_NO_PORT)
        {
            if(ucCurrentPort == _DSC_FROM_NO_PORT)
            {
#if(_AUDIO_SUPPORT == _ON)
                // Mute Audio Output
                UserCommonAudioMuteCurrentDigitalPortProc(ucCurrentPort);
#endif
                for(enumDscSelectPortCnt = enumDscSelectPortStart; enumDscSelectPortCnt <= enumDscSelectPortEnd; enumDscSelectPortCnt++)
                {
                    WORD usDscPortTypeCnt = UserCommonDscMenuKeyGetInputPortType(enumDscSelectPortCnt);
                    EnumInputPort enumDscInputPortCnt = GET_INPUT_PORT(usDscPortTypeCnt);
                    EnumPortType enumDscPortTypeCnt = GET_PORT_TYPE(usDscPortTypeCnt);

                    UserCommonDscSwitchPortCapabilityProc(enumDscInputPortCnt, enumDscPortTypeCnt, _DSC_DECODER_SUPPORT_OFF);
                }
            }
        }

        // Turn on All Port's DSC_ON Config
        if(ucCurrentPort != _DSC_FROM_NO_PORT)
        {
            if(ucPreviousPort == _DSC_FROM_NO_PORT)
            {
#if(_AUDIO_SUPPORT == _ON)
                // Mute Audio Output
                UserCommonAudioMuteCurrentDigitalPortProc(ucCurrentPort);
#endif
                for(enumDscSelectPortCnt = enumDscSelectPortStart; enumDscSelectPortCnt <= enumDscSelectPortEnd; enumDscSelectPortCnt++)
                {
                    WORD usDscPortTypeCnt = UserCommonDscMenuKeyGetInputPortType(enumDscSelectPortCnt);
                    EnumInputPort enumDscInputPortCnt = GET_INPUT_PORT(usDscPortTypeCnt);
                    EnumPortType enumDscPortTypeCnt = GET_PORT_TYPE(usDscPortTypeCnt);

                    UserCommonDscSwitchPortCapabilityProc(enumDscInputPortCnt, enumDscPortTypeCnt, _DSC_DECODER_SUPPORT_ON);
                }
            }
        }
    }
#else
    {
        // User Define to User Define
        // Turn OFF Previous Port DSC Support
        if(ucPreviousPort != _DSC_FROM_NO_PORT)
        {
            WORD usPreviousPortType = UserCommonDscMenuKeyGetInputPortType(ucPreviousPort);
            EnumInputPort enumPreDscInputPort = GET_INPUT_PORT(usPreviousPortType);
            EnumPortType enumPreDscPortType = GET_PORT_TYPE(usPreviousPortType);

#if(_AUDIO_SUPPORT == _ON)
            // Mute Audio Output
            UserCommonAudioMuteCurrentDigitalPortProc(ucCurrentPort);
#endif
            UserCommonDscSwitchPortCapabilityProc(enumPreDscInputPort, enumPreDscPortType, _DSC_DECODER_SUPPORT_OFF);
        }

        // Turn on Current Port DSC Support
        if(ucCurrentPort != _DSC_FROM_NO_PORT)
        {
            WORD usCurrentPortType = UserCommonDscMenuKeyGetInputPortType(ucCurrentPort);
            EnumInputPort enumCurDscInputPort = GET_INPUT_PORT(usCurrentPortType);
            EnumPortType enumCurDscPortType = GET_PORT_TYPE(usCurrentPortType);

#if(_AUDIO_SUPPORT == _ON)
            // Mute Audio Output
            UserCommonAudioMuteCurrentDigitalPortProc(ucCurrentPort);
#endif
            UserCommonDscSwitchPortCapabilityProc(enumCurDscInputPort, enumCurDscPortType, _DSC_DECODER_SUPPORT_ON);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Switch Port DSC Capability
// Input Value  : ucPreviousPort, ucCurrentPort
// Output Value :
//--------------------------------------------------
void UserCommonDscSwitchDisplayModeCapability(void)
{
    EnumDscSelectPort enumDscSelectPortStart = _DSC_FROM_D0_PORT;
    EnumDscSelectPort enumDscSelectPortEnd = _DSC_FROM_D4_PORT;
    EnumDscSelectPort enumDscSelectPortCnt = enumDscSelectPortStart;

    for(enumDscSelectPortCnt = enumDscSelectPortStart; enumDscSelectPortCnt <= enumDscSelectPortEnd; enumDscSelectPortCnt++)
    {
        WORD usDscPortTypeCnt = UserCommonDscMenuKeyGetInputPortType(enumDscSelectPortCnt);
        EnumInputPort enumDscInputPortCnt = GET_INPUT_PORT(usDscPortTypeCnt);
        EnumPortType enumDscPortTypeCnt = GET_PORT_TYPE(usDscPortTypeCnt);

        if(UserInterfaceDscDecoderGetEnable(enumDscInputPortCnt) == _DSC_DECODER_SUPPORT_OFF)
        {
            // Turn off Selected Port's DSC_ON Config
            UserCommonDscSwitchPortCapabilityProc(enumDscInputPortCnt, enumDscPortTypeCnt, _DSC_DECODER_SUPPORT_OFF);
        }
        else
        {
            // Turn on Selected Port's DSC_ON Config
            UserCommonDscSwitchPortCapabilityProc(enumDscInputPortCnt, enumDscPortTypeCnt, _DSC_DECODER_SUPPORT_ON);
        }
    }
}

//--------------------------------------------------
// Description  : Switch Port DSC Capability
// Input Value  : enumInputPort -> target input port
//                enumPortType --> target port type
//                enumSupport ---> target status
// Output Value :
//--------------------------------------------------
void UserCommonDscSwitchPortCapabilityProc(EnumInputPort enumInputPort, EnumPortType enumPortType, EnumDscDecoderSupport enumSupport)
{
    switch(enumPortType)
    {
#if(_VGA_SUPPORT == _ON)
        case _PORT_VGA:
            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
            switch(enumInputPort)
            {
#if(_D1_HDMI_SUPPORT == _ON)
                case _D1_INPUT_PORT:
#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
                    if(UserInterfaceEdidCheckHdmiDscEdidIndexChange(_D1_INPUT_PORT) == _EDID_NEED_CHANGE)
                    {
                        // Switch EDID
                        UserCommonEdidSwitchHdmiEdid(_D1_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D1_INPUT_PORT));
                    }
#endif
                    break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
                case _D2_INPUT_PORT:
#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
                    if(UserInterfaceEdidCheckHdmiDscEdidIndexChange(_D2_INPUT_PORT) == _EDID_NEED_CHANGE)
                    {
                        // Switch EDID
                        UserCommonEdidSwitchHdmiEdid(_D2_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D2_INPUT_PORT));
                    }
#endif
                    break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
                case _D3_INPUT_PORT:
#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
                    if(UserInterfaceEdidCheckHdmiDscEdidIndexChange(_D3_INPUT_PORT) == _EDID_NEED_CHANGE)
                    {
                        // Switch EDID
                        UserCommonEdidSwitchHdmiEdid(_D3_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D3_INPUT_PORT));
                    }
#endif
                    break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
                case _D4_INPUT_PORT:
#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
                    if(UserInterfaceEdidCheckHdmiDscEdidIndexChange(_D4_INPUT_PORT) == _EDID_NEED_CHANGE)
                    {
                        // Switch EDID
                        UserCommonEdidSwitchHdmiEdid(_D4_INPUT_PORT, UserInterfaceEdidGetMultiHdmiEdidIndex(_D4_INPUT_PORT));
                    }
#endif
                    break;
#endif

                default:
                    break;
            }
#endif
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            switch(enumInputPort)
            {
#if(_D0_DP_SUPPORT == _ON)
                case _D0_INPUT_PORT:

                    // Config DPCD & HPD
                    ScalerDscDecoderSyncDpSupportSwitch(_D0_INPUT_PORT, enumSupport);
                    break;
#endif

#if(_D1_DP_SUPPORT == _ON)
                case _D1_INPUT_PORT:

                    // Config DPCD & HPD
                    ScalerDscDecoderSyncDpSupportSwitch(_D1_INPUT_PORT, enumSupport);
                    break;
#endif

#if(_D2_DP_SUPPORT == _ON)
                case _D2_INPUT_PORT:

                    // Config DPCD & HPD
                    ScalerDscDecoderSyncDpSupportSwitch(_D2_INPUT_PORT, enumSupport);
                    break;
#endif

                default:
                    break;
            }
#endif
            break;
#endif

        default:
            break;
    }
}

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable MST2SST Branch Dsc Decoder or Not
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
EnumDscDecoderSupport UserCommonDscDecoderMst2sstGetEnable(void)
{
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        return UserInterfaceDscDecoderMst2sstGetEnable();
    }
    else
    {
        return _DSC_DECODER_SUPPORT_OFF;
    }
}
#endif
//--------------------------------------------------
// Description  : Switch Port DSC Capability
// Input Value  : ucPreviousPort, ucCurrentPort
// Output Value :
//--------------------------------------------------
WORD UserCommonDscMenuKeyGetInputPortType(BYTE ucDscMenuKey)
{
    switch(ucDscMenuKey)
    {
        case _DSC_FROM_D0_PORT:
            return _D0_INPUT_PORT_TYPE;
            break;

        case _DSC_FROM_D1_PORT:
            return _D1_INPUT_PORT_TYPE;
            break;

        case _DSC_FROM_D2_PORT:
            return _D2_INPUT_PORT_TYPE;
            break;

        case _DSC_FROM_D3_PORT:
            return _D3_INPUT_PORT_TYPE;
            break;

        case _DSC_FROM_D4_PORT:
            return _D4_INPUT_PORT_TYPE;
            break;

        case _DSC_FROM_D5_PORT:
            return _D5_INPUT_PORT_TYPE;
            break;

        case _DSC_FROM_NO_PORT:
        default:
            return ((_NO_INPUT_PORT << 4) | _PORT_NONE);
            break;
    }

    return ((_NO_INPUT_PORT << 4) | _PORT_NONE);
}

//--------------------------------------------------
// Description  : Get DSC Mode Enabled
// Input Value  : enumInputPort
// Output Value : True  --> Enabled
//                False --> Disabled
//--------------------------------------------------
bit UserCommonDscGetEnable(EnumInputPort enumInputPort)
{
    return (bit)(ScalerDscDecoderDxInputPortGetDscDecoderMac(enumInputPort) != _DSC_MAC_NONE);
}

//--------------------------------------------------
// Description  : Get DSC Version
// Input Value  : enumInputPort
// Output Value : DSC Version
//--------------------------------------------------
BYTE UserCommonDscGetVersion(EnumInputPort enumInputPort)
{
    return ScalerDscDecoderGetDscVersion(ScalerDscDecoderDxInputPortGetDscDecoderMac(enumInputPort));
}

//--------------------------------------------------
// Description  : Get DSC Slice Height
// Input Value  : enumInputPort
// Output Value : DSC Slice Height
//--------------------------------------------------
WORD UserCommonDscGetSliceHeight(EnumInputPort enumInputPort)
{
    return ScalerDscDecoderGetDscSliceHeight(ScalerDscDecoderDxInputPortGetDscDecoderMac(enumInputPort));
}

//--------------------------------------------------
// Description  : Get DSC Slice Width
// Input Value  : enumInputPort
// Output Value : DSC Slice Width
//--------------------------------------------------
WORD UserCommonDscGetSliceWidth(EnumInputPort enumInputPort)
{
    return ScalerDscDecoderGetDscSliceWidth(ScalerDscDecoderDxInputPortGetDscDecoderMac(enumInputPort));
}

//--------------------------------------------------
// Description  : Get DSC Chunk Size
// Input Value  : enumInputPort
// Output Value : DSC Chunk Size
//--------------------------------------------------
WORD UserCommonDscGetChunkSize(EnumInputPort enumInputPort)
{
    return ScalerDscDecoderGetDscChunkSize(ScalerDscDecoderDxInputPortGetDscDecoderMac(enumInputPort));
}

//--------------------------------------------------
// Description  : Get DSC Bit Per Component Value
// Input Value  : enumInputPort
// Output Value : DSC Bit Per Component Value
//--------------------------------------------------
WORD UserCommonDscGetBpc(EnumInputPort enumInputPort)
{
    return ScalerDscDecoderGetDscBpc(ScalerDscDecoderDxInputPortGetDscDecoderMac(enumInputPort));
}

//--------------------------------------------------
// Description  : Get DSC Bit Per Pixel Value
// Input Value  : enumInputPort
// Output Value : DSC Color Depth Bit Per Pixel Value
//--------------------------------------------------
WORD UserCommonDscGetBitPerPixel(EnumInputPort enumInputPort)
{
    // The DSC Bit Per Pixel Precision is 1/16, Then The Return Value Is Multiplied By 16
    // For example, the DSC BPP is 8.125, then the return value is 130, which is multiplied By 16
    return ScalerDscDecoderGetDscBitPerPixel(ScalerDscDecoderDxInputPortGetDscDecoderMac(enumInputPort));
}

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DSC HCactive
// Input Value  : enumInputPort
// Output Value : DSC HCactive
//--------------------------------------------------
WORD UserCommonDscGetHCActive(EnumInputPort enumInputPort)
{
    return ScalerDscDecoderGetDscHCActive(ScalerDscDecoderDxInputPortGetDscDecoderMac(enumInputPort));
}

//--------------------------------------------------
// Description  : Get DSC HCblank
// Input Value  : enumInputPort
// Output Value : DSC HCblank
//--------------------------------------------------
WORD UserCommonDscGetHCBlank(EnumInputPort enumInputPort)
{
    return ScalerDscDecoderGetDscHCBlank(ScalerDscDecoderDxInputPortGetDscDecoderMac(enumInputPort));
}
#endif

#endif
